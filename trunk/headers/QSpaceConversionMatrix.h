// [TERMS&CONDITIONS]

#ifndef __QSPACECONVERSIONMATRIX__
#define __QSPACECONVERSIONMATRIX__

#include "QBaseVector3.h"
#include "QBaseVector4.h"
#include "QBaseQuaternion.h"
#include "QMatrix4x4.h"
#include "QTransformationMatrix.h"

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
/// Class representing a matrix which symbolizes coordinate system transformations. It adds functionality 
/// to change to view, projection and world spaces. 
/// </summary>
class QDllExport QSpaceConversionMatrix : public QMatrix4x4
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It's initialized to identity matrix.
    /// </summary>
    inline QSpaceConversionMatrix()
    {
        this->ResetToIdentity();  
    }

    /// <summary>
    /// Constructor from a matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix, 
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="m">[IN] The matrix in which we want the resident matrix to be based.</param>
    inline explicit QSpaceConversionMatrix(const QBaseMatrix4x4 &m) : QMatrix4x4(m) { }

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f02">[IN] Floating point value for element of row 0, column 2.</param>
    /// <param name="f03">[IN] Floating point value for element of row 0, column 3.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
    /// <param name="f12">[IN] Floating point value for element of row 1, column 2.</param>
    /// <param name="f13">[IN] Floating point value for element of row 1, column 3.</param>
    /// <param name="f20">[IN] Floating point value for element of row 2, column 0.</param>
    /// <param name="f21">[IN] Floating point value for element of row 2, column 1.</param>
    /// <param name="f22">[IN] Floating point value for element of row 2, column 2.</param>
    /// <param name="f23">[IN] Floating point value for element of row 2, column 3.</param>
    /// <param name="f30">[IN] Floating point value for element of row 3, column 0.</param>
    /// <param name="f31">[IN] Floating point value for element of row 3, column 1.</param>
    /// <param name="f32">[IN] Floating point value for element of row 3, column 2.</param>
    /// <param name="f33">[IN] Floating point value for element of row 3, column 3.</param>
    inline QSpaceConversionMatrix(const float_q &f00, const float_q &f01, const float_q &f02, const float_q &f03, 
                                  const float_q &f10, const float_q &f11, const float_q &f12, const float_q &f13, 
                                  const float_q &f20, const float_q &f21, const float_q &f22, const float_q &f23, 
                                  const float_q &f30, const float_q &f31, const float_q &f32, const float_q &f33) : 

                        QMatrix4x4(f00, f01, f02, f03, f10, f11, f12, f13, f20, f21, f22, f23, f30, f31, f32, f33) { }

    /// <summary>
    /// Constructor that receives a pointer to 16 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 4 consecutive elements 
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="pfMatrix">[IN] Pointer to a 16 length array of floating point values.</param>
    inline explicit QSpaceConversionMatrix(const float_q *pfMatrix) : QMatrix4x4(pfMatrix) { }

    /// <summary>
    /// Constructor from four 4x32 floating point packed values. Each parameter contains a row of the matrix.
    /// </summary>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row3">[IN] 4x32 values for row 3, columns 0 to 3 unpacked in this order.</param>
    inline QSpaceConversionMatrix(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2, const vf32_q &row3) : 
        QMatrix4x4(row0, row1, row2, row3) { }


    // METHODS
    // ---------------
