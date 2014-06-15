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

#ifndef __QNTREE__
#define __QNTREE__

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
/// Represents an N-ary tree, i. e. an acyclic undirected graph whose nodes have up to a maximum number of children nodes.
/// </summary>
/// <remarks>
/// Trees are empty when they are created; to add the root node, use the the SetRootNode method.<br/>
/// The number of child nodes per node (N) is set when the tree is created. Trees with different value of N cannot interact.<br/>
/// Every node keeps a reference to its parent and its children. Removing a node implies removing all its children.<br/>
/// There is not a default way to traverse an N-ary tree, the desired method will have to be specified when necessary.<br/>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T"> The type of the list elements.</typeparam>
/// <typeparam name="AllocatorT"> The allocator used to reserve memory. The default type is QPoolAllocator.</typeparam>
/// <typeparam name="ComparatorT"> The comparator. The default type is QComparatorDefault.</typeparam>
template <class T, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class ComparatorT = QComparatorDefault<T> >
class QNTree
{

    // INTERNAL CLASSES
    // -----------------

protected:

    /// <summary>
    /// A node of the N-ary tree for internal use.
    /// </summary>
    /// <remarks>
    /// Nodes store the position of the parent node, the previous node, the next node and the first child node, in the internal
    /// contiguous chunks of memory used to store all the nodes and the elements.<br/>
    /// Child nodes are not stored in parent nodes, only the first child node is referenced and the rest are part of a double
    /// linked list formed by all the children.
    /// </remarks>
    class QNode
    {
	    // CONSTRUCTORS
	    // ---------------

    public:

        /// <summary>
        /// Constructor that receives the positions in the allocated memory chunk of the related nodes.
        /// </summary>
        /// <param name="uParent">[IN] Position of the parent of the node.</param>
        /// <param name="uNext">[IN] Position of the next node.</param>
        /// <param name="uPrevious">[IN] Position of the previous node.</param>
        /// <param name="uFirstChild">[IN] Position of the first child node of the node.</param>
        QNode(const pointer_uint_q uParent, const pointer_uint_q uNext, const pointer_uint_q uPrevious, const pointer_uint_q uFirstChild) :
                                                                                    m_uParent(uParent),
                                                                                    m_uNext(uNext),
                                                                                    m_uPrevious(uPrevious),
                                                                                    m_uFirstChild(uFirstChild)
        {
        }


        // PROPERTIES
	    // ---------------

    public:

        /// <summary>
        /// Gets the position of the parent node.
        /// </summary>
        /// <returns>
        /// The position of the parent node. Returns QNTree::END_POSITION_FORWARD if there is no parent node (it is the root node).
        /// </returns>
        pointer_uint_q GetParent() const
        {
            return m_uParent;
        }

        /// <summary>
        /// Gets the position of the next node.
        /// </summary>
        /// <returns>
        /// The position of the next node. Returns QNTree::END_POSITION_FORWARD if there is no next node (it is the last child).
        /// </returns>
        pointer_uint_q GetNext() const
        {
            return m_uNext;
        }

        /// <summary>
        /// Gets the position of the previous node.
        /// </summary>
        /// <returns>
        /// The position of the previous node. Returns QNTree::END_POSITION_FORWARD if there is no previous node (it is the first child).
        /// </returns>
        pointer_uint_q GetPrevious() const
        {
            return m_uPrevious;
        }

        /// <summary>
        /// Gets the position of the first child node.
        /// </summary>
        /// <returns>
        /// The position of the first child node. Returns QNTree::END_POSITION_FORWARD if there is no first child node.
        /// </returns>
        pointer_uint_q GetFirstChild() const
        {
            return m_uFirstChild;
        }

        /// <summary>
        /// Sets the position of the parent node.
        /// </summary>
        /// <param name="uParent">[IN] The position of the parent node. It can be QNTree::END_POSITION_FORWARD if there is no parent node (it is the root node).</param>
        void SetParent(const pointer_uint_q uParent)
        {
            m_uParent = uParent;
        }

        /// <summary>
        /// Sets the position of the next node.
        /// </summary>
        /// <param name="uNext">[IN] The position of the next node. It can be QNTree::END_POSITION_FORWARD if there is no next node (it is the last child node).</param>
        void SetNext(const pointer_uint_q uNext)
        {
            m_uNext = uNext;
        }

        /// <summary>
        /// Sets the position of the previous node.
        /// </summary>
        /// <param name="uPrevious">[IN] The position of the previous node. It can be QNTree::END_POSITION_FORWARD if there is no previous node (it is the first child node).</param>
        void SetPrevious(const pointer_uint_q uPrevious)
        {
            m_uPrevious = uPrevious;
        }

        /// <summary>
        /// Sets the position of the first child node.
        /// </summary>
        /// <param name="uFirstChild">[IN] The position of the first child node. It can be QNTree::END_POSITION_FORWARD if there is no child node (it has not got children nodes).</param>
        void SetFirstChild(const pointer_uint_q uFirstChild)
        {
            m_uFirstChild;
        }


        // ATTRIBUTES
	    // ---------------

    private:

        /// <returns>
        /// The position of the parent node. Returns QNTree::END_POSITION_FORWARD if there is no parent node (it is the root node).
        /// </returns>
        pointer_uint_q m_uParent;

        /// <returns>
        /// The position of the next node. Returns QNTree::END_POSITION_FORWARD if there is no next node (it is the last child).
        /// </returns>
        pointer_uint_q m_uNext;

        /// <returns>
        /// The position of the previous node. Returns QNTree::END_POSITION_FORWARD if there is no previous node (it is the first child).
        /// </returns>
        pointer_uint_q m_uPrevious;

        /// <returns>
        /// The position of the first child node. Returns QNTree::END_POSITION_FORWARD if there is no first child node.
        /// </returns>
        pointer_uint_q m_uFirstChild;

    };


   	// CONSTANTS
	// ---------------

    /// <summary>
    /// Number of elements for which to reserve memory by default.
    /// </summary>
    static pointer_uint_q sm_uDefaultCapacity;

	/// <summary>
	/// Constant to symbolize the absence of a node or the end of the sequence when the tree is traversed.
	/// </summary>
    static const pointer_uint_q END_POSITION_FORWARD = -1;

	/// <summary>
	/// The maximum number of child nodes per node.
	/// </summary>
    const pointer_uint_q MAX_CHILDREN;


	// CONSTRUCTORS
	// ---------------

public:

    /// <summary>
    /// Constructor that only receives the maximum number of child nodes per node in the tree.
    /// </summary>
    /// <remarks>
    /// Once the maximum number of child nodes has been set, it cannot be changed in the future.
    /// </remarks>
    /// <param name="uMaximumChildren">[IN] The maximum number of child nodes per node. It must be greater than zero.</param>
    QNTree(const pointer_uint_q uMaximumChildren) : MAX_CHILDREN(uMaximumChildren),
                                                    m_elementAllocator(QNTree::sm_uDefaultCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                                    m_nodeAllocator(QNTree::sm_uDefaultCapacity * sizeof(QNTree::QNode), sizeof(QNTree::QNode), QAlignment(alignof_q(QNTree::QNode))),
                                                    m_uRoot(QNTree::END_POSITION_FORWARD)
    {
        QE_ASSERT(uMaximumChildren > 0, "The maximum number of children for every node of the tree must be greater than zero.");
    }

    /// <summary>
    /// Constructor that receives the maximum number of child nodes per node in the tree and the initial capacity.
    /// </summary>
    /// <remarks>
    /// Once the maximum number of child nodes has been set, it cannot be changed in the future.
    /// </remarks>
    /// <param name="uMaximumChildren">[IN] The maximum number of child nodes per node. It must be greater than zero.</param>
    /// <param name="uInitialCapacity">[IN] The number of elements for which to reserve memory. It must be greater than zero.</param>
    QNTree(const pointer_uint_q uMaximumChildren, const pointer_uint_q uInitialCapacity) :
                                                            MAX_CHILDREN(uMaximumChildren),
                                                            m_elementAllocator(uInitialCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                                            m_nodeAllocator(uInitialCapacity * sizeof(QNTree::QNode), sizeof(QNTree::QNode), QAlignment(alignof_q(QNTree::QNode))),
                                                            m_uRoot(QNTree::END_POSITION_FORWARD)
    {
        QE_ASSERT(uMaximumChildren > 0, "The maximum number of children for every node of the tree must be greater than zero.");
        QE_ASSERT(uInitialCapacity > 0, "The initial capacity of the tree must be greater than zero.");
    }

protected:

    // DESTRUCTOR
	// ---------------

public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element will be called in an undetermined order.
    /// </remarks>
    ~QNTree()
    {
        /* [TODO] Thund: Uncomment when the iterator and GetFirst exists
        for(QNTree::QNTreeIterator it = this->GetFirst(); !it.IsEnd(); ++it)
            it->~T();*/
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Shrinks the capacity of the tree so it uses only the necessary amount of memory to store the existing elements.
    /// </summary>
    /// <remarks>
    /// In case the tree has allocated as many elements as its capacity indicates, nothing will happen.<br/>
    /// This operation implies a reallocation, which means:<br/>
    /// - Iterators pointing to elements of this tree may become invalid.<br/>
    /// - Any pointer to elements of this tree will be pointing to garbage.
    /// </remarks>
    void Shrink()
    {/* [TODO] Thund: Uncomment when QNTreeIterator is implemented
        // If the pool is full, it cannot be shrunk
        if(m_elementAllocator.CanAllocate())
        {
            const pointer_uint_q NUMBER_OF_BLOCKS = this->GetCapacity();
            u8_q* arOccupiedBlocks = new u8_q[NUMBER_OF_BLOCKS];

            // Marks all the block positions occupied by an element
            pointer_uint_q uElementPosition = 0;

            for(QNTree::QNTreeIterator it = this->GetFirst(); !it.IsEnd(); ++it)
            {
                uElementPosition = (T*)m_elementAllocator.GetPointer() - &(*it);
                arOccupiedBlocks[uElementPosition] = 1;
            }

            // Marks all the free blocks as allocated in the allocator so they can be used in the following loop
            while(m_elementAllocator.CanAllocate())
            {
                m_elementAllocator.Allocate();
                m_nodeAllocator.Allocate();
            }

            // Uses the marks to move elements from latest blocks to free blocks in lower positions
            pointer_uint_q uPositionOfLastBlockToBeMoved = 0;
            bool bBlockToBeMovedSelected = false;

            for(pointer_uint_q i = NUMBER_OF_BLOCKS - 1; i >= 0; --i)
            {
                // <------------------ i
                // _____________________
                // | x |   | x | x |   |
                // |___|___|___|___|___|
                //       ^_______|

                if(arOccupiedBlocks[i] == 0 && bBlockToBeMovedSelected) // If this block is free and there is a block to be moved already selected
                {
                    // Copies the occupied block to the free block
                    T* pOccupiedBlock = ((T*)m_elementAllocator.GetPointer() + uPositionOfLastBlockToBeMoved);
                    T* pFreeBlock     = ((T*)m_elementAllocator.GetPointer() + i);
                    memcpy(pFreeBlock, pOccupiedBlock, sizeof(T));

                    QNTree::QNode* pOccupiedNodeBlock = ((QNTree::QNode*)m_nodeAllocator.GetPointer() + uPositionOfLastBlockToBeMoved);
                    QNTree::QNode* pFreeNodeBlock     = ((QNTree::QNode*)m_nodeAllocator.GetPointer() + i);
                    memcpy(pFreeNodeBlock, pOccupiedNodeBlock, sizeof(T));

                    // Updates the positions of the node and the related nodes
                    this->UpdateNodesPositions(pFreeNodeBlock);

                    bBlockToBeMovedSelected = false;
                }
                else if(!bBlockToBeMovedSelected) // If this block is occupied and the block to be moved has not been selected
                {
                    uPositionOfLastBlockToBeMoved = i;
                    bBlockToBeMovedSelected = true;
                }
            }

            // Frees the list
            delete[] arOccupiedBlocks;

            // Reallocates
            m_elementAllocator.Shrink(m_elementAllocator.GetAllocatedBytes());
            m_nodeAllocator.Shrink(m_nodeAllocator.GetAllocatedBytes());
        }*/
    }

    /// <summary>
    /// Increases the capacity of the tree, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means:<br/>
    /// - Iterators pointing to elements of this tree may become invalid.<br/>
    /// - Any pointer to elements of this tree will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const pointer_uint_q uNumberOfElements)
    {
        if(uNumberOfElements > this->GetCapacity())
        {
            m_elementAllocator.Reallocate(uNumberOfElements);
            m_nodeAllocator.Reallocate(uNumberOfElements);
        }
    }

    /// <summary>
    /// Sets the root node of the tree.
    /// </summary>
    /// <remarks>
    /// If the tree is empty, the root node will be created, calling the copy constructor of the new element.<br/>
    /// If there is already a root node, then it will be assigned to the input object, calling the assignment operator of
    /// the existing element.
    /// </remarks>
    /// <param name="newRoot">[IN] The new value of the root node.</param>
    void SetRootValue(const T &newRoot)
    {
        if(this->IsEmpty())
        {
            static const pointer_uint_q NO_PARENT_POSITION = QNTree::END_POSITION_FORWARD;
            static const pointer_uint_q NO_PREVIOUS_POSITION = QNTree::END_POSITION_FORWARD;
            static const pointer_uint_q NO_NEXT_POSITION = QNTree::END_POSITION_FORWARD;
            static const pointer_uint_q NO_CHILD_POSITION = QNTree::END_POSITION_FORWARD;

            T* pNewRoot = new(m_elementAllocator.Allocate()) T(newRoot);
            QNTree::QNode* pNode = new(m_nodeAllocator.Allocate()) QNTree::QNode(NO_PARENT_POSITION, NO_NEXT_POSITION, NO_PREVIOUS_POSITION, NO_CHILD_POSITION);

            m_uRoot = pNewRoot - (T*)m_elementAllocator.GetPointer();
        }
        else
        {
            *((T*)m_elementAllocator.GetPointer() + m_uRoot) = newRoot; // [TODO] Thund: Replace with GetRootNode when it exists
        }
    }

private:

    /// <summary>
    /// Updates the reference positions of all the nodes related to one given node.
    /// </summary>
    /// <remarks>
    /// This is used when a node is moved to a different position in the internal buffer.
    /// </remarks>
    /// <param name="pNode">[IN] The node whose related nodes are to be updated.</param>
    void UpdateNodesPositions(typename QNTree::QNode* pNode)
    {
        QNTree::QNode* pFirstBlock = (QNTree::QNode*)m_nodeAllocator().GetPointer();
        const pointer_uint_q NODE_POSITION = pFirstBlock - pNode;

        // Updates the first child node position of its parent
        if(pNode->GetParent() != QNTree::END_POSITION_FORWARD)
        {
            // [ ]
            //  |
            //  v
            // [x]
            pFirstBlock[pNode->GetParent()].SetFirstChild(NODE_POSITION);
        }

        // Updates the previous node position of its previous node
        if(pNode->GetPrevious() != QNTree::END_POSITION_FORWARD)
        {
            // [ ]
            //  |
            // [ ] --> [x]
            pFirstBlock[pNode->GetPrevious()].SetNext(NODE_POSITION);
        }

        // Updates the next node position of its next node
        if(pNode->GetNext() != QNTree::END_POSITION_FORWARD)
        {
            // [ ]
            //  |
            // [x] <-- [ ]
            pFirstBlock[pNode->GetNext()].SetPrevious(NODE_POSITION);
        }

        // Updates the parent node position of all its child nodes
        if(pNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
        {
            // [x] <
            //  ^   \
            //  |    \
            // [ ] -- [ ]
            QNTree::QNode* pNextNode = pFirstBlock[pNode->GetFirstChild()];
            while(pNextNode != null_q)
            {
                pNextNode->SetParent(NODE_POSITION);

                if(pNextNode->GetNext() != QNTree::END_POSITION_FORWARD)
                    pNextNode = pFirstBlock[pNextNode->GetNext()];
                else
                    pNextNode = null_q;
            }
        }
    }


    // PROPERTIES
	// ---------------

public:

   	/// <summary>
	/// Gets the element allocator.
	/// </summary>
    /// <returns>
    /// The element allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return &m_elementAllocator;
    }

    /// <summary>
	/// Gets the capacity of the tree, which means the number of elements that can be added before they are reallocated
    /// another part of memory.
	/// </summary>
    /// <returns>
    /// The capacity of the tree.
    /// </returns>
    pointer_uint_q GetCapacity() const
    {
        return m_elementAllocator.GetPoolSize() / sizeof(T);
    }

    /// <summary>
	/// Gets the number of elements added to the tree.
	/// </summary>
    /// <returns>
    /// The number of elements in the tree.
    /// </returns>
    pointer_uint_q GetCount() const
    {
        return m_elementAllocator.GetAllocatedBytes() / sizeof(T);
    }

    /// <summary>
	/// Indicates whether the tree is empty or not.
	/// </summary>
    /// <returns>
    /// True if the tree is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const
    {
        return m_elementAllocator.GetAllocatedBytes() == 0;
    }


    // ATTRIBUTES
	// ---------------

protected:

    /// <summary>
	/// The position of the root node in the internal buffer.
	/// </summary>
    pointer_uint_q m_uRoot;

	/// <summary>
	/// The allocator which stores the tree elements.
	/// </summary>
    AllocatorT m_elementAllocator;

  	/// <summary>
	/// The allocator which stores the tree nodes for internal operations.
	/// </summary>
    AllocatorT m_nodeAllocator;

    /// <summary>
	/// The comparator used to compare elements.
	/// </summary>
    ComparatorT m_comparator;

};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template <class T, class AllocatorT, class ComparatorT>
pointer_uint_q QNTree<T, AllocatorT, ComparatorT>::sm_uDefaultCapacity = 1;


} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QNTREE__
