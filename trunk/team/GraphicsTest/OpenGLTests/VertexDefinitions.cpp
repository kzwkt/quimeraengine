
#include "VertexDefinitions.h"


const u32_q* QVertexComponent::GetValuesPerComponentType()
{
    static const u32_q VALUES_PER_TYPE[] = {
                                            3U * sizeof(float_q), // E_Position3D
                                            4U * sizeof(float_q), // E_Position4D
                                            3U * sizeof(float_q), // E_Normal
                                            2U * sizeof(float_q), // E_TextureCoord2D
                                            3U * sizeof(float_q), // E_TextureCoord3D
                                            4U * sizeof(float_q)  // E_Color
                                           };

    return VALUES_PER_TYPE;
}

QCustomVertexDescription CUSTOM_VERTEX_DESCRIPTION;