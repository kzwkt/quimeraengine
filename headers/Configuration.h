// [TERMS&CONDITIONS]

#ifndef __QUIMERAENGINE_CONFIGURATION__
#define __QUIMERAENGINE_CONFIGURATION__

#include "ExternalDefinitions.h"

#ifdef QE_COMPILER_MSVC
    #include <xmmintrin.h> // Includes __m128 definition.
#endif


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Core
{
namespace Configuration
{

// --------------------------------------------------------------------------------------------------------
// Precission: This block defines the engine's operations precission, this means, how accurate the 
// mathematical operations are. Take on account that more precission decreases performance.
// How to use it: Write a precission definition value as the default precission definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_PRECISSION_SIMPLE     0x0 // Simple precission: A 32 bits size floating point type.
#define QE_CONFIG_PRECISSION_DOUBLE     0x1 // Double precission: A large size (more than 32 bits) floating point type.
#define QE_CONFIG_PRECISSION_MAXIMUM    0x2 // Maximum precission: A extremely large size (more than 32 bits) floating point type.

#define QE_CONFIG_PRECISSION_DEFAULT QE_CONFIG_PRECISSION_SIMPLE // [Configurable]

// --------------------------------------------------------------------------------------------------------
// Float type: Defines which floating point type will be used by the whole engine, according to the
// configured precission.
// --------------------------------------------------------------------------------------------------------
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    typedef float float_q;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    typedef double float_q;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM
    typedef long double float_q;
#else
    typedef float float_q;
#endif

// --------------------------------------------------------------------------------------------------------
// Tolerance: Defines how much different can be two floating point values to be considered equals, 
// according to the configured precission.
// --------------------------------------------------------------------------------------------------------
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    const float EPSILON_Q = 1e-6f;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    const double EPSILON_Q = 1e-12;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM
    const long double EPSILON_Q = 1e-18;
#else
    const float EPSILON_Q = 1e-6f;
#endif

// --------------------------------------------------------------------------------------------------------
// Pi: Defines how much accurate the mathematical Pi value is.
// --------------------------------------------------------------------------------------------------------
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    const float PI_Q = 3.141592654f;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    const double PI_Q = 3.14159265358979323846;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM
    const long double PI_Q = 3.141592653589793238462643383279;
#else
    const float PI_Q = 3.141592654f;
#endif

// --------------------------------------------------------------------------------------------------------
// 1/Pi: Defines how much accurate the mathematical Pi value is to calculate its inverse.
// --------------------------------------------------------------------------------------------------------
const float INVERSE_PI_Q = 1.0f / PI_Q; // [TODO] Thund: To take the constant value.

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
#endif

// --------------------------------------------------------------------------------------------------------
// Null Pointer: Defines the value that identifies a null pointer, depending on the compiler.
// --------------------------------------------------------------------------------------------------------
#ifdef QE_COMPILER_MSVC
    #if QE_COMPILER_MSVC >= 10
        #define null_q nullptr // Microsoft Visual C++ 2010 definition for null pointers
    #else
        #define null_q 0
    #endif
#endif

}//namespace Configuration
}//namespace Core
}//namespace QuimeraEngine
}//namespace Kinesis

#endif // __QUIMERAENGINE_CONFIGURATION__