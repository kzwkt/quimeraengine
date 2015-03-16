
#ifndef __QMODELLOADER__
#define __QMODELLOADER__


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "QStaticModel.h"
#include "VertexDefinitions.h"

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
#define QE_LOG_MODELLOAD(strMessage) QE_LOG(strMessage)
#else
#define QE_LOG_MODELLOAD(strMessage)
#endif

#undef max

// IMPORTANT: Float precision must match ASSIMP's floats precission

class QModelLoader
{
public:

    // The vertex type should be flexible

    static void LoadModel(const QPath &filePath, QStaticModel &model)
    {
        QE_LOG_MODELLOAD(string_q("Loading model from '") + filePath.GetAbsolutePath() + "'");

        Assimp::Importer importer;
        const aiScene* pScene = importer.ReadFile(filePath.ToString().ToBytes(EQTextEncoding::E_UTF8).Get(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded | aiProcess_FindInvalidData | aiProcess_ValidateDataStructure);

        QE_ASSERT_ERROR(pScene != null_q && pScene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && pScene->mRootNode != null_q,
                        string_q("An error occurred when loading a model from '") + filePath.ToString() + "'. " + importer.GetErrorString());

        QE_LOG_MODELLOAD("ASSIMP model loaded correctly\n");

        QE_LOG_MODELLOAD("Creating internal model...\n");

        u32_q uNumVertices = 0;
        u32_q uNumIndices = 0;
        u32_q uNumNodes = CountNodes(pScene->mRootNode) + 1U;
        aiMesh** pCurrenMesh = pScene->mMeshes;

        for (u32_q i = 0; i < pScene->mNumMeshes; ++i, ++pCurrenMesh)
        {
            uNumVertices += (*pCurrenMesh)->mNumVertices;
            uNumIndices += (*pCurrenMesh)->mNumFaces * 3U;
        }
        
        model.GenerateVertexBuffer(model.GetVertexDescription()->GetVertexSize(), uNumVertices);
        model.GenerateIndexBuffer(uNumIndices);
        model.GenerateMeshBuffers(uNumNodes, pScene->mNumMeshes);

        QE_LOG_MODELLOAD(string_q("Vertex buffer: ") + string_q::FromInteger(uNumVertices) + " vertices\n");
        QE_LOG_MODELLOAD(string_q("Index buffer: ") + string_q::FromInteger(uNumIndices) + " indices\n");
        QE_LOG_MODELLOAD(string_q("Mesh buffer: ") + string_q::FromInteger(uNumNodes) + " meshes\n");
        QE_LOG_MODELLOAD(string_q("Submesh buffer: ") + string_q::FromInteger(pScene->mNumMeshes) + " submeshes\n");
        QE_LOG_MODELLOAD("\n");

        QE_LOG_MODELLOAD("Processing ASSIMP model...\n");

        u32_q uMeshIndex = 1;
        u32_q uSubmeshIndex = 0;
        ProcessNode(pScene->mRootNode, model, 0, 0);
        ProcessHierarchy(model, pScene->mMeshes, pScene->mRootNode, uMeshIndex, uSubmeshIndex, 0);

        QE_LOG_MODELLOAD("Freeing intermediate resources...\n");

        importer.FreeScene();

        QE_LOG_MODELLOAD("Model loaded.\n");
    }

protected:

    static u32_q CountNodes(const aiNode* pNode)
    {
        u32_q uNumNodes = 0;

        for (u32_q i = 0; i < pNode->mNumChildren; ++i)
            uNumNodes += CountNodes(pNode->mChildren[i]);

        return pNode->mNumChildren + uNumNodes;
    }

    static void ProcessHierarchy(QStaticModel &model, aiMesh** const arMeshes, const aiNode* pNode, u32_q &uOutpuMeshIndex, u32_q &uOutpuSubmeshIndex, const u32_q uParentMeshIndex)
    {
        //        A
        //       / \
        //      B   D
        //     /   / \
        //    C   E   F

        // Meshes    [  A   |   B  |  C   |  D   |  E   |   F  |      |      |      ]
        // Submeshes [  A1  |  A2  |  B1  |  C1  |  D1  |  D2  |  E1  |  F1  |      ]

        // The intent is that meshes in the same level under a node, or brother nodes, are contiguous

        QStaticModel::QMesh* pParentMesh = model.GetMeshByIndex(uParentMeshIndex);
        pParentMesh->FirstChildMesh = -1;

        if(pNode->mNumChildren != 0)
            pParentMesh->FirstChildMesh = uOutpuMeshIndex;

        QE_LOG_MODELLOAD(string_q("Processing children of mesh[") + string_q::FromInteger(uParentMeshIndex) + "]...\n");
        QE_LOG_MODELLOAD(string_q("First child: ") + string_q::FromInteger(pParentMesh->FirstChildMesh) + "\n");

        QStaticModel::QMesh* pPreviousMesh = null_q;

        for (u32_q i = 0; i < pNode->mNumChildren; ++i, ++uOutpuMeshIndex)
        {
            ProcessNode(pNode->mChildren[i], model, uOutpuMeshIndex, uOutpuSubmeshIndex);

            if (pNode->mChildren[i]->mNumMeshes > 0)
                ProcessMesh(arMeshes, pNode->mChildren[i]->mMeshes, model, uOutpuMeshIndex, uOutpuSubmeshIndex);
        }

        QE_LOG_MODELLOAD(string_q("Children of mesh[") + string_q::FromInteger(uParentMeshIndex) + "] processed.\n");
        QE_LOG_MODELLOAD("Processing every child's children...\n");

        for (u32_q i = 0; i < pNode->mNumChildren; ++i)
            ProcessHierarchy(model, arMeshes, pNode->mChildren[i], uOutpuMeshIndex, uOutpuSubmeshIndex, uParentMeshIndex + i);

        QE_LOG_MODELLOAD("Child's children processed.\n");
    }

    static void ProcessNode(aiNode* const pInputNode, QStaticModel &model, const u32_q uMeshIndex, const u32_q uSubmeshIndex)
    {
        QE_LOG_MODELLOAD(string_q("Processing mesh[") + string_q::FromInteger(uMeshIndex) + "]...\n");

        QStaticModel::QMesh* pMesh = model.GetMeshByIndex(uMeshIndex);
        QStaticModel::QMeshId* pMeshId = model.GetMeshIdByIndex(uMeshIndex);
        pMesh->SubmeshCount = pInputNode->mNumMeshes;
        pMesh->FirstSubmesh = uSubmeshIndex;
        pMeshId->Mesh = uMeshIndex;
        pMeshId->Id = pInputNode->mName.C_Str();
        QTransformationMatrix<QMatrix4x4> transformation(QMatrix4x4(&pInputNode->mTransformation.a1));
        transformation.Decompose(pMesh->Translation, pMesh->Rotation, pMesh->Scale);

        QE_LOG_MODELLOAD(string_q("First submesh: ") + string_q::FromInteger(pMesh->FirstSubmesh) + "\n");
        QE_LOG_MODELLOAD(string_q("Number of submeshes: ") + string_q::FromInteger(pMesh->SubmeshCount) + "\n");
        QE_LOG_MODELLOAD(string_q("Name: ") + pMeshId->Id + "\n");
        QE_LOG_MODELLOAD(string_q("Translation: ") + pMesh->Translation.ToString() + "\n");
        QE_LOG_MODELLOAD(string_q("Rotation: ") + pMesh->Rotation.ToString() + "\n");
        QE_LOG_MODELLOAD(string_q("Scale: ") + pMesh->Scale.ToString() + "\n");
        QE_LOG_MODELLOAD("\n");
    }

    static void ProcessMesh(aiMesh** const arExternalSubmeshes, unsigned int* arSubmeshes, QStaticModel &model, const u32_q uMeshIndex, u32_q &uOutpuSubmeshIndex)
    {
        for (u32_q i = 0; i < model.GetMeshByIndex(uMeshIndex)->SubmeshCount; ++i, ++uOutpuSubmeshIndex)
            ProcessSubmesh(arExternalSubmeshes[arSubmeshes[i]], model, model.GetMeshByIndex(uMeshIndex)->FirstSubmesh + i);
    }

    static void ProcessSubmesh(const aiMesh* pExternalSubmesh, QStaticModel &model, const u32_q uSubmeshIndex)
    {
        QE_LOG_MODELLOAD(string_q("Processing submesh[") + string_q::FromInteger(uSubmeshIndex) + "]...\n");

        QStaticModel::QSubmesh* pSubmesh = model.GetSubmeshByIndex(uSubmeshIndex);
        pSubmesh->VertexCount = pExternalSubmesh->mNumVertices;
        pSubmesh->IndexCount = pExternalSubmesh->mNumFaces * 3U;
        pSubmesh->FirstVertex = 0;
        pSubmesh->FirstIndex = 0;

        if (uSubmeshIndex != 0)
        {
            QStaticModel::QSubmesh* pPreviousSubmesh = model.GetSubmeshByIndex(uSubmeshIndex - 1U);
            pSubmesh->FirstVertex = pPreviousSubmesh->FirstVertex + pPreviousSubmesh->VertexCount;
            pSubmesh->FirstIndex = pPreviousSubmesh->FirstIndex + pPreviousSubmesh->IndexCount;
        }

        QE_LOG_MODELLOAD(string_q("Number of vertices: ") + string_q::FromInteger(pSubmesh->VertexCount) + "\n");
        QE_LOG_MODELLOAD(string_q("Number of indices: ") + string_q::FromInteger(pSubmesh->IndexCount) + "\n");
        QE_LOG_MODELLOAD(string_q("First vertex: ") + string_q::FromInteger(pSubmesh->FirstVertex) + "\n");
        QE_LOG_MODELLOAD(string_q("First index: ") + string_q::FromInteger(pSubmesh->FirstIndex) + "\n");


        const QVertexDescription* pVertexDescription = model.GetVertexDescription();
        float_q* pFirstValueInSubmesh = rcast_q(rcast_q(model.GetVertexBuffer(), pointer_uint_q) + pSubmesh->FirstVertex * pVertexDescription->GetVertexSize(), float_q*);

        u32_q uComponentOffset = 0;
        u32_q uTextureCoordArrayIndex = 0;
        u32_q uColorArrayIndex = 0;
        const u32_q NUMBER_OF_VALUES_IN_VERTEX = pVertexDescription->GetVertexSize() / sizeof(float_q);

        for (u32_q i = 0; i < pVertexDescription->GetVertexComponentCount(); ++i)
        {
            switch (pVertexDescription->GetVertexComponents()[i].Type)
            {
            case QVertexComponent::E_Position3D:
                Copy3DVectors(&pExternalSubmesh->mVertices->x, pFirstValueInSubmesh + uComponentOffset, pSubmesh->VertexCount, NUMBER_OF_VALUES_IN_VERTEX);
                break;
            case QVertexComponent::E_Position4D:
                CopyVertexPositions4D(&pExternalSubmesh->mVertices->x, pFirstValueInSubmesh + uComponentOffset, pSubmesh->VertexCount, NUMBER_OF_VALUES_IN_VERTEX);
                break;
            case QVertexComponent::E_Normal:
                if (pExternalSubmesh->mNormals)
                    Copy3DVectors(&pExternalSubmesh->mNormals->x, pFirstValueInSubmesh + uComponentOffset, pSubmesh->VertexCount, NUMBER_OF_VALUES_IN_VERTEX);
                break;
            case QVertexComponent::E_TextureCoord2D:
                if (pExternalSubmesh->mTextureCoords && uTextureCoordArrayIndex < pExternalSubmesh->GetNumUVChannels())
                    CopyTextureCoords2D(&pExternalSubmesh->mTextureCoords[uTextureCoordArrayIndex]->x, pFirstValueInSubmesh + uComponentOffset, pSubmesh->VertexCount, NUMBER_OF_VALUES_IN_VERTEX);
                ++uTextureCoordArrayIndex;
                break;
            case QVertexComponent::E_TextureCoord3D:
                if (pExternalSubmesh->mTextureCoords && uTextureCoordArrayIndex < pExternalSubmesh->GetNumUVChannels())
                    Copy3DVectors(&pExternalSubmesh->mTextureCoords[uTextureCoordArrayIndex]->x, pFirstValueInSubmesh + uComponentOffset, pSubmesh->VertexCount, NUMBER_OF_VALUES_IN_VERTEX);
                ++uTextureCoordArrayIndex;
                break;
            case QVertexComponent::E_Color:
                if (pExternalSubmesh->mColors)
                    Copy4DVectors(&pExternalSubmesh->mColors[uColorArrayIndex]->r, pFirstValueInSubmesh + uComponentOffset, pSubmesh->VertexCount, NUMBER_OF_VALUES_IN_VERTEX);
                ++uColorArrayIndex;
                break;
            }

            uComponentOffset += pVertexDescription->GetVertexComponents()[i].Size / sizeof(float_q);
        }

        CopyTriangleIndices(model.GetIndexbuffer() + pSubmesh->FirstIndex, pExternalSubmesh->mFaces, pSubmesh->IndexCount, pSubmesh->FirstVertex);
    }

    static void CopyTriangleIndices(u32_q* arOutputIndices, const aiFace* arInputFaces, const u32_q uIndexCount, const u32_q uIndexOffset)
    {
        for (u32_q i = 0; i < uIndexCount; ++i)
            arOutputIndices[i] = arInputFaces[i / 3U].mIndices[i % 3U] + uIndexOffset;
        /*
        for (u32_q i = 0; i < uIndexCount / 3U; i += 3U)
        {
            arOutputIndices[i + 0] = arInputFaces[i].mIndices[2] + uIndexOffset;
            arOutputIndices[i + 1] = arInputFaces[i].mIndices[1] + uIndexOffset;
            arOutputIndices[i + 2] = arInputFaces[i].mIndices[0] + uIndexOffset;
        }*/
    }

    static void Copy2DVectors(float* pInput, float_q* pOutput, const u32_q uVectors, const u32_q uVertexSize)
    {
        for (u32_q i = 0; i < uVectors; ++i)
        {
            u32_q uOutputVectorComponentIndex = uVertexSize * i;
            u32_q uInputVectorComponentIndex = 2U * i;
            pOutput[0 + uOutputVectorComponentIndex] = pInput[0 + uInputVectorComponentIndex];
            pOutput[1 + uOutputVectorComponentIndex] = pInput[1 + uInputVectorComponentIndex];
        }
    }

    static void Copy3DVectors(float* pInput, float_q* pOutput, const u32_q uVectors, const u32_q uVertexSize)
    {
        for (u32_q i = 0; i < uVectors; ++i)
        {
            u32_q uOutputVectorComponentIndex = uVertexSize * i;
            u32_q uInputVectorComponentIndex = 3U * i;
            pOutput[0 + uOutputVectorComponentIndex] = pInput[0 + uInputVectorComponentIndex];
            pOutput[1 + uOutputVectorComponentIndex] = pInput[1 + uInputVectorComponentIndex];
            pOutput[2 + uOutputVectorComponentIndex] = pInput[2 + uInputVectorComponentIndex];
        }
    }

    static void Copy4DVectors(float* pInput, float_q* pOutput, const u32_q uVectors, const u32_q uVertexSize)
    {
        for (u32_q i = 0; i < uVectors; ++i)
        {
            u32_q uOutputVectorComponentIndex = uVertexSize * i;
            u32_q uInputVectorComponentIndex = 4U * i;
            pOutput[0 + uOutputVectorComponentIndex] = pInput[0 + uInputVectorComponentIndex];
            pOutput[1 + uOutputVectorComponentIndex] = pInput[1 + uInputVectorComponentIndex];
            pOutput[2 + uOutputVectorComponentIndex] = pInput[2 + uInputVectorComponentIndex];
            pOutput[3 + uOutputVectorComponentIndex] = pInput[3 + uInputVectorComponentIndex];
        }
    }

    static void CopyVertexPositions4D(float* pInputPosition, float_q* pOutputPosition, const u32_q uVertices, const u32_q uVertexSize)
    {
        for (u32_q i = 0; i < uVertices; ++i)
        {
            u32_q uOutputPositionComponentIndex = uVertexSize * i;
            u32_q uInputPositionComponentIndex = 3U * i;
            pOutputPosition[0 + uOutputPositionComponentIndex] = pInputPosition[0 + uInputPositionComponentIndex];
            pOutputPosition[1 + uOutputPositionComponentIndex] = pInputPosition[1 + uInputPositionComponentIndex];
            pOutputPosition[2 + uOutputPositionComponentIndex] = pInputPosition[2 + uInputPositionComponentIndex];
            pOutputPosition[3 + uOutputPositionComponentIndex] = SQFloat::_1;
        }
    }

    static void CopyTextureCoords2D(float* pInput, float_q* pOutput, const u32_q uVectors, const u32_q uVertexSize)
    {
        for (u32_q i = 0; i < uVectors; ++i)
        {
            u32_q uOutputVectorComponentIndex = uVertexSize * i;
            u32_q uInputVectorComponentIndex = 3U * i;
            pOutput[0 + uOutputVectorComponentIndex] = pInput[0 + uInputVectorComponentIndex];
            pOutput[1 + uOutputVectorComponentIndex] = pInput[1 + uInputVectorComponentIndex];
        }
    }

};

#endif // __QMODELLOADER__