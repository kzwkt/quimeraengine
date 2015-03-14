//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __COMMONCONFIGDEFINITIONS__
#define __COMMONCONFIGDEFINITIONS__

#include "ExternalDefinitions.h"

/*
[TODO] Thund: Identificar y añadir al bloque de abajo
// Linux 32 bits OS, Debug, Shared runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
// Linux 32 bits OS, Debug, Shared runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
// Linux 32 bits OS, Release, Shared runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
// Linux 32 bits OS, Release, Shared runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
// Linux 32 bits OS, Debug, Static runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
// Linux 32 bits OS, Debug, Static runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
// Linux 32 bits OS, Release, Static runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
// Linux 32 bits OS, Release, Static runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT

// Macintosh 32 bits OS, Debug, Shared runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
// Macintosh 32 bits OS, Debug, Shared runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
// Macintosh 32 bits OS, Release, Shared runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
// Macintosh 32 bits OS, Release, Shared runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
// Macintosh 32 bits OS, Debug, Static runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
// Macintosh 32 bits OS, Debug, Static runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
// Macintosh 32 bits OS, Release, Static runtime linking, Static library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
// Macintosh 32 bits OS, Release, Static runtime linking, Dynamic library output
#define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT
*/

// CURRENT CONFIGURATION INDENTIFICATION
// ---------------------------------------

#if defined(TAT_OS_WINDOWS)

    #ifdef TAT_COMPILER_MSVC // Microsoft Visual C++
        #if TAT_COMPILER_MSVC >= 10 // Microsoft Visual C++ 2010
            #if defined(TAT_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Debug, Shared runtime linking, Static library output
                #define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(TAT_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(TAT_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Release, Shared runtime linking, Static library output
                #define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(TAT_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Release, Shared runtime linking, Dynamic library output
                #define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(TAT_DEBUG) && defined(_MT) && !defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Debug, Static runtime linking, Static library output
                #define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(TAT_DEBUG) && defined(_MT) && defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Debug, Static runtime linking, Dynamic library output
                #define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(TAT_DEBUG) && defined(_MT) && !defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Release, Static runtime linking, Static library output
                #define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(TAT_DEBUG) && defined(_MT) && defined(TAT_CONFIG_COMPILER_IMPORT)
                // Windows 32 bits OS, Release, Static runtime linking, Dynamic library output
                #define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #else// Microsoft Visual C++ < 2010
        #endif
    #elif defined(TAT_COMPILER_GCC) // GCC (MinGW)
        #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
        #if defined(TAT_DEBUG) && defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Debug, Shared runtime linking, Static library output
            #define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
        #elif defined(TAT_DEBUG) && defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Debug, Shared runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
        #elif !defined(TAT_DEBUG) && defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Release, Shared runtime linking, Static library output
            #define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
        #elif !defined(TAT_DEBUG) && defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Release, Shared runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
        #elif defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Debug, Static runtime linking, Static library output
            #define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
        #elif defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Debug, Static runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
        #elif !defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Release, Static runtime linking, Static library output
            #define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
        #elif !defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Windows 32 bits OS, Release, Static runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT
        #else
            #error "Unknown configuration"
        #endif
    #endif
// [TODO] Thund: Completar con resto de compiladores.
#elif defined(TAT_OS_LINUX)
    #if defined(TAT_COMPILER_GCC) // GCC
        #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
        #if defined(TAT_DEBUG) && defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Debug, Shared runtime linking, Static library output
            #define TAT_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_STATICOUT
        #elif defined(TAT_DEBUG) && defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Debug, Shared runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
        #elif !defined(TAT_DEBUG) && defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Release, Shared runtime linking, Static library output
            #define TAT_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_STATICOUT
        #elif !defined(TAT_DEBUG) && defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Release, Shared runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
        #elif defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Debug, Static runtime linking, Static library output
            #define TAT_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_STATICOUT
        #elif defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Debug, Static runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_DYNAMICOUT
        #elif !defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && !defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Release, Static runtime linking, Static library output
            #define TAT_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_STATICOUT
        #elif !defined(TAT_DEBUG) && !defined(UsingSharedRuntime) && defined(TAT_CONFIG_COMPILER_IMPORT)
            // Linux 32 bits OS, Release, Static runtime linking, Dynamic library output
            #define TAT_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_DYNAMICOUT
        #else
            #error "Unknown configuration"
        #endif
    #endif
#else
    #error "Operative system not supported."
#endif


// CONFIGURATION DEFINITIONS
// ----------------------------

#if   defined(TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32DebugSharedrtStatic"
#elif defined(TAT_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32DebugSharedrtDynamic"
#elif defined(TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32ReleaseSharedrtStatic"
#elif defined(TAT_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32ReleaseSharedrtDynamic"
#elif defined(TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32DebugStaticrtStatic"
#elif defined(TAT_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32DebugStaticrtDynamic"
#elif defined(TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32ReleaseStaticrtStatic"
#elif defined(TAT_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Win32ReleaseStaticrtDynamic"

#elif defined(TAT_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32DebugSharedrtStatic"
#elif defined(TAT_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32DebugSharedrtDynamic"
#elif defined(TAT_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32ReleaseSharedrtStatic"
#elif defined(TAT_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32ReleaseSharedrtDynamic"
#elif defined(TAT_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32DebugStaticrtStatic"
#elif defined(TAT_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32DebugStaticrtDynamic"
#elif defined(TAT_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32ReleaseStaticrtStatic"
#elif defined(TAT_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Linux32ReleaseStaticrtDynamic"

#elif defined(TAT_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32DebugSharedrtStatic"
#elif defined(TAT_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32DebugSharedrtDynamic"
#elif defined(TAT_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32ReleaseSharedrtStatic"
#elif defined(TAT_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32ReleaseSharedrtDynamic"
#elif defined(TAT_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32DebugStaticrtStatic"
#elif defined(TAT_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32DebugStaticrtDynamic"
#elif defined(TAT_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_STATICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32ReleaseStaticrtStatic"
#elif defined(TAT_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define TAT_TEST_CONFIG_NAME "Mac32ReleaseStaticrtDynamic"

#endif

#endif // __COMMONCONFIGDEFINITIONS__
