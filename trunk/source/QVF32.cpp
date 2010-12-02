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

std::string QVF32::ToString(const vf32_q &inPack)
{
    float_q fFirst  = QFloat::_0;
    float_q fSecond = QFloat::_0;
    float_q fThird  = QFloat::_0;
    float_q fFourth = QFloat::_0;

    QVF32::Unpack(inPack, fFirst, fSecond, fThird, fFourth);

    std::string strHead = "VF(";

    return strHead + QFloat::ToString(fFirst) + ", " + 
                     QFloat::ToString(fSecond) + ", " +
                     QFloat::ToString(fThird) + ", " +
                     QFloat::ToString(fFourth) + ")";
}


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
