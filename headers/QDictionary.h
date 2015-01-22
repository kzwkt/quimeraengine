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

#ifndef __QDICTIONARY__
#define __QDICTIONARY__

#include "ToolsDefinitions.h"
#include "SQComparatorDefault.h"
#include "QPoolAllocator.h"
#include "QKeyValuePair.h"
#include "QBinarySearchTree.h"
#include "SQKeyValuePairComparator.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{


/// <summary>
/// Represents a data structure that stores pairs composed of a value and its associated key which must be unique in the container. 
/// </summary>
/// <remarks>
/// Key and value types are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If SQComparatorDefault is used as key comparator, keys will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="KeyT">The type of the keys associated to every value.</typeparam>
/// <typeparam name="ValueT">The type of the values.</typeparam>
/// <typeparam name="AllocatorT">The allocator used to reserve memory. The default type is QPoolAllocator.</typeparam>
/// <typeparam name="KeyComparatorT">The type of comparator utilized to compare keys. The default type is SQComparatorDefault.</typeparam>
template<class KeyT, class ValueT, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class KeyComparatorT = SQComparatorDefault<KeyT> >
class QDictionary
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QDictionary()
    {
    }

    /// <summary>
    /// Constructor that receives the initial capacity.
    /// </summary>
    /// <param name="uInitialCapacity">[IN] The number of key-value pairs for which to reserve memory. It must be greater than zero.</param>
    explicit QDictionary(const pointer_uint_q uInitialCapacity) : m_binaryTree(uInitialCapacity)
    {
    }
    
    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every key and value, in an arbitrary order.
    /// </remarks>
    /// <param name="dictionary">[IN] The other dictionary to be copied.</param>
    QDictionary(const QDictionary &dictionary) : m_binaryTree(dictionary.m_binaryTree)
    {
    }


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every key and value will be called in an undetermined order.
    /// </remarks>
    ~QDictionary()
    {
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Assignment operator that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// All the elements in the resident dictionary will be firstly removed, calling each keys's and value's destructor.
    /// The copy constructor is then called for every copied key and value, in an arbitrary order.
    /// </remarks>
    /// <param name="dictionary">[IN] The other dictionary to be copied.</param>
    /// <returns>
    /// A reference to the resultant dictionary.
    /// </returns>
    QDictionary& operator=(const QDictionary dictionary)
    {
        if(this != &dictionary)
            m_binaryTree = dictionary.m_binaryTree;

        return *this;
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the allocator of keys and values.
    /// </summary>
    /// <returns>
    /// The key-value allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return m_binaryTree.GetAllocator();
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The internal binary search tree that holds all the key-value pairs.
    /// </summary>
    QBinarySearchTree<QKeyValuePair<KeyT, ValueT>, AllocatorT, SQKeyValuePairComparator<KeyT, ValueT, KeyComparatorT> > m_binaryTree;
};

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QDICTIONARY__
