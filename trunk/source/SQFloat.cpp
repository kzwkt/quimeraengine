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

#include "SQFloat.h"

#include <cmath>
#include "StringsDefinitions.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |               ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

// Numbers
#if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

    const float_q SQFloat::_0   = 0.0f;
    const float_q SQFloat::_1   = 1.0f;
    const float_q SQFloat::_2   = 2.0f;
    const float_q SQFloat::_3   = 3.0f;
    const float_q SQFloat::_4   = 4.0f;
    const float_q SQFloat::_5   = 5.0f;
    const float_q SQFloat::_6   = 6.0f;
    const float_q SQFloat::_7   = 7.0f;
    const float_q SQFloat::_8   = 8.0f;
    const float_q SQFloat::_9   = 9.0f;
    const float_q SQFloat::_10  = 10.0f;
    const float_q SQFloat::_0_5 = 0.5f;
    const float_q SQFloat::_0_25 = 0.25f;

#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

    const float_q SQFloat::_0   = 0.0;
    const float_q SQFloat::_1   = 1.0;
    const float_q SQFloat::_2   = 2.0;
    const float_q SQFloat::_3   = 3.0;
    const float_q SQFloat::_4   = 4.0;
    const float_q SQFloat::_5   = 5.0;
    const float_q SQFloat::_6   = 6.0;
    const float_q SQFloat::_7   = 7.0;
    const float_q SQFloat::_8   = 8.0;
    const float_q SQFloat::_9   = 9.0;
    const float_q SQFloat::_10  = 10.0;
    const float_q SQFloat::_0_5 = 0.5;
    const float_q SQFloat::_0_25 = 0.25;

#endif

// Epsilon / Tolerance
#if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

    const float_q SQFloat::Epsilon = 1e-6f;

#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

    const float_q SQFloat::Epsilon = 1e-12;

#endif

// Max / Min constants
#if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

    const float_q SQFloat::MaxFloat_Q = 3.4028234e+38f; // 2 ^ 128
    const float_q SQFloat::MinFloat_Q = 1.7014118346046923173168730371588e-38f; // 2 ^ -127

#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

    const float_q SQFloat::MaxFloat_Q = 1.797693134862315e+308; // 2 ^ 1024
    const float_q SQFloat::MinFloat_Q = 8.9884656743115795386465259539451e-307; // 2 ^ -1023

#endif

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool SQFloat::IsNaN(const float_q fValue)
{
    // [REVIEW] Thund: Boost provides functions to check this
    return fValue != fValue;
}

bool SQFloat::IsInfinite(const float_q fValue)
{
    // [REVIEW] Thund: Boost provides functions to check this
    return SQFloat::IsLessThan(fValue, -SQFloat::MaxFloat_Q) || SQFloat::IsGreaterThan(fValue, SQFloat::MaxFloat_Q);
}

bool SQFloat::IsNanOrInfinite(const float_q fValue)
{
    return SQFloat::IsNaN(fValue) || SQFloat::IsInfinite(fValue);
}

bool SQFloat::AreEqual(const float_q fValueA, const float_q fValueB)
{
    return SQFloat::Abs(fValueA - fValueB) <= SQFloat::Epsilon;
}

bool SQFloat::AreEqual(const float_q fValueA, const float_q fValueB, const float_q fTolerance)
{
    // The tolerance provided must be equal to or greater than the system tolerance. If the tolerance is too small it could become useless.
    QE_ASSERT_WARNING(fTolerance >= SQFloat::Epsilon, "The tolerance provided must be equal to or greater than the system tolerance. If the tolerance is too small it could become useless");

    return SQFloat::Abs(fValueA - fValueB) <= fTolerance;
}

bool SQFloat::AreNotEqual(const float_q fValueA, const float_q fValueB)
{
    return SQFloat::Abs(fValueA - fValueB) > SQFloat::Epsilon;
}

bool SQFloat::AreNotEqual(const float_q fValueA, const float_q fValueB, const float_q fTolerance)
{
    return SQFloat::Abs(fValueA - fValueB) > fTolerance;
}

