//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __COMMONCONFIGDEFINITIONS__
#define __COMMONCONFIGDEFINITIONS__

#include "ExternalDefinitions.h"

// --------------------------------------------------------------------------------------------------------
// Test execution configuration: This flag defines how the tests are executed, whether they are ignored or
// executed in the normal order. The main purpose of including this flag is to let a developer to check the
// results of the tests he/she is developing at the moment, not having to wait for the execution of all
// the other tests of the module previously implemented. So, when creating the tests for class C, this flag
// would nullify all the tests but those that are marked as exceptions. See definitions EXQTEST_-.
// --------------------------------------------------------------------------------------------------------
#define QE_TEST_CONFIG_TEST_EXECUTION_NORMAL 0x0
#define QE_TEST_CONFIG_TEST_EXECUTION_IGNORE 0x1

#define QE_TEST_CONFIG_TEST_EXECUTION QE_TEST_CONFIG_TEST_EXECUTION_NORMAL

// --------------------------------------------------------------------------------------------------------
// Current compilation configuration: This group of definitions identifies the compilation configuration
// that is currently selected for the operative system where it is running on.
// --------------------------------------------------------------------------------------------------------
#if defined(QE_OS_WINDOWS)

    #ifdef QE_COMPILER_MSVC // Microsoft Visual C++
        #if QE_COMPILER_MSVC >= 10 // Microsoft Visual C++ 2010
            #if defined(QE_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Debug, Shared runtime linking, Static library output
                #define QE_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(QE_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define QE_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(QE_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Release, Shared runtime linking, Static library output
                #define QE_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(QE_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Release, Shared runtime linking, Dynamic library output
                #define QE_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(QE_DEBUG) && defined(_MT) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Debug, Static runtime linking, Static library output
                #define QE_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(QE_DEBUG) && defined(_MT) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Debug, Static runtime linking, Dynamic library output
                #define QE_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(QE_DEBUG) && defined(_MT) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Release, Static runtime linking, Static library output
                #define QE_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(QE_DEBUG) && defined(_MT) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
                // Windows 32 bits OS, Release, Static runtime linking, Dynamic library output
                #define QE_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #else// Microsoft Visual C++ < 2010
        #endif
    #elif defined(QE_COMPILER_GCC) // GCC (MinGW)
        #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
        #if defined(QE_DEBUG) && defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Debug, Shared runtime linking, Static library output
            #define QE_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
        #elif defined(QE_DEBUG) && defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Debug, Shared runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
        #elif !defined(QE_DEBUG) && defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Release, Shared runtime linking, Static library output
            #define QE_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
        #elif !defined(QE_DEBUG) && defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Release, Shared runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
        #elif defined(QE_DEBUG) && !defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Debug, Static runtime linking, Static library output
            #define QE_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
        #elif defined(QE_DEBUG) && !defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Debug, Static runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
        #elif !defined(QE_DEBUG) && !defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Release, Static runtime linking, Static library output
            #define QE_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
        #elif !defined(QE_DEBUG) && !defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Windows 32 bits OS, Release, Static runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT
        #else
            #error "Unknown configuration"
        #endif
    #endif
// [TODO] Thund: Completar con resto de compiladores.
#elif defined(QE_OS_LINUX)
    #if defined(QE_COMPILER_GCC) // GCC
        #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
        #if defined(QE_DEBUG) && defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Debug, Shared runtime linking, Static library output
            #define QE_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_STATICOUT
        #elif defined(QE_DEBUG) && defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Debug, Shared runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
        #elif !defined(QE_DEBUG) && defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Release, Shared runtime linking, Static library output
            #define QE_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_STATICOUT
        #elif !defined(QE_DEBUG) && defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Release, Shared runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
        #elif defined(QE_DEBUG) && !defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Debug, Static runtime linking, Static library output
            #define QE_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_STATICOUT
        #elif defined(QE_DEBUG) && !defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Debug, Static runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_DYNAMICOUT
        #elif !defined(QE_DEBUG) && !defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Release, Static runtime linking, Static library output
            #define QE_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_STATICOUT
        #elif !defined(QE_DEBUG) && !defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Linux 32 bits OS, Release, Static runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_DYNAMICOUT
        #else
            #error "Unknown configuration"
        #endif
    #endif
#elif defined(QE_OS_MAC)
    #if defined(QE_COMPILER_GCC) // GCC
        #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
        #if defined(QE_DEBUG) && defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Debug, Shared runtime linking, Static library output
            #define QE_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_STATICOUT
        #elif defined(QE_DEBUG) && defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Debug, Shared runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
        #elif !defined(QE_DEBUG) && defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Release, Shared runtime linking, Static library output
            #define QE_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_STATICOUT
        #elif !defined(QE_DEBUG) && defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Release, Shared runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
        #elif defined(QE_DEBUG) && !defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Debug, Static runtime linking, Static library output
            #define QE_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_STATICOUT
        #elif defined(QE_DEBUG) && !defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Debug, Static runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_DYNAMICOUT
        #elif !defined(QE_DEBUG) && !defined(UsingSharedRuntime) && !defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Release, Static runtime linking, Static library output
            #define QE_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_STATICOUT
        #elif !defined(QE_DEBUG) && !defined(UsingSharedRuntime) && defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
            // Mac OS X 32 bits OS, Release, Static runtime linking, Dynamic library output
            #define QE_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_DYNAMICOUT
        #else
            #error "Unknown configuration"
        #endif
    #endif
#else
    #error "Quimera Engine Error Message: Operative system not supported."
#endif


// --------------------------------------------------------------------------------------------------------
// Compilation configuration names: Depending on the operative system and the compilation configuration
// currently selected, a name is assigned. This name is going to be used, for example, to generate the
// test result file.
// --------------------------------------------------------------------------------------------------------
#if   defined(QE_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Win32DebugSharedrtStatic"
#elif defined(QE_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Win32DebugSharedrtDynamic"
#elif defined(QE_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Win32ReleaseSharedrtStatic"
#elif defined(QE_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Win32ReleaseSharedrtDynamic"
#elif defined(QE_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Win32DebugStaticrtStatic"
#elif defined(QE_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Win32DebugStaticrtDynamic"
#elif defined(QE_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Win32ReleaseStaticrtStatic"
#elif defined(QE_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Win32ReleaseStaticrtDynamic"

#elif defined(QE_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32DebugSharedrtStatic"
#elif defined(QE_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32DebugSharedrtDynamic"
#elif defined(QE_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32ReleaseSharedrtStatic"
#elif defined(QE_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32ReleaseSharedrtDynamic"
#elif defined(QE_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32DebugStaticrtStatic"
#elif defined(QE_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32DebugStaticrtDynamic"
#elif defined(QE_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32ReleaseStaticrtStatic"
#elif defined(QE_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Linux32ReleaseStaticrtDynamic"

#elif defined(QE_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32DebugSharedrtStatic"
#elif defined(QE_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32DebugSharedrtDynamic"
#elif defined(QE_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32ReleaseSharedrtStatic"
#elif defined(QE_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32ReleaseSharedrtDynamic"
#elif defined(QE_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32DebugStaticrtStatic"
#elif defined(QE_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32DebugStaticrtDynamic"
#elif defined(QE_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_STATICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32ReleaseStaticrtStatic"
#elif defined(QE_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define QE_TEST_CONFIG_NAME "Mac32ReleaseStaticrtDynamic"

#endif

#endif // __COMMONCONFIGDEFINITIONS__
