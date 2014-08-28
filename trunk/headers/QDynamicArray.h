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

#ifndef __QDYNAMICARRAY__
#define __QDYNAMICARRAY__

#include "ToolsDefinitions.h"
#include "QFixedArray.h"
#include <cstring>


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Represents a set of elements distributed sequentially as a one-dimensional vector whose length can change if necessary. Every position of 
/// the array can be accessed directly.
/// </summary>
/// <remarks>
/// Elements are assured to be placed contiguously in memory.<br/>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of every element in the array.</typeparam>
/// <typeparam name="AllocatorT">Optional. The type of allocator to store the elements of the array. By default, QPoolAllocator will
/// be used.</typeparam>
/// <typeparam name="ComparatorT">Optional. The type of comparator to compare elements to each other, used in search and ordering
/// algorithms. By default, QComparatorDefault will be used.</typeparam>
template<class T, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class ComparatorT = QComparatorDefault<T> >
class QDynamicArray : public QFixedArray<T, AllocatorT, ComparatorT>
{
    using QFixedArray<T, AllocatorT, ComparatorT>::m_allocator;
    using QFixedArray<T, AllocatorT, ComparatorT>::m_uFirst;
    using QFixedArray<T, AllocatorT, ComparatorT>::m_uLast;
    

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
    /// Default constructor.
    /// </summary>
    /// <remarks>
    /// The initial capacity depends on the value of the default initial capacity of the class.
    /// </remarks>
    QDynamicArray()
    {
        if(sm_uDefaultCapacity > QFixedArray<T, AllocatorT, ComparatorT>::DEFAULT_CAPACITY)
            this->Reserve(sm_uDefaultCapacity);
    }

    /// <summary>
    /// Constructor that receives the initial capacity.
    /// </summary>
    /// <param name="uInitialCapacity">[IN] The number of elements for which to reserve memory, the initial capacity. If it equals zero, the 
    /// default capacity will be used instead.</param>
    explicit QDynamicArray(const pointer_uint_q uInitialCapacity)
    {
        QE_ASSERT(uInitialCapacity > 0, "The initial capacity cannot be zero, it must be, at least, one.");

        pointer_uint_q uCapacity = uInitialCapacity;

        if(uInitialCapacity == 0)
            uCapacity = sm_uDefaultCapacity;

        if(uCapacity > QFixedArray<T, AllocatorT, ComparatorT>::DEFAULT_CAPACITY)
            this->Reserve(uCapacity);
    }
    
    /// <summary>
    /// Copy constructor that receives a fixed array.
    /// </summary>
    /// <remarks>
    /// The copy constructor of every new element is called, from first to last.<br/>
    /// The capacity of the resultant array will be just the necessary to store the amount of elements of the input array.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    QDynamicArray(const QFixedArray<T, AllocatorT, ComparatorT> &arInputArray)
    {
        const pointer_uint_q INPUT_COUNT = arInputArray.GetCount();

        // The array is expanded to store the exceeding elements
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        m_uLast = INPUT_COUNT - 1U;// Fixed arrays are supposed not to be empty
        m_uFirst = 0; // Fixed arrays are supposed to start at 0

        // Copies every element
        for(pointer_uint_q uIndex = 0; uIndex < m_uLast + 1U; ++uIndex) // Fixed arrays are supposed not to be empty
            new(m_allocator.Allocate()) T(arInputArray[uIndex]);
    }

