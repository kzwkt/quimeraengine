// [TERMS&CONDITIONS]

#ifndef __QQUATERNION__
#define __QQUATERNION__

#include "QAngle.h"
#include "QBaseQuaternion.h"
#include "QBaseVector3.h"
#include "QBaseVector4.h"
#include "QRotationMatrix3x3.h"
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
/// Quaternions extend the concept of rotation in three dimensions to
/// rotation in four dimensions. This avoids the problem of "gimbal-lock"
/// and allows for the implementation of smooth and continuous rotation.
///
/// In effect, they may be considered to add a additional rotation angle
/// to spherical coordinates ie. Longitude, Latitude and Rotation angles
///
/// A Quaternion is defined using four floating point values |x y z w|.
///
/// These are calculated from the combination of the three coordinates
/// of the rotation axis and the rotation angle.
///
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
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    friend QQuaternion operator*(const float_q &fScalar, const QBaseQuaternion &qQuat);

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Represents the identity quaternion.
    /// </summary>
    static const QQuaternion Identity;

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    inline QQuaternion() : QBaseQuaternion() {};

    /// <summary>
    /// Constructor that receives a base quaternion.
    /// </summary>
    /// <param name="qQuat">[IN] A base quaternion.</param>
    inline explicit QQuaternion(const QBaseQuaternion &qQuat) : QBaseQuaternion(qQuat) {};

    /// <summary>
    /// Constructor that receives 3 angles, one for each Euler angle, to represent a spacial rotation as a quaternion.
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll. This is a slow operation.
    /// </summary>
    /// <param name="fAngleX">[IN] Rotation angle about X global axis.</param>
    /// <param name="fAngleY">[IN] Rotation angle about Y global axis.</param>
    /// <param name="fAngleZ">[IN] Rotation angle about Z global axis.</param>
    QQuaternion(const float_q &fAngleX, const float_q &fAngleY, const float_q &fAngleZ);

    /// <summary>
    /// Constructor that receives 4 values, one per quaternion's component.
    /// </summary>
    /// <param name="fValueX">[IN] X component value.</param>
    /// <param name="fValueY">[IN] Y component value.</param>
    /// <param name="fValueZ">[IN] Z component value.</param>
    /// <param name="fValueW">[IN] W component value.</param>
    inline QQuaternion(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ, const float_q &fValueW)
         : QBaseQuaternion(fValueX, fValueY, fValueZ, fValueW) {};

    /// <summary>
    /// Constructor that receives a pointer to a sequence of 4 contiguous values, one per quaternion's component.
    /// </summary>
    /// <param name="pValues">[IN] Sequence of 4 contiguous values.</param>
    inline explicit QQuaternion(const float_q* pValues) : QBaseQuaternion(pValues) {};

    /// <summary>
    /// Constructor that receives four 32 bits floating point type, one per quaternion's component, packaged
    /// into a 128 bits structure. The values order is: X, Y, Z and W.
    /// </summary>
    /// <param name="vfValue">[IN] A four 32 bits floating point types pack.</param>
    inline explicit QQuaternion(const vf32_q &vfValue) : QBaseQuaternion(vfValue) {};

	/// <summary>
	/// Constructor that receives a rotation angle \f$ (\theta)\f$ and
	/// a normalized vector \f$ \vec{n}(n_x, n_y, n_z)\f$ in the direction of the spin axis.
	/// The resultant quaternion is \f$ (n_x sin(\frac{\theta}{2}), n_y sin(\frac{\theta}{2}), n_z sin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$
    /// </summary>
    /// <param name="vAxis">[IN] Normalined vector in the direction of the spin axis.</param>
	/// <param name="fAngle">[IN] Angle of rotation.</param>
	/// <remarks>
	/// Please note it's a mandatory that the input vector representing the spin axis has to be normalized
	/// in order to create the quaternion correctly.
	/// </remarks>
	QQuaternion(const QBaseVector3 &vAxis, const float_q &fAngle);

	/// <summary>
	/// Constructor that receives a rotation angle \f$ (\theta)\f$ and
	/// a normalized vector \f$ \vec{n}(n_x, n_y, n_z)\f$ in the direction of the spin axis.
	/// The resultant quaternion is \f$ (n_x sin(\frac{\theta}{2}), n_y sin(\frac{\theta}{2}), n_z sin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$
	/// Fourth vector component is ignored.
    /// </summary>
    /// <param name="vAxis">[IN] Normalized vector in the direction of the spin axis.</param>
	/// <param name="fAngle">[IN] Angle of rotation.</param>
	/// <remarks>
	/// Please note it's a mandatory that the input vector representing the spin axis has to be normalized
	/// in order to create the quaternion correctly.
	/// </remarks>
	QQuaternion(const QBaseVector4 &vAxis, const float_q &fAngle);

	/// <summary>
	/// Constructor that receives a transformation matrix, whose dimensions depend on the
	/// method template parameter.
    /// </summary>
    /// <param name="m">[IN] A transformation matrix.</param>
	template <class MatrixType>
	inline explicit QQuaternion(const QTransformationMatrix<MatrixType> &m)
	{
		m.GetRotation(*this);
	}

	/// <summary>
	/// Constructor that receives a 3x3 rotation matrix.
    /// </summary>
    /// <param name="m">[IN] A 3x3 rotation matrix.</param>
	inline explicit QQuaternion(const QRotationMatrix3x3 &m)
	{
		m.GetRotation(*this);
	}

	// METHODS
	// ---------------
public:

    /// <summary>
    /// Add operator. Each input quaternion's component is added to the corresponding quaternion's.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion that is Added.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator+(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Subtract operator. Each input quaternion's component is subtracted to the corresponding quaternion's.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion that is subtracted.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator-(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Multiply operator. The quaternion is multipled by the input one and the result is returned.
    /// This is calculated as follows:
    ///
    /// \f$ Q_1 \cdot Q_2=(w_1w_2-x_1x_2-y_1y_2-z_1z_2)+(w_1x_2+x_1w_2+y_1z_2-z_1y_2)i+(w_1y_2+y_1w_2+z_1x_2-x_1z_2)j+(w_1z_2+z_1w_2+xv1y_2-y_1x_2)k\f$
    ///
    /// Note that quaternion multiplication is not conmutative.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Multiply by scalar operator. All quaternion's components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const float_q &fScalar) const;

	/// <summary>
    /// Multiply by 3D vector operator. The vector is converted into a
	/// quaternion \f$ (v_x, v_y, v_z, 0) \f$ before multiplication.
    /// </summary>
    /// <param name="v">[IN] The vector to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const QBaseVector3 &v) const;

	/// <summary>
    /// Multiply by 4D vector operator. The vector is converted into a
	/// quaternion \f$ (v_x, v_y, v_z, v_w) \f$ before multiplication.
    /// </summary>
    /// <param name="v">[IN] The vector to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator*(const QBaseVector4 &v) const;

    /// <summary>
    /// Divide operator. The quaternion is divided by the input one. The division is performed by
    /// multiplying by the input quaternion's inverse. Note that, if you want boost your division performance and
    /// you work with normalized quaternions, then you can multiply by the quaternion's conjugate (that is
    /// cheaper to calculate) instead of using this operator.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to divide by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator/(const QBaseQuaternion &qQuat) const;

    /// <summary>
    /// Divide by scalar operator. All quaternion's components are divided by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    QQuaternion operator/(const float_q &fScalar) const;

    /// <summary>
    /// Add and assign operator. Each input quaternion's component is added to the corresponding quaternion's.
    /// </summary>
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
    /// Multiply and assign operator. The quaternion is multipled by the input one.
    /// This is calculated as follows:
    ///
    /// \f$ Q_1 \cdot Q_2=(w_1w_2-x_1x_2-y_1y_2-z_1z_2)+(w_1x_2+x_1w_2+y_1z_2-z_1y_2)i+(w_1y_2+y_1w_2+z_1x_2-x_1z_2)j+(w_1z_2+z_1w_2+xv1y_2-y_1x_2)k\f$
    ///
    /// Note that quaternion multiplication is not conmutative.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to multiply by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const QBaseQuaternion &qQuat)
    {
        QQuaternion resQuat( this->w * qQuat.x + this->x * qQuat.w + this->y * qQuat.z - this->z * qQuat.y,
                             this->w * qQuat.y + this->y * qQuat.w + this->z * qQuat.x - this->x * qQuat.z,
                             this->w * qQuat.z + this->z * qQuat.w + this->x * qQuat.y - this->y * qQuat.x,
                             this->w * qQuat.w - this->x * qQuat.x - this->y * qQuat.y - this->z * qQuat.z);
        this->x = resQuat.x;
        this->y = resQuat.y;
        this->z = resQuat.z;
        this->w = resQuat.w;

        return *this;
    }

    /// <summary>
    /// Multiply by scalar and assign operator. All quaternion's components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const float_q &fScalar)
    {
        this->x *= fScalar;
        this->y *= fScalar;
        this->z *= fScalar;
        this->w *= fScalar;

        return *this;
    }

	/// <summary>
    /// Multiply by 3D vector and assign operator. The vector is converted into a
	/// quaternion \f$ (v_x, v_y, v_z, 0) \f$ before multiplication.
    /// </summary>
    /// <param name="v">[IN] The vector to multiply by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const QBaseVector3 &v)
	{
		QQuaternion qAux(v.x, v.y, v.z, QFloat::_0);

		*this *= qAux;

		return *this;
	}

	/// <summary>
    /// Multiply by 4D vector and assign operator. The vector is converted into a
	/// quaternion \f$ (v_x, v_y, v_z, v_w) \f$ before multiplication.
    /// </summary>
    /// <param name="v">[IN] The vector to multiply by.</param>
    /// <returns>
    /// The resultant quaternion.
    /// </returns>
    inline QQuaternion& operator*=(const QBaseVector4 &v)
	{
		QQuaternion qAux(v.x, v.y, v.z, v.w);

		*this *= qAux;

		return *this;
	}

    /// <summary>
    /// Divide and assign operator. The quaternion is divided by the input one. The division is performed by
    /// multiplying by the input quaternion's inverse. Note that, if you want boost your division performance and
    /// you work with normalized quaternions, then you can multiply by the quaternion's conjugate (that is
    /// cheaper to calculate) instead of using this operator.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to divide by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator/=(const QBaseQuaternion &qQuat)
    {
        QBaseQuaternion resQuat;

        reinterpret_cast<const QQuaternion&> (qQuat).Reverse(resQuat);

        this->operator*=(resQuat);

        return *this;
    }

    /// <summary>
    /// Divide by scalar and assign operator. All quaternion's components are divided by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by.</param>
    /// <returns>
    /// The modified quaternion.
    /// </returns>
    inline QQuaternion& operator/=(const float_q &fScalar)
    {
        QE_ASSERT(fScalar != QFloat::_0);

        this->x /= fScalar;
        this->y /= fScalar;
        this->z /= fScalar;
        this->w /= fScalar;

        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided quaternion to the resident quaternion.
    /// </summary>
    /// <param name="q">[IN] The quaternion to be assigned.</param>
    /// <returns>
    /// A reference to the modified quaternion.
    /// </returns>
    inline QQuaternion& operator=(const QBaseQuaternion &q)
    {
        QBaseQuaternion::operator=(q);
        return *this;
    }

    /// <summary>
    /// Normalizes the quaternion by dividing all quaternion's components by the quaternion's length.
    /// A quaternion is normalized when its length is equal to 1.
    /// </summary>
    inline void Normalize()
    {
        float_q fLength = this->GetLength();

        QE_ASSERT(fLength != QFloat::_0);

        this->x /= fLength;
        this->y /= fLength;
        this->z /= fLength;
        this->w /= fLength;
    }

    /// <summary>
    /// Gets a normalized copy of the quaternion. A quaternion is normalized when its length is equal to 1.
    /// To calculate it, all quaternion's components are divided by the quaternion's length.
    /// </summary>
    /// <param name="qQuat">[OUT] The normalized quaternion copy.</param>
    inline void Normalize(QBaseQuaternion &qQuat) const
    {
        qQuat = *this;
        reinterpret_cast<QQuaternion&> (qQuat).Normalize();
    }

    /// <summary>
    /// Calculates the quaternion's inverse. Note that, when the quaternion is normalized, the inverse
    /// coincides with the conjugate (which is cheaper to calculate).
    /// Quaternion inverse is obtained by the following equation:
    ///
    /// \f$ Q^{-1} = \frac{w - xi - yj - zk}{\left|Q\right|^2}\f$
    /// </summary>
    inline void Reverse()
    {
        // [TODO] Thund: DirectX implementation uses ln(Q) = (0, theta * v), is it faster?
        float_q fSquaredLength = this->GetSquaredLength();

        QE_ASSERT(fSquaredLength != QFloat::_0);

        this->x = -this->x / fSquaredLength;
        this->y = -this->y / fSquaredLength;
        this->z = -this->z / fSquaredLength;
        this->w =  this->w / fSquaredLength;
    }

    /// <summary>
    /// Gets a reveted copy of the quaternion. Note that, when the quaternion is normalized, the inverse
    /// coincides with the conjugate (which is cheaper to calculate).
    /// Quaternion inverse is obtained by the following equation:
    ///
    /// \f$ Q^{-1} = \frac{w - xi - yj - zk}{\left|Q\right|^2}\f$
    /// </summary>
    /// <param name="qQuat">[OUT] The reverted quaternion copy.</param>
    inline void Reverse(QBaseQuaternion &qQuat) const
    {
        qQuat = *this;
        reinterpret_cast<QQuaternion&> (qQuat).Reverse();
    }

    /// <summary>
    /// Calculates the inverse of a unit quaternion, which coincides with its conjugate.
    /// Quaternion inverse is then obtained by the following equation:
    ///
    /// \f$ Q^{-1} = w - xi - yj - zk \f$
    /// </summary>
    inline void UnitReverse()
    {
		this->Conjugate();
    }

    /// <summary>
    /// Gets a reverted copy of a unit quaternion, which coincides with its conjugate.
    /// Quaternion inverse is then obtained by the following equation:
    ///
    /// \f$ Q^{-1} = w - xi - yj - zk \f$
    /// </summary>
	/// <param name="qQuat">[OUT] The reverted quaternion copy.</param>
	inline void UnitReverse(QBaseQuaternion &qQuat) const
	{
        qQuat = *this;
        reinterpret_cast<QQuaternion&> (qQuat).Conjugate();
	}

    /// <summary>
    /// Sets all quaternion's components to zero.
    /// </summary>
    inline void ResetToZero()
    {
        this->x = this->y = this->z = this->w = QFloat::_0;
    }

    /// <summary>
    /// Sets quaternion to the identity quaternion.
    /// </summary>
    inline void ResetToIdentity()
    {
        this->x = this->y = this->z = QFloat::_0;
        this->w = QFloat::_1;
    }

    /// <summary>
    /// Calculates the dot product between the quaternion and the input quaternion.
    /// This is obtained using the equation: \f$ f(Q_1, Q_2) = x_1x_2 + y_1y_2 + z_1z_2 + w_1w_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to multiply by.</param>
    /// <returns>
    /// A real number equals to: \f$|Q_1|\cdot |Q_2| cos(\beta)\f$, where \f$\beta = \frac{\widehat{Q_1Q_2}}{2}\f$
    /// (half the angle between quaternions, when using unit quaternions).
    /// </returns>
    inline float_q DotProduct(const QBaseQuaternion &qQuat) const
    {
        return this->x * qQuat.x + this->y * qQuat.y + this->z * qQuat.z + this->w * qQuat.w;
    }

    /// <summary>
    /// Calculates the angle between resident quaternion and the provided quaternion, via dot product.
    /// Both quaternions are treated as 3D vectors, ignoring W component.
    /// </summary>
    /// <param name="qQuat">[IN] Multiplying quaternion.</param>
    /// <returns>
    /// A floating point value which is the smaller angle between quaternions (less or equal to 180º).
    /// </returns>
    inline float_q DotProductAngle(const QBaseQuaternion &qQuat) const
    {
        float_q fLength = sqrt( (this->x*this->x + this->y*this->y + this->z*this->z) *
                                (qQuat.x*qQuat.x + qQuat.y*qQuat.y + qQuat.z*qQuat.z) );

        // Checkout to avoid division by zero.
        QE_ASSERT(fLength != QFloat::_0);

        float_q fDot = (this->x*qQuat.x + this->y*qQuat.y + this->z*qQuat.z)/fLength;

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(QFloat::Abs(fDot) <= QFloat::_1);

        float_q fAngle = acos(fDot);

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            QAngle::RadiansToDegrees(fAngle, fAngle);
        #endif

        return fAngle;
    }

    /// <summary>
    /// Calculates the quaternion's conjugate. It's calculated this way: \f$Q^* = w - xi - yj - zk\f$.
    /// </summary>
    inline void Conjugate()
    {
        this->x = -this->x;
        this->y = -this->y;
        this->z = -this->z;
        this->w =  this->w;
    }

    /// <summary>
    /// Gets a conjugated quaternion copy. It's calculated this way: \f$Q^* = w - xi - yj - zk\f$.
    /// </summary>
    /// <param name="qQuat">[OUT] The conjugated quaternion copy.</param>
    inline void Conjugate(QBaseQuaternion &qQuat) const
    {
        qQuat = *this;
        reinterpret_cast<QQuaternion&> (qQuat).Conjugate();
    }

    /// <summary>
    /// Calculates the linear interpolation between the quaternion and the input quaternion. This is calculated
    /// by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = \frac{(1 - s)Q_1 + sQ_2}{|(1 - s)Q_1 + sQ_2|}\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two quaternions and s the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above).</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    void Lerp(const QBaseQuaternion &qQuat, const float_q &fProportion);

    /// <summary>
    /// Calculates the linear interpolation between the quaternion and the input quaternion. This is calculated
    /// by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = \frac{(1 - s)Q_1 + sQ_2}{|(1 - s)Q_1 + sQ_2|}\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two quaternions and s the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// The resultant quaternion is stored in an output quaternion.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above).</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    /// <param name="qOutQuat">[OUT] The resultant quaternion.</param>
    inline void Lerp(const QBaseQuaternion &qQuat, const float_q &fProportion, QBaseQuaternion &qOutQuat) const
    {
        qOutQuat = *this;
        reinterpret_cast<QQuaternion&> (qOutQuat).Lerp(qQuat, fProportion);
    }

    /// <summary>
    /// Calculates the spherical linear interpolation between the quaternion and the input quaternion. This is
    /// calculated by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = w_1Q_1 + w_2Q_2\f$
    ///
    /// where
    /// \f$ w_1 = \frac{sin( (1 - s) \beta)}{sin(\beta)}\f$
    ///
    /// \f$ w_2 = \frac{sin( s\beta)}{sin(\beta)})\f$
    ///
    /// where
    ///
    /// \f$ \beta = \arccos(Q_1Q_2)\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two quaternions and s the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above).</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    void Slerp(const QBaseQuaternion &qQuat, const float_q &fProportion);

    /// <summary>
    /// Calculates the spherical linear interpolation between the quaternion and the input quaternion. This is
    /// calculated by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = w_1Q_1 + w_2Q_2\f$
    ///
    /// where
    /// \f$ w_1 = \frac{sin( (1 - s) \beta)}{sin(\beta)}\f$
    ///
    /// \f$ w_2 = \frac{sin( s\beta)}{sin(\beta)})\f$
    ///
    /// where
    ///
    /// \f$ \beta = \arccos(Q_1Q_2)\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two quaternions and s the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// The resultant quaternion is stored in an output quaternion.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above).</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    /// <param name="qOutQuat">[OUT] The interpolation result.</param>
    inline void Slerp(const QBaseQuaternion &qQuat, const float_q &fProportion, QBaseQuaternion &qOutQuat) const
    {
        qOutQuat = *this;
        reinterpret_cast<QQuaternion&> (qOutQuat).Slerp(qQuat, fProportion);
    }


    /// <summary>
    /// Calculates the spherical linear interpolation between two unit quaternions. This is
    /// calculated by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = w_1Q_1 + w_2Q_2\f$
    ///
    /// where
    /// \f$ w_1 = \frac{sin( (1 - s) \beta)}{sin(\beta)}\f$
    ///
    /// \f$ w_2 = \frac{sin( s\beta)}{sin(\beta)})\f$
    ///
    /// where
    ///
    /// \f$ \beta = \arccos(Q_1Q_2)\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two unit quaternions and s the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above). It must be a unit quaternion</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    void UnitSlerp(const QBaseQuaternion &qQuat, const float_q &fProportion);

    /// <summary>
    /// Calculates the spherical linear interpolation between two unit quaternions. This is
    /// calculated by the following expression:
    ///
    /// \f$ f(Q_1, Q_2, s) = w_1Q_1 + w_2Q_2\f$
    ///
    /// where
    /// \f$ w_1 = \frac{sin( (1 - s) \beta)}{sin(\beta)}\f$
    ///
    /// \f$ w_2 = \frac{sin( s\beta)}{sin(\beta)})\f$
    ///
    /// where
    ///
    /// \f$ \beta = \arccos(Q_1Q_2)\f$
    ///
    /// being \f$ Q_1\f$ and \f$ Q_2\f$ two unit quaternions and s the scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.
    /// The resultant quaternion is stored in an output quaternion.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to interpolate with (\f$ Q_2\f$ in expression above). It must be a unit quaternion</param>
    /// <param name="fProportion">[IN] The scalar proportion of distance from \f$ Q_1\f$ to \f$ Q_2\f$.</param>
    /// <param name="qOutQuat">[OUT] The interpolation result.</param>
    inline void UnitSlerp(const QBaseQuaternion &qQuat, const float_q &fProportion, QBaseQuaternion &qOutQuat) const
    {
        qOutQuat = *this;
        reinterpret_cast<QQuaternion&> (qOutQuat).UnitSlerp(qQuat, fProportion);
    }

    /// <summary>
    /// Obtains Euler angles that represent the same rotation than the quaternion does.
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.
    /// To achieve this, the following equations are implemented:
    ///
    /// \f$ X = atan2( 2xw - 2xz, 1 - 2y^2 - 2z^2 )\f$
    /// \f$ Y = asin(2xy + 2zw)\f$
    /// \f$ Z = atan2( 2xw - 2yz, 1 - 2x^2 - 2z^2 )\f$
    ///
    /// except when \f$ xy + zw = +0.5\f$ (north pole)
    ///
    /// \f$ X = 2atan2(x, w)\f$
    /// \f$ Z = 0\f$
    ///
    /// or when \f$ xy + zw = -0.5\f$ (south pole)
    ///
    /// \f$ X = -2atan2(x, w)\f$
    /// \f$ Z = 0\f$
    ///
    /// See atan2 documentation for more interesting information.
    /// </summary>
    /// <param name="fAngleX">X Euler angle (pitch).</param>
    /// <param name="fAngleY">Y Euler angle (yaw).</param>
    /// <param name="fAngleZ">Z Euler angle (roll).</param>
    inline void ToEulerAngles(float_q &fAngleX, float_q &fAngleY, float_q &fAngleZ) const
    {
        // [TODO] Thund: Check whether this implementation corresponds to YawPitchRoll.
        const float_q fNorthAndSouthPoleCheckValue = this->x * this->y + this->z * this->w;

        // X (pitch or heading) and Z (roll or bank) checking
        if(QFloat::AreEquals(fNorthAndSouthPoleCheckValue, QFloat::_0_5)) // North pole
        {
            // The atan2 result is undefined when both parameters are equal to zero
            QE_ASSERT(this->x != QFloat::_0 || this->w != QFloat::_0);

            fAngleX = QFloat::_2 * atan2(this->x, this->w);
            fAngleZ = QFloat::_0;
        }
        else if(QFloat::AreEquals(fNorthAndSouthPoleCheckValue, -QFloat::_0_5)) // South pole
        {
            // The atan2 result is undefined when both parameters are equal to zero
            QE_ASSERT(this->x != QFloat::_0 || this->w != QFloat::_0);

            fAngleX = -QFloat::_2 * atan2(this->x, this->w);
            fAngleZ = QFloat::_0;
        }
        else
        {
            float_q fFirstParameter  = QFloat::_2 * this->x * this->w - QFloat::_2 * this->x * this->z;
            float_q fSecondParameter = QFloat::_1 - QFloat::_2 * this->y * this->y - QFloat::_2 * this->z * this->z;

            // The atan2 result is undefined when both parameters are equal to zero
            QE_ASSERT(fFirstParameter != QFloat::_0 || fSecondParameter != QFloat::_0);

            fAngleX = atan2(fFirstParameter, fSecondParameter);

            fFirstParameter = QFloat::_2 * this->x * this->w - QFloat::_2 * this->y * this->z;
            fSecondParameter = QFloat::_1 - QFloat::_2 * this->x * this->x - QFloat::_2 * this->z * this->z;

            // The atan2 result is undefined when both parameters are equal to zero
            QE_ASSERT(fFirstParameter != QFloat::_0 || fSecondParameter != QFloat::_0);

            fAngleZ = atan2(fFirstParameter, fSecondParameter);
        }

        fAngleY = asin( QFloat::_2 * this->x * this->y + QFloat::_2 * this->z * this->w );

        QE_ASSERT( !QFloat::IsNaN(fAngleX) );
        QE_ASSERT( !QFloat::IsNaN(fAngleY) );
        QE_ASSERT( !QFloat::IsNaN(fAngleZ) );

    }

    /// <summary>
    /// Calculates the quaternion's length, this means, the square root of the squared components sum.
    /// </summary>
    /// <returns>
    /// The resultant length.
    /// </returns>
    inline float_q GetLength() const
    {
        //           _______________________
        // length = V x^2 + y^2 + z^2 + w^2
        //
        return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
    }

    /// <summary>
    /// Calculates the squared quaternion's length, this means, the squared components sum. This method
    /// exists due to performance reasons because it avoids to perform square roots when the result is
    /// going to be squared.
    /// </summary>
    /// <returns>
    /// The resultant squared length.
    /// </returns>
    inline float_q GetSquaredLength() const
    {
        //                    ______________________
        // squared length = (V x^2 + y^2 + z^2 + w^2)^2
        //
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
    }

    /// <summary>
    /// Obtains the angle of rotation and the spin axis contained in the resident quaternion.
	/// There are two possible singularities: when rotation angle is 0 or 180º.
    /// </summary>
    /// <param name="vAxis">Vector to store the spin axis.</param>
    /// <param name="fAngle">Angle of rotation.</param>
	void ToAxisAngle(QBaseVector3 &vAxis, float_q &fAngle) const;

    /// <summary>
    /// Obtains the angle of rotation and the spin axis contained in the resident quaternion.
	/// There are two possible singularities: when rotation angle is 0 or 180º.
    /// </summary>
    /// <param name="vAxis">Vector to store the spin axis.</param>
    /// <param name="fAngle">Angle of rotation.</param>
	void ToAxisAngle(QBaseVector4 &vAxis, float_q &fAngle) const;

	/// <summary>
    /// Gets a character string that represents the quaternion values.
    /// </summary>
    /// <returns>
    /// A character string, following this pattern: "Q( x, y, z, w)".
    /// </returns>
    inline string_q ToString() const
	{
		return QE_L("Q(") + QFloat::ToString(this->x) +
			   QE_L(", ") + QFloat::ToString(this->y) +
			   QE_L(", ") + QFloat::ToString(this->z) +
			   QE_L(", ") + QFloat::ToString(this->w) + QE_L(")");
	}


};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QQUATERNION__
