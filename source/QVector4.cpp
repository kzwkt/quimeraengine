// [TERMS&CONDITIONS]

#include "QVector4.h"

#include "QQuaternion.h"
#include "QDualQuaternion.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScaleMatrix3x3.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"

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

QVector4::QVector4(const QTranslationMatrix<QMatrix4x3> &translation) :
                       QBaseVector4(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2], SQFloat::_1)
{
}

QVector4::QVector4(const QTranslationMatrix<QMatrix4x4> &translation) :
                       QBaseVector4(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2], SQFloat::_1)
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

QVector4 QVector4::operator+(const QBaseVector4 &vVector) const
{
    return QVector4(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z, this->w + vVector.w);
}

QVector4 QVector4::operator+(const QBaseVector3 &vVector) const
{
    return QVector4(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z, this->w);
}

QVector4 QVector4::operator-(const QBaseVector4 &vVector) const
{
    return QVector4(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z, this->w - vVector.w);
}

QVector4 QVector4::operator-(const QBaseVector3 &vVector) const
{
    return QVector4(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z, this->w);
}

QVector4 QVector4::operator*(const float_q &fScalar) const
{
    return QVector4(this->x * fScalar, this->y * fScalar, this->z * fScalar, this->w * fScalar);
}

QVector4 QVector4::operator*(const QBaseVector4 &vVector) const
{
    return QVector4(this->x * vVector.x, this->y * vVector.y, this->z * vVector.z, this->w * vVector.w);
}

QVector4 QVector4::operator*(const QBaseMatrix4x4 &matrix) const
{
    return QVector4(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0] + this->w * matrix.ij[3][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1] + this->w * matrix.ij[3][1],
                    this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2] + this->w * matrix.ij[3][2],
                    this->x * matrix.ij[0][3] + this->y * matrix.ij[1][3] + this->z * matrix.ij[2][3] + this->w * matrix.ij[3][3]);
}

QBaseVector3 QVector4::operator*(const QBaseMatrix4x3 &matrix) const
{
    return QBaseVector3(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0] + this->w * matrix.ij[3][0],
                        this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1] + this->w * matrix.ij[3][1],
                        this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2] + this->w * matrix.ij[3][2]);

}

QVector4 QVector4::operator/(const float_q &fScalar) const
{
    // Checkout to avoid division by 0
    QE_ASSERT(fScalar != SQFloat::_0);

    const float_q &fDivisor = SQFloat::_1/fScalar;

    return QVector4(this->x * fDivisor, this->y * fDivisor, this->z * fDivisor, this->w * fDivisor);
}

QVector4 QVector4::operator/(const QBaseVector4 &vVector) const
{
    // Checkout to avoid division by 0
    QE_ASSERT(vVector.x != SQFloat::_0 && vVector.y != SQFloat::_0 &&
              vVector.z != SQFloat::_0 && vVector.w != SQFloat::_0);

    return QVector4(this->x / vVector.x, this->y / vVector.y, this->z / vVector.z, this->w / vVector.w);
}

QVector4& QVector4::operator*=(const QBaseMatrix4x4 &matrix)
{
    QVector4 vAux(*this);

    this->x = vAux.x * matrix.ij[0][0] + vAux.y * matrix.ij[1][0] + vAux.z * matrix.ij[2][0] + vAux.w * matrix.ij[3][0];
    this->y = vAux.x * matrix.ij[0][1] + vAux.y * matrix.ij[1][1] + vAux.z * matrix.ij[2][1] + vAux.w * matrix.ij[3][1];
    this->z = vAux.x * matrix.ij[0][2] + vAux.y * matrix.ij[1][2] + vAux.z * matrix.ij[2][2] + vAux.w * matrix.ij[3][2];
    this->w = vAux.x * matrix.ij[0][3] + vAux.y * matrix.ij[1][3] + vAux.z * matrix.ij[2][3] + vAux.w * matrix.ij[3][3];

    return *this;
}

QVector4 QVector4::operator-() const
{
    return QVector4(-this->x, -this->y, -this->z, -this->w);
}

// Left float product
QVector4 operator*(const float_q &fScalar, const QBaseVector4 &vVector)
{
    return QVector4(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar, vVector.w * fScalar);
}

float_q QVector4::GetLength() const
{
    return sqrt_q(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

float_q QVector4::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
}

bool QVector4::IsZero() const
{
    return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y) &&
            SQFloat::IsZero(this->z) && SQFloat::IsZero(this->w);
}

bool QVector4::IsVectorOfOnes() const
{
    return SQFloat::AreEquals(this->x, SQFloat::_1) && SQFloat::AreEquals(this->y, SQFloat::_1) &&
            SQFloat::AreEquals(this->z, SQFloat::_1) && SQFloat::AreEquals(this->w, SQFloat::_1);
}

float_q QVector4::DotProduct(const QBaseVector4 &vVector) const
{
    return(this->x * vVector.x + this->y * vVector.y + this->z * vVector.z + this->w * vVector.w);
}

float_q QVector4::DotProductAngle(const QBaseVector4 &vVector) const
{
    float_q fLength = sqrt_q( (this->x*this->x + this->y*this->y + this->z*this->z) * (vVector.x*vVector.x + vVector.y*vVector.y + vVector.z*vVector.z) );

    // Checkout to avoid division by zero.
    QE_ASSERT(fLength != SQFloat::_0);

    float_q fDot = (this->x*vVector.x + this->y*vVector.y + this->z*vVector.z) / fLength;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1);

    float_q fAngle = acos_q(fDot);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        SQAngle::RadiansToDegrees(fAngle, fAngle);
    #endif

    return fAngle;
}

void QVector4::CrossProduct(const QBaseVector4 &vVector)
{
    QVector4 vAux(*this);

    this->x = vAux.y * vVector.z - vAux.z * vVector.y;
    this->y = vAux.z * vVector.x - vAux.x * vVector.z;
    this->z = vAux.x * vVector.y - vAux.y * vVector.x;

}

void QVector4::Transform(const QQuaternion &qRotation)
{
    QQuaternion qAux(this->x, this->y, this->z, SQFloat::_0);
    QQuaternion qConj;

    qRotation.Conjugate(qConj);

    qAux = (qRotation * qAux) * qConj;

    this->x = qAux.x;
    this->y = qAux.y;
    this->z = qAux.z;
}

void QVector4::Transform(const QDualQuaternion &transformation)
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

void QVector4::Transform(const QRotationMatrix3x3 &rotation)
{
    QVector4 vAux;

    vAux.x = this->x * rotation.ij[0][0] + this->y * rotation.ij[1][0] + this->z * rotation.ij[2][0];
    vAux.y = this->x * rotation.ij[0][1] + this->y * rotation.ij[1][1] + this->z * rotation.ij[2][1];
    vAux.z = this->x * rotation.ij[0][2] + this->y * rotation.ij[1][2] + this->z * rotation.ij[2][2];
    vAux.w = this->w;

    *this = vAux;
}

void QVector4::Transform(const QRotationMatrix3x3 &rotation, QBaseVector4 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector4>().Transform(rotation);
}

void QVector4::Transform(const QScaleMatrix3x3 &scale)
{
    this->x *= scale.ij[0][0];
    this->y *= scale.ij[1][1];
    this->z *= scale.ij[2][2];
}


void QVector4::Transform(const QScaleMatrix3x3 &scale, QBaseVector4 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector4>().Transform(scale);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x3> &translation)
{
    TransformImp(translation);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x4> &translation)
{
    TransformImp(translation);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x3> &translation, QBaseVector4 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector4>().Transform(translation);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x4> &translation, QBaseVector4 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector4>().Transform(translation);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x3> &transformation)
{
    TransformImp(transformation);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x4> &transformation)
{
    TransformImp(transformation);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QBaseVector4 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector4>().Transform(transformation);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QBaseVector4 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector4>().Transform(transformation);
}


void QVector4::Transform(const QSpaceConversionMatrix &conversion)
{
    *this *= conversion;
}


void QVector4::Transform(const QSpaceConversionMatrix &conversion, QBaseVector4 &vOutVector) const
{
    vOutVector = *this;
    vOutVector.As<QVector4>().Transform(conversion);
}

string_q QVector4::ToString() const
{
    return QE_L("V4(") + SQFloat::ToString(this->x) +
           QE_L(", ")  + SQFloat::ToString(this->y) +
           QE_L(", ")  + SQFloat::ToString(this->z) +
           QE_L(", ")  + SQFloat::ToString(this->w) + QE_L(")");
}

template <class MatrixType>
inline void QVector4::TransformImp(const QTranslationMatrix<MatrixType> &translation)
{
    this->x += this->w * translation.ij[3][0];
    this->y += this->w * translation.ij[3][1];
    this->z += this->w * translation.ij[3][2];
}

template <class MatrixType>
void QVector4::TransformImp(const QTransformationMatrix<MatrixType> &transformation)
{
    QVector4 vAux;

    vAux.x = this->x * transformation.ij[0][0] + this->y * transformation.ij[1][0] + this->z * transformation.ij[2][0] + this->w * transformation.ij[3][0];
    vAux.y = this->x * transformation.ij[0][1] + this->y * transformation.ij[1][1] + this->z * transformation.ij[2][1] + this->w * transformation.ij[3][1];
    vAux.z = this->x * transformation.ij[0][2] + this->y * transformation.ij[1][2] + this->z * transformation.ij[2][2] + this->w * transformation.ij[3][2];

    *this = vAux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
