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

#include <sstream>

#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"
#include "Assertions.h"
#include "EQComparisonType.h"
#include <math.h>

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Helper class that offers functionality related to integer types.
/// </summary>
class QE_LAYER_COMMON_SYMBOLS SQInteger
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
    static i8_q Abs(const i8_q nValue);

    /// <summary>
    /// Returns the absolute value of a short integer value.
    /// </summary>
    /// <param name="nValue">[IN] A short integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as a short integer.
    /// </returns>
    static i16_q Abs(const i16_q nValue);

    /// <summary>
    /// Returns the absolute value of an integer value.
    /// </summary>
    /// <param name="nValue">[IN] An integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as an integer.
    /// </returns>
    static i32_q Abs(const i32_q nValue);

    /// <summary>
    /// Returns the absolute value of a long integer value.
    /// </summary>
    /// <param name="nValue">[IN] A long integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as a long integer.
    /// </returns>
    static i64_q Abs(const i64_q nValue);

    /// <summary>
    /// Inverts the order of bytes which compound an integer number and returns the result as output parameter.
    /// </summary>
    /// <remarks>
    /// A 32-bits integer number whose value equals to 0xAABBCCDD will be transformed to 0xDDCCBBAA, for example.
    /// </remarks>
    /// <typeparam name="IntegerT">The integral type passed as argument.</typeparam>
    /// <param name="nValue">[IN] The value whose bytes are to be swapped.</param>
    /// <returns>
    /// The transformed value.
    /// </returns>
    template<typename IntegerT>
    static IntegerT SwapEndianess(const IntegerT nValue)
    {
        const unsigned int INTEGER_SIZE = sizeof(IntegerT);

        // Ambiguous type to treat the same bit strip as byte array and integer types
        // Note: The type change is not immediate, it has memory reading/writing cost
        union IntegerOrBytesUnion
        {
            IntegerT _integer;
            u8_q     _bytes[INTEGER_SIZE];
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
    /// <typeparam name="IntegerT">The type of integral type passed as argument.</typeparam>
    /// <param name="nValue">[IN] The integer number to be converted.</param>
    /// <returns>
    /// The string that represents the number.
    /// </returns>
    template<typename IntegerT>
    static string_q ToString(const IntegerT nValue)
    {
        std::ostringstream output;
        output << nValue;
        return output.str().c_str();
    }

    /// <summary>
    /// Converts an unsigned integer number to its hexadecimal representation as a string.
    /// </summary>
    /// <typeparam name="IntegerT">The unsigned integral type passed as argument.</typeparam>
    /// <param name="uValue">[IN] The value whose bytes are to be printed.</param>
    /// <returns>
    /// The string that contains the hexadecimal representation of the integer.
    /// </returns>
    template<typename IntegerT>
    static string_q ToStringHexadecimal(const IntegerT uValue)
    {
        static const u8_q ASCII_FIRST_NUMBER = 48U;
        static const u8_q ASCII_FIRST_CAPITAL_LETTER = 65U;

        string_q strResult;
        const u8_q* arBytes = rcast_q(&uValue, const u8_q*);
        u8_q uCurrentByteHalf = 0;
        char_q correspondingChar(0);

        // Every half of every byte in the input variable is parsed and transformed to its textual hexadecimal representation
#if QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
        pointer_uint_q uIndexCorrection = 1U;

        for(pointer_uint_q uMemOffset = sizeof(IntegerT); uMemOffset > 0; --uMemOffset)
        {
#elif QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
        pointer_uint_q uIndexCorrection = 0;

        for(pointer_uint_q uMemOffset = 0; uMemOffset < sizeof(IntegerT); ++uMemOffset)
        {
#endif
            // Gets the first half of the byte
            uCurrentByteHalf = arBytes[uMemOffset - uIndexCorrection] >> 4U;

            // Writes the corresponding character for the first half
            correspondingChar = uCurrentByteHalf > 9U ? char_q(ASCII_FIRST_CAPITAL_LETTER + uCurrentByteHalf - 0x0A) : // It's a letter
                                                        char_q(ASCII_FIRST_NUMBER + uCurrentByteHalf);                 // It's a number
            strResult.Append(correspondingChar);

            // Gets the second half of the byte
            uCurrentByteHalf = arBytes[uMemOffset - uIndexCorrection] & 0x0F;

            // Writes the corresponding character for the second half
            correspondingChar = uCurrentByteHalf > 9U ? char_q(ASCII_FIRST_CAPITAL_LETTER + uCurrentByteHalf - 0x0A) : // It's a letter
                                                        char_q(ASCII_FIRST_NUMBER + uCurrentByteHalf);                 // It's a number
            strResult.Append(correspondingChar);
        }

        return strResult;
    }
    
    /// <summary>
    /// Generates an integer value from an hexadecimal number contained in a string.
    /// </summary>
    /// <remarks>
    /// The length of the input string must be equal or lower than the size, in bytes, of the integral type multiplied by 2 (every byte is represented by 2 cyphers).
    /// If the number has a prefix, it is not taken into account in the previous precondition.
    /// </remarks>
    /// <typeparam name="IntegerT">The unsigned integral type to be returned.</typeparam>
    /// <param name="strHexadecimal">[IN] The string that contains the hexadecimal number. It can contain a "0x" prefix. Letters can be uppercase or lowercase.</param>
    /// <returns>
    /// The obtained integer value.
    /// </returns>
    template<class IntegerT>
    static IntegerT FromHexadecimalString(const string_q &strHexadecimal)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
        using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;

        static const codepoint_q CODEPOINT_FIRST_NUMBER          = '0';
        static const codepoint_q CODEPOINT_LAST_NUMBER           = '9';
        static const codepoint_q CODEPOINT_FIRST_ALPHA_UPPERCASE = 'A';
        static const codepoint_q CODEPOINT_LAST_ALPHA_UPPERCASE  = 'Z';
        static const codepoint_q CODEPOINT_FIRST_ALPHA_LOWERCASE = 'a';
        static const codepoint_q CODEPOINT_LAST_ALPHA_LOWERCASE  = 'z';
        static const string_q HEX_PREFIX("0x");

        const unsigned int START_POSITION = strHexadecimal.Contains(HEX_PREFIX, EQComparisonType::E_BinaryCaseInsensitive) ? HEX_PREFIX.GetLength() :
                                                                                                                             0;
        const unsigned int STRING_LENGTH = strHexadecimal.GetLength();

        QE_ASSERT_ERROR(STRING_LENGTH - START_POSITION - 1U <= sizeof(IntegerT) * 2U, string_q("The string (\"") + strHexadecimal + "\") must contain 2 letters per byte of the integer (apart from the prefix, if it has any).");

        IntegerT uMultiplier = 0;
        codepoint_q byteHalf = 0;
        IntegerT value = 0;

        for(unsigned int i = START_POSITION; i < STRING_LENGTH; ++i)
        {
            // It's a change of base (16 to 10), the exponent of the power of 16 is greater as the number occupies a more significant position in the string
            uMultiplier = scast_q(powf(16.0f, scast_q(STRING_LENGTH - i - 1U, float)), IntegerT);

            byteHalf = strHexadecimal[i].GetCodePoint();

            if(byteHalf >= CODEPOINT_FIRST_NUMBER && byteHalf <= CODEPOINT_LAST_NUMBER)
                value += uMultiplier * (byteHalf - CODEPOINT_FIRST_NUMBER); // 16^n * number
            else if(byteHalf >= CODEPOINT_FIRST_ALPHA_UPPERCASE && byteHalf <= CODEPOINT_LAST_ALPHA_UPPERCASE)
                value += uMultiplier * (byteHalf - CODEPOINT_FIRST_ALPHA_UPPERCASE + 10U); // 16^n * letter [A-F] (where letters start with a value of 10)
            else if(byteHalf >= CODEPOINT_FIRST_ALPHA_LOWERCASE && byteHalf <= CODEPOINT_LAST_ALPHA_LOWERCASE)
                value += uMultiplier * (byteHalf - CODEPOINT_FIRST_ALPHA_LOWERCASE + 10U); // 16^n * letter [a-f] (where letters start with a value of 10)
            else
                QE_ASSERT_ERROR(false, "The string contains invalid characters.");
        }

        return value;
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
string_q QE_LAYER_COMMON_SYMBOLS SQInteger::ToString<i8_q>(const i8_q nValue);

/// <summary>
/// Converts the integer number to a readable character string that represents it.
/// </summary>
/// <param name="uValue">[IN] The integer number to be converted.</param>
/// <returns>
/// The string that represents the number.
/// </returns>
template<>
string_q QE_LAYER_COMMON_SYMBOLS SQInteger::ToString<u8_q>(const u8_q uValue);

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQINTEGER__
