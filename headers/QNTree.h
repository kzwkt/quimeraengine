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
#include "SQInteger.h"

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
/// The number of child nodes per node (N) is set when the tree is created. Trees with different value of N cannot interact in certain scenarios. However, 
/// trees can be created without that restriction by using the NO_MAX_CHILDREN constant.<br/>
/// Every node keeps a reference to its parent and its children. Removing a node implies removing all its children.<br/>
/// There is not a default way to traverse an N-ary tree, the desired method will have to be specified when necessary.<br/>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of the tree elements.</typeparam>
/// <typeparam name="AllocatorT">The allocator used to reserve memory. The default type is QPoolAllocator.</typeparam>
/// <typeparam name="ComparatorT">The comparator. The default type is QComparatorDefault.</typeparam>
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
            m_uFirstChild = uFirstChild;
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
    /// Iterator that steps once per element of an n-ary tree, in a concrete order, and does not allow the modification of them. Since the traversal order may vary, the meaning of the words
    /// "last", "first" and "next", used in the documentation of this class, can be different depending on such order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a tree, it cannot point to another tree ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the tree.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QConstNTreeIterator
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
        /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited. Currently, only depth-first pre-order is supported.</param>
        QConstNTreeIterator(const QNTree* pTree, const pointer_uint_q uPosition, const EQTreeTraversalOrder &eTraversalOrder) : m_pTree(pTree), 
                                                                                                                           m_uPosition(uPosition), 
                                                                                                                           m_eTraversalOrder(eTraversalOrder)
        {
            QE_ASSERT_ERROR(pTree != null_q, "Invalid argument: The pointer to the tree cannot be null");
            QE_ASSERT_WARNING(pTree->GetCapacity() > uPosition || 
                              uPosition == QNTree::END_POSITION_BACKWARD || 
                              uPosition == QNTree::END_POSITION_FORWARD, "Invalid argument: The position must be lower than the capacity of the tree");
            QE_ASSERT_ERROR(eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder, string_q("The traversal order specified (") + eTraversalOrder.ToString() + ") is not supported. The only traversal order available currently is: DepthFirstPreOrder.");

            if(pTree == null_q || 
               (pTree->GetCapacity() <= uPosition && uPosition != QNTree::END_POSITION_BACKWARD && uPosition != QNTree::END_POSITION_FORWARD) || 
               pTree->IsEmpty())
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
        QConstNTreeIterator& operator=(const QConstNTreeIterator &iterator)
        {
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid.");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "The input iterator points to a different tree");
            QE_ASSERT_WARNING(m_eTraversalOrder == iterator.m_eTraversalOrder, "The iterators have different traversal order.");

            if(m_pTree == iterator.m_pTree)
            {
                m_uPosition = iterator.m_uPosition;
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
        const T& operator*() const
        {
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the tree element");

            QE_ASSERT_ERROR(m_uPosition != QNTree::END_POSITION_FORWARD && m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return *(scast_q(m_pTree->m_elementAllocator.GetPointer(), T*) + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the tree element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the tree element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T* operator->() const
        {
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the tree element");

            QE_ASSERT_ERROR(m_uPosition != QNTree::END_POSITION_FORWARD && m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return scast_q(m_pTree->m_elementAllocator.GetPointer(), T*) + m_uPosition;
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
        QConstNTreeIterator operator++(int)
        {
            // Note: This code is a copy of the same method of QConstNTreeIterator (replacing QConstNTreeIterator with QConstNTreeIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QConstNTreeIterator iteratorCopy = *this;

            if(m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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
            } // if(m_uPosition != QNTree::END_POSITION_FORWARD)
            else if(m_uPosition == QNTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

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
        QConstNTreeIterator operator--(int)
        {
            // Note: This code is a copy of the same method of QConstNTreeIterator (replacing QConstNTreeIterator with QConstNTreeIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QConstNTreeIterator iteratorCopy = *this;

            if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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

                            if(pNode->GetParent() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = QNTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
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
            } // if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            else if(m_uPosition == QNTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

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
        QConstNTreeIterator& operator++()
        {
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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
            } // if(m_uPosition != QNTree::END_POSITION_FORWARD)
            else if(m_uPosition == QNTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

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
        QConstNTreeIterator& operator--()
        {
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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

                            if(pNode->GetParent() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = QNTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
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
            } // if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            else if(m_uPosition == QNTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

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
        bool operator==(const QConstNTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

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
        bool operator!=(const QConstNTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

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
        bool operator>(const QConstNTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QNTree::END_POSITION_FORWARD &&
               m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                QNTree::QConstNTreeIterator iteratorFromThis = *this;

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
        bool operator<(const QConstNTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QNTree::END_POSITION_BACKWARD &&
               m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                QNTree::QConstNTreeIterator iteratorFromThis = *this;

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
        bool operator>=(const QConstNTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QNTree::QConstNTreeIterator iteratorFromThis = *this;

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
        bool operator<=(const QConstNTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    QNTree::QConstNTreeIterator iteratorFromThis = *this;

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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid.");

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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid.");

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
            // Note: This code is a copy of the same method of QConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = QNTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    // In this order, the first node will be always the root
                    m_uPosition = m_pTree->m_uRoot;
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
            // Note: This code is a copy of the same method of QConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = QNTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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
        
        /// <summary>
        /// Gets the order in which the iterator traverses the tree.
        /// </summary>
        /// <returns>
        /// The tree traversal order.
        /// </returns>
        EQTreeTraversalOrder GetTraversalOrder() const
        {
            return m_eTraversalOrder;
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

    }; // QConstNTreeIterator

    
    /// <summary>
    /// Iterator that steps once per element of an n-ary tree, in a concrete order. Since the traversal order may vary, the meaning of the words
    /// "last", "first" and "next", used in the documentation of this class, can be different depending on such order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a tree, it cannot point to another tree ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the tree.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QNTreeIterator : public QNTree::QConstNTreeIterator
    {
        
    protected:
    
        using QNTree::QConstNTreeIterator::m_pTree;
        using QNTree::QConstNTreeIterator::m_uPosition;
        using QNTree::QConstNTreeIterator::m_eTraversalOrder;


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
        QNTreeIterator(const QNTree* pTree, const pointer_uint_q uPosition, const EQTreeTraversalOrder &eTraversalOrder) : QNTree::QConstNTreeIterator(pTree, uPosition, eTraversalOrder)
        {
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
            QNTree::QConstNTreeIterator::operator=(iterator);
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
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the tree element");

            QE_ASSERT_ERROR(m_uPosition != QNTree::END_POSITION_FORWARD && m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return *(scast_q(m_pTree->m_elementAllocator.GetPointer(), T*) + m_uPosition);
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
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the tree element");

            QE_ASSERT_ERROR(m_uPosition != QNTree::END_POSITION_FORWARD && m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return scast_q(m_pTree->m_elementAllocator.GetPointer(), T*) + m_uPosition;
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
            // Note: This code is a copy of the same method of QConstNTreeIterator (replacing QConstNTreeIterator with QNTreeIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QNTreeIterator iteratorCopy = *this;

            if(m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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
            } // if(m_uPosition != QNTree::END_POSITION_FORWARD)
            else if(m_uPosition == QNTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

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
            // Note: This code is a copy of the same method of QConstNTreeIterator (replacing QConstNTreeIterator with QNTreeIterator)

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QNTreeIterator iteratorCopy = *this;

            if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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

                            if(pNode->GetParent() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = QNTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
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
            } // if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            else if(m_uPosition == QNTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

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
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition != QNTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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
            } // if(m_uPosition != QNTree::END_POSITION_FORWARD)
            else if(m_uPosition == QNTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

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
            // Note: This code is a copy of the same method of QConstNTreeIterator

            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QNTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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

                            if(pNode->GetParent() == QNTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = QNTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
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
            } // if(m_uPosition != QNTree::END_POSITION_BACKWARD)
            else if(m_uPosition == QNTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

            return *this;
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of QConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = QNTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    // In this order, the first node will be always the root
                    m_uPosition = m_pTree->m_uRoot;
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
            // Note: This code is a copy of the same method of QConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = QNTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstPreOrder)
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


    }; // QNTreeIterator


   	// CONSTANTS
    // ---------------
public:
    
    /// <summary>
    /// Constant used to specify that the tree nodes have no maximum child nodes restriction.
    /// </summary>
    static const pointer_uint_q NO_MAXIMUM_CHILDREN = -1;

protected:

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

private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float REALLOCATION_FACTOR;
    

    // CONSTRUCTORS
    // ---------------

public:

    /// <summary>
    /// Constructor that only receives the maximum number of child nodes per node in the tree.
    /// </summary>
    /// <remarks>
    /// Once the maximum number of child nodes has been set, it cannot be changed in the future.
    /// </remarks>
    /// <param name="uMaximumChildren">[IN] The maximum number of child nodes per node. It must be greater than zero. Use the NO_MAXIMUM_CHILDREN constant to disable this restriction.</param>
    QNTree(const pointer_uint_q uMaximumChildren) : MAX_CHILDREN(uMaximumChildren),
                                                    m_elementAllocator(QNTree::sm_uDefaultCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                                    m_nodeAllocator(QNTree::sm_uDefaultCapacity * sizeof(QNTree::QNode), sizeof(QNTree::QNode), QAlignment(alignof_q(QNTree::QNode))),
                                                    m_uRoot(QNTree::END_POSITION_FORWARD)
    {
        QE_ASSERT_ERROR(uMaximumChildren > 0, "The maximum number of children for every node of the tree must be greater than zero.");
    }

    /// <summary>
    /// Constructor that receives the maximum number of child nodes per node in the tree and the initial capacity.
    /// </summary>
    /// <remarks>
    /// Once the maximum number of child nodes has been set, it cannot be changed in the future.
    /// </remarks>
    /// <param name="uMaximumChildren">[IN] The maximum number of child nodes per node. It must be greater than zero. Use the NO_MAXIMUM_CHILDREN constant to disable this restriction.</param>
    /// <param name="uInitialCapacity">[IN] The number of elements for which to reserve memory. It must be greater than zero.</param>
    QNTree(const pointer_uint_q uMaximumChildren, const pointer_uint_q uInitialCapacity) :
                                                            MAX_CHILDREN(uMaximumChildren),
                                                            m_elementAllocator(uInitialCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                                            m_nodeAllocator(uInitialCapacity * sizeof(QNTree::QNode), sizeof(QNTree::QNode), QAlignment(alignof_q(QNTree::QNode))),
                                                            m_uRoot(QNTree::END_POSITION_FORWARD)
    {
        QE_ASSERT_ERROR(uMaximumChildren > 0, "The maximum number of children for every node of the tree must be greater than zero.");
        QE_ASSERT_ERROR(uInitialCapacity > 0, "The initial capacity of the tree must be greater than zero.");
    }

    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every copied element, in an arbitrary order.
    /// </remarks>
    /// <param name="tree">[IN] The other tree to be copied.</param>
    QNTree(const QNTree &tree) :
                                MAX_CHILDREN(tree.MAX_CHILDREN),
                                m_elementAllocator(tree.GetCapacity() * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                m_nodeAllocator(tree.GetCapacity() * sizeof(QNTree::QNode), sizeof(QNTree::QNode), QAlignment(alignof_q(QNTree::QNode))),
                                m_uRoot(tree.m_uRoot)
    {
        if(!tree.IsEmpty())
        {
            tree.m_elementAllocator.CopyTo(m_elementAllocator);
            tree.m_nodeAllocator.CopyTo(m_nodeAllocator);

            QNTree::QNTreeIterator itSource = tree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
            QNTree::QNTreeIterator itDestination = this->GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);

            for(; !itSource.IsEnd(); ++itSource, ++itDestination)
                new(&*itDestination) T(*itSource);
        }
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
        if(!this->IsEmpty())
            for(QNTree::QConstNTreeIterator it = this->GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder); !it.IsEnd(); ++it)
                (*it).~T();
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Assignment operator that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// All the elements in the resident tree will be firstly removed, calling each element's destructor.
    /// The copy constructor is then called for every copied element, in an arbitrary order.
    /// </remarks>
    /// <param name="tree">[IN] The other tree to be copied. The maximum number of children per node in the tree must 
    /// be lower than or equal to the resident tree's.</param>
    QNTree& operator=(const QNTree &tree)
    {
        QE_ASSERT_ERROR(MAX_CHILDREN >= tree.MAX_CHILDREN && MAX_CHILDREN != QNTree::NO_MAXIMUM_CHILDREN, "The maximum number of children per node in the resident tree is lower than the input tree's.");

        if(this != &tree)
        {
            if(!this->IsEmpty())
                this->Clear();

            if(!tree.IsEmpty())
            {
                m_uRoot = tree.m_uRoot;

                if(this->GetCapacity() < tree.GetCapacity())
                    this->Reserve(tree.GetCapacity());

                tree.m_elementAllocator.CopyTo(m_elementAllocator);
                tree.m_nodeAllocator.CopyTo(m_nodeAllocator);

                QNTree::QNTreeIterator itSource = tree.GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);
                QNTree::QNTreeIterator itDestination = this->GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);

                for(; !itSource.IsEnd(); ++itSource, ++itDestination)
                    new(&*itDestination) T(*itSource);
            }
        }

        return *this;
    }
    
    /// <summary>
    /// Equality operator that checks whether two trees are equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other tree. Elements are compared using the tree's comparator.<br/>
    /// Trees are compared morphologically too, so if an element A is a child of another element B in one of the trees, this relation must exist in the other tree to be considered equal.
    /// </remarks>
    /// <param name="tree">[IN] The tree to compare to.</param>
    /// <returns>
    /// True if all the elements of both trees are equal and the trees have the same structure; False otherwise.
    /// </returns>
    bool operator==(const QNTree &tree) const
    {
        bool bAreEqual = true;

        // If they are not the same instance
        if(this != &tree)
        {
            // If they have the same number of elements
            if(this->GetCount() == tree.GetCount())
            {
                // Both trees are traversed in the same order
                QNTree::QNTreeIterator itThis = this->GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);
                QNTree::QNTreeIterator itInput = tree.GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder);

                QNTree::QNode* pNodeBasePointerThis  = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
                QNTree::QNode* pNodeBasePointerInput = scast_q(tree.m_nodeAllocator.GetPointer(), QNTree::QNode*);
                T* pElementBasePointerThis  = scast_q(m_elementAllocator.GetPointer(), T*);
                T* pElementBasePointerInput = scast_q(tree.m_elementAllocator.GetPointer(), T*);

                QNTree::QNode* pCurrentNodeThis = null_q;
                QNTree::QNode* pCurrentNodeInput = null_q;

                pointer_uint_q uCurrentNodePositionThis = 0;
                pointer_uint_q uCurrentNodePositionInput = 0;

                while(bAreEqual && !itThis.IsEnd())
                {
                    // Note: Both trees can have the same structure and be physically ordered differently in memory

                    uCurrentNodePositionThis = &*itThis - pElementBasePointerThis;
                    uCurrentNodePositionInput = &*itInput - pElementBasePointerInput;

                    pCurrentNodeThis = pNodeBasePointerThis + uCurrentNodePositionThis;
                    pCurrentNodeInput = pNodeBasePointerInput + uCurrentNodePositionInput;

                    // The value of the current element is checked
                    bAreEqual = m_comparator.Compare(*itThis, *itInput) == 0
                    // The relations of the current node are checked too
                                && ((pCurrentNodeThis->GetFirstChild() != QNTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetFirstChild() != QNTree::END_POSITION_FORWARD))
                                && ((pCurrentNodeThis->GetNext() != QNTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetNext() != QNTree::END_POSITION_FORWARD))
                                && ((pCurrentNodeThis->GetPrevious() != QNTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetPrevious() != QNTree::END_POSITION_FORWARD))
                                && ((pCurrentNodeThis->GetParent() != QNTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetParent() != QNTree::END_POSITION_FORWARD));

                    ++itThis;
                    ++itInput;
                }
            }
            else
                bAreEqual = false;
        }

        return bAreEqual;
    }
    
    /// <summary>
    /// Inequality operator that checks whether two trees are not equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other tree. Elements are compared using the tree's comparator.<br/>
    /// Trees are compared morphologically too, so if an element A is a child of another element B in one of the trees, this relation must exist in the other tree to be considered equal.
    /// </remarks>
    /// <param name="tree">[IN] The tree to compare to.</param>
    /// <returns>
    /// True if not all the elements of both trees are equal or if the trees do not have the same structure; False otherwise.
    /// </returns>
    bool operator!=(const QNTree &tree) const
    {
        return !this->operator==(tree);
    }

    /// <summary>
    /// Increases the capacity of the tree, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means that any pointer to elements of this tree will be pointing to garbage.
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
    
    /// <summary>
    /// Adds an element at the last position of the child node list.
    /// </summary>
    /// <remarks>
    /// If the tree is empty, use the SetRootValue method.<br/>
    /// If the parent node already has the maximum number of child nodes, the new element will not be added.<br/>
    /// If the capacity of the tree is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the new element will be called.
    /// </remarks>
    /// <param name="parentNode">[IN] An iterator that points to the parent node to which the element will be added as a child. It must not point to an end position.</param>
    /// <param name="newElement">[IN] The value of the new element.</param>
    /// <returns>
    /// An iterator that points to the just added element. If it was not added, the iterator will point to an end position.
    /// </returns>
    QNTreeIterator AddChild(const typename QNTree::QConstNTreeIterator &parentNode, const T &newElement)
    {
        //        R
        //       / \
        //      0-...
        //     /|\
        //    0-1-2-X
        //
        using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pParentNode = pBaseNodePointer + uNodePosition;
        
        pointer_uint_q uNewNodePosition = QNTree::END_POSITION_FORWARD;

        // If the parent node has any child node
        if(pParentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
        {
            QNTree::QNode* pCurrentNode = pBaseNodePointer + pParentNode->GetFirstChild();
            pointer_uint_q uNumberOfElements = 1U;

            // Navigates to the last child node
            while(pCurrentNode->GetNext() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetNext();
                ++uNumberOfElements;
            }

            QE_ASSERT_ERROR(uNumberOfElements < MAX_CHILDREN, string_q("It is not possible to add another child to this node, maximum allowed exceeded (") + SQInteger::ToString(MAX_CHILDREN) + ").");

            if(uNumberOfElements < MAX_CHILDREN)
            {
                // Reserves more memory if necessary
                if(this->GetCount() == this->GetCapacity())
                {
                    pointer_uint_q uLastNodePosition = pCurrentNode - pBaseNodePointer;
                    this->_ReallocateByFactor(this->GetCapacity() + 1U);
                    pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
                    pCurrentNode = pBaseNodePointer + uLastNodePosition;
                }

                // Adds the child to the end of the child list
                QNTree::QNode* pNewNode = new(m_nodeAllocator.Allocate()) QNode(uNodePosition, QNTree::END_POSITION_FORWARD, pCurrentNode - pBaseNodePointer, QNTree::END_POSITION_FORWARD);

                uNewNodePosition = pNewNode - pBaseNodePointer;
                pCurrentNode->SetNext(uNewNodePosition);
                
                // Copies the new element
                new(m_elementAllocator.Allocate()) T(newElement);
            }
        }
        else
        {
            // Reserves more memory if necessary
            if(this->GetCount() == this->GetCapacity())
            {
                this->_ReallocateByFactor(this->GetCapacity() + 1U);
                pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
                pParentNode = pBaseNodePointer + uNodePosition;
            }

            // Adds the child as the first of the child list
            QNTree::QNode* pNewNode = new(m_nodeAllocator.Allocate()) QNode(uNodePosition, QNTree::END_POSITION_FORWARD, QNTree::END_POSITION_FORWARD, QNTree::END_POSITION_FORWARD);

            uNewNodePosition = pNewNode - pBaseNodePointer;
            pParentNode->SetFirstChild(uNewNodePosition);

            // Copies the new element
            new(m_elementAllocator.Allocate()) T(newElement);
        }

        return QNTree::QNTreeIterator(this, uNewNodePosition, parentNode.GetTraversalOrder());
    }
    
    /// <summary>
    /// Removes an element from the tree and all its descendents.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called in an undefined order, from bottom to top.
    /// </remarks>
    /// <param name="node">[IN] An iterator that points to the node to be removed. It must not point to an end position. The root element is a valid target.</param>
    /// <returns>
    /// An iterator that points to the next element (following the traversal order of the input iterator). If the element was the last one, the iterator will point to an end position.
    /// </returns>
    QNTreeIterator Remove(const typename QNTree::QNTreeIterator &node)
    {
        //        X
        //       / \
        //      X-...
        //     /|\
        //    X-X-X...
        //
        
        QE_ASSERT_ERROR(node.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!node.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uNodePosition = &*node - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pNode = pBaseNodePointer + uNodePosition;

        QNTree::QNTreeIterator resultantIterator = node;
        ++resultantIterator;

        QNTree::QNode* pCurrentNode = pNode;
        QNTree::QNode* pNodeToRemove = null_q;

        // Traverses the tree in any order to remove the entire subtree defined by the input node
        do
        {
            if(pCurrentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetFirstChild();
            }
            else if(pCurrentNode->GetNext() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetNext();
            }
            else
            {
                pNodeToRemove = pCurrentNode;

                if(pCurrentNode->GetPrevious() != QNTree::END_POSITION_FORWARD)
                {
                    pCurrentNode = pBaseNodePointer + pCurrentNode->GetPrevious();
                    pCurrentNode->SetNext(QNTree::END_POSITION_FORWARD);
                }
                else if(pCurrentNode->GetParent() != QNTree::END_POSITION_FORWARD)
                {
                    pCurrentNode = pBaseNodePointer + pCurrentNode->GetParent();
                    pCurrentNode->SetFirstChild(QNTree::END_POSITION_FORWARD);
                }
                else
                {
                    // The node being removed is the only one in the tree
                    m_uRoot = QNTree::END_POSITION_FORWARD;
                    pCurrentNode = null_q;
                }

                // Removes the element
                T* pElement = pBaseElementPointer + (pNodeToRemove - pBaseNodePointer);
                pElement->~T();
                m_elementAllocator.Deallocate(pElement);

                // Removes the node
                m_nodeAllocator.Deallocate(pNodeToRemove);
            }
        }
        while(pNodeToRemove != pNode);

        return resultantIterator;
    }
    
    /// <summary>
    /// Removes a child node, at a given position in the child list, and all its descendents.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called in an undefined order, from bottom to top.
    /// </remarks>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be removed. It must not point to an end position.</param>
    /// <param name="uChildIndex">[IN] The position (zero-based index) of the child in the parent's child list. It must be lower than the number of children in the list.</param>
    void RemoveChild(const typename QNTree::QConstNTreeIterator &parentNode, const pointer_uint_q uChildIndex)
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uParentNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pParentNode = pBaseNodePointer + uParentNodePosition;

        QNTree::QNode* pCurrentNode = pParentNode;

        QE_ASSERT_ERROR(pParentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD, "The node has no children.");

        // If the node has children
        if(pParentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
        {
            pCurrentNode = pBaseNodePointer + pParentNode->GetFirstChild();
            
            pointer_uint_q i = 0;

            // Gets the child node at the specified index
            while(i < uChildIndex && pCurrentNode->GetNext() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetNext();
                ++i;
            }

            QE_ASSERT_WARNING(i == uChildIndex, "There is not a child node at the specified position index.");

            // If the child node exists at the specified index
            if(i == uChildIndex)
            {
                // Removes the node
                pointer_uint_q uNodeToRemovedPosition = pCurrentNode - pBaseNodePointer;
                this->Remove(QNTree::QNTreeIterator(this, uNodeToRemovedPosition, parentNode.GetTraversalOrder()));
            }
        }
    }
    
    /// <summary>
    /// Inserts a child node at a given position in the child list.
    /// </summary>
    /// <remarks>
    /// If the tree is empty, use the SetRootValue method.<br/>
    /// If the parent node already has the maximum number of child nodes, the new element will not be added.<br/>
    /// If the capacity of the tree is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the new element will be called.
    /// </remarks>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be removed. It must not point to an end position.</param>
    /// <param name="newElement">[IN] The newElement of the new element.</param>
    /// <param name="uChildIndex">[IN] The position (zero-based index) of the new child in the parent's child list. It must be lower than the number of children in the list.</param>
    /// <returns>
    /// An iterator that points to the just added element. If it was not added, the iterator will point to an end position.
    /// </returns>
    QNTreeIterator InsertChild(const typename QNTree::QConstNTreeIterator &parentNode, const T &newElement, const pointer_uint_q uChildIndex)
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X-X
        //
        using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");

        pointer_uint_q uResultNodePosition = QNTree::END_POSITION_FORWARD;

        // Reserves more memory if necessary
        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uParentNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pParentNode = pBaseNodePointer + uParentNodePosition;

        QNTree::QNode* pCurrentNode = pParentNode;
        pointer_uint_q uNewNodePosition = QNTree::END_POSITION_FORWARD;

        QE_ASSERT_WARNING(pParentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD, "The node has no children.");

        // If the node has children
        if(pParentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
        {
            pCurrentNode = pBaseNodePointer + pParentNode->GetFirstChild();
            
            pointer_uint_q i = 0;

            // Gets the child node at the specified index
            while(i < uChildIndex && pCurrentNode->GetNext() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetNext();
                ++i;
            }

            // Counts how many child nodes are there
            QNTree::QNode* pCurrentAux = pCurrentNode;
            pointer_uint_q uNumberOfElements = i + 1U;

            while(pCurrentAux->GetNext() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentAux = pBaseNodePointer + pCurrentAux->GetNext();
                ++uNumberOfElements;
            }

            QE_ASSERT_ERROR(uNumberOfElements < MAX_CHILDREN, string_q("It is not possible to insert another child to this node, maximum allowed exceeded (") + SQInteger::ToString(MAX_CHILDREN) + ").");

            if(uNumberOfElements < MAX_CHILDREN)
            {
                QE_ASSERT_WARNING(i == uChildIndex, "There is not a child node at the specified position index.");

                // If there is no children at the specified index
                if(i < uChildIndex)
                {
                    // Adds the node to the end of the child list
                    QNTree::QNode* pNewNode = new(m_nodeAllocator.Allocate()) QNode(uParentNodePosition, QNTree::END_POSITION_FORWARD, pCurrentNode - pBaseNodePointer, QNTree::END_POSITION_FORWARD);

                    uNewNodePosition = pNewNode - pBaseNodePointer;
                    pCurrentNode->SetNext(uNewNodePosition);
                }
                else
                {
                    // Adds the node at the specified position
                    QNTree::QNode* pNewNode = new(m_nodeAllocator.Allocate()) QNode(uParentNodePosition, pCurrentNode - pBaseNodePointer, pCurrentNode->GetPrevious(), QNTree::END_POSITION_FORWARD);

                    uNewNodePosition = pNewNode - pBaseNodePointer;
                    pCurrentNode->SetPrevious(uNewNodePosition);

                    if(pNewNode->GetPrevious() == QNTree::END_POSITION_FORWARD)
                        pParentNode->SetFirstChild(uNewNodePosition);
                    else
                        (pBaseNodePointer + pNewNode->GetPrevious())->SetNext(uNewNodePosition);
                }
            }
        }
        else // There are no children
        {
            // Adds the node as the first child node
            QNTree::QNode* pNewNode = new(m_nodeAllocator.Allocate()) QNode(uParentNodePosition, QNTree::END_POSITION_FORWARD, QNTree::END_POSITION_FORWARD, QNTree::END_POSITION_FORWARD);

            uNewNodePosition = pNewNode - pBaseNodePointer;
            pParentNode->SetFirstChild(uNewNodePosition);
        }
            
        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);

        uResultNodePosition = uNewNodePosition;

        return QNTree::QNTreeIterator(this, uResultNodePosition, parentNode.GetTraversalOrder());
    }

    /// <summary>
    /// Gets an iterator that points to a given position in the tree, depending on the traversal order.
    /// </summary>
    /// <param name="uIndex">[IN] Position in the tree, starting at zero, to which the iterator will point. It must be lower than the number of elements in the tree.
    /// If it is out of bounds, the returned iterator will point to the end position.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the position of the element.
    /// </returns>
    QNTreeIterator GetIterator(const pointer_uint_q uIndex, const EQTreeTraversalOrder &eTraversalOrder) const
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

        QE_ASSERT_WARNING(uIndex < this->GetCount(), string_q("The input index (") + SQInteger::ToString(uIndex) + ") is out of bounds.");
        QE_ASSERT_WARNING(!this->IsEmpty(), "It is not possible to get an iterator that points to the given position, the tree is empty.");

        QNTree::QNTreeIterator iterator(this, 0, eTraversalOrder);
        iterator.MoveFirst();

        for(pointer_uint_q i = 0; i < uIndex && !iterator.IsEnd(); ++i)
            ++iterator;

        return iterator;
    }
    
    /// <summary>
    /// Empties the tree.
    /// </summary>
    /// <remarks>
    /// This is equivalent to removing the root node.<br/>
    /// The destructor of each element will be called in an undefined order, from bottom to top.
    /// </remarks>
    void Clear()
    {
        if(!this->IsEmpty())
            this->Remove(this->GetRoot(EQTreeTraversalOrder::E_DepthFirstPreOrder));
        // Note: The traversal order does not affect the result
    }
    
    /// <summary>
    /// Gets a child of a node that occupies a given position in the child list.
    /// </summary>
    /// <param name="parentNode">[IN] The node whose child is to be obtained. It must not point to the end position.</param>
    /// <param name="uChildIndex">[IN] The position (zero-based index) of the child in the parent's child list. It must be lower than the number of children in the list.</param>
    /// <returns>
    /// An iterator that points to the child node. If there is not a child at the given position, the iterator will point to the end position.
    /// </returns>
    QNTreeIterator GetChild(const typename QNTree::QConstNTreeIterator &parentNode, const pointer_uint_q uChildIndex) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        QNTree::QNTreeIterator itResult(this, QNTree::END_POSITION_FORWARD, parentNode.GetTraversalOrder());

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uParentNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pParentNode = pBaseNodePointer + uParentNodePosition;

        QNTree::QNode* pCurrentNode = pParentNode;

        // If the node has children
        if(pParentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
        {
            pCurrentNode = pBaseNodePointer + pParentNode->GetFirstChild();
            
            pointer_uint_q i = 0;

            // Gets the child node at the specified index
            while(i < uChildIndex && pCurrentNode->GetNext() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetNext();
                ++i;
            }

            QE_ASSERT_WARNING(i == uChildIndex, "There is not a child node at the specified position index.");

            // If the child node exists at the specified index
            if(i == uChildIndex)
            {
                // Gets the node
                pointer_uint_q uNodeToRemovedPosition = pCurrentNode - pBaseNodePointer;
                itResult = QNTree::QNTreeIterator(this, uNodeToRemovedPosition, parentNode.GetTraversalOrder());
            }
        }

        return itResult;
    }
    
    /// <summary>
    /// Gets the parent of a node.
    /// </summary>
    /// <param name="node">[IN] The node whose parent is to be obtained. It must not point to the end position.</param>
    /// <returns>
    /// An iterator that points to the parent node. If the node does not have a parent, the iterator will point to the end position.
    /// </returns>
    QNTreeIterator GetParent(const typename QNTree::QConstNTreeIterator &node) const
    {
        //        X
        //       / \
        //      X-...
        //     /|\
        //    N-N-N
        //

        QE_ASSERT_ERROR(node.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!node.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uNodePosition = &*node - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pNode = pBaseNodePointer + uNodePosition;

        return QNTree::QNTreeIterator(this, pNode->GetParent(), node.GetTraversalOrder());
    }
    
    /// <summary>
    /// Gets the first element in the tree, depending on the traversal order.
    /// </summary>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the first element. If the tree is empty, the iterator will point to the end position.
    /// </returns>
    QNTreeIterator GetFirst(const EQTreeTraversalOrder &eTraversalOrder) const
    {
        QNTree::QNTreeIterator itFirst = this->GetRoot(eTraversalOrder);
        itFirst.MoveFirst();
        return itFirst;
    }
    
    /// <summary>
    /// Gets the number of child nodes of a parent node.
    /// </summary>
    /// <param name="parentNode">[IN] The node whose children are to be counted. It must not point to the end position.</param>
    /// <returns>
    /// The number of child nodes.
    /// </returns>
    pointer_uint_q GetChildrenCount(const typename QNTree::QConstNTreeIterator &parentNode) const
    {
        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        pointer_uint_q uCount = 0;

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uParentNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pCurrentNode = pBaseNodePointer + uParentNodePosition;

        // If the node has children
        if(pCurrentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
        {
            pCurrentNode = pBaseNodePointer + pCurrentNode->GetFirstChild();

            ++uCount; // At least, one

            // Counts the children
            while(pCurrentNode->GetNext() != QNTree::END_POSITION_FORWARD)
            {
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetNext();
                ++uCount;
            }
        }

        return uCount;
    }
    
    /// <summary>
    /// Checks whether a node has children or not.
    /// </summary>
    /// <param name="parentNode">[IN] The node to be checked. It must not point to the end position.</param>
    /// <returns>
    /// True if the node has any child; False otherwise.
    /// </returns>
    bool HasChildren(const typename QNTree::QConstNTreeIterator &parentNode) const
    {
        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uParentNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pParentNode = pBaseNodePointer + uParentNodePosition;

        return pParentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD;
    }
    
    /// <summary>
    /// Checks whether a node has a parent or not. Only a root node lacks parent.
    /// </summary>
    /// <param name="node">[IN] The node whose parent is to be checked. It must not point to the end position.</param>
    /// <returns>
    /// True if the node has parent; False otherwise.
    /// </returns>
    bool HasParent(const typename QNTree::QConstNTreeIterator &node) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        QE_ASSERT_ERROR(node.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!node.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uNodePosition = &*node - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pNode = pBaseNodePointer + uNodePosition;

        return pNode->GetParent() != QNTree::END_POSITION_FORWARD;
    }

    /// <summary>
    /// Gets the root node of the tree, which is independent from the traversal order.
    /// </summary>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited, used to create the iterator that points to the root.</param>
    /// <returns>
    /// An iterator that points to the root element. If the tree is empty, the iterator will point to the end position.
    /// </returns>
    QNTreeIterator GetRoot(const EQTreeTraversalOrder &eTraversalOrder) const
    {
        return QNTree::QNTreeIterator(this, m_uRoot, eTraversalOrder);
    }
    
    /// <summary>
    /// Checks whether any element in the tree has the same value as a given element.
    /// </summary>
    /// <remarks>
    /// Elements are compared to the provided value using the container's comparator, in an arbitrary order.<br/>
    /// </remarks>
    /// <param name="element">[IN] The value of the element to search for.</param>
    /// <returns>
    /// True if the element is present in the tree; False otherwise.
    /// </returns>
    bool Contains(const T &element) const
    {
        QNTree::QConstNTreeIterator itElement = this->GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);

        while(!itElement.IsEnd() && m_comparator.Compare(*itElement, element) != 0)
            ++itElement;

        return !itElement.IsEnd();
    }
    
    /// <summary>
    /// Searches for a given element and obtains its position.
    /// </summary>
    /// <param name="element">[IN] The value of the element to search for.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the position of the first occurrence of the element, depending on the traversal order. If the element is not present in the tree, 
    /// the iterator will point to the end position.
    /// </returns>
    QNTreeIterator PositionOf(const T &element, const EQTreeTraversalOrder &eTraversalOrder) const
    {
        QNTree::QNTreeIterator itElement = this->GetFirst(EQTreeTraversalOrder::E_DepthFirstPreOrder);

        while(!itElement.IsEnd() && m_comparator.Compare(*itElement, element) != 0)
            ++itElement;

        return itElement;
    }
    
    /// <summary>
    /// Searches for a given element, starting at a concrete point, and obtains its position.
    /// </summary>
    /// <param name="element">[IN] The value of the element to search for.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <param name="startPosition">[IN] An iterator that points to the node from which to start searching. It must not point to an end position.</param>
    /// <returns>
    /// An iterator that points to the position of the first occurrence of the element, starting at the given position, depending on the traversal order. If the element is not found, 
    /// the iterator will point to the end position.
    /// </returns>
    QNTreeIterator PositionOf(const T &element, const EQTreeTraversalOrder &eTraversalOrder, const typename QNTree::QConstNTreeIterator startPosition) const
    {
        QE_ASSERT_ERROR(!startPosition.IsEnd(), "The start position must not point to the end position.");

        QNTree::QNTreeIterator itElement = QNTree::QNTreeIterator(this, &*startPosition - scast_q(m_elementAllocator.GetPointer(), T*), startPosition.GetTraversalOrder());

        while(!itElement.IsEnd() && m_comparator.Compare(*itElement, element) != 0)
            ++itElement;

        return itElement;
    }
    
    /// <summary>
    /// Gets the first child in the child list of a given node.
    /// </summary>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be obtained. It must not point to an end position.</param>
    /// <returns>
    /// An iterator that points to the first child node. If the node has no children, the resultant iterator will point to the end position.
    /// </returns>
    QNTreeIterator GetFirstChild(const typename QNTree::QConstNTreeIterator &parentNode) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    0-X-X
        //

        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uParentNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pParentNode = pBaseNodePointer + uParentNodePosition;

        return QNTree::QNTreeIterator(this, pParentNode->GetFirstChild(), parentNode.GetTraversalOrder());
    }
    
    /// <summary>
    /// Gets the last child in the child list of a given node.
    /// </summary>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be obtained. It must not point to an end position.</param>
    /// <returns>
    /// An iterator that points to the last child node. If the node has no children, the resultant iterator will point to the end position.
    /// </returns>
    QNTreeIterator GetLastChild(const typename QNTree::QConstNTreeIterator &parentNode) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        QE_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        QE_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        QNTree::QNTreeIterator itResult(this, QNTree::END_POSITION_FORWARD, parentNode.GetTraversalOrder());

        // Gets node pointer and position
        T* pBaseElementPointer = scast_q(m_elementAllocator.GetPointer(), T*);
        pointer_uint_q uParentNodePosition = &*parentNode - pBaseElementPointer;

        QNTree::QNode* pBaseNodePointer = scast_q(m_nodeAllocator.GetPointer(), QNTree::QNode*);
        QNTree::QNode* pCurrentNode = pBaseNodePointer + uParentNodePosition;

        // If the node has children
        if(pCurrentNode->GetFirstChild() != QNTree::END_POSITION_FORWARD)
        {
            pCurrentNode = pBaseNodePointer + pCurrentNode->GetFirstChild();

            // Gets the last child
            while(pCurrentNode->GetNext() != QNTree::END_POSITION_FORWARD)
                pCurrentNode = pBaseNodePointer + pCurrentNode->GetNext();

            // Gets the node
            pointer_uint_q uLastChildPosition = pCurrentNode - pBaseNodePointer;
            itResult = QNTree::QNTreeIterator(this, uLastChildPosition, parentNode.GetTraversalOrder());
        }

        return itResult;
    }
    
    /// <summary>
    /// Gets the last element in the tree, depending on the traversal order.
    /// </summary>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the last element. If the tree is empty, the iterator will point to the end position.
    /// </returns>
    QNTreeIterator GetLast(const EQTreeTraversalOrder &eTraversalOrder) const
    {
        QNTree::QNTreeIterator itLast = this->GetRoot(eTraversalOrder);
        itLast.MoveLast();
        return itLast;
    }
    
    /// <summary>
    /// Performs a shallow copy of the contents of the tree to another tree.
    /// </summary>
    /// <remarks>
    /// If the capacity of the destination tree is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="destinationTree">[IN/OUT] The destination array to which the contents will be copied. The maximum number of children per node in the tree must 
    /// be greater than or equal to the resident tree's.</param>
    void Clone(QNTree &destinationTree) const
    {
        QE_ASSERT_ERROR(destinationTree.MAX_CHILDREN >= MAX_CHILDREN, "The maximum number of children per node in the destination tree is lower than the source tree's.");

        if(destinationTree.GetCapacity() < this->GetCapacity())
            destinationTree.Reserve(this->GetCapacity());

        this->m_nodeAllocator.CopyTo(destinationTree.m_nodeAllocator);
        this->m_elementAllocator.CopyTo(destinationTree.m_elementAllocator);
        destinationTree.m_uRoot = m_uRoot;
    }
    
    /// <summary>
    /// Swaps two elements of the tree.
    /// </summary>
    /// <remarks>
    /// The tree must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="elementA">[IN] The position of an element. It must not be an end position.</param>
    /// <param name="elementB">[IN] The position of the other element. It must not be an end position.</param>
    void Swap(const typename QNTree::QNTreeIterator elementA, const typename QNTree::QNTreeIterator elementB)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

        QE_ASSERT_ERROR(!elementA.IsEnd(), "The element A position is an end position.");
        QE_ASSERT_ERROR(!elementB.IsEnd(), "The element B position is an end position.");
        QE_ASSERT_ERROR(elementA.IsValid(), "The element A's position is not valid.");
        QE_ASSERT_ERROR(elementB.IsValid(), "The element B's position is not valid.");
        QE_ASSERT_WARNING(elementA != elementB, "Both elements are the same.");
        
        T* pElementA = &*elementA;
        T* pElementB = &*elementB;

        u8_q arBytes[sizeof(T)];
        memcpy(arBytes,   pElementA, sizeof(T));
        memcpy(pElementA, pElementB, sizeof(T));
        memcpy(pElementB, arBytes,   sizeof(T));
    }

private:

    /// <summary>
    /// Updates the reference positions of all the nodes related to one given node.
    /// </summary>
    /// <remarks>
    /// This is used when a node is moved to a different position in the internal buffer.
    /// </remarks>
    /// <param name="pNode">[IN] The node whose related nodes are to be updated.</param>
    void _UpdateNodesPositions(typename QNTree::QNode* pNode)
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

    /// <summary>
    /// Increases the capacity of the tree, reserving memory for more elements than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void _ReallocateByFactor(const pointer_uint_q uNumberOfElements)
    {
        const pointer_uint_q FINAL_CAPACITY = scast_q(scast_q(uNumberOfElements, float) * QNTree::REALLOCATION_FACTOR, pointer_uint_q);
        this->Reserve(FINAL_CAPACITY);
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
    /// Gets the capacity of the tree, which means the number of elements that can be added before they are reallocated to
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

template<class T, class AllocatorT, class ComparatorT>
float QNTree<T, AllocatorT, ComparatorT>::REALLOCATION_FACTOR = 1.5f;

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QNTREE__
