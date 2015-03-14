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

#ifndef __ITATLOGGER__
#define __ITATLOGGER__

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class TATFormattedMessage;

/// <summary>
/// A logger that sends traces (messages) to a recipient.
/// </summary>
/// <remarks>
/// It can work in 2 manners: sending traces as it receives them or buffering them until a flush is demanded.
/// </remarks>
class ITATLogger
{
	// CONSTRUCTORS
	// ---------------
protected:

	/// <summary>
	/// Default constructor.
	/// </summary>
    ITATLogger(){};


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
    virtual ~ITATLogger(){};


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Sends the trace to the recipient.
    /// </summary>
    /// <param name="message">The message to send.</param>
    virtual void Log(TATFormattedMessage message)=0;

    /// <summary>
    /// Processes all the buffered traces.
    /// </summary>
    virtual void Flush()=0;


    // PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Sets a flag that indicates whether to append a new line after every trace or not.
    /// </summary>
    /// <param name="bEnable">True to enable the mechanism, False to disable it.</param>
    virtual void SetAutoNewLinePrint(const bool &bEnable)=0;

    /// <summary>
    /// Gets a flag that indicates whether to append a new line after every trace or not.
    /// </summary>
    /// <returns>
    /// True when the mechanism is enabled, False otherwise.
    /// </returns>
    virtual bool GetAutoNewLinePrint() const=0;

    /// <summary>
    /// Sets a flag that indicates whether to insert the current time before every trace.
    /// </summary>
    /// <param name="bEnable">True to enable the mechanism, False to disable it.</param>
    virtual void SetAutoTimePrint(const bool &bEnable)=0;

    /// <summary>
    /// Gets a flag that indicates whether to insert the current time before every trace.
    /// </summary>
    /// <returns>
    /// True when the mechanism is enabled, False otherwise.
    /// </returns>
    virtual bool GetAutoTimePrint() const=0;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __ITATLOGGER__
