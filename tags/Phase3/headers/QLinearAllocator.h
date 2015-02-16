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

#ifndef __QLINEARALLOCATOR__
#define __QLINEARALLOCATOR__

#include "CommonDefinitions.h"
#include "DataTypesDefinitions.h"
#include "QAlignment.h"

using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{

/// <summary>
/// Represents an allocator that stores memory blocks of arbitrary sizes in a linear/contiguous way. It grows until the preallocated memory is filled and 
/// never diminishes, although it can be emptied completely.
/// </summary>
class QE_LAYER_COMMON_SYMBOLS QLinearAllocator
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Creates a linear allocator by specifying the size of its internal buffer and its alignment.
    /// </summary>
    /// <param name="uSize">[IN] The size, in bytes, of the buffer. It must be greater than zero.</param>
    /// <param name="alignment">[IN] The alignment of the memory block to be reserved.</param>
    QLinearAllocator(const pointer_uint_q uSize, const QAlignment &alignment);

    /// <summary>
    /// Creates a linear allocator by specifying an external buffer and its size.
    /// </summary>
    /// <remarks>
    /// When providing an external buffer, the user is in charge of deleting it.
    /// </remarks>
    /// <param name="uSize">[IN] The size, in bytes, of the buffer. It must be greater than zero.</param>
    /// <param name="pBuffer">[IN] The external buffer to be used to allocate memory blocks. It must not be null.</param>
    QLinearAllocator(const pointer_uint_q uSize, void* pBuffer);
    
    /// <summary>
    /// Creates a linear allocator by specifying an external buffer, its size and the desired alignment.
    /// </summary>
    /// <remarks>
    /// When providing an external buffer, the user is in charge of deleting it. If the buffer is not already aligned,
    /// an offset will be used internally, probably losing some bytes at the beginning.
    /// </remarks>
    /// <param name="uSize">[IN] The size, in bytes, of the buffer. It must be greater than zero.</param>
    /// <param name="pBuffer">[IN] The external buffer to be used to allocate memory blocks. It must not be null.</param>
    /// <param name="alignment">[IN] The alingment of the memory block.</param>
    QLinearAllocator(const pointer_uint_q uSize, void* pBuffer, const QAlignment &alignment);

private:

    // Hidden
    QLinearAllocator(const QLinearAllocator&);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor. Depending on whether the internal buffer was created by the allocator or provided by the user, it will be
    /// freed or not, respectively.
    /// </summary>
    ~QLinearAllocator();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Allocates a memory block and returns its address.
    /// </summary>
    /// <param name="uSize">[IN] The size, in bytes, of the memory block to be allocated. It must be greater than zero.</param>
    /// <returns>
    /// Pointer to the allocated memory block. Returns null if the internal buffer is full. Call CanAllocate method to know 
    /// whether the block fits into the buffer or not before allocating.
    /// </returns>
    void* Allocate(const pointer_uint_q uSize);
    
    /// <summary>
    /// Allocates a memory block, whose memory address depends on the alignment, and returns its address.
    /// </summary>
    /// <remarks>
    /// Due to the alignment adjustment, the amount of memory necessary to allocate the memory block could be bigger than expected.
    /// </remarks>
    /// <param name="uSize">[IN] The size, in bytes, of the memory block to be allocated. It must be greater than zero.</param>
    /// <param name="alignment">[IN] The alignment of the memory block.</param>
    /// <returns>
    /// Pointer to the allocated memory block. Returns null if the internal buffer is full. Call CanAllocate method to know 
    /// whether the block fits into the buffer or not before allocating.
    /// </returns>
    void* Allocate(const pointer_uint_q uSize, const QAlignment &alignment);

    /// <summary>
    /// Empties the internal buffer, deallocating everything.
    /// </summary>
    void Clear();

    /// <summary>
    /// Copies the contents of the internal buffer to another linear allocator's buffer.
    /// </summary>
    /// <remarks>
    /// The size of destination allocator's buffer must be greater than or equal to the amount of allocated bytes of the resident allocator; otherwise, 
    /// the beheavior is undefined.<br/>
    /// There is no guarantee the alignment of all the allocated blocks but the first one will be kept.
    /// </remarks>
    /// <param name="destination">[IN/OUT] The destination allocator.</param>
    void CopyTo(QLinearAllocator &destination) const;
    
    /// <summary>
    /// Moves the allocated data to a bigger buffer at a different memory address.
    /// </summary>    
    /// <remarks>
    /// The new address will be resolved by the system and will be aligned in the same way the current buffer's address is.<br/>
    /// There is no guarantee the alignment of all the allocated blocks but the first one will be kept.<br/>
    /// This method should be called only in case the allocator was created using an internal buffer.
    /// </remarks>
    /// <param name="uNewSize">[IN] The new size of the pool, in bytes. It must be greater than the current size of the pool; otherwise, no action 
    /// will be performed.</param>
    void Reallocate(const pointer_uint_q uNewSize);

    /// <summary>
    /// Moves the allocated data to a bigger memory block at a different memory address.
    /// </summary>
    /// <remarks>
    /// The buffer's memory address will be adjusted to the same alignment the resident buffer is so, if it is not already aligned, there will be some memory loss.<br/>
    /// There is no guarantee the alignment of all the allocated blocks but the first one will be kept.<br/>
    /// This method should be called only in case the allocator was created using an external buffer.
    /// </remarks>
    /// <param name="uNewSize">[IN] The new size of the pool, in bytes. It must be greater than the current size of the pool; otherwise, no action 
    /// will be performed.</param>
    /// <param name="pNewLocation">[IN] The new memory address where the new block will be reserved. It must not be null, or no reallocation will be done.</param>
    void Reallocate(const pointer_uint_q uNewSize, void* pNewLocation);

    /// <summary>
    /// Calculates whether there is enough free space in the buffer to allocate a memory block of a given size.
    /// </summary>
    /// <param name="uSize">[IN] The size, in bytes, to be checked.</param>
    /// <returns>
    /// True if there is enough free space; false otherwise.
    /// </returns>
    bool CanAllocate(const pointer_uint_q uSize) const;
    
    /// <summary>
    /// Calculates whether there is enough free space in the buffer to allocate a memory block of a given size with a given alignment.
    /// </summary>
    /// <param name="uSize">[IN] The size, in bytes, to be checked.</param>
    /// <param name="alignment">[IN] The alingment to which the memory block would be adjusted.</param>
    /// <returns>
    /// True if there is enough free space; false otherwise.
    /// </returns>
    bool CanAllocate(const pointer_uint_q uSize, const QAlignment &alignment) const;
    
private:

    // Hidden
    QLinearAllocator& operator=(const QLinearAllocator&);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the total size of the allocator's buffer.
    /// </summary>
    /// <returns>
    /// The total size of the allocator's buffer, in bytes.
    /// </returns>
    pointer_uint_q GetSize() const;

    /// <summary>
    /// Gets the number of bytes already allocated.
    /// </summary>
    /// <returns>
    /// The number of bytes already allocated, taking into account the alignment adjustments too.
    /// </returns>
    pointer_uint_q GetAllocatedBytes() const;

    /// <summary>
    /// Gets a pointer to the internal buffer.
    /// </summary>
    /// <remarks>
    /// If the allocator uses an external buffer, this pointer may not be pointing to the beginning of it. Due to alignment adjustments 
    /// (if it was necessary at the moment the allocator was created), the pointer could point to the first memory address which fit 
    /// the required alignment.
    /// </remarks>
    /// <returns>
    /// A pointer to the internal buffer where memory blocks are allocated.
    /// </returns>
    void* GetPointer() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The buffer where all the allocations are performed.
    /// </summary>
    void* m_pBase;

    /// <summary>
    /// The position of the free space in the buffer.
    /// </summary>
    void* m_pTop;

    /// <summary>
    /// The size, in bytes, of the buffer.
    /// </summary>
    pointer_uint_q m_uSize;

    /// <summary>
    /// Indicates whether the allocator was created using an internal buffer (false) or a external one (true).
    /// </summary>
    bool m_bUsesExternalBuffer;

    /// <summary>
    /// The alignment of the buffer.
    /// </summary>
    const pointer_uint_q m_uAlignment;

};

} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINEARALLOCATOR__
