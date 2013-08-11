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
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QRay2D.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QRay2D;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;

QTEST_SUITE_BEGIN( QRay2D_TestSuite )


/// <summary>
/// Checks if default values have not changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_ORIGIN(QVector2::GetZeroVector());
    const QVector2 EXPECTED_VALUE_FOR_DIRECTION = QVector2::GetZeroVector();

	// Execution
    QRay2D rayUT;

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_DIRECTION = QVector2(SQFloat::_4, SQFloat::_5);

    QRay2D EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// Execution
    QRay2D rayUT(EXPECTED_RAY);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseRay;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_DIRECTION = QVector2(SQFloat::_4, SQFloat::_5);

    QBaseRay<QVector2, QVector2> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// Execution
    QRay2D rayUT(EXPECTED_RAY);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_DIRECTION = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    QRay2D rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
QTEST_CASE ( Constructor4_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test )
{
    // Preparation
    const QVector2 INPUT_VALUE_FOR_ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 INPUT_VALUE_FOR_DIRECTION = QVector2(SQFloat::_4, SQFloat::_5);

    const QVector2 UNEXPECTED_VALUE_FOR_DIRECTION = INPUT_VALUE_FOR_DIRECTION.Normalize();

	// Execution
    QRay2D rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // Verification
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that it returns a null ray placed at the origin.
/// </summary>
QTEST_CASE ( GetRayZero_ReturnsWhatExpected_Test )
{
    // Preparation
    QRay2D EXPECTED_VALUE(QVector2::GetZeroVector(), QVector2::GetZeroVector());

	// Execution
    QRay2D obtinedRay = QRay2D::GetRayZero();

    // Verification
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that it returns a ray that is parallel to X axis and points to positive direction.
/// </summary>
QTEST_CASE ( GetRayX_ReturnsWhatExpected_Test )
{
    // Preparation
    QRay2D EXPECTED_VALUE(QVector2::GetZeroVector(), QVector2::GetUnitVectorX());

	// Execution
    QRay2D obtinedRay = QRay2D::GetRayX();

    // Verification
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that it returns a ray that is parallel to Y axis and points to positive direction.
/// </summary>
QTEST_CASE ( GetRayY_ReturnsWhatExpected_Test )
{
    // Preparation
    QRay2D EXPECTED_VALUE(QVector2::GetZeroVector(), QVector2::GetUnitVectorY());

	// Execution
    QRay2D obtinedRay = QRay2D::GetRayY();

    // Verification
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that a ray is correctly assigned to another ray.
/// </summary>
QTEST_CASE ( OperatorAssignation_RayIsAssignedProperlyToAnother_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseRay;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_DIRECTION = QVector2(SQFloat::_3, SQFloat::_4);

    const QRay2D OTHER_RAY = QRay2D(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// Execution
    QRay2D rayUT;
    rayUT = OTHER_RAY;

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that it returns False when rays don't intersect.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsFalseWhenRaysDoNotIntersect_Test )
{
    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_4).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY1.Intersection(RAY2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays intersect but not in Origin.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenRaysIntersectNoIncludingOrigin_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, -SQFloat::_4).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(-SQFloat::_1, -SQFloat::_2).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY1.Intersection(RAY2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays coincide totally.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenRaysCoincideTotally_Test )
{
    // O1O2-------->>d1d2  (I

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN1, DIRECTION1);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an origin of one ray is contained in the other ray (not including the other origin).
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenAnOriginIsContainedInTheOtherRay_Test )
{
    //         ^
    //        /
    //       /
    // O1---O2----->
    //
    //       I

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, SQFloat::_2).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the 2 rays share only one of their origins.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenRaysShareOriginOnly_Test )
{
    //       ^
    //      /
    //     /
    // O1O2----->
    //
    //     I

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_3, SQFloat::_2).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_3, SQFloat::_3).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
QTEST_CASE ( Intersection1_AssertionFailsWhenTheDirectionVectorIsNull_Test )
{
    // O1---O2(d2=0)----->d1
    //
    //        I

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 DIRECTION1 = QVector2::GetZeroVector();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    
    const QVector2 ORIGIN2 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed1 = false;
    
    try
    {
        RAY1.Intersection(RAY2); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        RAY2.Intersection(RAY1); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the other but would do it if it had an opposite direction.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsFalseWhenRaysDoNotIntersectButWouldDoIfTheyHadAnOppositeDirection_Test )
{
    // ^        ^
    //  \      /
    //   O1   /
    //    ·  /
    //     ·/
    //     /·
    //   O2  ·

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, -SQFloat::_4).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult1 = RAY1.Intersection(RAY2);
    bool bResult2 = RAY2.Intersection(RAY1);

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one fo the rays is contained in the other.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenOneRayIsContainedInTheOther_Test )
{
    //
    // O1---O2----->>
    //
    //     I

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, SQFloat::_0).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_0).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays point each other.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenRaysPointEachOther_Test )
{
    //
    // O1<-------->O2
    //
    //       I

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 DIRECTION2 = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that it's not necessary that rays are normalized.
/// </summary>
QTEST_CASE ( Intersection1_ItIsNotNecessaryNormalizeRays_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // Preparation
    const QVector2 ORIGIN1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, SQFloat::_4);
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(-SQFloat::_1, SQFloat::_2);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY1.Intersection(RAY2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common ray and a common triangle intersect.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenCommonRayIntersectsWithCommonTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(TRIANGLE);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common ray intersect with a vertex of the triangle.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenRayIntersectsWithTriangleVertex_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN1 = VERTEX_A - DIRECTION1;
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B - DIRECTION2;
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const QVector2 DIRECTION3 = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C - DIRECTION3;
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bIntersectsWithA = RAY1.Intersection(TRIANGLE);
    bool bIntersectsWithB = RAY2.Intersection(TRIANGLE);
    bool bIntersectsWithC = RAY3.Intersection(TRIANGLE);

    // Verification
    BOOST_CHECK_EQUAL(bIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when a common ray and a common triangle would intersect if the ray pointed to the opposite direction.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsFalseWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = -QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(TRIANGLE);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray is contained in the triangle.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenRayBelongsToTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 ORIGIN = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SQFloat::_0_25;
    const QVector2 DIRECTION = QVector2(VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(TRIANGLE);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray is contained in an edge of the triangle.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenOriginBelongsToEdgeOfTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 DIRECTION1 = QVector2(SQFloat::_0, SQFloat::_1).Normalize();
    const QVector2 ORIGIN1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION3 = QVector2(SQFloat::_1, -SQFloat::_2).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bOriginContainedInAB = RAY1.Intersection(TRIANGLE);
    bool bOriginContainedInAC = RAY2.Intersection(TRIANGLE);
    bool bOriginContainedInBC = RAY3.Intersection(TRIANGLE);

    // Verification
    BOOST_CHECK_EQUAL(bOriginContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInBC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenOriginAndTriangleVertexCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(VERTEX_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VERTEX_B, DIRECTION);
    const QRay2D RAY3 = QRay2D(VERTEX_C, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bOriginAndACoincide = RAY1.Intersection(TRIANGLE);
    bool bOriginAndBCoincide = RAY2.Intersection(TRIANGLE);
    bool bOriginAndCCoincide = RAY3.Intersection(TRIANGLE);

    // Verification
    BOOST_CHECK_EQUAL(bOriginAndACoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndBCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndCCoincide, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
QTEST_CASE ( Intersection2_ItIsNotNecessaryToNormalizeTheRay_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN;
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(TRIANGLE);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
QTEST_CASE ( Intersection2_AssertionFailsWhenRayDirectionIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_4, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_5, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(TRIANGLE);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
QTEST_CASE ( Intersection2_AssertionFailsWhenAllTriangleVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(SQFloat::_3, SQFloat::_3);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = VERTEX_A;
    const QVector2 VERTEX_C = VERTEX_A;

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(TRIANGLE);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns True when the origin of the ray coincides with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayOriginAndQuadrilateralVertexCoincide_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_A = VERTEX_A;
    const QVector2 DIRECTION_A = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B = VERTEX_B;
    const QVector2 DIRECTION_B = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QVector2 ORIGIN_C = VERTEX_C;
    const QVector2 DIRECTION_C = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_C = QRay2D(ORIGIN_C, DIRECTION_C);

    const QVector2 ORIGIN_D = VERTEX_D;
    const QVector2 DIRECTION_D = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_D = QRay2D(ORIGIN_D, DIRECTION_D);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_A = RAY_A.Intersection(QUAD);
    bool bResult_B = RAY_B.Intersection(QUAD);
    bool bResult_C = RAY_C.Intersection(QUAD);
    bool bResult_D = RAY_D.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_D, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with two contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithTwoContinuousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_BC = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_BC = QVector2(SQFloat::_2, -SQFloat::_1).Normalize();
    const QRay2D RAY_AB_BC = QRay2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const QVector2 ORIGIN_BC_CD = QVector2(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION_BC_CD = QVector2(-SQFloat::_1, -SQFloat::_2).Normalize();
    const QRay2D RAY_BC_CD = QRay2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const QVector2 ORIGIN_CD_DA = QVector2(SQFloat::_2, -SQFloat::_3);
    const QVector2 DIRECTION_CD_DA = QVector2(-SQFloat::_2, SQFloat::_3).Normalize();
    const QRay2D RAY_CD_DA = QRay2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const QVector2 ORIGIN_DA_AB = QVector2(-SQFloat::_1, -SQFloat::_3);
    const QVector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const QRay2D RAY_DA_AB = QRay2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_AB_BC = RAY_AB_BC.Intersection(QUAD);
    bool bResult_BC_CD = RAY_BC_CD.Intersection(QUAD);
    bool bResult_CD_DA = RAY_CD_DA.Intersection(QUAD);
    bool bResult_DA_AB = RAY_DA_AB.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_AB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD_DA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA_AB, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray belongs to one of the edges of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayOriginBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 ORIGIN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 ORIGIN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 ORIGIN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Fasle when the ray doesn't intersect with the quadrilateral but would do if the direction vector was the opposite.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsFalseWhenRayDoesNotIntersectWithQuadrilateralButWouldDoIfDirectionWasOpposite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = -QVector2(SQFloat::_2, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsFalseWhenRayAndQuadrilateralDoesNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithQuadrilateralVertex_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_A = QVector2(VERTEX_A.x - SQFloat::_1, VERTEX_A.y - SQFloat::_1);
    const QVector2 DIRECTION_A = (VERTEX_A - ORIGIN_A).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B = QVector2(VERTEX_B.x - SQFloat::_1, VERTEX_B.y + SQFloat::_1);
    const QVector2 DIRECTION_B = (VERTEX_B - ORIGIN_B).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QVector2 ORIGIN_C = QVector2(VERTEX_C.x + SQFloat::_1, VERTEX_C.y + SQFloat::_1);
    const QVector2 DIRECTION_C = (VERTEX_C - ORIGIN_C).Normalize();
    const QRay2D RAY_C = QRay2D(ORIGIN_C, DIRECTION_C);

    const QVector2 ORIGIN_D = QVector2(VERTEX_D.x + SQFloat::_1, VERTEX_D.y - SQFloat::_1);
    const QVector2 DIRECTION_D = (VERTEX_D - ORIGIN_D).Normalize();
    const QRay2D RAY_D = QRay2D(ORIGIN_D, DIRECTION_D);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_A = RAY_A.Intersection(QUAD);
    bool bResult_B = RAY_B.Intersection(QUAD);
    bool bResult_C = RAY_C.Intersection(QUAD);
    bool bResult_D = RAY_D.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_D, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray is inside the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayOriginIsContainedInQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);

    const QVector2 DIRECTION_AB = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN, DIRECTION_AB);

    const QVector2 DIRECTION_BC = (VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN, DIRECTION_BC);

    const QVector2 DIRECTION_CD = (VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D) - ORIGIN).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN, DIRECTION_CD);

    const QVector2 DIRECTION_DA = (VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A) - ORIGIN).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithTwoNonContinuousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_CD = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_CD = QVector2(SQFloat::_0, -SQFloat::_1).Normalize();
    const QRay2D RAY_AB_CD = QRay2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const QVector2 ORIGIN_BC_DA = QVector2(SQFloat::_3, SQFloat::_1);
    const QVector2 DIRECTION_BC_DA = QVector2(-SQFloat::_2, -SQFloat::_1).Normalize();
    const QRay2D RAY_BC_DA = QRay2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_AB_CD = RAY_AB_CD.Intersection(QUAD);
    bool bResult_BC_DA = RAY_BC_DA.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_AB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayBelongsToQuadrilateralEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB = (VERTEX_A - ORIGIN_AB).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 ORIGIN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC = (VERTEX_B - ORIGIN_BC).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 ORIGIN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD = (VERTEX_C - ORIGIN_CD).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 ORIGIN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA = (VERTEX_D - ORIGIN_DA).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
QTEST_CASE ( Intersection3_AssertionFailsWhenRayDirectionIsNull )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QRay2D NULL_RAY = QRay2D::GetRayZero();

    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        NULL_RAY.Intersection(QUAD);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
QTEST_CASE ( Intersection3_AssertionFailsWhenAllQuadrilateralVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = VERTEX_A;
    const QVector2 VERTEX_C = VERTEX_A;
    const QVector2 VERTEX_D = VERTEX_A;
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = (VERTEX_A - ORIGIN);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(QUAD);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( Intersection3_ResultIsNotDifferentWhenRayDirectionIsNotNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_0, -SQFloat::_1);
    const QRay2D NON_NORMALIZED_RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D NORMALIZED_RAY = NON_NORMALIZED_RAY.Normalize();

	// Execution
    bool bResultNormalized = NORMALIZED_RAY.Intersection(QUAD);
    bool bResultNonNormalized = NON_NORMALIZED_RAY.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultNormalized, bResultNonNormalized);
}

/// <summary>
/// Checks that it returns True when the ray intersects with two contiguous vertices of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithTwoContiguousVertices_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const QVector2 ORIGIN_AB = VERTEX_A - DIRECTION_AB;
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const QVector2 ORIGIN_BC = VERTEX_B - DIRECTION_BC;
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const QVector2 ORIGIN_CD = VERTEX_C - DIRECTION_CD;
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const QVector2 ORIGIN_DA = VERTEX_D - DIRECTION_DA;
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns no intersection points when rays don't intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionPointsWhenRaysDoNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_4).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when rays intersect but not in Origin.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionPointWhenRaysIntersectNoIncludingOrigin_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const QVector2 ORIGIN1(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(EXPECTED_POINT.x - ORIGIN1.x, EXPECTED_POINT.y - ORIGIN1.y).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2(SQFloat::_2, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(EXPECTED_POINT.x - ORIGIN2.x, EXPECTED_POINT.y - ORIGIN2.y).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

	// Execution
    QVector2 vIntersection = QVector2(SQFloat::_0, SQFloat::_0);
    EQIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when rays coincide totally.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsInfiniteIntersectionsWhenRaysCoincideTotally_Test )
{
    // O1O2-------->>d1d2  (I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN1, DIRECTION1);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection); // I
    EQIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns one intersection point when an origin of one ray is contained in the other ray (not including the other origin).
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenAnOriginIsContainedInTheOtherRay_Test )
{
    //         ^
    //        /
    //       /
    // O1---O2----->
    //
    //       I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, SQFloat::_2).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2(SQFloat::_2, SQFloat::_3);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = ORIGIN2;

	// Execution
    QVector2 vIntersection1 = QVector2(SQFloat::_0, SQFloat::_0);
    EQIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    QVector2 vIntersection2 = QVector2(SQFloat::_0, SQFloat::_0);
    EQIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the 2 rays share only one of their origins.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenRaysShareOriginOnly_Test )
{
    //       ^
    //      /
    //     /
    // O1O2----->
    //
    //     I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_3, SQFloat::_2).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2 = ORIGIN1;
    const QVector2 DIRECTION2 = QVector2(SQFloat::_3, SQFloat::_3).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = ORIGIN1;

	// Execution
    QVector2 vIntersection1 = QVector2(SQFloat::_0, SQFloat::_0);
    EQIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    QVector2 vIntersection2 = QVector2(SQFloat::_0, SQFloat::_0);
    EQIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint1_AssertionFailsWhenTheDirectionVectorIsNull_Test )
{
    // O1---O2(d2=0)----->d1
    //
    //        I

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_2, SQFloat::_4);
    const QVector2 DIRECTION1 = QVector2::GetZeroVector();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    
    const QVector2 ORIGIN2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed1 = false;
    QVector2 vIntersection1;

    try
    {
        RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;
    QVector2 vIntersection2;

    try
    {
        RAY2.IntersectionPoint(RAY1, vIntersection2); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns no intersections when the ray doesn't intersect with the other but would do it if it had an opposite direction.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionsWhenRaysDoNotIntersectButWouldDoIfTheyHadAnOppositeDirection_Test )
{
    // ^        ^
    //  \      /
    //   O1   /
    //    ·  /
    //     ·/
    //     /·
    //   O2  ·

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_2, -SQFloat::_4).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    QVector2 vIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when one fo the rays is contained in the other.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOneRayIsContainedInTheOther_Test )
{
    //
    // O1---O2----->>
    //
    //     I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, SQFloat::_0).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_0).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = ORIGIN2;


	// Execution
    QVector2 vIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    QVector2 vIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when rays point each other.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenRaysPointEachOther_Test )
{
    //
    // O1<-------->O2
    //
    //       I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN1(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2(SQFloat::_3, SQFloat::_4);
    const QVector2 DIRECTION2 = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_POINT1 = RAY1.Origin;
    const QVector2 EXPECTED_POINT2 = RAY2.Origin;

	// Execution
    QVector2 vIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    QVector2 vIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it's not necessary that rays are normalized.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ItIsNotNecessaryNormalizeRays_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const QVector2 ORIGIN1(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION1 = QVector2(EXPECTED_POINT.x - ORIGIN1.x, EXPECTED_POINT.y - ORIGIN1.y);
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 ORIGIN2(SQFloat::_2, SQFloat::_2);
    const QVector2 DIRECTION2 = QVector2(EXPECTED_POINT.x - ORIGIN2.x, EXPECTED_POINT.y - ORIGIN2.y);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

	// Execution
    QVector2 vIntersection = QVector2(SQFloat::_0, SQFloat::_0);
    EQIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when a common ray and a common triangle intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenCommonRayIntersectsWithCommonTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(EXPECTED_POINT - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenRayIntersectsWithTriangleVertex_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT_A = VERTEX_A;
    const QVector2 EXPECTED_POINT_B = VERTEX_B;
    const QVector2 EXPECTED_POINT_C = VERTEX_C;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN1 = VERTEX_A - DIRECTION1;
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B - DIRECTION2;
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const QVector2 DIRECTION3 = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C - DIRECTION3;
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);
    
	// Execution
    QVector2 vIntersectionA;
    QVector2 vIntersectionB;
    QVector2 vIntersectionC;
    EQIntersections eIntersectionsWithA = RAY1.IntersectionPoint(TRIANGLE, vIntersectionA);
    EQIntersections eIntersectionsWithB = RAY2.IntersectionPoint(TRIANGLE, vIntersectionB);
    EQIntersections eIntersectionsWithC = RAY3.IntersectionPoint(TRIANGLE, vIntersectionC);

    // Verification
    BOOST_CHECK_EQUAL(eIntersectionsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectionsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectionsWithC, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
}

/// <summary>
/// Checks that it returns no intersections when a common ray and a common triangle would intersect if the ray pointed to the opposite direction.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = -QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is contained in the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenRayBelongsToTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 EXPECTED_POINT = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);

    const QVector2 ORIGIN = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SQFloat::_0_25;
    const QVector2 DIRECTION = QVector2(EXPECTED_POINT - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection intersection when the origin of the ray is contained in an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 DIRECTION1 = QVector2(SQFloat::_0, SQFloat::_1).Normalize();
    const QVector2 ORIGIN1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION3 = QVector2(SQFloat::_1, -SQFloat::_2).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT1 = ORIGIN1;
    const QVector2 EXPECTED_POINT2 = ORIGIN2;
    const QVector2 EXPECTED_POINT3 = ORIGIN3;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// Execution
    QVector2 vIntersection1;
    QVector2 vIntersection2;
    QVector2 vIntersection3;
    EQIntersections eOriginContainedInAB = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EQIntersections eOriginContainedInAC = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EQIntersections eOriginContainedInBC = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eOriginContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray is contained in an edge of the triangle and the direction vector points to another edge.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfTriangleAndDirectionPointsToOtherEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 ORIGIN1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 ORIGIN2 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 ORIGIN3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION1 = QVector2(ORIGIN2 - ORIGIN1).Normalize();
    const QVector2 DIRECTION2 = QVector2(ORIGIN3 - ORIGIN2).Normalize();
    const QVector2 DIRECTION3 = QVector2(ORIGIN1 - ORIGIN3).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT1 = ORIGIN1;
    const QVector2 EXPECTED_POINT2 = ORIGIN2;
    const QVector2 EXPECTED_POINT3 = ORIGIN3;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vIntersection1;
    QVector2 vIntersection2;
    QVector2 vIntersection3;
    EQIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EQIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EQIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray coincides with a vertex of the triangle and the direction vector points to another edge.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenCoincidesWithVertexOfTriangleAndDirectionPointsToOtherEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 ORIGIN1 = VERTEX_A;
    const QVector2 ORIGIN2 = VERTEX_B;
    const QVector2 ORIGIN3 = VERTEX_C;
    const QVector2 DIRECTION1 = QVector2(VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN1).Normalize();
    const QVector2 DIRECTION2 = QVector2(VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN2).Normalize();
    const QVector2 DIRECTION3 = QVector2(VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN3).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT1 = ORIGIN1;
    const QVector2 EXPECTED_POINT2 = ORIGIN2;
    const QVector2 EXPECTED_POINT3 = ORIGIN3;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vIntersection1;
    QVector2 vIntersection2;
    QVector2 vIntersection3;
    EQIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EQIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EQIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 DIRECTION = QVector2(SQFloat::_0, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(VERTEX_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VERTEX_B, DIRECTION);
    const QRay2D RAY3 = QRay2D(VERTEX_C, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT1 = VERTEX_A;
    const QVector2 EXPECTED_POINT2 = VERTEX_B;
    const QVector2 EXPECTED_POINT3 = VERTEX_C;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// Execution
    QVector2 vIntersection1;
    QVector2 vIntersection2;
    QVector2 vIntersection3;
    EQIntersections eOriginAndACoincide = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EQIntersections eOriginAndBCoincide = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EQIntersections eOriginAndCCoincide = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eOriginAndACoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginAndBCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginAndCCoincide, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ItIsNotNecessaryToNormalizeTheRay_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(EXPECTED_POINT - ORIGIN);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
QTEST_CASE ( IntersectionPoint2_AssertionFailsWhenRayDirectionIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
QTEST_CASE ( IntersectionPoint2_AssertionFailsWhenAllTriangleVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(SQFloat::_3, SQFloat::_3);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = VERTEX_A;
    const QVector2 VERTEX_C = VERTEX_A;

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns the closest of the two intersection points.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTheClosestPointWhenIntersectingWithTwoEdges_Test )
{
    //       Y
    //       |   
    //      /|\
    //  <--/-|-x-----------O
    //    /  |  \
    //   /___|___\
    //       |______________ X

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 VERTEX_B = QVector2(-SQFloat::_2, SQFloat::_1);
    const QVector2 VERTEX_C = QVector2(SQFloat::_2, SQFloat::_1);

    const QVector2 ORIGIN = QVector2(SQFloat::_4, SQFloat::_2);
    const QVector2 DIRECTION = QVector2::GetUnitVectorInvX();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK( SQFloat::IsPositive(vIntersection.x) );
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two edges of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 EXPECTED_POINT1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 EXPECTED_POINT2 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_POINT3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);

    const QVector2 DIRECTION1 = QVector2(EXPECTED_POINT2 - EXPECTED_POINT1).Normalize();
    const QVector2 DIRECTION2 = QVector2(EXPECTED_POINT3 - EXPECTED_POINT2).Normalize();
    const QVector2 DIRECTION3 = QVector2(EXPECTED_POINT1 - EXPECTED_POINT3).Normalize();

    QVector2 ORIGIN1 = EXPECTED_POINT1 - QVector2(DIRECTION1);
    QVector2 ORIGIN2 = EXPECTED_POINT2 - QVector2(DIRECTION2);
    QVector2 ORIGIN3 = EXPECTED_POINT3 - QVector2(DIRECTION3);

    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vIntersection1;
    QVector2 vIntersection2;
    QVector2 vIntersection3;
    EQIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EQIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EQIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns two intersection points when the origin belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenRayBelongsToEdgeOfTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);
    
    const QVector2 ORIGIN1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION1 = (VERTEX_A - ORIGIN1).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION2 = (VERTEX_B - ORIGIN2).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION3 = (VERTEX_C - ORIGIN3).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT1 = ORIGIN1;
    const QVector2 EXPECTED_POINT2 = ORIGIN2;
    const QVector2 EXPECTED_POINT3 = ORIGIN3;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vIntersection1;
    QVector2 vIntersection2;
    QVector2 vIntersection3;
    EQIntersections eOriginContainedInAB = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EQIntersections eOriginContainedInAC = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EQIntersections eOriginContainedInBC = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eOriginContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns two intersection points when a common ray and a common triangle intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionPointsWhenCommonRayIntersectsWithCommonTriangle_Test )
{
    //         B
    //        / \
    //       /   \
    //      /     \
    //     A-------C
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 EXPECTED_SECONDPOINT = QVector2((float_q)2.333333333333333, (float_q)3.333333333333333);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    
	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenRayIntersectsWithTriangleVertex_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const QVector2 EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const QVector2 EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const QVector2 EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN1 = VERTEX_A - DIRECTION1;
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);

    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B - DIRECTION2;
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);

    const QVector2 DIRECTION3 = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C - DIRECTION3;
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

	// Execution
    QVector2 vFirstIntersectionA;
    QVector2 vFirstIntersectionB;
    QVector2 vFirstIntersectionC;
    QVector2 vSecondIntersectionA;
    QVector2 vSecondIntersectionB;
    QVector2 vSecondIntersectionC;
    EQIntersections eIntersectionsWithA = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersectionA, vSecondIntersectionA);
    EQIntersections eIntersectionsWithB = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersectionB, vSecondIntersectionB);
    EQIntersections eIntersectionsWithC = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersectionC, vSecondIntersectionC);

    // Verification
    BOOST_CHECK_EQUAL(eIntersectionsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectionsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectionsWithC, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersections when a common ray and a common triangle would intersect if the ray pointed to the opposite direction.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = -QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_POINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is contained in the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenRayBelongsToTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 EXPECTED_FIRSTPOINT = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 ORIGIN = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SQFloat::_0_25;
    const QVector2 DIRECTION = QVector2(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection intersection when the origin of the ray is contained in an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 DIRECTION1 = QVector2(SQFloat::_0, SQFloat::_1).Normalize();
    const QVector2 ORIGIN1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION2 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION3 = QVector2(SQFloat::_1, -SQFloat::_2).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const QVector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const QVector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// Execution
    QVector2 vFirstIntersection1;
    QVector2 vFirstIntersection2;
    QVector2 vFirstIntersection3;
    QVector2 vSecondIntersection1;
    QVector2 vSecondIntersection2;
    QVector2 vSecondIntersection3;
    EQIntersections eOriginContainedInAB = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eOriginContainedInAC = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EQIntersections eOriginContainedInBC = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eOriginContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray is contained in an edge of the triangle and the direction vector points to another edge.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfTriangleAndDirectionPointsToOtherEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 ORIGIN1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 ORIGIN2 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 ORIGIN3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION1 = QVector2(ORIGIN2 - ORIGIN1).Normalize();
    const QVector2 DIRECTION2 = QVector2(ORIGIN3 - ORIGIN2).Normalize();
    const QVector2 DIRECTION3 = QVector2(ORIGIN1 - ORIGIN3).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const QVector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const QVector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const QVector2 EXPECTED_SECONDPOINT1 = ORIGIN2;
    const QVector2 EXPECTED_SECONDPOINT2 = ORIGIN3;
    const QVector2 EXPECTED_SECONDPOINT3 = ORIGIN1;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    // Execution
    QVector2 vFirstIntersection1;
    QVector2 vFirstIntersection2;
    QVector2 vFirstIntersection3;
    QVector2 vSecondIntersection1;
    QVector2 vSecondIntersection2;
    QVector2 vSecondIntersection3;
    EQIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EQIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 DIRECTION = QVector2(SQFloat::_0, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(VERTEX_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VERTEX_B, DIRECTION);
    const QRay2D RAY3 = QRay2D(VERTEX_C, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT1 = VERTEX_A;
    const QVector2 EXPECTED_FIRSTPOINT2 = VERTEX_B;
    const QVector2 EXPECTED_FIRSTPOINT3 = VERTEX_C;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// Execution
    QVector2 vFirstIntersection1;
    QVector2 vFirstIntersection2;
    QVector2 vFirstIntersection3;
    QVector2 vSecondIntersection1;
    QVector2 vSecondIntersection2;
    QVector2 vSecondIntersection3;
    EQIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EQIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide and direction points to the opposite edge.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincideAndDirectionPointsToOppositeEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 ORIGIN1 = VERTEX_A;
    const QVector2 ORIGIN2 = VERTEX_B;
    const QVector2 ORIGIN3 = VERTEX_C;
    const QVector2 DIRECTION1 = QVector2(VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN1).Normalize();
    const QVector2 DIRECTION2 = QVector2(VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN2).Normalize();
    const QVector2 DIRECTION3 = QVector2(VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN3).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const QVector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const QVector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const QVector2 EXPECTED_SECONDPOINT1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_SECONDPOINT2 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_SECONDPOINT3 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    // Execution
    QVector2 vFirstIntersection1;
    QVector2 vFirstIntersection2;
    QVector2 vFirstIntersection3;
    QVector2 vSecondIntersection1;
    QVector2 vSecondIntersection2;
    QVector2 vSecondIntersection3;
    EQIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EQIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ItIsNotNecessaryToNormalizeTheRay_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 EXPECTED_SECONDPOINT = QVector2((float_q)2.333333333333333, (float_q)3.333333333333333);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = EXPECTED_FIRSTPOINT - ORIGIN;
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    
	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
QTEST_CASE ( IntersectionPoint3_AssertionFailsWhenRayDirectionIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
QTEST_CASE ( IntersectionPoint3_AssertionFailsWhenAllTriangleVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(SQFloat::_3, SQFloat::_3);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = VERTEX_A;
    const QVector2 VERTEX_C = VERTEX_A;

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns the closest of the two intersection points.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTheClosestPointInFirstParameterWhenIntersectingWithTwoEdges_Test )
{
    //       Y
    //       |   
    //      /|\
    //  <--2-|-1-----------O
    //    /  |  \
    //   /___|___\
    //       |______________ X

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 VERTEX_B = QVector2(-SQFloat::_2, SQFloat::_1);
    const QVector2 VERTEX_C = QVector2(SQFloat::_2, SQFloat::_1);

    const QVector2 ORIGIN = QVector2(SQFloat::_4, SQFloat::_2);
    const QVector2 DIRECTION = QVector2::GetUnitVectorInvX();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK( SQFloat::IsPositive(vFirstIntersection.x) );
    BOOST_CHECK( SQFloat::IsNegative(vSecondIntersection.x) );
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two edges of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenRayIntersectWithTwoEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 EXPECTED_FIRSTPOINT1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 EXPECTED_FIRSTPOINT2 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_FIRSTPOINT3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_SECONDPOINT1 = EXPECTED_FIRSTPOINT2;
    const QVector2 EXPECTED_SECONDPOINT2 = EXPECTED_FIRSTPOINT3;
    const QVector2 EXPECTED_SECONDPOINT3 = EXPECTED_FIRSTPOINT1;

    const QVector2 DIRECTION1 = QVector2(EXPECTED_FIRSTPOINT2 - EXPECTED_FIRSTPOINT1).Normalize();
    const QVector2 DIRECTION2 = QVector2(EXPECTED_FIRSTPOINT3 - EXPECTED_FIRSTPOINT2).Normalize();
    const QVector2 DIRECTION3 = QVector2(EXPECTED_FIRSTPOINT1 - EXPECTED_FIRSTPOINT3).Normalize();

    QVector2 ORIGIN1 = EXPECTED_FIRSTPOINT1 - QVector2(DIRECTION1);
    QVector2 ORIGIN2 = EXPECTED_FIRSTPOINT2 - QVector2(DIRECTION2);
    QVector2 ORIGIN3 = EXPECTED_FIRSTPOINT3 - QVector2(DIRECTION3);

    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vFirstIntersection1;
    QVector2 vFirstIntersection2;
    QVector2 vFirstIntersection3;
    QVector2 vSecondIntersection1;
    QVector2 vSecondIntersection2;
    QVector2 vSecondIntersection3;
    EQIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EQIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}

/// <summary>
/// Checks that the intersection is returned using the first output parameter when only one intersection is detected.
/// </summary>
QTEST_CASE ( IntersectionPoint3_IntersectionIsReturnedInFirstParameterWhenThereIsOnlyOneIntersection_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 DIRECTION = QVector2(SQFloat::_0, -SQFloat::_1);
    const QVector2 ORIGIN = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - DIRECTION;
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);

	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection != EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the origin belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenRayBelongsToEdgeOfTriangle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, SQFloat::_2);
    
    const QVector2 ORIGIN1 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION1 = (VERTEX_A - ORIGIN1).Normalize();
    const QVector2 ORIGIN2 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION2 = (VERTEX_B - ORIGIN2).Normalize();
    const QVector2 ORIGIN3 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION3 = (VERTEX_C - ORIGIN3).Normalize();
    const QRay2D RAY1 = QRay2D(ORIGIN1, DIRECTION1);
    const QRay2D RAY2 = QRay2D(ORIGIN2, DIRECTION2);
    const QRay2D RAY3 = QRay2D(ORIGIN3, DIRECTION3);

    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const QVector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const QVector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const QVector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const QVector2 EXPECTED_SECONDPOINT1 = VERTEX_A;
    const QVector2 EXPECTED_SECONDPOINT2 = VERTEX_B;
    const QVector2 EXPECTED_SECONDPOINT3 = VERTEX_C;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// Execution
    QVector2 vFirstIntersection1;
    QVector2 vFirstIntersection2;
    QVector2 vFirstIntersection3;
    QVector2 vSecondIntersection1;
    QVector2 vSecondIntersection2;
    QVector2 vSecondIntersection3;
    EQIntersections eOriginContainedInAB = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eOriginContainedInBC = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EQIntersections eOriginContainedInCA = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);
    
    // Verification
    BOOST_CHECK_EQUAL(eOriginContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eOriginContainedInCA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray coincides with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenRayOriginAndQuadrilateralVertexCoincide_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_A = VERTEX_A;
    const QVector2 DIRECTION_A = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B = VERTEX_B;
    const QVector2 DIRECTION_B = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QVector2 ORIGIN_C = VERTEX_C;
    const QVector2 DIRECTION_C = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_C = QRay2D(ORIGIN_C, DIRECTION_C);

    const QVector2 ORIGIN_D = VERTEX_D;
    const QVector2 DIRECTION_D = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_D = QRay2D(ORIGIN_D, DIRECTION_D);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINT_A = VERTEX_A;
    const QVector2 EXPECTED_POINT_B = VERTEX_B;
    const QVector2 EXPECTED_POINT_C = VERTEX_C;
    const QVector2 EXPECTED_POINT_D = VERTEX_D;

    QVector2 vIntersectionA;
    QVector2 vIntersectionB;
    QVector2 vIntersectionC;
    QVector2 vIntersectionD;

	// Execution
    EQIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vIntersectionA);
    EQIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vIntersectionB);
    EQIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vIntersectionC);
    EQIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vIntersectionD);

    // Verification
    BOOST_CHECK_EQUAL(eResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_D, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
    BOOST_CHECK(vIntersectionD == EXPECTED_POINT_D);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContinuousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_BC = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_BC = QVector2(SQFloat::_2, -SQFloat::_1).Normalize();
    const QRay2D RAY_AB_BC = QRay2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const QVector2 ORIGIN_BC_CD = QVector2(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION_BC_CD = QVector2(-SQFloat::_1, -SQFloat::_2).Normalize();
    const QRay2D RAY_BC_CD = QRay2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const QVector2 ORIGIN_CD_DA = QVector2(SQFloat::_2, -SQFloat::_3);
    const QVector2 DIRECTION_CD_DA = QVector2(-SQFloat::_2, SQFloat::_3).Normalize();
    const QRay2D RAY_CD_DA = QRay2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const QVector2 ORIGIN_DA_AB = QVector2(-SQFloat::_0_5, -SQFloat::_3);
    const QVector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const QRay2D RAY_DA_AB = QRay2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AB_BC = QVector2((float_q)1.5714285714285714, (float_q)1.7142857142857144);
    const QVector2 EXPECTED_POINT_BC_CD = QVector2((float_q)2.3999999999999999, (float_q)0.80000000000000004);
    const QVector2 EXPECTED_POINT_CD_DA = QVector2((float_q)1.0909090909090908, (float_q)-1.6363636363636362);
    const QVector2 EXPECTED_POINT_DA_AB = QVector2((float_q)0.08333333333333337, (float_q)-1.4999999999999998);

    QVector2 vIntersection_AB_BC;
    QVector2 vIntersection_BC_CD;
    QVector2 vIntersection_CD_DA;
    QVector2 vIntersection_DA_AB;

	// Execution
    EQIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vIntersection_AB_BC);
    EQIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vIntersection_BC_CD);
    EQIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vIntersection_CD_DA);
    EQIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vIntersection_DA_AB);
        
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD_DA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersection_BC_CD == EXPECTED_POINT_BC_CD);
    BOOST_CHECK(vIntersection_CD_DA == EXPECTED_POINT_CD_DA);
    BOOST_CHECK(vIntersection_DA_AB == EXPECTED_POINT_DA_AB);
}

/// <summary>
/// Checks that it returns two intersection points when the origin belongs to an edge and the ray intersects with other edge.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenOriginBelongsToAnEdgeAndRayIntersectsWithAnotherEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_BC = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB_BC = (VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN_AB_BC).Normalize();
    const QRay2D RAY_AB_BC = QRay2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const QVector2 ORIGIN_BC_CD = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC_CD = (VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D) - ORIGIN_BC_CD).Normalize();
    const QRay2D RAY_BC_CD = QRay2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const QVector2 ORIGIN_CD_DA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD_DA = (VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A) - ORIGIN_CD_DA).Normalize();
    const QRay2D RAY_CD_DA = QRay2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const QVector2 ORIGIN_DA_AB = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const QRay2D RAY_DA_AB = QRay2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AB_BC = ORIGIN_AB_BC;
    const QVector2 EXPECTED_POINT_BC_CD = ORIGIN_BC_CD;
    const QVector2 EXPECTED_POINT_CD_DA = ORIGIN_CD_DA;
    const QVector2 EXPECTED_POINT_DA_AB = ORIGIN_DA_AB;

    QVector2 vIntersection_AB_BC;
    QVector2 vIntersection_BC_CD;
    QVector2 vIntersection_CD_DA;
    QVector2 vIntersection_DA_AB;

	// Execution
    EQIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vIntersection_AB_BC);
    EQIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vIntersection_BC_CD);
    EQIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vIntersection_CD_DA);
    EQIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vIntersection_DA_AB);
        
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD_DA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersection_BC_CD == EXPECTED_POINT_BC_CD);
    BOOST_CHECK(vIntersection_CD_DA == EXPECTED_POINT_CD_DA);
    BOOST_CHECK(vIntersection_DA_AB == EXPECTED_POINT_DA_AB);
}

/// <summary>
/// Checks that it returns two intersection points when the origin coincides with a vertex and the ray intersects with other edge.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenOriginCoincidesWithAVertexAndRayIntersectsWithAnotherEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_BC = VERTEX_A;
    const QVector2 DIRECTION_AB_BC = (VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN_AB_BC).Normalize();
    const QRay2D RAY_AB_BC = QRay2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const QVector2 ORIGIN_BC_CD = VERTEX_B;
    const QVector2 DIRECTION_BC_CD = (VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D) - ORIGIN_BC_CD).Normalize();
    const QRay2D RAY_BC_CD = QRay2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const QVector2 ORIGIN_CD_DA = VERTEX_C;
    const QVector2 DIRECTION_CD_DA = (VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A) - ORIGIN_CD_DA).Normalize();
    const QRay2D RAY_CD_DA = QRay2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const QVector2 ORIGIN_DA_AB = VERTEX_D;
    const QVector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const QRay2D RAY_DA_AB = QRay2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AB_BC = ORIGIN_AB_BC;
    const QVector2 EXPECTED_POINT_BC_CD = ORIGIN_BC_CD;
    const QVector2 EXPECTED_POINT_CD_DA = ORIGIN_CD_DA;
    const QVector2 EXPECTED_POINT_DA_AB = ORIGIN_DA_AB;

    QVector2 vIntersection_AB_BC;
    QVector2 vIntersection_BC_CD;
    QVector2 vIntersection_CD_DA;
    QVector2 vIntersection_DA_AB;

	// Execution
    EQIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vIntersection_AB_BC);
    EQIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vIntersection_BC_CD);
    EQIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vIntersection_CD_DA);
    EQIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vIntersection_DA_AB);
        
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD_DA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersection_BC_CD == EXPECTED_POINT_BC_CD);
    BOOST_CHECK(vIntersection_CD_DA == EXPECTED_POINT_CD_DA);
    BOOST_CHECK(vIntersection_DA_AB == EXPECTED_POINT_DA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when only the origin of the ray belongs to one of the edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyRayOriginBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 ORIGIN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 ORIGIN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 ORIGIN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINT_AB = ORIGIN_AB;
    const QVector2 EXPECTED_POINT_BC = ORIGIN_BC;
    const QVector2 EXPECTED_POINT_CD = ORIGIN_CD;
    const QVector2 EXPECTED_POINT_DA = ORIGIN_DA;

    QVector2 vIntersection_AB;
    QVector2 vIntersection_BC;
    QVector2 vIntersection_CD;
    QVector2 vIntersection_DA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral, even of it would do if the direction vector was negated.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithQuadrilateralButWouldDoIfDirectionWasOpposite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

    QVector2 vIntersection;

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(QUAD, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionsWhenRayAndQuadrilateralDoesNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

    QVector2 vIntersection;

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(QUAD, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray intersects with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenRayIntersectsWithQuadrilateralVertex_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 DIRECTION_A = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN_A = VERTEX_A - DIRECTION_A;
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 DIRECTION_B = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN_B = VERTEX_B - DIRECTION_B;
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QVector2 DIRECTION_C = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN_C = VERTEX_C - DIRECTION_C;
    const QRay2D RAY_C = QRay2D(ORIGIN_C, DIRECTION_C);

    const QVector2 DIRECTION_D = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QVector2 ORIGIN_D = VERTEX_D - DIRECTION_D;
    const QRay2D RAY_D = QRay2D(ORIGIN_D, DIRECTION_D);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINT_A = VERTEX_A;
    const QVector2 EXPECTED_POINT_B = VERTEX_B;
    const QVector2 EXPECTED_POINT_C = VERTEX_C;
    const QVector2 EXPECTED_POINT_D = VERTEX_D;

    QVector2 vIntersectionA;
    QVector2 vIntersectionB;
    QVector2 vIntersectionC;
    QVector2 vIntersectionD;

	// Execution
    EQIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vIntersectionA);
    EQIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vIntersectionB);
    EQIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vIntersectionC);
    EQIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vIntersectionD);

    // Verification
    BOOST_CHECK_EQUAL(eResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_D, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
    BOOST_CHECK(vIntersectionD == EXPECTED_POINT_D);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is containde by the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenRayOriginIsContainedInQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 EXPECTED_POINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 EXPECTED_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_POINT_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 EXPECTED_POINT_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 ORIGIN = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);

    const QVector2 DIRECTION_AB = (EXPECTED_POINT_AB - ORIGIN).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN, DIRECTION_AB);

    const QVector2 DIRECTION_BC = (EXPECTED_POINT_BC - ORIGIN).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN, DIRECTION_BC);

    const QVector2 DIRECTION_CD = (EXPECTED_POINT_CD - ORIGIN).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN, DIRECTION_CD);

    const QVector2 DIRECTION_DA = (EXPECTED_POINT_DA - ORIGIN).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN, DIRECTION_DA);

    QVector2 vIntersection_AB;
    QVector2 vIntersection_BC;
    QVector2 vIntersection_CD;
    QVector2 vIntersection_DA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoNonContinuousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_CD = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_CD = QVector2(SQFloat::_0, -SQFloat::_1).Normalize();
    const QRay2D RAY_AB_CD = QRay2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const QVector2 ORIGIN_BC_DA = QVector2(SQFloat::_3, SQFloat::_1);
    const QVector2 DIRECTION_BC_DA = QVector2(-SQFloat::_2, -SQFloat::_1).Normalize();
    const QRay2D RAY_BC_DA = QRay2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AB_CD = QVector2(SQFloat::_1, (float_q)1.3333333333333335);
    const QVector2 EXPECTED_POINT_BC_DA = QVector2((float_q)2.4285714285714288, (float_q)0.7142857142857143);

    QVector2 vIntersection_AB_CD;
    QVector2 vIntersection_BC_DA;

	// Execution
    EQIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vIntersection_AB_CD);
    EQIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vIntersection_BC_DA);
        
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_DA, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_CD == EXPECTED_POINT_AB_CD);
    BOOST_CHECK(vIntersection_BC_DA == EXPECTED_POINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayBelongsToQuadrilateralEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 ORIGIN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 ORIGIN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 ORIGIN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const QVector2 EXPECTED_POINT_AB = ORIGIN_AB;
    const QVector2 EXPECTED_POINT_BC = ORIGIN_BC;
    const QVector2 EXPECTED_POINT_CD = ORIGIN_CD;
    const QVector2 EXPECTED_POINT_DA = ORIGIN_DA;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    QVector2 vIntersection_AB;
    QVector2 vIntersection_BC;
    QVector2 vIntersection_CD;
    QVector2 vIntersection_DA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
QTEST_CASE ( IntersectionPoint4_AssertionFailsWhenRayDirectionIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QRay2D NULL_RAY = QRay2D::GetRayZero();

    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const bool ASSERTION_FAILED = true;

    QVector2 vIntersection;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        NULL_RAY.IntersectionPoint(QUAD, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint4_AssertionFailsWhenAllQuadrilateralVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = VERTEX_A;
    const QVector2 VERTEX_C = VERTEX_A;
    const QVector2 VERTEX_D = VERTEX_A;
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = (VERTEX_A - ORIGIN);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

    QVector2 vIntersection;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(QUAD, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it's not necessary to normalize the ray.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ResultIsNotDifferentWhenRayDirectionIsNotNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_CD = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_CD = QVector2(SQFloat::_0, -SQFloat::_1);
    const QRay2D RAY_AB_CD = QRay2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const QVector2 ORIGIN_BC_DA = QVector2(SQFloat::_3, SQFloat::_1);
    const QVector2 DIRECTION_BC_DA = QVector2(-SQFloat::_2, -SQFloat::_1);
    const QRay2D RAY_BC_DA = QRay2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AB_CD = QVector2(SQFloat::_1, (float_q)1.3333333333333335);
    const QVector2 EXPECTED_POINT_BC_DA = QVector2((float_q)2.4285714285714288, (float_q)0.7142857142857143);

    QVector2 vIntersection_AB_CD;
    QVector2 vIntersection_BC_DA;

	// Execution
    EQIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vIntersection_AB_CD);
    EQIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vIntersection_BC_DA);
        
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_DA, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_CD == EXPECTED_POINT_AB_CD);
    BOOST_CHECK(vIntersection_BC_DA == EXPECTED_POINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous vertices.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContiguousVertices_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const QVector2 ORIGIN_AB = VERTEX_A - DIRECTION_AB;
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const QVector2 ORIGIN_BC = VERTEX_B - DIRECTION_BC;
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const QVector2 ORIGIN_CD = VERTEX_C - DIRECTION_CD;
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const QVector2 ORIGIN_DA = VERTEX_D - DIRECTION_DA;
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const QVector2 EXPECTED_POINT_AB = VERTEX_A;
    const QVector2 EXPECTED_POINT_BC = VERTEX_B;
    const QVector2 EXPECTED_POINT_CD = VERTEX_C;
    const QVector2 EXPECTED_POINT_DA = VERTEX_D;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    QVector2 vIntersection_AB;
    QVector2 vIntersection_BC;
    QVector2 vIntersection_CD;
    QVector2 vIntersection_DA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray coincides with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayOriginAndQuadrilateralVertexCoincide_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_A = VERTEX_A;
    const QVector2 DIRECTION_A = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B = VERTEX_B;
    const QVector2 DIRECTION_B = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QVector2 ORIGIN_C = VERTEX_C;
    const QVector2 DIRECTION_C = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_C = QRay2D(ORIGIN_C, DIRECTION_C);

    const QVector2 ORIGIN_D = VERTEX_D;
    const QVector2 DIRECTION_D = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_D = QRay2D(ORIGIN_D, DIRECTION_D);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const QVector2 EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const QVector2 EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const QVector2 EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    QVector2 vFirstIntersectionA, vSecondIntersectionA;
    QVector2 vFirstIntersectionB, vSecondIntersectionB;
    QVector2 vFirstIntersectionC, vSecondIntersectionC;
    QVector2 vFirstIntersectionD, vSecondIntersectionD;

	// Execution
    EQIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vFirstIntersectionA, vSecondIntersectionA);
    EQIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vFirstIntersectionB, vSecondIntersectionB);
    EQIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vFirstIntersectionC, vSecondIntersectionC);
    EQIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vFirstIntersectionD, vSecondIntersectionD);

    // Verification
    BOOST_CHECK_EQUAL(eResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_D, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContinuousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_BC = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_BC = QVector2(SQFloat::_2, -SQFloat::_1).Normalize();
    const QRay2D RAY_AB_BC = QRay2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const QVector2 ORIGIN_BC_CD = QVector2(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION_BC_CD = QVector2(-SQFloat::_1, -SQFloat::_2).Normalize();
    const QRay2D RAY_BC_CD = QRay2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const QVector2 ORIGIN_CD_DA = QVector2(SQFloat::_2, -SQFloat::_3);
    const QVector2 DIRECTION_CD_DA = QVector2(-SQFloat::_2, SQFloat::_3).Normalize();
    const QRay2D RAY_CD_DA = QRay2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const QVector2 ORIGIN_DA_AB = QVector2(-SQFloat::_0_5, -SQFloat::_3);
    const QVector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const QRay2D RAY_DA_AB = QRay2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_FIRSTPOINT_AB_BC = QVector2((float_q)1.5714285714285714, (float_q)1.7142857142857144);
    const QVector2 EXPECTED_FIRSTPOINT_BC_CD = QVector2((float_q)2.3999999999999999, (float_q)0.80000000000000004);
    const QVector2 EXPECTED_FIRSTPOINT_CD_DA = QVector2((float_q)1.0909090909090908, (float_q)-1.6363636363636362);
    const QVector2 EXPECTED_FIRSTPOINT_DA_AB = QVector2((float_q)0.08333333333333337, (float_q)-1.4999999999999998);
    const QVector2 EXPECTED_SECONDPOINT_AB_BC = QVector2((float_q)2.2000000000000002, (float_q)1.3999999999999999);
    const QVector2 EXPECTED_SECONDPOINT_BC_CD = QVector2((float_q)1.2000000000000002, (float_q)-1.5999999999999996);
    const QVector2 EXPECTED_SECONDPOINT_CD_DA = QVector2((float_q)0.26666666666666683, (float_q)-0.40000000000000036);
    const QVector2 EXPECTED_SECONDPOINT_DA_AB = QVector2((float_q)1.2500000000000002, (float_q)1.5000000000000009);

    QVector2 vFirstIntersection_AB_BC, vSecondIntersection_AB_BC;
    QVector2 vFirstIntersection_BC_CD, vSecondIntersection_BC_CD;
    QVector2 vFirstIntersection_CD_DA, vSecondIntersection_CD_DA;
    QVector2 vFirstIntersection_DA_AB, vSecondIntersection_DA_AB;

	// Execution
    EQIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vFirstIntersection_AB_BC, vSecondIntersection_AB_BC);
    EQIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vFirstIntersection_BC_CD, vSecondIntersection_BC_CD);
    EQIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vFirstIntersection_CD_DA, vSecondIntersection_CD_DA);
    EQIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vFirstIntersection_DA_AB, vSecondIntersection_DA_AB);
        
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD_DA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_BC == EXPECTED_FIRSTPOINT_AB_BC);
    BOOST_CHECK(vFirstIntersection_BC_CD == EXPECTED_FIRSTPOINT_BC_CD);
    BOOST_CHECK(vFirstIntersection_CD_DA == EXPECTED_FIRSTPOINT_CD_DA);
    BOOST_CHECK(vFirstIntersection_DA_AB == EXPECTED_FIRSTPOINT_DA_AB);
    BOOST_CHECK(vSecondIntersection_AB_BC == EXPECTED_SECONDPOINT_AB_BC);
    BOOST_CHECK(vSecondIntersection_BC_CD == EXPECTED_SECONDPOINT_BC_CD);
    BOOST_CHECK(vSecondIntersection_CD_DA == EXPECTED_SECONDPOINT_CD_DA);
    BOOST_CHECK(vSecondIntersection_DA_AB == EXPECTED_SECONDPOINT_DA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when only the origin of the ray belongs to one of the edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyRayOriginBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 ORIGIN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 ORIGIN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 ORIGIN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINT_AB = ORIGIN_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BC = ORIGIN_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CD = ORIGIN_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DA = ORIGIN_DA;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    QVector2 vFirstIntersection_AB, vSecondIntersectionAB;
    QVector2 vFirstIntersection_BC, vSecondIntersectionBC;
    QVector2 vFirstIntersection_CD, vSecondIntersectionCD;
    QVector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral, even of it would do if the direction vector was negated.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithQuadrilateralButWouldDoIfDirectionWasOpposite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    QVector2 vFirstIntersection = QVector2::GetZeroVector();
    QVector2 vSecondIntersection = QVector2::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsNoIntersectionsWhenRayAndQuadrilateralDoesNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    QVector2 vFirstIntersection = QVector2::GetZeroVector();
    QVector2 vSecondIntersection = QVector2::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray intersects with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayIntersectsWithQuadrilateralVertex_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 DIRECTION_A = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN_A = VERTEX_A - DIRECTION_A;
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 DIRECTION_B = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN_B = VERTEX_B - DIRECTION_B;
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QVector2 DIRECTION_C = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QVector2 ORIGIN_C = VERTEX_C - DIRECTION_C;
    const QRay2D RAY_C = QRay2D(ORIGIN_C, DIRECTION_C);

    const QVector2 DIRECTION_D = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QVector2 ORIGIN_D = VERTEX_D - DIRECTION_D;
    const QRay2D RAY_D = QRay2D(ORIGIN_D, DIRECTION_D);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const QVector2 EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const QVector2 EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const QVector2 EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    QVector2 vFirstIntersectionA, vSecondIntersectionA;
    QVector2 vFirstIntersectionB, vSecondIntersectionB;
    QVector2 vFirstIntersectionC, vSecondIntersectionC;
    QVector2 vFirstIntersectionD, vSecondIntersectionD;

	// Execution
    EQIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vFirstIntersectionA, vSecondIntersectionA);
    EQIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vFirstIntersectionB, vSecondIntersectionB);
    EQIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vFirstIntersectionC, vSecondIntersectionC);
    EQIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vFirstIntersectionD, vSecondIntersectionD);

    // Verification
    BOOST_CHECK_EQUAL(eResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_D, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is containde by the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayOriginIsContainedInQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_FIRSTPOINT_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 EXPECTED_FIRSTPOINT_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 ORIGIN = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);

    const QVector2 DIRECTION_AB = (EXPECTED_FIRSTPOINT_AB - ORIGIN).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN, DIRECTION_AB);

    const QVector2 DIRECTION_BC = (EXPECTED_FIRSTPOINT_BC - ORIGIN).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN, DIRECTION_BC);

    const QVector2 DIRECTION_CD = (EXPECTED_FIRSTPOINT_CD - ORIGIN).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN, DIRECTION_CD);

    const QVector2 DIRECTION_DA = (EXPECTED_FIRSTPOINT_DA - ORIGIN).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN, DIRECTION_DA);

    QVector2 vFirstIntersection_AB, vSecondIntersectionAB;
    QVector2 vFirstIntersection_BC, vSecondIntersectionBC;
    QVector2 vFirstIntersection_CD, vSecondIntersectionCD;
    QVector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoNonContinuousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_CD = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_CD = QVector2(SQFloat::_0, -SQFloat::_1).Normalize();
    const QRay2D RAY_AB_CD = QRay2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const QVector2 ORIGIN_BC_DA = QVector2(SQFloat::_3, SQFloat::_1);
    const QVector2 DIRECTION_BC_DA = QVector2(-SQFloat::_2, -SQFloat::_1).Normalize();
    const QRay2D RAY_BC_DA = QRay2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_FIRSTPOINT_AB_CD = QVector2(SQFloat::_1, (float_q)1.3333333333333335);
    const QVector2 EXPECTED_FIRSTPOINT_BC_DA = QVector2((float_q)2.4285714285714288, (float_q)0.7142857142857143);
    const QVector2 EXPECTED_SECONDPOINT_AB_CD = QVector2(SQFloat::_1, (float_q)-1.6666666666666665);
    const QVector2 EXPECTED_SECONDPOINT_BC_DA = QVector2((float_q)0.27272727272727249, (float_q)-0.36363636363636376);

    QVector2 vFirstIntersection_AB_CD;
    QVector2 vFirstIntersection_BC_DA;
    QVector2 vSecondIntersection_AB_CD;
    QVector2 vSecondIntersection_BC_DA;

	// Execution
    EQIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vFirstIntersection_AB_CD, vSecondIntersection_AB_CD);
    EQIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vFirstIntersection_BC_DA, vSecondIntersection_BC_DA);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_DA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_CD == EXPECTED_FIRSTPOINT_AB_CD);
    BOOST_CHECK(vFirstIntersection_BC_DA == EXPECTED_FIRSTPOINT_BC_DA);
    BOOST_CHECK(vSecondIntersection_AB_CD == EXPECTED_SECONDPOINT_AB_CD);
    BOOST_CHECK(vSecondIntersection_BC_DA == EXPECTED_SECONDPOINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayBelongsToQuadrilateralEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 ORIGIN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 ORIGIN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 ORIGIN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const QVector2 EXPECTED_FIRSTPOINT_AB = ORIGIN_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BC = ORIGIN_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CD = ORIGIN_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DA = ORIGIN_DA;
    const QVector2 EXPECTED_SECONDPOINT_AB = VERTEX_B;
    const QVector2 EXPECTED_SECONDPOINT_BC = VERTEX_C;
    const QVector2 EXPECTED_SECONDPOINT_CD = VERTEX_D;
    const QVector2 EXPECTED_SECONDPOINT_DA = VERTEX_A;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    QVector2 vFirstIntersection_AB, vSecondIntersectionAB;
    QVector2 vFirstIntersection_BC, vSecondIntersectionBC;
    QVector2 vFirstIntersection_CD, vSecondIntersectionCD;
    QVector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the origin belongs to an edge and the ray intersects with another edge.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenOriginBelongsToAnEdgeAndRayIntersectsWithAnotherEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_BC = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QVector2 DIRECTION_AB_BC = (VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - ORIGIN_AB_BC).Normalize();
    const QRay2D RAY_AB_BC = QRay2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const QVector2 ORIGIN_BC_CD = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 DIRECTION_BC_CD = (VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D) - ORIGIN_BC_CD).Normalize();
    const QRay2D RAY_BC_CD = QRay2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const QVector2 ORIGIN_CD_DA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 DIRECTION_CD_DA = (VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A) - ORIGIN_CD_DA).Normalize();
    const QRay2D RAY_CD_DA = QRay2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const QVector2 ORIGIN_DA_AB = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const QRay2D RAY_DA_AB = QRay2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_FIRSTPOINT_AB_BC = ORIGIN_AB_BC;
    const QVector2 EXPECTED_FIRSTPOINT_BC_CD = ORIGIN_BC_CD;
    const QVector2 EXPECTED_FIRSTPOINT_CD_DA = ORIGIN_CD_DA;
    const QVector2 EXPECTED_FIRSTPOINT_DA_AB = ORIGIN_DA_AB;
    const QVector2 EXPECTED_SECONDPOINT_AB_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QVector2 EXPECTED_SECONDPOINT_BC_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QVector2 EXPECTED_SECONDPOINT_CD_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QVector2 EXPECTED_SECONDPOINT_DA_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);

    QVector2 vFirstIntersection_AB_BC, vSecondIntersection_AB_BC;
    QVector2 vFirstIntersection_BC_CD, vSecondIntersection_BC_CD;
    QVector2 vFirstIntersection_CD_DA, vSecondIntersection_CD_DA;
    QVector2 vFirstIntersection_DA_AB, vSecondIntersection_DA_AB;

	// Execution
    EQIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vFirstIntersection_AB_BC, vSecondIntersection_AB_BC);
    EQIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vFirstIntersection_BC_CD, vSecondIntersection_BC_CD);
    EQIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vFirstIntersection_CD_DA, vSecondIntersection_CD_DA);
    EQIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vFirstIntersection_DA_AB, vSecondIntersection_DA_AB);
        
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD_DA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_BC == EXPECTED_FIRSTPOINT_AB_BC);
    BOOST_CHECK(vFirstIntersection_BC_CD == EXPECTED_FIRSTPOINT_BC_CD);
    BOOST_CHECK(vFirstIntersection_CD_DA == EXPECTED_FIRSTPOINT_CD_DA);
    BOOST_CHECK(vFirstIntersection_DA_AB == EXPECTED_FIRSTPOINT_DA_AB);
    BOOST_CHECK(vSecondIntersection_AB_BC == EXPECTED_SECONDPOINT_AB_BC);
    BOOST_CHECK(vSecondIntersection_BC_CD == EXPECTED_SECONDPOINT_BC_CD);
    BOOST_CHECK(vSecondIntersection_CD_DA == EXPECTED_SECONDPOINT_CD_DA);
    BOOST_CHECK(vSecondIntersection_DA_AB == EXPECTED_SECONDPOINT_DA_AB);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
QTEST_CASE ( IntersectionPoint5_AssertionFailsWhenRayDirectionIsNull )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QRay2D NULL_RAY = QRay2D::GetRayZero();

    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const bool ASSERTION_FAILED = true;

    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        NULL_RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint5_AssertionFailsWhenAllQuadrilateralVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = VERTEX_A;
    const QVector2 VERTEX_C = VERTEX_A;
    const QVector2 VERTEX_D = VERTEX_A;
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = (VERTEX_A - ORIGIN);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it's not necessary to normalize the ray.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ResultIsNotDifferentWhenRayDirectionIsNotNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 ORIGIN_AB_CD = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION_AB_CD = QVector2(SQFloat::_0, -SQFloat::_1);
    const QRay2D RAY_AB_CD = QRay2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const QVector2 ORIGIN_BC_DA = QVector2(SQFloat::_3, SQFloat::_1);
    const QVector2 DIRECTION_BC_DA = QVector2(-SQFloat::_2, -SQFloat::_1);
    const QRay2D RAY_BC_DA = QRay2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_FIRSTPOINT_AB_CD = QVector2(SQFloat::_1, (float_q)1.3333333333333335);
    const QVector2 EXPECTED_FIRSTPOINT_BC_DA = QVector2((float_q)2.4285714285714288, (float_q)0.7142857142857143);
    const QVector2 EXPECTED_SECONDPOINT_AB_CD = QVector2(SQFloat::_1, (float_q)-1.6666666666666665);
    const QVector2 EXPECTED_SECONDPOINT_BC_DA = QVector2((float_q)0.27272727272727293, (float_q)-0.36363636363636354);

    QVector2 vFirstIntersection_AB_CD;
    QVector2 vFirstIntersection_BC_DA;
    QVector2 vSecondIntersection_AB_CD;
    QVector2 vSecondIntersection_BC_DA;

	// Execution
    EQIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vFirstIntersection_AB_CD, vSecondIntersection_AB_CD);
    EQIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vFirstIntersection_BC_DA, vSecondIntersection_BC_DA);
    
    // Verification
    BOOST_CHECK_EQUAL(eResult_AB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC_DA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_CD == EXPECTED_FIRSTPOINT_AB_CD);
    BOOST_CHECK(vFirstIntersection_BC_DA == EXPECTED_FIRSTPOINT_BC_DA);
    BOOST_CHECK(vSecondIntersection_AB_CD == EXPECTED_SECONDPOINT_AB_CD);
    BOOST_CHECK(vSecondIntersection_BC_DA == EXPECTED_SECONDPOINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous vertices.
/// </summary>
QTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContiguousVertices_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VERTEX_A = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 VERTEX_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 VERTEX_C = QVector2(SQFloat::_3, -SQFloat::_1);
    const QVector2 VERTEX_D = QVector2(SQFloat::_0, -SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const QVector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const QVector2 ORIGIN_AB = VERTEX_A - DIRECTION_AB;
    const QRay2D RAY_AB = QRay2D(ORIGIN_AB, DIRECTION_AB);

    const QVector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const QVector2 ORIGIN_BC = VERTEX_B - DIRECTION_BC;
    const QRay2D RAY_BC = QRay2D(ORIGIN_BC, DIRECTION_BC);

    const QVector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const QVector2 ORIGIN_CD = VERTEX_C - DIRECTION_CD;
    const QRay2D RAY_CD = QRay2D(ORIGIN_CD, DIRECTION_CD);

    const QVector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const QVector2 ORIGIN_DA = VERTEX_D - DIRECTION_DA;
    const QRay2D RAY_DA = QRay2D(ORIGIN_DA, DIRECTION_DA);

    const QVector2 EXPECTED_FIRSTPOINT_AB = VERTEX_A;
    const QVector2 EXPECTED_FIRSTPOINT_BC = VERTEX_B;
    const QVector2 EXPECTED_FIRSTPOINT_CD = VERTEX_C;
    const QVector2 EXPECTED_FIRSTPOINT_DA = VERTEX_D;
    const QVector2 EXPECTED_SECONDPOINT_AB = VERTEX_B;
    const QVector2 EXPECTED_SECONDPOINT_BC = VERTEX_C;
    const QVector2 EXPECTED_SECONDPOINT_CD = VERTEX_D;
    const QVector2 EXPECTED_SECONDPOINT_DA = VERTEX_A;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    QVector2 vFirstIntersection_AB, vSecondIntersectionAB;
    QVector2 vFirstIntersection_BC, vSecondIntersectionBC;
    QVector2 vFirstIntersection_CD, vSecondIntersectionCD;
    QVector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// Execution
    EQIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EQIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EQIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EQIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // Verification
    BOOST_CHECK_EQUAL(eResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult_DA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns False when ray and line don't intersect.
/// </summary>
QTEST_CASE ( Intersection4_ReturnsFalseWhenRayAndLineDoNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_4);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = QVector2(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when ray and line intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE ( Intersection4_ReturnsTrueWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when ray and line coincide totally.
/// </summary>
QTEST_CASE ( Intersection4_ReturnsTrueWhenRayAndLineCoincideTotally_Test )
{
    // AO-------->B  (I
    // BO-------->A  (II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, -DIRECTION);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = RAY1.Intersection(LINE_SEGMENT); // I
    bool bResult2 = RAY2.Intersection(LINE_SEGMENT); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray is contained in the line (not including A, and B points in this case).
/// </summary>
QTEST_CASE ( Intersection4_ReturnsTrueWhenOriginIsContainedInTheLine_Test )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_2, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = RAY.Intersection(LINE_SEGMENT); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray's origin and one of the line's endpoints coincide.
/// </summary>
QTEST_CASE ( Intersection4_ReturnsTrueWhenRayAndLineShareOneEndPointOnly_Test )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1  = RAY1.Intersection(LINE_SEGMENT); // I
    bool bResult2  = RAY2.Intersection(LINE_SEGMENT); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray only intersects with a line's endpoint.
/// </summary>
QTEST_CASE ( Intersection4_ReturnsTrueWhenRayOnlyIntersectsWithLineEndpoint_Test )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_6);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_0);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QVector2 DIRECTION2 = QVector2(SQFloat::_2, SQFloat::_6).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION1);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1  = RAY1.Intersection(LINE_SEGMENT); // I
    bool bResult2  = RAY2.Intersection(LINE_SEGMENT); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
QTEST_CASE ( Intersection4_AssertionFailsWhenTheDirectionVectorIsNull_Test )
{
    // A-----O(d2=0)-----B
    //
    //          I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_0, SQFloat::_1);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    
    try
    {
        RAY.Intersection(LINE_SEGMENT); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
QTEST_CASE ( Intersection4_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test )
{
    // O-----AB----->
    //
    //       I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_2, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_A);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    
    try
    {
        RAY.Intersection(LINE_SEGMENT); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
QTEST_CASE ( Intersection4_ReturnsFalseWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
QTEST_CASE ( Intersection4_ReturnsFalseWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_0);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_0).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
QTEST_CASE ( Intersection4_ItIsNotNecessaryToNormalize_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns no intersection points when ray and line don't intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_4);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when ray and line intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);

    const QVector2 ORIGIN(SQFloat::_4, SQFloat::_5);
    const QVector2 DIRECTION = QVector2(EXPECTED_POINT - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when ray and line coincide totally.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsTwoIntersectionsWhenRayAndLineCoincideTotally_Test )
{
    // AO-------->B  (I
    // BO-------->A  (II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_POINT1 = LINE_SEGMENT.A;
    const QVector2 EXPECTED_POINT2 = LINE_SEGMENT.B;

    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, -DIRECTION);

	// Execution
    QVector2 vIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    QVector2 vIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vIntersection2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in the line (not including A, and B points in this case).
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenOriginIsContainedInTheLine_Test )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = ORIGIN;

    // Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when the ray's origin and one of the line's endpoints coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayAndLineShareOneEndPointOnly_Test )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT1 = VALUE_FOR_A;
    const QVector2 EXPECTED_POINT2 = VALUE_FOR_B;

    // Execution
    QVector2 vIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    QVector2 vIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vIntersection2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray only intersects with a line's endpoint.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayOnlyIntersectsWithLineEndpoint_Test )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_6);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_0);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QVector2 DIRECTION2 = QVector2(SQFloat::_2, SQFloat::_6).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION1);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, DIRECTION2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT1 = VALUE_FOR_A;
    const QVector2 EXPECTED_POINT2 = VALUE_FOR_B;

    // Execution
    QVector2 vIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    QVector2 vIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vIntersection2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
QTEST_CASE ( IntersectionPoint6_AssertionFailsWhenTheDirectionVectorIsNull_Test )
{
    // A-----O(d2=0)-----B
    //
    //          I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_0, SQFloat::_1);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QVector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vIntersection); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
QTEST_CASE ( IntersectionPoint6_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test )
{
    // O-----AB----->
    //
    //       I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_2, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_A);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QVector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vIntersection); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

    // Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_0);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_0).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

    // Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
QTEST_CASE ( IntersectionPoint6_ItIsNotNecessaryToNormalize_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);

    const QVector2 ORIGIN(SQFloat::_4, SQFloat::_5);
    const QVector2 DIRECTION = QVector2(EXPECTED_POINT - ORIGIN);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

	// Execution
    QVector2 vIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when ray and line don't intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_4);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_POINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when ray and line intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    const QVector2 ORIGIN(SQFloat::_4, SQFloat::_5);
    const QVector2 DIRECTION = QVector2(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

	// Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when ray and line coincide totally.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsTwoIntersectionsWhenRayAndLineCoincideTotally_Test )
{
    // AO-------->B  (I
    // BO-------->A  (II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_FIRSTPOINT1 = LINE_SEGMENT.A;
    const QVector2 EXPECTED_SECONDPOINT1 = LINE_SEGMENT.B;
    const QVector2 EXPECTED_FIRSTPOINT2 = LINE_SEGMENT.B;
    const QVector2 EXPECTED_SECONDPOINT2 = LINE_SEGMENT.A;

    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, -DIRECTION);

	// Execution
    QVector2 vFirstIntersection1;
    QVector2 vSecondIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    QVector2 vFirstIntersection2;
    QVector2 vSecondIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vFirstIntersection2, vSecondIntersection2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in the line (not including A, and B points in this case).
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenOriginIsContainedInTheLine_Test )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT = ORIGIN;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    // Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection = QVector2::GetZeroVector();
    EQIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection when the ray's origin and one of the line's endpoints coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayAndLineShareOneEndPointOnly_Test )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT1 = VALUE_FOR_A;
    const QVector2 EXPECTED_SECONDPOINT1 = QVector2::GetZeroVector();
    const QVector2 EXPECTED_FIRSTPOINT2 = VALUE_FOR_B;
    const QVector2 EXPECTED_SECONDPOINT2 = QVector2::GetZeroVector();

    // Execution
    QVector2 vFirstIntersection1;
    QVector2 vSecondIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    QVector2 vFirstIntersection2;
    QVector2 vSecondIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vFirstIntersection2, vSecondIntersection2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray only intersects with a line's endpoint.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayOnlyIntersectsWithLineEndpoint_Test )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_6);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_0);
    const QVector2 DIRECTION1 = QVector2(SQFloat::_1, SQFloat::_2).Normalize();
    const QVector2 DIRECTION2 = QVector2(SQFloat::_2, SQFloat::_6).Normalize();
    const QRay2D RAY1 = QRay2D(VALUE_FOR_A, DIRECTION1);
    const QRay2D RAY2 = QRay2D(VALUE_FOR_B, DIRECTION2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT1 = VALUE_FOR_A;
    const QVector2 EXPECTED_SECONDPOINT1 = QVector2::GetZeroVector();
    const QVector2 EXPECTED_FIRSTPOINT2 = VALUE_FOR_B;
    const QVector2 EXPECTED_SECONDPOINT2 = QVector2::GetZeroVector();

    // Execution
    QVector2 vFirstIntersection1;
    QVector2 vSecondIntersection1;
    EQIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    QVector2 vFirstIntersection2;
    QVector2 vSecondIntersection2;
    EQIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vFirstIntersection2, vSecondIntersection2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
QTEST_CASE ( IntersectionPoint7_AssertionFailsWhenTheDirectionVectorIsNull_Test )
{
    // A-----O(d2=0)-----B
    //
    //          I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_0, SQFloat::_1);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
QTEST_CASE ( IntersectionPoint7_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test )
{
    // O-----AB----->
    //
    //       I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_2, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_A);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    // Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult1 = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_0, SQFloat::_0);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_0).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    // Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult1 = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
QTEST_CASE ( IntersectionPoint7_ItIsNotNecessaryToNormalize_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_1);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

    const QVector2 ORIGIN(SQFloat::_4, SQFloat::_5);
    const QVector2 DIRECTION = QVector2(EXPECTED_FIRSTPOINT - ORIGIN);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    // Execution
    QVector2 vFirstIntersection;
    QVector2 vSecondIntersection;
    EQIntersections eResult1 = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns the expected ray when using a common ray and a common line which intersect.
/// </summary>
QTEST_CASE ( Reflection1_ExpectedRayIsReturnedWhenUsingCommonRayAndLine_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 EXPECTED_RAY_ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 EXPECTED_RAY_DIRECTION = QVector2(SQFloat::_1, SQFloat::_0);
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_RAY_ORIGIN, EXPECTED_RAY_DIRECTION);

    const QVector2 ORIGIN(SQFloat::_2, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(EXPECTED_RAY_ORIGIN - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that it returns the opposite ray when the original ray and the line are orthogonal.
/// </summary>
QTEST_CASE ( Reflection1_OppositeRayIsReturnedWhenRayAndLineAreOrthogonal_Test )
{
    //
    //    A
    //    |
    //    |<--->----O
    //    |
    //    B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_RAY_ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 EXPECTED_RAY_DIRECTION = -DIRECTION;
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_RAY_ORIGIN, EXPECTED_RAY_DIRECTION);

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that the ray is reflected when it intersects with an endpoint of the line segment,.
/// </summary>
QTEST_CASE ( Reflection1_RayIsReflectedWhenIntersectsWithLineEndpoint_Test )
{
    //    O
    //    |
    //    |______
    //    A           A
    //     \           \  O
    //      \           \ |
    //       \           \|________
    //        B           B
    //     I            II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 EXPECTED_RAY_ORIGIN_A = VALUE_FOR_A;
    const QVector2 EXPECTED_RAY_DIRECTION_A = QVector2(SQFloat::_1, SQFloat::_0);
    const QRay2D EXPECTED_RAY_A = QRay2D(EXPECTED_RAY_ORIGIN_A, EXPECTED_RAY_DIRECTION_A);

    const QVector2 EXPECTED_RAY_ORIGIN_B = VALUE_FOR_B;
    const QVector2 EXPECTED_RAY_DIRECTION_B = QVector2(SQFloat::_1, SQFloat::_0);
    const QRay2D EXPECTED_RAY_B = QRay2D(EXPECTED_RAY_ORIGIN_B, EXPECTED_RAY_DIRECTION_B);

    const QVector2 ORIGIN_A(SQFloat::_1, SQFloat::_4);
    const QVector2 DIRECTION_A = QVector2(VALUE_FOR_A - ORIGIN_A).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION_B = QVector2(VALUE_FOR_B - ORIGIN_B).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    QRay2D returnedRayA;
    QRay2D returnedRayB;

	// Execution
    RAY_A.Reflection(LINE_SEGMENT, returnedRayA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedRayB); // II

    // Verification
    BOOST_CHECK(returnedRayA.Direction == EXPECTED_RAY_A.Direction);
    BOOST_CHECK(returnedRayA.Origin == EXPECTED_RAY_A.Origin);
    BOOST_CHECK(returnedRayB.Direction == EXPECTED_RAY_B.Direction);
    BOOST_CHECK(returnedRayB.Origin == EXPECTED_RAY_B.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when the origin of this one belongs to the line.
/// </summary>
QTEST_CASE ( Reflection1_RayIsNotReflectedWhenOriginBelongsToLine_Test )
{
    //
    //    A  
    //     \ 
    //      O----->
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QRay2D EXPECTED_RAY = RAY;

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when the origin of this one coincides with tan endpoint of the line.
/// </summary>
QTEST_CASE ( Reflection1_RayIsNotReflectedWhenItsOriginCoincidesWithLineEndpoint_Test )
{
    //
    //    AO---->    A  
    //     \          \
    //      \          \
    //       \          \
    //        B          BO---->
    //     I          II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN_A = VALUE_FOR_A;
    const QVector2 DIRECTION_A = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B = VALUE_FOR_B;
    const QVector2 DIRECTION_B = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QRay2D EXPECTED_RAY_A = RAY_A;
    const QRay2D EXPECTED_RAY_B = RAY_B;

    QRay2D returnedRayA;
    QRay2D returnedRayB;

	// Execution
    RAY_A.Reflection(LINE_SEGMENT, returnedRayA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedRayB); // II

    // Verification
    BOOST_CHECK(returnedRayA.Direction == EXPECTED_RAY_A.Direction);
    BOOST_CHECK(returnedRayA.Origin == EXPECTED_RAY_A.Origin);
    BOOST_CHECK(returnedRayB.Direction == EXPECTED_RAY_B.Direction);
    BOOST_CHECK(returnedRayB.Origin == EXPECTED_RAY_B.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when it belongs to the line.
/// </summary>
QTEST_CASE ( Reflection1_RayIsNotReflectedWhenItBelongsToTheLine_Test )
{
    //
    //    A-------O------>----B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 DIRECTION = (VALUE_FOR_A - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QRay2D EXPECTED_RAY = RAY;

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when it doesn't point to the ling segment (they don't intersect).
/// </summary>
QTEST_CASE ( Reflection1_RayIsNotReflectedWhenItDoesNotPointToLine_Test )
{
    //
    //    A
    //    |   O
    //    |    \
    //    |     \
    //    B      v
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QRay2D EXPECTED_RAY = RAY;

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that the ray is not reflected when the original one intersects with both endpoints of the line..
/// </summary>
QTEST_CASE ( Reflection1_RayIsNotReflectedWhenIntersectsWithBothLineEndpoints_Test )
{
    //
    //   O-------->A------B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QRay2D EXPECTED_RAY = RAY;

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
QTEST_CASE ( Reflection1_AssertionFailsWhenRayIsNull_Test )
{
    // A-----O(d2=0)-----B
    //
    //          I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_0, SQFloat::_1);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QRay2D returnedRay;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedRay); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( Reflection1_AssertionFailsWhenLineEndpointsCoincide_Test )
{
    // O-----AB----->
    //
    //       I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_2, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_A);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QRay2D returnedRay;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedRay); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the resultant ray is not normalized when input ray is not.
/// </summary>
QTEST_CASE ( Reflection1_ResultIsNotNormalizedWhenInputRayIsNotNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B) - ORIGIN; // Not normalized
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    const QRay2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay != NORMALIZED_RESULT);
}

/// <summary>
/// Checks that the resultant ray is normalized when input ray is.
/// </summary>
QTEST_CASE ( Reflection1_ResultIsNormalizedWhenInputRayIsNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    QRay2D returnedRay;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // Verification
    const QRay2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that it returns the expected direction vector when using a common ray and a common line which intersect.
/// </summary>
QTEST_CASE ( Reflection2_ExpectedDirectionIsReturnedWhenUsingCommonRayAndLine_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 EXPECTED_DIRECTION = QVector2(SQFloat::_1, SQFloat::_0);

    const QVector2 ORIGIN(SQFloat::_2, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that it returns the opposite direction when the original ray and the line are orthogonal.
/// </summary>
QTEST_CASE ( Reflection2_OppositeDirectionIsReturnedWhenRayAndLineAreOrthogonal_Test )
{
    //
    //    A
    //    |
    //    |<--->----O
    //    |
    //    B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_DIRECTION = -DIRECTION;

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that the ray is reflected when it intersects with an endpoint of the line segment,.
/// </summary>
QTEST_CASE ( Reflection2_RayIsReflectedWhenIntersectsWithLineEndpoint_Test )
{
    //    O
    //    |
    //    |______
    //    A           A
    //     \           \  O
    //      \           \ |
    //       \           \|________
    //        B           B
    //     I            II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 EXPECTED_DIRECTION_A = QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 EXPECTED_DIRECTION_B = QVector2(SQFloat::_1, SQFloat::_0);

    const QVector2 ORIGIN_A(SQFloat::_1, SQFloat::_4);
    const QVector2 DIRECTION_A = QVector2(VALUE_FOR_A - ORIGIN_A).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B(SQFloat::_3, SQFloat::_2);
    const QVector2 DIRECTION_B = QVector2(VALUE_FOR_B - ORIGIN_B).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    QVector2 returnedDirectionA;
    QVector2 returnedDirectionB;

	// Execution
    RAY_A.Reflection(LINE_SEGMENT, returnedDirectionA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedDirectionB); // II

    // Verification
    BOOST_CHECK(returnedDirectionA == EXPECTED_DIRECTION_A);
    BOOST_CHECK(returnedDirectionB == EXPECTED_DIRECTION_B);
}

/// <summary>
/// Checks that returned direction equals original ray's direction when the origin of this one belongs to the line.
/// </summary>
QTEST_CASE ( Reflection2_RayIsNotReflectedWhenOriginBelongsToLine_Test )
{
    //
    //    A  
    //     \ 
    //      O----->
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_DIRECTION = DIRECTION;

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that returned ray equals original ray when the origin of this one coincides with tan endpoint of the line.
/// </summary>
QTEST_CASE ( Reflection2_RayIsNotReflectedWhenItsOriginCoincidesWithLineEndpoint_Test )
{
    //
    //    AO---->    A  
    //     \          \
    //      \          \
    //       \          \
    //        B          BO---->
    //     I          II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN_A = VALUE_FOR_A;
    const QVector2 DIRECTION_A = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_A = QRay2D(ORIGIN_A, DIRECTION_A);

    const QVector2 ORIGIN_B = VALUE_FOR_B;
    const QVector2 DIRECTION_B = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY_B = QRay2D(ORIGIN_B, DIRECTION_B);

    const QVector2 EXPECTED_DIRECTION_A = DIRECTION_A;
    const QVector2 EXPECTED_DIRECTION_B = DIRECTION_B;

    QVector2 returnedDirectionA;
    QVector2 returnedDirectionB;

	// Execution
    RAY_A.Reflection(LINE_SEGMENT, returnedDirectionA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedDirectionB); // II

    // Verification
    BOOST_CHECK(returnedDirectionA == EXPECTED_DIRECTION_A);
    BOOST_CHECK(returnedDirectionB == EXPECTED_DIRECTION_B);
}

/// <summary>
/// Checks that returned direction vector equals original ray's direction when it belongs to the line.
/// </summary>
QTEST_CASE ( Reflection2_RayIsNotReflectedWhenItBelongsToTheLine_Test )
{
    //
    //    A-------O------>----B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B);
    const QVector2 DIRECTION = (VALUE_FOR_A - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_DIRECTION = DIRECTION;

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that returned ray equals original ray when it doesn't point to the ling segment (they don't intersect).
/// </summary>
QTEST_CASE ( Reflection2_RayIsNotReflectedWhenItDoesNotPointToLine_Test )
{
    //
    //    A
    //    |   O
    //    |    \
    //    |     \
    //    B      v
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_DIRECTION = DIRECTION;

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that the ray is not reflected when the original one intersects with both endpoints of the line..
/// </summary>
QTEST_CASE ( Reflection2_RayIsNotReflectedWhenIntersectsWithBothLineEndpoints_Test )
{
    //
    //   O-------->A------B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_DIRECTION = DIRECTION;

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
QTEST_CASE ( Reflection2_AssertionFailsWhenRayIsNull_Test )
{
    // A-----O(d2=0)-----B
    //
    //          I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_0, SQFloat::_1);
    const QVector2 VALUE_FOR_B(SQFloat::_2, SQFloat::_3);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2::GetZeroVector();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QVector2 returnedDirection;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedDirection); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( Reflection2_AssertionFailsWhenLineEndpointsCoincide_Test )
{
    // O-----AB----->
    //
    //       I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_2, SQFloat::_2);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_A);

    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_1);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// Execution
    bool bAssertionFailed = false;
    QVector2 returnedDirection;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedDirection); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the resultant vector is not normalized when input ray is not.
/// </summary>
QTEST_CASE ( Reflection2_ResultIsNotNormalizedWhenInputRayIsNotNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B) - ORIGIN; // Not normalized
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    const QVector2 NORMALIZED_RESULT = returnedDirection.Normalize();

    BOOST_CHECK(returnedDirection != NORMALIZED_RESULT);
}

/// <summary>
/// Checks that the resultant vector is normalized when input ray is.
/// </summary>
QTEST_CASE ( Reflection2_ResultIsNormalizedWhenInputRayIsNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 VALUE_FOR_B(SQFloat::_3, SQFloat::_0);
    const QBaseLineSegment<QVector2> LINE_SEGMENT = QBaseLineSegment<QVector2>(VALUE_FOR_A, VALUE_FOR_B);

    const QVector2 ORIGIN(SQFloat::_3, SQFloat::_3);
    const QVector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SQFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    QVector2 returnedDirection;

	// Execution
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // Verification
    const QVector2 NORMALIZED_RESULT = returnedDirection.Normalize();

    BOOST_CHECK(returnedDirection == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly transformed.
/// </summary>
QTEST_CASE ( Transform_RayIsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_DIRECTION = QVector2((float_q)-0.24253562503633291, (float_q)0.97014250014533188);
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALATION = QVector2(SQFloat::_2, SQFloat::_0_5);
   
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#else
    const float_q ROTATION = SQAngle::_HalfPi;
#endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

	// Execution
    QRay2D returnedRay = RAY.Transform(TRANSFORMATION_MATRIX);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QRay2D EXPECTED_RAY = RAY;

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

	// Execution
    QRay2D returnedRay = RAY.Transform(TRANSFORMATION);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
QTEST_CASE ( Transform_AssertionFailsWhenMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Transform(TRANSFORMATION);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when implemented
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/*

[TODO] Thund: To be uncommented when the tests for disabled assertions are implemented

/// <summary>
/// Checks that the ray is moved to the coordinate origin and its direction nullified when it's transformed by a zero matrix.
/// </summary>
QTEST_CASE ( Transform_RayIsMovedToCoordinateOriginWhenTransfomedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QRay2D EXPECTED_RAY = QRay2D::GetRayZero();

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

	// Execution
    QRay2D returnedRay = RAY.Transform(TRANSFORMATION);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}
*/
/// <summary>
/// Checks that the resultant ray is normalized.
/// </summary>
QTEST_CASE ( Transform_ResultIsNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALATION = QVector2(SQFloat::_2, SQFloat::_0_5);
   
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

	// Execution
    QRay2D returnedRay = RAY.Transform(TRANSFORMATION_MATRIX);
    
    // Verification
    const QVector2& NORMALIZED_DIRECTION = returnedRay.Direction.Normalize();

    BOOST_CHECK(returnedRay.Direction == NORMALIZED_DIRECTION);
}

/// <summary>
/// Checks that a ray is correctly rotated.
/// </summary>
QTEST_CASE ( Rotate_RayIsCorrectlyRotated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_DIRECTION = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_90;
#else
    const float_q ANGLE = SQAngle::_HalfPi;
#endif

	// Execution
    QRay2D returnedRay = RAY.Rotate(ANGLE);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not rotated when angle is zero.
/// </summary>
QTEST_CASE ( Rotate_RayIsNotRotatedWhenAngleIsZero_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;
    const float_q ANGLE = SQFloat::_0;

	// Execution
    QRay2D returnedRay = RAY.Rotate(ANGLE);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly rotated with pivot point.
/// </summary>
QTEST_CASE ( RotateWithPivot_RayIsCorrectlyRotated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_0, SQFloat::_2);
    const QVector2 EXPECTED_DIRECTION = QVector2(-SQFloat::_1, -SQFloat::_1).Normalize();
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ANGLE = SQAngle::_90;
#else
    const float_q ANGLE = SQAngle::_HalfPi;
#endif

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QRay2D returnedRay = RAY.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not rotated with a pivot when angle is zero.
/// </summary>
QTEST_CASE ( RotateWithPivot_RayIsNotRotatedWhenAngleIsZero_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;
    const float_q ANGLE = SQFloat::_0;

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QRay2D returnedRay = RAY.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly translated.
/// </summary>
QTEST_CASE ( Translate1_RayIsCorrectlyTranslated_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_DIRECTION = DIRECTION;
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_4);

	// Execution
    QRay2D returnedRay = RAY.Translate(TRANSLATION_VECTOR);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not translated when translation is zero.
/// </summary>
QTEST_CASE ( Translate1_RayIsNotTranslatedWhenTranslationIsZero_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;

    const QVector2 TRANSLATION_VECTOR = QVector2::GetZeroVector();

	// Execution
    QRay2D returnedRay = RAY.Translate(TRANSLATION_VECTOR);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly translated.
/// </summary>
QTEST_CASE ( Translate2_RayIsCorrectlyTranslated_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_DIRECTION = DIRECTION;
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const float_q TRANSLATION_VALUE_X = SQFloat::_3;
    const float_q TRANSLATION_VALUE_Y = SQFloat::_4;

	// Execution
    QRay2D returnedRay = RAY.Translate(TRANSLATION_VALUE_X, TRANSLATION_VALUE_Y);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not translated when translation values equal zero.
/// </summary>
QTEST_CASE ( Translate2_RayIsNotTranslatedWhenTranslationIsZero_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;

    const float_q TRANSLATION_VALUE_X = SQFloat::_0;
    const float_q TRANSLATION_VALUE_Y = SQFloat::_0;

	// Execution
    QRay2D returnedRay = RAY.Translate(TRANSLATION_VALUE_X, TRANSLATION_VALUE_Y);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
QTEST_CASE ( Scale1_RayIsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_3).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_2, SQFloat::_6);
    const QVector2 EXPECTED_DIRECTION = QVector2(SQFloat::_4, SQFloat::_9).Normalize();
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_3);

	// Execution
    QRay2D returnedRay = RAY.Scale(SCALING_VECTOR);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
QTEST_CASE ( Scale1_RayIsNotScaledIfScalingValuesEqualOne_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;

    const QVector2 SCALING_VECTOR = QVector2::GetVectorOfOnes();

	// Execution
    QRay2D returnedRay = RAY.Scale(SCALING_VECTOR);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
QTEST_CASE ( Scale1_AssertionFailsWhenScaleVectorIsNull_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 SCALING_VECTOR = QVector2::GetZeroVector();

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Scale(SCALING_VECTOR);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the resultant ray is normalized.
/// </summary>
QTEST_CASE ( Scale1_ResultIsNormalized_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_3);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_3);

	// Execution
    QRay2D returnedRay = RAY.Scale(SCALING_VECTOR);
    
    // Verification
    const QRay2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
QTEST_CASE ( Scale2_RayIsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_3).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_2, SQFloat::_6);
    const QVector2 EXPECTED_DIRECTION = QVector2(SQFloat::_4, SQFloat::_9).Normalize();
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const float_q SCALING_FACTOR_X = SQFloat::_2;
    const float_q SCALING_FACTOR_Y = SQFloat::_3;

	// Execution
    QRay2D returnedRay = RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
QTEST_CASE ( Scale2_RayIsNotScaledIfScalingValuesEqualOne_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;

    const float_q SCALING_FACTOR_X = SQFloat::_1;
    const float_q SCALING_FACTOR_Y = SQFloat::_1;

	// Execution
    QRay2D returnedRay = RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
QTEST_CASE ( Scale2_AssertionFailsWhenScaleVectorIsNull_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const float_q SCALING_FACTOR_X = SQFloat::_0;
    const float_q SCALING_FACTOR_Y = SQFloat::_0;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the resultant ray is normalized.
/// </summary>
QTEST_CASE ( Scale2_ResultIsNormalized_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_3);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const float_q SCALING_FACTOR_X = SQFloat::_2;
    const float_q SCALING_FACTOR_Y = SQFloat::_3;

	// Execution
    QRay2D returnedRay = RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
    
    // Verification
    const QRay2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_RayIsCorrectlyScaleWithPivot_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 EXPECTED_DIRECTION = QVector2((float_q)0.24253562, (float_q)0.97014248).Normalize();
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

	// Execution
    QRay2D returnedRay = RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_RayIsNotScaleWithPivotIfScalingValuesEqualOne_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 SCALING_VECTOR = QVector2::GetVectorOfOnes();

	// Execution
    QRay2D returnedRay = RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_AssertionFailsWhenScaleWithPivotVectorIsNull_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 SCALING_VECTOR = QVector2::GetZeroVector();

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the resultant ray is normalized.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_ResultIsNormalized_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_3);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_3);

	// Execution
    QRay2D returnedRay = RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // Verification
    const QRay2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_RayIsCorrectlyScaleWithPivot_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_4).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 EXPECTED_DIRECTION = QVector2((float_q)0.24253562, (float_q)0.97014248).Normalize();
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const float_q SCALING_FACTOR_X = SQFloat::_2;
    const float_q SCALING_FACTOR_Y = SQFloat::_4;

	// Execution
    QRay2D returnedRay = RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_RayIsNotScaleWithPivotIfScalingValuesEqualOne_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QRay2D EXPECTED_RAY = RAY;

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_4);

    const float_q SCALING_FACTOR_X = SQFloat::_1;
    const float_q SCALING_FACTOR_Y = SQFloat::_1;

	// Execution
    QRay2D returnedRay = RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_AssertionFailsWhenScaleWithPivotVectorIsNull_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_3);
    const QVector2 DIRECTION = QVector2(-SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_4);

    const float_q SCALING_FACTOR_X = SQFloat::_0;
    const float_q SCALING_FACTOR_Y = SQFloat::_0;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the resultant ray is normalized.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_ResultIsNormalized_Test )
{
    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_2, SQFloat::_3);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q SCALING_FACTOR_X = SQFloat::_2;
    const float_q SCALING_FACTOR_Y = SQFloat::_3;

	// Execution
    QRay2D returnedRay = RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
    
    // Verification
    const QRay2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot_RayIsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 EXPECTED_ORIGIN = QVector2(SQFloat::_4, SQFloat::_1);
    const QVector2 EXPECTED_DIRECTION = QVector2((float_q)-0.24253562503633291, (float_q)0.97014250014533188);
    const QRay2D EXPECTED_RAY = QRay2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALATION = QVector2(SQFloat::_2, SQFloat::_0_5);
   
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#else
    const float_q ROTATION = SQAngle::_HalfPi;
#endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_2);

	// Execution
    QRay2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( TransformWithPivot_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QRay2D EXPECTED_RAY = RAY;

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

	const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_2);

	// Execution
    QRay2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
QTEST_CASE ( TransformWithPivot_AssertionFailsWhenMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

	const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_2);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when implemented
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}
/*

[TODO] Thund: To be uncommented when tests for disabled assertions are implemented

/// <summary>
/// Checks that the ray is moved to the coordinate origin and its direction nullified when it's transformed by a zero matrix.
/// </summary>
QTEST_CASE ( TransformWithPivot_RayIsMovedToPivotPointWhenTransfomedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1).Normalize();
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

	const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_2);

    const QRay2D EXPECTED_RAY = QRay2D(PIVOT_POINT, QVector2::GetZeroVector());

	// Execution
    QRay2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // Verification
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

*/
/// <summary>
/// Checks that the resultant ray is normalized.
/// </summary>
QTEST_CASE ( TransformWithPivot_ResultIsNormalized_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 ORIGIN(SQFloat::_1, SQFloat::_2);
    const QVector2 DIRECTION = QVector2(SQFloat::_1, SQFloat::_1);
    const QRay2D RAY = QRay2D(ORIGIN, DIRECTION);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALATION = QVector2(SQFloat::_2, SQFloat::_0_5);
   
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#else
    const float_q ROTATION = SQAngle::_HalfPi;
#endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

	const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_2);

	// Execution
    QRay2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);
    
    // Verification
    const QVector2& NORMALIZED_DIRECTION = returnedRay.Direction.Normalize();

    BOOST_CHECK(returnedRay.Direction == NORMALIZED_DIRECTION);
}

// [TODO] Thund: Protected methods will be tested in the future

// End - Test Suite: QRay2D
QTEST_SUITE_END()
