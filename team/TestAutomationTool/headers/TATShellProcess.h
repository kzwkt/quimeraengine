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

#ifndef __TATSHELLPROCESS__
#define __TATSHELLPROCESS__

#include <wx/string.h>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Represents an independent process that can be executed at any time by any process or thread.
/// </summary>
/// <remarks>
/// The output text of the process is redirected and sent to the client using the ITATShellProcessListener interface. This
/// interface lets an external component to listen to the incoming text. Using this interface, the component can be also
/// aware of the moment the process ends.
/// Currently, the process can be executed in a synchronous way only.
/// </remarks>
class TATShellProcess
{
    // INTERNAL CLASSES
    // ----------------
public:

    /// <summary>
    /// Lets an external component receive the output text of the process during its execution.
    /// </summary>
    class ITATShellProcessListener
    {
    protected:

        ITATShellProcessListener() {}
        virtual ~ITATShellProcessListener() {}

    public:

        /// <summary>
        /// Called when the process has finished its execution.
        /// </summary>
        /// <param name="nResult">The exit code returned by the process. Its meaning depends on the application implementation.</param>
        virtual void ProcessCompletedHandler(const int &nResult)=0;

        /// <summary>
        /// Called when a new output text is received.
        /// </summary>
        /// <param name="strOutput">The captured output text.</param>
        virtual void ProcessOutputHandler(const wxString &strOutput)=0;
    };


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    /// <remarks>
    /// Important: The process is not executed when this constructor is called.
    /// </remarks>
	TATShellProcess();

    /// <summary>
    /// Constructor that receives all the information needed for the execution of the process.
    /// </summary>
    /// <remarks>
    /// Important: The process is not executed when this constructor is called.
    /// </remarks>
    /// <param name="strCommand">The command to execute (executable's file path and parameters).</param>
    /// <param name="pListener">Optional. An external component to inform about process' events.</param>
    TATShellProcess(const wxString &strCommand, ITATShellProcessListener* pListener=NULL);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATShellProcess();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Executes the command creating a new process.
    /// </summary>
    /// <remarks>
    /// Produces the creation of a black window (when executes a console application) that closes automatically as the process dies.
    /// </remarks>
    /// <param name="bSynchronous">Optional. This feature is not implemented yet. Defines the way the process will be executed:
    /// synchronously or asynchronously.</param>
    void Execute(const bool &bSynchronous=true);

protected:

    /// <summary>
    /// Called when new output text has to be processed.
    /// </summary>
    /// <param name="outputBuffer">The text to be processed.</param>
    /// <param name="nBufferSize">The size of the text, in bytes.</param>
    virtual void OnOutputArrived(const char* outputBuffer, const unsigned int &uBufferSize);

    /// <summary>
    /// Called when the process execution ends.
    /// </summary>
    /// <param name="nProcessResult">The exit code returned by the process.</param>
    virtual void OnProcessCompleted(const int &nProcessResult);


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Sets the command to be executed.
    /// </summary>
    /// <param name="strCommand">The command to be executed (including executable's path and parameters).</param>
    void SetCommand(const wxString &strCommand);

    /// <summary>
    /// Gets the command to be executed.
    /// </summary>
    /// <returns>
    /// The command to be executed (including executable's path and parameters).
    /// </returns>
    wxString GetCommand() const;

    /// <summary>
    /// Sets the listener for the process' events.
    /// </summary>
    /// <param name="pListener">The listener component.</param>
    void SetListener(ITATShellProcessListener* pListener);

    /// <summary>
    /// Gets the listener for the process' events.
    /// </summary>
    /// <returns>
    /// The listener component.
    /// </returns>
    ITATShellProcessListener* GetListener() const;
    

	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The command to be executed.
    /// </summary>
    wxString m_strCommand;

    /// <summary>
    /// The listener of the process' events.
    /// </summary>
    ITATShellProcessListener* m_pListener;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATSHELLPROCESS__
