// [TERMS&CONDITIONS]

#ifndef __QUIMERAENGINE_CONFIGURATION__
#define __QUIMERAENGINE_CONFIGURATION__

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Core
{
namespace Configuration
{

// --------------------------------------------------------------------------------------------------------
// Precission: This block defines the engine's operations precission, this means, how accurate the 
// mathematical operations are. Take on account that more precission decreases performance.
// How to use it: Write a precission definition value as the default precission definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_PRECISSION_SIMPLE     0x0 // Simple precission: A 32 bits size floating point type.
#define QE_CONFIG_PRECISSION_DOUBLE     0x1 // Double precission: A large size (more than 32 bits) floating point type.

#define QE_CONFIG_PRECISSION_DEFAULT QE_CONFIG_PRECISSION_SIMPLE // [Configurable]


// --------------------------------------------------------------------------------------------------------
// Angle Notation: Defines whether the entire engine will work using Degrees or Radians.
// How to use it: Write an angle notation definition value as the default angle notation definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_ANGLENOTATION_RADIANS 0x0 // Radians notation: Angles are represented using radians, from 0 to 2*Pi.
#define QE_CONFIG_ANGLENOTATION_DEGREES 0x1 // Degrees notation: Angles are represented using degrees, from 0º to 360º.

#define QE_CONFIG_ANGLENOTATION_DEFAULT QE_CONFIG_ANGLENOTATION_RADIANS // [Configurable]


// --------------------------------------------------------------------------------------------------------
// Machine endianess: Defines the machine endianess, this means, which order does the hardware follow to 
// store and read bytes. This configuration value must be checked every time the project is compiled on
// a different hardware architecture. A way to know the machine endianess is as follows:
//
// int i = 1;           // 0x0001 => 0x01000000 || 0x00000001 ?
// char c = (char*)&i;  // 0x00 || 0x01 ?
//
// if(c == 1)           // Is c the most or the less relevant byte in i?
//   Little-Endian
// else
//   Big-Endian
//
// How to use it: Write an endianess definition value as the default endianess definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_MACHINEENDIANESS_LITTLEENDIAN 0x0 // Little-endian
#define QE_CONFIG_MACHINEENDIANESS_BIGENDIAN    0x1 // Big-endian

#define QE_CONFIG_MACHINEENDIANESS_DEFAULT QE_CONFIG_MACHINEENDIANESS_LITTLEENDIAN // [Configurable]


// --------------------------------------------------------------------------------------------------------
// Character Set: Specifies the character set used throughout the engine. It can be single-byte: 8 bits, 
// to represente ANSI characteres; multi-byte: 8 and 16 bits mixed, used by Windows systems (aka DBCS) to represent
// any existent alphabets; or Unicode: 16-bits characteres to also represent all existent alphabets.
//
// How to use it: Write a char width definition value as the default width definition.
// --------------------------------------------------------------------------------------------------------
#define QE_CONFIG_CHARACTERSET_SBCS 0x0    // Single-Byte Character Set
#define QE_CONFIG_CHARACTERSET_MBCS 0x1    // Multi-Byte Character Set [TODO] Thund: Not supported yet, will be available only for Windows OS.
#define QE_CONFIG_CHARACTERSET_UNICODE 0x2 // Unicode (2-bytes character set)

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

}//namespace Configuration
}//namespace Core
}//namespace QuimeraEngine
}//namespace Kinesis

#endif // __QUIMERAENGINE_CONFIGURATION__