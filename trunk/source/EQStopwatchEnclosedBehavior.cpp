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

#include "EQStopwatchEnclosedBehavior.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

EQStopwatchEnclosedBehavior::TNameValuePair EQStopwatchEnclosedBehavior::sm_arValueName[] =
    {
        std::pair<string_q, EQStopwatchEnclosedBehavior::EnumType>(QE_L("Clamped"),    EQStopwatchEnclosedBehavior::E_Clamped),
        std::pair<string_q, EQStopwatchEnclosedBehavior::EnumType>(QE_L("Proportional"),    EQStopwatchEnclosedBehavior::E_Proportional),
        std::pair<string_q, EQStopwatchEnclosedBehavior::EnumType>(QE_L("Cyclic"),    EQStopwatchEnclosedBehavior::E_Cyclic),
    };

EQStopwatchEnclosedBehavior::TNameValueMap EQStopwatchEnclosedBehavior::sm_mapValueName(
        EQStopwatchEnclosedBehavior::sm_arValueName ,
        &EQStopwatchEnclosedBehavior::sm_arValueName[0] + sizeof(EQStopwatchEnclosedBehavior::sm_arValueName) / sizeof(EQStopwatchEnclosedBehavior::sm_arValueName[0])
    );

} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

