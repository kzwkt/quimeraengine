// [TERMS&CONDITIONS]

#define BOOST_TEST_MODULE TestModule_Tools

#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "../common/CommonConfigDefinitions.h"
#include "../common/QCommonTestConfig.h"
using Kinesis::QuimeraEngine::Test::QCommonTestConfig;

const std::string TEST_MODULE_NAME("Tools");

/// <summary>
/// [DOC]
/// </summary>
class TestModuleConfiguration
{
public:
    
    TestModuleConfiguration()
    {
        QCommonTestConfig config(TEST_MODULE_NAME);
    }

    ~TestModuleConfiguration()
    {
    }
};

// Module fixture
BOOST_GLOBAL_FIXTURE( TestModuleConfiguration );
