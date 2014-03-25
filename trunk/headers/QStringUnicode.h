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

#ifndef __QSTRINGUNICODE__
#define __QSTRINGUNICODE__

#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"

#include <unicode/unistr.h>
#include <unicode/schriter.h>
#include <unicode/normalizer2.h>

#include "QCharUnicode.h"
#include "EQTextEncoding.h"
#include "EQNormalizationForm.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Represents text formed by a sequence of Unicode characters.
/// </summary>
/// <remarks>
/// Internally, characters are encoded in UTF-16. This may change in the future.<br/>
/// Instances of this class are mutable, this means, the same instance can take different values during its lifecycle.<br/>
/// Instances of this class are not thread-safe.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS QStringUnicode
{
    // INTERNAL CLASSES
    // ------------------
public:    

    /// <summary>
    /// Iterator that steps once per Unicode character throuhout a string. This iterator is constant, which means it does not
    /// allow to modify the referenced string.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a string, it cannot point to another string ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the string.<br/>
    /// The position before the first character or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QE_LAYER_COMMON_SYMBOLS QConstCharIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the string to iterate.
        /// </summary>
        /// <param name="strString">[IN] The string to iterate.</param>
        QConstCharIterator(const QStringUnicode &strString);

        /// <summary>
        /// Copy constructor.
        /// </summary>
        /// <param name="iterator">[IN] The iterator to be copied.</param>
        QConstCharIterator(const QConstCharIterator &iterator);


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last character (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QConstCharIterator operator++(int);

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QConstCharIterator operator--(int);

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QConstCharIterator& operator++();

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QConstCharIterator& operator--();

        /// <summary>
        /// Assignment operator that makes a copy of another iterator.
        /// </summary>
        /// <param name="iterator">[IN] The other iterator to be copied.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QConstCharIterator& operator=(const QConstCharIterator &iterator);
        
        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same string to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same string; False otherwise.
        /// </returns>
        bool operator==(const QConstCharIterator &iterator) const;
        
        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different string is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different string; False otherwise.
        /// </returns>
        bool operator!=(const QConstCharIterator &iterator) const;

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const QConstCharIterator &iterator) const;

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const QConstCharIterator &iterator) const;

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the 
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const QConstCharIterator &iterator) const;

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input 
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const QConstCharIterator &iterator) const;
        
        /// <summary>
        /// Obtains the Unicode character pointed by the interator.
        /// </summary>
        /// <remarks>
        /// If the iterator points to an end position, the character U+FFFF (non-character) will be returned.<br/>
        /// If the iterator is invalid, the behavior is undefined.
        /// </remarks>
        /// <returns>
        /// A Unicode character.
        /// </returns>
        QCharUnicode GetChar() const;

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the string.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first character and the position immediately after the last character are cosidered end 
        /// positions; therefore, this method can be used both for forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <returns>
        /// True if the iterator is pointing to an end position; False otherwise.
        /// </returns>
        bool IsEnd() const;

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the string is empty, the iterator will point to the end position.
        /// </remarks>
        void MoveFirst();

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the string is empty, the iterator will point to the end position.
        /// </remarks>
        void MoveLast();

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a string may have been shortened while the iterator 
        /// was pointing to its last position). If the string to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first character or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const;


        // ATTRIBUTES
	    // ---------------
    private:

        /// <summary>
        /// The string to iterate.
        /// </summary>
        const QStringUnicode* m_pString;

        /// <summary>
        /// Wrapped class that provides the iteration functionality.
        /// </summary>
        icu::StringCharacterIterator m_iterator;

        /// <summary>
        /// A workaround to be able to point to the position before the first character in the string.
        /// </summary>
        /// <remarks>
        /// When it is True, the iterator points to that position; when it is False the iterator is pointing to whatever else.
        /// Note that the other end position, after the last position, can be easily calculated using the current implementation.
        /// </remarks>
        bool m_bIsBeforeFirst;
    
    }; // QConstCharIterator
    
    

    // CONSTANTS
	// ---------------
public:

    /// <summary>
	/// Value to be used when the length of a string is unknown but can be calculated by checking for a null terminator.
	/// </summary>
    static const int LENGTH_NULL_TERMINATED;

    /// <summary>
    /// The Byte Order Mark, used in Unicode-encoded streams to indicate that it follows a Little Endian order.
    /// </summary>
    static const QCharUnicode CHAR_BOM_LE;

    /// <summary>
    /// The Byte Order Mark, used in Unicode-encoded streams to indicate that it follows a Big Endian order.
    /// </summary>
    static const QCharUnicode CHAR_BOM_BE;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QStringUnicode();

    /// <summary>
    /// Constructor that makes a copy of another string.
    /// </summary>
    /// <param name="strString">[IN] The input string to be copied.</param>
    QStringUnicode(const QStringUnicode &strString);

    /// <summary>
    /// Constructor that builds a string from an encoded input stream.
    /// </summary>
    /// <remarks>
    /// The null-terminated option can only be used along with the encodings ASCII and ISO 8859-1, otherwise the result is undefined.<br/>
    /// When passing texts encoded in Unicode, corrupted or ill-formed sequences will be repaired by replacing the erroneous characters by U+FFFD REPLACEMENT CHARACTER.<br/>
    /// When the encoding is UTF-16 or UTF-32 (without endianness), if the input stream begins with a U+FFFE or U+FEFF BYTE ORDER MARK CHARACTERs, the bytes
    /// will be reordered depending on both the local machine architecture and which of both BOMs was specified. The BOM character will not be part of the resultant string.<br/>
    /// When the encoding is UTF-16 or UTF-32 (without endianness) and the input stream does not includes a BOM character, it is treated as if the encoding was big endian.<br/>
    /// When the encoding is UTF-16 LE, UTF-16 BE, UTF-32 LE or UTF-32 BE, the bytes in the stream will be reordered depending on both the endianness specified and the
    /// local machine's architecture. If the stream includes a BOM character, it does not affect the result and will be included in the resultant string.<br/>
    /// If the stream is a null-terminated string (ASCII or ISO 8859-1) and the length is not provided, the final null character will not be added to the resultant string.
    /// </remarks>
    /// <param name="arBytes">[IN] The input stream as an array of bytes. It should not be null. If it is null and the 
    /// input length equals zero, an empty string will be created. If is null and the specified length is greater than zero, the behavior is undefined.</param>
    /// <param name="nLength">[Optional][IN] The length, in number of bytes, of the input byte stream. If it equals zero, an empty string will be created.
    /// When the encoding is ASCII or ISO 8859-1 and the input byte stream contains a null-terminated string, the constant LENGTH_NULL_TERMINATED can
    /// be used instead. By default it is set to LENGTH_NULL_TERMINATED.</param>
    /// <param name="eEncoding">[Optional][IN] The text encoding of the input byte stream. By default it is set to ISO 8859-1.</param>
    QStringUnicode(const i8_q* arBytes, 
                   const int nLength = QStringUnicode::LENGTH_NULL_TERMINATED, 
                   const EQTextEncoding eEncoding = EQTextEncoding::E_ISO88591);

    /// <summary>
    /// Constructor that builds a string from only one character.
    /// </summary>
    /// <param name="arBytes">[IN] The character that will form the new string.</param>
    QStringUnicode(const QCharUnicode &character);


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assignment operator that copies the value of another string.
    /// </summary>
    /// <param name="strString">[IN] The input string to be copied.</param>
    /// <returns>
    /// A reference to the resident string.
    /// </returns>
    QStringUnicode& operator=(const QStringUnicode &strString);

    /// <summary>
    /// Equality operator that performs a bitwise comparison of two strings to know if they are equal.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if strings are equal; False otherwise.
    /// </returns>
    bool operator==(const QStringUnicode &strString) const;

    /// <summary>
    /// Inequality operator that performs a bitwise comparison of two strings to know if they are different.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if strings are not equal; False otherwise.
    /// </returns>
    bool operator!=(const QStringUnicode &strString) const;

    /// <summary>
    /// Addition operator that generates a new string by concatenating two others.
    /// </summary>
    /// <param name="strString">[IN] The input string to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the input string.
    /// </returns>
    QStringUnicode operator+(const QStringUnicode &strString) const;
    
    /// <summary>
    /// Array subscripting operator that returns a Unicode character located at a given position.
    /// </summary>
    /// <remarks>
    /// If the string is empty, a non-character value will be returned (U+FFFF).
    /// </remarks>
    /// <param name="uIndex">[IN] The zero-based index of the character to retrieve. It must be lower than the lenght of the string or 
    /// a non-character value (U+FFFF) will be returned.</param>
    /// <returns>
    /// True if strings are not equal; False otherwise.
    /// </returns>
    QCharUnicode operator[](const unsigned int uIndex) const;

    /// <summary>
    /// Obtains a new string from a subset of characters of the resident string, limited by a given range of positions.
    /// </summary>
    /// <param name="uStartPosition">[IN] The position (zero-based index) of the first character of the resultant substring.</param>
    /// <param name="uLastPosition">[IN] The position (zero-based index) of the last character of the resultant substring.</param>
    /// <returns>
    /// A subset of the resident string.
    /// </returns>
    QStringUnicode Substring(const unsigned int uStartPosition, const unsigned int uLastPosition) const;

    /// <summary>
    /// Obtains a constant iterator pointing to the first position.
    /// </summary>
    /// <returns>
    /// A constant iterator.
    /// </returns>
    QConstCharIterator GetConstCharIterator() const;
    
    /// <summary>
    /// Converts the string to an array of bytes encoded in certain text encoding.
    /// </summary>
    /// <remarks>
    /// The output stream will always add a null terminator if the string does not have one.<br/>
    /// Since it is not possible to predict the length of the UTF-8 representation of the string (internally encoded in UTF-16), the
    /// amount of memory reserved to allocate the result may be bigger than necessary when using that encoding. However, the output length
    /// will contain only the size of the occupied memory.<br/>
    /// When the encoding is UTF-16 or UTF-32 (without endianness), the U+FFFE or U+FEFF BYTE ORDER CHARACTER is added at the beginning of the sequence. 
    /// Which of both depends on the local machine's endianness.<br/>
    /// When using UTF-16 LE, UTF-16 BE, UTF-32 LE or UTF-32 BE encodings, the bytes of the output steam will be reordered depending on the
    /// local machine's endianness.<br/>
    /// When using the ASCII or ISO 8859-1 encodings, if there are characters that cannot be translated to such encodings, they will be
    /// replaced by Substitution characters (#26 in ASCII table).
    /// </remarks>
    /// <param name="eEncoding">[IN] The encoding of the resultant text.</param>
    /// <param name="uOutputLength">[OUT] The length, in number of bytes, of the output byte stream, counting the null terminator. 
    /// If the string is empty, it will be set to zero.</param>
    /// <returns>
    /// An array of bytes that contains the encoded text. If the string is empty, null will be returned. Remember to delete the array when
    /// do not need it anymore.
    /// </returns>
    i8_q* ToBytes(const EQTextEncoding eEncoding, unsigned int &uOutputLength) const;

    /// <summary>
    /// Applies a Unicode text normalization form algorithm to the string.
    /// </summary>
    /// <remarks>
    /// Normalization algorithms are described in the Unicode Standard Annex #15 (http://www.unicode.org/reports/tr15/).<br/>
    /// Currently, the only normalization forms supported are Canonical Decomposition (NFD) and Canonical Decomposition followed
    /// by a Canonical Composition (NFC).<br/>
    /// Normalization allows to compare two strings that are equivalent, i. e. they are compound of different characters
    /// or in a different order but represent the same glyphs or compatibles.
    /// </remarks>
    /// <param name="eNormalizationForm">[IN] The normalization form on which the algorithm will be based. Only NFC and NFD are supported.</param>
    void Normalize(const EQNormalizationForm &eNormalizationForm);
    
