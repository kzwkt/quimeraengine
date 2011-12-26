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

QVector3::QVector3(const QTranslationMatrix<QMatrix4x3> &m) : QBaseVector3(m.ij[3][0], m.ij[3][1], m.ij[3][2])
{
}

QVector3::QVector3(const QTranslationMatrix<QMatrix4x4> &m) : QBaseVector3(m.ij[3][0], m.ij[3][1], m.ij[3][2])
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

QVector3 QVector3::operator + (const QBaseVector3 &v) const
{
    return QVector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

QVector3 QVector3::operator - (const QBaseVector3 &v) const
{
    return QVector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

QVector3 QVector3::operator * (const float_q &fValue) const
{
    return QVector3(this->x*fValue, this->y*fValue, this->z*fValue);
}

QVector3 QVector3::operator * (const QBaseVector3 &v) const
{
    return QVector3(this->x*v.x, this->y*v.y, this->z*v.z);
}

QVector3 QVector3::operator * (const QBaseMatrix3x3 &m) const
{
    return QVector3(this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0],
                    this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1],
                    this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2]);

}

QBaseVector4 QVector3::operator * (const QBaseMatrix3x4 &m) const
{
    return QBaseVector4(this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0],
                        this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1],
                        this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2],
                        this->x * m.ij[0][3] + this->y * m.ij[1][3] + this->z * m.ij[2][3]);

}

QVector3 QVector3::operator / (const float_q &fValue) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (fValue != SQFloat::_0);

    return QVector3(this->x/fValue, this->y/fValue, this->z/fValue);
}

QVector3 QVector3::operator / (const QBaseVector3 &v) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (v.x != SQFloat::_0 && v.y != SQFloat::_0 && v.z != SQFloat::_0);

    return QVector3(this->x/v.x, this->y/v.y, this->z/v.z);
}

// Product and assignment by a matrix 3x3
QVector3& QVector3::operator *= (const QBaseMatrix3x3 &m)
{
    QVector3 aux( this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0],
                  this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1],
                  this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2]);

    this->x = aux.x;
    this->y = aux.y;
    this->z = aux.z;

    return *this;
}

// Left float product
QVector3 operator * (const float_q &fValue, const QBaseVector3 &v)
{
    return QVector3(v.x*fValue, v.y*fValue, v.z*fValue);
}

//Unary operators

QVector3 QVector3::operator- () const
{
    return QVector3(-this->x, -this->y, -this->z);
}

void QVector3::CrossProduct(const QBaseVector3 &v)
{
    QVector3 aux(*this);

    this->x = aux.y*v.z - aux.z*v.y;
    this->y = aux.z*v.x - aux.x*v.z;
    this->z = aux.x*v.y - aux.y*v.x;

}

void QVector3::Transform(const QQuaternion &qR)
{
    QQuaternion qAux(this->x, this->y, this->z, SQFloat::_0);
    QQuaternion qConj;

    qR.Conjugate(qConj);

    qAux = (qR * qAux) * qConj;

    this->x = qAux.x;
    this->y = qAux.y;
    this->z = qAux.z;
}

void QVector3::Transform(const QDualQuaternion &dqTransf)
{
    QDualQuaternion dqAux(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                        QBaseQuaternion(this->x, this->y, this->z, SQFloat::_0));
    QDualQuaternion dqConj;

    dqTransf.DoubleConjugate(dqConj);

    dqAux = (dqTransf * dqAux ) * dqConj;

    this->x = dqAux.d.x;
    this->y = dqAux.d.y;
    this->z = dqAux.d.z;
}

void QVector3::Transform(const QSpaceConversionMatrix &mTransf)
{
	QVector3 vAux;

    vAux.x = this->x * mTransf.ij[0][0] + this->y * mTransf.ij[1][0] + this->z * mTransf.ij[2][0] + mTransf.ij[3][0];
    vAux.y = this->x * mTransf.ij[0][1] + this->y * mTransf.ij[1][1] + this->z * mTransf.ij[2][1] + mTransf.ij[3][1];
    vAux.z = this->x * mTransf.ij[0][2] + this->y * mTransf.ij[1][2] + this->z * mTransf.ij[2][2] + mTransf.ij[3][2];

    *this = vAux;
}

void QVector3::Transform(const QRotationMatrix3x3 &mRot)
{
    *this *= mRot;
}


void QVector3::Transform(const QRotationMatrix3x3 &mRot, QBaseVector3 &vOut) const
{
    vOut = *this;
    vOut.As<QVector3>().Transform(mRot);
}

void QVector3::Transform(const QScaleMatrix3x3 &mScale)
{
    this->x *= mScale.ij[0][0];
    this->y *= mScale.ij[1][1];
    this->z *= mScale.ij[2][2];
}

void QVector3::Transform(const QScaleMatrix3x3 &mScale, QBaseVector3 &vOut) const
{
    vOut = *this;
    vOut.As<QVector3>().Transform(mScale);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x3> &mDisp)
{
    TransformImp(mDisp);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x4> &mDisp)
{
    TransformImp(mDisp);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x3> &mDisp, QBaseVector3 &vOut) const
{
    vOut = *this;
    vOut.As<QVector3>().Transform(mDisp);
}

void QVector3::Transform(const QTranslationMatrix<QMatrix4x4> &mDisp, QBaseVector3 &vOut) const
{
    vOut = *this;
    vOut.As<QVector3>().Transform(mDisp);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x3> &mTransf)
{
    TransformImp(mTransf);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x4> &mTransf)
{
    TransformImp(mTransf);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x3> &mTransf, QBaseVector3 &vOut) const
{
    vOut = *this;
    vOut.As<QVector3>().Transform(mTransf);
}

void QVector3::Transform(const QTransformationMatrix<QMatrix4x4> &mTransf, QBaseVector3 &vOut) const
{
    vOut = *this;
    vOut.As<QVector3>().Transform(mTransf);
}


void QVector3::Transform(const QSpaceConversionMatrix &mTransf, QBaseVector3 &vOut) const
{
    vOut = *this;
    vOut.As<QVector3>().Transform(mTransf);
}

template <class MatrixType>
inline void QVector3::TransformImp(const QTranslationMatrix<MatrixType> &mDisp)
{
    this->x += mDisp.ij[3][0];
    this->y += mDisp.ij[3][1];
    this->z += mDisp.ij[3][2];
}

template <class MatrixType>
void QVector3::TransformImp(const QTransformationMatrix<MatrixType> &mTransf)
{
    QVector3 vAux;

    vAux.x = this->x * mTransf.ij[0][0] + this->y * mTransf.ij[1][0] + this->z * mTransf.ij[2][0] + mTransf.ij[3][0];
    vAux.y = this->x * mTransf.ij[0][1] + this->y * mTransf.ij[1][1] + this->z * mTransf.ij[2][1] + mTransf.ij[3][1];
    vAux.z = this->x * mTransf.ij[0][2] + this->y * mTransf.ij[1][2] + this->z * mTransf.ij[2][2] + mTransf.ij[3][2];

    *this = vAux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
