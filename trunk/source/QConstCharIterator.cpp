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

#include "QStringUnicode.h"

#include "Assertions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################



//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QStringUnicode::QConstCharIterator::QConstCharIterator(const QStringUnicode &strString) : m_pString(&strString),
                                                                                          m_iterator(strString.m_strString),
                                                                                          m_bIsBeforeFirst(false)
{
}

QStringUnicode::QConstCharIterator::QConstCharIterator(const QConstCharIterator &iterator) : m_pString(iterator.m_pString),
                                                                                             m_iterator(iterator.m_iterator),
                                                                                             m_bIsBeforeFirst(iterator.m_bIsBeforeFirst)
{
}

QStringUnicode::QConstCharIterator::QConstCharIterator(const QStringUnicode &strString, const unsigned int uInitialPosition) : 
                                                                                             m_pString(&strString),
                                                                                             m_iterator(strString.m_strString, uInitialPosition),
                                                                                             m_bIsBeforeFirst(false)
{
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QStringUnicode::QConstCharIterator QStringUnicode::QConstCharIterator::operator++(int)
{
    // It is not possible to move an invalid iterator forward
    QE_ASSERT(this->IsValid(), "It is not possible to move an invalid iterator forward");

    // It is not possible to move forward when pointing to the end position after the last character
    QE_ASSERT(m_iterator.getIndex() != m_iterator.endIndex(), "It is not possible to move forward when pointing to the end position after the last character");

    QConstCharIterator previousState(*this);

    // If the iterator is incremented, the result will never be pointing to the position before the first
    if(m_bIsBeforeFirst)
        m_bIsBeforeFirst = false;
    else
        m_iterator.next();

    return previousState;
}

QStringUnicode::QConstCharIterator QStringUnicode::QConstCharIterator::operator--(int)
{
    // It is not possible to move an invalid iterator backward
    QE_ASSERT(this->IsValid(), "It is not possible to move an invalid iterator backward");

    // It is not possible to move forward when pointing to the end position before the first character
    QE_ASSERT(!m_bIsBeforeFirst, "It is not possible to move forward when pointing to the end position before the first character");

    QConstCharIterator previousState(*this);

    if(previousState.m_iterator.getIndex() == 0)
        m_bIsBeforeFirst = true;
    else
        m_iterator.previous();

    return previousState;
}

QStringUnicode::QConstCharIterator& QStringUnicode::QConstCharIterator::operator++()
{
    // It is not possible to move an invalid iterator forward
    QE_ASSERT(this->IsValid(), "It is not possible to move an invalid iterator forward");

    // It is not possible to move forward when pointing to the end position after the last character
    QE_ASSERT(m_iterator.getIndex() != m_iterator.endIndex(), "It is not possible to move forward when pointing to the end position after the last character");

    // If the iterator is incremented, the result will never be pointing to the position before the first
    if(m_bIsBeforeFirst)
        m_bIsBeforeFirst = false;
    else
        m_iterator.next();

    return *this;
}

QStringUnicode::QConstCharIterator& QStringUnicode::QConstCharIterator::operator--()
{
    // It is not possible to move an invalid iterator backward
    QE_ASSERT(this->IsValid(), "It is not possible to move an invalid iterator backward");

    // It is not possible to move forward when pointing to the end position before the first character
    QE_ASSERT(!m_bIsBeforeFirst, "It is not possible to move forward when pointing to the end position before the first character");

    if(m_iterator.getIndex() == 0)
        m_bIsBeforeFirst = true;
    else
        m_iterator.previous();

    return *this;
}

QStringUnicode::QConstCharIterator& QStringUnicode::QConstCharIterator::operator=(const QStringUnicode::QConstCharIterator &iterator)
{
    // The iterator should not be assigned to an invalid iterator
    QE_ASSERT(iterator.IsValid(), "The iterator should not be assigned to an invalid iterator");

    // Both iterators must refer to the same string
    QE_ASSERT(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    if(&iterator != this && m_pString == iterator.m_pString)
    {
        m_iterator = iterator.m_iterator;
        m_bIsBeforeFirst = iterator.m_bIsBeforeFirst;
    }

    return *this;
}

bool QStringUnicode::QConstCharIterator::operator==(const QConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    QE_ASSERT(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    QE_ASSERT(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return ( (m_iterator == iterator.m_iterator) == TRUE ) &&
           m_pString == iterator.m_pString &&
           m_bIsBeforeFirst == iterator.m_bIsBeforeFirst;
}

bool QStringUnicode::QConstCharIterator::operator!=(const QConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    QE_ASSERT(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    QE_ASSERT(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return ( (m_iterator != iterator.m_iterator) == TRUE ) ||
           m_pString != iterator.m_pString ||
           m_bIsBeforeFirst != iterator.m_bIsBeforeFirst;
}

bool QStringUnicode::QConstCharIterator::operator>(const QConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    QE_ASSERT(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    QE_ASSERT(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return (m_iterator.getIndex() > iterator.m_iterator.getIndex() ||
            (!m_bIsBeforeFirst && iterator.m_bIsBeforeFirst) ) &&
           m_pString == iterator.m_pString;
    // The position before the first is considered lower than any other position
}

bool QStringUnicode::QConstCharIterator::operator<(const QConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    QE_ASSERT(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    QE_ASSERT(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return (m_iterator.getIndex() < iterator.m_iterator.getIndex() ||
            (m_bIsBeforeFirst && !iterator.m_bIsBeforeFirst) ) &&
           m_pString == iterator.m_pString;
}

bool QStringUnicode::QConstCharIterator::operator>=(const QConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    QE_ASSERT(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    QE_ASSERT(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    const int32_t& nResidentPosition = m_iterator.getIndex();
    const int32_t& nInputPosition = iterator.m_iterator.getIndex();

    return (nResidentPosition > nInputPosition ||
            (!m_bIsBeforeFirst && iterator.m_bIsBeforeFirst) ||
            (nResidentPosition == nInputPosition && m_bIsBeforeFirst == iterator.m_bIsBeforeFirst) ) &&
           m_pString == iterator.m_pString;
}

bool QStringUnicode::QConstCharIterator::operator<=(const QConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    QE_ASSERT(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    QE_ASSERT(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    const int32_t& nResidentPosition = m_iterator.getIndex();
    const int32_t& nInputPosition = iterator.m_iterator.getIndex();

    return (nResidentPosition < nInputPosition ||
            (m_bIsBeforeFirst && !iterator.m_bIsBeforeFirst) ||
            (nResidentPosition == nInputPosition && m_bIsBeforeFirst == iterator.m_bIsBeforeFirst) ) &&
           m_pString == iterator.m_pString;
}

bool QStringUnicode::QConstCharIterator::IsEnd() const
{
    // The iterator must be valid to get a correct result
    QE_ASSERT(this->IsValid(), "The iterator must be valid to get a correct result");

    return m_bIsBeforeFirst || m_iterator.getIndex() == m_iterator.endIndex();
}

QCharUnicode QStringUnicode::QConstCharIterator::GetChar() const
{
    // It is not possible to get the character refered to by an invalid iterator
    QE_ASSERT(this->IsValid(), "It is not possible to get the character refered to by an invalid iterator");

    // It is not possible to get the character of an end position
    QE_ASSERT(!this->IsEnd(), "It is not possible to get the character of an end position");

    static const UChar32 NON_CHARACTER = 0xFFFF; // U+FFFF, the same returned by the current32() method when the iterator points to the end position

    UChar32 character = m_bIsBeforeFirst ? NON_CHARACTER : m_iterator.current32();

    return QCharUnicode(scast_q(character, codepoint_q));
}

void QStringUnicode::QConstCharIterator::MoveFirst()
{
    // It is not possible to go to the first position of an empty string
    QE_ASSERT(m_pString->GetLength() > 0, "It is not possible to go to the first position of an empty string");

    m_bIsBeforeFirst = false;

    m_iterator.first();
}

void QStringUnicode::QConstCharIterator::MoveLast()
{
    // It is not possible to go to the last position of an empty string
    QE_ASSERT(m_pString->GetLength() > 0, "It is not possible to go to the last position of an empty string");

    m_bIsBeforeFirst = false;

    m_iterator.last();
}

bool QStringUnicode::QConstCharIterator::IsValid() const
{
    // If the index of the iterator is outside the bounds of the string, the iterator is not valid
    // The end position is valid
    return scast_q(m_iterator.getIndex(), unsigned int) <= m_pString->GetLength();
}



} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
