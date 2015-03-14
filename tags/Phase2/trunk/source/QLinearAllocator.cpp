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

#include "QLinearAllocator.h"

#include "Assertions.h"
#include "AllocationOperators.h"
#include <cstring>

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################



//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QLinearAllocator::QLinearAllocator(const pointer_uint_q uSize, const QAlignment &alignment) : 
                                                                 m_uSize(uSize),
                                                                 m_bUsesExternalBuffer(false),
                                                                 m_uAlignment(alignment)
{
    QE_ASSERT_ERROR(uSize > 0, "The size of the buffer cannot be zero.");

    m_pBase = ::operator new(uSize, alignment);
    m_pTop = m_pBase;
}

QLinearAllocator::QLinearAllocator(const pointer_uint_q uSize, void* pBuffer) : m_pBase(pBuffer),
                                                                                m_pTop(pBuffer),
                                                                                m_uSize(uSize),
                                                                                m_bUsesExternalBuffer(true),
                                                                                m_uAlignment(1U)
{
    QE_ASSERT_ERROR(uSize > 0, "The size of the buffer cannot be zero.");
    QE_ASSERT_ERROR(pBuffer != null_q, "The pointer to the external buffer cannot be null.");
}
    
QLinearAllocator::QLinearAllocator(const pointer_uint_q uSize, void* pBuffer, const QAlignment &alignment) : 
                                                                                m_pBase(pBuffer),
                                                                                m_pTop(pBuffer),
                                                                                m_uSize(uSize),
                                                                                m_bUsesExternalBuffer(true),
                                                                                m_uAlignment(alignment)
{
    QE_ASSERT_ERROR(uSize > 0, "The size of the buffer cannot be zero.");
    QE_ASSERT_ERROR(pBuffer != null_q, "The pointer to the external buffer cannot be null.");

    pointer_uint_q uAdjustment = m_uAlignment - ((pointer_uint_q)m_pBase & (m_uAlignment - 1U));

    // Changes the base pointer to the first memory address that is aligned as intended
    if(uAdjustment != m_uAlignment)
    {
        m_pBase = (void*)((pointer_uint_q)m_pBase + uAdjustment);
        m_pTop = m_pBase;
        m_uSize -= uAdjustment; // Some free space is lost
    }
}
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QLinearAllocator::~QLinearAllocator()
{
    if(!m_bUsesExternalBuffer)
        ::operator delete(m_pBase, QAlignment(m_uAlignment));
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void* QLinearAllocator::Allocate(const pointer_uint_q uSize)
{
    QE_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");
    QE_ASSERT_WARNING(this->CanAllocate(uSize), "The size of the memory block to be allocated does not fit in the available free space.");

    void* pAllocatedMemory = null_q;
    
    if(this->CanAllocate(uSize))
    {
        pAllocatedMemory = m_pTop;
        m_pTop = (void*)((pointer_uint_q)m_pTop + uSize);
    }

    return pAllocatedMemory;
}

void* QLinearAllocator::Allocate(const pointer_uint_q uSize, const QAlignment &alignment)
{
    QE_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");
    QE_ASSERT_WARNING(this->CanAllocate(uSize, alignment), "The size of the memory block to be allocated (plus the alignment adjustment) does not fit in the available free space.");

    void* pAllocatedMemory = null_q;

    if(this->CanAllocate(uSize, alignment))
    {
        pointer_uint_q uAdjustment = alignment - ((pointer_uint_q)m_pTop & (alignment - 1U));

        if(uAdjustment == alignment)
            uAdjustment = 0;

        pAllocatedMemory = (void*)((pointer_uint_q)m_pTop + uAdjustment);
        m_pTop = (void*)((pointer_uint_q)m_pTop + uSize + uAdjustment);
    }

    return pAllocatedMemory;
}

void QLinearAllocator::Clear()
{
    m_pTop = m_pBase;
}

void QLinearAllocator::CopyTo(QLinearAllocator &destination) const
{
    QE_ASSERT_ERROR(destination.GetSize() >= this->GetAllocatedBytes(), "The input allocator's size must be greater than or equal to the size of the allocated bytes in the resident allocator.");
    QE_ASSERT_WARNING(destination.m_uAlignment == m_uAlignment, "The alignment of the input allocator is different from the resident allocator's.");

    const pointer_uint_q BYTES_TO_COPY = this->GetAllocatedBytes();

    memcpy(destination.m_pBase, m_pBase, BYTES_TO_COPY);

    destination.m_pTop = (void*)((pointer_uint_q)destination.m_pBase + BYTES_TO_COPY);
}

void QLinearAllocator::Reallocate(const pointer_uint_q uNewSize)
{
    QE_ASSERT_ERROR(!m_bUsesExternalBuffer, "This allocator uses an external buffer so internal reallocation is not possible");
    QE_ASSERT_WARNING(uNewSize > m_uSize, "The new size must be greater than the current size");

    if(uNewSize > m_uSize)
    {
        const pointer_uint_q BYTES_TO_COPY = this->GetAllocatedBytes();

        void* pNewBuffer = ::operator new(uNewSize, QAlignment(m_uAlignment));
        memcpy(pNewBuffer, m_pBase, BYTES_TO_COPY);
        ::operator delete(m_pBase, QAlignment(m_uAlignment));
        m_pBase = pNewBuffer;
        m_pTop = (void*)((pointer_uint_q)m_pBase + BYTES_TO_COPY);
        m_uSize = uNewSize;
    }
}

void QLinearAllocator::Reallocate(const pointer_uint_q uNewSize, void* pNewLocation)
{
    QE_ASSERT_ERROR(m_bUsesExternalBuffer, "This allocator uses an internal buffer so external reallocation is not possible");
    QE_ASSERT_ERROR(pNewLocation != null_q, "The pointer to the new buffer cannot be null");
    QE_ASSERT_WARNING(uNewSize > m_uSize, "The new size must be greater than the current size");

    if(uNewSize > m_uSize)
    {
        pointer_uint_q uAdjustment = m_uAlignment - ((pointer_uint_q)pNewLocation & (m_uAlignment - 1U));

        if(uAdjustment == m_uAlignment)
            uAdjustment = 0;

        const pointer_uint_q ADJUSTED_SIZE = uNewSize - uAdjustment;
        QE_ASSERT_WARNING(ADJUSTED_SIZE > m_uSize, "Due to the alignment adjustment, there is not enough space in the new buffer to allocate the data to be moved");

        if(ADJUSTED_SIZE > m_uSize)
        {
            const pointer_uint_q BYTES_TO_COPY = this->GetAllocatedBytes();
            void* pAdjustedLocation = (void*)((pointer_uint_q)pNewLocation + uAdjustment);
            memcpy(pAdjustedLocation, m_pBase, BYTES_TO_COPY);

            // Changes the base pointer to the first memory address that is aligned as intended
            m_pBase = pAdjustedLocation;
            m_pTop = (void*)((pointer_uint_q)m_pBase + BYTES_TO_COPY);
            m_uSize = ADJUSTED_SIZE; // Some free space may be lost
        }
    }
}

bool QLinearAllocator::CanAllocate(const pointer_uint_q uSize) const
{
    QE_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");

    return m_uSize - this->GetAllocatedBytes() >= uSize;
}

bool QLinearAllocator::CanAllocate(const pointer_uint_q uSize, const QAlignment &alignment) const
{
    QE_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");

    pointer_uint_q uAdjustment = alignment - ((pointer_uint_q)m_pTop & (alignment - 1U));

    if(uAdjustment == alignment)
        uAdjustment = 0;

    return m_uSize - this->GetAllocatedBytes() >= uSize + uAdjustment;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

pointer_uint_q QLinearAllocator::GetSize() const
{
    return m_uSize;
}

pointer_uint_q QLinearAllocator::GetAllocatedBytes() const
{
    return (pointer_uint_q)m_pTop - (pointer_uint_q)m_pBase;
}

void* QLinearAllocator::GetPointer() const
{
    return m_pBase;
}


} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