public:

    // Binary operators

    /// <summary>
    /// Multiplies a space conversion matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QSpaceConversionMatrix operator*(const QSpaceConversionMatrix &m) const;
    
    // Assign operators

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="m">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    QSpaceConversionMatrix& operator*=(const QSpaceConversionMatrix &m);

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QSpaceConversionMatrix& operator=(const QSpaceConversionMatrix &m)
    {
        reinterpret_cast<QMatrix4x4&>(*this) = m;
        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QSpaceConversionMatrix& operator=(const QMatrix4x4 &m)
    {
        reinterpret_cast<QMatrix4x4&>(*this) = m;    
        return *this;
    }

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="vDisp">[IN] Vector which contains the translation (position).</param>
    /// <param name="qRot">[IN] Quaternion which contains the rotation (orientation).</param>
    /// <param name="vScale">[IN] Vector which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QBaseVector3 &vDisp, const QBaseQuaternion &qRot, const QBaseVector3 &vScale);
    
    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="vDisp">[IN] Vector which contains the translation (position).</param>
    /// <param name="qRot">[IN] Quaternion which contains the rotation (orientation).</param>
    /// <param name="vScale">[IN] Vector which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QBaseVector4 &vDisp, const QBaseQuaternion &qRot, const QBaseVector3 &vScale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="mDisp">[IN] Matrix which contains the translation (position).</param>
    /// <param name="mRot">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="mScale">[IN] Matrix which contains the scale (size).</param>
    template <class MatrixType>
    void SetWorldSpaceMatrix(const QTranslationMatrix<MatrixType> &mDisp, const QRotationMatrix3x3 &mRot, const QScaleMatrix3x3 &mScale)
    {
        QTransformationMatrix4x4 aux(mDisp, mRot, mScale);

        *this = reinterpret_cast<QSpaceConversionMatrix&>(aux);
    }

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="mDisp">[IN] Matrix which contains the translation (position).</param>
    /// <param name="mRot">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="mScale">[IN] Matrix which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QTransformationMatrix4x4 &mDisp, const QTransformationMatrix4x4 &mRot, 
        const QTransformationMatrix4x4 &mScale);

    /// <summary>
    /// Sets the view space matrix, also called camera space matrix, defined by the point of view or camera position,
    /// the position of the object we are looking at and the direction we consider is "up direction".
    /// </summary>
    /// <param name="vPointOfView">[IN] Vector which defines the position of the camera or the point of view.</param>
    /// <param name="vTarget">[IN] Vector which defines the point where we are looking at.</param>
    /// <param name="vUpDirection">[IN] Vector which defines the "up direction".</param>
    void SetViewSpaceMatrix(const QBaseVector3 &vPointOfView, const QBaseVector3 &vTarget, const QBaseVector3 &vUpDirection);

    /// <summary>
    /// Sets the view space matrix, also called camera space matrix, defined by the point of view or camera position,
    /// the position of the object we are looking at and the direction we consider is "up direction".
    /// </summary>
    /// <param name="vPointOfView">[IN] Vector which defines the position of the camera or the point of view.</param>
    /// <param name="vTarget">[IN] Vector which defines the point where we are looking at.</param>
    /// <param name="vUpDirection">[IN] Vector which defines the "up direction".</param>
    inline void SetViewSpaceMatrix(const QBaseVector4 &vPointOfView, const QBaseVector4 &vTarget, const QBaseVector4 &vUpDirection)
    {
        SetViewSpaceMatrix(QBaseVector3(vPointOfView.x, vPointOfView.y, vPointOfView.z),
                           QBaseVector3(vTarget.x, vTarget.y, vTarget.z),
                           QBaseVector3(vUpDirection.x, vUpDirection.y, vUpDirection.z));
    }

    /// <summary>
    /// Sets the projection space matrix, which defines how perspective is applied to the scene.
    /// </summary>
    /// <param name="fNearClipPlane">[IN] Floating point value which defines the distance to the nearest clipping plane.</param>
    /// <param name="fFarClipPlane">[IN] Floating point value which defines the distance to the farthest clipping plane.</param>
    /// <param name="fAspectRatio">[IN] Floating point value which defines the frame width/height ratio.</param>
    /// <param name="fVerticalFOV">[IN] Floating point value which defines the vertical field of view.</param>
    void SetProjectionSpaceMatrix(const float_q &fNearClipPlane, const float_q &fFarClipPlane, 
        const float_q &fAspectRatio, const float_q &fVerticalFOV);

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// Remember that Quimera Engine works with left-hand convention by default.
    /// To do that, we treat the world space matrix as a transformation matrix,
    /// inverting both rotation (by trasposing it) and z translation component.
    /// </summary>
    inline void SwitchHandConventionWorldSpaceMatrix()
    {
        reinterpret_cast<QTransformationMatrix4x4 &>(*this).SwitchHandConvention();
    }

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// Remember that Quimera Engine works with left-hand convention by default.
    /// To do that, we treat the world space matrix as a transformation matrix,
    /// inverting both rotation (by trasposing it) and z translation component.
    /// </summary>
    /// <param name="m">[OUT] Matrix where to store the new world space matrix.</param>
    inline void SwitchHandConventionWorldSpaceMatrix(QSpaceConversionMatrix &m) const
    {
        m = *this;
        m.SwitchHandConventionWorldSpaceMatrix();
    }

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// Remember that Quimera Engine works with left-hand convention by default.
    /// To do that, we invert the Z axis, and then the matrix is recalculated.
    /// </summary>
    void SwitchHandConventionViewSpaceMatrix();

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// Remember that Quimera Engine works with left-hand convention by default.
    /// To do that, we invert the Z axis, and then matrix is recalculated.
    /// </summary>
    /// <param name="m">[OUT] Matrix where to store the new view space matrix.</param>
    inline void SwitchHandConventionViewSpaceMatrix(QSpaceConversionMatrix &m)
    {
        m = *this;
        m.SwitchHandConventionViewSpaceMatrix();
    }

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// Remember that Quimera Engine works with left-hand convention by default.
    /// To do that, we change the sign of elements \f$ a_{22}\f$ and \f$ a_{23}\f$.
    /// </summary>
    inline void SwitchHandConventionProjectionSpaceMatrix()
    {
        this->ij[2][2] = -this->ij[2][2];
        this->ij[2][3] = -this->ij[2][3];
    }
    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// Remember that Quimera Engine works with left-hand convention by default.
    /// To do that, we change the sign of elements \f$ a_{22}\f$ and \f$ a_{23}\f$.
    /// </summary>
    /// <param name="m">[OUT] Matrix where to store the new projection space matrix.</param>
    inline void SwitchHandConventionProjectionSpaceMatrix(QSpaceConversionMatrix &m)
    {
        m = *this;
        m.SwitchHandConventionProjectionSpaceMatrix();
    }

protected:
    
    // Hidden method to prevent it could be used.
    void ResetToZero();
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSPACECONVERSIONMATRIX__