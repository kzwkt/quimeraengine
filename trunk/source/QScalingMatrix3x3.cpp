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

#include "Assertions.h"
#include "QVector3.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QTransformationMatrix.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "SQFloat.h"

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
    
QScalingMatrix3x3::QScalingMatrix3x3()
{
    this->ResetToIdentity();
}

QScalingMatrix3x3::QScalingMatrix3x3(const QScalingMatrix3x3 &scale) : QMatrix3x3(scale)
{
}

QScalingMatrix3x3::QScalingMatrix3x3(const QBaseMatrix3x3 &scale) : QMatrix3x3(scale)
{
}

QScalingMatrix3x3::QScalingMatrix3x3(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
{
    this->ij[0][0] = fScaleX;
    this->ij[1][1] = fScaleY;
    this->ij[2][2] = fScaleZ;

    this->ij[0][1] = this->ij[0][2] = this->ij[1][0] =
    this->ij[1][2] = this->ij[2][0] = this->ij[2][1] = SQFloat::_0;
}

QScalingMatrix3x3::QScalingMatrix3x3(const QBaseVector3 &vScale)
{
    this->ij[0][0] = vScale.x;
    this->ij[1][1] = vScale.y;
    this->ij[2][2] = vScale.z;

    this->ij[0][1] = this->ij[0][2] = this->ij[1][0] =
    this->ij[1][2] = this->ij[2][0] = this->ij[2][1] = SQFloat::_0;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
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

QScalingMatrix3x3& QScalingMatrix3x3::operator=(const QBaseMatrix3x3 &matrix)
{
    QBaseMatrix3x3::operator=(matrix);
    return *this;
}

QScalingMatrix3x3 QScalingMatrix3x3::Invert() const
{
    // If one of the diagonal elements is 0, the matrix has not inverse.
    QE_ASSERT_WARNING(this->ij[0][0] != SQFloat::_0 && this->ij[1][1] != SQFloat::_0 && this->ij[2][2] != SQFloat::_0, "One of the diagonal elements equals zero, so the matrix has not inverse");

    return QScalingMatrix3x3(SQFloat::_1 / this->ij[0][0], SQFloat::_1 / this->ij[1][1], SQFloat::_1 / this->ij[2][2]);
}

void QScalingMatrix3x3::GetScale(float_q &fScaleX, float_q &fScaleY, float_q &fScaleZ) const
{
    fScaleX = this->ij[0][0];
    fScaleY = this->ij[1][1];
    fScaleZ = this->ij[2][2];
}

void QScalingMatrix3x3::GetScale(QBaseVector3 &vScale) const
{
    vScale.x = this->ij[0][0];
    vScale.y = this->ij[1][1];
    vScale.z = this->ij[2][2];
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

template <class MatrixType>
QTransformationMatrix<MatrixType> QScalingMatrix3x3::ProductOperatorImp(const QTranslationMatrix<MatrixType> &matrix) const
{
    QTransformationMatrix<MatrixType> aux(QTransformationMatrix<MatrixType>::GetIdentity());

    aux.ij[0][0] = this->ij[0][0];
    aux.ij[1][1] = this->ij[1][1];
    aux.ij[2][2] = this->ij[2][2];

    aux.ij[3][0] = matrix.ij[3][0];
    aux.ij[3][1] = matrix.ij[3][1];
    aux.ij[3][2] = matrix.ij[3][2];

    return aux;
}

/// <summary>
/// Multiplies a 4x3 or 4x4 transformation matrix by the resident matrix.
/// </summary>
/// <remarks>
/// This product is not conmmutative.
/// </remarks>
/// <typeparam name="MatrixType">Allowed types: QMatrix4x3, QMatrix4x4.</typeparam>
/// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
/// <returns>
/// The resultant 4x3 or 4x4 transformation matrix, depending on the method template parameter.
/// </returns>
template <class MatrixType>
QTransformationMatrix<MatrixType> QScalingMatrix3x3::ProductOperatorImp(const QTransformationMatrix<MatrixType> &matrix) const
{
    QTransformationMatrix<MatrixType> aux(QTransformationMatrix<MatrixType>::GetIdentity());

    aux.ij[3][0] = matrix.ij[3][0];
    aux.ij[3][1] = matrix.ij[3][1];
    aux.ij[3][2] = matrix.ij[3][2];

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


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QScalingMatrix3x3& QScalingMatrix3x3::GetIdentity()
{
    static const QScalingMatrix3x3 IDENTITY(QMatrix3x3::GetIdentity());
    return IDENTITY;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
