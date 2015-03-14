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

#ifndef __QCOMPARATORDEFAULT__
#define __QCOMPARATORDEFAULT__

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
/// Class implementing functionality for comparing two objects of the same type.
/// </summary>
/// <remarks>
/// Types used as template parameter MUST implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of the elements to compare.</typeparam>
template <class T>
class QComparatorDefault
{
    // METHODS
    // --------------
public:

    /// <summary>
    /// Compares two elements.
    /// </summary>
    /// <param name="leftOperand">[IN] First operand to compare.</param>
    /// <param name="rightOperand">[IN] Second operand to compare.</param>
    /// <returns>
    /// Compare returns -1 in case left operand is lower than right operand; 0 if they are equal; +1 if left operand is greater than right operand.
    /// </returns>
    Kinesis::QuimeraEngine::Common::DataTypes::i8_q Compare (const T &leftOperand, const T &rightOperand) const
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

        // Variables representing the three return values
        static const i8_q LEFT_IS_LOWER_THAN_RIGHT = -1;
        static const i8_q LEFT_IS_GREATER_THAN_RIGHT = 1;
        static const i8_q ARE_EQUAL = 0;

        Kinesis::QuimeraEngine::Common::DataTypes::i8_q nResult = LEFT_IS_GREATER_THAN_RIGHT;

        if (leftOperand < rightOperand)
            nResult = LEFT_IS_LOWER_THAN_RIGHT;
        else if (leftOperand == rightOperand)
            nResult = ARE_EQUAL;

        return nResult;
    }
};

} // namespace Time
} // namespace Tools
} // namespace QuimeraEngine
} // namespace Kinesis

#endif // __QCOMPARATORDEFAULT__
