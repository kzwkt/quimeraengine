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
#include "AllocationOperators.h"    // Overloaded operators new, new[], delete and delete[]
#include "Assertions.h"             // QE_ASSERT


using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
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

        m_pTop = m_pPrevious = m_pBase;
        m_uSize              = uPreallocationSize;
}

QStackAllocator::QStackAllocator(const pointer_uint_q uPreallocationSize, const QAlignment& alignment) : m_alignment(alignment)
{
    // In this case, the preallocated block has to be deleted by the stack allocator.
    m_bDeletePreallocatedBlock = true;

    this->ClearAttributes();

    pointer_uint_q uAlignment = alignment;

    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    QE_ASSERT( !(0 == uAlignment) && !(uAlignment & (uAlignment - 1)) , "The given alignment value for preallocation must be a power of two.");

    m_pBase = this->Preallocate(uPreallocationSize, alignment);
    QE_ASSERT(null_q != m_pBase, "Error during preallocation, stack base remains as null.");

    m_pTop = m_pPrevious = m_pBase;
    m_uSize              = uPreallocationSize;
}

QStackAllocator::QStackAllocator(const pointer_uint_q uPreallocationSize, void* pMemAddress) : m_alignment(ALIGNMENT_VALUE_DEFAULT)
{
    // In this case, the preallocated block has NOT to be deleted by the stack allocator (it will be done so externally
    // by the entity which passed it).
    m_bDeletePreallocatedBlock = false;

    this->ClearAttributes();

    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    QE_ASSERT(null_q != pMemAddress, "The the input pointer to a preallocated memory block cannot be null.");

    // VERY IMPORTANT: there is no way to prove pMemAddress points to the start of a real allocated memory block.
    m_pBase              = pMemAddress;
    m_pTop = m_pPrevious = m_pBase;
    m_uSize              = uPreallocationSize;
}

QStackAllocator::QStackAllocator(const pointer_uint_q uPreallocationSize, void* pMemAddress, const QAlignment& alignment) : m_alignment(alignment)
{
    // In this case, the preallocated block has NOT to be deleted by the stack allocator (it will be done so externally
    // by the entity which passed it).
    m_bDeletePreallocatedBlock = false;

    this->ClearAttributes();

    pointer_uint_q uAlignment = alignment;

    QE_ASSERT(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    QE_ASSERT(null_q != pMemAddress, "Error while trying to assign an external preallocated memory block, stack base remains as null.");
    QE_ASSERT( !(0 == uAlignment) && !(uAlignment & (uAlignment - 1)) , "The given alignment value for preallocation must be a power of two.");

    // VERY IMPORTANT: there is no way to prove pMemAddress points to the start of a real allocated memory block.
    m_pBase = pMemAddress;
        
    // If necessary, adjust the address of the stack base to make it to point to the first address, starting from
    // the input address, that has the given alignment.
    pointer_uint_q  uAmountMisalignedBytes = (rcast_q(m_pBase, pointer_uint_q)) & (uAlignment - 1);
    if (uAmountMisalignedBytes > 0)
    {
        pointer_uint_q  uAddressResult         = (rcast_q(m_pBase, pointer_uint_q)) + uAmountMisalignedBytes;
        m_pBase                                = rcast_q(uAddressResult, void*);
    }

    m_pTop = m_pPrevious = m_pBase;
    m_uSize              = uPreallocationSize;
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
    this->Finalize();
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
    pointer_uint_q uAlignment = alignment;
    QE_ASSERT( !(0 == uAlignment) && !(uAlignment & (uAlignment - 1)) , "The given alignment value for preallocation must be a power of two.");

    // If something goes wrong (and the block cannot be allocated) a null pointer is returned.
    void* pPreallocatedRes    = new (alignment) u8_q[uPreallocationSize];
    QE_ASSERT(null_q != pPreallocatedRes, "Error: couldn't preallocate the asked memory block.");

    return pPreallocatedRes;
}


void QStackAllocator::Finalize()
{  
    // STEP 1) Clear the stack
    this->Clear();

    if (null_q != m_pBase)
    {
        // STEP 2) Deallocate the preallocated memory block if it has to be made.
        if (true == m_bDeletePreallocatedBlock)
        {
            operator delete[](m_pBase, m_alignment);
        }

        // STEP 3) Set the attributes to a default value.
        this->ClearAttributes();
    }
}


void* QStackAllocator::Allocate(const pointer_uint_q uSize)
{
    return this->Allocate( uSize, QAlignment(ALIGNMENT_VALUE_DEFAULT) );
}

void* QStackAllocator::Allocate(const pointer_uint_q uSize, const QAlignment& alignment)
{
    void* pAllocBlock                              = null_q;
    QE_ASSERT(uSize > 0, "The given size for the memory block to allocate cannot be zero.");
    pointer_uint_q uAlignment                      = alignment;
    QE_ASSERT( !(0 == uAlignment) && !(uAlignment & (uAlignment - 1)) ,
               "The given alignment value for allocation must be a power of two.");
    QE_ASSERT(true == this->CanAllocate(uSize, alignment),
              "Error: allocation cannot be accomplished, currently there's not enough space to allocate a memory block \
              with such size.");


    // STEP 1) Prerrequisites.

    void* pAux                             = m_pPrevious;
    m_pPrevious                            = m_pTop;


    // STEP 2) Compute the alignment offset, if it proceeds.
    pointer_uint_q  uAmountMisalignedBytes = ((rcast_q(m_pTop, pointer_uint_q)) + sizeof(QBlockHeader)) & (uAlignment - 1);


    // STEP 3) Create a Block Header.
    //         (** using the so-called 'placement new operator' **).
    QBlockHeader*   pBlockHeader           = new (m_pTop) QBlockHeader(uSize, uAmountMisalignedBytes, (m_pTop == m_pBase) ? 0 : ( (scast_q(pAux,QBlockHeader*)->GetAllocatedBlockSize())
                                                                                                                                    + (scast_q(pAux,QBlockHeader*)->GetAlignmentOffset())
                                                                                                                                    + sizeof(QBlockHeader)
                                                                                                                                )
                                                                      );
    QE_ASSERT(null_q != pBlockHeader, "Error while allocation: Could not allocate the block header for the me");


    // STEP 4) Insert the block Header into the stack allocator and update the stack top.

    pointer_uint_q uTopAddres              = rcast_q(m_pTop, pointer_uint_q);
    pointer_uint_q uInc                    = uTopAddres + sizeof(QBlockHeader) + uAmountMisalignedBytes;
    m_pTop                                 = rcast_q(uInc, void*);


    // STEP 5) Allocate the block.

    pAllocBlock                            = m_pTop;
    uTopAddres                             = rcast_q(m_pTop, pointer_uint_q);
    uInc                                   = uTopAddres + uSize;
    m_pTop                                 = rcast_q(uInc,void*);


    // STEP 6) Update the current size (in bytes) of occupied size in the stack allocator,
    //         counting on the size of the Block Header as well.
    m_uAllocatedBytes                     += (sizeof(QBlockHeader) + uAmountMisalignedBytes + uSize);


    // STEP 7) Return the pointer to the block header.
    return pAllocBlock;
}


void QStackAllocator::Deallocate()
{
    QE_ASSERT(this->GetAllocatedBytes() > 0, "Error trying to deallocate: stack allocator is empty.");
    
    // STEP 1) Compute the Previous header.

    pointer_uint_q uBackOffset          = scast_q(m_pPrevious,QBlockHeader*)->GetPreviousHeaderBackOffset();
    pointer_uint_q uPointerDecremented  = rcast_q(m_pPrevious,pointer_uint_q) - uBackOffset;
    void*          pPreviousBlockHeader = rcast_q(uPointerDecremented, void*);

    if (null_q == pPreviousBlockHeader)
    {
        pPreviousBlockHeader   = m_pBase;
    }


    // STEP 2) Compute the deallocation.

    m_pTop                     = m_pPrevious;
    m_pPrevious                = pPreviousBlockHeader;


    // STEP 3) Update the current size (in bytes) of occupied size in the stack allocator.

    m_uAllocatedBytes -= (  scast_q(m_pTop, QBlockHeader*)->GetAllocatedBlockSize()
                          + scast_q(m_pTop, QBlockHeader*)->GetAlignmentOffset()
                          + sizeof(QBlockHeader) );
    QE_ASSERT(m_uAllocatedBytes >= 0,
              "Error while updating the amount of allocated bytes after deallcoation, computed size is now negative.");
}

void QStackAllocator::Deallocate(const QStackAllocator::QMark& mark)
{
    QE_ASSERT(this->GetAllocatedBytes() > 0, "Error trying to deallocate: stack allocator is empty.");

    void* pMarkAddress = mark.GetMemoryAddress();
    QE_ASSERT(null_q != pMarkAddress,  "The given mark address cannot be null.");
    QE_ASSERT(pMarkAddress >= m_pBase, "Error: mark out of range --> lesser than stack base.");
    QE_ASSERT(pMarkAddress <= m_pTop,  "Error: mark out of range --> greater than current stack top.");

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
   
    // Now 'm_pPrevious' is pointing to block header regarding to the memory block that now is considered the one
    // placed in the top of the stack.
    //
    // And 'uTempAllocBytes' has the value representing the deallocated amount of bytes of the "freed" space.

    // STEP 2) Update the stack top.
    m_pTop = pMarkAddress;

    // Now 'm_pTop' is pointing to the start of the considered "free space" in the stack (everything stored in higher memory
    // addresses into the preallocated memory block is considered as released/deleted).
    
    // STEP 3) Update the amount of allocated bytes.
    m_uAllocatedBytes -= uAcumDecrementOfAllocatedBytes;
}


bool QStackAllocator::CanAllocate(const pointer_uint_q uSize) const
{
    QE_ASSERT(uSize > 0, "The size of the intended memory block to be allocated cannot be zero.");

    if (uSize > 0)
    {
        // Free space in the preallocated block...: m_uSize - m_uAllocatedBytes
        // Space occupied by the new block........:   uSize + sizeof(QBlockHeader)  <-- there's no misaligned bytes since the default alignment is 1.

        pointer_uint_q uFreeSpaceInPreallocatedBlock  = m_uSize - m_uAllocatedBytes;
        pointer_uint_q uSpaceOccupiedByNewMemoryBlock =   uSize + (sizeof(QBlockHeader));

        return uFreeSpaceInPreallocatedBlock >= uSpaceOccupiedByNewMemoryBlock;
    }

    return false;
}

bool QStackAllocator::CanAllocate(const pointer_uint_q uSize, const QAlignment& alignment) const
{
    QE_ASSERT(uSize > 0, "The given size for the intended memory block to be allocated cannot be zero.");
    pointer_uint_q uAlignment = alignment;
    QE_ASSERT( !(0 == uAlignment) && !(uAlignment & (uAlignment - 1)) , "The given alignment value must be a power of two.");

    if (uSize > 0)
    {
        // Free space in the preallocated block...: m_uSize - m_uAllocatedBytes
        // Space occupied by the new block........:   uSize + sizeof(QBlockHeader) + OffsetToAlign(NewBlock)

        pointer_uint_q  uOffsetToAlign                 = ((rcast_q(m_pTop, pointer_uint_q)) + sizeof(QBlockHeader)) & (uAlignment - 1);
        pointer_uint_q  uFreeSpaceInPreallocatedBlock  = m_uSize - m_uAllocatedBytes;
        pointer_uint_q  uSpaceOccupiedByNewMemoryBlock =   uSize + (sizeof(QBlockHeader)) + uOffsetToAlign;

        return uFreeSpaceInPreallocatedBlock >= uSpaceOccupiedByNewMemoryBlock;
    }

    return false;
}

void QStackAllocator::CopyTo(QStackAllocator& stackAllocator) const
{
    QE_ASSERT( (this->GetSize() > 0) && (stackAllocator.GetSize() > 0), "Error on copying of stack allocators: the size of both stack allocators cannot be zero.");
    QE_ASSERT(this->GetSize() <= stackAllocator.GetSize(), "Error on copying of stack allocators: the size of the passed stack allocator cannot be lower than the size of the resident one.");

    // If the above assertion has passed the test, is assumed that the amount of allocated bytes 
    // in the resident stack allocator will be <= than the amount of allocated bytes in the passed one.

    // STEP 1) Clear the passed stack allocator.
    stackAllocator.Clear();

    // STEP 2) Set the new state for the passed stack allocator, part 1/4: Setting the basic attributes for the class: alignment
    //         value and amount of allocated bytes.
    stackAllocator.m_alignment        = this->m_alignment;
    stackAllocator.m_uAllocatedBytes  = this->m_uAllocatedBytes;

    // STEP 3) Set the new state for the passed stack allocator, part 2/4: Copying the preallocated block of the resident allocator
    //         onto the passed stack allocator.
    //
    //         VERY IMPORTANT: The passed stack allocator will keep its preallocated memory block due to two main reasons:
    //                           -The size of the resident stack allocator's preallocated block will be <= than the size of the passed one
    //                            when reached this stage, so there's no chance of overwritting a memory location out of bounds.
    //                           -It cannot be determined if the passed stack allocator's preallocated block was created by itself, or was
    //                            externally assigned, so it cannot be deleted.
    //                          
    //                         IN RESUME: The preallocated block of the passed stack allocator is overwritten accordingly, not deleted and
    //                                    then created from scratch.
    memcpy(stackAllocator.m_pBase, this->m_pBase, this->m_uAllocatedBytes);

    // STEP 4) Set the new state for the passed stack allocator, part 3/4: Updating its Stack Top.
    pointer_uint_q uAddressTemp       = rcast_q(stackAllocator.m_pBase, pointer_uint_q) + stackAllocator.m_uAllocatedBytes;
    void* pTopAdressRes               = rcast_q(uAddressTemp, void*);
    stackAllocator.m_pTop             = pTopAdressRes;

    // STEP 5) Set the new state for the passed stack allocator, part 4/4: Updating its m_pPrevious pointer.
    pointer_uint_q uTempAllocBytes    = 0;
    stackAllocator.m_pPrevious        = stackAllocator.m_pBase;
    void* pPreviousAddressRes         = stackAllocator.m_pBase;
    do
    {
        stackAllocator.m_pPrevious    = pPreviousAddressRes;
        pointer_uint_q uMemBlockSize  = scast_q(stackAllocator.m_pPrevious, QBlockHeader*)->GetAllocatedBlockSize();
        pointer_uint_q uOffset        = scast_q(stackAllocator.m_pPrevious, QBlockHeader*)->GetAlignmentOffset();
        pointer_uint_q uAddress       = rcast_q(stackAllocator.m_pPrevious, pointer_uint_q);
        pPreviousAddressRes           = rcast_q( (uAddress + sizeof(QBlockHeader) + uOffset + uMemBlockSize), void*);
        uTempAllocBytes              += (sizeof(QBlockHeader) + uOffset + uMemBlockSize);
    } while(pPreviousAddressRes < stackAllocator.m_pTop);

    // STEP 6) Validate or invalidate the stack allocator if checks are successful.

    QE_ASSERT(pPreviousAddressRes == stackAllocator.m_pTop,
    "Error while updating the pointer to the current memory block allocated in the stack, temp pointer differs from the expected value address.");
    QE_ASSERT(uTempAllocBytes     == stackAllocator.m_uAllocatedBytes,
    "Error while updating the pointer to the current memory block allocated in the stack, accumulated amount of allocated bytes differs from the expected value.");
}

} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
