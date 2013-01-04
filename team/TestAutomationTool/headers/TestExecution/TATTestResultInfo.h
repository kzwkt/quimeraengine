// [TERMS&CONDITIONS]

#ifndef __TATTESTRESULTINFO__
#define __TATTESTRESULTINFO__

#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class TATTestResultNode;

/// <summary>
/// Information about a test result, like the context where the test has been executed into, or
/// the result tree.
/// </summary>
class TATTestResultInfo
{
    // CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    TATTestResultInfo();


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the name of the flag combination set for the test execution.
    /// </summary>
    /// <returns>
    /// The name of the flag combination set for the test execution.
    /// </returns>
    wxString GetFlagCombinationName() const;

    /// <summary>
    /// Sets the name of the flag combination set for the test execution.
    /// </summary>
    /// <param name="strName">The name of the flag combination set for the test execution.</param>
    void SetFlagCombinationName(const wxString &strName);

    /// <summary>
    /// Gets the flag combination values set for the test execution.
    /// </summary>
    /// <returns>
    /// The flag combination values set for the test execution.
    /// </returns>
    wxString GetFlagCombinationValues() const;

    /// <summary>
    /// Sets the flag combination values set for the test execution.
    /// </summary>
    /// <param name="strValues">The flag combination values set for the test execution.</param>
    void SetFlagCombinationValues(const wxString &strValues);

    /// <summary>
    /// Gets the name of the compilation configuration set for the test execution.
    /// </summary>
    /// <returns>
    /// The name of the compilation configuration set for the test execution.
    /// </returns>
    wxString GetCompilationConfiguration() const;

    /// <summary>
    /// Sets the name of the compilation configuration set for the test execution.
    /// </summary>
    /// <param name="strConfiguration">The name of the compilation configuration set for the test execution.</param>
    void SetCompilationConfiguration(const wxString &strConfiguration);

    /// <summary>
    /// Gets the name of the compiler set for the test execution.
    /// </summary>
    /// <returns>
    /// The name of the compiler set for the test execution.
    /// </returns>
    wxString GetCompilerName() const;

    /// <summary>
    /// Sets the name of the compiler set for the test execution.
    /// </summary>
    /// <param name="strName">The name of the compiler set for the test execution.</param>
    void SetCompilerName(const wxString &strName);

    /// <summary>
    /// Gets the result tree generated during the test execution.
    /// </summary>
    /// <returns>
    /// The result tree generated during the test execution.
    /// </returns>
    TATTestResultNode* GetResultTree() const;

    /// <summary>
    /// Sets the result tree generated during the test execution.
    /// </summary>
    /// <param name="pResultTree">The result tree generated during the test execution.</param>
    void SetResultTree(TATTestResultNode* pResultTree);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The name of the flag combination set for the test execution.
    /// </summary>
    wxString m_strFlagCombinationName;

    /// <summary>
    /// The flag combination values set for the test execution.
    /// </summary>
    wxString m_strFlagCombinationValues;

    /// <summary>
    /// The name of the compilation configuration set for the test execution.
    /// </summary>
    wxString m_strCompilationConfiguration;

    /// <summary>
    /// The name of the compiler set for the test execution.
    /// </summary>
    wxString m_strCompilerName;

    /// <summary>
    /// The result tree generated during the test execution.
    /// </summary>
    TATTestResultNode* m_pResultTree;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTINFO__
