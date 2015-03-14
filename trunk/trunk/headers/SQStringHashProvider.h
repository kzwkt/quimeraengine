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

#ifndef __SQSTRINGHASHPROVIDER__
#define __SQSTRINGHASHPROVIDER__

#include "ToolsDefinitions.h"

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
/// Represents a hash provider that generates hash keys from strings.
/// </summary>
class QE_LAYER_TOOLS_SYMBOLS SQStringHashProvider
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQStringHashProvider();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Generates a hash key from a string.
    /// </summary>
    /// <remarks>
    /// It implements the Jenkins' one-at-a-time hash function, followed by the calculation of the remainder of dividing the result by the number of buckets.
    /// </remarks>
    /// <param name="strInput">[IN] A string value. It can be empty.</param>
    /// <param name="uBucketsInTable">[IN] The number of buckets in the table for which the hash key is to be calculated.</param>
    /// <returns>
    /// A hash key.
    /// </returns>
    static Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q GenerateHashKey(const Kinesis::QuimeraEngine::Common::DataTypes::string_q &strInput, 
                                                                                     const Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q uBucketsInTable);

};

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQSTRINGHASHPROVIDER__
