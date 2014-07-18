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

#include "SQAngle.h"

#include "MathDefinitions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |               ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

#if   QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE

    const float_q SQAngle::_15           = 15.0f;
    const float_q SQAngle::_30           = 30.0f;
    const float_q SQAngle::_45           = 45.0f;
    const float_q SQAngle::_60           = 60.0f;
    const float_q SQAngle::_90           = 90.0f;
    const float_q SQAngle::_180          = 180.0f;
    const float_q SQAngle::_270          = 270.0f;
    const float_q SQAngle::_360          = 360.0f;
    const float_q SQAngle::_HalfPi       = (float_q) (PI_Q * 0.5);
    const float_q SQAngle::_QuarterPi    = (float_q) (PI_Q * 0.25);
    const float_q SQAngle::_ThirdPi      = (float_q) (PI_Q / 3.0);
    const float_q SQAngle::_2Pi          = (float_q) (PI_Q * 2.0);
    const float_q SQAngle::_Pi           = PI_Q;
    const float_q SQAngle::_3HalfsPi     = (float_q) (PI_Q * 1.5);

    const float_q SQAngle::DegreesPerRadian  = (float_q) (180.0 / PI_Q);
    const float_q SQAngle::RadiansPerDegree  = (float_q) (PI_Q / 180.0);

#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE

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
    const float_q SQAngle::_ThirdPi      = PI_Q / 3.0;
    const float_q SQAngle::_2Pi          = PI_Q * 2.0;
    const float_q SQAngle::_Pi           = PI_Q;
    const float_q SQAngle::_3HalfsPi     = PI_Q * 1.5;

    const float_q SQAngle::DegreesPerRadian  = 180.0 / PI_Q;
    const float_q SQAngle::RadiansPerDegree  = PI_Q / 180.0;

#endif


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float_q SQAngle::DegreesToRadians(const float_q &fDegrees)
{

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    // This workaround is necessary due to an unacceptable loss of precision
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
    return (float_q) (f64_q(fDegrees) * 4.0 * atan_q(1.0) / 180.0);
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    return fDegrees * SQAngle::RadiansPerDegree;
#endif

}

float_q SQAngle::RadiansToDegrees(const float_q &fRadians)
{

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    // This workaround is necessary due to an unacceptable loss of precision
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
    return (float_q) (f64_q(fRadians) * 180.0 / (4.0 * atan_q(1.0)));
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    return fRadians * SQAngle::DegreesPerRadian;
#endif

}

float_q SQAngle::Truncate(const float_q &fAngle)
{

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    return fmod_q(fAngle, SQAngle::_2Pi);  
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    return fmod_q(fAngle, SQAngle::_360);
#endif

}

float_q SQAngle::CountRevolutions(const float_q &fAngle)
{
    const float_q COMPLETE_REVOLUTION =
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
            SQAngle::_2Pi;
        #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            SQAngle::_360;
        #endif

    return fAngle / COMPLETE_REVOLUTION;
}

float_q SQAngle::CountCompleteRevolutions(const float_q &fAngle)
{
    const float_q COMPLETE_REVOLUTION =
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
            SQAngle::_2Pi;
        #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            SQAngle::_360;
        #endif

    return SQFloat::Truncate(fAngle / COMPLETE_REVOLUTION);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
