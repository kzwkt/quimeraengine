
#ifndef __QSHADINGPIPELINE__
#define __QSHADINGPIPELINE__

#include "QuimeraEngineIncludesAndUsings.h"
#include <GL/glew.h>

class QShadingPipeline
{
public:

    QShadingPipeline(GLuint pipelineId) : m_pipelineId(pipelineId)
    {
    }

    void SetVertexShader(const QHashedString &strId)
    {


        //glUseProgramStages(m_pipelineId, GL_VERTEX_SHADER_BIT, 
        //m_strVertexShader = strId;
    }

    QHashedString GetVertexShader() const
    {
        return m_strVertexShader;
    }

    void SetFragmentShader(const QHashedString &strId)
    {
        m_strFragmentShader = strId;
    }

    QHashedString GetFragmentShader() const
    {
        return m_strFragmentShader;
    }

    void SetGeometryShader(const QHashedString &strId)
    {
        m_strGeometryShader = strId;
    }

    QHashedString GetGeometryShader() const
    {
        return m_strGeometryShader;
    }

    void SetGeometryShader(const QHashedString &strId)
    {
        m_strGeometryShader = strId;
    }

    QHashedString GetGeometryShader() const
    {
        return m_strGeometryShader;
    }

    void SetTesselationEvaluationShader(const QHashedString &strId)
    {
        m_strTesselationEvaluationShader = strId;
    }

    QHashedString GetTesselationEvaluationShader() const
    {
        return m_strTesselationEvaluationShader;
    }

    void SetTesselationEvaluationShader(const QHashedString &strId)
    {
        m_strTesselationEvaluationShader = strId;
    }

    QHashedString GetTesselationEvaluationShader() const
    {
        return m_strTesselationEvaluationShader;
    }

    void SetComputeShader(const QHashedString &strId)
    {
        m_strComputeShader = strId;
    }

    QHashedString GetComputeShader() const
    {
        return m_strComputeShader;
    }

    GLuint GetExternalId() const
    {
        return m_pipelineId;
    }

protected:

    QHashedString m_strVertexShader;
    QHashedString m_strFragmentShader;
    QHashedString m_strGeometryShader;
    QHashedString m_strTesselationControlShader;
    QHashedString m_strTesselationEvaluationShader;
    QHashedString m_strComputeShader;

    GLuint m_pipelineId;
};

#endif // __QSHADINGPIPELINE__