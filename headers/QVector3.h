// [TERMS&CONDITIONS]

#ifndef __QVECTOR3__
#define __QVECTOR3__

#include "QFloat.h"
#include "QBaseVector3.h"

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
/// This class implements three components vector functionality. It inherits from QBaseVector3.
///	A vector is a geometric object that has both a magnitude (or length) and direction. 
///	It is frequently represented by a line segment with a definite direction, or graphically as an arrow, 
///	connecting an initial point A with a terminal point B. The vector is then denoted by AB with a arrow hat.
/// </summary>
class QDllExport QVector3 : public QBaseVector3
{
   
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QVector3() : QBaseVector3() { }

	/// <summary>
	/// Constructor from a QBaseVector3.
	/// </summary>
	/// <param name="v">[IN] The QBaseVector3 in which we want QVector3 to be based.</param>
	inline explicit QVector3(const QBaseVector3 &v) : QBaseVector3(v) { }

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
	/// <param name="fPackComps">[IN] 4x32 packed floating point value containing the three components.</param>
	inline QVector3(const vf32_q &fPackComps) : QBaseVector3 (fPackComps) { }

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
	QVector3 operator + (const QVector3 &v) const;

	/// <summary>
	/// Vectors subtraction: it's performed component by component.
	/// </summary>
	/// <param name="v">[IN] Subtracting vector.</param>
	/// <returns>
	/// A vector that is the result of the subtraction.
	/// </returns>
	QVector3 operator - (const QVector3 &v) const;

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
	
	/// <summary>
	/// Product by a scalar: all components are multiplied by the floating point value provided.
	/// Shorcut to multiply on the left.
	/// </summary>
	/// <param name="fValue">[IN] Multiplying floating point value.</param>
	/// <param name="v">[IN] Vector to be multiplied.</param>
	/// <returns>
	/// A vector that is the result of the product.
	/// </returns>
	friend QVector3 operator * (const float_q &fValue, const QVector3 &v);

	/// <summary>
	/// Compares two vectors.
	/// </summary>
	/// <param name="v">[IN] Vector with which to compare.</param>
	/// <returns>
	/// True if vectors are the same, false otherwise.
	/// </returns>
	inline bool operator == (const QBaseVector3 &v) const
	{
        return ( QFloat::AreEquals(v.x, this->x) && QFloat::AreEquals(v.y, this->y) && QFloat::AreEquals(v.z, this->z) );
	}

	/// <summary>
	/// Compares two vectors.
	/// </summary>
	/// <param name="v">[IN] Vector with which to compare.</param>
	/// <returns>
	/// True if vectors are not the same, false otherwise.
	/// </returns>
    inline bool operator != (const QBaseVector3 &v) const
	{
        return QFloat::AreNotEquals(v.x, this->x) || QFloat::AreNotEquals(v.y, this->y) || QFloat::AreNotEquals(v.z, this->z);
	}

	// assignment operators

	/// <summary>
	/// Adds a vector provided to current vector.
	/// </summary>
	/// <param name="v">[IN] Adding vector.</param>
	/// <returns>
	/// A reference to vector result of the addition.
	/// </returns>
	inline QVector3& operator += (const QVector3 &v) 
	{ 
		this->x += v.x;
		this->y += v.y;
		this->z += v.z; 
		
		return *this; 
	}

	/// <summary>
	/// Subtracts a vector provided to current vector.
	/// </summary>
	/// <param name="v">[IN] Subtracting vector.</param>
	/// <returns>
	/// A reference to vector result of the subtraction.
	/// </returns>
	inline QVector3& operator -= (const QVector3 &v) 
	{ 
		this->x -= v.x; 
		this->y -= v.y; 
		this->z -= v.z; 
		
		return *this; 
	}

	/// <summary>
	/// Multiplies current vector by a floating point value provided.
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
	/// Multiplies current vector by a vector provided. It's performed component by component. It's not dot product or cross product!
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
	/// Divides current vector by a floating point value provided.
	/// </summary>
	/// <param name="fValue">[IN] Dividing floating point value.</param>
	/// <returns>
	/// A reference to vector result of the division.
	/// </returns>
	inline QVector3& operator /= (const float_q &fValue) 
	{ 
		// Checkout to avoid division by 0
		QE_ASSERT(fValue);

		this->x /= fValue; 
		this->y /= fValue; 
		this->z /= fValue; 
		
		return *this; 
	}
	
	/// <summary>
	/// Divides current vector by a vector provided. It's performed component by component.
	/// </summary>
	/// <param name="v">[IN] Dividing vector.</param>
	/// <returns>
	/// A reference to vector result of the division.
	/// </returns>
	inline QVector3& operator /= (const QBaseVector3 &v)
	{
		// Checkout to avoid division by 0
		QE_ASSERT (v.x && v.y && v.z);

		this->x /= v.x; 
		this->y /= v.y; 
		this->z /= v.z; 
		
		return *this;
	}
	
	//Methods

