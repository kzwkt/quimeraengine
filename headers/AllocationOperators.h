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

#ifndef __ALLOCATIONOPERATORS__
#define __ALLOCATIONOPERATORS__

#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"
#include "QAlignment.h"

#ifdef QE_COMPILER_GCC
    #include "malloc.h" // __mingw_aligned_malloc, __mingw_aligned_free
                        // [REVIEW]: __mingw_aligned_alloc and __mingw_aligned_free may be unsafe, and break the code
                        //           after time; there must be replaced by two stable and standard functions compatible
                        //           as well with MinGW.
#endif


using Kinesis::QuimeraEngine::Common::Memory::QAlignment;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


/// <summary>
/// Aligned deallocation wrapper function, for using the allocation function provided for operative system and compiler.
/// </summary>
/// <remarks>
/// The behaviour of this function may vary depending on operative system and compiler if data alignment value, being a power of two, is either a power of sizeof(void*) as well or not:<br/>
/// <br/><br/>
/// <br/><B>MSVC:</B> It's not necessary to be a power of sizeof(void*), but to be a power of two is still mandatory.<br/>
/// <br/><B>MinGW, GCC:</B> If data alignment value is not a power of sizeof(void*) as well, the function will fix this issue automatically,
/// setting the alignment to sizeof(void*) if the entry one is lesser than it.<br/>
/// </remarks>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated (in C++, this value will always at least 1).</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two).</param>
/// <returns>
/// An aligned memory block of the specified type.
/// </returns>
inline void* aligned_alloc_q (const pointer_uint_q& uSize, const QAlignment& alignment)
{
    void* pMemoryBlock = null_q;

#ifdef QE_OS_WINDOWS
    #ifdef QE_COMPILER_MSVC
        pMemoryBlock = _aligned_malloc(uSize, alignment);
    #elif  QE_COMPILER_GC
        // __mingw_alligned_alloc will internally set the alignment to sizeof(void*) if the entry one is lesser than it.
        // 
        // [REVIEW]: __mingw_aligned_alloc may be unsafe, and break the code after time;
        //           there must be replaced with two stable and standard functions compatible
        //           as well with MinGW.
        pMemoryBlock = __mingw_aligned_malloc(uSize, alignment);
    #endif
#elif  defined (QE_OS_LINUX)
    #ifdef QE_COMPILER_GCC
        // __posix_memalign will return an error message and the allocation operation will be cancelled if the alignment value is not a power of sizeof(void*),
        // so if the entry one is lesser than it, it must be set to sizeof(void*)
        QAlignment algAux( (alignment < (sizeof(void*))) ? sizeof(void*) : alignment );

        // posix_memalign won't alter the pointer value if something goes wrong,
        // so the pointer will remain to a null value.
        posix_memalign(&pMemoryBlock, algAux, uSize);
    #endif
#endif

    return pMemoryBlock;
}

/// <summary>
/// Aligned deallocation wrapper function for using the deallocation function provided for operative system and compiler.
/// </summary>
/// <remarks>
/// The memory block has to be allocated using the corresponding allocation wrapper function, or undefined bahaviour (such as heap corruption assertion) may occur.
/// </remarks>
/// <param name="pMemoryBlock">[IN] Pointer to the aligned memory block to be deallocated.</param>
#ifdef QE_OS_WINDOWS
    #ifdef QE_COMPILER_MSVC
        #define aligned_free_q(pMemoryBlock)                    _aligned_free(pMemoryBlock)
    #elif QE_COMPILER_GCC
        // [REVIEW]: __mingw_aligned_alloc and __mingw_aligned_free may be unsafe, and break the code
        //           after time; there must be replaced with two stable and standard functions compatible
        //           as well with MinGW.
        #define aligned_free_q(pMemoryBlock)                    __mingw_aligned_free(pMemoryBlock)
    #endif
#elif defined(QE_OS_LINUX)
    #ifdef QE_COMPILER_GCC
        #define aligned_free_q(pMemoryBlock)                    free(pMemoryBlock)
    #endif
#endif


/// <summary>
/// Overload for new operator to get dynamic allocation of aligned memory blocks.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated (in C++, this value will always at least 1).</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two). Please refer to the documentation of <B>alignment_alloq_q</B> for further information about the specifications of the date alignment value.</param>
/// <returns>
/// An aligned memory block of the specified type when calling to the operator.
/// </returns>
QE_LAYER_COMMON_SYMBOLS void* operator new      (const pointer_uint_q uSize, const QAlignment& alignment);

/// <summary>
/// Overload for new[] operator to get dynamic allocation of aligned memory blocks.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the whole memory block to be allocated (in C++, this value will always at least 1).</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two). Please refer to the documentation of <B>alignment_alloq_q</B> for further information about the specifications of the date alignment value.</param>
/// <returns>
/// An aligned memory block of the specified amount of the specified type when calling to the operator, grouped as an array of the specified amount of elements.
/// </returns>
QE_LAYER_COMMON_SYMBOLS void* operator new[]    (const pointer_uint_q uSize, const QAlignment& alignment);

/// <summary>
/// Overload for delete operator to get dynamic deallocation of aligned memory blocks.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the aligned memory block to be deallocated.</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two).</param>
QE_LAYER_COMMON_SYMBOLS void operator delete    (void* pMemoryBlock, const QAlignment& alignment);

/// <summary>
/// Overload for delete[] operator to get dynamic deallocation aligned memory blocks, grouped as arrays.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the first aligned memory block of the whole to be deallocated.</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two).</param>
QE_LAYER_COMMON_SYMBOLS void operator delete[]  (void* pMemoryBlock, const QAlignment& alignment);

#endif // __ALLOCATIONOPERATORS__
