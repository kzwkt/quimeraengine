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

#include "EQFileOpenMode.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace IO
{
namespace FileSystem
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

EQFileOpenMode::TNameValuePair EQFileOpenMode::sm_arValueName[] =
    {
        std::pair<string_q, EQFileOpenMode::EnumType>(QE_L("Append"),            EQFileOpenMode::E_Append),
        std::pair<string_q, EQFileOpenMode::EnumType>(QE_L("Create"),            EQFileOpenMode::E_Create),
        std::pair<string_q, EQFileOpenMode::EnumType>(QE_L("CreateOrOverwrite"), EQFileOpenMode::E_CreateOrOverwrite),
        std::pair<string_q, EQFileOpenMode::EnumType>(QE_L("Open"),              EQFileOpenMode::E_Open),
        std::pair<string_q, EQFileOpenMode::EnumType>(QE_L("OpenOrCreate"),      EQFileOpenMode::E_OpenOrCreate),

    };

EQFileOpenMode::TNameValueMap EQFileOpenMode::sm_mapValueName(
        EQFileOpenMode::sm_arValueName ,
        &EQFileOpenMode::sm_arValueName[0] + sizeof(EQFileOpenMode::sm_arValueName) / sizeof(EQFileOpenMode::sm_arValueName[0])
    );


} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
