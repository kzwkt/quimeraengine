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

#include "SQDirectory.h"

#include "EQTextEncoding.h"
#include "EQComparisonType.h"
#include "QTimeZone.h"
#include "QLocalTimeZone.h"
#include "Assertions.h"
#include "QStopwatch.h"
#include "SQThisThread.h"

using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
using Kinesis::QuimeraEngine::Common::DataTypes::QArrayResult;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace IO
{
namespace FileSystem
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

EQFileSystemError SQDirectory::Delete(const QPath &directory)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(directory);

    EQFileSystemError eErrorCode = EQFileSystemError::E_Success;
    boost::system::error_code removeErrorCode;

    if(SQDirectory::Exists(directory, eErrorCode) && eErrorCode == EQFileSystemError::E_Success) // This check is necessary because remove_all does not return an error when the directory does not exist
    {
        boost::filesystem::remove_all(directoryPath, removeErrorCode);
        eErrorCode = SQDirectory::_ConvertErrorCodeToFileSystemError(removeErrorCode);
    }
    else
    {
        eErrorCode = EQFileSystemError::E_DoesNotExist;
    }

    return eErrorCode;
}

EQFileSystemError SQDirectory::Move(const QPath &directory, const QPath &newLocation, const bool bReplaceContent)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The source path (\"") + directory.ToString() + "\") must refer to a directory.");
    QE_ASSERT_ERROR(newLocation.IsDirectory(), string_q("The destination path (\"") + newLocation.ToString() + "\") must refer to a directory.");

    // Note: It would be faster to call rename() when the destination path does not exist but it fails when using different drive letters in source and destination paths

    QPath destination = newLocation;
    destination.AppendDirectory(directory.GetLastDirectory());

    EQFileSystemError eErrorCode = EQFileSystemError::E_Success;

    if(!SQDirectory::Exists(destination, eErrorCode) || bReplaceContent)
    {
        // Moves and replaces the directory
        if(eErrorCode == EQFileSystemError::E_Success)
        {
            // The copy first
            eErrorCode = SQDirectory::Copy(directory, newLocation, bReplaceContent);

            // Then the deletion of the original directory
            if(eErrorCode == EQFileSystemError::E_Success)
            {
                static const bool WAIT_FOR_DIRECTORY_CREATION = false;
                SQDirectory::_WaitForCreationOrDeletion(SQDirectory::_ConvertToBoostPath(destination), WAIT_FOR_DIRECTORY_CREATION);

                eErrorCode = SQDirectory::Delete(directory);
            }
        }
    }
    else
    {
        eErrorCode = EQFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EQFileSystemError SQDirectory::Rename(QPath &directory, const string_q &strNewDirectoryName)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    QPath renamedPath = directory;
    renamedPath.RemoveLastDirectory();
    renamedPath.AppendDirectory(strNewDirectoryName);

    EQFileSystemError eErrorCode = EQFileSystemError::E_Success;

    if(!SQDirectory::Exists(renamedPath, eErrorCode)) // This check is necessary because rename returns "no permissions" instead of "already exists" when there is already a directory with the target name
    {
        boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(directory);
        boost::filesystem::path newDirectoryPath = SQDirectory::_ConvertToBoostPath(renamedPath);

        boost::system::error_code renameErrorCode;
        boost::filesystem::rename(directoryPath, newDirectoryPath, renameErrorCode);

        if(renameErrorCode == boost::system::posix_error::success)
        {
            directory = renamedPath;
        }

        eErrorCode = SQDirectory::_ConvertErrorCodeToFileSystemError(renameErrorCode);
    }
    else
    {
        eErrorCode = EQFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EQFileSystemError SQDirectory::Copy(const QPath &directory, const QPath& locationToCopyTo, const bool bReplaceContent)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The source path (\"") + directory.ToString() + "\") must refer to a directory.");
    QE_ASSERT_ERROR(locationToCopyTo.IsDirectory(), string_q("The destination path (\"") + locationToCopyTo.ToString() + "\") must refer to a directory.");

    // Paths transformations
    QPath absoluteDirectory = directory.GetAbsolutePath();
    QPath absoluteLocationToCopyTo = locationToCopyTo.GetAbsolutePath();
    absoluteLocationToCopyTo.AppendDirectory(absoluteDirectory.GetLastDirectory());

    boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(absoluteDirectory);
    boost::filesystem::path newLocationPath = SQDirectory::_ConvertToBoostPath(absoluteLocationToCopyTo);

    EQFileSystemError eErrorCode = EQFileSystemError::E_Success;

    // Copies the directory
    boost::system::error_code copyErrorCode;
    boost::filesystem::copy_directory(directoryPath, newLocationPath, copyErrorCode);

    // If the destination folder already exists, it is not cosidered an error
    eErrorCode = copyErrorCode.default_error_condition() == boost::system::posix_error::file_exists ? 
                                                                        EQFileSystemError(EQFileSystemError::E_Success) : 
                                                                        SQDirectory::_ConvertErrorCodeToFileSystemError(copyErrorCode);
    
    if(eErrorCode == EQFileSystemError::E_Success)
    {
        // Copies the content of the directory
        boost::filesystem::recursive_directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::recursive_directory_iterator endOfContent;
        const boost::filesystem::copy_option COPY_OPTION(bReplaceContent ? boost::filesystem::copy_option::overwrite_if_exists : 
                                                                           boost::filesystem::copy_option::fail_if_exists
                                                        );

        while((eErrorCode == EQFileSystemError::E_Success || eErrorCode == EQFileSystemError::E_AlreadyExists) && currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            string_q strCurrentDirOrFilePath = SQDirectory::_ConvertPathToString(currentDirOrFilePath);

            // If the current element is a directory, it adds a trailing separator (this is necessary to adapt Boost's paths)
            bool bIsDirectory = boost::filesystem::is_directory(currentDirOrFilePath);
        
            if(bIsDirectory)
                strCurrentDirOrFilePath.Append(QPath::GetPathSeparator());

            // Compounds a path as if the file or directory was already copied to the destination
            QPath destinationFileOrDir(absoluteLocationToCopyTo.ToString() + QPath(absoluteDirectory).GetRelativePathTo(strCurrentDirOrFilePath) + QPath(strCurrentDirOrFilePath).GetFilename());

            // Copies the current file or directory
            boost::filesystem::path destinationPath = SQDirectory::_ConvertToBoostPath(destinationFileOrDir);
            copyErrorCode.clear();

            if(bIsDirectory && !SQDirectory::Exists(destinationFileOrDir, eErrorCode) && eErrorCode == EQFileSystemError::E_Success)
                // Copies the directory if it does not exist
                boost::filesystem::copy_directory(currentDirOrFilePath, destinationPath, copyErrorCode);
            else if(!bIsDirectory)
                // Copies the file and overwrites if it has to
                boost::filesystem::copy_file(currentDirOrFilePath, destinationPath, COPY_OPTION, copyErrorCode);

            static const bool WAIT_FOR_DIRECTORY_CREATION = false;

            if(copyErrorCode != boost::system::posix_error::success)
                // An error occurred
                eErrorCode = SQDirectory::_ConvertErrorCodeToFileSystemError(copyErrorCode);
            else if(bIsDirectory)
                // Waits until the directory has been created
                SQDirectory::_WaitForCreationOrDeletion(destinationPath, WAIT_FOR_DIRECTORY_CREATION);

            ++currentDirOrFile;
        }
    }

    return eErrorCode;
}

QPath SQDirectory::GetCurrentWorkingDirectory()
{
    // Note: Interesting article about the variable PATH_MAX http://insanecoding.blogspot.com.es/2007/11/pathmax-simply-isnt.html
    // Note: Interesting article about working directories on Windows http://blogs.msdn.com/b/oldnewthing/archive/2010/10/11/10073890.aspx

    //  This is an alternative to Boost
    //
    //#if defined(QE_OS_WINDOWS)
    //    #include <Windows.h>
    //#else
    //    #include <unistd.h>
    //#endif
    //
    //    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    //
    //    string_q strPath;
    //
    //#if defined(QE_OS_WINDOWS)
    //    DWORD uPathLength = ::GetCurrentDirectoryW(0, null_q);
    //    wchar_t* arCharacters = new wchar_t[uPathLength + 1U];
    //    ::GetCurrentDirectoryW(uPathLength, arCharacters);
    //
    //    strPath = string_q(rcast_q(arCharacters, char*), uPathLength * sizeof(wchar_t), EQTextEncoding::E_UTF16LE);
    //    delete[] arCharacters;
    //#elif defined(_GNU_SOURCE)
    //    char* arCharacters = ::get_current_dir_name();
    //    pointer_uint_q uPathLength = strlen(arCharacters);
    //    strPath = string_q(arCharacters, uPathLength, EQTextEncoding::E_UTF8);
    //    free(arCharacters);
    //#else
    //    char* arCharacters = ::getcwd(null_q, 0);
    //    pointer_uint_q uPathLength = strlen(arCharacters);
    //    strPath = string_q(arCharacters, uPathLength, EQTextEncoding::E_UTF8);
    //    free(arCharacters);
    //#endif
    //
    //    // Adds a trailing slash if it does not end with one
    //    if(!strPath.IsEmpty() && strPath.Substring(strPath.GetLength() - QPath::GetPathSeparator().GetLength()) != QPath::GetPathSeparator())
    //        strPath.Append(QPath::GetPathSeparator());
    //
    //    return QPath(strPath);

    boost::system::error_code eErrorCode;
    boost::filesystem::path directoryPath = boost::filesystem::current_path(eErrorCode);

    QE_ASSERT_ERROR(eErrorCode == boost::system::posix_error::success, "An unexpected error occurred when retrieving the current working directory.");

    return QPath(SQDirectory::_ConvertPathToString(directoryPath) + QPath::GetPathSeparator());
}

