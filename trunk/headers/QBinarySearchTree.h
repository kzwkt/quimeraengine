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
/// Represents a binary search tree. It is an optimized special case of an N-ary tree, whose nodes have up to two child nodes (left and right) which are ordered
/// in such a way that left child nodes are always lower than parent nodes and right child nodes are always greater than parent nodes. Therefore, there can not
/// be duplicate nodes. Comparisons among nodes are performed using a comparator component whose type is provided as a template parameter.
/// </summary>
/// <remarks>
/// Nodes in the tree are re-ordered as nodes are added or removed. Although they follow a tree structure, removing a parent does not imply the removal of its children.<br/>
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
        /* [TODO] Thund: Uncomment when GetFirst exists
        for(QBinarySearchTree::QBinarySearchTreeIterator it = this->GetFirst(); !it.IsEnd(); ++it)
            it->~T();*/
    }


    // METHODS
    // ---------------
public:
    
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
            m_nodeAllocator.Reallocate(uNumberOfElements * sizeof(QBinarySearchTree::QBinaryNode));
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


} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis


#endif // __QBINARYSEARCHTREE__