	/// <summary>
	/// Calculates the length of current vector.
	/// </summary>
	/// <returns>
	/// A floating point value which is the length of the vector.
	/// </returns>
	inline float_q GetLength() 
	{ 
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z); 
	}


	/// <summary>
	/// Makes current vector unitary
	/// </summary>
	inline void Normalize() 
	{
		// Gets vector length
		float_q fLength = this->GetLength(); 

		// Checkout to avoid division by 0
		QE_ASSERT(fLength);

		//Normalize
		this->x /= fLength; 
		this->y /= fLength;	
		this->z /= fLength;
	}

	/// <summary>
	/// Convert current vector in its opposite vector.
	/// </summary>
	inline void Reverse() 
	{ 
		this->x = -this->x; 
		this->y = -this->y; 
		this->z = -this->z; 
	}

	/// <summary>
	/// Resets all components of current vector to 1.
	/// </summary>
	inline void ResetToOne() 
	{ 
		this->x = QFloat::_1; 
		this->y = QFloat::_1; 
		this->z = QFloat::_1; 
	}

	/// <summary>
	/// Resets all components of current vector to 0.
	/// </summary>
	inline void ResetToZero() 
	{ 
		this->x = QFloat::_0; 
		this->y = QFloat::_0; 
		this->z = QFloat::_0; 
	}

	/// <summary>
	/// Check if all components of current vector are 0.
	/// </summary>
	/// <returns>
	/// True if all components are 0. False otherwise.
	/// </returns>
	inline bool IsZero() 
	{ 
        return QFloat::IsZero(this->x) && QFloat::IsZero(this->y) && QFloat::IsZero(this->z); 
	}

	/// <summary>
	/// Check if all components of current vector are 1.
	/// </summary>
	/// <returns>
	/// True if all components are 1. False otherwise.
	/// </returns>
	inline bool IsVectorOfOnes() 
	{ 
        return QFloat::AreEquals(this->x, QFloat::_1) && QFloat::AreEquals(this->y, QFloat::_1) && QFloat::AreEquals(this->z, QFloat::_1); 
	}

	/// <summary>
	/// Calculates Dot Product by a vector provided.
	/// </summary>
	/// <param name="v">[IN] Multiplying vector.</param>
	/// <returns>
	/// A floating point value which is the result of Dot Product.
	/// </returns>
	inline float_q DotProduct(const QVector3 &v) 
	{ 
		return(this->x*v.x + this->y*v.y + this->z*v.z); 
	}

	/// <summary>
	/// Calculates Cross Product by a vector provided (left handed rules).
	/// </summary>
	/// <param name="v">[IN] Multiplying vector.</param>
	/// <param name="vOut">[OUT] Vector to store the resul of Cross Product.</param>
	inline void CrossProduct(const QVector3 &v, QVector3 &vOut) const 
	{ 
		vOut.x = v.y*this->z - v.z*this->y;
		vOut.y = v.z*this->x - v.x*this->z;
		vOut.z = v.x*this->y - v.y*this->x; 
	}

	/// <summary>
	/// Calculates Cross Product by a vector provided (left handed rules), and stores it in current vector.
	/// </summary>
	/// <param name="v">[IN] Multiplying vector.</param>
	inline void CrossProduct(const QVector3 &v) 
	{ 
		QVector3 aux = *this;

		this->x = v.y*aux.z - v.z*aux.y;
		this->y = v.z*aux.x - v.x*aux.z;
		this->z = v.x*aux.y - v.y*aux.x; 
	}

	/// <summary>
	/// Makes a Linear Interpolation between current vector and other vector provided. It stores result in current vector.
	/// </summary>
	/// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the current vector (per one).</param>
	/// <param name="v">[IN] Vector with which to interpolate.</param>
	inline void Lerp(const float_q &fFactor, const QVector3 &v)
	{ 
		this->x = this->x*fFactor + v.x*(QFloat::_1 - fFactor);
		this->y = this->y*fFactor + v.y*(QFloat::_1 - fFactor);
		this->z = this->z*fFactor + v.z*(QFloat::_1 - fFactor); 
	}

	/// <summary>
	/// Makes a Linear Interpolation between current vector and other vector provided. It stores result in a vector provided.
	/// </summary>
	/// <param name="fFactor">[IN] A floating point value which represents how close is the result vector from the current vector (per one).</param>
	/// <param name="v">[IN] Vector with which to interpolate.</param>
	/// <param name="vOut">[OUT] Vector to store results of Interpolation.</param>
	inline void Lerp(const float_q &fFactor, const QVector3 &v, QVector3 &vOut) const
	{
		vOut.x = this->x*fFactor + v.x*(QFloat::_1 - fFactor);
		vOut.y = this->y*fFactor + v.y*(QFloat::_1 - fFactor); 
		vOut.z = this->z*fFactor + v.z*(QFloat::_1 - fFactor); 
	}

	/// <summary>
	/// Calculates the distance between two vector heads (or two points). It computes the difference of two vectors and returns its length.
	/// </summary>
	/// <param name="v">[IN] Vector we want to calculate the distance from current vector.</param>
	/// <returns>
	/// A positive floating point value containing the distance between both vectors.
	/// </returns>
	inline float_q Distance(const QVector3 &v) const
	{
		return sqrt( (this->x-v.x)*(this->x-v.x) + (this->y-v.y)*(this->y-v.y) + (this->z-v.z)*(this->z-v.z) );
	}

	/// <summary>
	/// Converts vector into a string with the following format:
	/// “V3(x, y, z)”.
	/// </summary>
	/// <returns>The string with the format specified.</returns>
	string_q ToString();
	
	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Stores a vector with all components setted to 0
	/// </summary>
	static const QVector3 ZeroVector;
	/// <summary>
	/// Stores a vector with all components setted to 1
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

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVECTOR3__
