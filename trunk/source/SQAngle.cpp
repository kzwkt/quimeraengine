// [TERMS&CONDITIONS]

#include "SQAngle.h" 

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  CONSTANTS INITIALIZATION  |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
        
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE

    const float_q SQAngle::_15           = 15.0f;
    const float_q SQAngle::_30           = 30.0f;
    const float_q SQAngle::_45           = 45.0f;
    const float_q SQAngle::_60           = 60.0f;
    const float_q SQAngle::_90           = 90.0f;
    const float_q SQAngle::_180          = 180.0f;
    const float_q SQAngle::_270          = 270.0f;
    const float_q SQAngle::_360          = 360.0f;
    const float_q SQAngle::_HalfPi       = PI_Q * 0.5f;
    const float_q SQAngle::_QuarterPi    = PI_Q * 0.25f;
    const float_q SQAngle::_ThridPi      = PI_Q / 3.0f;
    const float_q SQAngle::_2Pi          = PI_Q * 2.0f;
    const float_q SQAngle::_Pi           = PI_Q;
    const float_q SQAngle::_3HalfsPi     = PI_Q * 1.5f;

    const float_q SQAngle::DegreesPerRadian  = 180.0f / PI_Q;
    const float_q SQAngle::RadiansPerDegree  = PI_Q / 180.0f;

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE

    const float_q SQAngle::_15           = 15.0;
    const float_q SQAngle::_30           = 30.0;
    const float_q SQAngle::_45           = 45.0;
    const float_q SQAngle::_60           = 60.0;
    const float_q SQAngle::_90           = 90.0;
    const float_q SQAngle::_180          = 180.0;
    const float_q SQAngle::_270          = 270.0;
    const float_q SQAngle::_360          = 360.0;
    const float_q SQAngle::_HalfPi       = PI_Q * 0.5;
    const float_q SQAngle::_QuarterPi    = PI_Q * 0.25;
    const float_q SQAngle::_ThridPi      = PI_Q / 3.0;
    const float_q SQAngle::_2Pi          = PI_Q * 2.0;
    const float_q SQAngle::_Pi           = PI_Q;
    const float_q SQAngle::_3HalfsPi     = PI_Q * 1.5;

    const float_q SQAngle::DegreesPerRadian  = 180.0 / PI_Q;
    const float_q SQAngle::RadiansPerDegree  = PI_Q / 180.0;

#endif


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
