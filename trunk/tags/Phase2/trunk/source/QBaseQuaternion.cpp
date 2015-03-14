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

#include "QBaseQuaternion.h"

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
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QBaseQuaternion::QBaseQuaternion() : x(SQFloat::_0), y(SQFloat::_0), z(SQFloat::_0), w(SQFloat::_0)
{
}

QBaseQuaternion::QBaseQuaternion(const QBaseQuaternion &qQuat)
{
    this->x = qQuat.x;
    this->y = qQuat.y;
    this->z = qQuat.z;
    this->w = qQuat.w;
}

QBaseQuaternion::QBaseQuaternion(const float_q &fValueX, const float_q &fValueY,
                                const float_q &fValueZ, const float_q &fValueW) :
                                       x(fValueX), y(fValueY), z(fValueZ), w(fValueW)
{
}

QBaseQuaternion::QBaseQuaternion(const float_q* arValues)
{
    // [REVIEW] Thund: Should we put these constants in another place?
    static const int QE_X_INDEX_IN_FLOATTYPE_ARRAY = 0;
    static const int QE_Y_INDEX_IN_FLOATTYPE_ARRAY = 1;
    static const int QE_Z_INDEX_IN_FLOATTYPE_ARRAY = 2;
    static const int QE_W_INDEX_IN_FLOATTYPE_ARRAY = 3;

    QE_ASSERT_ERROR(arValues != null_q, "Input array must not be null");

    this->x = arValues[QE_X_INDEX_IN_FLOATTYPE_ARRAY];
    this->y = arValues[QE_Y_INDEX_IN_FLOATTYPE_ARRAY];
    this->z = arValues[QE_Z_INDEX_IN_FLOATTYPE_ARRAY];
    this->w = arValues[QE_W_INDEX_IN_FLOATTYPE_ARRAY];
}

QBaseQuaternion::QBaseQuaternion(const vf32_q &value)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;

    // Quaternion's components are mapped into the 4x32 pack as configured (see DataTypesDefinitions.h for further information)
    SQVF32::Unpack(value, QE_VF32_FIRST_COMPONENT, QE_VF32_SECOND_COMPONENT, QE_VF32_THIRD_COMPONENT, QE_VF32_FOURTH_COMPONENT);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool QBaseQuaternion::operator==(const QBaseQuaternion &qQuat) const
{
    return   SQFloat::AreEqual(this->x, qQuat.x) &&
                SQFloat::AreEqual(this->y, qQuat.y) &&
                SQFloat::AreEqual(this->z, qQuat.z) &&
                SQFloat::AreEqual(this->w, qQuat.w);
}

bool QBaseQuaternion::operator!=(const QBaseQuaternion &qQuat) const
{
    return !(*this == qQuat);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
