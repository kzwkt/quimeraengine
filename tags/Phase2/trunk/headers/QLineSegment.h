//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __QLINESEGMENT__
#define __QLINESEGMENT__

#include "EQIntersections.h"
#include "QBaseLineSegment.h"
#include "QBaseOrb.h"
#include "SQAngle.h"
#include "MathDefinitions.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a chunk (segment) of straight line in the space, defined by two endpoints A and B.
/// </summary>
/// <remarks>
/// These points may be expressed as 2D or 3D points or vectors, depending on the template parameter,
/// which may be 2D vector, 3D vector or 4D vector.<br/>
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment
/// except for the unit line (see below).
/// </remarks>
/// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
template <class VectorType>
class QLineSegment : public QBaseLineSegment<VectorType>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QBaseLineSegment<VectorType>::A;
    using QBaseLineSegment<VectorType>::B;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QLineSegment()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="segment">[IN] The segment from which we want to create a copy in the resident segment.</param>
    QLineSegment(const QLineSegment<VectorType> &segment) : QBaseLineSegment<VectorType>(segment)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="segment">[IN] The segment in which we want resident segment to be based.</param>
    QLineSegment(const QBaseLineSegment<VectorType> &segment) : QBaseLineSegment<VectorType>(segment)
    {
    }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
    QLineSegment(const VectorType &vA, const VectorType &vB) : QBaseLineSegment<VectorType>(vA,vB)
    {
    }

    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
    /// <returns>
    /// A 1-length segment.
    /// </returns>
    static const QLineSegment<VectorType>& GetUnitLine()
    {
        static const QLineSegment<VectorType> UNITLINE(VectorType::GetNullVector(), VectorType::GetUnitVectorX());
        return UNITLINE;
    }

    /// <summary>
    /// Gets a zero segment lying in the coordinates center whose endpoints
    /// both equals to (0,0) and it's length equals 0.
    /// </summary>
    /// <returns>
    /// A zero-length segment.
    /// </returns>
    static const QLineSegment<VectorType>& GetLineZero()
    {
        static const QLineSegment<VectorType> LINEZERO(VectorType::GetNullVector(), VectorType::GetNullVector());
        return LINEZERO;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assigning operator.
    /// </summary>
    /// <param name="segment">[IN] The 2D segment to be copied from.</param>
    /// <returns>
    /// A reference to the modified line segment.
    /// </returns>
    QLineSegment& operator=(const QBaseLineSegment<VectorType> &segment)
    {
        QBaseLineSegment<VectorType>::operator=(segment);
        return *this;
    }

    /// <summary>
    /// Computes the length of the segment, that is, the distance between the segment endpoints A and B.
    /// </summary>
    /// <returns>
    /// The resultant distance between the two endpoints.
    /// </returns>
    float_q GetLength() const
    {
        return A.Distance(B);
    }

    /// <summary>
    /// Computes the central point of the segment.
    /// </summary>
    /// <returns>
    /// The center of the segment.
    /// </returns>
    VectorType GetCenter() const
    {
        // 1) Direction: AB --> B - A, so that: S(t) = A + [t(B - A)] = ... = t(A + B)
        // 2) Center:    S(0.5) --> A + [0.5(B - A)] --> ... --> 0.5(A + B)
        return SQFloat::_0_5 * (A + B);
    }

    /// <summary>
    /// This method receives another line segment, and computes whether they intersect each other or not.
    /// </summary>
    /// <remarks>
    /// If the length of any of both segments equals zero, it will be considered as a point (which is wrong).<br/>
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <param name="segment">[IN] The segment to be compared to.</param>
    /// <returns>
    /// A boolean value that indicates whether the line segments intersect.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The line segments intersect, including the following cases:<br/>
    /// - The segments intersect in one point.
    /// - The segments coincide totally.
    /// - One segment is contained in the other.
    /// - The segments share one endpoint only.
    /// - The segments are overlapped.
    /// - An endpoint of one segment is contained in the other segment.
    ///
    /// <b>False</b><br/>
    /// There is no common point between both segments.
    /// </returns>
    bool Intersection(const QBaseLineSegment<VectorType> &segment) const
    {
        // The endpoints of a segment should not coincide
        QE_ASSERT_WARNING(this->A != this->B && segment.A != segment.B, "The endpoints of a segment should not coincide");

        // if MinDistance is 0          --> there's intersection, return true
        // else                          --> return false
        return SQFloat::IsZero(this->MinDistance(segment));
    }

    /// <summary>
    /// This method receives a orb, and computes if it intersects the resident segment or not.
    /// </summary>
    /// <remarks>
    /// If the length of the segment or the radius of the orb equal zero, the orb or the segment will be considered as a point (which is wrong).<br/>
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <param name="orb">[IN] The orb to be compared to.</param>
    /// <returns>
    /// A boolean value that indicates whether the line segments intersect.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The line segment and the orb intersect, including the following cases:<br/>
    /// - Only one endpoint of the segment is inside the orb.
    /// - The line is tangent to the orb by an endpoint.
    /// - The line is totally contained in the orb.
    /// - The line intersects with the orb in two points.
    /// - The line is tangent to the orb by one point between both endpoints.
    ///
    /// <b>False</b><br/>
    /// There is no common point between the segment and the orb.
    /// </returns>
    bool Intersection(const QBaseOrb<VectorType> &orb) const
    {
        // The endpoints of a segment should not coincide and the radius should be greater than zero
        QE_ASSERT_WARNING(this->A != this->B && SQFloat::IsGreaterThan(orb.Radius, SQFloat::_0), "The end points of a segment should not coincide and the radius should be greater than zero (either or both of this rules may have failed)");

        // An intersection between the segment and the orb is considered if the minimum
        // distance between "the whole segment" and the center of the orb (this is, the
        // minimum distance between the center of the orb and the closest point inside
        // the segment) is either lesser or equal to the radius of the orb.
        return SQFloat::IsLessOrEquals(this->MinDistance(orb.Center), orb.Radius);
    };

    /// <summary>
    /// This method receives another line segment, and computes the intersection point between them, if it exists.
    /// </summary>
    /// <remarks>
    /// If the length of any of both segments equals zero, it will be considered as a point (which is wrong).<br/>
    /// If there's no intersection points or if they are infinite, the output parameters used for storing these points won't be modified.<br/>
    /// If there is any intersection, the first parameter will be set to the closest one to the resident line's A endpoint.
    /// </remarks>
    /// <param name="segment">[IN] The segment to be compared to.</param>
    /// <param name="vIntersection">[OUT] The point where they intersect that is closest to A (of resident segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The segments intersect in one point only, between A and B endpoints.
    /// - An endpoint of one segment is contained in the other segment.
    /// - The segments share one endpoint.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segments coincide partially, so each one has an endpoint inside the other.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The line segments are the same
    /// - One segment is contained in the other.
    /// </returns>
    EQIntersections IntersectionPoint(const QBaseLineSegment<VectorType> &segment, VectorType &vIntersection) const
     {
        // The endpoints of a segment should not coincide
        QE_ASSERT_WARNING(this->A != this->B && segment.A != segment.B, "The endpoints of a segment should not coincide");

        // Remark: S1 == (*this), Segment S2 == the input segment parameter.

        VectorType v1 = this->B - this->A;
        VectorType v2 = segment.B - segment.A;

        const float_q& V1_SQUARED_LENGTH = v1.GetSquaredLength();
        const float_q& V2_SQUARED_LENGTH = v2.GetSquaredLength();
        float_q fSqrLengthProd = V1_SQUARED_LENGTH * V2_SQUARED_LENGTH;

        if ( SQFloat::IsZero(fSqrLengthProd) )
        {
            // At least one of the segments' length equals zero
            if(SQFloat::IsZero(V1_SQUARED_LENGTH) && SQFloat::IsZero(V2_SQUARED_LENGTH))
            {
                if(*this == segment)
                {
                    // Both endpoints coincide
                    return EQIntersections::E_Infinite;
                }
                else
                {
                    // No intersections
                    return EQIntersections::E_None;
                }
            }
            else if(SQFloat::IsZero(V1_SQUARED_LENGTH))
            {
                if(SQFloat::IsZero(this->MinDistance(segment)))
                {
                    vIntersection = this->A;
                    return EQIntersections::E_Two;
                }
                else
                {
                    // No intersections
                    return EQIntersections::E_None;
                }
            }
            else // if(SQFloat::IsZero(V2_SQUARED_LENGTH)
            {
                if(SQFloat::IsZero(this->MinDistance(segment)))
                {
                    vIntersection = segment.A;
                    return EQIntersections::E_Two;
                }
                else
                {
                    // No intersections
                    return EQIntersections::E_None;
                }
            }
        }
        else // Neither segments have length 0 --> fSqrLengthProd ALWAYS > 0 at this stage.
        {

            // Compute the sinus of the angle between v1 and v2.

            float_q fAngle = v1.AngleBetween(v2);

            // If angles are currently specified in degrees, then converts angle to radians
            // so we can use "sin" function.
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                fAngle = SQAngle::DegreesToRadians(fAngle);
            #endif

            // At this stage we have the angle expressed in RADIANS.
            float_q fSin   = sin_q(fAngle);

            // Compute Squared Module of cross product:
            float_q fSquaredMod = fSqrLengthProd * fSin * fSin;

            if ( SQFloat::IsNotZero(fSquaredMod) )
            {
                // CASE 2)
                // In this case, the situation is as follows:
                //
                //  -The lines containing the segments doesn't intersect between themselves,
                //     so the same can be said for the segments.
                // OR
                //    -The lines containing the segments intersect in a single point...
                //     ...but do the segments make the same?.
                //
                //  For asking these questions we need the closest points to each segment
                //  from respect the other one.
                VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
                this->GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

                if (vClosestPtInS1ToS2 == vClosestPtInS2ToS1)
                {
                    // Segments intersect each other IN A SINGLE POINT.

                    vIntersection = vClosestPtInS1ToS2; // The same with vClosestPtInS2ToS1.
                    return EQIntersections::E_One;
                }
                else
                {
                    // Segments doesn't intersect each other either:
                    //  - The lines containing the segments DOESN'T intersect between themselves.
                    // OR
                    //  - The lines containing the segments DOES intersect between themselves in a single point...
                    //      ...but that intersection occurs "outside" of the segments, it's not a point belonging
                    //      to them.

                    return EQIntersections::E_None;
                }
            }
            else // 0 == fSquaredMod
            {
                // CASE 3)
                // In this case, the situation is as follows:
                //
                //  -The lines containing the segments are PARALLEL between themselves, so do the segments --> NO intersections.
                // OR
                //  -Both segments lie on the SAME line, so there can be:
                //
                //       -No intersection points.
                //       -One single intersection point.
                //       -Two intersection points.
                //     -Infinite intersection points.
                //
                //   It may depend of the situation, more info provided below on the walk.

                float_q fMinDistance = this->MinDistance(segment);

                if ( SQFloat::IsNotZero(fMinDistance) ) // fMinDistance always nonnegative --> fMinDistance > 0
                {
                    // fMinDistance > 0 -->  -Segments are PARALLEL
                    //                        OR
                    //                         -They lie on the same line, but they DON'T intersect.
                    //
                    //                        Anyway, NO intersections.

                    return EQIntersections::E_None;
                }
                else // 0 == fMinDistance, Intersection Points: One OR Infinite.
                {
                    // BOTH segments lie on the SAME line --> Angle (v1,v2) == 0 OR 180 degrees <-- Please note at this stage v1.DotProduct(v2) ALWAYS != 0

                    // Note: r = resident (this), i = input (segment)

                    if(this->A == segment.A)
                    {
                        if(this->B == segment.B)
                        {
                            // ArAi---BrBi
                            return EQIntersections::E_Infinite; 
                        }
                        else
                        {
                            vIntersection = this->A;

                            // Reference vector for all the comparisons
                            const VectorType& ArBr = this->B - this->A;

                            const VectorType& ArBi = segment.B - this->A;

                            if(SQFloat::IsNegative( ArBi.DotProduct(ArBr) ))
                            {
                                // Br---ArAi---Bi
                                //       I1
                                return EQIntersections::E_One;
                            }
                            else
                            {
                                // ArAi---Br---Bi
                                //  I1    I2
                                //
                                // or
                                //
                                // ArAi---Bi---Br
                                //  I1    I2
                                return EQIntersections::E_Two;
                            }
                        }
                    }
                    else if(this->A == segment.B)
                    {
                        if(this->B == segment.A)
                        {
                            // ArBi---BrAi
                            return EQIntersections::E_Infinite;
                        }
                        else
                        {
                            vIntersection = this->A;

                            // Reference vector for all the comparisons
                            const VectorType& ArBr = this->B - this->A;

                            const VectorType& ArAi = segment.A - this->A;

                            if(SQFloat::IsNegative( ArAi.DotProduct(ArBr) ))
                            {
                                // Br---ArBi---Ai
                                //        I1
                                return EQIntersections::E_One;
                            }
                            else
                            {
                                // ArBi---Ai---Br
                                //  I1    I2
                                //
                                // or
                                //
                                // ArBi---Br---Ai
                                //  I1    I2
                                return EQIntersections::E_Two;
                            }
                        }
                    }
                    else if(this->B == segment.A)
                    {
                        // Reference vector for all the comparisons
                        const VectorType& ArBr = this->B - this->A;

                        const VectorType& BrBi = segment.B - this->B;

                        if(SQFloat::IsNegative( BrBi.DotProduct(ArBr) ))
                        {
                            const VectorType& ArBi = segment.B - this->A;

                            if(SQFloat::IsNegative( ArBi.DotProduct(ArBr) ))
                            {
                                // AiBr---Ar---Bi
                                //  I2    I1
                                vIntersection = this->A;
                            }
                            else
                            {
                                // AiBr---Bi---Ar
                                //  I2    I1
                                vIntersection = segment.B;
                            }

                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            // Ar---AiBr---Bi
                            //        I1
                            vIntersection = this->B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if(this->B == segment.B)
                    {
                        // Reference vector for all the comparisons
                        const VectorType& ArBr = this->B - this->A;

                        const VectorType& BrAi = segment.A - this->B;

                        if(SQFloat::IsNegative( BrAi.DotProduct(ArBr) ))
                        {
                            const VectorType& ArAi = segment.A - this->A;

                            if(SQFloat::IsNegative( ArAi.DotProduct(ArBr) ))
                            {
                                // BrBi---Ar---Ai
                                //  I2    I1
                                vIntersection = this->A;
                            }
                            else
                            {
                                // BrBi---Ai---Ar
                                //  I2    I1
                                vIntersection = segment.A;
                            }

                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            // Ar---BrBi---Ai
                            //        I1
                            vIntersection = this->B;
                            return EQIntersections::E_One;
                        }
                    }
                    else // (A != segment.A) && (B != segment.B) && (A != segment.B) && (segment.A != B)
                    {
                        //  -Segments are just parcially coincident (no endpoints shared).
                        // OR
                        //  -One of the segments are totally cointained inside the other, AND no endpoints shared.
                        
                        // Note: r = resident (this), i = input (segment)

                        // Reference vector for all the comparisons
                        const VectorType& ArBr = this->B - this->A;

                        const VectorType& ArAi = segment.A - this->A;

                        if(SQFloat::IsNegative( ArAi.DotProduct(ArBr) ))
                        {
                            const VectorType& BrBi = segment.B - this->B;

                            if(SQFloat::IsNegative( BrBi.DotProduct(ArBr) ))
                            {
                                // Ai---Ar---Bi---Br
                                //      I1   I2
                                vIntersection = this->A; 
                            }
                            else
                            {
                                // Ai---Ar---Br---Bi
                                //      I1   I2
                                vIntersection = this->A;
                            }
                        }
                        else
                        {
                            const VectorType& ArBi = segment.B - this->A;

                            if(SQFloat::IsNegative( ArBi.DotProduct(ArBr) ))
                            {
                                const VectorType& BrAi = segment.A - this->B;

                                if(SQFloat::IsNegative( BrAi.DotProduct(ArBr) ))
                                {
                                    // Bi---Ar---Ai---Br
                                    //      I1   I2
                                    vIntersection = this->A;
                                }
                                else
                                {
                                    // Ai---Br---Ar---Bi
                                    //      I2   I1
                                    vIntersection = this->A;
                                }
                            }
                            else
                            {
                                const VectorType& BrAi = segment.A - this->B;

                                if(SQFloat::IsNegative( BrAi.DotProduct(ArBr) ))
                                {
                                    const VectorType& BrBi = segment.B - this->B;

                                    if(SQFloat::IsNegative( BrBi.DotProduct(ArBr) ))
                                    {
                                        const VectorType& AiBi = segment.B - segment.A;

                                        if(SQFloat::IsNegative( AiBi.DotProduct(ArBr) ))
                                        {
                                            // Ar---Bi---Ai---Br
                                            //      I1   I2
                                            vIntersection = segment.B;
                                        }
                                        else
                                        {
                                            // Ar---Ai---Bi---Br
                                            //      I1   I2
                                            vIntersection = segment.A;
                                        }
                                    }
                                    else
                                    {
                                        // Bi---Br---Ai---Ar
                                        //      I2   I1
                                        vIntersection = segment.A;
                                    }
                                }
                                else
                                {
                                    // Ai---Br---Bi---Ar
                                    //      I2   I1
                                    vIntersection = segment.B;
                                }
                            }
                        }

                        return EQIntersections::E_Two;
                    }
                } // if ( SQFloat::IsNotZero(fMinDistance)
            } // if ( SQFloat::IsNotZero(fSquaredMod)
        } // if ( SQFloat::IsZero(fLenght)

    }
    
    /// <summary>
    /// This method receives another line segment, and computes the intersection points between them, if they exist.
    /// </summary>
    /// <remarks>
    /// If the length of any of both segments equals zero, it will be considered as a point (which is wrong).<br/>
    /// If there's no intersection points, the output parameters used for storing these points won't be modified.<br/>
    /// If there is any intersection, the first parameter will be set to the closest one to the resident line's A endpoint.
    /// </remarks>
    /// <param name="segment">[IN] The segment to be compared to.</param>
    /// <param name="vIntersection1">[OUT] The point where they intersect that is closest to the endpoint A (of resident segment).</param>
    /// <param name="vIntersection2">[OUT] The point where they intersect that is furthest to the endpoint A (of resident segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The segments intersect in one point only, between A and B endpoints.
    /// - An endpoint of one segment is contained in the other segment.
    /// - The segments share one endpoint.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segments coincide partially, so each one has an endpoint inside the other.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The line segments are the same
    /// - One segment is contained in the other.
    /// </returns>
    EQIntersections IntersectionPoint(const QBaseLineSegment<VectorType> &segment, VectorType &vIntersection1, VectorType &vIntersection2) const
     {
        // The endpoints of a segment should not coincide
        QE_ASSERT_WARNING(this->A != this->B && segment.A != segment.B, "The endpoints of a segment should not coincide");

        // Remark: S1 == (*this), Segment S2 == the input segment parameter.

        VectorType v1 = this->B - this->A;
        VectorType v2 = segment.B - segment.A;

        const float_q& V1_SQUARED_LENGTH = v1.GetSquaredLength();
        const float_q& V2_SQUARED_LENGTH = v2.GetSquaredLength();
        float_q fSqrLengthProd = V1_SQUARED_LENGTH * V2_SQUARED_LENGTH;

        if ( SQFloat::IsZero(fSqrLengthProd) )
        {
            // At least one of the segments' length equals zero
            if(SQFloat::IsZero(V1_SQUARED_LENGTH) && SQFloat::IsZero(V2_SQUARED_LENGTH))
            {
                if(*this == segment)
                {
                    // Both endpoints coincide
                    return EQIntersections::E_Infinite;
                }
                else
                {
                    // No intersections
                    return EQIntersections::E_None;
                }
            }
            else if(SQFloat::IsZero(V1_SQUARED_LENGTH))
            {
                if(SQFloat::IsZero(this->MinDistance(segment)))
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->A;
                    return EQIntersections::E_Two;
                }
                else
                {
                    // No intersections
                    return EQIntersections::E_None;
                }
            }
            else // if(SQFloat::IsZero(V2_SQUARED_LENGTH)
            {
                if(SQFloat::IsZero(this->MinDistance(segment)))
                {
                    vIntersection1 = segment.A;
                    vIntersection2 = segment.A;
                    return EQIntersections::E_Two;
                }
                else
                {
                    // No intersections
                    return EQIntersections::E_None;
                }
            }
        }
        else // Neither segments have length 0 --> fSqrLengthProd ALWAYS > 0 at this stage.
        {

            // Compute the sinus of the angle between v1 and v2.

            float_q fAngle = v1.AngleBetween(v2);

            // If angles are currently specified in degrees, then converts angle to radians
            // so we can use "sin" function.
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                fAngle = SQAngle::DegreesToRadians(fAngle);
            #endif

            // At this stage we have the angle expressed in RADIANS.
            float_q fSin   = sin_q(fAngle);

            // Compute Squared Module of cross product:
            float_q fSquaredMod = fSqrLengthProd * fSin * fSin;

            if ( SQFloat::IsNotZero(fSquaredMod) )
            {
                // CASE 2)
                // In this case, the situation is as follows:
                //
                //  -The lines containing the segments doesn't intersect between themselves,
                //     so the same can be said for the segments.
                // OR
                //    -The lines containing the segments intersect in a single point...
                //     ...but do the segments make the same?.
                //
                //  For asking these questions we need the closest points to each segment
                //  from respect the other one.
                VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
                this->GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

                if (vClosestPtInS1ToS2 == vClosestPtInS2ToS1)
                {
                    // Segments intersect each other IN A SINGLE POINT.

                    vIntersection1 = vClosestPtInS1ToS2; // The same with vClosestPtInS2ToS1.
                    return EQIntersections::E_One;
                }
                else
                {
                    // Segments doesn't intersect each other either:
                    //  - The lines containing the segments DOESN'T intersect between themselves.
                    // OR
                    //  - The lines containing the segments DOES intersect between themselves in a single point...
                    //      ...but that intersection occurs "outside" of the segments, it's not a point belonging
                    //      to them.

                    return EQIntersections::E_None;
                }
            }
            else // 0 == fSquaredMod
            {
                // CASE 3)
                // In this case, the situation is as follows:
                //
                //  -The lines containing the segments are PARALLEL between themselves, so do the segments --> NO intersections.
                // OR
                //  -Both segments lie on the SAME line, so there can be:
                //
                //       -No intersection points.
                //       -One single intersection point.
                //       -Two intersection points.
                //     -Infinite intersection points.
                //
                //   It may depend of the situation, more info provided below on the walk.

                float_q fMinDistance = this->MinDistance(segment);

                if ( SQFloat::IsNotZero(fMinDistance) ) // fMinDistance always nonnegative --> fMinDistance > 0
                {
                    // fMinDistance > 0 -->  -Segments are PARALLEL
                    //                        OR
                    //                         -They lie on the same line, but they DON'T intersect.
                    //
                    //                        Anyway, NO intersections.

                    return EQIntersections::E_None;
                }
                else // 0 == fMinDistance, Intersection Points: One OR Infinite.
                {
                    // BOTH segments lie on the SAME line --> Angle (v1,v2) == 0 OR 180 degrees <-- Please note at this stage v1.DotProduct(v2) ALWAYS != 0

                    // Note: r = resident (this), i = input (segment)

                    if(this->A == segment.A)
                    {
                        if(this->B == segment.B)
                        {
                            // ArAi---BrBi
                            return EQIntersections::E_Infinite; 
                        }
                        else
                        {
                            vIntersection1 = this->A;

                            // Reference vector for all the comparisons
                            const VectorType& ArBr = this->B - this->A;

                            const VectorType& ArBi = segment.B - this->A;

                            if(SQFloat::IsNegative( ArBi.DotProduct(ArBr) ))
                            {
                                // Br---ArAi---Bi
                                //       I1
                                return EQIntersections::E_One;
                            }
                            else
                            {
                                const VectorType& BrBi = segment.B - this->B;

                                if(SQFloat::IsNegative( BrBi.DotProduct(ArBr) ))
                                {
                                    // ArAi---Bi---Br
                                    //  I1    I2
                                    vIntersection2 = segment.B;
                                }
                                else
                                {
                                    // ArAi---Br---Bi
                                    //  I1    I2
                                    vIntersection2 = this->B;
                                }

                                return EQIntersections::E_Two;
                            }
                        }
                    }
                    else if(this->A == segment.B)
                    {
                        if(this->B == segment.A)
                        {
                            // ArBi---BrAi
                            return EQIntersections::E_Infinite;
                        }
                        else
                        {
                            vIntersection1 = this->A;

                            // Reference vector for all the comparisons
                            const VectorType& ArBr = this->B - this->A;

                            const VectorType& ArAi = segment.A - this->A;

                            if(SQFloat::IsNegative( ArAi.DotProduct(ArBr) ))
                            {
                                // Br---ArBi---Ai
                                //        I1
                                return EQIntersections::E_One;
                            }
                            else
                            {
                                const VectorType& BrAi = segment.A - this->B;

                                if(SQFloat::IsNegative( BrAi.DotProduct(ArBr) ))
                                {
                                    // ArBi---Ai---Br
                                    //  I1    I2
                                    vIntersection2 = segment.A;
                                }
                                else
                                {
                                    // ArBi---Br---Ai
                                    //  I1    I2
                                    vIntersection2 = this->B;
                                }

                                return EQIntersections::E_Two;
                            }
                        }
                    }
                    else if(this->B == segment.A)
                    {
                        // Reference vector for all the comparisons
                        const VectorType& ArBr = this->B - this->A;

                        const VectorType& BrBi = segment.B - this->B;

                        if(SQFloat::IsNegative( BrBi.DotProduct(ArBr) ))
                        {
                            const VectorType& ArBi = segment.B - this->A;

                            if(SQFloat::IsNegative( ArBi.DotProduct(ArBr) ))
                            {
                                // AiBr---Ar---Bi
                                //  I2    I1
                                vIntersection1 = this->A;
                                vIntersection2 = this->B;
                            }
                            else
                            {
                                // AiBr---Bi---Ar
                                //  I2    I1
                                vIntersection1 = segment.B;
                                vIntersection2 = this->B;
                            }

                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            // Ar---AiBr---Bi
                            //        I1
                            vIntersection1 = this->B;
                            return EQIntersections::E_One;
                        }
                    }
                    else if(this->B == segment.B)
                    {
                        // Reference vector for all the comparisons
                        const VectorType& ArBr = this->B - this->A;

                        const VectorType& BrAi = segment.A - this->B;

                        if(SQFloat::IsNegative( BrAi.DotProduct(ArBr) ))
                        {
                            const VectorType& ArAi = segment.A - this->A;

                            if(SQFloat::IsNegative( ArAi.DotProduct(ArBr) ))
                            {
                                // BrBi---Ar---Ai
                                //  I2    I1
                                vIntersection1 = this->A;
                                vIntersection2 = this->B;
                            }
                            else
                            {
                                // BrBi---Ai---Ar
                                //  I2    I1
                                vIntersection1 = segment.A;
                                vIntersection2 = this->B;
                            }

                            return EQIntersections::E_Two;
                        }
                        else
                        {
                            // Ar---BrBi---Ai
                            //        I1
                            vIntersection1 = this->B;
                            return EQIntersections::E_One;
                        }
                    }
                    else // (A != segment.A) && (B != segment.B) && (A != segment.B) && (segment.A != B)
                    {
                        //  -Segments are just parcially coincident (no endpoints shared).
                        // OR
                        //  -One of the segments are totally cointained inside the other, AND no endpoints shared.
                        
                        // Note: r = resident (this), i = input (segment)

                        // Reference vector for all the comparisons
                        const VectorType& ArBr = this->B - this->A;

                        const VectorType& ArAi = segment.A - this->A;

                        if(SQFloat::IsNegative( ArAi.DotProduct(ArBr) ))
                        {
                            const VectorType& BrBi = segment.B - this->B;

                            if(SQFloat::IsNegative( BrBi.DotProduct(ArBr) ))
                            {
                                // Ai---Ar---Bi---Br
                                //      I1   I2
                                vIntersection1 = this->A; 
                                vIntersection2 = segment.B; 
                            }
                            else
                            {
                                // Ai---Ar---Br---Bi
                                //      I1   I2
                                vIntersection1 = this->A;
                                vIntersection2 = this->B; 
                            }
                        }
                        else
                        {
                            const VectorType& ArBi = segment.B - this->A;

                            if(SQFloat::IsNegative( ArBi.DotProduct(ArBr) ))
                            {
                                const VectorType& BrAi = segment.A - this->B;

                                if(SQFloat::IsNegative( BrAi.DotProduct(ArBr) ))
                                {
                                    // Bi---Ar---Ai---Br
                                    //      I1   I2
                                    vIntersection1 = this->A;
                                    vIntersection2 = segment.A; 
                                }
                                else
                                {
                                    // Ai---Br---Ar---Bi
                                    //      I2   I1
                                    vIntersection1 = this->A;
                                    vIntersection2 = this->B; 
                                }
                            }
                            else
                            {
                                const VectorType& BrAi = segment.A - this->B;

                                if(SQFloat::IsNegative( BrAi.DotProduct(ArBr) ))
                                {
                                    const VectorType& BrBi = segment.B - this->B;

                                    if(SQFloat::IsNegative( BrBi.DotProduct(ArBr) ))
                                    {
                                        const VectorType& AiBi = segment.B - segment.A;

                                        if(SQFloat::IsNegative( AiBi.DotProduct(ArBr) ))
                                        {
                                            // Ar---Bi---Ai---Br
                                            //      I1   I2
                                            vIntersection1 = segment.B;
                                            vIntersection2 = segment.A; 
                                        }
                                        else
                                        {
                                            // Ar---Ai---Bi---Br
                                            //      I1   I2
                                            vIntersection1 = segment.A;
                                            vIntersection2 = segment.B; 
                                        }
                                    }
                                    else
                                    {
                                        // Bi---Br---Ai---Ar
                                        //      I2   I1
                                        vIntersection1 = segment.A;
                                        vIntersection2 = this->B; 
                                    }
                                }
                                else
                                {
                                    // Ai---Br---Bi---Ar
                                    //      I2   I1
                                    vIntersection1 = segment.B;
                                    vIntersection2 = this->B; 
                                }
                            }
                        }

                        return EQIntersections::E_Two;
                    }
                } // if ( SQFloat::IsNotZero(fMinDistance)
            } // if ( SQFloat::IsNotZero(fSquaredMod)
        } // if ( SQFloat::IsZero(fLenght)
    }

    /// <summary>
    /// This method receives an orb and computes the points where the resident line segment intersects with it,
    /// if they exist.
    /// </summary>
    /// <remarks>
    /// If the length of the segment or the radius of the orb equal zero, the orb or the segment will be considered as a point (which is wrong).<br/>
    /// If there's no intersection point, the output parameters used for storing the points won't be modified.<br/>
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection1">[OUT] The point where they intersect that is closest to the endpoint A.</param>
    /// <param name="vIntersection2">[OUT] The point where they intersect that is furthest to the endpoint A.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - Only one endpoint is inside the orb.
    /// - Only one endpoint is tangent to the orb, even if the other endpoint is inside the orb.
    /// - The segment is tangent to the orb in a point between A and B.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segment pierces the orb in two points.
    /// - Both endpoints are tangent to the orb's surface / perimeter (so the line is inside the orb).
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The line segment is totally contained in the orb. The endpoints are not tangent to the orb's surface / perimeter.
    /// </returns>
    EQIntersections IntersectionPoint(const QBaseOrb<VectorType> &orb, VectorType &vIntersection1, VectorType &vIntersection2) const
    {
        // The endpoints of a segment should not coincide and the radius should be greater than zero
        QE_ASSERT_WARNING(this->A != this->B && SQFloat::IsGreaterThan(orb.Radius, SQFloat::_0), "The endpoints of a segment should not coincide and the radius should be greater than zero (either or both of this rules may have failed)");

        // We reduce line segment and orb to origin, in order to simplify orb equation, and we calculate
        // the new point A and vector B-A, to compute intersection as with a ray
        VectorType vNewA(this->A - orb.Center);
        VectorType vDirection(this->B - this->A);

        // We replace then in the orb equation to force it to verify the ray equation
        // vDirection^2*t^2 + 2*vNewA*vDirection*t + vNewA^2 - r^2 = 0
        // The intersections with ray follows this rules (extracted from quadratic ecuation):
        //       D = b^2 - 4ac = 0 => 1 intersection
        //       D = b^2 - 4ac < 0 => 0 intersections
        //       D = b^2 - 4ac > 0 => 2 intersections

        const float_q &a = vDirection.DotProduct(vDirection);
        const float_q &b = SQFloat::_2 * vNewA.DotProduct(vDirection);
        const float_q &c = vNewA.DotProduct(vNewA) - orb.Radius * orb.Radius;

        const float_q &D = b * b - SQFloat::_4 * a * c;

        if (SQFloat::IsNegative(D)) // D = b^2 - 4ac < 0 => 0 intersections
            return EQIntersections::E_None;
        else if (SQFloat::IsZero(D)) // D = b^2 - 4ac = 0 => 1 intersection
        {
            QE_ASSERT_WARNING(SQFloat::IsNotZero(a), "The variable \"a\" should not equal zero, this will produce a division by zero");

            const float_q &t = -(b*SQFloat::_0_5 / a);

            VectorType vAux(vNewA + t * vDirection + orb.Center);

            if (SQFloat::IsZero(this->MinDistance(vAux)))
            {
                vIntersection1 = vAux;
                return EQIntersections::E_One;
            }
            else
            {
                if(SQFloat::IsZero(a))
                {
                    // The length of the line segment equals zero (A == B). Rare case.
                    const float_q& DISTANCE_TO_CENTER = this->A.Distance(orb.Center);

                    if(SQFloat::IsLessThan(DISTANCE_TO_CENTER, orb.Radius))
                    {
                        return EQIntersections::E_Infinite;
                    }
                    else if(SQFloat::AreEqual(DISTANCE_TO_CENTER, orb.Radius))
                    {
                        vIntersection1 = this->A;
                        vIntersection2 = this->A;
                        return EQIntersections::E_Two;
                    }
                    else
                    {
                        return EQIntersections::E_None;
                    }
                }
                else
                {
                    return EQIntersections::E_None;
                }
            }
        }
        else // D = b^2 - 4ac > 0 => 2 intersections
        {
            QE_ASSERT_WARNING(SQFloat::IsNotZero(a), "The variable \"a\" should not equal zero, this will produce a division by zero");

            const float_q &fAux1 = sqrt_q(D);
            const float_q &fAux2 = SQFloat::_0_5 / a;

            // Closest intersection to ls.A
            const float_q &t1 = (-b - fAux1) * fAux2;
            VectorType vAux1(vNewA + t1 * vDirection + orb.Center);

            // Farthest intersection to ls.A
            const float_q &t2 = (-b + fAux1) * fAux2;
            VectorType vAux2(vNewA + t2 * vDirection + orb.Center);

            const bool &bIsInSegment1 = SQFloat::IsZero(this->MinDistance(vAux1));
            const bool &bIsInSegment2 = SQFloat::IsZero(this->MinDistance(vAux2));

            // Both points are in line segment.
            if (bIsInSegment1 && bIsInSegment2)
            {
                vIntersection1 = vAux1;
                vIntersection2 = vAux2;
                return EQIntersections::E_Two;
            }
            else if (bIsInSegment1) // Only t1 point is in line segment.
            {
                vIntersection1 = vAux1;
                return EQIntersections::E_One;
            }
            else if (bIsInSegment2) // Only t2 is in line segment.
            {
                vIntersection1 = vAux2;
                return EQIntersections::E_One;
            }
            else // There are no intersections or the line is contained by the orb.
            {
                // If the end points are inside the orb, the distance to the center is less than the radius of the orb
                if( SQFloat::IsLessThan(this->A.Distance(orb.Center), orb.Radius) )
                    // The line is contained in the orb
                    // Note: B end point is not checked because if the execution flow has reached this point
                    //       then it's impossible that there is one end point inside and the other outside the orb
                    return EQIntersections::E_Infinite;
                else
                    return EQIntersections::E_None;
            }
        }
    }

    /// <summary>
    /// This method receives an orb, and computes the point where the resident line segment intersects with it,
    /// if it exists.
    /// </summary>
    /// <remarks>
    /// If the length of the segment or the radius of the orb equal zero, the orb or the segment will be considered as a point (which is wrong).<br/>
    /// If there's no intersection point or if there are infinite, the output parameter used for storing the point won't be modified.<br/>
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection">[OUT] The point where they intersect that is closest to the endpoint A.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - Only one endpoint is inside the orb.
    /// - Only one endpoint is tangent to the orb, even if the other endpoint is inside the orb.
    /// - The segment is tangent to the orb in a point between A and B.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segment pierces the orb in two points.
    /// - Both endpoints are tangent to the orb's surface / perimeter (so the line is inside the orb).
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The line segment is totally contained in the orb. The endpoints are not tangent to the orb's surface / perimeter.
    /// </returns>
    EQIntersections IntersectionPoint(const QBaseOrb<VectorType> &orb, VectorType &vIntersection) const
    {
        // The endpoints of a segment should not coincide and the radius should be greater than zero
        QE_ASSERT_WARNING(this->A != this->B && SQFloat::IsGreaterThan(orb.Radius, SQFloat::_0), "The endpoints of a segment should not coincide and the radius should be greater than zero (either or both of this rules may have failed)");

        VectorType vAux;
        return this->IntersectionPoint(orb, vIntersection, vAux);
    }

    /// <summary>
    /// Given an input line segment, this method returns the minimum distance between this and the input one,
    ///    that is, the distance between their closest points.
    /// </summary>
    /// <remarks>
    /// If the length of any of both segments equals zero it will be considered as a point (which is wrong).
    /// </remarks>
    /// <param name="segment">[IN] The line segment the distance will be measured to.</param>
    /// <returns>
    /// A floating point value (always nonnegative) which represents the minimum distance between the two segments.
    /// </returns>
    float_q MinDistance(const QBaseLineSegment<VectorType> &segment) const
    {
        // Just compute the closests points between the segments, and return
        // the distance between them; that is the minimum distance.
        //
        // Remark: S1 == (*this), Segment S2 == the input segment parameter.

        // The endpoints of a segment should not coincide
        QE_ASSERT_WARNING(this->A != this->B && segment.A != segment.B, "The endpoints of a segment should not coincide");

        VectorType vClosestPtInS1ToS2, vClosestPtInS2ToS1;
        this->GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);

        return vClosestPtInS1ToS2.Distance(vClosestPtInS2ToS1);
    }

    /// <summary>
    /// Given an input vector (which represents a point), this method returns the minimum distance between this and
    /// the segment, that is, the distance between the input point and the closest point lying into the segment.
    /// </summary>
    /// <remarks>
    /// If the length of the segment equals zero it will be considered as a point (which is wrong).
    /// </remarks>
    /// <param name="vPoint">[IN] The point the distance will be measured to.</param>
    /// <returns>
    /// A floating point value (always nonnegative) which represents the minimum distance between point and segment.
    /// </returns>
    float_q MinDistance(const VectorType &vPoint) const
    {
        // The endpoints of a segment should not coincide
        QE_ASSERT_WARNING(this->A != this->B, "The endpoints of a segment should not coincide");

        if (A != B)
        {
            // STEP 0) v1 = B - A, v2 = vPoint - A
            // STEP 1) if ( DotProduct(v1, v2) <= 0 ) --> Angle(v1, v2) >= (PI / 2) --> vPoint is closer to A, MinDistance = Length(v2)
            //           else
            //           STEP 2) if ( DotProduct (v1, v2) >= DotProduct(v1, v1) ) --> vPoint is closer to B, MinDistance = Length(vPoint - B)
            //                   else
            //                   STEP 3) ProjectionOverAB(vPoint) falls into the segment, so:
            //                           MinDistance = Length( ProjectionOverAB(vPoint) - vPoint ) = Length( (A + ((DotProduct(v1, v2) / DotProduct(v1, v1)) * v1)) - vPoint )
            float_q fDotProductv1v1 = SQFloat::_0;
            VectorType v1            = B - A;
            VectorType v2            = vPoint - A;
            float_q fDotProductv1v2 = v1.DotProduct(v2);

            if ( (SQFloat::IsNegative(fDotProductv1v2)) || (SQFloat::IsZero(fDotProductv1v2)) )
            {
                return v2.GetLength();
            }
            else
            {
                fDotProductv1v1 = v1.DotProduct(v1);

                if ( SQFloat::IsGreaterOrEquals(fDotProductv1v2, fDotProductv1v1) )
                {
                    return ( (vPoint - B).GetLength() );
                }
                else
                {
                    // Checkout to avoid division by 0
                    QE_ASSERT_WARNING (fDotProductv1v1 != SQFloat::_0, "The variable \"fDotProductv1v1\" should not equal zero, this will produce a division by zero");

                    return ((A + ((fDotProductv1v2 / fDotProductv1v1) * v1)) - vPoint).GetLength();
                }

            }
        } // if (A != B
        else
        {
            return (vPoint - B).GetLength(); // (vPoint - A) could have been used as well.
        }
    }

    /// <summary>
    /// Given a lengthening factor, this method computes the lengthening of the segment; endpoints move away or approach
    /// to the center, depending of the lengthening factor value.
    /// </summary>
    /// <remarks>
    /// If the lengthening factor is 0.0, the segment degenerates into a point (both endpoints become the center).<br/>
    /// If the lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
    /// </remarks>
    /// <param name="fLengtheningFactor">[IN] A floating point value that lengthens the segment.</param>
    void Lengthen(const float_q &fLengtheningFactor)
    {
        // If Lengthening Factor == 1 we just don't touch the segment.
        if ( SQFloat::AreNotEqual(fLengtheningFactor, SQFloat::_1) )
        {
            VectorType vCenter;
            vCenter = this->GetCenter();

            // If Lengthening Factor == 0, just reduce the endpoints to the center.
            if (SQFloat::AreEqual(fLengtheningFactor, SQFloat::_0))
            {
                A = vCenter;
                B = vCenter;
            }
            else // Compute the new segment endpoints from the center.
            {
                A = vCenter + (fLengtheningFactor * (A - vCenter) );
                B = vCenter + (fLengtheningFactor * (B - vCenter) );
            }
        }
    }

    /// <summary>
    /// Given a lengthening factor, this method computes the lengthening of the segment; endpoint B moves away or approaches to A,
    /// depending of the lengthening factor value. In any case, A stays the same.
    /// </summary>
    /// <remarks>
    /// If lengthening factor is 0.0, the segment degenerates into a point (both endpoints become A).<br/>
    /// If lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
    /// </remarks>
    /// <param name="fLengtheningFactor">[IN] A floating point value that lengthens the segment.</param>
    void LengthenFromA(const float_q &fLengtheningFactor)
    {
        // If Lengthening Factor == 1 we just don't touch the segment.
        if ( SQFloat::AreNotEqual(fLengtheningFactor, SQFloat::_1) )
        {
            // If Lengthening Factor == 0, just reduce the endpoints to A.
            if ( SQFloat::AreEqual(fLengtheningFactor, SQFloat::_0) )
            {
                B = A;
            }
            else // Lengthen from A --> Compute the new B.
            {
                B = A + (fLengtheningFactor * (B - A));
            }
        }
    }

    /// <summary>
    /// Given a lengthening factor, this method computes the lengthening of the segment; endpoint A moves away or approaches to B,
    /// depending of the lengthening factor value. In any case, B stays the same.
    /// </summary>
    /// <remarks>
    /// If lengthening factor is 0.0, the segment degenerates into a point (both endpoints become B).<br/>
    /// If lengthening factor is 1.0, the segment won't experiment any modification, as this represent a 100% lengthening.
    /// </remarks>
    /// <param name="fLengtheningFactor">[IN] A floating point value that lengthens the segment.</param>
    void LengthenFromB(const float_q &fLengtheningFactor)
    {
        // If Lengthening Factor == 1 we just don't touch the segment.
        if ( SQFloat::AreNotEqual(fLengtheningFactor, SQFloat::_1) )
        {
            // If Lengthening Factor == 0, just reduce the endpoints to B.
            if ( SQFloat::AreEqual(fLengtheningFactor, SQFloat::_0) )
            {
                A = B;
            }
            else // Lengthen from B --> Compute the new A.
            {
                A = B + (fLengtheningFactor * (A - B));
            }
        }
    }

    /// <summary>
    /// Converts vector into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "LS(a($A),b($B))".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>
    /// The string with the format specified.
    /// </returns>
    string_q ToString() const
    {
        return string_q("LS(a(") + A.ToString() + QE_L("),b(") + B.ToString() + QE_L("))");
    }

protected:

    /// <summary>
    /// This method computes the closest points between two line segments.
    /// </summary>
    /// <param name="segment">[IN] The segment to whom the distace has to be computed from.</param>
    /// <param name="vClosestPtInS1ToS2">[OUT] It stores the closest point to S2 belonging to S1.</param>
    /// <param name="vClosestPtInS2ToS1">[OUT] It stores the closest point to S1 belonging to S2.</param>
    /// <remarks>
    /// We assume S1 is the segment which executes this member function, and S2 the segment passed as
    /// a parameter to S1.
    /// </remarks>
    void GetClosestPoints(const QBaseLineSegment<VectorType> &segment,
                          VectorType& vClosestPtInS1ToS2, VectorType& vClosestPtInS2ToS1) const
    {
        bool bBothDegeneratedIntoPoints = false; // True if both segments degenerate into points.

        // STEP 0) -Segment S1 == (*this)        == B - A
        //           -Segment S2 == the parameter == segment.B - segment.A
        //           -fSFactor1,fSFactor2: [0,1]  == Sample factors, so the closest points between S1 and S2
        //                                           will be given through:
        //
        //                                                S1(fSFactor1) = (A + (fSFactor1 * v1))
        //                                                S2(fSFactor2) = (segment.A + (fSFactor2 * v2))
        float_q       fSFactor1  = SQFloat::_0;
        float_q       fSFactor2  = SQFloat::_0;
        VectorType v1          = B - A;
        VectorType v2          = segment.B - segment.A;

        // STEP 1) Precomputing intermediate values for solving s and t.
        float_q       fSqrLengthv1          = v1.DotProduct(v1);    // Squared length of segment S1, always nonnegative.
        float_q       fSqrLengthv2          = v2.DotProduct(v2);    // Squared length of segment S2, always nonnegative.
        VectorType vTails              = A - segment.A;            // Segment whose endpoints are the "tail" points of each segment.
        float_q       fDotProdv2vTails   = v2.DotProduct(vTails);

        // STEP 2) Check if either or both segments degenerate into points
        if ( (SQFloat::IsZero(fSqrLengthv1)) && (SQFloat::IsZero(fSqrLengthv2)) )
        {
            // BOTH segments degenerate into points --> The closest points are THEMSELVES.
            vClosestPtInS1ToS2           = A;          // The same with B.
            vClosestPtInS2ToS1           = segment.A; // The same with segment.B
            bBothDegeneratedIntoPoints = true;
        }

        if (!bBothDegeneratedIntoPoints)
        {
            if (SQFloat::IsZero(fSqrLengthv1))
            {
                // S1 (*this) degenerates into a point;
                // fSFactor1 = 0 --> fSFactor2 = (((fDotProdv1v2 * fSFactor1) + fDotProdv2vTails) / fSqrLengthv2) = (fDotProdv2vTails / fSqrLengthv2)

                // Checkout to avoid division by 0
                QE_ASSERT_WARNING(fSqrLengthv2 != SQFloat::_0, "The variable \"fSqrLengthv2\" should not equal zero (line endpoints should not coincide), this will produce a division by zero");

                fSFactor2 = SQFloat::Clamp( (fDotProdv2vTails / fSqrLengthv2), SQFloat::_0, SQFloat::_1);
            }
            else
            {
                float_q fDotProdv1vTails = v1.DotProduct(vTails);

                if (SQFloat::IsZero(fSqrLengthv2))
                {
                    // S2 (the parameter) degenerates into a point;
                    // fSFactor2 = 0 --> fSFactor1 = (((fDotProdv1v2 * fSFactor2) - fDotProdv1vTails) / fSqrLengthv1) = (-fDotProdv1vTails / fSqrLengthv1)

                    // Checkout to avoid division by 0
                    QE_ASSERT_WARNING(fSqrLengthv1 != SQFloat::_0, "The variable \"fSqrLengthv1\" should not equal zero (line endpoints should not coincide), this will produce a division by zero");

                    fSFactor1 = SQFloat::Clamp( (-fDotProdv1vTails / fSqrLengthv1), SQFloat::_0, SQFloat::_1 );

                }
                else
                {
                    // Length of both segments are > 0;
                    // STEP 3) Compute values for fSFactor1 and fSFactor2
                    //
                    float_q fDotProdv1v2 = v1.DotProduct(v2);
                    float_q fDenom       = (fSqrLengthv1 * fSqrLengthv2) - (fDotProdv1v2 * fDotProdv1v2); // Always nonnegative:
                                                                                                      //    fDenom == 0 --> S1 || S2;
                                                                                                      //    fDenom >  0 --> S1 not || S2
                    // STEP 3.1)
                    // If segments not parallel, compute sample factor for S1, fSFactor1, and
                    // clamp to segment S1. (** if they're paraller pick arbitrary fSFactor1 -here 0- **)
                    //
                    // fSFactor1 = ((fDotProdv1v2 * fDotProdv2vTails) - (fDotProdv1vTails * fSqrLengthv2)) / fDenom
                    if (SQFloat::IsNotZero(fDenom))
                    {
                        fSFactor1 = SQFloat::Clamp( ((fDotProdv1v2 * fDotProdv2vTails) - (fDotProdv1vTails * fSqrLengthv2)) / fDenom, SQFloat::_0, SQFloat::_1 );
                    }
                    else
                    {
                        fSFactor1 = SQFloat::_0;
                    }

                    // STEP 3.2) Compute sample factor for S2, fSFactor2
                    float_q fNom = (fSFactor1 * fDotProdv1v2) + fDotProdv2vTails;

                    // If fNom in range [0..1] --> fSFactor2 = fNom / fSqrLengthv2;
                    // else clamp fSFactor2 to 0 or 1, recompute fSFactor1 for the new value
                    // of fSFactor2 using:
                    //
                    //        fSFactor1 = ((fSFactor2 * fDotProdv1v2) - fDotProdv1vTails) / fSqrLengthv1
                    //
                    // and clamp fSFactor1 to range [0..1]
                    if (SQFloat::IsNegative(fNom))
                    {
                        fSFactor2 = SQFloat::_0;

                        // Checkout to avoid division by 0
                        QE_ASSERT_WARNING(fSqrLengthv1 != SQFloat::_0, "The variable \"fSqrLengthv1\" should not equal zero (line endpoints should not coincide), this will produce a division by zero");

                        fSFactor1 = SQFloat::Clamp( (-fDotProdv1vTails / fSqrLengthv1), SQFloat::_0, SQFloat::_1 );
                    }
                    else if (fNom > fSqrLengthv2)
                    {
                        fSFactor2 = SQFloat::_1;

                        // Checkout to avoid division by 0
                        QE_ASSERT_WARNING(fSqrLengthv1 != SQFloat::_0, "The variable \"fSqrLengthv1\" should not equal zero (line endpoints should not coincide), this will produce a division by zero");

                        fSFactor1 = SQFloat::Clamp( ((fDotProdv1v2 - fDotProdv1vTails) / fSqrLengthv1), SQFloat::_0, SQFloat::_1 );

                    }
                    else // fNom in range [0..1]
                    {
                        // Checkout to avoid division by 0
                        QE_ASSERT_WARNING(fSqrLengthv2 != SQFloat::_0, "The variable \"fSqrLengthv2\" should not equal zero (line endpoints should not coincide), this will produce a division by zero");

                        fSFactor2 = fNom / fSqrLengthv2;
                    };
                }
            }

            // STEP 4) Finally compute the closest points between S1 and S2 and storing them
            // in the output parameters.
            vClosestPtInS1ToS2 = A + (fSFactor1 * v1);
            vClosestPtInS2ToS1 = segment.A + (fSFactor2 * v2);

        } // if (!bBothDegeneratedIntoPoints
    }

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

template class QE_LAYER_TOOLS_SYMBOLS QLineSegment<Kinesis::QuimeraEngine::Tools::Math::QVector2>;
template class QE_LAYER_TOOLS_SYMBOLS QLineSegment<Kinesis::QuimeraEngine::Tools::Math::QVector3>;
template class QE_LAYER_TOOLS_SYMBOLS QLineSegment<Kinesis::QuimeraEngine::Tools::Math::QVector4>;

#endif // QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT__
