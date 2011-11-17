#ifndef __TESTHERE__
#define __TESTHERE__

#include "TestConfiguration.h"

// Put your tests here.
//
// There are several geometric figures available, depending on the configuration (TestConfiguration.h file):
//      QLineSegment3D: LineSegment3D1, LineSegment3D2
//      QRay3D: Ray3D1, Ray3D2
//      QSphere: Sphere1, Sphere2
//      QHexahedron: Hexhahedron1, Hexahedron2
//      QTriangle3D: Triangle3D1, Triangle3D2
//
// The input parameter timeDelta can be used to animate objects.
//
// You can use the keyboard to move around figures: 
//      W, S, A, D, N, M, R, F, UP, DOWN, LEFT, RIGHT
//
// Use OutputDebugStringW to print messages and values to Output window (remember always to end with '\n');
//
// To change the VectorType type, go to TestConfiguration.h and change the typedef statement.
//

void Test(float fTimeDelta)
{
    // Planning
    OutputDebugStringW(L"Posing test...\n");

    Ray3D1.Direction.x = 1.0f;     Ray3D1.Direction.y = 0.0f;    Ray3D1.Direction.z = 0.0f;
    Ray3D1.Point.x = 1.0f;         Ray3D1.Point.y = 1.0f;        Ray3D1.Point.z = -1.0f;

    Ray3D2.Direction.x = 1.0f;     Ray3D2.Direction.y = 0.0f;    Ray3D2.Direction.z = 0.0f;
    Ray3D2.Point.x = 1.0f;         Ray3D2.Point.y = 1.0f;        Ray3D2.Point.z = -2.0f;

    LineSegment3D1.A.x = -1.0f;    LineSegment3D1.A.y = 0.0f;    LineSegment3D1.A.z = 0.0f;
    LineSegment3D1.B.x = -1.0f;    LineSegment3D1.B.y = 1.0f;    LineSegment3D1.B.z = 0.0f;

    LineSegment3D2.A.x = 1.0f;    LineSegment3D2.A.y = 0.0f;    LineSegment3D2.A.z = 0.0f;
    LineSegment3D2.B.x = 1.0f;    LineSegment3D2.B.y = 1.0f;    LineSegment3D2.B.z = 0.0f;

    Triangle3D1.A.x = 0.0f; Triangle3D1.A.y = 1.0f; Triangle3D1.A.z = 2.0f;
    Triangle3D1.B.x = -0.7f; Triangle3D1.B.y = 0.0f; Triangle3D1.B.z = 2.0f;
    Triangle3D1.C.x = 0.7f; Triangle3D1.C.y = 0.0f; Triangle3D1.C.z = 2.0f;

    Triangle3D2.A.x = -1.3f; Triangle3D2.A.y = 1.0f; Triangle3D2.A.z = 2.0f;
    Triangle3D2.B.x = -2.0f; Triangle3D2.B.y = 0.0f; Triangle3D2.B.z = 2.0f;
    Triangle3D2.C.x = -0.6f; Triangle3D2.C.y = 0.0f; Triangle3D2.C.z = 2.0f;

    Hexahedron1.A.x = -0.5f; Hexahedron1.A.y = 0.5f;  Hexahedron1.A.z = 0.5f;
    Hexahedron1.B.x = -0.5f; Hexahedron1.B.y = 0.5f;  Hexahedron1.B.z = -0.5f;
    Hexahedron1.C.x = -0.5f; Hexahedron1.C.y = -0.5f; Hexahedron1.C.z = -0.5f;
    Hexahedron1.D.x = -0.5f; Hexahedron1.D.y = -0.5f; Hexahedron1.D.z = 0.5f;
    Hexahedron1.E.x = 0.5f;  Hexahedron1.E.y = 0.5f;  Hexahedron1.E.z = 0.5f;
    Hexahedron1.F.x = 0.5f;  Hexahedron1.F.y = 0.5f;  Hexahedron1.F.z = -0.5f;
    Hexahedron1.G.x = 0.5f;  Hexahedron1.G.y = -0.5f; Hexahedron1.G.z = -0.5f;
    Hexahedron1.H.x = 0.5f;  Hexahedron1.H.y = -0.5f; Hexahedron1.H.z = 0.5f;

    Hexahedron2.A.x = -0.5f; Hexahedron2.A.y = 0.5f;  Hexahedron2.A.z = 0.5f;
    Hexahedron2.B.x = -0.5f; Hexahedron2.B.y = 0.5f;  Hexahedron2.B.z = -0.5f;
    Hexahedron2.C.x = -0.5f; Hexahedron2.C.y = -0.5f; Hexahedron2.C.z = -0.5f;
    Hexahedron2.D.x = -0.5f; Hexahedron2.D.y = -0.5f; Hexahedron2.D.z = 0.5f;
    Hexahedron2.E.x = 0.5f;  Hexahedron2.E.y = 0.5f;  Hexahedron2.E.z = 0.5f;
    Hexahedron2.F.x = 0.5f;  Hexahedron2.F.y = 0.5f;  Hexahedron2.F.z = -0.5f;
    Hexahedron2.G.x = 0.5f;  Hexahedron2.G.y = -0.5f; Hexahedron2.G.z = -0.5f;
    Hexahedron2.H.x = 0.5f;  Hexahedron2.H.y = -0.5f; Hexahedron2.H.z = 0.5f;



    // Test
    OutputDebugStringW(L"Executing test...\n");

    // Hexahedron animated rotation sample
    static float_q fRotationY = 0.0f;
    fRotationY += fTimeDelta;
    Hexahedron1.Rotate(QQuaternion(0.0f, fRotationY, 0.0f));
    Hexahedron1.Translate(2.0f, 0.0f, 0.0f);

    // Hexahedron translation sample
    Hexahedron2.Translate(2.0f, 0.0f, 2.0f);

    // Ray rotation sample
    Ray3D1.RotateWithPivot(QQuaternion(0.0f, 0.0f, fRotationY), VectorType(Ray3D1.Point));



    // Log (see output window)
    OutputDebugStringW(LineSegment3D1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(LineSegment3D2.ToString().c_str()); OutputDebugStringW(L"\n");

    OutputDebugStringW(Triangle3D1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(Triangle3D2.ToString().c_str()); OutputDebugStringW(L"\n");
 
    OutputDebugStringW(Hexahedron1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(Hexahedron2.ToString().c_str()); OutputDebugStringW(L"\n");
}

#endif