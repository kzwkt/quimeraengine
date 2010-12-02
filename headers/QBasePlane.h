// [TERMS&CONDITIONS]

#ifndef __QBASEPLANE__
#define __QBASEPLANE__

#include "QFloat.h"
#include "QVF32.h"

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
/// It represents the basic form of a 3D plane, defined by the equation ax + by + cz + d = 0. 
/// We can see that the vector (a, b, c) is normal to the plane, and d represents the sorthest distance from plane to the origin.
/// </summary>
class QDllExport QBasePlane
{
    // CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QBasePlane() : a(QFloat::_0), b(QFloat::_0), c(QFloat::_0), d(QFloat::_0) { }

	/// <summary>
	/// Constructor from a floating point value for each coefficient.
	/// </summary>
	/// <param name="fA">[IN] Floating point value for a coefficient.</param>
	/// <param name="fB">[IN] Floating point value for b coefficient.</param>
	/// <param name="fC">[IN] Floating point value for c coefficient.</param>
	/// <param name="fD">[IN] Floating point value for independent term d.</param>
	inline QBasePlane(float_q fA, float_q fB, float_q fC, float_q fD) : a(fA), b(fB), c(fC), d(fD) { }

	/// <summary>
	/// Constructor from a floating point value for all coefficients.
	/// </summary>
	/// <param name="fValue">[IN] Floating point value.</param>
	inline explicit QBasePlane(float_q fValue) : a(fValue), b(fValue), c(fValue), d(fValue) { }

	/// <summary>
	/// Constructor from a pointer to a array of floating point values.
	/// </summary>
	/// <param name="pValue">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
	inline explicit QBasePlane(float_q *pValue) 
	{
		// Null pointer checkout
		QE_ASSERT(pValue != null_q);

		// Assignments
		this->a = pValue[0]; 
		this->b = pValue[1]; 
		this->c = pValue[2];
		this->d = pValue[3];
	}

	/// <summary>
	/// Constructor from a 4x32 packed float value.
	/// </summary>
	/// <param name="fValue">[IN] 4x32 packed float containing the four components.
	/// The parse order: 1st value (a coefficient), 2nd value (b coefficient), 
	/// 3rd value (c coefficient), 4th value (d independent term).</param>
	inline explicit QBasePlane(const vf32_q fValue)
	{ 
		QVF32::Unpack(fValue, this->a, this->b, this->c, this->d);
	}

	// ATTRIBUTES
	// ---------------
public:


	/// <summary>
	/// X coefficient of the plane equation.
	/// </summary>
	float_q a;

	/// <summary>
	/// Y coefficient of the plane equation.
	/// </summary>
	float_q b;

	/// <summary>
	/// Z coefficient of the plane equation.
	/// </summary>
	float_q c;

	/// <summary>
	/// Independent term of the plane equation.
	/// </summary>
	float_q d;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEPLANE__
