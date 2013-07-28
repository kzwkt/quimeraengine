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

#ifndef __SQINTEGER__
#define __SQINTEGER__

#include <string>
#include <cstdlib>

#include <boost\lexical_cast.hpp>

#include "DataTypesDefinitions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace DataTypes
{

/// <summary>
/// Helper class that offers functionality related to integer types.<br>
/// Use these static methods extensively in your code, as far as you can.
/// </summary>
class QDllExport SQInteger
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Maximum unsigned 8 bits integer value.
    /// </summary>
    static const u8_q MaxU8_Q;

    /// <summary>
    /// Maximum unsigned 16 bits integer value.
    /// </summary>
    static const u16_q MaxU16_Q;

    /// <summary>
    /// Maximum unsigned 32 bits integer value.
    /// </summary>
    static const u32_q MaxU32_Q;

    /// <summary>
    /// Maximum unsigned 64 bits integer value.
    /// </summary>
    static const u64_q MaxU64_Q;

    /// <summary>
    /// Maximum signed 8 bits integer positive value.
    /// </summary>
    static const i8_q MaxPositiveI8_Q;

    /// <summary>
    /// Maximum signed 8 bits integer positive value.
    /// </summary>
    static const i8_q MaxNegativeI8_Q;

    /// <summary>
    /// Maximum signed 16 bits integer positive value.
    /// </summary>
    static const i16_q MaxPositiveI16_Q;

    /// <summary>
    /// Maximum signed 16 bits integer positive value.
    /// </summary>
    static const i16_q MaxNegativeI16_Q;

    /// <summary>
    /// Maximum signed 32 bits integer positive value.
    /// </summary>
    static const i32_q MaxPositiveI32_Q;

    /// <summary>
    /// Maximum signed 32 bits integer positive value.
    /// </summary>
    static const i32_q MaxNegativeI32_Q;

    /// <summary>
    /// Maximum signed 64 bits integer positive value.
    /// </summary>
    static const i64_q MaxPositiveI64_Q;

    /// <summary>
    /// Maximum signed 64 bits integer positive value.
    /// </summary>
    static const i64_q MaxNegativeI64_Q;


	// CONSTRUCTORS
	// ---------------
private:

	// Default constructor (hidden).
	SQInteger();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Returns the absolute value of an 8-bit integer value.
    /// </summary>
    /// <param name="nValue">[IN] An 8-bit integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as an 8-bit integer.
    /// </returns>
    inline static i8_q Abs(i8_q& nValue)
    {
       return abs(nValue);
    }

    /// <summary>
    /// Returns the absolute value of a short integer value.
    /// </summary>
    /// <param name="nValue">[IN] A short integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as a short integer.
    /// </returns>
    inline static i16_q Abs(const i16_q& nValue)
    {
       return abs(nValue);
    }

    /// <summary>
    /// Returns the absolute value of an integer value.
    /// </summary>
    /// <param name="nValue">[IN] An integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as an integer.
    /// </returns>
    inline static i32_q Abs(const i32_q& nValue)
    {
       return abs(nValue);
    }

    /// <summary>
    /// Returns the absolute value of a long integer value.
    /// </summary>
    /// <param name="nValue">[IN] A long integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as a long integer.
    /// </returns>
    inline static i64_q Abs(const i64_q& nValue)
    {
	   return llabs(nValue);
    }

    /// <summary>
    /// Inverts the order of bytes which compound an integer number and returns the result as output parameter.<br>
    /// A 32-bits integer number whose value equals to 0xAABBCCDD will be transformed to 0xDDCCBBAA, for example.
    /// </summary>
    /// <param name="nValue">[IN] The value whose bytes are to be swapped.</param>
    /// <returns>
    /// The transformed value.
    /// </returns>
    template<typename IntegerType>
    inline static IntegerType SwapEndianess(const IntegerType &nValue)
    {
        const unsigned int INTEGER_SIZE = sizeof(IntegerType);

        // Ambiguous type to treat the same bit strip as byte array and integer types
        // Note: The type change is not immediate, it has memory reading/writing cost
        union IntegerOrBytesUnion
        {
            IntegerType _integer;
            u8_q        _bytes[INTEGER_SIZE];
        };

        IntegerOrBytesUnion srcValue;
        srcValue._integer = nValue;

        IntegerOrBytesUnion swappedValue;

        // Integer's bytes are copied in inverse order to the output float
        for(unsigned int i = 0, j = INTEGER_SIZE - 1; i < INTEGER_SIZE; ++i, --j)
            swappedValue._bytes[i] = srcValue._bytes[j];

        return swappedValue._integer;
    }

    /// <summary>
    /// Converts the integer number to a readable character string that represents it.
    /// </summary>
    /// <param name="nValue">[IN] The integer number to be converted.</param>
    /// <returns>
    /// The string that represents the number.
    /// </returns>
    template<typename IntegerType>
    static string_q ToString(const IntegerType &nValue)
    {
        string_q strOut = boost::lexical_cast<string_q>(nValue);
        return strOut;
    }

};

// SPECIALIZATIONS
// ---------------

/// <summary>
/// Converts the integer number to a readable character string that represents it.
/// </summary>
/// <param name="nValue">[IN] The integer number to be converted.</param>
/// <returns>
/// The string that represents the number.
/// </returns>
template<>
string_q SQInteger::ToString<i8_q>(const char &nValue);

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQINTEGER__
