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

#ifndef __TATUNITTESTMODULEBASE__
#define __TATUNITTESTMODULEBASE__

#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "../testsystem/CommonConfigDefinitions.h"
#include "../testsystem/TATCommonTestConfig.h"

using Kinesis::TestAutomationTool::Test::TATCommonTestConfig;
using Kinesis::TestAutomationTool::Test::ETATTestType;

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Test
{

/// <summary>
/// Base class for unit test modules. Always inherit from this class to define a new unit test module.
/// </summary>
class TATUnitTestModuleBase
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Constructor that receives the name of the module.
	/// </summary>
    /// <param name="strModuleName">The name of the module.</param>
	TATUnitTestModuleBase(const std::string &strModuleName)
    {
        TATCommonTestConfig config(strModuleName, ETATTestType::E_UnitTest);
    }


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATUnitTestModuleBase()
    {
    }

};

} //namespace Test
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATUNITTESTMODULEBASE__
