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

#ifndef __MATHDEFINITIONS__
#define __MATHDEFINITIONS__

#include "Configuration.h"
#include "SQFloat.h"
#include <math.h>

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// --------------------------------------------------------------------------------------------------------
// Trigonometric functions: Wrappers for all the trigonometric functions provided by the runtime libraries.
// --------------------------------------------------------------------------------------------------------
#define sin_q(fRadians)  sin(fRadians)
#define sinh_q(fRadians) sinh(fRadians)
#define cos_q(fRadians)  cos(fRadians)
#define cosh_q(fRadians) cosh(fRadians)
#define tan_q(fRadians)  tan(fRadians)
#define tanh_q(fRadians) tanh(fRadians)
#define asin_q(fRadians) asin(fRadians)
#define acos_q(fRadians) acos(fRadians)
#define atan_q(fRadians) atan(fRadians)
#define atan2_q(fY, fX)  atan2(fY, fX)

// --------------------------------------------------------------------------------------------------------
// Other mathematical functions: Wrappers for non-classified mathematic functions provided by the runtime libraries.
// --------------------------------------------------------------------------------------------------------
#define exp_q(fValue)   exp(fValue)
#define pow_q(fValue,   exponent) pow(fValue, exponent)
#define log_q(fValue)   log(fValue)
#define log10_q(fValue) log10(fValue)
#define sqrt_q(fValue)  sqrt(fValue)

#ifdef QE_COMPILER_MSVC
    #if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
        #define hypot_q(fX, fY) _hypotf(fX, fY)
    #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
        #define hypot_q(fX, fY) _hypot(fX, fY)
    #endif
#elif defined(QE_COMPILER_GCC)
    #define hypot_q(fX, fY) hypot(fX, fY)
#endif

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    #define fmod_q(fX, fY) fmodf(fX, fY) // To improve the compatibility, we prefer fmodf to fmod overloaded version
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    #define fmod_q(fX, fY) fmod(fX, fY)
#endif

// --------------------------------------------------------------------------------------------------------
// Pi: Defines how much accurate the mathematical Pi value is.
// --------------------------------------------------------------------------------------------------------
const float_q PI_Q = (float_q) (4.0 * atan_q(1.0));

// --------------------------------------------------------------------------------------------------------
// 1/Pi: Defines how much accurate the mathematical Pi value is to calculate its inverse.
// --------------------------------------------------------------------------------------------------------
const float_q INVERSE_PI_Q = (float_q) (1.0 / 4.0 * atan_q(1.0));

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __MATHDEFINITIONS__
