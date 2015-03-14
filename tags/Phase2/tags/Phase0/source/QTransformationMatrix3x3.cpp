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

#include "QTransformationMatrix3x3.h"

#include "QBaseVector2.h"
#include "SQAngle.h"
#include "SQFloat.h"
#include "MathDefinitions.h"

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
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QTransformationMatrix3x3::QTransformationMatrix3x3()
{
    this->ResetToIdentity();
}

QTransformationMatrix3x3::QTransformationMatrix3x3(const QTransformationMatrix3x3 &transformation) : QMatrix3x3(transformation)
{
}

QTransformationMatrix3x3::QTransformationMatrix3x3(const QBaseMatrix3x3 &transformation) : QMatrix3x3(transformation)
{
}

QTransformationMatrix3x3::QTransformationMatrix3x3(const QBaseVector2 &vTranslation, const float_q &fRotationAngle, const QBaseVector2 &vScale)
{
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_q &ROT_RAD = SQAngle::DegreesToRadians(fRotationAngle);

        const float_q& fA   = cos_q(ROT_RAD);
        const float_q& fB   = sin_q(ROT_RAD);
    #else
        const float_q& fA   = cos_q(fRotationAngle);
        const float_q& fB   = sin_q(fRotationAngle);
    #endif

    this->ij[0][0] =  vScale.x * fA;
    this->ij[0][1] =  vScale.x * fB;
    this->ij[0][2] =  SQFloat::_0;

    this->ij[1][0] =  vScale.y * -fB;
    this->ij[1][1] =  vScale.y * fA;
    this->ij[1][2] =  SQFloat::_0;

    this->ij[2][0] =  vTranslation.x;
    this->ij[2][1] =  vTranslation.y;
    this->ij[2][2] =  SQFloat::_1;

}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QTransformationMatrix3x3& QTransformationMatrix3x3::operator=(const QBaseMatrix3x3 &matrix)
{
    QBaseMatrix3x3::operator=(matrix);
    return *this;
}

void QTransformationMatrix3x3::Decompose(QBaseVector2 &vOutDisp, float_q &fOutRot, QBaseVector2 &vOutScale) const
{
    vOutDisp.x = this->ij[2][0];
    vOutDisp.y = this->ij[2][1];

    vOutScale.x = hypot_q(this->ij[0][0], this->ij[0][1]);
    vOutScale.y = hypot_q(this->ij[1][0], this->ij[1][1]);

    // Checkout to avoid division by zero.
    QE_ASSERT(vOutScale.x != SQFloat::_0)

    float_q COS_ROT = this->ij[0][0] / vOutScale.x;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(COS_ROT > SQFloat::_1)
        COS_ROT = SQFloat::_1;
    else if(COS_ROT < -SQFloat::_1)
        COS_ROT = -SQFloat::_1;

    fOutRot = acos_q(COS_ROT);

    QE_ASSERT( !SQFloat::IsNaN(fOutRot) );

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles must be specified in degrees, then converts it.
        fOutRot = SQAngle::RadiansToDegrees(fOutRot);
    #endif
}

void QTransformationMatrix3x3::GetTranslation(QBaseVector2 &vTranslation) const
{
    vTranslation.x = this->ij[2][0];
    vTranslation.y = this->ij[2][1];
}
void QTransformationMatrix3x3::GetRotation(float_q &fRotationAngle) const
{
    const float_q &SCALE = hypot_q(this->ij[0][0], this->ij[0][1]);

    // Checkout to avoid division by zero.
    QE_ASSERT(SCALE != SQFloat::_0)

    float_q COS_ROT = this->ij[0][0] / SCALE;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(COS_ROT > SQFloat::_1)
        COS_ROT = SQFloat::_1;
    else if(COS_ROT < -SQFloat::_1)
        COS_ROT = -SQFloat::_1;

    fRotationAngle = acos_q(COS_ROT);

    QE_ASSERT( !SQFloat::IsNaN(fRotationAngle) );
      
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles must be specified in degrees, then converts it.
        fRotationAngle = SQAngle::RadiansToDegrees(fRotationAngle);
    #endif
}

void QTransformationMatrix3x3::GetScale(QBaseVector2 &vScale) const
{
    vScale.x = hypot_q(this->ij[0][0], this->ij[0][1]);
    vScale.y = hypot_q(this->ij[1][0], this->ij[1][1]);
}

QTransformationMatrix3x3 QTransformationMatrix3x3::SwitchHandConvention() const
{
    QTransformationMatrix3x3 switchedMatrix = *this;
    switchedMatrix.ij[0][1] = -this->ij[0][1];
    switchedMatrix.ij[1][0] = -this->ij[1][0];
    return switchedMatrix;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QTransformationMatrix3x3& QTransformationMatrix3x3::GetIdentity()
{
    static const QTransformationMatrix3x3 IDENTITY(QMatrix3x3::GetIdentity());
    return IDENTITY;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
