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

#include "SQFile.h"

#include "Assertions.h"
#include "EQTextEncoding.h"
#include "QDateTime.h"
#include "QLocalTimeZone.h"
#include "QStopwatch.h"
#include "SQThisThread.h"

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
#elif defined(QE_OS_MAC)
    #include <sys/attr.h>
    #include <unistd.h>
#endif

using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;
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

EQFileSystemError SQFile::Delete(const QPath &file)
{
    QE_ASSERT_ERROR(file.IsFile(), string_q("The input path (\"") + file.ToString() + "\") must refer to a file.");

    boost::filesystem::path filePath = SQFile::_ConvertToBoostPath(file);

    EQFileSystemError eErrorCode = EQFileSystemError::E_Success;

    if(SQFile::Exists(file, eErrorCode) && eErrorCode == EQFileSystemError::E_Success) // This check is necessary because remove does not return an error when the file does not exist
    {
        boost::system::error_code removeErrorCode;
        boost::filesystem::remove(filePath, removeErrorCode);
        eErrorCode = SQFile::_ConvertErrorCodeToFileSystemError(removeErrorCode);
    }
    else if(eErrorCode == EQFileSystemError::E_Success)
    {
        eErrorCode = EQFileSystemError::E_DoesNotExist;
    }

    return eErrorCode;
}

