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

#ifndef __QLIST__
#define __QLIST__

#include "DataTypesDefinitions.h"
#include "ToolsDefinitions.h"
#include "Assertions.h"
#include "QPoolAllocator.h"
#include "QAlignment.h"
#include "QComparatorDefault.h"
#include "AllocationOperators.h"
#include "EQIterationDirection.h"


using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Represents a double linked list of elements that can be accessed either sequentally or arbitrarily, using a zero-based index.
/// </summary>
/// <remarks>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T"> The type of the list elements.</typeparam>
/// <typeparam name="AllocatorT"> The allocator used to reserve memory. The default type is QPoolAllocator.</typeparam>
/// <typeparam name="ComparatorT"> The comparator. The default type is QComparatorDefault.</typeparam>
template <class T, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class ComparatorT = QComparatorDefault<T> >
class QList
{
    // CONSTANTS
    // ---------------
private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float REALLOCATION_FACTOR;


    // INTERNAL CLASSES
    // -----------------

protected:

    /// <summary>
    /// Class intended to store the information needed to link one element of the list to another.
    /// </summary>
    class QLink
    {
        // CONSTRUCTORS
        // ---------------

    public:

        /// <summary>
        /// Constructor with the positions in the allocated memory chunk to the previous and next elements,
        /// passed by parameter.
        /// </summary>
        /// <param name="uPrevious">[IN] Position of the previous element.</param>
        /// <param name="uNext">[IN] Position of the next element.</param>
        QLink(const pointer_uint_q uPrevious, const pointer_uint_q uNext) :
                m_uNext(uNext),
                m_uPrevious(uPrevious)
                
        {
        }


        // PROPERTIES
        // ---------------

        /// <summary>
        /// Returns the index of the next element in the list.
        /// </summary>
        /// <returns>
        /// The index of the next element in the list. Returns QList::END_POSITION_FORWARD constant if there is no previous element.
        /// </returns>
        pointer_uint_q GetNext() const
        {
            return m_uNext;
        }

        /// <summary>
        /// Returns the index of the previous element in the list.
        /// </summary>
        /// <returns>
        /// The index of the previous element in the list. Returns QList::END_POSITION_BACKWARD constant if there is no previous element.
        /// </returns>
        pointer_uint_q GetPrevious() const
        {
            return m_uPrevious;
        }

        /// <summary>
        /// Sets the index of the next element in the list.
        /// </summary>
        /// <param name="uNext">[IN] The index of the next element in the list. If there is no next element, you must pass QList::END_POSITION_FORWARD constant.</param>
        void SetNext(const pointer_uint_q uNext)
        {
            m_uNext = uNext;
        }

        /// <summary>
        /// Sets the index of the previous element in the list.
        /// </summary>
        /// <param name="uPrevious">[IN] The index of the previous element in the list. If there is no previous element, you must pass QList::END_POSITION_BACKWARD constant.</param>
        void SetPrevious(const pointer_uint_q uPrevious)
        {
            m_uPrevious = uPrevious;
        }

    public:

        // ATTRIBUTES
        // ---------------

    protected:

        /// <summary>
        /// The index of the next element in the list. QList::END_POSITION_FORWARD must be used when there is no next element.
        /// </summary>
        pointer_uint_q m_uNext;

        /// <summary>
        /// The index of the previous element in the list. QList::END_POSITION_BACKWARD must be used when there is no previous element.
        /// </summary>
        pointer_uint_q m_uPrevious;

    };

public:

