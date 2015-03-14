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
#if defined(QE_COMPILER_MSVC)
    #if QE_COMPILER_MSVC >= 10
        #define null_q 0
    #else
        #define null_q 0
    #endif
#elif defined(QE_COMPILER_GCC)
    #define null_q 0
#endif

// --------------------------------------------------------------------------------------------------------
// Warning disabler: Defines the compiler proprocessor #pragma instruction that disables a warning.
//                   Note that it is not cross-platform since every compiler uses very different syntaxes.
// --------------------------------------------------------------------------------------------------------
#if defined(QE_COMPILER_MSVC)
    #if QE_COMPILER_MSVC >= 10
        #define QE_DISABLE_WARNING(number) warning (disable : number )
    #else
        #define QE_DISABLE_WARNING(number) warning (disable : number )
    #endif
#elif defined(QE_COMPILER_GCC)
    #define QE_DISABLE_WARNING(flag) GCC diagnostic ignored flag
#endif

// --------------------------------------------------------------------------------------------------------
// Dll exportation / importation aliases: Defines which compiler keywords will be used to export and import
// symbols when compiling as a DLL, depending on the operative system and the compiler.
// --------------------------------------------------------------------------------------------------------
#if defined(QE_OS_WINDOWS)
    #if defined(QE_COMPILER_MSVC)
        #define QE_EXPORT_SYMBOLS __declspec( dllexport )
        #define QE_EXPORT_SYMBOLS_EXTERN
        #define QE_IMPORT_SYMBOLS __declspec( dllimport )
        #define QE_IMPORT_SYMBOLS_EXTERN extern
    #elif defined(QE_COMPILER_GCC)
        #define QE_EXPORT_SYMBOLS __attribute__(( dllexport ))
        #define QE_EXPORT_SYMBOLS_EXTERN
        #define QE_IMPORT_SYMBOLS __attribute__(( dllimport ))
        #define QE_IMPORT_SYMBOLS_EXTERN extern
    #endif
#elif defined(QE_OS_LINUX)
    #if defined(QE_COMPILER_GCC)
        #define QE_EXPORT_SYMBOLS __attribute__ ((visibility ("default")))
        #define QE_EXPORT_SYMBOLS_EXTERN
        #define QE_IMPORT_SYMBOLS
        #define QE_IMPORT_SYMBOLS_EXTERN extern
    #endif
#elif defined(QE_OS_MAC)
    #if defined(QE_COMPILER_GCC)
        #define QE_EXPORT_SYMBOLS __attribute__ ((visibility ("default")))
        #define QE_EXPORT_SYMBOLS_EXTERN
        #define QE_IMPORT_SYMBOLS
        #define QE_IMPORT_SYMBOLS_EXTERN extern
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
// Alignment calculation functions: Alias for every compiler's alignment calculation function.
// Note: There is a difference between GCC and MSVC functions, it is not possible to use objects in MSVC's version.
// --------------------------------------------------------------------------------------------------------
#if   defined(QE_COMPILER_MSVC)
    #define alignof_q( type ) __alignof(type)
#elif defined(QE_COMPILER_GCC)
    #define alignof_q( type ) __alignof__(type)
#endif


#endif // __INTERNALDEFINITIONS__
