// [TERMS&CONDITIONS]

#include "QVector3.h"

#include "QQuaternion.h"
#include "QDualQuaternion.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QSpaceConversionMatrix.h"
#include "QTranslationMatrix.h"
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
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QVector3::QVector3(const QTranslationMatrix<QMatrix4x3> &translation) :
                       QBaseVector3(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2])
{
}

QVector3::QVector3(const QTranslationMatrix<QMatrix4x4> &translation) :
                       QBaseVector3(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2])
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QVector3 QVector3::operator+(const QBaseVector3 &vVector) const
{
    return QVector3(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z);
}

QVector3 QVector3::operator-(const QBaseVector3 &vVector) const
{
    return QVector3(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z);
}

QVector3 QVector3::operator*(const float_q &fScalar) const
{
    return QVector3(this->x * fScalar, this->y * fScalar, this->z * fScalar);
}

QVector3 QVector3::operator*(const QBaseVector3 &vVector) const
{
    return QVector3(this->x * vVector.x, this->y * vVector.y, this->z * vVector.z);
}

QVector3 QVector3::operator*(const QBaseMatrix3x3 &matrix) const
{
    return QVector3(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                    this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2]);

}

QBaseVector4 QVector3::operator*(const QBaseMatrix3x4 &matrix) const
{
    return QBaseVector4(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                        this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                        this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2],
                        this->x * matrix.ij[0][3] + this->y * matrix.ij[1][3] + this->z * matrix.ij[2][3]);

}

QVector3 QVector3::operator/(const float_q &fScalar) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (fScalar != SQFloat::_0)

    const float_q &fDivisor = SQFloat::_1/fScalar;

    return QVector3(this->x * fDivisor, this->y * fDivisor, this->z * fDivisor);
}

QVector3 QVector3::operator/(const QBaseVector3 &vVector) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (vVector.x != SQFloat::_0 && vVector.y != SQFloat::_0 && vVector.z != SQFloat::_0)

    return QVector3(this->x / vVector.x, this->y / vVector.y, this->z / vVector.z);
}

QVector3& QVector3::operator*=(const QBaseMatrix3x3 &matrix)
{
    QVector3 vAux( this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                   this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                   this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2]);

    this->x = vAux.x;
    this->y = vAux.y;
    this->z = vAux.z;

    return *this;
}

QVector3 operator*(const float_q &fScalar, const QBaseVector3 &vVector)
{
    return QVector3(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar);
}

QVector3 QVector3::operator-() const
{
    return QVector3(-this->x, -this->y, -this->z);
}

float_q QVector3::GetLength() const
{
    return sqrt_q(this->x * this->x + this->y * this->y + this->z * this->z);
}

float_q QVector3::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y + this->z*this->z;
}

bool QVector3::IsZero() const
{
    return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y) && SQFloat::IsZero(this->z);
}

bool QVector3::IsVectorOfOnes() const
{
    return SQFloat::AreEquals(this->x, SQFloat::_1) && SQFloat::AreEquals(this->y, SQFloat::_1) && SQFloat::AreEquals(this->z, SQFloat::_1);
}

float_q QVector3::DotProduct(const QBaseVector3 &vVector) const
{
    return(this->x * vVector.x + this->y * vVector.y + this->z * vVector.z);
}

float_q QVector3::DotProductAngle(const QVector3 &vVector) const
{
    float_q fLength = this->GetLength() * vVector.GetLength();

    // Checkout to avoid division by zero.
    QE_ASSERT(fLength != SQFloat::_0)

    float_q fDot = this->DotProduct(vVector)/fLength;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1)

    float_q fAngle = acos_q(fDot);
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle, fAngle);
    #endif

    return fAngle;
}

void QVector3::CrossProduct(const QBaseVector3 &vVector)
{
    QVector3 vAux(*this);

    this->x = vAux.y * vVector.z - vAux.z * vVector.y;
    this->y = vAux.z * vVector.x - vAux.x * vVector.z;
    this->z = vAux.x * vVector.y - vAux.y * vVector.x;

}

