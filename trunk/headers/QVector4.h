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

#ifndef __QVECTOR4__
#define __QVECTOR4__

#include "QBaseVector4.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward declarations
class QBaseMatrix3x3;
class QBaseMatrix3x4;
class QBaseMatrix4x3;
class QBaseMatrix4x4;
class QMatrix4x3;
class QMatrix4x4;
template<class MatrixType> class QTranslationMatrix;
class QQuaternion;
class QDualQuaternion;
template<class MatrixType> class QTransformationMatrix;
class QSpaceConversionMatrix;
class QRotationMatrix3x3;
class QScalingMatrix3x3;
class QBaseVector3;


/// <summary>
/// A vector with four components: X, Y, Z and W.
/// </summary>
/// <remarks>
///    A vector is a geometric object that has both a magnitude (or length) and a direction.
/// The fourth component may equal 0, if the vector represents a normal in 3D space, or 1, if it represents a point.
/// This is important when applying transformations to the vector.
/// </remarks>
class QE_LAYER_TOOLS_SYMBOLS QVector4 : public QBaseVector4
{
    // FRIENDS
    // ---------------
public:

    /// <summary>
    /// Product of a scalar by a vector. All the components are multiplied by the scalar provided.
    /// </summary>
    /// <param name="fScalar">[IN] Scalar to multiply.</param>
    /// <param name="vVector">[IN] Vector to be multiplied by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    friend QVector4 QE_LAYER_TOOLS_SYMBOLS operator*(const float_q fScalar, const QVector4 &vVector);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    /// <remarks>
    ///    By default, all the components are set to zero.
    /// </remarks>
    QVector4();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="vVector">[IN] The vector whose components are to be copied.</param>
    QVector4(const QVector4 &vVector);

    /// <summary>
    /// Constructor that receives an instance of the base type.
    /// </summary>
    /// <param name="vVector">[IN] The vector whose components are to be copied.</param>
    QVector4(const QBaseVector4 &vVector);

    /// <summary>
    /// Constructor that receives 3D vector. The W component is set to zero.
    /// </summary>
    /// <param name="vVector">[IN] The vector whose components are to be copied.</param>
    explicit QVector4(const QBaseVector3 &vVector);

    /// <summary>
    /// Constructor that receives a vector and a scalar to fill the W component.
    /// </summary>
    /// <param name="vVector">[IN] The vector to copy its components.</param>
    /// <param name="fValue">[IN] Scalar value representing the W component.</param>
    explicit QVector4(const QBaseVector3 &vVector, const float &fValue);

    /// <summary>
    /// Constructor that receives the value of every vector's component.
    /// </summary>
    /// <param name="fValueX">[IN] The value for X component.</param>
    /// <param name="fValueY">[IN] The value for Y component.</param>
    /// <param name="fValueZ">[IN] The value for Z component.</param>
    /// <param name="fValueW">[IN] The value for W component.</param>
    QVector4(const float_q fValueX, const float_q fValueY, const float_q fValueZ, const float_q fValueW);

    /// <summary>
    /// Constructor from a single value for all the vector's components.
    /// </summary>
    /// <param name="fValueAll">[IN] The value for all components.</param>
    explicit QVector4(const float_q fValueAll);

    /// <summary>
    /// Constructor that receives an array of scalars.
    /// </summary>
    /// <remarks>
    /// The array must contain, at least, four elements. Only the first four elements will be considered; the rest will be ignored.
    /// </remarks>
    /// <param name="arValues">[IN] An array of scalars. It must contain, at least, four elements. If it is null, the behavior is undefined.</param>
    explicit QVector4(const float_q* arValues);

    /// <summary>
    /// Constructor that receives a pack of four scalars.
    /// </summary>
    /// <param name="value">[IN] 4x32 packed floating point value containing the three components.</param>
    explicit QVector4(const vf32_q value);

    /// <summary>
    /// Constructor that receives a 4x3 translation matrix from which to extract the translation vector.
    /// </summary>
    /// <remarks>
    /// It takes the vector components from elements \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ of the translation matrix.<br/>
    /// The W component is set to one.
    /// </remarks>
    /// <param name="translation">[IN] The translation matrix from which to obtain the translation vector.</param>
    explicit QVector4(const QTranslationMatrix<QMatrix4x3> &translation);

