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

#ifndef __SQFLOAT__
#define __SQFLOAT__

#include <string>

#include <boost/math/special_functions/trunc.hpp>

#include "DataTypesDefinitions.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace DataTypes
{

/// <summary>
/// Helper class that offers functionality related to floating point (IEEE 754) types.<br/>
/// Use these constants and static methods extensively in your code, as far as you can.
/// </summary>
class QDllExport SQFloat
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// The number 0, as a floating point type.
    /// </summary>
    static const float_q _0;

    /// <summary>
    /// The number 1, as a floating point type.
    /// </summary>
    static const float_q _1;

    /// <summary>
    /// The number 2, as a floating point type.
    /// </summary>
    static const float_q _2;

    /// <summary>
    /// The number 3, as a floating point type.
    /// </summary>
    static const float_q _3;

    /// <summary>
    /// The number 4, as a floating point type.
    /// </summary>
    static const float_q _4;

    /// <summary>
    /// The number 5, as a floating point type.
    /// </summary>
    static const float_q _5;

    /// <summary>
    /// The number 6, as a floating point type.
    /// </summary>
    static const float_q _6;

    /// <summary>
    /// The number 7, as a floating point type.
    /// </summary>
    static const float_q _7;

    /// <summary>
    /// The number 8, as a floating point type.
    /// </summary>
    static const float_q _8;

    /// <summary>
    /// The number 9, as a floating point type.
    /// </summary>
    static const float_q _9;

    /// <summary>
    /// The number 10, as a floating point type.
    /// </summary>
    static const float_q _10;

    /// <summary>
    /// The fraction \f$ \frac{1}{2}\f$, as a floating point type.
    /// </summary>
    static const float_q _0_5;

    /// <summary>
    /// The fraction \f$ \frac{1}{4}\f$, as a floating point type.
    /// </summary>
    static const float_q _0_25;

    /// <summary>
    /// Defines the comparison tolerance, or how much different can be two floating point values
    /// to be considered equals, according to the configured precission.
    /// </summary>
    static const float_q Epsilon;

    /// <summary>
    /// Maximum floating point value (farthest to zero positive real number).
    /// </summary>
    static const float_q MaxFloat_Q;

    /// <summary>
    /// Minimum floating point value (closest to zero positive real number).
    /// </summary>
    static const float_q MinFloat_Q;



	// CONSTRUCTORS
	// ---------------
private:

	// Default constructor (hidden).
    SQFloat();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Checks if the floating point value's state is NaN.<br/>
    /// That kind of value is undefined or non-representable, and it's said it isn't a number (NaN = Not a Number).<br/>
    /// Every time you use functions like acos, asin or atan2, you should check the result
    /// value.
    /// </summary>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is not a number, then returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsNaN(const float_q &fValue)
    {
        // [REVIEW] Thund: Boost provides functions to check this
        return fValue != fValue;
    }

    /// <summary>
    /// Checks if the floating point value's state is Infinite.<br/>
    /// That kind of value is non-representable and appears as an arithmetic
    /// operation result that overflows the floating point type bounds.<br/>
    /// Every time you use functions like tan, you should check the result value.
    /// </summary>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is infinite, then returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsInfinite(const float_q &fValue)
    {
        // [REVIEW] Thund: Boost provides functions to check this
        return SQFloat::IsLessThan(fValue, -SQFloat::MaxFloat_Q) || SQFloat::IsGreaterThan(fValue, SQFloat::MaxFloat_Q);
    }

    /// <summary>
    /// Checks if the floating point value's state is one of the special ones described in IEEE specification.<br/>
    /// That kind of values are undefined or non-representable (like infinite).
    /// </summary>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is infinite or is not a number, then returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsNanOrInfinite(const float_q &fValue)
    {
        return SQFloat::IsNaN(fValue) || SQFloat::IsInfinite(fValue);
    }

    /// <summary>
    /// Performs an equality comparison between two floating point numbers, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValueA">[IN] First floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Second floating point number to be compared.</param>
    /// <returns>
    /// If values are the same, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool AreEqual(const float_q &fValueA, const float_q &fValueB)
    {
        return SQFloat::Abs(fValueA - fValueB) <= SQFloat::Epsilon;
    }
    
    /// <summary>
    /// Performs an equality comparison between two floating point numbers, using a custom tolerance.
    /// </summary>
    /// <param name="fValueA">[IN] First floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Second floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If values are the same, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool AreEqual(const float_q &fValueA, const float_q &fValueB, const float_q &fTolerance)
    {
        // The tolerance provided must be equal to or greater than the system tolerance. If the tolerance is too small it could become useless.
        QE_ASSERT(fTolerance >= SQFloat::Epsilon);

        return SQFloat::Abs(fValueA - fValueB) <= fTolerance;
    }

    /// <summary>
    /// Performs an inequality comparison between two floating point numbers, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValueA">[IN] First floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Second floating point number to be compared.</param>
    /// <returns>
    /// If values are not the same, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool AreNotEqual(const float_q &fValueA, const float_q &fValueB)
    {
        return SQFloat::Abs(fValueA - fValueB) > SQFloat::Epsilon;
    }

    /// <summary>
    /// Checks if a floating point value is greater than a reference value, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fGreaterValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is greater than the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsGreaterThan(const float_q &fGreaterValue, const float_q &fReferenceValue)
    {
        // If subtraction result is positive, and is greater than Epsilon (are different numbers), the value is greater
        return (fGreaterValue - fReferenceValue) > SQFloat::Epsilon;
    }

    /// <summary>
    /// Checks if a floating point value is lower than a reference value, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fLowerValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is lower than the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsLessThan(const float_q &fLowerValue, const float_q &fReferenceValue)
    {
        // If subtraction result is negative, and is lower than Epsilon (are different numbers), the value is lower
        return (fLowerValue - fReferenceValue) < -SQFloat::Epsilon;
    }

    /// <summary>
    /// Checks if a floating point value is greater than or equals to a reference value, taking into account the
    /// system tolerance constant (Epsilon).
    /// </summary>
    /// <param name="fGreaterOrEqualsValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is greater than or equals to the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsGreaterOrEquals(const float_q &fGreaterOrEqualsValue, const float_q &fReferenceValue)
    {
        // If subtraction is greater or equals to -Epsilon, the value is greater or equals
        return (fGreaterOrEqualsValue - fReferenceValue) >= -SQFloat::Epsilon;
    }

    /// <summary>
    /// Checks if a floating point value is lower than or equals to a reference value, taking into account the
    /// system tolerance constant (Epsilon).
    /// </summary>
    /// <param name="fLessOrEqualsValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is lower than or equals to the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsLessOrEquals(const float_q &fLessOrEqualsValue, const float_q &fReferenceValue)
    {
        // If subtraction is lower or equals to Epsilon, the value is lower or equals
        return (fLessOrEqualsValue - fReferenceValue) <= SQFloat::Epsilon;
    }

    /// <summary>
    /// Checks whether a floating point number equals zero or is close to zero, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">[IN] The floating point number to be compared.</param>
    /// <returns>
    /// If the value equals zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsZero(const float_q &fValue)
    {
        return SQFloat::AreEqual(fValue, SQFloat::_0);
    }

    /// <summary>
    /// Checks whether a floating point number doesn't equal zero or is close to zero, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">[IN] The floating point number to be compared.</param>
    /// <returns>
    /// If the value doesn't equal zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsNotZero(const float_q &fValue)
    {
        return SQFloat::AreNotEqual(fValue, SQFloat::_0);
    }

    /// <summary>
    /// Converts the floating point number to a readable character string that represents it.
    /// </summary>
    /// <remarks>
    /// String representation for NaN or Infinite values are not guaranteed to be the same for different compilers.
    /// </remarks>
    /// <param name="fValue">[IN] The floating point number to be converted.</param>
    /// <returns>
    /// The string that represents the number (using a dot as decimal separator).
    /// </returns>
    static string_q ToString(const float_q &fValue);

    /// <summary>
    /// Converts a floating point number type to an integer number type.<br/>
    /// The result will be rounded (>0.5 --> 1.0).<br/>
    /// Expected template parameters are: int, long, long long, i32_q, i64_q.<br/>
    /// Integer type size should equals floating point type size or unexpected behavior will occur.
    /// </summary>
    /// <remarks>
    /// Depending on the configured precission, there is a performance overload due to standard conversion use when the value
    /// is greater than the one representable by floating point type mantissa:
    /// - For 32-bits floating point type values:
    ///  - Must be greater than or equals to \f$ -2^{22} \f$ (-4194304) and lower than or equals to \f$ 2^{23} \f$ (8388608).
    /// - For 64-bits floating point type values:
    ///  - Must be greater than or equals to \f$ -2^{51} \f$ (-2251799813685248l) and lower than or equals to \f$ 2^{52} \f$ (4503599627370496l).
    /// </remarks>
    /// <param name="fValue">[IN] Floating point number to be converted.</param>
    /// <returns>
    /// Integer value obtained.
    /// </returns>
    template<typename IntegerType>
    inline static IntegerType ToInteger(const float_q &fValue)
    {
        IntegerType outInteger;

        // Checks whether both input types have the same size
        QE_ASSERT( sizeof(fValue) == sizeof(outInteger) )

        #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

            const IntegerType LOWEST_EXPONENT_BIT_POS = 23;
            const IntegerType EXPONENT = 127 + LOWEST_EXPONENT_BIT_POS;
            const float_q MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  8388608; // Maximum convertible integer value = 2^23
            const float_q MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -4194304; // Maximum convertible integer negative value = 2^22

        #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

            const IntegerType LOWEST_EXPONENT_BIT_POS = 52;
            const IntegerType EXPONENT = 1023 + LOWEST_EXPONENT_BIT_POS;
            const float_q MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  4503599627370496l; // Maximum convertible integer value = 2^52
            const float_q MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -2251799813685248l; // Maximum convertible integer negative value = 2^51

        #endif

        if(fValue > MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED ||
           fValue < MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED)
        {
            // Checks whether the value is too big to be converted this way
            QE_ASSERT( fValue <= MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED )

            // Checks whether the value is too big (when it's negative) to be converted this way
            QE_ASSERT( fValue >= MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED )

            // When the value is out of the convertible bounds (using fast conversion), standard conversion is used
            outInteger = scast_q(fValue, IntegerType);
        }
        else
        {
            // Ambiguous type to treat the same bit strip as integer and floating point types
            // Note: The type change is not immediate, it has memory reading/writing cost
            union IntegerOrFloatUnion
            {
                float_q _float;
                IntegerType _integer;
            };

            IntegerOrFloatUnion biasValue;  // Used to manipulate the float mantissa
            IntegerOrFloatUnion finalValue; // Used to store operations results

            finalValue._float = fValue;

            if(finalValue._integer < 0)
                biasValue._integer = (EXPONENT << LOWEST_EXPONENT_BIT_POS) + (IntegerType(1) << (LOWEST_EXPONENT_BIT_POS - IntegerType(1))); // Equivalent to 1 x 2 ^ LOWEST_MANTISSA_BIT_POS + 1 x 2 ^ (LOWEST_MANTISSA_BIT_POS - 1)
            else
                biasValue._integer = EXPONENT << LOWEST_EXPONENT_BIT_POS; // Equivalent to 1 x 2 ^ LOWEST_MANTISSA_BIT_POS

            finalValue._float   += biasValue._float;
            finalValue._integer -= biasValue._integer; // Removes the exponent bits

            outInteger = finalValue._integer;
        }

        return outInteger;
    }

    /// <summary>
    /// Removes the fractional part of a floating point number and returns the result as output parameter.<br/>
    /// No rounding off is performed.
    /// </summary>
    /// <param name="fValue">[IN] Value to be truncated.</param>
    /// <returns>
    /// Value without fractional part.
    /// </returns>
    inline static float_q Truncate(const float_q &fValue)
    {
        return boost::math::trunc(fValue);
    }

	/// <summary>
	/// This method clamps the input value to lie within the range [Min..Max]. No tolerance is used for this operation.
	/// </summary>
	/// <param name="fValue">[IN] A floating point value; the value to be clamped, if neccesary.</param>
	/// <param name="fMin">[IN] A floating point value; the minimum value into the range.</param>
	/// <param name="fMax">[IN] A floating point value; the maximum value into the range.</param>
    /// <returns>
    /// The clamped value.
    /// </returns>
	inline static float_q Clamp(const float_q& fValue, const float_q& fMin, const float_q& fMax)
	{
		const float_q CAMPLED_VALUE = (fValue > fMax) ?  fMax :
										                 (fValue < fMin) ?  fMin :
														                    fValue;
        return CAMPLED_VALUE;
	}

    /// <summary>
    /// Inverts the order of bytes which compound a floating point number and returns the result as output parameter.<br/>
    /// A 32-bits floating point number whose value equals to 0xAABBCCDD will be
    /// transformed to 0xDDCCBBAA, for example.
    /// </summary>
    /// <param name="fValue">[IN] The value whose bytes are to be swapped.</param>
    /// <returns>
    /// The transformed value.
    /// </returns>
    inline static float_q SwapEndianess(const float_q &fValue)
    {
        const unsigned int FLOAT_SIZE = sizeof(float_q);

        // Ambiguous type to treat the same bit strip as byte array and floating point types
        // Note: The type change is not immediate, it has memory reading/writing cost
        union FloatOrBytesUnion
        {
            float_q _float;
            u8_q    _bytes[FLOAT_SIZE];
        };

        FloatOrBytesUnion srcValue;
        srcValue._float = fValue;

        FloatOrBytesUnion swappedValue;

        // Float's bytes are copied in inverse order to the output float
        for(unsigned int i = 0, j = FLOAT_SIZE - 1; i < FLOAT_SIZE; ++i, --j)
            swappedValue._bytes[i] = srcValue._bytes[j];

        return swappedValue._float;
    }

    /// <summary>
    /// Indicates whether the floating point number has negative sign.
    /// </summary>
    /// <param name="fValue">[IN] The value whose sign is going to be checked.</param>
    /// <returns>
    /// If the number is lower than zero, returns True. Otherwise, returns False.
    /// </returns>
    inline static bool IsNegative(const float_q &fValue)
    {
        return SQFloat::IsLessThan(fValue, SQFloat::_0);
    }

    /// <summary>
    /// Indicates whether the floating point number has positive sign.<br/>
    /// Zero is cosidered as positive.
    /// </summary>
    /// <param name="fValue">[IN] The value whose sign is going to be checked.</param>
    /// <returns>
    /// If the number is greater than or equals to zero, returns True. Otherwise, returns False.
    /// </returns>
    inline static bool IsPositive(const float_q &fValue)
    {
        return SQFloat::IsGreaterOrEquals(fValue, SQFloat::_0);
    }

    /// <summary>
    /// Copies a floating point number sign to another one.
    /// </summary>
    /// <param name="fSignedValue">[IN] A floating point number whose sign is to be copied.</param>
    /// <param name="fValueToCopyTo">[OUT] A floating point number whose sign is to be replaced.</param>
    inline static void CopySign(const float_q &fSignedValue, float_q &fValueToCopyTo)
    {
        // Negative source & Negative target = Keep negative
        // Negative source & Positive target = Change sign
        // Positive source & Negative target = Change sign
        // Positive source & Positive target = Keep positive
        fValueToCopyTo = SQFloat::IsNegative(fSignedValue)
                            ?
                            SQFloat::IsNegative(fValueToCopyTo) ? fValueToCopyTo : -fValueToCopyTo
                            :
                            SQFloat::IsNegative(fValueToCopyTo) ? -fValueToCopyTo : fValueToCopyTo;
    }

    /// <summary>
    /// Calculates the absolute value of the provided floating point number.
    /// </summary>
    /// <param name="fValue">[IN] A floating point number whose absolute value is wanted.</param>
    /// <returns>
    /// If the provided number is greater or equals to zero, it returns the same number,
    /// otherwise it returns the same number but with opposite sign.
    /// </returns>
    inline static float_q Abs(const float_q &fValue)
    {
        #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

            return fabsf(fValue);

        #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

            return fabsl(fValue);

        #endif
    }

};

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQFLOAT__
