
#include "QBuffer.h"

#include "QuimeraEngine.h"


void* QBuffer::MapRange(const EQBufferMappingMode eMappingMode, const pointer_uint_q uRangeStart, const pointer_uint_q uRangeSize, const void* pImplementationParameters)
{
    GLenum eFinalMappingMode;
    GLbitfield uFinalAccessMode;

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

    void* pContent = glMapNamedBufferRange(m_uId, uRangeStart, uRangeSize, eFinalMappingMode | uFinalAccessMode); // [TODO]: Put both bitfields together in the enumeration

    QE_ASSERT_OPENGL_ERROR("An error occurred when mapping a buffer (glMapNamedBufferRange).");

    return pContent;
}

bool QBuffer::Unmap()
{
    return glUnmapNamedBuffer(m_uId) == GL_TRUE;
}

void QBuffer::CopyRange(const QHashedString strDestinationBuffer, const u32_q uSourceOffset, const u32_q uDestinationOffset, const u32_q uSizeToCopy) const
{
    QE_ASSERT_ERROR(uSourceOffset + uSizeToCopy <= m_uSize, "The region to be read is out of bounds.");

    QBuffer* pDestinationBuffer = QE->Resources->GetBuffer(strDestinationBuffer);

    QE_ASSERT_ERROR(uDestinationOffset + uSizeToCopy <= pDestinationBuffer->GetSize(), "The region to be written is out of bounds.");

    glCopyNamedBufferSubData(m_uId, pDestinationBuffer->GetOpenGLId(), uSourceOffset, uDestinationOffset, uSizeToCopy);
}