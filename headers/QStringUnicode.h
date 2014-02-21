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

#include "unicode/unistr.h"
#include "unicode/schriter.h"

#include "QCharUnicode.h"

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
        /// Assignation operator that makes a copy of another iterator.
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


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assignation operator that copies the value of another string.
    /// </summary>
    /// <param name="strString">[IN] The input string to be copied.</param>
    /// <returns>
    /// A reference to the resident string.
    /// </returns>
    QStringUnicode& operator=(const QStringUnicode &strString);

    /// <summary>
    /// Obtains a new string from a subset of characters of the resident string, limited by a given range of positions.
    /// </summary>
    /// <param name="uStartPosition">[IN] The position (zero-based index) of the first character of the resultant substring.</param>
    /// <param name="uLastPosition">[IN] The position (zero-based index) of the last character of the resultant substring.</param>
    /// <returns>
    /// A subset of the resident string.
    /// </returns>
    QStringUnicode Substring(const unsigned int &uStartPosition, const unsigned int &uLastPosition) const;

    /// <summary>
    /// Obtains a constant iterator pointing to the first position.
    /// </summary>
    /// <returns>
    /// A constant iterator.
    /// </returns>
    QConstCharIterator GetConstCharIterator() const;


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the length of the string, this means, the number of characters that compose the sequence.
    /// </summary>
    /// <returns>
    /// The number of characters.
    /// </returns>
    unsigned int GetLength() const;


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
