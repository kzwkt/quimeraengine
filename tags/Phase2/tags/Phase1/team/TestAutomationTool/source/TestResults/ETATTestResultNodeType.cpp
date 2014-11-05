//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "TestResults/ETATTestResultNodeType.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

ETATTestResultNodeType::TNameValuePair ETATTestResultNodeType::sm_arValueName[] =
    {
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Result"), ETATTestResultNodeType::E_Result),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Case"),   ETATTestResultNodeType::E_Case),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Suite"),  ETATTestResultNodeType::E_Suite),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Module"), ETATTestResultNodeType::E_Module),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Root"),   ETATTestResultNodeType::E_Root),
    };

ETATTestResultNodeType::TNameValueMap ETATTestResultNodeType::sm_mapValueName(
        ETATTestResultNodeType::sm_arValueName ,
        &ETATTestResultNodeType::sm_arValueName[0] + sizeof(ETATTestResultNodeType::sm_arValueName) / sizeof(ETATTestResultNodeType::sm_arValueName[0])
    );

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
