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

#include "EQNormalizationForm.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

EQNormalizationForm::TNameValuePair EQNormalizationForm::sm_arValueName[] =
    {
        std::pair<string_q, EQNormalizationForm::EnumType>(QE_L("C"),    EQNormalizationForm::E_C),
        std::pair<string_q, EQNormalizationForm::EnumType>(QE_L("D"),    EQNormalizationForm::E_D),
        std::pair<string_q, EQNormalizationForm::EnumType>(QE_L("KC"),    EQNormalizationForm::E_KC),
        std::pair<string_q, EQNormalizationForm::EnumType>(QE_L("KD"),    EQNormalizationForm::E_KD),
    };

EQNormalizationForm::TNameValueMap EQNormalizationForm::sm_mapValueName(
        EQNormalizationForm::sm_arValueName ,
        &EQNormalizationForm::sm_arValueName[0] + sizeof(EQNormalizationForm::sm_arValueName) / sizeof(EQNormalizationForm::sm_arValueName[0])
    );

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
