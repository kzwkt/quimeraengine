//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

// Note: In these unit tests we are no fulfilling the principle of reproducibility. We are running out of time at the moment.
// Note2: These unit tests make use of some artifacts located at /testing/bin/artifacts/artifacts/SQFile/ (copied to the cwd before execution).

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "SQFile.h"

// These includes are needed by WaitForCreationOrDeletion function
#include "QStopwatch.h"
#include "QBasicArray.h"
#include "EQTextEncoding.h"
#include <boost/thread.hpp>
#include <fstream>

using Kinesis::QuimeraEngine::System::IO::FileSystem::SQFile;
using Kinesis::QuimeraEngine::System::IO::FileSystem::QPath;
using Kinesis::QuimeraEngine::System::IO::FileSystem::EQFileSystemError;
using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

// The base path to all the artifacts used by these tests
static const string_q PATH_TO_ARTIFACTS("./artifacts/SQFile/");

// Function that waits for a predefined amount of time for a file system operation to complete
bool WaitForCreationOrDeletion_SQFileTestHelper(const QPath &directoryOrFile, const bool bTDeletionFCreation)
{
    using Kinesis::QuimeraEngine::System::Timing::QStopwatch;
    using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    static const u64_q MAXIMUM_WAIT_TIME = 600ULL; // milliseconds

#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    static const EQTextEncoding PATH_ENCODING = EQTextEncoding::E_UTF8;
#elif defined(QE_OS_WINDOWS)
    static const EQTextEncoding PATH_ENCODING = string_q::GetLocalEncodingUTF16();
#endif

    QBasicArray<i8_q> arBytesDirectory = directoryOrFile.ToString().ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesDirectory.Get();
    boost::filesystem::path directoryOrFilePath(szPath);

    QStopwatch elapsedTime;
    elapsedTime.Set();
    bool bTooMuchTime = false;

    while(boost::filesystem::exists(directoryOrFilePath) == bTDeletionFCreation && !bTooMuchTime)
    {
        boost::this_thread::yield(); // [TODO] Thund: Use SQThisThread when it exists
        bTooMuchTime = elapsedTime.GetElapsedTimeAsTimeSpan().GetMilliseconds() < MAXIMUM_WAIT_TIME;
    }

    QE_ASSERT_ERROR(!bTooMuchTime, "The timeout expired, the file or directory could not be created or deleted fast enough.");

    return !bTooMuchTime;
}

// This function checks the existence of the content in a concrete file
bool CheckFileContent(const QPath &filePath, const string_q &strExpectedFileContent)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

    EQFileSystemError errorCode = EQFileSystemError::E_Success;
    bool bContentMatchesExpectations = true;

    // Checks that the file exists
    bContentMatchesExpectations = bContentMatchesExpectations && SQFile::Exists(filePath, errorCode);

    if(bContentMatchesExpectations)
    {
        // [TODO] Thund: Replace this stuff with QTextStreamReader<QFileStream> when they both exist
        // Opens the file
        QBasicArray<i8_q> arFilePath = filePath.ToString().ToBytes(EQTextEncoding::E_ASCII);
        std::ifstream inputFile(arFilePath.Get());

        if(inputFile.is_open())
        {
            std::string strContent;
            bool bEOF = false;

            while(!bEOF)
            {
                bEOF = (inputFile >> strContent).eof();
            }

            string_q strFileContent = strContent.c_str();

            // Checks the content of the file
            bContentMatchesExpectations = bContentMatchesExpectations && strFileContent == strExpectedFileContent;
        }
        else
        {
            bContentMatchesExpectations = false;
        }
    }

    return bContentMatchesExpectations;
}



