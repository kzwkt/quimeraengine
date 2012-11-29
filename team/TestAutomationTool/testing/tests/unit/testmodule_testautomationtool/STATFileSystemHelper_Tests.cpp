// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "STATFileSystemHelper.h"

#include <wx/filefn.h>

using Kinesis::TestAutomationTool::Backend::STATFileSystemHelper;

// IMPORTANT: There are some required prerequisites to fulfil. A text file called "TestFile.txt" must exist with the content
//            "FILE CREATED FOR TESTING PURPOSES. DON'T DELETE." and the encoding UTF-8. An executable file called "TestExecutable.*"
//            must also exist (* means the appropiate extension for the execution OS).
//
// REMEMBER ALWAYS TO CLEAN THE TESTING ENVIRONMENT AFTER EVERY TEST SO THE STATE IS ALWAYS THE SAME AT THE BEGINNING OF THE TEST EXECUTION.

QTEST_SUITE_BEGIN( STATFileSystemHelper_TestSuite )
    
/// <summary>
/// Path to the prerequired text file used by many unit tests.
/// </summary>
#ifdef TAT_OS_WINDOWS
    const wxString PATH_TO_EXECUTABLE_FILE = wxT("TestFile.exe");
#elif defined(TAT_OS_LINUX)
    const wxString PATH_TO_EXECUTABLE_FILE = wxT("TestFile.sh");
#elif defined(TAT_OS_MAC)
    // TODO [Thund]: Complete this with Mac configuration.
#endif

/// <summary>
/// Path to the prerequired text file used by many unit tests.
/// </summary>
const wxString PATH_TO_TEXT_FILE = wxT("TestFile.txt");

/// <summary>
/// The prerequired text file's name used by many unit tests.
/// </summary>
const wxString TEXT_FILE_NAME = wxT("TestFile.txt");

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
    const wxString PATH_TO_FILE = PATH_TO_TEXT_FILE;
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
    const wxString PATH_TO_FILE = PATH_TO_TEXT_FILE;
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
    const wxString PATH_TO_FILE = wxT("DELETE") + PATH_TO_TEXT_FILE;
    wxCopyFile(PATH_TO_TEXT_FILE, PATH_TO_FILE, true);

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
    const wxString PATH_TO_FILE = wxT("DELETE") + PATH_TO_TEXT_FILE;
    wxCopyFile(PATH_TO_TEXT_FILE, PATH_TO_FILE, true);

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
    bool bResult = STATFileSystemHelper::Move(PATH_TO_TEXT_FILE, DESTINATION);
    
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
    const wxString SOURCE = PATH_TO_TEXT_FILE;
    const wxString DESTINATION = wxGetCwd() + wxT("MOVED") + TEXT_FILE_NAME;
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
    const wxString SOURCE = PATH_TO_TEXT_FILE;
    const wxString DESTINATION = wxGetCwd() + wxT("MOVED") + TEXT_FILE_NAME;
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
    const wxString SOURCE = PATH_TO_TEXT_FILE;
    const wxString NEW_NAME = wxT("RENAMED") + TEXT_FILE_NAME;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Rename(SOURCE, NEW_NAME);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

    // Cleaning
    wxRenameFile(NEW_NAME, SOURCE);
}

/// <summary>
/// Checks that the file is physically renamed.
/// </summary>
QTEST_CASE ( Rename_TheFileIsRenamed_Test )
{
    // Preparation
    const wxString SOURCE = PATH_TO_TEXT_FILE;
    const wxString NEW_NAME = wxT("RENAMED") + TEXT_FILE_NAME;
    const bool FILE_WAS_RENAMED = true;

	// Execution
    STATFileSystemHelper::Rename(SOURCE, NEW_NAME);
    
    // Verification
    const bool OLD_FILE_DOESNT_EXIST = !wxFileExists(SOURCE);
    const bool NEW_FILE_EXISTS = wxFileExists(NEW_NAME);
    BOOST_CHECK_EQUAL(OLD_FILE_DOESNT_EXIST, FILE_WAS_RENAMED);
    BOOST_CHECK_EQUAL(NEW_FILE_EXISTS, FILE_WAS_RENAMED);

    // Cleaning
    wxRenameFile(NEW_NAME, SOURCE);
}

/// <summary>
/// Checks that the operation returns False when the file to be executed doesn't exist.
/// </summary>
QTEST_CASE ( Execute_ReturnsFalseWhenFileDoesntExist_Test )
{
    // Preparation
    const wxString EXECUTABLE_FILE = wxT("SOURCE.DOESNT.EXIST");
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = STATFileSystemHelper::Execute(EXECUTABLE_FILE);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns True when the file was executed.
/// </summary>
QTEST_CASE ( Execute_ReturnsTrueWhenFileIsExecuted_Test )
{
    // Preparation
    const wxString EXECUTABLE_FILE = PATH_TO_EXECUTABLE_FILE;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = STATFileSystemHelper::Execute(EXECUTABLE_FILE);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the operation returns True when the file exists.
/// </summary>
QTEST_CASE ( Exists_ReturnsTrueWhenFileExists_Test )
{
    // Preparation
    const wxString FILE_TO_VERIFY = PATH_TO_TEXT_FILE;
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
    bool bResult = STATFileSystemHelper::Copy(PATH_TO_TEXT_FILE, DESTINATION);
    
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
    const wxString SOURCE = PATH_TO_TEXT_FILE;
    const wxString DESTINATION = wxGetCwd() + wxT("COPIED") + TEXT_FILE_NAME;
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
    const wxString SOURCE = PATH_TO_TEXT_FILE;
    const wxString DESTINATION = wxGetCwd() + wxT("COPIED") + TEXT_FILE_NAME;
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
/// Checks that the value is returned as expected.
/// </summary>
QTEST_CASE ( GetExecutableFileExtension_TheValueIsReturnedCorrectly_Test )
{
    // Preparation
#ifdef TAT_OS_WINDOWS
    const wxString EXPECTED_FILE_EXTENSION = wxT("exe");
#elif defined(TAT_OS_LINUX)
    const wxString EXPECTED_FILE_EXTENSION = wxT("sh");
// TODO [Thund]: Port for Mac
#endif

	// Execution
    wxString strObtainedFileExtension = STATFileSystemHelper::GetExecutableFileExtension();
    
    // Verification
    BOOST_CHECK_EQUAL(strObtainedFileExtension, EXPECTED_FILE_EXTENSION);
}

// End - Test Suite: STATFileSystemHelper
QTEST_SUITE_END()
