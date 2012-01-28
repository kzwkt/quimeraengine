// [TERMS&CONDITIONS]

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
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE

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

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE

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
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE

    const float_q SQFloat::Epsilon = 1e-6f;

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE

    const float_q SQFloat::Epsilon = 1e-12;

#endif

// Max / Min constants
#if   QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE

    const float_q SQFloat::MaxFloat_Q = 3.4028234e+38f; // 2 ^ 128
    const float_q SQFloat::MinFloat_Q = 1.7014118346046923173168730371588e-38f; // 2 ^ -127

#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE

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
}

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
