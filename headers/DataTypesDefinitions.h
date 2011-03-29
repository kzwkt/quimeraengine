// [TERMS&CONDITIONS]

#ifndef __DATATYPESDEFINITIONS__
#define __DATATYPESDEFINITIONS__

#include "Configuration.h"
#include <string>
// Below, tchar.h is included depending on the configuration values.

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

#if defined(QE_OS_WINDOWS) && (QE_OS_WINDOWS == 32)
    #ifdef QE_COMPILER_MSVC
        typedef unsigned char       u8_q;   // Unsigned 8-bits integer
        typedef char                i8_q;   // Signed 8-bits integer
        typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
        typedef short int           i16_q;  // Signed 16-bits integer
        typedef unsigned int        u32_q;  // Unsigned 32-bits integer
        typedef int                 i32_q;  // Signed 32-bits integer
        typedef long long           i64_q;  // Signed 64-bits integer
        typedef float               f32_q;  // 32-bits floating point number
        typedef double              f64_q;  // 64-bits floating point number
        typedef __m128              vf32_q; // 4 x 32-bits packed floating point numbers
        // Note: There is no integer or float whose size is greater than 64 bits on Windows 32 bits
    #elif QE_COMPILER_GCC
        typedef unsigned char       u8_q;   // Unsigned 8-bits integer
        typedef char                i8_q;   // Signed 8-bits integer
        typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
        typedef short int           i16_q;  // Signed 16-bits integer
        typedef unsigned int        u32_q;  // Unsigned 32-bits integer
        typedef int                 i32_q;  // Signed 32-bits integer
        typedef long long           i64_q;  // Signed 64-bits integer
        typedef float               f32_q;  // 32-bits floating point number
        typedef double              f64_q;  // 64-bits floating point number
        struct vf32_q
        {
            f32_q v[4];
        };
        // Note: There is no integer or float whose size is greater than 64 bits on Windows 32 bits
    #else
        // [TODO] Thund: Test the system in another compiler and write the basic types for that compiler
    #endif

#elif defined(QE_OS_LINUX) && (QE_OS_LINUX == 32)
    #if QE_COMPILER_GCC
        typedef unsigned char       u8_q;   // Unsigned 8-bits integer
        typedef char                i8_q;   // Signed 8-bits integer
        typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
        typedef short int           i16_q;  // Signed 16-bits integer
        typedef unsigned int        u32_q;  // Unsigned 32-bits integer
        typedef int                 i32_q;  // Signed 32-bits integer
        typedef long long           i64_q;  // Signed 64-bits integer
        typedef float               f32_q;  // 32-bits floating point number
        typedef double              f64_q;  // 64-bits floating point number
        struct vf32_q // [TODO] GCC has a 128bits type too, I think
        {
            f32_q v[4];
        };
    #else
        // [TODO] Thund: Test the system in another compiler and write the basic types for that compiler
    #endif
    // [TODO] Thund: Test the system in another platform and write the basic types for that machine
    // Win64, Linux 32, Mac OS 32

#endif


// --------------------------------------------------------------------------------------------------------
// Float type: Defines which floating point type will be used by the whole engine, according to the
// configured precission.
// --------------------------------------------------------------------------------------------------------

#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    typedef f32_q float_q;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    typedef f64_q float_q;
#else
    typedef f32_q float_q;
#endif

// --------------------------------------------------------------------------------------------------------
// Float type size: Defines the floating point type size (in bytes), depending on the configured precission.
// The size depens on the operative system / compiler too.
// --------------------------------------------------------------------------------------------------------
#if defined(QE_OS_WINDOWS) && (QE_OS_WINDOWS == 32)
    #ifdef QE_COMPILER_MSVC
        #if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
            #define QE_FLOAT_SIZE 4
        #elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
            #define QE_FLOAT_SIZE 8
        #else
            #define QE_FLOAT_SIZE 4
        #endif
    #elif QE_COMPILER_GCC
         #if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
            #define QE_FLOAT_SIZE 4
        #elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
            #define QE_FLOAT_SIZE 8
        #else
            #define QE_FLOAT_SIZE 4
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#elif defined(QE_OS_LINUX) && (QE_OS_LINUX == 32)
    #if QE_COMPILER_GCC
         #if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
            #define QE_FLOAT_SIZE 4
        #elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
            #define QE_FLOAT_SIZE 8
        #else
            #define QE_FLOAT_SIZE 4
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#else
    // [TODO] Thund: Test the system in another platform and write the type sizes in that machine
    // Win64, Linux 32, Mac OS 32
#endif

// --------------------------------------------------------------------------------------------------------
// Integer/Float type sizes equivalence: Defines the integer type whose size equals to the selected floating
// point type size.
// --------------------------------------------------------------------------------------------------------
#if defined(QE_OS_WINDOWS) && (QE_OS_WINDOWS == 32)
    #ifdef QE_COMPILER_MSVC
        #if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
            typedef i32_q int_for_float_q;
        #elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
            typedef i64_q int_for_float_q;
        #else
            typedef i32_q int_for_float_q;
        #endif
    #elif QE_COMPILER_GCC
        #if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
            typedef i32_q int_for_float_q;
        #elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
            typedef i64_q int_for_float_q;
        #else
            typedef i32_q int_for_float_q;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#elif defined(QE_OS_LINUX) && (QE_OS_LINUX == 32)
    #if QE_COMPILER_GCC
        #if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
            typedef i32_q int_for_float_q;
        #elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
            typedef i64_q int_for_float_q;
        #else
            typedef i32_q int_for_float_q;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#else
    // [TODO] Thund: Test the system in another platform and write the type sizes in that machine
    // Win64, Linux64, Mac OS 32
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


// --------------------------------------------------------------------------------------------------------
// Char type: Defines the char width used throughout the engine, depending on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_SBCS
    typedef char char_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    typedef wchar_t char_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_MBCS && defined(QE_OS_WINDOWS)
    #include <tchar.h>
    typedef TCHAR char_q;
#else
    typedef char char_q;
#endif


// --------------------------------------------------------------------------------------------------------
// String type: Defines the string class used throughout the engine, depending on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_SBCS
    typedef std::string string_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    typedef std::wstring string_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_MBCS && defined(QE_OS_WINDOWS)
    typedef std::wstring string_q;
#else
    typedef std::string string_q;
#endif


// --------------------------------------------------------------------------------------------------------
// Literals prefix: Specifies if character string literals must be prefixed with the wide-char token, depending
// on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_SBCS
    #define QE_L
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    #define QE_L(str) L##str
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_MBCS && defined(QE_OS_WINDOWS)
    #define QE_L(str) L##str
#else
    #define QE_L
#endif


// --------------------------------------------------------------------------------------------------------
// Enumeration's limits: Concretes the maximum and minimum values an enumerated type can store.
// --------------------------------------------------------------------------------------------------------
#if (defined(QE_OS_WINDOWS) && QE_OS_WINDOWS == 32) || (defined(QE_OS_LINUX) && QE_OS_LINUX == 32)
    #define QE_ENUMERATION_MIN_VALUE 0x0
    #define QE_ENUMERATION_MAX_VALUE 0xFFFFFFFF
#else if (defined(QE_OS_WINDOWS) && QE_OS_WINDOWS == 64) || (defined(QE_OS_LINUX) && QE_OS_LINUX == 64)
    #define QE_ENUMERATION_MIN_VALUE 0x0
    #define QE_ENUMERATION_MAX_VALUE 0xFFFFFFFFFFFFFFFF
    // [TODO] Thund: Tener en cuenta también a MacOS
#endif


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __DATATYPESDEFINITIONS__
