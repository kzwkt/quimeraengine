// [TERMS&CONDITIONS]

#ifndef __QUNITTESTMODULEBASE__
#define __QUNITTESTMODULEBASE__

#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "../testsystem/CommonConfigDefinitions.h"
#include "../testsystem/QCommonTestConfig.h"

using Kinesis::QuimeraEngine::Test::QCommonTestConfig;
using Kinesis::QuimeraEngine::Test::EQTestType;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

/// <summary>
/// Base class for unit test modules. Always inherit from this class to define a new unit test module.
/// </summary>
class QDllExport QUnitTestModuleBase
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Constructor that receives the name of the module.
	/// </summary>
    /// <param name="strModuleName">The name of the module.</param>
	QUnitTestModuleBase(const std::string &strModuleName)
    {
        QCommonTestConfig config(strModuleName, EQTestType::E_UnitTest);
    }


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~QUnitTestModuleBase()
    {
    }

};

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QUNITTESTMODULEBASE__
