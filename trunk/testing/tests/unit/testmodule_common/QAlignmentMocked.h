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

#ifndef __QALIGNMENTMOCKED__
#define __QALIGNMENTMOCKED__


#include "QAlignment.h"
#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"

using Kinesis::QuimeraEngine::Common::Memory::QAlignment;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{
namespace Test
{


/// <summary>
/// [DOC]
/// </summary>
class QAlignmentMocked : public QAlignment
{
	// CONSTRUCTORS
	// ---------------
public:

	explicit QAlignmentMocked(const pointer_uint_q &uAlignment) : QAlignment (uAlignment) {}


	// METHODS
	// ---------------
public:
    // TO-DO: [DOC]
    void SabotageAlignmentValue()
    {
        do
        {
            ++m_uAlignment;
        } while ( !(0 == m_uAlignment) && !(m_uAlignment & (m_uAlignment - 1)) );
    }
};


} //namespace Test
} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QALIGNMENTMOCKED__
