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

const char* EQTextEncoding::sm_arStrings[] = { "ASCII", 
                                               "ISO-8859-1", 
                                               "UTF-8", 
                                               "UTF-16", 
                                               "UTF-32", 
                                               "UTF-16 BE", 
                                               "UTF-16 LE", 
                                               "UTF-32 BE", 
                                               "UTF-32 LE"};

const EQTextEncoding::EnumType EQTextEncoding::sm_arValues[] = { EQTextEncoding::E_ASCII,
                                                                 EQTextEncoding::E_ISO88591,
                                                                 EQTextEncoding::E_UTF8,
                                                                 EQTextEncoding::E_UTF16,
                                                                 EQTextEncoding::E_UTF32,
                                                                 EQTextEncoding::E_UTF16BE,
                                                                 EQTextEncoding::E_UTF16LE,
                                                                 EQTextEncoding::E_UTF32BE,
                                                                 EQTextEncoding::E_UTF32LE};


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

unsigned int EQTextEncoding::_GetNumberOfValues()
{
    return sizeof(sm_arValues) / sizeof(EQTextEncoding::EnumType);
}


} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis