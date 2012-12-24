// [TERMS&CONDITIONS]

#ifndef __TATTESTEXECUTIONTHREADWHITEBOX__
#define __TATTESTEXECUTIONTHREADWHITEBOX__

#include "TestExecution/TATTestAutomationToolExecution.h"
#include "TATTestAutomationToolExecutionWhiteBox.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATTestExecutionThread for testing purposes.
/// </summary>
class TATTestExecutionThreadWhiteBox : public TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread
{
public:

    TATTestExecutionThreadWhiteBox(TATTestAutomationToolExecution* pHandler) : TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread(pHandler)
    {
    }

    // Utility methods for testing purposes
    int GetExpectedLastExitCode()
    {
        return m_nLastProcessResult;
    }

    // Exposed methods
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::CreateConfigurationFileBackup;
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::RestoreConfigurationFileBackup;
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::ReplaceFlagValuesInConfigurationFile;
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::ReplaceFlagValues;
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::ExecuteCompilerCommand;
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::ExecuteTestModule;
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::ReadTestModuleFiles;
    using TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread::Log;
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTEXECUTIONTHREADWHITEBOX__
