#ifndef __TESTHERE__
#define __TESTHERE__

#include "TestConfiguration.h"

// Put your tests here.
//
// There are several geometric figures available, depending on the configuration (TestConfiguration.h file):
//      QLineSegment2D: LineSegment2D1, LineSegment2D2
//      QRay2D: Ray2D1, Ray2D2
//      QCircle: Circle1, Circle2
//      QQuadrilateral: Quadrilateral1, Quadrilateral2
//      QTriangle2D: Triangle2D1, Triangle2D2
//
// The input parameter timeDelta can be used to animate objects.
//
// You can use the keyboard to move around figures: 
//      W, S, A, D, N, M, R, F, UP, DOWN, LEFT, RIGHT
//
// Use OutputDebugStringW to print messages and values to Output window (remember always to end with '\n');
//

void Test(float fTimeDelta)
{
    // Planning
    OutputDebugStringW(L"Posing test...\n");

    Ray2D1.Direction.x = 1.0f;     Ray2D1.Direction.y = 0.0f;
    Ray2D1.Origin.x = 1.0f;        Ray2D1.Origin.y = 3.0f;

    Ray2D2.Direction.x = 1.0f;     Ray2D2.Direction.y = 0.0f;
    Ray2D2.Origin.x = 1.0f;        Ray2D2.Origin.y = 2.0f;

    LineSegment2D1.A.x = -1.0f;    LineSegment2D1.A.y = 0.0f;
    LineSegment2D1.B.x = -1.0f;    LineSegment2D1.B.y = 1.0f;

    LineSegment2D2.A.x = 1.0f;    LineSegment2D2.A.y = 0.0f;
    LineSegment2D2.B.x = 1.0f;    LineSegment2D2.B.y = 1.0f;

    Triangle2D1.A.x = 0.0f; Triangle2D1.A.y = 1.0f;
    Triangle2D1.B.x = -0.7f; Triangle2D1.B.y = 0.0f;
    Triangle2D1.C.x = 0.7f; Triangle2D1.C.y = 0.0f;

    Triangle2D2.A.x = -1.3f; Triangle2D2.A.y = 1.0f;
    Triangle2D2.B.x = -2.0f; Triangle2D2.B.y = 0.0f;
    Triangle2D2.C.x = -0.6f; Triangle2D2.C.y = 0.0f;

    Quadrilateral1.A.x = -0.5f; Quadrilateral1.A.y = 0.5f;
    Quadrilateral1.B.x = 0.5f; Quadrilateral1.B.y = 0.5f;
    Quadrilateral1.C.x = 0.5f; Quadrilateral1.C.y = -0.5f;
    Quadrilateral1.D.x = -0.5f; Quadrilateral1.D.y = -0.5f;

    Quadrilateral2.A.x = -0.5f; Quadrilateral2.A.y = 0.5f;
    Quadrilateral2.B.x = 0.5f; Quadrilateral2.B.y = 0.5f;
    Quadrilateral2.C.x = 0.5f; Quadrilateral2.C.y = -0.5f;
    Quadrilateral2.D.x = -0.5f; Quadrilateral2.D.y = -0.5f;

    Circle1.Center.x = 4.0f; Circle1.Center.y = 0.0f;
    Circle1.Radius = 1.0f;

    Circle2.Center.x = -5.0f; Circle2.Center.y = 0.0f;
    Circle2.Radius = 1.0f;

    // Test
    OutputDebugStringW(L"Executing test...\n");

    // Example of line rotation
    static float_q fRotation = 0.0f;
    fRotation += fTimeDelta;
    LineSegment2D1.Rotate(fRotation);
    LineSegment2D2.Rotate(fRotation);

    // Quadrilateral translation
    Quadrilateral1.Translate(0, -3);
    Quadrilateral2.Translate(0, -5);

    
    
    // Log (see output window)
    OutputDebugStringW(LineSegment2D1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(LineSegment2D2.ToString().c_str()); OutputDebugStringW(L"\n");

    OutputDebugStringW(Triangle2D1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(Triangle2D2.ToString().c_str()); OutputDebugStringW(L"\n");
 
    OutputDebugStringW(Quadrilateral1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(Quadrilateral2.ToString().c_str()); OutputDebugStringW(L"\n");
}

#endif