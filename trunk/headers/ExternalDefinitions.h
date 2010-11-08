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
#elif defined LINUX // [TODO] Thund: Complete the list, including: Linux 32 bits, Linux 64 bits and MacOS
    #define QE_OS_LINUX         // Linux
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

#endif // __EXTERNALDEFINITIONS__