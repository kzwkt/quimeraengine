// [TERMS&CONDITIONS]

#ifndef __QHEXAHEDRON__
#define __QHEXAHEDRON__

#include "QBaseHexahedron.h"
#include "QPoint.h"
#include "QQuaternion.h"
#include "QPlane.h"

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
/// Class which represents a hexahedron in the space. The hexahedron is defined by its eight vertices.
/// It's supossed that ABCD defines a face of the hexahedron (eventually the top face) and
/// EFGH defines the opposite face (eventually the bottom one).
/// The six faces are defined by the followings vertices: ABCD, EFGH, AEFD, ABHE, BCGH, CDFG
/// The twelve edges are AB, BC, CD, DA, EF, FG, GH, HE, AE, BH, CG, DF
/// </summary>
template <class VectorType>
class QDllExport QHexahedron : public QBaseHexahedron<VectorType>
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Defines a cube whose egdes are 1 unit length, centered in the coordinate origin, and with all edges parallel
    /// to coordinate axis.
    /// </summary>
    static const QHexahedron<VectorType> UnitCube;

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QHexahedron () { }

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
    inline QHexahedron (const VectorType &vA, const VectorType &vB, const VectorType &vC, const VectorType &vD,
                        const VectorType &vE, const VectorType &vF, const VectorType &vG, const VectorType &vH) :
           QBaseHexahedron<VectorType>(vA, vB, vC, vD, vE, vF, vG, vH) { }

    /// <summary>
    /// Constructor from two vectors which defines two opposite vertices, with no common faces between them
    /// (the ends of any inner diagonals).
    /// </summary>
    /// <param name="vA">[IN] Vector which defines one vertex of a inner diagonal (it will be used to initialize A).</param>
    /// <param name="vG">[IN] Vector which defines the other vertex of the inner diagonal (it Will be used to initialized G).</param>
    inline QHexahedron (const VectorType &vA, const VectorType &vG) : QBaseHexahedron<VectorType>(vA, vG) { }

    /// <summary>
    /// Constructor from a vector which defines the gravity center of the box and three floating
    /// points values which defines its height (Y), width (X) and depth (Z).
    /// It's supossed that all edges are parallel to one of the axis.
    /// </summary>
    /// <param name="vCenter">[IN] Center point of the box.</param>
    /// <param name="fLenX">[IN] Length of an edge parallel to X axis (width).</param>
    /// <param name="fLenY">[IN] Length of an edge parallel to Y axis (height).</param>
    /// <param name="fLenZ">[IN] Length of an edge parallel to Z axis (depth).</param>
    inline QHexahedron (const VectorType &vCenter, const float_q &fLenX, const float_q &fLenY, const float_q &fLenZ) :
           QBaseHexahedron<VectorType>(vCenter, fLenX, fLenY,fLenZ) { }

    // METHODS
    // ---------------
