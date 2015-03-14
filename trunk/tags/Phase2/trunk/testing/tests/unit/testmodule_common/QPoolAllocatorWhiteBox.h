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

#ifndef __QPOOLALLOCATORWHITEBOX__
#define __QPOOLALLOCATORWHITEBOX__

#include "QPoolAllocator.h"

using Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator;

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
/// Class to be used to expose protected methods of QPoolAllocator for testing purposes.
/// </summary>

class QPoolAllocatorWhiteBox : public QPoolAllocator
{
	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	QPoolAllocatorWhiteBox(pointer_uint_q uSize, pointer_uint_q uBlockSize, QAlignment alignment) :
        QPoolAllocator(uSize, uBlockSize, alignment)
    {
    }

    // Necessary for testing
    QPoolAllocatorWhiteBox(pointer_uint_q uSize, pointer_uint_q uBlockSize, void *pBuffer) :
        QPoolAllocator(uSize, uBlockSize, pBuffer)
    {
    }

    // Necessary for testing
    QPoolAllocatorWhiteBox(pointer_uint_q uSize, pointer_uint_q uBlockSize, void *pBuffer, QAlignment alignment) :
        QPoolAllocator(uSize, uBlockSize, pBuffer, alignment )
    {
    }
	// METHODS
	// ---------------
public:

    // Exposed member.
    void* GetpAllocatedMemory()
    {
        return m_pAllocatedMemory;
    }

    // Exposed member.
    void* GetpFirst() 
    {
        return m_pFirst;
    }

    // Exposed member.
    pointer_uint_q GetSize() 
    {
        return m_uSize;
    }

    // Returns address of the block in the passed position.
    void* GetpBlock(pointer_uint_q uBlockIndex)
    {
        return (void*)((pointer_uint_q)m_pFirst + uBlockIndex*m_uBlockSize);
    }
};

} //namespace Test
} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QPOOLALLOCATORWHITEBOX__
