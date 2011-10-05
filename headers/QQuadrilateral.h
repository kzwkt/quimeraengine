// [TERMS&CONDITIONS]

#ifndef __QQUADRILATERAL__
#define __QQUADRILATERAL__

#include "QBaseQuadrilateral.h"
#include "QLineSegment2D.h"
#include "QVector2.h"
#include "QAngle.h"

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
/// Class which represents a quadrilateral in 2D space. Methods in this class are related to transformations in 2D.
/// The quadrilateral is defined by four consecutive vertices A, B, C, D, being the edges AB, BC, CD and DA segments.
/// </summary>
class QDllExport QQuadrilateral : public QBaseQuadrilateral
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Stores a square with center in coordinate origin and unitary length edges which are parallels to axes.
    /// </summary>
    static const QQuadrilateral UnitSquare;

	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QQuadrilateral() { }

    /// <summary>
    /// Constructor from four 2D vectors.
    /// </summary>
    /// <remarks>
    /// Note that the four vertices must be consecutive, so that the egdes of the quadrilateral must be AB, BC, CD and DA.
    /// </remarks>
    /// <param name="vA">[IN] The 2D vector which defines A vertex.</param>
    /// <param name="vB">[IN] The 2D vector which defines B vertex.</param>
    /// <param name="vC">[IN] The 2D vector which defines C vertex.</param>
    /// <param name="vD">[IN] The 2D vector which defines D vertex.</param>
    inline QQuadrilateral(const QVector2 &vA, const QVector2 &vB,
                          const QVector2 &vC, const QVector2 &vD ) : QBaseQuadrilateral(vA, vB, vC, vD) { }


    // METHODS
    // ---------------
public:

    //Unary operators

    /// <summary>
    /// Assign operator. Assigns the provided quadrilateral to the resident quadrilateral.
    /// </summary>
    /// <param name="q">[IN] The quadrilateral to be assigned.</param>
    /// <returns>
    /// A reference to the modified quadrilateral.
    /// </returns>
    inline QQuadrilateral& operator=(const QBaseQuadrilateral &q)
    {
        reinterpret_cast<QBaseQuadrilateral&>(*this) = q;
        return *this;
    }

    //Methods

    /// <summary>
    /// Checks if a given point is inside quadrilateral or not. This is made in a different way depending on the
    /// kind of quadrilateral we have (crossed, standard convex or concave).
    /// </summary>
    /// <param name="v">[IN] The point we want to check.</param>
    /// <returns>
    /// True if the given point is inside quadrilateral, false otherwise.
    /// The quadrilateral perimeter is considered inside.
    /// </returns>
    bool Contains (const QBaseVector2 &v) const;

    /// <summary>
    /// Checks if the resident quadrilateral intersects with the provided one. To do that, it checks the intersection
    /// with the four segments of the resident quadrilateral with the provided quadrilateral. Additionally, it checks if
    /// one arbitrary edge of provided quadrilateral intersects with the resident one, to check the case where the provided
    /// quadrilateral is included in the resident one.
    /// </summary>
    /// <param name="q">[IN] The quadrilateral we want to check the intersection with resident one.</param>
    /// <returns>
    /// True if the given quadrilateral intersects with resident quadrilateral, false otherwise.
    /// </returns>
    inline bool Intersection (const QBaseQuadrilateral &q) const
    {

        // Checks if any edge of resident quadrilateral intersects with q
        QLineSegment2D ls1(this->A, this->B);
        if ( ls1.Intersection(q) )
            return true;

        ls1 = QLineSegment2D(this->B, this->C);
        if ( ls1.Intersection(q) )
            return true;

        ls1 = QLineSegment2D(this->C, this->D);
        if ( ls1.Intersection(q) )
            return true;

        ls1 = QLineSegment2D(this->D, this->A);
        if ( ls1.Intersection(q) )
            return true;

        // q may be contained by resident quadrilateral, we check it.
        if ( this->Contains(q.A) )
            return true;

        return false;
    }

    /// <summary>
    /// Checks if the resident quadrilateral is crossed. To do that, it checks if A and D vertices are in the
    /// same side of BC segment AND C and D vertices are in the same side of AB segment, in which case the quadrilateral
    /// is not crossed.
    /// </summary>
    /// <returns>
    /// True if the resident quadrilateral is crossed, false otherwise.
    /// </returns>
    inline bool IsCrossed () const
    {
        if ( ( !PointsInSameSideOfLine(this->A, this->D, this->B, this->C) &&
               !PointsInSameSideOfLine(this->C, this->B, this->A, this->D) ) ||
             ( !PointsInSameSideOfLine(this->A, this->B, this->D, this->C) &&
               !PointsInSameSideOfLine(this->C, this->D, this->A, this->B) ) )
            return true;
        else
            return false;
    }

    /// <summary>
    /// Checks if the resident quadrilateral is convex. To do that, it checks if the quadrilateral diagonals intersects.
    /// </summary>
    /// <remarks>
    /// Crossed quadrilaterals are considered as convex. Quadrilaterals with a 180º angle are considered convex too.
    /// </remarks>
    /// <returns>
    /// True if the resident quadrilateral is convex, false otherwise.
    /// </returns>
    inline bool IsConvex () const
    {
        // [TODO] jwladi: May be it can be optimized if it is considered that most of quadrilateral are convex

        if (this->IsCrossed()) // Crossed quadrilateral diagonals don't intersects.
            return true;

        QLineSegment2D ls1(this->A, this->C);
        QLineSegment2D ls2(this->B, this->D);

        if (ls1.Intersection(ls2))
            return true;
        else
            return false;
    }

    /// <summary>
    /// Checks if the resident quadrilateral is concave.
    /// </summary>
    /// <returns>
    /// True if the resident quadrilateral is concave, false otherwise.
    /// </returns>
    inline bool IsConcave () const
    {
        return !this->IsConvex();
    }

    /// <summary>
    /// Computes the interior angle between AB and AD edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    inline float_q GetAngleA() const
    {
        const float_q &fAngle = (this->D - this->A).DotProductAngle(this->B - this->A);

        if (this->IsConcaveHere(this->A, this->B, this->D, this->C))
        {
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                return QAngle::_360 - fAngle;
            #else
                return QAngle::_2Pi - fAngle;
            #endif
        }
        else
            return fAngle;
    }

    /// <summary>
    /// Computes the interior angle between BC and BA edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    inline float_q GetAngleB() const
    {
        const float_q &fAngle = (this->A - this->B).DotProductAngle(this->C - this->B);

        if (this->IsConcaveHere(this->B, this->A, this->C, this->D))
        {
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                return QAngle::_360 - fAngle;
            #else
                return QAngle::_2Pi - fAngle;
            #endif
        }
        else
            return fAngle;
    }

    /// <summary>
    /// Computes the angle between CD and CB edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    inline float_q GetAngleC() const
    {
        const float_q &fAngle = (this->B - this->C).DotProductAngle(this->D - this->C);

        if (this->IsConcaveHere(this->C, this->B, this->D, this->A))
        {
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                return QAngle::_360 - fAngle;
            #else
                return QAngle::_2Pi - fAngle;
            #endif
        }
        else
            return fAngle;
    }

    /// <summary>
    /// Computes the angle between DA and DC edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    inline float_q GetAngleD() const
    {
        const float_q &fAngle = (this->C - this->D).DotProductAngle(this->A - this->D);

        if (this->IsConcaveHere(this->D, this->A, this->C, this->B))
        {
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                return QAngle::_360 - fAngle;
            #else
                return QAngle::_2Pi - fAngle;
            #endif
        }
        else
            return fAngle;
    }

    /// <summary>
    /// Converts quadrilateral into a string with the following format:
    /// "QL:A(<A.ToString>), B(<B.ToString>), C(<C.ToString>), D(<D.ToString>)".
    /// </summary>
    /// <returns>The string with the specified format.</returns>
    inline string_q ToString()
    {
        return QE_L("QL:A(") + this->A.ToString() + QE_L("), B(") +
                               this->B.ToString() + QE_L("), C(") +
                               this->C.ToString() + QE_L("), D(") +
                               this->D.ToString() + QE_L(")");
    }

protected:

    // Calculates if two points are in the same side of a line segment. Used to know if
    // a quadrilateral is crossed, and to check if a point is inside a triangle.
    // In 2D case, I think is more efficient than the baricentric method.
    // It is bassed on the orientation of the two tringles compossed by
    // each point of the two we want to check and the end points of the line. If both triangles have
    // the same orientation, both points are in the same side of the line.
    bool PointsInSameSideOfLine(const QBaseVector2 &vP1, const QBaseVector2 &vP2,
                                const QBaseVector2 &vLine1, const QBaseVector2 &vLine2) const
    {

        const float_q &fOrientation1 = (vLine1.x - vP1.x)*(vLine2.y - vP1.y) - (vLine1.y - vP1.y)*(vLine2.x - vP1.x);
        const float_q &fOrientation2 = (vLine1.x - vP2.x)*(vLine2.y - vP2.y) - (vLine1.y - vP2.y)*(vLine2.x - vP2.x);

        if ( QFloat::IsZero(fOrientation1) || QFloat::IsZero(fOrientation2) )
            return true;
        else if ( QFloat::IsNegative(fOrientation1) == QFloat::IsNegative(fOrientation2) )
            return true;
        else
            return false;
    }

    // Checks if exists concavity in the "AngleVertex" vertex.
    // AngleEndVertex1 and 2 are the two vertices in the end of the segments which defines the angle (adjacent vertices)
    bool IsConcaveHere(const QVector2 &AngleVertex, const QVector2 &AngleEndVertex1,
                   const QVector2 &AngleEndVertex2, const QVector2 &OppositeVertex) const
    {
        if (this->IsConvex())
            return false;
        else if ( !PointsInSameSideOfLine(OppositeVertex, AngleVertex, AngleEndVertex1, AngleEndVertex2) )
            return false; // The outer diagonal should not divide quadrilateral
        else
        {
            QLineSegment2D ls(AngleEndVertex1, AngleEndVertex2);

            // Angle vertex must be the closest to outer diagonal
            if ( ls.MinDistance(AngleVertex) < ls.MinDistance(OppositeVertex) )
                return true;
            else
                return false;
        }
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QQUADRILATERAL__
