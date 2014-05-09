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

#ifndef __QLIST__
#define __QLIST__

#include "DataTypesDefinitions.h"
#include "ToolsDefinitions.h"
#include "Assertions.h"
#include "QPoolAllocator.h"
#include "QAlignment.h"
#include "QComparatorDefault.h"
#include "AllocationOperators.h"


using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Represents a sequence of elements to be accessed sequentally, although they can be arbitrarily accessed using a zero-based index.<br/>
/// For best performance it's internally managed as a double linked-list.
/// </summary>
/// <remarks>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T"> The type of the list elements.</typeparam>
/// <typeparam name="Allocator"> The allocator used to reserve memory. The default type is QPoolAllocator.</typeparam>
/// <typeparam name="Comparator"> The comparator. The default type is QComparatorDefault.</typeparam>
template <class T, class Allocator = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class Comparator = QComparatorDefault<T> >
class QList
{

    // INTERNAL CLASSES
    // -----------------

protected:

    /// <summary>
    /// Class intended to store the information needed to link one element of the list to another.
    /// </summary>
    class QLink
    {
   	    // CONSTANTS
	    // ---------------

	    // CONSTRUCTORS
	    // ---------------

    public:

        /// <summary>
        /// Constructor with the positions in the allocated memory chunk to the previous and next elements,
        /// passed by parameter.
        /// </summary>
        /// <param name="uPrevious"> [IN] Position of the previous element.</param>
        /// <param name="uNext"> [IN] Position of the next element.</param>
        QLink(const pointer_uint_q uPrevious, const pointer_uint_q uNext) :
                m_uPrevious(uPrevious),
                m_uNext(uNext)
        {
        }

    protected:

        // DESTRUCTOR
	    // ---------------

    public:

	    // METHODS
	    // ---------------

    public:

        // PROPERTIES
	    // ---------------

        /// <summary>
        /// Returns the index of the next element in the list.
        /// </summary>
        /// <returns>
        /// The index of the next element in the list. Returns QList::END_POSITION_FORWARD constant if there is no previous element.
        /// </returns>
        pointer_uint_q GetNext() const
        {
            return m_uNext;
        }

        /// <summary>
        /// Returns the index of the previous element in the list.
        /// </summary>
        /// <returns>
        /// The index of the previous element in the list. Returns QList::END_POSITION_BACKWARD constant if there is no previous element.
        /// </returns>
        pointer_uint_q GetPrevious() const
        {
            return m_uPrevious;
        }

        /// <summary>
        /// Sets the index of the next element in the list.
        /// </summary>
        /// <param name="uNext"> [IN] The index of the next element in the list. If there is no next element, you must pass QList::END_POSITION_FORWARD constant.</param>
        void SetNext(const pointer_uint_q uNext)
        {
            m_uNext = uNext;
        }

        /// <summary>
        /// Sets the index of the previous element in the list.
        /// </summary>
        /// <param name="uPrevious"> [IN] The index of the previous element in the list. If there is no previous element, you must pass QList::END_POSITION_BACKWARD constant.</param>
        void SetPrevious(const pointer_uint_q uPrevious)
        {
            m_uPrevious = uPrevious;
        }

    public:

        // ATTRIBUTES
	    // ---------------

    protected:

        /// <summary>
        /// The index of the next element in the list. QList::END_POSITION_FORWARD must be used when there is no next element.
        /// </summary>
        pointer_uint_q m_uNext;

        /// <summary>
        /// The index of the previous element in the list. QList::END_POSITION_BACKWARD must be used when there is no previous element.
        /// </summary>
        pointer_uint_q m_uPrevious;

    };


   	// CONSTANTS
	// ---------------

    /// <summary>
    /// Number of elements for which to reserve memory in the default constructor.
    /// </summary>
    static const pointer_uint_q DEFAULT_NUMBER_OF_ELEMENTS = 10;

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
    /// Default constructor. It reserves memory for the number of elements indicated at DEFAULT_NUMBER_OF_ELEMENTS constants.
    /// </summary>
    QList() :
            m_uFirst(QList::END_POSITION_BACKWARD),
            m_uLast(QList::END_POSITION_FORWARD)
    {
        m_pElementAllocator = new Allocator(QList::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(T), sizeof(T), QAlignment(alignof_q(T)));
        m_pLinkAllocator = new Allocator(QList::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)));
    }

    /// <summary>
    /// Constructor that reserves space to store the number of elements passed by parameter.
    /// </summary>
    /// <param name="uInitialCapacity"> [IN] Number of elements for wich to reserve space. It must be greater than zero.</param>
    QList(const pointer_uint_q uInitialCapacity) :
            m_uFirst(QList::END_POSITION_BACKWARD),
            m_uLast(QList::END_POSITION_FORWARD)
    {
        QE_ASSERT( uInitialCapacity > 0, "Initial capacity must be greater than zero" );

        m_pElementAllocator = new Allocator(uInitialCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T)));
        m_pLinkAllocator = new Allocator(uInitialCapacity * sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)));
    }

    // [TODO] rdelasheras. Uncomment when iterators exists.
