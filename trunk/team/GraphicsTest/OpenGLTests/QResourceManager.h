
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
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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
        EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
        EQFileSystemError eGetSizeErrorInfo = EQFileSystemError::E_Unknown;
        
        QFileStream fs(imagePath, EQFileOpenMode::E_Open, SQFile::GetFileInfo(imagePath, eGetSizeErrorInfo).GetSize(), eErrorInfo);
        QBinaryStreamReader<QFileStream> bs(fs);
        stbi_uc* pImageFile = new stbi_uc[fs.GetLength()];
        bs.ReadBytes(pImageFile, fs.GetLength());

        int nWidth = 0;
        int nHeight = 0;
        int nComponents = 0;
        stbi_uc* pImage = null_q;
        int nExpectedComponents = eColorComponents == QImage::E_RGB ? STBI_rgb : 
                                                                      eColorComponents == QImage::E_RGBA ? STBI_rgb_alpha : 
                                                                                                           0;

        pImage = stbi_load_from_memory(pImageFile, fs.GetLength(), &nWidth, &nHeight, &nComponents, nExpectedComponents);

        QE_ASSERT_ERROR(pImage != null_q, string_q("An error occurred when loading the image with ID \"") + strId + "\" from \"" + imagePath.ToString() + "\".");

        QImage* pNewImage = new QImage(pImage, imagePath, eColorComponents, scast_q(nWidth, unsigned int), scast_q(nHeight, unsigned int));
        m_arImages.Add(strId, pNewImage);

        return pNewImage;
    }

    QTexture2D* CreateTexture2D(const QHashedString strId, const QHashedString &strImageId, const QImage::EQImageColorComponents eFormat)
    {
        QImage* pImage = this->GetImage(strImageId);

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

        QTexture2D* pTexture = new QTexture2D(textureID);
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
        QModelLoader::LoadModel(modelPath, *pModel);
        this->SetupStaticModelGeometry(pModel);

        m_arStaticModels.Add(strId, pModel);
        return pModel;
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

    QHashtable<QHashedString, QMaterial*, SQStringHashProvider> m_arMaterials;
    QHashtable<QHashedString, QAspect*, SQStringHashProvider> m_arAspects;
    QHashtable<QHashedString, QImage*, SQStringHashProvider> m_arImages;
    QHashtable<QHashedString, QTexture2D*, SQStringHashProvider> m_arTextures2D;
    QHashtable<QHashedString, QStaticModel *, SQStringHashProvider> m_arStaticModels;
    // Unify both hashtables? It seems shaders are always trated in the same way
    QHashtable<QHashedString, QVertexShader*, SQStringHashProvider> m_arVertexShaders;
    QHashtable<QHashedString, QFragmentShader*, SQStringHashProvider> m_arFragmentShaders;
    QShaderCompositor* m_pShaderCompositor;

};

#endif // __QRESOURCEMANAGER__