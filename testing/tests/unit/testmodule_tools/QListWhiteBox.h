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

#ifndef __QLISTWHITEBOX__
#define __QLISTWHITEBOX__

#include "QList.h"
#include "QPoolAllocator.h"

using Kinesis::QuimeraEngine::Tools::Containers::QList;
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
/// Class intended to be used to expose protected methods of QList for testing purposes.
/// </summary>
template <class T, class AllocatorT = QPoolAllocator>
class QListWhiteBox : public QList<T, AllocatorT>
{
    using QList<T>::m_linkAllocator;
    using QList<T>::m_uFirst;
    using QList<T>::m_uLast;
    using QList<T>::DEFAULT_NUMBER_OF_ELEMENTS;

	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
    QListWhiteBox() : QList<T>()
    {
    }

    // Necessary for testing
    QListWhiteBox(pointer_uint_q uReserve) : QList<T>(uReserve)
    {
    }

	// PROPERTIES
	// ---------------
public:

    // Necessary for testing
    pointer_uint_q GetFirstPosition() const
    {
        return m_uFirst;
    }

    // Necessary for testing
    pointer_uint_q GetLastPosition() const
    {
        return m_uLast;
    }

    // Necessary for testing
    const AllocatorT* GetLinkAllocator() const
    {
        return &m_linkAllocator;
    }

    // Necessary for testing
    static pointer_uint_q GetDefaultInitialCapacity()
    {
        return DEFAULT_NUMBER_OF_ELEMENTS;
    }
};

} //namespace Test
} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLISTWHITEBOX__
