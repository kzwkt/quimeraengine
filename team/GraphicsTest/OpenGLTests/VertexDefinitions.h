
#ifndef __VERTEXDEFINITIONS__
#define __VERTEXDEFINITIONS__

#include "QuimeraEngineIncludesAndUsings.h"

struct QVertexComponent
{
    enum EQVertexComponentType
    {
        E_Position3D = 0,
        E_Position4D = 1,
        E_Normal = 2,
        E_TextureCoord2D = 3,
        E_TextureCoord3D = 4,
        E_Color = 5,
        E_Custom = 0xFFFFFFFF
    };

    u32_q Size;
    EQVertexComponentType Type;
    const char* Name; // This may not be necessary since names are always the same and can be deduced from Type (DirectX). However, it could serve to get the location of an input with OpenGL.
    // bool IsInstanced;
    // u32_q InstanceUpdateFrequency;

    static const u32_q* GetValuesPerComponentType();
};

class QVertexDescription
{
public:

    u32_q GetVertexSize() const
    {
        return m_uSize;
    }

    u32_q GetVertexComponentCount() const
    {
        return m_uVertexComponents;
    }

    const QVertexComponent* GetVertexComponents() const
    {
        return m_arVertexComponents;
    }

protected:

    void Initialize(const QVertexComponent* arVertexComponents, const u32_q uVertexComponents)
    {
        m_arVertexComponents = arVertexComponents;
        m_uVertexComponents = uVertexComponents;
        m_uSize = QVertexDescription::CalculateSize(arVertexComponents, uVertexComponents);
    }

    static u32_q CalculateSize(const QVertexComponent* arVertexComponents, const u32_q uVertexComponents)
    {
        u32_q uVertexSize = 0;
        for (u32_q i = 0; i < uVertexComponents; ++i)
            uVertexSize += arVertexComponents[i].Size;

        return uVertexSize;
    }

    const QVertexComponent* m_arVertexComponents;
    u32_q m_uVertexComponents;
    u32_q m_uSize;
};

class QCustomVertexDescription : public QVertexDescription
{
public:

    QCustomVertexDescription()
    {
        static const QVertexComponent VERTEX_COMPONENTS[] = { QVertexComponent::GetValuesPerComponentType()[QVertexComponent::E_Position4D],     QVertexComponent::E_Position4D,     null_q,
                                                              QVertexComponent::GetValuesPerComponentType()[QVertexComponent::E_Normal],         QVertexComponent::E_Normal,         null_q,
                                                              QVertexComponent::GetValuesPerComponentType()[QVertexComponent::E_TextureCoord2D], QVertexComponent::E_TextureCoord2D, null_q,
                                                              QVertexComponent::GetValuesPerComponentType()[QVertexComponent::E_TextureCoord2D], QVertexComponent::E_TextureCoord2D, null_q
                                                            };

        this->Initialize(VERTEX_COMPONENTS, sizeof(VERTEX_COMPONENTS) / sizeof(QVertexComponent));
    }
};

extern QCustomVertexDescription CUSTOM_VERTEX_DESCRIPTION;


struct QVertexWith1Normal2TextureCoords
{
    QVector4 Position;
    QVector3 Normal;
    QVector2 TextureCoords[2];
};

#endif // __VERTEXDEFINITIONS__