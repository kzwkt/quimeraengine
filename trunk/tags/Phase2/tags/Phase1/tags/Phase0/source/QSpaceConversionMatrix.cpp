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

#include "QSpaceConversionMatrix.h"

#include "QBaseQuaternion.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTransformationMatrix.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QBaseQuaternion.h"
#include "QMatrix4x3.h"
#include "SQFloat.h"
#include "SQAngle.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;


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
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
    
QSpaceConversionMatrix::QSpaceConversionMatrix()
{
    this->ResetToIdentity();
}

QSpaceConversionMatrix::QSpaceConversionMatrix(const QSpaceConversionMatrix &matrix) : QMatrix4x4(matrix)
{
}

QSpaceConversionMatrix::QSpaceConversionMatrix(const QBaseMatrix4x4 &matrix) : QMatrix4x4(matrix)
{
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QSpaceConversionMatrix& QSpaceConversionMatrix::operator=(const QBaseMatrix4x4 &matrix)
{
    QBaseMatrix4x4::operator=(matrix);
    return *this;
}

QSpaceConversionMatrix QSpaceConversionMatrix::operator*(const QSpaceConversionMatrix &matrix) const
{
    return rcast_q(*this, const QMatrix4x4&) * rcast_q(matrix, const QMatrix4x4&);
}

QSpaceConversionMatrix& QSpaceConversionMatrix::operator*=(const QSpaceConversionMatrix &matrix)
{
    rcast_q(*this, QMatrix4x4&) *= rcast_q(matrix, const QMatrix4x4&);
    return *this;
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QBaseVector3 &vTranslation, const QBaseQuaternion &qRotation, const QBaseVector3 &vScale)
{
    QTransformationMatrix<QMatrix4x4> aux(vTranslation, qRotation, vScale);

    *this = rcast_q(aux, QSpaceConversionMatrix&);
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QBaseVector4 &vTranslation, const QBaseQuaternion &qRotation, const QBaseVector3 &vScale)
{
    QTransformationMatrix<QMatrix4x4> aux(vTranslation, qRotation, vScale);

    *this = rcast_q(aux, QSpaceConversionMatrix&);
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QTransformationMatrix<QMatrix4x4> &translation, const QTransformationMatrix<QMatrix4x4> &rotation,
                                                 const QTransformationMatrix<QMatrix4x4> &scale)
{
    this->ij[0][0] = scale.ij[0][0] * rotation.ij[0][0];
    this->ij[0][1] = scale.ij[0][0] * rotation.ij[0][1];
    this->ij[0][2] = scale.ij[0][0] * rotation.ij[0][2];
    this->ij[0][3] = SQFloat::_0;

    this->ij[1][0] = scale.ij[1][1] * rotation.ij[1][0];
    this->ij[1][1] = scale.ij[1][1] * rotation.ij[1][1];
    this->ij[1][2] = scale.ij[1][1] * rotation.ij[1][2];
    this->ij[1][3] = SQFloat::_0;

    this->ij[2][0] = scale.ij[2][2] * rotation.ij[2][0];
    this->ij[2][1] = scale.ij[2][2] * rotation.ij[2][1];
    this->ij[2][2] = scale.ij[2][2] * rotation.ij[2][2];
    this->ij[2][3] = SQFloat::_0;

    this->ij[3][0] = translation.ij[3][0];
    this->ij[3][1] = translation.ij[3][1];
    this->ij[3][2] = translation.ij[3][2];
    this->ij[3][3] = SQFloat::_1;
}

void QSpaceConversionMatrix::SetViewSpaceMatrix(const QVector3 &vPointOfView, const QVector3 &vTarget,
                                                const QVector3 &vUpDirection)
{
    QVector3 vZAxis = (vTarget - vPointOfView).Normalize();

    QVector3 vXAxis = vUpDirection.CrossProduct(vZAxis).Normalize();

    QVector3 vYAxis = vZAxis.CrossProduct(vXAxis);

    this->ij[0][0] = vXAxis.x;
    this->ij[0][1] = vYAxis.x;
    this->ij[0][2] = vZAxis.x;
    this->ij[0][3] = SQFloat::_0;

    this->ij[1][0] = vXAxis.y;
    this->ij[1][1] = vYAxis.y;
    this->ij[1][2] = vZAxis.y;
    this->ij[1][3] = SQFloat::_0;

    this->ij[2][0] = vXAxis.z;
    this->ij[2][1] = vYAxis.z;
    this->ij[2][2] = vZAxis.z;
    this->ij[2][3] = SQFloat::_0;

    this->ij[3][0] = -vXAxis.DotProduct(vPointOfView);
    this->ij[3][1] = -vYAxis.DotProduct(vPointOfView);
    this->ij[3][2] = -vZAxis.DotProduct(vPointOfView);
    this->ij[3][3] = SQFloat::_1;
}

void QSpaceConversionMatrix::SetViewSpaceMatrix(const QVector4 &vPointOfView, const QVector4 &vTarget,
                                                const QVector4 &vUpDirection)
{
    this->SetViewSpaceMatrix(QVector3(vPointOfView),
                             QVector3(vTarget),
                             QVector3(vUpDirection));
}

void QSpaceConversionMatrix::SetProjectionSpaceMatrix(const float_q &fNearClipPlane, const float_q &fFarClipPlane,
                                                      const float_q &fAspectRatio, const float_q &fVerticalFOV)
{
    // The clipping planes should not coincide
    QE_ASSERT(SQFloat::AreNotEqual(fNearClipPlane, fFarClipPlane))

    // The aspect ratio must be positive and not equal zero
    QE_ASSERT(SQFloat::IsGreaterThan(fAspectRatio, SQFloat::_0))

    // The vertical field of view must be positive and not equal zero
    QE_ASSERT(SQFloat::IsGreaterThan(fVerticalFOV, SQFloat::_0))

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_q& HALF_VERT_FOV = SQAngle::DegreesToRadians(fVerticalFOV * SQFloat::_0_5);
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q& HALF_VERT_FOV = fVerticalFOV * SQFloat::_0_5;
    #endif

    QE_ASSERT( SQFloat::AreNotEqual(HALF_VERT_FOV, SQAngle::_HalfPi) )

    const float_q& SCALE_Y  = float_q((double)SQFloat::_1 / tan_q((double)HALF_VERT_FOV));
    const float_q& SCALE_X  = float_q((double)SCALE_Y / (double)fAspectRatio);

    this->ij[0][0] = SCALE_X;
    this->ij[0][1] = SQFloat::_0;
    this->ij[0][2] = SQFloat::_0;
    this->ij[0][3] = SQFloat::_0;
    this->ij[1][0] = SQFloat::_0;
    this->ij[1][1] = SCALE_Y;
    this->ij[1][2] = SQFloat::_0;
    this->ij[1][3] = SQFloat::_0;
    this->ij[2][0] = SQFloat::_0;
    this->ij[2][1] = SQFloat::_0;
    this->ij[2][2] = fFarClipPlane / (fFarClipPlane - fNearClipPlane);
    this->ij[2][3] = SQFloat::_1;
    this->ij[3][0] = SQFloat::_0;
    this->ij[3][2] = -fNearClipPlane * this->ij[2][2];
    this->ij[3][1] = SQFloat::_0;
    this->ij[3][3] = SQFloat::_0;

}

QSpaceConversionMatrix QSpaceConversionMatrix::SwitchHandConventionViewSpaceMatrix() const
{
    QVector3 vPOV = QVector3(-(this->ij[3][0]*this->ij[0][0] + this->ij[3][1]*this->ij[0][1] + this->ij[3][2]*this->ij[0][2]),
                             -(this->ij[3][0]*this->ij[1][0] + this->ij[3][1]*this->ij[1][1] + this->ij[3][2]*this->ij[1][2]),
                             -(this->ij[3][0]*this->ij[2][0] + this->ij[3][1]*this->ij[2][1] + this->ij[3][2]*this->ij[2][2]) );

    QVector3 vUp(this->ij[0][1], this->ij[1][1], this->ij[2][1]);

    QVector3 vZAxis = QVector3(-this->ij[0][2], -this->ij[1][2], -this->ij[2][2]);

    QVector3 vXAxis = vUp.CrossProduct(vZAxis);

    QVector3 vYAxis = vZAxis.CrossProduct(vXAxis);

    return QSpaceConversionMatrix( QMatrix4x4(vXAxis.x, vYAxis.x, vZAxis.x, SQFloat::_0,
                                              vXAxis.y, vYAxis.y, vZAxis.y, SQFloat::_0,
                                              vXAxis.z, vYAxis.z, vZAxis.z, SQFloat::_0,
                                              -vXAxis.DotProduct(vPOV), -vYAxis.DotProduct(vPOV), -vZAxis.DotProduct(vPOV), SQFloat::_1));
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QTranslationMatrix<QMatrix4x3> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
{
    SetWorldSpaceMatrixImp(translation, rotation, scale);
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QTranslationMatrix<QMatrix4x4> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
{
    SetWorldSpaceMatrixImp(translation, rotation, scale);
}

QSpaceConversionMatrix QSpaceConversionMatrix::SwitchHandConventionProjectionSpaceMatrix() const
{
    QSpaceConversionMatrix switchedMatrix = *this;
    switchedMatrix.ij[2][2] = -this->ij[2][2];
    switchedMatrix.ij[2][3] = -this->ij[2][3];
    return switchedMatrix;
}

template <class MatrixType>
void QSpaceConversionMatrix::SetWorldSpaceMatrixImp(const QTranslationMatrix<MatrixType> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
{
    QTransformationMatrix<QMatrix4x4> aux(translation, rotation, scale);

    *this = rcast_q(aux, QSpaceConversionMatrix&);
}

QSpaceConversionMatrix QSpaceConversionMatrix::SwitchHandConventionWorldSpaceMatrix() const
{
    return QSpaceConversionMatrix(rcast_q(*this, const QTransformationMatrix<QMatrix4x4>&).SwitchHandConvention());
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
