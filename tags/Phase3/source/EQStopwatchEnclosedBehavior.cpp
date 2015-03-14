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

const char* EQStopwatchEnclosedBehavior::sm_arStrings[] = { "Clamped", 
                                                            "Proportional", 
                                                            "Cyclic"};

const EQStopwatchEnclosedBehavior::EnumType EQStopwatchEnclosedBehavior::sm_arValues[] = { EQStopwatchEnclosedBehavior::E_Clamped,
                                                                                           EQStopwatchEnclosedBehavior::E_Proportional,
                                                                                           EQStopwatchEnclosedBehavior::E_Cyclic};


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

unsigned int EQStopwatchEnclosedBehavior::_GetNumberOfValues()
{
    return sizeof(sm_arValues) / sizeof(EQStopwatchEnclosedBehavior::EnumType);
}


} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

