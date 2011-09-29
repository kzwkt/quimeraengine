// [TERMS&CONDITIONS]

#ifndef __QTRIANGLE3D__
#define __QTRIANGLE3D__

#include "EQSpaceRelation.h"
#include "QTriangle.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QQuaternion.h"
#include "QBasePlane.h"

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
/// Class which represents a triangle in 3D. Methods in this class are related to transformations in 3D.
/// </summary>
template <class VectorType>
class QDllExport QTriangle3D : public QTriangle<VectorType>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QTriangle3D() { }

	/// <summary>
	/// Constructor from three vector types, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] Vector types which defines vertex A.</param>
	/// <param name="vB">[IN] Vector types which defines vertex B.</param>
	/// <param name="vC">[IN] Vector types which defines vertex C.</param>
	inline QTriangle3D(const VectorType& vA, const VectorType& vB, const VectorType& vC) : QTriangle<VectorType>(vA, vB, vC) { }

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex. Each pointer references to an array which has at least three or four elements.
	/// </summary>
	/// <param name="pValueA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="pValueB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="pValueC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QTriangle3D(const float_q* pValueA, const float_q* pValueB, const float_q* pValueC) : QTriangle<VectorType>(pValueA, pValueB, pValueC) { }

	/// <summary>
	/// Constructor from three V4x32-FLOAT, one for each vertex.
	/// </summary>
	/// <param name="vfValueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="vfValueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="vfValueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QTriangle3D(const vf32_q& vfValueA, const vf32_q& vfValueB, const vf32_q& vfValueC) : QTriangle<VectorType>(vfValueA, vfValueB, vfValueC) { }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator. Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="tValue">[IN] 3D triangle that is assigned to current triangle.</param>
	inline QTriangle3D& operator=(const QBaseTriangle<VectorType>& tValue)
	{
		reinterpret_cast<QBaseTriangle<VectorType>&> (*this) = tValue;
		return *this;
	}

	/// <summary>
	/// Calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormalVector">[OUT] Vector that will contain the normal vector.</param>
	inline void GetNormal(QBaseVector3& vNormalVector) const
	{
		this->GetNormalImp(reinterpret_cast<QVector3&> (vNormalVector));
	}

	/// <summary>
	/// Calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormalVector">[OUT] Vector that will contain the normal vector.</param>
	inline void GetNormal(QBaseVector4& vNormalVector) const
	{
		this->GetNormalImp(reinterpret_cast<QVector4&> (vNormalVector));
	}

	/// <summary>
	/// Calculates triangle's circumcenter.
	/// </summary>
	/// <param name="vCircumcenter">[OUT] Vector type that will contain the triangle´s circumcenter.</param>
	/// More information: https://www.box.net/shared/9736bjiyq1
	void GetCircumcenter(VectorType& vCircumcenter) const
	{
		//STEP 1: Calculate all previous stuff
		VectorType vA(this->B - this->A);
		VectorType vB(this->C - this->B);
		VectorType vC(this->A - this->C);

		//fSp: Triangle´s semiperimeter
		float_q fSp = (vA.GetLength() + vB.GetLength() + vC.GetLength()) * QFloat::_0_5;
		//fK: Triangle´s area
		float_q fK = sqrt(fSp * (fSp - vA.GetLength()) * (fSp - vB.GetLength()) * (fSp - vC.GetLength()));

		VectorType vCrossvAvB;
		VectorType vCrossvCvAvB;

		vA.CrossProduct(vB, vCrossvAvB);
		vC.CrossProduct(vCrossvAvB, vCrossvCvAvB);

		//STEP 2: Calculate circumcenter
		vCircumcenter = ((this->A + this->C) * QFloat::_0_5) + (vA.DotProduct(vB) / (QFloat::_8 * fK * fK)) * vCrossvCvAvB;
	}

	/// <summary>
	/// Translates the triangle.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector type that represents the translation.</param>
	inline void Translate(const VectorType& vTranslation)
	{
		this->A += vTranslation;
		this->B += vTranslation;
		this->C += vTranslation;
	}

	/// <summary>
	/// Translates the triangle.
	/// </summary>
	/// <param name="vTranslation">[IN] Scalar value  that represents the translation.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void Translate(const VectorType& vTranslation, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).Translate(vTranslation);
	}

	/// <summary>
	/// Translates the triangle.
	/// </summary>
	/// <param name="fTranslateX">[IN] Scalar value that contains the translation on X axis.</param>
	/// <param name="fTranslateY">[IN] Scalar value that contains the translation on Y axis.</param>
	/// <param name="fTranslateZ">[IN] Scalar value that contains the translation on Z axis.</param>
	inline void Translate(const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ)
	{
		VectorType vLocalTranslation(fTranslateX, fTranslateY, fTranslateZ);

		this->A += vLocalTranslation;
		this->B += vLocalTranslation;
		this->C += vLocalTranslation;
	}

	/// <summary>
	/// Translates the triangle.
	/// </summary>
	/// <param name="fTranslateX">[IN] Scalar value that contains the translation on X axis.</param>
	/// <param name="fTranslateY">[IN] Scalar value that contains the translation on Y axis.</param>
	/// <param name="fTranslateZ">[IN] Scalar value that contains the translation on Z axis.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void Translate(const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).Translate(fTranslateX, fTranslateY, fTranslateZ);
	}

	/// <summary>
	/// Rotates the triangle.
	/// </summary>
	/// <param name="rotQuaternion">[IN] Quaternion that represents the rotation.</param>
	void Rotate(const QQuaternion& rotQuaternion)
	{
		this->A.Transform(rotQuaternion);
		this->B.Transform(rotQuaternion);
		this->C.Transform(rotQuaternion);
	}

	/// <summary>
	/// Rotates the triangle.
	/// </summary>
	/// <param name="rotQuaternion">[IN] Quaternion that represents the rotation.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	void Rotate(const QQuaternion& rotQuaternion, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).Rotate(rotQuaternion);
	}

	/// <summary>
	/// Rotates the triangle from a vPivot.
	/// </summary>
	/// <param name="rotQuaternion">[IN] Quaternion that represents the rotation.</param>
	/// <param name="vPivot">[IN] Vector type which we will use as pivot.</param>
	void RotateFromvPivot(const QQuaternion& rotQuaternion, const VectorType& vPivot)
	{
		this->A += vPivot;
		this->B += vPivot;
		this->C += vPivot;

		this->Rotate(rotQuaternion);

		this->A -= vPivot;
		this->B -= vPivot;
		this->C -= vPivot;
	}

	/// <summary>
	/// Rotates the triangle from a vPivot.
	/// </summary>
	/// <param name="rotQuaternion">[IN] Quaternion that represents the rotation.</param>
	/// <param name="vPivot">[IN] Vector type used as vPivot.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	void RotateFromvPivot(const QQuaternion& rotQuaternion, const VectorType& vPivot, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).RotateFromvPivot(rotQuaternion, vPivot);
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="vScale">[IN] Vector type that represents the scale.</param>
	inline void Scale(const VectorType& vScale)
	{
		this->A *= vScale;
		this->B *= vScale;
		this->C *= vScale;
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="vScale">[IN] Vector type that represents the scale.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void Scale(const VectorType& vScale, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).Scale(vScale);
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	inline void Scale(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ)
	{
		VectorType localScale(fScaleX, fScaleY, fScaleZ);

		this->A *= localScale;
		this->B *= localScale;
		this->C *= localScale;
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void Scale(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).Scale(fScaleX, fScaleY, fScaleZ);
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="vScale">[IN] Vector type that represents the scale.</param>
	/// <param name="vPivot">[IN] Vector type which we will use as vPivot.</param>
	inline void ScaleFromvPivot(const VectorType& vScale, const VectorType& vPivot)
	{
		this->A += vPivot;
		this->B += vPivot;
		this->C += vPivot;

		this->Scale(Scale);

		this->A -= vPivot;
		this->B -= vPivot;
		this->C -= vPivot;
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="vScale">[IN] Vector type that represents the scale.</param>
	/// <param name="vPivot">[IN] Vector type used as vPivot.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void ScaleFromvPivot(const VectorType& vScale, const VectorType& vPivot, QBaseTriangle<VectorType> & outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).ScaleFromvPivot(vScale, vPivot);
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="vPivot">[IN] Vector type used as vPivot.</param>
	inline void ScaleFromvPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot)
	{
		this->A += vPivot;
		this->B += vPivot;
		this->C += vPivot;

		this->Scale(fScaleX, fScaleY, fScaleZ);

		this->A -= vPivot;
		this->B -= vPivot;
		this->C -= vPivot;
	}

	/// <summary>
	/// Scales the triangle.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="vPivot">[IN] Vector type used as Pivot.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void ScaleFromvPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).ScaleFromvPivot(fScaleX, fScaleY, fScaleZ, vPivot);
	}

	/// <summary>
	/// Checks the space relation between current triangle and a plane recieved as parameter. Space Relation means that
	/// the triangle is in the positive side of the space divided by the plane, in the negative side, in both sides (intersection)
	/// or even the triangle is contained in the plane.
	/// </summary>
	/// <param name="plane">[IN] The plane we want check the relation with current triangle.</param>
    /// <returns>
    /// An enumerated value like follows: Contained in the plane, Positive Side, Negative Side or Both Sides (intersects the plane).
    /// </returns>
	EQSpaceRelation SpaceRelation(const QBasePlane& plane) const
	{
		float_q fRelationA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
		float_q fRelationB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;
		float_q fRelationC = plane.a * this->C.x + plane.b * this->C.y + plane.c * this->C.z + plane.d;

		if (QFloat::IsZero(fRelationA))
		{
			if (QFloat::IsZero(fRelationB))
			{
				if (QFloat::IsZero(fRelationC))
				{
					//Triangle contained in the plane
					return EQSpaceRelation::E_Contained;
				}
				else if (QFloat::IsGreaterOrEquals(fRelationC, QFloat::_0))
				{
					//Triangle is in the positive side of the space delimited by the plane.
					return EQSpaceRelation::E_PositiveSide;
				}
				else
				{
					//Triangle is in the negative side of the space delimited by the plane.
					return EQSpaceRelation::E_NegativeSide;
				}
			}
			else if (QFloat::IsGreaterOrEquals(fRelationB, QFloat::_0))
			{
				if ((QFloat::IsZero(fRelationC)) || (QFloat::IsGreaterOrEquals(fRelationC, QFloat::_0)))
				{
					//Triangle is in the positive side of the space delimited by the plane.
					return EQSpaceRelation::E_PositiveSide;
				}
				else
				{
					//Triangle is in both sides of the plane, intersecting it.
					return EQSpaceRelation::E_BothSides;
				}
			}
			else
			{
				if (QFloat::IsZero(fRelationC))
				{
					//Triangle is in the negative side of the space delimited by the plane.
					return EQSpaceRelation::E_NegativeSide;
				}
				else if (QFloat::IsGreaterOrEquals(fRelationC, QFloat::_0))
				{
					//Triangle is in both sides of the plane, intersecting it.
					return EQSpaceRelation::E_BothSides;
				}
				else
				{
					//Triangle is in the negative side of the space delimited by the plane.
					return EQSpaceRelation::E_NegativeSide;
				}
			}
		}
		else if (QFloat::IsGreaterOrEquals(fRelationA, QFloat::_0))
		{
			if (QFloat::IsZero(fRelationB))
			{
				if ((QFloat::IsZero(fRelationC)) || (QFloat::IsGreaterOrEquals(fRelationC, QFloat::_0)))
				{
					//Triangle is in the positive side of the space delimited by the plane.
					return EQSpaceRelation::E_PositiveSide;
				}
				else
				{
					//Triangle is in both sides of the plane, intersecting it.
					return EQSpaceRelation::E_BothSides;
				}
			}
			else if (QFloat::IsGreaterOrEquals(fRelationB, QFloat::_0))
			{
				if ((QFloat::IsZero(fRelationC)) || (QFloat::IsGreaterOrEquals(fRelationC, QFloat::_0)))
				{
					//Triangle is in the positive side of the space delimited by the plane.
					return EQSpaceRelation::E_PositiveSide;
				}
				else
				{
					//Triangle is in both sides of the plane, intersecting it.
					return EQSpaceRelation::E_BothSides;
				}
			}
			else
			{
				//Triangle is in both sides of the plane, intersecting it.
				return EQSpaceRelation::E_BothSides;
			}
		}
		else
		{
			if (QFloat::IsZero(fRelationB))
			{
				if (QFloat::IsGreaterOrEquals(fRelationC, QFloat::_0))
				{
					//Triangle is in both sides of the plane, intersecting it.
					return EQSpaceRelation::E_BothSides;
				}
				else
				{
					//Triangle is in the negative side of the space delimited by the plane.
					return EQSpaceRelation::E_NegativeSide;
				}
			}
			else if (QFloat::IsGreaterOrEquals(fRelationB, QFloat::_0))
			{
				//Triangle is in both sides of the plane, intersecting it.
				return EQSpaceRelation::E_BothSides;
			}
			else
			{
				if (QFloat::IsGreaterOrEquals(fRelationC, QFloat::_0))
				{
					//Triangle is in both sides of the plane, intersecting it.
					return EQSpaceRelation::E_BothSides;
				}
				else
				{
					//Triangle is in the negative side of the space delimited by the plane.
					return EQSpaceRelation::E_NegativeSide;
				}
			}
		}
	}

	/// <summary>
	/// Moves the triangle along its normal vector the units indicated by a Scalar value .
	/// </summary>
	/// <param name="fAmount">[IN] Float type that contains the amount of the movement.</param>
	inline void Extrude(const float_q& fAmount)
	{
		VectorType vNormalVector;

		GetNormal(vNormalVector);

		vNormalVector = vNormalVector * fAmount;

		this->A += vNormalVector;
		this->B += vNormalVector;
		this->C += vNormalVector;
	}

	/// <summary>
	/// Moves the triangle along its normal vector the units indicated by a Scalar value .
	/// </summary>
	/// <param name="fAmount">[IN] Float type that contains the amount of the movement.</param>
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void Extrude(const float_q& fAmount, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).Extrude(fAmount);
	}

protected:

	/// <summary>
	/// Template method that calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormal">[OUT] Vector type which will store the normal vector.</param>
	template <class OtherVectorType>
	inline void GetNormalImp(OtherVectorType& vNormal) const
	{
		OtherVectorType vAB = this->B - this->A;
		OtherVectorType vBC = this->C - this->B;

		vAB.CrossProduct(vBC, vNormal);

		vNormal.Normalize();
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE3D__
