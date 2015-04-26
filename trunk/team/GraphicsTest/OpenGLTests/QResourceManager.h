
#ifndef __QRESOURCEMANAGER__
#define __QRESOURCEMANAGER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QShader.h"
#include "QShader.h"
#include "QShaderCompositor.h"
#include "QTexture1D.h"
#include "QTexture2D.h"
#include "QTexture3D.h"
#include "QImage.h"
#include "QAspect.h"
#include "QStaticModel.h"
#include "VertexDefinitions.h"
#include "QModelLoader.h"
#include "QImageLoader.h"
#include "QStaticModelRawData.h"
#include "QModelAspectsRawData.h"
#include "QBuffer.h"
#include "QAlphaBlender.h"
#include "ErrorTracingDefinitions.h"
#include "QShadingPipeline.h"
#include "SQEnumerationToOpenGLConverter.h"

// [TODO]: Unbind objects when they are deleted
// [TODO]: Add the capability of creating memory blocks, so every time a resource is created, it is associated to the block Id in such a way that the user can destroy the entire block with one call

// There will not be Mutable Textures, only immutable textures used via glTexStorage, at first sight there is no reason to allow changing a texture layout and there are some dangers, see:
// http://stackoverflow.com/questions/17946881/what-techniques-require-mutable-texture-storage
// Also DX does not seem to provide any similar feature


// The resource manager should receive a set of factories, one per type of asset, depending on whether using DirectX or OpenGL
class QResourceManager
{
public:

    QResourceManager(QShaderCompositor* pShaderCompositor) : 
                                                             m_arMaterials(5, 2),
                                                             m_arAspects(5, 2),
                                                             m_arImages(5, 2),
                                                             m_arTextures1D(5, 2),
                                                             m_arTextures2D(5, 2),
                                                             m_arTextures3D(5, 2),
                                                             m_arStaticModels(5, 2),
                                                             m_arSamplers2D(5, 2),
                                                             m_arTextureBlenders(5, 2),
                                                             m_arBuffers(5, 2),
                                                             m_arAlphaBlenders(5, 2),
                                                             m_arShaders(5, 2),
                                                             m_arShadingPipelines(5, 2),
                                                             m_pShaderCompositor(pShaderCompositor)
    {
    }

