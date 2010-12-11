// [TERMS&CONDITIONS]

#include "QVF32.h"

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

string_q QVF32::ToString(const vf32_q &inPack)
{
    float_q fFirst  = QFloat::_0;
    float_q fSecond = QFloat::_0;
    float_q fThird  = QFloat::_0;
    float_q fFourth = QFloat::_0;

    QVF32::Unpack(inPack, fFirst, fSecond, fThird, fFourth);

    return QE_L("VF(") + QFloat::ToString(fFirst)  + QE_L(", ") + 
                         QFloat::ToString(fSecond) + QE_L(", ") +
                         QFloat::ToString(fThird)  + QE_L(", ") +
                         QFloat::ToString(fFourth) + QE_L(")");
}


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
