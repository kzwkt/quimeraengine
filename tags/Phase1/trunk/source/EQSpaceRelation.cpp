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

#include "EQSpaceRelation.h"

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
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
EQSpaceRelation::TNameValuePair EQSpaceRelation::sm_arValueName[] =
    {
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("Contained"),    EQSpaceRelation::E_Contained),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("PositiveSide"), EQSpaceRelation::E_PositiveSide),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("NegativeSide"), EQSpaceRelation::E_NegativeSide),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("BothSides"),    EQSpaceRelation::E_BothSides)
    };

EQSpaceRelation::TNameValueMap EQSpaceRelation::sm_mapValueName(
        EQSpaceRelation::sm_arValueName ,
        &EQSpaceRelation::sm_arValueName[0] + sizeof(EQSpaceRelation::sm_arValueName) / sizeof(EQSpaceRelation::sm_arValueName[0])
    );

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
