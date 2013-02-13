//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

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
