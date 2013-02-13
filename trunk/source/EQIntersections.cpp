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

#include "EQIntersections.h"

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
EQIntersections::TNameValuePair EQIntersections::sm_arValueName[] =
    {
        std::pair<string_q, EQIntersections::EnumType>(QE_L("None"),    EQIntersections::E_None),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("One"), EQIntersections::E_One),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("Two"), EQIntersections::E_Two),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("More"), EQIntersections::E_More),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("Infinite"),    EQIntersections::E_Infinite)
    };

EQIntersections::TNameValueMap EQIntersections::sm_mapValueName(
        EQIntersections::sm_arValueName ,
        &EQIntersections::sm_arValueName[0] + sizeof(EQIntersections::sm_arValueName) / sizeof(EQIntersections::sm_arValueName[0])
    );


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
