// [TERMS&CONDITIONS]

#ifndef __TATCOMMONTESTCONFIG__
#define __TATCOMMONTESTCONFIG__

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <fstream>
#include <string>

#include "QSimpleConfigLoader.h"
#include "EQTestType.h"
#include "InternalDefinitions.h"

#ifdef TAT_OS_WINDOWS
    #include <direct.h>
    #define getcwd_t _getcwd
#else
    #include <unistd.h>
    #define getcwd_t getcwd
#endif

using namespace boost::unit_test;


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Test
{

/// <summary>
/// Configures the testing system and initializes it. It must be instantiated only once per module.
/// When instantiated, it reads the test configuration file and sets up, for example, the test 
/// logging objects.
/// </summary>
class TATCommonTestConfig
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
    TATCommonTestConfig();

    /// <summary>
    /// Constructor that receives the name of the test module and the type of test.
    /// </summary>
    /// <param name="strTestModuleName">The name of the module.</param>
    /// <param name="testType">The type of test.</param>
    TATCommonTestConfig(const std::string &strTestModuleName, const ETATTestType& testType);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATCommonTestConfig();


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
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCOMMONTESTCONFIG__

