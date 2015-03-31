
#ifndef __QMODELASPECTSRAWDATA__
#define __QMODELASPECTSRAWDATA__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QTextureBlender.h"
#include "QAspect.h"

struct QModelAspectsRawData
{
    struct QTextureInfo
    {
        QTexture2D::EQTextureMapping Mapping;
        QSampler2D::EQTextureWrapMode WrapMode[3];
        QTextureBlender::EQTextureBlendOperation BlendOperation;
        float_q BlendFactor;
        u8_q TextureCoordsIndex;
        string_q FilePath;
    };

    QMaterial** Materials;
    QTextureInfo* Textures;
    QAspect** Aspects;
    QHashedString* MaterialIds;
    QHashedString* TextureIds;
    QHashedString* AspectIds;
    u32_q MaterialCount;
    u32_q TextureCount;
    u32_q AspectCount;
};

#endif // __QMODELASPECTSRAWDATA__