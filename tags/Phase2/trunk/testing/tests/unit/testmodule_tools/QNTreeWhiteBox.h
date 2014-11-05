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

#ifndef __QNTREEWHITEBOX__
#define __QNTREEWHITEBOX__

#include "QNTree.h"
#include "QPoolAllocator.h"

using Kinesis::QuimeraEngine::Tools::Containers::QNTree;
using Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator;


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
/// Class intended to be used to expose protected methods of QNTree for testing purposes.
/// </summary>
template <class T, class AllocatorT = QPoolAllocator>
class QNTreeWhiteBox : public QNTree<T, AllocatorT>
{
public:

    using typename QNTree<T, AllocatorT>::QNode;


	// CONSTRUCTORS
	// ---------------
public:

    QNTreeWhiteBox(const pointer_uint_q uMaximumChildren) : QNTree<T, AllocatorT>(uMaximumChildren)
    {
    }

    QNTreeWhiteBox(const pointer_uint_q uMaximumChildren, const pointer_uint_q uInitialCapacity) : QNTree<T, AllocatorT>(uMaximumChildren, uInitialCapacity)
    {
    }



	// PROPERTIES
	// ---------------
public:

    pointer_uint_q GetRootPosition() const
    {
        return QNTree<T, AllocatorT>::m_uRoot;
    }

    const pointer_uint_q GetMaximumChildren() const
    {
        return QNTree<T, AllocatorT>::MAX_CHILDREN;
    }

    const AllocatorT& GetNodeAllocator() const
    {
        return QNTree<T, AllocatorT>::m_nodeAllocator;
    }

    static pointer_uint_q GetEndPositionForward()
    {
        return QNTree<T, AllocatorT>::END_POSITION_FORWARD;
    }

};

} //namespace Test
} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QNTREEWHITEBOX__
