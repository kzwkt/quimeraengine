
#ifndef __QPIXELFORMATDESCRIPTOR__
#define __QPIXELFORMATDESCRIPTOR__

#include "QuimeraEngineIncludesAndUsings.h"
#include "EQPixelFormat.h"

class QPixelFormatDescriptor
{
private:

    static const u8_q _PROPERTY_ISNORMALIZED_FLAG = 0x4;
    static const u8_q _PROPERTY_ISCOMPRESSED_FLAG = 0x8;

public:

    enum EQPixelFormatType
    {
        E_UnsignedInt,
        E_SignedInt,
        E_Float
    };

    QPixelFormatDescriptor(const EQPixelFormat::EnumType ePixelFormat)
    {
        memset(this, 0, sizeof(QPixelFormatDescriptor));

        switch (ePixelFormat)
        {
            case EQPixelFormat::E_R8UI_Normalized:
            {
                this->r = 8;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_R16UI_Normalized:
            {
                this->r = 16;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RG8UI_Normalized:
            {
                this->r = 8;
                this->g = 8;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RG16UI_Normalized:
            {
                this->r = 16;
                this->g = 16;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_R3G3B2UI_Normalized:
            {
                this->r = 3;
                this->g = 3;
                this->b = 2;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB4UI_Normalized:
            {
                this->r = 4;
                this->g = 4;
                this->b = 4;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB5UI_Normalized:
            {
                this->r = 8;
                this->g = 5;
                this->b = 5;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB8UI_Normalized:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB10UI_Normalized:
            {
                this->r = 10;
                this->g = 10;
                this->b = 10;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB12UI_Normalized:
            {
                this->r = 12;
                this->g = 12;
                this->b = 12;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB16UI_Normalized:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB565UI_Normalized:
            {
                this->r = 5;
                this->g = 6;
                this->b = 5;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGBA2UI_Normalized:
            {
                this->r = 2;
                this->g = 2;
                this->b = 2;
                this->a = 2;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGBA4UI_Normalized:
            {
                this->r = 4;
                this->g = 4;
                this->b = 4;
                this->a = 4;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB5A1UI_Normalized:
            {
                this->r = 5;
                this->g = 5;
                this->b = 5;
                this->a = 1;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGBA8UI_Normalized:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->a = 8;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB10A2UI_Normalized:
            {
                this->r = 10;
                this->g = 10;
                this->b = 10;
                this->a = 2;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGBA12UI_Normalized:
            {
                this->r = 12;
                this->g = 12;
                this->b = 12;
                this->a = 12;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGBA16UI_Normalized:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->a = 16;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_SRGB8_Compressed:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISCOMPRESSED_FLAG;
                break;
            }
            case EQPixelFormat::E_SRGB8A8_Compressed:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->a = 8;
                this->m_uProperties = E_UnsignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISCOMPRESSED_FLAG;
                break;
            }
            case EQPixelFormat::E_R16F:
            {
                this->r = 16;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_R32F:
            {
                this->r = 32;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_RG16F:
            {
                this->r = 16;
                this->g = 16;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_RG32F:
            {
                this->r = 32;
                this->g = 32;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_RGB16F:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_RGB32F:
            {
                this->r = 32;
                this->g = 32;
                this->b = 32;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_RGBA16F:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->a = 16;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_RGBA32F:
            {
                this->r = 32;
                this->g = 32;
                this->b = 32;
                this->a = 32;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_R11FG11FB10F:
            {
                this->r = 11;
                this->g = 11;
                this->b = 10;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_RGB9F_E5:
            {
                this->r = 9;
                this->g = 9;
                this->b = 9;
                this->a = 5;
                this->m_uProperties = E_Float;
                break;
            }
            case EQPixelFormat::E_R8I:
            {
                this->r = 8;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_R8UI:
            {
                this->r = 8;
                break;
            }
            case EQPixelFormat::E_R16I:
            {
                this->r = 16;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_R16UI:
            {
                this->r = 16;
                break;
            }
            case EQPixelFormat::E_R32I:
            {
                this->r = 32;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_R32UI:
            {
                this->r = 32;
                break;
            }
            case EQPixelFormat::E_RG8I:
            {
                this->r = 8;
                this->g = 8;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RG8UI:
            {
                this->r = 8;
                this->g = 8;
                break;
            }
            case EQPixelFormat::E_RG16I:
            {
                this->r = 16;
                this->g = 16;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RG16UI:
            {
                this->r = 16;
                this->g = 16;
                break;
            }
            case EQPixelFormat::E_RG32I:
            {
                this->r = 32;
                this->g = 32;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RG32UI:
            {
                this->r = 32;
                this->g = 32;
                break;
            }
            case EQPixelFormat::E_RGB8I:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RGB8UI:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                break;
            }
            case EQPixelFormat::E_RGB16I:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RGB16UI:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                break;
            }
            case EQPixelFormat::E_RGB32I:
            {
                this->r = 32;
                this->g = 32;
                this->b = 32;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RGB32UI:
            {
                this->r = 32;
                this->g = 32;
                this->b = 32;
                break;
            }
            case EQPixelFormat::E_RGBA8I:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RGBA8UI:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->a = 8;
                break;
            }
            case EQPixelFormat::E_RGBA16I:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->a = 16;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RGBA16UI:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->a = 16;
                break;
            }
            case EQPixelFormat::E_RGBA32I:
            {
                this->r = 32;
                this->g = 32;
                this->b = 32;
                this->a = 32;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_RGBA32UI:
            {
                this->r = 32;
                this->g = 32;
                this->b = 32;
                this->a = 32;
                break;
            }
            case EQPixelFormat::E_RGB10A2UI:
            {
                this->r = 10;
                this->g = 10;
                this->b = 10;
                this->a = 2;
                break;
            }
            case EQPixelFormat::E_R8I_Normalized:
            {
                this->r = 8;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_R16I_Normalized:
            {
                this->r = 16;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RG8I_Normalized:
            {
                this->r = 8;
                this->g = 8;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RG16I_Normalized:
            {
                this->r = 16;
                this->g = 16;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB8I_Normalized:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGB16I_Normalized:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGBA8I_Normalized:
            {
                this->r = 8;
                this->g = 8;
                this->b = 8;
                this->a = 8;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_RGBA16I_Normalized:
            {
                this->r = 16;
                this->g = 16;
                this->b = 16;
                this->a = 16;
                this->m_uProperties = E_SignedInt;
                this->m_uProperties |= QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG;
                break;
            }
            case EQPixelFormat::E_D16:
            {
                this->d = 16;
                this->m_uProperties = E_UnsignedInt;
                break;
            }
            case EQPixelFormat::E_D24:
            {
                this->d = 24;
                this->m_uProperties = E_UnsignedInt;
                break;
            }
            case EQPixelFormat::E_D32:
            {
                this->d = 32;
                this->m_uProperties = E_UnsignedInt;
                break;
            }
            case EQPixelFormat::E_D32F:
            {
                this->d = 32;
                this->m_uProperties = E_SignedInt;
                break;
            }
            case EQPixelFormat::E_S1:
            {
                this->s = 1;
                this->m_uProperties = E_UnsignedInt;
                break;
            }
            case EQPixelFormat::E_S4:
            {
                this->s = 4;
                break;
            }
            case EQPixelFormat::E_S8:
            {
                this->s = 8;
                this->m_uProperties = E_UnsignedInt;
                break;
            }
            case EQPixelFormat::E_S16:
            {
                this->s = 16;
                this->m_uProperties = E_UnsignedInt;
                break;
            }
            case EQPixelFormat::E_D24S8:
            {
                this->d = 24;
                this->s = 8;
                this->m_uProperties = E_UnsignedInt;
                break;
            }
            case EQPixelFormat::E_D32FS8:
            {
                this->d = 32;
                this->s = 8;
                this->m_uProperties = E_Float;
                break;
            }
            default:
            {
                QE_ASSERT_ERROR(false, "The provided pixel format is not supported.");
                break;
            }
        }
    }

    u32_q GetSize() const
    {
        return r + g + b + a + d + s;
    }

    bool IsNormalized() const
    {
        return (m_uProperties & QPixelFormatDescriptor::_PROPERTY_ISNORMALIZED_FLAG) != 0;
    }

    bool IsCompressed() const
    {
        return (m_uProperties & QPixelFormatDescriptor::_PROPERTY_ISCOMPRESSED_FLAG) != 0;
    }

    EQPixelFormatType GetType() const
    {
        static const u8_q PROPERTY_TYPE_MASK = 0x3;

        return scast_q(m_uProperties & PROPERTY_TYPE_MASK, EQPixelFormatType);
    }

    u8_q r;
    u8_q g;
    u8_q b;
    u8_q a;
    u8_q d; // depth
    u8_q s; // stencil

private:

    u8_q m_uProperties;
};

#endif // __QPIXELFORMATDESCRIPTOR__