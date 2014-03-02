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

#include "QPoolAllocator.h"
#include "AllocationOperators.h"
// To use memcpy
#include <cstring> 

#include "Assertions.h" 

using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

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


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QPoolAllocator::QPoolAllocator(const pointer_uint_q uSize, const pointer_uint_q uBlockSize, const QAlignment &alignment) :
            m_uBlockSize(uBlockSize), 
            m_uAllocatedBytes(0), 
            m_uAlignment(alignment), 
            m_uNeedDestroyMemoryChunk(1), 
            m_uPoolSize(uSize)
{
    QE_ASSERT( 0 != uSize, "Size cannot be zero"  );
    QE_ASSERT( 0 != uBlockSize, "Block size cannot be zero" );
    
    m_pAllocatedMemory = operator new(m_uPoolSize, alignment);
    QE_ASSERT( null_q != m_pAllocatedMemory, "Pointer to allocated memory is null" );

    m_pFirst = m_pAllocatedMemory;

    m_uBlocksCount = m_uPoolSize / uBlockSize;

    this->AllocateFreeBlocksList();
}

QPoolAllocator::QPoolAllocator(const pointer_uint_q uSize, const pointer_uint_q uBlockSize, const void *pBuffer) :
            m_uBlockSize(uBlockSize), 
            m_uAllocatedBytes(0), 
            m_uAlignment(QAlignment(sizeof(void**))), 
            m_uNeedDestroyMemoryChunk(0),
            m_uPoolSize(uSize)
{
    QE_ASSERT( 0 != uSize, "Size cannot be zero" );
    QE_ASSERT( 0 != uBlockSize, "Block size cannot be zero" );
    QE_ASSERT( 0 != pBuffer, "Pointer to buffer cannot be null" );
        
    // Calculates needed memory address offset (adjustment) for the chunk starts at multiple of alignment
    pointer_uint_q uAdjustment = m_uAlignment - ((pointer_uint_q)pBuffer & (m_uAlignment - 1));
    if(uAdjustment == m_uAlignment ) 
        uAdjustment = 0;

    m_pAllocatedMemory = (void**)((pointer_uint_q)pBuffer + uAdjustment);
    m_pFirst = m_pAllocatedMemory;

    m_uBlocksCount = (m_uPoolSize - uAdjustment) / uBlockSize;

    this->AllocateFreeBlocksList();
}

QPoolAllocator::QPoolAllocator(const pointer_uint_q uSize, const pointer_uint_q uBlockSize, const void *pBuffer, const QAlignment &alignment) :
            m_uBlockSize(uBlockSize), 
            m_uAllocatedBytes(0), 
            m_uAlignment(alignment), 
            m_uNeedDestroyMemoryChunk(0), 
            m_uPoolSize(uSize)
{
    QE_ASSERT( 0 != uSize, "Size cannot be zero" );
    QE_ASSERT( 0 != uBlockSize, "Block size cannot be zero" );
    QE_ASSERT( 0 != pBuffer, "Pointer to buffer cannot be null" );

    pointer_uint_q uAdjustment = alignment - ((pointer_uint_q)pBuffer & (alignment - 1));

    if(uAdjustment == alignment ) 
        uAdjustment = 0;

    m_pAllocatedMemory = (void**)((pointer_uint_q)pBuffer + uAdjustment);
    m_pFirst = m_pAllocatedMemory;

    m_uBlocksCount = (m_uPoolSize - uAdjustment) / uBlockSize;
        
    this->AllocateFreeBlocksList();
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QPoolAllocator::~QPoolAllocator()
{
    if(m_uNeedDestroyMemoryChunk != 0) 
        operator delete(m_pAllocatedMemory, m_uAlignment);

    operator delete(m_pFreeBlocks);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void* QPoolAllocator::Allocate()
{
    if( null_q == m_ppNextFreeBlock ) 
        return null_q;

    m_uAllocatedBytes += m_uBlockSize;

    // Takes the index of the next free block from the free blocks pointers list.
    pointer_uint_q uNextFreeBlockIndex = m_ppNextFreeBlock - m_pFreeBlocks;

    // Updates with the pointer to the new free block pointer.
    m_ppNextFreeBlock = (void**)*m_ppNextFreeBlock;

    // Returns pointer to the allocated block from the index taken before.
    return (void*)((pointer_uint_q)m_pFirst + uNextFreeBlockIndex * m_uBlockSize);
}

void QPoolAllocator::Deallocate(const void* pBlock)
{
    QE_ASSERT( null_q != pBlock, "Pointer to block to deallocate cannot be null" );
    QE_ASSERT( (pointer_uint_q)pBlock >= (pointer_uint_q)m_pAllocatedMemory && (pointer_uint_q)pBlock <= ((pointer_uint_q)m_pAllocatedMemory + m_uSize), "Pointer to block to deallocate must be an address provided by this pool allocator" );

    m_uAllocatedBytes -= m_uBlockSize;

    // Calculates the address in the blocks pointers list of the block to deallocate.
    // ppDeallocatedBlock = m_pFreeBlocks + Index of the block to deallocate
    void **ppDeallocatedBlock = m_pFreeBlocks + (((pointer_uint_q)pBlock - (pointer_uint_q)m_pFirst) / m_uBlockSize);

    // Inserts at the beginning of the free blocks pointers list the deallocated block.
    *ppDeallocatedBlock = m_ppNextFreeBlock;
    m_ppNextFreeBlock = (void**)ppDeallocatedBlock;
}


void QPoolAllocator::Clear()
{
    m_ppNextFreeBlock = m_pFreeBlocks;
    this->ClearFreeBlocksList();
}

void QPoolAllocator::CopyTo(QPoolAllocator &poolAllocator) const
{
    QE_ASSERT(m_uBlocksCount <= poolAllocator.m_uBlocksCount, "Blocks count of destination pool allocator must be greater or equal than the source pool allocator" );
    QE_ASSERT(m_uPoolSize <= poolAllocator.m_uPoolSize, "Chunk size for allocations must be greater or equal in the destination pool allocator than in the source pool allocator" );
    QE_ASSERT(m_uBlockSize == poolAllocator.m_uBlockSize, "Block sizes of origin and destination pool allocators must be equals");

    if(null_q == m_ppNextFreeBlock)
    {
        // No free blocks in source. Append extra destination free blocks pointers if it has more blocks count.
        if(m_uBlocksCount < poolAllocator.m_uBlocksCount)
        {
            // ppNext = first free block of remaining free blocks.
            void **ppNext = poolAllocator.m_pFreeBlocks + m_uBlocksCount;

            // Assigns the next free block in the destination pool
            poolAllocator.m_ppNextFreeBlock = ppNext;

            // Frees remaining blocks from destination redoing the rest of the list.
            for( pointer_uint_q uIndex = m_uBlocksCount; uIndex < poolAllocator.m_uBlocksCount - 1; uIndex++ )
            {
                *ppNext = (void*)((void**)ppNext + 1);
                ppNext = (void**)*ppNext;
            }

            *ppNext = null_q;
        }
        else
        {
            poolAllocator.m_ppNextFreeBlock = null_q;
        }
    }
    else
    {
        // Assigns the next free block in the destination pool (same block index as in origin).
        poolAllocator.m_ppNextFreeBlock = poolAllocator.m_pFreeBlocks + (m_ppNextFreeBlock - m_pFreeBlocks);

        // Copy free blocks pointers list from source to destination
        void **ppLastFreeBlock = m_ppNextFreeBlock;

        while( null_q != *ppLastFreeBlock )
        {
            // Index of the next free block in the source = *ppLastFreeBlock - m_pFreeBlocks
            *(poolAllocator.m_pFreeBlocks + ((void**)ppLastFreeBlock - m_pFreeBlocks)) =
                                    poolAllocator.m_pFreeBlocks + ((void**)*ppLastFreeBlock - m_pFreeBlocks);

            // ppLastFreeBlock will contain the pointer to last free block in the list or null if there are no free blocks
            // when exits from the while loop.
            if(null_q != *ppLastFreeBlock) 
                ppLastFreeBlock = (void**)*ppLastFreeBlock;
        }

        if(m_uBlocksCount < poolAllocator.m_uBlocksCount)
        {
            // Appends extra free blocks pointers of destination
            
            // Links copied free blocks list from source to remaining free blocks from destination.

            // ppNext = first free block of remaining free blocks.
            void **ppNext = poolAllocator.m_pFreeBlocks + m_uBlocksCount;

            // Links two lists.
            *(poolAllocator.m_pFreeBlocks +  (ppLastFreeBlock - m_pFreeBlocks)) = ppNext;

            // Frees the rest of blocks from destination redoing the rest of the list.
            for( pointer_uint_q uIndex = m_uBlocksCount; uIndex < poolAllocator.m_uBlocksCount - 1; uIndex++ )
            {
                *ppNext = (void*)((void**)ppNext + 1);
                ppNext = (void**)*ppNext;
            }

            *ppNext = null_q;
        }
    }

    // Copies all source blocks in destination
    memcpy(poolAllocator.m_pFirst, m_pFirst, m_uBlockSize * m_uBlocksCount);

    poolAllocator.m_uAllocatedBytes = m_uAllocatedBytes;
}

void QPoolAllocator::AllocateFreeBlocksList()
{
    m_pFreeBlocks = (void**) operator new(m_uBlocksCount * sizeof(void**));
    QE_ASSERT( null_q != m_pFreeBlocks, "Pointer to allocated memory for internals is null" );

    m_ppNextFreeBlock = m_pFreeBlocks;
    m_uSize = m_uPoolSize + m_uBlocksCount * sizeof(void**);

    this->ClearFreeBlocksList();
}

void QPoolAllocator::ClearFreeBlocksList()
{
    void **ppNext = m_pFreeBlocks;

    // Every pointer points to the next pointer as a linked list of free blocks to allocate.
    for( pointer_uint_q uIndex = 0; uIndex < m_uBlocksCount - 1; uIndex++ )
    {
        *ppNext = (void*)((void**)ppNext + 1);
        ppNext = (void**)*ppNext;
    }

    *ppNext = null_q;

    m_uAllocatedBytes = 0;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
void* QPoolAllocator::GetPointer() const
{
    return m_pFirst;
}


QAlignment QPoolAllocator::GetAlignment() const
{
    return m_uAlignment;
}

pointer_uint_q QPoolAllocator::GetTotalSize() const
{
    return m_uSize;
}

pointer_uint_q QPoolAllocator::GetPoolSize() const
{
    return m_uPoolSize;
}

bool QPoolAllocator::CanAllocate() const
{
    return null_q != m_ppNextFreeBlock;
}

pointer_uint_q QPoolAllocator::GetAllocatedBytes() const
{
    return m_uAllocatedBytes;
}


} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
