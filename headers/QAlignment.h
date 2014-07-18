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

#ifndef __QALIGNMENT__
#define __QALIGNMENT__

#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"


using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Memory
{

/// <summary>
/// Class which represents a memory alignment, that is, a number that is used to allocate memory at addresses that are power of it.
/// </summary>
/// <remarks>
/// Alignments must be always a power of 2.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS QAlignment
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor from a value.
    /// </summary>
    /// <param name="uAlignment">[IN] Unsigned integer value to define alignment. It MUST be a power of 2.</param>
    explicit QAlignment(const pointer_uint_q &uAlignment);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Conversion operator to unsigned integer.
    /// </summary>
    /// <returns>
    /// The alignment converted into an unsigned integer value.
    /// </returns>
    operator unsigned int() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// Value which represents the memory alignment, used to allocate memory at addresses that are power of it.
    /// </summary>
    /// <remarks>
    /// This value MUST be always a power of 2.
    /// </remarks>
    pointer_uint_q m_uAlignment;

};

} //namespace Memory
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QALIGNMENT__
