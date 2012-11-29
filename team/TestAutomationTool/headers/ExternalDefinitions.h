// [TERMS&CONDITIONS]

#ifndef __EXTERNALDEFINITIONS__
#define __EXTERNALDEFINITIONS__

#include <wx/string.h>

//------------------------
// OS Detection
//------------------------

#ifdef _WIN32
    #define TAT_OS_WINDOWS 32    // Windows 32 bits
#elif defined(_WIN64)
    #define TAT_OS_WINDOWS 64    // Windows 64 bits
#elif defined(__i386) && defined(__linux__)
    #define TAT_OS_LINUX 32      // Linux 32 bits
#elif defined(LINUX64) && defined(__linux__)
    #define TAT_OS_LINUX 64      // Linux 64 bits
#else
    #error Unknown operative system.
// [TODO] Thund: Complete the list, including: Linux 32 bits, Linux 64 bits and MacOS
#endif

//-------------------------
// New line characters
//-------------------------

#ifdef TAT_OS_WINDOWS
    const wxString TAT_NEWLINE_TOKEN = wxT("\r\n");
#elif defined(TAT_OS_LINUX)
    const wxString TAT_NEWLINE_TOKEN = wxT("\n");
#else
    const wxString TAT_NEWLINE_TOKEN = wxT("\r");
#endif

#endif // __EXTERNALDEFINITIONS__