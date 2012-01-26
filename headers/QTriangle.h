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
/// Class which represents a triangle in the space.<br>
/// The triangle may be represented in 2D or 3D,
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
	inline QTriangle()
    {
    }

	/// <summary>
	/// Constructor from three vectors, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] Vector to define vertex A.</param>
	/// <param name="vB">[IN] Vector to define vertex B.</param>
	/// <param name="vC">[IN] Vector to define vertex C.</param>
	inline QTriangle(const VectorType &vA, const VectorType &vB, const VectorType &vC) : QBaseTriangle<VectorType>(vA, vB, vC)
    {
    }

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex.
	/// </summary>
	/// <param name="arValuesA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="arValuesB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="arValuesC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QTriangle(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC) :
                         QBaseTriangle<VectorType>(arValuesA, arValuesB, arValuesC)
    {
    }

	/// <summary>
	/// Constructor from three 4x32 packed floating point values, one for each vertex.
	/// </summary>
	/// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QTriangle(const vf32_q &valueA, const vf32_q &valueB, const vf32_q &valueC) : QBaseTriangle<VectorType>(valueA, valueB, valueC)
    {
    }

	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator.<br>
	/// Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="triangle">[IN] Triangle that will be assigned to current triangle.</param>
	inline QTriangle<VectorType>& operator=(const QBaseTriangle<VectorType> &triangle)
	{
        QBaseTriangle<VectorType>::operator=(triangle);
        return *this;
	}

	/// <summary>
	/// Equality Operator.<br>
	/// Checks if the triangle recieved in the parameter is equal to the current triangle.
	/// </summary>
	/// <param name="triangle">[IN] Triangle to compare with current triangle.</param>
	bool operator==(const QBaseTriangle<VectorType> &triangle) const
	{
		return (this->A == triangle.A) && (this->B == triangle.B) && (this->C == triangle.C);
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

		return (sqrt_q((fLengthU * fLengthU) * (fLengthV * fLengthV) - (fDotProduct * fDotProduct)) * SQFloat::_0_5);
	}

	/// <summary>
	/// Calculates the angle formed by edges AB and AC.
	/// </summary>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
	float_q GetAngleA() const
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
	float_q GetAngleB() const
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
	float_q GetAngleC() const
	{
		VectorType u = A - C;
		VectorType v = B - C;

		return GetAngle(u, v);
	}

	/// <summary>
	/// Calculates the incenter of the triangle.
	/// </summary>
	/// <param name="vIncenter">[OUT] Vector that stores the resultant point.</param>
	void GetIncenter(VectorType & vIncenter) const
	{
		VectorType vtSideA = C - B;
		VectorType vtSideB = A - C;
		VectorType vtSideC = B - A;

		float_q fLengthA = vtSideA.GetLength();
		float_q fLengthB = vtSideB.GetLength();
		float_q fLengthC = vtSideC.GetLength();

		float_q fP = fLengthA + fLengthB + fLengthC;

		// Checkout to avoid division by zero.
		QE_ASSERT(fP != SQFloat::_0)

		vIncenter = (fLengthA * A + fLengthB * B + fLengthC * C) / fP;
	}

	/// <summary>
	/// Calculates the centroid of the triangle.
	/// </summary>
	/// <param name="vCentroid">[OUT] VectorType that stores the resultant point.</param>
	inline void GetCentroid(VectorType & vCentroid) const
	{
		vCentroid = (A + B + C) / SQFloat::_3;
	}

	/// <summary>
	/// Converts triangle into a string with the following format:<br>
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

	// <summary>
	// Calculates the angle between two vector types.
	// </summary>
	// <param name="vVector1">[IN] The first vector type.</param>
	// <param name="vVector2">[IN] The second vector type.</param>
	// <returns>
	// The angle in a float point type.
	// </returns>
	float_q GetAngle(const VectorType vVector1, const VectorType vVector2) const
	{
		float_q fLength1 = vVector1.GetLength();
		float_q fLength2 = vVector2.GetLength();

		// Checkout to avoid division by zero.
		QE_ASSERT(fLength1 != SQFloat::_0)
		QE_ASSERT(fLength2 != SQFloat::_0)

		float_q fCos = vVector1.DotProduct(vVector2) / (fLength1 * fLength2);

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(SQFloat::Abs(fCos) <= SQFloat::_1)

		float_q fAngle = acos_q(fCos);

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
