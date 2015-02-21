
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

protected:

    QResourceManager* m_pResourceManager;
    GLuint m_pipelineId;
};

#endif // __QGRAPHICSENGINE__