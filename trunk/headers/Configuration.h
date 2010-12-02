// [TERMS&CONDITIONS]

#ifndef __QUIMERAENGINE_CONFIGURATION__
#define __QUIMERAENGINE_CONFIGURATION__

#include "ExternalDefinitions.h"

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
// Angle Notation: Defines whether the entire engine will work using Degrees or Radians.
// How to use it: Write an angle notation definition value as the default angle notation definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_ANGLENOTATION_RADIANS 0x0 // Radians notation: Angles are represented using radians, from 0 to 2*Pi.
#define QE_CONFIG_ANGLENOTATION_DEGREES 0x1 // Degrees notation: Angles are represented using degrees, from 0º to 360º.

#define QE_CONFIG_ANGLENOTATION_DEFAULT QE_CONFIG_ANGLENOTATION_RADIANS // [Configurable]


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
// String type: [DOC].
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_STRINGCHARSET_ANSI 0x0
#define QE_CONFIG_STRINGCHARSET_UTF8 0x1


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


// --------------------------------------------------------------------------------------------------------
// Machine endianess: Defines the machine endianess, this means, which order does the hardware follow to 
// store and read bytes. This configuration value must be checked every time the project is compiled on
// a different hardware architecture. A way to know the machine endianess is as follows:
//
// int i = 1;           // 0x0001 => 0x01000000 || 0x00000001 ?
// char c = (char*)&i;  // 0x00 || 0x01 ?
//
// if(c == 1)           // Is c the most or the less relevant byte in i?
//   Little-Endian
// else
//   Big-Endian
//
// How to use it: Write an endianess definition value as the default endianess definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_MACHINEENDIANESS_LITTLEENDIAN 0x0 // Little-endian
#define QE_CONFIG_MACHINEENDIANESS_BIGENDIAN    0x1 // Big-endian
#define QE_CONFIG_MACHINEENDIANESS_DEFAULT QE_CONFIG_MACHINEENDIANESS_LITTLEENDIAN // [Configurable]


}//namespace Configuration
}//namespace Core
}//namespace QuimeraEngine
}//namespace Kinesis

#endif // __QUIMERAENGINE_CONFIGURATION__