bool SQFloat::IsGreaterThan(const float_q fGreaterValue, const float_q fReferenceValue)
{
    // If subtraction result is positive, and is greater than Epsilon (are different numbers), the value is greater
    return (fGreaterValue - fReferenceValue) > SQFloat::Epsilon;
}

bool SQFloat::IsGreaterThan(const float_q fGreaterValue, const float_q fReferenceValue, const float_q fTolerance)
{
    // If subtraction result is positive, and is greater than Epsilon (are different numbers), the value is greater
    return (fGreaterValue - fReferenceValue) > fTolerance;
}

bool SQFloat::IsLessThan(const float_q fLowerValue, const float_q fReferenceValue)
{
    // If subtraction result is negative, and is lower than Epsilon (are different numbers), the value is lower
    return (fLowerValue - fReferenceValue) < -SQFloat::Epsilon;
}

bool SQFloat::IsLessThan(const float_q fLowerValue, const float_q fReferenceValue, const float_q fTolerance)
{
    // If subtraction result is negative, and is lower than Epsilon (are different numbers), the value is lower
    return (fLowerValue - fReferenceValue) < -fTolerance;
}

bool SQFloat::IsGreaterOrEquals(const float_q fGreaterOrEqualsValue, const float_q fReferenceValue)
{
    // If subtraction is greater or equals to -Epsilon, the value is greater or equals
    return (fGreaterOrEqualsValue - fReferenceValue) >= -SQFloat::Epsilon;
}

bool SQFloat::IsGreaterOrEquals(const float_q fGreaterOrEqualsValue, const float_q fReferenceValue, const float_q fTolerance)
{
    // If subtraction is greater or equals to -Epsilon, the value is greater or equals
    return (fGreaterOrEqualsValue - fReferenceValue) >= -fTolerance;
}

bool SQFloat::IsLessOrEquals(const float_q fLessOrEqualsValue, const float_q fReferenceValue)
{
    // If subtraction is lower or equals to Epsilon, the value is lower or equals
    return (fLessOrEqualsValue - fReferenceValue) <= SQFloat::Epsilon;
}

bool SQFloat::IsLessOrEquals(const float_q fLessOrEqualsValue, const float_q fReferenceValue, const float_q fTolerance)
{
    // If subtraction is lower or equals to Epsilon, the value is lower or equals
    return (fLessOrEqualsValue - fReferenceValue) <= fTolerance;
}

bool SQFloat::IsZero(const float_q fValue)
{
    return SQFloat::AreEqual(fValue, SQFloat::_0);
}

bool SQFloat::IsZero(const float_q fValue, const float_q fTolerance)
{
    return SQFloat::AreEqual(fValue, SQFloat::_0, fTolerance);
}

bool SQFloat::IsNotZero(const float_q fValue)
{
    return SQFloat::AreNotEqual(fValue, SQFloat::_0);
}

bool SQFloat::IsNotZero(const float_q fValue, const float_q fTolerance)
{
    return SQFloat::AreNotEqual(fValue, SQFloat::_0, fTolerance);
}

float_q SQFloat::Truncate(const float_q fValue)
{
    return fValue >= SQFloat::_0 ? floor(fValue) : ceil(fValue);
}

float_q SQFloat::Clamp(const float_q fValue, const float_q fMin, const float_q fMax)
{
    const float_q CAMPLED_VALUE = (fValue > fMax) ?  fMax :
                                                        (fValue < fMin) ?  fMin :
                                                                        fValue;
    return CAMPLED_VALUE;
}

float_q SQFloat::SwapEndianess(const float_q fValue)
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

bool SQFloat::IsNegative(const float_q fValue)
{
    return SQFloat::IsLessThan(fValue, SQFloat::_0);
}

bool SQFloat::IsPositive(const float_q fValue)
{
    return SQFloat::IsGreaterThan(fValue, SQFloat::_0);
}

void SQFloat::CopySign(const float_q fSignedValue, float_q &fValueToCopyTo)
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

float_q SQFloat::Abs(const float_q fValue)
{
    #if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

        return fabsf(fValue);

    #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

        return fabsl(fValue);

    #endif
}


} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
