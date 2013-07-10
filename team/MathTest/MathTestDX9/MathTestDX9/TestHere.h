#ifndef __TESTHERE__
#define __TESTHERE__

#include "TestConfiguration.h"
#include "d3dx9.h"
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
    Ray3D1.Origin.x = 1.0f;        Ray3D1.Origin.y = 1.0f;       Ray3D1.Origin.z = -1.0f;

    Ray3D2.Direction.x = 1.0f;     Ray3D2.Direction.y = 0.0f;    Ray3D2.Direction.z = 0.0f;
    Ray3D2.Origin.x = 1.0f;        Ray3D2.Origin.y = 1.0f;       Ray3D2.Origin.z = -2.0f;

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

    Hexahedron1 = QHexahedron<VectorType>::GetUnitCube();
    Hexahedron2 = QHexahedron<VectorType>::GetUnitCube();

    Sphere1.Center.x = 0.0f; Sphere1.Center.y = 0.0f; Sphere1.Center.z = 0.0f;
    Sphere1.Radius = 1.0f;

    Sphere2.Center.x = 0.0f; Sphere2.Center.y = 0.0f; Sphere2.Center.z = 0.0f;
    Sphere2.Radius = 1.0f;

    // Test
    OutputDebugStringW(L"Executing test...\n");

    // Hexahedron animated rotation sample
    static float_q fRotationX = 0.0f;
    static float_q fRotationY = 0.0f;
    fRotationY += fTimeDelta;
    static float fRotationZ = 0.0f;
    fRotationZ += fTimeDelta * 0.05f;
    QRotationMatrix3x3 rMatrix(0.0f,fRotationY, fRotationZ);
    QQuaternion q1(0.0f, fRotationY, 0.0f), q2(0.0f, 0.0f, fRotationZ), q4;
    float_q fRotX, fRotY, fRotZ;
    rMatrix.GetRotation(q1);
    rMatrix.GetRotation(fRotX, fRotY, fRotZ);
    q4 = QQuaternion(0.0f, fRotationY, fRotationZ);
    q4.ToEulerAngles(fRotX, fRotY, fRotZ);
    D3DXQUATERNION q3, q5, qv;
    float_q fYaw = SQAngle::_Pi;
    float_q fPitch = SQAngle::_HalfPi;
    float_q fRoll = SQAngle::_QuarterPi;
    D3DXQuaternionRotationYawPitchRoll(&q3, fYaw, fPitch, fRoll);
    D3DXQuaternionNormalize(&q3, &q3);
    //Hexahedron1.Rotate(rcast_q(q3, QQuaternion&));

    D3DXQuaternionConjugate(&q5, &q3);
    qv.x = 1;
    qv.y = 2;
    qv.z = 4;
    qv.w = 0;
    float_q fLength1 = QVector3(qv.x, qv.y, qv.z).GetLength();
    D3DXQuaternionMultiply(&qv, &q3, &qv);
    D3DXQuaternionMultiply(&qv, &qv, &q5);
    
    D3DXMATRIX rotation, translation, scaling, transformation;
    D3DXMatrixRotationYawPitchRoll(&rotation, fYaw, fPitch, fRoll);
    D3DXMatrixScaling(&scaling, SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    D3DXMatrixTranslation(&translation, SQFloat::_2, SQFloat::_4, -SQFloat::_6);

    D3DXVECTOR3 vVector(1, 2, 4);
    transformation = scaling * rotation * translation;
    D3DXVECTOR3 vEye(1, 2, 3), vUp(0, 1, 0), vAt(0, 0, 1);
    D3DXMatrixLookAtLH(&transformation, &vEye, &vAt, &vUp);
    D3DXVec3TransformNormal(&vVector, &vVector, &transformation);

    /*QTransformationMatrix<QMatrix4x4>& mat = rcast_q(rot, QTransformationMatrix<QMatrix4x4>&);
    QTranslationMatrix<QMatrix4x4> mAux1;
    QScaleMatrix3x3 mAux2;
    mat.Decompose(mAux1, rMatrix, mAux2);*/
    float_q fLength2 = QVector3(qv.x, qv.y, qv.z).GetLength();

    Hexahedron1 = Hexahedron1.Translate(2.0f, 0.0f, 0.0f);

    // Hexahedron translation sample
    Hexahedron2 = Hexahedron2.Translate(2.0f, 0.0f, 2.0f);

    // Ray rotation sample
    Ray3D1 = Ray3D1.RotateWithPivot(QQuaternion(0.0f, 0.0f, fRotationY), VectorType(Ray3D1.Origin));

    // Sphere rotation
    Sphere1 = Sphere1.Translate(-3.0f, 0.0f, 0.0f);
    Sphere1.Radius = 0.3f;
    Sphere2 = Sphere2.Translate(-5.0f, 0.0f, 0.0f);
    Sphere1 = Sphere1.RotateWithPivot(QQuaternion(0.0f, fRotationY, 0.0f), Sphere2.Center);
    
    // Log (see output window)
    OutputDebugStringW(LineSegment3D1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(LineSegment3D2.ToString().c_str()); OutputDebugStringW(L"\n");

    OutputDebugStringW(Triangle3D1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(Triangle3D2.ToString().c_str()); OutputDebugStringW(L"\n");
 
    OutputDebugStringW(Hexahedron1.ToString().c_str()); OutputDebugStringW(L"\n");
    OutputDebugStringW(Hexahedron2.ToString().c_str()); OutputDebugStringW(L"\n");
}

#endif