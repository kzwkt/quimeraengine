
#ifndef __QSTATICMODELRAWDATA__
#define __QSTATICMODELRAWDATA__

#include "QuimeraEngineIncludesAndUsings.h"
#include "VertexDefinitions.h"

struct QStaticModelRawData
{
    enum EQPrimitiveType
    {
        E_Point,
        E_Line,
        E_Triangle,
        E_Polygon
    };

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
        EQPrimitiveType PrimitiveType;
    };

    struct QSubmeshAspect
    {
        u32_q Submesh;
        QHashedString AspectId;
    };

    void* Vertices;
    u32_q* Indices;
    QMesh* Meshes;
    QSubmesh* Submeshes;
    QSubmeshAspect* SubmeshAspects;
    QMeshId* MeshIds;
    const QVertexDescription* VertexDescription;

    u32_q VertexCount;
    u32_q IndexCount;
    u32_q MeshCount;
    u32_q SubmeshCount;

};

#endif // __QSTATICMODELRAWDATA__