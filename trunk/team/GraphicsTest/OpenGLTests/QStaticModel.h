
#ifndef __QSTATICMODEL__
#define __QSTATICMODEL__

#include "QuimeraEngineIncludesAndUsings.h"
#include "VertexDefinitions.h"

class QModelLoader;

class QStaticModel
{
    friend QModelLoader;

    struct QMesh
    {
        u32_q FirstSubmesh;
        u32_q SubmeshCount;
        u32_q SiblingMesh;
        u32_q FirstChildMesh;
        QVector3 Translation;
        QQuaternion Rotation;
        QVector3 Scale;
    };

    struct QMeshId
    {
        QHashedString Id;
        u32_q Mesh;
    };

    struct QSubmesh
    {
        u32_q FirstVertex;
        u32_q VertexCount;
        u32_q FirstIndex;
        u32_q IndexCount;
    };

    struct QSubmeshAspect
    {
        u32_q Submesh;
        QHashedString AspectId;
    };

public:

    QStaticModel(const QVertexDescription* pVertexDescription) : m_arVertices(null_q),
                                                                 m_arIndices(null_q),
                                                                 m_arMeshes(null_q),
                                                                 m_arSubmeshes(null_q),
                                                                 m_arSubmeshAspects(null_q),
                                                                 m_arMeshIds(null_q),
                                                                 m_pVertexDescription(pVertexDescription),
                                                                 m_uVertices(0),
                                                                 m_uIndices(0),
                                                                 m_uMeshes(0),
                                                                 m_uSubmeshes(0),
                                                                 m_uExternalId(0)
    {
    }

    void* GenerateVertexBuffer(const u32_q uVertexSize, const u32_q uAmount)
    {
        if (m_arVertices)
        {
            delete[] (char*)m_arVertices;
        }

        m_arVertices = new char[uVertexSize * uAmount];
        m_uVertices = uAmount;
        return m_arVertices;
    }

    u32_q* GenerateIndexBuffer(const u32_q uAmount)
    {
        if (m_arIndices)
        {
            delete[] m_arIndices;
        }

        m_arIndices = new u32_q[uAmount];
        m_uIndices = uAmount;
        return m_arIndices;
    }

    void GenerateMeshBuffers(const u32_q uMeshes, const u32_q uSubmeshes)
    {
        if (m_arMeshes)
        {
            delete[] m_arMeshes;
        }

        if (m_arSubmeshes)
        {
            delete[] m_arSubmeshes;
        }

        if (m_arMeshIds)
        {
            delete[] m_arMeshIds;
        }

        if (m_arSubmeshAspects)
        {
            delete[] m_arSubmeshAspects;
        }

        m_arMeshes = new QMesh[uMeshes];
        m_arMeshIds = new QMeshId[uMeshes];
        m_arSubmeshes = new QSubmesh[uSubmeshes];
        m_arSubmeshAspects = new QSubmeshAspect[uSubmeshes];
        m_uMeshes = uMeshes;
        m_uSubmeshes = uSubmeshes;
    }

    void* GetVertexBuffer() const
    {
        return m_arVertices;
    }

    u32_q* GetIndexbuffer() const
    {
        return m_arIndices;
    }

    QMesh* GetMeshByIndex(const u32_q uIndex) const
    {
        return m_arMeshes + uIndex;
    }

    QSubmesh* GetSubmeshByIndex(const u32_q uIndex) const
    {
        return m_arSubmeshes + uIndex;
    }

    QSubmesh* GetSubmeshFromMesh(const u32_q uMeshIndex, const u32_q uSubmeshIndex) const
    {
        u32_q uIndex = (m_arMeshes + uMeshIndex)->FirstSubmesh + uSubmeshIndex;
        return m_arSubmeshes + uIndex;
    }

    QSubmeshAspect* GetSubmeshAspectByIndex(const u32_q uIndex) const
    {
        return m_arSubmeshAspects + uIndex;
    }

    QMesh* GetMeshById(const QHashedString &strId) const
    {
        QMesh* pFoundMesh = null_q;

        u32_q uMeshIndex = 0;

        while (uMeshIndex < m_uMeshes && strId != m_arMeshIds[uMeshIndex].Id)
            ++uMeshIndex;

        if (uMeshIndex < m_uMeshes)
            pFoundMesh = m_arMeshes + m_arMeshIds[uMeshIndex].Mesh;

        return pFoundMesh;
    }

    QMeshId* GetMeshIdByIndex(const u32_q uIndex) const
    {
        return m_arMeshIds + uIndex;
    }

    const QVertexDescription* GetVertexDescription() const
    {
        return m_pVertexDescription;
    }

    u32_q GetVertexCount() const
    {
        return m_uVertices;
    }

    u32_q GetIndexCount() const
    {
        return m_uIndices;
    }

    u32_q GetMeshCount() const
    {
        return m_uMeshes;
    }

    u32_q GetSubmeshCount() const
    {
        return m_uSubmeshes;
    }

    u32_q HasVertices() const
    {
        return m_uVertices != 0;
    }

    u32_q HasIndices() const
    {
        return m_uIndices != 0;
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

    void* m_arVertices;
    u32_q* m_arIndices;
    QMesh* m_arMeshes;
    QSubmesh* m_arSubmeshes;
    QSubmeshAspect* m_arSubmeshAspects;
    QMeshId* m_arMeshIds;
    const QVertexDescription* m_pVertexDescription;

    u32_q m_uVertices;
    u32_q m_uIndices;
    u32_q m_uMeshes;
    u32_q m_uSubmeshes;

    pointer_uint_q m_uExternalId;
};


#endif // __QSTATICMODEL__