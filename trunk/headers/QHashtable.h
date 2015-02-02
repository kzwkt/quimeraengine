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

#ifndef __QHASHTABLE__
#define __QHASHTABLE__

#include "ToolsDefinitions.h"

#include "QDynamicArray.h"
#include "QList.h"
#include "SQKeyValuePairComparator.h"
#include "SQComparatorDefault.h"
#include "QKeyValuePair.h"
#include "SQIntegerHashProvider.h"
#include "QPoolAllocator.h"
#include "SQAnyTypeToStringConverter.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Represents a hash table, a data structure that acts as an associative array that maps unique keys to values.
/// </summary>
/// <remarks>
/// Currently, the hash table is implemented following the separate-chaining model (a.k.a. closed addressing or open hashing). An array is filled with buckets which point to slots 
/// (colliding elements) stored as key-value pairs into a single shared double-linked list; this allows every bucket to grow indefinitely. The array of buckets can grow too 
/// although it implies rehashing everything.<br/>
/// Hash tables use a hash function or hash provider to compute an internal index that determines the position of a new key-value pair. Such provider depends on the key's data type.<br/>
/// Keys and values are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If SQComparatorDefault is used as key comparator, keys will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="KeyT">The type of the key associated to every value in the table.</typeparam>
/// <typeparam name="ValueT">The type of the values stored in the table.</typeparam>
/// <typeparam name="HashProviderT">Optional. The type of the hash provider. By default, it is SQIntegerHashProvider.</typeparam>
/// <typeparam name="AllocatorT">Optional. The type of the allocator that reserves memory for keys, values and buckets. By default, it is QPoolAllocator.</typeparam>
/// <typeparam name="KeyComparatorT">Optional. The type of the comparator used to compare keys. By default, it is SQComparatorDefault.</typeparam>
template<class KeyT, class ValueT, class HashProviderT = SQIntegerHashProvider, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class KeyComparatorT = SQComparatorDefault<KeyT> >
class QHashtable
{
    // TYPEDEFS (I)
    // ---------------
protected:

    typedef QKeyValuePair<KeyT, ValueT> KeyValuePairType;
    typedef QList<KeyValuePairType, AllocatorT, SQKeyValuePairComparator<KeyT, ValueT, KeyComparatorT> > SlotListType;


    // INTERNAL CLASSES
    // ---------------
public:

    /// <summary>
    /// Stores information about the position and size of a bucket in the slot list.
    /// </summary>
    class QBucket
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Default constructor that sets up the information about a bucket.
        /// </summary>
        QBucket() : m_uSlotPosition(QHashtable::END_POSITION_FORWARD),
                    m_uSlotCount(0)
        {
        }


        // PROPERTIES
        // ---------------
    public:
        
        /// <summary>
        /// Gets the position of the first slot of the bucket.
        /// </summary>
        /// <returns>
        /// The position of the slot.
        /// </returns>
        pointer_uint_q GetSlotPosition() const
        {
            return m_uSlotPosition;
        }
        
        /// <summary>
        /// Sets the position of the first slot of the bucket.
        /// </summary>
        /// <param name="uPosition">[IN] The slot position.</param>
        void SetSlotPosition(const pointer_uint_q uPosition)
        {
            m_uSlotPosition = uPosition;
        }
        
        /// <summary>
        /// Gets the number of slots stored in the bucket.
        /// </summary>
        /// <returns>
        /// The amount of slots.
        /// </returns>
        pointer_uint_q GetSlotCount() const
        {
            return m_uSlotCount;
        }
        
        /// <summary>
        /// Sets the number of slots stored in the bucket.
        /// </summary>
        /// <param name="uCount">[IN] The number of slots.</param>
        void SetSlotCount(const pointer_uint_q uCount)
        {
            m_uSlotCount = uCount;
        }


        // ATTRIBUTES
        // ---------------
    private:
        
        /// <summary>
        /// The physical position of the first slot in the slot list.
        /// </summary>
        pointer_uint_q m_uSlotPosition;
        
