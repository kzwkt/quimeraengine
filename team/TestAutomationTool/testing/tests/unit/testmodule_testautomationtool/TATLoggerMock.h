// [TERMS&CONDITIONS]

#ifndef __TATLOGGERMOCK__
#define __TATLOGGERMOCK__

#include <wx/string.h>

#include "TestExecution/ITATLogger.h"
#include "TestExecution/TATFormattedMessage.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// A mock derived from ITATLogger for testing purposes.
/// </summary>
class TATLoggerMock : public ITATLogger
{
public:

    virtual void Log(TATFormattedMessage message)
    {
        m_strLog += message.GetFullMessage();
    }

    virtual void Flush()
    {
        m_strLog.Clear();
    }

    virtual void SetAutoNewLinePrint(const bool &bEnable)
    {
    }

    virtual bool GetAutoNewLinePrint() const
    {
        return false;
    }

    virtual void SetAutoTimePrint(const bool &bEnable)
    {
    }

    virtual bool GetAutoTimePrint() const
    {
        return false;
    }

    wxString GetLog() const
    {
        return m_strLog;
    }

protected:

    wxString m_strLog;
};


} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATLOGGERMOCK__
