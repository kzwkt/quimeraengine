// [TERMS&CONDITIONS]

#ifndef __TATTESTAUTOMATIONTOOLEXECUTIONWHITEBOX__
#define __TATTESTAUTOMATIONTOOLEXECUTIONWHITEBOX__

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
/// Class intented to be used to expose protected methods of TATTestAutomationToolExecution for testing purposes.
/// </summary>
class TATTestAutomationToolExecutionWhiteBox : public TATTestAutomationToolExecution
{
	// METHODS
	// ---------------
public:

    // Exposed methods
    void Destroy()
    {
        TATTestAutomationToolExecution::Destroy();
    }
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLEXECUTIONWHITEBOX__
