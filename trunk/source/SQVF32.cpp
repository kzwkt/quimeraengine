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
