// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QQuaternion.h"
#include "QQuaternionWhitebox.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

QTEST_SUITE_BEGIN( QQuaternion_TestSuite )

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByQuaternion_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)1.5f;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_3);
    const float_q  SCALAR = SQFloat::_0_5;

	// Execution
    QQuaternion qQuaternionUT = SCALAR * QUATERNION;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHasNotChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_0;

	// Execution
    QQuaternion qQuaternionUT;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the components of the quaternion are correctly copied to other quaternion.
/// </summary>
QTEST_CASE ( Constructor2_QuaternionIsCorrectlyCopied_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_W = SQFloat::_4;
    const QQuaternion QUATERNION(EXPECTED_VALUE_X, EXPECTED_VALUE_Y, EXPECTED_VALUE_Z, EXPECTED_VALUE_W);

	// Execution
    QQuaternion qQuaternionUT(QUATERNION);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_W);
}

/// <summary>
/// Checks that the quaternion is correctly built when using arbitrary Euler angles.
/// </summary>
QTEST_CASE ( Constructor3_QuaternionIsCorrectlyFormedWhenUsingArbitraryEulerAngles_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const float_q EXPECTED_VALUE_X = (float_q)0.56098545;
    const float_q EXPECTED_VALUE_Y = (float_q)0.092295930;
    const float_q EXPECTED_VALUE_Z = (float_q)0.43045926;
    const float_q EXPECTED_VALUE_W = (float_q)0.70105726;

    // Expected results calculated using DirectX SDK
    // D3DXQUATERNION q3;
    // float_q fYaw = D3DXToRadian(60);
    // float_q fPitch = D3DXToRadian(45);
    // float_q fRoll = D3DXToRadian(90);
    // D3DXQuaternionRotationYawPitchRoll(&q3, fYaw, fPitch, fRoll);

	// Execution
    QQuaternion qQuaternionUT(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_W) );
}

/// <summary>
/// Checks that the quaternion is correctly built when using arbitrary Euler angles.
/// </summary>
QTEST_CASE ( Constructor3_ResultIsNormalizedWhenUsingNonZeroAngles_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QQuaternion NORMALIZED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z).Normalize();

	// Execution
    QQuaternion qQuaternionUT(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    // Verification
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the identity quaternion is obtained when all the angles equal zero.
/// </summary>
QTEST_CASE ( Constructor3_IdentityIsObtainedWhenAllAnglesEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const float_q ALL_ANGLES_VALUE = SQFloat::_0;

    const QQuaternion EXPECTED_VALUE = QQuaternion::GetIdentity();

	// Execution
    QQuaternion qQuaternionUT(ALL_ANGLES_VALUE, ALL_ANGLES_VALUE, ALL_ANGLES_VALUE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that the quaternion is built by following the Yaw-Pitch-Roll rotation order.
/// </summary>
QTEST_CASE ( Constructor3_FollowsYawPitchRollRotationOrder_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QQuaternion PITCH = QQuaternion(EULER_ANGLE_X, SQFloat::_0, SQFloat::_0);
    const QQuaternion YAW   = QQuaternion(SQFloat::_0, EULER_ANGLE_Y, SQFloat::_0);
    const QQuaternion ROLL  = QQuaternion(SQFloat::_0, SQFloat::_0, EULER_ANGLE_Z);

    const QQuaternion EXPECTED_VALUE = ROLL * PITCH * YAW;

    // Expected results calculated using DirectX SDK
    // D3DXQUATERNION q3, yaw, pitch, roll;
    // float_q fYaw = D3DXToRadian(60);
    // float_q fPitch = D3DXToRadian(45);
    // float_q fRoll = D3DXToRadian(90);
    // D3DXQuaternionRotationYawPitchRoll(&yaw, fYaw, 0, 0);
    // D3DXQuaternionRotationYawPitchRoll(&pitch, 0, fPitch, 0);
    // D3DXQuaternionRotationYawPitchRoll(&roll, 0, 0, fRoll);
    // q3 = roll * pitch * yaw;

	// Execution
    QQuaternion qQuaternionUT(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreCorrectlySet_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_W = SQFloat::_4;

	// Execution
    QQuaternion qQuaternionUT(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_W);
}

/// <summary>
/// Checks that every element of the array is put in the correct component.
/// </summary>
QTEST_CASE ( Constructor5_QuaternionComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_4;

    float_q* VALID_ARRAY_OF_4_FLOATS = new float_q[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_Y;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_Z;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_W;

	// Execution
    QQuaternion qQuaternionUT(VALID_ARRAY_OF_4_FLOATS);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, VALID_ARRAY_OF_4_FLOATS[0]);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, VALID_ARRAY_OF_4_FLOATS[1]);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, VALID_ARRAY_OF_4_FLOATS[2]);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, VALID_ARRAY_OF_4_FLOATS[3]);

    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenPointerIsNull_Test )
{
    // Preparation
    const float_q* NULL_ARRAY = null_q;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QQuaternion qQuaternionUT(NULL_ARRAY);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if quaternion components are set to the correct values packed in a valid vf32 object.
/// </summary>
QTEST_CASE ( Constructor6_QuaternionComponentsAreSetToValidVF32PackedValues_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_4;

	vf32_q PACK;
	SQVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W, PACK);

	// Execution
	QQuaternion qQuaternionUT(PACK);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly formed when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
QTEST_CASE ( Constructor7_QuaternionCorrectlyFormedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4).Normalize();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const float_q EXPECTED_VALUE_FOR_X = (float_q)0.083508380;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.16701676;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)0.33403352;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)0.92387950;

    // Expected results calculated using DirectX SDK:
    // D3DXVECTOR3 axis(1, 2, 4);
    // D3DXVec3Normalize(&axis, &axis);
    // float_q fAngle = SQAngle::_QuarterPi;
    // D3DXQuaternionRotationAxis(&q3, &axis, fAngle);

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}


/// <summary>
/// Checks that the resultant quaternion is normalized when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
QTEST_CASE ( Constructor7_QuaternionIsNormalizedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4).Normalize();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const QQuaternion NORMALIZED_RESULT = QQuaternion(AXIS, ANGLE).Normalize();

    // Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using a null vector as axis.
/// </summary>
QTEST_CASE ( Constructor7_NoRotationStoredInQuaternionWhenUsingNullVectorAsAxis_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 AXIS = QVector3::GetZeroVector();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const float_q EXPECTED_VALUE_FOR_VECTOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Z = SQFloat::_3;

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    // Verifies that the vector doesn't rotate
    QVector3 vVectorForVerification(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using zero as angle.
/// </summary>
QTEST_CASE ( Constructor7_NoRotationStoredInQuaternionWhenUsingZeroAsAngle_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 AXIS = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6).Normalize();
    const float_q ANGLE = SQFloat::_0;

    const float_q EXPECTED_VALUE_FOR_VECTOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Z = SQFloat::_3;

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    // Verifies that the vector doesn't rotate
    QVector3 vVectorForVerification(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
}

/// <summary>
/// Checks that the resultant quaternion is not normalized when using a null vector as axis.
/// </summary>
QTEST_CASE ( Constructor7_ResultIsNotNormalizedWhenUsingNullVectorAsAxis_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 AXIS = QVector3::GetZeroVector();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const QQuaternion NORMALIZED_RESULT = QQuaternion(AXIS, ANGLE).Normalize();

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is not correct when a not normalized vector is used as axis.
/// </summary>
QTEST_CASE ( Constructor7_ResultIsIncorrectWhenUsingNotNormalizedAxis_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const QQuaternion CORRECT_QUATERNION(AXIS.Normalize(), ANGLE);

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( qQuaternionUT != CORRECT_QUATERNION );
}

/// <summary>
/// Checks that the quaternion is correctly formed when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
QTEST_CASE ( Constructor8_QuaternionCorrectlyFormedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector4 AXIS = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0).Normalize();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const float_q EXPECTED_VALUE_FOR_X = (float_q)0.083508380;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.16701676;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)0.33403352;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)0.92387950;

    // Expected results calculated using DirectX SDK:
    // D3DXVECTOR3 axis(1, 2, 4);
    // D3DXVec3Normalize(&axis, &axis);
    // float_q fAngle = SQAngle::_QuarterPi;
    // D3DXQuaternionRotationAxis(&q3, &axis, fAngle);

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the resultant quaternion is normalized when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
QTEST_CASE ( Constructor8_QuaternionIsNormalizedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector4 AXIS = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0).Normalize();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const QQuaternion NORMALIZED_RESULT = QQuaternion(AXIS, ANGLE).Normalize();

    // Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using a null vector as axis.
/// </summary>
QTEST_CASE ( Constructor8_NoRotationStoredInQuaternionWhenUsingNullVectorAsAxis_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector4 AXIS = QVector4::GetZeroVector();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const float_q EXPECTED_VALUE_FOR_VECTOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_VECTOR_W = SQFloat::_4;

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    // Verifies that the vector doesn't rotate
    QVector4 vVectorForVerification(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
    BOOST_CHECK_EQUAL( vVectorForVerification.w, EXPECTED_VALUE_FOR_VECTOR_W );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using zero as angle.
/// </summary>
QTEST_CASE ( Constructor8_NoRotationStoredInQuaternionWhenUsingZeroAsAngle_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector4 AXIS = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_0).Normalize();
    const float_q ANGLE = SQFloat::_0;

    const float_q EXPECTED_VALUE_FOR_VECTOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_VECTOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_VECTOR_W = SQFloat::_4;

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    // Verifies that the vector doesn't rotate
    QVector4 vVectorForVerification(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
    BOOST_CHECK_EQUAL( vVectorForVerification.w, EXPECTED_VALUE_FOR_VECTOR_W );
}

/// <summary>
/// Checks that the resultant quaternion is not normalized when using a null vector as axis.
/// </summary>
QTEST_CASE ( Constructor8_ResultIsNotNormalizedWhenUsingNullVectorAsAxis_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector4 AXIS = QVector4::GetZeroVector();

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const QQuaternion NORMALIZED_RESULT = QQuaternion(AXIS, ANGLE).Normalize();

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is not correct when a not normalized vector is used as axis.
/// </summary>
QTEST_CASE ( Constructor8_ResultIsIncorrectWhenUsingNotNormalizedAxis_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector4 AXIS = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_8);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ANGLE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_45;
#endif

    const QQuaternion CORRECT_QUATERNION(AXIS.Normalize(), ANGLE);

	// Execution
	QQuaternion qQuaternionUT(AXIS, ANGLE);

    // Verification
    BOOST_CHECK( qQuaternionUT != CORRECT_QUATERNION );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that only contains rotation is used.
/// </summary>
QTEST_CASE ( Constructor9_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION(QTranslationMatrix<QMatrix4x3>(),
                                                           QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           QScalingMatrix3x3());
    const QQuaternion EXPECTED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that contains translation, rotation and scale is used.
/// </summary>
QTEST_CASE ( Constructor9_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION(QTranslationMatrix<QMatrix4x3>(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           QScalingMatrix3x3(SQFloat::_0_25, -SQFloat::_0_5, (float_q)200.0f));
    const QQuaternion EXPECTED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION); // [TODO] Thund: Fails due to QTransformationMatrix problems

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a identity quaternion is obtained when using a transformation matrix that contains translation and scale but not rotation.
/// </summary>
QTEST_CASE ( Constructor9_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION(QTranslationMatrix<QMatrix4x3>(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QRotationMatrix3x3(),
                                                           QScalingMatrix3x3(SQFloat::_0_25, -SQFloat::_0_5, (float_q)200.0f));
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION); // [TODO] Thund: Fails due to QTransformationMatrix problems

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that an assertion fails when a transformation matrix whose elements all equal zero is used.
/// </summary>
QTEST_CASE ( Constructor9_AssertionFailsWhenUsingNullMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<QMatrix4x3> ZERO_MATRIX(QTransformationMatrix<QMatrix4x3>::GetZeroMatrix());
    const QQuaternion EXPECTED_RESULT(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QQuaternion qQuaternionUT(ZERO_MATRIX);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an identity quaternion is obtained when a transformation matrix is the identity.
/// </summary>
QTEST_CASE ( Constructor9_IdentityIsObtainedWhenUsingIdentityMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION(QTransformationMatrix<QMatrix4x3>::GetIdentity());
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that only contains rotation is used.
/// </summary>
QTEST_CASE ( Constructor10_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION(QTranslationMatrix<QMatrix4x4>(),
                                                           QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           QScalingMatrix3x3());
    const QQuaternion EXPECTED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that contains translation, rotation and scale is used.
/// </summary>
QTEST_CASE ( Constructor10_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION(QTranslationMatrix<QMatrix4x4>(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           QScalingMatrix3x3(SQFloat::_0_25, -SQFloat::_0_5, (float_q)200.0f));
    const QQuaternion EXPECTED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION); // [TODO] Thund: Fails due to QTransformationMatrix problems

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a identity quaternion is obtained when using a transformation matrix that contains translation and scale but not rotation.
/// </summary>
QTEST_CASE ( Constructor10_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION(QTranslationMatrix<QMatrix4x4>(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QRotationMatrix3x3(),
                                                           QScalingMatrix3x3(SQFloat::_0_25, -SQFloat::_0_5, (float_q)200.0f));
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION); // [TODO] Thund: Fails due to QTransformationMatrix problems

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that an assertion fails when a transformation matrix whose elements all equal zero is used.
/// </summary>
QTEST_CASE ( Constructor10_AssertionFailsWhenUsingNullMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<QMatrix4x4> ZERO_MATRIX(QTransformationMatrix<QMatrix4x4>::GetZeroMatrix());
    const QQuaternion EXPECTED_RESULT(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QQuaternion qQuaternionUT(ZERO_MATRIX);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an identity quaternion is obtained when a transformation matrix is the identity.
/// </summary>
QTEST_CASE ( Constructor10_IdentityIsObtainedWhenUsingIdentityMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION(QTransformationMatrix<QMatrix4x4>::GetIdentity());
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
	QQuaternion qQuaternionUT(TRANSFORMATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a common rotation matrix is used.
/// </summary>
QTEST_CASE ( Constructor11_QuaternionIsCorrectlyBuiltWhenUsingArbitraryRotationMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QRotationMatrix3x3 ROTATION(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QQuaternion EXPECTED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// Execution
	QQuaternion qQuaternionUT(ROTATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that an assertion fails when a rotation matrix whose elements all equal zero is used.
/// </summary>
QTEST_CASE ( Constructor11_AssertionFailsWhenUsingNullMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    const QRotationMatrix3x3 ZERO_MATRIX(QRotationMatrix3x3::GetZeroMatrix());
    const QQuaternion EXPECTED_RESULT(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QQuaternion qQuaternionUT = QQuaternion(ZERO_MATRIX);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an identity quaternion is obtained when a rotation matrix is the identity.
/// </summary>
QTEST_CASE ( Constructor11_IdentityIsObtainedWhenUsingIdentityMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    const QRotationMatrix3x3 ROTATION(QRotationMatrix3x3::GetIdentity());
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
	QQuaternion qQuaternionUT(ROTATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Template method used by QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QTransformationMatrix<MatrixType> TRANSFORMATION(QTranslationMatrix<MatrixType>(),
                                                           QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           QScalingMatrix3x3());
    const QQuaternion EXPECTED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// Execution
	QQuaternionWhiteBox qQuaternionUT;
    qQuaternionUT.QQuaternionImp(TRANSFORMATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that only contains rotation is used.
/// </summary>
QTEST_CASE ( QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_QuarterPi;
    const float_q EULER_ANGLE_Y = SQAngle::_ThirdPi;
    const float_q EULER_ANGLE_Z = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_45;
    const float_q EULER_ANGLE_Y = SQAngle::_60;
    const float_q EULER_ANGLE_Z = SQAngle::_90;
#endif

    const QTransformationMatrix<MatrixType> TRANSFORMATION(QTranslationMatrix<MatrixType>(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           QScalingMatrix3x3(SQFloat::_0_25, -SQFloat::_0_5, (float_q)200.0f));
    const QQuaternion EXPECTED_RESULT = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// Execution
	QQuaternionWhiteBox qQuaternionUT;
    qQuaternionUT.QQuaternionImp(TRANSFORMATION); // [TODO] Thund: Fails due to QTransformationMatrix problems

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that contains translation, rotation and scale is used.
/// </summary>
QTEST_CASE ( QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QQuaternionImp_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by QQuaternionImp_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void QQuaternionImp_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<MatrixType> TRANSFORMATION(QTranslationMatrix<MatrixType>(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QRotationMatrix3x3(),
                                                           QScalingMatrix3x3(SQFloat::_0_25, -SQFloat::_0_5, (float_q)200.0f));
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
	QQuaternionWhiteBox qQuaternionUT;
    qQuaternionUT.QQuaternionImp(TRANSFORMATION); // [TODO] Thund: Fails due to QTransformationMatrix problems

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a identity quaternion is obtained when using a transformation matrix that contains translation and scale but not rotation.
/// </summary>
QTEST_CASE ( QQuaternionImp_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QQuaternionImp_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QQuaternionImp_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by QQuaternionImp_AssertionFailsWhenUsingNullMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void QQuaternionImp_AssertionFailsWhenUsingNullMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<MatrixType> ZERO_MATRIX(QTransformationMatrix<MatrixType>::GetZeroMatrix());
    const QQuaternion EXPECTED_RESULT(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QQuaternionWhiteBox qQuaternionUT;
        qQuaternionUT.QQuaternionImp(ZERO_MATRIX);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when a transformation matrix whose elements all equal zero is used.
/// </summary>
QTEST_CASE ( QQuaternionImp_AssertionFailsWhenUsingNullMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QQuaternionImp_AssertionFailsWhenUsingNullMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QQuaternionImp_AssertionFailsWhenUsingNullMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by QQuaternionImp_IdentityIsObtainedWhenUsingIdentityMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void QQuaternionImp_IdentityIsObtainedWhenUsingIdentityMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION(QTransformationMatrix<QMatrix4x4>::GetIdentity());
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
	QQuaternionWhiteBox qQuaternionUT;
    qQuaternionUT.QQuaternionImp(TRANSFORMATION);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that an identity quaternion is obtained when a transformation matrix is the identity.
/// </summary>
QTEST_CASE ( QQuaternionImp_IdentityIsObtainedWhenUsingIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QQuaternionImp_IdentityIsObtainedWhenUsingIdentityMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QQuaternionImp_IdentityIsObtainedWhenUsingIdentityMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Checks that X, Y, and Z equal zero and W equals one.
/// </summary>
QTEST_CASE ( GetIdentity_XYZEqualZeroAndWEqualsOne_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_XYZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_1;

	// Execution
    QQuaternion qQuaternionUT = QQuaternion::GetIdentity();

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_XYZ);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_XYZ);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_XYZ);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different quaternions are correctly added.
/// </summary>
QTEST_CASE ( OperatorAddition_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3 + SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_9;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 + OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of adding two common quaternions is not normalized.
/// </summary>
QTEST_CASE ( OperatorAddition_ResultIsNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QQuaternion NORMALIZED_RESULT = (OPERAND1 + OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 + OPERAND2;

    // Verification
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks if two different quaternions are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtraction_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_3;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_9);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_0_5, SQFloat::_4, -SQFloat::_5, SQFloat::_6);

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 - OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of subtracting two common quaternions is not normalized.
/// </summary>
QTEST_CASE ( OperatorSubtraction_ResultIsNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QQuaternion NORMALIZED_RESULT = (OPERAND1 - OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 - OPERAND2;

    // Verification
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by another arbitrary quaternion.
/// </summary>
QTEST_CASE ( OperatorProduct1_QuaternionIsCorrectlyMultipliedByAnotherQuaternion_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)0.34045884;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.20951314;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)0.54997200;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)-0.73329598;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the product between quaternions is not commutative.
/// </summary>
QTEST_CASE ( OperatorProduct1_ProductIsNotCommutative_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternion1UT = OPERAND1 * OPERAND2;
    QQuaternion qQuaternion2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the product by an identity quaternion returns the same quaternion.
/// </summary>
QTEST_CASE ( OperatorProduct1_ProductByIdentityReturnsTheSame_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion IDENTITY_QUATERNION = QQuaternion::GetIdentity();
    const QQuaternion EXPECTED_RESULT = OPERAND;


	// Execution
    QQuaternion qQuaternionUT = OPERAND * IDENTITY_QUATERNION;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the product of a quaternion by its inverse returns the identity.
/// </summary>
QTEST_CASE ( OperatorProduct1_ProductByInverseReturnsIdentity_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion INVERSE = OPERAND.Invert();
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
    QQuaternion qQuaternionUT = OPERAND * INVERSE;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
QTEST_CASE ( OperatorProduct1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2);
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
QTEST_CASE ( OperatorProduct1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProduct2_QuaternionIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_2;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_0, -SQFloat::_2, SQFloat::_4);
    const float_q SCALAR = SQFloat::_0_5;

	// Execution
    QQuaternion qQuaternionUT = QUATERNION * SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 3D vector.
/// </summary>
QTEST_CASE ( OperatorProduct3_QuaternionIsCorrectlyMultipliedBy3DVector_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector3 VECTOR = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QQuaternion EXPECTED_RESULT = QQuaternion((float_q)11.0f, (float_q)4.0f, (float_q)15.0f, (float_q)-32.0f);

	// Execution
    QQuaternion qQuaternionUT = QUATERNION * VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
QTEST_CASE ( OperatorProduct3_ResultIsNotNormalized_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector3 VECTOR = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QQuaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// Execution
    QQuaternion qQuaternionUT = QUATERNION * VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 4D vector.
/// </summary>
QTEST_CASE ( OperatorProduct4_QuaternionIsCorrectlyMultipliedBy4DVector_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector4 VECTOR = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8);
    const QQuaternion EXPECTED_RESULT = QQuaternion((float_q)19.0f, (float_q)20.0f, (float_q)39.0f, (float_q)-16.0f);

	// Execution
    QQuaternion qQuaternionUT = QUATERNION * VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
QTEST_CASE ( OperatorProduct4_ResultIsNotNormalized_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector4 VECTOR = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QQuaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// Execution
    QQuaternion qQuaternionUT = QUATERNION * VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly divided by another arbitrary quaternion.
/// </summary>
QTEST_CASE ( OperatorDivision1_QuaternionIsCorrectlyDividedByAnotherQuaternion_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)-0.23570225;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)-2.8097901e-008;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)-0.23570226;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)0.94280905;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 / OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the division between quaternions is not commutative.
/// </summary>
QTEST_CASE ( OperatorDivision1_DivisionIsNotCommutative_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternion1UT = OPERAND1 / OPERAND2;
    QQuaternion qQuaternion2UT = OPERAND2 / OPERAND1;

    // Verification
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the division by an identity quaternion returns the same quaternion.
/// </summary>
QTEST_CASE ( OperatorDivision1_DivisionByIdentityReturnsTheSame_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion IDENTITY_QUATERNION = QQuaternion::GetIdentity();
    const QQuaternion EXPECTED_RESULT = OPERAND;

	// Execution
    QQuaternion qQuaternionUT = OPERAND / IDENTITY_QUATERNION;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
QTEST_CASE ( OperatorDivision1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2);
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 / OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
QTEST_CASE ( OperatorDivision1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1 / OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks if all the components of the quaternion are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivision2_QuaternionIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_8;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_0, -SQFloat::_2, SQFloat::_4);
    const float_q SCALAR = SQFloat::_0_5;

	// Execution
    QQuaternion qQuaternionUT = QUATERNION / SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}


/// <summary>
/// Checks if two different quaternions are correctly added.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3 + SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_9;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT += OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of adding two common quaternions is not normalized.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_ResultIsNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QQuaternion NORMALIZED_RESULT = (OPERAND1 + OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT += OPERAND2;

    // Verification
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks if the quaternion is correctly added and assigned to itself (same instance for both operands).
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_AddedToItself_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion EXPECTED_RESULT = QQuaternion(SQFloat::_0_5, SQFloat::_2, SQFloat::_4, SQFloat::_6);

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT += qQuaternionUT;

    // Verification
    BOOST_CHECK(qQuaternionUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if two different quaternions are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_3;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_9);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_0_5, SQFloat::_4, -SQFloat::_5, SQFloat::_6);

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT -= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of subtracting two common quaternions is not normalized.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_ResultIsNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QQuaternion NORMALIZED_RESULT = (OPERAND1 - OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT -= OPERAND2;

    // Verification
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks if the quaternion is correctly subtracted and assigned to itself (same instance for both operands).
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_SubtractedToItself_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion EXPECTED_RESULT = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT -= qQuaternionUT;

    // Verification
    BOOST_CHECK(qQuaternionUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by another arbitrary quaternion.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_QuaternionIsCorrectlyMultipliedByAnotherQuaternion_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)0.34045884;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.20951314;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)0.54997200;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)-0.73329598;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT *= OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the product between quaternions is not commutative.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_ProductIsNotCommutative_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternion1UT = OPERAND1;
    qQuaternion1UT *= OPERAND2;
    QQuaternion qQuaternion2UT = OPERAND2;
    qQuaternion2UT *= OPERAND1;

    // Verification
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the product by an identity quaternion returns the same quaternion.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_ProductByIdentityReturnsTheSame_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion IDENTITY_QUATERNION = QQuaternion::GetIdentity();
    const QQuaternion EXPECTED_RESULT = OPERAND;

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= IDENTITY_QUATERNION;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the product of a quaternion by its inverse returns the identity.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_ProductByInverseReturnsIdentity_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion INVERSE = OPERAND.Invert();
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= INVERSE;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2);
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT *= OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT *= OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by itself (same instance used for both operands).
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_QuaternionIsCorrectlyMultipliedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)0.22222225;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.44444451;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)0.66666675;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)-0.55555564;

    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= qQuaternionUT;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_QuaternionIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_2;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_0, -SQFloat::_2, SQFloat::_4);
    const float_q SCALAR = SQFloat::_0_5;

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by any of its own components (same instance used for both operands).
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_QuaternionIsCorrectlyMultipliedByOneOfItsComponents_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)288.0f;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)576.0f;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)864.0f;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)576.0f;

    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= qQuaternionUT.x;
    qQuaternionUT *= qQuaternionUT.y; // x 1
    qQuaternionUT *= qQuaternionUT.z; // x 2
    qQuaternionUT *= qQuaternionUT.w; // x 2 x 3

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 3D vector.
/// </summary>
QTEST_CASE ( OperatorProductAssignation3_QuaternionIsCorrectlyMultipliedBy3DVector_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector3 VECTOR = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QQuaternion EXPECTED_RESULT = QQuaternion((float_q)11.0f, (float_q)4.0f, (float_q)15.0f, (float_q)-32.0f);

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
QTEST_CASE ( OperatorProductAssignation3_ResultIsNotNormalized_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector3 VECTOR = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QQuaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 4D vector.
/// </summary>
QTEST_CASE ( OperatorProductAssignation4_QuaternionIsCorrectlyMultipliedBy4DVector_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector4 VECTOR = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8);
    const QQuaternion EXPECTED_RESULT = QQuaternion((float_q)19.0f, (float_q)20.0f, (float_q)39.0f, (float_q)-16.0f);

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
QTEST_CASE ( OperatorProductAssignation4_ResultIsNotNormalized_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QVector4 VECTOR = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QQuaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly divided by another arbitrary quaternion.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_QuaternionIsCorrectlyDividedByAnotherQuaternion_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)-0.23570225;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)-2.8097901e-008;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)-0.23570226;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)0.94280905;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT /= OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the division between quaternions is not commutative.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_DivisionIsNotCommutative_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();

	// Execution
    QQuaternion qQuaternion1UT = OPERAND1;
    qQuaternion1UT /= OPERAND2;
    QQuaternion qQuaternion2UT = OPERAND2;
    qQuaternion2UT /= OPERAND1;

    // Verification
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the division by an identity quaternion returns the same quaternion.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_DivisionByIdentityReturnsTheSame_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion IDENTITY_QUATERNION = QQuaternion::GetIdentity();
    const QQuaternion EXPECTED_RESULT = OPERAND;

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT /= IDENTITY_QUATERNION;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2);
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT /= OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2).Normalize();
    const QQuaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1;
    qQuaternionUT /= OPERAND2;

    // Verification
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly divided by itself (same instance used for both operands).
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_QuaternionIsCorrectlyDividedByItself_Test )
{
    // Preparation
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2).Normalize();
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT /= qQuaternionUT;

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks if all the components of the quaternion are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_QuaternionIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_8;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_0, -SQFloat::_2, SQFloat::_4);
    const float_q SCALAR = SQFloat::_0_5;

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT /= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly divided by any of its own components (same instance used for both operands).
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_QuaternionIsCorrectlyDivisionByOneOfItsComponents_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)1.5f;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)SQFloat::_1;

    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_2);

	// Execution
    QQuaternion qQuaternionUT = OPERAND;
    qQuaternionUT /= qQuaternionUT.x;
    qQuaternionUT /= qQuaternionUT.y; // / 1
    qQuaternionUT /= qQuaternionUT.z; // / 2
    qQuaternionUT /= qQuaternionUT.w; // / 2 / 3

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that a quaternion is correctly assigned to another quaternion.
/// </summary>
QTEST_CASE ( OperatorAssignation_QuaternionIsAssignedProperlyToAnother_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_4;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

	// Execution
    QQuaternion qQuaternionUT;
    qQuaternionUT = QUATERNION;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that all quaternion components are correctly negated.
/// </summary>
QTEST_CASE ( OperatorUnaryMinus_ComponentsAreNegated_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_4;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, -SQFloat::_2, SQFloat::_3, -SQFloat::_4);

	// Execution
    QQuaternion qQuaternionUT = -QUATERNION;

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that a common quaternion becomes a unit quaternion.
/// </summary>
QTEST_CASE ( Normalize_CommonQuaternionIsCorrectlyNormalized_Test )
{
    // Preparation
    const float_q EXPECTED_SQUAREDLENGTH = SQFloat::_1;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

	// Execution
    QQuaternion qQuaternionUT = QUATERNION.Normalize();

    // Verification
    float_q fSquaredLength = qQuaternionUT.GetSquaredLength();

    BOOST_CHECK(SQFloat::AreEqual(fSquaredLength, EXPECTED_SQUAREDLENGTH));
}

/// <summary>
/// Checks that the assertion fails when a null quaternion is to be normalized.
/// </summary>
QTEST_CASE ( Normalize_AssertionFailsWhenNullQuaternionIsToBeNormalized_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QQuaternion qQuaternionUT = QUATERNION.Normalize();
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that a common quaternion is correctly inverted.
/// </summary>
QTEST_CASE ( Invert_CommonQuaternionIsCorrectlyInverted_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion EXPECTED_RESULT = QQuaternion((float_q)-0.033333331, (float_q)0.066666663, (float_q)-0.099999994, (float_q)0.13333333);

	// Execution
    QQuaternion qQuaternionUT = QUATERNION.Invert();

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a normalized quaternion is correctly inverted.
/// </summary>
QTEST_CASE ( UnitInvert_NormalizedQuaternionIsCorrectlyInverted_Test )
{
    // Preparation
    const QQuaternion NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion EXPECTED_RESULT = QQuaternion((float_q)-0.18257418, (float_q)0.36514837, (float_q)-0.54772258, (float_q)0.73029673);

	// Execution
    QQuaternion qQuaternionUT = NORMALIZED_QUATERNION.UnitInvert();

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a quaternion that is not normalized is not correctly inverted.
/// </summary>
QTEST_CASE ( UnitInvert_NotNormalizedQuaternionIsNotCorrectlyInverted_Test )
{
    // Preparation
    const QQuaternion NOT_NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion NOT_EXPECTED_RESULT = QQuaternion((float_q)-0.18257418, (float_q)0.36514837, (float_q)-0.54772258, (float_q)0.73029673);

	// Execution
    QQuaternion qQuaternionUT = NOT_NORMALIZED_QUATERNION.UnitInvert();

    // Verification
    BOOST_CHECK( qQuaternionUT != NOT_EXPECTED_RESULT );
}

/// <summary>
/// Checks that all quaternion components are set to zero.
/// </summary>
QTEST_CASE ( ResetToZero_AllQuaternionComponentsAreSetToZero_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT.ResetToZero();

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that the quaternion is converted to an identity quaternion.
/// </summary>
QTEST_CASE ( ResetToIdentity_QuaternionBecomesIdentity_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_0);
    const QQuaternion IDENTITY = QQuaternion::GetIdentity();

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    qQuaternionUT.ResetToIdentity();

    // Verification
    BOOST_CHECK(qQuaternionUT == IDENTITY);
}

/// <summary>
/// Checks that the returned dot product result for 2 common quaternions equals the expected value.
/// </summary>
QTEST_CASE ( DotProduct_ReturnsDotProductFor2CommonQuaternions_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = (float_q)0.975900114;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7).Normalize();

	// Execution
    float_q fResultUT = OPERAND1.DotProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
QTEST_CASE ( DotProduct_DotProductIsCommutative_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7).Normalize();

	// Execution
    float_q fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the dot product equals one when both operands are the same.
/// </summary>
QTEST_CASE ( DotProduct_DotProductEqualsOneWhenRotationAxisIsTheSame_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const float_q EXPECTED_RESULT = (float_q)30.0f;
    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

	// Execution
    float_q fResultUT = OPERAND.DotProduct(OPERAND);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is a null quaternion.
/// </summary>
QTEST_CASE ( DotProduct_ReturnsZeroWhenAOperandIsNullQuaternion_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QQuaternion NONNULL_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    float_q fResult1UT = NONNULL_QUATERNION.DotProduct(NULL_QUATERNION);
    float_q fResult2UT = NULL_QUATERNION.DotProduct(NONNULL_QUATERNION);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for 2 common quaternions equals the expected value.
/// </summary>
QTEST_CASE ( DotProductAngle_ReturnsAngleBetween2CommonQuaternions_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        float_q EXPECTED_RESULT = SQAngle::_45;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
    #endif

    QVector3 ROTATION_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();

    const QQuaternion OPERAND1 = QQuaternion(ROTATION_AXIS, SQFloat::_0);
    const QQuaternion OPERAND2 = QQuaternion(ROTATION_AXIS, EXPECTED_RESULT);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
QTEST_CASE ( DotProductAngle_DotProductAngleIsCommutative_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);

	// Execution
    float_q fResult1UT = OPERAND1.DotProductAngle(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProductAngle(OPERAND1);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the angle equals zero when both quaternions are normalized and are the same.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleEqualsZeroWhenNormalizedQuaternionsAreTheSame_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QQuaternion OPERAND = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();

	// Execution
    float_q fResultUT = OPERAND.DotProductAngle(OPERAND);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleIsAlwaysPositive_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q HALF_CIRCUMFERENCE_ANGLE = -SQAngle::_180;
    #else
        const float_q HALF_CIRCUMFERENCE_ANGLE = -SQAngle::_Pi;
    #endif

    const QQuaternion REFERENCE_OPERAND = QQuaternion::GetIdentity();
    const QQuaternion QUATERNION = QQuaternion(QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0), HALF_CIRCUMFERENCE_ANGLE);

	// Execution
    float_q fResultUT = REFERENCE_OPERAND.DotProductAngle(QUATERNION);

    // Verification
    BOOST_CHECK( SQFloat::IsPositive(fResultUT) );
}

/// <summary>
/// Checks that a common quaternion is correctly conjugated.
/// </summary>
QTEST_CASE ( Conjugate_CommonQuaternionIsCorrectlyConjugated_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion EXPECTED_RESULT = QQuaternion(-SQFloat::_1, SQFloat::_2, -SQFloat::_3, SQFloat::_4);

	// Execution
    QQuaternion qQuaternionUT = QUATERNION.Conjugate();

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a correct quaternion is obtained as result of interpolating between 2 common quaternions.
/// </summary>
QTEST_CASE ( Lerp_CorrectLerpedQuaternionIsObtainedForTwoCommonQuaternions_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QQuaternion OPERAND1 = QQuaternion(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize(), SQFloat::_0).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize(), SQFloat::_1).Normalize();
    //const QQuaternion EXPECTED_RESULT = QQuaternion(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize(), SQFloat::_0_25).Normalize();
    // [TODO] Thund: There is a problem with imprecission, is it a matter of precission degradation or calculus error? It could be even an imprecission inherent to this Lerp process, reason to use Slerp
    const QQuaternion EXPECTED_RESULT = QQuaternion((float_q)0.032794558, (float_q)0.065589115, (float_q)0.098383665, (float_q)0.99244314);

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Lerp(SQFloat::_0_25, OPERAND2);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent NORMALIZED quaternions is the same quaternion.
/// </summary>
QTEST_CASE ( Lerp_InterpolatingTwoEquivalentNormalizedQuaternionsGivesSameQuaternion_Test )
{
    // Preparation
    const QQuaternion EXPECTED_RESULT = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();

	// Execution
    QQuaternion qQuaternionUT = EXPECTED_RESULT.Lerp(SQFloat::_0_5, EXPECTED_RESULT);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the result is always normalized, even if parameter is not.
/// </summary>
QTEST_CASE ( Lerp_ResultIsAlwaysNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);
    const QQuaternion EXPECTED_RESULT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the result of interpolating just in the middle between a quaternion and its conjugated is an identity quaternion.
/// </summary>
QTEST_CASE ( Lerp_InterpolatingInTheMiddleOfQuaternionsAndItsConjugatedGivesIdentityQuaternion_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = OPERAND1.Conjugate();
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 0, the returned quaternion is the resident quaternion, normalized.
/// </summary>
QTEST_CASE ( Lerp_ProportionZeroMeansNormalizedResidentQuaternion_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);
    const QQuaternion EXPECTED_RESULT = OPERAND1.Normalize();
    const float_q PROPORTION = SQFloat::_0;

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned quaternion is the input quaternion, normalized.
/// </summary>
QTEST_CASE ( Lerp_ProportionOneMeansNormalizedInputQuaternion_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);
    const QQuaternion EXPECTED_RESULT = OPERAND2.Normalize();
    const float_q PROPORTION = SQFloat::_1;

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that a correct quaternion is obtained as result of interpolating between 2 common quaternions.
/// </summary>
QTEST_CASE ( Slerp_CorrectSlerpedQuaternionIsObtainedForTwoCommonQuaternions_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QQuaternion OPERAND1 = QQuaternion(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize(), SQFloat::_0).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize(), SQFloat::_1).Normalize();
    const QQuaternion EXPECTED_RESULT = QQuaternion(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize(), SQFloat::_0_25).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Slerp(SQFloat::_0_25, OPERAND2);

    // Verification
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent NORMALIZED quaternions is the same quaternion.
/// </summary>
QTEST_CASE ( Slerp_InterpolatingTwoEquivalentNormalizedQuaternionsGivesSameQuaternion_Test )
{
    // Preparation
    const QQuaternion EXPECTED_RESULT = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();

	// Execution
    QQuaternion qQuaternionUT = EXPECTED_RESULT.Slerp(SQFloat::_0_5, EXPECTED_RESULT);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the result is always normalized, even if parameter is not.
/// </summary>
QTEST_CASE ( Slerp_ResultIsAlwaysNormalized_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8).Normalize();
    const QQuaternion EXPECTED_RESULT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2).Normalize();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Slerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SQFloat::AreEqual(qQuaternionUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the result of interpolating just in the middle between 2 a quaternion and its conjugated is an identity quaternion.
/// </summary>
QTEST_CASE ( Slerp_InterpolatingInTheMiddleOfQuaternionAndItsConjugatedGivesIdentityQuaternion_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = OPERAND1.Conjugate();
    const QQuaternion EXPECTED_RESULT = QQuaternion::GetIdentity();

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Slerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 0, the returned quaternion is the resident quaternion, normalized.
/// </summary>
QTEST_CASE ( Slerp_ProportionZeroMeansNormalizedResidentQuaternion_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);
    const QQuaternion EXPECTED_RESULT = OPERAND1.Normalize();
    const float_q PROPORTION = SQFloat::_0;

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Slerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned quaternion is the input quaternion, normalized.
/// </summary>
QTEST_CASE ( Slerp_ProportionOneMeansNormalizedInputQuaternion_Test )
{
    // Preparation
    const QQuaternion OPERAND1 = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion OPERAND2 = QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);
    const QQuaternion EXPECTED_RESULT = OPERAND2.Normalize();
    const float_q PROPORTION = SQFloat::_1;

	// Execution
    QQuaternion qQuaternionUT = OPERAND1.Slerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that obtained angles equal zero when the quaternion is the identity.
/// </summary>
QTEST_CASE ( ToEulerAngles_AnglesEqualZeroWhenQuaternionIsIdentity_Test )
{
    // Preparation
    const QQuaternion IDENTITY = QQuaternion::GetIdentity();
    const float_q EXPECTED_ANGLES = SQFloat::_0;

	// Execution
    float_q fAngleXUT = SQFloat::_1;
    float_q fAngleYUT = SQFloat::_1;
    float_q fAngleZUT = SQFloat::_1;
    IDENTITY.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    // Verification
    BOOST_CHECK_EQUAL(fAngleXUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleYUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleZUT, EXPECTED_ANGLES);
}

/// <summary>
/// Checks that correct angles are obtained from a common quaternion.
/// </summary>
QTEST_CASE ( ToEulerAngles_CorrectAnglesAreObtainedFromCommonQuaternion_Test )
{
    // Preparation
    const float_q EXPECTED_X_ANGLE = SQFloat::_1;
    const float_q EXPECTED_Y_ANGLE = SQFloat::_2;
    const float_q EXPECTED_Z_ANGLE = (float_q)-2.2831850;
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_4);

	// Execution
    float_q fAngleXUT = SQFloat::_0;
    float_q fAngleYUT = SQFloat::_0;
    float_q fAngleZUT = SQFloat::_0;
    QUATERNION.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fAngleXUT, EXPECTED_X_ANGLE) );
    BOOST_CHECK( SQFloat::AreEqual(fAngleYUT, EXPECTED_Y_ANGLE) );
    BOOST_CHECK( SQFloat::AreEqual(fAngleZUT, EXPECTED_Z_ANGLE) );
}

/// <summary>
/// Checks that obtained angles correspond to the same rotation, even if they don't coincide with the values used to create the quaternion.
/// </summary>
QTEST_CASE ( ToEulerAngles_ObtainedAnglesCorrespondToSameRotationEvenWhenAnglesAreNotWhatExpected_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QQuaternion QUATERNION = QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_4);
    const QVector3 VECTOR(SQFloat::_1, SQFloat::_0, SQFloat::_0);

	// Execution
    float_q fAngleXUT = SQFloat::_0;
    float_q fAngleYUT = SQFloat::_0;
    float_q fAngleZUT = SQFloat::_0;
    QVector3 vVectorRotatedWithOriginalAngles = VECTOR.Transform(QUATERNION);

    QUATERNION.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    QQuaternion qQuaternionCreatedWithObtainedAngles(fAngleXUT, fAngleYUT, fAngleZUT);
    QVector3 vVectorRotatedWithObtainedAngles = VECTOR.Transform(qQuaternionCreatedWithObtainedAngles);

    // Verification
    BOOST_CHECK( vVectorRotatedWithOriginalAngles == vVectorRotatedWithObtainedAngles );
}

/// <summary>
/// Checks that obtained angles equal zero when the quaternion is null.
/// </summary>
QTEST_CASE ( ToEulerAngles_AnglesEqualZeroWhenQuaternionIsNull_Test )
{
    // Preparation
    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_ANGLES = SQFloat::_0;

	// Execution
    float_q fAngleXUT = SQFloat::_1;
    float_q fAngleYUT = SQFloat::_1;
    float_q fAngleZUT = SQFloat::_1;
    NULL_QUATERNION.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    // Verification
    BOOST_CHECK_EQUAL(fAngleXUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleYUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleZUT, EXPECTED_ANGLES);
}

// TODO Thund: There is a special case, when X = +-90º. TEst it!

/// <summary>
/// Checks that the length of a common quaternion is what expected.
/// </summary>
QTEST_CASE ( GetLength_CorrectLengthObtainedFromCommonQuaternion_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const float_q EXPECTED_LENGTH = (float_q)5.4772258f;

	// Execution
    float_q fLengthUT = QUATERNION.GetLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that unit quaternions' length equals 1.
/// </summary>
QTEST_CASE ( GetLength_Equals1WhenUsingUnitQuaternion_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const float_q EXPECTED_LENGTH = SQFloat::_1;

	// Execution
    float_q fLengthUT = QUATERNION.GetLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that identity quaternion's length equals 1.
/// </summary>
QTEST_CASE ( GetLength_Equals1WhenUsingIdentity_Test )
{
    // Preparation
    const QQuaternion IDENTITY = QQuaternion::GetIdentity();
    const float_q EXPECTED_LENGTH = SQFloat::_1;

	// Execution
    float_q fLengthUT = IDENTITY.GetLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that null quaternion's length equals 0.
/// </summary>
QTEST_CASE ( GetLength_EqualsZeroWhenUsingNullQuaternion_Test )
{
    // Preparation
    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_LENGTH = SQFloat::_0;

	// Execution
    float_q fLengthUT = NULL_QUATERNION.GetLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that the squared length of a common quaternion is what expected.
/// </summary>
QTEST_CASE ( GetSquaredLength_CorrectLengthObtainedFromCommonQuaternion_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const float_q EXPECTED_LENGTH = (float_q)30.0f;

	// Execution
    float_q fLengthUT = QUATERNION.GetSquaredLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that unit quaternions' squared length equals 1.
/// </summary>
QTEST_CASE ( GetSquaredLength_Equals1WhenUsingUnitQuaternion_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const float_q EXPECTED_LENGTH = SQFloat::_1;

	// Execution
    float_q fLengthUT = QUATERNION.GetSquaredLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that identity quaternion's squared length equals 1.
/// </summary>
QTEST_CASE ( GetSquaredLength_Equals1WhenUsingIdentity_Test )
{
    // Preparation
    const QQuaternion IDENTITY = QQuaternion::GetIdentity();
    const float_q EXPECTED_LENGTH = SQFloat::_1;

	// Execution
    float_q fLengthUT = IDENTITY.GetSquaredLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that null quaternion's squared length equals 0.
/// </summary>
QTEST_CASE ( GetSquaredLength_EqualsZeroWhenUsingNullQuaternion_Test )
{
    // Preparation
    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_LENGTH = SQFloat::_0;

	// Execution
    float_q fLengthUT = NULL_QUATERNION.GetSquaredLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that correct angle and rotation axis are obtained from a common quaternion.
/// </summary>
QTEST_CASE ( ToAxisAngle1_CorrectAngleAndAxisAreObtainedFromCommonQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const float_q EXPECTED_ANGLE = SQFloat::_2;
    const QVector3 EXPECTED_AXIS = QVector3(-SQFloat::_1, SQFloat::_2, -SQFloat::_3).Normalize();

    const QQuaternion QUATERNION(QVector3(-SQFloat::_1, SQFloat::_2, -SQFloat::_3).Normalize(), SQFloat::_2);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector3 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the quaternion is the identity.
/// </summary>
QTEST_CASE ( ToAxisAngle1_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenQuaternionIsIdentity_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const float_q EXPECTED_ANGLE = SQFloat::_0;
    const QVector3 UNITVECTORX = QVector3::GetUnitVectorX();

    const QQuaternion IDENTITY = QQuaternion::GetIdentity();

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector3 vAxisUT;
    IDENTITY.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == UNITVECTORX );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals PI (or 180º) and rotation axis equals null vector when the quaternion is null.
/// </summary>
QTEST_CASE ( ToAxisAngle1_AxisIsNullAndAngleEqualsPiOr180WhenQuaternionIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_ANGLE = SQAngle::_Pi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_ANGLE = SQAngle::_180;
#endif

    const QVector3 EXPECTED_AXIS = QVector3::GetZeroVector();

    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector3 vAxisUT;
    NULL_QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that correct results are obtained when the rotation angle equals Pi (or 180º).
/// </summary>
QTEST_CASE ( ToAxisAngle1_CorrectValuesObtainedWhenRotationAngleEqualsPiOr180_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_ANGLE = SQAngle::_Pi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_ANGLE = SQAngle::_180;
#endif

    const QVector3 EXPECTED_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();
    const QQuaternion QUATERNION = QQuaternion(EXPECTED_AXIS, EXPECTED_ANGLE);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector3 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the rotation angle is zero.
/// </summary>
QTEST_CASE ( ToAxisAngle1_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenRotationAngleIsZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const float_q EXPECTED_ANGLE = SQFloat::_0;
    const QVector3 UNITVECTORX = QVector3::GetUnitVectorX();

    const QQuaternion QUATERNION = QQuaternion(UNITVECTORX, EXPECTED_ANGLE);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector3 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == UNITVECTORX );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle is always positive, even when the angle used to build the quaternion was negative.
/// </summary>
QTEST_CASE ( ToAxisAngle1_AngleIsAlwaysPositive_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const float_q EXPECTED_ANGLE = SQFloat::_2;
    const QVector3 AXIS = QVector3(-SQFloat::_1, SQFloat::_2, -SQFloat::_3).Normalize();

    const QQuaternion QUATERNION_USING_POSITIVE_ANGLE = QQuaternion(AXIS, EXPECTED_ANGLE);
    const QQuaternion QUATERNION_USING_NEGATIVE_ANGLE = QQuaternion(AXIS, -EXPECTED_ANGLE);

	// Execution
    float_q fAngleUTFromPositive = SQFloat::_0;
    float_q fAngleUTFromNegative = SQFloat::_0;
    QVector3 vAxisUT;
    QUATERNION_USING_POSITIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromPositive);
    QUATERNION_USING_NEGATIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromNegative);

    // Verification
    BOOST_CHECK_EQUAL( fAngleUTFromPositive, EXPECTED_ANGLE );
    BOOST_CHECK_EQUAL( fAngleUTFromNegative, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that correct angle and rotation axis are obtained from a common quaternion.
/// </summary>
QTEST_CASE ( ToAxisAngle2_CorrectAngleAndAxisAreObtainedFromCommonQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const float_q EXPECTED_ANGLE = SQFloat::_2;
    QVector4 EXPECTED_AXIS = QVector4(-SQFloat::_1, SQFloat::_2, -SQFloat::_3, SQFloat::_4).Normalize();
    EXPECTED_AXIS.w = SQFloat::_0; // Axis is a vector, not a point

    const QQuaternion QUATERNION(QVector4(-SQFloat::_1, SQFloat::_2, -SQFloat::_3, SQFloat::_4).Normalize(), SQFloat::_2);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector4 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the quaternion is the identity.
/// </summary>
QTEST_CASE ( ToAxisAngle2_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenQuaternionIsIdentity_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const float_q EXPECTED_ANGLE = SQFloat::_0;
    const QVector4 UNITVECTORX = QVector4::GetUnitVectorX();

    const QQuaternion IDENTITY = QQuaternion::GetIdentity();

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector4 vAxisUT;
    IDENTITY.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == UNITVECTORX );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals PI (or 180º) and rotation axis equals null vector when the quaternion is null.
/// </summary>
QTEST_CASE ( ToAxisAngle2_AxisIsNullAndAngleEqualsPiOr180WhenQuaternionIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_ANGLE = SQAngle::_Pi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_ANGLE = SQAngle::_180;
#endif

    const QVector4 EXPECTED_AXIS = QVector4::GetZeroVector();

    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector4 vAxisUT;
    NULL_QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that correct results are obtained when the rotation angle equals Pi (or 180º).
/// </summary>
QTEST_CASE ( ToAxisAngle2_CorrectValuesObtainedWhenRotationAngleEqualsPiOr180_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_ANGLE = SQAngle::_Pi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_ANGLE = SQAngle::_180;
#endif

    QVector4 EXPECTED_AXIS = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    EXPECTED_AXIS.w = SQFloat::_0; // Axis is a vector, not a point
    const QQuaternion QUATERNION = QQuaternion(EXPECTED_AXIS, EXPECTED_ANGLE);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector4 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the rotation angle is zero.
/// </summary>
QTEST_CASE ( ToAxisAngle2_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenRotationAngleIsZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const float_q EXPECTED_ANGLE = SQFloat::_0;
    QVector4 EXPECTED_AXIS = QVector4::GetUnitVectorX();

    const QQuaternion QUATERNION = QQuaternion(EXPECTED_AXIS, EXPECTED_ANGLE);

	// Execution
    float_q fAngleUT = SQFloat::_0;
    QVector4 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // Verification
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle is always positive, even when the angle used to build the quaternion was negative.
/// </summary>
QTEST_CASE ( ToAxisAngle2_AngleIsAlwaysPositive_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const float_q EXPECTED_ANGLE = SQFloat::_2;
    const QVector4 AXIS = QVector4(-SQFloat::_1, SQFloat::_2, -SQFloat::_3, SQFloat::_4).Normalize();

    const QQuaternion QUATERNION_USING_POSITIVE_ANGLE = QQuaternion(AXIS, EXPECTED_ANGLE);
    const QQuaternion QUATERNION_USING_NEGATIVE_ANGLE = QQuaternion(AXIS, -EXPECTED_ANGLE);

	// Execution
    float_q fAngleUTFromPositive = SQFloat::_0;
    float_q fAngleUTFromNegative = SQFloat::_0;
    QVector4 vAxisUT;
    QUATERNION_USING_POSITIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromPositive);
    QUATERNION_USING_NEGATIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromNegative);

    // Verification
    BOOST_CHECK_EQUAL( fAngleUTFromPositive, EXPECTED_ANGLE );
    BOOST_CHECK_EQUAL( fAngleUTFromNegative, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // Preparation
    const QQuaternion QUATERNION = QQuaternion(SQFloat::_0_25, (float_q)-0.000002f, (float_q)40000.0f, (float_q)1.0f );
    const string_q EXPECTED_STRING_FORM = QE_L("Q(0.25,-1.99999999e-006,40000,1)");

	// Execution
    QQuaternion qQuaternionUT = QUATERNION;
    string_q strStringForm = qQuaternionUT.ToString();

    // Verification
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// End - Test Suite: QQuaternion
QTEST_SUITE_END()
