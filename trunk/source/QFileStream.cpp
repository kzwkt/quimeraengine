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

#include "QFileStream.h"

#include "SQFile.h"
#include "QAlignment.h"
#include "SQInteger.h"
#include "EQTextEncoding.h"
#include <cstring>

#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <errno.h>
#endif

#if defined(QE_OS_MAC)
    typedef int error_t; // It exists on Linux but not on MacOSX
#endif

using Kinesis::QuimeraEngine::Common::Memory::QAlignment;
using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;
using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;


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
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float QFileStream::_REALLOCATION_FACTOR = 1.5f;


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QFileStream::QFileStream(const pointer_uint_q uInitialCapacity) :
                                                                m_path(string_q::GetEmpty()),
                                                                m_rwBuffer(uInitialCapacity, QAlignment(4U)), // 4-byte alignment since maximum supported character length is 4 bytes (UTF-32)
                                                                m_uFileSize(0),
                                                                m_uPositionPointer(0),
                                                                m_uBufferStartPosition(0),
                                                                m_uBufferVirtualSize(0),
                                                                m_bIsOpen(false),
                                                                m_bIsWritePending(false),
                                                                m_bWritingIsAllowed(false)
{
    m_rwBuffer.Allocate(uInitialCapacity);
}

QFileStream::QFileStream(const QPath &filePath, const EQFileOpenMode &eOpenMode, const pointer_uint_q uInitialCapacity, EQFileSystemError &eErrorInfo) : 
                                                                                      m_path(filePath),
                                                                                      m_rwBuffer(uInitialCapacity, QAlignment(4U)), // 4-byte alignment since maximum supported character length is 4 bytes (UTF-32)
                                                                                      m_uFileSize(0),
                                                                                      m_uPositionPointer(0),
                                                                                      m_uBufferStartPosition(0),
                                                                                      m_uBufferVirtualSize(0),
                                                                                      m_bIsOpen(false),
                                                                                      m_bIsWritePending(false),
                                                                                      m_bWritingIsAllowed(false)
{
    m_rwBuffer.Allocate(uInitialCapacity);
    eErrorInfo = this->Open(filePath, eOpenMode);
}
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QFileStream::~QFileStream()
{
    if(m_bIsOpen)
    {
        this->Close();
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QFileStream::Read(void* pOutput, const pointer_uint_q uOutputOffset, const pointer_uint_q uOutputSize)
{
    QE_ASSERT_ERROR(uOutputSize > 0, "The output size must not equal zero.");
    QE_ASSERT_ERROR(pOutput != null_q, "The output buffer cannot be null.");
    QE_ASSERT_ERROR(m_bIsOpen == true, "The file must be opened before reading.");

    using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

    const pointer_uint_q FUTURE_POSITION_POINTER = m_uPositionPointer + uOutputSize;

    QE_ASSERT_WARNING(FUTURE_POSITION_POINTER <= m_uFileSize, "Attempting to read from outside of the file.");

    // If the output size is greater than the remaining bytes, it is fixed so the next read position does not exceed the end of the file
    pointer_uint_q uClampedOutputSize = FUTURE_POSITION_POINTER > m_uFileSize ? scast_q(m_uFileSize, pointer_uint_q) - m_uPositionPointer :
                                                                                uOutputSize;

    u8_q* pOutputPosition = scast_q(pOutput, u8_q*) + uOutputOffset;

    // Flushes if the buffer is going to be discontinued
    this->_FlushIfPositionDoesNotBelongToBuffer();

    // Calculates the relative position in the read/write buffer. Note: After flushing, operands below are equal and result is zero. The first will never be lower than the second.
    pointer_uint_q uPositionInBuffer = m_uPositionPointer - m_uBufferStartPosition;

    // Reallocates the read/write buffer if necessary
    pointer_uint_q uBytesFromPositionToEndOfAllocatedMemory = m_rwBuffer.GetSize() - uPositionInBuffer;
    if(uBytesFromPositionToEndOfAllocatedMemory < uClampedOutputSize)
    {
        pointer_uint_q uExceedingBytes = uClampedOutputSize - uBytesFromPositionToEndOfAllocatedMemory;
        pointer_uint_q uPreviousSize = m_rwBuffer.GetSize();
        this->_ReallocateByFactor(uPreviousSize + uExceedingBytes);
        m_rwBuffer.Allocate(m_rwBuffer.GetSize() - uPreviousSize);
    }

    u8_q* pPositionInBuffer = scast_q(m_rwBuffer.GetPointer(), u8_q*) + uPositionInBuffer;

    // Reads the data from the file
    // Only the bytes that are not in the buffer yet are read directly from the file
    bool bOperationSuccessful = true;
    pointer_uint_q uBytesFromPositionToEndOfBuffer = m_uBufferVirtualSize - uPositionInBuffer;

    if(uBytesFromPositionToEndOfBuffer < uClampedOutputSize)
    {
        pointer_uint_q uExceedingBytesToReadFromFile = uClampedOutputSize - uBytesFromPositionToEndOfBuffer;
        pointer_uint_q uPositionAtEndOfBuffer = m_uPositionPointer + uBytesFromPositionToEndOfBuffer;
        u8_q* pPositionAtEndOfBuffer = pPositionInBuffer + uBytesFromPositionToEndOfBuffer;

        bOperationSuccessful = QFileStream::_ReadPlatformImplementation(pPositionAtEndOfBuffer, uExceedingBytesToReadFromFile, uPositionAtEndOfBuffer, m_nativeHandle, m_path);

        if(bOperationSuccessful)
        {
            m_uBufferVirtualSize += uExceedingBytesToReadFromFile;
        }
        
    } // if(uBytesFromPositionToEndOfBuffer < uClampedOutputSize)
            
    if(bOperationSuccessful)
    {
        // Copies the content of the read/write buffer to the output buffer from the current position
        memcpy(pOutputPosition, pPositionInBuffer, uClampedOutputSize);

        m_uPositionPointer = FUTURE_POSITION_POINTER > m_uFileSize ? 
                                                                    m_uFileSize : 
                                                                    FUTURE_POSITION_POINTER;
    }
}

void QFileStream::Write(const void* pInput, const pointer_uint_q uInputOffset, const pointer_uint_q uInputSize)
{
    QE_ASSERT_ERROR(uInputSize > 0, "The output size must not equal zero.");
    QE_ASSERT_ERROR(pInput != null_q, "The output buffer cannot be null.");
    QE_ASSERT_ERROR(m_bIsOpen == true, "The file must be opened before writing.");

    using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

    const u8_q* pInputPosition = scast_q(pInput, const u8_q*) + uInputOffset;

    // Flushes if the buffer is going to be discontinued
    this->_FlushIfPositionDoesNotBelongToBuffer();

    // Calculates the relative position in the read/write buffer
    pointer_uint_q uPositionInBuffer = m_uPositionPointer - m_uBufferStartPosition;

    // Reallocates the read/write buffer if necessary
    pointer_uint_q uBytesFromPositionToEndOfAllocatedMemory = m_rwBuffer.GetSize() - uPositionInBuffer;
    if(uBytesFromPositionToEndOfAllocatedMemory < uInputSize)
    {
        pointer_uint_q uExceedingBytes = uInputSize - uBytesFromPositionToEndOfAllocatedMemory;
        pointer_uint_q uPreviousSize = m_rwBuffer.GetSize();
        this->_ReallocateByFactor(uPreviousSize + uExceedingBytes);
        m_rwBuffer.Allocate(m_rwBuffer.GetSize() - uPreviousSize);
    }

    u8_q* pPositionInBuffer = scast_q(m_rwBuffer.GetPointer(), u8_q*) + uPositionInBuffer;

    // Copies the content of the input buffer to the read/write buffer from the current position
    memcpy(pPositionInBuffer, pInputPosition, uInputSize);
    m_bIsWritePending = true;
    m_uBufferVirtualSize = uPositionInBuffer + uInputSize > m_uBufferVirtualSize ? uPositionInBuffer + uInputSize :
                                                                                   m_uBufferVirtualSize;
    m_uPositionPointer += uInputSize;
    m_uFileSize = m_uPositionPointer > m_uFileSize ? m_uPositionPointer :
                                                     m_uFileSize;
}

void QFileStream::Flush()
{
    QE_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");
    QE_ASSERT_ERROR(!m_bIsWritePending || m_bWritingIsAllowed, "It is not possible to write to the file, it is read-only.");

    bool bOperationSuccessful = true;

    if(m_bIsWritePending)
    {
        // Writes the full buffer
        bOperationSuccessful = QFileStream::_WritePlatformImplementation(m_rwBuffer.GetPointer(), m_uBufferVirtualSize, m_uBufferStartPosition, m_nativeHandle, m_path);
    }

    if(bOperationSuccessful)
    {
        m_uBufferStartPosition = m_uPositionPointer;
        m_uBufferVirtualSize = 0;
        m_bIsWritePending = false;
    }
}

void QFileStream::MoveBackward(const pointer_uint_q uAmount)
{
    QE_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");
    QE_ASSERT_WARNING(m_uPositionPointer >= uAmount, "It is not possible to move backward the specified amount, it would be out of bounds.");

    pointer_uint_q uFixedAmount = m_uPositionPointer < uAmount ? uAmount - m_uPositionPointer :
                                                                 uAmount;
    m_uPositionPointer -= uFixedAmount;
}

void QFileStream::MoveForward(const pointer_uint_q uAmount)
{
    QE_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");
    QE_ASSERT_WARNING(m_uPositionPointer + uAmount <= m_uFileSize, "It is not possible to move forward the specified amount, it would be out of bounds.");

    pointer_uint_q uFixedAmount = m_uPositionPointer + uAmount > m_uFileSize ? m_uFileSize - m_uPositionPointer :
                                                                               uAmount;
    m_uPositionPointer += uFixedAmount;
}

EQFileSystemError QFileStream::Open(const QPath &filePath, const EQFileOpenMode &eOpenMode)
{
    QE_ASSERT_ERROR(m_bIsOpen != true, "The file stream is already open.");

    EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
    const bool FILE_EXISTS = SQFile::Exists(filePath, eErrorInfo);

    if((FILE_EXISTS && (eOpenMode == EQFileOpenMode::E_Append || eOpenMode == EQFileOpenMode::E_Open)) ||
       (!FILE_EXISTS && eOpenMode == EQFileOpenMode::E_Create)                                         ||
       eOpenMode == EQFileOpenMode::E_CreateOrOverwrite                                                || 
       eOpenMode == EQFileOpenMode::E_OpenOrCreate)
    {
        if(FILE_EXISTS)
        {
            QFileInfo fileInfo = SQFile::GetFileInfo(filePath, eErrorInfo);
            m_uFileSize = scast_q(fileInfo.GetSize(), pointer_uint_q);
            m_bWritingIsAllowed = !fileInfo.IsReadOnly();
            
            QE_ASSERT_ERROR(!(fileInfo.IsReadOnly() && eOpenMode == EQFileOpenMode::E_CreateOrOverwrite), string_q("The current user does not have permissions to overwrite the file \"") + filePath.GetAbsolutePath() + "\".");
        }
        else
        {
            m_uFileSize = 0;
            m_bWritingIsAllowed = true;
        }

        m_path = filePath;

        bool bOperationSuccessful = QFileStream::_OpenPlatformImplementation(m_path, eOpenMode, m_bWritingIsAllowed, m_nativeHandle, eErrorInfo);
        
        if(bOperationSuccessful)
        {
            m_bIsOpen = true;
            eErrorInfo = EQFileSystemError::E_Success;

            if(eOpenMode == EQFileOpenMode::E_Append)
                this->SetPosition(m_uFileSize);
            else
                this->SetPosition(0);

            QE_ASSERT_WARNING(m_uFileSize <= pointer_uint_q(-1), "The the file is too large, this class cannot access file offsets over 2^32 - 1 when it is compiled for x86 architecture.");

            if(m_uFileSize > pointer_uint_q(-1))
            {
                eErrorInfo = EQFileSystemError::E_FileIsTooLarge;
            }
        }
    }
    else if(FILE_EXISTS && eOpenMode == EQFileOpenMode::E_Create)
    {
        eErrorInfo = EQFileSystemError::E_AlreadyExists;
    }
    else
    {
        eErrorInfo = EQFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

void QFileStream::Close()
{
    QE_ASSERT_WARNING(m_bIsOpen == true, "The file was already closed.");

    if(m_bIsOpen)
    {
        if(m_bIsWritePending)
            this->Flush();

        bool bOperationSuccessful = QFileStream::_ClosePlarformImplementation(m_nativeHandle, m_path);

        if(bOperationSuccessful)
        {
            m_bIsOpen = false;
        }
    }
}

void QFileStream::_ReallocateByFactor(const pointer_uint_q uBytes)
{
    const pointer_uint_q FINAL_CAPACITY = scast_q(scast_q(uBytes, float) * QFileStream::_REALLOCATION_FACTOR, pointer_uint_q);
    m_rwBuffer.Reallocate(FINAL_CAPACITY);
}

bool QFileStream::_FlushIfPositionDoesNotBelongToBuffer()
{
    bool bPositionDoesNotBelongToBuffer = m_uPositionPointer < m_uBufferStartPosition || m_uPositionPointer > m_uBufferStartPosition + m_uBufferVirtualSize;

    // If the resultant relative position in the buffer is lower than the base position or surpasses the current virtual size, the buffer is flushed
    if(bPositionDoesNotBelongToBuffer)
        this->Flush();

    return bPositionDoesNotBelongToBuffer;
}

#if defined(QE_OS_WINDOWS)

bool QFileStream::_ReadPlatformImplementation(u8_q* pOutputBuffer, const pointer_uint_q uNumberOfBytes, const pointer_uint_q uFileOffset, const QFileStream::NativeHandle &handle, const QPath &filePath)
{
    bool bSuccess = true;

    OVERLAPPED offsets;
    memset(&offsets, 0, sizeof(OVERLAPPED)); // The structure MUST be zero-initialized

    // Sets the offset from where to start reading
#if QE_OS_WINDOWS == 32
        offsets.Offset = uFileOffset;
        offsets.OffsetHigh = 0;
#elif QE_OS_WINDOWS == 64
        const u32_q* pPosition = rcast_q(&uFileOffset, const u32_q*);
    #if QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
        offsets.Offset = pPosition[1];
        offsets.OffsetHigh = pPosition[0];
    #elif QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
        offsets.Offset = pPosition[0];
        offsets.OffsetHigh = pPosition[1];
    #endif
#endif

    static const BOOL READ_OPERATION_FAILED = 0;
    BOOL uReadFileResult = ::ReadFile(handle, pOutputBuffer, uNumberOfBytes, NULL, &offsets);

    if(uReadFileResult == READ_OPERATION_FAILED)
    {
        bSuccess = false;
        DWORD uReadFileLastError = ::GetLastError();
        QE_ASSERT_ERROR(uReadFileResult != 0, string_q("An unexpected error occurred when reading from the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(uReadFileLastError) + ".");
    }

    return bSuccess;
}

bool QFileStream::_WritePlatformImplementation(const void* pInputBuffer, const pointer_uint_q uNumberOfBytes, const pointer_uint_q uFileOffset, const QFileStream::NativeHandle &handle, const QPath &filePath)
{
    bool bSuccess = true;

    OVERLAPPED offsets;
    memset(&offsets, 0, sizeof(OVERLAPPED)); // The structure MUST be zero-initialized

    // Sets the offset from where to start reading
#if QE_OS_WINDOWS == 32
        offsets.Offset = uFileOffset;
        offsets.OffsetHigh = 0;
#elif QE_OS_WINDOWS == 64
        const u32_q* pPosition = rcast_q(&uFileOffset, const u32_q*);
    #if QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
        offsets.Offset = pPosition[1];
        offsets.OffsetHigh = pPosition[0];
    #elif QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
        offsets.Offset = pPosition[0];
        offsets.OffsetHigh = pPosition[1];
    #endif
#endif

    static const BOOL WRITE_OPERATION_FAILED = 0;
    BOOL uWriteFileResult = ::WriteFile(handle, pInputBuffer, uNumberOfBytes, NULL, &offsets);

    if(uWriteFileResult == WRITE_OPERATION_FAILED)
    {
        bSuccess = false;
            
        DWORD uWriteFileLastError = ::GetLastError();
        QE_ASSERT_WARNING(uWriteFileResult != WRITE_OPERATION_FAILED, string_q("An unexpected error occurred when writing to the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(uWriteFileLastError) + ".");
    }

    return bSuccess;
}

bool QFileStream::_OpenPlatformImplementation(const QPath &filePath, const EQFileOpenMode &eOpenMode, const bool bIsWritingAllowed, QFileStream::NativeHandle &handle, EQFileSystemError &eErrorInfo)
{
    bool bSuccess = true;

    using Kinesis::QuimeraEngine::Common::DataTypes::QArrayResult;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

    QArrayResult<i8_q> arPath = filePath.ToString().ToBytes(string_q::GetLocalEncodingUTF16());
    const wchar_t* szPath = rcast_q(arPath.Get(), wchar_t*);
    DWORD uAccess = bIsWritingAllowed ? GENERIC_READ | GENERIC_WRITE : 
                                        GENERIC_READ;
    DWORD uOpenMode = 0;

    switch(eOpenMode)
    {
    case EQFileOpenMode::E_Append:
    case EQFileOpenMode::E_Open:
        uOpenMode = OPEN_EXISTING;
        break;
    case EQFileOpenMode::E_Create:
        uOpenMode = CREATE_NEW;
        break;
    case EQFileOpenMode::E_CreateOrOverwrite:
        uOpenMode = CREATE_ALWAYS;
        break;
    case EQFileOpenMode::E_OpenOrCreate:
        uOpenMode = OPEN_ALWAYS;
        break;
    default:
        break;
    }

    handle = ::CreateFileW(szPath, uAccess, FILE_SHARE_READ, NULL, uOpenMode, FILE_FLAG_RANDOM_ACCESS, NULL);

    const bool FILE_OPENED_SUCCESSFULLY = handle != INVALID_HANDLE_VALUE;

    if(!FILE_OPENED_SUCCESSFULLY)
    {
        bSuccess = false;
        DWORD uCreateFileWLastError = ::GetLastError();
        QE_ASSERT_ERROR(handle != INVALID_HANDLE_VALUE, string_q("An unexpected error occurred when opening the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(uCreateFileWLastError) + ".");

        if(uCreateFileWLastError == ERROR_ACCESS_DENIED)
            eErrorInfo = EQFileSystemError::E_NoPermissions;
        else
            eErrorInfo = EQFileSystemError::E_Unknown;
    }

    return bSuccess;
}

bool QFileStream::_ClosePlarformImplementation(const QFileStream::NativeHandle &handle, const QPath &filePath)
{
    bool bSuccess = true;

    static const BOOL CLOSE_OPERATION_FAILED = 0;
    BOOL uCloseHandleResult = ::CloseHandle(handle);

    if(uCloseHandleResult == CLOSE_OPERATION_FAILED)
    {
        bSuccess = false;
        DWORD uCloseHandleLastError = ::GetLastError();
        QE_ASSERT_ERROR(uCloseHandleResult != 0, string_q("An unexpected error occurred when closing the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(uCloseHandleLastError) + ".");
    }

    return bSuccess;
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

bool QFileStream::_ReadPlatformImplementation(u8_q* pOutputBuffer, const pointer_uint_q uNumberOfBytes, const pointer_uint_q uFileOffset, const QFileStream::NativeHandle &handle, const QPath &filePath)
{
    bool bSuccess = true;

    ssize_t nResult = pread(handle, pOutputBuffer, uNumberOfBytes, uFileOffset);
        
    if(nResult < 0)
    {
        bSuccess = false;
        error_t lastError = errno;
        QE_ASSERT_ERROR(nResult >= 0, string_q("An unexpected error occurred when reading from the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(lastError) + ".");
    }

    return bSuccess;
}

bool QFileStream::_WritePlatformImplementation(const void* pInputBuffer, const pointer_uint_q uNumberOfBytes, const pointer_uint_q uFileOffset, const QFileStream::NativeHandle &handle, const QPath &filePath)
{
    bool bSuccess = true;

    ssize_t nResult = pwrite(handle, pInputBuffer, uNumberOfBytes, uFileOffset);
        
    if(nResult < 0)
    {
        bSuccess = false;
        error_t lastError = errno;
        QE_ASSERT_ERROR(nResult >= 0, string_q("An unexpected error occurred when writing to the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(lastError) + ".");
    }

    return bSuccess;
}

bool QFileStream::_OpenPlatformImplementation(const QPath &filePath, const EQFileOpenMode &eOpenMode, const bool bIsWritingAllowed, QFileStream::NativeHandle &handle, EQFileSystemError &eErrorInfo)
{
    bool bSuccess = true;

    using Kinesis::QuimeraEngine::Common::DataTypes::QArrayResult;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    QArrayResult<i8_q> szPath = filePath.ToString().ToBytes(EQTextEncoding::E_UTF8);
        
    int nAccess = bIsWritingAllowed ? O_RDWR: 
                                      O_RDONLY;
    int nPermissions = S_IRWXU; // Read, write and execution permissions for the owner
    int nOpenMode = 0;

    switch(eOpenMode)
    {
    case EQFileOpenMode::E_Append:
    case EQFileOpenMode::E_Open:
        nOpenMode = 0;
        break;
    case EQFileOpenMode::E_Create:
        nOpenMode = O_CREAT | O_EXCL;
        break;
    case EQFileOpenMode::E_CreateOrOverwrite:
        nOpenMode = O_CREAT | O_TRUNC;
        break;
    case EQFileOpenMode::E_OpenOrCreate:
        nOpenMode = O_CREAT;
        break;
    default:
        break;
    }
        
    handle = open(szPath.Get(), nAccess | nOpenMode, nPermissions);

    const bool FILE_OPENED_SUCCESSFULLY = handle >= 0;
        
    if(!FILE_OPENED_SUCCESSFULLY)
    {
        bSuccess = false;
        error_t lastError = errno;
        QE_ASSERT_ERROR(handle >= 0, string_q("An unexpected error occurred when opening the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(lastError) + ".");
            
        if(lastError == EACCES)
            eErrorInfo = EQFileSystemError::E_NoPermissions;
        else
            eErrorInfo = EQFileSystemError::E_Unknown;
    }

    return bSuccess;
}

bool QFileStream::_ClosePlarformImplementation(const QFileStream::NativeHandle &handle, const QPath &filePath)
{
    bool bSuccess = true;

    int nResult = close(handle);

    if(nResult < 0)
    {
        bSuccess = false;
        error_t lastError = errno;
        QE_ASSERT_ERROR(nResult >= 0, string_q("An unexpected error occurred when closing the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + SQInteger::ToString(lastError) + ".");
    }

    return bSuccess;
}

#endif


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

pointer_uint_q QFileStream::GetLength() const
{
    QE_ASSERT_WARNING(m_bIsOpen == true, "The file is not open.");

    return m_uFileSize;
}

pointer_uint_q QFileStream::GetPosition() const
{
    return m_uPositionPointer;
}

void QFileStream::SetPosition(const pointer_uint_q uPosition)
{
    QE_ASSERT_WARNING(m_bIsOpen == true, "The file is not open.");
    QE_ASSERT_WARNING(uPosition <= m_uFileSize, "It is not possible to set the specified position, it would be out of bounds.");

    m_uPositionPointer = uPosition > m_uFileSize ? m_uFileSize :
                                                   uPosition;
}

QPath QFileStream::GetPath() const
{
    return m_path;
}

bool QFileStream::IsOpen() const
{
    return m_bIsOpen;
}

QFileStream::NativeHandle QFileStream::GetNativeHandle() const
{
    QE_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");

    return m_nativeHandle;
}


} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
