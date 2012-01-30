// [TERMS&CONDITIONS]

#ifndef __QHEXAHEDRON__
#define __QHEXAHEDRON__

#include "QBaseHexahedron.h"
#include "SQPoint.h"
#include "QQuaternion.h"
#include "QPlane.h"
#include "QLineSegment3D.h"

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
/// Class which represents a hexahedron in the space. The hexahedron is defined by its eight vertices.<br>
/// It's supossed that ABCD defines a face of the hexahedron (eventually the top face) and
/// EFGH defines the opposite face (eventually the bottom one).<br>
/// The six faces are defined by the followings vertices: ABCD, EFGH, AEFD, ABHE, BCGH, CDFG.<br>
/// The twelve edges are AB, BC, CD, DA, EF, FG, GH, HE, AE, BH, CG, DF.
/// </summary>
template <class VectorType>
class QDllExport QHexahedron : public QBaseHexahedron<VectorType>
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QHexahedron()
    {
    }

    /// <summary>
    /// Constructor from eight vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    /// <param name="vD">[IN] Vector to define vertex D.</param>
    /// <param name="vE">[IN] Vector to define vertex E.</param>
    /// <param name="vF">[IN] Vector to define vertex F.</param>
    /// <param name="vG">[IN] Vector to define vertex G.</param>
    /// <param name="vH">[IN] Vector to define vertex H.</param>
    inline QHexahedron(const VectorType &vA, const VectorType &vB, const VectorType &vC, const VectorType &vD,
                       const VectorType &vE, const VectorType &vF, const VectorType &vG, const VectorType &vH) :
                           QBaseHexahedron<VectorType>(vA, vB, vC, vD, vE, vF, vG, vH)
    {
    }

    /// <summary>
    /// Constructor from two vectors which defines two opposite vertices, with no common faces between them
    /// (the ends of any inner diagonals).
    /// </summary>
    /// <param name="vA">[IN] Vector which defines one vertex of a inner diagonal (it will be used to initialize A).</param>
    /// <param name="vG">[IN] Vector which defines the other vertex of the inner diagonal (it Will be used to initialized G).</param>
    inline QHexahedron(const VectorType &vA, const VectorType &vG) : QBaseHexahedron<VectorType>(vA, vG)
    {
    }

    /// <summary>
    /// Constructor from a vector which defines the gravity center of the box and three floating
    /// points values which defines its height (Y), width (X) and depth (Z).<br>
    /// It's supossed that all edges are parallel to one of the axis.
    /// </summary>
    /// <param name="vCenter">[IN] Center point of the box.</param>
    /// <param name="fLengthX">[IN] Length of an edge parallel to X axis (width).</param>
    /// <param name="fLengthY">[IN] Length of an edge parallel to Y axis (height).</param>
    /// <param name="fLengthZ">[IN] Length of an edge parallel to Z axis (depth).</param>
    inline QHexahedron(const VectorType &vCenter, const float_q &fLengthX, const float_q &fLengthY, const float_q &fLengthZ) :
                           QBaseHexahedron<VectorType>(vCenter, fLengthX, fLengthY, fLengthZ)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets an hexahedron that defines a cube whose egdes are 1 unit length, centered in the coordinate origin, and with all edges parallel
    /// to coordinate axis.
    /// </summary>
    /// <returns>
	/// A "unit cube".
	/// </returns>
    inline static const QHexahedron<VectorType>& GetUnitCube()
    {
        static const QHexahedron<VectorType> UNITCUBE(-VectorType::GetVectorOfOnes()*SQFloat::_0_5, VectorType::GetVectorOfOnes()*SQFloat::_0_5);
        return UNITCUBE;
    }


    // METHODS
    // ---------------
public:

	/// <summary>
	/// Assign operator.
	/// </summary>
	/// <param name="hexahedron">[IN] The hexahedron to be copied from.</param>
	/// <returns>
	/// A reference to the modified hexahedron.
	/// </returns>
    inline QHexahedron& operator=(const QBaseHexahedron<VectorType>& hexahedron)
    {
        QBaseHexahedron<VectorType>::operator=(hexahedron);
        return *this;
    }

	/// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided quaternion
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
	inline void Rotate(const QQuaternion &qRotation)
	{
        SQPoint::Rotate(qRotation, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided quaternion
	/// around the coordinate axis centre, and stores the resulting hexahedron in the output parameter.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The resultant rotated hexahedron.</param>
	/// <remarks>
	/// -The resident hexahedron is NOT modified, it stays the same.
	/// </remarks>
	inline void Rotate(const QQuaternion &qRotation, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Rotate(qRotation, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the provided quaternion
	/// around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot)
	{
	    SQPoint::RotateWithPivot(qRotation, vPivot, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the provided quaternion
	/// around a pivot point (which acts as center of rotation), and then storing it in the output parameter.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="outHexahedron">[OUT] The rotated hexahedron.</param>
	/// <remarks>
	/// The resident hexahedron is NOT modified, remains unchanged.
	/// </remarks>
	inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::RotateWithPivot(qRotation, vPivot, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    inline void Translate(const QBaseVector3 &vTranslation)
	{
	    SQPoint::Translate(vTranslation, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided vector, storing the
	/// resultant hexahedron in the provided one.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The translated hexahedron.</param>
	inline void Translate(const QBaseVector3 &vTranslation, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Translate(vTranslation, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	/// <param name="fTranslationZ">[IN] The amount of translation to be applied in Z direction.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ)
	{
	    SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided amounts for every axis,
	/// storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	/// <param name="fTranslationZ">[IN] The amount of translation to be applied in Z direction.</param>
	/// <param name="outHexahedron">[OUT] The translated hexahedron.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ,
                          QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	inline void Scale(const QBaseVector3 &vScale)
	{
	    SQPoint::Scale(vScale, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="outHexahedron">[OUT] The scaled hexahedron.</param>
	inline void Scale(const QBaseVector3 &vScale, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Scale(vScale, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
	{
	     SQPoint::Scale(fScaleX, fScaleY, fScaleZ, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	/// <param name="outHexahedron">[OUT] The scaled hexahedron.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ,
                      QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Scale(fScaleX, fScaleY, fScaleZ, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector,
	/// acting the other provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const QBaseVector3 &vScale, const VectorType &vPivot)
	{
	    SQPoint::ScaleWithPivot(vScale, vPivot, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector,
	/// acting the other provided vector as pivot of scale, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outHexahedron">[OUT] The scaled hexahedron.</param>
	inline void ScaleWithPivot(const QBaseVector3 &vScale, const VectorType &vPivot, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::ScaleWithPivot(vScale, vPivot, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot)
	{
	     SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, fScaleZ, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outHexahedron">[OUT] The scaled hexahedron.</param>
	inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ,
                               const VectorType &vPivot, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, outHexahedron.template AsPtr<VectorType>(), 8);
	}

    /// <summary>
	/// This method store in the output parameter the six planes which defines the hexahedron.<br>
	/// The six planes are:<br>
	/// <br><ul>
	/// <li>plane A, B, C -> ABCD face, stored in element 0 of the array</li>
	/// <li>plane E, F, G -> EFGH face, stored in element 1 of the array</li>
    /// <li>plane A, E, F -> AEFD face, stored in element 2 of the array</li>
    /// <li>plane A, B, H -> ABHE face, stored in element 3 of the array</li>
    /// <li>plane B, C, G -> BCGH face, stored in element 4 of the array</li>
    /// <li>plane C, D, F -> CDFG face, stored in element 5 of the array</li>
    /// </ul>
	/// </summary>
	/// <param name="arPlanes">[OUT] An array where to store the six planes. It must have at least six elements.</param>
	/// <remarks>
	/// All returned planes are normalized.
	/// </remarks>
    inline void GetPlanes(QPlane *arPlanes) const
    {
        arPlanes[0] = QPlane(this->A, this->B, this->C); // ABCD face
        arPlanes[1] = QPlane(this->E, this->F, this->G); // EFGH face
        arPlanes[2] = QPlane(this->A, this->E, this->F); // AEFD face
        arPlanes[3] = QPlane(this->A, this->B, this->H); // ABHE face
        arPlanes[4] = QPlane(this->B, this->C, this->G); // BCGH face
        arPlanes[5] = QPlane(this->C, this->D, this->F); // CDFG face
    }

    /// <summary>
	/// Checks if a point is inside or outside resident hexahedron.
	/// </summary>
	/// <param name="vPoint">[IN] Point which is being checked.</param>
	/// <returns>
	/// True if the point is inside hexahedron, false otherwise.
	/// </returns>
	/// <remarks>
	/// Points in the surface of the hexahedron are considered inside it.
	/// </remarks>
    inline bool Contains(const VectorType &vPoint) const
    {
        return ( PointsInSameSideOfPlane(vPoint, this->E, this->A, this->B, this->C) &&
                 PointsInSameSideOfPlane(vPoint, this->A, this->E, this->F, this->G) &&
                 PointsInSameSideOfPlane(vPoint, this->C, this->A, this->B, this->H) &&
                 PointsInSameSideOfPlane(vPoint, this->A, this->B, this->C, this->G) &&
                 PointsInSameSideOfPlane(vPoint, this->C, this->A, this->D, this->F) &&
                 PointsInSameSideOfPlane(vPoint, this->A, this->C, this->D, this->F) );
    }

    /// <summary>
    /// Checks the relation between resident hexahedron and the provided plane.<br>
    /// Since a plane divides space into two parts, we can check if the "distances" (allowing distances having sign) from
    /// the plane to all vertices of hexahedron have diferent sign, in which case the segment crosses the plane.<br>
    /// If distances from plane to all vertices have the same sign, all hexahedron is in the same
    /// side of the space.
    /// </summary>
    /// <remarks>
    /// Note that if a vertex of the resident hexahedron lies on the plane, we don't consider that it is
    /// crossing the plane.
    /// </remarks>
    /// <param name="plane">[IN] The plane the relation with resident hexahedron will be check.</param>
    /// <returns>
    /// An enumerated value like follows:
    /// - Contained: All hexahedron lies on plane.
    /// - PositiveSide: The hexahedron is fully contained in the positive side of the space defined by the plane.
    /// - NegativeSide: The hexahedron is fully contained in the negative side of the space defined by the plane.
    /// - BothSides: The hexahedron crosses the plane.
    /// <br>
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane) const
    {
        const float_q &distA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_q &distB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;
        const float_q &distC = plane.a * this->C.x + plane.b * this->C.y + plane.c * this->C.z + plane.d;
        const float_q &distD = plane.a * this->D.x + plane.b * this->D.y + plane.c * this->D.z + plane.d;
        const float_q &distE = plane.a * this->E.x + plane.b * this->E.y + plane.c * this->E.z + plane.d;
        const float_q &distF = plane.a * this->F.x + plane.b * this->F.y + plane.c * this->F.z + plane.d;
        const float_q &distG = plane.a * this->G.x + plane.b * this->G.y + plane.c * this->G.z + plane.d;
        const float_q &distH = plane.a * this->H.x + plane.b * this->H.y + plane.c * this->H.z + plane.d;

        if (SQFloat::IsZero(distA) && SQFloat::IsZero(distB) && SQFloat::IsZero(distC) && SQFloat::IsZero(distD) &&
            SQFloat::IsZero(distE) && SQFloat::IsZero(distF) && SQFloat::IsZero(distG) && SQFloat::IsZero(distH) )
            return EQSpaceRelation::E_Contained;
        else if ( SQFloat::IsPositive(distA) && SQFloat::IsPositive(distB) && SQFloat::IsPositive(distC) && SQFloat::IsPositive(distD) &&
            SQFloat::IsPositive(distE) && SQFloat::IsPositive(distF) && SQFloat::IsPositive(distG) && SQFloat::IsPositive(distH) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( SQFloat::IsLowerOrEquals(distA, SQFloat::_0) && SQFloat::IsLowerOrEquals(distB, SQFloat::_0) &&
                  SQFloat::IsLowerOrEquals(distC, SQFloat::_0) && SQFloat::IsLowerOrEquals(distD, SQFloat::_0) &&
                  SQFloat::IsLowerOrEquals(distE, SQFloat::_0) && SQFloat::IsLowerOrEquals(distF, SQFloat::_0) &&
                  SQFloat::IsLowerOrEquals(distG, SQFloat::_0) && SQFloat::IsLowerOrEquals(distH, SQFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
    }

    /// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contais the rotation to be applied.</param>
	inline void Rotate(const QRotationMatrix3x3 &rotation)
	{
        SQPoint::Rotate(rotation, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre, and stores the resulting hexahedron in the output parameter.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contais the rotation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The resultant rotated hexahedron.</param>
	/// <remarks>
	/// The segment is NOT modified, it stays the same.
	/// </remarks>
	inline void Rotate(const QRotationMatrix3x3 &rotation, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Rotate(rotation, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot)
	{
	    SQPoint::RotateWithPivot(rotation, vPivot, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation),
	/// and then storing it in the output parameter.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="outHexahedron">[OUT] The rotated hexahedron.</param>
	/// <remarks>
	/// The resident hexahedron is NOT modified, remains unchanged.
	/// </remarks>
	inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::RotateWithPivot(rotation, vPivot, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation)
	{
	    SQPoint::Translate(translation, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix,
	/// storing the resultant hexahedron in the provided one.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The translated hexahedron.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Translate(translation, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation)
	{
	    SQPoint::Translate(translation, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix,
	/// storing the resultant hexahedron in the provided one.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The translated hexahedron.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Translate(translation, outHexahedron.template AsPtr<VectorType>(), 8);
	}

    /// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided scale matrix.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	inline void Scale(const QScaleMatrix3x3 &scale)
	{
	    SQPoint::Scale(scale, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided scale matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="outHexahedron">[OUT] The scaled hexahedron.</param>
	inline void Scale(const QScaleMatrix3x3 &scale, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Scale(scale, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const VectorType &vPivot)
	{
	    SQPoint::ScaleWithPivot(scale, vPivot, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outHexahedron">[OUT] The scaled hexahedron.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const VectorType &vPivot, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::ScaleWithPivot(scale, vPivot, outHexahedron.template AsPtr<VectorType>(), 8);
	}

    /// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation)
	{
	    SQPoint::Transform(transformation, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The transformed hexahedron.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Transform(transformation, outHexahedron.template AsPtr<VectorType>(), 8);
	}

    /// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation)
	{
	    SQPoint::Transform(transformation, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The transformed hexahedron.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Transform(transformation, outHexahedron.template AsPtr<VectorType>(), 8);
	}

    /// <summary>
	/// This method transforms the resident hexahedron applying the provided space conversion matrix.
	/// </summary>
	/// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	inline void Transform(const QSpaceConversionMatrix &spaceConversion)
	{
	    SQPoint::Transform(spaceConversion, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided space conversion matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	/// <param name="outHexahedron">[OUT] The transformed hexahedron.</param>
	inline void Transform(const QSpaceConversionMatrix &spaceConversion, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::Transform(spaceConversion, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(transformation, vPivot, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outHexahedron">[OUT] The transformed hexahedron.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::TransformWithPivot(transformation, vPivot, outHexahedron.template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(transformation, vPivot, this->template AsPtr<VectorType>(), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outHexahedron">[OUT] The transformed hexahedron.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot, QBaseHexahedron<VectorType> &outHexahedron) const
	{
	    outHexahedron = *this;
	    SQPoint::TransformWithPivot(transformation, vPivot, outHexahedron.template AsPtr<VectorType>(), 8);
	}

    /// <summary>
	/// Checks if resident hexahedron intersects a given hexahedron.
	/// </summary>
	/// <param name="hexahedron">[IN] Hexahedron which intersections with resident hexahedron will be checked.</param>
	/// <returns>
	/// True if both hexahedrons intersects, false otherwise.
	/// </returns>
	inline bool Intersection(const QBaseHexahedron<VectorType> &hexahedron) const
	{
	    return ( this->Contains(hexahedron.A) || this->Contains(hexahedron.B) || this->Contains(hexahedron.C) || this->Contains(hexahedron.D) ||
                 this->Contains(hexahedron.E) || this->Contains(hexahedron.F) || this->Contains(hexahedron.G) || this->Contains(hexahedron.H) ||
                 QLineSegment3D<VectorType>(this->A, this->B).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->B, this->C).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->C, this->D).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->D, this->A).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->E, this->F).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->F, this->G).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->G, this->H).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->H, this->E).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->A, this->E).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->B, this->H).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->C, this->G).Intersection(hexahedron) ||
                 QLineSegment3D<VectorType>(this->D, this->F).Intersection(hexahedron) );
	}

    /// <summary>
	/// Projects resident hexahedron over a given plane, storing the resultant hexahedron in the provided one.
	/// </summary>
	/// <param name="plane">[IN] Plane where project resident hexahedron to.</param>
	/// <param name="hexahedron">[OUT] Hexahedron where to store the projected one.</param>
	/// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
    inline void ProjectToPlane(const QPlane &plane, QBaseHexahedron<VectorType> &hexahedron) const
    {
        plane.PointProjection(this->A, hexahedron.A);
        plane.PointProjection(this->B, hexahedron.B);
        plane.PointProjection(this->C, hexahedron.C);
        plane.PointProjection(this->D, hexahedron.D);
        plane.PointProjection(this->E, hexahedron.E);
        plane.PointProjection(this->F, hexahedron.F);
        plane.PointProjection(this->G, hexahedron.G);
        plane.PointProjection(this->H, hexahedron.H);
    }

    /// <summary>
    /// Converts hexahedron into a string with the following format:<br>
    /// "HX(a($A),b($B),c($C),d($D),e($E),f($F),g($G),h($H))".<br>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>The string with the specified format.</returns>
    string_q ToString() const
    {
        return QE_L("HX(a(") + this->A.ToString() + QE_L("),b(") + this->B.ToString() + QE_L("),c(") +
                               this->C.ToString() + QE_L("),d(") + this->D.ToString() + QE_L("),e(") +
                               this->E.ToString() + QE_L("),f(") + this->F.ToString() + QE_L("),g(") +
                               this->G.ToString() + QE_L("),h(") + this->H.ToString() + QE_L("))");
    }


protected:

    // Calculates if two points are in the same side of a plane defined by 3 points.
    template <class VectorTypeParam>
    inline bool PointsInSameSideOfPlane(const VectorTypeParam &vP1, const VectorTypeParam &vP2,
                                        const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC) const
    {
        QPlane p(vA, vB, vC);

        const float_q &fDistP1 = p.a * vP1.x + p.b * vP1.y + p.c * vP1.z + p.d;
        const float_q &fDistP2 = p.a * vP2.x + p.b * vP2.y + p.c * vP2.z + p.d;

        return !SQFloat::IsNegative(fDistP1 * fDistP2);
    }
};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QHEXAHEDRON__
