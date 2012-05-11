#ifndef __TESTCONFIGURATION__
#define __TESTCONFIGURATION__

#define QLINESEGMENT3D
#define QRAY3D
#define QTRIANGLE3D
#define QSPHERE
#define QHEXAHEDRON

#include <QVector3.h>
#include <QVector4.h>
#include <QQuaternion.h>
#include <QMatrix3x3.h>
#include <QMatrix4x4.h>
#include <QMatrix4x3.h>
#include <QTranslationMatrix.h>
#include <QTransformationMatrix.h>
#include <QRotationMatrix3x3.h>
#include <QScalingMatrix3x3.h>
#include <QLineSegment3D.h>
#include <QHexahedron.h>
#include <QRay3D.h>
#include <QSphere.h>
#include <QTriangle3D.h>

using namespace Kinesis::QuimeraEngine::Tools::Math;

typedef QVector3 VectorType;

#ifdef QLINESEGMENT3D
    QLineSegment3D<VectorType> LineSegment3D1;
    QLineSegment3D<VectorType> LineSegment3D2;
#endif

#ifdef QRAY3D
    QRay3D<VectorType> Ray3D1;
    QRay3D<VectorType> Ray3D2;
#endif

#ifdef QTRIANGLE3D
    QTriangle3D<VectorType> Triangle3D1;
    QTriangle3D<VectorType> Triangle3D2;
#endif

#ifdef QSPHERE
    QSphere<VectorType> Sphere1;
    QSphere<VectorType> Sphere2;
#endif

#ifdef QHEXAHEDRON
    QHexahedron<VectorType> Hexahedron1;
    QHexahedron<VectorType> Hexahedron2;
#endif

#endif