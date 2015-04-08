
#ifndef __QGRAPHICSENGINE__
#define __QGRAPHICSENGINE__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QResourceManager.h"
#include "QViewport.h"
#include "EQPixelFormat.h"

class QGraphicsEngine
{
public:

    enum EQRenderbufferElementType
    {
    };

    enum EQRenderbufferType
    {
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
    };

    class QFramebuffer
    {
    public:

        QArrayDynamic<QHashedString> ColorBuffers;
        QHashedString DepthBuffer;
        QHashedString StencilBuffer;
    };

    class QFramebufferOpenGL : public QFramebuffer
    {
    public:

        GLuint Id;
    };

    struct QRenderbuffer
    {
        u32_q Width;
        u32_q Height;
    };

    struct QRenderbufferOpenGL : public QRenderbuffer
    {
        GLuint Id;
        GLenum Type;
        GLenum ElementType;
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
                                                                                          m_pipelineId(0),
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

    void CreateFramebuffer(const QHashedString &strId)
    {
        GLuint framebufferId = 0;
        glGenFramebuffers(1, &framebufferId);

        QFramebufferOpenGL* pFramebuffer = new QFramebufferOpenGL();
        pFramebuffer->Id = framebufferId;

        m_framebuffers.Add(strId, pFramebuffer);
    }

    void CreateRenderbuffer(const QHashedString &strId, const EQRenderbufferType eType, const EQRenderbufferElementType eElementType)
    {
    }

    void DestroyFramebuffer(const QHashedString &strId)
    {
    }

    void DestroyRenderbuffer(const QHashedString &strId)
    {
    }

    void SetRenderTarget(const QHashedString &strId)
    {
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
        glFrontFace(QGraphicsEngine::_GetEquicalentFrontFaceOpenGLValue(eWindingOrder));
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
                                      WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                                      WGL_CONTEXT_FLAGS_ARB, bDebug ? WGL_CONTEXT_DEBUG_BIT_ARB : 0,
                                      0, 0 };

        // [TODO]: rendering contexts Sharing?
        HGLRC renderingContextHandle = ::wglCreateContextAttribsARB(deviceContexHandle, null_q, arContextAttributes);

        if (renderingContextHandle == null_q)
        {
            QE_ASSERT_WINDOWS_ERROR("Failed when attempring to create a custom rendering context (wglCreateContext).");
        }

        QRenderingContextOpenGL renderingContext;
        renderingContext.DeviceContextId = strDeviceContextId;
        renderingContext.Handle = renderingContextHandle;
        m_renderingContexts[strDeviceContextId].Add(renderingContext);

        QE_LOG("LOG: OpenGL 4.3 Rendering context created.\n");

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

    void SetVertexShader(const QHashedString &strId)
    {
/////////////////////////////---------------------------------------------------------------------MOVE THIS TO ASPECT!!!!
        glGenProgramPipelines(1, &m_pipelineId);
        glBindProgramPipeline(m_pipelineId);

        QE_LOG("LOG: Pogram pipeline set.\n");
///////////////////////////////----------------------------------------------------------------------
        QShader* pVertexShader = m_pResourceManager->GetShader(strId);

        // Makes the program the current
        glUseProgramStages(m_pipelineId, GL_VERTEX_SHADER_BIT, pVertexShader->GetExternalId());

        //QE_LOG(string_q("LOG: Using vertex shader [") + strId + "].\n");
    }

    void SetFragmentShader(const QHashedString &strId)
    {
        QShader* pFragmentShader = m_pResourceManager->GetShader(strId);

        // Makes the program the current
        glUseProgramStages(m_pipelineId, GL_FRAGMENT_SHADER_BIT, pFragmentShader->GetExternalId());

        //QE_LOG(string_q("LOG: Using fragment shader [") + strId + "].\n");
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
                QE_ASSERT_WINDOWS_ERROR("An error occurred while getting the location of a uniform (SetupTextures).");
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

        this->SetVertexShader(pAspect->GetVertexShader());
        this->SetFragmentShader(pAspect->GetFragmentShader());

        QMaterial* pMaterial = m_pResourceManager->GetMaterial(pAspect->GetMaterial());

        // [TODO]: Loop of textures
        this->SetTexture(pAspect->GetTexture(QAspect::E_Diffuse, 0), 0, pAspect->GetFragmentShader(), "sampler1"); // It's possible to send textures to Vertex Shader for spherical mapping

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

    static GLenum _GetEquicalentFrontFaceOpenGLValue(const EQWindingOrder eWindingOrder)
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

protected:

    QResourceManager* m_pResourceManager;
    QHashtable<QHashedString, QDeviceContext*, SQStringHashProvider> m_deviceContexts;
    // 1 window -> many rendering contexts
    QHashtable<QHashedString, QArrayDynamic<QRenderingContextOpenGL>, SQStringHashProvider> m_renderingContexts;

    // This should be in the QAspect class, which stores both vertex and fragment shaders
    GLuint m_pipelineId;

    // Graphic pipeline states
    QRenderPipelineStates m_states;

    QHashedString m_activeAspect;
    QHashedString m_activeFramebuffer;
    QHashtable<QHashedString, QFramebuffer*, SQStringHashProvider> m_framebuffers;
    QHashtable<QHashedString, QRenderbuffer*, SQStringHashProvider> m_renderbuffers;
};

#endif // __QGRAPHICSENGINE__