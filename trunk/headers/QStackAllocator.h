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

#ifndef __QSTACKALLOCATOR__
#define __QSTACKALLOCATOR__


#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"
#include "QAlignment.h"
#include "Assertions.h"             // QE_ASSERT


using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{

/// <summary>
/// Class which represents a Stack allocator, that is, a custom allocator that works as a stack, allocating new blocks of memory<br/>
/// at the top and releasing them from top to bottom.
/// </summary>
/// <remarks>
/// -As a stack, memory cannot be freed in an arbitrary order, but in an order opposite to that in which they were allocated.<br/>
/// -It is possible to roll-back to a previously set mark, but not to arbitrary locations within the stack.
/// -The memory blocks will be allocated from a continous block of memory, so it always be necessary<br/>
/// to pass to the constructors, at least, the size for this preallocated memory block.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS QStackAllocator
{

    // INTERNAL CLASSES
	// -----------------

public:

    /// <summary>
    /// Class which represents a mark in the stack; this will let to save a memory address pointing to one of the memory blocks.
    /// </summary>
    /// <remarks>
    /// The use of this mark is optional respect to the stack allocator, but the overall deletion of blocks from the stack may<br/>
    /// speed up by deleting them at once (the stack shall decrease until the position pointed by the mark) instead of deleting<br/>
    /// the blocks one by one.
    /// </remakrs>
    class QE_LAYER_COMMON_SYMBOLS QMark
    {

	    // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor from a memory address.
        /// </summary>
        /// <param name="pMemAddress">[IN] The memory address representing the mark to be kept in. It cannot be a null address.</param>
        explicit QMark(void* pMemAddress);


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Returns the address being kept in as a mark, representing a marked memory block into the stack allocator.
        /// </summary>
        /// <returns>
        /// The kept in mark address, pointing to the memory block.
        /// </returns>
        void* GetMemoryAddress() const;


        // ATTRIBUTES
        // ---------------
    protected:

        /// <summary>
        /// The address being kept in as a mark, representing a marked memory block into the stack allocator.
        /// </summary>
        /// <remarks>
        /// It cannot be a null address.
        /// </remakrs>
        void* m_pMemoryAddress;

    }; // --- QMark ---

protected:

    /// <summary>
    /// Class which represents a memory block header.
    /// </summary>
    /// <remarks>
    /// -Every allocated block has a header structure that contains information about the size of the block, the amount of bytes<br/>
    /// left as a gap in the stack (if it proceeds) between the end of the block header and the start of the memory block for<br/>
    /// making the block to be aligned according to its alignment value, and the amount of bytes necessary to roll the stack back<br/>
    /// to the previous block header.
    /// </remakrs>
    class QE_LAYER_COMMON_SYMBOLS QBlockHeader
    {
	    // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor from a given size for the corresponding block header, a given alignment offset and a given back offset for accessing<br/>
        /// to the previous block header.
        /// </summary>
        /// <param name="uSize">[IN] The size of its corresponding memory block. It cannot be zero.</param>
        /// <param name="uAlignmentOffset">[IN] The amount of bytes left as a gap in the stack (if it proceeds) between the end<br/>
        /// of the block header and the start of the memory block. If the memory block is correctly aligned, this value will be<br/>
        /// zero so the block will be stored in the stack immediatly after the block header.</param>
        /// <param name="uPreviousBlockHeaderBackOffset">[IN] The amount of bytes necessary to roll the stack back to the<br/>
        /// previous block header. If the block header is the first one in the stack, this value will be zero.</param>
        explicit inline QBlockHeader(const pointer_uint_q uSize, const pointer_uint_q uAlignmentOffset, const pointer_uint_q uPreviousBlockHeaderBackOffset )
        {
            QE_ASSERT(uSize > 0, "The given size for the memory block cannot be zero.");

            // uAlignmentOffset and uPreviousBlockHeaderBackOffset cannot be negative, due to they are unsigned.

            m_uSize                      = uSize;
            m_uAlignmentOffset           = uAlignmentOffset;
            m_uPreviousHeaderBackOffset  = uPreviousBlockHeaderBackOffset;
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Returns the size of its corresponding memory block.
        /// </summary>
        /// <remarks>
        /// This size is always greater than zero.
        /// </remarks>
        /// <returns>
        /// A discrete, positive value representing the size of the memory block to which the block header is referring to.
        /// </returns>
        inline pointer_uint_q GetAllocatedBlockSize() const
        {
            return m_uSize;
        }

        /// <summary>
        /// Returns the amount of bytes left as a gap in the stack (if it proceeds) between the end of the block header and<br/>
        /// the start of the memory block.
        /// </summary>
        /// <remarks>
        /// If the memory block is correctly aligned, this value will be zero so the block will be stored in the stack immediatly<br/>
        /// after the block header.
        /// </remarks>
        /// <returns>
        /// A discrete, positive value (or zero) representing the size of the gap between the end of the block header and<br/>
        /// the start of the memory block.
        /// </returns>
        inline pointer_uint_q GetAlignmentOffset() const
        {
            return m_uAlignmentOffset;
        }

        /// <summary>
        /// Returns the amount of bytes necessary to roll the stack back to the previous block header.
        /// </summary>
        /// <remarks>
        /// If the block header is the first one in the stack, this value will be zero.
        /// </remakrs>
        /// <returns>
        /// A discrete, positie value (or zero) representing the necessary offset to make the stack to point to the previous<br/>
        /// block header respect to the current one.
        /// </returns>
        inline pointer_uint_q GetPreviousHeaderBackOffset() const
        {
            return m_uPreviousHeaderBackOffset;
        }


        // ATTRIBUTES
        // ---------------
    private:

        /// <summary>
        /// The size of its corresponding memory block.
        /// </summary>
        /// <remarks>
        /// It cannot be zero.
        /// </remakrs>
        pointer_uint_q m_uSize;

        /// <summary>
        /// The amount of bytes left as a gap in the stack (if it proceeds) between the end of the block header and the start<br/>
        /// of the memory block.
        /// </summary>
        /// <remarks>
        /// -If the memory block is correctly aligned, this value will be zero so the block will be stored in the stack<br/>
        /// immediatly after the block header.<br/>
        /// -If a negative value for this member was computed, the behaviour is undefined.
        /// </remakrs>
        pointer_uint_q m_uAlignmentOffset;

        /// <summary>
        /// The amount of bytes necessary to roll the stack back to the previous block header.
        /// </summary>
        /// <remarks>
        /// -Due to this value will be always POSITIVE it will always have to be SUBTRACTED from the starting address<br/>
        /// of the current bloch header in order to roll back to the previous one.<br/>
        /// -If the current block header is the first one in the stack, this value will be zero.<br/>
        /// -If a negative value for this member was computed, the behaviour is undefined.
        /// </remakrs>
        pointer_uint_q m_uPreviousHeaderBackOffset;

    }; // --- QBlockHeader ---


    // CONSTANTS
	// ---------------
protected:

   	/// <summary>
	/// Constant to symbolize the alignment value by default, when no other alignment value is specified.
	/// </summary>
    static const pointer_uint_q ALIGNMENT_VALUE_DEFAULT;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
    /// Constructor from a given size for the preallocated memory block.
	/// </summary>
    /// <remarks>
    /// -A memory alignment of 1 byte is assumed.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the contiguous preallocation block of memory needed by the stack allocator to work.<br/>
    /// It cannot be zero.</param>
	explicit QStackAllocator(const pointer_uint_q uPreallocationSize);

	/// <summary>
    /// Constructor from a preallocation size and an alignment value.
	/// </summary>
    /// <param name="uPreallocationSize">[IN] The size of the large and contiguous preallocation block of memory needed by the stack allocator to work.<br/>
    /// It cannot be zero.</param>
    /// <param name="alignment">[IN] The alignment for the preallocated memory block. It has to be a power of two.</param>
    QStackAllocator(const pointer_uint_q uPreallocationSize, const QAlignment& alignment);

    /// <summary>
    /// Constructor from a specific pointer to a continous block of preallocated memory and its correspondent size.
    /// </summary>
    /// <remarks>
    /// -The stack allocator will not delete the input preallocated memory block; it has to be deleted externally<br/>
    /// by the entity who provided it.
    /// -If the pointer is not pointing to a real preallocated memory block, the behaviour is undefined.<br/>
    /// -If the pointer is null, stack base remains as null.<br/>
    /// -A memory alignment of 1 byte is assumed.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the contiguous preallocation block of memory needed by the stack allocator to work.<br/>
    /// It cannot be zero.</param>
    /// <param name="pMemAddress">[IN] A pointer to the start of the preallocated memory block from which the stack allocator may perform allocations.<br/>
    /// It cannot be null.</param>
    QStackAllocator(const pointer_uint_q uPreallocationSize, void* pMemAddress);

    /// <summary>
    /// Constructor from a specific pointer to a continous block of preallocated memory,<br/>
    /// and its correspondent size and alignment value.
    /// </summary>
    /// <remarks>
    /// -The stack allocator will not delete the input preallocated memory block; it has to be deleted externally<br/>
    /// by the entity who provided it.
    /// -If the pointer is not pointing to a real preallocated memory block, the behaviour is undefined.<br/>
    /// -If the pointer is null, the stack base remains as null.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the large and contiguous preallocation block of memory needed by the stack allocator to work.<br/>
    /// It cannot be zero.</param>
    /// <param name="pMemAddress">[IN] A pointer to the start of the preallocated memory block from which the stack allocator may perform allocations.<br/>
    /// It cannot be null.</param>
    /// <param name="alignment">[IN] The alignment for the preallocated aligned memory block. It has to be power of two.</param>
    QStackAllocator(const pointer_uint_q uPreallocationSize, void* pMemAddress, const QAlignment& alignment);

private:

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <remarks>
    /// This constructor is invalidated, so that the user has to use QStackAllocator::CopyTo in order to copy the stack allocator.
    /// </remakrs>
    /// <param name="stackAllocator">[IN] The stack allocator from which there is a try to create a copy in the resident stack allocator.</param>
    QStackAllocator(const QStackAllocator& stackAllocator);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
    /// <remarks>
    /// The stack allocator will not delete the preallocated memory block when it has been provided externally by the user.
    /// </remakrs>
	~QStackAllocator();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Allocates a memory block having the specified size, if there is enough space yet on the preallocated memory block<br/>
    /// used by the stack allocator to be fitted.
    /// </summary>
    /// <remarks>
    /// -If something goes wrong and the block cannot be allocated a null pointer is returned.<br/>
    /// -A memory alignment of 1 byte is assumed.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the memory block to be allocated. It cannot be zero.</param>
    /// <returns>
    /// A pointer to the start of the allocated memory block.
    /// </returns>
    void* Allocate(const pointer_uint_q uSize);

    /// <summary>
    /// Allocates an aligned memory block having the specified size and alignment value, if there is enough space yet<br/>
    /// on the preallocated memory block used by the stack allocator to be fitted.
    /// </summary>
    /// <remarks>
    /// If something goes wrong and the block cannot be allocated a null pointer is returned.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the memory block to be allocated. It cannot be zero.</param>
    /// <param name="alignment">[IN] The alignment for the preallocated aligned memory block. It has to be a power of two.</param>
    /// <returns>
    /// A pointer to the start of the allocated memory block.
    /// </returns>
    void* Allocate(const pointer_uint_q uSize, const QAlignment& alignment);

    /// <summary>
    /// Deallocates from the stack the memory block currently placed on top of the stack.
    /// </summary>
    /// <remarks>
    /// -If the stack is empty an assertion is thrown, if they are enabled; otherwise nothing happens. In any case,<br/>
    /// the stack allocator won't be affected.<br/>
    /// -If the stack allocator was not correctly created nothing happens.
    /// </remakrs>
    void Deallocate();

    /// <summary>
    /// Rolls the stack top back to the specified mark, deallocating all the previously allocated memory blocks<br/>
    /// between the top of the stack and the mark.
    /// </summary>
    /// <remarks>
    /// -The specified mark represents the start of the now considered "free space" in the stack (everything stored in higher<br/>
    /// memory addresses into the preallocated memory block will be considered as released/deleted).<br/>
    /// -If the stack is empty an assertion is thrown, if they are enabled; otherwise nothing happens. In any case,<br/>
    /// the stack allocator won't be affected.<br/>
    /// -If the mark is out of the bounds of stack Base and the current stack top, deallocation will not occur.<br/>
    /// -If the stack allocator was not correctly created nothing happens.
    /// </remakrs>
    /// <param name="mark">[IN] The mark to which the stack has to be rolled back. It cannot be null,<br/>
    /// and will always be in a range into the base address of the stack and the stack top.</param>
    void Deallocate(const QMark& mark);

    /// <summary>
    /// Clears completely the stack from previously allocated memory blocks.
    /// </summary>
    /// <remarks>
    /// If the stack is empty nothing happens.
    /// </remakrs>
    inline void Clear()
    {
        m_pTop = m_pPrevious = m_pBase;
        m_uAllocatedBytes = 0;
    }

    /// <summary>
    /// Returns the total size (in bytes) of the stack allocator, that is,<br/>
    /// the amount of bytes occupied by the preallocated memory block.
    /// </summary>
    /// <remarks>
    /// This size cannot be, by no means, lesser than the sum of the sizes of the currently allocated blocks.
    /// </remakrs>
    /// <returns>
    /// A discrete, positive value representing the amount of bytes occupied by the preallocated memory block.
    /// </returns>
    inline pointer_uint_q GetSize() const
    {
        QE_ASSERT(m_uAllocatedBytes <= m_uSize, "Error: the amount of allocated bytes is greater than the size of the preallocated memory block.");
        return m_uSize;
    }

    /// <summary>
    /// Returns if a memory block of a specified size, due to the current free space in the stack, can be allocated or not.
    /// </summary>
    /// <remarks>
    /// -Due to it is necessary to store some metadata for each allocated memory block, certain combinations of block size and<br/>
    /// alignment could make it impossible to allocate new memory blocks, even if it seemed at first sight that the allocation<br/>
    /// could occur. Proceed with extreme caution when the stack allocator is nearly full.<br/>
    /// <br/>
    /// For instance:<br/>
    /// Having created a stack allocator with a valid preallocation size of 1024 bytes and having an alignment value of 16 bytes,<br/>
    /// it could be expected that an allocation of a memory block whose size occupies 1024 bytes, and a valid alignment value<br/>
    /// of 16 bytes, could occur. However, it will not and CanAllocate will return false due to the necessary extra bytes to store<br/>
    /// the metadata.<br/>
    /// <br/>
    /// -A memory alignment of 1 byte is assumed.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the intended memory block to be allocated. It cannot be zero.</param>
    /// <returns>
    /// True if the allocation is possible. False otherwise.
    /// </returns>
    bool CanAllocate(const pointer_uint_q uSize) const;

    /// <summary>
    /// Returns if a memory block of a specified size and alignment value, due to the current free space in the stack,<br/>
    /// can be allocated or not.
    /// </summary>
    /// <remarks>
    /// Due to it is necessary to store some metadata for each allocated memory block, certain combinations of block size and<br/>
    /// alignment could make it impossible to allocate new memory blocks, even if it seemed at first sight that the allocation<br/>
    /// could occur. Proceed with extreme caution when the stack allocator is nearly full.<br/>
    /// <br/>
    /// For instance:<br/>
    /// Having created a stack allocator with a valid preallocation size of 1024 bytes and having an alignment value of 16 bytes,<br/>
    /// it could be expected that an allocation of a memory block whose size occupies 1024 bytes, and a valid alignment value<br/>
    /// of 16 bytes, could occur. However, it will not and CanAllocate will return false due to the necessary extra bytes to store<br/>
    /// the metadata.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the intended memory block to be allocated. It cannot be zero.</param>
    /// <param name="alignment">[IN] The alignment value for the memory block which intended to be allocated.<br/>
    /// It has to be a power of two.</param>
    /// <returns>
    /// True if the allocation is possible. False otherwise.
    /// </returns>
    bool CanAllocate(const pointer_uint_q uSize, const QAlignment& alignment) const;

    /// <summary>
    /// Returns the amount of bytes occupied in the stack by all its allocated memory blocks.
    /// </summary>
    /// <remarks>
    /// This size cannot be, by no means, greater than the size of the preallocated memory block.
    /// </remakrs>
    /// <returns>
    /// A discrete, positive value representing the amount of bytes occupied in the stack by all its allocated memory blocks.
    /// </returns>
    pointer_uint_q GetAllocatedBytes() const
    {
        QE_ASSERT(m_uAllocatedBytes <= m_uSize, "Error: the amount of allocated bytes is greater than the size of the preallocated memory block.");
        return m_uAllocatedBytes;
    }

    /// <summary>
    /// Copies raw data in allocated blocks from the resident stack allocator into the specified one.
    /// </summary>
    /// <remarks>
    /// -If the resident stack allocator was not correctly created the specified one is not modified in any way.<br/>
    /// -If the resident stack allocator has a greater size than the specified oneto, this one is not modified in any way.
    /// </remakrs>
    /// <param name="stackAllocator">[OUT] The stack allocator in which the resident has to copy its data.</param>
    void CopyTo(QStackAllocator& stackAllocator) const;

    /// <summary>
    /// Returns a mark to the current top of the stack.
    /// </summary>
    /// <remarks>
    /// -If the stack allocator is not correctly created undefined behaviour is expected.<br/>
    /// -This mark will not be lesser than the Stack Base address.<br/>
    /// -Special attention has to be taken when using this mark, because it could become obsolete due to further deallocations<br/>
    /// in the stack; if the user uses an obsolete mark for trying to roll the stack top back, undefined behaviour is expected.
    /// </remakrs>
    /// <returns>
    /// A mark to the current Stack Top.
    /// </returns>
    inline QMark GetMark() const
    {
        QE_ASSERT(null_q != m_pTop, "Error on retrieving a mark: stack top is null.");
        return QMark(m_pTop);
    }

protected:

    /// <summary>
    /// Initializes all the attributes of the class (but the alignment) to a default starting value in order to avoid<br/>
    /// garbage values for non-initialized attributes.
    /// </summary>
    /// <remarks>
    /// -Because it is mandatory to specify an alignment for all the constructors of the class it is not necessary to set<br/>
    ///  a default value to the alignment on this method.<br/>
    /// -In order to avoid a huge memory leak the preallocated memory block has to be freed before calling this method.<br/>
    /// -The stack allocator keeps its current state (either validated or invalidated) after calling to this method. If the state<br/>
    /// has to be modified, it has to be done apart from this method.
    /// </remakrs>
    inline void ClearAttributes()
    {
        m_pBase = m_pTop = m_pPrevious = null_q;
        m_uSize = m_uAllocatedBytes    = 0;
    }

    /// <summary>
    /// Internal method used by the class to preallocate a large and fixed continous block of memory,<br/>
    /// used for allocations of memory blocks.
    /// </summary>
    /// <remarks>
    /// If something goes wrong (and the block cannot be allocated) a null pointer is returned.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the large and contiguous preallocation block of memory needed by the stack allocator to work.<br/>
    /// It cannot be zero.</param>
    /// <param name="alignment">[IN] The alignment for the preallocated aligned memory block. It has to be a power of two.</param>
    /// <returns>
    /// A pointer to the start of the preallocated memory block.
    /// </returns>
    void* Preallocate(const pointer_uint_q uPreallocationSize, const QAlignment& alignment);

    /// <summary>
    /// Internal method used by the class to finalize the stack allocator.
    /// </summary>
    /// <remarks>
    /// It will be used in the destructor of the class for releasing all the dynamically allocated resources by the stack allocator<br/>
    /// and clear all the members.
    /// </remakrs>
    void Finalize();

private:

    /// <summary>
    /// Assign operator.
    /// </summary>
    /// <remarks>
    /// This operator is invalidated, so that the user has to use QStackAllocator::CopyTo in order to copy the stack allocator.
    /// </remakrs>
    /// <param name="stackallocator">[IN] The stack allocator from which there is a try to create a copy in the resident stack allocator.</param>
    QStackAllocator& operator=(const QStackAllocator& stackallocator);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// Pointer to the base of the stack.
    /// </summary>
    /// <remarks>
    /// Its main role is to point to the start of the prellocated memory block.
    /// </remakrs>
    void* m_pBase;

    /// <summary>
    /// Pointer to the top of the stack.
    /// </summary>
    /// <remarks>
    /// When the stack is empty it points to the same address as the pointer to the stack base.
    /// </remakrs>
    void* m_pTop;

    /// <summary>
    /// Pointer to the previous allocated memory block regarding from the top of the stack.
    /// </summary>
    /// <remarks>
    /// When the stack is empty it points to the same address as the pointer to the stack top.
    /// </remakrs>
    void* m_pPrevious;

    /// <summary>
    /// Alignment value for the preallocated memory block.
    /// </summary>
    /// <remarks>
    /// By default it equals one, otherwise it has to be a power of two.
    /// </remakrs>
    QAlignment m_alignment;

    /// <summary>
    /// Size (in bytes) for the preallocated memory block.
    /// </summary>
    /// <remarks>
    /// This value cannot be, by no means, lower than the sum of the sizes of the currently allocated blocks.
    /// </remarks>
    pointer_uint_q m_uSize;

    /// <summary>
    /// The amount of bytes occupied in the stack by all its allocated memory blocks.
    /// </summary>
    /// <remarks>
    /// This size cannot be, by no means, greater than the size of the preallocated memory block.
    /// </remakrs>
    pointer_uint_q m_uAllocatedBytes;

    /// <summary>
    /// If True, the preallocated memory block will be deleted during the destruction of the Stack Allocator object.<br/>
    /// If False, it will not be deleted so it must be done so externally by other means in order to avoid a memory leak.
    /// </summary>
    /// <remarks>
    /// The stack allocator has to delete the preallocated memory block when it is created by its own, and it has not to do so<br/>
    /// when it was externally passed from.
    /// </remakrs>
    bool m_bDeletePreallocatedBlock;
};

} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSTACKALLOCATOR__
