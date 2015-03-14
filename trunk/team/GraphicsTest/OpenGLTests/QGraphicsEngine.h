
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

        QE_LOG("LOG: Pogram pipeline set.\n");
    }

    void SetVertexShader(const QHashedString &strId)
    {
        QVertexShader* pVertexShader = m_pResourceManager->GetVertexShader(strId);

        // Makes the program the current
        glUseProgramStages(m_pipelineId, GL_VERTEX_SHADER_BIT, pVertexShader->GetProgramID());

        QE_LOG(string_q("LOG: Using vertex shader [") + strId + "].\n");
    }

    void SetFragmentShader(const QHashedString &strId)
    {
        QFragmentShader* pFragmentShader = m_pResourceManager->GetFragmentShader(strId);

        // Makes the program the current
        glUseProgramStages(m_pipelineId, GL_FRAGMENT_SHADER_BIT, pFragmentShader->GetProgramID());

        QE_LOG(string_q("LOG: Using fragment shader [") + strId + "].\n");
    }

    void SetTexture(const QHashedString &strTextureId, const unsigned int uIndex, const QHashedString &strShaderId, const char* szShaderSamplerName)
    {
        QFragmentShader* pFragmentShader = m_pResourceManager->GetFragmentShader(strShaderId);
        QTexture2D* pTexture = m_pResourceManager->GetTexture2D(strTextureId);

        glActiveTexture(GL_TEXTURE0 + uIndex);
        glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureID());

        GLint samplerLocation = glGetUniformLocation(pFragmentShader->GetProgramID(), szShaderSamplerName);

        if (samplerLocation == -1)
        {
            QE_ASSERT_WINDOWS_ERROR("An error occurred while getting the location of a uniform (SetupTextures).");
        }

        glProgramUniform1i(pFragmentShader->GetProgramID(), samplerLocation, uIndex);

        QE_LOG(string_q("LOG: Using texture [") + strTextureId + "] in sampler \"" + szShaderSamplerName + "\" with index " + string_q::FromInteger(uIndex) + ".\n");
    }

    void SetAspect(const QHashedString &strAspectId)
    {
        QE_LOG(string_q("LOG: Setting aspect [") + strAspectId + "]...\n");

        QAspect* pAspect = m_pResourceManager->GetAspect(strAspectId);

        this->SetVertexShader(pAspect->GetVertexShader());
        this->SetFragmentShader(pAspect->GetFragmentShader());
        
        for (unsigned int i = 0; i < pAspect->GetTextureCount(); ++i)
            this->SetTexture(pAspect->GetTextureId(i), i, pAspect->GetFragmentShader(), pAspect->GetShaderSamplerName(i));
        
        QE_LOG(string_q("LOG: Aspect [") + strAspectId + "] set.\n");
    }

    void UpdateVertexShaderData(const QHashedString &strVertexShaderId, const string_q &strDataBufferName, const f32_q fValue0, const f32_q fValue1, const f32_q fValue2, const f32_q fValue3)
    {
        QVertexShader* pVertexShader = m_pResourceManager->GetVertexShader(strVertexShaderId);

        GLint bufferLocation = glGetUniformLocation(pVertexShader->GetProgramID(), strDataBufferName.ToBytes(EQTextEncoding::E_ASCII).Get());

        QE_ASSERT_ERROR(bufferLocation != -1, string_q("The shader data buffer with name \"") + strDataBufferName + "\" was not found in the shader with ID \"" + strVertexShaderId + "\".");
        
        glProgramUniform4f(pVertexShader->GetProgramID(), bufferLocation, fValue0, fValue1, fValue2, fValue3);
    }

    void UpdateVertexShaderData(const QHashedString &strVertexShaderId, const string_q &strDataBufferName, const QBaseMatrix4x4 &matrix)
    {
        QVertexShader* pVertexShader = m_pResourceManager->GetVertexShader(strVertexShaderId);

        // Store the location of every uniform so this call does not have to be performed every time
        GLint bufferLocation = glGetUniformLocation(pVertexShader->GetProgramID(), strDataBufferName.ToBytes(EQTextEncoding::E_ASCII).Get());

        QE_ASSERT_ERROR(bufferLocation != -1, string_q("The shader data buffer with name \"") + strDataBufferName + "\" was not found in the shader with ID \"" + strVertexShaderId + "\".");

        glProgramUniformMatrix4fv(pVertexShader->GetProgramID(), bufferLocation, 1, GL_FALSE, &matrix.ij[0][0]); // No traspose
    }

    // Should receive pointers instead of string ids? performance vs robustness
    void UpdateFragmentShaderData(const QHashedString &strVertexShaderId, const string_q &strDataBufferName, const f32_q fValue0, const f32_q fValue1, const f32_q fValue2, const f32_q fValue3)
    {
        QFragmentShader* pFragmentShader = m_pResourceManager->GetFragmentShader(strVertexShaderId);

        GLint bufferLocation = glGetUniformLocation(pFragmentShader->GetProgramID(), strDataBufferName.ToBytes(EQTextEncoding::E_ASCII).Get());

        QE_ASSERT_ERROR(bufferLocation != -1, string_q("The shader data buffer with name \"") + strDataBufferName + "\" was not found in the shader with ID \"" + strVertexShaderId + "\".");

        glProgramUniform4f(pFragmentShader->GetProgramID(), bufferLocation, fValue0, fValue1, fValue2, fValue3);
    }

protected:

    QResourceManager* m_pResourceManager;

    // This should be in the QAspect class, which stores both vertex and fragment shaders
    GLuint m_pipelineId;
};

#endif // __QGRAPHICSENGINE__