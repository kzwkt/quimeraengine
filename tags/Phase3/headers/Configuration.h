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

#ifndef __QUIMERAENGINE_CONFIGURATION__
#define __QUIMERAENGINE_CONFIGURATION__

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Configuration
{

// --------------------------------------------------------------------------------------------------------
// Precission: This block defines the engine's operations precission, this means, how accurate the 
// mathematical operations are. Take on account that more precission decreases performance.
// How to use it: Write a precission definition value as the default precission definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_PRECISION_SIMPLE     0x0 // Simple precission: A 32 bits size floating point type.
#define QE_CONFIG_PRECISION_DOUBLE     0x1 // Double precission: A large size (more than 32 bits) floating point type.

#define QE_CONFIG_PRECISION_DEFAULT QE_CONFIG_PRECISION_SIMPLE // [Configurable]


// --------------------------------------------------------------------------------------------------------
// Angle Notation: Defines whether the entire engine will work using Degrees or Radians.
// How to use it: Write an angle notation definition value as the default angle notation definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_ANGLENOTATION_RADIANS 0x0 // Radians notation: Angles are represented using radians, from 0 to 2*Pi.
#define QE_CONFIG_ANGLENOTATION_DEGREES 0x1 // Degrees notation: Angles are represented using degrees, from 0º to 360º.

#define QE_CONFIG_ANGLENOTATION_DEFAULT QE_CONFIG_ANGLENOTATION_RADIANS // [Configurable]


// --------------------------------------------------------------------------------------------------------
// Character Set: Specifies the character set used throughout the engine. It can be ASCII: 8 bits 
// per character (using 7 bits, actually), limited to the English alphabet; or Unicode (UTF-16): 16/32-bits wide
// characters to represent all existent alphabets.
//
// How to use it: Write a character set value as the default character set definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_CHARACTERSET_ASCII 0x0   // ASCII
#define QE_CONFIG_CHARACTERSET_UNICODE 0x1 // Unicode

#define QE_CONFIG_CHARACTERSET_DEFAULT QE_CONFIG_CHARACTERSET_UNICODE // [Configurable]

    
// --------------------------------------------------------------------------------------------------------
// Asserts behavior: Specifies the behavior of assertions throughout the engine. Assertions can be disabled
// or be replaced by exceptions, for example.
//
// How to use it: Write a behavior value as the default definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_ASSERTSBEHAVIOR_ENABLED 0x0
#define QE_CONFIG_ASSERTSBEHAVIOR_DISABLED 0x1
#define QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS 0x2

#define QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT QE_CONFIG_ASSERTSBEHAVIOR_ENABLED // [Configurable]
    
// --------------------------------------------------------------------------------------------------------
// Asserts tracing behavior: Specifies whether failed assertions will be traced or not.
//
// How to use it: Write a behavior value as the default definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_ASSERTSTRACING_DISABLED 0x0
#define QE_CONFIG_ASSERTSTRACING_ENABLED  0x1

#define QE_CONFIG_ASSERTSTRACING_DEFAULT QE_CONFIG_ASSERTSTRACING_ENABLED // [Configurable]


}//namespace Configuration
}//namespace Common
}//namespace QuimeraEngine
}//namespace Kinesis

#endif // __QUIMERAENGINE_CONFIGURATION__
