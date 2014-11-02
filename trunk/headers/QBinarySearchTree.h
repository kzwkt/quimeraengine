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

#ifndef __QBINARYSEARCHTREE__
#define __QBINARYSEARCHTREE__

#include "ToolsDefinitions.h"

#include "Assertions.h"
#include "QPoolAllocator.h"
#include "QAlignment.h"
#include "QComparatorDefault.h"
#include "EQTreeTraversalOrder.h"
#include "EQIterationDirection.h"

using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;
using Kinesis::QuimeraEngine::Tools::Containers::EQTreeTraversalOrder;
using Kinesis::QuimeraEngine::Tools::Containers::EQIterationDirection;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Represents a binary search tree. It is an optimized special case of an N-ary tree, whose nodes have up to two child nodes (left and right) which are ordered
/// in such a way that left child nodes are always lower than parent nodes and right child nodes are always greater than parent nodes. Therefore, there can not
/// be duplicate nodes. Comparisons among nodes are performed using a comparator component whose type is provided as a template parameter.
/// </summary>
/// <remarks>
/// Nodes are placed in their corresponding position as they are added or removed. Although they follow a tree structure, removing a parent does not imply the 
/// removal of its children.<br/>
/// In a binary search tree, elements cannot be modified, their position in the tree may become inconsistent since it depends on their value and the comparison algorithm.<br/>
/// There is not a default way to traverse an binary search tree, the desired method will have to be specified when necessary.<br/>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If QComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of the tree elements.</typeparam>
/// <typeparam name="AllocatorT">The allocator used to reserve memory. The default type is QPoolAllocator.</typeparam>
/// <typeparam name="ComparatorT">The comparator. The default type is QComparatorDefault.</typeparam>
template<class T, class AllocatorT = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator, class ComparatorT = QComparatorDefault<T> >
class QBinarySearchTree
{
    // INTERNAL CLASSES
    // -----------------
protected:

    /// <summary>
    /// Data structure that stores information about every node and its position in the binary tree.
    /// </summary>
    class QBinaryNode
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives all the information about the node.
        /// </summary>
        /// <param name="uParentPosition">[IN] The physical position of the parent node.</param>
        /// <param name="uLeftChildPosition">[IN] The physical position of left child node.</param>
        /// <param name="uRightChildPosition">[IN] The physical position of the right child node.</param>
        QBinaryNode(const pointer_uint_q uParentPosition, const pointer_uint_q uLeftChildPosition, const pointer_uint_q uRightChildPosition) :
                                                                                            m_uParent(uParentPosition),
                                                                                            m_uLeft(uLeftChildPosition),
                                                                                            m_uRight(uRightChildPosition)
        {
        }
        

        // PROPERTIES
        // ---------------
    public:

        /// <summary>
        /// Gets the physical position of the parent node.
        /// </summary>
        /// <returns>
        /// The physical position of the parent node.
        /// </returns>
        pointer_uint_q GetParent() const
        {
            return m_uParent;
        }
        
        /// <summary>
        /// Gets the physical position of the left child node.
        /// </summary>
        /// <returns>
        /// The physical position of the left child node.
        /// </returns>
        pointer_uint_q GetLeftChild() const
        {
            return m_uLeft;
        }
        
        /// <summary>
        /// Gets the physical position of the right child node.
        /// </summary>
        /// <returns>
        /// The physical position of the right child node.
        /// </returns>
        pointer_uint_q GetRightChild() const
        {
            return m_uRight;
        }
        
        /// <summary>
        /// Sets the physical position of the parent node.
        /// </summary>
        /// <param name="uPosition">[IN] The physical position of the parent node.</param>
        void SetParent(const pointer_uint_q uPosition)
        {
            m_uParent = uPosition;
        }
        
        /// <summary>
        /// Sets the physical position of the left child node.
        /// </summary>
        /// <param name="uPosition">[IN] The physical position of the left child node.</param>
        void SetLeftChild(const pointer_uint_q uPosition)
        {
            m_uLeft = uPosition;
        }
        
        /// <summary>
        /// Sets the physical position of the right child node.
        /// </summary>
        /// <param name="uPosition">[IN] The physical position of the right child node.</param>
        void SetRightChild(const pointer_uint_q uPosition)
        {
            m_uRight = uPosition;
        }


        // ATTRIBUTES
        // ---------------
    private:

        /// <returns>
        /// The physical position of the parent node.
        /// </returns>
        pointer_uint_q m_uParent;

        /// <returns>
        /// The physical position of the left child node.
        /// </returns>
        pointer_uint_q m_uLeft;

        /// <returns>
        /// The physical position of the right child node.
        /// </returns>
        pointer_uint_q m_uRight;

    }; // class QBinaryNode
    
public:

    /// <summary>
    /// Iterator that steps once per element of a binary search tree, in a concrete order. Since the traversal order may vary, the meaning of the words
    /// "last", "first" and "next", used in the documentation of this class, can be different depending on such order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a tree, it cannot point to another tree ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the tree.<br/>
    /// The position just before the first element or just after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class QConstBinarySearchTreeIterator
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
        QConstBinarySearchTreeIterator(const QBinarySearchTree* pTree, const pointer_uint_q uPosition, const EQTreeTraversalOrder &eTraversalOrder) : m_pTree(pTree), 
                                                                                                                                                      m_uPosition(uPosition), 
                                                                                                                                                      m_eTraversalOrder(eTraversalOrder)
        {
            QE_ASSERT_ERROR(pTree != null_q, "Invalid argument: The pointer to the tree cannot be null");
            QE_ASSERT_WARNING(pTree->GetCapacity() > uPosition || 
                              uPosition == QBinarySearchTree::END_POSITION_BACKWARD || 
                              uPosition == QBinarySearchTree::END_POSITION_FORWARD, "Invalid argument: The position must be lower than the capacity of the tree");
            QE_ASSERT_ERROR(eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstInOrder, string_q("The traversal order specified (") + eTraversalOrder.ToString() + ") is not supported.");

            if(pTree == null_q || 
               (pTree->GetCapacity() <= uPosition && uPosition != QBinarySearchTree::END_POSITION_BACKWARD && uPosition != QBinarySearchTree::END_POSITION_FORWARD) || 
               pTree->IsEmpty())
                m_uPosition = QBinarySearchTree::END_POSITION_FORWARD;
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
        QConstBinarySearchTreeIterator& operator=(const QConstBinarySearchTreeIterator &iterator)
        {
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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the tree element");

            QE_ASSERT_ERROR(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD && m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

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
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the tree element");

            QE_ASSERT_ERROR(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD && m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

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
        QConstBinarySearchTreeIterator operator++(int)
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            QConstBinarySearchTreeIterator iteratorCopy = *this;

            if(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstInOrder)
                {
                    //         4
                    //       /   \
                    //      /     \
                    //     2       6
                    //    / \     / \
                    //   /   \   /   \
                    //  1     3 5     7

                    if(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD)
                    {
                        QBinarySearchTree::QBinaryNode* pNextNode = null_q;

                        QBinarySearchTree::QBinaryNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
                        QBinarySearchTree::QBinaryNode* pNode = pBasePointer + m_uPosition;

                        if(pNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If current node has a right-child, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetRightChild();

                            // And searches for the "leftest" and deepest node
                            while(pNextNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
                                pNextNode = pBasePointer + pNextNode->GetLeftChild();

                            m_uPosition = pNextNode - pBasePointer;
                        }
                        else if(pNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If current node has a parent, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetParent();

                            // And searches for the first parent reached from the left side
                            while(pNextNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD &&
                                  pNextNode->GetRightChild() == pNode - pBasePointer)
                            {
                                pNode = pNextNode;
                                pNextNode = pBasePointer + pNextNode->GetParent();
                            }
                            
                            if(pNextNode->GetParent() == QBinarySearchTree::END_POSITION_FORWARD &&
                               pNextNode->GetLeftChild() != pNode - pBasePointer)
                                // Root node found
                                m_uPosition = QBinarySearchTree::END_POSITION_FORWARD;
                            else
                                // Gets the position of the found next node
                                m_uPosition = pNextNode - pBasePointer;
                        }
                        else
                        {
                            // The current node is the root node and there is no right child
                            m_uPosition = QBinarySearchTree::END_POSITION_FORWARD;
                        }
                    }
                    else if(m_uPosition == QBinarySearchTree::END_POSITION_BACKWARD)
                    {
                        this->MoveFirst();
                    }
                }
            } // if(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD)

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
        QConstBinarySearchTreeIterator operator--(int)
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            QE_ASSERT_WARNING(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            QConstBinarySearchTreeIterator iteratorCopy = *this;

            if(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstInOrder)
                {
                    //         4
                    //       /   \
                    //      /     \
                    //     6       2
                    //    / \     / \
                    //   /   \   /   \
                    //  7     5 3     1

                    if(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        QBinarySearchTree::QBinaryNode* pNextNode = null_q;

                        QBinarySearchTree::QBinaryNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
                        QBinarySearchTree::QBinaryNode* pNode = pBasePointer + m_uPosition;

                        if(pNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If current node has a left-child, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetLeftChild();

                            // And searches for the rightest and deepest child
                            while(pNextNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                                pNextNode = pBasePointer + pNextNode->GetRightChild();

                            m_uPosition = pNextNode - pBasePointer;
                        }
                        else if(pNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If the node has a parent, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetParent();

                            // And searches for the first ancestor reached from the right side
                            while(pNextNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD &&
                                  pNextNode->GetLeftChild() == pNode - pBasePointer)
                            {
                                pNode = pNextNode;
                                pNextNode = pBasePointer + pNextNode->GetParent();
                            }

                            if(pNextNode->GetParent() == QBinarySearchTree::END_POSITION_FORWARD &&
                               pNextNode->GetRightChild() != pNode - pBasePointer)
                                // Root node found
                                m_uPosition = QBinarySearchTree::END_POSITION_BACKWARD;
                            else
                                // Gets the position of the found previous node
                                m_uPosition = pNextNode - pBasePointer;
                        }
                        else
                        {
                            // The current node is the root node and there is no left child
                            m_uPosition = QBinarySearchTree::END_POSITION_BACKWARD;
                        }
                    }
                    else if(m_uPosition == QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        this->MoveLast();
                    }
                }
            } // if(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD)

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
        QConstBinarySearchTreeIterator& operator++()
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            QE_ASSERT_WARNING(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstInOrder)
                {
                    //         4
                    //       /   \
                    //      /     \
                    //     2       6
                    //    / \     / \
                    //   /   \   /   \
                    //  1     3 5     7

                    if(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD)
                    {
                        QBinarySearchTree::QBinaryNode* pNextNode = null_q;

                        QBinarySearchTree::QBinaryNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
                        QBinarySearchTree::QBinaryNode* pNode = pBasePointer + m_uPosition;

                        if(pNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If current node has a right-child, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetRightChild();

                            // And searches for the "leftest" and deepest node
                            while(pNextNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
                                pNextNode = pBasePointer + pNextNode->GetLeftChild();

                            m_uPosition = pNextNode - pBasePointer;
                        }
                        else if(pNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If current node has a parent, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetParent();

                            // And searches for the first parent reached from the left side
                            while(pNextNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD &&
                                  pNextNode->GetRightChild() == pNode - pBasePointer)
                            {
                                pNode = pNextNode;
                                pNextNode = pBasePointer + pNextNode->GetParent();
                            }

                            if(pNextNode->GetParent() == QBinarySearchTree::END_POSITION_FORWARD &&
                               pNextNode->GetLeftChild() != pNode - pBasePointer)
                                // Root node found
                                m_uPosition = QBinarySearchTree::END_POSITION_FORWARD;
                            else
                                // Gets the position of the found next node
                                m_uPosition = pNextNode - pBasePointer;
                        }
                        else
                        {
                            // The current node is the root node and there is no right child
                            m_uPosition = QBinarySearchTree::END_POSITION_FORWARD;
                        }
                    }
                    else if(m_uPosition == QBinarySearchTree::END_POSITION_BACKWARD)
                    {
                        this->MoveFirst();
                    }
                }
            } // if(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD)

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
        QConstBinarySearchTreeIterator& operator--()
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            QE_ASSERT_WARNING(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");
            
            if(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstInOrder)
                {
                    //         4
                    //       /   \
                    //      /     \
                    //     6       2
                    //    / \     / \
                    //   /   \   /   \
                    //  7     5 3     1

                    if(m_uPosition != QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        QBinarySearchTree::QBinaryNode* pNextNode = null_q;

                        QBinarySearchTree::QBinaryNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
                        QBinarySearchTree::QBinaryNode* pNode = pBasePointer + m_uPosition;

                        if(pNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If current node has a left-child, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetLeftChild();

                            // And searches for the rightest and deepest child
                            while(pNextNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                                pNextNode = pBasePointer + pNextNode->GetRightChild();

                            m_uPosition = pNextNode - pBasePointer;
                        }
                        else if(pNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD)
                        {
                            // If the node has a parent, the pointer moves to it
                            pNextNode = pBasePointer + pNode->GetParent();

                            // And searches for the first ancestor reached from the right side
                            while(pNextNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD &&
                                  pNextNode->GetLeftChild() == pNode - pBasePointer)
                            {
                                pNode = pNextNode;
                                pNextNode = pBasePointer + pNextNode->GetParent();
                            }
                            
                            if(pNextNode->GetParent() == QBinarySearchTree::END_POSITION_FORWARD &&
                               pNextNode->GetRightChild() != pNode - pBasePointer)
                                // Root node found
                                m_uPosition = QBinarySearchTree::END_POSITION_BACKWARD;
                            else
                                // Gets the position of the found previous node
                                m_uPosition = pNextNode - pBasePointer;
                        }
                        else
                        {
                            // The current node is the root node and there is no left child
                            m_uPosition = QBinarySearchTree::END_POSITION_BACKWARD;
                        }
                    }
                    else if(m_uPosition == QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        this->MoveLast();
                    }
                }
            } // if(m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD)

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
        bool operator==(const QConstBinarySearchTreeIterator &iterator) const
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
        bool operator!=(const QConstBinarySearchTreeIterator &iterator) const
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
        bool operator>(const QConstBinarySearchTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QBinarySearchTree::END_POSITION_FORWARD &&
               m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD)
            {
                QBinarySearchTree::QConstBinarySearchTreeIterator iteratorFromThis = *this;

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
        bool operator<(const QConstBinarySearchTreeIterator &iterator) const
        {
            QE_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            QE_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            QE_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != QBinarySearchTree::END_POSITION_BACKWARD &&
               m_uPosition != QBinarySearchTree::END_POSITION_FORWARD)
            {
                QBinarySearchTree::QConstBinarySearchTreeIterator iteratorFromThis = *this;

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
        bool operator>=(const QConstBinarySearchTreeIterator &iterator) const
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
                    QBinarySearchTree::QConstBinarySearchTreeIterator iteratorFromThis = *this;

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
        bool operator<=(const QConstBinarySearchTreeIterator &iterator) const
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
                    QBinarySearchTree::QConstBinarySearchTreeIterator iteratorFromThis = *this;

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
            return m_uPosition == QBinarySearchTree::END_POSITION_BACKWARD || m_uPosition == QBinarySearchTree::END_POSITION_FORWARD;
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
            return (eIterationDirection == EQIterationDirection::E_Backward && m_uPosition == QBinarySearchTree::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EQIterationDirection::E_Forward  && m_uPosition == QBinarySearchTree::END_POSITION_FORWARD);
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
                m_uPosition = QBinarySearchTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstInOrder)
                {
                    QBinarySearchTree::QBinaryNode* pNextNode = null_q;

                    QBinarySearchTree::QBinaryNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
                    QBinarySearchTree::QBinaryNode* pNode = pBasePointer + m_pTree->m_uRoot;

                    if(pNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        // If root node has a left-child, the pointer moves to it
                        pNextNode = pBasePointer + pNode->GetLeftChild();

                        // And searches for the "leftest" and deepest child
                        while(pNextNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
                            pNextNode = pBasePointer + pNextNode->GetLeftChild();

                        m_uPosition = pNextNode - pBasePointer;
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
                m_uPosition = QBinarySearchTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == EQTreeTraversalOrder::E_DepthFirstInOrder)
                {
                    QBinarySearchTree::QBinaryNode* pNextNode = null_q;

                    QBinarySearchTree::QBinaryNode* pBasePointer = rcast_q(m_pTree->m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
                    QBinarySearchTree::QBinaryNode* pNode = pBasePointer + m_pTree->m_uRoot;

                    if(pNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        // If root node has a right-child, the pointer moves to it
                        pNextNode = pBasePointer + pNode->GetRightChild();

                        // And searches for the "rightest" and deepest child
                        while(pNextNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                            pNextNode = pBasePointer + pNextNode->GetRightChild();

                        m_uPosition = pNextNode - pBasePointer;
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
                   (m_uPosition < m_pTree->m_nodeAllocator.GetPoolSize() / sizeof(QBinaryNode) ||
                    m_uPosition == QBinarySearchTree::END_POSITION_BACKWARD ||
                    m_uPosition == QBinarySearchTree::END_POSITION_FORWARD);
        }


        // ATTRIBUTES
	    // ---------------
    protected:

        /// <summary>
        /// The tree the iterator points to.
        /// </summary>
        const QBinarySearchTree* m_pTree;

        /// <summary>
        /// The current iteration position regarding the base position of the buffer (zero). It is zero-based.
        /// </summary>
        pointer_uint_q m_uPosition;

        /// <summary>
        /// The order in which elements will be visited.
        /// </summary>
        const EQTreeTraversalOrder m_eTraversalOrder;

    }; // QConstBinarySearchTreeIterator


   	// CONSTANTS
    // ---------------
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
    
private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float REALLOCATION_FACTOR;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QBinarySearchTree() : m_elementAllocator(QBinarySearchTree::sm_uDefaultCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                          m_nodeAllocator(QBinarySearchTree::sm_uDefaultCapacity * sizeof(QBinarySearchTree::QBinaryNode), sizeof(QBinarySearchTree::QBinaryNode), QAlignment(alignof_q(QBinarySearchTree::QBinaryNode))),
                          m_uRoot(QBinarySearchTree::END_POSITION_FORWARD)
                          
    {
    }

    /// <summary>
    /// Constructor that receives the initial capacity.
    /// </summary>
    /// <param name="uInitialCapacity">[IN] The number of elements for which to reserve memory. It must be greater than zero.</param>
    QBinarySearchTree(const pointer_uint_q uInitialCapacity) : m_elementAllocator(uInitialCapacity * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                                               m_nodeAllocator(uInitialCapacity * sizeof(QBinarySearchTree::QBinaryNode), sizeof(QBinarySearchTree::QBinaryNode), QAlignment(alignof_q(QBinarySearchTree::QBinaryNode))),
                                                               m_uRoot(QBinarySearchTree::END_POSITION_FORWARD)
    {
        QE_ASSERT_ERROR(uInitialCapacity > 0, "The initial capacity of the tree must be greater than zero.");
    }
    
    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every copied element, in an arbitrary order.
    /// </remarks>
    /// <param name="tree">[IN] The other tree to be copied.</param>
    QBinarySearchTree(const QBinarySearchTree &tree): m_elementAllocator(tree.GetCapacity() * sizeof(T), sizeof(T), QAlignment(alignof_q(T))),
                                                      m_nodeAllocator(tree.GetCapacity() * sizeof(QBinarySearchTree::QBinaryNode), sizeof(QBinarySearchTree::QBinaryNode), QAlignment(alignof_q(QBinarySearchTree::QBinaryNode))),
                                                      m_uRoot(tree.m_uRoot)
    {
        if(!tree.IsEmpty())
        {
            tree.m_elementAllocator.CopyTo(m_elementAllocator);
            tree.m_nodeAllocator.CopyTo(m_nodeAllocator);

            // [TODO] Thund: Replace with GetFirst
            QBinarySearchTree::QConstBinarySearchTreeIterator itSource(&tree, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);
            QBinarySearchTree::QConstBinarySearchTreeIterator itDestination(this, 0, EQTreeTraversalOrder::E_DepthFirstInOrder);

            for(itSource.MoveFirst(), itDestination.MoveFirst(); !itSource.IsEnd(); ++itSource, ++itDestination)
                new(ccast_q(&*itDestination, T*)) T(*itSource);
        }
    }


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element will be called in an undetermined order.
    /// </remarks>
    ~QBinarySearchTree()
    {
        // [TODO] Thund: Replace with GetFirst when it exists
        QBinarySearchTree::QConstBinarySearchTreeIterator it(this, m_uRoot, EQTreeTraversalOrder::E_DepthFirstInOrder);

        for(it.MoveFirst(); !it.IsEnd(); ++it)
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
    /// <param name="tree">[IN] The other tree to be copied.</param>
    QBinarySearchTree& operator=(const QBinarySearchTree &tree)
    {
        if(this != &tree)
        {
            // Removes all the elements in the resident tree
            // [TODO] Thund: Replace with Clear when it exists
            QBinarySearchTree::QConstBinarySearchTreeIterator it(this, m_uRoot, EQTreeTraversalOrder::E_DepthFirstInOrder);

            for(it.MoveFirst(); !it.IsEnd(); ++it)
                (*it).~T();

            m_elementAllocator.Clear();
            m_nodeAllocator.Clear();

            m_uRoot = QBinarySearchTree::END_POSITION_FORWARD;

            // Copies all the elements of the input tree, if any
            if(!tree.IsEmpty())
            {
                m_uRoot = tree.m_uRoot;

                if(this->GetCapacity() < tree.GetCapacity())
                    this->Reserve(tree.GetCapacity());

                tree.m_elementAllocator.CopyTo(m_elementAllocator);
                tree.m_nodeAllocator.CopyTo(m_nodeAllocator);

                QBinarySearchTree::QConstBinarySearchTreeIterator itSource = tree.GetFirst(EQTreeTraversalOrder::E_DepthFirstInOrder);
                QBinarySearchTree::QConstBinarySearchTreeIterator itDestination = this->GetFirst(EQTreeTraversalOrder::E_DepthFirstInOrder);

                for(; !itSource.IsEnd(); ++itSource, ++itDestination)
                    new(ccast_q(&*itDestination, T*)) T(*itSource);
            }
        }

        return *this;
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
            m_nodeAllocator.Reallocate(uNumberOfElements * sizeof(QBinarySearchTree::QBinaryNode));
        }
    }
    
    /// <summary>
    /// Adds an element to the tree as a leaf node.
    /// </summary>
    /// <remarks>
    /// This operation may imply a reallocation, which means that any pointer to elements of this tree will be pointing to garbage.<br/>
    /// The copy constructor of the new element will be called.
    /// </remarks>
    /// <param name="newElement">[IN] The value of the new element. There must not be any element in the tree with the same value.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited. It is used to create the returned iterator.</param>
    /// <returns>
    /// An iterator that points to the just added element. If the element was already in the tree, the returned iterator will point to the end position.
    /// </returns>
    QConstBinarySearchTreeIterator Add(const T &newElement, const EQTreeTraversalOrder &eTraversalOrder)
    {
        if(this->GetCapacity() == this->GetCount())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        new(m_elementAllocator.Allocate()) T(newElement);

        T* pElementBasePosition = scast_q(m_elementAllocator.GetPointer(), T*);
        QBinarySearchTree::QBinaryNode* pNodeBasePosition = scast_q(m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
        QBinarySearchTree::QBinaryNode* pNewNode = null_q;

        if(m_uRoot == QBinarySearchTree::END_POSITION_FORWARD)
        {
            // If the tree is empty, the root node is created
            pNewNode = new(m_nodeAllocator.Allocate()) QBinarySearchTree::QBinaryNode(QBinarySearchTree::END_POSITION_FORWARD, 
                                                                                      QBinarySearchTree::END_POSITION_FORWARD,
                                                                                      QBinarySearchTree::END_POSITION_FORWARD);
            m_uRoot = pNewNode - pNodeBasePosition;
        }
        else
        {
            static const int INPUT_VALUE_IS_LOWER = -1;
            static const int INPUT_VALUE_IS_GREATER = 1;
            QBinarySearchTree::QBinaryNode* pCurrentNode = pNodeBasePosition + m_uRoot;
            T* pCurrentElement = pElementBasePosition + m_uRoot;

            int nComparisonResult = 0;
            
            // Performs a binary search through the tree to determine the position of the new element
            while(pNewNode == null_q) // Until the new node is created
            {
                nComparisonResult = m_comparator.Compare(newElement, *pCurrentElement);

                QE_ASSERT_ERROR(nComparisonResult != 0, "The input element already exists in the tree.");

                if(nComparisonResult == INPUT_VALUE_IS_LOWER)
                {
                    if(pCurrentNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        // If the new value is lower than the current element's value and there is a left child, moves down to the left child
                        pCurrentElement = pElementBasePosition + pCurrentNode->GetLeftChild();
                        pCurrentNode = pNodeBasePosition + pCurrentNode->GetLeftChild();
                    }
                    else
                    {
                        // If the new value is lower than the current element's value and there is not a left child, the new value occupies the left position
                        pNewNode = new(m_nodeAllocator.Allocate()) QBinarySearchTree::QBinaryNode(pCurrentNode - pNodeBasePosition, 
                                                                                                  QBinarySearchTree::END_POSITION_FORWARD, 
                                                                                                  QBinarySearchTree::END_POSITION_FORWARD);
                        pCurrentNode->SetLeftChild(pNewNode - pNodeBasePosition);
                    }
                }
                else if(nComparisonResult == INPUT_VALUE_IS_GREATER)
                {
                    if(pCurrentNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                    {
                        // If the new value is greater than the current element's value and there is a right child, moves down to the right child
                        pCurrentElement = pElementBasePosition + pCurrentNode->GetRightChild();
                        pCurrentNode = pNodeBasePosition + pCurrentNode->GetRightChild();
                    }
                    else
                    {
                        // If the new value is greater than the current element's value and there is not a right child, the new value occupies the right position
                        pNewNode = new(m_nodeAllocator.Allocate()) QBinarySearchTree::QBinaryNode(pCurrentNode - pNodeBasePosition, 
                                                                                                  QBinarySearchTree::END_POSITION_FORWARD, 
                                                                                                  QBinarySearchTree::END_POSITION_FORWARD);
                        pCurrentNode->SetRightChild(pNewNode - pNodeBasePosition);
                    }
                }
            } // while(pNewNode != null_q)
        }

        return QBinarySearchTree::QConstBinarySearchTreeIterator(this, pNewNode - pNodeBasePosition, eTraversalOrder);
    }
    
    /// <summary>
    /// Removes an element from the tree.
    /// </summary>
    /// <remarks>
    /// The destructor of the element will be called.<br/>
    /// Removing an element does not imply the removal of its child nodes; instead, they will be reordered so the right child will be always a descendant of the left child when both exist.
    /// </remarks>
    /// <param name="elementPosition">[IN] The position of the element to remove. It must not point to the end position.</param>
    /// <returns>
    /// An iterator that points to the next element. If the removed element was the last one in the tree, the returned iterator will point to the end position.
    /// The traversal order of the returned iterator will be the same as the input iterator's.
    /// </returns>
    QConstBinarySearchTreeIterator Remove(const typename QBinarySearchTree::QConstBinarySearchTreeIterator &elementPosition)
    {
        QE_ASSERT_ERROR(!elementPosition.IsEnd(), "The input iterator must not point to an end position.");
        QE_ASSERT_ERROR(elementPosition.IsValid(), "The input iterator is invalid.");
        QE_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, the element does not exist.");

        QBinarySearchTree::QConstBinarySearchTreeIterator resultIterator = elementPosition;
        ++resultIterator;

        T* pElementBasePosition = scast_q(m_elementAllocator.GetPointer(), T*);
        const T* pElement = &*elementPosition;
        pointer_uint_q uElementPosition = pElement - pElementBasePosition;

        QBinarySearchTree::QBinaryNode* pNodeBasePosition = scast_q(m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
        QBinarySearchTree::QBinaryNode* pNode = pNodeBasePosition + uElementPosition;
        
        pointer_uint_q uNewChild = QBinarySearchTree::END_POSITION_FORWARD;

        if(pNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD && 
           pNode->GetLeftChild()  != QBinarySearchTree::END_POSITION_FORWARD)
        {
            // The node has both left and right children

            // The node will be replaced with the left child
            uNewChild = pNode->GetLeftChild();

            // The right child will be appended to the deepest right child in the branch of the node's left child
            QBinarySearchTree::QBinaryNode* pRightMostChild = pNodeBasePosition + pNode->GetLeftChild();

            while(pRightMostChild->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
                pRightMostChild = pNodeBasePosition + pRightMostChild->GetRightChild();

            pRightMostChild->SetRightChild(pNode->GetRightChild());
            QBinarySearchTree::QBinaryNode* pRightChildNode = pNodeBasePosition + pNode->GetRightChild();
            pRightChildNode->SetParent(pRightMostChild - pNodeBasePosition);
        }
        else if(pNode->GetLeftChild() != QBinarySearchTree::END_POSITION_FORWARD)
        {
            // The node has left child only
            // The node will be replaced with the left child
            uNewChild = pNode->GetLeftChild();
        }
        else if(pNode->GetRightChild() != QBinarySearchTree::END_POSITION_FORWARD)
        {
            // The node has right child only
            // The node will be replaced with the right child
            uNewChild = pNode->GetRightChild();
        }

        // If the node has a child that will occupy its position
        if(uNewChild != QBinarySearchTree::END_POSITION_FORWARD)
        {
            // Sets the parent of the node that will occupy the position of the removed node
            QBinarySearchTree::QBinaryNode* pNewChild = pNodeBasePosition + uNewChild;
            pNewChild->SetParent(pNode->GetParent());
        }
        
        // If the removed node had a parent, its child (either left or right) is set to the node that occupies its place
        if(pNode->GetParent() != QBinarySearchTree::END_POSITION_FORWARD)
        {
            QBinarySearchTree::QBinaryNode* pParentNode = pNodeBasePosition + pNode->GetParent();
            
            if(pParentNode->GetLeftChild() == uElementPosition)
                pParentNode->SetLeftChild(uNewChild);
            else // It is the right-child
                pParentNode->SetRightChild(uNewChild);
        }

        // Updates the root of the tree if necessary
        if(uElementPosition == m_uRoot)
            m_uRoot = uNewChild;

        // Both element and node are destroyed
        pElement->~T();
        m_elementAllocator.Deallocate(pElement);
        m_nodeAllocator.Deallocate(pNode);

        return resultIterator;
    }
    
    /// <summary>
    /// Checks whether there is any element in the tree that is equal to other given element.
    /// </summary>
    /// <remarks>
    /// Elements are compared to the provided value using the container's comparator.<br/>
    /// </remarks>
    /// <param name="value">[IN] The value of the element to search for.</param>
    /// <returns>
    /// True if the element is present in the tree; False otherwise.
    /// </returns>
    bool Contains(const T &value) const
    {
        static const int INPUT_VALUE_IS_LOWER = -1;
        static const int INPUT_VALUE_IS_GREATER = 1;
        static const int INPUT_VALUE_IS_EQUAL = 0;
        static const int INVALID_RESULT = -2;

        pointer_uint_q uCurrentPosition = m_uRoot;

        QBinarySearchTree::QBinaryNode* pNodeBasePointer = scast_q(m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
        QBinarySearchTree::QBinaryNode* pCurrentNode = pNodeBasePointer + uCurrentPosition;
        T* pElementBasePointer = scast_q(m_elementAllocator.GetPointer(), T*);
        T* pCurrentElement = pElementBasePointer + uCurrentPosition;
        int nComparisonResult = INVALID_RESULT;

        while(uCurrentPosition != QBinarySearchTree::END_POSITION_FORWARD && nComparisonResult != INPUT_VALUE_IS_EQUAL)
        {
            nComparisonResult = m_comparator.Compare(value, *pCurrentElement);

            if(nComparisonResult == INPUT_VALUE_IS_LOWER)
                uCurrentPosition = pCurrentNode->GetLeftChild();
            else if(nComparisonResult == INPUT_VALUE_IS_GREATER)
                uCurrentPosition = pCurrentNode->GetRightChild();

            pCurrentElement = pElementBasePointer + uCurrentPosition;
            pCurrentNode = pNodeBasePointer + uCurrentPosition;
        }

        return nComparisonResult == INPUT_VALUE_IS_EQUAL;
    }
    
    /// <summary>
    /// Gets the first element in the tree, depending on the traversal order.
    /// </summary>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the first element. If the tree is empty, the iterator will point to the end position.
    /// </returns>
    QConstBinarySearchTreeIterator GetFirst(const EQTreeTraversalOrder &eTraversalOrder) const
    {
        QBinarySearchTree::QConstBinarySearchTreeIterator itResult(this, m_uRoot, eTraversalOrder);
        itResult.MoveFirst();
        return itResult;
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
    QConstBinarySearchTreeIterator GetIterator(const pointer_uint_q uIndex, const EQTreeTraversalOrder &eTraversalOrder) const
    {
        QE_ASSERT_ERROR(uIndex < this->GetCount(), "The input index must be lower than the number of elements in the tree.");

        QBinarySearchTree::QConstBinarySearchTreeIterator itResult = this->GetFirst(eTraversalOrder);

        for(pointer_uint_q i = 0; i < uIndex; ++i)
            ++itResult;

        return itResult;
    }
    
    /// <summary>
    /// Searches for a given element and obtains its position.
    /// </summary>
    /// <param name="element">[IN] The value of the element to search for.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited. It is used just to create the resultant iterator.</param>
    /// <returns>
    /// An iterator that points to the position of the element. If the element is not present in the tree, the iterator will point to the end position.
    /// </returns>
    QConstBinarySearchTreeIterator PositionOf(const T &element, const EQTreeTraversalOrder &eTraversalOrder) const
    {
        static const int INPUT_VALUE_IS_LOWER = -1;
        static const int INPUT_VALUE_IS_GREATER = 1;
        static const int INPUT_VALUE_IS_EQUAL = 0;
        static const int INVALID_RESULT = -2;

        pointer_uint_q uCurrentPosition = m_uRoot;

        QBinarySearchTree::QBinaryNode* pNodeBasePointer = scast_q(m_nodeAllocator.GetPointer(), QBinarySearchTree::QBinaryNode*);
        QBinarySearchTree::QBinaryNode* pCurrentNode = pNodeBasePointer + uCurrentPosition;
        T* pElementBasePointer = scast_q(m_elementAllocator.GetPointer(), T*);
        T* pCurrentElement = pElementBasePointer + uCurrentPosition;
        int nComparisonResult = INVALID_RESULT;

        while(uCurrentPosition != QBinarySearchTree::END_POSITION_FORWARD && nComparisonResult != INPUT_VALUE_IS_EQUAL)
        {
            nComparisonResult = m_comparator.Compare(element, *pCurrentElement);

            if(nComparisonResult == INPUT_VALUE_IS_LOWER)
                uCurrentPosition = pCurrentNode->GetLeftChild();
            else if(nComparisonResult == INPUT_VALUE_IS_GREATER)
                uCurrentPosition = pCurrentNode->GetRightChild();

            pCurrentElement = pElementBasePointer + uCurrentPosition;
            pCurrentNode = pNodeBasePointer + uCurrentPosition;
        }

        return QBinarySearchTree::QConstBinarySearchTreeIterator(this, uCurrentPosition, eTraversalOrder);
    }
    
    /// <summary>
    /// Performs a shallow copy of the contents of the tree to another tree.
    /// </summary>
    /// <remarks>
    /// If the capacity of the destination tree is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="destinationTree">[IN/OUT] The destination array to which the contents will be copied.</param>
    void Clone(QBinarySearchTree &destinationTree) const
    {
        if(destinationTree.GetCapacity() < this->GetCapacity())
            destinationTree.Reserve(this->GetCapacity());

        this->m_nodeAllocator.CopyTo(destinationTree.m_nodeAllocator);
        this->m_elementAllocator.CopyTo(destinationTree.m_elementAllocator);
        destinationTree.m_uRoot = m_uRoot;
    }

private:

    /// <summary>
    /// Increases the capacity of the tree, reserving memory for more elements than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void _ReallocateByFactor(const pointer_uint_q uNumberOfElements)
    {
        const pointer_uint_q FINAL_CAPACITY = scast_q(scast_q(uNumberOfElements, float) * QBinarySearchTree::REALLOCATION_FACTOR, pointer_uint_q);
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
        return m_uRoot == QBinarySearchTree::END_POSITION_FORWARD;
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
pointer_uint_q QBinarySearchTree<T, AllocatorT, ComparatorT>::sm_uDefaultCapacity = 1;

template<class T, class AllocatorT, class ComparatorT>
float QBinarySearchTree<T, AllocatorT, ComparatorT>::REALLOCATION_FACTOR = 1.5f;


} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis


#endif // __QBINARYSEARCHTREE__
