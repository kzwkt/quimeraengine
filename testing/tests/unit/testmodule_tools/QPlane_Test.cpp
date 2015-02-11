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

#include "QBasePlane.h"
#include "QPlane.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QQuaternion.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QTranslationMatrix.h"
#include "QTransformationMatrix.h"
#include "SQVF32.h"
#include "SQAngle.h"
#include "QSpaceConversionMatrix.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Tools::Math::QPlane;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;
using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

typedef boost::mpl::list<QVector3, QVector4> TQVectorTypes;
typedef boost::mpl::list<QMatrix4x3, QMatrix4x4> TQMatrixTypes;


QTEST_SUITE_BEGIN( QPlane_TestSuite )

/// <summary>
/// Checks if all the components of the plane are multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByPlane_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_1 + SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_2;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const float_q SCALAR = SQFloat::_0_5;

	// [Execution]
    QPlane planeUT = SCALAR * PLANE;

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_0;

	// [Execution]
    QPlane planeUT;

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if copy constructor sets plane's components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

    const QPlane PLANE_TO_COPY(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    QPlane planeUT = PLANE_TO_COPY;

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if base type constructor sets plane's components properly.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

    const QBasePlane PLANE_TO_COPY(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    QPlane planeUT = QPlane(PLANE_TO_COPY);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if values used as parameters are properly set to plane's components.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

	// [Execution]
    QPlane planeUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if the value provided is set to all the plane's components.
/// </summary>
QTEST_CASE ( Constructor5_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_5;

	// [Execution]
    QPlane planeUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_ALL) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_ALL) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_ALL) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_ALL) );
}

/// <summary>
/// Checks if the plane's components are set to the correct floats stored in a valid memory space.
/// </summary>
QTEST_CASE ( Constructor6_VectorComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

    float_q* VALID_ARRAY_OF_4_FLOATS = new float_q[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_A;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_B;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_C;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_D;

	// [Execution]
    QPlane planeUT(VALID_ARRAY_OF_4_FLOATS);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, VALID_ARRAY_OF_4_FLOATS[0]) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, VALID_ARRAY_OF_4_FLOATS[1]) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, VALID_ARRAY_OF_4_FLOATS[2]) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, VALID_ARRAY_OF_4_FLOATS[3]) );

    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    float_q* NULL_ARRAY = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPlane planeUT(NULL_ARRAY);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if plane's components are set to the correct values packed in a valid vf32 object.
