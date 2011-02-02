// [TERMS&CONDITIONS]

#ifndef __QDUALQUATERNION__
#define __QDUALQUATERNION__

#include "QBaseDualQuaternion.h"

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
class QBaseVector3;
class QBaseVector4;


/// <summary>
/// Class which implements the basic functionality of a dual quaternion. 
/// A dual quaternion is a complex number with two components, a non-dual component and a dual one, e.g. \f$ r + d\varepsilon \f$. 
/// Both components (r and d) of a dual quaternion are (regular) quaternions.
/// The dual unit, called epsilon (\f$ \varepsilon \f$), verifies \f$ \varepsilon^2=0 \f$. Then, a full quaternion looks like:
/// \f$ r_w + r_xi + r_yj + r_zk + (d_w + d_xi + d_yj + d_zk)\varepsilon\f$
/// We'll normally employ it to represent and execute rigid transformations, that is, transformations which involves
/// one rotation and one translation, without deforming the transformed solid (which acts as a rigid solid).
/// </summary>
class QDllExport QDualQuaternion : public QBaseDualQuaternion
{
    // FRIENDS
    // ---------------
public:

    /// <summary>
    /// Multiply by scalar operator. All dual quaternion components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar factor.</param>
    /// <param name="dqQuat">[IN] The dual quaternion factor.</param>
    /// <returns>
    /// The resultant dual quaternion.
    /// </returns>
    friend QDualQuaternion operator*(const float_q &fScalar, const QBaseDualQuaternion &dqQuat);


    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Represents the identity dual quaternion. It's (0,0,0,1) (0,0,0,0).
    /// </summary>
    static const QDualQuaternion Identity;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    inline QDualQuaternion() : QBaseDualQuaternion() { }

    /// <summary>
    /// Constructor that receives a base dual quaternion.
    /// </summary>
    /// <param name="dqQuat">[IN] A base dual quaternion.</param>
    inline explicit QDualQuaternion(const QBaseDualQuaternion &dqQuat) : QBaseDualQuaternion(dqQuat) { };

    /// <summary>
    /// Constructor from two regular quaternions.
    /// </summary>
    /// <param name="qR">[IN] Regular quaternion to define non-dual part.</param>
    /// <param name="qD">[IN] Regular quaternion to define dual part.</param>
    inline QDualQuaternion(const QBaseQuaternion &qR, const QBaseQuaternion &qD) : QBaseDualQuaternion(qR, qD) { }

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$, 
    /// and the dual quaternion will be:
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:
    /// \f$\hat{q}_d = (0, 0, 0, 1) (d_x, d_y, d_z, 0)\f$.
    /// Our transformation dual quaternion is given by the product of the translation dual quaternion by
    /// the rotation dual quaternion, taking into account that the transfomation is done as follows:
    /// FIRST ROTATION THEN TRANSLATION.
    /// </summary>
    /// <param name="qR">[IN] The quaternion that keeps the rotation.</param>
    /// <param name="vD">[IN] The vector which represents the translation. It must be a QBaseVector3, a QBaseVector4 or its descendants.</param>
    template <class VectorType> 
    QDualQuaternion(const QBaseQuaternion &qR, const VectorType &vD)
    { 
        QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
        QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                             QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

        *this = Desp * Rot;
    }

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$, 
    /// and the dual quaternion will be:
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:
    /// \f$\hat{q}_d = (0, 0, 0, 1) (d_x, d_y, d_z, 0)\f$.
    /// Our transformation dual quaternion is given by the product of the rotation dual quaternion by
    /// the translation dual quaternion, taking into account that the transfomation is done as follows:
    /// FIRST TRANSLATION THEN ROTATION.
    /// </summary>
    /// <param name="qR">[IN] The quaternion that keeps the rotation.</param>
    /// <param name="vD">[IN] The vector which represents the translation. It must be a QBaseVector3, a QBaseVector4 or its descendants.</param>
    template <class VectorType>
    QDualQuaternion(const VectorType &vD, const QBaseQuaternion &qR)
    { 
        QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
        QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                    QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

        *this = Rot * Desp;
    }