/*
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the list.
    /// </remarks>
    /// <param name="list"> [IN] Origin list to copy.</param>
    QList(const QList& list)
    {
        // [TODO] rdelasheras. Use GetCapacity when it exists.
        m_pElementAllocator = new Allocator(list.m_pElementAllocator->GetPoolSize() / sizeof(T), sizeof(T), QAlignment(alignof_q(T)));
        m_pLinkAllocator = new Allocator(list.m_pLinkAllocator->GetPoolSize() / sizeof(QList::QLink), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)));

        if(list.m_uFirst == QList::END_POSITION_BACKWARD)
        {
            m_uFirst = QList::END_POSITION_BACKWARD;
            m_uLast = QList::END_POSITION_FORWARD;
        }
        else
        {
            // [TODO] rdelasheras. Uncomment when iterators exists.
            list.m_pLinkAllocator->CopyTo(*m_pLinkAllocator);
            list.m_pElementAllocator->CopyTo(*m_pElementAllocator);

            m_uFirst = list.m_uFirst;
            m_uLast = list.m_uLast;

            QListIterator iteratorOrigin = QListIterator(&list);
            QListIterator iteratorDestination = QListIterator(this);

            for(iteratorOrigin.MoveFirst(), iteratorDestination.MoveFirst();
                !iteratorOrigin.IsEnd();
                ++iteratorOrigin, ++iteratorDestination)
            {
                iteratorDestination->T(*iteratorOrigin);
            }

        }
    }
    */
protected:

    // DESTRUCTOR
	// ---------------

