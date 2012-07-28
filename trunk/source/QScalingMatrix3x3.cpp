// [TERMS&CONDITIONS]

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
