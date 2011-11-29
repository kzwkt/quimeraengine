// [TERMS&CONDITIONS]

#ifndef __MATHDEFINITIONS__
#define __MATHDEFINITIONS__

#include "Configuration.h"
#include "SQFloat.h"

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
// Pi: Defines how much accurate the mathematical Pi value is.
// --------------------------------------------------------------------------------------------------------
const float_q PI_Q = SQFloat::_4 * atan(SQFloat::_1);

// --------------------------------------------------------------------------------------------------------
// 1/Pi: Defines how much accurate the mathematical Pi value is to calculate its inverse.
// --------------------------------------------------------------------------------------------------------

const float_q INVERSE_PI_Q = SQFloat::_1 / PI_Q;
    
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __MATHDEFINITIONS__
