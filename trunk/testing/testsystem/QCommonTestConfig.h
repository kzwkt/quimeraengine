// [TERMS&CONDITIONS]

#ifndef __QCOMMONTESTCONFIG__
#define __QCOMMONTESTCONFIG__

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <fstream>
#include <string>

#include "QSimpleConfigLoader.h"
#include "EQTestType.h"

using namespace boost::unit_test;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

/// <summary>
/// Configures the testing system and initializes it. It must be instantiated only once per module.
/// When instantiated, it reads the test configuration file and sets up, for example, the test 
/// logging objects.
/// </summary>
class QCommonTestConfig
{

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Predefined file name of the test configuration file.
    /// </summary>
    static const std::string TestConfigFileName;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QCommonTestConfig();

    /// <summary>
    /// Constructor that receives the name of the test module and the type of test.
    /// </summary>
    /// <param name="strTestModuleName">The name of the module.</param>
    /// <param name="testType">The type of test.</param>
    QCommonTestConfig(const std::string &strTestModuleName, const EQTestType& testType);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~QCommonTestConfig();

    // METHODS
    // ---------------
protected:

    /// <summary>
    /// Gets the current date and time.
    /// </summary>
    /// <returns>
    /// The date and the time following this format: "YYYY-MM-DD-hh-mm-ss".
    /// </returns>
    std::string GetCurrentTime();


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The path of the file where the tests results are to be written.
    /// </summary>
    /// <remarks>
    /// It has to be static because, internally, it's used by the logger of Boost library, that needs it 
    /// alive until the application exits.
    /// </remarks>
    static std::string s_strLogFilePath;

    /// <summary>
    /// The output file stream where the logger will write.
    /// </summary>
    /// <remarks>
    /// It has to be static because, internally, it's used by the logger of Boost library, that needs it 
    /// alive until the application exits.
    /// </remarks>
    static std::ofstream s_resultsFileStream;

};

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCOMMONTESTCONFIG__

