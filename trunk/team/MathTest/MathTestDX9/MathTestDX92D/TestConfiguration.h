#ifndef __TESTCONFIGURATION__
#define __TESTCONFIGURATION__

#define QLINESEGMENT2D
#define QRAY2D
#define QTRIANGLE2D
#define QCIRCLE
#define QQUADRILATERAL

#include <QVector2.h>
#include <QCircle.h>
#include <QLineSegment2D.h>
#include <QRay2D.h>
#include <QQuadrilateral.h>
#include <QTriangle2D.h>

using namespace Kinesis::QuimeraEngine::Tools::Math;

#ifdef QLINESEGMENT2D
    QLineSegment2D LineSegment2D1;
    QLineSegment2D LineSegment2D2;
#endif

#ifdef QRAY2D
    QRay2D Ray2D1;
    QRay2D Ray2D2;
#endif

#ifdef QTRIANGLE2D
    QTriangle2D Triangle2D1;
    QTriangle2D Triangle2D2;
#endif

#ifdef QCIRCLE
    QCircle Circle1;
    QCircle Circle2;
#endif

#ifdef QQUADRILATERAL
    QQuadrilateral Quadrilateral1;
    QQuadrilateral Quadrilateral2;
#endif

#endif