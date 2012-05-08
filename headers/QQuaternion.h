// [TERMS&CONDITIONS]

#ifndef __QQUATERNION__
#define __QQUATERNION__

#include "SQAngle.h"
#include "QBaseQuaternion.h"
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
class QMatrix4x3;
class QMatrix4x4;
template<class MatrixType> class QTransformationMatrix;
class QRotationMatrix3x3;


/// <summary>
/// Quaternions extend the concept of rotation in three dimensions to rotation in four dimensions.<br>
/// This avoids the problem of "gimbal-lock"
/// and allows for the implementation of smooth and continuous rotation.<br>
/// In effect, they may be considered to add a additional rotation angle
/// to spherical coordinates ie. Longitude, Latitude and Rotation angles.<br>
/// A Quaternion is defined using four floating point values |x y z w|.<br>
/// These are calculated from the combination of the three coordinates
/// of the rotation axis and the rotation angle.<br>
/// Text extracted from: Flipcode.
/// </summary>
class QDllExport QQuaternion : public QBaseQuaternion
{
    // FRIENDS
    // ---------------
public:

    // [REVIEW] Thund: Does Doxygen catch this documentation for global functions?
    /// <summary>
    /// Multiply by scalar operator. All quaternion's components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar factor.</param>
    /// <param name="qQuat">[IN] The quaternion factor.</param>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    friend QQuaternion operator*(const float_q &fScalar, const QQuaternion &qQuat);


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    inline QQuaternion() : QBaseQuaternion()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion in which we want resident quaternion to be based.</param>
    inline QQuaternion(const QBaseQuaternion &qQuat) : QBaseQuaternion(qQuat)
    {
    }

    /// <summary>
    /// Constructor that receives 3 angles, one for each Euler angle, to represent a spacial rotation as a quaternion.<br>
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.<br>
    /// This is a slow operation.
    /// </summary>
    /// <param name="fRotationAngleX">[IN] Rotation angle about X global axis.</param>
    /// <param name="fRotationAngleY">[IN] Rotation angle about Y global axis.</param>
    /// <param name="fRotationAngleZ">[IN] Rotation angle about Z global axis.</param>
    /// <remarks>
    /// This method produces a normalized quaternion.
    /// </remarks>
    QQuaternion(const float_q &fRotationAngleX, const float_q &fRotationAngleY, const float_q &fRotationAngleZ);

    /// <summary>
    /// Constructor that receives 4 values, one per quaternion's component.
    /// </summary>
    /// <param name="fValueX">[IN] X component value.</param>
    /// <param name="fValueY">[IN] Y component value.</param>
    /// <param name="fValueZ">[IN] Z component value.</param>
    /// <param name="fValueW">[IN] W component value.</param>
    inline QQuaternion(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ, const float_q &fValueW) :
                           QBaseQuaternion(fValueX, fValueY, fValueZ, fValueW)
    {
    }

    /// <summary>
    /// Constructor that receives a pointer to a sequence of 4 contiguous values, one per quaternion's component.
    /// </summary>
    /// <param name="arValues">[IN] Sequence of 4 contiguous values.</param>
    inline explicit QQuaternion(const float_q* arValues) : QBaseQuaternion(arValues)
    {
    }

    /// <summary>
    /// Constructor that receives four 32 bits floating point type, one per quaternion's component, packaged
    /// into a 128 bits structure.<br>
    /// The values order is: X, Y, Z and W.
    /// </summary>
    /// <param name="value">[IN] A four 32 bits floating point types pack.</param>
    inline explicit QQuaternion(const vf32_q &value) : QBaseQuaternion(value)
    {
    }

	/// <summary>
	/// Constructor that receives a rotation angle \f$ (\theta)\f$ and
	/// a normalized vector \f$ \vec{n}(n_x, n_y, n_z)\f$ in the direction of the spin axis.<br>
	/// The resultant quaternion is:
	///
	/// \f$ (n_x sin(\frac{\theta}{2}), n_y sin(\frac{\theta}{2}), n_z sin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$
    /// </summary>
    /// <param name="vRotationAxis">[IN] Normalined vector in the direction of the spin axis.</param>
	/// <param name="fRotationAngle">[IN] Angle of rotation.</param>
	/// <remarks>
	/// Please note it's a mandatory that the input vector representing the spin axis has to be normalized
	/// in order to create the quaternion correctly (a normalized rotation quaternion).
	/// </remarks>
	QQuaternion(const QBaseVector3 &vRotationAxis, const float_q &fRotationAngle);

	/// <summary>
	/// Constructor that receives a rotation angle \f$ (\theta)\f$ and
	/// a normalized vector \f$ \vec{n}(n_x, n_y, n_z)\f$ in the direction of the spin axis.<br>
	/// The resultant quaternion is:
	/// \f$ (n_x sin(\frac{\theta}{2}), n_y sin(\frac{\theta}{2}), n_z sin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$
	///
	/// Fourth vector component is ignored.
    /// </summary>
    /// <param name="vRotationAxis">[IN] Normalized vector in the direction of the spin axis.</param>
	/// <param name="fRotationAngle">[IN] Angle of rotation.</param>
	/// <remarks>
	/// Please note it's a mandatory that the input vector representing the spin axis has to be normalized
	/// in order to create the quaternion correctly (a normalized rotation quaternion).
	/// </remarks>
	QQuaternion(const QBaseVector4 &vRotationAxis, const float_q &fRotationAngle);

	/// <summary>
	/// Constructor that receives a transformation matrix. The quaternion will contain the rotation the matrix represents.
    /// </summary>
    /// <param name="transformation">[IN] A transformation matrix.</param>
    /// <remarks>
    /// This method produces a normalized quaternion.
    /// </remarks>
	explicit QQuaternion(const QTransformationMatrix<QMatrix4x3> &transformation);

	/// <summary>
	/// Constructor that receives a transformation matrix. The quaternion will contain the rotation the matrix represents.
    /// </summary>
    /// <param name="transformation">[IN] A transformation matrix.</param>
	explicit QQuaternion(const QTransformationMatrix<QMatrix4x4> &transformation);

	/// <summary>
	/// Constructor that receives a 3x3 rotation matrix.
    /// </summary>
    /// <param name="rotation">[IN] A 3x3 rotation matrix.</param>
    /// <remarks>
    /// This method produces a normalized quaternion.
    /// </remarks>
	explicit QQuaternion(const QRotationMatrix3x3 &rotation);

protected:

	// <summary>
	// Constructor that receives a transformation matrix. The quaternion will contain the rotation the matrix represents.
    // </summary>
    // <param name="transformation">[IN] A transformation matrix.</param>
	template <class MatrixType>
	void QQuaternionImp(const QTransformationMatrix<MatrixType> &transformation);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the identity quaternion.
    /// </summary>
    /// <returns>
    /// The identity quaternion.
    /// </returns>
    inline static const QQuaternion& GetIdentity()
    {
        static const QQuaternion IDENTITY(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
        return IDENTITY;
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Add operator. Each input quaternion's component is added to the corresponding quaternion's.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="qQuat">[IN] The quaternion that is Added.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator+(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Subtract operator. Each input quaternion's component is subtracted to the corresponding quaternion's.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="qQuat">[IN] The quaternion that is subtracted.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator-(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Multiply operator. The quaternion is multipled by the input one and the result is returned.<br>
    /// This is calculated as follows:
    ///
    /// \f$ Q_1 \cdot Q_2=(w_1w_2-x_1x_2-y_1y_2-z_1z_2)+(w_1x_2+x_1w_2+y_1z_2-z_1y_2)i+(w_1y_2+y_1w_2+z_1x_2-x_1z_2)j+(w_1z_2+z_1w_2+xv1y_2-y_1x_2)k\f$
    ///
    /// Note that quaternion multiplication is not conmutative.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="qQuat">[IN] The quaternion to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const QBaseQuaternion &qQuat) const;// [DOC] Thund: Update the documentation (formula changed)

    /// <summary>
    /// Multiply by scalar operator. All quaternion's components are multiplied by the scalar.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const float_q &fScalar) const;

	/// <summary>
    /// Multiply by 3D vector operator.<br>
    /// The vector is converted into a quaternion \f$ (v_x, v_y, v_z, 0) \f$ before multiplication.
    /// </summary>
    /// <param name="vVector">[IN] The vector to multiply by.</param>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const QBaseVector3 &vVector) const;

	/// <summary>
    /// Multiply by 4D vector operator.<br>
    /// The vector is converted into a quaternion \f$ (v_x, v_y, v_z, v_w) \f$ before multiplication.
    /// </summary>
    /// <param name="vVector">[IN] The vector to multiply by.</param>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const QBaseVector4 &vVector) const;

    /// <summary>
    /// Divide operator. The quaternion is divided by the input one.<br>
    /// The division is performed by multiplying by the input quaternion's inverse.<br>
    /// Note that, if you want boost your division performance and you work with normalized quaternions,
    /// then you can multiply by the quaternion's conjugate (that is
    /// cheaper to calculate) instead of using this operator.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to divide by.</param>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator/(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Divide by scalar operator. All quaternion's components are divided by the scalar.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="fScalar">[IN] The scalar to divide by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator/(const float_q &fScalar) const;

    /// <summary>
    /// Add and assign operator. Each input quaternion's component is added to the corresponding quaternion's.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="qQuat">[IN] The quaternion that is Added.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator+=(const QBaseQuaternion &qQuat)
    {
        this->x += qQuat.x;
        this->y += qQuat.y;
        this->z += qQuat.z;
        this->w += qQuat.w;
        return *this;
    }

    /// <summary>
    /// Subtract and assign operator. Each input quaternion's component is subtracted to the corresponding quaternion's.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="qQuat">[IN] The quaternion that is subtracted.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator-=(const QBaseQuaternion &qQuat)
    {
        this->x -= qQuat.x;
        this->y -= qQuat.y;
        this->z -= qQuat.z;
        this->w -= qQuat.w;

        return *this;
    }

    /// <summary>
    /// Multiply and assign operator. The quaternion is multipled by the input one.<br>
    /// This is calculated as follows:
    ///
    /// \f$ Q_1 \cdot Q_2=(w_1w_2-x_1x_2-y_1y_2-z_1z_2)+(w_1x_2+x_1w_2+y_1z_2-z_1y_2)i+(w_1y_2+y_1w_2+z_1x_2-x_1z_2)j+(w_1z_2+z_1w_2+xv1y_2-y_1x_2)k\f$
    ///
    /// Note that quaternion multiplication is not conmutative.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="qQuat">[IN] The quaternion to multiply by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const QBaseQuaternion &qQuat)// [DOC] Thund: Update the documentation (formula changed)
    {
        QQuaternion resQuat( qQuat.w * this->x + qQuat.x * this->w + qQuat.y * this->z - qQuat.z * this->y,	   // Vx
                             qQuat.w * this->y + qQuat.y * this->w + qQuat.z * this->x - qQuat.x * this->z,	   // Vy
                             qQuat.w * this->z + qQuat.z * this->w + qQuat.x * this->y - qQuat.y * this->x,	   // Vz
                             qQuat.w * this->w - qQuat.x * this->x - qQuat.y * this->y - qQuat.z * this->z );  // W
        this->x = resQuat.x;
        this->y = resQuat.y;
        this->z = resQuat.z;
        this->w = resQuat.w;

        return *this;
    }

    /// <summary>
    /// Multiply by scalar and assign operator. All quaternion's components are multiplied by the scalar.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const float_q fScalar)
    {
        this->x *= fScalar;
        this->y *= fScalar;
        this->z *= fScalar;
        this->w *= fScalar;

        return *this;
    }

	/// <summary>
    /// Multiply by 3D vector and assign operator.<br>
    /// The vector is converted into a quaternion \f$ (v_x, v_y, v_z, 0) \f$ before multiplication.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="vVector">[IN] The vector to multiply by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const QBaseVector3 &vVector)
	{
		QQuaternion qAux(vVector.x, vVector.y, vVector.z, SQFloat::_0);

		*this *= qAux;

		return *this;
	}

	/// <summary>
    /// Multiply by 4D vector and assign operator.<br>
    /// The vector is converted into a quaternion \f$ (v_x, v_y, v_z, v_w) \f$ before multiplication.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="vVector">[IN] The vector to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const QBaseVector4 &vVector)
	{
		QQuaternion qAux(vVector.x, vVector.y, vVector.z, vVector.w);

		*this *= qAux;

		return *this;
	}

    /// <summary>
    /// Divide and assign operator. The quaternion is divided by the input one.<br>
    /// The division is performed by multiplying by the input quaternion's inverse.<br>
    /// Note that, if you want boost your division performance and
    /// you work with normalized quaternions, then you can multiply by the quaternion's conjugate (that is
    /// cheaper to calculate) instead of using this operator.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="qQuat">[IN] The quaternion to divide by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator/=(const QBaseQuaternion &qQuat)
    {
        QBaseQuaternion resQuat = qQuat.As<const QQuaternion>().Invert();

        this->operator*=(resQuat);

        return *this;
    }

    /// <summary>
    /// Divide by scalar and assign operator. All quaternion's components are divided by the scalar.
    /// </summary>
    /// <remarks>
    /// Note that the quaternion could be denormalized after this operation.
    /// </remarks>
    /// <param name="fScalar">[IN] The scalar to divide by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator/=(const float_q &fScalar)
    {
        QE_ASSERT(fScalar != SQFloat::_0)

        const float_q &DIVISOR = SQFloat::_1/fScalar;

        this->x *= DIVISOR;
        this->y *= DIVISOR;
        this->z *= DIVISOR;
        this->w *= DIVISOR;

        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided quaternion to the resident quaternion.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to be assigned.</param>
    /// <returns>
    /// A reference to the modified quaternion.
    /// </returns>
    inline QQuaternion& operator=(const QBaseQuaternion &qQuat)
    {
        QBaseQuaternion::operator=(qQuat);
        return *this;
    }

    /// <summary>
    /// Unary minus operator. Obtains a copy of the resident quaternion which has each component multiplied by -1.
    /// </summary>
    /// <returns>
    /// A copy of the resident quaternion which has each component multiplied by -1.
    /// </returns>
	inline QQuaternion operator-() const
	{
		return QQuaternion(-this->x, -this->y, -this->z, -this->w);
	}
	
	/// <summary>
    /// Normalizes the quaternion by dividing all quaternion's components by the quaternion's length.<br>
    /// A quaternion is normalized when its length is equal to 1.
    /// </summary>
    /// <returns>
    /// The normalized quaternion.
    /// </returns>
    inline QQuaternion Normalize() const
    {
        QE_ASSERT(this->GetLength()) // Code that will not execute, no overhead

        const float_q& INV_LENGTH = SQFloat::_1 / this->GetLength();

        return QQuaternion(this->x * INV_LENGTH, this->y * INV_LENGTH, this->z * INV_LENGTH, this->w * INV_LENGTH);
    }

    /// <summary>
    /// Calculates the quaternion's inverse.<br>
    /// Note that, when the quaternion is normalized, the inverse coincides with the conjugate (which is cheaper to calculate).<br>
    /// Quaternion inverse is obtained by the following equation:
    ///
    /// \f$ Q^{-1} = \frac{w - xi - yj - zk}{\left|Q\right|^2}\f$
    /// </summary>
    /// <returns>
    /// The reversed quaternion.
    /// </returns>
    inline QQuaternion Invert() const
    {
        // [TODO] Thund: DirectX implementation uses ln(Q) = (0, theta * v), is it faster?
        const float_q& SQUARED_LENGTH = this->GetSquaredLength();

        QE_ASSERT(SQUARED_LENGTH != SQFloat::_0)

        const float_q& NEG_INV_LENGTH = -SQFloat::_1/SQUARED_LENGTH;

        return QQuaternion(this->x * NEG_INV_LENGTH, this->y * NEG_INV_LENGTH, this->z * NEG_INV_LENGTH, this->w * -NEG_INV_LENGTH);
    }

    /// <summary>
    /// Calculates the inverse of a normalized quaternion, which coincides with its conjugate.<br>
    /// Quaternion inverse is then obtained by the following equation:
    ///
    /// \f$ Q^{-1} = w - xi - yj - zk \f$
    /// </summary>
    /// <returns>
    /// The reversed quaternion.
    /// </returns>
    inline QQuaternion UnitInvert() const
    {
		return this->Conjugate();
    }

    /// <summary>
    /// Sets all quaternion's components to zero.
    /// </summary>
    inline void ResetToZero()
    {
        this->x = this->y = this->z = this->w = SQFloat::_0;
    }

    /// <summary>
    /// Sets quaternion to the identity quaternion.
    /// </summary>
    inline void ResetToIdentity()
    {
        this->x = this->y = this->z = SQFloat::_0;
        this->w = SQFloat::_1;
    }

    /// <summary>
    /// Calculates the dot product between the quaternion and the input quaternion.<br>
    /// This is obtained using the equation:
    ///
    /// \f$ f(Q_1, Q_2) = x_1x_2 + y_1y_2 + z_1z_2 + w_1w_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to multiply by.</param>
    /// <returns>
    /// A real number equals to:
    ///
    /// \f$|Q_1|\cdot |Q_2| cos(\beta)\f$, where
    ///
    /// \f$\beta = \frac{\widehat{Q_1Q_2}}{2}\f$
    ///
    /// (half the angle between quaternions, when using normalized quaternions).
    /// </returns>
    float_q DotProduct(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Calculates the angle between resident quaternion and the provided quaternion, via dot product. Both 
    /// quaternions have to be normalized to obtain a more precise value.<br>
    /// </summary>
    /// <param name="qQuat">[IN] Multiplying quaternion.</param>
    /// <returns>
    /// A floating point value which is the smaller angle between quaternions (less or equal to \f$ 180^0\f$).
    /// </returns>
    float_q DotProductAngle(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Calculates the quaternion's conjugate.<br>
    /// It's calculated this way:
    ///
    /// \f$Q^* = w - xi - yj - zk\f$.
    /// </summary>
    /// <returns>
    /// The conjugated quaternion.
    /// </returns>
    inline QQuaternion Conjugate() const
    {
        return QQuaternion(-this->x, -this->y, -this->z, this->w);
    }

    /// <summary>
    /// Calculates the linear interpolation between the quaternion and the input quaternion.<br>
    /// This is calculated by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = \frac{(1 - s)Q_1 + sQ_2}{|(1 - s)Q_1 + sQ_2|}\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two quaternions and \f$ s\f$ the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above).</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    /// <returns>
    /// The "lerped" quaternion. It's normalized.
    /// </returns>
    QQuaternion Lerp(const QQuaternion &qQuat, const float_q &fProportion) const; // DOC Thund: Explain that 1 means input, 0 means resident. Maybe calculus is about to change.

    /// <summary>
    /// Calculates the spherical linear interpolation between the quaternion and the input quaternion.
    /// This is calculated by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = w_1Q_1 + w_2Q_2\f$
    ///
    /// where
    ///
    /// \f$ w_1 = \frac{sin( (1 - s) \beta)}{sin(\beta)}\f$
    ///
    /// \f$ w_2 = \frac{sin( s\beta)}{sin(\beta)})\f$
    ///
    /// where
    ///
    /// \f$ \beta = \arccos(Q_1Q_2)\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two quaternions and \f$ s\f$ the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above).</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    /// <returns>
    /// The "lerped" quaternion.
    /// </returns>
    QQuaternion Slerp(const QQuaternion &qQuat, const float_q &fProportion) const; // DOC Thund: Explain that 1 means input, 0 means resident. Maybe calculus is about to change.
    
    /// <summary>
    /// Calculates the spherical linear interpolation between two normalized quaternions.
    /// This is calculated by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = w_1Q_1 + w_2Q_2\f$
    ///
    /// where
    ///
    /// \f$ w_1 = \frac{sin( (1 - s) \beta)}{sin(\beta)}\f$
    ///
    /// \f$ w_2 = \frac{sin( s\beta)}{sin(\beta)})\f$
    ///
    /// where
    ///
    /// \f$ \beta = \arccos(Q_1Q_2)\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two normalized quaternions and \f$ s\f$ the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above). It must be a normalized quaternion</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    /// <returns>
    /// The "lerped" quaternion.
    /// </returns>
    QQuaternion UnitSlerp(const QQuaternion &qQuat, const float_q &fProportion) const; // DOC Thund: Explain that 1 means input, 0 means resident. Maybe calculus is about to change.

    /// <summary>
    /// Obtains Euler angles that represent the same rotation than the quaternion does.<br>
    /// </summary>
    /// <remarks>
    /// The quaternion must be normalized in order to get correct results.<br>
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.<br>
    /// To achieve this, the following equations are implemented:<br>
    ///
    /// \f$ X = atan2( 2xw - 2xz, 1 - 2y^2 - 2z^2 )\f$
    ///
    /// \f$ Y = asin(2xy + 2zw)\f$
    ///
    /// \f$ Z = atan2( 2xw - 2yz, 1 - 2x^2 - 2z^2 )\f$
    ///
    /// except when \f$ xy + zw = +0.5\f$ (north pole)
    ///
    /// \f$ X = 2atan2(x, w)\f$
    ///
    /// \f$ Z = 0\f$
    ///
    /// or when \f$ xy + zw = -0.5\f$ (south pole)
    ///
    /// \f$ X = -2atan2(x, w)\f$
    ///
    /// \f$ Z = 0\f$
    ///
    /// See atan2 documentation for more interesting information.
    /// Note that obtained angles haven't to match whatever values 
    /// were used to create the quaternion from 3 Euler angles.
    /// </remarks>
    /// <param name="fRotationAngleX">X Euler angle (pitch).</param>
    /// <param name="fRotationAngleY">Y Euler angle (yaw).</param>
    /// <param name="fRotationAngleZ">Z Euler angle (roll).</param>
    void ToEulerAngles(float_q &fRotationAngleX, float_q &fRotationAngleY, float_q &fRotationAngleZ) const; // DOC [Thund]: Maybe formulas has to be updated

    /// <summary>
    /// Calculates the quaternion's length, this means, the square root of the squared components sum.
    /// </summary>
    /// <returns>
    /// The resultant length.
    /// </returns>
    float_q GetLength() const;

    /// <summary>
    /// Calculates the squared quaternion's length, this means, the squared components sum.
    /// This method exists due to performance reasons because it avoids to perform square roots when the result is
    /// going to be squared.
    /// </summary>
    /// <returns>
    /// The resultant squared length.
    /// </returns>
    float_q GetSquaredLength() const;

    /// <summary>
    /// Obtains the angle of rotation and the spin axis contained in the resident quaternion.<br>
	/// There are two possible singularities: when rotation angle is 0 or \f$ 180^0\f$.
    /// </summary>
    /// <param name="vRotationAxis">Vector to store the spin axis.</param>
    /// <param name="fRotationAngle">Angle of rotation.</param>
	void ToAxisAngle(QBaseVector3 &vRotationAxis, float_q &fRotationAngle) const;

    /// <summary>
    /// Obtains the angle of rotation and the spin axis contained in the resident quaternion.<br>
	/// There are two possible singularities: when rotation angle is 0 or \f$ 180^0\f$.
    /// </summary>
    /// <remarks>
    /// Note that angle and axis haven't to match whatever values were used to create the quaternion from 
    /// an axis and an angle.
    /// </remarks>
    /// <param name="vRotationAxis">Vector to store the spin axis.</param>
    /// <param name="fRotationAngle">Angle of rotation.</param>
	void ToAxisAngle(QBaseVector4 &vRotationAxis, float_q &fRotationAngle) const;

	/// <summary>
    /// Gets a character string that represents the quaternion values.
    /// </summary>
    /// <returns>
    /// A character string, following this pattern:<br>
    /// "Q($x,$y,$z,$w)".<br>
    /// Where "$" means "string representation of attribute".
    /// </returns>
    string_q ToString() const;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QQUATERNION__
