// [TERMS&CONDITIONS]

#ifndef __TATTESTAUTOMATIONTOOLEXECUTIONMOCK__
#define __TATTESTAUTOMATIONTOOLEXECUTIONMOCK__

#include "TestExecution/TATTestAutomationToolExecution.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// A mock derived from TATTestAutomationToolExecution for testing purposes.
/// </summary>
class TATTestAutomationToolExecutionMock : public TATTestAutomationToolExecution
{
public:

    TATTestAutomationToolExecutionMock(ITATLogger* logger)
    {
        m_pLogger = logger;
    }

    TATTestAutomationToolExecutionMock(ITATTestResultLoader* pTestResultLoader)
    {
        m_pTestResultLoader = pTestResultLoader;
    }
};


} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLEXECUTIONMOCK__
