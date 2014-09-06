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

#include "EQAssertionType.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{

EQAssertionType::TNameValuePair EQAssertionType::sm_arValueName[] =
    {
        std::pair<string_q, EQAssertionType::EnumType>(QE_L("Deprecation"), EQAssertionType::E_Deprecation),
        std::pair<string_q, EQAssertionType::EnumType>(QE_L("Warning"),     EQAssertionType::E_Warning),
        std::pair<string_q, EQAssertionType::EnumType>(QE_L("Error"),       EQAssertionType::E_Error),
    };

EQAssertionType::TNameValueMap EQAssertionType::sm_mapValueName(
        EQAssertionType::sm_arValueName ,
        &EQAssertionType::sm_arValueName[0] + sizeof(EQAssertionType::sm_arValueName) / sizeof(EQAssertionType::sm_arValueName[0])
    );

} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

