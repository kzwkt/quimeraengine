// [TERMS&CONDITIONS]

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
