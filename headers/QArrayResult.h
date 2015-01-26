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

#ifndef __QARRAYRESULT__
#define __QARRAYRESULT__

#include "CommonDefinitions.h"
#include "QBasicArray.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{
   
/// <summary>
/// A wrapper for C-style arrays that stores both, the array and the number of elements in it, intended to be used as a return type only. It also acts as a kind-of scoped smart pointer
/// so it can be attached to the array, deleting it when the destructor is called.
/// </summary>
/// <remarks>
/// When the wrapper is instanced, it is attached to the array. It can be detached afterwards when necessary.<br/>
/// There can be up to one wrapper attached to the same array, therefore copying a wrapper detaches the array from the source instance and attaches it to the destination instance.<br/>
/// This class is intended to be a usability improvement for functions that return arrays allocated in the heap.
/// </remarks>
/// <typeparam name="T">The type of the elements in the array.</typeparam>
template<class T>
class QArrayResult : public QBasicArray<T>
{
protected:

    using QBasicArray<T>::m_pArray;
    

    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the array, which is attached to the wrapper, and the number of elements in it.
    /// </summary>
    /// <remarks>
    /// If the input array is null, the wrapper will not be attached.
    /// </remarks>
    /// <param name="pArray">[IN] The array to be wrapped.</param>
    /// <param name="uCount">[IN] The number of elements in the array.</param>
    QArrayResult(T* pArray, const pointer_uint_q uCount) : QBasicArray<T>(pArray, uCount),
                                                           m_bIsAttached(pArray != null_q)
    {
    }
    
    /// <summary>
    /// Copy constructor that receives another array wrapper.
    /// </summary>
    /// <remarks>
    /// If the input wrapper is attached to the array, it will be detached. Then the array will be attached to the resident wrapper.
    /// </remarks>
    /// <param name="array">[IN] The array wrapper to be copied.</param>
    QArrayResult(const QArrayResult& array) : QBasicArray<T>(array),
                                              m_bIsAttached(array.m_bIsAttached) 
    {
        ccast_q(array, QArrayResult<T>&).Detach();
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
    ~QArrayResult()
    {
        if(m_bIsAttached)
            delete[] m_pArray;
    }


    // METHODS
    // ---------------
private:
    
    // Not allowed
    QArrayResult& operator=(const QArrayResult &array);
    
public:

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


    // PROPERTIES
    // ---------------
public:
    
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
    /// Indicates whether the array is attached to the wrapper or not.
    /// </summary>
    mutable bool m_bIsAttached;
};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QARRAYRESULT__
