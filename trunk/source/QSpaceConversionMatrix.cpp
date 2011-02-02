// [TERMS&CONDITIONS]

#include "QSpaceConversionMatrix.h"

#include "QBaseQuaternion.h"
#include "QVector3.h"
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

// Binary operators

QSpaceConversionMatrix QSpaceConversionMatrix::operator*(const QSpaceConversionMatrix &m) const
{
    QSpaceConversionMatrix aux;

    aux = static_cast<QSpaceConversionMatrix>( static_cast<QMatrix4x4>(*this) * static_cast<QMatrix4x4>(m) );

    return aux;
}

QSpaceConversionMatrix& QSpaceConversionMatrix::operator*=(const QSpaceConversionMatrix &m) 
{
    static_cast<QMatrix4x4>(*this) *= static_cast<QMatrix4x4>(m);
    return *this;
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QBaseVector3 &vDisp, const QBaseQuaternion &qRot, const QBaseVector3 &vScale)
{
    QTransformationMatrix4x4 aux(vDisp, qRot, vScale);

    *this = static_cast<QSpaceConversionMatrix>(aux);
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QBaseVector4 &vDisp, const QBaseQuaternion &qRot, const QBaseVector3 &vScale)
{
    QTransformationMatrix4x4 aux(vDisp, qRot, vScale);

    *this = static_cast<QSpaceConversionMatrix>(aux);
}

void QSpaceConversionMatrix::SetWorldSpaceMatrix(const QTransformationMatrix4x4 &mDisp, const QTransformationMatrix4x4 &mRot, 
    const QTransformationMatrix4x4 &mScale)
{
    this->ij[0][0] = mScale.ij[0][0]*mRot.ij[0][0];
    this->ij[0][1] = mScale.ij[0][0]*mRot.ij[0][1];
    this->ij[0][2] = mScale.ij[0][0]*mRot.ij[0][2];
    this->ij[0][3] = QFloat::_0;

    this->ij[1][0] = mScale.ij[1][1]*mRot.ij[1][0];
    this->ij[1][1] = mScale.ij[1][1]*mRot.ij[1][1];
    this->ij[1][2] = mScale.ij[1][1]*mRot.ij[1][2];
    this->ij[1][3] = QFloat::_0;

    this->ij[2][0] = mScale.ij[2][2]*mRot.ij[2][0];
    this->ij[2][1] = mScale.ij[2][2]*mRot.ij[2][1];
    this->ij[2][2] = mScale.ij[2][2]*mRot.ij[2][2];
    this->ij[2][3] = QFloat::_0;

    this->ij[3][0] = mDisp.ij[3][0];
    this->ij[3][1] = mDisp.ij[3][1];
    this->ij[3][2] = mDisp.ij[3][2];
    this->ij[3][3] = QFloat::_1;
}

void QSpaceConversionMatrix::SetViewSpaceMatrix(const QBaseVector3 &vPointOfView, const QBaseVector3 &vTarget, 
    const QBaseVector3 &vUpDirection)
{
    QVector3 vZAxis(vTarget.x - vPointOfView.x, vTarget.y - vPointOfView.y, vTarget.z - vPointOfView.z);
    vZAxis.Normalize();

    QVector3 vXAxis(vUpDirection);
    vXAxis.CrossProduct(vZAxis);
    vXAxis.Normalize();

    QVector3 vYAxis(vZAxis);
    vYAxis.CrossProduct(vXAxis);

    this->ij[0][0] = vXAxis.x;
    this->ij[0][1] = vYAxis.x;
    this->ij[0][2] = vZAxis.x;
    this->ij[0][3] = QFloat::_0;

    this->ij[1][0] = vXAxis.y;
    this->ij[1][1] = vYAxis.y;
    this->ij[1][2] = vZAxis.y;
    this->ij[1][3] = QFloat::_0;

    this->ij[2][0] = vXAxis.z;
    this->ij[2][1] = vYAxis.z;
    this->ij[2][2] = vZAxis.z;
    this->ij[2][3] = QFloat::_0;

    this->ij[3][0] = -vXAxis.DotProduct(vPointOfView);
    this->ij[3][1] = -vYAxis.DotProduct(vPointOfView);
    this->ij[3][2] = -vZAxis.DotProduct(vPointOfView);
    this->ij[3][3] = QFloat::_1;
}

void QSpaceConversionMatrix::SetProjectionSpaceMatrix(const float_q &fNearClipPlane, const float_q &fFarClipPlane, 
        const float_q &fAspectRatio, const float_q &fVerticalFOV)
{
    QE_ASSERT(QFloat::AreNotEquals(fNearClipPlane, fFarClipPlane));
    QE_ASSERT(fAspectRatio > QFloat::_0);
    QE_ASSERT(fVerticalFOV > QFloat::_0);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fHalfVertFOV = QAngle::DegreesToRadians(fVerticalFOV*QFloat::_0_5, fHalfVertFOV);
    #else
        const float_q &fHalfVertFOV = fVerticalFOV * QFloat::_0_5;
    #endif

    QE_ASSERT(fHalfVertFOV != QAngle::_HalfPi);

    const float_q &fScaleY  = QFloat::_1 / tan(fHalfVertFOV);
    const float_q &fScaleX  = fScaleY / fAspectRatio;

    this->ResetToZero();

    this->ij[0][0] = fScaleX;
    this->ij[1][1] = fScaleY;
    this->ij[2][2] = fFarClipPlane/(fFarClipPlane - fNearClipPlane);
    this->ij[3][2] = -fNearClipPlane * this->ij[2][2];
    this->ij[2][3] = QFloat::_1;
}

void QSpaceConversionMatrix::SwitchHandConventionViewSpaceMatrix()
{
    QBaseVector3 vPOV;
    vPOV.x = -(this->ij[3][0]*this->ij[0][0] + this->ij[3][1]*this->ij[0][1] + this->ij[3][2]*this->ij[0][2]);
    vPOV.y = -(this->ij[3][0]*this->ij[1][0] + this->ij[3][1]*this->ij[1][1] + this->ij[3][2]*this->ij[1][2]);
    vPOV.z = -(this->ij[3][0]*this->ij[2][0] + this->ij[3][1]*this->ij[2][1] + this->ij[3][2]*this->ij[2][2]);

    QBaseVector3 vUp (this->ij[0][1], this->ij[1][1], this->ij[2][1]);

    QVector3 vAux;

    QVector3 vZAxis(-this->ij[0][2], -this->ij[1][2], -this->ij[2][2]);
        
    QVector3 vXAxis(vUp);
    vXAxis.CrossProduct(vZAxis);
        
    QVector3 vYAxis(vZAxis);
    vYAxis.CrossProduct(vXAxis);

    this->ij[0][0] = vXAxis.x;
    this->ij[0][1] = vYAxis.x;
    this->ij[0][2] = vZAxis.x;
    this->ij[0][3] = QFloat::_0;

    this->ij[1][0] = vXAxis.y;
    this->ij[1][1] = vYAxis.y;
    this->ij[1][2] = vZAxis.y;
    this->ij[1][3] = QFloat::_0;

    this->ij[2][0] = vXAxis.z;
    this->ij[2][1] = vYAxis.z;
    this->ij[2][2] = vZAxis.z;
    this->ij[2][3] = QFloat::_0;

    this->ij[3][0] = -vXAxis.DotProduct(vPOV);
    this->ij[3][1] = -vYAxis.DotProduct(vPOV);
    this->ij[3][2] = -vZAxis.DotProduct(vPOV);
    this->ij[3][3] = QFloat::_1;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
