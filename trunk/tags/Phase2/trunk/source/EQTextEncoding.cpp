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

#include "EQTextEncoding.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
EQTextEncoding::TNameValuePair EQTextEncoding::sm_arValueName[] =
    {
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("ASCII"),         EQTextEncoding::E_ASCII),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("ISO 8859-1"),    EQTextEncoding::E_ISO88591),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("UTF-8"),         EQTextEncoding::E_UTF8),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("UTF-16"),        EQTextEncoding::E_UTF16),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("UTF-32"),        EQTextEncoding::E_UTF32),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("UTF-16 BE"),     EQTextEncoding::E_UTF16BE),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("UTF-16 LE"),     EQTextEncoding::E_UTF16LE),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("UTF-32 BE"),     EQTextEncoding::E_UTF32BE),
        std::pair<string_q, EQTextEncoding::EnumType>(QE_L("UTF-32 LE"),     EQTextEncoding::E_UTF32LE),
    };

EQTextEncoding::TNameValueMap EQTextEncoding::sm_mapValueName(
        EQTextEncoding::sm_arValueName ,
        &EQTextEncoding::sm_arValueName[0] + sizeof(EQTextEncoding::sm_arValueName) / sizeof(EQTextEncoding::sm_arValueName[0])
    );


} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis