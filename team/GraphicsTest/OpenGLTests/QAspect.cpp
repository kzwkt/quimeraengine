
#include "QAspect.h"

#include "QuimeraEngine.h"


QShadingPipeline* QAspect::GetShadingPipeline() const
{
    return QE->Resources->GetShadingPipeline(m_strShadingPipeline);
}