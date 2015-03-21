
#ifndef __QRESOURCEMANAGER__
#define __QRESOURCEMANAGER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QVertexShader.h"
#include "QFragmentShader.h"
#include "QShaderCompositor.h"
#include "QTexture2D.h"
#include "QImage.h"
#include "QAspect.h"
#include "QStaticModel.h"
#include "VertexDefinitions.h"
#include "QModelLoader.h"
#include "QImageLoader.h"

// The resource manager should receive a set of factories, one per type of asset, depending on whether using DirectX or OpenGL
class QResourceManager
{
public:

    QResourceManager(QShaderCompositor* pShaderCompositor) : 
                                                             m_arMaterials(5, 2),
                                                             m_arAspects(5, 2),
                                                             m_arImages(5, 2),
                                                             m_arTextures2D(5, 2), 
                                                             m_arStaticModels(5, 2),
                                                             m_arSamplers2D(5, 2),
                                                             m_arTextureBlenders(5, 2),
                                                             m_arVertexShaders(5, 2),
                                                             m_arFragmentShaders(5, 2),
                                                             m_pShaderCompositor(pShaderCompositor)
    {
    }

    QVertexShader* CreateVertexShader(const QHashedString strId, const QPath &vertexShaderPath)
    {
        QVertexShader* pVertexShader = m_pShaderCompositor->CompileAndLinkVertexShader(vertexShaderPath);
        m_arVertexShaders.Add(strId, pVertexShader);
        return pVertexShader;
    }

    QFragmentShader* CreateFragmentShader(const QHashedString strId, const QPath &fragmentShaderPath)
    {
        QFragmentShader* pFragmentShader = m_pShaderCompositor->CompileAndLinkFragmentShader(fragmentShaderPath);
        m_arFragmentShaders.Add(strId, pFragmentShader);
        return pFragmentShader;
    }

    // It is necessary to differentiate the type of image, (integer, float)
    // Maybe images should not be created using different factories for either graphic library
    QImage* CreateImage(const QHashedString strId, const QPath &imagePath, const QImage::EQImageColorComponents eColorComponents)
    {
        QImageLoader loader;
        QImage* pNewImage = loader.LoadImage(imagePath, eColorComponents);

        QE_ASSERT_ERROR(pNewImage != null_q, string_q("An error occurred when loading the image with ID \"") + strId + "\" from \"" + imagePath.ToString() + "\".");

        m_arImages.Add(strId, pNewImage);
        return pNewImage;
    }

    QImage* CreateImage(const QHashedString strId, const void* pImageBuffer, const pointer_uint_q uBufferSize, const QImage::EQImageColorComponents eColorComponents)
    {
        QImageLoader loader;
        QImage* pNewImage = loader.LoadImage(pImageBuffer, uBufferSize, eColorComponents);

        QE_ASSERT_ERROR(pNewImage != null_q, string_q("An error occurred when loading the image with ID \"") + strId + "\".");

        m_arImages.Add(strId, pNewImage);
        return pNewImage;
    }

    QTexture2D* CreateTexture2D(const QHashedString strId, const QHashedString &strImageId, const QImage::EQImageColorComponents eFormat, const QTexture2D::EQTextureMapping eTextureMapping)
    {
        QImage* pImage = this->GetImage(strImageId);
        QTexture2D* pTexture = null_q;

        if (pImage)
        {
            GLint nInternalFormat = pImage->GetColorComponents() == QImage::E_RGB ? GL_RGB :
                pImage->GetColorComponents() == QImage::E_RGBA ? GL_RGBA :
                0;
            GLint nFormat = eFormat == QImage::E_RGB ? GL_RGB :
                eFormat == QImage::E_RGBA ? GL_RGBA :
                0;
            GLuint textureID = 0;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, nInternalFormat, pImage->GetWidth(), pImage->GetHeight(), 0, nFormat, GL_UNSIGNED_BYTE, pImage->GetData());

            pTexture = new QTexture2D(textureID);
            pTexture->SetMapping(eTextureMapping);
        }

        m_arTextures2D.Add(strId, pTexture);

        return pTexture;
    }

    QAspect* CreateAspect(const QHashedString strId)
    {
        QAspect* pAspect = new QAspect();
        m_arAspects.Add(strId, pAspect);
        return pAspect;
    }

    QMaterial* CreateMaterial(const QHashedString strId)
    {
        QMaterial* pMaterial = new QMaterial();
        m_arMaterials.Add(strId, pMaterial);
        return pMaterial;
    }

    QStaticModel* CreateStaticModel(const QHashedString strId, const QPath &modelPath, const QVertexDescription* pVertexDescription)
    {
        QStaticModel* pModel = new QStaticModel(pVertexDescription);
        QModelLoader::QModelAspects modelAspects;

        QModelLoader loader;
        loader.LoadModel(modelPath, *pModel, modelAspects);

        this->GenerateTexturesSamplersBlenders(modelAspects);
        this->SetupStaticModelGeometry(pModel);

        m_arStaticModels.Add(strId, pModel);
        return pModel;
    }

    QSampler2D* CreateSampler2D(const QHashedString strId, 
                                const QSampler2D::EQTextureWrapMode eWrapModeU, 
                                const QSampler2D::EQTextureWrapMode eWrapModeV, 
                                const QSampler2D::EQTextureWrapMode eWrapModeW, 
                                const QColor &borderColor,
                                const QSampler2D::EQMinificationFilter eMinFilter, 
                                const QSampler2D::EQMagnificationFilter eMagFilter)
    {
        GLuint samplerID = 0;

        glGenSamplers(1, &samplerID);
        
        glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, QResourceManager::GetEquivalentMagnificationFilterOpenGLValue(eMagFilter));
        glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, QResourceManager::GetEquivalentMinificationFilterOpenGLValue(eMinFilter));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, QResourceManager::GetEquivalentWrapModeOpenGLValue(eWrapModeU));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, QResourceManager::GetEquivalentWrapModeOpenGLValue(eWrapModeV));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, QResourceManager::GetEquivalentWrapModeOpenGLValue(eWrapModeW));
        glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, &borderColor.x);

        QSampler2D* pSampler = new QSampler2D(samplerID);
        pSampler->SetMagnificationFilter(eMagFilter);
        pSampler->SetMinificationFilter(eMinFilter);
        pSampler->SetWrapModeU(eWrapModeU);
        pSampler->SetWrapModeV(eWrapModeV);
        pSampler->SetWrapModeW(eWrapModeW);
        pSampler->SetBorderColor(borderColor);

        m_arSamplers2D.Add(strId, pSampler);
        
        return pSampler;
    }

    QTextureBlender* CreateTextureBlender(const QHashedString strId, const QTextureBlender::EQTextureBlendOperation eBlendOperation, const float_q fBlendFactor)
    {
        QTextureBlender* pTextureBlender = new QTextureBlender();
        pTextureBlender->SetBlendOperation(eBlendOperation);
        pTextureBlender->SetBlendFactor(fBlendFactor);

        m_arTextureBlenders.Add(strId, pTextureBlender);
        return pTextureBlender;
    }

    QVertexShader* GetVertexShader(const QHashedString &strId) const
    {
        return m_arVertexShaders[strId];
    }

    QFragmentShader* GetFragmentShader(const QHashedString &strId) const
    {
        return m_arFragmentShaders[strId];
    }

    QImage* GetImage(const QHashedString &strId) const
    {
        return m_arImages[strId];
    }

    QTexture2D* GetTexture2D(const QHashedString &strId) const
    {
        return m_arTextures2D[strId];
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

    // FindNameOf***(pointer to resource ***)

protected:

    virtual void SetupStaticModelGeometry(QStaticModel* pModel)
    {
        // create VAO
        GLuint vaoMesh = 0;
        glGenVertexArrays(1, &vaoMesh);
        glBindVertexArray(vaoMesh);

        // Set up VAO

        // create VBO
        GLuint vboMesh = 0;
        glGenBuffers(1, &vboMesh);
        glBindBuffer(GL_ARRAY_BUFFER, vboMesh);
        glBufferData(GL_ARRAY_BUFFER, pModel->GetVertexCount() * pModel->GetVertexDescription()->GetVertexSize(), pModel->GetVertexBuffer(), GL_STATIC_DRAW);

        u32_q uComponentOffset = 0;
        u32_q uComponentsSize = 0;

        for (u32_q i = 0; i < pModel->GetVertexDescription()->GetVertexComponentCount(); ++i)
        {
            uComponentsSize = pModel->GetVertexDescription()->GetVertexComponents()[i].Size;
            glVertexAttribPointer(i, uComponentsSize / sizeof(float_q), GL_FLOAT, GL_FALSE, pModel->GetVertexDescription()->GetVertexSize(), (GLvoid*)uComponentOffset);
            glEnableVertexAttribArray(i);
            uComponentOffset += uComponentsSize;
        }

        // create EBO
        GLuint eboMesh = 0;
        glGenBuffers(1, &eboMesh);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboMesh);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, pModel->GetIndexCount() * sizeof(u32_q), pModel->GetIndexbuffer(), GL_STATIC_DRAW);

        pModel->SetExternalId(vaoMesh);
    }

    virtual void GenerateTexturesSamplersBlenders(const QModelLoader::QModelAspects &modelAspects)
    {
        // Images
        for (u32_q i = 0; i < modelAspects.ImageCount; ++i)
            m_arImages.Add(modelAspects.ImageIds[i], modelAspects.Images[i]);

        // Aspects
        for (u32_q i = 0; i < modelAspects.AspectCount; ++i)
            m_arAspects.Add(modelAspects.AspectIds[i], modelAspects.Aspects[i]);

        // Materials
        for (u32_q i = 0; i < modelAspects.MaterialCount; ++i)
            m_arMaterials.Add(modelAspects.MaterialIds[i], modelAspects.Materials[i]);

        // Textures
        for (u32_q i = 0; i < modelAspects.TextureCount; ++i)
        {
            QTexture2D* pTexture = this->CreateTexture2D(modelAspects.TextureIds[i], modelAspects.ImageIds[i], QImage::E_RGB, modelAspects.Textures[i].Mapping);
            QSampler2D* pSampler = this->CreateSampler2D(modelAspects.TextureIds[i], modelAspects.Textures[i].WrapMode[0], modelAspects.Textures[i].WrapMode[1], modelAspects.Textures[i].WrapMode[2], QColor::GetVectorOfOnes(), QSampler2D::E_LinearMipmaps, QSampler2D::E_MagLinear);
            QTextureBlender* pBlender = this->CreateTextureBlender(modelAspects.TextureIds[i], modelAspects.Textures[i].BlendOperation, modelAspects.Textures[i].BlendFactor);
        }
    }

    static GLint GetEquivalentWrapModeOpenGLValue(const QSampler2D::EQTextureWrapMode eWrapMode)
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


    static GLint GetEquivalentMagnificationFilterOpenGLValue(const QSampler2D::EQMagnificationFilter eFilter)
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

    static GLint GetEquivalentMinificationFilterOpenGLValue(const QSampler2D::EQMinificationFilter eFilter)
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

    QHashtable<QHashedString, QMaterial*, SQStringHashProvider> m_arMaterials;
    QHashtable<QHashedString, QAspect*, SQStringHashProvider> m_arAspects;
    QHashtable<QHashedString, QImage*, SQStringHashProvider> m_arImages;
    QHashtable<QHashedString, QTexture2D*, SQStringHashProvider> m_arTextures2D;
    QHashtable<QHashedString, QStaticModel*, SQStringHashProvider> m_arStaticModels;
    QHashtable<QHashedString, QSampler2D*, SQStringHashProvider> m_arSamplers2D;
    QHashtable<QHashedString, QTextureBlender*, SQStringHashProvider> m_arTextureBlenders;
    // Unify both hashtables? It seems shaders are always trated in the same way
    QHashtable<QHashedString, QVertexShader*, SQStringHashProvider> m_arVertexShaders;
    QHashtable<QHashedString, QFragmentShader*, SQStringHashProvider> m_arFragmentShaders;
    QShaderCompositor* m_pShaderCompositor;

};

#endif // __QRESOURCEMANAGER__