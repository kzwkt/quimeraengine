// [TERMS&CONDITIONS]

#ifndef __QRAY2D__
#define __QRAY2D__

#include "QRay.h"
#include "QVector2.h"
#include "QBaseOrb.h"
#include "QBaseTriangle.h"
#include "QBaseQuadrilateral.h"
#include "QLineSegment2D.h"
#include "QTransformationMatrix3x3.h"
#include "EQIntersections.h"

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
/// Represents a ray in 2D space, which consists of a origin point or position, and a direction.<br>
/// The direction symbolizes a line with only one end (which coincides with the point) and that extends to the infinite.
/// </summary>
class QDllExport QRay2D : public QRay<QVector2, QVector2>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QRay2D()
    {
    }

    /// <summary>
    /// Constructor that receives a ray.
    /// </summary>
    /// <param name="ray">[IN] An existing ray.</param>
    inline QRay2D(const QRay<QVector2, QVector2> &ray) : QRay<QVector2, QVector2>(ray)
    {
    }

    /// <summary>
    /// Constructor that receives the ray's position and direction.<br>
    /// The direction vector must be normalized.
    /// </summary>
    /// <param name="vOrigin">[IN] Ray's position.</param>
    /// <param name="vDirection">[IN] Ray's direction.</param>
    /// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    inline QRay2D(const QVector2 &vOrigin, const QVector2 &vDirection) : QRay<QVector2, QVector2>(vOrigin, vDirection)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
	/// Gets a ray placed at the coordinate origin and whose direction vector is null.
	/// </summary>
	/// <returns>
    /// The null ray.
    /// </returns>
    inline static const QRay2D& GetRayZero()
    {
        static const QRay2D RAYZERO(QVector2::GetZeroVector(), QVector2::GetZeroVector());
        return RAYZERO;
    }

    /// <summary>
	/// Gets a ray placed at the coordinate origin and whose direction vector is in X growing direction.
	/// </summary>
	/// <returns>
    /// A ray that points to X direction.
    /// </returns>
    inline static const QRay2D& GetRayX()
    {
        static const QRay2D RAYX(QVector2::GetZeroVector(), QVector2::GetUnitVectorX());
        return RAYX;
    }

    /// <summary>
	/// Gets a ray placed at the coordinate origin and whose direction vector is in Y growing direction.
	/// </summary>
	/// <returns>
    /// A ray that points to Y direction.
    /// </returns>
    inline static const QRay2D& GetRayY()
    {
        static const QRay2D RAYY(QVector2::GetZeroVector(), QVector2::GetUnitVectorY());
        return RAYY;
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assign operator that receives another ray.
    /// </summary>
    /// <param name="ray">[IN] An existing ray.</param>
    /// <returns>
    /// A reference to this ray, after assignation.
    /// </returns>
    inline QRay2D& operator=(const QBaseRay<QVector2, QVector2> &ray)
    {
        QBaseRay<QVector2, QVector2>::operator=(ray);
        return *this;
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided one.
    /// </summary>
    /// <param name="ray">[IN] The ray whose intersection with resident one will be checked.</param>
    /// <returns>
    /// True if both rays intersect, false otherwise.
    /// </returns>
    /// <remarks>
    /// If both rays intesect, the intersection point must verify both vectorial ecuations:
    ///
    /// \f$ P \equiv P_1 + \lambda_1 \cdot D_1 \f$
    ///
    /// \f$ P \equiv P_2 + \lambda_2 \cdot D_2 \f$
    ///
    /// These ecuations can be decomposed by components, obtaining  two equalities:
    ///
    /// 1) \f$ P_{1x} + \lambda_1 \cdot D_{1x} = P_{2x} + \lambda_2 \cdot D_{2x}\f$
    ///
    /// 2) \f$ P_{1y} + \lambda_1 \cdot D_{1y} = P_{2y} + \lambda_2 \cdot D_{2y}\f$
    ///
    /// Finally, both \f$ \lambda_1 \f$ and \f$ \lambda_2 \f$ are forced to be greater or equal to 0, to
    /// ensure ray direction is being followed.<br>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
    bool Intersection(const QBaseRay<QVector2, QVector2> &ray) const;

    /// <summary>
    /// Checks if resident ray intersects with the provided orb.
    /// </summary>
    /// <remarks>
    /// Ray must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersection with resident ray will be checked.</param>
    /// <returns>
    /// True if ray intersect orb, false otherwise.
    /// </returns>
    inline bool Intersection(const QBaseOrb<QVector2> &orb) const
    {
        return QRay<QVector2, QVector2>::Intersection(orb);
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided triangle.
    /// </summary>
    /// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked.</param>
    /// <returns>
    /// True if ray intersect triangle, false otherwise.
    /// </returns>
    inline bool Intersection(const QBaseTriangle<QVector2> &triangle) const
    {
        return ( this->Intersection(triangle.A, triangle.B) ||
                 this->Intersection(triangle.B, triangle.C) ||
                 this->Intersection(triangle.C, triangle.A) );
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided quadrilateral.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral whose intersection with resident ray will be checked.</param>
    /// <returns>
    /// True if ray intersect quadrilateral, false otherwise.
    /// </returns>
    inline bool Intersection(const QBaseQuadrilateral &quad) const
    {
        return ( this->Intersection(quad.A, quad.B) || this->Intersection(quad.B, quad.C) ||
                 this->Intersection(quad.C, quad.D) || this->Intersection(quad.D, quad.A));
    }

	/// <summary>
	/// Computes the intersection point between resident and provided ray, if it exists.
	/// </summary>
    /// <remarks>
	/// Both rays must be normalized to ensure correct result.<br>
	/// If there's no intersection point, or the rays are totally or parcially coincident,
	/// the output parameter used for storing that point won't be modified.<br>
    /// If both rays intesect, the intersection point must verify both vectorial ecuations:
    ///
    /// \f$ P \equiv P_1 + \lambda_1 \cdot D_1 \f$
    ///
    /// \f$ P \equiv P_2 + \lambda_2 \cdot D_2 \f$
    ///
    /// These ecuations can be decomposed by components, obtaining two equalities:
    ///
    /// 1) \f$ P_{1x} + \lambda_1 \cdot D_{1x} = P_{2x} + \lambda_2 \cdot D_{2x}\f$
    ///
    /// 2) \f$ P_{1y} + \lambda_1 \cdot D_{1y} = P_{2y} + \lambda_2 \cdot D_{2y}\f$
    ///
    /// Finally, both \f$ \lambda_1 \f$ and \f$ \lambda_2 \f$ are forced to be greater or equal to 0, to
    /// ensure ray direction is being followed.<br>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
	/// </remarks>
	/// <param name="ray">[IN] The ray whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect, if they do.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the rays, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
    EQIntersections IntersectionPoint(const QBaseRay<QVector2, QVector2> &ray, QBaseVector2 &vIntersection) const;

	/// <summary>
	/// Computes the intersection point between resident ray and provided orb, if it exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection">[OUT] Closest intersection point to ray origin point, if it exists.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// Ray must be normalized to obtain a correct result.<br>
	/// If there's no intersection point, the output parameters won't be modified.<br>
	/// If there's one intersection point, the output parameter stores it.<br>
    /// If there are two intersection points, the output parameter is filled with the closest to the origin point of the ray.
	/// </remarks>
    inline EQIntersections IntersectionPoint(const QBaseOrb<QVector2> &orb, QBaseVector2 &vIntersection) const
    {
        return QRay<QVector2, QVector2>::IntersectionPoint(orb, vIntersection.As<QVector2>());
    }

	/// <summary>
	/// Computes the intersection point between resident ray and provided orb, if it exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection1">[OUT] First point where they intersect, if they do.</param>
	/// <param name="vIntersection2">[OUT] Second point where they intersect, if they do.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// Ray must be normalized to obtain a correct result.<br>
	/// If there's no intersection point, the output parameters won't be modified.<br>
	/// If there's one intersection point, the second output parameter won't be modified,
	/// and first output parameter is filled with the intersection point.<br>
    /// If there are two intersection points, both output parameters are filled with the intersection points, storing
    /// in the first output parameter the closest to the origin point of the ray.
	/// </remarks>
    EQIntersections IntersectionPoint(const QBaseOrb<QVector2> &orb, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
    {
        return QRay<QVector2, QVector2>::IntersectionPoint(orb, vIntersection1.As<QVector2>(), vIntersection2.As<QVector2>());
    }

	/// <summary>
	/// Computes the intersection point between resident ray and provided triangle, if it exists.
	/// </summary>
	/// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection">[OUT] Closest intersection point to ray origin point, if it exists.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the triangle, and can take
    /// the following values: E_None, E_One or E_Two.
	/// </returns>
	/// <remarks>
	/// If there's no intersection point, the output parameter won't be modified.<br>
	/// If there's one intersection point, the output parameter stores it.<br>
    /// If there are two intersection points, the output parameter is filled with the closest to the origin point of the ray.
	/// </remarks>
    EQIntersections IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection) const
    {
        QBaseVector2 vAux;
        return this->IntersectionPoint(triangle, vIntersection, vAux);
    }

	/// <summary>
	/// Computes the intersection point between resident ray and provided triangle, if it exists.
	/// </summary>
	/// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection1">[OUT] First point where they intersect, if they do.</param>
	/// <param name="vIntersection2">[OUT] Second point where they intersect, if they do.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the triangle, and can take
    /// the following values: E_None, E_One or E_Two.
	/// </returns>
	/// <remarks>
	/// If there's no intersection point, the output parameters won't be modified.<br>
	/// If there's one intersection point, the second output parameter won't be modified,
	/// and first output parameter is filled with the intersection point.<br>
    /// If there are two intersection points, both output parameters are filled with the intersection points, storing
    /// in the first output parameter the closest to the origin point of the ray.
	/// </remarks>
    EQIntersections IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const;

	/// <summary>
	/// Computes the intersection point between resident ray and provided quadrilateral, if it exists.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection">[OUT] Closest intersection point to ray origin point, if it exists.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the quadrilateral, and can take
    /// the following values: E_None, E_One or E_Two.
	/// </returns>
	/// <remarks>
	/// If there's no intersection point, the output parameter won't be modified.<br>
	/// If there's one intersection point, the output parameter stores it.<br>
    /// If there are two intersection points, the output parameter is filled with the closest to the origin point of the ray.
	/// </remarks>
    EQIntersections IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection) const
    {
        QBaseVector2 vAux;
        return this->IntersectionPoint(quad, vIntersection, vAux);
    }

	/// <summary>
	/// Computes the intersection point between resident ray and provided quadrilateral, if it exists.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral whose intersection with resident ray will be checked.</param>
	/// <param name="vIntersection1">[OUT] First point where they intersect, if they do.</param>
	/// <param name="vIntersection2">[OUT] Second point where they intersect, if they do.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the quadrilateral, and can take
    /// the following values: E_None, E_One or E_Two.
	/// </returns>
	/// <remarks>
	/// If there's no intersection point, the output parameters won't be modified.<br>
	/// If there's one intersection point, the second output parameter won't be modified,
	/// and first output parameter is filled with the intersection point.<br>
    /// If there are two intersection points, both output parameters are filled with the intersection points, storing
    /// in the first output parameter the closest to the origin point of the ray.
	/// </remarks>
    EQIntersections IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const;

    /// <summary>
    /// Checks if resident ray and provided line segment intersects.
    /// </summary>
    /// <param name="segment">[IN] The line segment whose intersection with resident ray will be checked.</param>
    /// <returns>
    /// True if line segment and resident ray intersects, false otherwise.
    /// </returns>
    bool Intersection(const QBaseLineSegment<QVector2> &segment) const;

    /// <summary>
    /// Computes the intersection point between resident ray and provided line segment, if it exists.
    /// </summary>
    /// <param name="segment">[IN] The line segment whose intersection with resident ray will be checked.</param>
    /// <param name="vIntersection">[OUT] The intersection point with line segment, if it exists.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the ray and the quadrilateral, and can take
    /// the following values: E_None, E_One or E_Infinite.
    /// </returns>
    /// <remarks>
    /// If there's no intersection point, the output parameters won't be modified.<br>
    /// If there's one intersection point, output parameter is filled with the intersection point.<br>
    /// If there are infinite intersection points, the output parameters won't be modified.
    /// </remarks>
    EQIntersections IntersectionPoint(const QBaseLineSegment<QVector2> &segment, QBaseVector2 &vIntersection) const;

    /// <summary>
	/// Computes a ray that is the result of resident ray reflection on the line segment provided.
	/// </summary>
	/// <param name="segment">[IN] The line segment which acts as mirror.</param>
	/// <param name="ray">[OUT] The reflected ray.</param>
	/// <remarks>
	/// Ray direction must be normalized to obtain a correct result.<br>
	/// If there's no intersection point between ray and line segment, or are both coincident or parallel,
	/// reflected ray is the resident ray itself.<br>
	/// If there's one intersection point between them, then the reflected ray has it origin point at the intersection point
	/// and its direction verifies that the incident angle and the reflected angle are equals.
	/// </remarks>
    inline void Reflection(const QBaseLineSegment<QVector2> &segment, QBaseRay<QVector2, QVector2> &ray) const
    {
        //Method based in this: http://www.inmensia.com/articulos/raytracing/mecanismosluz.html

        QVector2 vAux = QVector2(segment.B - segment.A).Normalize();

        ray = *this;

        // Avoiding cases where ray and line segment are parallels or coincident.
        if (vAux == this->Direction || vAux == -this->Direction)
            return;
        else
        {
            QVector2 vPoint;
            EQIntersections numInt = this->IntersectionPoint(segment, vPoint);
            if (numInt == EQIntersections::E_One)
            {
                // Reflected origin is the intersection point
                ray.Origin = vPoint;

                // Calculates normal to line segment (is normalized like vAux)
                QVector2 vNorm = vAux.GetPerpendicular();

                // Calculates reflected direction
                ray.Direction -= SQFloat::_2 * (this->Direction.DotProduct(vNorm)) * vNorm;
            }
        }
    }

    /// <summary>
	/// Computes a vector that is the resultant direction of resident ray reflection on the line segment provided.
	/// </summary>
	/// <param name="segment">[IN] The line segment which acts as mirror.</param>
	/// <param name="vDirection">[OUT] The direction of the reflected ray.</param>
	/// <remarks>
	/// Ray direction must be normalized to obtain a correct result.<br>
	/// If there's no intersection point between ray and line segment, or are both coincident or parallel,
	/// reflected ray is the resident ray itself.<br>
	/// If there's one intersection point between them, then the reflected ray direction verifies
	/// that the incident angle and the reflected angle are equals.
	/// </remarks>
    inline void Reflection(const QBaseLineSegment<QVector2> &segment, QBaseVector2 &vDirection) const
    {
        //Method based in this: http://www.inmensia.com/articulos/raytracing/mecanismosluz.html

        QVector2 vAux = QVector2(segment.B - segment.A).Normalize();

        vDirection = this->Direction;

        // Avoiding cases where ray and line segment are parallels or coincident.
        if (vAux == this->Direction || vAux == -this->Direction)
            return;
        else if (this->Intersection(segment))
        {
            // Calculates normal to line segment (is normalized like vAux)
            QVector2 vNorm = vAux.GetPerpendicular();

            // Calculates reflected direction
            vDirection = this->Direction - SQFloat::_2 * (this->Direction.DotProduct(vNorm)) * vNorm;
        }
    }

    /// <summary>
	/// Applies the transformation given by the matrix provided to resident ray.
	/// </summary>
	/// <param name="transformation">[IN] The transformation matrix to be applied.</param>
	/// <remarks>
	/// Resultant ray is normalized after this operation.<br>
	/// All transformations affects both origin ray point and ray direction, except translations,
	/// that only affects origin ray point.
	/// </remarks>
    /// <returns>
    /// The transformed ray.
    /// </returns>
	inline QRay2D Transform(const QTransformationMatrix3x3 &transformation) const
	{
        QRay2D auxRay = *this;
	    auxRay.Origin = auxRay.Origin.Transform(transformation);

        // Direction is transformed without translation. The calculation takes into account only the submatrix that contains
        // the rotation and the scale.
        const float_q fNewX = this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0];
        const float_q fNewY = this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1];

        auxRay.Direction = QVector2(fNewX, fNewY).Normalize();

        return auxRay;
	}
    
    /// <summary>
	/// This method rotates the resident ray the provided angle around the coordinate axis centre.
	/// </summary>
	/// <param name="fRotationAngle">[IN] Angle of rotation.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
	inline QRay2D Rotate(const float_q &fRotationAngle) const
	{
        QRay2D auxRay = *this;
        SQPoint::Rotate(fRotationAngle, auxRay.AsPtr<QVector2>(), 2);
        return auxRay;
	}


    /// <summary>
	/// This method rotates the resident ray the provided angle around the point provided as pivot.
	/// </summary>
	/// <param name="fRotationAngle">[IN] Angle of rotation.</param>
	/// <param name="vPivot">[IN] Point which acts as pivot.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
	inline QRay2D RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot) const
	{
        QRay2D auxRay = *this;
        SQPoint::RotateWithPivot(fRotationAngle, vPivot, &auxRay.Origin, 1);
        SQPoint::Rotate(fRotationAngle, &auxRay.Direction, 1);
        return auxRay;
	}

    /// <summary>
	/// This method translates the resident ray by the translation contained in the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
	inline QRay2D Translate(const QBaseVector2 &vTranslation) const
	{
        QRay2D auxRay = *this;
        SQPoint::Translate(vTranslation, &auxRay.Origin, 1);
        return auxRay;
	}
    
    /// <summary>
	/// This method translates the resident ray by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] Amount of translation in X direction.</param>
	/// <param name="fTranslationY">[IN] Amount of translation in Y direction.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
	inline QRay2D Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
	{
        QRay2D auxRay = *this;
        SQPoint::Translate(fTranslationX, fTranslationY, &auxRay.Origin, 1);
        return auxRay;
	}
    
    /// <summary>
	/// This method scales the resident ray by the scale contained in the provided vector.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay2D Scale(const QBaseVector2 &vScale) const
	{
        QRay2D auxRay = *this;
        SQPoint::Scale(vScale, auxRay.AsPtr<QVector2>(), 2);
        return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
	}
    
    /// <summary>
	/// This method scales the resident ray by the amounts provided for every axis.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScaleX">[IN] Scale to be applied in X direction.</param>
	/// <param name="vScaleY">[IN] Scale to be applied in Y direction.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay2D Scale(const float_q &vScaleX, const float_q &vScaleY) const
	{
        QRay2D auxRay = *this;
        SQPoint::Scale(vScaleX, vScaleY, auxRay.AsPtr<QVector2>(), 2);
        return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method scales the resident ray by the scale contained in the provided vector from
	/// the provided point that acts as pivot.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay2D ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const
	{
        QRay2D auxRay = *this;
        SQPoint::ScaleWithPivot(vScale, vPivot, &auxRay.Origin, 1);
        SQPoint::Scale(vScale, &auxRay.Direction, 1);
        return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method scales the resident ray by the amounts provided for every axis from
	/// the provided point that acts as pivot.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="vScaleX">[IN] Scale to be applied in X direction.</param>
	/// <param name="vScaleY">[IN] Scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
	inline QRay2D ScaleWithPivot(const float_q &vScaleX, const float_q &vScaleY, const QBaseVector2 &vPivot) const
	{
        QRay2D auxRay = *this;
        SQPoint::ScaleWithPivot(vScaleX, vScaleY, vPivot, &auxRay.Origin, 1);
        SQPoint::Scale(vScaleX, vScaleY, &auxRay.Direction, 1);
        return QRay2D(auxRay.Origin, auxRay.Direction.Normalize());
	}

    /// <summary>
	/// This method applies the transformation contained in the provided transformation matrix from
	/// the provided point that acts as pivot.
	/// </summary>
    /// <remarks>
	/// Resultant ray is normalized after this operation.
	/// </remarks>
	/// <param name="transformation">[IN] Tranformation matrix to be applied.</param>
	/// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
	inline QRay2D TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const
	{
        QRay2D auxRay = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, &auxRay.Origin, 1);

        const float_q fNewX = this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0];
        const float_q fNewY = this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1];

        auxRay.Direction = QVector2(fNewX, fNewY).Normalize();

        return auxRay;
	}

protected:

    // Checks if resident ray contains a given point.
    bool Contains(const QVector2 &vPoint) const
    {
        if (this->Origin == vPoint)
            return true;
        else if ( SQFloat::IsZero(this->Direction.x) )
        {
            if ( SQFloat::AreNotEquals(vPoint.x, this->Origin.x) )
                return false;
            if ( SQFloat::IsNegative(vPoint.y - this->Origin.y) == SQFloat::IsNegative(this->Direction.y) )
                return true;
            else
                return false;
        }
        else if ( SQFloat::IsZero(this->Direction.y) )
        {
            if ( SQFloat::AreNotEquals(vPoint.y, this->Origin.y) )
                return false;
            if ( SQFloat::IsNegative(vPoint.x - this->Origin.x) == SQFloat::IsNegative(this->Direction.x) )
                return true;
            else
                return false;
        }
        else
        {
            const float_q &paramX = (vPoint.x - this->Origin.x)/this->Direction.x;
            const float_q &paramY = (vPoint.y - this->Origin.y)/this->Direction.y;

            if ( SQFloat::AreNotEquals(paramX, paramY) || SQFloat::IsNegative(paramX))
                return false;
            else
                return true;
        }

    }

    // Checks if resident ray intersects the AB line segment
    bool Intersection(const QVector2 &vA, const QVector2 &vB) const
    {
        return this->Intersection(QBaseLineSegment<QVector2>(vA, vB));
    }

    // Checks if resident ray intersects the AB line segment and calculates the intersection point if exists
    EQIntersections IntersectionPoint(const QVector2 &vA, const QVector2 &vB, QBaseVector2 &vIntersection) const
    {
        return this->IntersectionPoint(QBaseLineSegment<QVector2>(vA, vB), vIntersection);
    }

    // Checks if a point is inside a triangle.
	// [TODO] jwladi: Replace by the QTriangle2D or QTriangle Contains method, when it exists.
	inline bool PointInsideTriangle(const QBaseTriangle<QVector2>& triangle, const QVector2& vPoint) const
	{
        return ( PointsInSameSideOfLine(vPoint, triangle.A, triangle.B, triangle.C) &&
                 PointsInSameSideOfLine(vPoint, triangle.B, triangle.C, triangle.A) &&
                 PointsInSameSideOfLine(vPoint, triangle.C, triangle.A, triangle.B) );
	}

    // Check if two points are in the same side of a line.
	inline bool PointsInSameSideOfLine(const QVector2 &vP1, const QVector2 &vP2, const QVector2 &vLine1, const QVector2 &vLine2) const
	{
        const float_q &fOrientation1 = (vLine1.x - vP1.x)*(vLine2.y - vP1.y) - (vLine1.y - vP1.y)*(vLine2.x - vP1.x);
        const float_q &fOrientation2 = (vLine1.x - vP2.x)*(vLine2.y - vP2.y) - (vLine1.y - vP2.y)*(vLine2.x - vP2.x);

        if ( SQFloat::IsZero(fOrientation1) || SQFloat::IsZero(fOrientation2) )
            return true;
        else if ( SQFloat::IsNegative(fOrientation1) == SQFloat::IsNegative(fOrientation2) )
            return true;
        else
            return false;
	}

	// Checks if a point is inside a quadrilateral.
	// [TODO] jwladi: Replace by the QQuadrilateral Contains method, when it exists.
	inline bool PointInsideQuadrilateral(const QBaseQuadrilateral& quad, const QVector2& vPoint) const
	{
	    return ( PointsInSameSideOfLine(vPoint, quad.C, quad.A, quad.B) &&
                 PointsInSameSideOfLine(vPoint, quad.A, quad.B, quad.C) &&
                 PointsInSameSideOfLine(vPoint, quad.A, quad.C, quad.D) &&
                 PointsInSameSideOfLine(vPoint, quad.C, quad.D, quad.A) );
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QRAY2D__
