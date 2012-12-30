// [TERMS&CONDITIONS]

#ifndef __TATTESTRESULTNODE__
#define __TATTESTRESULTNODE__

#include "TATNode.h"
#include "TestExecution/ETATResult.h"

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
    TATTestResultNode(const wxString &strName, const ETATResult &eResult, const wxString &strMessage, const int &nTime);


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
    int GetTime() const;

    /// <summary>
    /// Sets the ammout of time the test took, in microseconds.
    /// </summary>
    /// <param name="nTime">The ammout of time the test took, in microseconds.</param>
    void SetTime(const int &nTime);

    /// <summary>
    /// Checks whether the test result or one of its children contains errors.
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
    int m_nTime;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTNODE__