    QKeyValuePair<QHashedString, QShader*> CreateShader(const QHashedString strId, const QPath &shaderPath, const QShader::EQShaderType eShaderType)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arShaders);
        
        QShader* pShader = m_pShaderCompositor->CompileAndLinkShader(shaderPath, eShaderType, null_q, null_q);
        m_arShaders.Add(strDefinitiveId, pShader);
        return QKeyValuePair<QHashedString, QShader*>(strDefinitiveId, pShader);
    }

    // It is necessary to differentiate the type of image, (integer, float)
    // Maybe images should not be created using different factories for either graphic library

    // [TODO]: Implement fallback mechanism to attempt loading the image from the current working directory

    QKeyValuePair<QHashedString, QImage*> CreateImage(const QHashedString strId, const QPath &imagePath, const QImage::EQImageColorComponents eColorComponents)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arImages);
        
        QImageLoader loader;
        QImage* pNewImage = loader.LoadImage(imagePath, eColorComponents);

        if (!pNewImage)
        {
            strDefinitiveId = "DEFAULT";
            QE_LOG(string_q("An error occurred when loading the image with ID \"") + strId + "\" from \"" + imagePath.ToString() + "\".\n");
        }
        else
        {
            m_arImages.Add(strDefinitiveId, pNewImage);
        }
        
        return QKeyValuePair<QHashedString, QImage*>(strDefinitiveId, pNewImage);
    }

    QKeyValuePair<QHashedString, QImage*> CreateImage(const QHashedString strId, const void* pImageBuffer, const pointer_uint_q uBufferSize, const QImage::EQImageColorComponents eColorComponents)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arImages);
        
        QImageLoader loader;
        QImage* pNewImage = loader.LoadImage(pImageBuffer, uBufferSize, eColorComponents);

        if (!pNewImage)
        {
            strDefinitiveId = "DEFAULT";
            QE_LOG(string_q("An error occurred when loading the image with ID \"") + strId + "\".\n");
        }
        else
        {
            m_arImages.Add(strDefinitiveId, pNewImage);
        }

        return QKeyValuePair<QHashedString, QImage*>(strDefinitiveId, pNewImage);
    }

    QKeyValuePair<QHashedString, QTexture2D*> CreateTexture2D(const QHashedString strId, const QHashedString &strImageId, const QImage::EQImageColorComponents eImageFormat)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arTextures2D);
        
        QImage* pImage = this->GetImage(strImageId);
        QTexture2D* pTexture = null_q;

        if (pImage)
        {
            GLint nFormat = eImageFormat == QImage::E_RGB ? GL_RGB8 :
                                                            eImageFormat == QImage::E_RGBA ? GL_RGBA8 :
                                                                                             0;
            GLint nLayout = eImageFormat == QImage::E_RGB ? GL_RGB :
                                                            eImageFormat == QImage::E_RGBA ? GL_RGBA :
                                                                                             0;
            EQPixelFormat::EnumType eFormat = QImage::E_RGB ? EQPixelFormat::E_RGB8UI_Normalized :
                                                              eImageFormat == QImage::E_RGBA ? EQPixelFormat::E_RGBA8UI_Normalized :
                                                                                               EQPixelFormat::E_Undefined;

            static const GLint MIPMAP_LEVELS = 1;
            GLuint textureID = 0;
            glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
            glTextureStorage2D(textureID, MIPMAP_LEVELS, nFormat, pImage->GetWidth(), pImage->GetHeight());

            QE_ASSERT_OPENGL_ERROR("An error occurred when reserving memory for the texture.");

            static const GLint MIPMAP_LEVEL = 0;
            static const GLint OFFSET_X = 0;
            static const GLint OFFSET_Y = 0;
            static const GLenum PIXEL_DATA_TYPE = GL_UNSIGNED_BYTE;
            glTextureSubImage2D(textureID, MIPMAP_LEVEL, OFFSET_X, OFFSET_Y, pImage->GetWidth(), pImage->GetHeight(), nLayout, PIXEL_DATA_TYPE, pImage->GetData());

            QE_ASSERT_OPENGL_ERROR("An error occurred when copying image data to the texture.");

            static const u8_q NUM_SAMPLES = 0;
            pTexture = new QTexture2D(textureID, PIXEL_DATA_TYPE, nLayout, eFormat, pImage->GetWidth(), pImage->GetHeight(), MIPMAP_LEVELS, NUM_SAMPLES);
            //pTexture->SetMapping(eTextureMapping); [TODO]: Depending on the mapping, the texture may be created as a cube map or a UV map
        }

        m_arTextures2D.Add(strDefinitiveId, pTexture);

        return QKeyValuePair<QHashedString, QTexture2D*>(strDefinitiveId, pTexture);
    }

    QKeyValuePair<QHashedString, QTexture2D*> CreateTexture2D(const QHashedString strId, const EQPixelFormat::EnumType eTextureFormat, const u32_q uWidth, const u32_q uHeight, const u8_q uMipmapLevels, const u8_q uMultisamplingSamples)
    {
        QE_ASSERT_WARNING(uMipmapLevels == 1 || uMultisamplingSamples == 0, "Multisample textures cannot store multiple mipmaps, only 1 will be stored.");
        QE_ASSERT_ERROR(uMipmapLevels > 0, "It is mandatory to store, at least, 1 mipmap level.");

        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arTextures2D);

        QTexture2D* pTexture = null_q;

        GLenum formatType = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataType(eTextureFormat);
        GLenum formatLayout = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataFormatNonSized(eTextureFormat);
        GLenum nFormat = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataFormatSized(eTextureFormat);

        GLuint textureID = 0;
        glCreateTextures(GL_TEXTURE_2D, 1, &textureID);

        if(uMultisamplingSamples > 0)
            glTextureStorage2DMultisample(textureID, uMultisamplingSamples, nFormat, uWidth, uHeight, GL_FALSE);
        else
            glTextureStorage2D(textureID, uMipmapLevels, nFormat, uWidth, uHeight);

        QE_ASSERT_OPENGL_ERROR("An error occurred when reserving memory for the texture.");

        pTexture = new QTexture2D(textureID, formatType, formatLayout, eTextureFormat, uWidth, uHeight, uMipmapLevels, uMultisamplingSamples);

        m_arTextures2D.Add(strDefinitiveId, pTexture);

        return QKeyValuePair<QHashedString, QTexture2D*>(strDefinitiveId, pTexture);
    }

    QKeyValuePair<QHashedString, QTexture1D*> CreateTexture1D(const QHashedString strId, const EQPixelFormat::EnumType eTextureFormat, const u32_q uWidth, const u8_q uMipmapLevels)
    {
        QE_ASSERT_ERROR(uMipmapLevels > 0, "It is mandatory to store, at least, 1 mipmap level.");

        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arTextures2D);

        QTexture1D* pTexture = null_q;

        GLenum formatType = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataType(eTextureFormat);
        GLenum formatLayout = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataFormatNonSized(eTextureFormat);
        GLenum nFormat = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataFormatSized(eTextureFormat);

        GLuint textureID = 0;
        glCreateTextures(GL_TEXTURE_1D, 1, &textureID);
        glTextureStorage1D(textureID, uMipmapLevels, nFormat, uWidth);

        QE_ASSERT_OPENGL_ERROR("An error occurred when reserving memory for the texture.");

        pTexture = new QTexture1D(textureID, formatType, formatLayout, eTextureFormat, uWidth, uMipmapLevels);

        m_arTextures1D.Add(strDefinitiveId, pTexture);

        return QKeyValuePair<QHashedString, QTexture1D*>(strDefinitiveId, pTexture);
    }

    QKeyValuePair<QHashedString, QTexture3D*> CreateTexture3D(const QHashedString strId, const EQPixelFormat::EnumType eTextureFormat, const u32_q uWidth, const u32_q uHeight, const u32_q uDepth, const u8_q uMipmapLevels, const u8_q uMultisamplingSamples)
    {
        QE_ASSERT_WARNING(uMipmapLevels == 1 || uMultisamplingSamples == 0, "Multisample textures cannot store multiple mipmaps, only 1 will be stored.");
        QE_ASSERT_ERROR(uMipmapLevels > 0, "It is mandatory to store, at least, 1 mipmap level.");

        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arTextures2D);

        QTexture3D* pTexture = null_q;

        GLenum formatType = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataType(eTextureFormat);
        GLenum formatLayout = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataFormatNonSized(eTextureFormat);
        GLenum nFormat = SQEnumerationToOpenGLConverter::ConvertPixelFormatToPixelDataFormatSized(eTextureFormat);

        GLuint textureID = 0;
        glCreateTextures(GL_TEXTURE_3D, 1, &textureID);

        if (uMultisamplingSamples > 0)
            glTextureStorage3DMultisample(textureID, uMultisamplingSamples, nFormat, uWidth, uHeight, uDepth, GL_FALSE);
        else
            glTextureStorage3D(textureID, uMipmapLevels, nFormat, uWidth, uHeight, uDepth);

        QE_ASSERT_OPENGL_ERROR("An error occurred when reserving memory for the texture.");

        pTexture = new QTexture3D(textureID, formatType, formatLayout, eTextureFormat, uWidth, uHeight, uDepth, uMipmapLevels);

        m_arTextures3D.Add(strDefinitiveId, pTexture);

        return QKeyValuePair<QHashedString, QTexture3D*>(strDefinitiveId, pTexture);
    }

    QKeyValuePair<QHashedString, QAspect*> CreateAspect(const QHashedString strId)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arAspects);
        
        QAspect* pAspect = new QAspect();
        m_arAspects.Add(strId, pAspect);
        return QKeyValuePair<QHashedString, QAspect*>(strDefinitiveId, pAspect);
    }

    QKeyValuePair<QHashedString, QMaterial*> CreateMaterial(const QHashedString strId)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arMaterials);
        
        QMaterial* pMaterial = new QMaterial();
        m_arMaterials.Add(strDefinitiveId, pMaterial);
        return QKeyValuePair<QHashedString, QMaterial*>(strDefinitiveId, pMaterial);
    }

    // Add an overload that retrieves lists of all the generated resource Ids
    // Add parameter to inject a postprocessing algorithm
    // Add possibility of setting the texture directory
    QKeyValuePair<QHashedString, QStaticModel*> CreateStaticModel(const QHashedString strId, const QPath &modelPath, const QVertexDescription* pVertexDescription)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arStaticModels);

        QStaticModel* pModel = null_q;
        QModelAspectsRawData modelAspects;
        QStaticModelRawData modelRawData;

        QModelLoader loader;
        loader.LoadModel(modelPath, pVertexDescription, modelRawData, modelAspects);

        // [TODO]: Whether existing IDs should be regenerated or not should be optional
        QDictionary<QHashedString, QHashedString> actualAspectIds; 
        
        this->_GenerateTexturesSamplersBlenders(modelAspects, actualAspectIds);
        this->_SetupStaticModelGeometry(&modelRawData, actualAspectIds, &pModel);
        
        QResourceManager::_FreeModelRawData(modelRawData);
        QResourceManager::_FreeModelAspectsRawData(modelAspects);

        m_arStaticModels.Add(strDefinitiveId, pModel);
        return QKeyValuePair<QHashedString, QStaticModel*>(strDefinitiveId, pModel);
    }

    QKeyValuePair<QHashedString, QSampler2D*> CreateSampler2D(const QHashedString strId,
                                                              const QSampler2D::EQTextureWrapMode eWrapModeU, 
                                                              const QSampler2D::EQTextureWrapMode eWrapModeV, 
                                                              const QSampler2D::EQTextureWrapMode eWrapModeW, 
                                                              const QColor &borderColor,
                                                              const QSampler2D::EQMinificationFilter eMinFilter, 
                                                              const QSampler2D::EQMagnificationFilter eMagFilter)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arSamplers2D);

        GLuint samplerID = 0;
        glCreateSamplers(1, &samplerID);
        
        glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, QResourceManager::_GetEquivalentMagnificationFilterOpenGLValue(eMagFilter));
        glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, QResourceManager::_GetEquivalentMinificationFilterOpenGLValue(eMinFilter));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, QResourceManager::_GetEquivalentWrapModeOpenGLValue(eWrapModeU));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, QResourceManager::_GetEquivalentWrapModeOpenGLValue(eWrapModeV));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, QResourceManager::_GetEquivalentWrapModeOpenGLValue(eWrapModeW));
        glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, &borderColor.x);

        QSampler2D* pSampler = new QSampler2D(samplerID);
        pSampler->SetMagnificationFilter(eMagFilter);
        pSampler->SetMinificationFilter(eMinFilter);
        pSampler->SetWrapModeU(eWrapModeU);
        pSampler->SetWrapModeV(eWrapModeV);
        pSampler->SetWrapModeW(eWrapModeW);
        pSampler->SetBorderColor(borderColor);

        m_arSamplers2D.Add(strDefinitiveId, pSampler);
        
        return QKeyValuePair<QHashedString, QSampler2D*>(strDefinitiveId, pSampler);
    }

    QKeyValuePair<QHashedString, QTextureBlender*> CreateTextureBlender(const QHashedString strId, const QTextureBlender::EQTextureBlendOperation eBlendOperation, const float_q fBlendFactor)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arTextureBlenders);

        QTextureBlender* pTextureBlender = new QTextureBlender();
        pTextureBlender->SetBlendOperation(eBlendOperation);
        pTextureBlender->SetBlendFactor(fBlendFactor);

        m_arTextureBlenders.Add(strId, pTextureBlender);
        return QKeyValuePair<QHashedString, QTextureBlender*>(strDefinitiveId, pTextureBlender);
    }

    QKeyValuePair<QHashedString, QBuffer*> CreateBuffer(const QHashedString strId, const QBuffer::EQBufferType eType, const pointer_uint_q uSize, const QBuffer::EQModificationFrequency eModificationFrequency, const QBuffer::EQExpectedOperations eExpectedOperations)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arBuffers);

        GLuint bufferId = 0;
        glCreateBuffers(1, &bufferId);

        QBuffer* pBuffer = new QBuffer(bufferId, eType, uSize, eModificationFrequency, eExpectedOperations);

        glNamedBufferData(bufferId, uSize, null_q, pBuffer->GetOpenGLUsage());
        
        m_arBuffers.Add(strDefinitiveId, pBuffer);

        return QKeyValuePair<QHashedString, QBuffer*>(strDefinitiveId, pBuffer);
    }

    QKeyValuePair<QHashedString, QAlphaBlender*> CreateAlphaBlender(const QHashedString strId, const QAlphaBlender::EQBlendingFunction eSourceFactor, const QAlphaBlender::EQBlendingFunction eDestinationFactor, const QColor &constantColor=QColor())
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arAlphaBlenders);

        QAlphaBlender* pAlphaBlender = new QAlphaBlender();
        pAlphaBlender->SetConstantColor(constantColor);
        pAlphaBlender->SetDestinationColorFactor(eDestinationFactor);
        pAlphaBlender->SetSourceColorFactor(eSourceFactor);

        m_arAlphaBlenders.Add(strDefinitiveId, pAlphaBlender);

        return QKeyValuePair<QHashedString, QAlphaBlender*>(strDefinitiveId, pAlphaBlender);
    }

    QKeyValuePair<QHashedString, QAlphaBlender*> CreateAlphaBlender(const QHashedString strId, const QAlphaBlender::EQBlendingFunction eSourceColorFactor, const QAlphaBlender::EQBlendingFunction eDestinationColorFactor, const QAlphaBlender::EQBlendingFunction eSourceAlphaFactor, const QAlphaBlender::EQBlendingFunction eDestinationAlphaFactor, const QColor &constantColor = QColor())
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arAlphaBlenders);

        QAlphaBlender* pAlphaBlender = new QAlphaBlender();
        pAlphaBlender->SetConstantColor(constantColor);
        pAlphaBlender->SetDestinationColorFactor(eDestinationColorFactor);
        pAlphaBlender->SetSourceColorFactor(eSourceColorFactor);
        pAlphaBlender->SetDestinationAlphaFactor(eDestinationAlphaFactor);
        pAlphaBlender->SetSourceAlphaFactor(eSourceAlphaFactor);
        pAlphaBlender->SetSeparateAlphaFactors(true);

        m_arAlphaBlenders.Add(strDefinitiveId, pAlphaBlender);

        return QKeyValuePair<QHashedString, QAlphaBlender*>(strDefinitiveId, pAlphaBlender);
    }

    QKeyValuePair<QHashedString, QShadingPipeline*> CreateShadingPipeline(const QHashedString strId)
    {
        QHashedString strDefinitiveId = QResourceManager::_GenerateId(strId, m_arShadingPipelines);

        GLuint pipelineId = 0;
        glCreateProgramPipelines(1, &pipelineId);
        QShadingPipeline* pShadingPipeline = new QShadingPipeline(pipelineId);

        m_arShadingPipelines.Add(strDefinitiveId, pShadingPipeline);
        return QKeyValuePair<QHashedString, QShadingPipeline*>(strDefinitiveId, pShadingPipeline);
    }

    QShader* GetShader(const QHashedString &strId) const
    {
        return m_arShaders[strId];
    }

    QImage* GetImage(const QHashedString &strId) const
    {
        return m_arImages[strId];
    }

    QTexture2D* GetTexture2D(const QHashedString &strId) const
    {
        return m_arTextures2D[strId];
    }

    QTexture1D* GetTexture1D(const QHashedString &strId) const
    {
        return m_arTextures1D[strId];
    }

    QTexture3D* GetTexture3D(const QHashedString &strId) const
    {
        return m_arTextures3D[strId];
    }

    QAspect* GetAspect(const QHashedString &strId) const
    {
        return m_arAspects[strId];
    }

    QMaterial* GetMaterial(const QHashedString &strId) const
    {
        return m_arMaterials[strId];
    }

    QStaticModel* GetStaticModel(const QHashedString &strId) const
    {
        return m_arStaticModels[strId];
    }

    QSampler2D* GetSampler2D(const QHashedString &strId) const
    {
        return m_arSamplers2D[strId];
    }

    QTextureBlender* GetTextureBlender(const QHashedString &strId) const
    {
        return m_arTextureBlenders[strId];
    }

    QBuffer* GetBuffer(const QHashedString &strId) const
    {
        return m_arBuffers[strId];
    }

    QAlphaBlender* GetAlphaBlender(const QHashedString &strId)
    {
        return m_arAlphaBlenders[strId];
    }

    QShadingPipeline* GetShadingPipeline(const QHashedString &strId)
    {
        return m_arShadingPipelines[strId];
    }

    // [TODO]: FindNameOf***(pointer to resource ***)
    // [TODO]: Destroy functions
    // [TODO]: Clone functions

protected:

    static void _FreeModelRawData(QStaticModelRawData &modelRawData)
    {
        // This was reserved inside the model loader, and should be freed there too
        delete[] rcast_q(modelRawData.Vertices, char*);
        delete[] modelRawData.Indices;
    }

    static void _FreeModelAspectsRawData(QModelAspectsRawData &modelAspectsRawData)
    {
        delete[] modelAspectsRawData.AspectIds;
        delete[] modelAspectsRawData.MaterialIds;
        delete[] modelAspectsRawData.TextureIds;
        delete[] modelAspectsRawData.Textures;
        delete[] modelAspectsRawData.Aspects;
        delete[] modelAspectsRawData.Materials;
    }

    virtual void _SetupStaticModelGeometry(const QStaticModelRawData* pModel, const QDictionary<QHashedString, QHashedString> &actualAspectIds, QStaticModel** pOutputModel)
    {
        // create VAO
        GLuint vaoMesh = 0;
        glCreateVertexArrays(1, &vaoMesh);

        // create VBO
        QKeyValuePair<QHashedString, QBuffer*> vertexBuffer = this->CreateBuffer(pModel->MeshIds[0].Id, QBuffer::E_VertexArray, pModel->VertexCount * pModel->VertexDescription->GetVertexSize(), QBuffer::E_Rarely, QBuffer::E_GPUReadsCPUWrites);
        glVertexArrayVertexBuffer(vaoMesh, 0, vertexBuffer.GetValue()->GetOpenGLId(), 0, pModel->VertexDescription->GetVertexSize());
        void* pVertices = vertexBuffer.GetValue()->MapRange(QBuffer::E_Write, 0, vertexBuffer.GetValue()->GetSize());
        memcpy(pVertices, pModel->Vertices, vertexBuffer.GetValue()->GetSize());
        bool bUnmapResult = vertexBuffer.GetValue()->Unmap();
        
        if (!bUnmapResult)
        {
            GLenum eErrorCode = glGetError();
            const GLubyte* szMessage = gluErrorString(eErrorCode);
            QE_LOG(string_q("An error occurred when unmapping buffer: ") + (char*)szMessage + "\n");
        }

        // create EBO
        QKeyValuePair<QHashedString, QBuffer*> indexBuffer = this->CreateBuffer(pModel->MeshIds[0].Id, QBuffer::E_IndexArray, pModel->IndexCount * sizeof(u32_q), QBuffer::E_Never, QBuffer::E_GPUReadsCPUWrites);

        //QBuffer* pVertexBuffer = m_pResourceManager->GetBuffer(pModel->GetVertexBufferId());
        void* pIndices = indexBuffer.GetValue()->MapRange(QBuffer::E_Write, 0, indexBuffer.GetValue()->GetSize());
        glVertexArrayElementBuffer(vaoMesh, indexBuffer.GetValue()->GetOpenGLId());
        memcpy(pIndices, pModel->Indices, indexBuffer.GetValue()->GetSize());
        bUnmapResult = indexBuffer.GetValue()->Unmap();
        
        if (!bUnmapResult)
        {
            GLenum eErrorCode = glGetError();
            const GLubyte* szMessage = gluErrorString(eErrorCode);
            QE_LOG(string_q("An error occurred when unmapping buffer: ") + (char*)szMessage + "\n");
        }

        // Vertex description
        QResourceManager::_SetVertexLayout(pModel->VertexDescription, vaoMesh);

        // Updates aspect ids to actual ids (after aspects have been added to the manager)
        for (u32_q i = 0; i < pModel->SubmeshCount; ++i)
            pModel->SubmeshAspects[i].AspectId = actualAspectIds[pModel->SubmeshAspects[i].AspectId];

        *pOutputModel = new QStaticModel(vaoMesh, vertexBuffer.GetKey(), indexBuffer.GetKey(), pModel);
    }

    static void _SetVertexLayout(const QVertexDescription* pVertexDescription, const GLuint vertexArrayObject)
    {
        u32_q uComponentOffset = 0;
        u32_q uComponentsSize = 0;

        for (u32_q i = 0; i < pVertexDescription->GetVertexComponentCount(); ++i)
        {
            uComponentsSize = pVertexDescription->GetVertexComponents()[i].Size;
            glEnableVertexArrayAttrib(vertexArrayObject, i);
            glVertexArrayAttribBinding(vertexArrayObject, i, 0);
            glVertexArrayAttribFormat(vertexArrayObject, i, uComponentsSize / sizeof(float_q), GL_FLOAT, GL_FALSE, uComponentOffset);
            uComponentOffset += uComponentsSize;
        }
    }

    virtual void _GenerateTexturesSamplersBlenders(QModelAspectsRawData &modelAspects, QDictionary<QHashedString, QHashedString> &actualAspectIds)
    {
        // These dictionaries are used to store resource Id pairs, where the key is the original Id and the value is the final Id (which may be different if the Id already existed in the resource container)
        // Then the dictionaries are used to update the Ids stored in the Aspect, so they match
        QDictionary<QHashedString, QHashedString> actualTextureIds(modelAspects.TextureCount);
        QDictionary<QHashedString, QHashedString> actualTextureBlenderIds(modelAspects.TextureCount);
        QDictionary<QHashedString, QHashedString> actualSampler2DIds(modelAspects.TextureCount);
        QDictionary<QHashedString, QHashedString> actualMaterialIds(modelAspects.MaterialCount);

        // Materials
        QHashedString strMaterialId;

        for (u32_q i = 0; i < modelAspects.MaterialCount; ++i)
        {
            strMaterialId = QResourceManager::_GenerateId(modelAspects.MaterialIds[i], m_arMaterials);
            actualMaterialIds.Add(modelAspects.MaterialIds[i], strMaterialId);
            m_arMaterials.Add(strMaterialId, modelAspects.Materials[i]);
        }

        // Textures, blenders and samplers
        QHashedString strTextureId;
        QHashedString strTextureBlenderId;
        QHashedString strSampler2DId;

        for (u32_q i = 0; i < modelAspects.TextureCount; ++i)
        {
            strTextureId = QResourceManager::_GenerateId(modelAspects.TextureIds[i], m_arTextures2D);
            strTextureBlenderId = QResourceManager::_GenerateId(modelAspects.TextureIds[i], m_arTextureBlenders);
            strSampler2DId = QResourceManager::_GenerateId(modelAspects.TextureIds[i], m_arSamplers2D);
            actualTextureIds.Add(modelAspects.TextureIds[i], strTextureId);
            actualTextureBlenderIds.Add(modelAspects.TextureIds[i], strTextureBlenderId);
            actualSampler2DIds.Add(modelAspects.TextureIds[i], strSampler2DId);
            QKeyValuePair<QHashedString, QImage*> image = this->CreateImage(strTextureId, modelAspects.Textures[i].FilePath, QImage::E_RGB);
            QKeyValuePair<QHashedString, QTexture2D*> texture = this->CreateTexture2D(strTextureId, image.GetKey(), QImage::E_RGB);
            QKeyValuePair<QHashedString, QTextureBlender*> blender = this->CreateTextureBlender(strTextureBlenderId, modelAspects.Textures[i].BlendOperation, modelAspects.Textures[i].BlendFactor);
            QKeyValuePair<QHashedString, QSampler2D*> sampler = this->CreateSampler2D(strSampler2DId, modelAspects.Textures[i].WrapMode[0], modelAspects.Textures[i].WrapMode[1], modelAspects.Textures[i].WrapMode[2], QColor::GetVectorOfOnes(), QSampler2D::E_LinearMipmaps, QSampler2D::E_MagLinear);
        }

        // Aspects
        QHashedString strAspectId;

        for (u32_q i = 0; i < modelAspects.AspectCount; ++i)
        {
            strAspectId = QResourceManager::_GenerateId(modelAspects.AspectIds[i], m_arAspects);
            actualAspectIds.Add(modelAspects.AspectIds[i], strAspectId);
            m_arAspects.Add(strAspectId, modelAspects.Aspects[i]);

            strMaterialId = modelAspects.Aspects[i]->GetMaterial();
            modelAspects.Aspects[i]->SetMaterial(actualMaterialIds[strMaterialId]);

            // It's necessary to set the same ID in both the aspect and the texture components
            QResourceManager::_UpdateAspectTextureIds(actualTextureIds, actualTextureBlenderIds, actualSampler2DIds, modelAspects.Aspects[i]);
        }
    }

    void _UpdateAspectTextureIds(const QDictionary<QHashedString, QHashedString> &actualTextureIds, 
                                 const QDictionary<QHashedString, QHashedString> &actualTextureBlenderIds,
                                 const QDictionary<QHashedString, QHashedString> &actualSampler2DIds,
                                 QAspect* pAspect)
    {
        static const QAspect::EQAspectComponentType COMPONENT_TYPES[] = {   QAspect::E_Ambient,
                                                                            QAspect::E_Diffuse,
                                                                            QAspect::E_Specular,
                                                                            QAspect::E_Normals,
                                                                            QAspect::E_Opacity,
                                                                            QAspect::E_Displacement,
                                                                            QAspect::E_Height,
                                                                            QAspect::E_Shininess,
                                                                            QAspect::E_Reflection,
                                                                            QAspect::E_Lightmap,
                                                                            QAspect::E_Emissive
                                                                        };

        QHashedString strTextureId;
        QHashedString strTextureBlenderId;
        QHashedString strTextureSampler2DId;

        for (u32_q iComponentType = 0; iComponentType < pAspect->GetAspectComponentCount(); ++iComponentType)
        {
            for (u32_q iTextureLayer = 0; iTextureLayer < pAspect->GetTextureLayerCount(COMPONENT_TYPES[iComponentType]); ++iTextureLayer)
            {
                // Updates the id of the texture
                strTextureId = pAspect->GetTexture(COMPONENT_TYPES[iComponentType], iTextureLayer);
                pAspect->SetTexture(COMPONENT_TYPES[iComponentType], iTextureLayer, actualTextureIds[strTextureId]);

                // Updates the id of the texture blender
                strTextureBlenderId = pAspect->GetTextureBlender(COMPONENT_TYPES[iComponentType], iTextureLayer);
                pAspect->SetTextureBlender(COMPONENT_TYPES[iComponentType], iTextureLayer, actualTextureBlenderIds[strTextureBlenderId]);

                // Updates the id of the texture sampler 2D
                strTextureSampler2DId = pAspect->GetTextureSampler2D(COMPONENT_TYPES[iComponentType], iTextureLayer);
                pAspect->SetTextureSampler2D(COMPONENT_TYPES[iComponentType], iTextureLayer, actualSampler2DIds[strTextureSampler2DId]);
            }
        }
    }

    static GLint _GetEquivalentWrapModeOpenGLValue(const QSampler2D::EQTextureWrapMode eWrapMode)
    {
        GLint nWrapMode = 0;

        switch (eWrapMode)
        {
        case QSampler2D::E_Border:
            nWrapMode = GL_CLAMP_TO_BORDER;
            break;
        case QSampler2D::E_Clamp:
            nWrapMode = GL_CLAMP_TO_EDGE;
            break;
        case QSampler2D::E_Repeat:
            nWrapMode = GL_REPEAT;
            break;
        case QSampler2D::E_RepeatMirror:
            nWrapMode = GL_MIRRORED_REPEAT;
            break;
        }

        return nWrapMode;
    }


    static GLint _GetEquivalentMagnificationFilterOpenGLValue(const QSampler2D::EQMagnificationFilter eFilter)
    {
        GLint nFilter = 0;

        switch (eFilter)
        {
        case QSampler2D::E_MagNearest:
            nFilter = GL_NEAREST;
            break;
        case QSampler2D::E_MagLinear:
            nFilter = GL_LINEAR;
            break;
        }

        return nFilter;
    }

    static GLint _GetEquivalentMinificationFilterOpenGLValue(const QSampler2D::EQMinificationFilter eFilter)
    {
        GLint nFilter = 0;

        switch (eFilter)
        {
        case QSampler2D::E_MinNearest:
            nFilter = GL_NEAREST;
            break;
        case QSampler2D::E_MinLinear:
            nFilter = GL_LINEAR;
            break;
        case QSampler2D::E_LinearMipmaps:
            nFilter = GL_LINEAR_MIPMAP_LINEAR;
            break;
        }

        return nFilter;
    }

    template<class ResourceT>
    static QHashedString _GenerateId(const QHashedString &strProposedId, const QHashtable<QHashedString, ResourceT*, SQStringHashProvider> &container)
    {
        QHashedString strDefinitiveId = strProposedId;

        QE_LOG(container.ContainsKey(strProposedId) ? string_q("The resource Id '") + strProposedId + "' already exists.\n" : string_q::GetEmpty());

        if (container.ContainsKey(strProposedId))
            strDefinitiveId = strDefinitiveId + string_q::FromInteger(container.GetCount());

        return strDefinitiveId;
    }

    // Instances must be stored using pool allocators
    QHashtable<QHashedString, QMaterial*, SQStringHashProvider> m_arMaterials;
    QHashtable<QHashedString, QAspect*, SQStringHashProvider> m_arAspects;
    QHashtable<QHashedString, QImage*, SQStringHashProvider> m_arImages;
    QHashtable<QHashedString, QTexture1D*, SQStringHashProvider> m_arTextures1D;
    QHashtable<QHashedString, QTexture2D*, SQStringHashProvider> m_arTextures2D;
    QHashtable<QHashedString, QTexture3D*, SQStringHashProvider> m_arTextures3D;
    QHashtable<QHashedString, QStaticModel*, SQStringHashProvider> m_arStaticModels;
    QHashtable<QHashedString, QSampler2D*, SQStringHashProvider> m_arSamplers2D;
    QHashtable<QHashedString, QTextureBlender*, SQStringHashProvider> m_arTextureBlenders;
    QHashtable<QHashedString, QBuffer*, SQStringHashProvider> m_arBuffers;
    QHashtable<QHashedString, QShader*, SQStringHashProvider> m_arShaders;
    QHashtable<QHashedString, QShadingPipeline*, SQStringHashProvider> m_arShadingPipelines;
    QHashtable<QHashedString, QAlphaBlender*, SQStringHashProvider> m_arAlphaBlenders;
    QShaderCompositor* m_pShaderCompositor;

};

#endif // __QRESOURCEMANAGER__