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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ToolsExports.h"

#include "QSphere.h"

#include "SQAngle.h"
#include "QMatrix4x3.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTranslationMatrix.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QSphere;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector3, QVector4> TQTemplateTypes;

QTEST_SUITE_BEGIN( QSphere_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE_FOR_CENTER = T::GetZeroVector();
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QSphere<T> sphereUT;

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets sphere's center and radius properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_5;

    const QSphere<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QSphere<T> sphereUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets sphere's center and radius properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QOrb;

    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_5;

    const QOrb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QSphere<T> sphereUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_5;

	// [Execution]
    QSphere<T> sphereUT(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned sphere has not changed since the last time the test was executed.
/// </summary>
QTEST_CASE_TEMPLATE ( GetUnitSphere_ValueHasNotChanged_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;

    const QSphere<T> EXPECTED_ORB = QSphere<T>(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QSphere<T> sphereUT = QSphere<T>::GetUnitSphere();

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a sphere is correctly assigned to another sphere.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_SphereIsAssignedProperlyToAnother_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QOrb;

    // [Preparation]
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_5 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_4;

    const QOrb<T> OTHER_ORB = QOrb<T>(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QSphere<T> sphereUT;
    sphereUT = OTHER_ORB;

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a common sphere is correctly translated using common translation vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_CommonSphereIsCorrectlyTranslatedWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

    const QVector3 TRANSLATION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_SphereIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const QVector3 TRANSLATION = QVector3::GetZeroVector();

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly translated using common translation values.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_CommonSphereIsCorrectlyTranslatedWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

    const float_q TRANSLATION_X = SQFloat::_1;
    const float_q TRANSLATION_Y = SQFloat::_2;
    const float_q TRANSLATION_Z = SQFloat::_3;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_SphereIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const float_q TRANSLATION_X = SQFloat::_0;
    const float_q TRANSLATION_Y = SQFloat::_0;
    const float_q TRANSLATION_Z = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_SphereIsNotRotatedWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion::GetIdentity();

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetZeroVector();

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_SphereIsCorrectlyTransformedByCommonQuaternions_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QQuaternion ROTATION = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { (float_q)0.29289321881345243, (float_q)1.2928932188134525, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_SphereIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion::GetIdentity();

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_CommonSphereIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const float_q RADIUS_SCALE = SQFloat::_2;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the components of the scaling vector and the radius scale equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_SphereIsNotScaledWhenVectorComponentsAndRadiusScaleEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();
    const float_q RADIUS_SCALE = SQFloat::_1;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    const QVector3 SCALE = QVector3::GetZeroVector();
    const float_q RADIUS_SCALE = SQFloat::_0;

    const float_q RADIUS = SQFloat::_5;
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetZeroVector();
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling values.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_CommonSphereIsCorrectlyScaledWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;
    const float_q RADIUS_SCALE = SQFloat::_2;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the values equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_SphereIsNotScaledWhenValuesEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;
    const float_q RADIUS_SCALE = SQFloat::_1;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the values equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenValuesEqualZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;
    const float_q RADIUS_SCALE = SQFloat::_0;

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetZeroVector();
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonSphereIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const float_q RADIUS_SCALE = SQFloat::_2;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the components of the scaling vector equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_SphereIsNotTranslatedWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();
    const float_q RADIUS_SCALE = SQFloat::_1;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToPivotPositionWhenVectorIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    const QVector3 SCALE = QVector3::GetZeroVector();
    const float_q RADIUS_SCALE = SQFloat::_0;

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling values.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonSphereIsCorrectlyScaledWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;
    const float_q RADIUS_SCALE = SQFloat::_2;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the values equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_SphereIsNotScaledWhenValuesEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;
    const float_q RADIUS_SCALE = SQFloat::_1;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the values equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedPivotPositionWhenValuesEqualZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;
    const float_q RADIUS_SCALE = SQFloat::_0;

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_SphereIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { 0.70710659f, -SQFloat::_4, -2.1213202f, SQFloat::_1 };
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { (float_q)0.70710678118654768, -SQFloat::_4, (float_q)-2.1213203435596428, SQFloat::_1 };
#endif

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_SphereIsNotRotatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetIdentity();

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetZeroVector();

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_SphereIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the rotation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_SphereIsNotRotateWithPivotdWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3::GetIdentity();

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the rotation matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Template method used by Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly translated using common translation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetZeroMatrix();

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_CommonSphereIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const float_q RADIUS_SCALE = SQFloat::_2;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_SphereIsNotScaledWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetIdentity();
    const float_q RADIUS_SCALE = SQFloat::_1;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();
    const float_q RADIUS_SCALE = SQFloat::_0;

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetZeroVector();
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonSphereIsCorrectlyScaledWhenUsingCommonMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const float_q RADIUS_SCALE = SQFloat::_2;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_SphereIsNotTranslatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetIdentity();
    const float_q RADIUS_SCALE = SQFloat::_1;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetZeroMatrix();
    const float_q RADIUS_SCALE = SQFloat::_0;

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Template method used by Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const float_q RADIUS_SCALE = SQFloat::_2;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { (float_q)6.0658639918226491, SQFloat::_8, (float_q)-10.419417382415922, SQFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Transform(TRANSFORMATION, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetZeroVector();

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetZeroMatrix();
    const float_q RADIUS_SCALE = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Transform(TRANSFORMATION, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
}

/// <summary>
/// Checks that all the center of the sphere is moved to the coordinate origin when transformation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();
    const float_q RADIUS_SCALE = SQFloat::_1;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Transform(TRANSFORMATION, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_SphereIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    QSpaceConversionMatrix CONVERSION = QSpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    const float_q CENTER_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T CENTER(CENTER_COMPONENTS);
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(CENTER, RADIUS);

    const QSphere<T> EXPECTED_SPHERE = QSphere<T>(CENTER.Transform(CONVERSION),
                                                  RADIUS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK(returnedSphere == EXPECTED_SPHERE);
}

/// <summary>
/// Checks that the sphere doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_SphereDoesNotChangeWhenTransformedByIdentityMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QSpaceConversionMatrix IDENTITY_MATRIX = QSpaceConversionMatrix::GetIdentity();

	const float_q CENTER_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T CENTER(CENTER_COMPONENTS);
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(CENTER, RADIUS);

    const QSphere<T> EXPECTED_SPHERE = SPHERE;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(returnedSphere == EXPECTED_SPHERE);
}

/// <summary>
/// Checks that the sphere is nullified when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_EndpointsAreNullifiedWhenMatrixIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QSpaceConversionMatrix ZERO_MATRIX = QMatrix4x4::GetZeroMatrix();

	const float_q CENTER_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T CENTER(CENTER_COMPONENTS);
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(CENTER, RADIUS);

    const QSphere<T> EXPECTED_SPHERE = QSphere<T>(T::GetZeroVector(), RADIUS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.Transform(ZERO_MATRIX);

    // [Verification]
    BOOST_CHECK(returnedSphere == EXPECTED_SPHERE);
}

/// <summary>
/// Template method used by TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const float_q RADIUS_SCALE = SQFloat::_2;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_q EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SQFloat::_3, SQFloat::_7, -SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_10;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.TransformWithPivot(TRANSFORMATION, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetZeroMatrix();
    const float_q RADIUS_SCALE = SQFloat::_0;

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.TransformWithPivot(TRANSFORMATION, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
}

/// <summary>
/// Checks that all the center of the sphere is moved to the position of the pivot point when transformation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();
    const float_q RADIUS_SCALE = SQFloat::_1;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QSphere<T> returnedSphere = SPHERE.TransformWithPivot(TRANSFORMATION, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SQFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that it returns "negative side" when the sphere is "behind" the plane and doesn't intersect with it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheSphereIsBehindPlaneAndTheyDoNotIntersect_Test, TQTemplateTypes )
{
    //     ____        |
    //    /    \       |
    //   |      |      |-->
    //    \____/       |
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_1;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// [Execution]
    EQSpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the sphere is "in front" the plane and doesn't intersect with it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheSphereIsInFrontPlaneAndTheyDoNotIntersect_Test, TQTemplateTypes )
{
    //    |         ____
    //    |        /    \
    //    |-->    |      |
    //    |        \____/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_1;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// [Execution]
    EQSpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the sphere intersects with the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheSphereIntersectsWithThePlane_Test, TQTemplateTypes )
{
    //     |
    //   __|__
    //  /  |  \
    // |   |   |
    //  \__|__/
    //     |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_10;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_BothSides;

	// [Execution]
    EQSpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the sphere is "behind" the plane and is tangent to it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheSphereIsBehindPlaneAndIsTangentToPlane_Test, TQTemplateTypes )
{
    //     ____ |
    //    /    \|
    //   |      |-->
    //    \____/|
    //          |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

    const float_q RADIUS = SQFloat::_5;
    const QVector3 PLANE_TO_SPHERE = QVector3(PLANE.a, PLANE.b, PLANE.c) * RADIUS;

    const float_q VECTOR_COMPONENTS_CENTER[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER) - PLANE_TO_SPHERE, RADIUS);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// [Execution]
    EQSpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the sphere is "in front" of the plane and is tangent to it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheSphereIsInFrontPlaneAndIsTangentToPlane_Test, TQTemplateTypes )
{
    //    | ____
    //    |/    \
    //    |-->   |
    //    |\____/
    //    |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const float_q RADIUS = SQFloat::_5;
    const QVector3 PLANE_TO_SPHERE = QVector3(PLANE.a, PLANE.b, PLANE.c) * RADIUS;

    const float_q VECTOR_COMPONENTS_CENTER[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER) + PLANE_TO_SPHERE, RADIUS);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// [Execution]
    EQSpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is not different when the plane is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ResultIsNotDifferentWhenPlaneIsNotNormalized_Test, TQTemplateTypes )
{
    //     ____ |
    //    /    \|
    //   |      |-->
    //    \____/|
    //          |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane NONNORMALIZED_PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10);
    const QPlane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_q RADIUS = SQFloat::_5;
    const QVector3 PLANE_TO_SPHERE = QVector3(NORMALIZED_PLANE.a, NORMALIZED_PLANE.b, NORMALIZED_PLANE.c) * RADIUS;

    const float_q VECTOR_COMPONENTS_CENTER[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SQFloat::_1 };
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER) - PLANE_TO_SPHERE, RADIUS);

	// [Execution]
    EQSpaceRelation eResultNonNotmalized = SPHERE.SpaceRelation(NONNORMALIZED_PLANE);
    EQSpaceRelation eResultNormalized = SPHERE.SpaceRelation(NORMALIZED_PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResultNonNotmalized, eResultNormalized);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_AssertionFailsWhenPlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const QBasePlane NULL_PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPHERE.SpaceRelation(NULL_PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the radius equals zero.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_AssertionFailsWhenRadiusEqualsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_0;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const QBasePlane PLANE = QBasePlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPHERE.SpaceRelation(PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the sphere is correctly projected to the plane when it is in its negative side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_SphereIsProjectedWhenItIsInNegativeSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, -SQFloat::_5, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_COMPONENTS_CENTER[] = { (float_q)1.8095238095238098, (float_q)-3.3809523809523805, (float_q)6.238095238095239, SQFloat::_1 };

    const QSphere<T> EXPECTED_SPHERE = QSphere<T>(T(EXPECTED_COMPONENTS_CENTER), RADIUS);

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

	// [Execution]
    QSphere<T> projectedSphere = SPHERE.ProjectToPlane(PLANE);

    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedSphere.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedSphere.Center == EXPECTED_SPHERE.Center);
    BOOST_CHECK(projectedSphere.Radius == EXPECTED_SPHERE.Radius);
}

/// <summary>
/// Checks that the sphere is correctly projected to the plane when it is in its positive side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_SphereIsProjectedWhenItIsInPositiveSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_COMPONENTS_CENTER[] = { (float_q)-0.28571428571428581, (float_q)-5.5714285714285712, (float_q)-2.1428571428571432, SQFloat::_1 };
    const QSphere<T> EXPECTED_SPHERE = QSphere<T>(T(EXPECTED_COMPONENTS_CENTER), RADIUS);

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, SQFloat::_10).Normalize();

	// [Execution]
    QSphere<T> projectedSphere = SPHERE.ProjectToPlane(PLANE);

    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedSphere.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedSphere.Center == EXPECTED_SPHERE.Center);
    BOOST_CHECK(projectedSphere.Radius == EXPECTED_SPHERE.Radius);
}

/// <summary>
/// Checks that the sphere is correctly projected to the plane when it intersects with the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_SphereIsProjectedWhenItIntersectsWithPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_q EXPECTED_COMPONENTS_CENTER[] = { SQFloat::_0, -SQFloat::_5, SQFloat::_0, SQFloat::_1 };
    const QSphere<T> EXPECTED_SPHERE = QSphere<T>(T(EXPECTED_COMPONENTS_CENTER), RADIUS);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

	// [Execution]
    QSphere<T> projectedSphere = SPHERE.ProjectToPlane(PLANE);

    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedSphere.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedSphere.Center == EXPECTED_SPHERE.Center);
    BOOST_CHECK(projectedSphere.Radius == EXPECTED_SPHERE.Radius);
}

/// <summary>
/// Checks that the result is different when the plane is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE( ProjectToPlane_ResultIsDifferentWhenPlaneIsNotNormalized_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane NONNORMALIZED_PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10);
    const QPlane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

	// [Execution]
    QSphere<T> resultNonNotmalized = SPHERE.ProjectToPlane(NONNORMALIZED_PLANE);
    QSphere<T> resultNormalized = SPHERE.ProjectToPlane(NORMALIZED_PLANE);

    // [Verification]
    BOOST_CHECK(resultNonNotmalized != resultNormalized);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE( ProjectToPlane_AssertionFailsWhenPlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q RADIUS = SQFloat::_5;
    const QSphere<T> SPHERE = QSphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const QBasePlane NULL_PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPHERE.ProjectToPlane(NULL_PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// End - Test Suite: QSphere
QTEST_SUITE_END()
