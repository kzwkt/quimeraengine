
#ifndef __QASPECT__
#define __QASPECT__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QMaterial.h"
#include "QVertexShader.h"
#include "QFragmentShader.h"
#include "QTexture2D.h"

class QAspect
{
public:

    static const unsigned int MAX_LAYERS = 8;
    static const unsigned int MAX_COMPONENTS = 11;

    struct QTextureLayer
    {
        QHashedString TextureId;
        QHashedString BlenderId;
        QHashedString SamplerId;
    };

    struct QAspectComponent
    {
        QTextureLayer TextureStack[QAspect::MAX_LAYERS];
        u8_q TextureStackSize;
        u8_q Enabled;
    };

    enum EQAspectComponentType
    {
        E_Ambient,
        E_Diffuse,
        E_Specular,
        E_Normals,
        E_Opacity,
        E_Displacement,
        E_Height,
        E_Shininess,
        E_Reflection,
        E_Lightmap,
        E_Emissive
    };

    enum EQAlphaBlendingMode
    {
        E_Alpha,
        E_Addition
    };


    QAspect() : m_bWireframeEnabled(false),
                m_bFaceCullingEnabled(true),
                m_bFaceted(false),
                m_eAplhaBlendingMode(E_Addition),
                m_fOpacity(SQFloat::_0)
    {
        static QHashedString DEFAULT_ID = "QE:DEFAULT";

        m_strVertexShader = DEFAULT_ID;
        m_strFragmentShader = DEFAULT_ID;
        m_strMaterial = DEFAULT_ID;

        static QAspectComponent DEFAULT_ASPECT_COMPONENTS[] = { { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                                { { DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID,
                                                                    DEFAULT_ID, DEFAULT_ID, DEFAULT_ID, }, 0, true },
                                                            };

        memcpy(m_arAspectComponents, DEFAULT_ASPECT_COMPONENTS, sizeof(DEFAULT_ASPECT_COMPONENTS));

    }

    void SetVertexShader(const QHashedString &strId)
    {
        m_strVertexShader = strId;
    }

    void SetFragmentShader(const QHashedString &strId)
    {
        m_strFragmentShader = strId;
    }

    void AddTextureLayer(const EQAspectComponentType eComponentType, const QHashedString textureId, const QHashedString samplerId, const QHashedString blenderId)
    {
        QE_ASSERT_ERROR(m_arAspectComponents[eComponentType].TextureStackSize <= QAspect::MAX_LAYERS, string_q("The stack of textures is full, it is not possible to add another one."));

        u32_q uNewIndex = m_arAspectComponents[eComponentType].TextureStackSize;
        ++m_arAspectComponents[eComponentType].TextureStackSize;

        m_arAspectComponents[eComponentType].TextureStack[uNewIndex].TextureId = textureId;
        m_arAspectComponents[eComponentType].TextureStack[uNewIndex].SamplerId = samplerId;
        m_arAspectComponents[eComponentType].TextureStack[uNewIndex].BlenderId = blenderId;
    }

    void SetTexture(const EQAspectComponentType eComponentType, const u32_q uTextureLayer, const QHashedString textureId)
    {
        QE_ASSERT_ERROR(uTextureLayer < m_arAspectComponents[eComponentType].TextureStackSize, string_q("Texture layer index (") + uTextureLayer + ") out of bounds.");

        m_arAspectComponents[eComponentType].TextureStack[uTextureLayer].TextureId = textureId;
    }

    void SetTextureBlender(const EQAspectComponentType eComponentType, const u32_q uTextureLayer, const QHashedString blenderId)
    {
        QE_ASSERT_ERROR(uTextureLayer < m_arAspectComponents[eComponentType].TextureStackSize, string_q("Texture layer index (") + uTextureLayer + ") out of bounds.");

        m_arAspectComponents[eComponentType].TextureStack[uTextureLayer].BlenderId = blenderId;
    }

    void SetTextureSampler2D(const EQAspectComponentType eComponentType, const u32_q uTextureLayer, const QHashedString samplerId)
    {
        QE_ASSERT_ERROR(uTextureLayer < m_arAspectComponents[eComponentType].TextureStackSize, string_q("Texture layer index (") + uTextureLayer + ") out of bounds.");

        m_arAspectComponents[eComponentType].TextureStack[uTextureLayer].SamplerId = samplerId;
    }

    u32_q GetTextureLayerCount(const EQAspectComponentType eComponentType)
    {
        return m_arAspectComponents[eComponentType].TextureStackSize;
    }

    QHashedString GetTexture(const EQAspectComponentType eComponentType, const u32_q uTextureLayer) const
    {
        QE_ASSERT_ERROR(uTextureLayer < m_arAspectComponents[eComponentType].TextureStackSize, string_q("Texture layer index (") + uTextureLayer + ") out of bounds.");

        return m_arAspectComponents[eComponentType].TextureStack[uTextureLayer].TextureId;
    }

    QHashedString GetMaterial() const
    {
        return m_strMaterial;
    }

    void SetMaterial(const QHashedString &strMaterialId)
    {
        m_strMaterial = strMaterialId;
    }

    QHashedString GetTextureSampler2D(const EQAspectComponentType eComponentType, const u32_q uTextureLayer) const
    {
        QE_ASSERT_ERROR(uTextureLayer < m_arAspectComponents[eComponentType].TextureStackSize, string_q("Texture layer index (") + uTextureLayer + ") out of bounds.");

        return m_arAspectComponents[eComponentType].TextureStack[uTextureLayer].SamplerId;
    }

    QHashedString GetTextureBlender(const EQAspectComponentType eComponentType, const u32_q uTextureLayer) const
    {
        QE_ASSERT_ERROR(uTextureLayer < m_arAspectComponents[eComponentType].TextureStackSize, string_q("Texture layer index (") + uTextureLayer + ") out of bounds.");

        return m_arAspectComponents[eComponentType].TextureStack[uTextureLayer].BlenderId;
    }

    QHashedString GetVertexShader() const
    {
        return m_strVertexShader;
    }

    QHashedString GetFragmentShader() const
    {
        return m_strFragmentShader;
    }

    unsigned int GetAspectComponentCount() const
    {
        return QAspect::MAX_COMPONENTS;
    }

    void SetWireframeMode(const bool bEnabled)
    {
        m_bWireframeEnabled = bEnabled;
    }

    bool GetWireframeMode() const
    {
        return m_bWireframeEnabled;
    }

    void SetFaceCulling(const bool bEnabled)
    {
        m_bFaceCullingEnabled = bEnabled;
    }

    bool GetFaceCulling() const
    {
        return m_bFaceCullingEnabled;
    }

    void SetFacetedModeStatus(const bool bEnabled)
    {
        m_bFaceted = bEnabled;
    }

    bool GetFacetedModeStatus() const
    {
        return m_bFaceted;
    }

    EQAlphaBlendingMode GetAlphaBlendingMode() const
    {
        return m_eAplhaBlendingMode;
    }

    void SetAlphaBlendingMode(const EQAlphaBlendingMode eMode)
    {
        m_eAplhaBlendingMode = eMode;
    }

    float_q GetAlphaBlendingOpacity() const
    {
        return m_fOpacity;
    }

    void SetAlphaBlendingOpacity(const float_q fOpacity)
    {
        m_fOpacity = fOpacity;
    }

    void EnableAspectComponent(const EQAspectComponentType eComponentType, const bool bEnable)
    {
        m_arAspectComponents[eComponentType].Enabled = bEnable;
    }

protected:

    QAspectComponent m_arAspectComponents[QAspect::MAX_COMPONENTS];
    QHashedString m_strMaterial;
    QHashedString m_strVertexShader;
    QHashedString m_strFragmentShader;
    EQAlphaBlendingMode m_eAplhaBlendingMode;
    float_q m_fOpacity;
    bool m_bWireframeEnabled;
    bool m_bFaceCullingEnabled;
    bool m_bFaceted;
};


#endif // __QASPECT__