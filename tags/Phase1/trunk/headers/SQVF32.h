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

#ifndef __SQVF32__
#define __SQVF32__

#include "SQFloat.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Helper class that offers functionality related to 4 x 32-bits floating point variables packs.
/// </summary>
/// <remarks>
/// This kind of packs are used in SIMD operations.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS SQVF32
{

	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	SQVF32();


	// METHODS
	// ---------------
public:
    // [TODO] Thund: Review this doc.
    /// <summary>
    /// Packs four input floating point variables into a 128-bits type.
    /// </summary>
    /// <remarks>
    /// The order of variables in the package must be read from left to right, this is:<br/>
    ///  | Fourth | Third | Second | First | position<br/>
    /// 128       96     64        32      0 bit<br/>
    /// This is endianess-independent.
    /// </remarks>
    /// <param name="fFirst">[IN] First value in the packet.</param>
    /// <param name="fSecond">[IN] Second value in the packet.</param>
    /// <param name="fThird">[IN] Third value in the packet.</param>
    /// <param name="fFourth">[IN] Fourth value in the packet.</param>
    /// <param name="pack">[OUT] The package containing four 32-bits floating point values.</param>
    static void Pack(const float_q &fFirst, const float_q &fSecond, const float_q &fThird, const float_q &fFourth, vf32_q &pack);

    /// <summary>
    /// Unpacks into four output floating point variables stored in a 128-bits type.
    /// </summary>
    /// <remarks>
    /// The order of variables in the package is read from left to right, this is:<br/>
    ///  | Fourth | Third | Second | First | position<br/>
    /// 128       96     64        32      0 bit<br/>
    /// This is endianess-independent.
    /// </remarks>
    /// <param name="pack">[IN] The package containing four 32-bits floating point values.</param>
    /// <param name="fFirst">[OUT] First value in the packet.</param>
    /// <param name="fSecond">[OUT] Second value in the packet.</param>
    /// <param name="fThird">[OUT] Third value in the packet.</param>
    /// <param name="fFourth">[OUT] Fourth value in the packet.</param>
    static void Unpack(const vf32_q &pack, float_q &fFirst, float_q &fSecond, float_q &fThird, float_q &fFourth);

    /// <summary>
    /// Represents the package content as a character string.
    /// </summary>
    /// <param name="inPack">[IN] A package containing four 32-bits floating point values.</param>
    /// <returns>
    /// The packet represented as a character string.<br/>
    /// The format is: VF( First, Second, Third, Fourth ).
    /// </returns>
    static string_q ToString(const vf32_q &inPack);

};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQVF32__
