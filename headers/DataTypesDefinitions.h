// [TERMS&CONDITIONS]

#ifndef __DATATYPESDEFINITIONS__
#define __DATATYPESDEFINITIONS__

#include "Configuration.h"

#ifdef QE_COMPILER_MSVC
    #include <xmmintrin.h> // Includes __m128 definition.
#endif

using namespace Kinesis::QuimeraEngine::Core::Configuration;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace DataTypes
{
    
// --------------------------------------------------------------------------------------------------------
// Basic types: Defines all basic types used by some engine components, whose size is assured to be 
// always the same.
// --------------------------------------------------------------------------------------------------------
// [TODO] Thund: Do these types' size depends on the compiler?
typedef unsigned char       u8_q;   // Unsigned 8-bits integer
typedef char                i8_q;   // Signed 8-bits integer
typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
typedef short int           i16_q;  // Signed 16-bits integer
typedef unsigned int        u32_q;  // Unsigned 32-bits integer
typedef int                 i32_q;  // Signed 32-bits integer
typedef float               f32_q;  // 32-bits floating point number

#ifdef QE_COMPILER_MSVC
    typedef __m128          vf32_q; // 4 x 32-bits packed floating point numbers
#else
    class vf32_q
    {
        f32_q x;
        f32_q y;
        f32_q z;
        f32_q w;
    };
#endif
        

// --------------------------------------------------------------------------------------------------------
// 4-components vector mapping to 4x32 floats pack: Defines all basic types used by some engine components, 
// whose size is assured to be always the same.
// These definitions are used into many math classes that receives a 4x32-bits floating points pack.
// --------------------------------------------------------------------------------------------------------
#define QE_VF32_FIRST_COMPONENT  this->x
#define QE_VF32_SECOND_COMPONENT this->y
#define QE_VF32_THIRD_COMPONENT  this->z
#define QE_VF32_FOURTH_COMPONENT this->w


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __DATATYPESDEFINITIONS__
