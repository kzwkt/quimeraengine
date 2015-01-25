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
    // TYPEDEFS
    // ---------------
protected:

    typedef QBinarySearchTree<QKeyValuePair<KeyT, ValueT>, AllocatorT, SQKeyValuePairComparator<KeyT, ValueT, KeyComparatorT> > InternalBinaryTreeType;
    typedef QKeyValuePair<KeyT, ValueT> KeyValuePairType;


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
    explicit QDictionary(const pointer_uint_q uInitialCapacity) : m_keyValues(uInitialCapacity)
    {
    }
    
    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every key and value, in an arbitrary order.
    /// </remarks>
    /// <param name="dictionary">[IN] The other dictionary to be copied.</param>
    QDictionary(const QDictionary &dictionary) : m_keyValues(dictionary.m_keyValues)
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
            m_keyValues = dictionary.m_keyValues;

        return *this;
    }
        
    /// <summary>
    /// Performs a shallow copy of the content of the dictionary to another dictionary.
    /// </summary>
    /// <remarks>
    /// If the capacity of the destination dictionary is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="destinationDictionary">[IN/OUT] The destination dictionary to which the contents will be copied.</param>
    void Clone(QDictionary &destinationDictionary) const
    {
        m_keyValues.Clone(destinationDictionary.m_keyValues);
    }

    /// <summary>
    /// Array subscript operator that receives a key and retrieves its associated value.
    /// </summary>
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the dictionary.</param>
    /// <returns>
    /// A reference to the associated value.
    /// </returns>
    ValueT& operator[](const KeyT &key) const
    {
        return this->GetValue(key);
    }
    
    /// <summary>
    /// Gets the value that corresponds to the given key.
    /// </summary>
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the dictionary.</param>
    /// <returns>
    /// A reference to the associated value.
    /// </returns>
    ValueT& GetValue(const KeyT& key) const
    {
        // Creates a fake key-value pair with the input key
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator position = m_keyValues.PositionOf(*pKeyValue, EQTreeTraversalOrder::E_DepthFirstInOrder);

        QE_ASSERT_ERROR(!position.IsEnd(), "The specified key does not exist.");

        return ccast_q(position->GetValue(), ValueT&);
    }

    /// <summary>
    /// Sets the value that corresponds to the given key.
    /// </summary>
    /// <remarks>
    /// It calls the assignment operator of the value.
    /// </remarks>
    /// <param name="key">[IN] A key whose associated value will be modified. It must exist in the dictionary.</param>
    /// <param name="newValue">[IN] The value that will be replace the existing one.</param>
    void SetValue(const KeyT& key, const ValueT& newValue) const
    {
        // Creates a fake key-value pair with the input key
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator position = m_keyValues.PositionOf(*pKeyValue, EQTreeTraversalOrder::E_DepthFirstInOrder);

        QE_ASSERT_ERROR(!position.IsEnd(), "The specified key does not exist.");

        ccast_q(*position, KeyValuePairType&).SetValue(newValue);
    }

    /// <summary>
    /// Empties the dictionary.
    /// </summary>
    /// <remarks>
    /// The destructor of each key and value will be called in an undefined order.
    /// </remarks>
    void Clear()
    {
        m_keyValues.Clear();
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
        return m_keyValues.GetAllocator();
    }
        
    /// <summary>
    /// Gets the number of elements added to the dictionary.
    /// </summary>
    /// <returns>
    /// The number of elements in the dictionary.
    /// </returns>
    pointer_uint_q GetCount() const
    {
        return m_keyValues.GetCount();
    }
    
    /// <summary>
    /// Indicates whether the dictionary is empty or not.
    /// </summary>
    /// <returns>
    /// True if the dictionary is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const
    {
        return m_keyValues.IsEmpty();
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The internal binary search tree that holds all the keys.
    /// </summary>
    InternalBinaryTreeType m_keyValues;
};



} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QDICTIONARY__
