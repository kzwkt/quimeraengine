#ifndef __QTRANSFORMATIONMATRIX3X3__
#define __QTRANSFORMATIONMATRIX3X3__

#include "QBaseVector2.h"
#include "QMatrix3x3.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

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
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Stores an identity matrix.
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    /// 
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    static const QTransformationMatrix3x3 Identity;

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
    /// Constructor from a 3x3 matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix, 
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="m">[IN] The matrix in which we want the resident matrix to be based.</param>
    inline explicit QTransformationMatrix3x3(const QBaseMatrix3x3 &m) : QMatrix3x3(m) { }

    /// <summary>
    /// Constructor from a 2D vector which stores a scale, a floating point value which stores a rotation 
    /// and a 2D vector which stores a translation.
    /// </summary>
    /// <param name="vDisp">[IN] Vector with the displacement values.</param>
    /// <param name="fRot">[IN] Angle of rotation.</param>
    /// <param name="vScale">[IN] Vector with the scale values.</param>
    QTransformationMatrix3x3 (const QBaseVector2 &vDisp, const float_q &fRot, const QBaseVector2 &vScale);

    // METHODS
    // ---------------
public:

        /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QTransformationMatrix3x3& operator=(const QTransformationMatrix3x3 &m)
    {
        reinterpret_cast<QMatrix3x3&>(*this) = m;
        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QTransformationMatrix3x3& operator=(const QMatrix3x3 &m)
    {
        reinterpret_cast<QMatrix3x3&>(*this) = m;    
        return *this;
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <param name="vOutDisp">[OUT] A 2D vector to store the translation.</param>
    /// <param name="fOutRot">[OUT] Floating point variable to store the angle of rotation.</param>
    /// <param name="vOutScale">[OUT] A 2D vector to store the scale.</param>
    void Decompose (QBaseVector2 &vOutDisp, float_q &fOutRot, QBaseVector2 &vOutScale) const;
    
    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="&vOutDisp">[OUT] A 2D vector where to store the displacement.</param>
    inline void GetTranslation (QBaseVector2 &vOutDisp) const
    {
        vOutDisp.x = this->ij[2][0];
        vOutDisp.x = this->ij[2][1];
    }

    /// <summary>
    /// Extracts the rotation angle from the transformation matrix. 
    /// </summary>
    /// <param name="fOutRot">[OUT] Floating point variable to store the angle of rotation.</param>
    inline void GetRotation (float_q &fOutRot) const
    {
        const float_q &fScale = sqrt(this->ij[0][0]*this->ij[0][0] + this->ij[0][1]*this->ij[0][1]);

        // Checkout to avoid division by zero.
        QE_ASSERT(fScale != QFloat::_0);

        const float_q &fCosRot = this->ij[0][0]/fScale;

        // checkout to avoid improper values of cosine. Remember cosine must be in [-1,1] range.
        QE_ASSERT(abs(fCosRot) <= QFloat::_1);

        fOutRot = acos(fCosRot);

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles must be specified in degrees, then converts it.
            QAngle::RadiansToDegrees(fOutRot, fOutRot);
        #endif
    }

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="&vOutScale">[OUT] A 2D vector where to store the scale factors.</param>
    inline void GetScale (QBaseVector2 &vOutScale) const
    {
        vOutScale.x = sqrt(this->ij[0][0]*this->ij[0][0] + this->ij[0][1]*this->ij[0][1]);
        vOutScale.y = sqrt(this->ij[1][0]*this->ij[1][0] + this->ij[1][1]*this->ij[1][1]);
    }

    /// <summary>
    /// Turns the hand convention into opposite rules.
	/// Remember that Quimera Engine works with left-hand convention by default.
	/// To do that, we simply invert rotation (by trasposing its submatrix).
    /// </summary>
    inline void SwitchHandConvention ()
    {
        this->ij[0][1] = -this->ij[0][1];
        this->ij[1][0] = -this->ij[1][0];
    }

    /// <summary>
    /// Turns the hand convention into opposite rules.
	/// Remember that Quimera Engine works with left-hand convention by default.
	/// To do that, we simply invert rotation (by trasposing its submatrix).
    /// </summary>
    /// <param name="m">[OUT] Matrix to store the changed transformation matrix.</param>
    inline void SwitchHandConvention (QTransformationMatrix3x3 &m)
    {
        m = *this;
        m.SwitchHandConvention();
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
