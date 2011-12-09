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

QVector4::QVector4(const QTranslationMatrix<QMatrix4x3> &m) : QBaseVector4(m.ij[3][0], m.ij[3][1], m.ij[3][2], SQFloat::_1)
{
}

QVector4::QVector4(const QTranslationMatrix<QMatrix4x4> &m) : QBaseVector4(m.ij[3][0], m.ij[3][1], m.ij[3][2], SQFloat::_1)
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

QVector4 QVector4::operator + (const QBaseVector4 &v) const
{
    return QVector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}

QVector4 QVector4::operator + (const QBaseVector3 &v) const
{
    return QVector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w);
}

QVector4 QVector4::operator - (const QBaseVector4 &v) const
{
    return QVector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}

QVector4 QVector4::operator - (const QBaseVector3 &v) const
{
    return QVector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w);
}

QVector4 QVector4::operator * (const float_q &fValue) const
{
    return QVector4(this->x*fValue, this->y*fValue, this->z*fValue, this->w*fValue);
}

QVector4 QVector4::operator * (const QBaseVector4 &v) const
{
    return QVector4(this->x*v.x, this->y*v.y, this->z*v.z, this->w*v.w);
}

QVector4 QVector4::operator * (const QBaseMatrix4x4 &m) const
{
    return QVector4(this->x*m.ij[0][0] + this->y*m.ij[1][0] + this->z*m.ij[2][0] + this->w*m.ij[3][0],
                    this->x*m.ij[0][1] + this->y*m.ij[1][1] + this->z*m.ij[2][1] + this->w*m.ij[3][1],
                    this->x*m.ij[0][2] + this->y*m.ij[1][2] + this->z*m.ij[2][2] + this->w*m.ij[3][2],
                    this->x*m.ij[0][3] + this->y*m.ij[1][3] + this->z*m.ij[2][3] + this->w*m.ij[3][3]);
}

QBaseVector3 QVector4::operator * (const QBaseMatrix4x3 &m) const
{
    return QBaseVector3(this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0] + this->w * m.ij[3][0],
                        this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1] + this->w * m.ij[3][1],
                        this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2] + this->w * m.ij[3][2]);

}

QVector4 QVector4::operator / (const float_q &fValue) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (fValue != SQFloat::_0);

    return QVector4(this->x/fValue, this->y/fValue, this->z/fValue, this->w/fValue);
}

QVector4 QVector4::operator / (const QBaseVector4 &v) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (v.x != SQFloat::_0 && v.y != SQFloat::_0 &&
        v.z != SQFloat::_0 && v.w != SQFloat::_0);

    return QVector4(this->x/v.x, this->y/v.y, this->z/v.z, this->w/v.w);
}

// Asignment operators

QVector4& QVector4::operator *= (const QBaseMatrix4x4 &m)
{
    QVector4 vAux(*this);

    this->x = vAux.x*m.ij[0][0] + vAux.y*m.ij[1][0] + vAux.z*m.ij[2][0] + vAux.w*m.ij[3][0];
    this->y = vAux.x*m.ij[0][1] + vAux.y*m.ij[1][1] + vAux.z*m.ij[2][1] + vAux.w*m.ij[3][1];
    this->z = vAux.x*m.ij[0][2] + vAux.y*m.ij[1][2] + vAux.z*m.ij[2][2] + vAux.w*m.ij[3][2];
    this->w = vAux.x*m.ij[0][3] + vAux.y*m.ij[1][3] + vAux.z*m.ij[2][3] + vAux.w*m.ij[3][3];

    return *this;
}

//Unary operators

QVector4 QVector4::operator- () const
{
    return QVector4(-this->x, -this->y, -this->z, -this->w);
}

// Left float product
QVector4 operator * (const float_q &fValue, const QBaseVector4 &v)
{
    return QVector4(v.x*fValue, v.y*fValue, v.z*fValue, v.w*fValue);
}

void QVector4::CrossProduct(const QBaseVector4 &v)
{
    QVector4 aux(*this);

    this->x = aux.y*v.z - aux.z*v.y;
    this->y = aux.z*v.x - aux.x*v.z;
    this->z = aux.x*v.y - aux.y*v.x;

}

void QVector4::Transform(const QQuaternion &qR)
{
    QQuaternion qAux(this->x, this->y, this->z, SQFloat::_0);
    QQuaternion qConj;

    qR.Conjugate(qConj);

    qAux = (qR * qAux) * qConj;

    this->x = qAux.x;
    this->y = qAux.y;
    this->z = qAux.z;
}

void QVector4::Transform(const QDualQuaternion &dqTransf)
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

void QVector4::Transform(const QRotationMatrix3x3 &mRot)
{
    QVector4 vAux;

    vAux.x = this->x * mRot.ij[0][0] + this->y * mRot.ij[1][0] + this->z * mRot.ij[2][0];
    vAux.y = this->x * mRot.ij[0][1] + this->y * mRot.ij[1][1] + this->z * mRot.ij[2][1];
    vAux.z = this->x * mRot.ij[0][2] + this->y * mRot.ij[1][2] + this->z * mRot.ij[2][2];
    vAux.w = this->w;

    *this = vAux;
}

void QVector4::Transform(const QRotationMatrix3x3 &mRot, QBaseVector4 &vOut) const
{
    vOut = *this;
    reinterpret_cast<QVector4&> (vOut).Transform(mRot);
}

void QVector4::Transform(const QScaleMatrix3x3 &mScale)
{
    this->x *= mScale.ij[0][0];
    this->y *= mScale.ij[1][1];
    this->z *= mScale.ij[2][2];
}


void QVector4::Transform(const QScaleMatrix3x3 &mScale, QBaseVector4 &vOut) const
{
    vOut = *this;
    reinterpret_cast<QVector4&> (vOut).Transform(mScale);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x3> &mDisp)
{
    TransformImp(mDisp);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x4> &mDisp)
{
    TransformImp(mDisp);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x3> &mDisp, QBaseVector4 &vOut) const
{
    vOut = *this;
    reinterpret_cast<QVector4&> (vOut).Transform(mDisp);
}


void QVector4::Transform(const QTranslationMatrix<QMatrix4x4> &mDisp, QBaseVector4 &vOut) const
{
    vOut = *this;
    reinterpret_cast<QVector4&> (vOut).Transform(mDisp);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x3> &mTransf)
{
    TransformImp(mTransf);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x4> &mTransf)
{
    TransformImp(mTransf);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x3> &mTransf, QBaseVector4 &vOut) const
{
    vOut = *this;
    reinterpret_cast<QVector4&> (vOut).Transform(mTransf);
}


void QVector4::Transform(const QTransformationMatrix<QMatrix4x4> &mTransf, QBaseVector4 &vOut) const
{
    vOut = *this;
    reinterpret_cast<QVector4&> (vOut).Transform(mTransf);
}


void QVector4::Transform(const QSpaceConversionMatrix &mTransf)
{
    *this *= mTransf;
}


void QVector4::Transform(const QSpaceConversionMatrix &mTransf, QBaseVector4 &vOut) const
{
    vOut = *this;
    reinterpret_cast<QVector4&> (vOut).Transform(mTransf);
}

template <class MatrixType>
inline void QVector4::TransformImp(const QTranslationMatrix<MatrixType> &mDisp)
{
    this->x += this->w * mDisp.ij[3][0];
    this->y += this->w * mDisp.ij[3][1];
    this->z += this->w * mDisp.ij[3][2];
}

template <class MatrixType>
void QVector4::TransformImp(const QTransformationMatrix<MatrixType> &mTransf)
{
    QVector4 vAux;

    vAux.x = this->x * mTransf.ij[0][0] + this->y * mTransf.ij[1][0] + this->z * mTransf.ij[2][0] + this->w * mTransf.ij[3][0];
    vAux.y = this->x * mTransf.ij[0][1] + this->y * mTransf.ij[1][1] + this->z * mTransf.ij[2][1] + this->w * mTransf.ij[3][1];
    vAux.z = this->x * mTransf.ij[0][2] + this->y * mTransf.ij[1][2] + this->z * mTransf.ij[2][2] + this->w * mTransf.ij[3][2];

    *this = vAux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
