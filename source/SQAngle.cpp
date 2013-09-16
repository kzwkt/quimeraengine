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


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
