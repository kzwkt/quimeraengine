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

#ifndef __SQNOCOMPARATOR__
#define __SQNOCOMPARATOR__

#include "DataTypesDefinitions.h"
#include "ToolsDefinitions.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{


/// <summary>
/// Provides an empty implementation of a comparator, intended to be used when a functionality requires a comparator type for elements that cannot be compared.
/// </summary>
/// <remarks>
/// Type used as template parameter MUST implement both operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of the elements to compare.</typeparam>
template <class T>
class SQNoComparator
{
    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQNoComparator();


    // METHODS
    // --------------
public:

    /// <summary>
    /// Compares two elements.
    /// </summary>
    /// <param name="leftOperand">[IN] First operand to compare.</param>
    /// <param name="rightOperand">[IN] Second operand to compare.</param>
    /// <returns>
    /// Always zero.
    /// </returns>
    static Kinesis::QuimeraEngine::Common::DataTypes::i8_q Compare (const T &leftOperand, const T &rightOperand)
    {
        QE_ASSERT_ERROR(false, "Functions that perform comparisons must not be called when using SQNoComparator.");
        return 0;
    }
};

} // namespace Containers
} // namespace Tools
} // namespace QuimeraEngine
} // namespace Kinesis

#endif // __SQNOCOMPARATOR__
