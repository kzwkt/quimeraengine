
#ifndef __QRESOURCEMANAGER__
#define __QRESOURCEMANAGER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QVertexShader.h"
#include "QFragmentShader.h"
#include "QShaderCompositor.h"

class QResourceManager
{
public:

    QResourceManager(QShaderCompositor* pShaderCompositor) : m_arVertexShaders(5, 2),
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

    QVertexShader* GetVertexShader(const QHashedString &strId) const
    {
        return m_arVertexShaders[strId];
    }

    QFragmentShader* GetFragmentShader(const QHashedString &strId) const
    {
        return m_arFragmentShaders[strId];
    }

protected:

    QHashtable<QHashedString, QVertexShader*, SQStringHashProvider> m_arVertexShaders;
    QHashtable<QHashedString, QFragmentShader*, SQStringHashProvider> m_arFragmentShaders;
    QShaderCompositor* m_pShaderCompositor;

};

#endif // __QRESOURCEMANAGER__