    /// <summary>
    /// Constructor from two four components arrays of floating point values, one for each quaternion component.
    /// </summary>
    /// <param name="pQuatR">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
    /// <param name="pQuatD">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
    inline QDualQuaternion(const float_q *pQuatR, const float_q *pQuatD) 
    {
        QE_ASSERT(pQuatR != null_q && pQuatD != null_q);

        this->r = QQuaternion(pQuatR[0], pQuatR[1], pQuatR[2], pQuatR[3]);
        this->d = QQuaternion(pQuatD[0], pQuatD[1], pQuatD[2], pQuatD[3]);
    }


	// METHODS
	// ---------------
public:
    // binary operators

    /// <summary>
    /// Dual quaternions addition: it's performed component by component.
    /// </summary>
    /// <param name="dqQuat">[IN] Adding dual quaternion.</param>
    /// <returns>
    /// A dual quaternion that is the result of the addition.
    /// </returns>
    QDualQuaternion operator + (const QBaseDualQuaternion &dqQuat) const;

    /// <summary>
    /// Dual quaternions subtraction: it's performed component by component.
    /// </summary>
    /// <param name="dqQuat">[IN] Subtracting dual quaternion.</param>
    /// <returns>
    /// A dual quaternion that is the result of the subtraction.
    /// </returns>
    QDualQuaternion operator - (const QBaseDualQuaternion &dqQuat) const;

    /// <summary>
    /// Dual quaternions product: it's performed as follows:
    /// \f$ q\cdot q' = r\cdot r' + (r\cdot d' + r'\cdot d)\varepsilon\f$
    /// </summary>
    /// <param name="dqQuat">[IN] Multiplying dual quaternion.</param>
    /// <returns>
    /// A dual quaternion that is the result of the product.
    /// </returns>
    QDualQuaternion operator * (const QBaseDualQuaternion &dqQuat) const;

    /// <summary>
    /// Multiply by scalar operator. Both quaternion components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant dual quaternion.
    /// </returns>
    QDualQuaternion operator*(const float_q &fScalar) const;

    /// <summary>
    /// Product by a vector (multiplying to the dual quaternion by the right). The vector is transformed into a dual quaternion, 
    /// then is multiplied by the resident dual quaternion by the left and transformed back to a vector.
    /// If vector is \f$ \vec{v}=(x, y, z)\f$, it's transformed into \f$ \hat{Q}=(0, 0, 0, 1)(x, y, z, 0)\f$.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QDualQuaternion operator * (const QBaseVector3 &v) const;

    /// <summary>
    /// Product by a vector (multiplying to the dual quaternion by the right). The vector is transformed into a dual quaternion, 
    /// then is multiplied by the resident dual quaternion by the left and transformed back to a vector.
    /// If vector is \f$ \vec{v}=(x, y, z)\f$, it's transformed into \f$ \hat{Q}=(0, 0, 0, 1)(x, y, z, 0)\f$.
    /// </summary>
    /// <param name="v">[IN] Multiplying vector.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    QDualQuaternion operator * (const QBaseVector4 &v) const;

    /// <summary>
    /// Divide by scalar operator. Both quaternion components are divided by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by.</param>
    /// <returns>
    /// The resultant dual quaternion.
    /// </returns>
    QDualQuaternion operator/(const float_q &fScalar) const;

    /// <summary>
    /// Add and assign operator. Each input quaternion component is added to the corresponding quaternion 
    /// of the resident dual quaternion.
    /// </summary>
    /// <param name="dqQuat">[IN] The dual quaternion that is Added.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    inline QDualQuaternion& operator+=(const QBaseDualQuaternion &dqQuat)
    {
        this->r += dqQuat.r;
        this->d += dqQuat.d;
        
        return *this;
    }

    /// <summary>
    /// Subtract and assign operator. Each input quaternion component is subtracted to the corresponding quaternion
    /// of the resident dual quaternion.
    /// </summary>
    /// <param name="dqQuat">[IN] The dual quaternion that is subtracted.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    inline QDualQuaternion& operator-=(const QBaseDualQuaternion &dqQuat)
    {
        this->r -= dqQuat.r;
        this->d -= dqQuat.d;

        return *this;
    }

    /// <summary>
    /// Multiply and assign operator. The resident dual quaternion is multiplied by the input one.
    /// This is calculated as follows:
    /// \f$ q\cdot q' = r\cdot r' + (r\cdot d' + r'\cdot d)\varepsilon\f$ 
    /// Note that quaternion multiplication is not conmutative.
    /// </summary>
    /// <param name="dqQuat">[IN] The dual quaternion to multiply by.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    inline QDualQuaternion& operator*=(const QBaseDualQuaternion &dqQuat)
    {
        QDualQuaternion aux(*this);

        this->r = aux.r * dqQuat.r;
        this->d = aux.r * dqQuat.d + dqQuat.r * aux.d;
    
        return *this;
    }

    /// <summary>
    /// Multiply by a floating point value and assign operator. Each dual quaternion component is 
    /// multiplied by the input floating point value.
    /// </summary>
    /// <param name="fValue">[IN] The floating point value to multiply by.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    inline QDualQuaternion& operator*=(const float_q fValue)
    {
        this->r *= fValue;
        this->d *= fValue;

        return *this;
    }

    /// <summary>
    /// Divide and assign operator. Each dual quaternion component is divided by the input floating point value.
    /// </summary>
    /// <param name="fValue">[IN] The floating point value to divide by.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    inline QDualQuaternion& operator/=(const float_q fValue)
    {
        // Checkout to avoid division by zero.
        QE_ASSERT(fValue != QFloat::_0);

        this->r /= fValue;
        this->d /= fValue;

        return *this;
    }

    /// <summary>
    /// Equal operator. Compares component by component.
    /// </summary>
    /// <param name="dqQuat">[IN] The dual quaternion to compare to.</param>
    /// <returns>
    /// If dual quaternions are equal, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseDualQuaternion &dqQuat) const
    {
        return this->r == dqQuat.r && this->d == dqQuat.d;
    }

    /// <summary>
    /// Non-equal operator. Compares component by component.
    /// </summary>
    /// <param name="dqQuat">[IN] The quaternion to compare to.</param>
    /// <returns>
    /// If quaternions are not equal, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseDualQuaternion &dqQuat) const
    {
        return this->r != dqQuat.r || this->d != dqQuat.d;
    }

    /// <summary>
    /// Resets to zero all components of both quaternions of the dual quaternion.
    /// </summary>
    inline void ResetToZero () 
    {
        this->r.ResetToZero();
        this->d.ResetToZero();
    }

    /// <summary>
    /// Resets to identity the dual quaternion. This implies that de non-dual component is reset to identity
    /// and de dual component is reset to zero.
    /// </summary>
    inline void ResetToIdentity () 
    {
        this->r.ResetToIdentity();
        this->d.ResetToZero();
    }

    /// <summary>
    /// Calculates the SINGLE dual quaternion's conjugate. It's calculated this way: \f$ Q^* = r^* + d^*\varepsilon\f$ .
    /// </summary>
    inline void Conjugate()
    {
        this->r.Conjugate();
        this->d.Conjugate();
    }

    /// <summary>
    /// Gets a SINGLE conjugated dual quaternion copy. It's calculated this way: \f$ Q^* = r^* + d^*\varepsilon\f$.
    /// </summary>
    /// <param name="dqOut">[OUT] The conjugated dual quaternion copy.</param>
    inline void Conjugate(QBaseDualQuaternion &dqOut) const
    {
        this->r.Conjugate(dqOut.r);
        this->d.Conjugate(dqOut.d);
    }

    /// <summary>
    /// Calculates the DOUBLE dual quaternion's conjugate. It's calculated this way: \f$ Q^* = r^* - d^*\varepsilon\f$.
    /// </summary>
    inline void DoubleConjugate()
    {
        this->Conjugate();
        this->d *= -QFloat::_1;
    }

    /// <summary>
    /// Gets a DOUBLE conjugated dual quaternion copy. It's calculated this way: \f$ Q^* = r^* - d^*\varepsilon\f$.
    /// </summary>
    /// <param name="dqOut">[OUT] The conjugated dual quaternion copy.</param>
    inline void DoubleConjugate(QBaseDualQuaternion &dqOut) const
    {
        this->Conjugate(dqOut);
        dqOut.d *= -QFloat::_1;
    }

    /// <summary>
    /// Calculates the length of the non-dual part of the resident dual quaternion. It is used to normalize
    /// an interpolated transformation. See Lerp method for further information.
    /// </summary>
    /// <returns>
    /// A floating point value that is the length of the non-dual part of the dual quaternion.
    /// </returns>
    inline float_q GetNonDualLength() const
    {
        return this->r.GetLength();
    }

    /// <summary>
    /// Applies a transformation to the resident dual quaternion. The transformation is performed as follows:
    ///     \f$ P' = T \cdot P \cdot T^*\f$, where 
    ///     \f$ P'\f$: Transformed dual quaternion.
    ///     \f$ T \f$: Transformation applied.
    ///     \f$ P \f$: Dual quaternion which is transformed.
    ///     \f$ T^*\f$: Double conjugate of the transformation.
    /// </summary>
    /// <param name="dqTransf">[IN] Transformation to be applied.</param>
    void Transform(const QBaseDualQuaternion &dqTransf);

    /// <summary>
    /// Makes a transformed copy of the resident dual quaternion. The transformation is performed as follows:
    ///     \f$ P' = T \cdot P \cdot T^*\f$, where 
    ///     \f$ P'\f$: Transformed dual quaternion.
    ///     \f$ T \f$: Transformation applied.
    ///     \f$ P \f$: Dual quaternion which is transformed.
    ///     \f$ T^*\f$: Double conjugate of the transformation.
    /// </summary>
    /// <param name="dqTransf">[IN] Transformation to be applied.</param>
    /// <param name="dqOut">[OUT] Dual quaternion where the result of transformation is stored.</param>
    void Transform(const QBaseDualQuaternion &dqTransf, QBaseDualQuaternion &dqOut) const;

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the rotation first and then the traslation.
    /// </summary>
    /// <param name="qR">[IN] Regular quaternion which defines the rotation.</param>
    /// <param name="vD">[IN] Vector which defines the translation. It must be a QBaseVector3, a QBaseVector4 or its descendants.</param>
    template <class VectorType>
    void TransformRotationFirst(const QBaseQuaternion &qR, const VectorType &vD)
    { 
        QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
        QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                    QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

        QDualQuaternion dqTransf = Desp * Rot;

        this->Transform(dqTransf);
    }

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the traslation first and then the rotation.
    /// </summary>
    /// <param name="vD">[IN] Vector which defines the translation. It must be a QBaseVector3, a QBaseVector4 or its descendants.</param>
    /// <param name="qR">[IN] Regular quaternion which defines the rotation.</param>
    template <class VectorType>
    void TransformTranslationFirst(const VectorType &vD, const QBaseQuaternion &qR)
    { 
        QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
        QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                    QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

        QDualQuaternion dqTransf = Rot * Desp;

        this->Transform(dqTransf);
    }

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the rotation first and then the traslation.
    /// </summary>
    /// <param name="qR">[IN] Regular quaternion which defines the rotation.</param>
    /// <param name="vD">[IN] Vector which defines the translation. It must be a QBaseVector3, a QBaseVector4 or its descendants.</param>
    /// <param name="dqOut">[OUT] Dual quaternion where the result of transformation is stored.</param>
    template <class VectorType>
    void TransformRotationFirst(const QBaseQuaternion &qR, const VectorType &vD, QBaseDualQuaternion &dqOut) const
    { 
        QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
        QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                    QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

        QDualQuaternion dqTransf = Desp * Rot;

        this->Transform(dqTransf, dqOut);
    }

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the traslation first and then the rotation.
    /// </summary>
    /// <param name="vD">[IN] Vector which defines the translation. It must be a QBaseVector3, a QBaseVector4 or its descendants.</param>
    /// <param name="qR">[IN] Regular quaternion which defines the rotation.</param>
    /// <param name="dqOut">[OUT] Dual quaternion where the result of transformation is stored.</param>
    template <class VectorType>
    void TransformTranslationFirst(const VectorType &vD, const QBaseQuaternion &qR, QBaseDualQuaternion &dqOut) const
    { 
        QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
        QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                    QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

        QDualQuaternion dqTransf = Rot * Desp;

        this->Transform(dqTransf, dqOut);
    }

