
#ifndef __QGRAPHICSENGINE__
#define __QGRAPHICSENGINE__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QResourceManager.h"
#include "QViewport.h"
#include "EQPixelFormat.h"
#include "QDeviceContext.h"
#include "EQPrimitiveType.h"
#include "QFramebuffer.h"
#include "QRenderbuffer.h"
#include "QScreenRectangle.h"

// [TODO]: Check framebuffer with glCheckFramebufferStatus
// [TODO]: Clear specific buffer with glClearBuffer
// [TODO]: Invalidation of framebuffer with glInvalidateFramebuffer and glInvalidateSubFramebuffer
// [TODO]: Binding fragment shader output variables with indices to different renderbuffers (glBindFragDataLocation, glBindFragDataLocationIndexed), (glGetFragDataLocation, glGetFragDataIndex) (glEnablei with GL_BLEND or GL_SCISSOR_TEST)



class QGraphicsEngine
{
public:

    enum EQFramebufferOperation
    {
        E_Read,
        E_Write,
        E_ReadAndWrite
    };

    enum EQTestFunction
    {
        E_Never,
        E_Always,
        E_LessThan,
        E_LessThanOrEqual,
        E_Equal,
        E_GreaterThan,
        E_GreaterThanOrEqual,
        E_NotEqual
    };

    enum EQOperationAfterTest
    {
        E_Keep,
        E_Zero,
        E_Replace,
        E_Increment,
        E_IncrementAndWrap,
        E_Decrement,
        E_DecrementAndWrap,
        E_Invert
    };

    enum EQCulledPolygonFace
    {
        E_Front,
        E_Back,
        E_FrontAndBack
    };

    enum EQWindingOrder
    {
        E_Clockwise,
        E_CounterClockwise
    };

    enum EQBufferTypeFlag
    {
        E_Color   = 0x1,
        E_Depth   = 0x2,
        E_Stencil = 0x4
    };

    typedef enum_int_q EQBufferTypeFlags; // Flags: name of the enum in plural to let the user know where to find the values

    enum EQPixelCopyFilter
    {
        E_Linear,
        E_Nearest
    };

    enum EQPixelLayout
    {
        E_Red,
        E_RedInteger,
        E_Green,
        E_GreenInteger,
        E_Blue,
        E_BlueInteger,
        E_Alpha,
        E_AlphaInteger,
        E_RG,
        E_RGInteger,
        E_RGB,
        E_RGBInteger,
        E_RGBA,
        E_RGBAInteger,
        E_BGRA,
        E_BGRAInteger,
        E__Stencil,
        E__Depth,
        E_DepthStencil
    };

    enum EQPixelDataType
    {
        E_U8,
        E_I8,
        E_U16,
        E_I16,
        E_U32,
        E_I32,
        E_F16,
        E_F32,
        E_U8_3_3_2Packed,
        E_U8_2_3_3PackedReversed,
        E_U16_5_6_5Packed,
        E_U16_5_6_5PackedReversed,
        E_U16_4_4_4_4Packed,
        E_U16_4_4_4_4PackedReversed,
        E_U16_5_5_5_1Packed,
        E_U16_5_5_5_1PackedReversed,
        E_U32_8_8_8_8Packed,
        E_U32_8_8_8_8PackedReversed,
        E_U32_10_10_10_2Packed,
        E_U32_2_10_10_10PackedReversed,
        E_U32_24_8Packed,
        E_U32_F10_F11_F11PackedReversed,
        E_U32_5_9_9_9PackedReversed,
        E_F32_F24_U8PackedReversed
    };

    enum EQColorBuffer
    {
        E__Front,
        E__Back,
        E_Left,
        E_Right,
        E_FrontAndLeft,
        E_FrontAndRight,
        E_BackAndLeft,
        E_BackAndRight,
        E__FrontAndBack,
        E_Renderbuffer
    };

protected:

    // [TODO]: Occlussion query
    // [TODO]: Logical operation
    // [TODO]: Scissor test
    // [TODO]: Alpha multisampling

    struct QDepthDrawingStates
    {
        EQTestFunction Function;
    };

    struct QStencilDrawingStates
    {
        EQTestFunction Function;
        EQOperationAfterTest OperationWhenDepthTestPasses;
        EQOperationAfterTest OperationWhenDepthTestFails;
        EQOperationAfterTest OperationWhenStencilTestFails;
    };

    struct QRenderPipelineStates
    {
        QColor ColorBufferClearValue;
        f64_q DepthBufferClearValue;
        f32_q StencilBufferClearValue;
        QViewport Viewport;
        bool IsMultisamplingEnabled;
        bool IsStencilTestEnabled;
        bool IsDepthTestEnabled;
        bool IsFaceCullingEnabled;
        EQCulledPolygonFace CulledFace;
        EQWindingOrder WindingOrder;
        QDepthDrawingStates DepthDrawingStates;
        QStencilDrawingStates StencilDrawingStates;
        QAspect AspectStates;
        QHashedString StaticModel;
    };

    struct QRenderingContext
    {
        QHashedString DeviceContextId;
    };

    struct QRenderingContextOpenGL : public QRenderingContext
    {
        HGLRC Handle;
    };

public:

    QGraphicsEngine(QResourceManager* pResourceManager, QDeviceContext* pDeviceContext) : m_pResourceManager(pResourceManager),
                                                                                          m_renderingContexts(2, 2),
                                                                                          m_deviceContexts(2, 2),
                                                                                          m_framebuffers(5, 2),
                                                                                          m_renderbuffers(5, 2)
    {
        static const QHashedString FAKE_RENDERING_CONTEXT_ID("FAKE");
        this->RegisterDeviceContext(FAKE_RENDERING_CONTEXT_ID, pDeviceContext);
        HGLRC fakeRenderingContext = QGraphicsEngine::_CreateFakeRenderingContextAndInitializeGLEW(pDeviceContext);

        QRenderingContextOpenGL renderingContextInfo;
        renderingContextInfo.Handle = fakeRenderingContext;
        renderingContextInfo.DeviceContextId = FAKE_RENDERING_CONTEXT_ID;
        m_renderingContexts[FAKE_RENDERING_CONTEXT_ID].Add(renderingContextInfo);
    }

