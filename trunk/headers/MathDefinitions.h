// [TERMS&CONDITIONS]

#ifndef __MATHDEFINITIONS__
#define __MATHDEFINITIONS__

#include "Configuration.h"
#include "SQFloat.h"
#include <math.h>

using namespace Kinesis::QuimeraEngine::Core::Configuration;
using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

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
    #if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
        #define hypot_q(fX, fY) _hypotf(fX, fY)
    #elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
        #define hypot_q(fX, fY) _hypot(fX, fY)
    #endif
#elif defined(QE_COMPILER_GCC)
    #define hypot_q(fX, fY) hypot(fX, fY)
#endif

#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
	#define fmod_q(fX, fY) fmodf(fX, fY) // To improve the compatibility, we prefer fmodf to fmod overloaded version
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
	#define fmod_q(fX, fY) fmod(fX, fY)
#endif

// --------------------------------------------------------------------------------------------------------
// Pi: Defines how much accurate the mathematical Pi value is.
// --------------------------------------------------------------------------------------------------------
const float_q PI_Q = SQFloat::_4 * atan_q(SQFloat::_1);

// --------------------------------------------------------------------------------------------------------
// 1/Pi: Defines how much accurate the mathematical Pi value is to calculate its inverse.
// --------------------------------------------------------------------------------------------------------
const float_q INVERSE_PI_Q = SQFloat::_1 / PI_Q;

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __MATHDEFINITIONS__
