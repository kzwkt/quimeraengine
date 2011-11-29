// [TERMS&CONDITIONS]

#ifndef __QTRIANGLE__
#define __QTRIANGLE__

#include "QBaseTriangle.h"

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
/// Class which represents a triangle in the space. The triangle may be represented in 2D or 3D,
///	and using points or vectors, depending on the parameter of the template, which may be
///	2D vector, 3D vector or 4D vector.
/// </summary>
template <class VectorType>
class QDllExport QTriangle : public QBaseTriangle<VectorType>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QBaseTriangle<VectorType>::A;
    using QBaseTriangle<VectorType>::B;
    using QBaseTriangle<VectorType>::C;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QTriangle() { }

	/// <summary>
	/// Constructor from three vectors, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] Vector to define vertex A.</param>
	/// <param name="vB">[IN] Vector to define vertex B.</param>
	/// <param name="vC">[IN] Vector to define vertex C.</param>
	inline QTriangle(const VectorType &vA, const VectorType &vB, const VectorType &vC) : QBaseTriangle<VectorType>(vA, vB, vC) { }

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex.
	/// </summary>
	/// <param name="pValueA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="pValueB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="pValueC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QTriangle(const float_q *pValueA, const float_q *pValueB, const float_q *pValueC) : QBaseTriangle<VectorType>(pValueA, pValueB, pValueC) { }

	/// <summary>
	/// Constructor from three V4x32-FLOAT, one for each vertex.
	/// </summary>
	/// <param name="vfValueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="vfValueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="vfValueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QTriangle(const vf32_q &vfValueA, const vf32_q &vfValueB, const vf32_q &vfValueC) : QBaseTriangle<VectorType>(vfValueA, vfValueB, vfValueC) { }

	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator. Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="btValue">[IN] QBaseTriangle that will be assigned to current triangle.</param>
	inline QTriangle<VectorType> & operator=(const QBaseTriangle<VectorType> & btValue)
	{
        QBaseTriangle<VectorType>::operator=(btValue);
        return *this;
	}

	/// <summary>
	/// Equality Operator. Checks if the triangle recieved in the parameter is equal to the current triangle.
	/// </summary>
	/// <param name="btValue">[IN] QBaseTriangle to compare with current triangle.</param>
	inline bool operator==(const QBaseTriangle<VectorType> & btValue) const
	{
		return (this->A == btValue.A) && (this->B == btValue.B) && (this->C == btValue.C);
	}

	/// <summary>
	/// Calculates the triangle surface.
	/// </summary>
    /// <returns>
    /// The surface of the triangle in a float point type.
    /// </returns>
	float_q GetSurface() const
	{
		VectorType u = B - A;
		VectorType v = C - A;

		float_q fLengthU = u.GetLength();
		float_q fLengthV = v.GetLength();

		float_q fDotProduct = u.DotProduct(v);

		return (sqrt((fLengthU * fLengthU) * (fLengthV * fLengthV) - (fDotProduct * fDotProduct)) / SQFloat::_2);
	}

	/// <summary>
	/// Calculates the angle formed by edges AB and AC.
	/// </summary>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
	inline float_q GetAngleA() const
	{
		VectorType u = B - A;
		VectorType v = C - A;

		return GetAngle(u, v);
	}

	/// <summary>
	/// Calculates the angle formed by edges BA and BC.
	/// </summary>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
	inline float_q GetAngleB() const
	{
		VectorType u = A - B;
		VectorType v = C - B;

		return GetAngle(u, v);
	}

	/// <summary>
	/// Calculates the angle formed by edges CB and CA.
	/// </summary>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
	inline float_q GetAngleC() const
	{
		VectorType u = A - C;
		VectorType v = B - C;

		return GetAngle(u, v);
	}

	/// [TODO] Txaneto: void GetCircumcenter(VectorType & vValue) - Public method that calculates the circumcenter of the triangle. (Intersection point of the medians)

	/// [TODO] Txaneto: void GetOrthocenter(VectorType & vValue) - Public method that calculates the orthocenter of the triangle. (Intersection point of the heights)

	/// <summary>
	/// Calculates the incenter of the triangle.
	/// </summary>
	/// <param name="vValue">[OUT] VectorType that stores the resultant point.</param>
	void GetIncenter(VectorType & vValue) const
	{
		VectorType vtSideA = C - B;
		VectorType vtSideB = A - C;
		VectorType vtSideC = B - A;

		float_q fLengthA = vtSideA.GetLength();
		float_q fLengthB = vtSideB.GetLength();
		float_q fLengthC = vtSideC.GetLength();

		float_q fP = fLengthA + fLengthB + fLengthC;

		// Checkout to avoid division by zero.
		QE_ASSERT(fP != SQFloat::_0);

		vValue = (fLengthA * A + fLengthB * B + fLengthC * C) / fP;
	}

	/// <summary>
	/// Calculates the centroid of the triangle.
	/// </summary>
	/// <param name="vValue">[OUT] VectorType that stores the resultant point.</param>
	inline void GetCentroid(VectorType & vValue) const
	{
		vValue = (A + B + C) / SQFloat::_3;
	}

	/// <summary>
	/// Converts triangle into a string with the following format:
	/// "T:A(<A.ToString>), B(<B.ToString>), C(<C.ToString>)"
	/// </summary>
	/// <returns>
	/// The string in the specified format.
	/// </returns>
	string_q ToString()
	{
		return QE_L("T:A(") + A.ToString() + QE_L("), B(") + B.ToString() + QE_L("), C(") + C.ToString() + QE_L(")");
	}

protected:

	/// <summary>
	/// Calculates the angle between two vector types.
	/// </summary>
	/// <param name="vtU">[IN] The first vector type.</param>
	/// <param name="vtV">[IN] The second vector type.</param>
	/// <returns>
	/// The angle in a float point type.
	/// </returns>
	inline float_q GetAngle(const VectorType vtU, const VectorType vtV) const
	{
		float_q fLengthU = vtU.GetLength();
		float_q fLengthV = vtV.GetLength();

		// Checkout to avoid division by zero.
		QE_ASSERT(fLengthU != SQFloat::_0);
		QE_ASSERT(fLengthV != SQFloat::_0);

		float_q fCos = vtU.DotProduct(vtV) / (fLengthU * fLengthV);

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(SQFloat::Abs(fCos) <= SQFloat::_1);

		float_q fAngle = acos(fCos);

        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            fAngle = SQAngle::RadiansToDegrees(fAngle, fAngle);
        #endif

		return fAngle;
	}

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTriangle__
