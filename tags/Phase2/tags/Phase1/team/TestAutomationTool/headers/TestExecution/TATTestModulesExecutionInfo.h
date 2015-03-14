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

    /// <summary>
    /// Checks if two instances are equal or not.
    /// </summary>
    /// <param name="compilerInfo">The other instance to compare to.</param>
    /// <returns>
    /// Returns true when instances are equal and false otherwise.
    /// </returns>
    bool operator==(const TATTestModulesExecutionInfo& executionInfo) const;

        /// <summary>
    /// Checks if two instances are different or not.
    /// </summary>
    /// <param name="compilerInfo">The other instance to compare to.</param>
    /// <returns>
    /// Returns true when instances are different and false otherwise.
    /// </returns>
    bool operator!=(const TATTestModulesExecutionInfo& executionInfo) const;


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
