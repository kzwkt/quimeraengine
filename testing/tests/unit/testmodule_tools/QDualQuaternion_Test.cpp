// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QDualQuaternion.h"
#include "QDualQuaternionWhiteBox.h"
#include "QBaseVector3.h"
#include "QBaseVector4.h"

using Kinesis::QuimeraEngine::Tools::Math::QDualQuaternion;

QTEST_SUITE_BEGIN( QDualQuaternion_TestSuite )

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RZ = (float_q)1.5f;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_DX = (float_q)2.5f;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_DZ = (float_q)3.5f;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_4;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const float_q SCALAR = SQFloat::_0_5;

    // Execution
    QDualQuaternion dualQuaternionUT = SCALAR * DUALQUATERNION;

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHasNotChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

	// Execution
    QDualQuaternion dualQuaternionUT;

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks if copy constructor sets dual quaternion components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseQuaternion EXPECTED_VALUE_D = QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseQuaternion EXPECTED_VALUE_R = QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);

    const QDualQuaternion DQUAT_TO_COPY(EXPECTED_VALUE_R, EXPECTED_VALUE_D);

	// Execution
    QDualQuaternion dualQuaternionUT = DQUAT_TO_COPY;

    // Verification
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_VALUE_D);
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_VALUE_R);
}

