
#ifndef __QSTATICMODEL__
#define __QSTATICMODEL__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QStaticModelRawData.h"
#include "VertexDefinitions.h"


// Rename to QFixedSizeModel?
class QStaticModel
{
public:

    QStaticModel(const GLuint vaoId, const QHashedString &strVertexBufferId, const QHashedString &strIndexBufferId, const QStaticModelRawData* pRawData) : 
                                                                                        m_arMeshes(pRawData->Meshes),
                                                                                        m_arSubmeshes(pRawData->Submeshes),
                                                                                        m_arSubmeshAspects(pRawData->SubmeshAspects),
                                                                                        m_arMeshIds(pRawData->MeshIds),
                                                                                        m_pVertexDescription(pRawData->VertexDescription),
                                                                                        m_uMeshes(pRawData->MeshCount),
                                                                                        m_uSubmeshes(pRawData->SubmeshCount),
                                                                                        m_uExternalId(vaoId),
                                                                                        m_strVertexBufferId(strVertexBufferId),
                                                                                        m_strIndexBufferId(strIndexBufferId)
    {
    }

    QHashedString GetVertexBufferId() const
    {
        return m_strVertexBufferId;
    }

    QHashedString GetIndexbufferId() const
    {
        return m_strIndexBufferId;
    }

    QStaticModelRawData::QMesh* GetMeshByIndex(const u32_q uIndex) const
    {
        return m_arMeshes + uIndex;
    }

    QStaticModelRawData::QSubmesh* GetSubmeshByIndex(const u32_q uIndex) const
    {
        return m_arSubmeshes + uIndex;
    }

    QStaticModelRawData::QSubmesh* GetSubmeshFromMesh(const u32_q uMeshIndex, const u32_q uSubmeshIndex) const
    {
        u32_q uIndex = (m_arMeshes + uMeshIndex)->FirstSubmesh + uSubmeshIndex;
        return m_arSubmeshes + uIndex;
    }

    QStaticModelRawData::QSubmeshAspect* GetSubmeshAspectByIndex(const u32_q uIndex) const
    {
        return m_arSubmeshAspects + uIndex;
    }

    QStaticModelRawData::QMesh* GetMeshById(const QHashedString &strId) const
    {
        QStaticModelRawData::QMesh* pFoundMesh = null_q;

        u32_q uMeshIndex = 0;

        while (uMeshIndex < m_uMeshes && strId != m_arMeshIds[uMeshIndex].Id)
            ++uMeshIndex;

        if (uMeshIndex < m_uMeshes)
            pFoundMesh = m_arMeshes + m_arMeshIds[uMeshIndex].Mesh;

        return pFoundMesh;
    }

    QStaticModelRawData::QMeshId* GetMeshIdByIndex(const u32_q uIndex) const
    {
        return m_arMeshIds + uIndex;
    }

    const QVertexDescription* GetVertexDescription() const
    {
        return m_pVertexDescription;
    }

    u32_q GetMeshCount() const
    {
        return m_uMeshes;
    }

    u32_q GetSubmeshCount() const
    {
        return m_uSubmeshes;
    }

    u32_q HasMeshes() const
    {
        return m_uMeshes != 0;
    }

    u32_q HasSubmeshes() const
    {
        return m_uSubmeshes != 0;
    }

    pointer_uint_q GetExternalId() const
    {
        return m_uExternalId;
    }

    template<class T>
    T GetExternalIdAs() const
    {
        // For DX
        return rcast_q(m_uExternalId, T);
    }

    void SetExternalId(const pointer_uint_q uId)
    {
        m_uExternalId = uId;
    }

    void SetExternalId(const void* pId)
    {
        // This overload would be used by DX
        m_uExternalId = rcast_q(pId, pointer_uint_q);
    }

protected:

    QStaticModelRawData::QMesh* m_arMeshes;
    QStaticModelRawData::QSubmesh* m_arSubmeshes;
    QStaticModelRawData::QSubmeshAspect* m_arSubmeshAspects;
    QStaticModelRawData::QMeshId* m_arMeshIds;
    const QVertexDescription* m_pVertexDescription;

    u32_q m_uMeshes;
    u32_q m_uSubmeshes;

    pointer_uint_q m_uExternalId;
    QHashedString m_strVertexBufferId;
    QHashedString m_strIndexBufferId;
};


#endif // __QSTATICMODEL__