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

#include "QBasePlane.h"

#include "Assertions.h"
#include "StringsDefinitions.h"
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
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QBasePlane::QBasePlane() : a(SQFloat::_0), b(SQFloat::_0), c(SQFloat::_0), d(SQFloat::_0)
{
}

QBasePlane::QBasePlane(const QBasePlane &plane)
{
    this->a = plane.a;
    this->b = plane.b;
    this->c = plane.c;
    this->d = plane.d;
}

QBasePlane::QBasePlane(const float_q fValueA, const float_q fValueB, const float_q fValueC, const float_q fValueD) :
                        a(fValueA), b(fValueB), c(fValueC), d(fValueD)
{
}

QBasePlane::QBasePlane(const float_q fValueAll) : a(fValueAll), b(fValueAll), c(fValueAll), d(fValueAll)
{
}

QBasePlane::QBasePlane(const float_q* arValues)
{
    // Null pointer checkout
    QE_ASSERT_ERROR(arValues != null_q, "The input array must not be null");

    // Assignments
    this->a = arValues[0];
    this->b = arValues[1];
    this->c = arValues[2];
    this->d = arValues[3];
}

QBasePlane::QBasePlane(const vf32_q value)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;

    SQVF32::Unpack(value, this->a, this->b, this->c, this->d);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool QBasePlane::operator==(const QBasePlane &plane) const
{
    return ( SQFloat::AreEqual(plane.a, this->a) && SQFloat::AreEqual(plane.b, this->b) &&
                SQFloat::AreEqual(plane.c, this->c) && SQFloat::AreEqual(plane.d, this->d) );
}

bool QBasePlane::operator!=(const QBasePlane &plane) const
{
    return !(*this == plane);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