EQFileSystemError SQFile::Move(const QPath &file, const QPath& newLocation, const bool bReplace)
{
    QE_ASSERT_ERROR(file.IsFile(), string_q("The source path (\"") + file.ToString() + "\") must refer to a file.");
    QE_ASSERT_ERROR(newLocation.IsDirectory(), string_q("The destination path (\"") + newLocation.ToString() + "\") must refer to a directory.");

    QPath destination = newLocation;
    destination.SetFilenameAndExtension(file.GetFilename());

    EQFileSystemError eErrorCode = EQFileSystemError::E_Success;
    
    if(!SQFile::Exists(destination, eErrorCode) || bReplace)
    {
        // Moves and replaces the file
        if(eErrorCode == EQFileSystemError::E_Success)
        {
            // The copy first
            eErrorCode = SQFile::Copy(file, newLocation, bReplace);

            // Then the deletion of the original directory
            if(eErrorCode == EQFileSystemError::E_Success)
            {
                SQFile::_WaitForCreation(SQFile::_ConvertToBoostPath(destination));

                eErrorCode = SQFile::Delete(file);
            }
        }
    }
    else
    {
        eErrorCode = EQFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EQFileSystemError SQFile::Rename(QPath &file, const string_q &strNewFileName, const bool bRenameExtension)
{
    QE_ASSERT_ERROR(file.IsFile(), string_q("The input path (\"") + file.ToString() + "\") must refer to a file.");

    QPath renamedPath = file;

    if(bRenameExtension)
        renamedPath.SetFilenameAndExtension(strNewFileName);
    else
        renamedPath.SetFilename(strNewFileName);

    EQFileSystemError eErrorCode = EQFileSystemError::E_Success;

    if(!SQFile::Exists(renamedPath, eErrorCode)) // This check is necessary because rename returns "success" instead of "already exists" when there is already a file with the target name
    {
        boost::filesystem::path filePath = SQFile::_ConvertToBoostPath(file);
        boost::filesystem::path newFilePath = SQFile::_ConvertToBoostPath(renamedPath);

        boost::system::error_code renameErrorCode;
        boost::filesystem::rename(filePath, newFilePath, renameErrorCode);

        if(renameErrorCode == boost::system::posix_error::success)
        {
            file = renamedPath;
        }

        eErrorCode = SQFile::_ConvertErrorCodeToFileSystemError(renameErrorCode);
    }
    else
    {
        eErrorCode = EQFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EQFileSystemError SQFile::Copy(const QPath &file, const QPath& locationToCopyTo, const bool bReplace)
{
    QE_ASSERT_ERROR(file.IsFile(), string_q("The source path (\"") + file.ToString() + "\") must refer to a file.");
    QE_ASSERT_ERROR(locationToCopyTo.IsDirectory(), string_q("The destination path (\"") + locationToCopyTo.ToString() + "\") must refer to a directory.");

    // Paths transformations
    QPath absoluteDirectory = file.GetAbsolutePath();
    QPath absoluteLocationToCopyTo = locationToCopyTo.GetAbsolutePath();
    absoluteLocationToCopyTo.SetFilenameAndExtension(file.GetFilename());

    boost::filesystem::path filePath = SQFile::_ConvertToBoostPath(absoluteDirectory);
    boost::filesystem::path newLocationPath = SQFile::_ConvertToBoostPath(absoluteLocationToCopyTo);

    // Copies the directory
    const boost::filesystem::copy_option COPY_OPTION(bReplace ? boost::filesystem::copy_option::overwrite_if_exists : 
                                                                boost::filesystem::copy_option::fail_if_exists);
    boost::system::error_code copyErrorCode;
    boost::filesystem::copy_file(filePath, newLocationPath, COPY_OPTION, copyErrorCode);

    return SQFile::_ConvertErrorCodeToFileSystemError(copyErrorCode);
}

bool SQFile::Exists(const QPath &file, EQFileSystemError& eErrorInfo)
{
    QE_ASSERT_ERROR(file.IsFile(), string_q("The input path (\"") + file.ToString() + "\") must refer to a file.");

    boost::filesystem::path filePath = SQFile::_ConvertToBoostPath(file);

    boost::system::error_code errorCode;
    bool bExists = boost::filesystem::exists(filePath, errorCode);

    eErrorInfo = SQFile::_ConvertErrorCodeToFileSystemError(errorCode);

    if(eErrorInfo == EQFileSystemError::E_DoesNotExist)
        eErrorInfo = EQFileSystemError::E_Success;

    return bExists;
}

QFileInfo SQFile::GetFileInfo(const QPath &file, EQFileSystemError &eErrorInfo)
{
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
    using Kinesis::QuimeraEngine::System::Timing::QLocalTimeZone;

    QE_ASSERT_ERROR(file.IsFile(), string_q("The input path (\"") + file.ToString() + "\") must refer to a file.");

    boost::filesystem::path filePath = SQFile::_ConvertToBoostPath(file);
    uintmax_t uFileSize = 0;
    QDateTime lastModificationDateTime = QDateTime::GetUndefinedDate();
    QDateTime creationDateTime = QDateTime::GetUndefinedDate();
    bool bIsReadOnly = false;

    // Gets the size of the file
    boost::system::error_code errorCode;
    uFileSize = boost::filesystem::file_size(filePath, errorCode);

    // Gets the last modification date and time
    if(errorCode == boost::system::posix_error::success)
    {
        // Number of seconds passed since 01/01/1970
        time_t lastModificationTime = boost::filesystem::last_write_time(filePath, errorCode);

        if(errorCode == boost::system::posix_error::success)
        {
            static const QDateTime EPOCH(1970, 1, 1);
            QTimeSpan seconds(0, 0, 0, lastModificationTime, 0, 0, 0);
            lastModificationDateTime = QDateTime(EPOCH + seconds, QLocalTimeZone().Get());
        }
    }

    // Gets the creation date and time
    if(errorCode == boost::system::posix_error::success)
    {
#if defined(QE_OS_LINUX)
        // There is no way to get the creation date of a file on Linux
        creationDateTime = lastModificationDateTime;
#else
        creationDateTime = QDateTime(SQFile::_GetFileCreationDateTime(file), QLocalTimeZone().Get());
#endif
    }

    // Gets the file permissions
    if(errorCode == boost::system::posix_error::success)
    {
        boost::filesystem::file_status fileStatus = boost::filesystem::status(filePath, errorCode);

        if(errorCode == boost::system::posix_error::success)
        {
            boost::filesystem::perms eFilePermissions = fileStatus.permissions();
            bIsReadOnly = (eFilePermissions & boost::filesystem::owner_write) == 0;
        }
    }

    eErrorInfo = SQFile::_ConvertErrorCodeToFileSystemError(errorCode);

    return QFileInfo(file, uFileSize, creationDateTime, lastModificationDateTime, bIsReadOnly);
}

boost::filesystem::path SQFile::_ConvertToBoostPath(const QPath &pathToConvert)
{
#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    static const EQTextEncoding PATH_ENCODING = EQTextEncoding::E_UTF8;
#elif defined(QE_OS_WINDOWS)
    static const EQTextEncoding PATH_ENCODING = string_q::GetLocalEncodingUTF16();
#endif

    QBasicArray<i8_q> arBytesDirectory = pathToConvert.ToString().ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesDirectory.Get();
    return boost::filesystem::path(szPath);
}

string_q SQFile::_ConvertPathToString(const boost::filesystem::path &pathToConvert)
{
#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    return string_q(pathToConvert.c_str(), strlen(pathToConvert.c_str()), EQTextEncoding::E_UTF8);
#elif defined(QE_OS_WINDOWS)
    return string_q((i8_q*)pathToConvert.c_str(), wcslen(pathToConvert.c_str()) * sizeof(boost::filesystem::path::value_type), string_q::GetLocalEncodingUTF16());
#endif
}

EQFileSystemError SQFile::_ConvertErrorCodeToFileSystemError(const boost::system::error_code &errorCode)
{
    EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
    boost::system::error_condition posixError = errorCode.default_error_condition();

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

bool SQFile::_WaitForCreation(const boost::filesystem::path &filePath)
{
    using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
    using Kinesis::QuimeraEngine::System::Timing::QStopwatch;
    using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

    static const u64_q MAXIMUM_WAIT_TIME = 600ULL; // milliseconds

    QStopwatch elapsedTime;
    elapsedTime.Set();
    bool bTooMuchTime = false;

    while(!boost::filesystem::exists(filePath) && !bTooMuchTime)
    {
        SQThisThread::Yield(); // [TODO] Thund: Use SQThisThread when it exists
        bTooMuchTime = elapsedTime.GetElapsedTimeAsTimeSpan().GetMilliseconds() < MAXIMUM_WAIT_TIME;
    }

    QE_ASSERT_ERROR(!bTooMuchTime, "The timeout expired, the file or directory could not be created or deleted fast enough.");

    return !bTooMuchTime;
}

#if defined(QE_OS_WINDOWS)

Kinesis::QuimeraEngine::Tools::Time::QDateTime SQFile::_GetFileCreationDateTime(const QPath &file)
{
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

    // GetFileAttributesExW returns the number of hundreds of nanosecond since January 1, 1601 (UTC)
    static const QDateTime SYSTEM_EPOCH(1601, 1, 1);

    // Gets the raw data from the system
    WIN32_FILE_ATTRIBUTE_DATA fileAttributes;
    QBasicArray<i8_q> arPathString = file.ToString().ToBytes(string_q::GetLocalEncodingUTF16());
    BOOL bResult = GetFileAttributesExW(rcast_q(arPathString.Get(), wchar_t*), GetFileExInfoStandard, &fileAttributes);

    QE_ASSERT_ERROR(bResult != 0, "An unexpected error ocurred when obtaining the file attributes.");
    
    // Uses an intermediate structure to extract the number of hundreds of nanoseconds
    ULARGE_INTEGER uTimePassedSinceEpochInHundredsOfNanoseconds;
    uTimePassedSinceEpochInHundredsOfNanoseconds.LowPart = fileAttributes.ftCreationTime.dwLowDateTime;
    uTimePassedSinceEpochInHundredsOfNanoseconds.HighPart = fileAttributes.ftCreationTime.dwHighDateTime;

    // Builds a time span from the obtained data
    QTimeSpan uTimeSinceEpoch(uTimePassedSinceEpochInHundredsOfNanoseconds.QuadPart);

    // The result is the system epoch plus the time passed since then
    return SYSTEM_EPOCH + uTimeSinceEpoch;
}

#elif defined(QE_OS_MAC)

Kinesis::QuimeraEngine::Tools::Time::QDateTime SQFile::_GetFileCreationDateTime(const QPath &file)
{
    using Kinesis::QuimeraEngine::Tools::Time::QDateTime;
    using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
    
    // getattrlist returns the number of seconds since January 1, 1970 (UTC)
    static const QDateTime SYSTEM_EPOCH(1970, 1, 1);

    struct FileCreationDataStructure
    {
        uint32_t length;
        timespec creationTime;
    };

    struct attrlist al;
    al.bitmapcount = ATTR_BIT_MAP_COUNT;
    al.reserved = 0;
    al.commonattr = ATTR_CMN_CRTIME;
    al.volattr = 0;
    al.dirattr = 0;
    al.fileattr = 0;
    al.forkattr = 0;
    
    QBasicArray<i8_q> arPathString = file.ToString().ToBytes(EQTextEncoding::E_UTF8);
    FileCreationDataStructure fileCreationData;
    int nResult = getattrlist(arPathString.Get(), &al, &fileCreationData, sizeof(fileCreationData), FSOPT_REPORT_FULLSIZE);
    
    QE_ASSERT_ERROR(nResult == 0, "An unexpected error ocurred when obtaining the file attributes.");
    
    return SYSTEM_EPOCH + QTimeSpan(0, 0, 0, fileCreationData.creationTime.tv_sec, 0, 0, 0);
}

#endif

} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
