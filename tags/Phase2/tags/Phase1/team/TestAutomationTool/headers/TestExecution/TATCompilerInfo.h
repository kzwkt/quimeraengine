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

#ifndef __TATCOMPILERINFO__
#define __TATCOMPILERINFO__

#include <list>

#include <wx/string.h>

#include "TestExecution/TATTestModulesExecutionInfo.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Holds information related to a compiler like the commands it expects, the path where it's located at or the projects
/// to be compiled with it.
/// </summary>
class TATCompilerInfo
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATCompilerInfo();


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATCompilerInfo();


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
    bool operator==(const TATCompilerInfo& compilerInfo) const;

    /// <summary>
    /// Checks if two instances are different or not.
    /// </summary>
    /// <param name="compilerInfo">The other instance to compare to.</param>
    /// <returns>
    /// Returns true when instances are different and false otherwise.
    /// </returns>
    bool operator!=(const TATCompilerInfo& compilerInfo) const;


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the name of the compiler.
    /// </summary>
    /// <returns>
    /// The name of the compiler. It hasn't to be the same as the physical compiler's name.
    /// </returns>
    wxString GetName() const;

    /// <summary>
    /// Sets the name of the compiler.
    /// </summary>
    /// <param name="strCompilerName">The name of the compiler. It hasn't to be the same as the physical compiler's name.</param>
    void SetName(const wxString& strCompilerName);

    /// <summary>
    /// Gets the word that the compiler expects to be the command for building.
    /// </summary>
    /// <returns>
    /// The "build" command's name.
    /// </returns>
    wxString GetBuildCommand() const;

    /// <summary>
    /// Sets the word that the compiler expects to be the command for building.
    /// </summary>
    /// <param name="strCommandName">The "build" command's name</param>
    void SetBuildCommand(const wxString& strCommandName);

    /// <summary>
    /// Gets the word that the compiler expects to be the command for cleaning.
    /// </summary>
    /// <returns>
    /// The "clean" command's name.
    /// </returns>
    wxString GetCleanCommand() const;

    /// <summary>
    /// Sets the word that the compiler expects to be the command for cleaning.
    /// </summary>
    /// <param name="strCommandName">The "clean" command's name.</param>
    void SetCleanCommand(const wxString& strCommandName);

    /// <summary>
    /// Gets a string that contains all the parameters for the "build" command.
    /// </summary>
    /// <returns>
    /// The parameters for the "build" command.
    /// </returns>
    wxString GetBuildParams() const;

    /// <summary>
    /// Sets a string that contains all the parameters for the "build" command.
    /// </summary>
    /// <param name="strParams">The parameters for the "build" command.</param>
    void SetBuildParams(const wxString& strParams);
    
    /// <summary>
    /// Gets a string that contains all the parameters for the "clean" command.
    /// </summary>
    /// <returns>
    /// The parameters for the "clean" command.
    /// </returns>
    wxString GetCleanParams() const;

    /// <summary>
    /// Sets a string that contains all the parameters for the "clean" command.
    /// </summary>
    /// <param name="strParams">The parameters for the "clean" command.</param>
    void SetCleanParams(const wxString& strParams);
    
    /// <summary>
    /// Gets a string that contains the token used by the compiler to specify the project file.
    /// </summary>
    /// <returns>
    /// The token used by the compiler to specify the project file.
    /// </returns>
    wxString GetFileSpecifier() const;

    /// <summary>
    /// Sets a string that contains the token used by the compiler to specify the project file.
    /// </summary>
    /// <param name="strToken">The token used by the compiler to specify the project file.</param>
    void SetFileSpecifier(const wxString& strToken);

    /// <summary>
    /// Gets the physical path of the compiler.
    /// </summary>
    /// <returns>
    /// The file path of the compiler.
    /// </returns>
    wxString GetCompilerPath() const;

    /// <summary>
    /// Sets the physical path of the compiler.
    /// </summary>
    /// <param name="strCompilerPath">The file path of the compiler.</param>
    void SetCompilerPath(const wxString& strCompilerPath);
    
    /// <summary>
    /// Gets a list of file paths of projects of the SUT (System Under Testing) to be compiled.
    /// </summary>
    /// <returns>
    /// A list of project paths.
    /// </returns>
    std::list<wxString> GetSUTProjects() const;

    /// <summary>
    /// Sets a list of file paths of projects of the SUT (System Under Testing) to be compiled.
    /// </summary>
    /// <param name="sutProjectsToCompile">A list of project paths.</param>
    void SetSUTProjects(const std::list<wxString>& sutProjectsToCompile);
    
    /// <summary>
    /// Gets a list of structures that hold information about test projects to be compiled.
    /// </summary>
    /// <returns>
    /// List of test project information structures.
    /// </returns>
    std::list<TATTestModulesExecutionInfo> GetTestModulesExecutionInfo() const;

    /// <summary>
    /// Sets a list of structures that hold information about test projects to be compiled.
    /// </summary>
    /// <param name="testModulesExecutionInfos">List of test project information structures.</param>
    void SetTestModulesExecutionInfo(const std::list<TATTestModulesExecutionInfo>& testModulesExecutionInfos);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The name of the compiler.
    /// </summary>
    wxString m_strName;

    /// <summary>
    /// The "build" command's name.
    /// </summary>
    wxString m_strBuildCommand;

    /// <summary>
    /// The "clean" command's name.
    /// </summary>
    wxString m_strCleanCommand;

    /// <summary>
    /// The parameters for the "build" command.
    /// </summary>
    wxString m_strBuildParams;

    /// <summary>
    /// The parameters for the "clean" command.
    /// </summary>
    wxString m_strCleanParams;
    
    /// <summary>
    /// The token used by the compiler to specify the file of the project.
    /// </summary>
    wxString m_strFileSpecifier;

    /// <summary>
    /// The file path of the compiler.
    /// </summary>
    wxString m_strCompilerPath;

    /// <summary>
    /// A list of project paths to be compiled.
    /// </summary>
    std::list<wxString> m_sutProjectsToCompile;

    /// <summary>
    /// List of test project information structures.
    /// </summary>
    std::list<TATTestModulesExecutionInfo> m_testModulesExecutionInfos;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCOMPILERINFO__
