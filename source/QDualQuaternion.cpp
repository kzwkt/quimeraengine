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

#include "QDualQuaternion.h"

#include "QBaseVector3.h"
#include "QBaseVector4.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QDualQuaternion QDualQuaternion::operator+(const QBaseDualQuaternion &dualQuat) const
{
    return QDualQuaternion(QBaseQuaternion(this->r + dualQuat.r), QBaseQuaternion(this->d + dualQuat.d));
}

QDualQuaternion QDualQuaternion::operator-(const QBaseDualQuaternion &dualQuat) const
{
    return QDualQuaternion(QBaseQuaternion(this->r - dualQuat.r), QBaseQuaternion(this->d - dualQuat.d));
}

QDualQuaternion QDualQuaternion::operator*(const QBaseDualQuaternion &dualQuat) const
{
    return QDualQuaternion(QBaseQuaternion(this->r * dualQuat.r), QBaseQuaternion(this->r * dualQuat.d + this->d * dualQuat.r));
}

QDualQuaternion QDualQuaternion::operator*(const float_q &fScalar) const
{
    return QDualQuaternion(QBaseQuaternion(this->r * fScalar), QBaseQuaternion(this->d * fScalar));
}

QDualQuaternion operator*(const float_q &fScalar, const QDualQuaternion &dualQuat)
{
    return QDualQuaternion(QBaseQuaternion(dualQuat.r * fScalar), QBaseQuaternion(dualQuat.d * fScalar));
}

QDualQuaternion QDualQuaternion::operator*(const QBaseVector3 &vVector) const
{
    // Vector3 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    QDualQuaternion auxQ(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                         QBaseQuaternion(vVector.x, vVector.y, vVector.z, SQFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

QDualQuaternion QDualQuaternion::operator*(const QBaseVector4 &vVector) const
{
    // Vector4 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    QDualQuaternion auxQ(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                         QBaseQuaternion(vVector.x, vVector.y, vVector.z, SQFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

QDualQuaternion QDualQuaternion::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != SQFloat::_0)

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    return QDualQuaternion(QBaseQuaternion(this->r * DIVISOR), QBaseQuaternion(this->d * DIVISOR));
}

QDualQuaternion QDualQuaternion::Transform(const QDualQuaternion &transformation) const
{
    return QDualQuaternion(transformation * (*this) * transformation.DoubleConjugate());
}

string_q QDualQuaternion::ToString() const
{
    return QE_L("DQ(r(") + r.ToString() +
           QE_L("),d(")  + d.ToString() + QE_L("))");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
