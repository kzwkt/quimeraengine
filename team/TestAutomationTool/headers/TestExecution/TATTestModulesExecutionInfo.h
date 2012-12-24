// [TERMS&CONDITIONS]

#ifndef __TATTESTMODULESEXECUTIONINFO__
#define __TATTESTMODULESEXECUTIONINFO__

#include <wx/string.h>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// A data structure that contains information about a set of test modules.
/// </summary>
class TATTestModulesExecutionInfo
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATTestModulesExecutionInfo();


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATTestModulesExecutionInfo();


	// METHODS
	// ---------------
public:


	// PROPERTIES
	// ---------------
public:
    
    /// <summary>
    /// Gets the path to the directory where the tests modules are.
    /// </summary>
    /// <returns>
    /// The path to the folder of the test modules.
    /// </returns>
    wxString GetTestModulesPath() const;

    /// <summary>
    /// Sets the path to the directory where the tests modules are.
    /// </summary>
    /// <param name="strTestModulesPath">The path to the folder of the test modules.</param>
    void SetTestModulesPath(const wxString& strTestModulesPath);
    
    /// <summary>
    /// Gets the path to the directory where the test result files written by the test modules are to be stored.
    /// </summary>
    /// <returns>
    /// The path to the directory of the test result files.
    /// </returns>
    wxString GetResultsPath() const;

    /// <summary>
    /// Sets the path to the directory where the test result files written by the test modules are to be stored.
    /// </summary>
    /// <param name="strResultsPath">The path to the directory of the test result files.</param>
    void SetResultsPath(const wxString& strResultsPath);
    
    /// <summary>
    /// Gets the path to the test project that generates the test module files.
    /// </summary>
    /// <returns>
    /// The path to the test project file.
    /// </returns>
    wxString GetTestProjectPath() const;

    /// <summary>
    /// Sets the path to the test project that generates the test module files.
    /// </summary>
    /// <param name="strTestProjectPath">The path to the test project file.</param>
    void SetTestProjectPath(const wxString& strTestProjectPath);


	// ATTRIBUTES
	// ---------------
protected:
    
    /// <summary>
    /// The path to the folder of the test modules.
    /// </summary>
    wxString m_strTestModulesPath;

    /// <summary>
    /// The path to the directory of the test result files.
    /// </summary>
    wxString m_strResultsPath;

    /// <summary>
    /// The path to the test project file.
    /// </summary>
    wxString m_strTestProjectPath;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTMODULESEXECUTIONINFO__
