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


using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;
using Kinesis::QuimeraEngine::Tools::Containers::QComparatorDefault;

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
/// index. Their size is defined when it is constructed and cannot be changed afterwards.
/// </summary>
/// <remarks>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.
/// </remarks>
template <class T, class Allocator = QPoolAllocator, class Comparator = QComparatorDefault<T> >
class QFixedArray
{
protected:

   	// CONSTANTS
	// ---------------

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
        // [TODO] : rdelasheras. Replace "fixedArray.m_uLast + 1" with "fixedArray.GetCount()" when it exists.
        m_pAllocator = new Allocator((fixedArray.m_uLast + 1) * sizeof(T), sizeof(T), QAlignment(alignof_q(T)));

        for(pointer_uint_q uIndex = 0; uIndex < fixedArray.m_uLast + 1; uIndex++)
        {
            // Constructs a T object over the buffer returned by the allocator and initializes it with
            // the value of the origin element in the corresponding array position.
            // [TODO] : rdelasheras. Access to every element with "fixedArray[uIndex]" when it exists instead of using pointers arithmetic.
            new(m_pAllocator->Allocate()) 
                T(*(T*)((pointer_uint_q)fixedArray.GetAllocator()->GetPointer() + uIndex * sizeof(T)));
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
 
        // [TODO] : rdelasheras. Replace "m_uLast + 1" with "this->GetCount()" when it exists.
        // [TODO] : rdelasheras. Access to every element with "(*this)[uIndex]" when it exists instead of using pointers arithmetic.
        for(pointer_uint_q uIndex = 0; uIndex < m_uLast + 1; uIndex++)
            ((T*)((pointer_uint_q)m_pAllocator->GetPointer() + uIndex * sizeof(T)))->~T();
            

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

        // [TODO] : rdelasheras. Replace "m_uLast + 1" with "GetCount()" when it exists.
        if( m_uLast > fixedArray.m_uLast )
            uElementsToCopy = fixedArray.m_uLast + 1;
        else
            uElementsToCopy = m_uLast + 1;

        for( pointer_uint_q uIndex = 0; uIndex < uElementsToCopy; uIndex++ )
        {
            // Destination array element value = Origin array element value, using pointers arithmetic
            // [TODO] : rdelasheras. Access to every element with "[uIndex]" when it exists instead of using pointers arithmetic.
            *(T*)((pointer_uint_q)m_pAllocator->GetPointer() + uIndex * sizeof(T)) =
                *(T*)((pointer_uint_q)fixedArray.m_pAllocator->GetPointer() + uIndex * sizeof(T));
        }

        return *this;
    }

private:
    
    /// <sumary>
    /// Checks if the multiplication of two operands overflows for the pointer_uint_q type.
    /// </sumary>
    /// <param name="uOperandA"> [IN] Operand to multiply.</param>
    /// <param name="uOperandB"> [IN] Operand to multiply.</param>
    /// <returns>
    /// True if the result overflows for the pointer_uint_q type.
    /// </returns>
    bool MultiplicationOverflows(pointer_uint_q uOperandA, pointer_uint_q uOperandB) const 
    {
        return this->HighestOneBitPosition(uOperandA) + this->HighestOneBitPosition(uOperandB) > sizeof(pointer_uint_q) * 8;
    }

    /// <sumary>
    /// Gets the highest one bit position of a number converted to binary format.
    /// </sumary>
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
            uValue>>=1;
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
