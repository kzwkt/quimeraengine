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
/// <typeparam name="ValueComparatorT">The type of comparator utilized to compare values. The default type is SQComparatorDefault.</typeparam>
template<class KeyT, class ValueT, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class KeyComparatorT = SQComparatorDefault<KeyT>, class ValueComparatorT = SQComparatorDefault<ValueT> >
class QDictionary
{
    // TYPEDEFS (I)
    // ---------------
protected:

    typedef QBinarySearchTree<QKeyValuePair<KeyT, ValueT>, AllocatorT, SQKeyValuePairComparator<KeyT, ValueT, KeyComparatorT> > InternalBinaryTreeType;
    typedef QKeyValuePair<KeyT, ValueT> KeyValuePairType;


    // INTERNAL CLASSES
    // ---------------
public:

    /// <summary>
    /// Iterator that steps once per key-value pair of a dictionary, from the lowest key to the greatest.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a dictionary, it cannot point to another dictionary ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the dictionary.<br/>
    /// The position just before the first element or just after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QConstDictionaryIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the dictionary to iterate through and the position to physically point. This constructor is intended 
        /// to be used internally, use GetIterator method of the QDictionary class instead.
        /// </summary>
        /// <remarks>
        /// If the dictionary is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pDictionary">[IN] The dictionary to iterate through. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of dictionary elements, but the physical.
        /// It must be lower than the capacity of the dictionary.</param>
        QConstDictionaryIterator(const QDictionary* pDictionary, const pointer_uint_q uPosition) : m_treeIterator(&pDictionary->m_keyValues, 
                                                                                                                  uPosition, 
                                                                                                                  EQTreeTraversalOrder::E_DepthFirstInOrder),
                                                                                                   m_pDictionary(pDictionary)
        {
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator. The traversal order is also copied.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same dictionary as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QConstDictionaryIterator& operator=(const QConstDictionaryIterator &iterator)
        {
            m_treeIterator = iterator.m_treeIterator;

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the key-value pair the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the key-value pair the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const KeyValuePairType& operator*() const
        {
            return *m_treeIterator;
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the key-value pair the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the key-value pair the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const KeyValuePairType* operator->() const
        {
            return m_treeIterator.operator->();
        }

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QConstDictionaryIterator operator++(int)
        {
            QConstDictionaryIterator iteratorCopy = *this;
            m_treeIterator++;
            return iteratorCopy;
        }

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        QConstDictionaryIterator operator--(int)
        {
            QConstDictionaryIterator iteratorCopy = *this;
            m_treeIterator--;
            return iteratorCopy;
        }

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QConstDictionaryIterator& operator++()
        {
            ++m_treeIterator;

            return *this;
        }

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        QConstDictionaryIterator& operator--()
        {
            --m_treeIterator;

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same dictionary to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same dictionary; False otherwise.
        /// </returns>
        bool operator==(const QConstDictionaryIterator &iterator) const
        {
            return m_treeIterator == iterator.m_treeIterator;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different dictionary is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different dictionary; False otherwise.
        /// </returns>
        bool operator!=(const QConstDictionaryIterator &iterator) const
        {
            return m_treeIterator != iterator.m_treeIterator;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const QConstDictionaryIterator &iterator) const
        {
            return m_treeIterator > iterator.m_treeIterator;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const QConstDictionaryIterator &iterator) const
        {
            return m_treeIterator < iterator.m_treeIterator;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const QConstDictionaryIterator &iterator) const
        {
            return m_treeIterator >= iterator.m_treeIterator;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const QConstDictionaryIterator &iterator) const
        {
            return m_treeIterator <= iterator.m_treeIterator;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the dictionary.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <returns>
        /// True if the iterator is pointing to an end position; False otherwise.
        /// </returns>
        bool IsEnd() const
        {
            return m_treeIterator.IsEnd();
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the dictionary, distinguishing which of them.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <param name="eIterationDirection">[IN] The iteration direction used to identify which of the end positions is checked.</param>
        /// <returns>
        /// True if the iterator is pointing to the position after the last element when iterating forward or if it is
        /// pointing to the position immediately before the first position when iterating backward; False otherwise.
        /// </returns>
        bool IsEnd(const EQIterationDirection &eIterationDirection) const
        {
            return m_treeIterator.IsEnd(eIterationDirection);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the dictionary is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            m_treeIterator.MoveFirst();
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the dictionary is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            m_treeIterator.MoveLast();
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a dictionary may have been shortened while the iterator
        /// was pointing to its last position). If the dictionary to iterate has been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_treeIterator.IsValid();
        }


        // ATTRIBUTES
	    // ---------------
    protected:

        /// <summary>
        /// A wrapped binary search tree iterator.
        /// </summary>
        typename InternalBinaryTreeType::ConstIterator m_treeIterator;
        
        /// <summary>
        /// The traversed dictionary.
        /// </summary>
        const QDictionary* m_pDictionary;

    }; // QConstDictionaryIterator


    // TYPEDEFS (II)
    // ---------------
public:

    typedef typename QDictionary::QConstDictionaryIterator ConstIterator;
    

   	// CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Constant to symbolize the absence of a key-value pair or the end of the sequence when the dictionary is traversed forward.
    /// </summary>
    static const pointer_uint_q END_POSITION_FORWARD = -1;


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
    QDictionary& operator=(const QDictionary &dictionary)
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

    /// <summary>
    /// Increases the capacity of the dictionary, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means that any pointer to elements of this dictionary will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const pointer_uint_q uNumberOfElements)
    {
        m_keyValues.Reserve(uNumberOfElements);
    }
    
    /// <summary>
    /// Adds a key and its associated value to the dictionary.
    /// </summary>
    /// <remarks>
    /// This operation may imply a reallocation, which means that any pointer to elements of this dictionary will be pointing to garbage.<br/>
    /// The copy constructor of both the new key and the new value will be called.
    /// </remarks>
    /// <param name="key">[IN] The new key. It must not exist in the directory yet.</param>
    /// <param name="value">[IN] The new value associated to the new key.</param>
    /// <returns>
    /// An iterator that points to the just added key-value pair. If the key was already in the dictionary, the returned iterator will point to the end position.
    /// </returns>
    QConstDictionaryIterator Add(const KeyT &key, const ValueT &value)
    {
        // Creates a key-value by copying the data without calling any constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        memcpy(pKeyValueBlock + sizeof(KeyT), &value, sizeof(ValueT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.Add(*pKeyValue, EQTreeTraversalOrder::E_DepthFirstInOrder);

        pointer_uint_q uIteratorPosition = &*treeIterator - rcast_q(m_keyValues.GetAllocator()->GetPointer(), const KeyValuePairType*);
        return QConstDictionaryIterator(this, uIteratorPosition);
    }

    /// <summary>
    /// Removes an key-value pair from the dictionary by its position.
    /// </summary>
    /// <remarks>
    /// The destructor of both the key and the value will be called.
    /// </remarks>
    /// <param name="pairPosition">[IN] The position of the key-value pair to remove. It must not point to the end position.</param>
    /// <returns>
    /// An iterator that points to the next key-value pair. If the removed pair was the last one in the dictionary, the returned iterator will point to the end position.
    /// </returns>
    QConstDictionaryIterator Remove(const typename QDictionary::QConstDictionaryIterator &pairPosition)
    {
        // Creates a key-value by copying the data without calling any constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &pairPosition->GetKey(), sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        const KeyValuePairType* pBasePointer = rcast_q(m_keyValues.GetAllocator()->GetPointer(), const KeyValuePairType*);
        pointer_uint_q uIteratorPosition = &*pairPosition - pBasePointer;
        InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.Remove(InternalBinaryTreeType::ConstIterator(&m_keyValues, uIteratorPosition, EQTreeTraversalOrder::E_DepthFirstInOrder));
        
        uIteratorPosition = QDictionary::END_POSITION_FORWARD;
            
        if(!treeIterator.IsEnd())
            uIteratorPosition = &*treeIterator - pBasePointer;

        return QDictionary::QConstDictionaryIterator(this, uIteratorPosition);

    }
    
    /// <summary>
    /// Removes an key-value pair from the dictionary by its key.
    /// </summary>
    /// <remarks>
    /// The destructor of both the key and the value will be called.
    /// </remarks>
    /// <param name="key">[IN] The key to search for.</param>
    void Remove(const KeyT &key)
    {
        // Creates a key-value by copying the data without calling any constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.PositionOf(*pKeyValue, EQTreeTraversalOrder::E_DepthFirstInOrder);
        m_keyValues.Remove(treeIterator);
    }

    /// <summary>
    /// Gets the first element in the dictionary, which is the one whose key is the lowest.
    /// </summary>
    /// <returns>
    /// An iterator that points to the first key-value pair. If the dictionary is empty, the iterator will point to the end position.
    /// </returns>
    QConstDictionaryIterator GetFirst() const
    {
        QDictionary::QConstDictionaryIterator iterator(this, 0);
        iterator.MoveFirst();
        return iterator;
    }

    /// <summary>
    /// Gets the last element in the dictionary, which is the one whose key is the greatest.
    /// </summary>
    /// <returns>
    /// An iterator that points to the last key-value pair. If the dictionary is empty, the iterator will point to the end position.
    /// </returns>
    QConstDictionaryIterator GetLast() const
    {
        QDictionary::QConstDictionaryIterator iterator(this, 0);
        iterator.MoveLast();
        return iterator;
    }

    /// <summary>
    /// Checks whether there is any value in the dictionary that is equal to another given value.
    /// </summary>
    /// <remarks>
    /// Values are compared to the provided value using the container's value comparator.<br/>
    /// </remarks>
    /// <param name="value">[IN] The value to search for.</param>
    /// <returns>
    /// True if the value is present in the dictionary; False otherwise.
    /// </returns>
    bool ContainsValue(const ValueT &value) const
    {
        QConstDictionaryIterator itKeyValue = this->GetFirst();

        while(!itKeyValue.IsEnd() && ValueComparatorT::Compare(itKeyValue->GetValue(), value) != 0)
            ++itKeyValue;

        return !itKeyValue.IsEnd();
    }

    /// <summary>
    /// Checks whether there is any key in the dictionary that is equal to other given key.
    /// </summary>
    /// <remarks>
    /// Keys are compared to the provided key using the container's key comparator.<br/>
    /// </remarks>
    /// <param name="key">[IN] The key to search for.</param>
    /// <returns>
    /// True if the key is present in the dictionary; False otherwise.
    /// </returns>
    bool ContainsKey(const KeyT &key) const
    {
        // Creates a key-value by copying the key without calling its constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        return m_keyValues.Contains(*pKeyValue);
    }

    /// <summary>
    /// Searches for a given key-value pair and obtains its position.
    /// </summary>
    /// <param name="key">[IN] The key of the pair to search for.</param>
    /// <returns>
    /// An iterator that points to the position of the key-value pair. If the key is not present in the dictionary, the iterator will point to the end position.
    /// </returns>
    QConstDictionaryIterator PositionOfKey(const KeyT &key) const
    {
        // Creates a key-value by copying the key without calling its constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.PositionOf(*pKeyValue, EQTreeTraversalOrder::E_DepthFirstInOrder);

        pointer_uint_q uIteratorPosition = QDictionary::END_POSITION_FORWARD;

        if(!treeIterator.IsEnd())
            uIteratorPosition = &*treeIterator - rcast_q(m_keyValues.GetAllocator()->GetPointer(), const KeyValuePairType*);

        return QConstDictionaryIterator(this, uIteratorPosition);
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
    /// Gets the capacity of the directory, which means the number of elements that can be added before they are reallocated to
    /// another part of memory.
    /// </summary>
    /// <returns>
    /// The capacity of the dictionary.
    /// </returns>
    pointer_uint_q GetCapacity() const
    {
        return m_keyValues.GetCapacity();
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
