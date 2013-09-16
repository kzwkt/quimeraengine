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

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "SQFloat.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace DataTypes
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  CONSTANTS INITIALIZATION  |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
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
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

string_q SQFloat::ToString(const float_q &fValue)
{
    string_q strOut = boost::lexical_cast<string_q>(fValue);
	return strOut;
  
// Is this better? [SMELL] Thund:
//    template <class T> inline std::string stringify(T x)
//    {
//	    std::ostringstream o;
//	    o << x;
//	    return o.str();
//    }
}

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
