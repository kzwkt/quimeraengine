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

#ifndef __DATATYPESDEFINITIONS__
#define __DATATYPESDEFINITIONS__

#include "CrossPlatformBasicTypes.h"

#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    #include <string>
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    #include "QCharUnicode.h"
    #include "QStringUnicode.h"
#endif

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{
    
// --------------------------------------------------------------------------------------------------------
// Float type: Defines which floating point type will be used by the whole engine, according to the
// configured precission.
// --------------------------------------------------------------------------------------------------------

#if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    typedef f32_q float_q;
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    typedef f64_q float_q;
#endif

// --------------------------------------------------------------------------------------------------------
// Float type size: Defines the floating point type size (in bytes), depending on the configured precission.
// The size depens on the operative system / compiler too.
// --------------------------------------------------------------------------------------------------------
#if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    #define QE_FLOAT_SIZE 4
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    #define QE_FLOAT_SIZE 8
#endif

// --------------------------------------------------------------------------------------------------------
// Integer/Float type sizes equivalence: Defines the integer type whose size equals to the selected floating
// point type size.
// --------------------------------------------------------------------------------------------------------
#if defined(QE_OS_WINDOWS) && (QE_OS_WINDOWS == 32)
    #ifdef QE_COMPILER_MSVC
        #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
            typedef i32_q int_for_float_q;
        #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
            typedef i64_q int_for_float_q;
        #else
            typedef i32_q int_for_float_q;
        #endif
    #elif QE_COMPILER_GCC
        #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
            typedef i32_q int_for_float_q;
        #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
            typedef i64_q int_for_float_q;
        #else
            typedef i32_q int_for_float_q;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#elif defined(QE_OS_LINUX) && (QE_OS_LINUX == 32)
    #if QE_COMPILER_GCC
        #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
            typedef i32_q int_for_float_q;
        #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
            typedef i64_q int_for_float_q;
        #else
            typedef i32_q int_for_float_q;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#elif defined(QE_OS_MAC) && (QE_OS_MAC == 32)
    #if QE_COMPILER_GCC
        #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
            typedef i32_q int_for_float_q;
        #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
            typedef i64_q int_for_float_q;
        #else
            typedef i32_q int_for_float_q;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#else
    // [TODO] Thund: Test the system in another platform and write the type sizes in that machine
    // Win64, Linux64
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
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    typedef char char_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    typedef QCharUnicode char_q;
#else
    typedef char char_q;
#endif


// --------------------------------------------------------------------------------------------------------
// String type: Defines the string class used throughout the engine, depending on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    typedef std::string string_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    typedef QStringUnicode string_q;
#endif


// --------------------------------------------------------------------------------------------------------
// Literals prefix: Specifies if character string literals must be prefixed with the wide-char token, depending
// on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    #define QE_L(str) str
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    #define QE_L(str) str
#endif


// --------------------------------------------------------------------------------------------------------
// Enumeration's integer equivalent: Defines which is the equivalent integer type for enumeration types.
//                       Enumeration types used in Quimera Engine are guaranteed to be 32-bit unsigned integers,
//                       whatever the OS or the architecture it executes on.
// --------------------------------------------------------------------------------------------------------
typedef u32_q enum_int_q;

// --------------------------------------------------------------------------------------------------------
// Enumeration's limits: Concretes the maximum and minimum values an enumerated type can store.
//                       Enumeration types used in Quimera Engine are guaranteed to be 32-bit unsigned integers,
//                       whatever the OS or the architecture it executes on.
// --------------------------------------------------------------------------------------------------------
#define QE_ENUMERATION_MIN_VALUE 0x0
#define QE_ENUMERATION_MAX_VALUE 0xFFFFFFFF

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __DATATYPESDEFINITIONS__
