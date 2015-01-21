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

#ifndef __SQEQUALITYCOMPARATOR__
#define __SQEQUALITYCOMPARATOR__

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
/// Implements functionality for checking if two objects are equal or not.
/// </summary>
/// <remarks>
/// Type used as template parameter MUST implement the equality operator ("==").
/// </remarks>
/// <typeparam name="T">The type of the elements to compare.</typeparam>
template <class T>
class SQEqualityComparator
{
    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQEqualityComparator();


    // METHODS
    // --------------
public:

    /// <summary>
    /// Compares two elements.
    /// </summary>
    /// <param name="leftOperand">[IN] First operand to compare.</param>
    /// <param name="rightOperand">[IN] Second operand to compare.</param>
    /// <returns>
    /// 1 in case operads are different; 0 if they are equal.
    /// </returns>
    static Kinesis::QuimeraEngine::Common::DataTypes::i8_q Compare (const T &leftOperand, const T &rightOperand)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

        // Variables representing the three return values
        static const i8_q ARE_NOT_EQUAL = 1;
        static const i8_q ARE_EQUAL = 0;

        return leftOperand == rightOperand ? ARE_EQUAL : 
                                             ARE_NOT_EQUAL;
    }
};

} // namespace Containers
} // namespace Tools
} // namespace QuimeraEngine
} // namespace Kinesis

#endif // __SQEQUALITYCOMPARATOR__
