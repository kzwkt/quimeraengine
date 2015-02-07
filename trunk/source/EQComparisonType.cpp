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

#include "EQComparisonType.h"


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

const char* EQComparisonType::sm_arStrings[] = { "BinaryCaseSensitive", 
                                                 "BinaryCaseInsensitive", 
                                                 "CanonicalCaseSensitive", 
                                                 "CanonicalCaseInsensitive"};

const EQComparisonType::EnumType EQComparisonType::sm_arValues[] = { EQComparisonType::E_BinaryCaseSensitive,
                                                                     EQComparisonType::E_BinaryCaseInsensitive,
                                                                     EQComparisonType::E_CanonicalCaseSensitive,
                                                                     EQComparisonType::E_CanonicalCaseInsensitive};


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

unsigned int EQComparisonType::_GetNumberOfValues()
{
    return sizeof(sm_arValues) / sizeof(EQComparisonType::EnumType);
}


} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

