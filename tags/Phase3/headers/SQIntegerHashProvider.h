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

#ifndef __SQINTEGERHASHPROVIDER__
#define __SQINTEGERHASHPROVIDER__

#include "ToolsDefinitions.h"

#include "Assertions.h"
#include "StringsDefinitions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Represents a hash provider that generates hash keys from integer numbers.
/// </summary>
class QE_LAYER_TOOLS_SYMBOLS SQIntegerHashProvider
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQIntegerHashProvider();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Generates a hash key from an integer value.
    /// </summary>
    /// <remarks>
    /// It just calculates the remainder of dividing the input value by the number of buckets in the table.
    /// </remarks>
    /// <typeparam name="IntegerT">The integer type of the input value.</typeparam>
    /// <param name="input">[IN] An integer value.</param>
    /// <param name="uBucketsInTable">[IN] The number of buckets in the table for which the hash key is to be calculated. It must be greater than zero.</param>
    /// <returns>
    /// A hash key.
    /// </returns>
    template<class IntegerT>
    static Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q GenerateHashKey(const IntegerT input, const Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q uBucketsInTable)
    {
        QE_ASSERT_ERROR(uBucketsInTable > 0, "The input number of buckets must be greater than zero.");

        return input % uBucketsInTable;
    }

};

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQINTEGERHASHPROVIDER__
