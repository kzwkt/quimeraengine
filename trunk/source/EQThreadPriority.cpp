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

#include "EQThreadPriority.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Threading
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

EQThreadPriority::TNameValuePair EQThreadPriority::sm_arValueName[] =
    {
        std::pair<string_q, EQThreadPriority::EnumType>(QE_L("Lowest"),  EQThreadPriority::E_Lowest),
        std::pair<string_q, EQThreadPriority::EnumType>(QE_L("Low"),     EQThreadPriority::E_Low),
        std::pair<string_q, EQThreadPriority::EnumType>(QE_L("Normal"),  EQThreadPriority::E_Normal),
        std::pair<string_q, EQThreadPriority::EnumType>(QE_L("High"),    EQThreadPriority::E_High),
        std::pair<string_q, EQThreadPriority::EnumType>(QE_L("Highest"), EQThreadPriority::E_Highest),
    };

EQThreadPriority::TNameValueMap EQThreadPriority::sm_mapValueName(
        EQThreadPriority::sm_arValueName ,
        &EQThreadPriority::sm_arValueName[0] + sizeof(EQThreadPriority::sm_arValueName) / sizeof(EQThreadPriority::sm_arValueName[0])
    );

} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
