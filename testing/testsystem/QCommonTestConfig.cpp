// [TERMS&CONDITIONS]

#include "QCommonTestConfig.h"
#include "CommonConfigDefinitions.h"

#include <boost/date_time.hpp>

namespace Kinesis
{
namespace QuimeraEngine
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

const std::string QCommonTestConfig::TestConfigFileName("TestConfig.txt");
std::string QCommonTestConfig::s_strLogFilePath;
std::ofstream QCommonTestConfig::s_resultsFileStream;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QCommonTestConfig::QCommonTestConfig()
{
}

QCommonTestConfig::QCommonTestConfig(const std::string &strTestModuleName, const EQTestType &testType)
{
    // Loads configuration values from disk
    // -------------------------------------
    Kinesis::QuimeraEngine::Test::QSimpleConfigLoader config(QCommonTestConfig::TestConfigFileName);

    if(config.LoadEntries())
    {
        // Entries order in the configuration file
        const int FILE_UNITTEST_RESULTSPATH_ENTRY_POSITION = 0;
        const int FILE_PERFORMANCETEST_RESULTSPATH_ENTRY_POSITION = 1;
        
        // Depending on the test type, a path is selected to store the results file
        int nEntryToReadResultsPathFrom = 0;

        switch(testType)
        {
        case EQTestType::E_UnitTest:
            {
                nEntryToReadResultsPathFrom = FILE_UNITTEST_RESULTSPATH_ENTRY_POSITION;
                break;
            }
        case EQTestType::E_PerformanceTest:
            {
                nEntryToReadResultsPathFrom = FILE_PERFORMANCETEST_RESULTSPATH_ENTRY_POSITION;
                break;
            }
        }

        QCommonTestConfig::s_strLogFilePath = (config[nEntryToReadResultsPathFrom] + strTestModuleName + "_" + QE_TEST_CONFIG_NAME + "_" + this->GetCurrentTime() + ".xml");
        QCommonTestConfig::s_resultsFileStream.open(QCommonTestConfig::s_strLogFilePath.c_str(), std::ofstream::out);

        // Log configuration
        // -------------------
        // Output file format
        unit_test_log.set_format(XML);
        // Output stream
        unit_test_log.set_stream(QCommonTestConfig::s_resultsFileStream);
        // Threshold level
        unit_test_log.set_threshold_level(log_successful_tests);
    }
    else
    {
        std::cout << "An error occured when loading the test configuration file (" << QCommonTestConfig::TestConfigFileName << ").";
    }
}

	
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QCommonTestConfig::~QCommonTestConfig()
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS	    	 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

std::string QCommonTestConfig::GetCurrentTime()
{
    // Read from http://stackoverflow.com/questions/2612938/simplest-way-to-get-current-time-in-current-timezone-using-boostdate-time

    std::string strResult;

    std::ostringstream stringStream;
    const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_facet *const facet = new boost::posix_time::time_facet("%Y-%m-%d-%H-%M-%S");
    stringStream.imbue(std::locale(stringStream.getloc(), facet));
    stringStream << now;

    strResult = stringStream.str();

    return strResult;
}

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis
