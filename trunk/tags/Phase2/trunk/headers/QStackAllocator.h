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
#include "Assertions.h"


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
/// Represents a stack allocator, that is, a custom allocator that works as a stack, allocating new blocks of memory
/// at the top and releasing them from top to bottom.
/// </summary>
/// <remarks>
/// -As a stack, memory cannot be freed in an arbitrary order, but in an order opposite to that in which they were allocated.<br/>
/// -It is possible to roll-back to a previously set mark, but not to arbitrary locations within the stack.<br/>
/// -Memory blocks will be allocated into a continuous block of memory, so it is always necessary
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
    /// The use of this mark is optional with respect to the stack allocator, but the overall deletion of blocks from the stack may
    /// speed up by deleting them at once (the stack shall decrease until the position pointed by the mark) instead of deleting
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
    /// Every allocated block has a header structure that contains information about the size of the block, the amount of bytes
    /// left as a gap in the stack (if it proceeds) between the end of the block header and the start of the memory block for
    /// making the block to be aligned according to its alignment value, and the amount of bytes necessary to roll the stack back
    /// to the previous block header.
    /// </remakrs>
    class QE_LAYER_COMMON_SYMBOLS QBlockHeader
    {
	    // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor from a given size for the corresponding block header, a given alignment offset and a given back offset for accessing
        /// the previous block header.
        /// </summary>
        /// <param name="uSize">[IN] The size of its corresponding memory block. It cannot be zero.</param>
        /// <param name="uAlignmentOffset">[IN] The amount of bytes left as a gap in the stack (if it proceeds) between the end
        /// of the block header and the start of the memory block. If the memory block is correctly aligned, this value will be
        /// zero so the block will be stored in the stack immediately after the block header.</param>
        /// <param name="uPreviousBlockHeaderBackOffset">[IN] The amount of bytes necessary to roll the stack back to the
        /// previous block header. If the block header is the first one in the stack, this value should be zero.</param>
        explicit QBlockHeader(const pointer_uint_q uSize, const pointer_uint_q uAlignmentOffset, const pointer_uint_q uPreviousBlockHeaderBackOffset);


        // PROPERTIES
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
        pointer_uint_q GetAllocatedBlockSize() const;

        /// <summary>
        /// Returns the amount of bytes left as a gap in the stack (if it proceeds) between the end of the block header and
        /// the start of the memory block.
        /// </summary>
        /// <remarks>
        /// If the memory block is correctly aligned, this value will be zero so the block will be stored in the stack immediately
        /// after the block header.
        /// </remarks>
        /// <returns>
        /// A discrete, positive value (or zero) representing the size of the gap between the end of the block header and
        /// the start of the memory block.
        /// </returns>
        pointer_uint_q GetAlignmentOffset() const;

        /// <summary>
        /// Returns the amount of bytes necessary to roll the stack back to the previous block header.
        /// </summary>
        /// <remarks>
        /// If the block header is the first one in the stack, this value will be zero.
        /// </remakrs>
        /// <returns>
        /// A discrete, positie value (or zero) representing the necessary offset to make the stack to point to the previous
        /// block header respect to the current one.
        /// </returns>
        pointer_uint_q GetPreviousHeaderBackOffset() const;


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
        /// The amount of bytes left as a gap in the stack (if it proceeds) between the end of the block header and the start
        /// of the memory block.
        /// </summary>
        /// <remarks>
        /// -If the memory block is correctly aligned, this value will be zero so the block will be stored in the stack
        /// immediately after the block header.<br/>
        /// -If a negative value for this member was computed, the behaviour is undefined.
        /// </remakrs>
        pointer_uint_q m_uAlignmentOffset;

        /// <summary>
        /// The amount of bytes necessary to roll the stack back to the previous block header.
        /// </summary>
        /// <remarks>
        /// -Due to this value will be always POSITIVE it will always have to be SUBTRACTED from the starting address
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
    /// A memory alignment of 1 byte is assumed.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the contiguous preallocation block of memory needed by the stack allocator to work.
    /// It cannot be zero.</param>
	explicit QStackAllocator(const pointer_uint_q uPreallocationSize);

	/// <summary>
    /// Constructor from a preallocation size and an alignment value.
	/// </summary>
    /// <param name="uPreallocationSize">[IN] The size of the contiguous preallocated block of memory needed by the stack allocator to work.
    /// It cannot be zero.</param>
    /// <param name="alignment">[IN] The alignment for the preallocated memory block.</param>
    QStackAllocator(const pointer_uint_q uPreallocationSize, const QAlignment& alignment);

    /// <summary>
    /// Constructor from a specific pointer to a continuous block of preallocated memory and its corresponding size.
    /// </summary>
    /// <remarks>
    /// -The stack allocator will not delete the input preallocated memory block; it has to be deleted externally
    /// by the entity which provided it.<br/>
    /// -A memory alignment of 1 byte is assumed.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the contiguous preallocation block of memory needed by the stack allocator to work.
    /// It cannot be zero. If the pointer is not pointing to a real preallocated memory block, the behaviour is undefined.</param>
    /// <param name="pMemAddress">[IN] A pointer to the start of the preallocated memory block into which the stack allocator will perform allocations.
    /// It cannot be null.</param>
    QStackAllocator(const pointer_uint_q uPreallocationSize, void* pMemAddress);

    /// <summary>
    /// Constructor from a specific pointer to a continuous block of preallocated memory, its corresponding size and its alignment.
    /// </summary>
    /// <remarks>
    /// If the memory block's alignment and the alignment value provided do not match, an offset will be applied internally. This means that
    /// some amount memory may be useless at the beginning of the block.<br/>
    /// The stack allocator will not delete the input preallocated memory block; it has to be deleted externally
    /// by the entity which provided it.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the and contiguous preallocation block of memory needed by the stack allocator to work.
    /// It cannot be zero.</param>
    /// <param name="pMemAddress">[IN] A pointer to the start of the preallocated memory block from which the stack allocator may perform allocations.
    /// It cannot be null. If the pointer is not pointing to a real preallocated memory block, the behaviour is undefined.</param>
    /// <param name="alignment">[IN] The alignment for the preallocated memory block.</param>
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
    /// Allocates a memory block having the specified size, if it fits in the remaining space of the preallocated memory block used by the stack allocator.
    /// </summary>
    /// <remarks>
    /// -If something goes wrong and the block cannot be allocated a null pointer is returned.<br/>
    /// -A memory alignment of 1 byte is assumed.<br/>
    /// -Every allocation requires an extra amount of bytes of 12 bytes.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the memory block to be allocated. It cannot be zero.</param>
    /// <returns>
    /// A pointer to the start of the allocated memory block.
    /// </returns>
    void* Allocate(const pointer_uint_q uSize);

    /// <summary>
    /// Allocates an aligned memory block having the specified size and alignment value, if it fits in the remaining space of the preallocated memory block used by the stack allocator.
    /// </summary>
    /// <remarks>
    /// If something goes wrong and the block cannot be allocated a null pointer is returned.<br/>
    /// Every allocation requires an extra amount of bytes of 12 bytes.<br/>
    /// Due to the alignment adjustment, the required free space may be greater than expected.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the memory block to be allocated. It cannot be zero.</param>
    /// <param name="alignment">[IN] The alignment for the new memory block.</param>
    /// <returns>
    /// A pointer to the start of the allocated memory block.
    /// </returns>
    void* Allocate(const pointer_uint_q uSize, const QAlignment& alignment);

    /// <summary>
    /// Deallocates the memory block currently placed on top of the stack.
    /// </summary>
    /// <remarks>
    /// If the stack is empty nothing happens.
    /// </remakrs>
    void Deallocate();

    /// <summary>
    /// Rolls the stack top back to the specified mark, deallocating all the previously allocated memory blocks
    /// between the top of the stack and the mark.
    /// </summary>
    /// <remarks>
    /// -The specified mark represents the start of the now considered "free space" in the stack (everything stored in higher
    /// memory addresses into the preallocated memory block will be considered as released/deleted).<br/>
    /// -If the stack is empty nothing happens.<br/>
    /// -If the mark is out of the bounds of stack base and the stack top, deallocation will not occur.
    /// </remakrs>
    /// <param name="mark">[IN] The mark to which the stack has to be rolled back. It cannot be null,
    /// and will always be in a range between the base address of the stack and the stack top.</param>
    void Deallocate(const QMark& mark);

    /// <summary>
    /// Clears completely the stack from previously allocated memory blocks.
    /// </summary>
    /// <remarks>
    /// If the stack is empty nothing happens.
    /// </remakrs>
    void Clear();

    /// <summary>
    /// Returns the total size (in bytes) of the stack allocator, that is,
    /// the amount of bytes occupied by the preallocated memory block.
    /// </summary>
    /// <remarks>
    /// This size cannot be, by no means, lesser than the sum of the sizes of the currently allocated blocks.
    /// </remakrs>
    /// <returns>
    /// A discrete, positive value representing the amount of bytes occupied by the preallocated memory block.
    /// </returns>
    pointer_uint_q GetSize() const;

    /// <summary>
    /// Returns if a memory block of a specified size, due to the current free space in the stack, can be allocated or not.
    /// </summary>
    /// <remarks>
    /// -Due to it is necessary to store some metadata for each allocated memory block, certain combinations of block size and
    /// alignment could make it impossible to allocate new memory blocks, even if it seemed at first sight that the allocation
    /// could occur. Proceed with extreme caution when the stack allocator is nearly full.<br/>
    /// <br/>
    /// For instance:<br/>
    /// Having created a stack allocator with a valid preallocation size of 1024 bytes and having an alignment value of 16 bytes,
    /// it could be expected that an allocation of a memory block whose size occupies 1024 bytes, and a valid alignment value
    /// of 16 bytes, could occur. However, it will not and CanAllocate will return false due to the necessary extra bytes to store
    /// the metadata.<br/>
    /// <br/>
    /// -A memory alignment of 1 byte is assumed.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the memory block to be allocated.</param>
    /// <returns>
    /// True if the allocation is possible. False otherwise.
    /// </returns>
    bool CanAllocate(const pointer_uint_q uSize) const;

    /// <summary>
    /// Returns if a memory block of a specified size and alignment value, due to the current free space in the stack,
    /// can be allocated or not.
    /// </summary>
    /// <remarks>
    /// Due to it is necessary to store some metadata for each allocated memory block, certain combinations of block size and
    /// alignment could make it impossible to allocate new memory blocks, even if it seemed at first sight that the allocation
    /// could occur. Proceed with extreme caution when the stack allocator is nearly full.<br/>
    /// <br/>
    /// For instance:<br/>
    /// Having created a stack allocator with a valid preallocation size of 1024 bytes and having an alignment value of 16 bytes,
    /// it could be expected that an allocation of a memory block whose size occupies 1024 bytes, and a valid alignment value
    /// of 16 bytes, could occur. However, it will not and CanAllocate will return false due to the necessary extra bytes to store
    /// the metadata.
    /// </remakrs>
    /// <param name="uSize">[IN] Size of the memory block to be allocated.</param>
    /// <param name="alignment">[IN] The alignment value for the memory block to be allocated.</param>
    /// <returns>
    /// True if the allocation is possible. False otherwise.
    /// </returns>
    bool CanAllocate(const pointer_uint_q uSize, const QAlignment& alignment) const;

    /// <summary>
    /// Returns the amount of bytes occupied in the stack by all its allocated memory blocks.
    /// </summary>
    /// <remarks>
    /// This size cannot be, by no means, greater than the size of the preallocated memory block.<br/>
    /// The amount of allocated bytes includes the bytes lost due to the alignment adjustment of allocated blocks.
    /// </remakrs>
    /// <returns>
    /// A discrete, positive value representing the amount of bytes occupied in the stack by all its allocated memory blocks.
    /// </returns>
    pointer_uint_q GetAllocatedBytes() const;

    /// <summary>
    /// Copies raw data in allocated blocks from the resident stack allocator into the specified one.
    /// </summary>
    /// <remarks>
    /// If the resident stack allocator has a greater size than the specified one, the latter is not modified in any way.<br/>
    /// The alignment of both allocators must be the same or nothing will be done.<br/>
    /// An important thing to take into account is that, since the buffer is copied in one go, all the blocks may be misaligned in the destination allocator.
    /// </remakrs>
    /// <param name="stackAllocator">[OUT] The stack allocator in which the resident has to copy its data.</param>
    void CopyTo(QStackAllocator& stackAllocator) const;

    /// <summary>
    /// Returns a mark to the current top of the stack.
    /// </summary>
    /// <remarks>
    /// Special attention has to be taken when using this mark, because it could become obsolete due to further deallocations
    /// in the stack; if the user uses an obsolete mark for trying to roll the stack top back, undefined behaviour is expected.
    /// </remakrs>
    /// <returns>
    /// A mark to the current stack top.
    /// </returns>
    QMark GetMark() const;

protected:

    /// <summary>
    /// Initializes all the attributes of the class (but the alignment) to a default starting value in order to avoid
    /// garbage values for non-initialized attributes.
    /// </summary>
    /// <remarks>
    /// -Because it is mandatory to specify an alignment for all the constructors of the class it is not necessary to set
    ///  a default value to the alignment on this method.<br/>
    /// -In order to avoid a huge memory leak the preallocated memory block has to be freed before calling this method.<br/>
    /// -The stack allocator keeps its current state (either validated or invalidated) after calling to this method. If the state
    /// has to be modified, it has to be done apart from this method.
    /// </remakrs>
    void ClearAttributes();

    /// <summary>
    /// Internal method used by the class to preallocate a large and fixed continuous block of memory,
    /// used for allocations of memory blocks.
    /// </summary>
    /// <remarks>
    /// If something goes wrong (and the block cannot be allocated) a null pointer is returned.
    /// </remakrs>
    /// <param name="uPreallocationSize">[IN] The size of the preallocated block of memory needed by the stack allocator to work.
    /// It cannot be zero.</param>
    /// <param name="alignment">[IN] The alignment for the preallocated aligned memory block.</param>
    /// <returns>
    /// A pointer to the start of the preallocated memory block.
    /// </returns>
    void* Preallocate(const pointer_uint_q uPreallocationSize, const QAlignment& alignment);

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
    /// If True, the preallocated memory block will be deleted during the destruction of the stack allocator.
    /// If False, it will not be deleted so it must be done externally by other means in order to avoid a memory leak.
    /// </summary>
    bool m_bDeletePreallocatedBlock;
};

} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSTACKALLOCATOR__
