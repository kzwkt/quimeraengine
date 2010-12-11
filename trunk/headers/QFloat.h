// [TERMS&CONDITIONS]

#ifndef __QFLOAT__
#define __QFLOAT__

#include <string>

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
/// Helper class that offers functionality related to floating point types.
/// Use these constants and static methods extensively in your code, as far as you can.
/// </summary>
class QDllExport QFloat
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
    /// The fraction 1/2, as a floating point type.
    /// </summary>
    static const float_q _0_5;

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

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
    QFloat();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Checks if the floating point value's state is NaN. That kind of value is undefined or non-representable, and it's said 
    /// it isn't a number (NaN = Not a Number). Every time you use functions like acos, asin or atan2, you should check the result 
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
    /// Checks if the floating point value's state is Infinite. That kind of value is non-representable and appears as an arithmetic 
    /// operation result that overflows the floating point type bounds. Every time you use functions like tan, you should check the result 
    /// value.
    /// </summary>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is infinite, then returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsInfinite(const float_q &fValue)
    {
        // [REVIEW] Thund: Boost provides functions to check this
        return (fValue > -QFloat::MaxFloat_Q) && (fValue < QFloat::MaxFloat_Q);
    }

    /// <summary>
    /// Checks if the floating point value's state is one of the special ones described in IEEE specification.
    /// That kind of values are undefined or non-representable (like infinite).
    /// </summary>
    /// <param name="fValue">[IN] A floating point number.</param>
    /// <returns>
    /// If the value is infinite or is not a number, then returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsNanOrInfinite(const float_q &fValue)
    {
        return QFloat::IsNaN(fValue) || QFloat::IsInfinite(fValue);
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
    inline static bool AreEquals(const float_q &fValueA, const float_q &fValueB)
    {
        return abs(fValueA - fValueB) <= QFloat::Epsilon;
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
    inline static bool AreNotEquals(const float_q &fValueA, const float_q &fValueB)
    {
        return abs(fValueA - fValueB) > QFloat::Epsilon;
    }

    /// <summary>
    /// Checks whether a floating point number equals zero or is close to zero, taking into account the system tolerance 
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">The floating point number to be compared.</param>
    /// <returns>
    /// If the value equals zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsZero(const float_q &fValue)
    {
        return QFloat::AreEquals(fValue, QFloat::_0);
    }

    /// <summary>
    /// Checks whether a floating point number doesn't equal zero or is close to zero, taking into account the system tolerance 
    /// constant (Epsilon).
    /// </summary>
    /// <param name="fValue">The floating point number to be compared.</param>
    /// <returns>
    /// If the value doesn't equal zero, then it returns True. Otherwise, it returns False.
    /// </returns>
    inline static bool IsNotZero(const float_q &fValue)
    {
        return QFloat::AreNotEquals(fValue, QFloat::_0);
    }

    /// <summary>
    /// Converts the floating point number to a readable character string that represents it.
    /// </summary>
    /// <param name="fValue">The floating point number to be converted.</param>
    /// <returns>
    /// The string that represents the number (using a dot as decimal separator).
    /// </returns>
    static string_q ToString(const float_q &fValue);
};

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QFLOAT__
