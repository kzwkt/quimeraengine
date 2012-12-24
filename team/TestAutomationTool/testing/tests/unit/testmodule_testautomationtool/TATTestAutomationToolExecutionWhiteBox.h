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
    // INTERNAL CLASSES
    // ----------------
public:

    class TATTestExecutionThread : public TATTestAutomationToolExecution::TATTestExecutionThread
    {
    public:

        TATTestExecutionThread(TATTestAutomationToolExecution* pHandler) : TATTestAutomationToolExecution::TATTestExecutionThread(pHandler)
        {
        }
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map< wxString, std::map<wxString, wxString> > TFlagCombinationCollection;
    typedef std::map< wxString, wxString > TFlagCombinationValues;


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
