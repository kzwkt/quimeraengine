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

#ifndef __CROSSPLATFORMBASICBASICTYPES__
#define __CROSSPLATFORMBASICBASICTYPES__

#include "InternalDefinitions.h"

#ifdef QE_COMPILER_MSVC
    #include <xmmintrin.h> // Includes __m128 definition.
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
// Basic types: Defines all basic types used by some engine components, whose size is assured to be
// always the same.
// --------------------------------------------------------------------------------------------------------

#if defined(QE_OS_WINDOWS) && (QE_OS_WINDOWS == 32)
    #ifdef QE_COMPILER_MSVC
        typedef unsigned char       u8_q;   // Unsigned 8-bits integer
        typedef char                i8_q;   // Signed 8-bits integer
        typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
        typedef short int           i16_q;  // Signed 16-bits integer
        typedef unsigned int        u32_q;  // Unsigned 32-bits integer
        typedef int                 i32_q;  // Signed 32-bits integer
        typedef unsigned long long  u64_q;  // Unsigned 64-bits integer
        typedef long long           i64_q;  // Signed 64-bits integer
        typedef float               f32_q;  // 32-bits floating point number
        typedef double              f64_q;  // 64-bits floating point number
        typedef __m128              vf32_q; // 4 x 32-bits packed floating point numbers
        // Note: There is no integer or float whose size is greater than 64 bits on Windows 32 bits
    #elif QE_COMPILER_GCC
        typedef unsigned char       u8_q;   // Unsigned 8-bits integer
        typedef char                i8_q;   // Signed 8-bits integer
        typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
        typedef short int           i16_q;  // Signed 16-bits integer
        typedef unsigned int        u32_q;  // Unsigned 32-bits integer
        typedef int                 i32_q;  // Signed 32-bits integer
        typedef unsigned long long  u64_q;  // Unsigned 64-bits integer
        typedef long long           i64_q;  // Signed 64-bits integer
        typedef float               f32_q;  // 32-bits floating point number
        typedef double              f64_q;  // 64-bits floating point number
        typedef union  // [TODO] Thund: Check if this type can be used with SSE instructions
        {
             float m128_f32[4];
             u64_q m128_u64[2];
             i8_q  m128_i8[16];
             i16_q m128_i16[8];
             i32_q m128_i32[4];
             i64_q m128_i64[2];
             u8_q  m128_u8[16];
             u16_q m128_u16[8];
             u32_q m128_u32[4];
        } vf32_q __attribute__((aligned(16))); // 4 x 32-bits packed floating point numbers
        // Note: There is no integer or float whose size is greater than 64 bits on Windows 32 bits
    #else
		#error Compiler not detected on Windows
        // [TODO] Thund: Test the system in another compiler and write the basic types for that compiler
    #endif

    typedef u32_q        pointer_uint_q; // Unsigned integer types for pointer conversion (32 bits) common for ms and gcc compilers

#elif defined(QE_OS_LINUX) && (QE_OS_LINUX == 32)
    #if QE_COMPILER_GCC
        typedef unsigned char       u8_q;   // Unsigned 8-bits integer
        typedef char                i8_q;   // Signed 8-bits integer
        typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
        typedef short int           i16_q;  // Signed 16-bits integer
        typedef unsigned int        u32_q;  // Unsigned 32-bits integer
        typedef int                 i32_q;  // Signed 32-bits integer
        typedef unsigned long long  u64_q;  // Unsigned 64-bits integer
        typedef long long           i64_q;  // Signed 64-bits integer
        typedef float               f32_q;  // 32-bits floating point number
        typedef double              f64_q;  // 64-bits floating point number
        typedef union  // [TODO] Thund: Check if this type can be used with SSE instructions
        {
             float m128_f32[4];
             u64_q m128_u64[2];
             i8_q  m128_i8[16];
             i16_q m128_i16[8];
             i32_q m128_i32[4];
             i64_q m128_i64[2];
             u8_q  m128_u8[16];
             u16_q m128_u16[8];
             u32_q m128_u32[4];
        } vf32_q __attribute__((aligned(16))); // 4 x 32-bits packed floating point numbers
    #else
		#error Compiler not detected on Linux
        // [TODO] Thund: Test the system in another compiler and write the basic types for that compiler
    #endif

    typedef u32_q        pointer_uint_q; // Unsigned integer types for pointer conversion (32 bits) common for ms and gcc compilers


#elif defined(QE_OS_MAC) && (QE_OS_MAC == 32)
    #if QE_COMPILER_GCC
        typedef unsigned char       u8_q;   // Unsigned 8-bits integer
        typedef char                i8_q;   // Signed 8-bits integer
        typedef short unsigned int  u16_q;  // Unsigned 16-bits integer
        typedef short int           i16_q;  // Signed 16-bits integer
        typedef unsigned int        u32_q;  // Unsigned 32-bits integer
        typedef int                 i32_q;  // Signed 32-bits integer
        typedef unsigned long long  u64_q;  // Unsigned 64-bits integer
        typedef long long           i64_q;  // Signed 64-bits integer
        typedef float               f32_q;  // 32-bits floating point number
        typedef double              f64_q;  // 64-bits floating point number
        typedef union  // [TODO] Thund: Check if this type can be used with SSE instructions
        {
             float m128_f32[4];
             u64_q m128_u64[2];
             i8_q  m128_i8[16];
             i16_q m128_i16[8];
             i32_q m128_i32[4];
             i64_q m128_i64[2];
             u8_q  m128_u8[16];
             u16_q m128_u16[8];
             u32_q m128_u32[4];
        } vf32_q __attribute__((aligned(16))); // 4 x 32-bits packed floating point numbers
    #else
	
		#error Compiler not detected on Mac
        // [TODO] Thund: Test the system in another compiler and write the basic types for that compiler
    #endif

    typedef unsigned long        pointer_uint_q; // Unsigned integer types for pointer conversion (32 bits) common for ms and gcc compilers

#else

	#error OS not detected
	
#endif

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __CROSSPLATFORMBASICBASICTYPES__
