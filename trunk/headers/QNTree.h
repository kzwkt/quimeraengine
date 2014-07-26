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
#include "EQTreeTraversalOrder.h"
#include "EQIterationDirection.h"

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
/// <typeparam name="T"> The type of the tree elements.</typeparam>
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
    
public:

    /// <summary>
    /// Iterator that steps once per element of an n-ary tree, in a concrete order. Since the traversal order may vary, the meaning of the words
    /// "last", "first" and "next", used in the documentation of this class, can be different depending on such order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a tree, it cannot point to another tree ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the tree.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QNTreeIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the tree to iterate through, the position to physically point to and the traversal order. This constructor is intended 
        /// to be used internally, use GetConstIterator and GetIterator methods instead.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pTree">[IN] The tree to iterate through. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of tree elements, but the physical.
        /// It must be lower than the capacity of the tree.</param>
        /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
        QNTreeIterator(const QNTree* pTree, const pointer_uint_q uPosition, const EQTreeTraversalOrder &eTraversalOrder) : m_pTree(pTree), 
                                                                                                                           m_uPosition(uPosition), 
                                                                                                                           m_eTraversalOrder(eTraversalOrder)
        {
            QE_ASSERT(pTree != null_q, "Invalid argument: The pointer to the tree cannot be null");
            QE_ASSERT(pTree->GetCapacity() > uPosition, "Invalid argument: The position must be lower than the capacity of the tree");

            if(pTree == null_q || pTree->GetCapacity() <= uPosition || pTree->IsEmpty())
                m_uPosition = QNTree::END_POSITION_FORWARD;
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator. The traversal order is also copied.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same tree as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        QNTreeIterator& operator=(const QNTreeIterator &iterator)
        {
            QE_ASSERT(m_pTree == iterator.m_pTree, "The input iterator points to a different tree");

            if(m_pTree == iterator.m_pTree)
            {
                m_uPosition = iterator.m_uPosition;
                m_eTraversalOrder = iterator.m_eTraversalOrder;
            }

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the tree element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the tree element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T& operator*() const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the tree element");

            QE_ASSERT(m_uPosition != QNTree::END_POSITION_FORWARD && m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return *(((T*)m_pTree->m_pElementAllocator->GetPointer()) + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the tree element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the tree element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T* operator->() const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the tree element");

            QE_ASSERT(m_uPosition != QNTree::END_POSITION_FORWARD && m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return ((T*)m_pTree->m_pElementAllocator->GetPointer()) + m_uPosition;
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
        QNTreeIterator operator++(int)
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT(m_uPosition != QNTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QNTreeIterator iteratorCopy = *this;

            if(m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                switch(m_eTraversalOrder)
                {
                case EQTreeTraversalOrder::E_DepthFirstPreOrder:
                    {
                        //          1
                        //         /|\
                        //        / | \
                        //       2  5  6
                        //      / \     \
                        //     /   \     \
                        //    3     4     7

                        if(m_uPosition != QNTree::END_POSITION_BACKWARD)
                        {
                            QNTree::QNode* pNode = (QNTree::QNode*)m_pTree->m_nodeAllocator.GetPointer() + m_uPosition;

                            if(pNode->GetFirstChild() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no children

                                if(pNode->GetNext() == QNTree::END_POSITION_FORWARD)
                                {
                                    // This node has no more brothers

                                    // Goes up in the tree until it finds a parent with non-visited brothers or it reaches the root node
                                    QNTree::QNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QNTree::QNode*);

                                    while(pNode->GetParent() != QNTree::END_POSITION_FORWARD && 
                                          (pBasePointer + pNode->GetParent())->GetNext() == QNTree::END_POSITION_FORWARD)
                                    {
                                        // Visits current node's parent
                                        pNode = pBasePointer + pNode->GetParent();
                                    }

                                    if(pNode->GetParent() == QNTree::END_POSITION_FORWARD)
                                    {
                                        // It reached the root node, all the nodes have been visited
                                        m_uPosition = QNTree::END_POSITION_FORWARD;
                                    }
                                    else
                                    {
                                        // It finds an ascendant whose brothers haven't been visited yet
                                        m_uPosition = (pBasePointer + pNode->GetParent())->GetNext();
                                    }
                                }
                                else // pNode->GetNext() == QNTree::END_POSITION_FORWARD
                                {
                                    // The next brother is visited
                                    m_uPosition = pNode->GetNext();
                                }
                            }
                            else // pNode->GetFirstChild() == QNTree::END_POSITION_FORWARD
                            {
                                // The first child of the current node is visited
                                m_uPosition = pNode->GetFirstChild();
                            }
                        }
                        else // m_uPosition != QNTree::END_POSITION_BACKWARD
                        {
                            if(m_pTree->m_uRoot != QNTree::END_POSITION_FORWARD)
                            {
                                this->MoveFirst();
                            }
                            else
                            {
                                // The tree is empty
                                m_uPosition = QNTree::END_POSITION_FORWARD;
                            }
                        }
                    }
                }
            } // if(m_uPosition != QNTree::END_POSITION_FORWARD)

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
        QNTreeIterator operator--(int)
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT(m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QNTreeIterator iteratorCopy = *this;

            if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                switch(m_eTraversalOrder)
                {
                case EQTreeTraversalOrder::E_DepthFirstPreOrder:
                    {
                        //          7
                        //         /|\
                        //        / | \
                        //       6  3  2
                        //      / \     \
                        //     /   \     \
                        //    5     4     1

                        if(m_uPosition != QNTree::END_POSITION_FORWARD)
                        {
                            QNTree::QNode* pNode = ((QNTree::QNode*)m_pTree->m_nodeAllocator.GetPointer() + m_uPosition);

                            if(pNode->GetPrevious() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no previous brother

                                if(pNode->Parent() == QNTree::END_POSITION_FORWARD)
                                {
                                    // The current node has no parent so it is the root, all the nodes have been visited
                                    m_uPosition = QNTree::END_POSITION_BACKWARD;
                                }
                                else
                                {
                                    // The current node's parent is visited
                                    m_uPosition = pNode->Parent();
                                }
                            }
                            else
                            {
                                // The current node has a previous brother
                                QNTree::QNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QNTree::QNode*);
                                pNode = pBasePointer + pNode->GetPrevious();

                                // Searches for the last child of the deepest descendant
                                while(pNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
                                {
                                    pNode = pBasePointer + pNode->GetFirstChild();

                                    while(pNode->GetNext() != QNTree::END_POSITION_FORWARD)
                                    {
                                        pNode = pBasePointer + pNode->GetNext();
                                    }
                                }

                                m_uPosition = scast_q(pNode - pBasePointer, pointer_uint_q);
                            }
                        }
                        else // m_uPosition == QNTree::END_POSITION_FORWARD
                        {
                            if(m_pTree->m_uRoot != QNTree::END_POSITION_FORWARD)
                            {
                                this->MoveLast();
                            }
                            else
                            {
                                // The tree is empty
                                m_uPosition = QNTree::END_POSITION_BACKWARD;
                            }
                        }
                    }
                }
            } // if(m_uPosition != QNTree::END_POSITION_BACKWARD)

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
        QNTreeIterator& operator++()
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT(m_uPosition != QNTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                switch(m_eTraversalOrder)
                {
                case EQTreeTraversalOrder::E_DepthFirstPreOrder:
                    {
                        //          1
                        //         /|\
                        //        / | \
                        //       2  5  6
                        //      / \     \
                        //     /   \     \
                        //    3     4     7

                        if(m_uPosition != QNTree::END_POSITION_BACKWARD)
                        {
                            QNTree::QNode* pNode = (QNTree::QNode*)m_pTree->m_nodeAllocator.GetPointer() + m_uPosition;

                            if(pNode->GetFirstChild() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no children

                                if(pNode->GetNext() == QNTree::END_POSITION_FORWARD)
                                {
                                    // This node has no more brothers
                                    // Goes up in the tree until it finds a parent with non-visited brothers or it reaches the root node
                                    QNTree::QNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QNTree::QNode*);

                                    while(pNode->GetParent() != QNTree::END_POSITION_FORWARD && 
                                          (pBasePointer + pNode->GetParent())->GetNext() == QNTree::END_POSITION_FORWARD)
                                    {
                                        // Visits current node's parent
                                        pNode = pBasePointer + pNode->GetParent();
                                    }

                                    if(pNode->GetParent() == QNTree::END_POSITION_FORWARD)
                                    {
                                        // It reached the root node, all the nodes have been visited
                                        m_uPosition = QNTree::END_POSITION_FORWARD;
                                    }
                                    else // pNode->GetParent()->GetNext() != QNTree::END_POSITION_FORWARD
                                    {
                                        // It finds an ascendant whose brothers haven't been visited yet
                                        m_uPosition = (pBasePointer + pNode->GetParent())->GetNext();
                                    }
                                }
                                else
                                {
                                    // The next brother is visited
                                    m_uPosition = pNode->GetNext();
                                }
                            }
                            else
                            {
                                // The first child of the current node is visited
                                m_uPosition = pNode->GetFirstChild();
                            }
                        }
                        else // m_uPosition == QNTree::END_POSITION_BACKWARD
                        {
                            if(m_pTree->IsEmpty())
                            {
                                m_uPosition = QNTree::END_POSITION_FORWARD;
                            }
                            else
                            {
                                this->MoveFirst();
                            }
                        }
                    }
                }
            } // if(m_uPosition != QNTree::END_POSITION_FORWARD)

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
        QNTreeIterator& operator--()
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT(m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                switch(m_eTraversalOrder)
                {
                case EQTreeTraversalOrder::E_DepthFirstPreOrder:
                    {
                        //          7
                        //         /|\
                        //        / | \
                        //       6  3  2
                        //      / \     \
                        //     /   \     \
                        //    5     4     1

                        if(m_uPosition != QNTree::END_POSITION_FORWARD)
                        {
                            QNTree::QNode* pNode = ((QNTree::QNode*)m_pTree->m_nodeAllocator.GetPointer() + m_uPosition);

                            if(pNode->GetPrevious() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no previous brother

                                if(pNode->Parent() == QNTree::END_POSITION_FORWARD)
                                {
                                    // The current node has no parent so it is the root, all the nodes have been visited
                                    m_uPosition = QNTree::END_POSITION_BACKWARD;
                                }
                                else
                                {
                                    // The current node's parent is visited
                                    m_uPosition = pNode->Parent();
                                }
                            }
                            else
                            {
                                // The current node has a previous brother
                                QNTree::QNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QNTree::QNode*);
                                pNode = pBasePointer + pNode->GetPrevious();

                                // Searches for the last child of the deepest descendant
                                while(pNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
                                {
                                    pNode = pBasePointer + pNode->GetFirstChild();

                                    while(pNode->GetNext() != QNTree::END_POSITION_FORWARD)
                                    {
                                        pNode = pBasePointer + pNode->GetNext();
                                    }
                                }

                                m_uPosition = scast_q(pNode - pBasePointer, pointer_uint_q);
                            }
                        }
                        else // m_uPosition == QNTree::END_POSITION_FORWARD
                        {
                            if(m_pTree->IsEmpty())
                            {
                                // The tree is empty
                                m_uPosition = QNTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                this->MoveLast();
                            }
                        }
                    }
                }
            } // if(m_uPosition != QNTree::END_POSITION_BACKWARD)

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same tree to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same tree; False otherwise.
        /// </returns>
        bool operator==(const QNTreeIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            return m_uPosition == iterator.m_uPosition && m_pTree == iterator.m_pTree;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different tree is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different tree; False otherwise.
        /// </returns>
        bool operator!=(const QNTreeIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            return m_uPosition != iterator.m_uPosition || m_pTree != iterator.m_pTree;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const QNTreeIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QNTree::END_POSITION_FORWARD &&
               m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                QNTree::QNTreeIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator does not equal the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const QNTreeIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QNTree::END_POSITION_BACKWARD &&
               m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                QNTree::QNTreeIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator equals the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const QNTreeIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QNTree::QNTreeIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator does not equal the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const QNTreeIterator &iterator) const
        {
            QE_ASSERT(this->IsValid(), "The iterator is not valid");
            QE_ASSERT(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QNTree::QNTreeIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator equals the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the tree.
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
            return m_uPosition == QNTree::END_POSITION_BACKWARD || m_uPosition == QNTree::END_POSITION_FORWARD;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the tree, distinguishing which of them.
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
            return (eIterationDirection == EQIterationDirection::E_Backward && m_uPosition == QNTree::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EQIterationDirection::E_Forward  && m_uPosition == QNTree::END_POSITION_FORWARD);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            if(m_pTree->IsEmpty())
            {
                m_uPosition = QNTree::END_POSITION_FORWARD;
            }
            else
            {
                switch(m_eTraversalOrder)
                {
                case EQTreeTraversalOrder::E_DepthFirstPreOrder:
                    {
                        // In this order, the first node will be always the root
                        m_uPosition = m_pTree->m_uRoot;
                    }
                }
            }
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            if(m_pTree->IsEmpty())
            {
                m_uPosition = QNTree::END_POSITION_FORWARD;
            }
            else
            {
                switch(m_eTraversalOrder)
                {
                case EQTreeTraversalOrder::E_DepthFirstPreOrder:
                    {
                        // The current node has a previous brother
                        QNTree::QNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QNTree::QNode*);
                        QNTree::QNode* pNode = pBasePointer + m_pTree->m_uRoot;

                        // Searches for the last child of the deepest descendant
                        while(pNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
                        {
                            pNode = pBasePointer + pNode->GetFirstChild();

                            while(pNode->GetNext() != QNTree::END_POSITION_FORWARD)
                            {
                                pNode = pBasePointer + pNode->GetNext();
                            }
                        }

                        m_uPosition = scast_q(pNode - pBasePointer, pointer_uint_q);
                    }
                }
            }
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a tree may have been shortened while the iterator
        /// was pointing to its last position). If the tree to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_pTree != null_q && 
                   (m_uPosition < m_pTree->m_nodeAllocator.GetPoolSize() / sizeof(QNode) ||
                    m_uPosition == QNTree::END_POSITION_BACKWARD ||
                    m_uPosition == QNTree::END_POSITION_FORWARD);
        }


        // ATTRIBUTES
	    // ---------------
    protected:

        /// <summary>
        /// The tree the iterator points to.
        /// </summary>
        const QNTree* m_pTree;

        /// <summary>
        /// The current iteration position regarding the base position of the buffer (zero). It is zero-based.
        /// </summary>
        pointer_uint_q m_uPosition;

        /// <summary>
        /// The order in which elements will be visited.
        /// </summary>
        const EQTreeTraversalOrder m_eTraversalOrder;

    }; // QNTreeIterator


   	// CONSTANTS
    // ---------------

    /// <summary>
    /// Number of elements for which to reserve memory by default.
    /// </summary>
    static pointer_uint_q sm_uDefaultCapacity;
    
	/// <summary>
	/// Constant to symbolize the end of the sequence when the tree is traversed backward.
	/// </summary>
    static const pointer_uint_q END_POSITION_BACKWARD = -2;

    /// <summary>
    /// Constant to symbolize the absence of a node or the end of the sequence when the tree is traversed forward.
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
            m_elementAllocator.Reallocate(uNumberOfElements * sizeof(T));
            m_nodeAllocator.Reallocate(uNumberOfElements * sizeof(QNTree::QNode));
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
            new(m_nodeAllocator.Allocate()) QNTree::QNode(NO_PARENT_POSITION, NO_NEXT_POSITION, NO_PREVIOUS_POSITION, NO_CHILD_POSITION);

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
    /// The allocator which stores the tree elements.
    /// </summary>
    AllocatorT m_elementAllocator;

      /// <summary>
    /// The allocator which stores the tree nodes for internal operations.
    /// </summary>
    AllocatorT m_nodeAllocator;

    /// <summary>
    /// The position of the root node in the internal buffer.
    /// </summary>
    pointer_uint_q m_uRoot;
    
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