        /// <summary>
        /// The number of the slots stored in the bucket.
        /// </summary>
        pointer_uint_q m_uSlotCount;
    };


    /// <summary>
    /// Iterator that steps once per key-value pair of a hashtable, in an undefined order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a hashtable, it cannot point to another hashtable ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the hashtable.<br/>
    /// The position just before the first element or just after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QConstHashtableIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the hashtable to iterate through and the position to physically point to. This constructor is intended 
        /// to be used internally, use GetFirst or GetLast methods of the QHashtable class instead.
        /// </summary>
        /// <remarks>
        /// If the hashtable is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pHashtable">[IN] The hashtable to iterate through. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of hashtable elements, but the physical.
        /// It must be lower than the capacity of the hashtable.</param>
        QConstHashtableIterator(const QHashtable* pHashtable, const pointer_uint_q uPosition) : m_slotIterator(&pHashtable->m_slots, uPosition),
                                                                                                m_pHashtable(pHashtable)
        {
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator. The traversal order is also copied.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same hashtable as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QConstHashtableIterator& operator=(const QConstHashtableIterator &iterator)
        {
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid.");
            QE_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "The input iterator points to a different hashtable.");

            m_slotIterator = iterator.m_slotIterator;

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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the hashtable element.");

            return *m_slotIterator;
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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the hashtable element.");

            return m_slotIterator.operator->();
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
        QConstHashtableIterator operator++(int)
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            QE_ASSERT_WARNING(!this->IsEnd(EQIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            QConstHashtableIterator iteratorCopy = *this;
            m_slotIterator++;
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
        QConstHashtableIterator operator--(int)
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            QE_ASSERT_WARNING(!this->IsEnd(EQIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to increment it");

            QConstHashtableIterator iteratorCopy = *this;
            m_slotIterator--;
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
        QConstHashtableIterator& operator++()
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            QE_ASSERT_WARNING(!this->IsEnd(EQIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ++m_slotIterator;

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
        QConstHashtableIterator& operator--()
        {            
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            QE_ASSERT_WARNING(!this->IsEnd(EQIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to increment it");

            --m_slotIterator;

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same hashtable to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same hashtable; False otherwise.
        /// </returns>
        bool operator==(const QConstHashtableIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator == iterator.m_slotIterator;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different hashtable is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different hashtable; False otherwise.
        /// </returns>
        bool operator!=(const QConstHashtableIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator != iterator.m_slotIterator;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const QConstHashtableIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator > iterator.m_slotIterator;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const QConstHashtableIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator < iterator.m_slotIterator;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const QConstHashtableIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator >= iterator.m_slotIterator;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const QConstHashtableIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator <= iterator.m_slotIterator;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the hashtable.
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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return m_slotIterator.IsEnd();
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the hashtable, distinguishing which of them.
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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return m_slotIterator.IsEnd(eIterationDirection);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the hashtable is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            m_slotIterator.MoveFirst();
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the hashtable is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            m_slotIterator.MoveLast();
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a hashtable may have been shortened while the iterator
        /// was pointing to its last position). If the hashtable to iterate has been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_slotIterator.IsValid();
        }
        
        /// <summary>
        /// Gets the container that is being traversed by the iterator.
        /// </summary>
        /// <returns>
        /// A pointer to the container. It never changes since the iterator is created.
        /// </returns>
        const QHashtable* GetContainer() const
        {
            return m_pHashtable;
        }
        
        /// <summary>
        /// Gets the "physical" position of the container's allocated buffer where the iterator is pointing to.
        /// </summary>
        /// <remarks>
        /// This method is intended to be used internally by containers, users should not call it.
        /// </remarks>
        /// <returns>
        /// The position the iterator points to.
        /// </returns>
        pointer_uint_q GetInternalPosition() const
        {
            return m_slotIterator.GetInternalPosition();
        }


        // ATTRIBUTES
	    // ---------------
    protected:

        /// <summary>
        /// A wrapped slot list iterator.
        /// </summary>
        typename SlotListType::ConstIterator m_slotIterator;
        
        /// <summary>
        /// The traversed hashtable.
        /// </summary>
        const QHashtable* m_pHashtable;

    }; // QConstHashtableIterator


    // TYPEDEFS (II)
    // ---------------
public:

    typedef typename QHashtable::QConstHashtableIterator ConstIterator;

protected:

    typedef QDynamicArray<QBucket> BucketsArrayType;


    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Constant to symbolize the end of the sequence near the last element.
    /// </summary>
    static const pointer_uint_q END_POSITION_FORWARD = -1;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the first element.
    /// </summary>
    static const pointer_uint_q END_POSITION_BACKWARD = -2;


    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the initial number of buckets and their expected slots.
    /// </summary>
    /// <param name="uNumberOfBuckets">[IN] The number of buckets in the table. The higher it is, the less collisions occurs. It must be greater than zero.</param>
    /// <param name="uSlotsPerBucket">[IN] The number of expected slots per bucket. The higher it is, the more capacity the table has initially. It must be greater than zero.</param>
    QHashtable(const pointer_uint_q uNumberOfBuckets, const pointer_uint_q uSlotsPerBucket) : m_arBuckets(uNumberOfBuckets),
                                                                                              m_slots(uNumberOfBuckets * uSlotsPerBucket)
    {
        QE_ASSERT_ERROR(uNumberOfBuckets > 0, "The number of buckets must be greater than zero.");
        QE_ASSERT_ERROR(uSlotsPerBucket > 0, "The number of slots per bucket must be greater than zero.");

        static const QHashtable::QBucket DEFAULT_BUCKET;

        // The array of buckets is pre-allocated and initialized
        for(pointer_uint_q uIndex = 0; uIndex < uNumberOfBuckets; ++uIndex)
            m_arBuckets.Add(DEFAULT_BUCKET);
    }
    
    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every copied key and value, in an arbitrary order.<br/>
    /// The capacity of the resultant hashtable is equal to the amount of elements in the input hashtable. If it is empty, then the capacity of the input hashtable is used instead.
    /// </remarks>
    /// <param name="hashtable">[IN] The other hashtable to be copied.</param>
    QHashtable(const QHashtable &hashtable) : m_arBuckets(hashtable.m_arBuckets.GetCount()),
                                              m_slots(hashtable.m_slots.GetCount() == 0 ? hashtable.GetCapacity() : hashtable.m_slots.GetCount())
    {
        static const QHashtable::QBucket DEFAULT_BUCKET;

        // The array of buckets is pre-allocated and initialized
        for(pointer_uint_q uIndex = 0; uIndex < hashtable.m_arBuckets.GetCount(); ++uIndex)
            m_arBuckets.Add(DEFAULT_BUCKET);

        // Every key-value pair is copied
        for(QHashtable::QConstHashtableIterator it = hashtable.GetFirst(); !it.IsEnd(); ++it)
            this->Add(it->GetKey(), it->GetValue());
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
    ~QHashtable()
    {
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Increases the capacity of the hashtable, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// It does not produce the rehash of any element.<br/>
    /// This operation implies a reallocation, which means that any pointer to elements of this hashtable will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of key-value pairs for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const pointer_uint_q uNumberOfElements)
    {
        m_slots.Reserve(uNumberOfElements);
    }

    /// <summary>
    /// Adds a key and its associated value to the hashtable.
    /// </summary>
    /// <remarks>
    /// This operation may imply a reallocation, which means that any pointer to elements of this hashtable will be pointing to garbage.<br/>
    /// The copy constructor of both the new key and the new value will be called.
    /// </remarks>
    /// <param name="key">[IN] The new key. It must not exist in the hashtable yet.</param>
    /// <param name="value">[IN] The new value associated to the new key.</param>
    /// <returns>
    /// An iterator that points to the just added key-value pair. If the key was already in the hashtable, the returned iterator will point to the end position.
    /// </returns>
    QConstHashtableIterator Add(const KeyT &key, const ValueT &value)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter;

        QE_ASSERT_ERROR(!this->ContainsKey(key), string_q("The new key (") + SQAnyTypeToStringConverter::Convert(key) + ") already exists in the hashtable.");

        // Gets the corresponding bucket
        pointer_uint_q uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        QHashtable::QBucket& bucket = m_arBuckets[uHashKey];
        
        // Creates a key-value by copying the data without calling any constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        memcpy(pKeyValueBlock + sizeof(KeyT), &value, sizeof(ValueT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        m_slots.Add(*pKeyValue);
        bucket.SetSlotCount(bucket.GetSlotCount() + 1U);

        // Finds the first slot of the bucket
        pointer_uint_q uFirstSlotPosition = bucket.GetSlotPosition();

        if(uFirstSlotPosition == QHashtable::END_POSITION_FORWARD)
        {
            // The bucket was empty, the first slot's position is set
            uFirstSlotPosition = m_slots.GetLast().GetInternalPosition();
            bucket.SetSlotPosition(uFirstSlotPosition);
        }

        return QHashtable::QConstHashtableIterator(this, uFirstSlotPosition);
    }
    
    /// <summary>
    /// Array subscript operator that receives a key and retrieves its associated value.
    /// </summary>
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the hashtable.</param>
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
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the hashtable.</param>
    /// <returns>
    /// A reference to the associated value.
    /// </returns>
    ValueT& GetValue(const KeyT& key) const
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter;

        // Gets the corresponding bucket
        pointer_uint_q uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        QHashtable::QBucket& bucket = m_arBuckets[uHashKey];

        QE_ASSERT_ERROR(bucket.GetSlotCount() > 0, string_q("The input key (") + SQAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotPosition());
        pointer_uint_q uSlot = 0;

        // Traverses all the slots of the bucket
        while(uSlot < bucket.GetSlotCount() && KeyComparatorT::Compare(slot->GetKey(), key) != 0)
        {
            ++slot;
            ++uSlot;
        }
        
        QE_ASSERT_ERROR(uSlot < bucket.GetSlotCount(), string_q("The input key (") + SQAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        return ccast_q(slot->GetValue(), ValueT&);
    }

    /// <summary>
    /// Sets the value that corresponds to the given key.
    /// </summary>
    /// <remarks>
    /// It calls the assignment operator of the value.
    /// </remarks>
    /// <param name="key">[IN] A key whose associated value will be modified. It must exist in the hashtable.</param>
    /// <param name="newValue">[IN] The value that will replace the existing one.</param>
    void SetValue(const KeyT& key, const ValueT& newValue) const
    {
        this->GetValue(key) = newValue;
    }
    
    /// <summary>
    /// Checks whether there is any key in the hashtable that is equal to other given key.
    /// </summary>
    /// <remarks>
    /// Keys are compared to the provided key using the container's key comparator.<br/>
    /// </remarks>
    /// <param name="key">[IN] The key to search for.</param>
    /// <returns>
    /// True if the key is present in the hashtable; False otherwise.
    /// </returns>
    bool ContainsKey(const KeyT &key) const
    {
        // Creates a key-value by copying the key without calling its constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        return m_slots.Contains(*pKeyValue);
    }
    
    /// <summary>
    /// Removes an key-value pair from the hashtable by its key.
    /// </summary>
    /// <remarks>
    /// The destructor of both the key and the value will be called.
    /// </remarks>
    /// <param name="key">[IN] The key to search for. It must exist in the hashtable.</param>
    void Remove(const KeyT &key)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter;

        // Gets the corresponding bucket
        pointer_uint_q uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        QHashtable::QBucket& bucket = m_arBuckets[uHashKey];

        QE_ASSERT_ERROR(bucket.GetSlotCount() > 0, string_q("The input key (") + SQAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotPosition());
        pointer_uint_q uSlot = 0;

        while(uSlot < bucket.GetSlotCount() && KeyComparatorT::Compare(slot->GetKey(), key) != 0)
        {
            ++slot;
            ++uSlot;
        }
        
        QE_ASSERT_ERROR(uSlot < bucket.GetSlotCount(), string_q("The input key (") + SQAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        // Updates the bucket
        bucket.SetSlotCount(bucket.GetSlotCount() - 1U);

        if(bucket.GetSlotCount() == 0)
            bucket.SetSlotPosition(QHashtable::END_POSITION_FORWARD);

        m_slots.Remove(slot);
    }

    /// <summary>
    /// Gets the first element in the hashtable, which can be any of the existing elements since no defined order is followed.
    /// </summary>
    /// <returns>
    /// An iterator that points to the first key-value pair. If the hashtable is empty, the iterator will point to the end position.
    /// </returns>
    QConstHashtableIterator GetFirst() const
    {
        QHashtable::QConstHashtableIterator iterator(this, 0);
        iterator.MoveFirst();
        return iterator;
    }

    /// <summary>
    /// Gets the last element in the hashtable, which can be any of the existing elements since no defined order is followed.
    /// </summary>
    /// <returns>
    /// An iterator that points to the last key-value pair. If the hashtable is empty, the iterator will point to the end position.
    /// </returns>
    QConstHashtableIterator GetLast() const
    {
        QHashtable::QConstHashtableIterator iterator(this, 0);
        iterator.MoveLast();
        return iterator;
    }
    
    /// <summary>
    /// Searches for a given key-value pair and obtains its position.
    /// </summary>
    /// <param name="key">[IN] The key of the pair to search for.</param>
    /// <returns>
    /// An iterator that points to the position of the key-value pair. If the key is not present in the hashtable, the iterator will point to the end position.
    /// </returns>
    QConstHashtableIterator PositionOfKey(const KeyT &key) const
    {
        // Creates a key-value by copying the key without calling its constructor
        u8_q pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_q(pKeyValueBlock, KeyValuePairType*);

        // Gets the corresponding bucket
        pointer_uint_q uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        QHashtable::QBucket& bucket = m_arBuckets[uHashKey];

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotPosition());
        pointer_uint_q uSlot = 0;
        pointer_uint_q uResultPosition = bucket.GetSlotPosition();

        // Traverses all the slots of the bucket
        while(uSlot < bucket.GetSlotCount() && KeyComparatorT::Compare(slot->GetKey(), key) != 0)
        {
            uResultPosition = slot.GetInternalPosition();
            ++slot;
            ++uSlot;
        }

        // If the key was not found, the iterator points to an end position
        if(uSlot == bucket.GetSlotCount())
            uResultPosition = QHashtable::END_POSITION_FORWARD;

        return QHashtable::QConstHashtableIterator(this, uResultPosition);
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Returns the number of key-value pairs that can be stored in the hashtable without a reallocation.
    /// </summary>
    /// <returns>
    /// The number of key-value pairs that can be stored in the hashtable without a reallocation.
    /// </returns>
    pointer_uint_q GetCapacity() const
    {
        return m_slots.GetCapacity();
    }
    
    /// <summary>
    /// Gets the allocator of keys and values.
    /// </summary>
    /// <returns>
    /// The key-value allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return m_slots.GetAllocator();
    }

    /// <summary>
    /// Gets the number of elements added to the hashtable.
    /// </summary>
    /// <returns>
    /// The number of elements in the hashtable.
    /// </returns>
    pointer_uint_q GetCount() const
    {
        return m_slots.GetCount();
    }
    
    /// <summary>
    /// Indicates whether the hashtable is empty or not.
    /// </summary>
    /// <returns>
    /// True if the hashtable is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const
    {
        return m_slots.IsEmpty();
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The array of buckets. Every hash key corresponds to one position in this array.
    /// </summary>
    BucketsArrayType m_arBuckets;

    /// <summary>
    /// The slot list. It is shared among all the buckets. Every bucket knows where its slots are placed in the list.
    /// </summary>
    SlotListType m_slots;

};

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QHASHTABLE__
