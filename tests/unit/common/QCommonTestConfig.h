// [TERMS&CONDITIONS]

#ifndef __QCOMMONTESTCONFIG__
#define __QCOMMONTESTCONFIG__

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <fstream>
#include <string>

#include "QSimpleConfigLoader.h"

using namespace boost::unit_test;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

/// <summary>
/// [DOC]
/// </summary>
class QCommonTestConfig
{

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// [DOC]
    /// </summary>
    static const std::string TestConfigFileName;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="QCommonTestConfig">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
    QCommonTestConfig();

    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="strTestModuleName">[DOC]</param>
    QCommonTestConfig(const std::string &strTestModuleName);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~QCommonTestConfig();


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// [DOC]
    /// </summary>
    static std::string s_strLogFilePath;

    /// <summary>
    /// [DOC]
    /// </summary>
    static std::ofstream s_resultsFileStream;

};

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCOMMONTESTCONFIG__

