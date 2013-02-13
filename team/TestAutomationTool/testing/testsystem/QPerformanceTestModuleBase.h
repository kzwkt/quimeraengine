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

#ifndef __QPERFORMANCETESTMODULEBASE__
#define __QPERFORMANCETESTMODULEBASE__

#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "../common/CommonConfigDefinitions.h"
#include "../common/QCommonTestConfig.h"

using Kinesis::QuimeraEngine::Test::QCommonTestConfig;
using Kinesis::QuimeraEngine::Test::EQTestType;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

/// <summary>
/// Base class for performance test modules. Always inherit from this class to define a new performance test module.
/// </summary>
class QDllExport QPerformanceTestModuleBase
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Constructor that receives the name of the module.
	/// </summary>
    /// <param name="strModuleName">The name of the module.</param>
	QPerformanceTestModuleBase(const std::string &strModuleName)
    {
        QCommonTestConfig config(strModuleName, EQTestType::E_PerformanceTest);
    }


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~QPerformanceTestModuleBase()
    {
    }

};

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QPERFORMANCETESTMODULEBASE__
