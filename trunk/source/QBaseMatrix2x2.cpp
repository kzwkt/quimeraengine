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

#include "QBaseMatrix2x2.h"

#include <memory>

#include "Assertions.h"
#include "SQFloat.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################



//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QBaseMatrix2x2::QBaseMatrix2x2()
{
    ij[0][0] = SQFloat::_0;
    ij[0][1] = SQFloat::_0;
    ij[1][0] = SQFloat::_0;
    ij[1][1] = SQFloat::_0;
}

QBaseMatrix2x2::QBaseMatrix2x2(const QBaseMatrix2x2 &matrix)
{
    memcpy(this->ij, matrix.ij, sizeof(float_q) * 4);
}

QBaseMatrix2x2::QBaseMatrix2x2(const float_q fValueAll)
{
    ij[0][0] = ij[0][1] =
    ij[1][0] = ij[1][1] = fValueAll;
}

QBaseMatrix2x2::QBaseMatrix2x2(const float_q f00, const float_q f01, const float_q f10, const float_q f11)
{
    ij[0][0] = f00;
    ij[0][1] = f01;
    ij[1][0] = f10;
    ij[1][1] = f11;
}

/// <summary>
/// Constructor that receives a pointer to 4 floating point values.
/// </summary>
/// <remarks>
/// Keeps the convention rows x columns, so each chunck of 2 consecutive elements
/// corresponds to a row, where each element in the chunck is the column in the row.
/// </remarks>
/// <param name="arValues">[IN] A 4 length array of floating point values. If the pointer is null, the behavior  
/// is undefined.</param>
QBaseMatrix2x2::QBaseMatrix2x2(const float_q* arValues)
{
    QE_ASSERT_ERROR(arValues != null_q, "The input array must not be null");

    ij[0][0] = arValues[0];
    ij[0][1] = arValues[1];
    ij[1][0] = arValues[2];
    ij[1][1] = arValues[3];
}

/// <summary>
/// Constructor from one 4x32 floating point packed values. Each value contains an element of the matrix.<br/>
/// Each pack element is unpacked following the row x column convention.
/// </summary>
/// <param name="value">[IN] 4x32 values for the matrix.</param>
QBaseMatrix2x2::QBaseMatrix2x2(const vf32_q value)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;

    SQVF32::Unpack(value, this->ij[0][0], this->ij[0][1], this->ij[1][0], this->ij[1][1]);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool QBaseMatrix2x2::operator==(const QBaseMatrix2x2 &matrix) const
{
    return SQFloat::AreEqual(this->ij[0][0], matrix.ij[0][0]) &&
            SQFloat::AreEqual(this->ij[0][1], matrix.ij[0][1]) &&
            SQFloat::AreEqual(this->ij[1][0], matrix.ij[1][0]) &&
            SQFloat::AreEqual(this->ij[1][1], matrix.ij[1][1]);
}

bool QBaseMatrix2x2::operator!=(const QBaseMatrix2x2 &matrix) const
{
    return  !(*this == matrix);
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