    /// <summary>
    /// Iterator that steps once per element of a list and does not allow to modify them.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a list, it cannot point to another list ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the list.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QConstListIterator
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the list to iterate and the position to point to. This constructor is intended to be used internally, use
        /// GetIterator method of the QList class instead.
        /// </summary>
        /// <remarks>
        /// If the list is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pList">[IN] The list to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of list elements, but the physical.
        /// It must be lower than the capacity of the list.</param>
        QConstListIterator(const QList* pList, const unsigned int uPosition) : m_pList(pList), m_uPosition(uPosition)
        {
            QE_ASSERT_ERROR(pList != null_q, "Invalid argument: The pointer to the list cannot be null");
            QE_ASSERT_WARNING(pList->GetCapacity() > uPosition || 
                              uPosition == QList::END_POSITION_BACKWARD || 
                              uPosition == QList::END_POSITION_FORWARD, "Invalid argument: The position must be lower than the capacity of the list");

            if(pList == null_q || 
               (pList->GetCapacity() <= uPosition && uPosition != QList::END_POSITION_BACKWARD && uPosition != QList::END_POSITION_FORWARD) || 
               pList->IsEmpty())
                   m_uPosition = QList::END_POSITION_FORWARD;
        }


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same list as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QConstListIterator& operator=(const QConstListIterator &iterator)
        {
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid.");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "The input iterator points to a different list");

            if(m_pList == iterator.m_pList)
                m_uPosition = iterator.m_uPosition;

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T& operator*() const
        {
            // Note: This code is a copy of the same method of QListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the list element");

            QE_ASSERT_ERROR(m_uPosition != QList::END_POSITION_FORWARD && m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return *(scast_q(m_pList->m_elementAllocator.GetPointer(), T*) + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T* operator->() const
        {
            // Note: This code is a copy of the same method of QListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the list element");

            QE_ASSERT_ERROR(m_uPosition != QList::END_POSITION_FORWARD && m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return scast_q(m_pList->m_elementAllocator.GetPointer(), T*) + m_uPosition;
        }

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QConstListIterator operator++(int)
        {
            // Note: This code is a copy of the same method of QListIterator (replacing QListIterator with QConstListIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QConstListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = QList::END_POSITION_FORWARD;
            else if(m_uPosition == QList::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != QList::END_POSITION_FORWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetNext();

            return iteratorCopy;
        }

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QConstListIterator operator--(int)
        {
            // Note: This code is a copy of the same method of QListIterator (replacing QListIterator with QConstListIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QConstListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = QList::END_POSITION_BACKWARD;
            else if(m_uPosition == QList::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != QList::END_POSITION_BACKWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetPrevious();

            return iteratorCopy;
        }

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QConstListIterator& operator++()
        {
            // Note: This code is a copy of the same method of QListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = QList::END_POSITION_FORWARD;
            else if(m_uPosition == QList::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != QList::END_POSITION_FORWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetNext();

            return *this;
        }

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QConstListIterator& operator--()
        {
            // Note: This code is a copy of the same method of QListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = QList::END_POSITION_BACKWARD;
            else if(m_uPosition == QList::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != QList::END_POSITION_BACKWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetPrevious();

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same list to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same list; False otherwise.
        /// </returns>
        bool operator==(const QConstListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            return m_uPosition == iterator.m_uPosition && m_pList == iterator.m_pList;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different list is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different list; False otherwise.
        /// </returns>
        bool operator!=(const QConstListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            return m_uPosition != iterator.m_uPosition || m_pList != iterator.m_pList;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const QConstListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QList::END_POSITION_FORWARD &&
               m_uPosition != QList::END_POSITION_BACKWARD)
            {
                QList::QConstListIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator does not equal the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const QConstListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QList::END_POSITION_BACKWARD &&
               m_uPosition != QList::END_POSITION_FORWARD)
            {
                QList::QConstListIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator equals the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const QConstListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QList::QConstListIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator does not equal the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const QConstListIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QList::QConstListIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator equals the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the list.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <returns>
        /// True if the iterator is pointing to an end position; False otherwise.
        /// </returns>
        bool IsEnd() const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return m_uPosition == QList::END_POSITION_BACKWARD || m_uPosition == QList::END_POSITION_FORWARD;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the list, distinguishing which of them.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <param name="eIterationDirection">[IN] The iteration direction used to identify which of the end positions is checked.</param>
        /// <returns>
        /// True if the iterator is pointing to the position after the last element when iterating forward or if it is
        /// pointing to the position immediately before the first position when iterating backward; False otherwise.
        /// </returns>
        bool IsEnd(const EQIterationDirection &eIterationDirection) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return (eIterationDirection == EQIterationDirection::E_Backward && m_uPosition == QList::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EQIterationDirection::E_Forward  && m_uPosition == QList::END_POSITION_FORWARD);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of QListIterator

            m_uPosition = m_pList->m_uFirst == QList::END_POSITION_BACKWARD ? QList::END_POSITION_FORWARD : m_pList->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of QListIterator

            m_uPosition = m_pList->m_uLast;
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a list may have been shortened while the iterator
        /// was pointing to its last position). If the list to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_pList != null_q && 
                   (m_uPosition < m_pList->m_linkAllocator.GetPoolSize() / sizeof(QList::QLink) ||
                    m_uPosition == QList::END_POSITION_BACKWARD ||
                    m_uPosition == QList::END_POSITION_FORWARD);
        }


        // ATTRIBUTES
        // ---------------
    protected:

        /// <summary>
        /// The list the iterator points to.
        /// </summary>
        const QList* m_pList;

        /// <summary>
        /// The current iteration position regarding the base position of the buffer (zero). It is zero-based.
        /// </summary>
        pointer_uint_q m_uPosition;

    }; // QConstListIterator

    
    /// <summary>
    /// Iterator that steps once per element of a list.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a list, it cannot point to another list ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the list.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QListIterator : public QList::QConstListIterator
    {
        using QList::QConstListIterator::m_pList;
        using QList::QConstListIterator::m_uPosition;


        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the list to iterate and the position to point to. This constructor is intended to be used internally, use
        /// GetIterator method of the QList class instead.
        /// </summary>
        /// <remarks>
        /// If the list is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pList">[IN] The list to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of list elements, but the physical.
        /// It must be lower than the capacity of the list.</param>
        QListIterator(const QList* pList, const unsigned int uPosition) : QConstListIterator(pList, uPosition)
        {
        }


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same list as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QListIterator& operator=(const QListIterator &iterator)
        {
            QList::QConstListIterator::operator=(iterator);
            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T& operator*() const
        {
            // Note: This code is a copy of the same method of QConstListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the list element");

            QE_ASSERT_ERROR(m_uPosition != QList::END_POSITION_FORWARD && m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return *(scast_q(m_pList->m_elementAllocator.GetPointer(), T*) + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T* operator->() const
        {
            // Note: This code is a copy of the same method of QConstListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the list element");

            QE_ASSERT_ERROR(m_uPosition != QList::END_POSITION_FORWARD && m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return scast_q(m_pList->m_elementAllocator.GetPointer(), T*) + m_uPosition;
        }

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QListIterator operator++(int)
        {
            // Note: This code is a copy of the same method of QConstListIterator (replacing QConstListIterator with QListIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = QList::END_POSITION_FORWARD;
            else if(m_uPosition == QList::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != QList::END_POSITION_FORWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetNext();

            return iteratorCopy;
        }

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QListIterator operator--(int)
        {
            // Note: This code is a copy of the same method of QConstListIterator (replacing QConstListIterator with QListIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = QList::END_POSITION_BACKWARD;
            else if(m_uPosition == QList::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != QList::END_POSITION_BACKWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetPrevious();

            return iteratorCopy;
        }

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QListIterator& operator++()
        {
            // Note: This code is a copy of the same method of QConstListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = QList::END_POSITION_FORWARD;
            else if(m_uPosition == QList::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != QList::END_POSITION_FORWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetNext();

            return *this;
        }

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QListIterator& operator--()
        {
            // Note: This code is a copy of the same method of QConstListIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QList::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = QList::END_POSITION_BACKWARD;
            else if(m_uPosition == QList::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != QList::END_POSITION_BACKWARD)
                m_uPosition = (((QList::QLink*)m_pList->m_linkAllocator.GetPointer()) + m_uPosition)->GetPrevious();

            return *this;
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of QConstListIterator

            m_uPosition = m_pList->m_uFirst == QList::END_POSITION_BACKWARD ? QList::END_POSITION_FORWARD : m_pList->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of QConstListIterator

            m_uPosition = m_pList->m_uLast;
        }

    }; // QListIterator
    

    // TYPEDEFS
    // --------------
public:

    typedef typename QList::QListIterator Iterator;
    typedef typename QList::QConstListIterator ConstIterator;


    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Number of elements for which to reserve memory in the default constructor.
    /// </summary>
    static const pointer_uint_q DEFAULT_NUMBER_OF_ELEMENTS = 1;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the last element.
    /// </summary>
    static const pointer_uint_q END_POSITION_FORWARD = -1;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the first element.
    /// </summary>
    static const pointer_uint_q END_POSITION_BACKWARD = -2;
    
public:

    /// <summary>
    /// Constant to symbolize an invalid index returned when an element is not found.
    /// </summary>
    static const pointer_uint_q ELEMENT_NOT_FOUND = -1;


    // CONSTRUCTORS
    // ---------------

public:

    /// <summary>
    /// Default constructor. It reserves memory for the number of elements indicated at DEFAULT_NUMBER_OF_ELEMENTS constants.
    /// </summary>
    QList() :
            m_uFirst(QList::END_POSITION_BACKWARD),
            m_uLast(QList::END_POSITION_FORWARD),
            m_elementAllocator(QList::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
            m_linkAllocator(QList::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)))
    {
    }

    /// <summary>
    /// Constructor that reserves space to store the number of elements passed by parameter.
    /// </summary>
    /// <param name="uInitialCapacity">[IN] Number of elements for wich to reserve space. It must be greater than zero.</param>
    QList(const pointer_uint_q uInitialCapacity) :
            m_uFirst(QList::END_POSITION_BACKWARD),
            m_uLast(QList::END_POSITION_FORWARD),
            m_elementAllocator(uInitialCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
            m_linkAllocator(uInitialCapacity * sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)))
    {
        QE_ASSERT_ERROR( uInitialCapacity > 0, "Initial capacity must be greater than zero" );
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <remarks>
    /// The copy constructor of every element is called.
    /// </remarks>
    /// <param name="list">[IN] Source list to copy.</param>
    QList(const QList& list) : m_elementAllocator(list.m_elementAllocator.GetPoolSize(), sizeof(T), QAlignment(alignof_q(T))),
                               m_linkAllocator(list.m_linkAllocator.GetPoolSize(), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)))
    {
        if(list.m_uFirst == QList::END_POSITION_BACKWARD)
        {
            m_uFirst = QList::END_POSITION_BACKWARD;
            m_uLast = QList::END_POSITION_FORWARD;
        }
        else
        {
            list.m_linkAllocator.CopyTo(m_linkAllocator);
            list.m_elementAllocator.CopyTo(m_elementAllocator);

            m_uFirst = list.m_uFirst;
            m_uLast = list.m_uLast;

            QList::QListIterator iteratorOrigin = list.GetFirst();
            QList::QListIterator iteratorDestination = this->GetFirst();

            for(; !iteratorOrigin.IsEnd(); ++iteratorOrigin, ++iteratorDestination)
            {
                new(&(*iteratorDestination)) T(*iteratorOrigin);
            }
        }
    }
    
    /// <summary>
    /// Constructor that receives an existing array and its size.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the list.
    /// </remarks>
    /// <param name="pArray">[IN] The existing array that will be copied. It must not be null.</param>
    /// <param name="uNumberOfElements">[IN] The number of elements in the input array. It must be greater than zero.</param>
    QList(const T* pArray, const pointer_uint_q uNumberOfElements) :
                                                        m_uFirst(QList::END_POSITION_BACKWARD),
                                                        m_uLast(QList::END_POSITION_FORWARD),
                                                        m_elementAllocator(uNumberOfElements * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                                        m_linkAllocator(uNumberOfElements * sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)))
    {
        QE_ASSERT_ERROR( pArray != null_q, "The argument pArray is null." );
        QE_ASSERT_ERROR( uNumberOfElements > 0, "The number of elements in the array must be greater than zero." );

        const T* pElement = pArray;

        for(pointer_uint_q uIndex = 0; uIndex < uNumberOfElements; ++uIndex, ++pElement)
            this->Add(*pElement);
    }


    // DESTRUCTOR
    // ---------------

public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element is called in the same order they appear in the list.
    /// </remarks>
    ~QList()
    {
        if(!this->IsEmpty())
        {
            // Iterates the list in an orderly manner, calling the destructor for each element.
            for(QList::QListIterator it = this->GetFirst(); !it.IsEnd(); ++it)
                (*it).~T();
        }
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignment operator that copies one list to another.
    /// </summary>
    /// <remarks>
    /// Assignment operator will be called for every element of the list.
    /// </remarks>
    /// <param name="list">[IN] List to copy in the current list.</param>
    /// <returns>
    /// A reference to the current list.
    /// </returns>
    QList& operator= (const QList& list)
    {
        if(this != &list)
        {
            if(list.GetCount() == this->GetCount())
            {
                QListIterator iteratorOrigin = list.GetFirst();
                QListIterator iteratorDestination = this->GetFirst();

                for(; !iteratorOrigin.IsEnd(); ++iteratorOrigin, ++iteratorDestination)
                    *iteratorDestination = *iteratorOrigin;
            }
            else if(list.GetCount() < this->GetCount())
            {
                pointer_uint_q uFirstIndexToDestroy;
                pointer_uint_q uOldLast = m_uLast;

                if(list.GetCount() == 0)
                {
                    uFirstIndexToDestroy = m_uFirst;
                    m_uFirst = QList::END_POSITION_BACKWARD;
                    m_uLast = QList::END_POSITION_FORWARD;
                }
                else
                {
                    // Makes the copy calling assignment operator with existing elements.

                    T* pElementOrigin = null_q;
                    T* pElementDestination = null_q;
                    QList::QLink* pLinkOrigin = null_q;
                    QList::QLink* pLinkDestination = null_q;

                    pointer_uint_q uIndexOrigin = list.m_uFirst;
                    pointer_uint_q uIndexDestination = m_uFirst;

                    bool bCopied = false;

                    while(!bCopied)
                    {
                        pElementOrigin = (T*)list.m_elementAllocator.GetPointer() + uIndexOrigin;
                        pElementDestination = (T*)m_elementAllocator.GetPointer() + uIndexDestination;

                        *pElementDestination = *pElementOrigin;

                        bCopied = (uIndexOrigin == list.m_uLast);
                        m_uLast = uIndexDestination;

                        pLinkOrigin = (QList::QLink*)list.m_linkAllocator.GetPointer() + uIndexOrigin;
                        uIndexOrigin = pLinkOrigin->GetNext();

                        pLinkDestination = (QList::QLink*)m_linkAllocator.GetPointer() + uIndexDestination;
                        uIndexDestination = pLinkDestination->GetNext();
                    }
                    uFirstIndexToDestroy = uIndexDestination;
                }

                // Destroys the rest of the destination list

                pointer_uint_q uIndex = uFirstIndexToDestroy;
                pointer_uint_q uNextIndex;

                bool bDestroyed = false;

                while(!bDestroyed && uIndex != QList::END_POSITION_FORWARD)
                {
                    QList::QLink* pLink = (QList::QLink*)m_linkAllocator.GetPointer() + uIndex;
                    uNextIndex = pLink->GetNext();
                    m_linkAllocator.Deallocate(pLink);

                    T* pElement = (T*)m_elementAllocator.GetPointer() + uIndex;
                    pElement->~T();
                    m_elementAllocator.Deallocate(pElement);

                    bDestroyed = (uIndex == uOldLast);
                    uIndex = uNextIndex;
                }
            }
            else
            {
                // Increases the capacity of the destination, if necessary
                if(list.GetCapacity() > this->GetCapacity())
                    this->Reserve(list.GetCapacity());

                QListIterator iteratorOrigin = list.GetFirst();
                QListIterator iteratorDestination = this->GetFirst();

                // Copies as many elements as it has the destination list.

                for(; !iteratorDestination.IsEnd(); ++iteratorOrigin, ++iteratorDestination)
                    *iteratorDestination = *iteratorOrigin;

                // Adds the rest of elements if needed.

                while(!iteratorOrigin.IsEnd())
                {
                    this->Add(*iteratorOrigin);
                    ++iteratorOrigin;
                }
            }
        }
        
        return *this;
    }
    
    /// <summary>
    /// Equality operator that checks whether two lists are equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other list. Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="list">[IN] The list to compare to.</param>
    /// <returns>
    /// True if all the elements of both lists are equal; False otherwise.
    /// </returns>
    bool operator==(const QList &list) const
    {
        bool bAreEqual = true;

        // If they are not the same instance and they are not both empty
        if(this != &list && !(m_uLast == QList::END_POSITION_FORWARD && list.m_uLast == QList::END_POSITION_FORWARD))
        {
            // If they have the same number of elements
            if(this->GetCount() == list.GetCount())
            {
                QList::QConstListIterator itThis = this->GetFirst();
                QList::QConstListIterator itInput = list.GetFirst();

                while(bAreEqual && !itThis.IsEnd())
                {
                    bAreEqual = m_comparator.Compare(*itThis, *itInput) == 0;
                    ++itThis;
                    ++itInput;
                }
            }
            else
                bAreEqual = false;
        }

        return bAreEqual;
    }
    
    /// <summary>
    /// Inequality operator that checks whether two lists are not equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other list. Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="list">[IN] The list to compare to.</param>
    /// <returns>
    /// True if not all the elements of both lists are equal; False otherwise.
    /// </returns>
    bool operator!=(const QList &list) const
    {
        return !this->operator==(list);
    }
    
    /// <summary>
    /// Performs a fast shallow copy of the list elements.
    /// </summary>
    /// <remarks>
    /// Neither elements' constructor nor element's assignment operator are called.
    /// </remarks>
    /// <param name="destinationList"> [OUT] Destination list where to copy the list elements. If the destination list's capacity is lower
    /// than the resident list's capacity, it will be increased.</param>
    void Clone(QList &destinationList) const
    {
        // Uncomment when reserve method is implemented
        if(destinationList.GetCapacity() < this->GetCapacity())
            destinationList.Reserve(this->GetCapacity());

        m_elementAllocator.CopyTo(destinationList.m_elementAllocator);
        m_linkAllocator.CopyTo(destinationList.m_linkAllocator);
        destinationList.m_uFirst = m_uFirst;
        destinationList.m_uLast = m_uLast;
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to access. It must be less than the list's size. Note that indexes are zero-based.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& GetValue(const pointer_uint_q uIndex) const
    {
        QE_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );
        
        return *this->GetIterator(uIndex);
    }

    /// <summary>
    /// Sets the value in the index passed as parameter.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to set. It must be less than the list's size. Note that indexes are zero-based.</param>
    void SetValue(const pointer_uint_q uIndex, const T& value)
    {
        QE_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );
        
        *this->GetIterator(uIndex) = value;
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position. Indexes are zero-based.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to access. It must be less than the list's size.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& operator[] (const pointer_uint_q uIndex) const
    {
        // [TODO] raul. When unit tests get done, check if the program crashes in case the index is not lower than the number of elements.
        // [TODO] raul. If so a remark must be added in the documentation.
        return this->GetValue(uIndex);
    }
    
    /// <summary>
    /// Gets an iterator that points to a given position in the list.
    /// </summary>
    /// <param name="uIndex">[IN] Position in the list, starting at zero, to which the iterator will point. If it is out of bounds, the returned iterator will point 
    /// to the end position.</param>
    /// <returns>
    /// An iterator that points to the position of the element.
    /// </returns>
    QListIterator GetIterator(const pointer_uint_q uIndex) const 
    {
        QE_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );

        QList::QListIterator iterator(this, m_uFirst);

        if(!this->IsEmpty())
            for(pointer_uint_q i = 0; i < uIndex; ++i)
                ++iterator;

        return iterator;
    }

    /// <summary>
    /// Gets an iterator that points to the first position in the list.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the first element. If the list is empty, the iterator will point to the end position.
    /// </returns>
    QListIterator GetFirst() const
    {
        return QList::QListIterator(this, m_uFirst);
    }

    /// <summary>
    /// Gets an iterator that points to the last position in the list.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the last element. If the list is empty, the iterator will point to the end position.
    /// </returns>
    QListIterator GetLast() const
    {
        return QList::QListIterator(this, m_uLast);
    }
    
    /// <summary>
    /// Increases the capacity of the list, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means that any pointer to elements of this array will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const pointer_uint_q uNumberOfElements)
    {
        if(uNumberOfElements > this->GetCapacity())
        {
            m_elementAllocator.Reallocate(uNumberOfElements * sizeof(T));
            m_linkAllocator.Reallocate(uNumberOfElements * sizeof(QList::QLink));
        }
    }

    /// <summary>
    /// Copies an element to the end of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    void Add(const T &newElement)
    {
        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);
        
        pointer_uint_q uNewLinkPrevious = m_uLast;

        if(this->IsEmpty())
        {
            // If the list is empty, there is no previous link
            uNewLinkPrevious = QList::END_POSITION_BACKWARD;
        }

        // Creates the new link
        QList::QLink* pBasePointer = scast_q(m_linkAllocator.GetPointer(), QList::QLink*);
        QList::QLink* pNewLastLink = new(m_linkAllocator.Allocate()) QList::QLink(uNewLinkPrevious, QList::END_POSITION_FORWARD);

        if(uNewLinkPrevious != QList::END_POSITION_BACKWARD)
        {
            // Makes the last link point to the new link
            QList::QLink* pLastLink = pBasePointer + m_uLast;
            pLastLink->SetNext(pNewLastLink - pBasePointer);
            m_uLast = pNewLastLink - pBasePointer;
        }
        else
        {
            m_uFirst = m_uLast = 0;
        }

        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the list and returns an iterator that points to it.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="position">[IN] The position where the new element will be placed. It should not be an end position; if it is, 
    /// the element will be inserted at the end by default. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// list; otherwise, the behavior is undefined.</param>
    /// <returns>
    /// An iterator that points to the just inserted element.
    /// </returns>
    QListIterator Insert(const T &newElement, const typename QList::QConstListIterator &position)
    {
        QE_ASSERT_ERROR(position.IsValid(), "The input iterator is not valid");
        QE_ASSERT_WARNING(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        // Gets the position of the iterator
        pointer_uint_q uIndex = &(*position) - (T*)m_elementAllocator.GetPointer();
        QList::QLink* pBasePointer = scast_q(m_linkAllocator.GetPointer(), QList::QLink*);

        pointer_uint_q uNewLinkNext = 0;
        pointer_uint_q uNewLinkPrevious = 0;

        QList::QLink* pNextLink = null_q;
        QList::QLink* pPreviousLink = null_q;

        // Calculates what's the next link and what's the previous one
        if(this->IsEmpty())
        {
            // If the list is empty, there is no previous link nor next link
            uNewLinkPrevious = QList::END_POSITION_BACKWARD;
            uNewLinkNext = QList::END_POSITION_FORWARD;
        }
        else if(position.IsEnd(EQIterationDirection::E_Forward))
        {
            // Adding at the end
            pPreviousLink = pBasePointer + m_uLast;
            uNewLinkPrevious = m_uLast;
            uNewLinkNext = QList::END_POSITION_FORWARD;
        }
        else if(uIndex == m_uFirst)
        {
            // Adding at the beginning
            pNextLink = pBasePointer + m_uFirst;
            uNewLinkPrevious = QList::END_POSITION_BACKWARD;
            uNewLinkNext = m_uFirst;
        }
        else
        {
            // Adding somewhere in the middle
            pNextLink = pBasePointer + uIndex;
            uNewLinkPrevious = pNextLink->GetPrevious();
            uNewLinkNext = uIndex;
            pPreviousLink = pBasePointer + uNewLinkPrevious;
        }

        // Creates the new link
        QList::QLink* pNewLastLink = new(m_linkAllocator.Allocate()) QList::QLink(uNewLinkPrevious, uNewLinkNext);
        pointer_uint_q uNewLinkPosition = pNewLastLink - pBasePointer;

        if(pNextLink)
        {
            // Makes the next link point to the new link
            pNextLink->SetPrevious(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the end
            m_uLast = uNewLinkPosition;
        }
        
        if(pPreviousLink)
        {
            // Makes the next link point to the new link
            pPreviousLink->SetNext(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the beginning
            m_uFirst = uNewLinkPosition;
        }

        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);

        return QList::QListIterator(this, uNewLinkPosition);
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="uIndex">[IN] The index (zero-based) where the new element will be placed. It should be lower than the number of elements of the list; if it is not, 
    /// the element will be inserted at the end by default.</param>
    void Insert(const T &newElement, const pointer_uint_q uPosition)
    {
        QE_ASSERT_WARNING(!this->IsEmpty() && uPosition < this->GetCount(), "The input iterator is out of bounds");
        
        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        pointer_uint_q uNewLinkNext = 0;
        pointer_uint_q uNewLinkPrevious = 0;

        QList::QLink* pNextLink = null_q;
        QList::QLink* pPreviousLink = null_q;

        QList::QLink* pBasePointer = scast_q(m_linkAllocator.GetPointer(), QList::QLink*);

        // Gets the physical position of the link at the given ordinal position
        pointer_uint_q uIndex = &this->GetValue(uPosition) - (T*)m_elementAllocator.GetPointer();

        // Calculates what's the next link and what's the previous one
        if(this->IsEmpty())
        {
            // If the list is empty, there is no previous link
            uNewLinkPrevious = QList::END_POSITION_BACKWARD;
            uNewLinkNext = QList::END_POSITION_FORWARD;
        }
        else if(uIndex >= this->GetCount())
        {
            // Adding at the end
            pPreviousLink = pBasePointer + m_uLast;
            uNewLinkPrevious = m_uLast;
            uNewLinkNext = QList::END_POSITION_FORWARD;
        }
        else if(uIndex == m_uFirst)
        {
            // Adding at the beginning
            pNextLink = pBasePointer + m_uFirst;
            uNewLinkPrevious = QList::END_POSITION_BACKWARD;
            uNewLinkNext = m_uFirst;
        }
        else
        {
            // Adding somewhere in the middle
            pNextLink = pBasePointer + uIndex;
            uNewLinkPrevious = pNextLink->GetPrevious();
            uNewLinkNext = uIndex;
            pPreviousLink = pBasePointer + uNewLinkPrevious;
        }

        // Creates the new link
        QList::QLink* pNewLastLink = new(m_linkAllocator.Allocate()) QList::QLink(uNewLinkPrevious, uNewLinkNext);
        pointer_uint_q uNewLinkPosition = pNewLastLink - pBasePointer;

        if(pNextLink)
        {
            // Makes the next link point to the new link
            pNextLink->SetPrevious(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the end
            m_uLast = uNewLinkPosition;
        }
        
        if(pPreviousLink)
        {
            // Makes the next link point to the new link
            pPreviousLink->SetNext(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the beginning
            m_uFirst = uNewLinkPosition;
        }

        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the list and returns an iterator that points to the next position.
    /// </summary>
    /// <remarks>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="position">[IN] The position of the element to be deleted. It should not be an end position; if it is, 
    /// nothing will be done. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// list; otherwise, the behavior is undefined.</param>
    /// <returns>
    /// An iterator that points to the ordinal position that was occupied by the just removed element. If there was not another element next, 
    /// the iterator will point to the end position.
    /// </returns>
    QListIterator Remove(const typename QList::QListIterator position)
    {
        QE_ASSERT_ERROR(position.IsValid(), "The input iterator is not valid");
        QE_ASSERT_WARNING(!this->IsEmpty(), "The list is empty, there is nothing to remove");
        QE_ASSERT_WARNING(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        pointer_uint_q uNext = QList::END_POSITION_FORWARD;
        pointer_uint_q uPrevious = QList::END_POSITION_BACKWARD;

        if(!this->IsEmpty() && !position.IsEnd())
        {
            // Gets the position of the iterator
            pointer_uint_q uIndex = &(*position) - (T*)m_elementAllocator.GetPointer();
            QList::QLink* pLinkBasePointer = scast_q(m_linkAllocator.GetPointer(), QList::QLink*);
            QList::QLink* pLinkToRemove = pLinkBasePointer + uIndex;
            T* pElementToRemove = &(*position);

            uNext = pLinkToRemove->GetNext();
            uPrevious = pLinkToRemove->GetPrevious();

            if(uNext != QList::END_POSITION_FORWARD)
            {
                // If there is next link
                QList::QLink* pNextLink = pLinkBasePointer + uNext;
                pNextLink->SetPrevious(uPrevious);
            }
            else if(uPrevious != QList::END_POSITION_BACKWARD)
            {
                // If this link was the last one, and there is a previous link, the last link in the list will be the previous link
                m_uLast = uPrevious;
            }
            else
            {
                // If this link was the only one in the list the first and the last position are end positions
                m_uFirst = QList::END_POSITION_BACKWARD;
                m_uLast = QList::END_POSITION_FORWARD;
            }

            if(uPrevious != QList::END_POSITION_BACKWARD)
            {
                QList::QLink* pPreviousLink = pLinkBasePointer + uPrevious;
                pPreviousLink->SetNext(uNext);
            }
            else if(uNext != QList::END_POSITION_FORWARD)
            {
                // If this link was the first one, and there is a next link, the first link in the list will be the next link
                m_uFirst = uNext;
            }

            pElementToRemove->~T();
            m_linkAllocator.Deallocate(pLinkToRemove);
            m_elementAllocator.Deallocate(pElementToRemove);
        }

        return QList::QListIterator(this, uNext);
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the list.
    /// </summary>
    /// <remarks>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="uIndex">[IN] The index (zero-based) of the element to be deleted. It should be lower than the number of elements of the list; if it is not, 
    /// nothing will happen.</param>
    void Remove(const pointer_uint_q uPosition)
    {
        QE_ASSERT_WARNING(!this->IsEmpty(), "The list is empty, there is nothing to remove");
        QE_ASSERT_WARNING(!this->IsEmpty() && uPosition < this->GetCount(), "The input iterator is out of bounds");

        if(!this->IsEmpty() && uPosition < this->GetCount())
        {
            // Gets the position of the iterator
            T* pElementToRemove = &this->GetValue(uPosition);
            pointer_uint_q uIndex = pElementToRemove - (T*)m_elementAllocator.GetPointer();

            QList::QLink* pLinkBasePointer = scast_q(m_linkAllocator.GetPointer(), QList::QLink*);
            QList::QLink* pLinkToRemove = pLinkBasePointer + uIndex;

            pointer_uint_q uNext = pLinkToRemove->GetNext();
            pointer_uint_q uPrevious = pLinkToRemove->GetPrevious();
            
            if(uNext != QList::END_POSITION_FORWARD)
            {
                // If there is next link
                QList::QLink* pNextLink = pLinkBasePointer + uNext;
                pNextLink->SetPrevious(uPrevious);
            }
            else if(uPrevious != QList::END_POSITION_BACKWARD)
            {
                // If this link was the last one, and there is a previous link, the last link in the list will be the previous link
                m_uLast = uPrevious;
            }
            else
            {
                // If this link was the only one in the list the first and the last position are end positions
                m_uFirst = QList::END_POSITION_BACKWARD;
                m_uLast = QList::END_POSITION_FORWARD;
            }

            if(uPrevious != QList::END_POSITION_BACKWARD)
            {
                QList::QLink* pPreviousLink = pLinkBasePointer + uPrevious;
                pPreviousLink->SetNext(uNext);
            }
            else if(uNext != QList::END_POSITION_FORWARD)
            {
                // If this link was the first one, and there is a next link, the first link in the list will be the next link
                m_uFirst = uNext;
            }

            pElementToRemove->~T();
            m_linkAllocator.Deallocate(pLinkToRemove);
            m_elementAllocator.Deallocate(pElementToRemove);
        }
    }
    
    /// <summary>
    /// Removes all the elements of the list.
    /// </summary>
    /// <remarks>
    /// This operation will make any existing iterator or pointer invalid.<br/>
    /// The destructor of every element will be called.
    /// </remarks>
    void Clear()
    {
        if(!this->IsEmpty())
        {
            // Calls every destructor, from first to last
            for(QList::QListIterator it = this->GetFirst(); !it.IsEnd(); ++it)
                (*it).~T();

            m_uFirst = QList::END_POSITION_BACKWARD;
            m_uLast = QList::END_POSITION_FORWARD;

            m_elementAllocator.Clear();
            m_linkAllocator.Clear();
        }
    }
    
    /// <summary>
    /// Gets a range of elements from the list.
    /// </summary>
    /// <remarks>
    /// The copy constructor of each element in the range will be called, at least, once.
    /// </remarks>
    /// <param name="first">[IN] The position of the first element to be copied. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or anterior to the last element in the range.</param>
    /// <param name="last">[IN] The position of the last element to be copied. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or posterior to the first element in the range.</param>
    /// <returns>
    /// A list that contains a copy of all the elements in the given range.
    /// </returns>
    QList GetRange(const typename QList::QConstListIterator &first, const typename QList::QConstListIterator &last) const
    {
        QE_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        QE_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        QE_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        QE_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        QE_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        QList resultList;

        QList::QConstListIterator itEnd = last;
        ++itEnd;

        for(QList::QConstListIterator it = first; it != itEnd; ++it)
            resultList.Add(*it);

        return resultList;
    }
    
    /// <summary>
    /// Gets a range of elements from the list.
    /// </summary>
    /// <remarks>
    /// The copy constructor of each element in the range will be called, at least, once.
    /// </remarks>
    /// <param name="uFirst">[IN] The position index (zero-based) of the first element to be copied. It must be lower than the number of elements of the list.
    /// It must be equal or lower than the last element's index in the range.</param>
    /// <param name="uLast">[IN] The position index (zero-based) of the last element to be copied. It must be lower than the number of elements of the list.
    /// It must be equal or greater than the first element's index in the range.</param>
    /// <returns>
    /// An list that contains a copy of all the elements in the given range.
    /// </returns>
    QList GetRange(const pointer_uint_q uFirst, const pointer_uint_q uLast) const
    {
        QE_ASSERT_ERROR(uFirst <= uLast, "The first element must be prior to the last element in the range.");
        QE_ASSERT_ERROR(uFirst < this->GetCount(), "The first position is out of bounds.");
        QE_ASSERT_ERROR(uLast < this->GetCount(), "The last position is out of bounds.");
        
        const pointer_uint_q ELEMENTS_TO_GET_COUNT = uLast - uFirst + 1U;

        QList resultList(ELEMENTS_TO_GET_COUNT);

        QList::QConstListIterator it = this->GetIterator(uFirst);

        for(pointer_uint_q i = 0; i < ELEMENTS_TO_GET_COUNT; ++it, ++i)
            resultList.Add(*it);

        return resultList;
    }
    
    /// <summary>
    /// Swaps two elements of the list.
    /// </summary>
    /// <remarks>
    /// The list must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="uElementA">[IN] The index (zero-based) of an element. It must be lower than the number of elements of the list.</param>
    /// <param name="uElementB">[IN] The index (zero-based) of the other element. It must be lower than the number of elements of the list.</param>
    void Swap(const pointer_uint_q uElementA, const pointer_uint_q uElementB)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

        QE_ASSERT_ERROR(uElementA < this->GetCount(), "The first index is out of bounds.");
        QE_ASSERT_ERROR(uElementB < this->GetCount(), "The last index is out of bounds.");
        QE_ASSERT_WARNING(uElementA != uElementB, "Both elements are the same.");
        
        T* pElementA = &this->GetValue(uElementA);
        T* pElementB = &this->GetValue(uElementB);

        u8_q arBytes[sizeof(T)];
        memcpy(arBytes,   pElementA, sizeof(T));
        memcpy(pElementA, pElementB, sizeof(T));
        memcpy(pElementB, arBytes,   sizeof(T));
    }
    
    /// <summary>
    /// Swaps two elements of the list.
    /// </summary>
    /// <remarks>
    /// The list must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="elementA">[IN] The position of an element. It must not be an end position.</param>
    /// <param name="elementB">[IN] The position of the other element. It must not be an end position.</param>
    void Swap(const typename QList::QListIterator elementA, const typename QList::QListIterator elementB)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

        QE_ASSERT_ERROR(!elementA.IsEnd(), "The element A position is an end position.");
        QE_ASSERT_ERROR(!elementB.IsEnd(), "The element B position is an end position.");
        QE_ASSERT_ERROR(elementA.IsValid(), "The element A's position is not valid.");
        QE_ASSERT_ERROR(elementB.IsValid(), "The element B's position is not valid.");
        QE_ASSERT_WARNING(elementA != elementB, "Both elements are the same.");
        
        T* pElementA = &*elementA;
        T* pElementB = &*elementB;

        u8_q arBytes[sizeof(T)];
        memcpy(arBytes,   pElementA, sizeof(T));
        memcpy(pElementA, pElementB, sizeof(T));
        memcpy(pElementB, arBytes,   sizeof(T));
    }
    
    /// <summary>
    /// Checks if any of the elements in the list is equal to a given one.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to be searched through the list.</param>
    /// <returns>
    /// True if the element is found; False otherwise.
    /// </returns>
    bool Contains(const T &element) const
    {
        bool bElementFound = false;
        QList::QConstListIterator itElement = this->GetFirst();

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = m_comparator.Compare(*itElement, element) == 0;
            ++itElement;
        }

        return bElementFound;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one and obtains its position index.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <returns>
    /// The position index (zero-based) of the first element that is equal to the input one. If the element is not found,
    /// the ELEMENT_NOT_FOUND constant will be returned.
    /// </returns>
    pointer_uint_q IndexOf(const T &element) const
    {
        bool bElementFound = false;
        QList::QConstListIterator itElement = this->GetFirst();
        pointer_uint_q uIndex = 0;

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = m_comparator.Compare(*itElement, element) == 0;
            ++itElement;
            ++uIndex;
        }

        return bElementFound ? uIndex - 1U : QList::ELEMENT_NOT_FOUND;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one, starting from a concrete position, and obtains its position index.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <param name="uStartIndex">[IN] The start position to search from. It must be lower than the number of elements in the list.</param>
    /// <returns>
    /// The position index (zero-based) of the first element that is equal to the input one. If the element is not found,
    /// the ELEMENT_NOT_FOUND constant will be returned.
    /// </returns>
    pointer_uint_q IndexOf(const T &element, const pointer_uint_q uStartIndex) const
    {
        QE_ASSERT_WARNING(uStartIndex < this->GetCount(), "The input start index must be lower than the number of elements in the list.");

        bool bElementFound = false;
        QList::QConstListIterator itElement = this->GetIterator(uStartIndex);
        pointer_uint_q uIndex = uStartIndex;

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = m_comparator.Compare(*itElement, element) == 0;
            ++itElement;
            ++uIndex;
        }

        return bElementFound ? uIndex - 1U : QList::ELEMENT_NOT_FOUND;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one and obtains its position.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <returns>
    /// The position of the first element that is equal to the input one. If the element is not found,
    /// the iterator will point to the forward end position.
    /// </returns>
    QListIterator PositionOf(const T &element) const
    {
        bool bElementFound = false;
        QList::QListIterator itElement = this->GetFirst();

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = m_comparator.Compare(*itElement, element) == 0;
            ++itElement;
        }

        return bElementFound ? --itElement : itElement;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one, starting from a concrete position, and obtains its position.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <param name="startPosition">[IN] The start position to search from. It must not point to an end position.</param>
    /// <returns>
    /// The position of the first element that is equal to the input one. If the element is not found,
    /// the iterator will point to the forward end position.
    /// </returns>
    QListIterator PositionOf(const T &element, const typename QList::QConstListIterator &startPosition) const
    {
        QE_ASSERT_WARNING(!startPosition.IsEnd(), "The input start position must not point to an end position.");
        QE_ASSERT_ERROR(startPosition.IsValid(), "The input start position is not valid.");

        bool bElementFound = false;
        QList::QListIterator itElement = QList::QListIterator(this, &*startPosition - scast_q(m_elementAllocator.GetPointer(), T*));
        pointer_uint_q uIndex = 0;

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = m_comparator.Compare(*itElement, element) == 0;
            ++itElement;
            ++uIndex;
        }

        return bElementFound ? --itElement : itElement;
    }
    
    /// <summary>
    /// Copies a range of elements from another list to the end of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same list is safe only if no reallocation is necessary.<br/>
    /// The first and the last element of the range must belong to the same list.<br/>
    /// The copy constructor of each element will be called.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    void AddRange(const typename QList::QConstListIterator &first, const typename QList::QConstListIterator &last)
    {
        QE_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        QE_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        QE_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        QE_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        QE_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        // Copies each element in the input range
        QList::QConstListIterator it = first;

        for(; it != last; ++it)
            this->Add(*it);

        this->Add(*it);
    }

    /// <summary>
    /// Copies a range of elements from another list to a concrete position of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same list is safe only if no reallocation is necessary.<br/>
    /// The first and the last element of the range must belong to the same list.<br/>
    /// The copy constructor of each element will be called.<br/>
    /// Use AddRange method to insert elements at the end.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    /// <param name="uIndex">[IN] The index (zero-based) where the range of elements will be placed. It should be lower than the number of elements of the list; if it is not, 
    /// the element will be inserted at the end by default.</param>
    void InsertRange(const typename QList::QConstListIterator &first, const typename QList::QConstListIterator &last, const pointer_uint_q uIndex)
    {
        QE_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        QE_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        QE_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        QE_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        QE_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");
        QE_ASSERT_WARNING(uIndex < this->GetCount(), "The index is out of bounds.");

        // Copies each element in the input range
        QList::QConstListIterator it = last;

        for(; it != first; --it)
            this->Insert(*it, uIndex);

        this->Insert(*it, uIndex);
    }
    
    /// <summary>
    /// Copies a range of elements from another list to a concrete position of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same list is safe only if no reallocation is necessary.<br/>
    /// The first and the last element of the range must belong to the same list.<br/>
    /// The copy constructor of each element will be called.<br/>
    /// Use AddRange method to insert elements at the end.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    /// <param name="position">[IN] The position where the range of elements will be placed. It should not be an end position; if it is, 
    /// the range will be inserted at the end by default. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// list; otherwise, the behavior is undefined.</param>
    void InsertRange(const typename QList::QConstListIterator &first, const typename QList::QConstListIterator &last, const typename QList::QListIterator &position)
    {
        QE_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        QE_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        QE_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        QE_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        QE_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");
        QE_ASSERT_WARNING(!position.IsEnd(), "The insertion position should not point to an end position.");
        QE_ASSERT_ERROR(position.IsValid(), "The input iterator that points to the insertion position is not valid.");
        
        // Copies each element in the input range
        QList::QConstListIterator it = first;

        for(; it != last; ++it)
            this->Insert(*it, position);

        this->Insert(*it, position);
    }
    
    /// <summary>
    /// Deletes a range of elements placed at a concrete position in the list.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called.
    /// </remarks>
    /// <param name="first">[IN] The position of the first element to be deleted. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or anterior to the last element in the range.</param>
    /// <param name="last">[IN] The position of the last element to be deleted. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or posterior to the first element in the range.</param>
    void RemoveRange(const typename QList::QListIterator &first, const typename QList::QListIterator &last)
    {
        QE_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        QE_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        QE_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        QE_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        QE_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        QList::QListIterator it = first;
        QList::QListIterator itNext = first;

        while(it != last)
        {
            itNext = it;
            ++itNext;
            this->Remove(it);
            it = itNext;
        }

        this->Remove(it);
    }
    
    /// <summary>
    /// Deletes a range of elements placed at a concrete position in the list.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called.
    /// </remarks>
    /// <param name="uFirst">[IN] The position index (zero-based) of the first element to be deleted. It must be equal or lower than the last element's index in the range. 
    /// It must be lower than the number of elements of the list.</param>
    /// <param name="uLast">[IN] The position index (zero-based) of the last element to be deleted. It must be equal or greater than the first element's index in the range.
    /// It must be lower than the number of elements of the list.</param>
    void RemoveRange(const pointer_uint_q uFirst, const pointer_uint_q uLast)
    {
        QList::QListIterator it = this->GetIterator(uFirst);
        const QList::QListIterator LAST = this->GetIterator(uLast);
        QList::QListIterator itNext = it;

        while(it != LAST)
        {
            itNext = it;
            ++itNext;
            this->Remove(it);
            it = itNext;
        }

        this->Remove(it);
    }
    
    
private:

    /// <summary>
    /// Increases the capacity of the list, reserving memory for more elements than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void _ReallocateByFactor(const pointer_uint_q uNumberOfElements)
    {
        const pointer_uint_q FINAL_CAPACITY = scast_q(scast_q(uNumberOfElements, float) * QList::REALLOCATION_FACTOR, pointer_uint_q);
        this->Reserve(FINAL_CAPACITY);
    }


    // PROPERTIES
    // ---------------

public:

    /// <summary>
    /// Returns a constant pointer to the element allocator.
    /// </summary>
    /// <returns>
    /// Constant pointer to the element allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return &m_elementAllocator;
    }

    /// <summary>
    /// Returns the number of elements in the list.
    /// </summary>
    /// <returns>
    /// The number of elements in the list.
    /// </returns>
    pointer_uint_q GetCount() const
    {
        return m_elementAllocator.GetAllocatedBytes() / sizeof(T);
    }

    /// <summary>
    /// Returns the number of elements that can be stored in the list without a reallocation.
    /// </summary>
    /// <returns>
    /// The number of elements that can be stored in the list without a reallocation.
    /// </returns>
    pointer_uint_q GetCapacity() const
    {
        return m_elementAllocator.GetPoolSize() / sizeof(T);
    }

    /// <summary>
    /// Checks whether the list is empty or not.
    /// </summary>
    /// <returns>
    /// True if the list is empty.
    /// </returns>
    bool IsEmpty() const
    {
        return (GetCount() == 0);
    }

    // ATTRIBUTES
    // ---------------

protected:

    /// <summary>
    /// The comparator used to compare elements.
    /// </summary>
    ComparatorT m_comparator;

    /// <summary>
    /// Index of the first element in the sequence. If there is no first element, its value is END_POSITION_BACKWARD constant.
    /// </summary>
    pointer_uint_q m_uFirst;

       /// <summary>
    /// Index of the last element in the sequence. If there is no last element, its value is END_POSITION_FORWARD constant.
    /// </summary>
    pointer_uint_q m_uLast;

    /// <summary>
    /// The allocator which stores the list elements.
    /// </summary>
    AllocatorT m_elementAllocator;

      /// <summary>
    /// The allocator which stores the double linked list for internals.
    /// </summary>
    AllocatorT m_linkAllocator;
};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template<class T, class AllocatorT, class ComparatorT>
float QList<T, AllocatorT, ComparatorT>::REALLOCATION_FACTOR = 1.5f;


} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLIST__
