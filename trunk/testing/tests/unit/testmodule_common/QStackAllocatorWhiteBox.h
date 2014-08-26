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

#ifndef __QSTACKALLOCATORWHITEBOX__
#define __QSTACKALLOCATORWHITEBOX__


#include "QStackAllocator.h"
#include "AllocationOperators.h"
#include "QAlignmentMocked.h"


using Kinesis::QuimeraEngine::Common::Memory::QStackAllocator;
using Kinesis::QuimeraEngine::Common::Memory::Test::QAlignmentMocked;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{
namespace Test
{

/// <summary>
/// This derived class from QStackAllocator is used to expose protected methods of QStackAllocator for testing purposes.
/// </summary>
class QStackAllocatorWhiteBox : public QStackAllocator
{
    // USINGS
	// -----------------
public:

    using QStackAllocator::QBlockHeader;
    
    
    // INTERNAL CLASSES
	// -----------------

public:

    /// <summary>
    /// Represents a fake mark that can autosabotage the address that holds for testing purposes of a stack allocator.
    /// </summary>
    class QMarkMocked : public QMark
    {
    private:
        // The offset value for autosabotage the address that the mark holds to a greater or lesser value<br/>
        // than the current one.
        static const pointer_uint_q QMARKMOCKED_OFFSET_VALUE;

        // CONSTRUCTORS
	    // ---------------
    public:

        explicit inline QMarkMocked(void* pMemAddress) : QMark(pMemAddress)
        { }


        // METHODS
	    // ---------------
    public:

        // Set the address to null.
        void SabotageMarkToNull();

        // Sets the address to a lesser value than the current one.
        void SabotageMarkToLesserMemoryAddress();

         // Sets the address to a greater value than the current one.
        void SabotageMarkToGreaterMemoryAddress();

    }; // --- QMarkMocked ---


	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	explicit QStackAllocatorWhiteBox(const pointer_uint_q uPreallocationSize) : QStackAllocator(uPreallocationSize)
    {
    }

    // Necessary for testing
    QStackAllocatorWhiteBox(const pointer_uint_q uPreallocationSize, const QAlignment& alignment) : QStackAllocator(uPreallocationSize, alignment)
    {
    }

    // Necessary for testing
    QStackAllocatorWhiteBox(const pointer_uint_q uPreallocationSize, void* pMemAddress) : QStackAllocator(uPreallocationSize, pMemAddress)
    {
    }

    // Necessary for testing
    QStackAllocatorWhiteBox(const pointer_uint_q uPreallocationSize, void* pMemAddress, const QAlignment& alignment) : QStackAllocator(uPreallocationSize, pMemAddress, alignment)
    {
    }


	// METHODS
	// ---------------

public:
    
    QAlignment operator =(const QAlignmentMocked& mocked)
    {
        pointer_uint_q uValue = mocked;
        QAlignment align(uValue);
        return align;
    }

    // Exposed member.
    void* GetpBase() const
    {
        return m_pBase;
    }

    // Exposed member.
    QAlignment GetAlignmentValue() const
    {
        return m_alignment;
    }

    // Exposed member.
    void* GetpPrevious() const
    {
        return m_pPrevious;
    }

    // Exposed member.
    // This member will NOT modify the preallocated block in the resident stack allocator,
    // is just for testing.
    void* PreallocatePublic (const pointer_uint_q uPreallocationSize,
                             const QAlignment& alignment)
    {
        return this->Preallocate(uPreallocationSize, alignment);
    }

    // Exposed member.
    void SetuAllocatedBytes(const pointer_uint_q uAllocatedBytes)
    {
        m_uAllocatedBytes = uAllocatedBytes;
    }

    // Enable or disable the deletion of the preallocated block. If disabled, this one must be deleted
    // externally in order to avoid a huge memory leak.
    void SetDeletePreallocatedBlock(const bool bDeletePreallocatedBlock)
    {
        m_bDeletePreallocatedBlock = bDeletePreallocatedBlock;
    }

    // Sabotages a StackAllocator correctly created as if it was not be created properly.
    void SabotageStackAllocator()
    {
        QStackAllocator::Finalize();
        this->Finalize();
    }

    // This method returns the starting address of the allocated memory block placed at the top of the stack.
    void* GetMemoryBlockStart()
    {
        pointer_uint_q uBaseAddress = rcast_q(m_pPrevious, pointer_uint_q);
        uBaseAddress += ( sizeof(QBlockHeader) + (scast_q(m_pPrevious, QBlockHeader*)->GetAlignmentOffset()) );
        return rcast_q(uBaseAddress, void*);
    }
};

} //namespace Test
} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSTACKALLOCATORWHITEBOX__
