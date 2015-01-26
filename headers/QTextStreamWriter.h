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

#ifndef __QTEXTSTREAMWRITER__
#define __QTEXTSTREAMWRITER__


#include "SystemDefinitions.h"

#include "EQNewLineCharacters.h"
#include "EQTextEncoding.h"
#include "EQComparisonType.h"
#include "SQInteger.h"
#include "QArrayResult.h"

using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace IO
{

/// <summary>
/// Component that encodes text and sends it to a stream.
/// </summary>
/// <typeparam name="StreamT">The type of the stream to write to (memory stream, file stream, etc.).</typeparam>
template<class StreamT>
class QTextStreamWriter
{
    // CONSTANTS
    // ---------------
protected:
    
    /// <summary>
    /// The default size (in bytes) of the batches used in the write operation.
    /// </summary>
    static const pointer_uint_q _COPY_BATCH_SIZE = 4096U; // 4096 bytes is apparently the most common cluster size in a file system. It should be tuned to improve performance


    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives a stream and the encoding to be used when writing to it.
    /// </summary>
    /// <remarks>
    /// The default new line character is a LF (line feed, a '\n' character).<br/>
    /// The stream's write pointer is not modified by this operation.
    /// </remarks>
    /// <param name="stream">[IN] The stream to write to.</param>
    /// <param name="eStreamEncoding">[IN] The encoding of the text to be written to the stream. The UTF-16 and UTF-32 encodings are 
    /// changed to their corresponding version depending on the local machine's endianness (either LE or BE).</param>
    QTextStreamWriter(StreamT& stream, const Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding &eStreamEncoding) :
                                                                                m_stream(stream),
                                                                                m_eEncoding(eStreamEncoding),
                                                                                m_eNewLine(EQNewLineCharacters::E_LF),
                                                                                m_arNewLineCharacters(null_q, 0),
                                                                                m_uCharSize(0)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

        // Encoding with no endianness is translated to encoding with the local machine's endianness
        if(eStreamEncoding == EQTextEncoding::E_UTF16)
            m_eEncoding = string_q::GetLocalEncodingUTF16();
        else if(eStreamEncoding == EQTextEncoding::E_UTF32)
            m_eEncoding = string_q::GetLocalEncodingUTF32();

        // Sets the size of characters in the given encoding, in bytes
        switch(m_eEncoding)
        {
        case EQTextEncoding::E_ASCII:
        case EQTextEncoding::E_ISO88591:
        case EQTextEncoding::E_UTF8:
            m_uCharSize = 1U;
            break;
        case EQTextEncoding::E_UTF16LE:
        case EQTextEncoding::E_UTF16BE:
            m_uCharSize = 2U;
            break;
        case EQTextEncoding::E_UTF32LE:
        case EQTextEncoding::E_UTF32BE:
            m_uCharSize = 4U;
            break;
        default:
            break;
        }

        // Sets the characters selected by default that limit the end of a line
        this->SetNewLineSeparator(m_eNewLine);
    }

private:

    // Hidden
    QTextStreamWriter(const QTextStreamWriter&);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    ~QTextStreamWriter()
    {
        delete[] m_arNewLineCharacters.Get();
    }


    // METHODS
    // ---------------
private:

    // Hidden
    QTextStreamWriter& operator=(const QTextStreamWriter&);

public:
    
    /// <summary>
    /// Writes all the characters from the input text to the stream at the current position and adds a new line separator afterwards.
    /// </summary>
    /// <remarks>
    /// Use the SetNewLineSeparator method to choose the sequence of characters that compound the new line separator.<br/>
    /// If there is a leading BOM character in the input text, it will be included in the output.<br/>
    /// If there is no leading BOM character in the input text, it will not be added to the output. Use the WriteBOM method to insert a BOM character.<br/>
    /// If there is a trailing zero in the sequence of characters, it will not be written.<br/>
    /// The write pointer of the stream will be moved to the position right after the new line characters.
    /// </remarks>
    /// <param name="strInput">[IN] The input string whose characters will be written. If it is empty, only the new line separator will be written.</param>
    /// <param name="uBatchSize">[Optional][IN] The size, in bytes, of every written batch. It must be greater than zero. It may affect the performance of the operation.</param>
    void WriteLine(const string_q &strInput, const pointer_uint_q uBatchSize=QTextStreamWriter::_COPY_BATCH_SIZE)
    {
        QE_ASSERT_ERROR(uBatchSize > 0, "The number of bytes per batch must be greater than zero.");

        this->Write(strInput, uBatchSize);
        m_stream.Write(m_arNewLineCharacters.Get(), 0, m_arNewLineCharacters.GetSize() - m_uCharSize); // Quits the last character ('\0')
    }

    /// <summary>
    /// Writes all the characters from the input text to the stream at the current position.
    /// </summary>
    /// <remarks>
    /// If there is a leading BOM character in the input text, it will be included in the output.<br/>
    /// If there is no leading BOM character in the input text, it will not be added to the output. Use the WriteBOM method to insert a BOM character.<br/>
    /// If there is a trailing zero in the sequence of characters, it will not be written.<br/>
    /// The write pointer of the stream will be moved to the position right after the last character written.
    /// </remarks>
    /// <param name="strInput">[IN] The input string whose characters will be written. If it is empty, nothing will be done.</param>
    /// <param name="uBatchSize">[Optional][IN] The size, in bytes, of every written batch. It must be greater than zero. It may affect the performance of the operation.</param>
    void Write(const string_q &strInput, const pointer_uint_q uBatchSize=QTextStreamWriter::_COPY_BATCH_SIZE)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::QArrayResult;
        using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
        
        QE_ASSERT_ERROR(uBatchSize > 0, "The number of bytes per batch must be greater than zero.");

        if(!strInput.IsEmpty())
        {
            QArrayResult<i8_q> arEncodedString = strInput.ToBytes(m_eEncoding);

            // The stream is copied batch by batch
            const pointer_uint_q NUMBER_OF_BATCHES = (arEncodedString.GetSize() - m_uCharSize) / uBatchSize; // Quits the last character ('\0')

            for(pointer_uint_q i = 0; i < NUMBER_OF_BATCHES; ++i)
                m_stream.Write(arEncodedString.Get(), i * uBatchSize, uBatchSize);

            const pointer_uint_q REST_OF_BYTES = (arEncodedString.GetSize() - m_uCharSize) % uBatchSize; // Quits the last character ('\0')

            if(REST_OF_BYTES != 0)
                m_stream.Write(arEncodedString.Get(), NUMBER_OF_BATCHES * uBatchSize, REST_OF_BYTES);
        }
    }
        
    /// <summary>
    /// Writes a Unicode BOM (U+FEFF Binary Order Mark) to the string at the current position.
    /// </summary>
    /// <remarks>
    /// The byte order of the character depends on the selected encoding's endianness.<br/>
    /// This method should be called only when using either UTF-16 or UTF-32 encodings.
    /// </remarks>
    void WriteBOM()
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
        using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;
        using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
        using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
        using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

        QE_ASSERT_WARNING(m_eEncoding == EQTextEncoding::E_UTF16LE ||
                          m_eEncoding == EQTextEncoding::E_UTF16BE ||
                          m_eEncoding == EQTextEncoding::E_UTF32LE ||
                          m_eEncoding == EQTextEncoding::E_UTF32BE,
                          string_q("Current text encoding (") + m_eEncoding.ToString() + ") does not use BOMs (Byte Order Marks).");

        static const u16_q BOM_UTF16 = 0xFEFF;
        static const string_q BOM_STRING(rcast_q(&BOM_UTF16, const i8_q*), sizeof(u16_q), string_q::GetLocalEncodingUTF16());

        QBasicArray<i8_q> arBOM(null_q, 0);

        if(m_eEncoding == EQTextEncoding::E_UTF16LE ||
           m_eEncoding == EQTextEncoding::E_UTF16BE ||
           m_eEncoding == EQTextEncoding::E_UTF32LE ||
           m_eEncoding == EQTextEncoding::E_UTF32BE)
        {
            QArrayResult<i8_q> arResult = BOM_STRING.ToBytes(m_eEncoding);
            arResult.Detach();
            arBOM = arResult;
        }

        if(arBOM.GetSize() > 0)
            m_stream.Write(arBOM.Get(), 0, arBOM.GetSize() - m_uCharSize); // Quits the last character ('\0')

        delete[] arBOM.Get();
    }

    /// <summary>
    /// Bitwise left shift operator that writes all the characters from the input text to the stream at the current position.
    /// </summary>
    /// <remarks>
    /// If there is a leading BOM character in the input text, it will be included in the output.<br/>
    /// If there is no leading BOM character in the input text, it will not be added to the output. Use the WriteBOM method to insert a BOM character.<br/>
    /// If there is a trailing zero in the sequence of characters, it will not be written.<br/>
    /// The write pointer of the stream will be moved to the position right after the last character written.<br/>
    /// It only calls Write using the default batch size.
    /// </remarks>
    /// <param name="strInput">[IN] The input string whose characters will be written. If it is empty, nothing will be done.</param>
    /// <returns>
    /// A reference to the text stream writer instance.
    /// </returns>
    QTextStreamWriter& operator<<(const string_q &strInput)
    {
        this->Write(strInput);
        return *this;
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the chosen new line characters utilized to separate lines.
    /// </summary>
    /// <returns>
    /// The chosen new line separator.
    /// </returns>
    EQNewLineCharacters GetNewLineSeparator() const
    {
        return m_eNewLine;
    }

    /// <summary>
    /// Sets the chosen new line characters utilized to separate lines.
    /// </summary>
    /// <param name="eNewLine">[IN] The new line separator.</param>
    void SetNewLineSeparator(const EQNewLineCharacters &eNewLine)
    {
        static const string_q NEW_LINE_CR("\r");
        static const string_q NEW_LINE_LF("\n");
        static const string_q NEW_LINE_CRLF("\r\n");

        switch(eNewLine)
        {
        case EQNewLineCharacters::E_CR:
            {
                QArrayResult arResult = NEW_LINE_CR.ToBytes(m_eEncoding);
                arResult.Detach();
                m_arNewLineCharacters = arResult;;
                break;
            }
        case EQNewLineCharacters::E_LF:
            {
                QArrayResult arResult = NEW_LINE_LF.ToBytes(m_eEncoding);
                arResult.Detach();
                m_arNewLineCharacters = arResult;;
                break;
            }
        case EQNewLineCharacters::E_CRLF:
            {
                QArrayResult arResult = NEW_LINE_CRLF.ToBytes(m_eEncoding);
                arResult.Detach();
                m_arNewLineCharacters = arResult;;
                break;
            }
        default:
            break;
        }
        
        m_eNewLine = eNewLine;
    }
    
    /// <summary>
    /// Gets the encoding of the text contained in the stream. It is set when the writer is created.
    /// </summary>
    /// <returns>
    /// The text encoding.
    /// </returns>
    Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding GetStreamEncoding() const
    {
        return m_eEncoding;
    }

    /// <summary>
    /// Gets the stream being written.
    /// </summary>
    /// <returns>
    /// A reference to the stream being written.
    /// </returns>
    StreamT& GetStream() const
    {
        return m_stream;
    }


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The stream being written.
    /// </summary>
    StreamT& m_stream;
    
    /// <summary>
    /// The encoding of the text.
    /// </summary>
    Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding m_eEncoding;
    
    /// <summary>
    /// The chosen new line separator.
    /// </summary>
    EQNewLineCharacters m_eNewLine;
    
    /// <summary>
    /// The characters that compound the new line separator.
    /// </summary>
    Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray<Kinesis::QuimeraEngine::Common::DataTypes::i8_q> m_arNewLineCharacters;
        
    /// <summary>
    /// The character size depending on the text encoding.
    /// </summary>
    pointer_uint_q m_uCharSize;
};


} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTEXTSTREAMWRITER__
