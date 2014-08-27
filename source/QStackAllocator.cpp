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

#include "QStackAllocator.h"

#include <cstring>                  // memcpy
#include "AllocationOperators.h"
#include "Assertions.h"


using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Common::Memory::QStackAllocator;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const pointer_uint_q QStackAllocator::ALIGNMENT_VALUE_DEFAULT = 1;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QStackAllocator::QStackAllocator(const pointer_uint_q uPreallocationSize) : m_alignment(ALIGNMENT_VALUE_DEFAULT)
{
    // In this case, the preallocated block has to be deleted by the stack allocator.
    m_bDeletePreallocatedBlock = true;

    this->ClearAttributes();

    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");

    QAlignment alignDefault(ALIGNMENT_VALUE_DEFAULT);

    m_pBase = this->Preallocate(uPreallocationSize, alignDefault);
    QE_ASSERT(null_q != m_pBase, "Error during preallocation, stack base remains as null.");

    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize;
}

QStackAllocator::QStackAllocator(const pointer_uint_q uPreallocationSize, const QAlignment& alignment) : m_alignment(alignment)
{
    // In this case, the preallocated block has to be deleted by the stack allocator.
    m_bDeletePreallocatedBlock = true;

    this->ClearAttributes();

    pointer_uint_q uAlignment = alignment;

    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    QE_ASSERT( !(0 == uAlignment) && !(uAlignment & (uAlignment - 1U)) , "The given alignment value for preallocation must be a power of two.");

    m_pBase = this->Preallocate(uPreallocationSize, alignment);
    QE_ASSERT(null_q != m_pBase, "Error during preallocation, stack base remains as null.");

    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize;
}

QStackAllocator::QStackAllocator(const pointer_uint_q uPreallocationSize, void* pMemAddress) : m_alignment(ALIGNMENT_VALUE_DEFAULT)
{
    // In this case, the preallocated block has NOT to be deleted by the stack allocator (it will be done so externally
    // by the entity which passed it).
    m_bDeletePreallocatedBlock = false;

    this->ClearAttributes();

    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    QE_ASSERT(null_q != pMemAddress, "The input pointer to a preallocated memory block cannot be null.");

    // VERY IMPORTANT: there is no way to prove pMemAddress points to the start of a real allocated memory block.
    m_pBase = pMemAddress;
    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize;
}

QStackAllocator::QStackAllocator(const pointer_uint_q uPreallocationSize, void* pMemAddress, const QAlignment& alignment) : m_alignment(alignment)
{
    // In this case, the preallocated block has NOT to be deleted by the stack allocator (it will be done so externally
    // by the entity which passed it).
    m_bDeletePreallocatedBlock = false;

    this->ClearAttributes();

    pointer_uint_q uAlignment = alignment;

    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    QE_ASSERT(null_q != pMemAddress, "The input pointer to a preallocated memory block cannot be null.");

    // VERY IMPORTANT: there is no way to prove pMemAddress points to the start of a real allocated memory block.
    m_pBase = pMemAddress;
        
    // If necessary, adjust the address of the stack base to make it to point to the first address, starting from
    // the input address, that has the given alignment.
    pointer_uint_q  uAmountMisalignedBytes = (rcast_q(m_pBase, pointer_uint_q)) & (uAlignment - 1U);
    if (uAmountMisalignedBytes > 0)
    {
        pointer_uint_q  uAddressResult = (rcast_q(m_pBase, pointer_uint_q)) + uAmountMisalignedBytes;
        m_pBase = rcast_q(uAddressResult, void*);
    }

    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize - uAmountMisalignedBytes;
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QStackAllocator::~QStackAllocator()
{
    // Deallocate the preallocated memory block if it has to be made.
    if (true == m_bDeletePreallocatedBlock)
    {
        operator delete(m_pBase, m_alignment);
    }
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void* QStackAllocator::Preallocate(const pointer_uint_q uPreallocationSize, const QAlignment& alignment)
{
    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");

    // If something goes wrong (and the block cannot be allocated) a null pointer is returned.
    void* pPreallocatedRes = operator new(uPreallocationSize, alignment);

    QE_ASSERT(null_q != pPreallocatedRes, "Error: couldn't preallocate the asked memory block.");

    return pPreallocatedRes;
}

void* QStackAllocator::Allocate(const pointer_uint_q uSize)
{
    return this->Allocate( uSize, QAlignment(ALIGNMENT_VALUE_DEFAULT) );
}

void* QStackAllocator::Allocate(const pointer_uint_q uSize, const QAlignment& alignment)
{
    QE_ASSERT(uSize > 0, "The given size for the memory block to allocate cannot be zero.");
    QE_ASSERT(this->CanAllocate(uSize, alignment), "Error: allocation cannot be accomplished, currently there's not enough space to allocate a memory block with such size.");

    void* pAllocBlock = null_q;

    if(this->CanAllocate(uSize, alignment))
    {
        // STEP 1) Prerrequisites.
        m_pPrevious = m_pTop;

        // STEP 2) Compute the alignment offset, if it proceeds.
        pointer_uint_q uAmountMisalignedBytes = (rcast_q(m_pTop, pointer_uint_q) + sizeof(QBlockHeader)) & (alignment - 1U);

        // STEP 3) Create a Block Header.
        //         (** using the so-called 'placement new operator' **).
        QBlockHeader* pLastBlock = scast_q(m_pPrevious, QBlockHeader*);
        pointer_uint_q uOffsetToPreviousBlock = pLastBlock != null_q ? 
                                                                      0 : 
                                                                      pLastBlock->GetAllocatedBlockSize() + pLastBlock->GetAlignmentOffset() + sizeof(QBlockHeader);

        QBlockHeader* pBlockHeader = new (m_pTop) QBlockHeader(uSize, uAmountMisalignedBytes, uOffsetToPreviousBlock);

        // STEP 4) Gets the allocated block and moves the stack top above it
        pointer_uint_q uAllocatedBlockAddress = rcast_q(m_pTop, pointer_uint_q) + sizeof(QBlockHeader) + uAmountMisalignedBytes;
        pAllocBlock = rcast_q(uAllocatedBlockAddress, void*);
        m_pTop = rcast_q(uAllocatedBlockAddress + uSize, void*);
        

        // STEP 5) Update the current size (in bytes) of occupied size in the stack allocator,
        //         counting on the size of the Block Header as well.
        m_uAllocatedBytes += sizeof(QBlockHeader) + uAmountMisalignedBytes + uSize;
    }

    // STEP 6) Return the pointer to the block header.
    return pAllocBlock;
}

void QStackAllocator::Deallocate()
{
    QE_ASSERT(this->GetAllocatedBytes() > 0, "Error trying to deallocate: stack allocator is empty.");
    
    if(this->GetAllocatedBytes() > 0)
    {
        // STEP 1) Compute the Previous header.

        pointer_uint_q uBackOffset          = scast_q(m_pPrevious, QBlockHeader*)->GetPreviousHeaderBackOffset();
        pointer_uint_q uPointerDecremented  = rcast_q(m_pPrevious, pointer_uint_q) - uBackOffset;
        void*          pPreviousBlockHeader = rcast_q(uPointerDecremented, void*);

        if (null_q == pPreviousBlockHeader)
        {
            pPreviousBlockHeader = m_pBase;
        }


        // STEP 2) Compute the deallocation.

        m_pTop      = m_pPrevious;
        m_pPrevious = pPreviousBlockHeader;


        // STEP 3) Update the current size (in bytes) of occupied size in the stack allocator.

        m_uAllocatedBytes -= scast_q(m_pTop, QBlockHeader*)->GetAllocatedBlockSize()
                              + scast_q(m_pTop, QBlockHeader*)->GetAlignmentOffset()
                              + sizeof(QBlockHeader);
    }
}

void QStackAllocator::Deallocate(const QStackAllocator::QMark& mark)
{
    QE_ASSERT(this->GetAllocatedBytes() > 0, "Error trying to deallocate: stack allocator is empty.");

    void* pMarkAddress = mark.GetMemoryAddress();

    QE_ASSERT(null_q != pMarkAddress,  "The given mark address cannot be null.");
    QE_ASSERT(pMarkAddress >= m_pBase, "Error: mark out of range --> lesser than stack base.");
    QE_ASSERT(pMarkAddress <= m_pTop,  "Error: mark out of range --> greater than current stack top.");
    
    if(this->GetAllocatedBytes() > 0 && pMarkAddress >= m_pBase && pMarkAddress < m_pTop)
    {
        // STEP 1) Update 'm_pPrevious'.

        // Auxiliar pointer that will point, on each iteration during the reverse traversal of the Preallocated Memory
        // Block, to the block header of each allocated memory block; at the end of the traversal, it will point to the
        // block header of the memory block that will become the top of the stack, so that m_pPrevious will also have to
        // point to the same address.
        void* pResultingBackAddress = null_q;
     
        // Auxiliar variable that will store the accumulated decrement of allocates bytes during the traversal.
        pointer_uint_q uAcumDecrementOfAllocatedBytes = 0;

        // Auxiliar variable that stores, on each case, the Offset to traverse back the the previous block header. 
        pointer_uint_q uOffset  = 0; 

        // Auxiar variables that stores, on each case, casted addresses.
        pointer_uint_q uAddress = 0;
    /*
        do
        {
            uAcumDecrementOfAllocatedBytes += (  scast_q(m_pPrevious, QBlockHeader*)->GetAllocatedBlockSize() 
                                               + scast_q(m_pPrevious, QBlockHeader*)->GetAlignmentOffset()
                                               + sizeof(QBlockHeader)
                                              );

            uOffset                = scast_q(m_pPrevious, QBlockHeader*)->GetPreviousHeaderBackOffset();
            uAddress               = rcast_q(m_pPrevious, pointer_uint_q);
    
            pResultingBackAddress  = rcast_q( (uAddress - uOffset), void* );
            m_pPrevious            = pResultingBackAddress;

            uAddress               = rcast_q(m_pPrevious, pointer_uint_q);
        
        } while( (uAddress + uOffset) > rcast_q(pMarkAddress, pointer_uint_q) );
   */
        uAcumDecrementOfAllocatedBytes = rcast_q(m_pTop, pointer_uint_q) - rcast_q(mark.GetMemoryAddress(), pointer_uint_q);
        QBlockHeader* pMarkBlockHeader = scast_q(mark.GetMemoryAddress(), QBlockHeader*);
        pointer_uint_q uMarkPreviousBlockAddress = rcast_q(mark.GetMemoryAddress(), pointer_uint_q) - pMarkBlockHeader->GetPreviousHeaderBackOffset();
        m_pPrevious = rcast_q(uMarkPreviousBlockAddress, void*);

        // Now 'm_pPrevious' is pointing to block header regarding to the memory block that now is considered the one
        // placed in the top of the stack.

        // STEP 2) Update the stack top.
        m_pTop = pMarkAddress;

        // Now 'm_pTop' is pointing to the start of the considered "free space" in the stack (everything stored in higher memory
        // addresses into the preallocated memory block is considered as released/deleted).
    
        // STEP 3) Update the amount of allocated bytes.
        m_uAllocatedBytes -= uAcumDecrementOfAllocatedBytes;
    }
}

void QStackAllocator::Clear()
{
    m_pTop = m_pPrevious = m_pBase;
    m_uAllocatedBytes = 0;
}

pointer_uint_q QStackAllocator::GetSize() const
{
    QE_ASSERT(m_uAllocatedBytes <= m_uSize, "Error: the amount of allocated bytes is greater than the size of the preallocated memory block.");
    return m_uSize;
}

bool QStackAllocator::CanAllocate(const pointer_uint_q uSize) const
{
    QE_ASSERT(uSize > 0, "The size of the memory block to be allocated cannot be zero.");

    // Free space in the preallocated block...: m_uSize - m_uAllocatedBytes
    // Space occupied by the new block........:   uSize + sizeof(QBlockHeader)  <-- there's no misaligned bytes since the default alignment is 1.

    pointer_uint_q uFreeSpaceInPreallocatedBlock  = m_uSize - m_uAllocatedBytes;
    pointer_uint_q uSpaceOccupiedByNewMemoryBlock =   uSize + (sizeof(QBlockHeader));

    return uFreeSpaceInPreallocatedBlock >= uSpaceOccupiedByNewMemoryBlock;
}

bool QStackAllocator::CanAllocate(const pointer_uint_q uSize, const QAlignment& alignment) const
{
    QE_ASSERT(uSize > 0, "The given size for the memory block to be allocated cannot be zero.");
    pointer_uint_q uAlignment = alignment;
    QE_ASSERT( !(0 == uAlignment) && !(uAlignment & (uAlignment - 1)) , "The given alignment value must be a power of two.");

    // Free space in the preallocated block...: m_uSize - m_uAllocatedBytes
    // Space occupied by the new block........:   uSize + sizeof(QBlockHeader) + OffsetToAlign(NewBlock)

    pointer_uint_q  uOffsetToAlign                 = ((rcast_q(m_pTop, pointer_uint_q)) + sizeof(QBlockHeader)) & (uAlignment - 1U);
    pointer_uint_q  uFreeSpaceInPreallocatedBlock  = m_uSize - m_uAllocatedBytes;
    pointer_uint_q  uSpaceOccupiedByNewMemoryBlock =   uSize + (sizeof(QBlockHeader)) + uOffsetToAlign;

    return uFreeSpaceInPreallocatedBlock >= uSpaceOccupiedByNewMemoryBlock;
}

pointer_uint_q QStackAllocator::GetAllocatedBytes() const
{
    QE_ASSERT(m_uAllocatedBytes <= m_uSize, "Error: the amount of allocated bytes is greater than the size of the preallocated memory block.");
    return m_uAllocatedBytes;
}

void QStackAllocator::CopyTo(QStackAllocator& stackAllocator) const
{
    QE_ASSERT( (this->GetSize() > 0) && (stackAllocator.GetSize() > 0), "Error on copying of stack allocators: the size of any stack allocators cannot be zero.");
    QE_ASSERT(this->GetSize() <= stackAllocator.GetSize(), "Error on copying of stack allocators: the size of the passed stack allocator cannot be lower than the size of the resident one.");
    QE_ASSERT(m_alignment == stackAllocator.m_alignment, "Error on copying of stack allocators: the alignment of both allocators must be the same.");

    if(this->GetSize() <= stackAllocator.GetSize() && m_alignment == stackAllocator.m_alignment)
    {
        // If the above assertion has passed the test, is assumed that the amount of allocated bytes 
        // in the resident stack allocator will be <= than the amount of allocated bytes in the passed one.

        // STEP 1) Clear the passed stack allocator.
        stackAllocator.Clear();

        // STEP 2) Set the new state for the passed stack allocator, part 1/4: Setting the basic attributes for the class: alignment
        //         value and amount of allocated bytes.
        stackAllocator.m_uAllocatedBytes = this->m_uAllocatedBytes;

        // STEP 3) Set the new state for the passed stack allocator, part 2/4: Copying the preallocated block of the resident allocator
        //         onto the passed stack allocator.
        //
        //         VERY IMPORTANT: The passed stack allocator will keep its preallocated memory block due to two main reasons:
        //                           -The size of the resident stack allocator's preallocated block will be <= than the size of the passed one
        //                            when reached this stage, so there's no chance of overwritting a memory location out of bounds.
        //                           -It cannot be determined if the passed stack allocator's preallocated block was created by itself, or was
        //                            externally assigned, so it cannot be deleted.
        //                          
        //                         SUMMARIZING: The preallocated block of the passed stack allocator is overwritten accordingly, not deleted and
        //                                    then created from scratch.
        memcpy(stackAllocator.m_pBase, this->m_pBase, this->m_uAllocatedBytes);

        // STEP 4) Set the new state for the passed stack allocator, part 3/4: Updating its Stack Top.
        pointer_uint_q uAddressTemp = rcast_q(stackAllocator.m_pBase, pointer_uint_q) + stackAllocator.m_uAllocatedBytes;
        stackAllocator.m_pTop       = rcast_q(uAddressTemp, void*);

        // STEP 5) Set the new state for the passed stack allocator, part 4/4: Updating its m_pPrevious pointer.
        /*pointer_uint_q uTempAllocBytes = 0;
        stackAllocator.m_pPrevious     = stackAllocator.m_pBase;
        void* pPreviousAddressRes      = stackAllocator.m_pBase;
        
        do
        {
            stackAllocator.m_pPrevious    = pPreviousAddressRes;
            pointer_uint_q uMemBlockSize  = scast_q(stackAllocator.m_pPrevious, QBlockHeader*)->GetAllocatedBlockSize();
            pointer_uint_q uOffset        = scast_q(stackAllocator.m_pPrevious, QBlockHeader*)->GetAlignmentOffset();
            pointer_uint_q uAddress       = rcast_q(stackAllocator.m_pPrevious, pointer_uint_q);
            pPreviousAddressRes           = rcast_q( (uAddress + sizeof(QBlockHeader) + uOffset + uMemBlockSize), void*);
            uTempAllocBytes              += (sizeof(QBlockHeader) + uOffset + uMemBlockSize);

        } while(pPreviousAddressRes < stackAllocator.m_pTop);
        */
        pointer_uint_q uBytesFromPreviousToBase = rcast_q(m_pPrevious, pointer_uint_q) - rcast_q(m_pBase, pointer_uint_q);
        stackAllocator.m_pPrevious = (void*)( (pointer_uint_q)stackAllocator.m_pBase + uBytesFromPreviousToBase );
    }
}

QStackAllocator::QMark QStackAllocator::GetMark() const
{
    QE_ASSERT(null_q != m_pTop, "Error on retrieving a mark: stack top is null.");
    return QMark(m_pTop);
}

void QStackAllocator::ClearAttributes()
{
    m_pBase = m_pTop = m_pPrevious = null_q;
    m_uSize = m_uAllocatedBytes    = 0;
}

} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
