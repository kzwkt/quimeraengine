// [TERMS&CONDITIONS]

#ifndef __TATSHELLPROCESSLISTENERMOCK__
#define __TATSHELLPROCESSLISTENERMOCK__

#include "TATShellProcess.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// A mock derived from ITATShellProcessListener for testing purposes.
/// </summary>
class TATShellProcessListenerMock : public TATShellProcess::ITATShellProcessListener
{
    // CONSTRUCTORS
	// ---------------
public:

    TATShellProcessListenerMock()
    {
        m_bProcessCompletedHandlerCalled = false;
        m_bProcessOutputHandlerCalled = false;
        m_nLastResult = 0;
        m_strReceivedOutput = wxT("");
    }

	// METHODS
	// ---------------
public:

    void ProcessCompletedHandler(const int &nResult)
    {
        m_bProcessCompletedHandlerCalled = true;

        m_nLastResult = nResult;
    }

    void ProcessOutputHandler(const wxString &strOutput)
    {
        m_bProcessOutputHandlerCalled = true;

        m_strReceivedOutput += strOutput;
    }


    // PROPERTIES
	// ---------------
public:

    // Properties for testing purposes

    bool WasProcessCompletedHandlerCalled() const
    {
        return m_bProcessCompletedHandlerCalled;
    }

    bool WasProcessOutputHandlerCalled() const
    {
        return m_bProcessOutputHandlerCalled;
    }

    wxString GetReceivedOutput() const
    {
        return m_strReceivedOutput;
    }

    void SetLastResult(const int& nResult)
    {
        m_nLastResult = nResult;
    }

    int GetLastResult() const
    {
        return m_nLastResult;
    }


    // ATTRIBUTES
	// ---------------
public:

    bool m_bProcessCompletedHandlerCalled;

    bool m_bProcessOutputHandlerCalled;

    wxString m_strReceivedOutput;

    int m_nLastResult;
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATSHELLPROCESSLISTENERMOCK__