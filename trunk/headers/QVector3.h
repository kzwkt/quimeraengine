// [TERMS&CONDITIONS]

#ifndef __QVECTOR3__
#define __QVECTOR3__

#include "SQAngle.h"
#include "QBaseVector3.h"
#include "QBaseVector4.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

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
class QScaleMatrix3x3;

/// <summary>
/// This class implements three components vector functionality. It inherits from QBaseVector3.
/// A vector is a geometric object that has both a magnitude (or length) and direction.
/// It is frequently represented by a line segment with a definite direction, or graphically as an arrow,
/// connecting an initial point A with a terminal point B. The vector is then denoted by AB with an arrow hat.
/// </summary>
class QDllExport QVector3 : public QBaseVector3
{
    // FRIENDS
    // ---------------
public:

    /// <summary>
    /// Product by a scalar: all components are multiplied by the floating point value provided.
    /// Shortcut to multiply on the left.
    /// </summary>
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <param name="v">[IN] Vector to be multiplied.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    friend QVector3 operator * (const float_q &fValue, const QBaseVector3 &v);

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Stores a vector with all components set to 0
    /// </summary>
    static const QVector3 ZeroVector;
    /// <summary>
    /// Stores a vector with all components set to 1
    /// </summary>
    static const QVector3 VectorOfOnes;
    /// <summary>
    /// Stores a unit vector in X positive direction
    /// </summary>
    static const QVector3 UnitVectorX;
    /// <summary>
    /// Stores a unit vector in Y positive direction
    /// </summary>
    static const QVector3 UnitVectorY;
    /// <summary>
    /// Stores a unit vector in Z positive direction
    /// </summary>
    static const QVector3 UnitVectorZ;
    /// <summary>
    /// Stores a unit vector in X negative direction
    /// </summary>
    static const QVector3 UnitVectorInvX;
    /// <summary>
    /// Stores a unit vector in Y negative direction
    /// </summary>
    static const QVector3 UnitVectorInvY;
    /// <summary>
    /// Stores a unit vector in Z negative direction
    /// </summary>
    static const QVector3 UnitVectorInvZ;

	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QVector3() { }

    /// <summary>
    /// Constructor from a 3D vector.
    /// </summary>
    /// <param name="v">[IN] The 3D vector in which we want resident vector to be based.</param>
    inline explicit QVector3(const QBaseVector3 &v) : QBaseVector3(v) { }

    /// <summary>
    /// Constructor from a 4D vector.
    /// </summary>
    /// <param name="v">[IN] The 4D vector in which we want resident vector to be based.</param>
    inline explicit QVector3(const QBaseVector4 &v) : QBaseVector3(v.x, v.y, v.z) { }

    /// <summary>
    /// Constructor from three floating point values for each component x, y and z.
    /// </summary>
    /// <param name="fValueX">[IN] Floating point value for x component.</param>
    /// <param name="fValueY">[IN] Floating point value for y component.</param>
    /// <param name="fValueZ">[IN] Floating point value for z component.</param>
    inline QVector3(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ) : QBaseVector3(fValueX, fValueY, fValueZ) { }

    /// <summary>
    /// Constructor from a single floating point value for all components.
    /// </summary>
    /// <param name="fValue">[IN] Floating point value for all components.</param>
    inline explicit QVector3(const float_q &fValue) : QBaseVector3(fValue) { }

    /// <summary>
    /// Constructor from a three component array of floating point values.
    /// </summary>
    /// <param name="pValue">[IN] Pointer to array of floating point values. It must have at least three elements.</param>
    inline explicit QVector3(const float_q *pValue) : QBaseVector3(pValue) { }

    /// <summary>
    /// Constructor from a 4x32 packed floating point value.
    /// </summary>
    /// <param name="vfValue">[IN] 4x32 packed floating point value containing the three components.</param>
    inline explicit QVector3(const vf32_q vfValue) : QBaseVector3 (vfValue) { }

    /// <summary>
    /// Constructor from a 4x4 or a 4x3 translation matrix. Takes translation components
	/// from elements \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ of the translation matrix.
    /// </summary>
    /// <param name="m">[IN] The translation matrix in which we want resident vector to be based.
	/// It must be a 4x4 or 4x3 matrix.</param>
	QVector3(const QTranslationMatrix<QMatrix4x3> &m);

    /// <summary>
    /// Constructor from a 4x4 or a 4x3 translation matrix. Takes translation components
	/// from elements \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ of the translation matrix.
    /// </summary>
    /// <param name="m">[IN] The translation matrix in which we want resident vector to be based.
	/// It must be a 4x4 or 4x3 matrix.</param>
	QVector3(const QTranslationMatrix<QMatrix4x4> &m);

    // METHODS
    // ---------------
public:

    // binary operators

    /// <summary>
    /// Vectors addition: it's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Adding vector.</param>
    /// <returns>
    /// A vector that is the result of the addition.
    /// </returns>
    QVector3 operator + (const QBaseVector3 &v) const;

    /// <summary>
    /// Vectors subtraction: it's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Subtracting vector.</param>
    /// <returns>
    /// A vector that is the result of the subtraction.
    /// </returns>
    QVector3 operator - (const QBaseVector3 &v) const;

    /// <summary>
    /// Product by a scalar: all components are multiplied by the floating point value provided.
    /// </summary>
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector3 operator * (const float_q &fValue) const;

    /// <summary>
    /// Product by a vector: it's performed component by component. It's not dot product or cross product!
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector3 operator * (const QBaseVector3 &v) const;

    /// <summary>
    /// Product by a matrix with 3 rows and 3 columns: it's performed following the matrices product rules.
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QVector3 operator * (const QBaseMatrix3x3 &m) const;

    /// <summary>
    /// Product by a matrix with 3 rows and 4 columns: it's performed following the matrices product rules.
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A 4D vector that is the result of the product.
    /// </returns>
    QBaseVector4 operator * (const QBaseMatrix3x4 &m) const;

    /// <summary>
    /// Division by a scalar: all components are divided by the floating point value provided.
    /// </summary>
    /// <param name="fValue">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    QVector3 operator / (const float_q &fValue) const;

    /// <summary>
    /// Division by a vector: it's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Dividing vector.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    QVector3 operator / (const QBaseVector3 &v) const;

    // assignment operators

    /// <summary>
    /// Adds a vector provided to resident vector.
    /// </summary>
    /// <param name="v">[IN] Adding vector.</param>
    /// <returns>
    /// A reference to vector result of the addition.
    /// </returns>
    inline QVector3& operator += (const QBaseVector3 &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;

        return *this;
    }

    /// <summary>
    /// Subtracts a vector provided to resident vector.
    /// </summary>
    /// <param name="v">[IN] Subtracting vector.</param>
    /// <returns>
    /// A reference to vector result of the subtraction.
    /// </returns>
    inline QVector3& operator -= (const QBaseVector3 &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;

        return *this;
    }

    /// <summary>
    /// Multiplies resident vector by a floating point value provided.
    /// </summary>
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    inline QVector3& operator *= (const float_q &fValue)
    {
        this->x *= fValue;
        this->y *= fValue;
        this->z *= fValue;

        return *this;
    }

    /// <summary>
    /// Multiplies resident vector by a vector provided. It's performed component by component. It's not dot product or cross product!
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    inline QVector3& operator *= (const QBaseVector3 &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;

        return *this;
    }

    /// <summary>
    /// Multiplies resident vector by a matrix with 3 rows and 3 columns provided. It's performed with matrix product rules.
    /// </summary>
    /// <param name="m">[IN] Multiplying matrix.</param>
    /// <returns>
    /// A reference to vector result of the product.
    /// </returns>
    QVector3& operator *= (const QBaseMatrix3x3 &m);

    /// <summary>
    /// Divides resident vector by a floating point value provided.
    /// </summary>
    /// <param name="fValue">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A reference to vector result of the division.
    /// </returns>
    inline QVector3& operator /= (const float_q &fValue)
    {
        // Checkout to avoid division by 0
        QE_ASSERT(fValue != SQFloat::_0);

        this->x /= fValue;
        this->y /= fValue;
        this->z /= fValue;

        return *this;
    }

    /// <summary>
    /// Divides resident vector by a vector provided. It's performed component by component.
    /// </summary>
    /// <param name="v">[IN] Dividing vector.</param>
    /// <returns>
    /// A reference to vector result of the division.
    /// </returns>
    inline QVector3& operator /= (const QBaseVector3 &v)
    {
        // Checkout to avoid division by 0
        QE_ASSERT (v.x != SQFloat::_0 && v.y != SQFloat::_0 && v.z != SQFloat::_0);

        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;

        return *this;
    }

    //Unary operators

    /// <summary>
    /// Assign operator. Assigns the provided vector to the resident vector.
    /// </summary>
    /// <param name="v">[IN] The vector to be assigned.</param>
    /// <returns>
    /// A reference to the modified vector.
    /// </returns>
    inline QVector3& operator=(const QBaseVector3 &v)
    {
        QBaseVector3::operator=(v);
        return *this;
    }

    /// <summary>
    /// Opposite vector: multiplies each component by -1.
    /// </summary>
    /// <returns>
    /// A vector that is the opposite of the resident vector.
    /// </returns>
    QVector3 operator- () const;

    //Methods

    /// <summary>
    /// Calculates the length of resident vector.
    /// </summary>
    /// <returns>
    /// A floating point value which is the length of the vector.
    /// </returns>
    inline float_q GetLength() const
    {
        return sqrt_q(this->x*this->x + this->y*this->y + this->z*this->z);
    }

    /// <summary>
    /// Calculates the squared length of resident vector.
    /// </summary>
    /// <returns>
    /// A floating point value which is the squared length of the vector.
    /// </returns>
    inline float_q GetSquaredLength() const
    {
        return this->x*this->x + this->y*this->y + this->z*this->z;
    }

    /// <summary>
    /// Makes resident vector unitary.
    /// </summary>
    inline void Normalize()
    {
        // Gets vector length
        float_q fLength = this->GetLength();

        // Checkout to avoid division by 0
        QE_ASSERT(fLength != SQFloat::_0);

        //Normalize
        this->x /= fLength;
        this->y /= fLength;
        this->z /= fLength;
    }

    /// <summary>
    /// Calculates a normalized vector from the resident one and stores it in an output vector provided.
    /// </summary>
    /// <param name="vOut">[OUT] Vector where we want store the normalized vector.</param>
    inline void Normalize(QBaseVector3 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector3&> (vOut).Normalize();
    }

    /// <summary>
    /// Convert resident vector in its opposite vector.
    /// </summary>
    inline void Reverse()
    {
        this->x = -this->x;
        this->y = -this->y;
        this->z = -this->z;
    }

    /// <summary>
    /// Calculates the opposite to resident vector and stores it in an output vector provided.
    /// </summary>
    /// <param name="vOut">[OUT] Vector where we want store the opposite vector.</param>
    inline void Reverse(QBaseVector3 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector3&> (vOut).Reverse();
    }

    /// <summary>
    /// Resets all components of resident vector to 1.
    /// </summary>
    inline void ResetToOne()
    {
        this->x = SQFloat::_1;
        this->y = SQFloat::_1;
        this->z = SQFloat::_1;
    }

    /// <summary>
    /// Resets all components of resident vector to 0.
    /// </summary>
    inline void ResetToZero()
    {
        this->x = SQFloat::_0;
        this->y = SQFloat::_0;
        this->z = SQFloat::_0;
    }

    /// <summary>
    /// Check if all components of resident vector are 0.
    /// </summary>
    /// <returns>
    /// True if all components are 0. False otherwise.
    /// </returns>
    inline bool IsZero() const
    {
        return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y) && SQFloat::IsZero(this->z);
    }

    /// <summary>
    /// Check if all components of resident vector are 1.
    /// </summary>
    /// <returns>
    /// True if all components are 1. False otherwise.
    /// </returns>
    inline bool IsVectorOfOnes() const
    {
        return SQFloat::AreEquals(this->x, SQFloat::_1) && SQFloat::AreEquals(this->y, SQFloat::_1) && SQFloat::AreEquals(this->z, SQFloat::_1);
    }

    /// <summary>
    /// Calculates Dot Product by a vector provided.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A floating point value which is the result of Dot Product.
    /// </returns>
    inline float_q DotProduct(const QBaseVector3 &v) const
    {
        return(this->x*v.x + this->y*v.y + this->z*v.z);
    }

    /// <summary>
    /// Calculates the angle between resident vector and the provided vector via Dot Product.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A floating point value which is the smaller angle between vectors (less or equal 180º).
    /// </returns>
    inline float_q DotProductAngle(const QVector3 &v) const
    {
        float_q fLength = this->GetLength() * v.GetLength();

        // Checkout to avoid division by zero.
        QE_ASSERT(fLength != SQFloat::_0);

        float_q fDot = this->DotProduct(v)/fLength;

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1);

        float_q fAngle = acos_q(fDot);
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            fAngle = SQAngle::RadiansToDegrees(fAngle, fAngle);
        #endif

        return fAngle;
    }

    /// <summary>
    /// Calculates Cross Product by a vector provided (left handed rules), and stores it in resident vector.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    void CrossProduct(const QBaseVector3 &v);

    /// <summary>
    /// Calculates Cross Product by a vector provided (left handed rules).
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <param name="vOut">[OUT] Vector to store the resul of Cross Product.</param>
    /// <remarks>
    /// Cross Product is noncommutative, please note the resident vector is the first operator, set to the left
    /// of the Cross Product operator sign, and the input vector is the second operator (set to the right).
    /// </remarks>
    inline void CrossProduct(const QBaseVector3 &v, QBaseVector3 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector3&> (vOut).CrossProduct(v);
    }

    /// <summary>
    /// Makes a Linear Interpolation between resident vector and other vector provided. It stores result in resident vector.
    /// </summary>
    /// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the resident vector (per one).</param>
    /// <param name="v">[IN] Vector with which to interpolate.</param>
    inline void Lerp(const float_q &fFactor, const QBaseVector3 &v)
    {
        this->x = this->x*fFactor + v.x*(SQFloat::_1 - fFactor);
        this->y = this->y*fFactor + v.y*(SQFloat::_1 - fFactor);
        this->z = this->z*fFactor + v.z*(SQFloat::_1 - fFactor);
    }

    /// <summary>
    /// Makes a Linear Interpolation between resident vector and other vector provided. It stores result in a vector provided.
    /// </summary>
    /// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the resident vector (per one).</param>
    /// <param name="v">[IN] Vector with which to interpolate.</param>
    /// <param name="vOut">[OUT] Vector to store results of interpolation.</param>
    inline void Lerp(const float_q &fFactor, const QBaseVector3 &v, QBaseVector3 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector3&> (vOut).Lerp(fFactor, v);
    }

    /// <summary>
    /// Calculates the distance between two vector heads (or two points). It computes the difference of two vectors and returns its length.
    /// </summary>
    /// <param name="v">[IN] Vector we want to calculate the distance from resident vector.</param>
    /// <returns>
    /// A positive floating point value containing the distance between both vectors.
    /// </returns>
    inline float_q Distance(const QBaseVector3 &v) const
    {
        return sqrt_q( (this->x-v.x)*(this->x-v.x) + (this->y-v.y)*(this->y-v.y) + (this->z-v.z)*(this->z-v.z) );

        //[TODO] jwladi: it may be done as follows, with 3 substractions less:
        // return QVector3(*this - v).GetLength();
    }

    /// <summary>
    /// Applies a rotation quaternion to resident vector. The rotation applied is clockwise.
    /// It's made by multiplying resident vector by the quaternion provided, as follows:
    /// \f$ v' = Q \cdot v \cdot Q^*\f$,
    /// where v is the resident vector, Q the quaternion and \f$ Q^*\f$ the conjugate of the quaternion.
    /// [TODO] jwladi: probably it will be necessary verify if rotation is clockwise or not.
    /// </summary>
    /// <param name="qR">[IN] The rotation quaternion.</param>
    void Transform(const QQuaternion &qR);

    /// <summary>
    /// Applies a rotation quaternion to resident vector, storing results in an out vector provided.
    /// The rotation applied is clockwise.
    /// It's made by multiplying resident vector by the quaternion provided, as follows:
    /// \f$ v' = Q \cdot v \cdot Q^*\f$,
    /// where v is the resident vector, Q the quaternion and \f$ Q^*\f$ the conjugate of the quaternion.
    /// </summary>
    /// <param name="qR">[IN] The rotation quaternion.</param>
    /// <param name="vOut">[OUT] The vector where the result of rotation is stored.</param>
    inline void Transform(const QQuaternion &qR, QBaseVector3 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector3&> (vOut).Transform(qR);
    }

    /// <summary>
    /// Applies a rigid transformation dual quaternion to resident vector.
    /// It's made by multiplying resident vector by the dual quaternion provided, as follows:
    /// \f$ v' = \hat{Q} \cdot v \cdot \hat{Q}^*\f$,
    /// where v is the resident vector, \f$\hat{Q}\f$ the dual quaternion and \f$\hat{Q}^*\f$ the double conjugate of the dual quaternion.
    /// </summary>
    /// <param name="dqTransf">[IN] The dual quaternion which wears the transformation.</param>
    void Transform(const QDualQuaternion &dqTransf);

    /// <summary>
    /// Applies a rigid transformation dual quaternion to resident vector, storing results in an out vector provided.
    /// It's made by multiplying resident vector by the dual quaternion provided, as follows:
    /// \f$ v' = \hat{Q} \cdot v \cdot \hat{Q}^*\f$,
    /// where v is the resident vector, \f$\hat{Q}\f$ the dual quaternion and \f$\hat{Q}^*\f$ the double conjugate of the dual quaternion.
    /// </summary>
    /// <param name="dqTransf">[IN] The dual quaternion which wears the transformation..</param>
    /// <param name="vOut">[OUT] The vector where the result of rotation is stored.</param>
    inline void Transform(const QDualQuaternion &dqTransf, QBaseVector3 &vOut) const
    {
        vOut = *this;
        reinterpret_cast<QVector3&> (vOut).Transform(dqTransf);
    }

    /// <summary>
    /// Applies a rotation to resident vector, multiplying the vector by a rotation matrix
    /// to transform it.
    /// </summary>
    /// <param name="mRot">[IN] The rotation matrix.</param>
	void Transform(const QRotationMatrix3x3 &mRot);

    /// <summary>
    /// Applies a rotation to resident vector, multiplying the vector by a rotation matrix
    /// to transform it. The rotated vector is stored into the provided one.
    /// </summary>
    /// <param name="mRot">[IN] The rotation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of rotation.</param>
	void Transform(const QRotationMatrix3x3 &mRot, QBaseVector3 &vOut) const;

    /// <summary>
    /// Applies a scale transformation to resident vector, multiplying the vector by a scale matrix
    /// to transform it.
    /// </summary>
    /// <param name="mScale">[IN] The scale matrix.</param>
	void Transform(const QScaleMatrix3x3 &mScale);

    /// <summary>
    /// Applies a scale transformation to resident vector, multiplying the vector by a scale matrix
    /// to transform it. The scaled vector is stored into the provided one.
    /// </summary>
    /// <param name="mScale">[IN] The scale matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of scale.</param>
	void Transform(const QScaleMatrix3x3 &mScale, QBaseVector3 &vOut) const;

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	void Transform(const QTranslationMatrix<QMatrix4x3> &mDisp);

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	void Transform(const QTranslationMatrix<QMatrix4x4> &mDisp);

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The translated vector is stored into the provided one.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of translation.</param>
	void Transform(const QTranslationMatrix<QMatrix4x3> &mDisp, QBaseVector3 &vOut) const;

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The translated vector is stored into the provided one.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of translation.</param>
	void Transform(const QTranslationMatrix<QMatrix4x4> &mDisp, QBaseVector3 &vOut) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	void Transform(const QTransformationMatrix<QMatrix4x3> &mTransf);

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	void Transform(const QTransformationMatrix<QMatrix4x4> &mTransf);

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The transformed vector is stored into the provided one.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of transformation.</param>
	void Transform(const QTransformationMatrix<QMatrix4x3> &mTransf, QBaseVector3 &vOut) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The transformed vector is stored into the provided one.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of transformation.</param>
	void Transform(const QTransformationMatrix<QMatrix4x4> &mTransf, QBaseVector3 &vOut) const;

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a space conversion matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The space conversion matrix.</param>
	void Transform(const QSpaceConversionMatrix &mTransf);

	/// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a space conversion matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced. The transformed vector is stored into the provided one.
    /// </summary>
    /// <param name="mTransf">[IN] The space conversion matrix.</param>
	/// <param name="vOut">[OUT] Vector where to store the result of transformation.</param>
	void Transform(const QSpaceConversionMatrix &mTransf, QBaseVector3 &vOut) const;

    /// <summary>
    /// Converts vector into a string with the following format:
    /// "V3(x, y, z)".
    /// </summary>
    /// <returns>The std::string with the format specified.</returns>
    inline string_q ToString() const
    {
        return QE_L("V3(") + SQFloat::ToString(this->x) +
               QE_L(", ")  + SQFloat::ToString(this->y) +
               QE_L(", ")  + SQFloat::ToString(this->z) + QE_L(")");
    }

protected:

    /// <summary>
    /// Applies a translation to resident vector, multiplying the vector by a translation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mDisp">[IN] The translation matrix. It must be a 4x3 or a 4x4 translation matrix.</param>
	template <class MatrixType>
	void TransformImp(const QTranslationMatrix<MatrixType> &mDisp);

    /// <summary>
    /// Applies a transformation composed of a scale, a rotation and a translation
	/// to resident vector, multiplying the vector by a transformation matrix
	/// to transform it. We assume that resident vector represents a 3D point
	/// \f$(v_x, v_y, v_z, 1)\f$ and not a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
	/// since a 3D vector cannot be displaced.
    /// </summary>
    /// <param name="mTransf">[IN] The transformation matrix. It must be a 4x3 or a 4x4 matrix.</param>
    template <class MatrixType>
	void TransformImp(const QTransformationMatrix<MatrixType> &mTransf);
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVECTOR3__