    QFramebuffer* CreateFramebuffer(const QHashedString &strId)
    {
        GLuint framebufferId = 0;
        glCreateFramebuffers(1, &framebufferId);
        
        QFramebuffer* pFramebuffer = new QFramebuffer(framebufferId);

        m_framebuffers.Add(strId, pFramebuffer);

        return pFramebuffer;
    }

    void CreateRenderbuffer(const QHashedString &strId,
                            const QRenderbuffer::EQRenderbufferType eType,
                            const QRenderbuffer::EQRenderbufferPixelFormat ePixelFormat,
                            const u32_q uWidth,
                            const u32_q uHeight,
                            const u32_q uSamples)
    {
        GLuint renderbufferId = 0;
        glCreateRenderbuffers(1, &renderbufferId);

        GLenum internalFormat = QGraphicsEngine::_GetEquivalentRenderbufferInternalFormatOpenGLValue(ePixelFormat);

        QRenderbuffer* pRenderbuffer = new QRenderbuffer(renderbufferId,
                                                         QGraphicsEngine::_GetEquivalentRenderbufferAttachmentOpenGLValue(eType),
                                                         internalFormat,
                                                         ePixelFormat,
                                                         eType);
        pRenderbuffer->SetHeight(uHeight);
        pRenderbuffer->SetWidth(uWidth);

        glNamedRenderbufferStorageMultisample(renderbufferId, uSamples, internalFormat, uWidth, uHeight);

        QE_ASSERT_OPENGL_ERROR("An error occurred when storing a renderbuffer (glNamedRenderbufferStorageMultisample).");

        m_renderbuffers.Add(strId, pRenderbuffer);
    }

    void DestroyFramebuffer(const QHashedString &strId) // [TODO]: Add option to destroy associated renderbuffers too
    {
        GLuint framebufferId = m_framebuffers[strId]->GetExternalId();
        glDeleteFramebuffers(1, &framebufferId);
        m_framebuffers.Remove(strId);
    }

    void DestroyRenderbuffer(const QHashedString &strId)
    {
        GLuint renderbufferId = m_renderbuffers[strId]->GetExternalId();
        glDeleteRenderbuffers(1, &renderbufferId);
        m_renderbuffers.Remove(strId);
    }

    void SetSourceFramebuffer(const QHashedString &strFramebufferId)
    {
        static QHashedString DEFAULT_FRAMEBUFFER("DEFAULT");

        GLuint framebufferId = 0;
        GLenum target = 0;

        if (strFramebufferId != DEFAULT_FRAMEBUFFER)
            framebufferId = m_framebuffers[strFramebufferId]->GetExternalId();

        m_strFramebufferForReading = strFramebufferId;

        glBindFramebuffer(QGraphicsEngine::_GetEquivalentFramebufferTargetOpenGLValue(E_Read), framebufferId);

        QE_ASSERT_OPENGL_ERROR("An error occurred when setting a framebuffer (glBindFramebuffer).");
    }

    void SetDestinationFramebuffer(const QHashedString &strFramebufferId)
    {
        static QHashedString DEFAULT_FRAMEBUFFER("DEFAULT");

        GLuint framebufferId = 0;
        GLenum target = 0;

        if (strFramebufferId != DEFAULT_FRAMEBUFFER)
            framebufferId = m_framebuffers[strFramebufferId]->GetExternalId();

        m_strFramebufferForWriting = strFramebufferId;

        glBindFramebuffer(QGraphicsEngine::_GetEquivalentFramebufferTargetOpenGLValue(E_Write), framebufferId);

        QE_ASSERT_OPENGL_ERROR("An error occurred when setting a framebuffer (glBindFramebuffer).");
    }
    
    QFramebuffer* GetFramebuffer(const QHashedString &strId) const
    {
        return m_framebuffers[strId];
    }

    QRenderbuffer* GetRenderbuffer(const QHashedString &strId) const
    {
        return m_renderbuffers[strId];
    }

