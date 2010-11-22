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
// Version: Defines the Quimera Engine's current version.
// How to use it: Version format is Major version + Minor version + Revision ("##.####.####").
// --------------------------------------------------------------------------------------------------------
const char QE_VERSION[13] = "0.0.0";
const unsigned int QE_VERSION_MAJOR = 0;
const unsigned int QE_VERSION_MINOR = 0;
const unsigned int QE_VERSION_REVISION = 0;

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
    const float PI_Q = 4.0f * atan(1.0f);
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    const double PI_Q = 4.0 * atan(1.0);
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM
    const long double PI_Q = 4.0 * atan(1.0);
#else
    const float PI_Q = 4.0f * atan(1.0f);
#endif

// --------------------------------------------------------------------------------------------------------
// 1/Pi: Defines how much accurate the mathematical Pi value is to calculate its inverse.
// --------------------------------------------------------------------------------------------------------
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    const float INVERSE_PI_Q = 1.0f / PI_Q;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    const double INVERSE_PI_Q = 1.0 / PI_Q;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM
    const long double INVERSE_PI_Q = 1.0 / PI_Q;
#else
    const float INVERSE_PI_Q = 1.0f / PI_Q;
#endif
    
// --------------------------------------------------------------------------------------------------------
// Radians per degree: Defines how many radians are equivalent to 1 degree, and how much accurate is that value.
// --------------------------------------------------------------------------------------------------------
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    const float RADIANS_PER_DEGREE_Q = PI_Q / 180.0f;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    const double RADIANS_PER_DEGREE_Q = PI_Q / 180.0;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM
    const long double RADIANS_PER_DEGREE_Q = PI_Q / 180.0;
#else
    const float RADIANS_PER_DEGREE_Q = PI_Q / 180.0f;
#endif
        
// --------------------------------------------------------------------------------------------------------
// Degrees per unit, in radians: Defines how many degrees are equivalent to the unit (1) in radians, and how much 
// accurate is that value.
// --------------------------------------------------------------------------------------------------------
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    const float DEGREES_PER_UNIT_INRADIANS_Q = 180.0f / PI_Q;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    const double DEGREES_PER_UNIT_INRADIANS_Q = 180.0 / PI_Q;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM
    const long double DEGREES_PER_UNIT_INRADIANS_Q = 180.0 / PI_Q;
#else
    const float DEGREES_PER_UNIT_INRADIANS_Q = 180.0f / PI_Q;
#endif

// --------------------------------------------------------------------------------------------------------
// Angle Notation: Defines whether the entire engine will work using Degrees or Radians.
// How to use it: Write an angle notation definition value as the default angle notation definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_ANGLENOTATION_RADIANS 0x0 // Degrees notation: Angles are represented using degrees, from 0º to 360º.
#define QE_CONFIG_ANGLENOTATION_DEGREES 0x1 // Radians notation: Angles are represented using radians, from 0 to 2*Pi.

#define QE_CONFIG_ANGLENOTATION_DEFAULT QE_CONFIG_ANGLENOTATION_RADIANS // [Configurable]

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
    struct vf32_q
    {
        f32_q x;
        f32_q y;
        f32_q z;
        f32_q w;
    };
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

// --------------------------------------------------------------------------------------------------------
// Dll Export Specifier: Defines which compiler keywords will be used to export symbols when compiling as 
// a DLL. Their values are "empty" when compiling the library as static.
// --------------------------------------------------------------------------------------------------------
#ifdef QE_CONFIG_COMPILER_DLL // QE_CONFIG_COMPILER_DLL is specified as a preprocessor definition [TODO] Thund: Add that definition when configuration is ready
    #ifdef QE_COMPILER_MSVC // [TODO] Thund: There must be one per compatible compiler.
        #define QDllExport __declspec( dllexport )
        #define QDllImport __declspec( dllimport )
    #else
        #define QDllExport
        #define QDllImport
    #endif
#else
    #define QDllExport
    #define QDllImport
#endif

    // [TODO] Thund: Remove these constants when QV4x32Flota class is implemented!!!!!!
    const int QE_X_POSITION_IN_4x32FLOAT_PACK = 1;
    const int QE_Y_POSITION_IN_4x32FLOAT_PACK = 2;
    const int QE_Z_POSITION_IN_4x32FLOAT_PACK = 3;
    const int QE_W_POSITION_IN_4x32FLOAT_PACK = 4;

}//namespace Configuration
}//namespace Core
}//namespace QuimeraEngine
}//namespace Kinesis

#endif // __QUIMERAENGINE_CONFIGURATION__