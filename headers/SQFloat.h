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

#include <boost/math/special_functions/trunc.hpp>

#include "Assertions.h"
#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
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
/// Helper class that offers functionality related to floating point (IEEE 754) types.<br/>
/// Use these constants and static methods extensively in your code, as far as you can.
/// </summary>
class QE_LAYER_COMMON_SYMBOLS SQFloat
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
    /// to be considered equal, according to the configured precision.
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
    /// Checks if the floating point value's state is NaN.
    /// </summary>
    /// <remarks>
    /// That kind of value is undefined or non-representable, and it's said it isn't a number (NaN = Not a Number).<br/>
    /// Every time you use functions like acos, asin or atan2, you should check the result
    /// value.
    /// </remarks>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is not a number, then returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsNaN(const float_q fValue);

    /// <summary>
    /// Checks if the floating point value's state is Infinite.
    /// </summary>
    /// <remarks>
    /// That kind of value is non-representable and appears as an arithmetic
    /// operation result that overflows the floating point type bounds.<br/>
    /// Every time you use functions like tan, you should check the result value.
    /// </remarks>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is infinite, then returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsInfinite(const float_q fValue);

    /// <summary>
    /// Checks if the floating point value's state is one of the special ones described in IEEE specification.
    /// </summary>
    /// <remarks>
    /// That kind of values are undefined or non-representable (like infinite).
    /// </remarks>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is infinite or is not a number, then returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsNanOrInfinite(const float_q fValue);

    /// <summary>
    /// Performs an equality comparison between two floating point numbers, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValueA">[IN] First floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Second floating point number to be compared.</param>
    /// <returns>
    /// If values are the same, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool AreEqual(const float_q fValueA, const float_q fValueB);

    /// <summary>
    /// Performs an equality comparison between two floating point numbers, using a custom tolerance.
    /// </summary>
    /// <param name="fValueA">[IN] First floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Second floating point number to be compared.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If values are the same, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool AreEqual(const float_q fValueA, const float_q fValueB, const float_q fTolerance);

    /// <summary>
    /// Performs an inequality comparison between two floating point numbers, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValueA">[IN] First floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Second floating point number to be compared.</param>
    /// <returns>
    /// If values are not the same, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool AreNotEqual(const float_q fValueA, const float_q fValueB);

    /// <summary>
    /// Performs an inequality comparison between two floating point numbers, using a custom tolerance.
    /// </summary>
    /// <param name="fValueA">[IN] First floating point number to be compared.</param>
    /// <param name="fValueB">[IN] Second floating point number to be compared.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If values are not the same, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool AreNotEqual(const float_q fValueA, const float_q fValueB, const float_q fTolerance);

    /// <summary>
    /// Checks if a floating point value is greater than a reference value, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fGreaterValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is greater than the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsGreaterThan(const float_q fGreaterValue, const float_q fReferenceValue);

    /// <summary>
    /// Checks if a floating point value is greater than a reference value, using a custom tolerance.
    /// </summary>
    /// <param name="fGreaterValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If the first value is greater than the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsGreaterThan(const float_q fGreaterValue, const float_q fReferenceValue, const float_q fTolerance);

    /// <summary>
    /// Checks if a floating point value is lower than a reference value, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fLowerValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is lower than the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsLessThan(const float_q fLowerValue, const float_q fReferenceValue);

    /// <summary>
    /// Checks if a floating point value is lower than a reference value, using a custom tolerance.
    /// </summary>
    /// <param name="fLowerValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If the first value is lower than the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsLessThan(const float_q fLowerValue, const float_q fReferenceValue, const float_q fTolerance);

    /// <summary>
    /// Checks if a floating point value is greater than or equals to a reference value, taking into account the
    /// system tolerance constant (Epsilon).
    /// </summary>
    /// <param name="fGreaterOrEqualsValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is greater than or equals to the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsGreaterOrEquals(const float_q fGreaterOrEqualsValue, const float_q fReferenceValue);

    /// <summary>
    /// Checks if a floating point value is greater than or equals to a reference value, using a custom tolerance.
    /// </summary>
    /// <param name="fGreaterOrEqualsValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If the first value is greater than or equals to the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsGreaterOrEquals(const float_q fGreaterOrEqualsValue, const float_q fReferenceValue, const float_q fTolerance);

    /// <summary>
    /// Checks if a floating point value is lower than or equals to a reference value, taking into account the
    /// system tolerance constant (Epsilon).
    /// </summary>
    /// <param name="fLessOrEqualsValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <returns>
    /// If the first value is lower than or equals to the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsLessOrEquals(const float_q fLessOrEqualsValue, const float_q fReferenceValue);

    /// <summary>
    /// Checks if a floating point value is lower than or equals to a reference value, using a custom tolerance.
    /// </summary>
    /// <param name="fLessOrEqualsValue">The value which is to be compared.</param>
    /// <param name="fReferenceValue">The reference number which the first value is to be compared with.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If the first value is lower than or equals to the reference one, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsLessOrEquals(const float_q fLessOrEqualsValue, const float_q fReferenceValue, const float_q fTolerance);

    /// <summary>
    /// Checks whether a floating point number equals zero or is close to zero, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">[IN] The floating point number to be compared.</param>
    /// <returns>
    /// If the value equals zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsZero(const float_q fValue);

    /// <summary>
    /// Checks whether a floating point number equals zero or is close to zero, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">[IN] The floating point number to be compared.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If the value equals zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsZero(const float_q fValue, const float_q fTolerance);

    /// <summary>
    /// Checks whether a floating point number doesn't equal zero or is close to zero, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">[IN] The floating point number to be compared.</param>
    /// <returns>
    /// If the value doesn't equal zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsNotZero(const float_q fValue);

    /// <summary>
    /// Checks whether a floating point number doesn't equal zero or is close to zero, taking into account the system tolerance
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">[IN] The floating point number to be compared.</param>
    /// <param name="fTolerance">[IN] Tolerance to be applied in the comparison.</param>
    /// <returns>
    /// If the value doesn't equal zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsNotZero(const float_q fValue, const float_q fTolerance);

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
    static string_q ToString(const float_q fValue);

    /// <summary>
    /// Converts a floating point number type to an integer number type.
    /// </summary>
    /// <remarks>
    /// The result will be rounded (>0.5 --> 1.0).<br/>
    /// Expected template parameters are: int, long, long long, i32_q, i64_q.<br/>
    /// Integer type size should equals floating point type size or unexpected behavior will occur.<br/>
    /// Depending on the configured precission, there is a performance overload due to standard conversion use when the value
    /// is greater than the one representable by floating point type mantissa:<br/>
    /// - For 32-bits floating point type values:<br/>
    ///  - Must be greater than or equals to \f$ -2^{22} \f$ (-4194304) and lower than or equals to \f$ 2^{23} \f$ (8388608).<br/>
    /// - For 64-bits floating point type values:<br/>
    ///  - Must be greater than or equals to \f$ -2^{51} \f$ (-2251799813685248l) and lower than or equals to \f$ 2^{52} \f$ (4503599627370496l).<br/>
    /// Use this method in case the values are expected to be between those ranges.
    /// </remarks>
    /// <param name="fValue">[IN] Floating point number to be converted.</param>
    /// <returns>
    /// Integer value obtained.
    /// </returns>
    template<typename IntegerT>
    static IntegerT ToInteger(const float_q fValue)
    {
        IntegerT outInteger;

        // Checks whether both input types have the same size
        QE_ASSERT_ERROR( sizeof(fValue) == sizeof(outInteger), "Input float and output integer must have the same size in memory" );

        #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

            const IntegerT LOWEST_EXPONENT_BIT_POS = 23;
            const IntegerT EXPONENT = 127 + LOWEST_EXPONENT_BIT_POS;
            const float_q MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  8388608; // Maximum convertible integer value = 2^23
            const float_q MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -4194304; // Maximum convertible integer negative value = 2^22

        #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

            const IntegerT LOWEST_EXPONENT_BIT_POS = 52;
            const IntegerT EXPONENT = 1023 + LOWEST_EXPONENT_BIT_POS;
            const float_q MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  4503599627370496l; // Maximum convertible integer value = 2^52
            const float_q MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -2251799813685248l; // Maximum convertible integer negative value = 2^51

        #endif

        if(fValue > MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED ||
           fValue < MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED)
        {
            // [TODO] Thund: Maybe, using assertions for notifying this fact is too hard since a user could think that
            //               using this this method is worth for the majority of the cases, although several values are not inside the appropiate ranges.
            //               In that case, getting assertion failures would be very annoying.

            // Checks whether the value is too big to be converted this way
            QE_ASSERT_WARNING( fValue <= MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED, "Input value is too big to be converted this way" );

            // Checks whether the value is too big (when it's negative) to be converted this way
            QE_ASSERT_WARNING( fValue >= MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED, "Input value is too big to be converted this way" );

            // When the value is out of the convertible bounds (using fast conversion), standard conversion is used
            outInteger = scast_q(fValue, IntegerT);
        }
        else
        {
            // Ambiguous type to treat the same bit strip as integer and floating point types
            // Note: The type change is not immediate, it has memory reading/writing cost
            union IntegerOrFloatUnion
            {
                float_q _float;
                IntegerT _integer;
            };

            IntegerOrFloatUnion biasValue;  // Used to manipulate the float mantissa
            IntegerOrFloatUnion finalValue; // Used to store operations results

            finalValue._float = fValue;

            if(finalValue._integer < 0)
                biasValue._integer = (EXPONENT << LOWEST_EXPONENT_BIT_POS) + (IntegerT(1) << (LOWEST_EXPONENT_BIT_POS - IntegerT(1))); // Equivalent to 1 x 2 ^ LOWEST_EXPONENT_BIT_POS + 1 x 2 ^ (LOWEST_EXPONENT_BIT_POS - 1)
            else
                biasValue._integer = EXPONENT << LOWEST_EXPONENT_BIT_POS; // Equivalent to 1 x 2 ^ LOWEST_EXPONENT_BIT_POS

            finalValue._float   += biasValue._float; // The mantissa is displaced N bits to the right (where N is bias exponent - original exponent). The exponent now equals bias exponent.
            finalValue._integer -= biasValue._integer; // Removes the exponent bits so only the displaced

            outInteger = finalValue._integer;
        }

        return outInteger;
    }

    /// <summary>
    /// Removes the fractional part of a floating point number and returns the result as output parameter.
    /// </summary>
    /// <remarks>
    /// No rounding off is performed.
    /// </remarks>
    /// <param name="fValue">[IN] Value to be truncated.</param>
    /// <returns>
    /// Value without fractional part.
    /// </returns>
    static float_q Truncate(const float_q fValue);

    /// <summary>
    /// This method clamps the input value to lie within the range [Min..Max].
    /// </summary>
    /// <remarks>
    /// No tolerance is used for this operation.
    /// </remarks>
    /// <param name="fValue">[IN] A floating point value; the value to be clamped, if neccesary.</param>
    /// <param name="fMin">[IN] A floating point value; the minimum value into the range.</param>
    /// <param name="fMax">[IN] A floating point value; the maximum value into the range.</param>
    /// <returns>
    /// The clamped value.
    /// </returns>
    static float_q Clamp(const float_q fValue, const float_q fMin, const float_q fMax);

    /// <summary>
    /// Inverts the order of bytes which compound a floating point number and returns the result as output parameter.
    /// </summary>
    /// <remarks>
    /// A 32-bits floating point number whose value equals to 0xAABBCCDD will be
    /// transformed to 0xDDCCBBAA, for example.
    /// </remarks>
    /// <param name="fValue">[IN] The value whose bytes are to be swapped.</param>
    /// <returns>
    /// The transformed value.
    /// </returns>
    static float_q SwapEndianess(const float_q fValue);

    /// <summary>
    /// Indicates whether the floating point number has negative sign.
    /// </summary>
    /// <remarks>
    /// Zero is neither positive nor negative.
    /// </remarks>
    /// <param name="fValue">[IN] The value whose sign is going to be checked.</param>
    /// <returns>
    /// If the number is lower than zero, it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsNegative(const float_q fValue);

    /// <summary>
    /// Indicates whether the number is positive or not.
    /// </summary>
    /// <remarks>
    /// Zero is neither positive nor negative.
    /// </remarks>
    /// <param name="fValue">[IN] The value whose sign is going to be checked.</param>
    /// <returns>
    /// If the number is greater than zero, it returns True. Otherwise, it returns False.
    /// </returns>
    static bool IsPositive(const float_q fValue);

    /// <summary>
    /// Copies a floating point number sign to another one.
    /// </summary>
    /// <param name="fSignedValue">[IN] A floating point number whose sign is to be copied.</param>
    /// <param name="fValueToCopyTo">[OUT] A floating point number whose sign is to be replaced.</param>
    static void CopySign(const float_q fSignedValue, float_q &fValueToCopyTo);

    /// <summary>
    /// Calculates the absolute value of the provided floating point number.
    /// </summary>
    /// <param name="fValue">[IN] A floating point number whose absolute value is wanted.</param>
    /// <returns>
    /// If the provided number is greater or equals to zero, it returns the same number,
    /// otherwise it returns the same number but with opposite sign.
    /// </returns>
    static float_q Abs(const float_q fValue);

};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQFLOAT__
