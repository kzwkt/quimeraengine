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

#include "ETATTestType.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Test
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
    
ETATTestType::TNameValuePair ETATTestType::sm_arValueName[] =
    {
        std::pair<wxString, ETATTestType::EnumType>(wxT("UnitTest"),    ETATTestType::E_UnitTest),
        std::pair<wxString, ETATTestType::EnumType>(wxT("PerformanceTest"),    ETATTestType::E_PerformanceTest),
        std::pair<wxString, ETATTestType::EnumType>(wxT("EnduranceTest"),    ETATTestType::E_EnduranceTest),
    };

ETATTestType::TNameValueMap ETATTestType::sm_mapValueName(
        ETATTestType::sm_arValueName ,
        &ETATTestType::sm_arValueName[0] + sizeof(ETATTestType::sm_arValueName) / sizeof(ETATTestType::sm_arValueName[0])
    );


} //namespace Test
} //namespace TestAutomationTool
} //namespace Kinesis