/// </summary>
QTEST_CASE ( Constructor7_VectorComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;
    using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;

    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

	vf32_q PACK;
	SQVF32::Pack(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D, PACK);

	// [Execution]
	QPlane planeUT(PACK);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the plane is correctly constructed when using 3 common points (not coincidental).
/// </summary>
QTEST_CASE ( Constructor8_PlaneIsConstructedWhenUsingThreeCommonPoints_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QVector3 POINT1 = QVector3(SQFloat::_2, SQFloat::_0, SQFloat::_0);
    const QVector3 POINT2 = QVector3(SQFloat::_0, SQFloat::_2, SQFloat::_0);
    const QVector3 POINT3 = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_2);

    const float_q EXPECTED_VALUE_FOR_A = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_B = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_C = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_D = (float_q)-1.1547005383792517;

	// [Execution]
    QPlane planeUT = QPlane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when any of the points coincide.
/// </summary>
QTEST_CASE ( Constructor8_AssertionFailsWhenAnyOfThePointsCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QVector3 SAME_POINT = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 DIFFERENT_POINT = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QPlane(SAME_POINT, SAME_POINT, DIFFERENT_POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QPlane(DIFFERENT_POINT, SAME_POINT, SAME_POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    bool bAssertionFailed3 = false;

    try
    {
        QPlane(SAME_POINT, DIFFERENT_POINT, SAME_POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed3 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed3, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the points belong to the same line.
/// </summary>
QTEST_CASE ( Constructor8_AssertionFailsWhenPointsAreCollinear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QVector3 POINT1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 POINT2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QVector3 POINT3 = QVector3(SQFloat::_7, SQFloat::_8, SQFloat::_9);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPlane(POINT1, POINT2, POINT3);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the returned plane is normalized.
/// </summary>
QTEST_CASE ( Constructor8_ConstructedPlaneIsNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QVector3 POINT1 = QVector3(SQFloat::_2, SQFloat::_0, SQFloat::_0);
    const QVector3 POINT2 = QVector3(SQFloat::_0, SQFloat::_2, SQFloat::_0);
    const QVector3 POINT3 = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_2);

    const float_q EXPECTED_VALUE_FOR_A = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_B = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_C = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_D = (float_q)-1.1547005383792517;

	// [Execution]
    QPlane planeUT = QPlane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that a different order of the points might change the resultant plane.
/// </summary>
QTEST_CASE ( Constructor8_OrderOfPointsAffectsResult_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QVector3 POINT1 = QVector3(SQFloat::_2, SQFloat::_0, SQFloat::_0);
    const QVector3 POINT2 = QVector3(SQFloat::_0, SQFloat::_2, SQFloat::_0);
    const QVector3 POINT3 = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_2);

	// [Execution]
    // Imagine that you use the normal of the plane that points to the origin as the rotation axis
    // of a clock whose hands spins pointing, one by one, to the points
    QPlane planeUT1 = QPlane(POINT1, POINT2, POINT3); //  Direction
    QPlane planeUT2 = QPlane(POINT1, POINT3, POINT2); // -Direction
    QPlane planeUT3 = QPlane(POINT2, POINT1, POINT3); // -Direction
    QPlane planeUT4 = QPlane(POINT2, POINT3, POINT1); //  Direction
    QPlane planeUT5 = QPlane(POINT3, POINT1, POINT2); //  Direction
    QPlane planeUT6 = QPlane(POINT3, POINT2, POINT1); // -Direction

    // [Verification]
    BOOST_CHECK(planeUT1 != planeUT2);
    BOOST_CHECK(planeUT1 != planeUT3);
    BOOST_CHECK(planeUT1 == planeUT4);
    BOOST_CHECK(planeUT1 == planeUT5);
    BOOST_CHECK(planeUT1 != planeUT6);
    BOOST_CHECK(planeUT2 == planeUT3);
    BOOST_CHECK(planeUT2 != planeUT4);
    BOOST_CHECK(planeUT2 != planeUT5);
    BOOST_CHECK(planeUT2 == planeUT6);
    BOOST_CHECK(planeUT3 != planeUT4);
    BOOST_CHECK(planeUT3 != planeUT5);
    BOOST_CHECK(planeUT3 == planeUT6);
    BOOST_CHECK(planeUT4 == planeUT5);
    BOOST_CHECK(planeUT4 != planeUT6);
    BOOST_CHECK(planeUT5 != planeUT6);
}

/// <summary>
/// Checks that the plane is correctly constructed when using 3 common points (not coincidental).
/// </summary>
QTEST_CASE ( Constructor9_PlaneIsConstructedWhenUsingThreeCommonPoints_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QVector4 POINT1 = QVector4(SQFloat::_2, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector4 POINT2 = QVector4(SQFloat::_0, SQFloat::_2, SQFloat::_0, SQFloat::_1);
    const QVector4 POINT3 = QVector4(SQFloat::_0, SQFloat::_0, SQFloat::_2, SQFloat::_1);

    const float_q EXPECTED_VALUE_FOR_A = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_B = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_C = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_D = (float_q)-1.1547005383792517;

	// [Execution]
    QPlane planeUT = QPlane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when any of the points coincides.
/// </summary>
QTEST_CASE ( Constructor9_AssertionFailsWhenAnyOfThePointsCoincides_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QVector4 SAME_POINT = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QVector4 DIFFERENT_POINT = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QPlane(SAME_POINT, SAME_POINT, DIFFERENT_POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QPlane(DIFFERENT_POINT, SAME_POINT, SAME_POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    bool bAssertionFailed3 = false;

    try
    {
        QPlane(SAME_POINT, DIFFERENT_POINT, SAME_POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed3 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed3, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the points belong to the same line.
/// </summary>
QTEST_CASE ( Constructor9_AssertionFailsWhenPointsAreCollinear_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QVector4 POINT1 = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QVector4 POINT2 = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1);
    const QVector4 POINT3 = QVector4(SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_1);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPlane(POINT1, POINT2, POINT3);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the returned plane is normalized.
/// </summary>
QTEST_CASE ( Constructor9_ConstructedPlaneIsNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QVector4 POINT1 = QVector4(SQFloat::_2, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector4 POINT2 = QVector4(SQFloat::_0, SQFloat::_2, SQFloat::_0, SQFloat::_1);
    const QVector4 POINT3 = QVector4(SQFloat::_0, SQFloat::_0, SQFloat::_2, SQFloat::_1);

    const float_q EXPECTED_VALUE_FOR_A = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_B = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_C = (float_q)0.57735026918962584;
    const float_q EXPECTED_VALUE_FOR_D = (float_q)-1.1547005383792517;

	// [Execution]
    QPlane planeUT = QPlane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that a different order of the points might change the resultant plane.
/// </summary>
QTEST_CASE ( Constructor9_OrderOfPointsAffectsResult_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QVector4 POINT1 = QVector4(SQFloat::_2, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector4 POINT2 = QVector4(SQFloat::_0, SQFloat::_2, SQFloat::_0, SQFloat::_1);
    const QVector4 POINT3 = QVector4(SQFloat::_0, SQFloat::_0, SQFloat::_2, SQFloat::_1);

	// [Execution]
    // Imagine that you use the normal of the plane that points to the origin as the rotation axis
    // of a clock whose hands spins pointing, one by one, to the points
    QPlane planeUT1 = QPlane(POINT1, POINT2, POINT3); //  Direction
    QPlane planeUT2 = QPlane(POINT1, POINT3, POINT2); // -Direction
    QPlane planeUT3 = QPlane(POINT2, POINT1, POINT3); // -Direction
    QPlane planeUT4 = QPlane(POINT2, POINT3, POINT1); //  Direction
    QPlane planeUT5 = QPlane(POINT3, POINT1, POINT2); //  Direction
    QPlane planeUT6 = QPlane(POINT3, POINT2, POINT1); // -Direction

    // [Verification]
    BOOST_CHECK(planeUT1 != planeUT2);
    BOOST_CHECK(planeUT1 != planeUT3);
    BOOST_CHECK(planeUT1 == planeUT4);
    BOOST_CHECK(planeUT1 == planeUT5);
    BOOST_CHECK(planeUT1 != planeUT6);
    BOOST_CHECK(planeUT2 == planeUT3);
    BOOST_CHECK(planeUT2 != planeUT4);
    BOOST_CHECK(planeUT2 != planeUT5);
    BOOST_CHECK(planeUT2 == planeUT6);
    BOOST_CHECK(planeUT3 != planeUT4);
    BOOST_CHECK(planeUT3 != planeUT5);
    BOOST_CHECK(planeUT3 == planeUT6);
    BOOST_CHECK(planeUT4 == planeUT5);
    BOOST_CHECK(planeUT4 != planeUT6);
    BOOST_CHECK(planeUT5 != planeUT6);
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( GetNullPlane_ExpectedValueIsReturned_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_0;

	// [Execution]
    QPlane planeUT = QPlane::GetNullPlane();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPlaneZX_ExpectedValueIsReturned_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_0;

	// [Execution]
    QPlane planeUT = QPlane::GetPlaneZX();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPlaneXY_ExpectedValueIsReturned_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_0;

	// [Execution]
    QPlane planeUT = QPlane::GetPlaneXY();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPlaneYZ_ExpectedValueIsReturned_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_0;

	// [Execution]
    QPlane planeUT = QPlane::GetPlaneYZ();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if all the components of the plane are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProduct_PlaneIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_8);
    const float_q SCALAR = SQFloat::_0_5;

	// [Execution]
    QPlane planeUT = PLANE * SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if all the components of the plane are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivision_PlaneIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_8);
    const float_q SCALAR = SQFloat::_2;

	// [Execution]
    QPlane planeUT = PLANE / SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if all the components of the plane are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_PlaneIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_8);
    const float_q SCALAR = SQFloat::_0_5;

	// [Execution]
    QPlane planeUT = PLANE;
    planeUT *= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if all the components of the plane are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_PlaneIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_4;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_8);
    const float_q SCALAR = SQFloat::_2;

	// [Execution]
    QPlane planeUT = PLANE;
    planeUT /= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all plane components but D are correctly negated.
/// </summary>
QTEST_CASE ( OperatorUnaryMinus_AllComponentsButDAreNegated_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = -SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_C = -SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_D = -SQFloat::_8;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, EXPECTED_VALUE_FOR_D);

	// [Execution]
    QPlane planeUT = -PLANE;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a plane is correctly assigned to another vector.
/// </summary>
QTEST_CASE ( OperatorAssignation_PlaneIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_A = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_B = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_C = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_D = SQFloat::_8;

    const QPlane PLANE = QPlane(EXPECTED_VALUE_FOR_A,
                                EXPECTED_VALUE_FOR_B,
                                EXPECTED_VALUE_FOR_C,
                                EXPECTED_VALUE_FOR_D);

	// [Execution]
    QPlane planeUT = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    planeUT = PLANE;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a common plane becomes a normalized plane.
/// </summary>
QTEST_CASE ( Normalize_CommonPlaneIsCorrectlyNormalized_Test )
{
    // [Preparation]
    const float_q EXPECTED_SQUAREDLENGTH = SQFloat::_1;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

	// [Execution]
    QPlane planeUT = PLANE.Normalize();

    // [Verification]
    float_q fSquaredLength = planeUT.GetSquaredLength();

    BOOST_CHECK(SQFloat::AreEqual(fSquaredLength, EXPECTED_SQUAREDLENGTH));
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when a null plane is to be normalized.
/// </summary>
QTEST_CASE ( Normalize_AssertionFailsWhenNullPlaneIsToBeNormalized_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Normalize();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the returned dot product result for 1 common plane and a common vector equals the expected value.
/// </summary>
QTEST_CASE ( DotProduct1_ReturnsDotProductForCommonVectorAndPlane_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const float_q EXPECTED_RESULT = (float_q)32.0;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7);
    const QVector3 VECTOR = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// [Execution]
    float_q fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when vector is orthogonal to the plane.
/// </summary>
QTEST_CASE ( DotProduct1_DotProductEqualsZeroWhenVectorIsOrthogonalToPlane_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane PLANE = QPlane(SQFloat::_3, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 VECTOR = QVector3(SQFloat::_0, SQFloat::_3, SQFloat::_0);

	// [Execution]
    float_q fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null.
/// </summary>
QTEST_CASE ( DotProduct1_ReturnsZeroWhenAOperandIsNull_Test )
{
    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane NONNULL_PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QPlane NULL_PLANE = QPlane::GetNullPlane();

    const QVector3 NONNULL_VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 NULL_VECTOR = QVector3::GetNullVector();

	// [Execution]
    float_q fResult1UT = NONNULL_PLANE.DotProduct(NULL_VECTOR);
    float_q fResult2UT = NULL_PLANE.DotProduct(NONNULL_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned dot product result for 1 common plane and a common vector equals the expected value.
/// </summary>
QTEST_CASE ( DotProduct2_ReturnsDotProductForCommonVectorAndPlane_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const float_q EXPECTED_RESULT = (float_q)32.0;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7);
    const QVector4 VECTOR = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8);

	// [Execution]
    float_q fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when vector is orthogonal to the plane.
/// </summary>
QTEST_CASE ( DotProduct2_DotProductEqualsZeroWhenVectorIsOrthogonalToPlane_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane PLANE = QPlane(SQFloat::_3, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector4 VECTOR = QVector4(SQFloat::_0, SQFloat::_3, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null.
/// </summary>
QTEST_CASE ( DotProduct2_ReturnsZeroWhenAOperandIsNull_Test )
{
    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane NONNULL_PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QPlane NULL_PLANE = QPlane::GetNullPlane();

    const QVector4 NONNULL_VECTOR = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QVector4 NULL_VECTOR = QVector4::GetNullVector();

	// [Execution]
    float_q fResult1UT = NONNULL_PLANE.DotProduct(NULL_VECTOR);
    float_q fResult2UT = NULL_PLANE.DotProduct(NONNULL_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
QTEST_CASE ( DotProduct2_VectorsWComponentDoesNotTakePartInTheOperation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QVector4 VECTOR1 = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QVector4 VECTOR2 = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResult1UT = PLANE.DotProduct(VECTOR1);
    float_q fResult2UT = PLANE.DotProduct(VECTOR2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the returned dot product result for 2 common planes equals the expected value.
/// </summary>
QTEST_CASE ( DotProduct3_ReturnsDotProductFor2Commonplanes_Test )
{
    // [Preparation]
    const float_q EXPECTED_RESULT = (float_q)32.0;

    const QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7);
    const QPlane OPERAND2 = QPlane(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8);

	// [Execution]
    float_q fResultUT = OPERAND1.DotProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
QTEST_CASE ( DotProduct3_DotProductIsCommutative_Test )
{
    // [Preparation]
    const QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7);
    const QPlane OPERAND2 = QPlane(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8);

	// [Execution]
    float_q fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the dot product equals zero when planes are orthogonal.
/// </summary>
QTEST_CASE ( DotProduct3_DotProductEqualsZeroWhenPlanesAreOrthogonal_Test )
{
    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane OPERAND1 = QPlane(SQFloat::_3, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QPlane OPERAND2 = QPlane(SQFloat::_0, SQFloat::_3, SQFloat::_0, SQFloat::_0);
    const QPlane OPERAND3 = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_3, SQFloat::_0);

	// [Execution]
    float_q fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProduct(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null plane.
/// </summary>
QTEST_CASE ( DotProduct3_ReturnsZeroWhenAOperandIsNullplane_Test )
{
    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane NONNULL_PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QPlane NULL_PLANE = QPlane::GetNullPlane();

	// [Execution]
    float_q fResult1UT = NONNULL_PLANE.DotProduct(NULL_PLANE);
    float_q fResult2UT = NULL_PLANE.DotProduct(NONNULL_PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for a common vector and a plane equals the expected value.
/// </summary>
QTEST_CASE ( AngleBetween1_ReturnsAngleBetweenCommonVectorAndPlane_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        float_q EXPECTED_RESULT = SQAngle::_45;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
    #endif

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_0);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the angle equals zero when the normal of the plane and the vector are parallel.
/// </summary>
QTEST_CASE ( AngleBetween1_AngleEqualsZeroWhenVectorAndPlaneNormalAreParallel_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 VECTOR = QVector3(SQFloat::_9, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when the normal of the plane and the vector are orthogonal.
/// </summary>
QTEST_CASE ( AngleBetween1_AngleEqualsHalfPiRadiansOr90DegreesWhenVectorAndPlaneNormalAreOrthogonal_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_90;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_HalfPi;
    #endif

    const QPlane PLANE = QPlane(SQFloat::_5, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 VECTOR = QVector3(SQFloat::_0, SQFloat::_5, SQFloat::_0);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when vector and the normal of the plane are opposite.
/// </summary>
QTEST_CASE ( AngleBetween1_AngleEqualsPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreOpposite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_180;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_Pi;
    #endif

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 VECTOR = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
QTEST_CASE ( AngleBetween1_AngleIsAlwaysPositive_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QPlane REFERENCE_OPERAND = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);                       // _
    const QVector3 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, SQFloat::_1, SQFloat::_0);  // \_
    const QVector3 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, -SQFloat::_1, SQFloat::_0); // /¨

	// [Execution]
    float_q fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SQFloat::IsGreaterOrEquals(fResult1UT, SQFloat::_0) );
    BOOST_CHECK( SQFloat::IsGreaterOrEquals(fResult2UT, SQFloat::_0) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when vector and the normal of the plane are not opposite.
/// </summary>
QTEST_CASE ( AngleBetween1_AngleIsLowerThanPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreNotOpposite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_180;
    #else
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_Pi;
    #endif

    const QPlane REFERENCE_OPERAND = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);                       // _
    const QVector3 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, SQFloat::_1, SQFloat::_0);  // \_
    const QVector3 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, -SQFloat::_1, SQFloat::_0); // /¨

	// [Execution]
    float_q fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SQFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that the operation returns a different angle when the plane is not normalized.
/// </summary>
QTEST_CASE ( AngleBetween1_ReturnsDifferentAngleWhenPlaneIsNotNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QPlane NOT_NORMALIZED_PLANE = QPlane(SQFloat::_0_5, SQFloat::_0_5, SQFloat::_0, SQFloat::_0);
    const QPlane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();
    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_0);

	// [Execution]
    float_q fResultWhenNormalized = NORMALIZED_PLANE.AngleBetween(VECTOR);
    float_q fResultWhenNotNormalized = NOT_NORMALIZED_PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SQFloat::AreNotEqual(fResultWhenNormalized, fResultWhenNotNormalized) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the plane or the vector is null.
/// </summary>
QTEST_CASE ( AngleBetween1_AssertionFailsWhenPlaneOrVectorIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    // [Preparation]
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QPlane NONNULL_PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 NULL_VECTOR = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 NONNULL_VECTOR = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        NULL_PLANE.AngleBetween(NONNULL_VECTOR);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NONNULL_PLANE.AngleBetween(NULL_VECTOR);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Add a test to check the returned value when assertions are disabled

/// <summary>
/// Checks that the returned angle result for a common vector and a plane equals the expected value.
/// </summary>
QTEST_CASE ( AngleBetween2_ReturnsAngleBetweenCommonVectorAndPlane_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        float_q EXPECTED_RESULT = SQAngle::_45;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
    #endif

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector4 VECTOR = QVector4(SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the angle equals zero when the normal of the plane and the vector are parallel.
/// </summary>
QTEST_CASE ( AngleBetween2_AngleEqualsZeroWhenVectorAndPlaneNormalAreParallel_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector4 VECTOR = QVector4(SQFloat::_9, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when the normal of the plane and the vector are orthogonal.
/// </summary>
QTEST_CASE ( AngleBetween2_AngleEqualsHalfPiRadiansOr90DegreesWhenVectorAndPlaneNormalAreOrthogonal_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_90;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_HalfPi;
    #endif

    const QPlane PLANE = QPlane(SQFloat::_5, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector4 VECTOR = QVector4(SQFloat::_0, SQFloat::_5, SQFloat::_0, SQFloat::_1);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when vector and the normal of the plane are opposite.
/// </summary>
QTEST_CASE ( AngleBetween2_AngleEqualsPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreOpposite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_180;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_Pi;
    #endif

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector4 VECTOR = QVector4(-SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1);

	// [Execution]
    float_q fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
QTEST_CASE ( AngleBetween2_AngleIsAlwaysPositive_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QPlane REFERENCE_OPERAND = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);                                    // _
    const QVector4 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QVector4(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1);  // \_
    const QVector4 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QVector4(-SQFloat::_1, -SQFloat::_1, SQFloat::_0, SQFloat::_1); // /¨

	// [Execution]
    float_q fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SQFloat::IsGreaterOrEquals(fResult1UT, SQFloat::_0) );
    BOOST_CHECK( SQFloat::IsGreaterOrEquals(fResult2UT, SQFloat::_0) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when vector and the normal of the plane are not opposite.
/// </summary>
QTEST_CASE ( AngleBetween2_AngleIsLowerThanPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreNotOpposite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_180;
    #else
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_Pi;
    #endif

    const QPlane REFERENCE_OPERAND = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);                                    // _
    const QVector4 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QVector4(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1);  // \_
    const QVector4 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QVector4(-SQFloat::_1, -SQFloat::_1, SQFloat::_0, SQFloat::_1); // /¨

	// [Execution]
    float_q fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SQFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that the operation returns a different angle when the plane is not normalized.
/// </summary>
QTEST_CASE ( AngleBetween2_ReturnsDifferentAngleWhenPlaneIsNotNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QPlane NOT_NORMALIZED_PLANE = QPlane(SQFloat::_0_5, SQFloat::_0_5, SQFloat::_0, SQFloat::_0);
    const QPlane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();
    const QVector4 VECTOR = QVector4(SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1);

	// [Execution]
    float_q fResultWhenNormalized = NORMALIZED_PLANE.AngleBetween(VECTOR);
    float_q fResultWhenNotNormalized = NOT_NORMALIZED_PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SQFloat::AreNotEqual(fResultWhenNormalized, fResultWhenNotNormalized) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the plane or the vector is null.
/// </summary>
QTEST_CASE ( AngleBetween2_AssertionFailsWhenPlaneOrVectorIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QPlane NONNULL_PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector4 NULL_VECTOR = QVector4(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector4 NONNULL_VECTOR = QVector4(SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        NULL_PLANE.AngleBetween(NONNULL_VECTOR);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NONNULL_PLANE.AngleBetween(NULL_VECTOR);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Add a test to check the returned value when assertions are disabled

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
QTEST_CASE ( AngleBetween2_VectorsWComponentDoesntTakePartInTheOperation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    // [Preparation]
    const QVector4 VECTOR1 = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QVector4 VECTOR2 = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResult1UT = PLANE.AngleBetween(VECTOR1);
    float_q fResult2UT = PLANE.AngleBetween(VECTOR2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the returned angle result for 2 common planes equals the expected value.
/// </summary>
QTEST_CASE ( AngleBetween3_ReturnsAngleBetween2CommonPlanes_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        float_q EXPECTED_RESULT = SQAngle::_45;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
    #endif

    QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0);
    OPERAND1 = OPERAND1.Normalize();
    const QPlane OPERAND2 = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
QTEST_CASE ( AngleBetween3_DComponentDoesNotTakePartInTheOperation_Test )
{
    // [Preparation]
    QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    QPlane OPERAND2 = QPlane(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_7);
    QPlane OPERAND3 = QPlane(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_10);
    OPERAND1 = OPERAND1.Normalize();
    OPERAND2 = OPERAND2.Normalize();
    OPERAND3 = OPERAND3.Normalize();

	// [Execution]
    float_q fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_q fResult2UT = OPERAND1.AngleBetween(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
QTEST_CASE ( AngleBetween_AngleBetweenIsCommutative_Test )
{
    // [Preparation]
    QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    QPlane OPERAND2 = QPlane(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);
    OPERAND1 = OPERAND1.Normalize();
    OPERAND2 = OPERAND2.Normalize();

	// [Execution]
    float_q fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_q fResult2UT = OPERAND2.AngleBetween(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the angle equals zero when planes are parallel.
/// </summary>
QTEST_CASE ( AngleBetween3_AngleEqualsZeroWhenPlanesAreParallel_Test )
{
    // [Preparation]
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QPlane OPERAND2 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_2);

	// [Execution]
    float_q fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when planes are orthogonal.
/// </summary>
QTEST_CASE ( AngleBetween3_AngleEqualsHalfPiRadiansOr90DegreesWhenPlanesAreOrthogonal_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_90;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_HalfPi;
    #endif

    const QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QPlane OPERAND2 = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QPlane OPERAND3 = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_1, SQFloat::_0);

	// [Execution]
    float_q fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_q fResult2UT = OPERAND2.AngleBetween(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when plane normals are opposite.
/// </summary>
QTEST_CASE ( AngleBetween3_AngleEqualsPiRadiansOr180DegreesWhenPlaneNormalsAreOpposite_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_180;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_Pi;
    #endif

    const QPlane OPERAND1 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QPlane OPERAND2 = QPlane(-SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
QTEST_CASE ( AngleBetween3_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
    const QPlane REFERENCE_OPERAND = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);                                // _
    const QPlane OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0);  // \_
    const QPlane OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QPlane(-SQFloat::_1, -SQFloat::_1, SQFloat::_0, SQFloat::_0); // /¨

	// [Execution]
    float_q fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SQFloat::IsGreaterOrEquals(fResult1UT, SQFloat::_0) );
    BOOST_CHECK( SQFloat::IsGreaterOrEquals(fResult2UT, SQFloat::_0) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when plane normals are not opposite.
/// </summary>
QTEST_CASE ( AngleBetween3_AngleIsLowerThanPiRadiansOr180DegreesWhenPlaneNormalsAreNotOpposite_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_180;
    #else
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_Pi;
    #endif

    const QPlane REFERENCE_OPERAND = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);                          // _
    QPlane OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0);  // \_
    QPlane OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QPlane(-SQFloat::_1, -SQFloat::_1, SQFloat::_0, SQFloat::_0); // /¨
    OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE.Normalize();
    OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE.Normalize();

	// [Execution]
    float_q fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SQFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that the operation returns a different angle when the plane is not normalized.
/// </summary>
QTEST_CASE ( AngleBetween3_ReturnsDifferentAngleWhenPlaneIsNotNormalized_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QPlane NOT_NORMALIZED_PLANE = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QPlane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// [Execution]
    float_q fResultWhenNormalized = NORMALIZED_PLANE.AngleBetween(PLANE);
    float_q fResultWhenNotNormalized = NOT_NORMALIZED_PLANE.AngleBetween(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreNotEqual(fResultWhenNormalized, fResultWhenNotNormalized) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when one of the planes is null.
/// </summary>
QTEST_CASE ( AngleBetween3_AssertionFailsWhenOnePlaneIsNull_Test )
{
    // [Preparation]
    const QPlane NOT_NULL_PLANE = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        NOT_NULL_PLANE.AngleBetween(NULL_PLANE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NULL_PLANE.AngleBetween(NOT_NULL_PLANE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Add a test to check the returned value when assertions are disabled

/// <summary>
/// Checks that a common point is correctly projected on a common plane.
/// </summary>
QTEST_CASE_TEMPLATE ( PointProjection_ACommonPointIsProjectedOnACommonPlaneCorrectly_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {SQFloat::_0, SQFloat::_2, SQFloat::_0, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0);
    PLANE = PLANE.Normalize();
    const float_q EXPECTED_POINT_COMPONENTS[] = {SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1};
    T EXPECTED_POINT = T(EXPECTED_POINT_COMPONENTS);

	// [Execution]
    T vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPoint == EXPECTED_POINT );
}

/// <summary>
/// Checks that a point that belongs to the plane remains the same.
/// </summary>
QTEST_CASE_TEMPLATE ( PointProjection_PointsThatBelongToPlaneRemainsTheSame_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();
    const float_q POINT_COMPONENTS[] = {PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    T EXPECTED_POINT = POINT;

	// [Execution]
    T vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPoint == EXPECTED_POINT );
}

/// <summary>
/// Checks that a common point that is placed in the "negative" side of the space divided by the plane is correctly projected.
/// </summary>
QTEST_CASE_TEMPLATE ( PointProjection_PointsBehindThePlaneAreCorrectlyProjected_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {SQFloat::_0, -SQFloat::_2, SQFloat::_0, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();
    const float_q EXPECTED_POINT_COMPONENTS[] = {-SQFloat::_1, -SQFloat::_1, SQFloat::_0, SQFloat::_1};
    T EXPECTED_POINT = T(EXPECTED_POINT_COMPONENTS);

	// [Execution]
    T vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPoint == EXPECTED_POINT );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( PointProjection_AssertionFailsWhenPlaneIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane NULL_PLANE = QPlane::GetNullPlane();
    const T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.PointProjection(POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the result is different when the plane is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( PointProjection_ResultIsDifferentWhenPlaneIsNotNormalized_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QPlane NORMALIZED_PLANE = PLANE.Normalize();

	// [Execution]
    T vProjectedPointOnNonNormalizedPlane = PLANE.PointProjection(POINT);
    T vProjectedPointOnNormalizedPlane = NORMALIZED_PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPointOnNonNormalizedPlane != vProjectedPointOnNormalizedPlane );
}

/// <summary>
/// Checks that the W component of the point is not affected by the operation.
/// </summary>
QTEST_CASE ( PointProjection_ItDoesNotAffectWComponent_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    // [Preparation]
    const QBaseVector4 POINT = QBaseVector4(SQFloat::_4, -SQFloat::_8, SQFloat::_3, SQFloat::_9);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();

	// [Execution]
    QBaseVector4 vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(vProjectedPoint.w, POINT.w);
}

/// <summary>
/// Checks that it returns True when a common point that belongs to the plane is used.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenUsingACommonPointThatBelongsToThePlane_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bResult = PLANE.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult, EXPECTED_VALUE );
}

/// <summary>
/// Checks that it returns False when a point that is in the "positive" side of the plane is used.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenUsingACommonPointThatIsInThePositiveSideOfThePlane_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bResult = PLANE.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult, EXPECTED_VALUE );
}

/// <summary>
/// Checks that it returns False when a point that is in the "negative" side of the plane is used.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenUsingACommonPointThatIsInTheNegativeSideOfThePlane_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bResult = PLANE.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult, EXPECTED_VALUE );
}

/// <summary>
/// Checks that it returns the same result either the plane is normalized or not .
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_PlaneNormalizationDoesNotAffectResult_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q CONTAINED_POINT_COMPONENTS[] = {(float_q)2.1250, (float_q)0.8750, SQFloat::_3, SQFloat::_1};
    const float_q NOT_CONTAINED_POINT_COMPONENTS[] = {SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1};
    const T CONTAINED_POINT = T(CONTAINED_POINT_COMPONENTS);
    const T NOT_CONTAINED_POINT = T(NOT_CONTAINED_POINT_COMPONENTS);
    const QPlane NOT_NORMALIZED_PLANE = QPlane(-SQFloat::_8, SQFloat::_8, SQFloat::_0, SQFloat::_10);
    const QPlane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    bool bResultNotContainedNorNormalized = NOT_NORMALIZED_PLANE.Contains(NOT_CONTAINED_POINT);
    bool bResultNotContainedButNormalized = NORMALIZED_PLANE.Contains(NOT_CONTAINED_POINT);
    bool bResultContainedButNotNormalized = NOT_NORMALIZED_PLANE.Contains(CONTAINED_POINT);
    bool bResultContainedAndNormalized = NORMALIZED_PLANE.Contains(CONTAINED_POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResultNotContainedNorNormalized, bResultNotContainedButNormalized );
    BOOST_CHECK_EQUAL( bResultContainedButNotNormalized, bResultContainedAndNormalized );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_AssertionFailsWhenPlaneIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane NULL_PLANE = QPlane::GetNullPlane();
    const T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.PointProjection(POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the W component of the point doesn't affect the result.
/// </summary>
QTEST_CASE ( Contains_WComponentDoesNotAffectTheResult_Test )
{
    // [Preparation]
    const QVector4 POINT1 = QVector4(SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1);
    const QVector4 POINT2 = QVector4(SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_10);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();

    // [Execution]
    bool bResult1 = PLANE.Contains(POINT1);
    bool bResult2 = PLANE.Contains(POINT2);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult1, bResult2 );
}

/// <summary>
/// Checks that the length of a non-normalized plane is correctly calculated.
/// </summary>
QTEST_CASE ( GetLength_ReturnsCorrectLengthFromNonNormalizedPlane_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const float_q EXPECTED_LENGTH = sqrt_q((float_q)14.0);

	// [Execution]
    float_q fLength = PLANE.GetLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals 1 when the plane is normalized.
/// </summary>
QTEST_CASE ( GetLength_ReturnsOneWhenPlaneIsNormalized_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1).Normalize();
    const float_q EXPECTED_LENGTH = SQFloat::_1;

	// [Execution]
    float_q fLength = PLANE.GetLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals zero when the plane is null.
/// </summary>
QTEST_CASE ( GetLength_ReturnsZeroWhenPlaneIsNull_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane::GetNullPlane();
    const float_q EXPECTED_LENGTH = SQFloat::_0;

	// [Execution]
    float_q fLength = PLANE.GetLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the D component of the plane doesn't affect the result.
/// </summary>
QTEST_CASE ( GetLength_DComponentDoesNotAffectResult_Test )
{
    // [Preparation]
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_5);

	// [Execution]
    float_q fLength1 = PLANE1.GetLength();
    float_q fLength2 = PLANE2.GetLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the length of a non-normalized plane is correctly calculated.
/// </summary>
QTEST_CASE ( GetSquaredLength_ReturnsCorrectLengthFromNonNormalizedPlane_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const float_q EXPECTED_LENGTH = (float_q)14.0;

	// [Execution]
    float_q fLength = PLANE.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals 1 when the plane is normalized.
/// </summary>
QTEST_CASE ( GetSquaredLength_ReturnsOneWhenPlaneIsNormalized_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1).Normalize();
    const float_q EXPECTED_LENGTH = SQFloat::_1;

	// [Execution]
    float_q fLength = PLANE.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals zero when the plane is null.
/// </summary>
QTEST_CASE ( GetSquaredLength_ReturnsZeroWhenPlaneIsNull_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane::GetNullPlane();
    const float_q EXPECTED_LENGTH = SQFloat::_0;

	// [Execution]
    float_q fLength = PLANE.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the D component of the plane doesn't affect the result.
/// </summary>
QTEST_CASE ( GetSquaredLength_DComponentDoesNotAffectResult_Test )
{
    // [Preparation]
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_5);

	// [Execution]
    float_q fLength1 = PLANE1.GetSquaredLength();
    float_q fLength2 = PLANE2.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the normal is correctly calculated for a common plane.
/// </summary>
QTEST_CASE ( GetNormal_NormalIsCorrectlyComputedWhenUsingCommonPlane_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QVector3 EXPECTED_NORMAL(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QVector3 vNormal = PLANE.GetNormal();

    // [Verification]
    BOOST_CHECK( vNormal == EXPECTED_NORMAL );
}

/// <summary>
/// Checks that the normal is not normalized when the plane is not normalized.
/// </summary>
QTEST_CASE ( GetNormal_ItIsNotNormalizedWhenPlaneIsNotNormalized_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

	// [Execution]
    QVector3 vNormal = PLANE.GetNormal();
    QVector3 vNormalizedNormal = vNormal.Normalize();

    // [Verification]
    BOOST_CHECK( vNormal != vNormalizedNormal );
}

/// <summary>
/// Checks that the normal is normalized when the plane is normalized.
/// </summary>
QTEST_CASE ( GetNormal_ItIsNormalizedWhenPlaneIsNormalized_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();

	// [Execution]
    QVector3 vNormal = PLANE.GetNormal();
    QVector3 vNormalizedNormal = vNormal.Normalize();

    // [Verification]
    BOOST_CHECK( vNormal == vNormalizedNormal );
}

/// <summary>
/// Checks that it's correctly calculated when a common point and a common plane are used.
/// </summary>
QTEST_CASE_TEMPLATE ( PointDistance_CorrectlyCalculatedWhenUsingCommonPointAndPlane_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q EXPECTED_DISTANCE = SQFloat::_3;
    const float_q POINT_COMPONENTS[] = {-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0};
    T POINT = T(POINT_COMPONENTS);
    POINT = POINT.Normalize() * EXPECTED_DISTANCE;
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();

	// [Execution]
    float_q fDistance = PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fDistance, EXPECTED_DISTANCE) );
}

/// <summary>
/// Checks that the distance is always positive, even when the point is in the "negative" side of the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( PointDistance_DistanceIsPositiveWhenPointIsInTheNegativeSideOfPlane_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q EXPECTED_DISTANCE = SQFloat::_3;
    const float_q POINT_COMPONENTS[] = {SQFloat::_1, -SQFloat::_1, SQFloat::_0, SQFloat::_0};
    T POINT = T(POINT_COMPONENTS);
    POINT = POINT.Normalize() * EXPECTED_DISTANCE;
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();

	// [Execution]
    float_q fDistance = PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fDistance, EXPECTED_DISTANCE) );
}

/// <summary>
/// Checks that it returns zero when the point belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( PointDistance_ReturnsZeroWhenPointBelongsToThePlane_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q EXPECTED_DISTANCE = SQFloat::_0;
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();
    const float_q POINT_COMPONENTS[] = {PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);

	// [Execution]
    float_q fDistance = PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fDistance, EXPECTED_DISTANCE) );
}

/// <summary>
/// Checks that the result is the same when the plane is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( PointDistance_ResultIsTheSameWhenPlaneIsNotNormalized_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane NOT_NORMALIZED_PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QPlane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    float_q fDistance1 = NOT_NORMALIZED_PLANE.PointDistance(POINT);
    float_q fDistance2 = NORMALIZED_PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fDistance1, fDistance2) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( PointDistance_AssertionFailsWhenPlaneIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane NULL_PLANE = QPlane::GetNullPlane();
    const T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.PointDistance(POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the W component of the point doesn't affect the result.
/// </summary>
QTEST_CASE ( PointDistance_WComponentDoesNotAffectTheResult_Test )
{
    // [Preparation]
    const float_q POINT_COMPONENTS1[] = {SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1};
    const float_q POINT_COMPONENTS2[] = {SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_10};
    const QVector4 POINT1 = QVector4(POINT_COMPONENTS1);
    const QVector4 POINT2 = QVector4(POINT_COMPONENTS2);
    const QPlane PLANE = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();

	// [Execution]
    float_q fResult1 = PLANE.PointDistance(POINT1);
    float_q fResult2 = PLANE.PointDistance(POINT2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1, fResult2 );
}

/// <summary>
/// Checks that the output point is not changed when the 3 planes coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenThreePlanesCoincide_Test, TQVectorTypes )
{
    //
    //       |
    //       |
    //       |--->
    //       |
    //       | x3
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = PLANE1;
    const QPlane PLANE3 = PLANE1;

	// [Execution]
    T vIntersection = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);

    // [Verification]
    BOOST_CHECK( vIntersection == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 3 planes coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsInfiniteWhenThreePlanesCoincide_Test, TQVectorTypes )
{
    //
    //       |
    //       |
    //       |--->
    //       |
    //       | x3
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = PLANE1;
    const QPlane PLANE3 = PLANE1;

	// [Execution]
    T vIntersection;
    EQIntersections eResult = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when 2 planes coincide and the other intersects.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTwoPlanesCoincideAndTheOtherIntersects_Test, TQVectorTypes )
{
    //
    //       |         /
    //       |        /
    //       |--->   /
    //       |      /
    //       | x2  /
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = PLANE1;
    const QPlane PLANE3 = QPlane(SQFloat::_3, SQFloat::_2, SQFloat::_1, SQFloat::_4).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 2 planes coincide and the other intersects.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsInfiniteWhenTwoPlanesCoincideAndTheOtherIntersects_Test, TQVectorTypes )
{
    //
    //       |         /
    //       |        /
    //       |--->   /
    //       |      /
    //       | x2  /
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = PLANE1;
    const QPlane PLANE3 = QPlane(SQFloat::_3, SQFloat::_2, SQFloat::_1, SQFloat::_4).Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EQIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EQIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EQIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EQIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EQIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when 2 planes coincide and the other is parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTwoPlanesCoincideAndTheOtherIsParallel_Test, TQVectorTypes )
{
    //
    //       |        |
    //       |        |
    //       |--->    |--->
    //       |        |
    //       | x2     |
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = PLANE1;
    const QPlane PLANE3 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_5).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 2 planes coincide and the other is parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneWhenTwoPlanesCoincideAndTheOtherIsParallel_Test, TQVectorTypes )
{
    //
    //       |        |
    //       |        |
    //       |--->    |--->
    //       |        |
    //       | x2     |
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = PLANE1;
    const QPlane PLANE3 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_5).Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EQIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EQIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EQIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EQIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EQIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when 2 planes coincide and the other is parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTheThreePlanesAreParallel_Test, TQVectorTypes )
{
    //
    //       |        |       |
    //       |        |       |
    //       |--->    |--->   |--->
    //       |        |       |
    //       |        |       |
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_5).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_6).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 2 planes coincide and the other is parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneTheThreePlanesAreParallel_Test, TQVectorTypes )
{
    //
    //       |        |       |
    //       |        |       |
    //       |--->    |--->   |--->
    //       |        |       |
    //       |        |       |
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_5).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_6).Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EQIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EQIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EQIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EQIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EQIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when the three planes intersect but don't share one single point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTheThreePlanesIntersectButNotShareASinglePoint_Test, TQVectorTypes )
{
    //
    //          /\
    //         /  \
    //        /    \
    //      _/______\_
    //      /        \
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const QPlane PLANE1 = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the three planes intersect but don't share one single point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneWhenTheThreePlanesIntersectButNotShareASinglePoint_Test, TQVectorTypes )
{
    //
    //          /\
    //         /  \
    //        /    \
    //      _/______\_
    //      /        \
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QPlane PLANE1 = QPlane(-SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_0).Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EQIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EQIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EQIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EQIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EQIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when two of the planes are parallel and intersect with the third one.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTwoPlanesAreParallelAndIntersectTheOther_Test, TQVectorTypes )
{
    //
    //       |        |
    //       |-->     |-->
    //       |    ^   |
    //      _|____|___|____
    //       |        |
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_2).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_3).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when two of the planes are parallel and intersect with the third one.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneWhenTwoPlanesAreParallelAndIntersectTheOther_Test, TQVectorTypes )
{
    //
    //       |        |
    //       |-->     |-->
    //       |    ^   |
    //      _|____|___|____
    //       |        |
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_2).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_3).Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EQIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EQIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EQIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EQIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EQIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is correctly calculated when the 3 planes coincide in one point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointIsCorrectlyCalculatedWhenTheThreePlanesShareOnePoint_Test, TQVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //
    const float_q POINT_COMPONENTS[] = {SQFloat::_2, -SQFloat::_4, SQFloat::_3, SQFloat::_0};
    const T EXPECTED_POINT = T(POINT_COMPONENTS);
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, -SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_3).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_5, -SQFloat::_9).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns One when the 3 planes coincide in one point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsOneWhenTheThreePlanesShareOnePoint_Test, TQVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, -SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_3).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_5, -SQFloat::_9).Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EQIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EQIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EQIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EQIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EQIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when the 3 planes share one line.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTheThreePlanesShareOneLine_Test, TQVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x L
    //      /|\
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const QPlane PLANE1 = QPlane(SQFloat::_1, -SQFloat::_1, SQFloat::_4, -SQFloat::_5).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_3, SQFloat::_1, SQFloat::_1, -SQFloat::_3).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_5, -SQFloat::_1, SQFloat::_9, (float_q)-13.0).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 3 planes share one line.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsInfiniteWhenTheThreePlanesShareOneLine_Test, TQVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x L
    //      /|\
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const QPlane PLANE1 = QPlane(SQFloat::_1, -SQFloat::_1, SQFloat::_4, -SQFloat::_5).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_3, SQFloat::_1, SQFloat::_1, -SQFloat::_3).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_5, -SQFloat::_1, SQFloat::_9, (float_q)-13.0).Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EQIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EQIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EQIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EQIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EQIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is the same even when at least one of the planes is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointIsTheSameWhenPlanesAreNotNormalized_Test, TQVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    // [Preparation]
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, -SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_3).Normalize();
    const QPlane NOT_NORMALIZED_PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_5, -SQFloat::_9);
    const QPlane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    T vIntersectionNormalizedPlane;
    T vIntersectionNotNormalizedPlane;

    PLANE1.IntersectionPoint(PLANE2, NORMALIZED_PLANE, vIntersectionNormalizedPlane);
    PLANE1.IntersectionPoint(PLANE2, NOT_NORMALIZED_PLANE, vIntersectionNotNormalizedPlane);

    // [Verification]
    BOOST_CHECK( vIntersectionNormalizedPlane == vIntersectionNotNormalizedPlane );
}

/// <summary>
/// Checks that the returned value is the same even when at least one of the planes is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnedValueIsTheSameWhenPlanesAreNotNormalized_Test, TQVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, -SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_3).Normalize();
    const QPlane NOT_NORMALIZED_PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_5, -SQFloat::_9);
    const QPlane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    T vIntersection;
    EQIntersections eResultNormalizedPlane = PLANE1.IntersectionPoint(PLANE2, NOT_NORMALIZED_PLANE, vIntersection);
    EQIntersections eResultNotNormalizedPlane = PLANE1.IntersectionPoint(PLANE2, NORMALIZED_PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResultNormalizedPlane == eResultNotNormalizedPlane);
}

/// <summary>
/// Checks that the W component of the output point doesn't ever change.
/// </summary>
QTEST_CASE ( IntersectionPoint_WComponentOfOutputPointIsNeverChanged_Test )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    // [Preparation]
    const float_q EXPECTED_W = SQFloat::_5;
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, -SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_3).Normalize();
    const QPlane PLANE3 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_5, -SQFloat::_9).Normalize();
    QVector4 vIntersection;
    vIntersection.w = EXPECTED_W;

	// [Execution]
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(vIntersection.w, EXPECTED_W);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when one of the planes is null.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint_AssertionFailsWhenOnePlaneIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane PLANE1 = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, -SQFloat::_1).Normalize();
    const QPlane PLANE2 = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_3).Normalize();
    const QPlane NULL_PLANE = QPlane::GetNullPlane();
    T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        PLANE1.IntersectionPoint(PLANE2, NULL_PLANE, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        PLANE1.IntersectionPoint(NULL_PLANE, PLANE2, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    bool bAssertionFailed3 = false;

    try
    {
        NULL_PLANE.IntersectionPoint(PLANE2, PLANE1, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed3 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed3, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns "positive side" when the other plane is parallel and resides in the positive side of the space division defined by the resident plane.
/// </summary>
QTEST_CASE( SpaceRelation_ReturnsPositiveSideWhenTheOtherPlaneIsParallelAndIsInThePositiveSide_Test )
{
    //     A        B
    //     |        |
    //     |-->     |-->
    //     |        |
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE_A = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1).Normalize();
    const QPlane PLANE_B = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_2).Normalize();
    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// [Execution]
    EQSpaceRelation eResult = PLANE_A.SpaceRelation(PLANE_B);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the other plane is parallel and resides in the negative side of the space division defined by the resident plane.
/// </summary>
QTEST_CASE( SpaceRelation_ReturnsNegativeSideWhenTheOtherPlaneIsParallelAndIsInTheNegativeSide_Test )
{
    //     B        A
    //     |        |
    //     |-->     |-->
    //     |        |
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE_A = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_3).Normalize();
    const QPlane PLANE_B = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_2).Normalize();
    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// [Execution]
    EQSpaceRelation eResult = PLANE_A.SpaceRelation(PLANE_B);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when planes intersect.
/// </summary>
QTEST_CASE( SpaceRelation_ReturnsBothSidesWhenPlanesIntersect_Test )
{
    //     A B
    //     |/
    //     |-->
    //    /|
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE_A = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_3).Normalize();
    const QPlane PLANE_B = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_BothSides;

	// [Execution]
    EQSpaceRelation eResult1 = PLANE_A.SpaceRelation(PLANE_B);
    EQSpaceRelation eResult2 = PLANE_B.SpaceRelation(PLANE_A);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when planes coincide.
/// </summary>
QTEST_CASE( SpaceRelation_ReturnsContainedWhenPlanesCoincide_Test )
{
    //    A&B
    //     |
    //     |-->>
    //     |
    //

    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE_A = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE_B = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_Contained;

	// [Execution]
    EQSpaceRelation eResult = PLANE_A.SpaceRelation(PLANE_B);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is different when one of the planes is not normalized.
/// </summary>
QTEST_CASE( SpaceRelation_ResultIsDifferentWhenOnePlaneIsNotNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE_NORMALIZED = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QPlane PLANE_NOTNORMALIZED = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

	// [Execution]
    EQSpaceRelation eResult1 = PLANE_NORMALIZED.SpaceRelation(PLANE_NORMALIZED);
    EQSpaceRelation eResult2 = PLANE_NORMALIZED.SpaceRelation(PLANE_NOTNORMALIZED);

    // [Verification]
    BOOST_CHECK(eResult1 != eResult2);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when one of the planes is null.
/// </summary>
QTEST_CASE( SpaceRelation_AssertionFailsWhenOnePlaneIsNull_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_1, SQFloat::_1, -SQFloat::_1).Normalize();
    const QPlane NULL_PLANE = QPlane::GetNullPlane();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        PLANE.SpaceRelation(NULL_PLANE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NULL_PLANE.SpaceRelation(PLANE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE ( Rotate1_PlaneIsCorrectlyTransformedByCommonRotationMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const QPlane EXPECTED_RESULT = QPlane( (float_q) 0.15430334996209197,
                                           (float_q)-0.87287156094396956,
                                           (float_q)-0.46291004988627582,
                                           PLANE.d );

    // Results calculated with DirectX SDK
    // float_q fYaw = SQAngle::_Pi;
    // float_q fPitch = SQAngle::_HalfPi;
    // float_q fRoll = SQAngle::_QuarterPi;
    // D3DXMATRIX rot;
    // D3DXMatrixRotationYawPitchRoll(&rot, fYaw, fPitch, fRoll);
    // D3DXVECTOR3 vRot(1, 2, 4);
    // D3DXVec3Normalize(&vRot, &vRot);
    // D3DXVec3TransformNormal(&vRot, &vRot, &rot);

	// [Execution]
    QPlane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Rotate1_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the rotation matrix is null.
/// </summary>
QTEST_CASE ( Rotate1_PlaneIsNullWhenRotationMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QRotationMatrix3x3 NULL_MATRIX = QRotationMatrix3x3(QMatrix3x3::GetNullMatrix());

    const QPlane EXPECTED_RESULT = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, PLANE.d);

	// [Execution]
    QPlane planeUT = PLANE.Rotate(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE ( Rotate2_PlaneIsCorrectlyTransformedByCommonQuaternion_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QQuaternion TRANSFORMATION = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const QPlane EXPECTED_RESULT = QPlane( (float_q)-0.77151674981045959,
                                           (float_q)-0.46291004988627560,
                                           (float_q)-0.43643578047198500,
                                           PLANE.d );

    // Results have been obtained by using DirectX SDK
    // D3DXQUATERNION qRot, qVector, qConjugate;
    // float_q fYaw = SQAngle::_Pi;
    // float_q fPitch = SQAngle::_HalfPi;
    // float_q fRoll = SQAngle::_QuarterPi;
    // D3DXQuaternionRotationYawPitchRoll(&qRot, fYaw, fPitch, fRoll);
    // D3DXQuaternionNormalize(&qRot, &qRot);
    // D3DXQuaternionConjugate(&qConjugate, &qRot);
    // D3DXVECTOR3 vVector(1, 2, 4);
    // D3DXVec3Normalize(&vVector, &vVector);
    // qVector.x = vVector.x; qVector.y = vVector.y; qVector.z = vVector.z; qVector.w = 0;
    // D3DXQuaternionMultiply(&qVector, &qRot, &qVector);
    // D3DXQuaternionMultiply(&qVector, &qVector, &qConjugate);

	// [Execution]
    QPlane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity quaternion.
/// </summary>
QTEST_CASE ( Rotate2_PlaneDoesNotChangeWhenTransformedByIdentityQuaternion_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion TRANSFORMATION = QQuaternion::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the quaternion is null.
/// </summary>
QTEST_CASE ( Rotate2_PlaneIsNullWhenQuaternionIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QPlane EXPECTED_RESULT = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, PLANE.d);

	// [Execution]
    QPlane planeUT = PLANE.Rotate(NULL_QUATERNION);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary scale matrix.
/// </summary>
QTEST_CASE ( Scale1_PlaneIsCorrectlyScaledByCommonScaleMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = QPlane((float_q)0.70224688317678341, (float_q)0.11704114719613057, (float_q)-0.70224688317678341, (float_q)0.87780860397097937);

	// [Execution]
    QPlane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Scale1_PlaneDoesNotChangeWhenScaledByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE.Normalize();

	// [Execution]
    QPlane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE ( Scale1_AssertionFailsWhenPlaneIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // [Preparation]
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3::GetIdentity();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.Scale(TRANSFORMATION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the scale matrix is null.
/// </summary>
QTEST_CASE ( Scale1_AssertionFailsWhenScaleMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QScalingMatrix3x3 NULL_MATRIX = QScalingMatrix3x3(QMatrix3x3::GetNullMatrix());

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Scale(NULL_MATRIX);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary vector.
/// </summary>
QTEST_CASE ( Scale2_PlaneIsCorrectlyScaledByCommonVector_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QVector3 TRANSFORMATION = QVector3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = QPlane((float_q)0.70224688317678341, (float_q)0.11704114719613057, (float_q)-0.70224688317678341, (float_q)0.87780860397097937);

	// [Execution]
    QPlane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by a vector of ones.
/// </summary>
QTEST_CASE ( Scale2_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QVector3 TRANSFORMATION = QVector3::GetVectorOfOnes();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE ( Scale2_AssertionFailsWhenPlaneIsNull_Test )
{
    // [Preparation]
    const QPlane NULL_PLANE = QPlane::GetNullPlane();
    const QVector3 TRANSFORMATION = QVector3::GetVectorOfOnes();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.Scale(TRANSFORMATION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
QTEST_CASE ( Scale2_AssertionFailsWhenVectorIsNull_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QVector3 NULL_VECTOR = QVector3::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Scale(NULL_VECTOR);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by arbitrary scaling values.
/// </summary>
QTEST_CASE ( Scale3_PlaneIsCorrectlyScaledByCommonScalingValues_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const float_q SCALE_X = SQFloat::_0_25;
    const float_q SCALE_Y = SQFloat::_3;
    const float_q SCALE_Z = -SQFloat::_1;

    const QPlane EXPECTED_RESULT = QPlane((float_q)0.70224688317678341, (float_q)0.11704114719613057, (float_q)-0.70224688317678341, (float_q)0.87780860397097937);

	// [Execution]
    QPlane planeUT = PLANE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when scale values equal one.
/// </summary>
QTEST_CASE ( Scale3_PlaneDoesntChangeWhenScaleValuesEqualOne_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE ( Scale3_AssertionFailsWhenPlaneIsNull_Test )
{
    // [Preparation]
    const QPlane NULL_PLANE = QPlane::GetNullPlane();
    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.Scale(SCALE_X, SCALE_Y, SCALE_Z);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
QTEST_CASE ( Scale3_AssertionFailsWhenVectorIsNull_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const float_q ZERO_SCALE_X = SQFloat::_0;
    const float_q ZERO_SCALE_Y = SQFloat::_0;
    const float_q ZERO_SCALE_Z = SQFloat::_0;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Scale(ZERO_SCALE_X, ZERO_SCALE_Y, ZERO_SCALE_Z);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary translation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_PlaneIsCorrectlyTranslatedByCommonTranslationMatrix_Test, TQMatrixTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTranslationMatrix<T> TRANSFORMATION = QTranslationMatrix<T>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);

    const QPlane EXPECTED_RESULT = QPlane((float_q)0.21821789023599239, (float_q)0.43643578047198478, (float_q)0.87287156094396956, (float_q)4.1461399144838555);

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_VectorDoesNotChangeWhenTranslatedByIdentityMatrix_Test, TQMatrixTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTranslationMatrix<T> TRANSFORMATION = QTranslationMatrix<T>::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when the translation matrix is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_PlaneDoesNotChangeWhenTranslationMatrixIsNull_Test, TQMatrixTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTranslationMatrix<T> NULL_MATRIX = QTranslationMatrix<T>(T::GetNullMatrix());

    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Translate(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane does not change when the displacement vector produced by the matrix is orthogonal to the plane's normal.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_PlaneDoesNotChangeWhenDisplacementVectorIsOrthogonalToPlaneNormal_Test, TQMatrixTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_5).Normalize();
    const QTranslationMatrix<T> TRANSFORMATION = QTranslationMatrix<T>(-SQFloat::_2, SQFloat::_1, SQFloat::_0);

    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary translation vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_PlaneIsCorrectlyTranslatedByCommonTranslationVector_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const float_q VECTOR_COMPONENTS[] = {SQFloat::_2, SQFloat::_4, -SQFloat::_6, SQFloat::_0};
    const T TRANSFORMATION = T(VECTOR_COMPONENTS);

    const QPlane EXPECTED_RESULT = QPlane((float_q)0.21821789023599239, (float_q)0.43643578047198478, (float_q)0.87287156094396956, (float_q)4.1461399144838555);

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when the translation vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_PlaneDoesNotChangeWhenTranslationVectorIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const T NULL_VECTOR = T::GetNullVector();

    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Translate(NULL_VECTOR);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane does not change when the displacement vector is orthogonal to the plane's normal.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_PlaneDoesNotChangeWhenDisplacementVectorIsOrthogonalToPlaneNormal_Test, TQVectorTypes )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_5).Normalize();
    const float_q VECTOR_COMPONENTS[] = {-SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_0};
    const T TRANSFORMATION = T(VECTOR_COMPONENTS);

    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by arbitrary translation values.
/// </summary>
QTEST_CASE ( Translate3_PlaneIsCorrectlyTranslatedByCommonTranslationValues_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();

    const float_q TRANSLATION_X = SQFloat::_2;
    const float_q TRANSLATION_Y = SQFloat::_4;
    const float_q TRANSLATION_Z = -SQFloat::_6;

    const QPlane EXPECTED_RESULT = QPlane((float_q)0.21821789023599239, (float_q)0.43643578047198478, (float_q)0.87287156094396956, (float_q)4.1461399144838555);

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when the translation values equal zero.
/// </summary>
QTEST_CASE ( Translate3_PlaneDoesNotChangeWhenTranslationValuesEqualZero_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();

    const float_q TRANSLATION_X = SQFloat::_0;
    const float_q TRANSLATION_Y = SQFloat::_0;
    const float_q TRANSLATION_Z = SQFloat::_0;

    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane does not change when the displacement vector is orthogonal to the plane's normal.
/// </summary>
QTEST_CASE ( Translate3_PlaneDoesNotChangeWhenDisplacementVectorIsOrthogonalToPlaneNormal_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_5).Normalize();

    const float_q TRANSLATION_X = -SQFloat::_2;
    const float_q TRANSLATION_Y = SQFloat::_1;
    const float_q TRANSLATION_Z = SQFloat::_0;

    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary translation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_PlaneIsCorrectlyTransformedByCommonTransformationMatrix_Test, TQMatrixTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTranslationMatrix<T> TRANSLATION = QTranslationMatrix<T>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

    // Note: The method was tested using translation only, rotation only and scale only, and the results match what expected (same as Translate, Rotate and Scale tests)
    const QPlane EXPECTED_RESULT = QPlane((float_q)-0.41380294430118403, (float_q)0.70224688317678341, (float_q)-0.57932412202165773, (float_q)-4.5795177722637330);

    // Results calculated using DirectX SDK
    // float_q fYaw = SQAngle::_Pi;
    // float_q fPitch = SQAngle::_HalfPi;
    // float_q fRoll = SQAngle::_QuarterPi;
    // D3DXMATRIX rotation, translation, scaling, transformation;
    // D3DXMatrixRotationYawPitchRoll(&rotation, fYaw, fPitch, fRoll);
    // D3DXMatrixScaling(&scaling, SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    // D3DXMatrixTranslation(&translation, SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    // transformation = scaling * rotation * translation;
    //
    // D3DXPLANE planeNew;
    // D3DXPLANE plane(1,2,4,5);
    // D3DXPlaneNormalize(&plane, &plane);
    // D3DXMatrixInverse(&transformation, NULL, &transformation);
    // D3DXMatrixTranspose(&transformation, &transformation);
    // D3DXPlaneTransform(&planeNew, &plane, &transformation);
    // D3DXPlaneNormalize(&planeNew, &planeNew);

	// [Execution]
    QPlane planeUT = PLANE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test, TQMatrixTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_AssertionFailsWhenTransformationMatrixIsNull_Test, TQMatrixTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QTransformationMatrix<T> NULL_TRANSFORMATION = T::GetNullMatrix();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Transform(NULL_TRANSFORMATION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
QTEST_CASE( Transform2_PlaneIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    QSpaceConversionMatrix CONVERSION = QSpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    // Note: The method was tested using translation only, rotation only and scale only, and the results match what expected (same as Translate, Rotate and Scale tests)
    const QPlane EXPECTED_RESULT = QPlane((float_q)0.19518001458970666, (float_q)-0.26024001945294228, (float_q)-0.94561085768930031, (float_q)4.8007935851918324);

    // Results calculated using DirectX SDK
    // D3DXMATRIX transformation;
    // D3DXVECTOR3 vEye(1, 2, 3);
    // D3DXVECTOR3 vUp(0, 0, 1);
    // D3DXVECTOR3 vAt(0, 1, 0);
    // D3DXMatrixLookAtLH(&transformation, &vEye, &vUp, &vAt);
    //
    // D3DXPLANE planeNew;
    // D3DXPLANE plane(1,2,4,5);
    // D3DXPlaneNormalize(&plane, &plane);
    // D3DXMatrixInverse(&transformation, NULL, &transformation);
    // D3DXMatrixTranspose(&transformation, &transformation);
    // D3DXPlaneTransform(&planeNew, &plane, &transformation);
    // D3DXPlaneNormalize(&planeNew, &planeNew);

	// [Execution]
    QPlane planeUT = PLANE.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE( Transform2_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QSpaceConversionMatrix TRANSFORMATION = QSpaceConversionMatrix::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the space conversion matrix is null.
/// </summary>
QTEST_CASE( Transform2_AssertionFailsWhenMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QSpaceConversionMatrix NULL_TRANSFORMATION = QSpaceConversionMatrix::GetNullMatrix();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Transform(NULL_TRANSFORMATION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary quaternion and an arbitrary point.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_PlaneIsCorrectlyTransformedByCommonQuaternionAndPoint_Test, TQVectorTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QQuaternion TRANSFORMATION = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QPlane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Rotate(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity quaternion.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_PlaneDoesntChangeWhenTransformedByIdentityQuaternion_Test, TQVectorTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion TRANSFORMATION = QQuaternion::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the rotation quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_PlaneIsNullWhenRotationQuaternionIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QPlane EXPECTED_RESULT = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_9);

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(NULL_QUATERNION, POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TQVectorTypes )
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

    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const T POINT = T::GetNullVector();

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QPlane EXPECTED_RESULT = PLANE.Rotate(TRANSFORMATION);

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary rotation matrix and an arbitrary point.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_PlaneIsCorrectlyTransformedByCommonRotationMatrixAndPoint_Test, TQVectorTypes )
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

    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QPlane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Rotate(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test, TQVectorTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the rotation matrix is null.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_PlaneIsNullWhenRotationMatrixIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QRotationMatrix3x3 NULL_MATRIX = QRotationMatrix3x3(QMatrix3x3::GetNullMatrix());

    const QPlane EXPECTED_RESULT = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_9);

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(NULL_MATRIX, POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TQVectorTypes )
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

    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const T POINT = T::GetNullVector();

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QPlane EXPECTED_RESULT = PLANE.Rotate(TRANSFORMATION);

	// [Execution]
    QPlane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary vector and an arbitrary point.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_PlaneIsCorrectlyScaledByCommonVectorAndPoint_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QVector3 TRANSFORMATION = QVector3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by a vector of ones.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QVector3 TRANSFORMATION = QVector3::GetVectorOfOnes();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_AssertionFailsWhenPlaneIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane NULL_PLANE = QPlane::GetNullPlane();
    const QVector3 TRANSFORMATION = QVector3::GetVectorOfOnes();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.ScaleWithPivot(TRANSFORMATION, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_AssertionFailsWhenVectorIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QVector3 NULL_VECTOR = QVector3::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.ScaleWithPivot(NULL_VECTOR, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const T POINT = T::GetNullVector();
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QVector3 TRANSFORMATION = QVector3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = PLANE.Scale(TRANSFORMATION);

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by arbitrary scale values and an arbitrary point.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_PlaneIsCorrectlyScaledByCommonVectorAndPoint_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const float_q SCALE_X = SQFloat::_0_25;
    const float_q SCALE_Y = SQFloat::_3;
    const float_q SCALE_Z = -SQFloat::_1;

    const QPlane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(SCALE_X, SCALE_Y, SCALE_Z)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by scale values that equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_AssertionFailsWhenPlaneIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the scale values equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_AssertionFailsWhenScaleValuesEqualZero_Test, TQVectorTypes )
{
    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const float_q ZERO_SCALE_X = SQFloat::_0;
    const float_q ZERO_SCALE_Y = SQFloat::_0;
    const float_q ZERO_SCALE_Z = SQFloat::_0;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.ScaleWithPivot(ZERO_SCALE_X, ZERO_SCALE_Y, ZERO_SCALE_Z, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const T POINT = T::GetNullVector();
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QVector3 TRANSFORMATION = QVector3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = PLANE.Scale(TRANSFORMATION);

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary vector and an arbitrary point.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_PlaneIsCorrectlyScaledByCommonVectorAndPoint_Test, TQVectorTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by a vector of ones.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test, TQVectorTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_AssertionFailsWhenPlaneIsNull_Test, TQVectorTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3::GetIdentity();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.ScaleWithPivot(TRANSFORMATION, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_AssertionFailsWhenVectorIsNull_Test, TQVectorTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QScalingMatrix3x3 NULL_MATRIX = QScalingMatrix3x3(QMatrix3x3::GetNullMatrix());

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.ScaleWithPivot(NULL_MATRIX, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary vector.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_PlaneIsCorrectlyScaledByCommonVector_Test, TQVectorTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TQVectorTypes )
{
    // [Preparation]
    const T POINT = T::GetNullVector();
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QVector3 TRANSFORMATION = QVector3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QPlane EXPECTED_RESULT = PLANE.Scale(TRANSFORMATION);

	// [Execution]
    QPlane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Template method used by TransformWithPivot1_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const VectorType POINT = VectorType(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTranslationMatrix<T> TRANSLATION = QTranslationMatrix<T>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

    const QPlane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Transform(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    QPlane planeUT = PLANE.TransformWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary translation matrix and an arbitrary point.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Test, TQMatrixTypes )
{
    BOOST_TEST_MESSAGE("VectorType=QVector3");
    TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Template<T, QVector3>();
    BOOST_TEST_MESSAGE("VectorType=QVector4");
    TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Template<T, QVector4>();
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Template method used by TransformWithPivot1_AssertionFailsWhenTransformationMatrixIsNull_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const VectorType POINT = VectorType(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();
    const QPlane EXPECTED_RESULT = PLANE;

	// [Execution]
    QPlane planeUT = PLANE.TransformWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Test, TQMatrixTypes )
{
    BOOST_TEST_MESSAGE("VectorType=QVector3");
    TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Template<T, QVector3>();
    BOOST_TEST_MESSAGE("VectorType=QVector4");
    TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Template<T, QVector4>();
}

/// <summary>
/// Template method used by TransformWithPivot1_AssertionFailsWhenTransformationMatrixIsNull_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q POINT_COMPONENTS[] = {-SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1};
    const VectorType POINT = VectorType(POINT_COMPONENTS);
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5);
    const QTransformationMatrix<T> NULL_TRANSFORMATION = T::GetNullMatrix();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.TransformWithPivot(NULL_TRANSFORMATION, POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Test, TQMatrixTypes )
{
    BOOST_TEST_MESSAGE("VectorType=QVector3");
    TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Template<T, QVector3>();
    BOOST_TEST_MESSAGE("VectorType=QVector4");
    TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Template<T, QVector4>();
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Template method used by TransformWithPivot1_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const VectorType POINT = VectorType::GetNullVector();

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_5).Normalize();
    const QTranslationMatrix<T> TRANSLATION = QTranslationMatrix<T>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

    const QPlane EXPECTED_RESULT = PLANE.Transform(TRANSFORMATION);

	// [Execution]
    QPlane planeUT = PLANE.TransformWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SQFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TQMatrixTypes )
{
    BOOST_TEST_MESSAGE("VectorType=QVector3");
    TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Template<T, QVector3>();
    BOOST_TEST_MESSAGE("VectorType=QVector4");
    TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Template<T, QVector4>();
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_0_25, (float_q)-0.000002, (float_q)40000.0, SQFloat::_0 );

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    #if defined(QE_COMPILER_GCC) && (defined(QE_OS_LINUX) || defined(QE_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_q EXPECTED_STRING_FORM = QE_L("PL(0.25,-1.99999999e-06,40000,0)");
    #else
        string_q EXPECTED_STRING_FORM = QE_L("PL(0.25,-1.99999999e-006,40000,0)");
    #endif
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    #if defined(QE_COMPILER_GCC) && (defined(QE_OS_LINUX) || defined(QE_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_q EXPECTED_STRING_FORM = QE_L("PL(0.25,-1.9999999999999999e-06,40000,0)");
    #else
        string_q EXPECTED_STRING_FORM = QE_L("PL(0.25,-1.9999999999999999e-006,40000,0)");
    #endif
#endif

	// [Execution]
    QPlane planeUT = PLANE;
    string_q strStringForm = planeUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// [TODO] Thund: Protected methods have not been tested yet, they were postponed

// End - Test Suite: QPlane
QTEST_SUITE_END()
