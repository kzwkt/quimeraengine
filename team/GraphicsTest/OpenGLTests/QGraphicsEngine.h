
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

    void UpdateVertexShaderData(const QHashedString &strVertexShaderId, const string_q &strDataBufferName, const f32_q fValue0, const f32_q fValue1, const f32_q fValue2, const f32_q fValue3)
    {
        QVertexShader* pVertexShader = m_pResourceManager->GetVertexShader(strVertexShaderId);

        GLint bufferLocation = glGetUniformLocation(pVertexShader->GetProgramID(), strDataBufferName.ToBytes(EQTextEncoding::E_ASCII).Get());

        QE_ASSERT_ERROR(bufferLocation != -1, string_q("The shader data buffer with name \"") + strDataBufferName + "\" was not found in the shader with ID \"" + strVertexShaderId + "\".");
        
        glProgramUniform4f(pVertexShader->GetProgramID(), bufferLocation, fValue0, fValue1, fValue2, fValue3);
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