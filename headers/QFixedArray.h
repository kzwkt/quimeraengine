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

#ifndef __QFIXEDARRAY__
#define __QFIXEDARRAY__

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
/// Class that represents a contiguous sequence of elements that can be arbitrarly accessed using a zero-based
/// index. Its size is defined when it is constructed and cannot be changed afterwards.
/// </summary>
/// <remarks>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of every element in the array.</typeparam>
/// <typeparam name="Allocator">Optional. The type of allocator to store the elements of the array. By default, QPoolAllocator will
/// be used.</typeparam>
/// <typeparam name="Comparator">Optional. The type of comparator to compare elements to each other, used in search and ordering
/// algorithms. By default, QComparatorDefault will be used.</typeparam>
template <class T, class Allocator = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class Comparator = QComparatorDefault<T> >
class QFixedArray
{
    // TYPEDEFS
	// --------------
protected:

    typedef QFixedArray<T, Allocator, Comparator> TFixedArray;


    // INTERNAL CLASSES
	// -----------------
public:

    /// <summary>
    /// Iterator that steps once per element of an array.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to an array, it cannot point to another array ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the array.<br/>
    /// The position before the first character or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QArrayIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the array to iterate and the position to point to.
        /// </summary>
        /// <remarks>
        /// If array is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pArray">[IN] The array to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. It must be lower than the number of elements in the array.</param>
        QArrayIterator(const QFixedArray* pArray, const unsigned int uPosition) : m_pArray(pArray), m_uPosition(uPosition)
        {
            QE_ASSERT(pArray != null_q, "Invalid argument: The pointer to the array cannot be null");
            QE_ASSERT(pArray->GetCount() > uPosition, "Invalid argument: The position must be lower than the number of elements in the array");

            if(pArray == null_q || pArray->GetCount() <= uPosition)
                m_uPosition = QFixedArray::END_POSITION_FORWARD;
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same array as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QArrayIterator& operator=(const QArrayIterator &iterator)
        {
            QE_ASSERT(m_pArray == iterator.m_pArray, "The input iterator points to a different array");

            if(m_pArray == iterator.m_pArray)
                m_uPosition = iterator.m_uPosition;

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the array element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the array element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T& operator*() const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the array element");

            QE_ASSERT(m_uPosition != QFixedArray::END_POSITION_FORWARD && m_uPosition != QFixedArray::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the array element");

            return *(((T*)m_pArray->m_pAllocator->GetPointer()) + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the array element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the array element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T* operator->() const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the array element");

            QE_ASSERT(m_uPosition != QFixedArray::END_POSITION_FORWARD && m_uPosition != QFixedArray::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the array element");

            return ((T*)m_pArray->m_pAllocator->GetPointer()) + m_uPosition;
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
        QArrayIterator operator++(int)
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT(m_uPosition != QFixedArray::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QArrayIterator iteratorCopy = *this;

            if(m_uPosition == m_pArray->m_uLast)
                m_uPosition = QFixedArray::END_POSITION_FORWARD;
            else if(m_uPosition == QFixedArray::END_POSITION_BACKWARD)
                m_uPosition = m_pArray->m_uFirst;
            else if(m_uPosition != QFixedArray::END_POSITION_FORWARD)
                ++m_uPosition;

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
        QArrayIterator operator--(int)
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT(m_uPosition != QFixedArray::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QArrayIterator iteratorCopy = *this;

            if(m_uPosition == m_pArray->m_uFirst)
                m_uPosition = QFixedArray::END_POSITION_BACKWARD;
            else if(m_uPosition == QFixedArray::END_POSITION_FORWARD)
                m_uPosition = m_pArray->m_uLast;
            else if(m_uPosition != QFixedArray::END_POSITION_BACKWARD)
                --m_uPosition;

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
        QArrayIterator& operator++()
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT(m_uPosition != QFixedArray::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition == m_pArray->m_uLast)
                m_uPosition = QFixedArray::END_POSITION_FORWARD;
            else if(m_uPosition == QFixedArray::END_POSITION_BACKWARD)
                m_uPosition = m_pArray->m_uFirst;
            else if(m_uPosition != QFixedArray::END_POSITION_FORWARD)
                ++m_uPosition;

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
        QArrayIterator& operator--()
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT(m_uPosition != QFixedArray::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition == m_pArray->m_uFirst)
                m_uPosition = QFixedArray::END_POSITION_BACKWARD;
            else if(m_uPosition == QFixedArray::END_POSITION_FORWARD)
                m_uPosition = m_pArray->m_uLast;
            else if(m_uPosition != QFixedArray::END_POSITION_BACKWARD)
                --m_uPosition;

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same array to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same array; False otherwise.
        /// </returns>
        bool operator==(const QArrayIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return m_uPosition == iterator.m_uPosition && m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different array is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different array; False otherwise.
        /// </returns>
        bool operator!=(const QArrayIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return m_uPosition != iterator.m_uPosition || m_pArray != iterator.m_pArray;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const QArrayIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition == QFixedArray::END_POSITION_FORWARD  && iterator.m_uPosition != QFixedArray::END_POSITION_FORWARD)  ||
                    (m_uPosition != QFixedArray::END_POSITION_BACKWARD && iterator.m_uPosition == QFixedArray::END_POSITION_BACKWARD) ||
                    m_uPosition > iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const QArrayIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition != QFixedArray::END_POSITION_FORWARD  && iterator.m_uPosition == QFixedArray::END_POSITION_FORWARD)  ||
                    (m_uPosition == QFixedArray::END_POSITION_BACKWARD && iterator.m_uPosition != QFixedArray::END_POSITION_BACKWARD) ||
                    m_uPosition < iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const QArrayIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition == QFixedArray::END_POSITION_FORWARD  && iterator.m_uPosition != QFixedArray::END_POSITION_FORWARD)  ||
                    (m_uPosition != QFixedArray::END_POSITION_BACKWARD && iterator.m_uPosition == QFixedArray::END_POSITION_BACKWARD) ||
                    m_uPosition >= iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const QArrayIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition != QFixedArray::END_POSITION_FORWARD  && iterator.m_uPosition == QFixedArray::END_POSITION_FORWARD)  ||
                    (m_uPosition == QFixedArray::END_POSITION_BACKWARD && iterator.m_uPosition != QFixedArray::END_POSITION_BACKWARD) ||
                    m_uPosition <= iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the array.
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
            return m_uPosition == QFixedArray::END_POSITION_BACKWARD || m_uPosition == QFixedArray::END_POSITION_FORWARD;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the array, distinguishing which of them.
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
            return (eIterationDirection == EQIterationDirection::E_Backward && m_uPosition == QFixedArray::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EQIterationDirection::E_Forward  && m_uPosition == QFixedArray::END_POSITION_FORWARD);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the array is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            m_uPosition = m_pArray->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the array is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            m_uPosition = m_pArray->m_uLast;
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (an array may have been shortened while the iterator
        /// was pointing to its last position). If the array to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_pArray != null_q && ((m_uPosition >= m_pArray->m_uFirst && m_uPosition <= m_pArray->m_uLast) ||
                                          m_uPosition == QFixedArray::END_POSITION_BACKWARD ||
                                          m_uPosition == QFixedArray::END_POSITION_FORWARD);
        }


        // ATTRIBUTES
	    // ---------------
    private:

        /// <summary>
        /// The array the iterator points to.
        /// </summary>
        const TFixedArray* m_pArray;

        /// <summary>
        /// The current iteration position regarding the first element. It is zero-based.
        /// </summary>
        pointer_uint_q m_uPosition;

    }; // QArrayIterator


   	// CONSTANTS
	// ---------------
protected:

	/// <summary>
	/// Constant to symbolize the end of the sequence near the last element.
	/// </summary>
    static const pointer_uint_q END_POSITION_FORWARD = -1;

	/// <summary>
	/// Constant to symbolize the end of the sequence near the first element.
	/// </summary>
    static const pointer_uint_q END_POSITION_BACKWARD = -2;


	// CONSTRUCTORS
	// ---------------

public:

	/// <summary>
	/// Constructs a fixed array passing the number of elements to store and their initial value.
	/// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the array.
    /// </remarks>
    /// <param name="uCount"> [IN] Number of elements to store. It must be greater than zero.</param>
    /// <param name="initialValue"> [IN] The initial value to assign to all array elements.</param>
    QFixedArray(const pointer_uint_q uCount, const T &initialValue) :
            m_uFirst(0),
            m_uLast(uCount - 1)
    {
        QE_ASSERT( uCount > 0, "Zero elements array is not allowed." );
        QE_ASSERT( this->MultiplicationOverflows(uCount, sizeof(T)) == false, "The amount of memory requested overflows." );

        m_pAllocator = new Allocator(uCount * sizeof(T), sizeof(T), QAlignment(alignof_q(T)));

        for(pointer_uint_q uIndex = 0; uIndex < uCount; uIndex++)
        {
            // Allocates and writes in the returned buffer the initial value
            new(m_pAllocator->Allocate()) T(initialValue);
        }
    }

    /// <summary>
	/// Copy constructor. Creates a fixed array from another.
	/// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the array.
    /// </remarks>
    /// <param name="fixedArray"> [IN] Fixed array from which to copy.</param>
    QFixedArray(const QFixedArray &fixedArray) :
            m_uFirst(fixedArray.m_uFirst),
            m_uLast(fixedArray.m_uLast)
    {
        m_pAllocator = new Allocator(fixedArray.GetCount() * sizeof(T), sizeof(T), QAlignment(alignof_q(T)));

        for(pointer_uint_q uIndex = 0; uIndex < fixedArray.m_uLast + 1; uIndex++)
        {
            // Constructs a T object over the buffer returned by the allocator and initializes it with
            // the value of the origin element in the corresponding array position.
            new(m_pAllocator->Allocate()) T(fixedArray[uIndex]);
        }
    }

protected:

	/// <summary>
	/// Constructs an empty and invalid fixed array. It's responsability of the derived classes to initialize it properly.
	/// </summary>
	QFixedArray() :
        m_uFirst(END_POSITION_BACKWARD),
        m_uLast(END_POSITION_FORWARD),
        m_pAllocator(null_q)
    {
    }

    // DESTRUCTOR
	// ---------------
public:
	/// <summary>
	/// Destructor.
	/// </summary>
    /// <remarks>
    /// The destructor is called for every element of the array.
    /// </remarks>
	~QFixedArray()
    {
        QE_ASSERT( null_q != m_pAllocator, "Allocator is null" );

        for(pointer_uint_q uIndex = 0; uIndex < this->GetCount(); uIndex++)
            this->GetValue(uIndex).~T();

        delete m_pAllocator;
    }


	// METHODS
	// ---------------
public:
  	/// <summary>
	/// Defines the assignment operator which makes a copy of the passed fixed array.
	/// </summary>
    /// <remarks>
    /// If the size of the destination array is less than the size of the origin array, it will copy
    /// only the first elements that fit in the destination array. The exceeding elements are not copied and
    /// the size of the destination array does not change.
    /// If the size of the destination array is greater than the size of the origin array, the remaining
    /// elements in the destination array does not change.
    /// Assignment operator will be called for every element of the array.
    /// </remarks>
    /// <param name="fixedArray"> [IN] Fixed array from which to copy.</param>
    /// <returns>
    /// A reference to the resulting fixed array.
    /// </returns>
    QFixedArray<T, Allocator, Comparator>& operator= (const QFixedArray<T, Allocator, Comparator> &fixedArray)
    {
        pointer_uint_q uElementsToCopy;

        if(m_uLast > fixedArray.m_uLast)
            uElementsToCopy = fixedArray.GetCount();
        else
            uElementsToCopy = this->GetCount();

        for(pointer_uint_q uIndex = 0; uIndex < uElementsToCopy; uIndex++)
        {
            // Destination array element value = Origin array element value, using pointers arithmetic
            this->SetValue(uIndex, fixedArray.GetValue(uIndex));
        }

        return *this;
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position.
    /// </summary>
    /// <param name="uIndex"> [IN] Position of the element to access. It must be less than the array's size.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& operator[] (const pointer_uint_q uIndex) const
    {
        return this->GetValue(uIndex);
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position.
    /// </summary>
    /// <param name="uIndex"> [IN] Position of the element to access. It must be less than the array's size.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& GetValue(const pointer_uint_q uIndex) const
    {
        QE_ASSERT( uIndex < this->GetCount(), "Index must be less than the array's size" );
        return *((T*)m_pAllocator->GetPointer() + uIndex);
    }

    /// <summary>
    /// Performs a fast shallow copy of the array elements.
    /// </summary>
    /// <param name="destinationArray"> [IN/OUT] Destination array where to copy the array elements. The capacity of the two arrays has to be equal.</param>
    void Clone(QFixedArray &destinationArray) const
    {
        QE_ASSERT( destinationArray.GetCapacity() == this->GetCapacity(), "The capacity of the two arrays has to be equal" );
        m_pAllocator->CopyTo(*destinationArray.m_pAllocator);
    }

    /// <summary>
    /// Copies the passed value in the passed position of the array.
    /// </summary>
    /// <remarks>
    /// The assignment operator will be called for the element that is currently occupying that position.
    /// </remarks>
    /// <param name="uIndex"> [IN] Position in the array where to copy the value. It must be less than the array's size.</param>
    /// <param name="value"> [IN] Value to copy in the array.</param>
    void SetValue(const pointer_uint_q uIndex, const T& value)
    {
        QE_ASSERT( uIndex < this->GetCount(), "Index must be less than the array's size" );
        *((T*)m_pAllocator->GetPointer() + uIndex) = value;
    }

    /// <summary>
    /// Method that returns the element placed in the position given by the parameter.
    /// </summary>
    /// <remarks>
    /// If the index is out of bounds the returned iterator will point to the end position.
    /// </remarks>
    /// <returns>
    /// An iterator that points to the position of the element which occupies the position N.
    /// </returns>
    QArrayIterator GetIterator(const pointer_uint_q uIndex) const 
    {
        if (uIndex >= this->GetCount())
        {
            QE_ASSERT( uIndex <= this->GetCount(), "Index must be less than the array's size" );
            return QArrayIterator(this, END_POSITION_FORWARD);
        }
        return QArrayIterator(this, uIndex);
    }

    /// <summary>
    /// Method that returns the first element in the array.
    /// </summary>
    /// <remarks>
    /// If the array is empty the returned iterator will point to an invalid position.
    /// </remarks>
    /// <returns>
    /// An iterator that points to the first element.
    /// </returns>
    QArrayIterator GetFirst() const
    {
        const pointer_uint_q FIRST_INDEX = 0;
        if (this->IsEmpty())
        {
            QE_ASSERT( this->GetCount() != 0, "Array cannot be empty!" );
            return QArrayIterator(this, END_POSITION_BACKWARD);
        }
        return QArrayIterator(this, FIRST_INDEX);
        
    }

    /// <summary>
    /// Method that returns the last element in the array.
    /// </summary>
    /// <remarks>
    /// If the array is empty the returned iterator will point to an invalid position.
    /// </remarks>
    /// <returns>
    /// An iterator that points to the last element.
    /// </returns>
    QArrayIterator GetLast() const
    {
        if (this->IsEmpty())
        {
            QE_ASSERT( this->GetCount() != 0, "Array cannot be empty!" );
            return QArrayIterator(this, END_POSITION_FORWARD);
        }
        const pointer_uint_q LAST_INDEX = this->GetCount() - 1;
        return QArrayIterator(this, LAST_INDEX);
    }

private:

    /// <summary>
    /// Checks if the multiplication of two operands overflows for the pointer_uint_q type.
    /// </summary>
    /// <param name="uOperandA"> [IN] Operand to multiply.</param>
    /// <param name="uOperandB"> [IN] Operand to multiply.</param>
    /// <returns>
    /// True if the result overflows for the pointer_uint_q type.
    /// </returns>
    bool MultiplicationOverflows(pointer_uint_q uOperandA, pointer_uint_q uOperandB) const
    {
        return this->HighestOneBitPosition(uOperandA) + this->HighestOneBitPosition(uOperandB) > sizeof(pointer_uint_q) * 8;
    }

    /// <summary>
    /// Gets the highest one bit position of a number converted to binary format.
    /// </summary>
    /// <param name="uValue"> [IN] Number to trate.</param>
    /// <returns>
    /// The highest one bit position of the number passed by parameter.
    /// </returns>
    pointer_uint_q HighestOneBitPosition(pointer_uint_q uValue) const
    {
        pointer_uint_q position = 0;

        while(uValue != 0)
        {
            ++position;
            uValue >>= 1;
        }

        return position;
    }


    // PROPERTIES
	// ---------------
public:
   	/// <summary>
	/// Returns a constant pointer to the allocator.
	/// </summary>
    /// <returns>
    /// Constant pointer to the allocator.
    /// </returns>
    const Allocator* GetAllocator() const
    {
        return m_pAllocator;
    }

    /// <summary>
    /// Returns the number of elements in the array.
    /// </summary>
    /// <returns>
    /// The number of elements in the array.
    /// </returns>
    pointer_uint_q GetCount() const
    {
        return m_pAllocator->GetAllocatedBytes() / sizeof(T);
    }

    /// <summary>
    /// Returns the number of elements that can be stored in the array without a reallocation.
    /// </summary>
    /// <returns>
    /// The number of elements that can be stored in the array without a reallocation.
    /// </returns>
    pointer_uint_q GetCapacity() const
    {
        return m_pAllocator->GetPoolSize() / sizeof(T);
    }

    /// <summary>
    /// Checks whether the array is empty or not.
    /// </summary>
    /// <returns>
    /// True if the array is empty.
    /// </returns>
    bool IsEmpty() const
    {
        return (this->GetCount() == 0);
    }

    // ATTRIBUTES
	// ---------------

protected:

	/// <summary>
	/// Pointer to the allocator which stores the array elements.
	/// </summary>
    Allocator* m_pAllocator;

    /// <summary>
	/// The Comparator.
	/// </summary>
    Comparator m_comparator;

    /// <summary>
	/// Index of the first element in the sequence. If the index points to an invalid position its value is the
    /// END_POSITION_BACKWARD constant.
	/// </summary>
    pointer_uint_q m_uFirst;

   	/// <summary>
	/// Index of the last element in the sequence. If the index points to an invalid position its value is the
    /// END_POSITION_FORWARD constant.
	/// </summary>
    pointer_uint_q m_uLast;

};

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QFIXEDARRAY__

