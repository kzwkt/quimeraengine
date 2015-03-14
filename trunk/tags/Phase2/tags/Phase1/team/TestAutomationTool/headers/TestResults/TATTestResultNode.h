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

#ifndef __TATTESTRESULTNODE__
#define __TATTESTRESULTNODE__

#include "TATNode.h"
#include "TestResults/ETATResult.h"
#include "TestResults/ETATTestResultNodeType.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// A node of a test result tree. This kind of node adds some information related to
/// the result of a test or a set of tests, like the time it took or whether they passed
/// or not.
/// </summary>
class TATTestResultNode : public TATNode
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATTestResultNode();

    /// <summary>
    /// Constructor that receives the name of the node.
    /// </summary>
    /// <param name="strName">The name of the node.</param>
    TATTestResultNode(const wxString &strName);

    /// <summary>
    /// Constructor that receives all the information of the node.
    /// </summary>
    /// <param name="strName">The name of the node.</param>
    /// <param name="eResult">The result of the test.</param>
    /// <param name="strMessage">The message or textual information of the test.</param>
    /// <param name="nTime">The time the test took.</param>
    /// <param name="eType">The type of the node.</param>
    TATTestResultNode(const wxString &strName, 
                      const ETATResult &eResult, 
                      const wxString &strMessage, 
                      const int &nTime, 
                      const ETATTestResultNodeType &eType);


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the result of the test.
    /// </summary>
    /// <returns>
    /// The result of the test (success, fail, error).
    /// </returns>
    ETATResult GetResult() const;

    /// <summary>
    /// Sets the result of the test.
    /// </summary>
    /// <param name="eResult">The result of the test (success, fail, error).</param>
    void SetResult(const ETATResult &eResult);

    /// <summary>
    /// Gets the message or textual information of the test.
    /// </summary>
    /// <returns>
    /// The message or textual information of the test
    /// </returns>
    wxString GetMessage() const;

    /// <summary>
    /// Sets the message or textual information of the test.
    /// </summary>
    /// <param name="strMessage">The message or textual information of the test</param>
    void SetMessage(const wxString &strMessage);

    /// <summary>
    /// Gets the ammout of time the test took, in microseconds.
    /// </summary>
    /// <returns>
    /// The ammout of time the test took, in microseconds.
    /// </returns>
    unsigned int GetTime() const;

    /// <summary>
    /// Sets the ammout of time the test took, in microseconds.
    /// </summary>
    /// <param name="nTime">The ammout of time the test took, in microseconds.</param>
    void SetTime(const unsigned int &nTime);
    
    /// <summary>
    /// Gets the type of the node (the level in the result tree).
    /// </summary>
    /// <returns>
    /// The type of the node (the level in the result tree).
    /// </returns>
    ETATTestResultNodeType GetNodeType() const;

    /// <summary>
    /// Sets the type of the node (the level in the result tree).
    /// </summary>
    /// <param name="eType">The type of the node (the level in the result tree).</param>
    void SetNodeType(const ETATTestResultNodeType &eType);

    /// <summary>
    /// Checks whether the test result or one of its children contains errors (result equals E_Fail or E_Error).
    /// </summary>
    /// <returns>
    /// True if the node or at least one of its children has errors.
    /// </returns>
    bool HasErrors() const;


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The result of the test.
    /// </summary>
    ETATResult m_eResult;

    /// <summary>
    /// The message of the test.
    /// </summary>
    wxString m_strMessage;

    /// <summary>
    /// The time the test took.
    /// </summary>
    unsigned int m_nTime;

    /// <summary>
    /// The type of the node (regarding the level in the tree).
    /// </summary>
    ETATTestResultNodeType m_eType;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTNODE__
