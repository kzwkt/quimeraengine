// [TERMS&CONDITIONS]

#ifndef __EXTERNALDEFINITIONS__
#define __EXTERNALDEFINITIONS__

// --------------------------------------------------------------------------------------------------------
// Compilation configuration: Defines if the current compilation configuration is set for debugging or
// releasing.
// --------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
    #define QE_DEBUG    // Debug compilation
#else
    #define QE_RELEASE  // Release compilation
#endif

// --------------------------------------------------------------------------------------------------------
// Operative system: Defines on which ooperative system is running the compiler.
// --------------------------------------------------------------------------------------------------------
#ifdef _WIN32
    #define QE_OS_WINDOWS 32    // Windows 32 bits
#elif defined _WIN64
    #define QE_OS_WINDOWS 64    // Windows 64 bits
#elif defined(__i386) && defined(__linux__)
    #define QE_OS_LINUX 32      // Linux 32 bits
#elif defined(LINUX64) && defined(__linux__)
    #define QE_OS_LINUX 64      // Linux 64 bits
#else
    #error Unknown operative system.
// [TODO] Thund: Complete the list, including: Linux 32 bits, Linux 64 bits and MacOS
#endif

// --------------------------------------------------------------------------------------------------------
// Compiler: Defines which compiler is compiling the code.
// --------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
    #if _MSC_VER >= 1600
        #define QE_COMPILER_MSVC 10 // Microsoft Visual C++ 2010
    #else
        #define QE_COMPILER_MSVC 0  // Microsoft Visual C++ < 2010
    #endif
#elif __GNUC__
    #define QE_COMPILER_GCC __GNUC__ // GCC
#else
    #error Unknown compiler.
#endif

// --------------------------------------------------------------------------------------------------------
// Compiler specifics: Assures that specific compiler macros are defined always.
// --------------------------------------------------------------------------------------------------------
#ifndef __LINE__
    #define __LINE__    // Microsoft Visual C++ macro
#endif
#ifndef __FILE__
    #define __FILE__    // Microsoft Visual C++ macro
#endif
#ifndef __DATE__
    #define __DATE__    // Microsoft Visual C++ macro
#endif
#ifndef __TIME__
    #define __TIME__    // Microsoft Visual C++ macro
#endif

// --------------------------------------------------------------------------------------------------------
// Assertions: Defines assertion statement behavior.
// --------------------------------------------------------------------------------------------------------
#ifndef QE_DISABLE_ASSERTS // This definition must be included as client application's preprocessor definitions to disable assert statements

    #include <boost/assert.hpp>

    #ifdef BOOST_ASSERT
        #define QE_ASSERT(expr) BOOST_ASSERT(expr)
    #endif

#endif

#ifndef QE_ASSERT
    #define QE_ASSERT(expr)
#endif

#endif // __EXTERNALDEFINITIONS__
