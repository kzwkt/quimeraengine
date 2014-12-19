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

#include "EQFileSystemError.h"


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

EQFileSystemError::TNameValuePair EQFileSystemError::sm_arValueName[] =
    {
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("Success"),          EQFileSystemError::E_Success),
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("Unknown"),          EQFileSystemError::E_Unknown),
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("DoesNotExist"),     EQFileSystemError::E_DoesNotExist),
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("FileIsTooLarge"),   EQFileSystemError::E_FileIsTooLarge),
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("NameIsTooLong"),    EQFileSystemError::E_NameIsTooLong),
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("NoSpaceInDevice"),  EQFileSystemError::E_NoSpaceInDevice),
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("NoPermissions"),    EQFileSystemError::E_NoPermissions),
        std::pair<string_q, EQFileSystemError::EnumType>(QE_L("AlreadyExists"),    EQFileSystemError::E_AlreadyExists),
    };

EQFileSystemError::TNameValueMap EQFileSystemError::sm_mapValueName(
        EQFileSystemError::sm_arValueName ,
        &EQFileSystemError::sm_arValueName[0] + sizeof(EQFileSystemError::sm_arValueName) / sizeof(EQFileSystemError::sm_arValueName[0])
    );


} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
