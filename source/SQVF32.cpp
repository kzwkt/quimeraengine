// [TERMS&CONDITIONS]

#include "SQVF32.h"

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
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

string_q SQVF32::ToString(const vf32_q &inPack)
{
    float_q fFirst  = SQFloat::_0;
    float_q fSecond = SQFloat::_0;
    float_q fThird  = SQFloat::_0;
    float_q fFourth = SQFloat::_0;

    SQVF32::Unpack(inPack, fFirst, fSecond, fThird, fFourth);

    return QE_L("VF(") + SQFloat::ToString(fFirst)  + QE_L(", ") + 
                         SQFloat::ToString(fSecond) + QE_L(", ") +
                         SQFloat::ToString(fThird)  + QE_L(", ") +
                         SQFloat::ToString(fFourth) + QE_L(")");
}


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
