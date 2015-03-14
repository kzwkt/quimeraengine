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