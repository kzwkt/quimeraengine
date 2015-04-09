
#include "QShadingPipeline.h"

#include "QuimeraEngine.h"

void QShadingPipeline::SetVertexShaderId(const QHashedString &strId)
{
    QShader* pShader = QE->Resources->GetShader(strId);

    glUseProgramStages(m_pipelineId, GL_VERTEX_SHADER_BIT, pShader->GetExternalId());
    m_strVertexShader = strId;
}

QHashedString QShadingPipeline::GetVertexShaderId() const
{
    return m_strVertexShader;
}

// If QResourceManager does not include QShader in the header, it would be possible to move this function to the header and make it inline
QShader* QShadingPipeline::GetVertexShader() const
{
    return QE->Resources->GetShader(m_strVertexShader);
}

void QShadingPipeline::SetFragmentShaderId(const QHashedString &strId)
{
    QShader* pShader = QE->Resources->GetShader(strId);

    glUseProgramStages(m_pipelineId, GL_FRAGMENT_SHADER_BIT, pShader->GetExternalId());
    m_strFragmentShader = strId;
}

QHashedString QShadingPipeline::GetFragmentShaderId() const
{
    return m_strFragmentShader;
}

QShader* QShadingPipeline::GetFragmentShader() const
{
    return QE->Resources->GetShader(m_strFragmentShader);
}

void QShadingPipeline::SetGeometryShaderId(const QHashedString &strId)
{
    QShader* pShader = QE->Resources->GetShader(strId);

    glUseProgramStages(m_pipelineId, GL_GEOMETRY_SHADER_BIT, pShader->GetExternalId());
    m_strGeometryShader = strId;
}

QHashedString QShadingPipeline::GetGeometryShaderId() const
{
    return m_strGeometryShader;
}

QShader* QShadingPipeline::GetGeometryShader() const
{
    return QE->Resources->GetShader(m_strGeometryShader);
}

void QShadingPipeline::SetTesselationEvaluationShaderId(const QHashedString &strId)
{
    QShader* pShader = QE->Resources->GetShader(strId);

    glUseProgramStages(m_pipelineId, GL_TESS_EVALUATION_SHADER_BIT, pShader->GetExternalId());
    m_strTesselationEvaluationShader = strId;
}

QHashedString QShadingPipeline::GetTesselationEvaluationShaderId() const
{
    return m_strTesselationEvaluationShader;
}

QShader* QShadingPipeline::GetTesselationEvaluationShader() const
{
    return QE->Resources->GetShader(m_strTesselationEvaluationShader);
}

void QShadingPipeline::SetTesselationControlShaderId(const QHashedString &strId)
{
    QShader* pShader = QE->Resources->GetShader(strId);

    glUseProgramStages(m_pipelineId, GL_TESS_CONTROL_SHADER_BIT, pShader->GetExternalId());
    m_strTesselationControlShader = strId;
}

QHashedString QShadingPipeline::GetTesselationControlShaderId() const
{
    return m_strTesselationControlShader;
}

QShader* QShadingPipeline::GetTesselationControlShader() const
{
    return QE->Resources->GetShader(m_strTesselationControlShader);
}

void QShadingPipeline::SetComputeShaderId(const QHashedString &strId)
{
    QShader* pShader = QE->Resources->GetShader(strId);

    glUseProgramStages(m_pipelineId, GL_COMPUTE_SHADER_BIT, pShader->GetExternalId());
    m_strComputeShader = strId;
}

QHashedString QShadingPipeline::GetComputeShaderId() const
{
    return m_strComputeShader;
}

QShader* QShadingPipeline::GetComputeShader() const
{
    return QE->Resources->GetShader(m_strComputeShader);
}

GLuint QShadingPipeline::GetExternalId() const
{
    return m_pipelineId;
}