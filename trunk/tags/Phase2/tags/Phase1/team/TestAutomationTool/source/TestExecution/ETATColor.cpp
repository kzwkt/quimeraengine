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

#include "TestExecution/ETATColor.h"

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

ETATColor::TNameValuePair ETATColor::sm_arValueName[] =
    {
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Black"),  ETATColor::E_Black),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_White"),  ETATColor::E_White),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Red"),    ETATColor::E_Red),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Yellow"), ETATColor::E_Yellow),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Blue"),   ETATColor::E_Blue),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Green"),  ETATColor::E_Green),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Purple"), ETATColor::E_Purple),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Grey"),   ETATColor::E_Grey),
    };

ETATColor::TNameValueMap ETATColor::sm_mapValueName(
        ETATColor::sm_arValueName ,
        &ETATColor::sm_arValueName[0] + sizeof(ETATColor::sm_arValueName) / sizeof(ETATColor::sm_arValueName[0])
    );

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