    /// <summary>
    /// Constructor that receives a 4x3 translation matrix from which to extract the translation vector.
    /// </summary>
    /// <remarks>
    /// It takes the vector components from elements \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ of the translation matrix.<br/>
    /// The W component is set to one.
    /// </remarks>
    /// <param name="translation">[IN] The translation matrix from which to obtain the translation vector.</param>
    explicit QVector4(const QTranslationMatrix<QMatrix4x4> &translation);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a vector whose X, Y and Z components equal zero and W component equals one.
    /// </summary>
    /// <returns>
    /// A point placed in the origin of coordinates.
    /// </returns>
    static const QVector4& GetZeroPoint();

    /// <summary>
    /// Gets a vector whose components equal zero.
    /// </summary>
    /// <returns>
    /// A null vector.
    /// </returns>
    static const QVector4& GetNullVector();

    /// <summary>
    /// Gets a vector whose components equal one.
    /// </summary>
    /// <returns>
    /// A vector of ones.
    /// </returns>
    static const QVector4& GetVectorOfOnes();

    /// <summary>
    /// Gets a unit vector that points to the positive direction of the X axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the positive direction of the X axis.
    /// </returns>
    static const QVector4& GetUnitVectorX();

    /// <summary>
    /// Gets a unit vector that points to the positive direction of the Y axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the positive direction of the Y axis.
    /// </returns>
    static const QVector4& GetUnitVectorY();

    /// <summary>
    /// Gets a unit vector that points to the positive direction of the Z axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the positive direction of the Z axis.
    /// </returns>
    static const QVector4& GetUnitVectorZ();

    /// <summary>
    /// Gets a unit vector that points to the negative direction of the X axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the negative direction of the X axis.
    /// </returns>
    static const QVector4& GetUnitVectorInvX();

    /// <summary>
    /// Gets a unit vector that points to the negative direction of the Y axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the negative direction of the Y axis.
    /// </returns>
    static const QVector4& GetUnitVectorInvY();

