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


    // TYPEDEFS
    // ---------------
protected:

    typedef QKeyValuePair<KeyT, ValueT> KeyValuePairType;
    typedef QDynamicArray<QBucket> BucketsArrayType;
    typedef QList<KeyValuePairType, AllocatorT, SQKeyValuePairComparator<KeyT, ValueT, KeyComparatorT> > SlotListType;


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
    /// The copy constructor is called for every copied key and value, in an arbitrary order.
    /// </remarks>
    /// <param name="hashtable">[IN] The other hashtable to be copied.</param>
    QHashtable(const QHashtable &hashtable)
    {
        // [TODO] Thund: Implement this when iterators exist
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
    void Add(const KeyT &key, const ValueT &value)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter;

        // [TODO] Thund: Uncomment when Contains exists
        //QE_ASSERT_ERROR(!this->Contains(key), string_q("The new key (" + SQAnyTypeToStringConverter::Convert(key) + ") already exists in the hashtable.");

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

        // [TODO] Thund: Uncomment when iterator exists
        // return QHashtable::QConstHashtableIterator(this, uFirstSlotPosition);
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

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotCount());
        pointer_uint_q uSlot = 0;

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
