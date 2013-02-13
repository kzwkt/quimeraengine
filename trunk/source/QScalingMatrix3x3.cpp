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

#include "QScalingMatrix3x3.h"

#include "QVector3.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QTransformationMatrix.h"

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

QScalingMatrix3x3 QScalingMatrix3x3::operator*(const QScalingMatrix3x3 &matrix) const
{
    return QScalingMatrix3x3(this->ij[0][0] * matrix.ij[0][0],
                             this->ij[1][1] * matrix.ij[1][1],
                             this->ij[2][2] * matrix.ij[2][2]);
}

QTransformationMatrix<QMatrix4x4> QScalingMatrix3x3::operator*(const QRotationMatrix3x3 &matrix) const
{
    QTransformationMatrix<QMatrix4x4> aux = QTransformationMatrix<QMatrix4x4>::GetIdentity();

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2];

    aux.ij[1][0] = this->ij[1][1] * matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] * matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][1] * matrix.ij[1][2];

    aux.ij[2][0] = this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] * matrix.ij[2][2];

    return aux;
}

QTransformationMatrix<QMatrix4x4> QScalingMatrix3x3::operator*(const QTranslationMatrix<QMatrix4x4> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x4>(matrix);
}

QTransformationMatrix<QMatrix4x3> QScalingMatrix3x3::operator*(const QTranslationMatrix<QMatrix4x3> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x3>(matrix);
}

QTransformationMatrix<QMatrix4x4> QScalingMatrix3x3::operator*(const QTransformationMatrix<QMatrix4x4> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x4>(matrix);
}

QTransformationMatrix<QMatrix4x3> QScalingMatrix3x3::operator*(const QTransformationMatrix<QMatrix4x3> &matrix) const
{
    return this->ProductOperatorImp<QMatrix4x3>(matrix);
}

float_q QScalingMatrix3x3::GetDeterminant() const
{
	return this->ij[0][0] * this->ij[1][1] * this->ij[2][2];
}

QScalingMatrix3x3& QScalingMatrix3x3::operator*=(const QScalingMatrix3x3 &matrix)
{
    this->ij[0][0] *= matrix.ij[0][0];
    this->ij[1][1] *= matrix.ij[1][1];
    this->ij[2][2] *= matrix.ij[2][2];

    return *this;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