    /// <summary>
    /// Copy constructor that receives dynamic array.
    /// </summary>
    /// <remarks>
    /// The copy constructor of every new element is called, from first to last.<br/>
    /// The capacity of the resultant array will be just the necessary to store the amount of elements of the input array.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    QDynamicArray(const QDynamicArray<T, AllocatorT, ComparatorT> &arInputArray)
    {
        const pointer_uint_q INPUT_COUNT = arInputArray.GetCount();

        // The array is expanded to store the exceeding elements
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        m_uLast = arInputArray.m_uLast;
        m_uFirst = arInputArray.m_uFirst;

        // Copies every element, if input array is not empty
        if(m_uLast != QFixedArray<T, AllocatorT, ComparatorT>::END_POSITION_FORWARD)
            for(pointer_uint_q uIndex = 0; uIndex < m_uLast + 1U; ++uIndex)
                new(m_allocator.Allocate()) T(arInputArray[uIndex]);
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignment operator that copies a fixed array.
    /// </summary>
    /// <remarks>
    /// If the input array has less elements than the resident array, the destructor of the last elements (the difference) 
    /// will be called.<br/>
    /// If the input array has more elements than the resident array, the copy constructor of the new elements (the difference)
    /// will be called.<br/>
    /// When copying an element of a position that already exists in the resident array, the assignment operator of that 
    /// element will be called.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    /// <returns>
    /// A reference to the resultant dynamic array.
    /// </returns>
    QDynamicArray& operator=(const QFixedArray<T, AllocatorT, ComparatorT> &arInputArray)
    {
        const pointer_uint_q INPUT_COUNT = arInputArray.GetCount();
        const pointer_uint_q RESIDENT_COUNT = this->GetCount();

        // The array is expanded to store the exceeding elements, if necessary
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        // Destroys exceeding elements of the resident array
        if(INPUT_COUNT < RESIDENT_COUNT)
        {   // [TODO] Thund: Replace this block with Remove
            T* pElement = &this->GetValue(INPUT_COUNT);

            for(pointer_uint_q uIndex = INPUT_COUNT; uIndex < RESIDENT_COUNT; ++uIndex)
            {
                pElement->~T();
                m_allocator.Deallocate(pElement);
                ++pElement;
            }
        }

        // Assigns every existing element
        const pointer_uint_q ELEMENTS_TO_ASSIGN = std::min(INPUT_COUNT, RESIDENT_COUNT);
        for(pointer_uint_q uIndex = 0; uIndex < ELEMENTS_TO_ASSIGN; ++uIndex)
            this->GetValue(uIndex) = arInputArray[uIndex];

        // Copies new elements
        if(INPUT_COUNT > RESIDENT_COUNT)
            for(pointer_uint_q uIndex = RESIDENT_COUNT; uIndex < INPUT_COUNT; ++uIndex)
                new(m_allocator.Allocate()) T(arInputArray[uIndex]);   // [TODO] Thund: Replace this block with Add

        m_uLast = INPUT_COUNT - 1U;
        m_uFirst = 0;

        return *this;
    }
    
    /// <summary>
    /// Assignment operator that copies a dynamic array.
    /// </summary>
    /// <remarks>
    /// If the input array has less elements than the resident array, the destructor of the last elements (the difference) 
    /// will be called.<br/>
    /// If the input array has more elements than the resident array, the copy constructor of the new elements (the difference)
    /// will be called.<br/>
    /// When copying an element of a position that already exists in the resident array, the assignment operator of that 
    /// element will be called.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    /// <returns>
    /// A reference to the resultant dynamic array.
    /// </returns>
    QDynamicArray& operator=(const QDynamicArray &arInputArray)
    {
        const pointer_uint_q INPUT_COUNT = arInputArray.GetCount();
        const pointer_uint_q RESIDENT_COUNT = this->GetCount();

        // The array is expanded to store the exceeding elements, if necessary
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        // Destroys exceeding elements of the resident array
        if(INPUT_COUNT < RESIDENT_COUNT)
        {
            T* pElement = &this->GetValue(INPUT_COUNT);

            for(pointer_uint_q uIndex = INPUT_COUNT; uIndex < RESIDENT_COUNT; ++uIndex)
            {   // [TODO] Thund: Replace this block with Remove
                pElement->~T();
                m_allocator.Deallocate(pElement);
                ++pElement;
            }
        }

        // Assigns every existing element
        const pointer_uint_q ELEMENTS_TO_ASSIGN = std::min(INPUT_COUNT, RESIDENT_COUNT);
        for(pointer_uint_q uIndex = 0; uIndex < ELEMENTS_TO_ASSIGN; ++uIndex)
            this->GetValue(uIndex) = arInputArray[uIndex];

        // Copies new elements
        if(INPUT_COUNT > RESIDENT_COUNT)
            for(pointer_uint_q uIndex = RESIDENT_COUNT; uIndex < INPUT_COUNT; ++uIndex)
                new(m_allocator.Allocate()) T(arInputArray[uIndex]);   // [TODO] Thund: Replace this block with Add

        m_uLast = arInputArray.m_uLast;
        m_uFirst = arInputArray.m_uFirst;

        return *this;
    }

    /// <summary>
    /// Increases the capacity of the array, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means:<br/>
    /// - Iterators pointing to elements of this array may become invalid.<br/>
    /// - Any pointer to elements of this array will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const pointer_uint_q uNumberOfElements)
    {
        if(uNumberOfElements > this->GetCapacity())
            m_allocator.Reallocate(uNumberOfElements * sizeof(T));
    }

    /// <summary>
    /// Copies an element to the end of the array.
    /// </summary>
    /// <remarks>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing iterator or pointer invalid.<br/>
    /// The copy constructor of the element will be called.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    void Add(const T &newElement)
    {
        if(this->GetCount() == this->GetCapacity())
            this->ReallocateByFactor(this->GetCapacity() + 1U);
        
        if(this->IsEmpty())
            m_uFirst = m_uLast = 0;
        else
            ++m_uLast;

        new(m_allocator.Allocate()) T(newElement);
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the array.
    /// </summary>
    /// <remarks>
    /// An insertion produces the movement of all the subsequent elements in the array one position forward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing iterator or pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="position">[IN] The position where the new element will be placed. It should not be an end position; if it is, 
    /// the element will be inserted at the end by default. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// array; otherwise, the behavior is undefined.</param>
    void Insert(const T &newElement, const typename QFixedArray<T, AllocatorT, ComparatorT>::QArrayIterator &position)
    {
        QE_ASSERT(position.IsValid(), "The input iterator is not valid");
        QE_ASSERT(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        // Gets the position of the iterator
        pointer_uint_q uIndex = &(*position) - (T*)m_allocator.GetPointer();

        if(this->GetCount() == this->GetCapacity())
            this->ReallocateByFactor(this->GetCapacity() + 1U);

        if(this->IsEmpty())
        {
            m_uFirst = m_uLast = 0;
            new(m_allocator.Allocate()) T(newElement);
        }
        else if(uIndex > m_uLast)
        {
            ++m_uLast;
            new(m_allocator.Allocate()) T(newElement);
        }
        else
        {
            // Increases the allocated space
            ++m_uLast;
            m_allocator.Allocate();
            
            // Moves all the contiguous elements 1 position forward
            void* pBuffer = m_allocator.GetPointer();
            memcpy((void*)((T*)pBuffer + uIndex + 1U),          // The position where the next blocks are to be moved
                   (void*)((T*)pBuffer + uIndex),               // The position where the element is to be inserted
                   (m_uLast - uIndex) * sizeof(T));             // The (size of) number of blocks to move (count - index - 1)
                   
            // Calls the copy constructor using the position where the element is inserted
            new((void*)((T*)pBuffer + uIndex)) T(newElement);
        }
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the array.
    /// </summary>
    /// <remarks>
    /// An insertion produces the movement of all the subsequent elements in the array one position forward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing iterator or pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="uIndex">[IN] The index (zero-based) where the new element will be placed. It should be lower than the number of elements of the array; if it is not, 
    /// the element will be inserted at the end by default.</param>
    void Insert(const T &newElement, const pointer_uint_q uIndex)
    {
        QE_ASSERT(!this->IsEmpty() && uIndex <= m_uLast, "The input index is out of bounds");

        if(this->GetCount() == this->GetCapacity())
            this->ReallocateByFactor(this->GetCapacity() + 1U);

        if(this->IsEmpty())
        {
            m_uFirst = m_uLast = 0;
            new(m_allocator.Allocate()) T(newElement);
        }
        else if(uIndex > m_uLast)
        {
            ++m_uLast;
            new(m_allocator.Allocate()) T(newElement);
        }
        else
        {
            // Increases the allocated space
            ++m_uLast;
            m_allocator.Allocate();

            // Moves all the contiguous elements 1 position forward
            void* pBuffer = m_allocator.GetPointer();
            memcpy((void*)((T*)pBuffer + uIndex + 1U),          // The position where the next blocks are to be moved
                   (void*)((T*)pBuffer + uIndex),               // The position where the element is to be inserted
                   (m_uLast - uIndex) * sizeof(T));             // The (size of) number of blocks to move (count - index - 1)

            // Calls the copy constructor using the position where the element is inserted
            new((void*)((T*)pBuffer + uIndex)) T(newElement);
        }
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the array.
    /// </summary>
    /// <remarks>
    /// A removal produces the movement of all the subsequent elements in the array one position backward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="position">[IN] The position of the element to be deleted. It should not be an end position; if it is, 
    /// nothing will be done. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// array; otherwise, the behavior is undefined.</param>
    void Remove(const typename QFixedArray<T, AllocatorT, ComparatorT>::QArrayIterator &position)
    {
        QE_ASSERT(position.IsValid(), "The input iterator is not valid");
        QE_ASSERT(!this->IsEmpty(), "The array is empty, there is nothing to remove");
        QE_ASSERT(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        // Gets the position of the iterator
        pointer_uint_q uIndex = &(*position) - (T*)m_allocator.GetPointer();

        if(!this->IsEmpty() && uIndex <= m_uLast)
        {
            if(this->GetCount() == 1U)
            {
                // The container is emptied
                ((T*)m_allocator.GetPointer())->~T();
                m_uFirst = QFixedArray<T, AllocatorT, ComparatorT>::END_POSITION_BACKWARD;
                m_uLast = QFixedArray<T, AllocatorT, ComparatorT>::END_POSITION_FORWARD;
                m_allocator.Clear();
            }
            else
            {
                // Calls the destructor using the position where the element is removed
                void* pBuffer = m_allocator.GetPointer();
                ((T*)pBuffer + uIndex)->~T();

                // Moves all the contiguous elements 1 position backward
                memcpy((void*)((T*)pBuffer + uIndex),         // The position where the next blocks are to be moved
                       (void*)((T*)pBuffer + uIndex + 1U),    // The position where the next blocks are currently
                       (m_uLast - uIndex) * sizeof(T));       // The (size of) number of blocks to move (count - index - 1)

                // Decreases the allocated space
                m_allocator.Deallocate((void*)((T*)pBuffer + m_uLast));
                --m_uLast;
            }
        }
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the array.
    /// </summary>
    /// <remarks>
    /// A removal produces the movement of all the subsequent elements in the array one position backward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="uIndex">[IN] The index (zero-based) of the element to be deleted. It should be lower than the number of elements of the array; if it is not, 
    /// nothing will happen.</param>
    void Remove(const pointer_uint_q uIndex)
    {
        QE_ASSERT(!this->IsEmpty(), "The array is empty, there is nothing to remove");
        QE_ASSERT(!this->IsEmpty() && uIndex <= m_uLast, "The input index is out of bounds");

        if(!this->IsEmpty() && uIndex <= m_uLast)
        {
            if(this->GetCount() == 1U)
            {
                // The container is emptied
                ((T*)m_allocator.GetPointer())->~T();
                m_uFirst = QFixedArray<T, AllocatorT, ComparatorT>::END_POSITION_BACKWARD;
                m_uLast = QFixedArray<T, AllocatorT, ComparatorT>::END_POSITION_FORWARD;
                m_allocator.Clear();
            }
            else
            {
                // Calls the destructor using the position where the element is removed
                void* pBuffer = m_allocator.GetPointer();
                ((T*)pBuffer + uIndex)->~T();

                // Moves all the contiguous elements 1 position backward
                memcpy((void*)((T*)pBuffer + uIndex),         // The position where the next blocks are to be moved
                       (void*)((T*)pBuffer + uIndex + 1U),    // The position where the next blocks are currently
                       (m_uLast - uIndex) * sizeof(T));       // The (size of) number of blocks to move (count - index - 1)

                // Decreases the allocated space
                m_allocator.Deallocate((void*)((T*)pBuffer + m_uLast));
                --m_uLast;
            }
        }
    }
    
    /// <summary>
    /// Removes all the elements of the array.
    /// </summary>
    /// <remarks>
    /// This operation will make any existing iterator or pointer invalid.<br/>
    /// The destructor of every element will be called.
    /// </remarks>
    void Clear()
    {
        if(!this->IsEmpty())
        {
            void* pBuffer = m_allocator.GetPointer();

            // Calls every destructor, from first to last
            for(pointer_uint_q uIndex = m_uFirst; uIndex <= m_uLast; ++uIndex)
                ((T*)pBuffer + uIndex)->~T();

            m_uFirst = QFixedArray<T, AllocatorT, ComparatorT>::END_POSITION_BACKWARD;
            m_uLast = QFixedArray<T, AllocatorT, ComparatorT>::END_POSITION_FORWARD;

            m_allocator.Clear();
        }
    }
    
    /// <summary>
    /// Performs a shallow copy of the contents of the array to another array.
    /// </summary>
    /// <remarks>
    /// If the capacity of the destination array is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="arDestinationArray">[IN/OUT] The destination array to which the contents will be copied.</param>
    void Clone(QDynamicArray &arDestinationArray) const
    {
        if(arDestinationArray.GetCapacity() < this->GetCapacity())
            arDestinationArray.Reserve(this->GetCapacity());

        this->m_allocator.CopyTo(arDestinationArray.m_allocator);
        arDestinationArray.m_uFirst = m_uFirst;
        arDestinationArray.m_uLast = m_uLast;
    }
    
private:

    /// <summary>
    /// Increases the capacity of the array, reserving memory for more elements than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void ReallocateByFactor(const pointer_uint_q uNumberOfElements)
    {
        const pointer_uint_q FINAL_CAPACITY = scast_q(scast_q(uNumberOfElements, float) * QDynamicArray::REALLOCATION_FACTOR, pointer_uint_q);
        this->Reserve(FINAL_CAPACITY);
    }


    // PROPERTIES
    // ---------------
public:


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The default capacity of all arrays when it is not specified. It must be greater or equal to 1.
    /// </summary>
    static pointer_uint_q sm_uDefaultCapacity;
};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template<class T, class AllocatorT, class ComparatorT>
pointer_uint_q QDynamicArray<T, AllocatorT, ComparatorT>::sm_uDefaultCapacity = 1;

template<class T, class AllocatorT, class ComparatorT>
float QDynamicArray<T, AllocatorT, ComparatorT>::REALLOCATION_FACTOR = 1.5f;


} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QDYNAMICARRAY__
