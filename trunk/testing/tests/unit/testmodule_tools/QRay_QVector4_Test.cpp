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

// !!!
// IMPORTANT NOTE: Whatever the test you modify in this file, replicate the same changes in the QRay_Test.cpp file!
//                 They had to be split because the template has 2 parameters that are not assured to be the same type.
// !!!

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QRay.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QBaseOrb.h"

using Kinesis::QuimeraEngine::Tools::Math::QRay;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QRay_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// Execution
    QRay<T, QVector3> rayUT;

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    QRay<T, QVector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// Execution
    QRay<T, QVector3> rayUT(EXPECTED_RAY);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseRay;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    QBaseRay<T, QVector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// Execution
    QRay<T, QVector3> rayUT(EXPECTED_RAY);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// Execution
    QRay<T, QVector3> rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const T UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const QVector3 UNEXPECTED_VALUE_FOR_DIRECTION = QVector3(INPUT_VALUE_FOR_DIRECTION).Normalize();

	// Execution
    QRay<T, QVector3> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // Verification
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that it returns a null ray placed at the origin.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRayZero_ReturnsWhatExpected_Test, TQTemplateTypes )
{
    // Preparation
    QRay<T, QVector3> EXPECTED_VALUE(T::GetZeroVector(), QVector3::GetZeroVector());

	// Execution
    QRay<T, QVector3> obtinedRay = QRay<T, QVector3>::GetRayZero();

    // Verification
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that a ray is correctly assigned to another ray.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_RayIsAssignedProperlyToAnother_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseRay;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_5 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_6 };
    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const QRay<T, QVector3> OTHER_RAY = QRay<T, QVector3>(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// Execution
    QRay<T, QVector3> rayUT;
    rayUT = OTHER_RAY;

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the correct value is obtained when using a common ray.
/// </summary>
QTEST_CASE_TEMPLATE ( Invert_CorrectValueIsReturnedForACommonRay_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const QRay<T, QVector3> EXPECTED_RAY = QRay<T, QVector3>(RAY.Origin, -RAY.Direction);

	// Execution
    QRay<T, QVector3> invertedRay = RAY.Invert();

    // Verification
    BOOST_CHECK(invertedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(invertedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Invert_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const T UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const QVector3 UNEXPECTED_VALUE_FOR_DIRECTION = -INPUT_VALUE_FOR_DIRECTION.Normalize();

	// Execution
    QRay<T, QVector3> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);
    rayUT = rayUT.Invert();

    // Verification
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the correct value is obtained when using a common ray.
/// </summary>
QTEST_CASE_TEMPLATE ( Normalize_CorrectValueIsReturnedForACommonRay_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const QRay<T, QVector3> EXPECTED_RAY = QRay<T, QVector3>(RAY.Origin, RAY.Direction.Normalize());

	// Execution
    QRay<T, QVector3> normalizedRay = RAY.Normalize();

    // Verification
    BOOST_CHECK(normalizedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(normalizedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the correct point is obtained when using a common distance to the ray's origin.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPoint_ExpectedPointIsReturnedForACommonDistance_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();
    
    const float_q DISTANCE = SQFloat::_5;
    const T EXPECTED_POINT = RAY.Origin + RAY.Direction * DISTANCE;

	// Execution
    T vPoint = RAY.GetPoint(DISTANCE);

    // Verification
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that the obtained point coincides with the origin of the ray when the input distance equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPoint_ObtainedPointCoincidesWithOriginOfRayWhenDistanceEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();
    
    const float_q DISTANCE = SQFloat::_0;
    const T EXPECTED_POINT = RAY.Origin;

	// Execution
    T vPoint = RAY.GetPoint(DISTANCE);

    // Verification
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that the correct point is obtained when using a negative distance to the ray's origin.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPoint_ExpectedPointIsReturnedForANegativeDistance_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();
    
    const float_q DISTANCE = -SQFloat::_5;
    const T EXPECTED_POINT = RAY.Origin + RAY.Direction * DISTANCE;

	// Execution
    T vPoint = RAY.GetPoint(DISTANCE);

    // Verification
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that an assertin fails when the ray is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPoint_AssertionFailsWhenRayIsNotNormalized_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const QRay<T, QVector3> NOT_NORMALIZED_RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    
    const float_q DISTANCE = SQFloat::_5;
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.GetPoint(DISTANCE);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/* Commented out until the tests are adapted to check the results when the assertion behavior is none
/// <summary>
/// Checks that obtained point is different when the ray is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPoint_UnexpectedPointIsReturnedWhenRayIsNotNormalized_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const QRay<T, QVector3> NOT_NORMALIZED_RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const QRay<T, QVector3> NORMALIZED_RAY = NOT_NORMALIZED_RAY.Normalize();
    
    const float_q DISTANCE = SQFloat::_5;

	// Execution
    T vPointWhenNotNormalized = NOT_NORMALIZED_RAY.GetPoint(DISTANCE);
    T vPointWhenNormalized = NORMALIZED_RAY.GetPoint(DISTANCE);

    // Verification
    BOOST_CHECK(vPointWhenNotNormalized != vPointWhenNormalized);
}
*/
/// <summary>
/// Checks that it returns false when there is no intersection.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenRayDoesNotIntersectTheOrb_Test, TQTemplateTypes )
{
    //            ___
    //   \       /   \
    //    \     |  x  |
    //     o     \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray intersects the orb twice.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenRayIntersectsTheOrbTwice_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----|-----|-----
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray's origin lies on the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOriginLiesOnTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //          |  x  o---------
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray's origin is contained in the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOriginIsContainedInTheOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //          |  o-----------
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray is tangent to the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenRayIsTangentToTheOrb_Test, TQTemplateTypes )
{
    //    o-------===------
    //           /   \
    //          |  x  |
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = RAY.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when the ray doesn't intersect the orb but would do if it was inverted.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenRayDoesNotIntersectTheOrbButWouldDoIfInverted_Test, TQTemplateTypes )
{
    //             ___
    //            /   \
    //  <-----o··|·····|··
    //            \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { -SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = RAY.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenRadiusOfTheOrbEqualsZero_Test, TQTemplateTypes )
{
    //
    //  o---------x---->
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_0;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(ORB);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenDirectionVectorIsNull_Test, TQTemplateTypes )
{
    //             ___
    //            /   \
    //        o  |  x  |
    //            \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(ORB);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertin fails when the ray is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenRayIsNotNormalized_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_3, SQFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> NOT_NORMALIZED_RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.Intersection(ORB);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_NoIntersectionPointsAreReturnedWhenRayDoesNotIntersectTheOrb_Test, TQTemplateTypes )
{
    // o            ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_3, SQFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_10, SQFloat::_10, SQFloat::_10, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects the orb twice.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoIntersectionPointsWhenRayIntersectsTheOrbTwice_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----x-----x-----
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin lies on the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenOriginLiesOnTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //          |  x  o---------
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray's origin lies on the surface of the orb and the ray points to the interior of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoPointsWhenOriginLiesOnTheSurfaceOfTheOrbAndTheRayPointsToInteriorOfOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //     -----x-----o
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { -SQFloat::_1, SQFloat::_0, SQFloat::_0 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin is contained in the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenOriginIsContainedInTheOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //          |  o--x---------
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is tangent to the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenRayIsTangentToTheOrb_Test, TQTemplateTypes )
{
    //    o-------===------
    //           /   \
    //          |  x  |
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns zero intersection points when the ray doesn't intersect the orb but would do if it was inverted.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoPointsWhenRayDoesNotIntersectTheOrbButWouldDoIfInverted_Test, TQTemplateTypes )
{
    //             ___
    //            /   \
    //  <-----o··|·····|··
    //            \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { -SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenRadiusOfTheOrbEqualsZero_Test, TQTemplateTypes )
{
    //
    //  o---------x---->
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_0;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT = T::GetZeroVector();
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenDirectionVectorIsNull_Test, TQTemplateTypes )
{
    //             ___
    //            /   \
    //        o  |  x  |
    //            \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION = QVector3::GetZeroVector();
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_0;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT = T::GetZeroVector();
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the ray is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenRayIsNotNormalized_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_3, SQFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> NOT_NORMALIZED_RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT = T::GetZeroVector();
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.IntersectionPoint(ORB, OUTPUT_POINT);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the returned intersection point is the closest one to the origin of the ray.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnedPointIsTheClosestOneToRayOrigin_Test, TQTemplateTypes )
{
    //            ___                     ___
    //           /   \                   /   \
    //    o-----x-----------        ----------x---o
    //           \___/                   \___/
    //
    //             I                       II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_q VECTOR_COMPONENTS_ORIGIN2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION2[] = { -SQFloat::_1, SQFloat::_0, SQFloat::_0};
    const T VALUE_FOR_ORIGIN2(VECTOR_COMPONENTS_ORIGIN2);
    const QVector3 VALUE_FOR_DIRECTION2(VECTOR_COMPONENTS_DIRECTION2);
    const QRay<T, QVector3> RAY2 = QRay<T, QVector3>(VALUE_FOR_ORIGIN2, VALUE_FOR_DIRECTION2.Normalize());

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    float_q VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);

    T OUTPUT_POINT = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    RAY.IntersectionPoint(ORB, OUTPUT_POINT);   // I
    RAY2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // Verification
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_NoIntersectionPointsAreReturnedWhenRayDoesNotIntersectTheOrb_Test, TQTemplateTypes )
{
    // o            ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_3, SQFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_10, SQFloat::_10, SQFloat::_10, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects the orb twice.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoIntersectionPointsWhenRayIntersectsTheOrbTwice_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----x-----x-----
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    float_q VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin lies on the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenOriginLiesOnTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //          |  x  o---------
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns two intersection points when the ray's origin lies on the surface of the orb and the ray points to the interior of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoPointsWhenOriginLiesOnTheSurfaceOfTheOrbAndTheRayPointsToInteriorOfOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //     -----x-----o
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { -SQFloat::_1, SQFloat::_0, SQFloat::_0 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin is contained in the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenOriginIsContainedInTheOrb_Test, TQTemplateTypes )
{
    //            ___
    //           /   \
    //          |  o--x---------
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is tangent to the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenRayIsTangentToTheOrb_Test, TQTemplateTypes )
{
    //    o-------===------
    //           /   \
    //          |  x  |
    //           \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns zero intersection points when the ray doesn't intersect the orb but would do if it was inverted.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoPointsWhenRayDoesNotIntersectTheOrbButWouldDoIfInverted_Test, TQTemplateTypes )
{
    //             ___
    //            /   \
    //  <-----o··|·····|··
    //            \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { -SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenRadiusOfTheOrbEqualsZero_Test, TQTemplateTypes )
{
    //
    //  o---------x---->
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_0;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenDirectionVectorIsNull_Test, TQTemplateTypes )
{
    //             ___
    //            /   \
    //        o  |  x  |
    //            \___/
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION = QVector3::GetZeroVector();
    QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_0;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the ray is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenRayIsNotNormalized_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_3, SQFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> NOT_NORMALIZED_RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_1;
    const QBaseOrb<T> ORB = QBaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be used here when defined
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the first returned intersection point is the closest one to the origin of the ray.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_FirstReturnedPointIsTheClosestOneToRayOrigin_Test, TQTemplateTypes )
{
    //            ___                     ___
    //           /   \                   /   \
    //    o-----1-----2-----        ----2-----1---o
    //           \___/                   \___/
    //
    //             I                       II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_q VECTOR_COMPONENTS_ORIGIN2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION2[] = { -SQFloat::_1, SQFloat::_0, SQFloat::_0};
    const T VALUE_FOR_ORIGIN2(VECTOR_COMPONENTS_ORIGIN2);
    const QVector3 VALUE_FOR_DIRECTION2(VECTOR_COMPONENTS_DIRECTION2);
    const QRay<T, QVector3> RAY2 = QRay<T, QVector3>(VALUE_FOR_ORIGIN2, VALUE_FOR_DIRECTION2.Normalize());

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    float_q VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);

    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT3 = T::GetZeroVector();
    T OUTPUT_POINT4 = T::GetZeroVector();

	// Execution
    RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);   // I
    RAY2.IntersectionPoint(ORB, OUTPUT_POINT3, OUTPUT_POINT4); // II

    // Verification
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const QRay<T, QVector3> RAY = QRay<T, QVector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    const string_q EXPECTED_STRING = QE_L("RY(o(") + VALUE_FOR_ORIGIN.ToString() + QE_L("),d(") + VALUE_FOR_DIRECTION.ToString() + QE_L("))");

	// Execution
    string_q strReturnedString = RAY.ToString();

    // Verification
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: QRay
QTEST_SUITE_END()
