
#ifndef __QGRAPHICSENGINE__
#define __QGRAPHICSENGINE__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QResourceManager.h"

class QGraphicsEngine
{
public:

    QGraphicsEngine(QResourceManager* pResourceManager) : m_pResourceManager(pResourceManager),
                                                          m_pipelineId(0)
    {
        glGenProgramPipelines(1, &m_pipelineId);
        glBindProgramPipeline(m_pipelineId);

        //QE_LOG("LOG: Pogram pipeline set.\n");
    }

    void SetVertexShader(const QHashedString &strId)
    {
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

    QResourceManager* m_pResourceManager;

    // This should be in the QAspect class, which stores both vertex and fragment shaders
    GLuint m_pipelineId;
};

#endif // __QGRAPHICSENGINE__