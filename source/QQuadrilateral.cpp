// [TERMS&CONDITIONS]

#include "QQuadrilateral.h"

using namespace Kinesis::QuimeraEngine::Tools::Math;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QQuadrilateral QQuadrilateral::UnitSquare    ( QVector2( SQFloat::_0_5,   SQFloat::_0_5),
                                                     QVector2(-SQFloat::_0_5,   SQFloat::_0_5),
                                                     QVector2(-SQFloat::_0_5,  -SQFloat::_0_5),
                                                     QVector2( SQFloat::_0_5,  -SQFloat::_0_5) );


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool QQuadrilateral::Contains (const QBaseVector2 &v) const
{
    if (this->IsConvex()) // Its convex
    {
        if (this->IsCrossed()) // Its crossed
        {
            QLineSegment2D ls1(this->A, this->D), ls2(this->B, this->C);
            QVector2 vAux;

            if (ls1.IntersectionPoint(ls2, vAux) == EQIntersections::E_One) // Check if AD and BC edges cross themselves
            {
                // It checks both triangles (ABvAux and CDvAux)
                if (( PointsInSameSideOfLine(v, vAux, this->A, this->B) &&
                      PointsInSameSideOfLine(v, this->A, this->B, vAux) &&
                      PointsInSameSideOfLine(v, this->B, vAux, this->A) ) ||
                    ( PointsInSameSideOfLine(v, this->C, vAux, this->D) &&
                      PointsInSameSideOfLine(v, vAux, this->D, this->C) &&
                      PointsInSameSideOfLine(v, this->D, this->C, vAux) ))

                    return true;
                else
                    return false;
            }
            else // Check if AB and CD edges cross themselves
            {
                ls1 = QLineSegment2D(this->A, this->B);
                ls2 = QLineSegment2D(this->C, this->D);

                if (ls1.IntersectionPoint(ls2, vAux) == EQIntersections::E_One)
                {
                    // It checks both triangles (ADvAux and BCvAux)
                    if (( PointsInSameSideOfLine(v, this->A, vAux, this->D) && PointsInSameSideOfLine(v, vAux, this->D, this->A) &&
                          PointsInSameSideOfLine(v, this->D, this->A, vAux) ) ||
                        ( PointsInSameSideOfLine(v, this->B, this->C, vAux) && PointsInSameSideOfLine(v, this->C, vAux, this->B) &&
                          PointsInSameSideOfLine(v, vAux, this->B, this->C) ))

                        return true;
                    else
                        return false;
                }
                // Something is wrong! : Its crossed quadrilateral but there are no intersections between edges.
                else
                    QE_ASSERT(false);
            }
        }
        else // Its standard convex
        {
            if (PointsInSameSideOfLine(v, this->C, this->A, this->B) && PointsInSameSideOfLine(v, this->D, this->B, this->C) &&
                PointsInSameSideOfLine(v, this->A, this->C, this->D) && PointsInSameSideOfLine(v, this->B, this->D, this->A))

                return true;
            else
                return false;
        }
    }
    else if (this->IsConcaveHere(this->A, this->B, this->D, this->C)) // Its concave in A vertex
    {
        // We check the two triangles around A vertex
        if (( PointsInSameSideOfLine(v, this->C, this->A, this->B) && PointsInSameSideOfLine(v, this->A, this->B, this->C) &&
              PointsInSameSideOfLine(v, this->B, this->C, this->A) ) ||
            ( PointsInSameSideOfLine(v, this->C, this->A, this->D) && PointsInSameSideOfLine(v, this->A, this->D, this->C) &&
              PointsInSameSideOfLine(v, this->D, this->C, this->A) ))

            return true;
        else
            return false;
    }
    else if (this->IsConcaveHere(this->B, this->A, this->C, this->D)) // Its concave in B vertex
    {
        // We check the two triangles around B vertex
        if (( PointsInSameSideOfLine(v, this->D, this->B, this->C) && PointsInSameSideOfLine(v, this->B, this->C, this->D) &&
              PointsInSameSideOfLine(v, this->C, this->D, this->B) ) ||
            ( PointsInSameSideOfLine(v, this->A, this->B, this->D) && PointsInSameSideOfLine(v, this->B, this->D, this->A) &&
              PointsInSameSideOfLine(v, this->D, this->A, this->B) ))

            return true;
        else
            return false;
    }
    else if (this->IsConcaveHere(this->C, this->B, this->D, this->A)) // Its concave in C vertex
    {
        // We check the two triangles around C vertex
        if (( PointsInSameSideOfLine(v, this->A, this->C, this->D) && PointsInSameSideOfLine(v, this->C, this->D, this->A) &&
              PointsInSameSideOfLine(v, this->D, this->A, this->C) ) ||
            ( PointsInSameSideOfLine(v, this->B, this->C, this->A) && PointsInSameSideOfLine(v, this->C, this->A, this->B) &&
              PointsInSameSideOfLine(v, this->A, this->B, this->C) ))

            return true;
        else
            return false;
    }
    else if (this->IsConcaveHere(this->D, this->A, this->C, this->B)) // Its concave in D vertex
    {
        // We check the two triangles around D vertex
        if (( PointsInSameSideOfLine(v, this->B, this->D, this->A) && PointsInSameSideOfLine(v, this->D, this->A, this->B) &&
              PointsInSameSideOfLine(v, this->A, this->B, this->D) ) ||
            ( PointsInSameSideOfLine(v, this->C, this->D, this->B) && PointsInSameSideOfLine(v, this->D, this->B, this->C) &&
              PointsInSameSideOfLine(v, this->B, this->C, this->D) ))

            return true;
        else
            return false;
    }
    else // Something is wrong! : its concave but no vertex has concavity
        QE_ASSERT(false);
}

string_q QQuadrilateral::ToString()
{
    return QE_L("QL:A(") + this->A.ToString() + QE_L("), B(") +
                           this->B.ToString() + QE_L("), C(") +
                           this->C.ToString() + QE_L("), D(") +
                           this->D.ToString() + QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
