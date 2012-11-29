// [TERMS&CONDITIONS]

#ifndef __TATUNITTESTMODULEBASE__
#define __TATUNITTESTMODULEBASE__

#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "../testsystem/CommonConfigDefinitions.h"
#include "../testsystem/QCommonTestConfig.h"

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
