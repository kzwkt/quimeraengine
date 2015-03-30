
#ifndef __QBUFFER__
#define __QBUFFER__

#include <GL/glew.h>
#include "QuimeraEngineIncludesAndUsings.h"

class QBuffer
{
public:

    enum EQBufferType
    {
        E_VertexArray,
        E_IndexArray,
        E_Texture,
        E_Constant
    };

    enum EQBufferMappingMode
    {
        E_Read,
        E_Write,
        E_ReadAndWrite,
        E_DiscardAndWrite,
        E_DiscardRangeAndWrite
    };

    struct OpenGLMapParameters
    {
        GLenum MappingMode;
        GLbitfield AccessMode;
    };

    enum EQModificationFrequency
    {
        E_Never,
        E_Rarely,
        E_Often,
        E_Continuously
    };

    enum EQExpectedOperations
    {
        E_GPUReadsAndWrites,
        E_GPUReadsCPUWrites,
        E_CPUReadsGPUWrites
    };

    // Base class constructor (const EQBufferType eType, const pointer_uint_q uSize, const EQModificationFrequency eModificationFrequency, const EQExpectedOperations eExpectedOperations)

    QBuffer(const GLuint uId, const EQBufferType eType, const pointer_uint_q uSize, const EQModificationFrequency eModificationFrequency, const EQExpectedOperations eExpectedOperations) :
                                                                                      m_uId(uId),
                                                                                      m_eTarget(QBuffer::GetEquivalentBufferTypeOpenGLValue(eType)),
                                                                                      m_eUsage(QBuffer::GetEquivalentBufferUsageOpenGLValue(eModificationFrequency, eExpectedOperations)),
                                                                                      m_uSize(uSize)
    {
    }

    void* MapRange(const EQBufferMappingMode eMappingMode, const pointer_uint_q uRangeStart, const pointer_uint_q uRangeSize, const void* pImplementationParameters = null_q)
    {
        GLenum eFinalMappingMode;
        GLbitfield uFinalAccessMode;

        glBindBuffer(m_eTarget, m_uId);

        if (pImplementationParameters)
        {
            // This could be a way to let users customize things depending on implementation
            const OpenGLMapParameters* pParams = rcast_q(pImplementationParameters, const OpenGLMapParameters*);
            eFinalMappingMode = pParams->MappingMode;
            uFinalAccessMode = pParams->AccessMode;
        }
        else
        {
            eFinalMappingMode = QBuffer::GetEquivalentBufferMappingModeOpenGLValue(eMappingMode);
            uFinalAccessMode = QBuffer::GetEquivalentBufferMapAccessOpenGLValue(eMappingMode);
        }

        return glMapBufferRange(m_eTarget, uRangeStart, uRangeSize, eFinalMappingMode | uFinalAccessMode); // [TODO]: Put both bitfields together in the enumeration
    }

    bool Unmap()
    {
        return glUnmapBuffer(m_eTarget) == GL_TRUE;
    }

    GLuint GetOpenGLId() const
    {
        return m_uId;
    }

    GLenum GetOpenGLTarget() const
    {
        return m_eTarget;
    }

    GLenum GetOpenGLUsage() const
    {
        return m_eUsage;
    }

    pointer_uint_q GetSize() const
    {
        return m_uSize;
    }


protected:

    static GLenum GetEquivalentBufferUsageOpenGLValue(const EQModificationFrequency eModificationFrequency, const EQExpectedOperations eExpectedOperations)
    {
        static const GLenum EQUIVALENCIES[4][3] = { GL_STATIC_COPY,     // E_Never, E_GPUReadsAndWrites
                                                    GL_STATIC_DRAW,     // E_Never, E_GPUReadsCPUWrites
                                                    GL_STREAM_READ,     // E_Never, E_CPUReadsGPUWrites
                                                    GL_STATIC_COPY,     // E_Rarely, E_GPUReadsAndWrites
                                                    GL_STATIC_DRAW,     // E_Rarely, E_GPUReadsCPUWrites
                                                    GL_STATIC_READ,     // E_Rarely, E_CPUReadsGPUWrites
                                                    GL_DYNAMIC_COPY,    // E_Often, E_GPUReadsAndWrites
                                                    GL_DYNAMIC_DRAW,    // E_Often, E_GPUReadsCPUWrites
                                                    GL_DYNAMIC_READ,    // E_Often, E_CPUReadsGPUWrites
                                                    GL_STREAM_COPY,     // E_Continuously, E_GPUReadsAndWrites
                                                    GL_STREAM_DRAW,     // E_Continuously, E_GPUReadsCPUWrites
                                                    GL_STREAM_READ,     // E_Continuously, E_CPUReadsGPUWrites
                                                  };

        return EQUIVALENCIES[eModificationFrequency][eExpectedOperations];
    }

    static GLenum GetEquivalentBufferMappingModeOpenGLValue(const EQBufferMappingMode eMappingMode)
    {
        static const GLenum EQUIVALENCIES[] = { GL_MAP_READ_BIT, 
                                                GL_MAP_WRITE_BIT, 
                                                GL_MAP_READ_BIT | GL_MAP_WRITE_BIT,
                                                GL_MAP_READ_BIT | GL_MAP_WRITE_BIT,
                                                GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
                                              };

        return EQUIVALENCIES[eMappingMode];
    }

    static GLenum GetEquivalentBufferMapAccessOpenGLValue(const EQBufferMappingMode eMappingMode)
    {
        static const GLenum EQUIVALENCIES[] = { 0,
                                                0,
                                                0,
                                                GL_MAP_INVALIDATE_BUFFER_BIT,
                                                GL_MAP_INVALIDATE_RANGE_BIT
                                              };

        return EQUIVALENCIES[eMappingMode];
    }

    static GLenum GetEquivalentBufferTypeOpenGLValue(const EQBufferType eType)
    {
        static const GLenum EQUIVALENCIES[] = { GL_ARRAY_BUFFER,
                                                GL_ELEMENT_ARRAY_BUFFER,
                                                GL_TEXTURE_BUFFER,
                                                GL_UNIFORM_BUFFER
                                              };

        return EQUIVALENCIES[eType];
    }

    GLuint m_uId;
    GLenum m_eTarget;
    GLenum m_eUsage;
    pointer_uint_q m_uSize;
};


#endif // __QBUFFER__