protected:

    /// <summary>
    /// Gets an ICU converter for a given text encoding.
    /// </summary>
    /// <param name="eEncoding">[IN] The text encoding to which the converter will convert.</param>
    /// <returns>
    /// A converter ready to be used.
    /// </returns>
    static UConverter* GetConverter(const EQTextEncoding eEncoding);

    /// <summary>
    /// Gets an ICU normalizer instance for a normalization form.
    /// </summary>
    /// <param name="eNormalizationForm">[IN] The normalization form on which the algorithm will be based.</param>
    /// <returns>
    /// A normalizer ready to be used.
    /// </returns>
    static const icu::Normalizer2* GetNormalilzer(const EQNormalizationForm &eNormalizationForm);



	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the length of the string, this means, the number of characters that compose the sequence.
    /// </summary>
    /// <returns>
    /// The number of characters, not including the final null character.
    /// </returns>
    unsigned int GetLength() const;

    /// <summary>
    /// Indicates whether the string is empty or not.
    /// </summary>
    /// <returns>
    /// True if the string is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const;

    /// <summary>
    /// Obtains a constant empty string.
    /// </summary>
    /// <returns>
    /// An empty string.
    /// </returns>
    static const QStringUnicode& GetEmpty();


	// ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// Internal string representation.
    /// </summary>
    icu::UnicodeString m_strString;

};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSTRINGUNICODE__
