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

#ifndef __QCONSTBINARYSEARCHTREEITERATORMOCK__
#define __QCONSTBINARYSEARCHTREEITERATORMOCK__

#include "QBinarySearchTree.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{
namespace Test
{

/// <summary>
/// Fake iterator used for testing purposes (to create invalid iterators, for example).
/// </summary>
/// <typeparam name="T">The type of the tree elements.</typeparam>
template <class T>
class QConstBinarySearchTreeIteratorMock : public QBinarySearchTree<T>::QConstBinarySearchTreeIterator
{
    using QBinarySearchTree<T>::QConstBinarySearchTreeIterator::m_uPosition;

public:

    // Constructor bypass
    QConstBinarySearchTreeIteratorMock(const QBinarySearchTree<T>* pTree, const pointer_uint_q uPosition, const EQTreeTraversalOrder &eTraversalOrder) : QBinarySearchTree<T>::QConstBinarySearchTreeIterator(pTree, uPosition, eTraversalOrder)
    {
    }

    /// <summary>
    /// Sets the position to which the iterator points.
    /// </summary>
    /// <param name="uPosition">[IN] The new position. It can be invalid.</param>
    void SetPosition(const pointer_uint_q uPosition)
    {
        m_uPosition = uPosition;
    }
};

} //namespace Test
} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCONSTBINARYSEARCHTREEITERATORMOCK__
