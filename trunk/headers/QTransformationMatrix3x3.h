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

#ifndef __QTRANSFORMATIONMATRIX3X3__
#define __QTRANSFORMATIONMATRIX3X3__

#include "MathDefinitions.h"
#include "QBaseVector2.h"
#include "QMatrix3x3.h"
#include "QBaseMatrix3x3.h"
#include "SQAngle.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// It represents a 3x3 matrix containing spatial transformations relating to translation, rotation and scaling,
/// applying them to 2D space points.
/// </summary>
class QDllExport QTransformationMatrix3x3 : public QMatrix3x3
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It's initialized to identity matrix.
    /// </summary>
    inline QTransformationMatrix3x3()
    {
        this->ResetToIdentity();
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="transformation">[IN] The 3x3 transformation matrix from which we want to create a copy in the resident 3x3 transformation matrix.</param>
    inline QTransformationMatrix3x3(const QTransformationMatrix3x3 &transformation) : QMatrix3x3(transformation)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="transformation">[IN] The 3x3 matrix in which we want the resident 3x3 transformation matrix to be based.</param>
    inline QTransformationMatrix3x3(const QBaseMatrix3x3 &transformation) : QMatrix3x3(transformation)
    {
    }

    /// <summary>
    /// Constructor from a 2D vector which stores a scale, a floating point value which stores a rotation
    /// and a 2D vector which stores a translation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    /// <param name="fRotationAngle">[IN] Angle of rotation.</param>
    /// <param name="vScale">[IN] Vector with the scale values.</param>
    QTransformationMatrix3x3(const QBaseVector2 &vTranslation, const float_q &fRotationAngle, const QBaseVector2 &vScale);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets an identity matrix.<br/>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    inline static const QTransformationMatrix3x3& GetIdentity()
    {
        static const QTransformationMatrix3x3 IDENTITY(QMatrix3x3::GetIdentity());
        return IDENTITY;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QTransformationMatrix3x3& operator=(const QBaseMatrix3x3 &matrix)
    {
        QBaseMatrix3x3::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <param name="vTranslation">[OUT] A 2D vector to store the translation.</param>
    /// <param name="fRotationAngle">[OUT] Floating point variable to store the angle of rotation.</param>
    /// <param name="vScale">[OUT] A 2D vector to store the scale.</param>
    void Decompose(QBaseVector2 &vTranslation, float_q &fRotationAngle, QBaseVector2 &vScale) const;

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] A 2D vector where to store the displacement.</param>
    inline void GetTranslation(QBaseVector2 &vTranslation) const
    {
        vTranslation.x = this->ij[2][0];
        vTranslation.y = this->ij[2][1];
    }

    /// <summary>
    /// Extracts the rotation angle from the transformation matrix.
    /// </summary>
    /// <param name="fRotationAngle">[OUT] Floating point variable to store the angle of rotation.</param>
    inline void GetRotation(float_q &fRotationAngle) const
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

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="vScale">[OUT] A 2D vector where to store the scale factors.</param>
    inline void GetScale(QBaseVector2 &vScale) const
    {
        vScale.x = hypot_q(this->ij[0][0], this->ij[0][1]);
        vScale.y = hypot_q(this->ij[1][0], this->ij[1][1]);
    }

    /// <summary>
    /// Turns the hand convention into opposite rules.<br/>
	/// Remember that Quimera Engine works with left-hand convention by default.<br/>
	/// To do that, we simply invert rotation (by trasposing its submatrix).
    /// </summary>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    inline QTransformationMatrix3x3 SwitchHandConvention() const
    {
        QTransformationMatrix3x3 switchedMatrix = *this;
        switchedMatrix.ij[0][1] = -this->ij[0][1];
        switchedMatrix.ij[1][0] = -this->ij[1][0];
        return switchedMatrix;
    }

protected:

    // Hidden method to prevent it could be used.
    void ResetToZero();

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSFORMATIONMATRIX3x3__