public:

	/// <summary>
	/// Assign operator.
	/// </summary>
	/// <param name="hex">[IN] The hexahedron to be copied from.</param>
	/// <returns>
	/// A reference to the modified hexahedron.
	/// </returns>
    inline QHexahedron& operator=(const QBaseHexahedron<VectorType>& hex)
    {
        QBaseHexahedron<VectorType>::operator=(hex);
        return *this;
    }

	/// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided quaternion
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contais the rotation to be applied.</param>
	inline void Rotate (const QQuaternion &qRot)
	{
        QPoint::Rotate(qRot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided quaternion
	/// around the coordinate axis centre, and stores the resulting hexahedron in the output parameter.
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="hOut">[OUT] The resultant rotated hexahedron.</param>
	/// <remarks>
	/// -The resident hexahedron is NOT modified, it stays the same.
	/// </remarks>
	inline void Rotate (const QQuaternion &qRot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Rotate(qRot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the provided quaternion
	/// around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateFromPivot (const QQuaternion &qRot, const VectorType &vPivot)
	{
	    QPoint::RotateFromPivot(qRot, vPivot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the provided quaternion
	/// around a pivot point (which acts as center of rotation), and then storing it in the output parameter.
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="hOut">[OUT] The rotated hexahedron.</param>
	/// <remarks>
	/// The resident hexahedron is NOT modified, remains unchanged.
	/// </remarks>
	inline void RotateFromPivot (const QQuaternion &qRot, const VectorType &vPivot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::RotateFromPivot(qRot, vPivot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    inline void Translate(const QBaseVector3 &vTranslation)
	{
	    QPoint::Translate(vTranslation, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided vector, storing the
	/// resultant hexahedron in the provided one.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
	/// <param name="hOut">[OUT] The translated hexahedron.</param>
	inline void Translate(const QBaseVector3 &vTranslation, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Translate(vTranslation, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	/// <param name="fTranslationZ">[IN] The amount of translation to be applied in Z direction.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ)
	{
	    QPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided amounts for every axis,
	/// storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	/// <param name="fTranslationZ">[IN] The amount of translation to be applied in Z direction.</param>
	/// <param name="hOut">[OUT] The translated hexahedron.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ,
                          QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	inline void Scale(const QBaseVector3 &vScale)
	{
	    QPoint::Scale(vScale, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="hOut">[OUT] The scaled hexahedron.</param>
	inline void Scale(const QBaseVector3 &vScale, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Scale(vScale, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
	{
	     QPoint::Scale(fScaleX, fScaleY, fScaleZ, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	/// <param name="hOut">[OUT] The scaled hexahedron.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ,
                      QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Scale(fScaleX, fScaleY, fScaleZ, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector,
	/// acting the other provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const QBaseVector3 &vScale, const VectorType &vPivot)
	{
	    QPoint::ScaleFromPivot(vScale, vPivot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided vector,
	/// acting the other provided vector as pivot of scale, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="hOut">[OUT] The scaled hexahedron.</param>
	inline void ScaleFromPivot(const QBaseVector3 &vScale, const VectorType &vPivot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::ScaleFromPivot(vScale, vPivot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot)
	{
	     QPoint::ScaleFromPivot(fScaleX, fScaleY, vPivot, fScaleZ, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="hOut">[OUT] The scaled hexahedron.</param>
	inline void ScaleFromPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ,
                               const VectorType &vPivot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::ScaleFromPivot(fScaleX, fScaleY, fScaleZ, vPivot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

    /// <summary>
	/// This method store in the output parameter the six planes which defines the hexahedron. The six planes are:
	/// plane A, B, C -> ABCD face, stored in element 0 of the array
	/// plane E, F, G -> EFGH face, stored in element 1 of the array
    /// plane A, E, F -> AEFD face, stored in element 2 of the array
    /// plane A, B, H -> ABHE face, stored in element 3 of the array
    /// plane B, C, G -> BCGH face, stored in element 4 of the array
    /// plane C, D, F -> CDFG face, stored in element 5 of the array
	/// </summary>
	/// <param name="arPlanes">[OUT] An array where to store the six planes. It must have at least six elements.</param>
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
    /// Checks the relation between resident hexahedron and the provided plane.
    /// Since a plane divides space into two parts, we can check if the "distances" (allowing distances having sign) from
    /// the plane to all vertices of hexahedron have diferent sign, in which case the segment crosses the plane.
    /// If distances from plane to all vertices have the same sign, all hexahedron is in the same
    /// side of the space.
    /// </summary>
    /// <remarks>
    /// Note that if a vertex of the resident hexahedron lies on the plane, we don't consider that it is
    /// crossing the plane.
    /// </remarks>
    /// <param name="plane">[IN] The plane the relation with resident hexahedron will be check.</param>
    /// <returns>
    /// An integer value like follows:
    ///     0 (Contained): All hexahedron lies on plane.
    ///     1 (PositiveSide): The hexahedron is fully contained in the positive side of the space defined by the plane.
    ///     2 (NegativeSide): The hexahedron is fully contained in the negative side of the space defined by the plane.
    ///     3 (BothSides): The hexahedron crosses the plane.
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &p) const
    {
        const float_q &distA = p.a * this->A.x + p.b * this->A.y + p.c * this->A.z + p.d;
        const float_q &distB = p.a * this->B.x + p.b * this->B.y + p.c * this->B.z + p.d;
        const float_q &distC = p.a * this->C.x + p.b * this->C.y + p.c * this->C.z + p.d;
        const float_q &distD = p.a * this->D.x + p.b * this->D.y + p.c * this->D.z + p.d;
        const float_q &distE = p.a * this->E.x + p.b * this->E.y + p.c * this->E.z + p.d;
        const float_q &distF = p.a * this->F.x + p.b * this->F.y + p.c * this->F.z + p.d;
        const float_q &distG = p.a * this->G.x + p.b * this->G.y + p.c * this->G.z + p.d;
        const float_q &distH = p.a * this->H.x + p.b * this->H.y + p.c * this->H.z + p.d;

        if (QFloat::IsZero(distA) && QFloat::IsZero(distB) && QFloat::IsZero(distC) && QFloat::IsZero(distD) &&
            QFloat::IsZero(distE) && QFloat::IsZero(distF) && QFloat::IsZero(distG) && QFloat::IsZero(distH) )
            return EQSpaceRelation::E_Contained;
        else if ( QFloat::IsPositive(distA) && QFloat::IsPositive(distB) && QFloat::IsPositive(distC) && QFloat::IsPositive(distD) &&
            QFloat::IsPositive(distE) && QFloat::IsPositive(distF) && QFloat::IsPositive(distG) && QFloat::IsPositive(distH) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( QFloat::IsLowerOrEquals(distA, QFloat::_0) && QFloat::IsLowerOrEquals(distB, QFloat::_0) &&
                  QFloat::IsLowerOrEquals(distC, QFloat::_0) && QFloat::IsLowerOrEquals(distD, QFloat::_0) &&
                  QFloat::IsLowerOrEquals(distE, QFloat::_0) && QFloat::IsLowerOrEquals(distF, QFloat::_0) &&
                  QFloat::IsLowerOrEquals(distG, QFloat::_0) && QFloat::IsLowerOrEquals(distH, QFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
    }

    /// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contais the rotation to be applied.</param>
	inline void Rotate (const QRotationMatrix3x3 &mRot)
	{
        QPoint::Rotate(mRot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method applies to the resident hexahedron the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre, and stores the resulting hexahedron in the output parameter.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contais the rotation to be applied.</param>
	/// <param name="hOut">[OUT] The resultant rotated hexahedron.</param>
	/// <remarks>
	/// -The segment is NOT modified, it stays the same.
	/// </remarks>
	inline void Rotate (const QRotationMatrix3x3 &mRot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Rotate(mRot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateFromPivot (const QRotationMatrix3x3 &mRot, const VectorType &vPivot)
	{
	    QPoint::RotateFromPivot(mRot, vPivot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation),
	/// and then storing it in the output parameter.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="hOut">[OUT] The rotated hexahedron.</param>
	/// <remarks>
	/// The resident hexahedron is NOT modified, remains unchanged.
	/// </remarks>
	inline void RotateFromPivot (const QRotationMatrix3x3 &mRot, const VectorType &vPivot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::RotateFromPivot(mRot, vPivot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix4x3 &mTranslation)
	{
	    QPoint::Translate(mTranslation, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix,
	/// storing the resultant hexahedron in the provided one.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="hOut">[OUT] The translated hexahedron.</param>
	inline void Translate(const QTranslationMatrix4x3 &mTranslation, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Translate(mTranslation, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix4x4 &mTranslation)
	{
	    QPoint::Translate(mTranslation, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method performs a translation of the resident hexahedron given by the provided translation matrix,
	/// storing the resultant hexahedron in the provided one.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="hOut">[OUT] The translated hexahedron.</param>
	inline void Translate(const QTranslationMatrix4x4 &mTranslation, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Translate(mTranslation, reinterpret_cast<VectorType*> (&hOut), 8);
	}

    /// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided scale matrix.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	inline void Scale(const QScaleMatrix3x3 &mScale)
	{
	    QPoint::Scale(mScale, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided scale matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="hOut">[OUT] The scaled hexahedron.</param>
	inline void Scale(const QScaleMatrix3x3 &mScale, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Scale(mScale, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const QScaleMatrix3x3 &mScale, const VectorType &vPivot)
	{
	    QPoint::ScaleFromPivot(mScale, vPivot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method scales the resident hexahedron by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="hOut">[OUT] The scaled hexahedron.</param>
	inline void ScaleFromPivot(const QScaleMatrix3x3 &mScale, const VectorType &vPivot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::ScaleFromPivot(mScale, vPivot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

    /// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	inline void Transform(const QTransformationMatrix4x3 &mTransf)
	{
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="hOut">[OUT] The transformed hexahedron.</param>
	inline void Transform(const QTransformationMatrix4x3 &mTransf, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (&hOut), 8);
	}

    /// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	inline void Transform(const QTransformationMatrix4x4 &mTransf)
	{
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="hOut">[OUT] The transformed hexahedron.</param>
	inline void Transform(const QTransformationMatrix4x4 &mTransf, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (&hOut), 8);
	}

    /// <summary>
	/// This method transforms the resident hexahedron applying the provided space conversion matrix.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	inline void Transform(const QSpaceConversionMatrix &mTransf)
	{
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided space conversion matrix, storing the
	/// resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	/// <param name="hOut">[OUT] The transformed hexahedron.</param>
	inline void Transform(const QSpaceConversionMatrix &mTransf, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (&hOut), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x3 &mTransf, const VectorType &vPivot)
	{
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="hOut">[OUT] The transformed hexahedron.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x3 &mTransf, const VectorType &vPivot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

		/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x4 &mTransf, const VectorType &vPivot)
	{
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (this), 8);
	}

	/// <summary>
	/// This method transforms the resident hexahedron applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant hexahedron in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="hOut">[OUT] The transformed hexahedron.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x4 &mTransf, const VectorType &vPivot, QBaseHexahedron<VectorType> &hOut) const
	{
	    hOut = *this;
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (&hOut), 8);
	}

    /// <summary>
    /// Converts hexahedron into a string with the following format:
    /// "H:A(<A.ToString>), B(<B.ToString>), C(<C.ToString>), D(<D.ToString>),
    /// E(<E.ToString>), F(<F.ToString>), G(<G.ToString>), H(<H.ToString>)".
    /// </summary>
    /// <returns>The string with the specified format.</returns>
    string_q ToString() const
    {
        return QE_L("QL:A(") + this->A.ToString() + QE_L("), B(") + this->B.ToString() + QE_L("), C(") +
                               this->C.ToString() + QE_L("), D(") + this->D.ToString() + QE_L("), E(") +
                               this->E.ToString() + QE_L("), F(") + this->F.ToString() + QE_L("), G(") +
                               this->G.ToString() + QE_L("), H(") + this->H.ToString() + QE_L(")");
    }


protected:

    // Calculates if two points are in the same side of a plane defined by 3 points.
    template <class VectorTypeParam>
    inline bool PointsInSameSideOfPlane(const VectorTypeParam &vP1, const VectorTypeParam &vP2,
        const VectorTypeParam &vA, const VectorTypeParam &vB, const VectorTypeParam &vC) const
    {
        QPlane p(vA, vB, vC);

        const float_q &distP1 = p.a * vP1.x + p.b * vP1.y + p.c * vP1.z + p.d;
        const float_q &distP2 = p.a * vP2.x + p.b * vP2.y + p.c * vP2.z + p.d;

        if ( QFloat::IsLessThan(distP1 * distP2, QFloat::_0) )
            return false;
        else
            return true;
    }
};

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |    CONSTANTS DEFINITIONS	 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

template <class VectorType>
const QHexahedron<VectorType> QHexahedron<VectorType>::UnitCube(-VectorType::VectorOfOnes*QFloat::_0_5, VectorType::VectorOfOnes*QFloat::_0_5);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QHEXAHEDRON__