public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element is called in the same order they appear in the list.
    /// </remarks>
    ~QList() 
    {
        if(m_uFirst != QList::END_POSITION_BACKWARD)
        {
            // Iterates the list in an orderly manner, calling the destructor for each element.
            pointer_uint_q uIndex = m_uFirst;
            pointer_uint_q uNextIndex;
            QList::QLink* pLink = null_q;
            T* pElement = null_q;
            bool bDestroyed = false;

            while(!bDestroyed)
            {
                pLink = (QList::QLink*)m_pLinkAllocator->GetPointer() + uIndex * sizeof(QList::QLink);
                uNextIndex = pLink->GetNext();

                pElement = (T*)m_pElementAllocator->GetPointer() + uIndex * sizeof(T);
                pElement->~T();

                if(uIndex == m_uLast)
                    bDestroyed = true;
                else
                    uIndex = uNextIndex;
            }
        }

        delete m_pElementAllocator;
        delete m_pLinkAllocator;
    }

	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assignment operator that copies one list to another.
    /// </summary>
    /// <remarks>
    /// Assignment operator will be called for every element of the list.
    /// </remarks>
    /// <param name="list">[IN] List to copy in the current list.</param>
    /// <returns>
    /// A reference to the current list.
    /// </returns>
    QList& operator= (const QList& list)
    {
        // [TODO] rdelasheras. Uncomment when GetCount and iterators exist.
        /*
        if(this != &list)
        {
            if(list.GetCount() == this->GetCount()) 
            {
                QListIterator iteratorOrigin = QListIterator(&list);
                QListIterator iteratorDestination = QListIterator(this);

                for(iteratorOrigin.MoveFirst(), iteratorDestination.MoveFirst();
                    !iteratorOrigin.IsEnd();
                    ++iteratorOrigin, ++iteratorDestination)
                {
                    *iteratorDestination = *iteratorOrigin;
                }
            }
            else if(list.GetCount() < this->GetCount()) 
            {
                pointer_uint_q uFirstIndexToDestroy;
                pointer_uint_q uOldLast = m_uLast;

                if(list.GetCount() == 0)
                {
                    uFirstIndexToDestroy = m_uFirst;
                    m_uFirst = QList::END_POSITION_BACKWARD;
                    m_uLast = QList::END_POSITION_FORWARD;
                }
                else
                {
                    // Makes the copy calling assignment operator with existing elements.
                    
                    T* pElementOrigin = null_q;
                    T* pElementDestination = null_q;
                    QList::QLink* pLinkOrigin = null_q;
                    QList::QLink* pLinkDestination = null_q;

                    pointer_uint_q uIndexOrigin = list.m_uFirst;
                    pointer_uint_q uIndexDestination = m_uFirst;

                    bool bCopied = false;

                    while(!bCopied)
                    {
                        pElementOrigin = (T*)list.m_pElementAllocator->GetPointer() + uIndexOrigin * sizeof(T);
                        pElementDestination = (T*)m_pElementAllocator->GetPointer() + uIndexDestination * sizeof(T);

                        *pElementDestination = *pElementOrigin;

                        bCopied = (uIndexOrigin == list.m_uLast);
                        m_uLast = uIndexDestination;

                        pLinkOrigin = (QList::QLink*)list.m_pLinkAllocator->GetPointer() + uIndexOrigin * sizeof(QList::QLink);
                        uIndexOrigin = pLinkOrigin->GetNext();

                        pLinkDestination = (QList::QLink*)m_pLinkAllocator->GetPointer() + uIndex * sizeof(QList::QLink);
                        uIndexDestination = pLinkDestination->GetNext();
                    }
                    uFirstIndexToDestroy = uIndexDestination;
                }

                // Destroys the rest of the destination list

                pointer_uint_q uIndex = uFirstIndexToDestroy;
                pointer_uint_q uNextIndex;

                bool bDestroyed = false;

                while(!bDestroyed && uIndex != QList::END_POSITION_FORWARD)
                {
                    QList::QLink* pLink = (QList::QLink*)m_pLinkAllocator->GetPointer() + uIndex * sizeof(QList::QLink);
                    uNextIndex = pLink->GetNext();
                    m_pLinkAllocator->Deallocate(pLink);

                    T* pElement = (T*)m_pElementAllocator->GetPointer() + uIndex * sizeof(T);
                    pElement->~T();
                    m_pElementAllocator->Deallocate(pElement);

                    bDestroyed = (uIndex == uOldLast);
                    uIndex = uNextIndex;
                }
            }
            else
            {
                if(list.GetCapacity() > this->GetCapacity()) 
                {
                    Allocator *pOldElementAllocator = m_pElementAllocator;
                    Allocator *pOldLinkAllocator = m_pLinkAllocator;

                    // Creates new allocators

                    m_pElementAllocator = new Allocator(list.GetCapacity(), sizeof(T), QAlignment(alignof_q(T)));
                    m_pLinkAllocator = new Allocator(list.GetCapacity(), sizeof(QList::QLink), QAlignment(alignof_q(QList::QLink)));

                    pOldElementAllocator->CopyTo(*m_pLinkAllocator);
                    pOldLinkAllocator->CopyTo(*m_pElementAllocator);

                    delete pOldElementAllocator;
                    delete pOldLinkAllocator;
                }

                QListIterator iteratorOrigin = QListIterator(&list);
                QListIterator iteratorDestination = QListIterator(this);

                // Copies as many elements as it has the destination list.

                for(iteratorOrigin.MoveFirst(), iteratorDestination.MoveFirst();
                    !iteratorDestination.IsEnd();
                    ++iteratorOrigin, ++iteratorDestination)
                {
                    *iteratorDestination = *iteratorOrigin;
                }

                // Adds the rest of elements if needed.

                while(!iteratorOrigin.IsEnd())
                {
                    this->Add(*iteratorOrigin);
                    ++iteratorOrigin;
                }
            }
        }
        */
        return *this;
    }

private:

    // PROPERTIES
	// ---------------

public:

   	/// <summary>
	/// Returns a constant pointer to the element allocator.
	/// </summary>
    /// <returns>
    /// Constant pointer to the element allocator.
    /// </returns>
    const Allocator* GetAllocator() const
    {
        return m_pElementAllocator;
    }

    // ATTRIBUTES
	// ---------------

protected:

	/// <summary>
	/// Pointer to the allocator which stores the list elements.
	/// </summary>
    Allocator* m_pElementAllocator;

  	/// <summary>
	/// Pointer to the allocator which stores the double linked list for internals.
	/// </summary>
    Allocator* m_pLinkAllocator;

    /// <summary>
	/// The comparator used to compare elements.
	/// </summary>
    Comparator m_comparator;

    /// <summary>
	/// Index of the first element in the sequence. If there is no first element, its value is END_POSITION_BACKWARD constant.
	/// </summary>
    pointer_uint_q m_uFirst;

   	/// <summary>
	/// Index of the last element in the sequence. If there is no last element, its value is END_POSITION_FORWARD constant.
	/// </summary>
    pointer_uint_q m_uLast;

};

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLIST__
