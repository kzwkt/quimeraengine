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

#ifndef __QBINARYSTREAMWRITER__
#define __QBINARYSTREAMWRITER__

#include "SystemDefinitions.h"

#include "DataTypesDefinitions.h"
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
/// Component that copies bytes from a known type instance to the stream.
/// </summary>
/// <typeparam name="StreamT">The type of the stream to write to (memory stream, file stream, etc.).</typeparam>
template<class StreamT>
class QBinaryStreamWriter
{

    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives a stream and stores a reference to it.
    /// </summary>
    /// <param name="stream">[IN] The stream to be read.</param>
    QBinaryStreamWriter(StreamT& stream) : m_stream(stream)
    {
    }

private:

    // Hidden
    QBinaryStreamWriter(const QBinaryStreamWriter&);


    // METHODS
    // ---------------
private:

    // Hidden
    QBinaryStreamWriter& operator=(const QBinaryStreamWriter&);

public:

    /// <summary>
    /// Writes a concrete amount of bytes from an input buffer.
    /// </summary>
    /// <remarks>
    /// Note that the read pointer of the stream is not restored after this operation.
    /// </remarks>
    /// <param name="pBuffer">[IN] The buffer from which to copy bytes to the stream. It must not be null.</param>
    /// <param name="uSize">[IN] The size of the buffer, in bytes. The same number of bytes will be written. It must be greater than zero.</param>
    void WriteBytes(const void* pBuffer, const Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q uSize)
    {
        QE_ASSERT_ERROR(pBuffer != null_q, "The input buffer cannot be null.");
        QE_ASSERT_ERROR(uSize > 0, "The size of the buffer must be greater than zero.");

        m_stream.Write(pBuffer, 0, uSize);
    }
    
    /// <summary>
    /// Writes enough bytes from an instance of a given type to the stream.
    /// </summary>
    /// <remarks>
    /// Note that the read pointer of the stream is not restored after this operation.<br/>
    /// The default constructor, the copy constructor and the destructor of the input instance will not be called.<br/>
    /// This method does the same as the bitwise left shift operator ("<<"). It's provided with the only purpose of improving readability 
    /// and/or usability in certain scenarios.
    /// </remarks>
    /// <typeparam name="T">The data type as which to interpret the bytes to write.</typeparam>
    /// <param name="value">[IN] The instance to be copied to the stream.</param>
    template<class T>
    void Write(const T& value)
    {
        m_stream.Write(&value, 0, sizeof(T));
    }
    
    /// <summary>
    /// Bitwise left shift operator that writes enough bytes to the stream to copy an instance of a given type.
    /// </summary>
    /// <remarks>
    /// Note that the read pointer of the stream is not restored after this operation.<br/>
    /// No instance's constructors nor operators are called.
    /// </remarks>
    /// <typeparam name="T">The data type as which to interpret the bytes to write.</typeparam>
    /// <param name="value">[IN] The instance to be copied to the stream.</param>
    /// <returns>
    /// A reference to the resident binary stream writer.
    /// </returns>
    template<class T>
    QBinaryStreamWriter& operator<<(const T& value)
    {
        m_stream.Write(&value, 0, sizeof(T));
        return *this;
    }
    
    /// <summary>
    /// Empties all the intermediate buffers and sends the data to the final storage support.
    /// </summary>
    void Flush()
    {
        m_stream.Flush();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the stream to write to.
    /// </summary>
    /// <returns>
    /// A reference to the stream to write to.
    /// </returns>
    StreamT& GetStream() const
    {
        return m_stream;
    }


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The stream to write to.
    /// </summary>
    StreamT& m_stream;

};

} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBINARYSTREAMWRITER__
