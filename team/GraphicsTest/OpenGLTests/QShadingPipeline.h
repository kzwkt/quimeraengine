
#ifndef __QSHADINGPIPELINE__
#define __QSHADINGPIPELINE__

#include "QuimeraEngineIncludesAndUsings.h"
#include <GL/glew.h>

class QShader;

class QShadingPipeline
{
public:

    QShadingPipeline(GLuint pipelineId) : m_pipelineId(pipelineId)
    {
    }

    void SetVertexShaderId(const QHashedString &strId);

    QHashedString GetVertexShaderId() const;

    // There will be two versions of every getter: one returns the pointer to the object, obtained from the Resource Manager, and the other returns just the ID

    QShader* GetVertexShader() const;

    void SetFragmentShaderId(const QHashedString &strId);

    QHashedString GetFragmentShaderId() const;

    QShader* GetFragmentShader() const;

    void SetGeometryShaderId(const QHashedString &strId);

    QHashedString GetGeometryShaderId() const;

    QShader* GetGeometryShader() const;

    void SetTesselationEvaluationShaderId(const QHashedString &strId);

    QHashedString GetTesselationEvaluationShaderId() const;

    QShader* GetTesselationEvaluationShader() const;

    void SetTesselationControlShaderId(const QHashedString &strId);

    QShader* GetTesselationControlShader() const;

    QHashedString GetTesselationControlShaderId() const;

    void SetComputeShaderId(const QHashedString &strId);

    QHashedString GetComputeShaderId() const;

    QShader* GetComputeShader() const;

    GLuint GetExternalId() const;

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