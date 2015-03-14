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

#ifndef __TATWXWIDGETSCONTROLLOGGER__
#define __TATWXWIDGETSCONTROLLOGGER__

#include <queue>
#include <wx/colour.h>
#include <wx/thread.h>

#include "TestExecution/ITATLogger.h"
#include "TestExecution/TATFormattedMessage.h"
#include "TestExecution/ETATColor.h"

class wxRichTextCtrl;

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Logger implementation that writes the messages on a Rich Text Control of the wxWidgets library.
/// </summary>
class TATwxWidgetsControlLogger : public ITATLogger
{
	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives the control to write on and when will the logger write its messages.
    /// </summary>
    /// <param name="pControl">A control to write the messages on.</param>
    /// <param name="bAutoFlush">A flag that indicates whether the messages will be processed as they arrive 
    /// or if they are to be buffered.</param>
    TATwxWidgetsControlLogger(wxRichTextCtrl* pControl, const bool& bAutoFlush=true);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATwxWidgetsControlLogger();


	// METHODS
	// ---------------
public:

    //! @copydoc ITATLogger::Log()
    virtual void Log(TATFormattedMessage message);

    //! @copydoc ITATLogger::Flush()
    virtual void Flush();

protected:

    /// <summary>
    /// Writes one of the parts of the message applying its own format.
    /// </summary>
    /// <param name="messagePart">The message part to write.</param>
    void WriteMessagePart(const TATFormattedMessage::TMessagePart& messagePart);

    /// <summary>
    /// Writes an entire message, part by part.
    /// </summary>
    /// <param name="message">The message to write.</param>
    void WriteMessage(TATFormattedMessage& message);

    /// <summary>
    /// Converts a color value to another defined in the wxWidgets library.
    /// </summary>
    /// <param name="color">A color value.</param>
    /// <returns>
    /// A color defined in the wxWidget library.
    /// </returns>
    wxColor TranslateColor(const ETATColor& color) const;


	// PROPERTIES
	// ---------------
public:

    //! @copydoc ITATLogger::SetAutoNewLinePrint()
    virtual void SetAutoNewLinePrint(const bool &bEnable);

    //! @copydoc ITATLogger::GetAutoNewLinePrint()
    virtual bool GetAutoNewLinePrint() const;

    //! @copydoc ITATLogger::SetAutoTimePrint()
    virtual void SetAutoTimePrint(const bool &bEnable);

    //! @copydoc ITATLogger::GetAutoTimePrint()
    virtual bool GetAutoTimePrint() const;


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The control to write on.
    /// </summary>
    wxRichTextCtrl* m_pControl;

    /// <summary>
    /// A flag that indicates whether the messages will be processed as they arrive 
    /// or if they are to be buffered.
    /// </summary>
    bool m_bAutoFlush;

    /// <summary>
    /// A buffer for messages. It's only used when auto-flush is disabled.
    /// </summary>
    std::queue<TATFormattedMessage> m_buffer;

    /// <summary>
    /// Object used to mark a critical section for multi-thread operations.
    /// </summary>
    wxCriticalSection m_criticalSection;

    /// <summary>
    /// A flag that indicates whether to append a new line after every trace or not.
    /// </summary>
    bool m_bAutoNewLinePrintEnabled;

    /// <summary>
    /// a flag that indicates whether to insert the current time before every trace.
    /// </summary>
    bool m_bAutoTimePrintEnabled;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATWXWIDGETSCONTROLLOGGER__