void SQDirectory::SetCurrentWorkingDirectory(const QPath& newDirectory, EQFileSystemError& eErrorInfo)
{
    QE_ASSERT_ERROR(newDirectory.IsDirectory(), string_q("The input path (\"") + newDirectory.ToString() + "\") must refer to a directory.");

    boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(newDirectory);

    boost::system::error_code errorCode;
    boost::filesystem::current_path(directoryPath, errorCode);

    eErrorInfo = SQDirectory::_ConvertErrorCodeToFileSystemError(errorCode);
}

bool SQDirectory::Exists(const QPath &directory, EQFileSystemError& eErrorInfo)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(directory);

    boost::system::error_code eErrorCode;
    bool bExists = boost::filesystem::exists(directoryPath, eErrorCode);

    eErrorInfo = SQDirectory::_ConvertErrorCodeToFileSystemError(eErrorCode);

    if(eErrorInfo == EQFileSystemError::E_DoesNotExist)
        eErrorInfo = EQFileSystemError::E_Success;

    return bExists;
}

QDirectoryInfo SQDirectory::GetDirectoryInfo(const QPath& directory, EQFileSystemError& eErrorInfo)
{
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
    using Kinesis::QuimeraEngine::System::Timing::QLocalTimeZone;

    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    QDateTime creationDateTime;

    boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(directory);

    // Number of seconds passed since 01/01/1970
    boost::system::error_code eErrorCode;
    time_t creationTime = boost::filesystem::last_write_time(directoryPath, eErrorCode);

    if(eErrorCode == boost::system::posix_error::success)
    {
        QTimeSpan seconds(0, 0, 0, creationTime, 0, 0, 0);
        static const QDateTime EPOCH(1970, 1, 1, QTimeZone::UTC);
        creationDateTime = QDateTime(EPOCH + seconds, QLocalTimeZone().Get());
    }

    eErrorInfo = SQDirectory::_ConvertErrorCodeToFileSystemError(eErrorCode);

    return QDirectoryInfo(directory, creationDateTime);
}

