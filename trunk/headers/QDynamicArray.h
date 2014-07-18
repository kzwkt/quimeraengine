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


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element is called, from first to last.
    /// </remarks>
    ~QDynamicArray()
    {
        // The destructor of every element is called
        for(pointer_uint_q uIndex = 0; uIndex < m_uLast + 1U; ++uIndex)
            this->GetValue(uIndex).~T();
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