float_q QVector3::Distance(const QBaseVector3 &vVector) const
{
    return (*this - vVector).GetLength();
}

void QVector3::Transform(const QQuaternion &qRotation)
{
    QQuaternion qAux(this->x, this->y, this->z, SQFloat::_0);
    QQuaternion qConj;

    qRotation.Conjugate(qConj);

    qAux = (qRotation * qAux) * qConj;

    this->x = qAux.x;
    this->y = qAux.y;
    this->z = qAux.z;
}

void QVector3::Transform(const QDualQuaternion &transformation)
{
    QDualQuaternion dqAux(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                          QBaseQuaternion(this->x, this->y, this->z, SQFloat::_0));
    QDualQuaternion dqConj;

    transformation.DoubleConjugate(dqConj);

    dqAux = (transformation * dqAux ) * dqConj;

    this->x = dqAux.d.x;
    this->y = dqAux.d.y;
    this->z = dqAux.d.z;
}

void QVector3::Transform(const QSpaceConversionMatrix &conversion)
{
	QVector3 vAux;

    vAux.x = this->x * conversion.ij[0][0] + this->y * conversion.ij[1][0] + this->z * conversion.ij[2][0] + conversion.ij[3][0];
    vAux.y = this->x * conversion.ij[0][1] + this->y * conversion.ij[1][1] + this->z * conversion.ij[2][1] + conversion.ij[3][1];
    vAux.z = this->x * conversion.ij[0][2] + this->y * conversion.ij[1][2] + this->z * conversion.ij[2][2] + conversion.ij[3][2];

    *this = vAux;
}

void QVector3::Transform(const QRotationMatrix3x3 &rotation)
{
    *this *= rotation;
}


void QVector3::Transform(const QRotationMatrix3x3 &rotation, QBaseVector3 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector3>().Transform(rotation);
}

void QVector3::Transform(const QScaleMatrix3x3 &scale)
{
    this->x *= scale.ij[0][0];
    this->y *= scale.ij[1][1];
    this->z *= scale.ij[2][2];
}

void QVector3::Transform(const QScaleMatrix3x3 &scale, QBaseVector3 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector3>().Transform(scale);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x3> &translation)
{
    TransformImp(translation);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x4> &translation)
{
    TransformImp(translation);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x3> &translation, QBaseVector3 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector3>().Transform(translation);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x4> &translation, QBaseVector3 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector3>().Transform(translation);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x3> &transformation)
{
    TransformImp(transformation);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x4> &transformation)
{
    TransformImp(transformation);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QBaseVector3 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector3>().Transform(transformation);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QBaseVector3 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector3>().Transform(transformation);
}


void QVector3::Transform(const QSpaceConversionMatrix &conversion, QBaseVector3 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector3>().Transform(conversion);
}

string_q QVector3::ToString() const
{
    return QE_L("V3(") + SQFloat::ToString(this->x) +
           QE_L(",")  + SQFloat::ToString(this->y) +
           QE_L(",")  + SQFloat::ToString(this->z) + QE_L(")");
}

template <class MatrixType>
inline void QVector3::TransformImp(const QTranslationMatrix<MatrixType> &translation)
{
    this->x += translation.ij[3][0];
    this->y += translation.ij[3][1];
    this->z += translation.ij[3][2];
}

template <class MatrixType>
void QVector3::TransformImp(const QTransformationMatrix<MatrixType> &transformation)
{
    QVector3 vAux;

    vAux.x = this->x * transformation.ij[0][0] + this->y * transformation.ij[1][0] + this->z * transformation.ij[2][0] + transformation.ij[3][0];
    vAux.y = this->x * transformation.ij[0][1] + this->y * transformation.ij[1][1] + this->z * transformation.ij[2][1] + transformation.ij[3][1];
    vAux.z = this->x * transformation.ij[0][2] + this->y * transformation.ij[1][2] + this->z * transformation.ij[2][2] + transformation.ij[3][2];

    *this = vAux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
