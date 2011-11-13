// [TERMS&CONDITIONS]

#ifndef __INTERNALDEFINITIONS__
#define __INTERNALDEFINITIONS__

#include "ExternalDefinitions.h"

// --------------------------------------------------------------------------------------------------------
// Version: Defines the Quimera Engine's current version.
// How to use it: Version format is Major version + Minor version + Revision ("##.####.####").
// --------------------------------------------------------------------------------------------------------
const char QE_VERSION[13] = "0.0.0";
const unsigned int QE_VERSION_MAJOR = 0;
const unsigned int QE_VERSION_MINOR = 0;
const unsigned int QE_VERSION_REVISION = 0;


// --------------------------------------------------------------------------------------------------------
// Null Pointer: Defines the value that identifies a null pointer, depending on the compiler.
// --------------------------------------------------------------------------------------------------------
#ifdef QE_COMPILER_MSVC
    #if QE_COMPILER_MSVC >= 10
        #define null_q nullptr // Microsoft Visual C++ 2010 definition for null pointers
    #else
        #define null_q 0
    #endif
#elif QE_COMPILER_GCC
    #define null_q 0
#endif


// --------------------------------------------------------------------------------------------------------
// Dll Export Specifier: Defines which compiler keywords will be used to export symbols when compiling as
// a DLL. Their values are "empty" when compiling the library as static.
// --------------------------------------------------------------------------------------------------------
#ifdef QE_CONFIG_COMPILER_SHAREDLIB // QE_CONFIG_COMPILER_SHAREDLIB is specified as a preprocessor definition [TODO] Thund: Add that definition to preprocessor when configuration is ready
    #ifdef QE_OS_WINDOWS
        #ifdef QE_COMPILER_MSVC
            #define QDllExport __declspec( dllexport )
        #elif QE_COMPILER_GCC
            #define QDllExport __attribute__(( dllexport ))
        #endif
    #elif defined(QE_OS_LINUX)
        #if QE_COMPILER_GCC
            #define QDllExport __attribute__((visibility("default")))( dllexport )
        #endif
    #endif
#elif defined(QE_CONFIG_COMPILER_IMPORT) // QE_CONFIG_COMPILER_IMPORT is specified as a preprocessor definition when compiling the client system
    #ifdef QE_OS_WINDOWS
        #ifdef QE_COMPILER_MSVC
            #define QDllExport __declspec( dllimport )
        #elif QE_COMPILER_GCC
            #define QDllExport __attribute__(( dllimport ))
        #endif
    #elif defined(QE_OS_LINUX)
        #if QE_COMPILER_GCC
            #define QDllExport
        #endif
    #endif
#else // Static library
    #ifdef QE_OS_WINDOWS
        #define QDllExport
    #elif defined(QE_OS_LINUX)
        #define QDllExport
    #endif
#endif

#endif // __INTERNALDEFINITIONS__
