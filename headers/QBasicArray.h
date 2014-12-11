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

#ifndef __QBASICARRAY__
#define __QBASICARRAY__

#include "CommonDefinitions.h"
#include <cstring>
#include "CrossPlatformBasicTypes.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{
   
/// <summary>
/// A wrapper for C-style arrays that stores both, the array and the number of elements in it. It also acts as a kind-of scoped smart pointer
/// so it can be attached to the array and delete it when the destructor is called.
/// </summary>
/// <remarks>
/// When the wrapper is instanced, it can be optionally attached to the array. It can be detached afterwards when necessary. As a rule of thumb,
/// always attach them when the instance is to be returned by a function so the client code does not have to worry about the destruction of the array.<br/>
/// There can be up to one wrapper attached to the same array, therefore copying a wrapper detaches the array from the source instance and attaches it to the destination instance.
/// </remarks>
/// <typeparam name="T">The type of the elements in the array.</typeparam>
template<class T>
class QBasicArray
{

    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the array, the number of elements in it and whether it is attached to the wrapper or not.
    /// </summary>
    /// <remarks>
    /// If the array was already attached to another wrapper, it must not be attached again until it is detached from it.<br/>
    /// If the input array is null, the wrapper will not be attached.
    /// </remarks>
    /// <param name="pArray">[IN] The array to be wrapped.</param>
    /// <param name="uCount">[IN] The number of elements in the array.</param>
    /// <param name="bAttach">[Optional][IN] Indicates whether the array will be attached to the wrapper, being deleted when the wrapper's destructor is called.
    /// It is False by default.</param>
    QBasicArray(T* pArray, const pointer_uint_q uCount, const bool bAttach=false) : m_pArray(pArray),
                                                                                    m_uCount(uCount),
                                                                                    m_bIsAttached(bAttach && pArray != null_q)
    {
    }

    /// <summary>
    /// Constructor that receives another instance and whether its array is to be attached to the wrapper or not.
    /// </summary>
    /// <remarks>
    /// If the resident wrapper is attached to the array of the input wrapper, the later will be detached from the array.<br/>
    /// If the input array is null, the resident wrapper will not be attached.
    /// </remarks>
    /// <param name="array">[IN] The array wrapper to be copied.</param>
    /// <param name="bAttach">[IN] Indicates whether the array wrapper will be attached to the array of the input wrapper. It is not possible to attach the wrapper to an array 
    /// that is not already attached to the input wrapper. Hence, if the input wrapper is detached, the value of this option will be always False.</param>
    QBasicArray(const QBasicArray& array, const bool bAttach) : m_pArray(array.m_pArray),
                                                                m_uCount(array.m_uCount),
                                                                m_bIsAttached(array.m_bIsAttached && bAttach && array.m_pArray != null_q)
    {
        if(bAttach)
            ccast_q(&array, QBasicArray<T>*)->Detach();
    }
    
    /// <summary>
    /// Copy constructor that receives another array wrapper.
    /// </summary>
    /// <remarks>
    /// If the input wrapper is attached to the array, it will be detached. Then the array will be attached to the resident wrapper.
    /// </remarks>
    /// <param name="array">[IN] The array wrapper to be copied.</param>
    QBasicArray(const QBasicArray& array) : m_pArray(array.m_pArray),
                                            m_uCount(array.m_uCount),
                                            m_bIsAttached(array.m_bIsAttached) 
    {
        ccast_q(&array, QBasicArray<T>*)->Detach();
    }
    

    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor. It destroys the wrapped array if it is attached.
    /// </summary>
    /// <remarks>
    /// The destructor of every element in the array will be called if the array is destroyed.
    /// </remarks>
    ~QBasicArray()
    {
        if(m_bIsAttached)
            this->_DestroyArray();
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Array subscript operator that returns an element of the array from a given position.
    /// </summary>
    /// <remarks>
    /// It is just a wrapper method for the operator of the wrapped array. It has been included just to make potential refactoring tasks easier.
    /// </remarks>
    /// <param name="uIndex">[IN] The position index of the element, starting at zero. It must be lower than the number of elements in the array.</param>
    /// <returns>
    /// A reference to the retrieved element.
    /// </returns>
    T& operator[](const pointer_uint_q uIndex) const
    {
        return m_pArray[uIndex];
    }
    
    /// <summary>
    /// Assignment operator that receives another array wrapper.
    /// </summary>
    /// <remarks>
    /// If the resident wrapper is attached to its array before the assignment, such array will be destroyed.<br/>
    /// If the input wrapper is attached to the array, it will be detached. Then the array will be attached to the resident wrapper.
    /// </remarks>
    /// <param name="array">[IN] The array wrapper to be copied.</param>
    /// <returns>
    /// A reference to the resident wrapper.
    /// </returns>
    QBasicArray& operator=(const QBasicArray &array)
    {
        if(&array != this)
        {
            if(m_bIsAttached)
                this->_DestroyArray();
            
            m_pArray = array.m_pArray;
            m_uCount = array.m_uCount;
            m_bIsAttached = array.m_bIsAttached;
            
            ccast_q(&array, QBasicArray<T>*)->Detach();
        }
        
        return *this;
    }
    
    /// <summary>
    /// Detaches the wrapper from the wrapped C-style array so when the destructor is called it will not destroy the array.
    /// </summary>
    /// <remarks>
    /// If the wrapper was already detached, it does nothing.
    /// </remarks>
    void Detach()
    {
        m_bIsAttached = false;
    }
    
protected:

    /// <summary>
    /// Destroys the internal array.
    /// </summary>
    void _DestroyArray()
    {
        delete[] m_pArray;
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the wrapped array.
    /// </summary>
    /// <returns>
    /// The C-style array contained in the wrapper.
    /// </returns>
    T* Get() const
    {
        return m_pArray;
    }
    
    /// <summary>
    /// Gets the number of elements in the array.
    /// </summary>
    /// <returns>
    /// The number of elements in the array.
    /// </returns>
    pointer_uint_q GetCount() const
    {
        return m_uCount;
    }
    
    /// <summary>
    /// Gets the size of the wrapped array, in bytes.
    /// </summary>
    /// <returns>
    /// The size of the array.
    /// </returns>
    pointer_uint_q GetSize() const
    {
        return m_uCount * sizeof(T);
    }
    
    /// <summary>
    /// Indicates whether the array is attached to the wrapper or not.
    /// </summary>
    /// <returns>
    /// True if the array is attached; False otherwise.
    /// </returns>
    bool IsAttached() const
    {
        return m_bIsAttached;
    }
    

    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The wrapped array.
    /// </summary>
    T* m_pArray;
    
    /// <summary>
    /// The number of elements in the array.
    /// </summary>
    pointer_uint_q m_uCount;
    
    /// <summary>
    /// Indicates whether the array is attached to the wrapper or not.
    /// </summary>
    bool m_bIsAttached;
};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASICARRAY__
