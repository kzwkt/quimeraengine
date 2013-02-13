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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "STATFileSystemHelper.h"
#include "TATShellProcessListenerMock.h"
#include "InternalDefinitions.h"

#include <wx/filefn.h>

using Kinesis::TestAutomationTool::Backend::STATFileSystemHelper;

// IMPORTANT: There are some required prerequisites to fulfil. A text file called "TestFile.txt" must exist with the content
//            "FILE CREATED FOR TESTING PURPOSES. DON'T DELETE." and the encoding UTF-8. An executable file called "TestExecutable.*"
//            must also exist (* means the appropiate extension for the execution OS).
//
// REMEMBER ALWAYS TO CLEAN THE TESTING ENVIRONMENT AFTER EVERY TEST SO THE STATE IS ALWAYS THE SAME AT THE BEGINNING OF THE TEST EXECUTION.

QTEST_SUITE_BEGIN( STATFileSystemHelper_TestSuite )

/// <summary>
/// The prerequired text file's name used by many unit tests.
/// </summary>
const wxString TEXT_FILE_NAME = wxT("TestFile.txt");

/// <summary>
/// Utility method for testing purposes. Path to the prerequired executable file used by many unit tests.
/// </summary>
/// <returns>
/// The path to the prerequired executable file used by many unit tests.
/// </returns>
wxString GetPathToExecutableFile_UtilityMethod()
{
#ifdef TAT_OS_WINDOWS
    const wxString PATH_TO_EXECUTABLE_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.exe");
#elif defined(TAT_OS_LINUX)
    const wxString PATH_TO_EXECUTABLE_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile");
#elif defined(TAT_OS_MAC)
    // TODO [Thund]: Complete this with Mac configuration.
    #error Not defined for Mac
#endif

    return PATH_TO_EXECUTABLE_FILE;
}

/// <summary>
/// Utility method for testing purposes. Path to the prerequired text file used by many unit tests.
/// </summary>
/// <returns>
/// The path to the prerequired text file used by many unit tests.
/// </returns>
wxString GetPathToTextFile_UtilityMethod()
{
    const wxString PATH_TO_TEXT_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.txt");

    return PATH_TO_TEXT_FILE;
}

/// <summary>
/// Checks that the operation returns False when trying to read from a file that doesn't exist.
/// </summary>
QTEST_CASE ( Read_ReturnsFalseWhenTheFileDoesntExist_Test )
{
    // Preparation
    const wxString PATH_TO_FILE = wxT("DOESNT.EXIST");
    const bool EXPECTED_VALUE = false;

	// Execution
    wxString strContent;
    bool bSuccess = STATFileSystemHelper::Read(PATH_TO_FILE, strContent);

    // Verification
    BOOST_CHECK_EQUAL(bSuccess, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the operation returns True when the file could be read.
/// </summary>
QTEST_CASE ( Read_ReturnsTrueWhenTheOperationWasSuccessful_Test )
{
    // Preparation
    const wxString PATH_TO_FILE = GetPathToTextFile_UtilityMethod();
    const bool EXPECTED_VALUE = true;

	// Execution
    wxString strContent;
    bool bSuccess = STATFileSystemHelper::Read(PATH_TO_FILE, strContent);

    // Verification
    BOOST_CHECK_EQUAL(bSuccess, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the output string is emptied when the read operation fails.
/// </summary>
QTEST_CASE ( Read_ObtainedStringIsEmptyWhenTheOperationFails_Test )
{
    // Preparation
    const wxString PATH_TO_FILE = wxT("DOESNT.EXIST");
    const wxString EXPECTED_CONTENT = wxT("");

	// Execution
    wxString strContent = wxT("WHATEVER");
    STATFileSystemHelper::Read(PATH_TO_FILE, strContent);

    // Verification
    BOOST_CHECK_EQUAL(strContent, EXPECTED_CONTENT);
}

/// <summary>
/// Checks that the output string is filled with the content of the read file.
/// </summary>
QTEST_CASE ( Read_ObtainedStringIsProperlyFilledWhenTheOperationSuccess_Test )
{
    // Preparation
    const wxString PATH_TO_FILE = GetPathToTextFile_UtilityMethod();
    const wxString EXPECTED_CONTENT = wxT("FILE CREATED FOR TESTING PURPOSES. DON'T DELETE.");

	// Execution
    wxString strContent;
    STATFileSystemHelper::Read(PATH_TO_FILE, strContent);

    // Verification
    BOOST_CHECK_EQUAL(strContent, EXPECTED_CONTENT);
}

/// <summary>
/// Checks if the operation returns True when the file to delete exists.
/// </summary>
QTEST_CASE ( Delete_ReturnsTrueWhenTheFileExists_Test )
{
    // Preparation
    const wxString PATH_TO_FILE = GetPathToTextFile_UtilityMethod() + wxT("DELETE");
    wxCopyFile(GetPathToTextFile_UtilityMethod(), PATH_TO_FILE, true);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Delete(PATH_TO_FILE);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns False when trying to delete a file that doesn't exist.
/// </summary>
QTEST_CASE ( Delete_ReturnsFalseWhenTheFileDidntExist_Test )
{
    // Preparation
    const wxString PATH_TO_FILE = wxT("FILE.DOESNT.EXIST");
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Delete(PATH_TO_FILE);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the file is physically removed.
/// </summary>
QTEST_CASE ( Delete_FileIsActuallyRemoved_Test )
{
    // Preparation
    const wxString PATH_TO_FILE = GetPathToTextFile_UtilityMethod() + wxT("DELETE");
    wxCopyFile(GetPathToTextFile_UtilityMethod(), PATH_TO_FILE, true);

    const bool FILE_WAS_REMOVED = !wxFileExists(PATH_TO_FILE);

	// Execution
    STATFileSystemHelper::Delete(PATH_TO_FILE);

    // Verification
    const bool FILE_EXISTS = wxFileExists(PATH_TO_FILE);
    BOOST_CHECK_EQUAL(FILE_EXISTS, FILE_WAS_REMOVED);
}

/// <summary>
/// Checks if the operation returns False when the destination folder doesn't exist.
/// </summary>
QTEST_CASE ( Move_ReturnsFalseWhenDestinationDoesntExist_Test )
{
    // Preparation
    const wxString DESTINATION = wxT("DESTINATION.DOESNT.EXIST");
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Move(GetPathToTextFile_UtilityMethod(), DESTINATION);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns False when the file to be moved doesn't exist.
/// </summary>
QTEST_CASE ( Move_ReturnsFalseWhenSourceDoesntExist_Test )
{
    // Preparation
    const wxString SOURCE = wxT("SOURCE.DOESNT.EXIST");
    const wxString DESTINATION = wxGetCwd();
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Move(SOURCE, DESTINATION);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns True when the source file and the destination folder exist.
/// </summary>
QTEST_CASE ( Move_ReturnsTrueWhenSourceAndDestinationExist_Test )
{
    // Preparation
    const wxString SOURCE = GetPathToTextFile_UtilityMethod();
    const wxString DESTINATION = GetPathToTextFile_UtilityMethod() + wxT("MOVED");
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Move(SOURCE, DESTINATION);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

    // Cleaning
    wxCopyFile(DESTINATION, SOURCE);
    wxRemove(DESTINATION);
}

/// <summary>
/// Checks that the file is physically moved.
/// </summary>
QTEST_CASE ( Move_TheFileIsMoved_Test )
{
    // Preparation
    const wxString SOURCE = GetPathToTextFile_UtilityMethod();
    const wxString DESTINATION = GetPathToTextFile_UtilityMethod() + wxT("MOVED");
    const bool FILE_WAS_MOVED = true;

	// Execution
    STATFileSystemHelper::Move(SOURCE, DESTINATION);

    // Verification
    const bool FILE_DOESNT_EXIST_IN_SOURCE = !wxFileExists(SOURCE);
    const bool FILE_EXISTS_IN_DESTINATION = wxFileExists(DESTINATION);
    BOOST_CHECK_EQUAL(FILE_DOESNT_EXIST_IN_SOURCE, FILE_WAS_MOVED);
    BOOST_CHECK_EQUAL(FILE_EXISTS_IN_DESTINATION, FILE_WAS_MOVED);

    // Cleaning
    wxCopyFile(DESTINATION, SOURCE);
    wxRemove(DESTINATION);
}

/// <summary>
/// Checks that the operation returns False when the file to be renamed doesn't exist.
/// </summary>
QTEST_CASE ( Rename_ReturnsFalseWhenFileDoesntExist_Test )
{
    // Preparation
    const wxString SOURCE = wxT("SOURCE.DOESNT.EXIST");
    const wxString NEW_NAME = wxT("DOESNT.MATTER");
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Rename(SOURCE, NEW_NAME);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns True when the source file exists.
/// </summary>
QTEST_CASE ( Rename_ReturnsTrueWhenOperationIsSuccessful_Test )
{
    // Preparation
    const wxString SOURCE = GetPathToTextFile_UtilityMethod();
    const wxString DESTINATION = GetPathToTextFile_UtilityMethod() + wxT("RENAMED");
    const wxString NEW_NAME = TEXT_FILE_NAME + wxT("RENAMED");
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Rename(SOURCE, NEW_NAME);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

    // Cleaning
    wxRenameFile(DESTINATION, SOURCE, true);
}

/// <summary>
/// Checks that the file is physically renamed.
/// </summary>
QTEST_CASE ( Rename_TheFileIsRenamed_Test )
{
    // Preparation
    const wxString SOURCE = GetPathToTextFile_UtilityMethod();
    const wxString DESTINATION = GetPathToTextFile_UtilityMethod() + wxT("RENAMED");
    const wxString NEW_NAME = TEXT_FILE_NAME + wxT("RENAMED");
    const bool FILE_WAS_RENAMED = true;

	// Execution
    STATFileSystemHelper::Rename(SOURCE, NEW_NAME);

    // Verification
    const bool OLD_FILE_DOESNT_EXIST = !wxFileExists(SOURCE);
    const bool NEW_FILE_EXISTS = wxFileExists(DESTINATION);
    BOOST_CHECK_EQUAL(OLD_FILE_DOESNT_EXIST, FILE_WAS_RENAMED);
    BOOST_CHECK_EQUAL(NEW_FILE_EXISTS, FILE_WAS_RENAMED);

    // Cleaning
    wxRenameFile(DESTINATION, SOURCE, true);
}

/// <summary>
/// Checks that the operation returns True when the file was executed.
/// </summary>
QTEST_CASE ( Execute_ReturnsTrueWhenFileIsExecuted_Test )
{
    // Preparation
    const wxString EXECUTABLE_FILE = GetPathToExecutableFile_UtilityMethod();
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Execute(EXECUTABLE_FILE);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a listener passed as parameter is notified about process' output updates.
/// </summary>
QTEST_CASE ( Execute_TheListenerIsNotifiedAboutProcessOutputUpdate_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATShellProcessListenerMock;

    // Preparation
    const wxString EXECUTABLE_FILE = GetPathToExecutableFile_UtilityMethod();
    const bool EXPECTED_RESULT = true;
    TATShellProcessListenerMock LISTENER;

	// Execution
    STATFileSystemHelper::Execute(EXECUTABLE_FILE, wxT(""), &LISTENER);

    // Verification
    BOOST_CHECK_EQUAL(LISTENER.WasProcessOutputHandlerCalled(), EXPECTED_RESULT);
}

/// <summary>
/// Checks that a listener passed as parameter is notified about process' completion.
/// </summary>
QTEST_CASE ( Execute_TheListenerIsNotifiedAboutProcessCompletion_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATShellProcessListenerMock;

    // Preparation
    const wxString EXECUTABLE_FILE = GetPathToExecutableFile_UtilityMethod();
    const bool EXPECTED_RESULT = true;
    TATShellProcessListenerMock LISTENER;;

	// Execution
    STATFileSystemHelper::Execute(EXECUTABLE_FILE, wxT(""), &LISTENER);

    // Verification
    BOOST_CHECK_EQUAL(LISTENER.WasProcessCompletedHandlerCalled(), EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns True when the file exists.
/// </summary>
QTEST_CASE ( Exists_ReturnsTrueWhenFileExists_Test )
{
    // Preparation
    const wxString FILE_TO_VERIFY = GetPathToTextFile_UtilityMethod();
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Exists(FILE_TO_VERIFY);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns False when the file doesn't exist.
/// </summary>
QTEST_CASE ( Exists_ReturnsFalseWhenFileDoesntExist_Test )
{
    // Preparation
    const wxString FILE_TO_VERIFY = wxT("DOESNT.EXIST");
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Exists(FILE_TO_VERIFY);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the operation returns False when the destination folder doesn't exist.
/// </summary>
QTEST_CASE ( Copy_ReturnsFalseWhenDestinationDoesntExist_Test )
{
    // Preparation
    const wxString DESTINATION = wxT("DESTINATION.DOESNT.EXIST");
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Copy(GetPathToTextFile_UtilityMethod(), DESTINATION);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns False when the file to be copied doesn't exist.
/// </summary>
QTEST_CASE ( Copy_ReturnsFalseWhenSourceDoesntExist_Test )
{
    // Preparation
    const wxString SOURCE = wxT("SOURCE.DOESNT.EXIST");
    const wxString DESTINATION = wxGetCwd();
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Copy(SOURCE, DESTINATION);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns True when the source file and the destination folder exist.
/// </summary>
QTEST_CASE ( Copy_ReturnsTrueWhenSourceAndDestinationExist_Test )
{
    // Preparation
    const wxString SOURCE = GetPathToTextFile_UtilityMethod();
    const wxString DESTINATION = GetPathToTextFile_UtilityMethod() + wxT("COPIED");
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Copy(SOURCE, DESTINATION);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

    // Cleaning
    wxRemove(DESTINATION);
}

/// <summary>
/// Checks that the file is physically copied.
/// </summary>
QTEST_CASE ( Copy_TheFileIsCopied_Test )
{
    // Preparation
    const wxString SOURCE = GetPathToTextFile_UtilityMethod();
    const wxString DESTINATION = GetPathToTextFile_UtilityMethod() + wxT("COPIED");
    const bool FILE_WAS_COPIED = true;

	// Execution
    STATFileSystemHelper::Copy(SOURCE, DESTINATION);

    // Verification
    const bool FILE_EXISTS_IN_SOURCE = wxFileExists(SOURCE);
    const bool FILE_EXISTS_IN_DESTINATION = wxFileExists(DESTINATION);
    BOOST_CHECK_EQUAL(FILE_EXISTS_IN_SOURCE, FILE_WAS_COPIED);
    BOOST_CHECK_EQUAL(FILE_EXISTS_IN_DESTINATION, FILE_WAS_COPIED);

    // Cleaning
    wxRemove(DESTINATION);
}

/// <summary>
/// Checks that the file is written with the expected content.
/// </summary>
QTEST_CASE ( Write_FileIsWrittenAndFilledWithExpectedContent_Test )
{
    // Preparation
    const wxString WRITTEN_FILE_PATH = GetPathToTextFile_UtilityMethod() + wxT("WRITTEN");
    const wxString WRITTEN_FILE_CONTENT = wxT("WRITE TEST");
    const bool EXPECTED_RESULT = true;

	// Execution
    wxString strWrittenContent;
    bool bResult = STATFileSystemHelper::Write(WRITTEN_FILE_PATH, WRITTEN_FILE_CONTENT);
    STATFileSystemHelper::Read(WRITTEN_FILE_PATH, strWrittenContent);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(strWrittenContent, WRITTEN_FILE_CONTENT);

    // Cleaning
    wxRemove(WRITTEN_FILE_PATH);
}

/// <summary>
/// Checks that the file is written when it already exists.
/// </summary>
QTEST_CASE ( Write_OperationIsSuccessfullWhenFileAlreadyExists_Test )
{
    // Preparation
    const wxString WRITTEN_FILE_PATH = GetPathToTextFile_UtilityMethod() + wxT("WRITTEN");
    const wxString WRITTEN_FILE_CONTENT = wxT("WRITE TEST");
    const bool EXPECTED_RESULT = true;

	// Execution
    wxString strWrittenContent;
    STATFileSystemHelper::Write(WRITTEN_FILE_PATH, WRITTEN_FILE_CONTENT);
    bool bResult = STATFileSystemHelper::Write(WRITTEN_FILE_PATH, WRITTEN_FILE_CONTENT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

    // Cleaning
    wxRemove(WRITTEN_FILE_PATH);
}

/// <summary>
/// Checks that all the files in a folder which match the extension filter are listed.
/// </summary>
QTEST_CASE ( ListFolderContent_AllFilesInFolderWithSpecificExtensionAreListed_Test )
{
    // Preparation
    const wxString FOLDER = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY;
    const wxString EXTENSION = wxT("txt");
    std::list<wxString> EXPECTED_FILES;
    EXPECTED_FILES.push_back(wxT("TestFile.txt"));

	// Execution
    std::list<wxString> listedFiles = STATFileSystemHelper::ListFolderContent(FOLDER, EXTENSION);

    // Verification
    BOOST_CHECK_EQUAL(listedFiles.size(), EXPECTED_FILES.size());

    std::list<wxString>::const_iterator iResult = listedFiles.begin();
    std::list<wxString>::const_iterator iExpected = EXPECTED_FILES.begin();

    for(; iResult != listedFiles.end() && iExpected != EXPECTED_FILES.end(); ++iResult, ++iExpected)
    {
        BOOST_CHECK_EQUAL(*iResult, *iExpected);
    }
}

/// <summary>
/// Checks that the value is returned as expected.
/// </summary>
QTEST_CASE ( GetExecutableFileExtension_TheValueIsReturnedCorrectly_Test )
{
    // Preparation
#ifdef TAT_OS_WINDOWS
    const wxString EXPECTED_FILE_EXTENSION = wxT("exe");
#elif defined(TAT_OS_LINUX)
    const wxString EXPECTED_FILE_EXTENSION = wxT("");
// TODO [Thund]: Port for Mac
#endif

	// Execution
    wxString strObtainedFileExtension = STATFileSystemHelper::GetExecutableFileExtension();

    // Verification
    BOOST_CHECK_EQUAL(strObtainedFileExtension, EXPECTED_FILE_EXTENSION);
}

// End - Test Suite: STATFileSystemHelper
QTEST_SUITE_END()