EQFileSystemError SQDirectory::Create(const QPath &directory, const string_q &strDirectoryName)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    boost::system::error_code errorCode;
    QPath newDirectory = directory;
    newDirectory.AppendDirectory(strDirectoryName);
    boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(newDirectory);
    boost::filesystem::create_directory(directoryPath, errorCode);

    return SQDirectory::_ConvertErrorCodeToFileSystemError(errorCode);
}

EQFileSystemError SQDirectory::GetFiles(const QPath &directory, Kinesis::QuimeraEngine::Tools::Containers::QArrayDynamic<QPath> &arFiles)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    EQFileSystemError eErrorInfo = EQFileSystemError::E_Success;

    if(SQDirectory::Exists(directory, eErrorInfo))
    {
        boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(directory);

        boost::filesystem::directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::directory_iterator endOfContent;

        while(currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            if(!boost::filesystem::is_directory(currentDirOrFilePath))
            {
                string_q strCurrentDirOrFilePath = SQDirectory::_ConvertPathToString(currentDirOrFilePath);
                arFiles.Add(strCurrentDirOrFilePath);
            }

            ++currentDirOrFile;
        }
    }
    else if(eErrorInfo == EQFileSystemError::E_Success)
    {
        eErrorInfo = EQFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

EQFileSystemError SQDirectory::GetFiles(const QPath &directory, Kinesis::QuimeraEngine::Tools::Containers::QArrayDynamic<QPath> &arFiles, const string_q &strExtensionFilter)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    EQFileSystemError eErrorInfo = EQFileSystemError::E_Success;

    if(SQDirectory::Exists(directory, eErrorInfo))
    {
        boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(directory);

        boost::filesystem::directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::directory_iterator endOfContent;

        while(currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            QPath fileOrDirectory(SQDirectory::_ConvertPathToString(currentDirOrFilePath));

#if defined(QE_OS_WINDOWS)
            static const EQComparisonType STRING_COMPARISON = EQComparisonType::E_CanonicalCaseInsensitive;
#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)
            static const EQComparisonType STRING_COMPARISON = EQComparisonType::E_CanonicalCaseSensitive;
#endif

            if(!boost::filesystem::is_directory(currentDirOrFilePath) && 
               fileOrDirectory.GetFileExtension().CompareTo(strExtensionFilter, STRING_COMPARISON) == 0)
                arFiles.Add(fileOrDirectory);

            ++currentDirOrFile;
        }
    }
    else if(eErrorInfo == EQFileSystemError::E_Success)
    {
        eErrorInfo = EQFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

EQFileSystemError SQDirectory::GetSubdirectories(const QPath &directory, Kinesis::QuimeraEngine::Tools::Containers::QArrayDynamic<QPath> &arDirectories)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    EQFileSystemError eErrorInfo = EQFileSystemError::E_Success;

    if(SQDirectory::Exists(directory, eErrorInfo))
    {
        boost::filesystem::path directoryPath = SQDirectory::_ConvertToBoostPath(directory);

        boost::filesystem::directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::directory_iterator endOfContent;

        while(currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            if(boost::filesystem::is_directory(currentDirOrFilePath))
            {
                string_q strCurrentDirOrFilePath = SQDirectory::_ConvertPathToString(currentDirOrFilePath);
                strCurrentDirOrFilePath.Append(QPath::GetPathSeparator());
                arDirectories.Add(strCurrentDirOrFilePath);
            }

            ++currentDirOrFile;
        }
    }
    else if(eErrorInfo == EQFileSystemError::E_Success)
    {
        eErrorInfo = EQFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

QPath SQDirectory::GetParentDirectory(const QPath &directory, EQFileSystemError &eErrorInfo)
{
    QE_ASSERT_ERROR(directory.IsDirectory(), string_q("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    eErrorInfo = EQFileSystemError::E_Success;
    QPath parentPath("./");

    if(SQDirectory::Exists(directory, eErrorInfo))
    {
        parentPath = QPath(directory.GetAbsolutePath());
        parentPath.RemoveLastDirectory();
    }
    else if(eErrorInfo == EQFileSystemError::E_Success)
    {
        eErrorInfo = EQFileSystemError::E_DoesNotExist;
    }

    return parentPath;
}

boost::filesystem::path SQDirectory::_ConvertToBoostPath(const QPath &pathToConvert)
{
#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    static const EQTextEncoding PATH_ENCODING = EQTextEncoding::E_UTF8;
#elif defined(QE_OS_WINDOWS)
    static const EQTextEncoding PATH_ENCODING = string_q::GetLocalEncodingUTF16();
#endif

    QArrayResult<i8_q> arBytesDirectory = pathToConvert.ToString().ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesDirectory.Get();
    return boost::filesystem::path(szPath);
}

string_q SQDirectory::_ConvertPathToString(const boost::filesystem::path &pathToConvert)
{
#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    return string_q(pathToConvert.c_str(), strlen(pathToConvert.c_str()), EQTextEncoding::E_UTF8);
#elif defined(QE_OS_WINDOWS)
    return string_q((i8_q*)pathToConvert.c_str(), wcslen(pathToConvert.c_str()) * sizeof(boost::filesystem::path::value_type), string_q::GetLocalEncodingUTF16());
#endif
}

EQFileSystemError SQDirectory::_ConvertErrorCodeToFileSystemError(const boost::system::error_code &eErrorCode)
{
    EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
    boost::system::error_condition posixError = eErrorCode.default_error_condition();

    if(posixError == boost::system::posix_error::success)
    {
        eErrorInfo = EQFileSystemError::E_Success;
    }
    else if(posixError == boost::system::posix_error::no_such_file_or_directory)
    {
        eErrorInfo = EQFileSystemError::E_DoesNotExist;
    }
    else if(posixError == boost::system::posix_error::file_exists)
    {
        eErrorInfo = EQFileSystemError::E_AlreadyExists;
    }
    else if(posixError == boost::system::posix_error::filename_too_long)
    {
        eErrorInfo = EQFileSystemError::E_NameIsTooLong;
    }
    else if(posixError == boost::system::posix_error::permission_denied)
    {
        eErrorInfo = EQFileSystemError::E_NoPermissions;
    }
    else if(posixError == boost::system::posix_error::file_too_large)
    {
        eErrorInfo = EQFileSystemError::E_FileIsTooLarge;
    }
    else if(posixError == boost::system::posix_error::no_space_on_device)
    {
        eErrorInfo = EQFileSystemError::E_NoSpaceInDevice;
    }
    else
    {
        eErrorInfo = EQFileSystemError::E_Unknown;
    }

    return eErrorInfo;
}

bool SQDirectory::_WaitForCreationOrDeletion(const boost::filesystem::path &directoryOrFilePath, const bool bTDeletionFCreation)
{
    using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
    using Kinesis::QuimeraEngine::System::Timing::QStopwatch;
    using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

    static const u64_q MAXIMUM_WAIT_TIME = 600ULL; // milliseconds

    QStopwatch elapsedTime;
    elapsedTime.Set();
    bool bTooMuchTime = false;

    while(boost::filesystem::exists(directoryOrFilePath) == bTDeletionFCreation && !bTooMuchTime)
    {
        SQThisThread::Yield();
        bTooMuchTime = elapsedTime.GetElapsedTimeAsTimeSpan().GetMilliseconds() < MAXIMUM_WAIT_TIME;
    }

    QE_ASSERT_ERROR(!bTooMuchTime, "The timeout expired, the file or directory could not be created or deleted fast enough.");

    return !bTooMuchTime;
}


} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