    /// <summary>
    /// Converts resident dual quaternion, assuming it's a transformation, in a new transformation which is
    /// a linear interpolation between it and a transformation provided, by a proportion also provided.
    /// Note that this isn't an interpolation between dual quaternions, only between unitary dual quaternions 
    /// which contains transformations. To take the transformed point or vector interpolating from a transformation, 
    /// its necessary to apply the resultant transformation of the lerp to the original point or vector, 
    /// obtaining a point or vector in a status of transformation given by the proportion used.
    /// Lerp is obtained as follows: if Q1 is the original transformation, and Q2 is the transformation provided,
    /// the transformation Q' which give us the status of any point at a proportion t in [0, 1] is
    ///
    /// \f$ \hat{Q} (t) = \frac{(1 - t)\hat{Q}_1 + t  \hat{Q}_2}{\left|(1 - t)\hat{Q}_1 + t  \hat{Q}_2\right|} \f$
    ///
    /// Where Q'(0) = Q1 (first transformation); Q'(1) = Q2 (second transformation).
    /// </summary>
    /// <param name="fProp">[IN] Proportion with we want to calculate the interpolation.</param>
    /// <param name="dqQ2">[IN] The other transformation implied in the interpolation.</param>
    inline void Lerp(const float_q &fProp, const QBaseDualQuaternion &dqQ2)
    {
        *this *= (1 - fProp);
        this->r += fProp * dqQ2.r;
        this->d += fProp * dqQ2.d;

        float_q fLength = this->GetNonDualLength();
        
        QE_ASSERT(fLength != QFloat::_0);
        
        *this /= fLength;
    }

    /// <summary>
    /// Calculates from resident dual quaternion, assuming it's a transformation, a new transformation which is
    /// a linear interpolation between it and a transformation provided, by a proportion also provided.
    /// Note that this isn't an interpolation between dual quaternions, only between unitary dual quaternions 
    /// which contains transformations. To take the transformed point or vector interpolating from a transformation, 
    /// its necessary to apply the resultant transformation of the lerp to the original point or vector, 
    /// obtaining a point or vector in a status of transformation given by the proportion used.
    /// Lerp is obtained as follows: if Q1 is the original transformation, and Q2 is the transformation provided,
    /// the transformation Q' which give us the status of any point at a proportion t in [0, 1] is
    ///
    /// \f$ \hat{Q} (t) = \frac{(1 - t)\hat{Q}_1 + t  \hat{Q}_2}{\left|(1 - t)\hat{Q}_1 + t  \hat{Q}_2\right|} \f$
    ///
    /// Where Q'(0) = Q1 (first transformation); Q'(1) = Q2 (second transformation).
    /// </summary>
    /// <param name="fProp">[IN] Proportion with we want to calculate the interpolation.</param>
    /// <param name="dqQ2">[IN] The other transformation implied in the interpolation.</param>
    /// <param name="dqOut">[OUT] The dual quaternion where we want store the result of interpolation.</param>
    inline void Lerp(const float_q &fProp, const QBaseDualQuaternion &dqQ2, QBaseDualQuaternion &dqOut)
    {
  	    
        dqOut = *this * (1-fProp);
        dqOut.r += fProp * dqQ2.r;
        dqOut.d += fProp * dqQ2.d;

        float_q fLength = static_cast<QDualQuaternion>(dqOut).GetNonDualLength();

        QE_ASSERT(fLength != QFloat::_0);

        dqOut.r /= fLength;
        dqOut.d /= fLength;
    }

    /// <summary>
    /// Converts dual quaternion into a string with the following format:
    /// "DQ(rX, rY, rZ, rW)(dX, dY, dZ, dW)".
    /// </summary>
    /// <returns>The std::string with the format specified.</returns>
    string_q ToString() const;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QDUALQUATERNION__
