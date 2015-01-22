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

#include "SQStringHashProvider.h"

#include "Assertions.h"

using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

pointer_uint_q SQStringHashProvider::GenerateHashKey(const string_q &strInput, const pointer_uint_q uBucketsInTable)
{
    // See: http://www.burtleburtle.net/bob/hash/doobs.html

    QE_ASSERT_ERROR(uBucketsInTable > 0, "The input number of buckets must be greater than zero.");

    pointer_uint_q uHashKey = 0;

    const u16_q* arCharacters = strInput.GetInternalBuffer();
    const pointer_uint_q LENGTH = strInput.GetLength();

    for(pointer_uint_q i = 0; i < LENGTH; ++i)
    {
        uHashKey += arCharacters[i];
        uHashKey += (uHashKey << 10U);
        uHashKey ^= (uHashKey >> 6U);
    }

    uHashKey += (uHashKey << 3U);
    uHashKey ^= (uHashKey >> 11U);
    uHashKey += (uHashKey << 15U);

    return uHashKey % uBucketsInTable;
}


} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
