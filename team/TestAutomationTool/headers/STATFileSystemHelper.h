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

#ifndef __STATFILESYSTEMHELPER__
#define __STATFILESYSTEMHELPER__

#include <list>
#include <wx/string.h>

#include "TATShellProcess.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Static class that provides with a set of common actions to manage the file system.
/// </summary>
class STATFileSystemHelper
{
	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
    STATFileSystemHelper();


	// DESTRUCTOR
	// ---------------
private:

	/// <summary>
	/// Destructor (hidden).
	/// </summary>		
    ~STATFileSystemHelper();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Retrieves the content of a text file (UTF-8 encoding).
    /// </summary>
    /// <param name="strFilePath">Full path to the file (including file name).</param>
    /// <param name="strReadStream">The content retrieved from the file.</param>
    /// <returns>
    /// True if the operation was successful; false otherwise.
    /// </returns>
    static bool Read(const wxString& strFilePath, wxString& strReadStream);

    /// <summary>
    /// Deletes a file.
    /// </summary>
    /// <param name="strFilePath">Full path to the file (including file name).</param>
    /// <returns>
    /// True if the operation was successful; false otherwise.
    /// </returns>
    static bool Delete(const wxString& strFilePath);

    /// <summary>
    /// Moves a file to the desired folder.
    /// </summary>
    /// <remarks>
    /// If the destination file already exists, it will be overwritten.
    /// </remarks>
    /// <param name="strFromFilePath">Current full path to the file (including file name).</param>
    /// <param name="strToFilePath">New full path to the file (including file name).</param>
    /// <returns>
    /// True if the operation was successful; false otherwise.
    /// </returns>
    static bool Move(const wxString& strFromFilePath, const wxString& strToFilePath);

    /// <summary>
    /// Renames a file (including file extension).
    /// </summary>
    /// <remarks>
    /// If the destination file already exists, the operation will fail.
    /// </remarks>
    /// <param name="strFilePath">Full path to the file (including file name).</param>
    /// <param name="strNewFileName">New file name (including file extension).</param>
    /// <returns>
    /// True if the operation was successful; false otherwise.
    /// </returns>
    static bool Rename(const wxString& strFilePath, const wxString& strNewFileName);

    /// <summary>
    /// Executes a file. The file has to contain an executable program. It's possible execute the file using parameters.
    /// </summary>
    /// <param name="strFilePath">Full path to the file (including file name).</param>
    /// <param name="strParams">Optional. Parameters to be used to execute the file.</param>
    /// <param name="pListener">Optional. Handler for the process' events.</param>
    /// <returns>
    /// True if the operation was successful; false otherwise.
    /// </returns>
    static bool Execute(const wxString& strFilePath, const wxString& strParams=wxT(""), TATShellProcess::ITATShellProcessListener* pListener=NULL);

    /// <summary>
    /// Verifies whether a file exists or not.
    /// </summary>
    /// <param name="strFilePath">Full path to the file (including file name).</param>
    /// <returns>
    /// True if the file exists; false otherwise.
    /// </returns>
    static bool Exists(const wxString& strFilePath);

    /// <summary>
    /// Creates an exact copy of a file in a different folder and / or with another name.
    /// </summary>
    /// <remarks>
    /// If the destination file already exists, it will be overwritten.
    /// </remarks>
    /// <param name="strFromFilePath">Full path to the original file (including file name).</param>
    /// <param name="strToFilePath">Full path to the new file (including file name).</param>
    /// <returns>
    /// True if the operation was successful; false otherwise.
    /// </returns>
    static bool Copy(const wxString& strFromFilePath, const wxString& strToFilePath);
    
    /// <summary>
    /// Creates a file and fills it with a given text.
    /// </summary>
    /// <remarks>
    /// If the destination file already exists, it will be overwritten.
    /// </remarks>
    /// <param name="strFilePath">Full path to the file (including file name).</param>
    /// <param name="strTextContent">The text content of the file.</param>
    /// <returns>
    /// True if the operation was successful; false otherwise.
    /// </returns>
    static bool Write(const wxString& strFilePath, const wxString& strTextContent);

    /// <summary>
    /// Explores a folder and gets a list of the files it contains.
    /// </summary>
    /// <param name="strFolderToExplore">The path to the folder to explore.</param>
    /// <param name="strExtensionFilter">Optional. When filled, only the files whose extension matches the given 
    /// one are included in the result list.</param>
    /// <returns>
    /// A list with the names (and extension) of the found files.
    /// </returns>
    static std::list<wxString> ListFolderContent(const wxString& strFolderToExplore, const wxString& strExtensionFilter=wxT("*"));

    
	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the extension of an executable file for the current operative system.
    /// </summary>
    /// <returns>
    /// The extension of the type of file. Normally it's not longer than 3 characters.
    /// </returns>
    static const wxString& GetExecutableFileExtension();


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The extension of an executable file for the current operative system.
    /// </summary>
    static const wxString sm_strExecutableFileExtension;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __STATFILESYSTEMHELPER__
