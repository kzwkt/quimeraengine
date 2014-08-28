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

#ifndef __QMEMORYSTREAM__
#define __QMEMORYSTREAM__

#include "SystemDefinitions.h"

#include "QLinearAllocator.h"
#include "Assertions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace IO
{

/// <summary>
/// Represents a stream of data stored in main memory.
/// </summary>
/// <remarks>
/// It keeps an internal pointer to a position of the buffer, which allows reading or writing a group of bytes from there forward.<br/>
/// The internal pointer can be moved back and forth as necessary, and it will be moved automatically after every read / write operation.<br/>
/// Streams grow as more memory is required to store the incoming bytes.
/// </remarks>
/// <typeparam name="AllocatorT">Optional. The type of allocator used to store the stream. By default, QLinearAllocator will be used.</typeparam>
template<class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QLinearAllocator>
class QMemoryStream
{
    
    // CONSTANTS
    // ---------------
private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float REALLOCATION_FACTOR;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that creates an empty stream receiving the initial capacity of the buffer.
    /// </summary>
    /// <remarks>
    /// The internal pointer's position is set to zero.<br/>
    /// The buffer is 1-byte aligned.
    /// </remarks>
    /// <param name="uCapacity">[IN] The initial capacity of the buffer, in bytes. It must not equal zero.</param>
    QMemoryStream(const pointer_uint_q uCapacity) : m_buffer(uCapacity, Kinesis::QuimeraEngine::Common::Memory::QAlignment(1U)),
                                                    m_uPositionPointer(0)
    {
        QE_ASSERT(uCapacity != 0, "The buffer capacity cannot be zero.");
    }
    
    /// <summary>
    /// Constructor that creates an empty stream receiving an external buffer, which will be copied, and its size.
    /// </summary>
    /// <remarks>
    /// The length and the capacity of the stream will equal the size of the input buffer.
    /// The internal pointer's position is set to zero.<br/>
    /// The internal buffer is 1-byte aligned.
    /// </remarks>
    /// <param name="pBuffer">[IN] An external buffer, whose content will be copied to the internal buffer. It must not be null.</param>
    /// <param name="uBufferSize">[IN] The size, in bytes, of the external buffer. It must not equal zero.</param>
    QMemoryStream(const void* pBuffer, const pointer_uint_q uBufferSize) : m_buffer(uBufferSize, Kinesis::QuimeraEngine::Common::Memory::QAlignment(1U)),
                                                                           m_uPositionPointer(0)
    {
        QE_ASSERT(pBuffer != null_q, "The buffer cannot be null.");
        QE_ASSERT(uBufferSize != 0, "The buffer size cannot be zero.");

        void* pAllocation = m_buffer.Allocate(uBufferSize);
        memcpy(pAllocation, pBuffer, uBufferSize);
    }
    
    /// <summary>
    /// Copy constructor that creates a stream by copying the content of another one.
    /// </summary>
    /// <remarks>
    /// The length and the capacity of the stream will equal the length of the input stream. In case the input stream is empty, the capacity of the internal
    /// buffer will be set to an arbitrary greater-than-zero value.<br/>
    /// The internal pointer's position is set to zero.<br/>
    /// The internal buffer is 1-byte aligned.
    /// </remarks>
    /// <param name="stream">[IN] The input stream to be copied.</param>
    QMemoryStream(const QMemoryStream &stream) : m_buffer(stream.GetLength() > 0 ? stream.GetLength() : 4U, Kinesis::QuimeraEngine::Common::Memory::QAlignment(1U)),
                                                 m_uPositionPointer(0)
    {
        if(stream.GetLength() > 0)
        {
            void* pAllocation = m_buffer.Allocate(stream.GetLength());
            memcpy(pAllocation, stream.m_buffer.GetPointer(), stream.GetLength()); 
        }
    }


    // METHODS
    // ---------------
private:

    // Hidden
    QMemoryStream<AllocatorT>& operator=(const QMemoryStream &);

public:
    
    /// <summary>
    /// Reads a group of bytes from the stream and copies them to an output buffer.
    /// </summary>
    /// <remarks>
    /// The internal pointer is moved forward by the number of bytes read, after the operation. If the number of bytes
    /// to read from the current position exceed the buffer's limits, the pointer will be moved to the lastest valid position.
    /// </remarks>
    /// <param name="pOutput">[OUT] The output buffer where bytes are to be copied. Is must not be null.</param>
    /// <param name="uOutputOffset">[IN] The offset, in bytes, from where to start writing to the output buffer..</param>
    /// <param name="uOutputSize">[IN] The number of bytes to be read. It must not equal zero.</param>
    void Read(void* pOutput, const pointer_uint_q uOutputOffset, const pointer_uint_q uOutputSize)
    {
        QE_ASSERT(uOutputSize > 0, "The output size must not equal zero.");
        QE_ASSERT(pOutput != null_q, "The output buffer cannot be null.");

        using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

        u8_q* pOutputPosition = scast_q(pOutput, u8_q*) + uOutputOffset;
        u8_q* pPositionPointer = scast_q(m_buffer.GetPointer(), u8_q*) + m_uPositionPointer;

        memcpy(pOutputPosition, pPositionPointer, uOutputSize);

        const pointer_uint_q FUTURE_POSITION_POINTER = m_uPositionPointer + uOutputSize;
        const pointer_uint_q BUFFER_SIZE = m_buffer.GetAllocatedBytes();

        QE_ASSERT(FUTURE_POSITION_POINTER <= BUFFER_SIZE, "Warning: Attempting to read from outside of the buffer.");

        m_uPositionPointer = FUTURE_POSITION_POINTER > BUFFER_SIZE ? 
                                                                    BUFFER_SIZE : 
                                                                    FUTURE_POSITION_POINTER;
    }

    /// <summary>
    /// Copies a group of bytes from an input buffer to the stream.
    /// </summary>
    /// <remarks>
    /// The internal pointer is moved forward by the number of bytes written, after the operation.<br/>
    /// The stream will grow as more memory is required to store new data.<br/>
    /// If the position of the internal pointer is not set to the end of the buffer, the stream will be partially overwritten.
    /// </remarks>
    /// <param name="pInput">[IN] The input buffer from which bytes are to be copied. Is must not be null.</param>
    /// <param name="uInputOffset">[IN] The offset, in bytes, from where to start reading from the input buffer..</param>
    /// <param name="uInputSize">[IN] The number of bytes to be written. It must not equal zero.</param>
    void Write(const void* pInput, const pointer_uint_q uInputOffset, const pointer_uint_q uInputSize)
    {
        QE_ASSERT(uInputSize > 0, "The input size must not equal zero.");
        QE_ASSERT(pInput != null_q, "The input buffer cannot be null.");

        using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

        const pointer_uint_q FUTURE_POSITION_POINTER = m_uPositionPointer + uInputSize;

        // If there is not enough free space in the buffer for storing the input bytes, the buffer is extended
        if(FUTURE_POSITION_POINTER > m_buffer.GetSize())
        {
            this->ReallocateByFactor(FUTURE_POSITION_POINTER);
        }

        // If the input memory block (or a part of it) is to be copied to the non-allocated zone of the buffer, it allocates more
        if(FUTURE_POSITION_POINTER > m_buffer.GetAllocatedBytes())
        {
            m_buffer.Allocate(FUTURE_POSITION_POINTER - m_buffer.GetAllocatedBytes());
        }

        u8_q* pPositionPointer = scast_q(m_buffer.GetPointer(), u8_q*) + m_uPositionPointer;
        const u8_q* pInputPosition = scast_q(pInput, const u8_q*) + uInputOffset;

        memcpy(scast_q(pPositionPointer, void*), scast_q(pInputPosition, const void*), uInputSize);

        m_uPositionPointer = FUTURE_POSITION_POINTER;
    }
    
    /// <summary>
    /// Copies the content of the stream to another stream of any other kind.
    /// </summary>
    /// <remarks>
    /// Bytes are copied sequentially as batches of an arbitrary size until the end of the source stream is reached.<br/>
    /// The internal pointer of the resident stream is not moved during this operation, unlike the destination stream's, which is moved forward by 
    /// the number of bytes copied, after the operation.<br/>
    /// The destination stream will grow as more memory is required to store new data.
    /// </remarks>
    /// <typeparam name="StreamT">The type of the destination stream.</typeparam>
    /// <param name="destinationStream">[OUT] The destination stream to which the content will be copied.</param>
    /// <param name="uSourceOffset">[IN] The offset, in bytes, from where to start reading from the source stream. It must be lower than the length of 
    /// the source stream.</param>
    /// <param name="uDestinationOffset">[IN] The offset, in bytes, from where to start writing to the destination stream. It must be lower than or equal to
    /// the length of the destination stream.</param>
    template<class StreamT>
    void CopyTo(StreamT &destinationStream, const pointer_uint_q uSourceOffset, const pointer_uint_q uDestinationOffset) const
    {
        static const pointer_uint_q BATCH_SIZE = 4096; // This is an arbitrary value, it should be tuned to improve performance

        QE_ASSERT(uSourceOffset < this->GetLength(), "The offset of the source stream is out of bounds.");
        QE_ASSERT(uDestinationOffset <= destinationStream.GetLength(), "The offset of the destination stream is out of bounds.");

        // If offsets point to valid positions
        if(uSourceOffset < this->GetLength() && uDestinationOffset <= destinationStream.GetLength())
        {
            // The stream is copied batch by batch
            const pointer_uint_q NUMBER_OF_BATCHES = (m_buffer.GetAllocatedBytes() - uSourceOffset) / BATCH_SIZE;

            destinationStream.SetPosition(uDestinationOffset);

            for(pointer_uint_q i = 0; i < NUMBER_OF_BATCHES; ++i)
                destinationStream.Write(m_buffer.GetPointer(), uSourceOffset + i * BATCH_SIZE, BATCH_SIZE);

            const pointer_uint_q REST_OF_BYTES = (m_buffer.GetAllocatedBytes() - uSourceOffset) % BATCH_SIZE;

            if(REST_OF_BYTES != 0)
                destinationStream.Write(m_buffer.GetPointer(), NUMBER_OF_BATCHES * BATCH_SIZE, REST_OF_BYTES);
        }
    }

    /// <summary>
    /// Empties all the intermediate buffers and sends the data to the final storage support. This is an immediate operation for memory streams so it does nothing.
    /// </summary>
    void Flush()
    {
        // It does nothing
    }
    
    /// <summary>
    /// Moves the internal pointer to a prior position.
    /// </summary>
    /// <param name="uAmount">[IN] The number of bytes to move back the internal pointer's position. If it is already at the first position, it does nothing.</param>
    void MoveBackward(const pointer_uint_q uAmount)
    {
        QE_ASSERT(uAmount <= m_uPositionPointer, "It is not possible to move backward, it would be out of bounds.");

        if(uAmount <= m_uPositionPointer)
            m_uPositionPointer -= uAmount;
    }
        
    /// <summary>
    /// Moves the internal pointer to a posterior position.
    /// </summary>
    /// <param name="uAmount">[IN] The number of bytes to move forward the internal pointer's position. If it is already at the latest position, it does nothing.</param>
    void MoveForward(const pointer_uint_q uAmount)
    {
        QE_ASSERT(m_uPositionPointer + uAmount <= m_buffer.GetAllocatedBytes(), "It is not possible to move forward, it would be out of bounds.");

        if(m_uPositionPointer + uAmount <= m_buffer.GetAllocatedBytes())
            m_uPositionPointer += uAmount;
    }
    
private:

    /// <summary>
    /// Increases the capacity of the buffer, reserving more memory than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uBytes">[IN] The number of bytes for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void ReallocateByFactor(const pointer_uint_q uBytes)
    {
        const pointer_uint_q FINAL_CAPACITY = scast_q(scast_q(uBytes, float) * QMemoryStream::REALLOCATION_FACTOR, pointer_uint_q);
        m_buffer.Reallocate(FINAL_CAPACITY);
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the length of the stream, in bytes.
    /// </summary>
    /// <returns>
    /// The number of bytes that have been written to the stream.
    /// </returns>
    pointer_uint_q GetLength() const
    {
        return m_buffer.GetAllocatedBytes();
    }
    
    /// <summary>
    /// Gets the position of the internal pointer in the stream.
    /// </summary>
    /// <returns>
    /// The byte number to which the internal pointer is pointing to.
    /// </returns>
    pointer_uint_q GetPosition() const
    {
        return m_uPositionPointer;
    }
    
    /// <summary>
    /// Sets the position of the internal pointer.
    /// </summary>
    /// <param name="uPosition">[IN] The new position of the internal pointer. It must be lower than or equal to the length of the stream 
    /// or it will not be set.</param>
    void SetPosition(const pointer_uint_q uPosition)
    {
        QE_ASSERT(uPosition <= m_buffer.GetAllocatedBytes(), "The input position is invalid, it is out of bounds.");

        if(uPosition <= m_buffer.GetAllocatedBytes())
            m_uPositionPointer = uPosition;
    }

    /// <summary>
    /// Gets the memory address to which the internal pointer is pointing.
    /// </summary>
    /// <returns>
    /// The memory address to which the internal pointer is pointing, given its current position.
    /// </returns>
    void* GetCurrentPointer() const
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

        return scast_q(m_buffer.GetPointer(), u8_q*) + m_uPositionPointer;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The allocator that stores the internal buffer.
    /// </summary>
    AllocatorT m_buffer;

    /// <summary>
    /// The position of the internal reading/writing pointer.
    /// </summary>
    pointer_uint_q m_uPositionPointer;
};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template<class AllocatorT>
float QMemoryStream<AllocatorT>::REALLOCATION_FACTOR = 1.5f;


} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QMEMORYSTREAM__