QTEST_SUITE_BEGIN( SQFile_TestSuite )

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist.
/// </summary>
QTEST_CASE ( Delete_FileDoesNotExist_Test )
{
    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_DoesNotExist;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Delete(FILE_PATH);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and is removed.
/// </summary>
QTEST_CASE ( Delete_FileIsDeleted_Test )
{
    // Assuming the existence of:
    // -./FileToDelete.txt

    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./FileToDelete.txt");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_Success;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Delete(FILE_PATH);
    
    // [Verification]
    WaitForCreationOrDeletion_SQFileTestHelper(FILE_PATH, true);

    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bFileExists = SQFile::Exists(FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(!bFileExists);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a file.
/// </summary>
QTEST_CASE ( Delete_AssertionFailsWhenInputPathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SQFile::Delete(FILE_PATH);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the source file does not exist.
/// </summary>
QTEST_CASE ( Move_SourceFileDoesNotExist_Test )
{
    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_DoesNotExist;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the destination directory does not exist.
/// </summary>
QTEST_CASE ( Move_DestinationDirectoryDoesNotExist_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_DoesNotExist;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that source file is moved when the destination has a file with the same name and the replace flag is True.
/// </summary>
QTEST_CASE ( Move_SourceFileIsMovedWhenDestinationHasContentWithSameNameAndReplaceIsTrue_Test )
{
    // Assuming the existence of:
    // -./FileToMove.txt
    // -./MoveDestinationWithSameFile/
    // -./MoveDestinationWithSameFile/FileToMove.txt

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToMove.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile/");
    const QPath EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile/FileToMove.txt");
    const string_q EXPECTED_FILE_CONTENT("MOVED");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SQFileTestHelper(EXPECTED_FILE_PATH, false);

    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bDestinationFileExists = SQFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bDestinationWasReplaced = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);
    bool bSourceFileDoesntExist = !SQFile::Exists(SOURCE_FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileDoesntExist);
    BOOST_CHECK(bDestinationWasReplaced);
}

/// <summary>
/// Checks that source file is not moved when the destination has a file with the same name and the replace flag is False.
/// </summary>
QTEST_CASE ( Move_SourceFileIsNotMovedWhenDestinationHasContentWithSameNameAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToMove2.txt
    // -./MoveDestinationWithSameFile2/
    // -./MoveDestinationWithSameFile2/FileToMove2.txt

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToMove2.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile2/");
    const QPath NOT_EXPECTED_CONTENT = QPath(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile2/FileToMove2.txt");
    const string_q EXPECTED_FILE_CONTENT = string_q::GetEmpty();
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_AlreadyExists;
    const bool INPUT_REPLACE = false;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bDestinationFileContentHasNotChanged = CheckFileContent(NOT_EXPECTED_CONTENT, EXPECTED_FILE_CONTENT);
    bool bSourceFileStillExists = SQFile::Exists(SOURCE_FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bDestinationFileContentHasNotChanged);
}

/// <summary>
/// Checks that source file is moved when the destination is empty and the replace flag is False.
/// </summary>
QTEST_CASE ( Move_SourceFileIsMovedWhenDestinationIsEmptyAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToMove3.txt
    // -./MoveDestinationEmpty/

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToMove3.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/");
    const QPath EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/FileToMove3.txt");
    const string_q EXPECTED_FILE_CONTENT("MOVED");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_Success;
    const bool INPUT_REPLACE = false;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SQFileTestHelper(EXPECTED_FILE_PATH, false);

    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bDestinationFileExists = SQFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bSourceFileDoesntExist = !SQFile::Exists(SOURCE_FILE_PATH, existsErrorCode);
    bool bContentExists = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileDoesntExist);
    BOOST_CHECK(bContentExists);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a file.
/// </summary>
QTEST_CASE ( Move_AssertionFailsWhenSourcePathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SQFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the destination path does not refer to a directory.
/// </summary>
QTEST_CASE ( Move_AssertionFailsWhenDestinationPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SQFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the source file does not exist.
/// </summary>
QTEST_CASE ( Rename_SourceFileDoesNotExist_Test )
{
    // [Preparation]
    const QPath EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    QPath sourceFile = EXPECTED_NEW_FILE_PATH;
    const string_q NEW_NAME("RenamedFile");
    const bool REPLACE_EXTENSION = true;
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_DoesNotExist;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

/// <summary>
/// Checks that it returns AlreadyExists when the there is already a file with the same name.
/// </summary>
QTEST_CASE ( Rename_AFileWithSameNameAlreadyExists_Test )
{
    // Assuming the existence of:
    // -./FileToRename.txt
    // -./ExistingRenamedFile.txt

    // [Preparation]
    const QPath EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToRename.txt");
    QPath sourceFile = EXPECTED_NEW_FILE_PATH;
    const string_q NEW_NAME("ExistingRenamedFile.txt");
    const bool REPLACE_EXTENSION = true;
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_AlreadyExists;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

/// <summary>
/// Checks that it returns the new path when the file is successfully renamed.
/// </summary>
QTEST_CASE ( Rename_ItReturnsNewPathWhenFileIsRenamed_Test )
{
    // Assuming the existence of:
    // -./FileToRename2.txt

    // [Preparation]
    const QPath EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./RenamedFile2.txt");
    QPath sourceFile(PATH_TO_ARTIFACTS + "./FileToRename2.txt");
    const string_q NEW_NAME("RenamedFile2.txt");
    const bool REPLACE_EXTENSION = true;
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_Success;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bRenamedFileExists = SQFile::Exists(sourceFile, existsErrorCode);
    BOOST_CHECK(bRenamedFileExists);
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

/// <summary>
/// Checks that the extension of the file is not modified when the input flag is False.
/// </summary>
QTEST_CASE ( Rename_ExtensionIsNotReplacedWhenInputFlagIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToRename3.txt

    // [Preparation]
    const QPath EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./RenamedFile3.txt");
    QPath sourceFile(PATH_TO_ARTIFACTS + "./FileToRename3.txt");
    const string_q NEW_NAME("RenamedFile3");
    const bool REPLACE_EXTENSION = false;
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_Success;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bRenamedFileExists = SQFile::Exists(sourceFile, existsErrorCode);
    BOOST_CHECK(bRenamedFileExists);
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a file.
/// </summary>
QTEST_CASE ( Rename_AssertionFailsWhenSourcePathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    QPath sourceFile(PATH_TO_ARTIFACTS + "./NotAFile/");
    const string_q NEW_NAME("RenamedFile");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SQFile::Rename(sourceFile, NEW_NAME, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the source file does not exist.
/// </summary>
QTEST_CASE ( Copy_SourceFileDoesNotExist_Test )
{
    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_DoesNotExist;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the destination directory does not exist.
/// </summary>
QTEST_CASE ( Copy_DestinationDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_DoesNotExist;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that source file is copied when the destination has a directory with the same name and the replace flag is True.
/// </summary>
QTEST_CASE ( Copy_SourceFileIsCopiedWhenDestinationHasContentWithSameNameAndReplaceIsTrue_Test )
{
    // Assuming the existence of:
    // -./FileToCopy.txt
    // -./CopyDestinationWithSameFile/FileToCopy,txt

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToCopy.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile/");
    const QPath EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile/FileToCopy.txt");
    const string_q EXPECTED_FILE_CONTENT("COPIED");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SQFileTestHelper(EXPECTED_FILE_PATH, false);

    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bDestinationFileExists = SQFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bSourceFileStillExists = SQFile::Exists(SOURCE_FILE_PATH, existsErrorCode);
    bool bContentExists = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bContentExists);
}

/// <summary>
/// Checks that source file is not copied when the destination contains a file with the same name and the replace flag is False.
/// </summary>
QTEST_CASE ( Copy_SourceFileIsNotCopiedWhenDestinationHasContentWithSameNameAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToCopy2.txt
    // -./CopyDestinationWithSameFile2/FileToCopy2,txt

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToCopy2.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile2/");
    const QPath EXPECTED_CONTENT = QPath(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile2/FileToCopy2.txt");
    const string_q EXPECTED_NOT_REPLACED_FILE_CONTENT = string_q::GetEmpty();
    const string_q EXPECTED_COPIED_FILE_CONTENT("COPIED");
    
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_AlreadyExists;
    const bool INPUT_REPLACE = false;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bDestinationFileContentHasNotChanged = CheckFileContent(EXPECTED_CONTENT, EXPECTED_NOT_REPLACED_FILE_CONTENT);
    bool bSourceFileStillExists = SQFile::Exists(SOURCE_FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bDestinationFileContentHasNotChanged);
}

/// <summary>
/// Checks that source file is copied when the destination is empty and the replace flag is False.
/// </summary>
QTEST_CASE ( Copy_SourceFileAndContentAreCopiedWhenDestinationIsEmptyAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToCopy3.txt
    // -./CopyDestinationEmpty/

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToCopy3.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/");
    const QPath EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/FileToCopy3.txt");
    const string_q EXPECTED_FILE_CONTENT("COPIED");
    const EQFileSystemError EXPECTED_RESULT = EQFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;

    // [Execution]
    EQFileSystemError errorCode = SQFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SQFileTestHelper(EXPECTED_FILE_PATH, false);

    EQFileSystemError existsErrorCode = EQFileSystemError::E_Success;
    bool bDestinationFileExists = SQFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bSourceFileStillExists = SQFile::Exists(SOURCE_FILE_PATH, existsErrorCode);
    bool bContentExists = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bContentExists);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a file.
/// </summary>
QTEST_CASE ( Copy_AssertionFailsWhenSourcePathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SQFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the destination path does not refer to a directory.
/// </summary>
QTEST_CASE ( Copy_AssertionFailsWhenDestinationPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const QPath SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const QPath DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SQFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns False when the file does not exist.
/// </summary>
QTEST_CASE ( Exists_ReturnsFalseWhenFileDoesNotExist_Test )
{
    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const bool EXPECTED_VALUE = false;
    const EQFileSystemError EXPECTED_ERRORCODE = EQFileSystemError::E_Success;
    EQFileSystemError errorCode = EQFileSystemError::E_Success;

    // [Execution]
    bool bReturnedValue = SQFile::Exists(FILE_PATH, errorCode);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bReturnedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when the file exists.
/// </summary>
QTEST_CASE ( Exists_ReturnsTrueWhenFileExists_Test )
{
    // Assumes the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const bool EXPECTED_VALUE = true;
    const EQFileSystemError EXPECTED_ERRORCODE = EQFileSystemError::E_Success;
    EQFileSystemError errorCode = EQFileSystemError::E_Success;

    // [Execution]
    bool bReturnedValue = SQFile::Exists(FILE_PATH, errorCode);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bReturnedValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a file.
/// </summary>
QTEST_CASE ( Exists_AssertionFailsWhenInputPathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const QPath NOT_A_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        EQFileSystemError errorCode = EQFileSystemError::E_Success;
        SQFile::Exists(NOT_A_FILE_PATH, errorCode);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist.
/// </summary>
QTEST_CASE ( GetFileInfo_FileDoesNotExist_Test )
{
    using Kinesis::QuimeraEngine::System::IO::FileSystem::QFileInfo;
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;

    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");

    const EQFileSystemError EXPECTED_ERRORCODE = EQFileSystemError::E_DoesNotExist;
    EQFileSystemError errorCode = EQFileSystemError::E_DoesNotExist;

    // [Execution]
    QFileInfo dirInfo = SQFile::GetFileInfo(FILE_PATH, errorCode);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns expected information when the file exists.
/// </summary>
QTEST_CASE ( GetFileInfo_ReturnsExpectedInformationWhenFileExists_Test )
{
    using Kinesis::QuimeraEngine::System::IO::FileSystem::QFileInfo;
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;

    // Assumes the existence of:
    // -./ExistingFile.txt (6 bytes length)

    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const u64_q EXPECTED_FILESIZE = 6;
    const bool EXPECTED_READONLY_FLAG = false;
    const EQFileSystemError EXPECTED_ERRORCODE = EQFileSystemError::E_Success;
    EQFileSystemError errorCode = EQFileSystemError::E_Success;

    // [Execution]
    QFileInfo fileInfo = SQFile::GetFileInfo(FILE_PATH, errorCode);
    
    // [Verification]
    bool bContainsCorrectPath = fileInfo.GetPath() == FILE_PATH;
    bool bCreationDateTimeIsNotUndefined = !fileInfo.GetCreationDate().IsUndefined();
    bool bLastModificationDateTimeIsNotUndefined = !fileInfo.GetCreationDate().IsUndefined();
    u64_q uFileSize = fileInfo.GetSize();
    bool bIsReadOnly = fileInfo.IsReadOnly();
    
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(bContainsCorrectPath);
    BOOST_CHECK(bCreationDateTimeIsNotUndefined);
    BOOST_CHECK(bLastModificationDateTimeIsNotUndefined);
    BOOST_CHECK_EQUAL(uFileSize, EXPECTED_FILESIZE);
    BOOST_CHECK_EQUAL(bIsReadOnly, EXPECTED_READONLY_FLAG);
}

/// <summary>
/// Checks that the read-only flag is True when the file is read-only.
/// </summary>
QTEST_CASE ( GetFileInfo_ReadyOnlyFlagIsTrueWhenFileIsReadOnly_Test )
{
    using Kinesis::QuimeraEngine::System::IO::FileSystem::QFileInfo;
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // Assumes the existence of:
    // -./ReadOnlyFile.txt

    // [Preparation]
    const QPath FILE_PATH(PATH_TO_ARTIFACTS + "./ReadOnlyFile.txt");
    const bool EXPECTED_READONLY_FLAG = true;
    const EQFileSystemError EXPECTED_ERRORCODE = EQFileSystemError::E_Success;
    EQFileSystemError errorCode = EQFileSystemError::E_Success;

    // Sets the file as read only
#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    static const EQTextEncoding PATH_ENCODING = EQTextEncoding::E_UTF8;
#elif defined(QE_OS_WINDOWS)
    static const EQTextEncoding PATH_ENCODING = string_q::GetLocalEncodingUTF16();
#endif

    QBasicArray<i8_q> arBytesFile = FILE_PATH.ToString().ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesFile.Get();
    boost::filesystem::path filePath(szPath);

    boost::system::error_code permissionsErrorCode;
    boost::filesystem::permissions(filePath, boost::filesystem::remove_perms | boost::filesystem::owner_write, permissionsErrorCode);

    // [Execution]
    QFileInfo fileInfo = SQFile::GetFileInfo(FILE_PATH, errorCode);
    
    // [Verification]
    bool bIsReadOnly = fileInfo.IsReadOnly();
    
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bIsReadOnly, EXPECTED_READONLY_FLAG);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a file.
/// </summary>
QTEST_CASE ( GetFileInfo_AssertionFailsWhenInputPathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const QPath NOT_A_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        EQFileSystemError errorCode = EQFileSystemError::E_Success;
        SQFile::GetFileInfo(NOT_A_FILE_PATH, errorCode);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: SQFile
QTEST_SUITE_END()
