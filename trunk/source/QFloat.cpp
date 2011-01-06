// [TERMS&CONDITIONS]

#include <sstream>

#include "QFloat.h"

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
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE

    const float_q QFloat::_0   = 0.0f;
    const float_q QFloat::_1   = 1.0f;
    const float_q QFloat::_2   = 2.0f;
    const float_q QFloat::_3   = 3.0f;
    const float_q QFloat::_4   = 4.0f;
    const float_q QFloat::_5   = 5.0f;
    const float_q QFloat::_6   = 6.0f;
    const float_q QFloat::_7   = 7.0f;
    const float_q QFloat::_8   = 8.0f;
    const float_q QFloat::_9   = 9.0f;
    const float_q QFloat::_10  = 10.0f;
    const float_q QFloat::_0_5 = 0.5f;

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE ||
      QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM

    const float_q QFloat::_0   = 0.0;
    const float_q QFloat::_1   = 1.0;
    const float_q QFloat::_2   = 2.0;
    const float_q QFloat::_3   = 3.0;
    const float_q QFloat::_4   = 4.0;
    const float_q QFloat::_5   = 5.0;
    const float_q QFloat::_6   = 6.0;
    const float_q QFloat::_7   = 7.0;
    const float_q QFloat::_8   = 8.0;
    const float_q QFloat::_9   = 9.0;
    const float_q QFloat::_10  = 10.0;
    const float_q QFloat::_0_5 = 0.5;

#endif

// Epsilon / Tolerance
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE

    const float_q QFloat::Epsilon = 1e-6f;

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE

    const float_q QFloat::Epsilon = 1e-12;

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM

    const float_q QFloat::Epsilon = 1e-18;

#endif

// Max / Min constants
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE

    const float_q QFloat::MaxFloat_Q = 3.4028234e+38f; // 2 ^ 128
    const float_q QFloat::MinFloat_Q = 1.7014118346046923173168730371588e-38f; // 2 ^ -127

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE

    const float_q QFloat::MaxFloat_Q = 1.797693134862315907729305190789e+308; // 2 ^ 1024
    const float_q QFloat::MinFloat_Q = 8.9884656743115795386465259539451e-307; // 2 ^ -1023

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_MAXIMUM

    const float_q QFloat::MaxFloat_Q = 1.189731495357231765085759326628e+4932; // 2 ^ 16384
    const float_q QFloat::MinFloat_Q = 5.94865747678615882542879663314e-4931; // 2 ^ -16383

#endif

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

string_q QFloat::ToString(const float_q &fValue)
{
    std::basic_ostringstream<char_q> ostr;
	ostr << fValue;
	return ostr.str();
}

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