    void ReadPixelsFromFramebufferColorBuffer(const QHashedString &strFramebufferId, 
                                              const EQColorBuffer eColorBuffer, 
                                              const QScreenRectangle<u32_q> rectangleToRead, 
                                              const EQPixelLayout eDestinationPixelLayout, 
                                              const EQPixelDataType eDestinationType, 
                                              void* pOutput)
    {
        if (m_strFramebufferForReading != strFramebufferId)
            this->SetSourceFramebuffer(strFramebufferId);

        GLuint sourceFramebuffer = strFramebufferId == "DEFAULT" ? 0 : m_framebuffers[strFramebufferId]->GetExternalId();

        glNamedFramebufferReadBuffer(sourceFramebuffer, QGraphicsEngine::_GetEquivalentColorBufferOpenGLValue(eColorBuffer));

        QE_ASSERT_OPENGL_ERROR("An error occurred when setting buffer of the framebuffer to read (glNamedFramebufferReadBuffer).");

        QE_ASSERT_ERROR(sourceFramebuffer == 0 || glCheckNamedFramebufferStatus(sourceFramebuffer, GL_READ_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "The framebuffer is not complete for reading.");

        glReadPixels(rectangleToRead.TopLeftCorner.x,
                     rectangleToRead.TopLeftCorner.y, 
                     rectangleToRead.BottomRightCorner.x, 
                     rectangleToRead.BottomRightCorner.y, 
                     QGraphicsEngine::_GetEquivalentFormatOpenGLValue(eDestinationPixelLayout), 
                     QGraphicsEngine::_GetEquivalentDataTypeOpenGLValue(eDestinationType), 
                     pOutput);

        QE_ASSERT_OPENGL_ERROR("An error occurred when reading pixels from a color buffer (glReadPixels).");
    }

    void WritePixelsToFramebufferColorBuffers(const QHashedString &strFramebufferId, 
                                              const QArrayBasic<EQColorBuffer> arColorBuffers,
                                              const QArrayBasic<u8_q> arRenderbuffers,
                                              const u32_q uWidth, 
                                              const u32_q uHeight, 
                                              const EQPixelLayout eDestinationPixelLayout, 
                                              const EQPixelDataType eDestinationType, 
                                              const void* pInput)
    {
        if (m_strFramebufferForWriting != strFramebufferId)
            this->SetDestinationFramebuffer(strFramebufferId);

        GLenum arEquivalentColorBuffers[GL_MAX_COLOR_ATTACHMENTS + 6U];
        u32_q uAttachmentIndex = 0;
        for (u32_q i = 0; i < arColorBuffers.GetCount(); ++i)
        {
            arEquivalentColorBuffers[i] = QGraphicsEngine::_GetEquivalentColorBufferOpenGLValue(arColorBuffers[i]);

            if (arColorBuffers[i] == E_Renderbuffer)
            {
                QE_ASSERT_ERROR(uAttachmentIndex < arRenderbuffers.GetCount(), "There are renderbuffers without specifying their indices.");

                arEquivalentColorBuffers[i] += arRenderbuffers[uAttachmentIndex];
                ++uAttachmentIndex;
            }
        }

        GLuint destinationFramebuffer = strFramebufferId == "DEFAULT" ? 0 : m_framebuffers[strFramebufferId]->GetExternalId();

        glNamedFramebufferDrawBuffers(destinationFramebuffer, arColorBuffers.GetCount(), arEquivalentColorBuffers);

        QE_ASSERT_OPENGL_ERROR("An error occurred when setting buffers of the framebuffer to write (glNamedFramebufferDrawBuffers).");

        QE_ASSERT_ERROR(destinationFramebuffer == 0 || glCheckNamedFramebufferStatus(destinationFramebuffer, GL_DRAW_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "The framebuffer is not complete for drawing.");

        glDrawPixels(uWidth, uHeight, QGraphicsEngine::_GetEquivalentFormatOpenGLValue(eDestinationPixelLayout), QGraphicsEngine::_GetEquivalentDataTypeOpenGLValue(eDestinationType), pInput);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing pixels to a color buffer (glDrawPixels).");
    }
    
    void CopyPixelsBetweenFramebuffers(const QHashedString &strSourceFramebufferId,
                                       const QHashedString &strDestinationFramebufferId,
                                       const QScreenRectangle<u32_q> rectangleToRead,
                                       const QScreenRectangle<u32_q> rectangleToWrite,
                                       const EQBufferTypeFlags impliedBuffers,
                                       const EQPixelCopyFilter filter)
    {
        if (m_strFramebufferForReading != strSourceFramebufferId)
            this->SetSourceFramebuffer(strSourceFramebufferId);

        if (m_strFramebufferForWriting != strDestinationFramebufferId)
            this->SetDestinationFramebuffer(strDestinationFramebufferId);

        GLbitfield bufferMask = QGraphicsEngine::_GetEquivalentBufferMaskOpenGLValue(impliedBuffers);
        GLenum equivalentFilter = QGraphicsEngine::_GetEquivalentFilterOpenGLValue(filter);

        GLuint sourceFramebuffer = strSourceFramebufferId == "DEFAULT" ? 0 : m_framebuffers[strSourceFramebufferId]->GetExternalId();
        GLuint destinationFramebuffer = strDestinationFramebufferId == "DEFAULT" ? 0 : m_framebuffers[strDestinationFramebufferId]->GetExternalId();

        QE_ASSERT_ERROR(sourceFramebuffer == 0 || glCheckNamedFramebufferStatus(sourceFramebuffer, GL_READ_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "The framebuffer is not complete for reading.");
        QE_ASSERT_ERROR(destinationFramebuffer == 0 || glCheckNamedFramebufferStatus(destinationFramebuffer, GL_DRAW_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "The framebuffer is not complete for drawing.");
        
        glBlitNamedFramebuffer(sourceFramebuffer,
                               destinationFramebuffer,
                               rectangleToRead.TopLeftCorner.x, 
                               rectangleToRead.TopLeftCorner.y, 
                               rectangleToRead.BottomRightCorner.x, 
                               rectangleToRead.BottomRightCorner.y, 
                               rectangleToWrite.TopLeftCorner.x,
                               rectangleToWrite.TopLeftCorner.y, 
                               rectangleToWrite.BottomRightCorner.x, 
                               rectangleToWrite.BottomRightCorner.y, 
                               bufferMask,
                               equivalentFilter);

        QE_ASSERT_OPENGL_ERROR("An error occurred when copying pixels of framebuffers (glBlitNamedFramebuffer).");
    }

    // Using Enable and Disable functions instead of 1 function with boolean parameters just because it is more readable in client's code
    void EnableDepthTest()
    {
        glEnable(GL_DEPTH_TEST);
        m_states.IsDepthTestEnabled = true;
    }

    void DisableDepthTest()
    {
        glDisable(GL_DEPTH_TEST);
        m_states.IsDepthTestEnabled = false;
    }

    void EnableStencilTest()
    {
        glEnable(GL_STENCIL_TEST);
        m_states.IsStencilTestEnabled = true;
    }

    void DisableStencilTest()
    {
        glDisable(GL_STENCIL_TEST);
        m_states.IsStencilTestEnabled = false;
    }

    void EnableMultisampling()
    {
        glEnable(GL_SAMPLE_SHADING);
        m_states.IsMultisamplingEnabled = true;
    }

    void DisableMultisampling()
    {
        glDisable(GL_SAMPLE_SHADING);
        m_states.IsMultisamplingEnabled = false;
    }

    void EnableFaceCulling()
    {
        glEnable(GL_CULL_FACE);
        m_states.IsFaceCullingEnabled = true;
    }

    void DisableFaceCulling()
    {
        glDisable(GL_CULL_FACE);
        m_states.IsFaceCullingEnabled = false;
    }

    void SetFaceCullingMode(const EQCulledPolygonFace eCulledPolygonFace)
    {
        glCullFace(QGraphicsEngine::_GetEquivalentCullFaceModeOpenGLValue(eCulledPolygonFace));
        m_states.CulledFace = eCulledPolygonFace;
    }

    void SetWindingOrder(const EQWindingOrder eWindingOrder)
    {
        glFrontFace(QGraphicsEngine::_GetEquivalentFrontFaceOpenGLValue(eWindingOrder));
        m_states.WindingOrder = eWindingOrder;
    }

    void ClearAllRenderTargets()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void SetColorBufferClearValue(const QColor &color)
    {
        m_states.ColorBufferClearValue = color;
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void SetDepthBufferClearValue(const f64_q &fValue)
    {
        m_states.DepthBufferClearValue = fValue;
        glClearDepth(fValue);
    }

    void SetStencilBufferClearValue(const f32_q &fValue)
    {
        m_states.StencilBufferClearValue = fValue;
        glClearStencil(fValue);
    }

    void SetViewport(const QViewport &viewport)
    {
        QE_ASSERT_ERROR(viewport.Width != 0 && viewport.Height != 0, string_q("Invalid viewport dimensions: ") + viewport.Width + "x" + viewport.Height);

        glViewport(viewport.Left, viewport.Top, viewport.Width, viewport.Height);
        m_states.Viewport = viewport;
    }

    QViewport GetViewport() const
    {
        return m_states.Viewport;
    }

    // Returns the index of the registered DC
    QHashedString RegisterDeviceContext(const QHashedString &strId, QDeviceContext* pDeviceContext)
    {
        QE_ASSERT_ERROR(pDeviceContext != null_q, "The input device context cannot be null.");

        m_deviceContexts.Add(strId, pDeviceContext);
        m_renderingContexts.Add(strId, QArrayDynamic<QRenderingContextOpenGL>(1));

        return strId;
    }

    void UnregisterDeviceContext(const QHashedString &strId)
    {
        m_deviceContexts.Remove(strId);

        // Removes associated rendering contexts
        for (u32_q i = 0; i < m_renderingContexts[strId].GetCount(); ++i)
            this->DestroyRenderingContext(strId, i);

        m_renderingContexts.Remove(strId);
    }

    QDeviceContext* GetDeviceContext(const QHashedString &strId)
    {
        return m_deviceContexts[strId];
    }

    pointer_uint_q GetDeviceContextCount() const
    {
        return m_deviceContexts.GetCount();
    }

    u32_q CreateRenderingContext(const QHashedString &strId, const QHashedString strDeviceContextId, const bool bDebug)
    {
        QE_LOG("LOG: Creating rendering context...\n");

#ifdef QE_OS_WINDOWS

        u32_q uDeviceContextIndex = m_renderingContexts[strDeviceContextId].GetCount();

        HDC deviceContexHandle = m_deviceContexts[strDeviceContextId]->GetNativeDeviceContext();

        int arContextAttributes[] = { WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                                      WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                                      WGL_CONTEXT_MINOR_VERSION_ARB, 5,
                                      WGL_CONTEXT_FLAGS_ARB, bDebug ? WGL_CONTEXT_DEBUG_BIT_ARB : 0,
                                      0, 0 };

        // [TODO]: rendering contexts Sharing?
        HGLRC renderingContextHandle = ::wglCreateContextAttribsARB(deviceContexHandle, null_q, arContextAttributes);

        if (renderingContextHandle == null_q)
        {
            QE_ASSERT_WINDOWS_ERROR("Failed when attempring to create a custom rendering context (wglCreateContextAttribsARB).");
        }

        QRenderingContextOpenGL renderingContext;
        renderingContext.DeviceContextId = strDeviceContextId;
        renderingContext.Handle = renderingContextHandle;
        m_renderingContexts[strDeviceContextId].Add(renderingContext);

        QE_LOG("LOG: OpenGL 4.5 Rendering context created.\n");

        // Makes the rendering context the current one for the current thread
        BOOL bResult = wglMakeCurrent(deviceContexHandle, renderingContextHandle);

        QE_ASSERT_ERROR(bResult == TRUE, "An error occurred when setting the new rendering context as the current.");

#endif
        QGraphicsEngine::_InitializeGLEW();

        return uDeviceContextIndex;
    }

    void DestroyRenderingContext(const QHashedString strDeviceContextId, const u32_q uRenderingContextIndex)
    {
#ifdef QE_OS_WINDOWS
        
        if (::wglGetCurrentContext() == m_renderingContexts[strDeviceContextId][uRenderingContextIndex].Handle)
            ::wglMakeCurrent(0, 0);

        BOOL bResult = ::wglDeleteContext(m_renderingContexts[strDeviceContextId][uRenderingContextIndex].Handle);

        QE_ASSERT_ERROR(bResult != 0, "The rendering context could not be deleted (wglDeleteContext).");

        m_renderingContexts[strDeviceContextId].Remove(uRenderingContextIndex);

#endif
    }

    void SwapBuffers()
    {
        typedef QHashtable<QHashedString, QDeviceContext*, SQStringHashProvider> DeviceContextContainer;

        for (DeviceContextContainer::ConstIterator it = m_deviceContexts.GetFirst(); !it.IsEnd(); ++it)
        {
            BOOL bResult = ::SwapBuffers(it->GetValue()->GetNativeDeviceContext());

            if (bResult == FALSE)
            {
                QE_TRACE_WINDOWS_ERROR("Rendering buffers could not be swapped (SwapBuffers).");
            }
        }
    }

    void SwapBuffers(const QHashedString strDeviceContextId)
    {
#ifdef QE_OS_WINDOWS

        BOOL bResult = ::SwapBuffers(m_deviceContexts[strDeviceContextId]->GetNativeDeviceContext());

        if (bResult == FALSE)
        {
            QE_TRACE_WINDOWS_ERROR("Rendering buffers could not be swapped (SwapBuffers).");
        }

#endif
    }

    void SetShadingPipeline(const QHashedString &strId)
    {
        QShadingPipeline* pShadingPipeline = m_pResourceManager->GetShadingPipeline(strId);

        // Makes the program the current
        glBindProgramPipeline(pShadingPipeline->GetExternalId());
    }

    void SetStaticModel(const QHashedString &strId)
    {
        QStaticModel* pModel = m_pResourceManager->GetStaticModel(strId);

        glBindVertexArray(pModel->GetExternalId());
    }

    void Draw(const EQPrimitiveType::EnumType ePrimitiveType, const u32_q uFirstVertex, const u32_q uVertexCount, const u32_q uFirstIndex, const u32_q uIndexCount)
    {
        // [TODO]: Add conditional logging
        if (uVertexCount == 0)
            QE_LOG("The number of vertex to draw is zero (Draw).\n");

        if (uIndexCount == 0)
            QE_LOG("The number of vertex to draw is zero (Draw).\n");

        glDrawRangeElementsBaseVertex(GL_TRIANGLES, uFirstVertex, uFirstVertex + uVertexCount, uIndexCount, GL_UNSIGNED_INT, (void*)(uFirstIndex * sizeof(u32_q)), uFirstVertex);
    }

    void SetTexture(const QHashedString &strTextureId, const unsigned int uTextureLayer, const QHashedString &strShaderId, const char* szShaderSamplerName)
    {
        QShader* pFragmentShader = m_pResourceManager->GetShader(strShaderId);
        QTexture2D* pTexture = m_pResourceManager->GetTexture2D(strTextureId);

        if (pTexture)
        {
            glActiveTexture(GL_TEXTURE0 + uTextureLayer);
            glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureID());

            GLint samplerLocation = glGetUniformLocation(pFragmentShader->GetExternalId(), szShaderSamplerName);

            if (samplerLocation == -1)
            {
                QE_ASSERT_OPENGL_ERROR("An error occurred while getting the location of a uniform (glGetUniformLocation).");
            }
            
            glProgramUniform1i(pFragmentShader->GetExternalId(), samplerLocation, uTextureLayer);

            //QE_LOG(string_q("LOG: Using texture [") + strTextureId + "] in sampler \"" + szShaderSamplerName + "\" with index " + uTextureLayer + ".\n");
        }
    }

    void SetSampler2D(const QHashedString &strSampler2DId, const unsigned int uTextureLayer)
    {
        QSampler2D* pSampler = m_pResourceManager->GetSampler2D(strSampler2DId);

        glBindSampler(uTextureLayer, pSampler->GetOpenGLId());
    }

    void SetAspect(const QHashedString &strAspectId)
    {
        //QE_LOG(string_q("LOG: Setting aspect [") + strAspectId + "]...\n");

        QAspect* pAspect = m_pResourceManager->GetAspect(strAspectId);

        this->SetShadingPipeline(pAspect->GetShadingPipelineId());

        QMaterial* pMaterial = m_pResourceManager->GetMaterial(pAspect->GetMaterial());

        // [TODO]: Loop of textures
        this->SetTexture(pAspect->GetTexture(QAspect::E_Diffuse, 0), 0, pAspect->GetShadingPipeline()->GetFragmentShaderId(), "sampler1"); // It's possible to send textures to Vertex Shader for spherical mapping

        this->SetSampler2D(pAspect->GetTextureSampler2D(QAspect::E_Diffuse, 0), 0);

        // [TODO]: Alpha blending

        //QE_LOG(string_q("LOG: Aspect [") + strAspectId + "] set.\n");
    }

    void UpdateVertexShaderData(const QHashedString &strVertexShaderId, const string_q &strDataBufferName, const f32_q fValue0, const f32_q fValue1, const f32_q fValue2, const f32_q fValue3)
    {
        QShader* pVertexShader = m_pResourceManager->GetShader(strVertexShaderId);

        GLint bufferLocation = glGetUniformLocation(pVertexShader->GetExternalId(), strDataBufferName.ToBytes(EQTextEncoding::E_ASCII).Get());

        QE_ASSERT_ERROR(bufferLocation != -1, string_q("The shader data buffer with name \"") + strDataBufferName + "\" was not found in the shader with ID \"" + strVertexShaderId + "\".");
        
        glProgramUniform4f(pVertexShader->GetExternalId(), bufferLocation, fValue0, fValue1, fValue2, fValue3);
    }

    void UpdateVertexShaderData(const QHashedString &strVertexShaderId, const string_q &strDataBufferName, const QBaseMatrix4x4 &matrix)
    {
        QShader* pVertexShader = m_pResourceManager->GetShader(strVertexShaderId);

        // Store the location of every uniform so this call does not have to be performed every time
        GLint bufferLocation = glGetUniformLocation(pVertexShader->GetExternalId(), strDataBufferName.ToBytes(EQTextEncoding::E_ASCII).Get());

        QE_ASSERT_ERROR(bufferLocation != -1, string_q("The shader data buffer with name \"") + strDataBufferName + "\" was not found in the shader with ID \"" + strVertexShaderId + "\".");

        glProgramUniformMatrix4fv(pVertexShader->GetExternalId(), bufferLocation, 1, GL_FALSE, &matrix.ij[0][0]); // No traspose
    }

    // Should receive pointers instead of string ids? performance vs robustness
    void UpdateFragmentShaderData(const QHashedString &strVertexShaderId, const string_q &strDataBufferName, const f32_q fValue0, const f32_q fValue1, const f32_q fValue2, const f32_q fValue3)
    {
        QShader* pFragmentShader = m_pResourceManager->GetShader(strVertexShaderId);

        GLint bufferLocation = glGetUniformLocation(pFragmentShader->GetExternalId(), strDataBufferName.ToBytes(EQTextEncoding::E_ASCII).Get());

        QE_ASSERT_ERROR(bufferLocation != -1, string_q("The shader data buffer with name \"") + strDataBufferName + "\" was not found in the shader with ID \"" + strVertexShaderId + "\".");

        glProgramUniform4f(pFragmentShader->GetExternalId(), bufferLocation, fValue0, fValue1, fValue2, fValue3);
    }

protected:

    static HGLRC _CreateFakeRenderingContextAndInitializeGLEW(QDeviceContext* pDeviceContext)
    {
#ifdef QE_OS_WINDOWS

        PIXELFORMATDESCRIPTOR desc;
        int nPixelFormat = ::ChoosePixelFormat(pDeviceContext->GetNativeDeviceContext(), &desc);
        ::SetPixelFormat(pDeviceContext->GetNativeDeviceContext(), nPixelFormat, &desc);

#endif

        HGLRC renderingContext = ::wglCreateContext(pDeviceContext->GetNativeDeviceContext());

        QE_ASSERT_ERROR(renderingContext != null_q, "The rendering context could not be created (wglCreateContext).");
        QE_ASSERT_WINDOWS_ERROR("The rendering context could not be created (wglCreateContext).");

        BOOL bResult = ::wglMakeCurrent(pDeviceContext->GetNativeDeviceContext(), renderingContext);

        QE_ASSERT_ERROR(bResult == TRUE, "The rendering context could not be set as current (wglMakeCurrent).");

        QGraphicsEngine::_InitializeGLEW();

        return renderingContext;
    }

    static void _InitializeGLEW()
    {
        glewExperimental = GL_TRUE;
        GLenum eInitResult = glewInit();

#ifdef QE_OS_WINDOWS
        // The call to glewInit may cause the last error code to be set to a not found module
        ::SetLastError(0);
        // The call to glewInit may cause the last OpenGL error code to be set to GL_INVALID_ENUM, which has to be ignored
        glGetError(); // The error code is reset
#endif

        QE_ASSERT_ERROR(eInitResult == GLEW_OK, string_q("An error occurred when attempting to initialize GLEW. ") + rcast_q(glewGetErrorString(eInitResult), const i8_q*));

        const GLubyte* u = glewGetErrorString(eInitResult);
        QE_LOG(string_q("LOG: GLEW Initialized (") + rcast_q(glewGetString(GLEW_VERSION), const i8_q*) + ")\n");
        QE_LOG(string_q("LOG: Open GL Version ") + rcast_q(glGetString(GL_VERSION), const i8_q*) + "\n");
    }

    static GLenum _GetEquivalentCullFaceModeOpenGLValue(const EQCulledPolygonFace eCulledPolygonFace)
    {
        GLenum eCulledFace = GL_BACK;

        switch (eCulledPolygonFace)
        {
        case E_Front:
            eCulledFace = GL_FRONT;
            break;
        case E_Back:
            eCulledFace = GL_BACK;
            break;
        case E_FrontAndBack:
            eCulledFace = GL_FRONT_AND_BACK;
            break;
        default:
            break;
        }

        return eCulledFace;
    }

    static GLenum _GetEquivalentFrontFaceOpenGLValue(const EQWindingOrder eWindingOrder)
    {
        GLenum eFrontFace = GL_CW;

        switch (eWindingOrder)
        {
        case E_CounterClockwise:
            eFrontFace = GL_CCW;
            break;
        case E_Clockwise:
            eFrontFace = GL_CW;
            break;
        default:
            break;
        }

        return eFrontFace;
    }

    static GLenum _GetEquivalentRenderbufferInternalFormatOpenGLValue(const QRenderbuffer::EQRenderbufferPixelFormat eType)
    {
        static const GLenum EQUIVALENT_VALUES[] = {
                                                    GL_R8,//E_R8UI_Normalized,
                                                    GL_R16,//E_R16UI_Normalized,
                                                    GL_RG,//E_RGUI_Normalized,
                                                    GL_RG8,//E_RG8UI_Normalized,
                                                    GL_RG16,//E_RG16UI_Normalized,
                                                    GL_R3_G3_B2,//E_R3G3B2UI_Normalized,
                                                    GL_RGB4,//E_RGB4UI_Normalized,
                                                    GL_RGB5,//E_RGB5UI_Normalized,
                                                    GL_RGB8,//E_RGB8UI_Normalized,
                                                    GL_RGB10,//E_RGB10UI_Normalized,
                                                    GL_RGB12,//E_RGB12UI_Normalized,
                                                    GL_RGB16,//E_RGB16UI_Normalized,
                                                    GL_RGBA2,//E_RGBA2UI_Normalized,
                                                    GL_RGBA4,//E_RGBA4UI_Normalized,
                                                    GL_RGB5_A1,//E_RGB5A1UI_Normalized,
                                                    GL_RGBA8,//E_RGBA8UI_Normalized,
                                                    GL_RGB10_A2,//E_RGB10A2UI_Normalized,
                                                    GL_RGBA12,//E_RGBA12UI_Normalized,
                                                    GL_RGBA16,//E_RGBA16UI_Normalized,
                                                    GL_SRGB8,//E_RGB8_Compressed,
                                                    GL_SRGB8_ALPHA8,//E_RGB8A8_Compressed,
                                                    GL_R16F,//E_R16F,
                                                    GL_R32F,//E_R32F,
                                                    GL_RG16F,//E_RG16F,
                                                    GL_RG32F,//E_RG32F,
                                                    GL_RGB16F,//E_RGB16F,
                                                    GL_RGB32F,//E_RGB32F,
                                                    GL_RGBA16F,//E_RGBA16F,
                                                    GL_RGBA32F,//E_RGBA32F,
                                                    GL_R11F_G11F_B10F,//E_R11FG11FB10F,
                                                    GL_RGB9_E5,//E_RGB9E5,
                                                    GL_R8I,//E_R8I,
                                                    GL_R8UI,//E_R8UI,
                                                    GL_R16I,//E_R16I,
                                                    GL_R16UI,//E_R16UI,
                                                    GL_R32I,//E_R32I,
                                                    GL_R32UI,//E_R32UI,
                                                    GL_RG8I,//E_RG8I,
                                                    GL_RG8UI,//E_RG8UI,
                                                    GL_RG16I,//E_RG16I,
                                                    GL_RG16UI,//E_RG16UI,
                                                    GL_R32I,//E_RG32I,
                                                    GL_R32UI,//E_RG32UI,
                                                    GL_RGB8I,//E_RGB8I,
                                                    GL_RGB8UI,//E_RGB8UI,
                                                    GL_RGB16I,//E_RGB16I,
                                                    GL_RGB16UI,//E_RGB16UI,
                                                    GL_RGB32I,//E_RGB32I,
                                                    GL_RGB32UI,//E_RGB32UI,
                                                    GL_RGBA8I,//E_RGBA8I,
                                                    GL_RGBA8UI,//E_RGBA8UI,
                                                    GL_RGBA16I,//E_RGBA16I,
                                                    GL_RGBA16UI,//E_RGBA16UI,
                                                    GL_RGBA32I,//E_RGBA32I,
                                                    GL_RGBA32UI,//E_RGBA32UI,
                                                    GL_R8_SNORM,//E_R8I_Normalized,
                                                    GL_R16_SNORM,//E_R16I_Normalized,
                                                    GL_RG8_SNORM,//E_RG8I_Normalized,
                                                    GL_RG16_SNORM,//E_RG16I_Normalized,
                                                    GL_RGB8_SNORM,//E_RGB8I_Normalized,
                                                    GL_RGB16_SNORM,//E_RGB16I_Normalized,
                                                    GL_RGBA8_SNORM,//E_RGBA8I_Normalized,
                                                    GL_RGBA16_SNORM,//E_RGBA16I_Normalized,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0,
                                                    GL_DEPTH_COMPONENT16,//E_D16,
                                                    GL_DEPTH_COMPONENT24,//E_D24,
                                                    GL_DEPTH_COMPONENT32,//E_D32,
                                                    GL_DEPTH_COMPONENT32F,//E_D32F,
                                                    0, 0, 0, 0, 0, 0,
                                                    GL_STENCIL_INDEX1,//E_S1,
                                                    GL_STENCIL_INDEX4,//E_S4,
                                                    GL_STENCIL_INDEX8,//E_S8,
                                                    GL_STENCIL_INDEX16,//E_S16,
                                                    0, 0, 0, 0, 0, 0,
                                                    GL_DEPTH24_STENCIL8,//E_D24S8,
                                                    GL_DEPTH32F_STENCIL8,//E_D32FS8
                                                    0, 0, 0
                                                };
        return EQUIVALENT_VALUES[eType];
    }

    static GLenum _GetEquivalentRenderbufferAttachmentOpenGLValue(const QRenderbuffer::EQRenderbufferType eType)
    {
        static const GLenum EQUIVALENT_VALUES[] = {
                                                    GL_COLOR_ATTACHMENT0,
                                                    GL_DEPTH_ATTACHMENT,
                                                    GL_STENCIL_ATTACHMENT,
                                                    GL_DEPTH_STENCIL_ATTACHMENT
                                                };

        return EQUIVALENT_VALUES[eType];
    }

    static GLenum _GetEquivalentFramebufferTargetOpenGLValue(const EQFramebufferOperation eTarget)
    {
        static const GLenum EQUIVALENT_VALUES[] = {
                                                    GL_READ_FRAMEBUFFER,
                                                    GL_DRAW_FRAMEBUFFER,
                                                    GL_FRAMEBUFFER
                                                };
        return EQUIVALENT_VALUES[eTarget];
    }

    static GLenum _GetEquivalentColorBufferOpenGLValue(const EQColorBuffer eColorBuffer)
    {
        static const GLenum EQUIVALENT_VALUES[] = {
                                                    GL_FRONT,//E_Front,
                                                    GL_BACK,//E_Back,
                                                    GL_LEFT,//E_Left,
                                                    GL_RIGHT,//E_Right,
                                                    GL_FRONT_LEFT,//E_FrontAndLeft,
                                                    GL_FRONT_RIGHT,//E_FrontAndRight,
                                                    GL_BACK_LEFT,//E_BackAndLeft,
                                                    GL_BACK_RIGHT,//E_BackAndRight,
                                                    GL_FRONT_AND_BACK,//E_FrontAndBack,
                                                    GL_COLOR_ATTACHMENT0//E_Renderbuffer
                                                  };

        return EQUIVALENT_VALUES[eColorBuffer];
    }

    static GLenum _GetEquivalentFormatOpenGLValue(const EQPixelLayout ePixelLayout)
    {
        static const GLenum EQUIVALENT_VALUES[] = {
                                                    GL_RED,//E_Red,
                                                    GL_RED_INTEGER,//E_RedInteger,
                                                    GL_GREEN,//E_Green,
                                                    GL_GREEN_INTEGER,//E_GreenInteger,
                                                    GL_BLUE,//E_Blue,
                                                    GL_BLUE_INTEGER,//E_BlueInteger,
                                                    GL_ALPHA,//E_Alpha,
                                                    GL_ALPHA_INTEGER,//E_AlphaInteger,
                                                    GL_RG,//E_RG,
                                                    GL_RG_INTEGER,//E_RGInteger,
                                                    GL_RGB,//E_RGB,
                                                    GL_RGB_INTEGER,//E_RGBInteger,
                                                    GL_RGBA,//E_RGBA,
                                                    GL_RGBA_INTEGER,//E_RGBAInteger,
                                                    GL_BGRA,//E_BGRA,
                                                    GL_BGRA_INTEGER,//E_BGRAInteger,
                                                    GL_STENCIL,//E_Stencil,
                                                    GL_DEPTH,//E_Depth,
                                                    GL_DEPTH_STENCIL//E_DepthStencil
                                                };

        return EQUIVALENT_VALUES[ePixelLayout];
    }

    static GLenum _GetEquivalentDataTypeOpenGLValue(const EQPixelDataType ePixelDataType)
    {
        static const GLenum EQUIVALENT_VALUES[] = {
                                                    GL_UNSIGNED_BYTE,//E_U8,
                                                    GL_BYTE,//E_I8,
                                                    GL_UNSIGNED_SHORT,//E_U16,
                                                    GL_SHORT,//E_I16,
                                                    GL_UNSIGNED_INT,//E_U32,
                                                    GL_INT,//E_I32,
                                                    GL_HALF_FLOAT,//E_F16,
                                                    GL_FLOAT,//E_F32,
                                                    GL_UNSIGNED_BYTE_3_3_2,//E_U8_3_3_2Packed,
                                                    GL_UNSIGNED_BYTE_2_3_3_REV,//E_U8_2_3_3PackedReversed,
                                                    GL_UNSIGNED_SHORT_5_6_5,//E_U16_5_6_5Packed,
                                                    GL_UNSIGNED_SHORT_5_6_5_REV,//E_U16_5_6_5PackedReversed,
                                                    GL_UNSIGNED_SHORT_4_4_4_4,//E_U16_4_4_4_4Packed,
                                                    GL_UNSIGNED_SHORT_4_4_4_4_REV,//E_U16_4_4_4_4PackedReversed,
                                                    GL_UNSIGNED_SHORT_5_5_5_1,//E_U16_5_5_5_1Packed,
                                                    GL_UNSIGNED_SHORT_1_5_5_5_REV,//E_U16_5_5_5_1PackedReversed,
                                                    GL_UNSIGNED_INT_8_8_8_8,//E_U32_8_8_8_8Packed,
                                                    GL_UNSIGNED_INT_8_8_8_8_REV,//E_U32_8_8_8_8PackedReversed,
                                                    GL_UNSIGNED_INT_10_10_10_2,//E_U32_10_10_10_2Packed,
                                                    GL_UNSIGNED_INT_2_10_10_10_REV,//E_U32_2_10_10_10PackedReversed,
                                                    GL_UNSIGNED_INT_24_8,//E_U32_24_8Packed,
                                                    GL_UNSIGNED_INT_10F_11F_11F_REV,//E_U32_F10_F11_F11PackedReversed,
                                                    GL_UNSIGNED_INT_5_9_9_9_REV,//E_U32_5_9_9_9PackedReversed,
                                                    GL_FLOAT_32_UNSIGNED_INT_24_8_REV//E_F32_F24_U8PackedReversed
                                                };

        return EQUIVALENT_VALUES[ePixelDataType];
    }

    static GLenum _GetEquivalentFilterOpenGLValue(const EQPixelCopyFilter eFilter)
    {
        static const GLenum EQUIVALENT_VALUES[] = {
                                                    GL_LINEAR,
                                                    GL_NEAREST
                                                  };

        return EQUIVALENT_VALUES[eFilter];
    }

    static GLenum _GetEquivalentBufferTypeOpenGLValue(const EQBufferTypeFlag eBufferType)
    {
        static const GLenum EQUIVALENT_VALUES[] = { 0,
                                                    GL_COLOR_BUFFER_BIT,//E_Color,
                                                    GL_DEPTH_BUFFER_BIT,//E_Depth,
                                                    0,
                                                    GL_STENCIL_BUFFER_BIT//E_Stencil
                                                };

        return EQUIVALENT_VALUES[eBufferType];
    }

    static GLbitfield _GetEquivalentBufferMaskOpenGLValue(const EQBufferTypeFlags bufferMask)
    {
        GLbitfield mask = 0;

        mask = mask | ((bufferMask & E_Color)   ? QGraphicsEngine::_GetEquivalentBufferTypeOpenGLValue(E_Color)   : 0);
        mask = mask | ((bufferMask & E_Depth)   ? QGraphicsEngine::_GetEquivalentBufferTypeOpenGLValue(E_Depth)   : 0);
        mask = mask | ((bufferMask & E_Stencil) ? QGraphicsEngine::_GetEquivalentBufferTypeOpenGLValue(E_Stencil) : 0);

        return mask;
    }

protected:

    QResourceManager* m_pResourceManager;
    QHashtable<QHashedString, QDeviceContext*, SQStringHashProvider> m_deviceContexts;
    // 1 window -> many rendering contexts
    QHashtable<QHashedString, QArrayDynamic<QRenderingContextOpenGL>, SQStringHashProvider> m_renderingContexts;

    // Graphic pipeline states
    QRenderPipelineStates m_states;

    QHashedString m_strActiveAspect;
    QHashedString m_strFramebufferForReading;
    QHashedString m_strFramebufferForWriting;
    QHashtable<QHashedString, QFramebuffer*, SQStringHashProvider> m_framebuffers;
    QHashtable<QHashedString, QRenderbuffer*, SQStringHashProvider> m_renderbuffers;
};

#endif // __QGRAPHICSENGINE__