    /// <summary>
    /// Gets a unit vector that points to the negative direction of the Z axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the negative direction of the Z axis.
    /// </returns>
    static const QVector4& GetUnitVectorInvZ();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Adds two vectors by adding each component.
    /// </summary>
    /// <param name="vVector">[IN] Vector to be added.</param>
    /// <returns>
    /// A vector that is the result of the addition.
    /// </returns>
    QVector4 operator+(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Adds two vectors by adding each component. The W component does not change.
    /// </summary>
    /// <param name="vVector">[IN] Vector to be added.</param>
    /// <returns>
    /// A vector that is the result of the addition.
    /// </returns>
    QVector4 operator+(const QBaseVector3 &vVector) const;

    /// <summary>
    /// Substracts two vectors by substracting each component.
    /// </summary>
    /// <param name="vVector">[IN] Vector to be substracted.</param>
    /// <returns>
    /// A vector that is the result of the subtraction.
    /// </returns>
    QVector4 operator-(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Substracts two vectors by substracting each component. The W component does not change.
    /// </summary>
    /// <param name="vVector">[IN] Vector to be substracted.</param>
    /// <returns>
    /// A vector that is the result of the subtraction.
    /// </returns>
    QVector4 operator-(const QBaseVector3 &vVector) const;

    /// <summary>
    /// Multiplies the vector by a scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector4 operator*(const float_q fScalar) const;

    /// <summary>
    /// Multiplies two vectors by multiplying each component.
    /// </summary>
    /// <param name="vVector">[IN] Vector to multiply by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector4 operator*(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Multiplies the vector by a 4x4 matrix.
    /// </summary>
    /// <remarks>
    /// The vector is treated as if it was a one-dimensional matrix with one row.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to multiply by.</param>
    /// <returns>
    /// A 4D vector that is the result of the product.
    /// </returns>
    QVector4 operator*(const QBaseMatrix4x4 &matrix) const;

    /// <summary>
    /// Multiplies the vector by a 4x3 matrix.
    /// </summary>
    /// <remarks>
    /// The vector is treated as if it was a one-dimensional matrix with one row.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to multiply by.</param>
    /// <returns>
    /// A 3D vector that is the result of the product.
    /// </returns>
    QBaseVector3 operator*(const QBaseMatrix4x3 &matrix) const;

    /// <summary>
    /// Divides the vector by a scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by. If it equals zero, the result is undefined.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    QVector4 operator/(const float_q fScalar) const;

    /// <summary>
    /// Divides two vectors by dividing each component.
    /// </summary>
    /// <param name="vVector">[IN] The vector to divide by. If any of its components equal zero, the result is undefined.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    QVector4 operator/(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Adds a vector to the resident vector. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be added.</param>
    /// <returns>
    /// A reference to the resident vector, result of the addition.
    /// </returns>
    QVector4& operator+=(const QBaseVector4 &vVector);

    /// <summary>
    /// Adds a vector to the resident vector, without changing the W component. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be added.</param>
    /// <returns>
    /// A reference to the resident vector, result of the addition.
    /// </returns>
    QVector4& operator+=(const QBaseVector3 &vVector);

    /// <summary>
    /// Subtracts a vector to the resident vector. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be substracted.</param>
    /// <returns>
    /// A reference to the resident vector, result of the subtraction.
    /// </returns>
    QVector4& operator-=(const QBaseVector4 &vVector);

    /// <summary>
    /// Subtracts a vector to the resident vector, without changing the W component. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be substracted.</param>
    /// <returns>
    /// A reference to the resident vector, result of the subtraction.
    /// </returns>
    QVector4& operator-=(const QBaseVector3 &vVector);

    /// <summary>
    /// Multiplies the resident vector by a scalar. The resident vector is set to the result.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// A reference to the resident vector, result of the product.
    /// </returns>
    QVector4& operator*=(const float_q fScalar);

    /// <summary>
    /// Multiplies two vectors by multiplying each component. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to multiply by.</param>
    /// <returns>
    /// A reference to the resident vector, result of the product.
    /// </returns>
    QVector4& operator*=(const QBaseVector4 &vVector);

    /// <summary>
    /// Multiplies the resident vector by a 4x4 matrix. The resident vector is set to the result.
    /// </summary>
    /// <remarks>
    /// The vector is treated as if it was a one-dimensional matrix with one row.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to multiply by.</param>
    /// <returns>
    /// A reference to the resident vector, result of the product.
    /// </returns>
    QVector4& operator*=(const QBaseMatrix4x4 &matrix);

    /// <summary>
    /// Divides the vector by a scalar. The resident vector is set to the result.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by. If it equals zero, the result is undefined.</param>
    /// <returns>
    /// A reference to the resident vector, result of the division.
    /// </returns>
    QVector4& operator/=(const float_q fScalar);

    /// <summary>
    /// Divides two vectors by dividing each component. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to divide by. If any of its components equal zero, the result is undefined.</param>
    /// <returns>
    /// A reference to the resident vector, result of the division.
    /// </returns>
    QVector4& operator/=(const QBaseVector4 &vVector);

    /// <summary>
    /// Assigns the provided vector to the resident vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be assigned.</param>
    /// <returns>
    /// A reference to the resident vector.
    /// </returns>
    QVector4& operator=(const QBaseVector4 &vVector);

    /// <summary>
    /// Negates the vector by negating each component.
    /// </summary>
    /// <returns>
    /// A vector that is the result of the negation.
    /// </returns>
    QVector4 operator-() const;

    /// <summary>
    /// Calculates the length (magnitude) of the vector.
    /// </summary>
    /// <returns>
    /// A scalar whose value equals the length of the vector.
    /// </returns>
    float_q GetLength() const;

    /// <summary>
    /// Calculates the squared length of the vector.
    /// </summary>
    /// <remarks>
    /// The squared length is calculated faster than the length and is commonly used to compare two vectors.
    /// </remarks>
    /// <returns>
    /// A scalar whose value equals the squared length of the vector.
    /// </returns>
    float_q GetSquaredLength() const;

    /// <summary>
    /// Normalizes the vector. The vector keeps its direction but its length equals one.
    /// </summary>
    /// <remarks>
    /// If the vector is null, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The normalized vector.
    /// </returns>
    QVector4 Normalize() const;

    /// <summary>
    /// Sets all the components of the vector to one.
    /// </summary>
    void ResetToOne();

    /// <summary>
    /// Sets all the components of the vector to zero but W, which is set to one.
    /// </summary>
    void ResetToZeroPoint();

    /// <summary>
    /// Sets all the components of the vector to zero.
    /// </summary>
    void ResetToZeroVector();

    /// <summary>
    /// Checks if all components equal zero.
    /// </summary>
    /// <returns>
    /// True if all components equal zero; False otherwise.
    /// </returns>
    bool IsZero() const;

    /// <summary>
    /// Checks if all components equal one.
    /// </summary>
    /// <returns>
    /// True if all components equal one; False otherwise.
    /// </returns>
    bool IsVectorOfOnes() const;

    /// <summary>
    /// Calculates the dot product of two vectors.
    /// </summary>
    /// <remarks>
    /// Remember that the dot product is commutative.<br/>
    /// Both vectors are considered as 3D vectors so the W component is ignored.
    /// </remarks>
    /// <param name="vVector">[IN] The second operand of the product.</param>
    /// <returns>
    /// A scalar whose value equals the result of dot product.
    /// </returns>
    float_q DotProduct(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Calculates the smaller angle between two vectors.
    /// </summary>
    /// <remarks>
    /// The angle will be always lower than or equal to \f$\pi\f$ radians (\f$ 180^0\f$). The order of the operands doesn't affect the result.
    /// </remarks>
    /// <param name="vVector">[IN] The second operand.</param>
    /// <returns>
    /// A scalar whose value equals the angle between the vectors.
    /// </returns>
    float_q AngleBetween(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Calculates the cross product between two vectors.
    /// </summary>
    /// <remarks>
    /// It follows the left-handed rules.<br/>
    /// Remember that this operation is NOT commutative.<br/>
    /// Due to cross product between two 4D vectors is not defined (it is a ternary operation in 4D space),
    /// it is treated as a cross product between two 3D vectors, copying the W component of the resident vector.
    /// </remarks>
    /// <param name="vVector">[IN] The second operand.</param>
    /// <returns>
    /// The resultant vector.
    /// </returns>
    QVector4 CrossProduct(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Calculates the linear interpolation between two vectors.
    /// </summary>
    /// <param name="fProportion">[IN] A value that represents how close is the resultant vector to the provided 
    /// vector. A value of 0 will produce a vector that equals the resident vector; a value of 1 will produce a vector that
    /// equals the input vector. Note tha values lower than 0 and higher than 1 are also valid.</param>
    /// <param name="vVector">[IN] Vector with which to interpolate.</param>
    /// <returns>
    /// A vector that is the result of the interpolation.
    /// </returns>
    QVector4 Lerp(const float_q fProportion, const QBaseVector4 &vVector) const;

    /// <summary>
    /// Calculates the distance between two vectors (two points).
    /// </summary>
    /// <remarks>
    /// The W component is ignored.
    /// </remarks>
    /// <param name="vVector">[IN] Vector to calculate the distance to.</param>
    /// <returns>
    /// A positive value that equals the distance between both vectors.
    /// </returns>
    float_q Distance(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Homogenizes the vector by dividing all its componentes by the W component so it is in homogeneus coordinates.
    /// </summary>
    /// <remarks>
    /// The W component is supposed to not equal zero. If it was the case, the returned vector will be the same as the original one.
    /// </remarks>
    /// <returns>
    /// The homogenized vector.
    /// </returns>
    QVector4 Homogenize() const;

    /// <summary>
    /// Applies a rotation to the vector, using a quaternion.
    /// </summary>
    /// <remarks>
    /// It's done by multiplying resident vector by the provided quaternion, as follows:<br/>
    /// <br/>
    /// \f$ v' = Q \cdot v \cdot Q^*\f$,<br/>
    /// <br/>
    /// where v is the resident vector, Q the quaternion and \f$ Q^*\f$ the conjugate of the quaternion.<br/>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="qRotation">[IN] The rotation transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QQuaternion &qRotation) const;

    /// <summary>
    /// Applies a rigid transformation to the vector, using a dual quaternion.
    /// </summary>
    /// <remarks>
    /// It's done by multiplying resident vector by the provided dual quaternion, as follows:<br/>
    /// <br/>
    /// \f$ v' = \hat{Q} \cdot v \cdot \hat{Q}^*\f$,<br/>
    /// <br/>
    /// where v is the resident vector, \f$\hat{Q}\f$ the dual quaternion and \f$\hat{Q}^*\f$ the double conjugate of the dual quaternion.<br/>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="transformation">[IN] The transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QDualQuaternion &transformation) const;

    /// <summary>
    /// Applies a rotation to the resident vector by multiplying the vector by a rotation matrix.
    /// </summary>
    /// <remarks>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="rotation">[IN] The rotation transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QRotationMatrix3x3 &rotation) const;

    /// <summary>
    /// Applies a scale to the resident vector by multiplying the vector by a scaling matrix.
    /// </summary>
    /// <remarks>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="scale">[IN] The scaling transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QScalingMatrix3x3 &scale) const;
    
    /// <summary>
    /// Applies a translation to the resident vector by multiplying the vector by a translation matrix.
    /// </summary>
    /// <remarks>
    /// The result depends on whether the W component equals zero (it is a normal) or one (it is a point). Since normals cannot be
    /// displaced, the result of translating the normal will be the same as the original vector.<br/>
    /// Note that this operation has better performance than multiplying by a common matrix since only relevant elements
    /// participate in the calculation.<br/>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="translation">[IN] The translation transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QTranslationMatrix<QMatrix4x3> &translation) const;

    /// <summary>
    /// Applies a translation to the resident vector by multiplying the vector by a translation matrix.
    /// </summary>
    /// <remarks>
    /// The result depends on whether the W component equals zero (it is a normal) or one (it is a point). Since normals cannot be
    /// displaced, the result of translating the normal will be the same as the original vector.<br/>
    /// Note that this operation has better performance than multiplying by a common matrix since only relevant elements
    /// participate in the calculation.<br/>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="translation">[IN] The translation transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QTranslationMatrix<QMatrix4x4> &translation) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation,a translation or a combination of them 
    /// to the resident vector by multiplying it by a transformation matrix.
    /// </summary>
    /// <remarks>
    /// The result depends on whether the W component equals zero (it is a normal) or one (it is a point). Since normals cannot be
    /// displaced, the result of translating the normal will be the same as the original vector.<br/>
    /// Note that this operation has better performance than multiplying by a common matrix since only relevant elements
    /// participate in the calculation.<br/>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="transformation">[IN] The transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation,a translation or a combination of them 
    /// to the resident vector by multiplying it by a transformation matrix.
    /// </summary>
    /// <remarks>
    /// The result depends on whether the W component equals zero (it is a normal) or one (it is a point). Since normals cannot be
    /// displaced, the result of translating the normal will be the same as the original vector.<br/>
    /// Note that this operation has better performance than multiplying by a common matrix since only relevant elements
    /// participate in the calculation.<br/>
    /// The W component is copied as is.
    /// </remarks>
    /// <param name="transformation">[IN] The transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const;

    /// <summary>
    /// Applies a transformation to the resident vector by multiplying the vector by a space conversion matrix. This produces
    /// that the vector is converted to a different vector space (view space, world space, projection space...).
    /// </summary>
    /// <remarks>
    /// The result depends on whether the W component equals zero (it is a normal) or one (it is a point). Since normals cannot be
    /// displaced, the result of translating the normal will be the same as the original vector.<br/>
    /// Note that this operation has better performance than multiplying by a common matrix since only relevant elements
    /// participate in the calculation.<br/>
    /// The W component is copied as is.
    /// <param name="spaceConversion">[IN] The space transformation.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    QVector4 Transform(const QSpaceConversionMatrix &spaceConversion) const;

    /// <summary>
    /// Converts vector into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "V4($x,$y,$z,$w)".<br/>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>
    /// The string with the format specified.
    /// </returns>
    string_q ToString() const;

private:

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
    /// to resident vector, multiplying the vector by a transformation matrix
    /// to transform it. The translation takes effect depending on if resident vector represents a 3D point
    /// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
    /// since a 3D vector cannot be displaced.
    /// </summary>
    /// <typeparam name="MatrixType">Allowed types: QMatrix4x3, QMatrix4x4.</typeparam>
    /// <param name="transformation">[IN] The transformation matrix. It must be a 4x3 or a 4x4 matrix.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    template <class MatrixType>
    QVector4 TransformImp(const QTranslationMatrix<MatrixType> &translation) const;

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
    /// to transform it. The translation takes effect depending on if resident vector represents a 3D point
    /// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
    /// since a 3D vector cannot be displaced.
    /// </summary>
    /// <typeparam name="MatrixType">Allowed types: QMatrix4x3, QMatrix4x4.</typeparam>
    /// <param name="translation">[IN] The translation matrix. It must be a 4x3 or a 4x4 translation matrix.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    template <class MatrixType>
    QVector4 TransformImp(const QTransformationMatrix<MatrixType> &transformation) const;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVECTOR4__
