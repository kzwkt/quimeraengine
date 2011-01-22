// [TERMS&CONDITIONS]

#include "QCommonTestConfig.h"


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

const std::string QCommonTestConfig::TestConfigFileName("UnitTestConfig.txt");
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

QCommonTestConfig::QCommonTestConfig(const std::string &strTestModuleName)
{
    // Loads configuration values from disk
    // -------------------------------------
    Kinesis::QuimeraEngine::Test::QSimpleConfigLoader config(QCommonTestConfig::TestConfigFileName);

    if(config.LoadEntries())
    {
        const int FILE_PATH_ENTRY_POSITION = 0;
        
        QCommonTestConfig::s_strLogFilePath = (config[FILE_PATH_ENTRY_POSITION] + strTestModuleName + ".xml");
        QCommonTestConfig::s_resultsFileStream.open(QCommonTestConfig::s_strLogFilePath.c_str(), std::ofstream::out);
    }

    // Log configuration
    // -------------------
    // Output file format
    unit_test_log.set_format(XML);
    // Output stream
    unit_test_log.set_stream(QCommonTestConfig::s_resultsFileStream);
    // Threshold level
    unit_test_log.set_threshold_level(log_successful_tests);
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

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis
