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

#include "QStackAllocator.h"
#include "Assertions.h"
#include "StringsDefinitions.h"

using Kinesis::QuimeraEngine::Common::Memory::QStackAllocator;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QStackAllocator::QBlockHeader::QBlockHeader(const pointer_uint_q uSize, const pointer_uint_q uAlignmentOffset, const pointer_uint_q uPreviousBlockHeaderBackOffset ) :
                                                                                        m_uSize(uSize),
                                                                                        m_uAlignmentOffset(uAlignmentOffset),
                                                                                        m_uPreviousHeaderBackOffset(uPreviousBlockHeaderBackOffset)
{
    QE_ASSERT_ERROR(uSize > 0, "The given size for the memory block cannot be zero.");
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

pointer_uint_q QStackAllocator::QBlockHeader::GetAllocatedBlockSize() const
{
    return m_uSize;
}

pointer_uint_q QStackAllocator::QBlockHeader::GetAlignmentOffset() const
{
    return m_uAlignmentOffset;
}

pointer_uint_q QStackAllocator::QBlockHeader::GetPreviousHeaderBackOffset() const
{
    return m_uPreviousHeaderBackOffset;
}

} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
