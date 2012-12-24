// [TERMS&CONDITIONS]

#include "QCommonTestConfig.h"
#include "CommonConfigDefinitions.h"

#include <iostream>

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

const std::string TATCommonTestConfig::TestConfigFileName("TestConfig.txt");
std::string TATCommonTestConfig::s_strLogFilePath;
std::ofstream TATCommonTestConfig::s_resultsFileStream;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATCommonTestConfig::TATCommonTestConfig()
{
}

TATCommonTestConfig::TATCommonTestConfig(const std::string &strTestModuleName, const ETATTestType &testType)
{
    // Loads configuration values from disk
    // -------------------------------------

   char* szCurrentWorkingDirectory = getcwd_t(null_t, 0);
    std::string strCurrentWorkingDirectory(szCurrentWorkingDirectory);
    delete[] szCurrentWorkingDirectory;

    Kinesis::QuimeraEngine::Test::QSimpleConfigLoader config(strCurrentWorkingDirectory + "/" + TATCommonTestConfig::TestConfigFileName);

    if(config.LoadEntries())
    {
        // Entries order in the configuration file
        const int FILE_UNITTEST_RESULTSPATH_ENTRY_POSITION = 0;
        const int FILE_PERFORMANCETEST_RESULTSPATH_ENTRY_POSITION = 1;
        
        // Depending on the test type, a path is selected to store the results file
        int nEntryToReadResultsPathFrom = 0;

        switch(testType)
        {
        case ETATTestType::E_UnitTest:
            {
                nEntryToReadResultsPathFrom = FILE_UNITTEST_RESULTSPATH_ENTRY_POSITION;
                break;
            }
        case ETATTestType::E_PerformanceTest:
            {
                nEntryToReadResultsPathFrom = FILE_PERFORMANCETEST_RESULTSPATH_ENTRY_POSITION;
                break;
            }
        }

        TATCommonTestConfig::s_strLogFilePath = (config[nEntryToReadResultsPathFrom] + strTestModuleName + "_" + TAT_TEST_CONFIG_NAME + ".xml");
        TATCommonTestConfig::s_resultsFileStream.open(TATCommonTestConfig::s_strLogFilePath.c_str(), std::ofstream::out);

        // Log configuration
        // -------------------
        // Output file format
        unit_test_log.set_format(XML);
        // Output stream
        unit_test_log.set_stream(TATCommonTestConfig::s_resultsFileStream);
        // Threshold level
        unit_test_log.set_threshold_level(log_successful_tests);
    }
    else
    {
        std::cout << "An error occured when loading the test configuration file (" << TATCommonTestConfig::TestConfigFileName << ").";
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

TATCommonTestConfig::~TATCommonTestConfig()
{
}

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis
