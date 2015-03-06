
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

    static const unsigned int MAX_TEXTURES = 16;

    QAspect() : m_uTexturesCount(0)
    {
        for (int i = 0; i < MAX_TEXTURES; ++i)
            m_samplerNames[i] = null_q;
    }

    void AddTexture(const QHashedString &strTextureId, const QHashedString &strMaterialId, const char* szShaderTextureSamplerName)
    {
        QE_ASSERT_ERROR(m_uTexturesCount < MAX_TEXTURES, "The texture cannot be added to the aspect, it is full.");

        m_materials[m_uTexturesCount] = strMaterialId;
        m_textures[m_uTexturesCount] = strTextureId;
        m_samplerNames[m_uTexturesCount] = szShaderTextureSamplerName;
        ++m_uTexturesCount;
    }

    void SetVertexShader(const QHashedString &strId)
    {
        m_strVertexShader = strId;
    }

    void SetFragmentShader(const QHashedString &strId)
    {
        m_strFragmentShader = strId;
    }

    QHashedString GetTextureId(const unsigned int uIndex) const
    {
        QE_ASSERT_ERROR(uIndex < m_uTexturesCount, "Index out of bounds.");

        return m_textures[uIndex];
    }

    QHashedString GetMaterialId(const unsigned int uIndex) const
    {
        QE_ASSERT_ERROR(uIndex < m_uTexturesCount, "Index out of bounds.");

        return m_materials[uIndex];
    }

    const char* GetShaderSamplerName(const unsigned int uIndex)
    {
        QE_ASSERT_ERROR(uIndex < m_uTexturesCount, "Index out of bounds.");

        return m_samplerNames[uIndex];
    }

    QHashedString GetVertexShader() const
    {
        return m_strVertexShader;
    }

    QHashedString GetFragmentShader() const
    {
        return m_strFragmentShader;
    }

    unsigned int GetTextureCount() const
    {
        return m_uTexturesCount;
    }


protected:

    QHashedString m_materials[MAX_TEXTURES];
    QHashedString m_textures[MAX_TEXTURES];
    const char* m_samplerNames[MAX_TEXTURES];
    QHashedString m_strVertexShader;
    QHashedString m_strFragmentShader;
    unsigned char m_uTexturesCount;
    // Blender

};


#endif // __QASPECT__