/// <summary>
/// Checks that the components of the dual quaternion are correctly copied to other dual quaternion.
/// </summary>
QTEST_CASE ( Constructor3_IsCorrectlyCopied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseDualQuaternion;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_8;

	// Execution
    QDualQuaternion dualQuaternionUT(QBaseDualQuaternion(QBaseQuaternion(EXPECTED_VALUE_FOR_RX, EXPECTED_VALUE_FOR_RY, EXPECTED_VALUE_FOR_RZ, EXPECTED_VALUE_FOR_RW),
                                                         QBaseQuaternion(EXPECTED_VALUE_FOR_DX, EXPECTED_VALUE_FOR_DY, EXPECTED_VALUE_FOR_DZ, EXPECTED_VALUE_FOR_DW)));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
QTEST_CASE ( Constructor4_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_DY = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_DZ = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_DW = (float_q)-19.0f;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                       QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
QTEST_CASE ( Constructor4_DualPartIsNullWhenTranslationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                       QBaseVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
QTEST_CASE ( Constructor4_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                                       QBaseVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
QTEST_CASE ( Constructor5_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_DY = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_DZ = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_DW = (float_q)-19.0f;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                       QBaseVector4(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
QTEST_CASE ( Constructor5_DualPartIsNullWhenTranslationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                       QBaseVector4(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
QTEST_CASE ( Constructor5_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                                       QBaseVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
QTEST_CASE ( Constructor6_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_DX = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_DZ = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_DW = (float_q)-19.0f;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7),
                                                       QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
QTEST_CASE ( Constructor6_DualPartIsNullWhenTranslationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                       QBaseVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
QTEST_CASE ( Constructor6_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                       QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
QTEST_CASE ( Constructor7_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_DX = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_DZ = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_DW = (float_q)-19.0f;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseVector4(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8),
                                                       QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the real part is a null quaternion when the translation is a null vector.
/// </summary>
QTEST_CASE ( Constructor7_DualPartIsNullWhenTranslationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                       QBaseVector4(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
QTEST_CASE ( Constructor7_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(QBaseVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                       QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that all the values are correctly set.
/// </summary>
QTEST_CASE ( Constructor8_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_8;

    float_q* arDualPartComponents = new float_q[4];
    arDualPartComponents[0] = EXPECTED_VALUE_FOR_DX;
    arDualPartComponents[1] = EXPECTED_VALUE_FOR_DY;
    arDualPartComponents[2] = EXPECTED_VALUE_FOR_DZ;
    arDualPartComponents[3] = EXPECTED_VALUE_FOR_DW;

    float_q* arRealPartComponents = new float_q[4];
    arRealPartComponents[0] = EXPECTED_VALUE_FOR_RX;
    arRealPartComponents[1] = EXPECTED_VALUE_FOR_RY;
    arRealPartComponents[2] = EXPECTED_VALUE_FOR_RZ;
    arRealPartComponents[3] = EXPECTED_VALUE_FOR_RW;

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion(arRealPartComponents, arDualPartComponents);

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);

    // Cleaning
    delete[] arDualPartComponents;
    delete[] arRealPartComponents;
}

/// <summary>
/// Checks that the assertion fails when the input pointers are null.
/// </summary>
QTEST_CASE ( Constructor8_AssertionFailsWhenPointersAreNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    float_q* arDualPartComponents = new float_q[4];
    float_q* arRealPartComponents = new float_q[4];

    const float_q* NULL_POINTER = null_q;

    const bool EXPECTED_VALUE = true;

	// Execution
    bool bAssertionFailedBecauseRealPartIsNull = false;
    bool bAssertionFailedBecauseDualPartIsNull = false;

    try
    {
        QDualQuaternion dualQuaternion = QDualQuaternion(arRealPartComponents, NULL_POINTER);
    }
    catch(...) // TODO avillalba: A concrete exception should be caoght when it's implemented
    {
        bAssertionFailedBecauseRealPartIsNull = true;
    }

    try
    {
        QDualQuaternion dualQuaternion = QDualQuaternion(NULL_POINTER, arDualPartComponents);
    }
    catch(...) // TODO avillalba: A concrete exception should be caught when it's implemented
    {
        bAssertionFailedBecauseDualPartIsNull = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailedBecauseRealPartIsNull, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bAssertionFailedBecauseDualPartIsNull, EXPECTED_VALUE);
}

/// <summary>
/// Template method used by QDualQuaternionImp1_IsCorrectlyCreatedWhenUsingCommonTransformations_Test to test
/// using different template parameters for method QDualQuaternionImp.
/// </summary>
template<class VectorType>
void QDualQuaternionImp1_IsCorrectlyCreatedWhenUsingCommonTransformations_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_DY = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_DZ = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_DW = (float_q)-19.0f;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

    VectorType TRANSLATION;
    TRANSLATION.x = SQFloat::_5;
    TRANSLATION.y = SQFloat::_6;
    TRANSLATION.z = SQFloat::_7;

	// Execution
    QDualQuaternionWhiteBox dualQuaternionUT;
    dualQuaternionUT.QDualQuaternionImp(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                        TRANSLATION);

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
QTEST_CASE ( QDualQuaternionImp1_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    QDualQuaternionImp1_IsCorrectlyCreatedWhenUsingCommonTransformations_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    QDualQuaternionImp1_IsCorrectlyCreatedWhenUsingCommonTransformations_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by QDualQuaternionImp1_DualPartIsNullWhenTranslationIsNull_Test to test
/// using different template parameters for method QDualQuaternionImp.
/// </summary>
template<class VectorType>
void QDualQuaternionImp1_DualPartIsNullWhenTranslationIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

    VectorType TRANSLATION;

	// Execution
    QDualQuaternionWhiteBox dualQuaternionUT;
    dualQuaternionUT.QDualQuaternionImp(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                        TRANSLATION);

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
QTEST_CASE ( QDualQuaternionImp1_DualPartIsNullWhenTranslationIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    QDualQuaternionImp1_DualPartIsNullWhenTranslationIsNull_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    QDualQuaternionImp1_DualPartIsNullWhenTranslationIsNull_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by QDualQuaternionImp1_DualAndRealPartsAreNullWhenRotationIsNull_Test to test
/// using different template parameters for method QDualQuaternionImp.
/// </summary>
template<class VectorType>
void QDualQuaternionImp1_DualAndRealPartsAreNullWhenRotationIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

    VectorType TRANSLATION;
    TRANSLATION.x = SQFloat::_1;
    TRANSLATION.y = SQFloat::_2;
    TRANSLATION.z = SQFloat::_3;

	// Execution
    QDualQuaternionWhiteBox dualQuaternionUT;
    dualQuaternionUT.QDualQuaternionImp(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0),
                                        TRANSLATION);

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
QTEST_CASE ( QDualQuaternionImp1_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    QDualQuaternionImp1_DualAndRealPartsAreNullWhenRotationIsNull_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    QDualQuaternionImp1_DualAndRealPartsAreNullWhenRotationIsNull_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by QDualQuaternionImp2_IsCorrectlyCreatedWhenUsingCommonTransformations_Test to test
/// using different template parameters for method QDualQuaternionImp.
/// </summary>
template<class VectorType>
void QDualQuaternionImp2_IsCorrectlyCreatedWhenUsingCommonTransformations_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const float_q EXPECTED_VALUE_FOR_DX = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_DZ = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_DW = (float_q)-19.0f;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

    VectorType TRANSLATION;
    TRANSLATION.x = SQFloat::_5;
    TRANSLATION.y = SQFloat::_6;
    TRANSLATION.z = SQFloat::_7;

	// Execution
    QDualQuaternionWhiteBox dualQuaternionUT;
    dualQuaternionUT.QDualQuaternionImp(TRANSLATION,
                                        QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
QTEST_CASE ( QDualQuaternionImp2_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    QDualQuaternionImp2_IsCorrectlyCreatedWhenUsingCommonTransformations_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    QDualQuaternionImp2_IsCorrectlyCreatedWhenUsingCommonTransformations_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by QDualQuaternionImp2_DualPartIsNullWhenTranslationIsNull_Test to test
/// using different template parameters for method QDualQuaternionImp.
/// </summary>
template<class VectorType>
void QDualQuaternionImp2_DualPartIsNullWhenTranslationIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_4;

    VectorType TRANSLATION;

	// Execution
    QDualQuaternionWhiteBox dualQuaternionUT;
    dualQuaternionUT.QDualQuaternionImp(TRANSLATION,
                                        QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
QTEST_CASE ( QDualQuaternionImp2_DualPartIsNullWhenTranslationIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    QDualQuaternionImp2_DualPartIsNullWhenTranslationIsNull_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    QDualQuaternionImp2_DualPartIsNullWhenTranslationIsNull_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by QDualQuaternionImp2_DualAndRealPartsAreNullWhenRotationIsNull_Test to test
/// using different template parameters for method QDualQuaternionImp.
/// </summary>
template<class VectorType>
void QDualQuaternionImp2_DualAndRealPartsAreNullWhenRotationIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const float_q EXPECTED_VALUE_FOR_DX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DW = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RX = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RY = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RZ = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RW = SQFloat::_0;

    VectorType TRANSLATION;
    TRANSLATION.x = SQFloat::_1;
    TRANSLATION.y = SQFloat::_2;
    TRANSLATION.z = SQFloat::_3;

	// Execution
    QDualQuaternionWhiteBox dualQuaternionUT;
    dualQuaternionUT.QDualQuaternionImp(TRANSLATION,
                                        QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
QTEST_CASE ( QDualQuaternionImp2_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    QDualQuaternionImp2_DualAndRealPartsAreNullWhenRotationIsNull_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    QDualQuaternionImp2_DualAndRealPartsAreNullWhenRotationIsNull_Template<QBaseVector4>();
}

/// <summary>
/// Checks that the real part equals identity and dual one is null.
/// </summary>
QTEST_CASE ( GetIdentity_DualPartIsNullAndRealPartEqualsIdentity_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QQuaternion EXPECTED_REAL_PART = QQuaternion::GetIdentity();
    const QQuaternion EXPECTED_DUAL_PART = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    QDualQuaternion dualQuaternionUT = QDualQuaternion::GetIdentity();

    // Verification
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_REAL_PART);
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_DUAL_PART);
}

/// <summary>
/// Checks if two different dual quaternions are correctly added.
/// </summary>
QTEST_CASE ( OperatorAddition_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                     QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion((float_q)7.25f, SQFloat::_9, (float_q)11.0f, (float_q)13.0f),
                                                           QQuaternion((float_q)14.0f, (float_q)16.0f, (float_q)18.0f, (float_q)20.0f));

	// Execution
    QDualQuaternion dualQuaternionUT = OPERAND1 + OPERAND2;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtraction_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion((float_q)7.25f, SQFloat::_9, (float_q)11.0f, (float_q)13.0f),
                                                     QQuaternion((float_q)14.0f, (float_q)16.0f, (float_q)18.0f, (float_q)20.0f));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));

	// Execution
    QDualQuaternion dualQuaternionUT = OPERAND1 - OPERAND2;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct1_TwoDifferentQuaternionsAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                     QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion((float_q)30.5f, (float_q)22.25f, (float_q)52.0f, (float_q)2.25f),
                                                           QQuaternion((float_q)123.5f, (float_q)111.25f, (float_q)183.0f, (float_q)-36.75f));

	// Execution
    QDualQuaternion dualQuaternionUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the product is not commutative.
/// </summary>
QTEST_CASE ( OperatorProduct1_IsNotCommutative_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                     QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

	// Execution
    QDualQuaternion dualQuaternion1UT = OPERAND1 * OPERAND2;
    QDualQuaternion dualQuaternion2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK(dualQuaternion1UT != dualQuaternion2UT);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a scalar.
/// </summary>
QTEST_CASE ( OperatorProduct2_ScalarAndDualQuaternionAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const float_q SCALAR = SQFloat::_7;

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion((float_q)1.75f, (float_q)7.0f, (float_q)14.0f, (float_q)21.0f),
                                                           QQuaternion((float_q)21.0f, (float_q)28.0f, (float_q)35.0f, (float_q)42.0f));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION * SCALAR;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a vector.
/// </summary>
QTEST_CASE ( OperatorProduct3_ResultIsCorrectWhenUsingCommonVector_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const QBaseVector3 VECTOR(SQFloat::_9, SQFloat::_10, (float_q)11.0f);

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion((float_q)49.0f, (float_q)30.0f, (float_q)59.0f, (float_q)-54.0f));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION * VECTOR;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a vector.
/// </summary>
QTEST_CASE ( OperatorProduct4_ResultIsCorrectWhenUsingCommonVector_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const QBaseVector4 VECTOR(SQFloat::_9, SQFloat::_10, (float_q)11.0f, (float_q)12.0f);

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion((float_q)49.0f, (float_q)30.0f, (float_q)59.0f, (float_q)-54.0f));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION * VECTOR;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly divided by a scalar.
/// </summary>
QTEST_CASE ( OperatorDivision_DualQuaternionIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion((float_q)1.75f, (float_q)7.0f, (float_q)14.0f, (float_q)21.0f),
                                                           QQuaternion((float_q)21.0f, (float_q)28.0f, (float_q)35.0f, (float_q)42.0f));
    const float_q SCALAR = SQFloat::_7;

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION / SCALAR;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that an assertion fails when the input scalar equals zero.
/// </summary>
QTEST_CASE ( OperatorDivision_AssertionFailsWhenScalarEqualsZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion((float_q)1.75f, (float_q)7.0f, (float_q)14.0f, (float_q)21.0f),
                                                           QQuaternion((float_q)21.0f, (float_q)28.0f, (float_q)35.0f, (float_q)42.0f));
    const float_q SCALAR = SQFloat::_0;

    const bool EXPECTED_VALUE = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QDualQuaternion dualQuaternionUT = DUALQUATERNION / SCALAR;
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly added.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                     QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion((float_q)7.25f, SQFloat::_9, (float_q)11.0f, (float_q)13.0f),
                                                           QQuaternion((float_q)14.0f, (float_q)16.0f, (float_q)18.0f, (float_q)20.0f));

	// Execution
    QDualQuaternion dualQuaternionUT = OPERAND1;
    dualQuaternionUT += OPERAND2;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion((float_q)7.25f, SQFloat::_9, (float_q)11.0f, (float_q)13.0f),
                                                     QQuaternion((float_q)14.0f, (float_q)16.0f, (float_q)18.0f, (float_q)20.0f));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));

	// Execution
    QDualQuaternion dualQuaternionUT = OPERAND1;
    dualQuaternionUT -= OPERAND2;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_TwoDifferentQuaternionsAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                     QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion((float_q)30.5f, (float_q)22.25f, (float_q)52.0f, (float_q)2.25f),
                                                           QQuaternion((float_q)123.5f, (float_q)111.25f, (float_q)183.0f, (float_q)-36.75f));

	// Execution
    QDualQuaternion dualQuaternionUT = OPERAND1;
    dualQuaternionUT *= OPERAND2;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the product is not commutative.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_IsNotCommutative_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                     QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10),
                                                     QQuaternion((float_q)11.0f, (float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

	// Execution
    QDualQuaternion dualQuaternion1UT = OPERAND1;
    dualQuaternion1UT *= OPERAND2;
    QDualQuaternion dualQuaternion2UT = OPERAND2;
    dualQuaternion2UT *= OPERAND1;

    // Verification
    BOOST_CHECK(dualQuaternion1UT != dualQuaternion2UT);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_ScalarAndDualQuaternionAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));
    const float_q SCALAR = SQFloat::_7;

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion((float_q)1.75f, (float_q)7.0f, (float_q)14.0f, (float_q)21.0f),
                                                           QQuaternion((float_q)21.0f, (float_q)28.0f, (float_q)35.0f, (float_q)42.0f));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT *= SCALAR;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly divided by a scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_DualQuaternionIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion((float_q)1.75f, (float_q)7.0f, (float_q)14.0f, (float_q)21.0f),
                                                           QQuaternion((float_q)21.0f, (float_q)28.0f, (float_q)35.0f, (float_q)42.0f));
    const float_q SCALAR = SQFloat::_7;

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT /= SCALAR;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that an assertion fails when the input scalar equals zero.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_AssertionFailsWhenScalarEqualsZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion((float_q)1.75f, (float_q)7.0f, (float_q)14.0f, (float_q)21.0f),
                                                           QQuaternion((float_q)21.0f, (float_q)28.0f, (float_q)35.0f, (float_q)42.0f));
    const float_q SCALAR = SQFloat::_0;

    const bool EXPECTED_VALUE = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QDualQuaternion dualQuaternionUT = DUALQUATERNION / SCALAR;
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly assigned to another dual quaternion.
/// </summary>
QTEST_CASE ( OperatorAssignation_DualQuaternionIsAssignedProperlyToAnother_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion EXPECTED_VALUE = QDualQuaternion(QQuaternion(SQFloat::_0_25, SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                                           QQuaternion(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6));

	// Execution
    QDualQuaternion dualQuaternionUT;
    dualQuaternionUT = EXPECTED_VALUE;

    // Verification
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that all dual quaternion components are set to zero.
/// </summary>
QTEST_CASE ( ResetToZero_AllDualQuaternionComponentsAreSetToZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT.ResetToZero();

    // Verification
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that the dual quaternion is converted to an identity dual quaternion.
/// </summary>
QTEST_CASE ( ResetToIdentity_DualQuaternionBecomesIdentity_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const QDualQuaternion IDENTITY = QDualQuaternion::GetIdentity();

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT.ResetToIdentity();

    // Verification
    BOOST_CHECK(dualQuaternionUT == IDENTITY);
}

/// <summary>
/// Checks that a common dual quaternion is correctly conjugated.
/// </summary>
QTEST_CASE ( Conjugate_CommonDualQuaternionIsCorrectlyConjugated_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QQuaternion(-SQFloat::_1, -SQFloat::_2, -SQFloat::_3, SQFloat::_4),
                                                            QQuaternion(-SQFloat::_5, -SQFloat::_6, -SQFloat::_7, SQFloat::_8));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.Conjugate();

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly double conjugated.
/// </summary>
QTEST_CASE ( DoubleConjugate_CommonDualQuaternionIsCorrectlyDoubleConjugated_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QQuaternion(-SQFloat::_1, -SQFloat::_2, -SQFloat::_3, SQFloat::_4),
                                                            QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, -SQFloat::_8));

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.DoubleConjugate();

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the non dual length of a common dual quaternion is what expected.
/// </summary>
QTEST_CASE ( GetNonDualLength_CorrectNonDualLengthObtainedFromCommonDualQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const float_q EXPECTED_LENGTH = (float_q)5.4772258f;

	// Execution
    float_q fLengthUT = DUALQUATERNION.GetNonDualLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that a common dual quaternion is correctly transformed by another common dual quaternion.
/// </summary>
QTEST_CASE ( Transform_CommonDualQuaternionIsCorrectlyTransformedByAnother_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                     QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_9, SQFloat::_10, (float_q)11.0f, (float_q)12.0f),
                                                     QQuaternion((float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f));
    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QQuaternion((float_q)766.0f, (float_q)1308.0f, (float_q)698.0f, (float_q)1784.0f),
                                                            QQuaternion((float_q)2518.0f, (float_q)2884.0f, (float_q)2866.0f, (float_q)3488.0f));

    // Execution
    QDualQuaternion dualQuaternionUT = OPERAND1.Transform(OPERAND2);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by identity dual quaternion.
/// </summary>
QTEST_CASE ( Transform_ResultEqualsOriginalDualQuaternionWhenTransformingByIdentity_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion OPERAND = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                    QQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));
    const QDualQuaternion IDENTITY = QDualQuaternion::GetIdentity();

    const QDualQuaternion EXPECTED_RESULT = OPERAND;

    // Execution
    QDualQuaternion dualQuaternionUT = OPERAND.Transform(IDENTITY);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly rotated and translated.
/// </summary>
QTEST_CASE ( TransformRotationFirst1_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 TRANSLATION = QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7);

    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QBaseQuaternion((float_q)30.0f, (float_q)60.0f, (float_q)90.0f, (float_q)120.0f),
                                                            QBaseQuaternion((float_q)718.0f, (float_q)820.0f, (float_q)1114.0f, (float_q)-900.0f));

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
QTEST_CASE ( TransformRotationFirst1_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 TRANSLATION = QBaseVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QDualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly rotated and translated.
/// </summary>
QTEST_CASE ( TransformRotationFirst2_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector4 TRANSLATION = QBaseVector4(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);

    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QBaseQuaternion((float_q)30.0f, (float_q)60.0f, (float_q)90.0f, (float_q)120.0f),
                                                            QBaseQuaternion((float_q)718.0f, (float_q)820.0f, (float_q)1114.0f, (float_q)-900.0f));

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
QTEST_CASE ( TransformRotationFirst2_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector4 TRANSLATION = QBaseVector4(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QDualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly translated and rotated.
/// </summary>
QTEST_CASE ( TransformTranslationFirst1_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 TRANSLATION = QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7);

    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QBaseQuaternion((float_q)30.0f, (float_q)60.0f, (float_q)90.0f, (float_q)120.0f),
                                                            QBaseQuaternion((float_q)590.0f, (float_q)500.0f, (float_q)1370.0f, (float_q)-900.0f));

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
QTEST_CASE ( TransformTranslationFirst1_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 TRANSLATION = QBaseVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QDualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly translated and rotated.
/// </summary>
QTEST_CASE ( TransformTranslationFirst2_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector4 TRANSLATION = QBaseVector4(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);

    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QBaseQuaternion((float_q)30.0f, (float_q)60.0f, (float_q)90.0f, (float_q)120.0f),
                                                            QBaseQuaternion((float_q)590.0f, (float_q)500.0f, (float_q)1370.0f, (float_q)-900.0f));

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
QTEST_CASE ( TransformTranslationFirst2_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                           QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector4 TRANSLATION = QBaseVector4(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QDualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a correct "lerped" dual quaternion is obtained when two common dual quaternions are used.
/// </summary>
QTEST_CASE ( Lerp_CorrectLerpedDualQuaternionIsObtainedForTwoCommonDualQuaternions_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize(),
                                                     QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_8, SQFloat::_9, SQFloat::_10, (float_q)11.0f).Normalize(),
                                                     QBaseVector3((float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QQuaternion((float_q)0.24356697f, (float_q)0.39486650f, (float_q)0.54616600f, (float_q)0.69746554f),
                                                            QQuaternion((float_q)1.9485357f, (float_q)3.2050655f, (float_q)2.6460013f, (float_q)-4.9507084f));
    const float_q PROPORTION = SQFloat::_0_25;

    // Execution
    QDualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the interpolation between two equivalent dual quaternions results in the same dual quaternion.
/// </summary>
QTEST_CASE ( Lerp_InterpolatingTwoEquivalentDualQuaternionsGivesSameDualQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize(),
                                                     QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QDualQuaternion OPERAND2 = OPERAND1;

    const QDualQuaternion EXPECTED_RESULT = OPERAND1;

    const float_q PROPORTION = SQFloat::_0_25;

    // Execution
    QDualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the real part of the result equals identity when interpolating with the double conjugated.
/// </summary>
QTEST_CASE ( Lerp_RealPartEqualsIdentityWhenInterpolatingInTheMiddleOfDualQuaternionsAndItsDoubleConjugated_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize(),
                                                     QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QDualQuaternion OPERAND2 = OPERAND1.DoubleConjugate();

    const QQuaternion EXPECTED_REAL_PART_VALUE = QQuaternion::GetIdentity();

    const float_q PROPORTION = SQFloat::_0_5;

    // Execution
    QDualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK( dualQuaternionUT.r == EXPECTED_REAL_PART_VALUE );
}

/// <summary>
/// Checks that the result equals left operand when proportion equals zero.
/// </summary>
QTEST_CASE ( Lerp_ProportionZeroMeansNormalizedResidentQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize(),
                                                     QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_8, SQFloat::_9, SQFloat::_10, (float_q)11.0f).Normalize(),
                                                     QBaseVector3((float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_RESULT = OPERAND1;

    const float_q PROPORTION = SQFloat::_0;

    // Execution
    QDualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals right operand when proportion equals one.
/// </summary>
QTEST_CASE ( Lerp_ProportionOneMeansNormalizedInputQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QDualQuaternion OPERAND1 = QDualQuaternion(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize(),
                                                     QBaseVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QDualQuaternion OPERAND2 = QDualQuaternion(QQuaternion(SQFloat::_8, SQFloat::_9, SQFloat::_10, (float_q)11.0f).Normalize(),
                                                     QBaseVector3((float_q)12.0f, (float_q)13.0f, (float_q)14.0f));

    const QDualQuaternion EXPECTED_RESULT = OPERAND2;

    const float_q PROPORTION = SQFloat::_1;

    // Execution
    QDualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QDualQuaternion DUALQUATERNION = QDualQuaternion(QQuaternion(SQFloat::_0_25, (float_q)-0.000002f, (float_q)40000.0f, (float_q)1.0f),
                                                           QQuaternion(SQFloat::_0_25, (float_q)-0.000002f, (float_q)40000.0f, (float_q)1.0f));
    const string_q EXPECTED_STRING_FORM = QE_L("DQ(r(Q(0.25,-1.99999999e-006,40000,1)),d(Q(0.25,-1.99999999e-006,40000,1)))");

	// Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION;
    string_q strStringForm = dualQuaternionUT.ToString();

    // Verification
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

/// <summary>
/// Template method used by TransformRotationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Test to test
/// using different template parameters for method TransformRotationFirst.
/// </summary>
template<class VectorType>
void TransformRotationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;

    const QDualQuaternionWhiteBox DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                                   QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    VectorType TRANSLATION;
    TRANSLATION.x = SQFloat::_5;
    TRANSLATION.y = SQFloat::_6;
    TRANSLATION.z = SQFloat::_7;

    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QBaseQuaternion((float_q)30.0f, (float_q)60.0f, (float_q)90.0f, (float_q)120.0f),
                                                            QBaseQuaternion((float_q)718.0f, (float_q)820.0f, (float_q)1114.0f, (float_q)-900.0f));

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirstImp(ROTATION, TRANSLATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly rotated and translated.
/// </summary>
QTEST_CASE ( TransformRotationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    TransformRotationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    TransformRotationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by TransformRotationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test to test
/// using different template parameters for method TransformRotationFirst.
/// </summary>
template<class VectorType>
void TransformRotationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;

    const QDualQuaternionWhiteBox DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                                   QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const VectorType TRANSLATION;

    const QDualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirstImp(ROTATION, TRANSLATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
QTEST_CASE ( TransformRotationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    TransformRotationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    TransformRotationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by TransformTranslationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Test to test
/// using different template parameters for method TransformTranslationFirst.
/// </summary>
template<class VectorType>
void TransformTranslationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;

    const QDualQuaternionWhiteBox DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                                   QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    VectorType TRANSLATION;
    TRANSLATION.x = SQFloat::_5;
    TRANSLATION.y = SQFloat::_6;
    TRANSLATION.z = SQFloat::_7;

    const QDualQuaternion EXPECTED_RESULT = QDualQuaternion(QBaseQuaternion((float_q)30.0f, (float_q)60.0f, (float_q)90.0f, (float_q)120.0f),
                                                            QBaseQuaternion((float_q)590.0f, (float_q)500.0f, (float_q)1370.0f, (float_q)-900.0f));

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirstImp(TRANSLATION, ROTATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly translated and rotated.
/// </summary>
QTEST_CASE ( TransformTranslationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    TransformTranslationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    TransformTranslationFirstImp_CommonDualQuaternionIsCorrectlyTransformed_Template<QBaseVector4>();
}

/// <summary>
/// Template method used by TransformTranslationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test to test
/// using different template parameters for method TransformTranslationFirst.
/// </summary>
template<class VectorType>
void TransformTranslationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QDualQuaternionWhiteBox;

    const QDualQuaternionWhiteBox DUALQUATERNION = QDualQuaternion(QBaseQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4),
                                                                   QBaseQuaternion(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8));

    const QBaseQuaternion ROTATION = QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const VectorType TRANSLATION;

    const QDualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // Execution
    QDualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirstImp(TRANSLATION, ROTATION);

    // Verification
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
QTEST_CASE ( TransformTranslationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    BOOST_TEST_MESSAGE("VectorType=QBaseVector3");
    TransformTranslationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Template<QBaseVector3>();
    BOOST_TEST_MESSAGE("VectorType=QBaseVector4");
    TransformTranslationFirstImp_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Template<QBaseVector4>();
}

// End - Test Suite: QDualQuaternion
QTEST_SUITE_END()
