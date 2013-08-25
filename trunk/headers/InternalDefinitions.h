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
        #define null_q 0
    #else
        #define null_q 0
    #endif
#elif QE_COMPILER_GCC
    #define null_q 0
#endif

// --------------------------------------------------------------------------------------------------------
// Warning disabler: Defines the compiler proprocessor #pragma instruction that disables a warning.
//                   Note that it is not cross-platform since every compiler uses very different syntaxes.
// --------------------------------------------------------------------------------------------------------
#ifdef QE_COMPILER_MSVC
    #if QE_COMPILER_MSVC >= 10
        #define QE_DISABLE_WARNING(number) warning (disable : number )
    #else
        #define QE_DISABLE_WARNING(number) warning (disable : number )
    #endif
#elif QE_COMPILER_GCC
    #define QE_DISABLE_WARNING(flag) GCC diagnostic ignored flag
#endif

// --------------------------------------------------------------------------------------------------------
// Dll Export Specifier: Defines which compiler keywords will be used to export symbols when compiling as
// a DLL. Their values are "empty" when compiling the library as static.
// --------------------------------------------------------------------------------------------------------
#ifdef QE_PREPROCESSOR_COMPILER_SHAREDLIB // QE_PREPROCESSOR_COMPILER_SHAREDLIB is specified as a preprocessor definition
    #ifdef QE_OS_WINDOWS
        #ifdef QE_COMPILER_MSVC
            #define QDllExport __declspec( dllexport )
            #define QE_DLLIMPORT_EXTERN
        #elif QE_COMPILER_GCC
            #define QDllExport __attribute__(( dllexport ))
            #define QE_DLLIMPORT_EXTERN
        #endif
    #elif defined(QE_OS_LINUX)
        #if QE_COMPILER_GCC
            #define QDllExport __attribute__((visibility("default")))( dllexport )
            #define QE_DLLIMPORT_EXTERN
        #endif
    #endif
#elif defined(QE_PREPROCESSOR_COMPILER_IMPORT) // QE_PREPROCESSOR_COMPILER_IMPORT is specified as a preprocessor definition when compiling the client system
    #ifdef QE_OS_WINDOWS
        #ifdef QE_COMPILER_MSVC
            #define QDllExport __declspec( dllimport )
            #define QE_DLLIMPORT_EXTERN extern
        #elif QE_COMPILER_GCC
            #define QDllExport __attribute__(( dllimport ))
            #define QE_DLLIMPORT_EXTERN extern
        #endif
    #elif defined(QE_OS_LINUX)
        #if QE_COMPILER_GCC
            #define QDllExport __attribute__(( dllimport ))
            #define QE_DLLIMPORT_EXTERN extern
        #endif
    #endif
#else // Static library
    #ifdef QE_OS_WINDOWS
        #define QDllExport
        #define QE_DLLIMPORT_EXTERN
    #elif defined(QE_OS_LINUX)
        #define QE_DLLIMPORT_EXTERN
        #define QDllExport
    #endif
#endif


// --------------------------------------------------------------------------------------------------------
// Casting operators: Wrappers for every casting operator to make them shorter and configurable.
// --------------------------------------------------------------------------------------------------------
#define rcast_q(object, type) reinterpret_cast<type>(object)
#define scast_q(object, type) static_cast<type>(object)
#define dcast_q(object, type) dynamic_cast<type>(object)
#define ccast_q(object, type) const_cast<type>(object)


// --------------------------------------------------------------------------------------------------------
// Assertions: Defines assertion statement behavior.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT != QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS // This is used for testing purposes
        #include <exception>
        #define QE_ASSERT(expr) { if(!(expr)) throw new std::exception(); } // TODO [Thund]: Create an special exception class for this
    #else
        #ifdef QE_COMPILER_GCC

            /// <summary>
            /// Special behaviour for using GDB so it stops at the line the assertion fails and let the
            /// developer to continue debugging from there on advance.
            /// </summary>
            QDllExport void QE_ASSERT_FAILED();

            #define QE_ASSERT(expr) (expr) ? (void(0)) : QE_ASSERT_FAILED(); // This sentence makes GDB to stop at the failing line and continue the execution later
        #else
            #include <boost/assert.hpp>

            #ifdef BOOST_ASSERT
                #define QE_ASSERT(expr) BOOST_ASSERT(expr);
            #else
                #define QE_ASSERT(expr) ;
            #endif
        #endif
    #endif

#else

    #define QE_ASSERT(expr) ;

#endif

#endif // __INTERNALDEFINITIONS__
