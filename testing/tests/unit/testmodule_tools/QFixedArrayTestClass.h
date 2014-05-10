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

#ifndef __QFIXEDARRAYTESTCLASS__
#define __QFIXEDARRAYTESTCLASS__

#include "QFixedArray.h"
#include "QPoolAllocator.h"

using Kinesis::QuimeraEngine::Tools::Containers::QFixedArray;

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
/// Class intended to be used to expose protected methods of QFixedArray for testing purposes.
/// </summary>
template <class T, class Allocator = Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator>
class QFixedArrayTestClass : public QFixedArray<T>
{
    using QFixedArray<T>::m_pAllocator;
	static const pointer_uint_q DEFAULT_NUMBER_OF_ELEMENTS = 1;

    // CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
    QFixedArrayTestClass() : QFixedArray<T>()
    {
        // To avoid that the destructor tries to delete a null pointer.
        if( null_q == m_pAllocator )
            m_pAllocator = new Allocator(QFixedArrayTestClass::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(T), sizeof(T), QAlignment(alignof_q(T)));
    }

};

} //namespace Test
} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QFIXEDARRAYTESTCLASS__
