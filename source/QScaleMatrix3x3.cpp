// [TERMS&CONDITIONS]

#include "QScaleMatrix3x3.h"

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
//##################		    |  CONSTANTS INITIALIZATION  |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QScaleMatrix3x3 QScaleMatrix3x3::Identity(  QFloat::_1, QFloat::_0, QFloat::_0,
                                                  QFloat::_0, QFloat::_1, QFloat::_0,
                                                  QFloat::_0, QFloat::_0, QFloat::_1);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QScaleMatrix3x3 QScaleMatrix3x3::operator*(const QScaleMatrix3x3 &m) const
{
    QScaleMatrix3x3 aux;

    aux.ResetToIdentity();

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0];
    aux.ij[1][1] = this->ij[1][1]*m.ij[1][1];
    aux.ij[2][2] = this->ij[2][2]*m.ij[2][2];

    return aux;
}

QTransformationMatrix4x4 QScaleMatrix3x3::operator*(const QRotationMatrix3x3 &m) const
{
    QTransformationMatrix4x4 aux;

    aux.ResetToIdentity();

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2];

    aux.ij[1][0] = this->ij[1][1]*m.ij[1][0];
    aux.ij[1][1] = this->ij[1][1]*m.ij[1][1];
    aux.ij[1][2] = this->ij[1][1]*m.ij[1][2];

    aux.ij[2][0] = this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][2]*m.ij[2][2];

    return aux;
}

QTransformationMatrix4x4 QScaleMatrix3x3::operator*(const QTranslationMatrix4x4 &m) const
{
    QTransformationMatrix4x4 aux(QTransformationMatrix4x4::Identity);

    aux.ResetToIdentity();

    aux.ij[0][0] = this->ij[0][0];
    aux.ij[1][1] = this->ij[1][1];
    aux.ij[2][2] = this->ij[2][2];

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    return aux;
}

QTransformationMatrix4x3 QScaleMatrix3x3::operator*(const QTranslationMatrix4x3 &m) const
{
    QTransformationMatrix4x3 aux(QTransformationMatrix4x3::Identity);

    aux.ij[0][0] = this->ij[0][0];
    aux.ij[1][1] = this->ij[1][1];
    aux.ij[2][2] = this->ij[2][2];

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    return aux;
}

QTransformationMatrix4x4 QScaleMatrix3x3::operator*(const QTransformationMatrix4x4 &m) const
{
    QTransformationMatrix4x4 aux(QTransformationMatrix4x4::Identity);

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2];

    aux.ij[1][0] = this->ij[1][1]*m.ij[1][0];
    aux.ij[1][1] = this->ij[1][1]*m.ij[1][1];
    aux.ij[1][2] = this->ij[1][1]*m.ij[1][2];

    aux.ij[2][0] = this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][2]*m.ij[2][2];

    return aux;
}

QTransformationMatrix4x3 QScaleMatrix3x3::operator*(const QTransformationMatrix4x3 &m) const
{
    QTransformationMatrix4x3 aux(QTransformationMatrix4x3::Identity);

    aux.ij[3][0] = m.ij[3][0];
    aux.ij[3][1] = m.ij[3][1];
    aux.ij[3][2] = m.ij[3][2];

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2];

    aux.ij[1][0] = this->ij[1][1]*m.ij[1][0];
    aux.ij[1][1] = this->ij[1][1]*m.ij[1][1];
    aux.ij[1][2] = this->ij[1][1]*m.ij[1][2];

    aux.ij[2][0] = this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][2]*m.ij[2][2];

    return aux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
