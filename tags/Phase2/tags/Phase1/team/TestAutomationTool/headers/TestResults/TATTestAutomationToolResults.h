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

#ifndef __TATTESTAUTOMATIONTOOLRESULTS__
#define __TATTESTAUTOMATIONTOOLRESULTS__

#include <map>
#include <wx/thread.h>
#include <wx/event.h>

#include "TATShellProcess.h"
#include "TestResults/ITATTestResultLoader.h"
#include "TestResults/TATTestResultInfo.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class ITATLogger;

/// <summary>
/// Manages the business logic of a functional sector of the application in a UI-independent way.
/// Provides functionality related to the execution of the tests.
/// </summary>
class TATTestAutomationToolResults : public wxEvtHandler
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATTestAutomationToolResults();


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATTestAutomationToolResults();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Releases all the resources.
    /// </summary>
    void Destroy();

    /// <summary>
    /// Parses all the result files at a given directory and returns the tree of results and the compilation-related information.
    /// </summary>
    /// <param name="strTestResultFilePath">The path to the test result files.</param>
    /// <returns>
    /// A list of structures that contain information about the results and the test execution context.
    /// </returns>
    std::list<TATTestResultInfo> ParseAllTestResultFiles(const wxString& strTestResultsPath);

    /// <summary>
    /// Parses a test result file and returns the tree of results and the compilation-related information.
    /// </summary>
    /// <param name="strTestResultFilePath">The path to the test result files.</param>
    /// <param name="strCompilationConfig">The name of the compilation configuration.</param>
    /// <param name="strCompilerName">The name of the compiler.</param>
    /// <param name="strFlagCombinationName">The flag combination name.</param>
    /// <param name="strFlagCombinationValues">The values of the flag combination.</param>
    /// <returns>
    /// Information about the results and the test execution context.
    /// </returns>
    TATTestResultInfo ParseTestResultFile(const wxString& strTestResultsPath,
                                          const wxString& strCompilationConfig,
                                          const wxString& strCompilerName,
                                          const wxString& strFlagCombinationName,
                                          const wxString& strFlagCombinationValues);

protected:

    /// <summary>
    /// Makes a list of all the test result files inside a given directory.
    /// </summary>
    /// <param name="strFolderPath">The path to the folder to search in.</param>
    /// <returns>
    /// A list of the paths to every test result file.
    /// </returns>
    std::list<wxString> ReadTestResultFiles(const wxString& strFolderPath) const;

    /// <summary>
    /// Parses the test result file using the test result loader.
    /// </summary>
    /// <param name="strTestResultFilePath">The path to the test result file.</param>
    void LoadAndParseTestResultFile(const wxString &strTestResultFilePath);


    // EVENT HANDLERS
    // ---------------
public:


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the path to the configuration file of the SUT.
    /// </summary>
    /// <returns>
    /// The path to the configuration file of the SUT.
    /// </returns>
    wxString GetTestResultsPath() const;

    /// <summary>
    /// Sets the path to the configuration file of the SUT.
    /// </summary>
    /// <param name="strCompilerFilePath">The path to the configuration file of the SUT.</param>
    void SetTestResultsPath(const wxString& strTestResultsPath);

    /// <summary>
    /// Gets the test result loader that will transform test result files into insternal structures.
    /// </summary>
    /// <returns>
    /// A test result loader to parse test result files.
    /// </returns>
    ITATTestResultLoader* GetTestResultLoader() const;

    /// <summary>
    /// Sets the test result loader that will transform test result files into insternal structures.
    /// </summary>
    /// <param name="pTestResultLoader">A test result loader to parse test result files.</param>
    void SetTestResultLoader(ITATTestResultLoader* pTestResultLoader);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The component that loads test result files and convertes them into internal structures.
    /// </summary>
    ITATTestResultLoader* m_pTestResultLoader;

    /// <summary>
    /// The path to the test result files.
    /// </summary>
    wxString m_strTestResultsPath;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLRESULTS__
