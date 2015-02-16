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

#ifndef __STRINGSDEFINITIONS__
#define __STRINGSDEFINITIONS__

#include "DataTypesDefinitions.h"

#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    #include <string>
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    #include "QCharUnicode.h"
    #include "QStringUnicode.h"
#endif

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

// --------------------------------------------------------------------------------------------------------
// Char type: Defines the char width used throughout the engine, depending on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    typedef char char_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    typedef QCharUnicode char_q;
#else
    typedef char char_q;
#endif


// --------------------------------------------------------------------------------------------------------
// String type: Defines the string class used throughout the engine, depending on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    typedef std::string string_q;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    typedef QStringUnicode string_q;
#endif


// --------------------------------------------------------------------------------------------------------
// Literals prefix: Specifies if character string literals must be prefixed with the wide-char token, depending
// on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
    #define QE_L(str) str
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
    #define QE_L(str) str
#endif


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __STRINGSDEFINITIONS__
