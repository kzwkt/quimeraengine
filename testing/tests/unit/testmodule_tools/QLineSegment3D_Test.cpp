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

#include "QLineSegment3D.h"

#include "QVector3.h"
#include "QVector4.h"
#include "QMatrix4x3.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTranslationMatrix.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QLineSegment3D;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector3, QVector4> TQTemplateTypes;

QTEST_SUITE_BEGIN( QLineSegment3D_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// [Execution]
    QLineSegment3D<T> lineSegmentUT;

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if copy constructor sets segment's points properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const QLineSegment3D<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    QLineSegment3D<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if points are copied cortectly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const QBaseLineSegment<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    QLineSegment3D<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// [Execution]
    QLineSegment3D<T> lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a unit-length line which point A is placed at origin and point B is contained in the positive X axis.
/// </summary>
QTEST_CASE_TEMPLATE ( GetUnitLine_AUnitLengthSegmentPlacedAtOriginAndContainedInPositiveXAxisIsReturned_Test, TQTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetUnitVectorX();

	// [Execution]
    QLineSegment3D<T> lineSegmentUT = QLineSegment3D<T>::GetUnitLine();

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a zero-length line which points A and B are placed at origin.
/// </summary>
QTEST_CASE_TEMPLATE ( GetLineZero_AZeroLengthSegmentPlacedAtOriginIsReturned_Test, TQTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    QLineSegment3D<T> lineSegmentUT = QLineSegment3D<T>::GetLineZero();

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line is correctly assigned to another line.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_LineIsAssignedProperlyToAnother_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const QBaseLineSegment<T> OTHER_LINE = QBaseLineSegment<T>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    QLineSegment3D<T> lineSegmentUT;
    lineSegmentUT = OTHER_LINE;

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns True when a common line segment and a common plane intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenCommonLineSegmentIntersectWithCommonPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, -SQFloat::_6, -SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when line segment and plane are parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenLineSegmentIsParallelToPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_3, SQFloat::_7, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_0, -SQFloat::_4).Normalize();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLineSegmentIsContainedInPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_0, -SQFloat::_4).Normalize();

    // The origin is the point of the plane calculated by multiplying the normal by the distance
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SQFloat::_2, PLANE.b * -PLANE.d + SQFloat::_1, PLANE.c * -PLANE.d, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line segment doesn't intersect with the plane but would do it if the line segment was lengthened.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenLineSegmentDoesNotIntersectWithPlaneButWouldDoIfLineSegmentWasLengthened_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_7, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only an endpoint of the line segment belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenOnlyAnEndpointBelongsToPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d - SQFloat::_1, PLANE.c * -PLANE.d, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT_A = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT_B = QLineSegment3D<T>(POINT_B, POINT_A);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultA = LINE_SEGMENT_A.Intersection(PLANE);
    bool bResultB = LINE_SEGMENT_B.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_AssertionFailsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_AssertionFailsWhenPlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_7, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS_CONTAINED[] = { SQFloat::_0, SQFloat::_4, SQFloat::_0, SQFloat::_1 };
    const float_q POINT_A_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };

    const T POINT_A_CONTAINED(POINT_A_COMPONENTS_CONTAINED);
    const T POINT_A_NOT_CONTAINED(POINT_A_COMPONENTS_NOT_CONTAINED);

    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_A_CONTAINED, POINT_A_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_A_NOT_CONTAINED, POINT_A_NOT_CONTAINED);

    const QPlane PLANE = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_4).Normalize();

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(PLANE);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when a common line segment and a common triangle intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenCommonLineSegmentIntersectsWithCommonTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_6, SQFloat::_0, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common line segment intersect with a vertex of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentIntersectsWithTriangleVertex_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS1[] = { SQFloat::_0, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS1[] = { SQFloat::_2, SQFloat::_0, SQFloat::_1, SQFloat::_1 };
    const T POINT_A1(POINT_A_COMPONENTS1);
    const T POINT_B1(POINT_B_COMPONENTS1);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);

    const float_q POINT_A_COMPONENTS2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS2[] = { SQFloat::_6, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const T POINT_A2(POINT_A_COMPONENTS2);
    const T POINT_B2(POINT_B_COMPONENTS2);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);

    const float_q POINT_A_COMPONENTS3[] = { SQFloat::_4, SQFloat::_3, SQFloat::_0, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS3[] = { SQFloat::_7, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T POINT_A3(POINT_A_COMPONENTS3);
    const T POINT_B3(POINT_B_COMPONENTS3);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithA = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bIntersectsWithB = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bIntersectsWithC = LINE_SEGMENT3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when a common line segment and a common triangle would intersect if the line segment was lengthened enough.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenLineSegmentDoesNotIntersectWithTriangleButWouldDoIfLineSegmentWasLengthenedEnough_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_4, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an endpoint of the line segment is contained in the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenAnEndpointIsContainedInTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A) + (VERTEX_C - VERTEX_B) * SQFloat::_0_5;
    const T POINT_B = POINT_A + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B, POINT_A);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bResult2 = LINE_SEGMENT2.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentBelongsToTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A) + (VERTEX_C - VERTEX_B) * SQFloat::_0_5;
    const T POINT_B = POINT_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an endpoint of the line segment is contained in an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenAnEndpointBelongsToEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B1 = POINT_A1 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B2 = POINT_A2 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B3 = POINT_A3 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointContainedInAB1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bEndpointContainedInAB2 = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bEndpointContainedInAC1 = LINE_SEGMENT3.Intersection(TRIANGLE);
    bool bEndpointContainedInAC2 = LINE_SEGMENT4.Intersection(TRIANGLE);
    bool bEndpointContainedInBC1 = LINE_SEGMENT5.Intersection(TRIANGLE);
    bool bEndpointContainedInBC2 = LINE_SEGMENT6.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentBelongsToEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_C);
    const T POINT_B3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInAB1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bContainedInAB2 = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bContainedInAC1 = LINE_SEGMENT3.Intersection(TRIANGLE);
    bool bContainedInAC2 = LINE_SEGMENT4.Intersection(TRIANGLE);
    bool bContainedInBC1 = LINE_SEGMENT5.Intersection(TRIANGLE);
    bool bContainedInBC2 = LINE_SEGMENT6.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInBC2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment intersects with an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentIntersectsEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B1 = POINT_A1 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B2 = POINT_A2 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B3 = POINT_A3 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithAB = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bIntersectsWithAC = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bIntersectsWithBC = LINE_SEGMENT3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithBC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an endpoint of the line segment and a vertex of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenAnEndpointAndTriangleVertexCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_OTHER_POINT = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_C);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointAAndVertexACoincide1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bEndpointBAndVertexACoincide2 = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bEndpointAAndVertexBCoincide1 = LINE_SEGMENT3.Intersection(TRIANGLE);
    bool bEndpointBAndVertexBCoincide2 = LINE_SEGMENT4.Intersection(TRIANGLE);
    bool bEndpointAAndVertexCCoincide1 = LINE_SEGMENT5.Intersection(TRIANGLE);
    bool bEndpointBAndVertexCCoincide2 = LINE_SEGMENT6.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointAAndVertexACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointBAndVertexACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAAndVertexBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointBAndVertexBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAAndVertexCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointBAndVertexCCoincide2, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheEndpointsCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(TRIANGLE);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_4, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = VERTEX_A;
    const T VERTEX_C = VERTEX_A;

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(TRIANGLE);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsExpectedResultsWhenTheEndpointsCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS_CONTAINED[] = { SQFloat::_2, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const T POINT_A_CONTAINED(POINT_A_COMPONENTS_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_A_CONTAINED, POINT_A_CONTAINED);

    const float_q POINT_A_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const T POINT_A_NOT_CONTAINED(POINT_A_COMPONENTS_NOT_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_A_NOT_CONTAINED, POINT_A_NOT_CONTAINED);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(TRIANGLE);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when a common line segment and a common hexahedron intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenCommonLineSegmentIntersectsWithCommonHexahedron_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_0, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common line segment intersect with a vertex of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentIntersectsWithHexahedronVertex_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_q POINT_A_COMPONENTS_LEFT[] = { SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_LEFT(POINT_A_COMPONENTS_LEFT);

    const float_q POINT_A_COMPONENTS_RIGHT[] = { SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_RIGHT(POINT_A_COMPONENTS_RIGHT);

    const T POINT_B_A = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_A);
    const T POINT_B_B = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_B);
    const T POINT_B_C = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_C);
    const T POINT_B_D = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_D);
    const T POINT_B_E = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_E);
    const T POINT_B_F = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_F);
    const T POINT_B_G = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_G);
    const T POINT_B_H = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_H);

    const QLineSegment3D<T> LINE_SEGMENT_A = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_A);
    const QLineSegment3D<T> LINE_SEGMENT_B = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_B);
    const QLineSegment3D<T> LINE_SEGMENT_C = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_C);
    const QLineSegment3D<T> LINE_SEGMENT_D = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_D);
    const QLineSegment3D<T> LINE_SEGMENT_E = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_E);
    const QLineSegment3D<T> LINE_SEGMENT_F = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_F);
    const QLineSegment3D<T> LINE_SEGMENT_G = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_G);
    const QLineSegment3D<T> LINE_SEGMENT_H = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_H);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithA = LINE_SEGMENT_A.Intersection(HEXAHEDRON);
    bool bIntersectsWithB = LINE_SEGMENT_B.Intersection(HEXAHEDRON);
    bool bIntersectsWithC = LINE_SEGMENT_C.Intersection(HEXAHEDRON);
    bool bIntersectsWithD = LINE_SEGMENT_D.Intersection(HEXAHEDRON);
    bool bIntersectsWithE = LINE_SEGMENT_E.Intersection(HEXAHEDRON);
    bool bIntersectsWithF = LINE_SEGMENT_F.Intersection(HEXAHEDRON);
    bool bIntersectsWithG = LINE_SEGMENT_G.Intersection(HEXAHEDRON);
    bool bIntersectsWithH = LINE_SEGMENT_H.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithH, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when a common line segment and a common hexahedron would intersect if the line segment was lengthened.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsFalseWhenLineSegmentDoesNotIntersectWithHexahedronButWouldDoIfLineSegmentWasLengthened_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_0, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the line segment belongs to a face of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenAnEndpointIsContainedInHexahedronFace_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC + QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE + QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB + QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB + QVector3(SQFloat::_0, SQFloat::_0, -SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD + QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH + QVector3(SQFloat::_0, -SQFloat::_1, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.Intersection(HEXAHEDRON);
    bool bContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.Intersection(HEXAHEDRON);
    bool bContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.Intersection(HEXAHEDRON);
    bool bContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.Intersection(HEXAHEDRON);
    bool bContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.Intersection(HEXAHEDRON);
    bool bContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.Intersection(HEXAHEDRON);
    bool bContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.Intersection(HEXAHEDRON);
    bool bContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.Intersection(HEXAHEDRON);
    bool bContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.Intersection(HEXAHEDRON);
    bool bContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.Intersection(HEXAHEDRON);
    bool bContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.Intersection(HEXAHEDRON);
    bool bContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment belongs to a face of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentBelongsToHexahedronFace_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.Intersection(HEXAHEDRON);
    bool bContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.Intersection(HEXAHEDRON);
    bool bContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.Intersection(HEXAHEDRON);
    bool bContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.Intersection(HEXAHEDRON);
    bool bContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.Intersection(HEXAHEDRON);
    bool bContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.Intersection(HEXAHEDRON);
    bool bContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.Intersection(HEXAHEDRON);
    bool bContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.Intersection(HEXAHEDRON);
    bool bContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.Intersection(HEXAHEDRON);
    bool bContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.Intersection(HEXAHEDRON);
    bool bContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.Intersection(HEXAHEDRON);
    bool bContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of a line segment is contained in the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenOnlyOneEndpointIsContainedInHexahedron_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B = POINT_A + QVector3(SQFloat::_3, -SQFloat::_3, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A, POINT_B);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(HEXAHEDRON);
    bool bResult2 = LINE_SEGMENT2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the line segment is contained in an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenOnlyOneEndpointBelongsToEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_POINT_B_DFGC = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_AEHB = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_ABCD = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_EFGH = QVector3(SQFloat::_0, -SQFloat::_1, SQFloat::_0);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB1 = QLineSegment3D<T>(POINT_A_IN_AB, 
                                                                    POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB2 = QLineSegment3D<T>(POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC1 = QLineSegment3D<T>(POINT_A_IN_BC, 
                                                                    POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC2 = QLineSegment3D<T>(POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD1 = QLineSegment3D<T>(POINT_A_IN_CD, 
                                                                    POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD2 = QLineSegment3D<T>(POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA1 = QLineSegment3D<T>(POINT_A_IN_DA, 
                                                                    POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA2 = QLineSegment3D<T>(POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF1 = QLineSegment3D<T>(POINT_A_IN_EF, 
                                                                    POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF2 = QLineSegment3D<T>(POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG1 = QLineSegment3D<T>(POINT_A_IN_FG, 
                                                                    POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG2 = QLineSegment3D<T>(POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH1 = QLineSegment3D<T>(POINT_A_IN_GH, 
                                                                    POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH2 = QLineSegment3D<T>(POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE1 = QLineSegment3D<T>(POINT_A_IN_HE, 
                                                                    POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE2 = QLineSegment3D<T>(POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF1 = QLineSegment3D<T>(POINT_A_IN_DF, 
                                                                    POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF2 = QLineSegment3D<T>(POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE1 = QLineSegment3D<T>(POINT_A_IN_AE, 
                                                                    POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE2 = QLineSegment3D<T>(POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH1 = QLineSegment3D<T>(POINT_A_IN_BH, 
                                                                    POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH2 = QLineSegment3D<T>(POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG1 = QLineSegment3D<T>(POINT_A_IN_CG, 
                                                                    POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG2 = QLineSegment3D<T>(POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInEF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInEF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInFG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInFG2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInGH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInHE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInHE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCG2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is fully contained in the hexahedron (not touching the surface).
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentIsContainedInHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T POINT_A = VERTEX_A.Lerp(SQFloat::_0_25, VERTEX_G);
    const T POINT_B = VERTEX_G.Lerp(SQFloat::_0_25, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bLineContained = LINE_SEGMENT.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bLineContained, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentBelongsToEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SQFloat::_0_25, VERTEX_B);
    const T POINT_B_IN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB = QLineSegment3D<T>(POINT_A_IN_AB, POINT_B_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_C);
    const T POINT_B_IN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC = QLineSegment3D<T>(POINT_A_IN_BC, POINT_B_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_D);
    const T POINT_B_IN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD = QLineSegment3D<T>(POINT_A_IN_CD, POINT_B_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B_IN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA = QLineSegment3D<T>(POINT_A_IN_DA, POINT_B_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SQFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF = QLineSegment3D<T>(POINT_A_IN_EF, POINT_B_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SQFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG = QLineSegment3D<T>(POINT_A_IN_FG, POINT_B_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SQFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH = QLineSegment3D<T>(POINT_A_IN_GH, POINT_B_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SQFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE = QLineSegment3D<T>(POINT_A_IN_HE, POINT_B_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SQFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF = QLineSegment3D<T>(POINT_A_IN_DF, POINT_B_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SQFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE = QLineSegment3D<T>(POINT_A_IN_AE, POINT_B_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH = QLineSegment3D<T>(POINT_A_IN_BH, POINT_B_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG = QLineSegment3D<T>(POINT_A_IN_CG, POINT_B_IN_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointContainedInAB = LINE_SEGMENT_IN_AB.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBC = LINE_SEGMENT_IN_BC.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCD = LINE_SEGMENT_IN_CD.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDA = LINE_SEGMENT_IN_DA.Intersection(HEXAHEDRON);
    bool bEndpointContainedInEF = LINE_SEGMENT_IN_EF.Intersection(HEXAHEDRON);
    bool bEndpointContainedInFG = LINE_SEGMENT_IN_FG.Intersection(HEXAHEDRON);
    bool bEndpointContainedInGH = LINE_SEGMENT_IN_GH.Intersection(HEXAHEDRON);
    bool bEndpointContainedInHE = LINE_SEGMENT_IN_HE.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDF = LINE_SEGMENT_IN_DF.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAE = LINE_SEGMENT_IN_AE.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBH = LINE_SEGMENT_IN_BH.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCG = LINE_SEGMENT_IN_CG.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment intersects with an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentIntersectsEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_q POINT_A_OVER_COMPONENTS[]  = { (float_q)1.5, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_BELOW_COMPONENTS[] = { (float_q)1.5, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_LEFT_COMPONENTS[]  = { SQFloat::_0, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_RIGHT_COMPONENTS[] = { SQFloat::_3, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_OVER  = T(POINT_A_OVER_COMPONENTS);  // For edges of face ABCD
    const T POINT_A_BELOW = T(POINT_A_BELOW_COMPONENTS); // For edges of face EFGH
    const T POINT_A_LEFT  = T(POINT_A_LEFT_COMPONENTS);  // For edges of face ADFE
    const T POINT_A_RIGHT = T(POINT_A_RIGHT_COMPONENTS); // For edges of face CGHB

    const T POINT_B_TO_AB = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B));
    const QLineSegment3D<T> LINE_SEGMENT_TO_AB = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_AB);

    const T POINT_B_TO_BC = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C));
    const QLineSegment3D<T> LINE_SEGMENT_TO_BC = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_BC);

    const T POINT_B_TO_CD = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D));
    const QLineSegment3D<T> LINE_SEGMENT_TO_CD = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_CD);

    const T POINT_B_TO_DA = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A));
    const QLineSegment3D<T> LINE_SEGMENT_TO_DA = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_DA);

    const T POINT_B_TO_EF = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F));
    const QLineSegment3D<T> LINE_SEGMENT_TO_EF = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_EF);

    const T POINT_B_TO_FG = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G));;
    const QLineSegment3D<T> LINE_SEGMENT_TO_FG = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_FG);

    const T POINT_B_TO_GH = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H));
    const QLineSegment3D<T> LINE_SEGMENT_TO_GH = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_GH);

    const T POINT_B_TO_HE = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E));
    const QLineSegment3D<T> LINE_SEGMENT_TO_HE = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_HE);

    const T POINT_B_TO_DF = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F));
    const QLineSegment3D<T> LINE_SEGMENT_TO_DF = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_DF);

    const T POINT_B_TO_AE = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E));
    const QLineSegment3D<T> LINE_SEGMENT_TO_AE = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_AE);

    const T POINT_B_TO_BH = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H));
    const QLineSegment3D<T> LINE_SEGMENT_TO_BH = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_BH);

    const T POINT_B_TO_CG = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G));
    const QLineSegment3D<T> LINE_SEGMENT_TO_CG = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithAB = LINE_SEGMENT_TO_AB.Intersection(HEXAHEDRON);
    bool bIntersectsWithBC = LINE_SEGMENT_TO_BC.Intersection(HEXAHEDRON);
    bool bIntersectsWithCD = LINE_SEGMENT_TO_CD.Intersection(HEXAHEDRON);
    bool bIntersectsWithDA = LINE_SEGMENT_TO_DA.Intersection(HEXAHEDRON);
    bool bIntersectsWithEF = LINE_SEGMENT_TO_EF.Intersection(HEXAHEDRON);
    bool bIntersectsWithFG = LINE_SEGMENT_TO_FG.Intersection(HEXAHEDRON);
    bool bIntersectsWithGH = LINE_SEGMENT_TO_GH.Intersection(HEXAHEDRON);
    bool bIntersectsWithHE = LINE_SEGMENT_TO_HE.Intersection(HEXAHEDRON);
    bool bIntersectsWithDF = LINE_SEGMENT_TO_DF.Intersection(HEXAHEDRON);
    bool bIntersectsWithAE = LINE_SEGMENT_TO_AE.Intersection(HEXAHEDRON);
    bool bIntersectsWithBH = LINE_SEGMENT_TO_BH.Intersection(HEXAHEDRON);
    bool bIntersectsWithCG = LINE_SEGMENT_TO_CG.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithCG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an endopoint of the line segment and a vertex of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenEndpointAndHexahedronVertexCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_POINT_B_DFGC = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_AEHB = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QLineSegment3D<T> LINE_SEGMENT_FROM_A1 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_A2 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_B1 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_B2 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_C1 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_C2 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_D1 = QLineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_D2 = QLineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_E1 = QLineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_E2 = QLineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_F1 = QLineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_F2 = QLineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_G1 = QLineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_G2 = QLineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_H1 = QLineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_H2 = QLineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointAndACoincide1 = LINE_SEGMENT_FROM_A1.Intersection(HEXAHEDRON);
    bool bEndpointAndACoincide2 = LINE_SEGMENT_FROM_A2.Intersection(HEXAHEDRON);
    bool bEndpointAndBCoincide1 = LINE_SEGMENT_FROM_B1.Intersection(HEXAHEDRON);
    bool bEndpointAndBCoincide2 = LINE_SEGMENT_FROM_B2.Intersection(HEXAHEDRON);
    bool bEndpointAndCCoincide1 = LINE_SEGMENT_FROM_C1.Intersection(HEXAHEDRON);
    bool bEndpointAndCCoincide2 = LINE_SEGMENT_FROM_C2.Intersection(HEXAHEDRON);
    bool bEndpointAndDCoincide1 = LINE_SEGMENT_FROM_D1.Intersection(HEXAHEDRON);
    bool bEndpointAndDCoincide2 = LINE_SEGMENT_FROM_D2.Intersection(HEXAHEDRON);
    bool bEndpointAndECoincide1 = LINE_SEGMENT_FROM_E1.Intersection(HEXAHEDRON);
    bool bEndpointAndECoincide2 = LINE_SEGMENT_FROM_E2.Intersection(HEXAHEDRON);
    bool bEndpointAndFCoincide1 = LINE_SEGMENT_FROM_F1.Intersection(HEXAHEDRON);
    bool bEndpointAndFCoincide2 = LINE_SEGMENT_FROM_F2.Intersection(HEXAHEDRON);
    bool bEndpointAndGCoincide1 = LINE_SEGMENT_FROM_G1.Intersection(HEXAHEDRON);
    bool bEndpointAndGCoincide2 = LINE_SEGMENT_FROM_G2.Intersection(HEXAHEDRON);
    bool bEndpointAndHCoincide1 = LINE_SEGMENT_FROM_H1.Intersection(HEXAHEDRON);
    bool bEndpointAndHCoincide2 = LINE_SEGMENT_FROM_H2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointAndACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndCCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndDCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndDCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndECoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndECoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndFCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndFCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndGCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndGCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndHCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndHCoincide2, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_AssertionFailsWhenLineSegmentEndpointsCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(HEXAHEDRON);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(HEXAHEDRON);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection3_ReturnsExpectedResultsWhenLineSegmentEndpointsCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS_CONTAINED[] = { (float_q)1.5, (float_q)1.5, SQFloat::_1, SQFloat::_1 };
    const T POINT_A_CONTAINED(POINT_A_COMPONENTS_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_A_CONTAINED, POINT_A_CONTAINED);

    const float_q POINT_A_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_5, SQFloat::_1, SQFloat::_1 };
    const T POINT_A_NOT_CONTAINED(POINT_A_COMPONENTS_NOT_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_A_NOT_CONTAINED, POINT_A_NOT_CONTAINED);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(HEXAHEDRON);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when a common line segment and a common plane intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenCommonLineSegmentIntersectWithCommonPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { -SQFloat::_7, -SQFloat::_8, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();

    const float_q EXPECTED_COMPONENTS[] = { (float_q)-5.2000000000000011, (float_q)-5.9000000000000004, SQFloat::_7, SQFloat::_1 };
    const T EXPECTED_POINT = T(EXPECTED_COMPONENTS);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersection;
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when line segment is plane are parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoInterserctionsWhenLineSegmentIsParallelToPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_3, SQFloat::_7, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_0, -SQFloat::_4).Normalize();

    const T EXPECTED_POINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line segment is contained in the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsInfiniteIntersectionsWhenLineSegmentIsContainedInPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_0, -SQFloat::_4).Normalize();

    // The origin is the point of the plane calculated by multiplying the normal by the distance
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SQFloat::_2, PLANE.b * -PLANE.d + SQFloat::_1, PLANE.c * -PLANE.d, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const T EXPECTED_POINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the line segment doesn't intersect with the plane but would do it if the line segment was lengthened.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithPlaneButWouldDoIfLineSegmentWasLengthened_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_7, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();

    const T EXPECTED_POINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when only an endpoint of the line segment belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyAnEndpointBelongsToPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d - SQFloat::_1, PLANE.c * -PLANE.d, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT_A = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT_B = QLineSegment3D<T>(POINT_B, POINT_A);

    const T EXPECTED_POINT_A = LINE_SEGMENT_A.A;
    const T EXPECTED_POINT_B = LINE_SEGMENT_B.B;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionA;
    T vIntersectionB;
    EQIntersections bResultA = LINE_SEGMENT_A.IntersectionPoint(PLANE, vIntersectionA);
    EQIntersections bResultB = LINE_SEGMENT_B.IntersectionPoint(PLANE, vIntersectionB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, -SQFloat::_4).Normalize();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenPlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_7, SQFloat::_7, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QPlane PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_COMPONENTS_CONTAINED[] = { SQFloat::_1, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q POINT_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const QPlane PLANE = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_4).Normalize();

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_Infinite;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = EQIntersections::E_None;

    const T EXPECTED_POINT = T::GetNullVector();

	// [Execution]
    T vIntersectionContained = T::GetNullVector();
    T vIntersectionNotContained = T::GetNullVector();

    const EQIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(PLANE, vIntersectionContained);
    const EQIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(PLANE, vIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained == EXPECTED_POINT);
    BOOST_CHECK(vIntersectionNotContained == EXPECTED_POINT);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when a common line segment and a common triangle intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenCommonLineSegmentIntersectsWithCommonTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B).Lerp(SQFloat::_0_5, VERTEX_C);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B = POINT_A.Lerp(SQFloat::_2, EXPECTED_POINT);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

	// [Execution]
    T vIntersection;
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenLineSegmentIntersectsWithTriangleVertex_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS1[] = { SQFloat::_0, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS1[] = { SQFloat::_2, SQFloat::_0, SQFloat::_1, SQFloat::_1 };
    const T POINT_A1(POINT_A_COMPONENTS1);
    const T POINT_B1(POINT_B_COMPONENTS1);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);

    const float_q POINT_A_COMPONENTS2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS2[] = { SQFloat::_6, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const T POINT_A2(POINT_A_COMPONENTS2);
    const T POINT_B2(POINT_B_COMPONENTS2);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);

    const float_q POINT_A_COMPONENTS3[] = { SQFloat::_4, SQFloat::_3, SQFloat::_0, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS3[] = { SQFloat::_7, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T POINT_A3(POINT_A_COMPONENTS3);
    const T POINT_B3(POINT_B_COMPONENTS3);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_A = VERTEX_A;
    const T EXPECTED_POINT_B = VERTEX_B;
    const T EXPECTED_POINT_C = VERTEX_C;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionA;
    T vIntersectionB;
    T vIntersectionC;
    EQIntersections eIntersectionsWithA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionA);
    EQIntersections eIntersectionsWithB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionB);
    EQIntersections eIntersectionsWithC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionC);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectionsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectionsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectionsWithC, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
}

/// <summary>
/// Checks that it returns no intersections when a common line segment and a common triangle would intersect if the line segment was lengthened enough.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithTriangleButWouldDoIfLineSegmentWasLengthenedEnough_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_4, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

	// [Execution]
    T vIntersection;
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment is contained in the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointIsContainedInTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A).Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B, POINT_A);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = POINT_A;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionA;
    T vIntersectionB;
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionA);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionB);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line segment is contained in the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsInfiniteIntersectionsWhenLineSegmentBelongsToTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A).Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const T EXPECTED_POINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B1 = POINT_A1 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B2 = POINT_A2 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B3 = POINT_A3 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const T EXPECTED_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionAB1;
    T vIntersectionAB2;
    T vIntersectionAC1;
    T vIntersectionAC2;
    T vIntersectionBC1;
    T vIntersectionBC2;
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAB2);
    EQIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionAC1);
    EQIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionAC2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionBC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionBC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB1 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAB2 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAC1 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionAC2 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionBC1 == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersectionBC2 == EXPECTED_POINT_BC);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangleAndTheOtherEndpointIsInsideTheTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T CENTER_POINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B).Lerp(SQFloat::_0_5, VERTEX_C);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B1 = CENTER_POINT;
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B2 = CENTER_POINT;
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B3 = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const T EXPECTED_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionAB1;
    T vIntersectionAB2;
    T vIntersectionAC1;
    T vIntersectionAC2;
    T vIntersectionBC1;
    T vIntersectionBC2;
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAB2);
    EQIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionAC1);
    EQIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionAC2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionBC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionBC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB1 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAB2 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAC1 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionAC2 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionBC1 == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersectionBC2 == EXPECTED_POINT_BC);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_C);
    const T POINT_B3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB1 = LINE_SEGMENT1.A;
    const T EXPECTED_POINT_AB2 = LINE_SEGMENT2.A;
    const T EXPECTED_POINT_AC1 = LINE_SEGMENT3.A;
    const T EXPECTED_POINT_AC2 = LINE_SEGMENT4.A;
    const T EXPECTED_POINT_BC1 = LINE_SEGMENT5.A;
    const T EXPECTED_POINT_BC2 = LINE_SEGMENT6.A;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vIntersectionAB1;
    T vIntersectionAB2;
    T vIntersectionAC1;
    T vIntersectionAC2;
    T vIntersectionBC1;
    T vIntersectionBC2;
    EQIntersections eContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB1);
    EQIntersections eContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAB2);
    EQIntersections eContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionAC1);
    EQIntersections eContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionAC2);
    EQIntersections eContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionBC1);
    EQIntersections eContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionBC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vIntersectionAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vIntersectionAC1 == EXPECTED_POINT_AC1);
    BOOST_CHECK(vIntersectionAC2 == EXPECTED_POINT_AC2);
    BOOST_CHECK(vIntersectionBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vIntersectionBC2 == EXPECTED_POINT_BC2);
}

/// <summary>
/// Checks that it returns one intersection point when the line segment intersects with an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B1 = POINT_A1 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B2 = POINT_A2 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B3 = POINT_A3 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T EXPECTED_POINT_AC = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionAB;
    T vIntersectionAC;
    T vIntersectionBC;
    EQIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB);
    EQIntersections eIntersectsWithAC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAC);
    EQIntersections eIntersectsWithBC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionBC);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAC == EXPECTED_POINT_AC);
    BOOST_CHECK(vIntersectionBC == EXPECTED_POINT_BC);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment and a vertex of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointAndTriangleVertexCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_OTHER_POINT = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_C);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_A = VERTEX_A;
    const T EXPECTED_POINT_B = VERTEX_B;
    const T EXPECTED_POINT_C = VERTEX_C;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionA1;
    T vIntersectionA2;
    T vIntersectionB1;
    T vIntersectionB2;
    T vIntersectionC1;
    T vIntersectionC2;
    EQIntersections eEndpointAAndVertexACoincide1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionA1);
    EQIntersections eEndpointBAndVertexACoincide2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionA2);
    EQIntersections eEndpointAAndVertexBCoincide1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionB1);
    EQIntersections eEndpointBAndVertexBCoincide2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionB2);
    EQIntersections eEndpointAAndVertexCCoincide1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionC1);
    EQIntersections eEndpointBAndVertexCCoincide2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointAAndVertexACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointBAndVertexACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAAndVertexBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointBAndVertexBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAAndVertexCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointBAndVertexCCoincide2, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA1 == VERTEX_A);
    BOOST_CHECK(vIntersectionA2 == VERTEX_A);
    BOOST_CHECK(vIntersectionB1 == VERTEX_B);
    BOOST_CHECK(vIntersectionB2 == VERTEX_B);
    BOOST_CHECK(vIntersectionC1 == VERTEX_C);
    BOOST_CHECK(vIntersectionC2 == VERTEX_C);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment intersects with two edges of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineSegmentIntersectsWithTwoEdgesOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);

    const T POINT_A1 = MID_POINT_AB.Lerp(-SQFloat::_2, MID_POINT_BC);
    const T POINT_B1 = MID_POINT_AB.Lerp(SQFloat::_2, MID_POINT_BC);
    const T POINT_A2 = MID_POINT_BC.Lerp(-SQFloat::_2, MID_POINT_CA);
    const T POINT_B2 = MID_POINT_BC.Lerp(SQFloat::_2, MID_POINT_CA);
    const T POINT_A3 = MID_POINT_CA.Lerp(-SQFloat::_2, MID_POINT_AB);
    const T POINT_B3 = MID_POINT_CA.Lerp(SQFloat::_2, MID_POINT_AB);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB_BC = MID_POINT_AB;
    const T EXPECTED_POINT_BC_CA = MID_POINT_BC;
    const T EXPECTED_POINT_CA_AB = MID_POINT_CA;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vIntersectionAB_BC;
    T vIntersectionBC_CA;
    T vIntersectionCA_AB;
    EQIntersections eIntersectsWithAB_BC = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB_BC);
    EQIntersections eIntersectsWithBC_CA = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionBC_CA);
    EQIntersections eIntersectsWithCA_AB = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionCA_AB);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC_CA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersectionBC_CA == EXPECTED_POINT_BC_CA);
    BOOST_CHECK(vIntersectionCA_AB == EXPECTED_POINT_CA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment belongs to the triangle and the line intersects with an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenEndpointBelongsToTriangleAndLineIntersectsEdge_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T INNER_POINT = MID_POINT_AB.Lerp(SQFloat::_0_5, MID_POINT_BC).Lerp(SQFloat::_0_5, MID_POINT_CA);

    const T POINT_A1 = INNER_POINT;
    const T POINT_B1 = INNER_POINT.Lerp(SQFloat::_2, MID_POINT_AB);
    const T POINT_A2 = INNER_POINT;
    const T POINT_B2 = INNER_POINT.Lerp(SQFloat::_2, MID_POINT_BC);
    const T POINT_A3 = INNER_POINT;
    const T POINT_B3 = INNER_POINT.Lerp(SQFloat::_2, MID_POINT_CA);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = MID_POINT_AB;
    const T EXPECTED_POINT_BC = MID_POINT_BC;
    const T EXPECTED_POINT_CA = MID_POINT_CA;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vIntersectionAB;
    T vIntersectionBC;
    T vIntersectionCA;
    EQIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB);
    EQIntersections eIntersectsWithBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionBC);
    EQIntersections eIntersectsWithCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionCA);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCA, EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersectionCA == EXPECTED_POINT_CA);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenTheEndpointsCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_4, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = VERTEX_A;
    const T VERTEX_C = VERTEX_A;

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_COMPONENTS_CONTAINED[] = { SQFloat::_3, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q POINT_COMPONENTS_IN_EDGE[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EDGE = QLineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_q POINT_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_Infinite;
    const EQIntersections EXPECTED_RESULT_IN_EDGE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = EQIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vIntersectionContained = T::GetNullVector();
    T vIntersectionInEdge = T::GetNullVector();
    T vIntersectionNotContained = T::GetNullVector();

    const EQIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(TRIANGLE, vIntersectionContained);
    const EQIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(TRIANGLE, vIntersectionInEdge);
    const EQIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(TRIANGLE, vIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultInEdge, EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when a common line segment and a common triangle intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenCommonLineSegmentIntersectsWithCommonTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B).Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B = POINT_A.Lerp(SQFloat::_2, EXPECTED_FIRSTPOINT);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection = T::GetNullVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenLineSegmentIntersectsWithTriangleVertex_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS1[] = { SQFloat::_0, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS1[] = { SQFloat::_2, SQFloat::_0, SQFloat::_1, SQFloat::_1 };
    const T POINT_A1(POINT_A_COMPONENTS1);
    const T POINT_B1(POINT_B_COMPONENTS1);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);

    const float_q POINT_A_COMPONENTS2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS2[] = { SQFloat::_6, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const T POINT_A2(POINT_A_COMPONENTS2);
    const T POINT_B2(POINT_B_COMPONENTS2);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);

    const float_q POINT_A_COMPONENTS3[] = { SQFloat::_4, SQFloat::_3, SQFloat::_0, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS3[] = { SQFloat::_7, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T POINT_A3(POINT_A_COMPONENTS3);
    const T POINT_B3(POINT_B_COMPONENTS3);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vSecondIntersectionA = T::GetNullVector();
    T vSecondIntersectionB = T::GetNullVector();
    T vSecondIntersectionC = T::GetNullVector();
    EQIntersections eIntersectionsWithA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionA, vSecondIntersectionA);
    EQIntersections eIntersectionsWithB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionB, vSecondIntersectionB);
    EQIntersections eIntersectionsWithC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionC, vSecondIntersectionC);

    // [Verification]
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
/// Checks that it returns no intersections when a common line segment and a common triangle would intersect if the line segment was lengthened enough.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithTriangleButWouldDoIfLineSegmentWasLengthenedEnough_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_4, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = T::GetNullVector();
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

	// [Execution]
    T vFirstIntersection = T::GetNullVector();
    T vSecondIntersection = T::GetNullVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment is contained in the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointIsContainedInTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A).Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B, POINT_A);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = POINT_A;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vSecondIntersectionA = T::GetNullVector();
    T vSecondIntersectionB = T::GetNullVector();
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionA, vSecondIntersectionA);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionB, vSecondIntersectionB);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line segment is contained in the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsInfiniteIntersectionsWhenLineSegmentBelongsToTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A).Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const T EXPECTED_POINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;

	// [Execution]
    T vFirstIntersection = T::GetNullVector();
    T vSecondIntersection = T::GetNullVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_POINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B1 = POINT_A1 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B2 = POINT_A2 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B3 = POINT_A3 + QVector3(SQFloat::_4, SQFloat::_4, SQFloat::_4);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1;
    T vFirstIntersectionAB2;
    T vFirstIntersectionAC1;
    T vFirstIntersectionAC2;
    T vFirstIntersectionBC1;
    T vFirstIntersectionBC2;
    T vSecondIntersectionAB1 = T::GetNullVector();
    T vSecondIntersectionAB2 = T::GetNullVector();
    T vSecondIntersectionAC1 = T::GetNullVector();
    T vSecondIntersectionAC2 = T::GetNullVector();
    T vSecondIntersectionBC1 = T::GetNullVector();
    T vSecondIntersectionBC2 = T::GetNullVector();
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EQIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC1, vSecondIntersectionAC1);
    EQIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC2, vSecondIntersectionAC2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionBC2, vSecondIntersectionBC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAC1 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionAC2 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangleAndTheOtherEndpointIsInsideTheTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T CENTER_POINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B).Lerp(SQFloat::_0_5, VERTEX_C);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B1 = CENTER_POINT;
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B2 = CENTER_POINT;
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B3 = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1;
    T vFirstIntersectionAB2;
    T vFirstIntersectionAC1;
    T vFirstIntersectionAC2;
    T vFirstIntersectionBC1;
    T vFirstIntersectionBC2;
    T vSecondIntersectionAB1 = T::GetNullVector();
    T vSecondIntersectionAB2 = T::GetNullVector();
    T vSecondIntersectionAC1 = T::GetNullVector();
    T vSecondIntersectionAC2 = T::GetNullVector();
    T vSecondIntersectionBC1 = T::GetNullVector();
    T vSecondIntersectionBC2 = T::GetNullVector();
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EQIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC1, vSecondIntersectionAC1);
    EQIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC2, vSecondIntersectionAC2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionBC2, vSecondIntersectionBC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAC1 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionAC2 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersections when the endpoints of the segment belong to different edges of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenEndpointsBelongToDifferentEdgesOfTheTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B1 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_B);
    const T POINT_A3 = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const T POINT_B3 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB_AC1 = LINE_SEGMENT1.A;
    const T EXPECTED_FIRSTPOINT_AB_AC2 = LINE_SEGMENT2.A;
    const T EXPECTED_FIRSTPOINT_AC_BC1 = LINE_SEGMENT3.A;
    const T EXPECTED_FIRSTPOINT_AC_BC2 = LINE_SEGMENT4.A;
    const T EXPECTED_FIRSTPOINT_AB_BC1 = LINE_SEGMENT5.A;
    const T EXPECTED_FIRSTPOINT_AB_BC2 = LINE_SEGMENT6.A;
    const T EXPECTED_SECONDPOINT_AB_AC1 = LINE_SEGMENT1.B;
    const T EXPECTED_SECONDPOINT_AB_AC2 = LINE_SEGMENT2.B;
    const T EXPECTED_SECONDPOINT_AC_BC1 = LINE_SEGMENT3.B;
    const T EXPECTED_SECONDPOINT_AC_BC2 = LINE_SEGMENT4.B;
    const T EXPECTED_SECONDPOINT_AB_BC1 = LINE_SEGMENT5.B;
    const T EXPECTED_SECONDPOINT_AB_BC2 = LINE_SEGMENT6.B;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB_AC1;
    T vFirstIntersectionAB_AC2;
    T vFirstIntersectionAC_BC1;
    T vFirstIntersectionAC_BC2;
    T vFirstIntersectionAB_BC1;
    T vFirstIntersectionAB_BC2;
    T vSecondIntersectionAB_AC1 = T::GetNullVector();
    T vSecondIntersectionAB_AC2 = T::GetNullVector();
    T vSecondIntersectionAC_BC1 = T::GetNullVector();
    T vSecondIntersectionAC_BC2 = T::GetNullVector();
    T vSecondIntersectionAB_BC1 = T::GetNullVector();
    T vSecondIntersectionAB_BC2 = T::GetNullVector();
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_AC1, vSecondIntersectionAB_AC1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_AC2, vSecondIntersectionAB_AC2);
    EQIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC_BC1, vSecondIntersectionAC_BC1);
    EQIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC_BC2, vSecondIntersectionAC_BC2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_BC1, vSecondIntersectionAB_BC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_BC2, vSecondIntersectionAB_BC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB_AC1 == EXPECTED_FIRSTPOINT_AB_AC1);
    BOOST_CHECK(vFirstIntersectionAB_AC2 == EXPECTED_FIRSTPOINT_AB_AC2);
    BOOST_CHECK(vFirstIntersectionAC_BC1 == EXPECTED_FIRSTPOINT_AC_BC1);
    BOOST_CHECK(vFirstIntersectionAC_BC2 == EXPECTED_FIRSTPOINT_AC_BC2);
    BOOST_CHECK(vFirstIntersectionAB_BC1 == EXPECTED_FIRSTPOINT_AB_BC1);
    BOOST_CHECK(vFirstIntersectionAB_BC2 == EXPECTED_FIRSTPOINT_AB_BC2);
    BOOST_CHECK(vSecondIntersectionAB_AC1 == EXPECTED_SECONDPOINT_AB_AC1);
    BOOST_CHECK(vSecondIntersectionAB_AC2 == EXPECTED_SECONDPOINT_AB_AC2);
    BOOST_CHECK(vSecondIntersectionAC_BC1 == EXPECTED_SECONDPOINT_AC_BC1);
    BOOST_CHECK(vSecondIntersectionAC_BC2 == EXPECTED_SECONDPOINT_AC_BC2);
    BOOST_CHECK(vSecondIntersectionAB_BC1 == EXPECTED_SECONDPOINT_AB_BC1);
    BOOST_CHECK(vSecondIntersectionAB_BC2 == EXPECTED_SECONDPOINT_AB_BC2);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_C);
    const T POINT_B3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_B1, POINT_A1);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(POINT_B2, POINT_A2);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(POINT_A3, POINT_B3);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(POINT_B3, POINT_A3);

    const T EXPECTED_FIRSTPOINT_AB1 = LINE_SEGMENT1.A;
    const T EXPECTED_FIRSTPOINT_AB2 = LINE_SEGMENT2.A;
    const T EXPECTED_FIRSTPOINT_AC1 = LINE_SEGMENT3.A;
    const T EXPECTED_FIRSTPOINT_AC2 = LINE_SEGMENT4.A;
    const T EXPECTED_FIRSTPOINT_BC1 = LINE_SEGMENT5.A;
    const T EXPECTED_FIRSTPOINT_BC2 = LINE_SEGMENT6.A;
    const T EXPECTED_SECONDPOINT_AB1 = LINE_SEGMENT1.B;
    const T EXPECTED_SECONDPOINT_AB2 = LINE_SEGMENT2.B;
    const T EXPECTED_SECONDPOINT_AC1 = LINE_SEGMENT3.B;
    const T EXPECTED_SECONDPOINT_AC2 = LINE_SEGMENT4.B;
    const T EXPECTED_SECONDPOINT_BC1 = LINE_SEGMENT5.B;
    const T EXPECTED_SECONDPOINT_BC2 = LINE_SEGMENT6.B;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB1 = T::GetNullVector();
    T vFirstIntersectionAB2 = T::GetNullVector();
    T vFirstIntersectionAC1 = T::GetNullVector();
    T vFirstIntersectionAC2 = T::GetNullVector();
    T vFirstIntersectionBC1 = T::GetNullVector();
    T vFirstIntersectionBC2 = T::GetNullVector();
    T vSecondIntersectionAB1 = T::GetNullVector();
    T vSecondIntersectionAB2 = T::GetNullVector();
    T vSecondIntersectionAC1 = T::GetNullVector();
    T vSecondIntersectionAC2 = T::GetNullVector();
    T vSecondIntersectionBC1 = T::GetNullVector();
    T vSecondIntersectionBC2 = T::GetNullVector();
    EQIntersections eContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EQIntersections eContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EQIntersections eContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC1, vSecondIntersectionAC1);
    EQIntersections eContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC2, vSecondIntersectionAC2);
    EQIntersections eContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EQIntersections eContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionBC2, vSecondIntersectionBC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstIntersectionAC1 == EXPECTED_FIRSTPOINT_AC1);
    BOOST_CHECK(vFirstIntersectionAC2 == EXPECTED_FIRSTPOINT_AC2);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT_AB1);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT_AB2);
    BOOST_CHECK(vSecondIntersectionAC1 == EXPECTED_SECONDPOINT_AC1);
    BOOST_CHECK(vSecondIntersectionAC2 == EXPECTED_SECONDPOINT_AC2);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT_BC1);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT_BC2);
}

/// <summary>
/// Checks that it returns one intersection point when the line segment intersects with an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B1 = POINT_A1 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const T POINT_A2 = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B2 = POINT_A2 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const T POINT_A3 = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C) - QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const T POINT_B3 = POINT_A3 + QVector3(SQFloat::_2, SQFloat::_2, SQFloat::_2);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T EXPECTED_FIRSTPOINT_AC = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionAC;
    T vFirstIntersectionBC;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionAC = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    EQIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB, vSecondIntersectionAB);
    EQIntersections eIntersectsWithAC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAC, vSecondIntersectionAC);
    EQIntersections eIntersectsWithBC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionBC, vSecondIntersectionBC);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAC == EXPECTED_FIRSTPOINT_AC);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment and a vertex of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointAndTriangleVertexCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_OTHER_POINT = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT4 = QLineSegment3D<T>(VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT5 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT6 = QLineSegment3D<T>(VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_C);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA1;
    T vFirstIntersectionA2;
    T vFirstIntersectionB1;
    T vFirstIntersectionB2;
    T vFirstIntersectionC1;
    T vFirstIntersectionC2;
    T vSecondIntersectionA1 = T::GetNullVector();
    T vSecondIntersectionA2 = T::GetNullVector();
    T vSecondIntersectionB1 = T::GetNullVector();
    T vSecondIntersectionB2 = T::GetNullVector();
    T vSecondIntersectionC1 = T::GetNullVector();
    T vSecondIntersectionC2 = T::GetNullVector();
    EQIntersections eEndpointAAndVertexACoincide1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionA1, vSecondIntersectionA1);
    EQIntersections eEndpointBAndVertexACoincide2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionA2, vSecondIntersectionA2);
    EQIntersections eEndpointAAndVertexBCoincide1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionB1, vSecondIntersectionB1);
    EQIntersections eEndpointBAndVertexBCoincide2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionB2, vSecondIntersectionB2);
    EQIntersections eEndpointAAndVertexCCoincide1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionC1, vSecondIntersectionC1);
    EQIntersections eEndpointBAndVertexCCoincide2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionC2, vSecondIntersectionC2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointAAndVertexACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointBAndVertexACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAAndVertexBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointBAndVertexBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAAndVertexCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointBAndVertexCCoincide2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA1 == VERTEX_A);
    BOOST_CHECK(vFirstIntersectionA2 == VERTEX_A);
    BOOST_CHECK(vFirstIntersectionB1 == VERTEX_B);
    BOOST_CHECK(vFirstIntersectionB2 == VERTEX_B);
    BOOST_CHECK(vFirstIntersectionC1 == VERTEX_C);
    BOOST_CHECK(vFirstIntersectionC2 == VERTEX_C);
    BOOST_CHECK(vSecondIntersectionA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment intersects with two edges of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineSegmentIntersectsWithTwoEdgesOfTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);

    const T POINT_A1 = MID_POINT_AB.Lerp(-SQFloat::_2, MID_POINT_BC);
    const T POINT_B1 = MID_POINT_AB.Lerp(SQFloat::_2, MID_POINT_BC);
    const T POINT_A2 = MID_POINT_BC.Lerp(-SQFloat::_2, MID_POINT_CA);
    const T POINT_B2 = MID_POINT_BC.Lerp(SQFloat::_2, MID_POINT_CA);
    const T POINT_A3 = MID_POINT_CA.Lerp(-SQFloat::_2, MID_POINT_AB);
    const T POINT_B3 = MID_POINT_CA.Lerp(SQFloat::_2, MID_POINT_AB);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB_BC = MID_POINT_AB;
    const T EXPECTED_FIRSTPOINT_BC_CA = MID_POINT_BC;
    const T EXPECTED_FIRSTPOINT_CA_AB = MID_POINT_CA;
    const T EXPECTED_SECONDPOINT_AB_BC = MID_POINT_BC;
    const T EXPECTED_SECONDPOINT_BC_CA = MID_POINT_CA;
    const T EXPECTED_SECONDPOINT_CA_AB = MID_POINT_AB;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB_BC;
    T vFirstIntersectionBC_CA;
    T vFirstIntersectionCA_AB;
    T vSecondIntersectionAB_BC;
    T vSecondIntersectionBC_CA;
    T vSecondIntersectionCA_AB;
    EQIntersections eIntersectsWithAB_BC = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_BC, vSecondIntersectionAB_BC);
    EQIntersections eIntersectsWithBC_CA = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionBC_CA, vSecondIntersectionBC_CA);
    EQIntersections eIntersectsWithCA_AB = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionCA_AB, vSecondIntersectionCA_AB);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC_CA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB_BC == EXPECTED_FIRSTPOINT_AB_BC);
    BOOST_CHECK(vFirstIntersectionBC_CA == EXPECTED_FIRSTPOINT_BC_CA);
    BOOST_CHECK(vFirstIntersectionCA_AB == EXPECTED_FIRSTPOINT_CA_AB);
    BOOST_CHECK(vSecondIntersectionAB_BC == EXPECTED_SECONDPOINT_AB_BC);
    BOOST_CHECK(vSecondIntersectionBC_CA == EXPECTED_SECONDPOINT_BC_CA);
    BOOST_CHECK(vSecondIntersectionCA_AB == EXPECTED_SECONDPOINT_CA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment belongs to the triangle and the line intersects with an edge of the triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenEndpointBelongsToTriangleAndLineIntersectsEdge_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_A);
    const T INNER_POINT = MID_POINT_AB.Lerp(SQFloat::_0_5, MID_POINT_BC).Lerp(SQFloat::_0_5, MID_POINT_CA);

    const T POINT_A1 = INNER_POINT;
    const T POINT_B1 = INNER_POINT.Lerp(SQFloat::_2, MID_POINT_AB);
    const T POINT_A2 = INNER_POINT;
    const T POINT_B2 = INNER_POINT.Lerp(SQFloat::_2, MID_POINT_BC);
    const T POINT_A3 = INNER_POINT;
    const T POINT_B3 = INNER_POINT.Lerp(SQFloat::_2, MID_POINT_CA);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A1, POINT_B1);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A2, POINT_B2);
    const QLineSegment3D<T> LINE_SEGMENT3 = QLineSegment3D<T>(POINT_A3, POINT_B3);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = MID_POINT_AB;
    const T EXPECTED_FIRSTPOINT_BC = MID_POINT_BC;
    const T EXPECTED_FIRSTPOINT_CA = MID_POINT_CA;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCA;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    T vSecondIntersectionCA = T::GetNullVector();
    EQIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB, vSecondIntersectionAB);
    EQIntersections eIntersectsWithBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionBC, vSecondIntersectionBC);
    EQIntersections eIntersectsWithCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionCA, vSecondIntersectionCA);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCA == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCA == EXPECTED_SECONDPOINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheEndpointsCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_4, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = VERTEX_A;
    const T VERTEX_C = VERTEX_A;

    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_COMPONENTS_CONTAINED[] = { SQFloat::_3, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q POINT_COMPONENTS_IN_EDGE[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EDGE = QLineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_q POINT_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_5, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const QBaseTriangle<T> TRIANGLE = QBaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_Infinite;
    const EQIntersections EXPECTED_RESULT_IN_EDGE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = EQIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionContained = T::GetNullVector();
    T vFirstIntersectionInEdge = T::GetNullVector();
    T vFirstIntersectionNotContained = T::GetNullVector();
    T vSecondIntersectionContained = T::GetNullVector();
    T vSecondIntersectionInEdge = T::GetNullVector();
    T vSecondIntersectionNotContained = T::GetNullVector();

    const EQIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(TRIANGLE, vFirstIntersectionContained, vSecondIntersectionContained);
    const EQIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(TRIANGLE, vFirstIntersectionInEdge, vSecondIntersectionInEdge);
    const EQIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(TRIANGLE, vFirstIntersectionNotContained, vSecondIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultInEdge, EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vFirstIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vSecondIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns two intersection points when a common line segment and a common hexahedron intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenCommonLineSegmentIntersectsWithCommonHexahedron_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_0, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const float_q POINT_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(POINT_COMPONENTS);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vIntersection;
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenLineSegmentIntersectsWithHexahedronVertex_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_q POINT_A_COMPONENTS_LEFT[] = { SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_LEFT(POINT_A_COMPONENTS_LEFT);

    const float_q POINT_A_COMPONENTS_RIGHT[] = { SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_RIGHT(POINT_A_COMPONENTS_RIGHT);

    const T POINT_B_A = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_A);
    const T POINT_B_B = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_B);
    const T POINT_B_C = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_C);
    const T POINT_B_D = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_D);
    const T POINT_B_E = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_E);
    const T POINT_B_F = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_F);
    const T POINT_B_G = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_G);
    const T POINT_B_H = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_H);

    const QLineSegment3D<T> LINE_SEGMENT_A = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_A);
    const QLineSegment3D<T> LINE_SEGMENT_B = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_B);
    const QLineSegment3D<T> LINE_SEGMENT_C = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_C);
    const QLineSegment3D<T> LINE_SEGMENT_D = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_D);
    const QLineSegment3D<T> LINE_SEGMENT_E = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_E);
    const QLineSegment3D<T> LINE_SEGMENT_F = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_F);
    const QLineSegment3D<T> LINE_SEGMENT_G = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_G);
    const QLineSegment3D<T> LINE_SEGMENT_H = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_H);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;

	// [Execution]
    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;
    EQIntersections eIntersectsWithA = LINE_SEGMENT_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA);
    EQIntersections eIntersectsWithB = LINE_SEGMENT_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB);
    EQIntersections eIntersectsWithC = LINE_SEGMENT_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC);
    EQIntersections eIntersectsWithD = LINE_SEGMENT_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD);
    EQIntersections eIntersectsWithE = LINE_SEGMENT_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE);
    EQIntersections eIntersectsWithF = LINE_SEGMENT_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF);
    EQIntersections eIntersectsWithG = LINE_SEGMENT_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG);
    EQIntersections eIntersectsWithH = LINE_SEGMENT_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithH, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
}

/// <summary>
/// Checks that it returns no intersection points when a common line segment and a common hexahedron would intersect if the line segment was lengthened.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithHexahedronButWouldDoIfLineSegmentWasLengthened_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_0, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

    T vFirstIntersection = T::GetNullVector();

	// [Execution]
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment belongs to a face of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenAnEndpointIsContainedInHexahedronFace_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC + QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE + QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB + QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB + QVector3(SQFloat::_0, SQFloat::_0, -SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD + QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH + QVector3(SQFloat::_0, -SQFloat::_1, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = POINT_A_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = POINT_A_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = POINT_A_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = POINT_A_EFGH;

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    EQIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1);
    EQIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2);
    EQIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1);
    EQIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2);
    EQIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1);
    EQIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2);
    EQIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1);
    EQIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2);
    EQIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1);
    EQIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2);
    EQIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1);
    EQIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment belongs to a face of the hexahedron and the other endpoint is inside the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenAnEndpointIsContainedInHexahedronFaceAndTheOtherEndpointIsInsideTheHexahedron_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T CENTER_POINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_G);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = QLineSegment3D<T>(POINT_B_DFGC, POINT_A_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = QLineSegment3D<T>(POINT_B_ADFE, POINT_A_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = QLineSegment3D<T>(POINT_B_AEHB, POINT_A_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = QLineSegment3D<T>(POINT_B_CGHB, POINT_A_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = QLineSegment3D<T>(POINT_B_ABCD, POINT_A_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = CENTER_POINT;
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = QLineSegment3D<T>(POINT_B_EFGH, POINT_A_EFGH);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = POINT_A_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = POINT_A_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = POINT_A_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = POINT_A_EFGH;

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    EQIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1);
    EQIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2);
    EQIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1);
    EQIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2);
    EQIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1);
    EQIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2);
    EQIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1);
    EQIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2);
    EQIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1);
    EQIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2);
    EQIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1);
    EQIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH);
}

/// <summary>
/// Checks that it returns two intersection points when the endpoints of the line segment belongs to different faces of the hexahedron and the other endpoint is inside the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenEndpointsAreContainedInDifferentHexahedronFaces_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_ABHE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC_ABHE1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_ABHE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC_ABHE2 = QLineSegment3D<T>(POINT_B_ABHE, POINT_A_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_BCHG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE_BCHG1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_BCHG);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE_BCHG2 = QLineSegment3D<T>(POINT_B_BCHG, POINT_A_ADFE);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH_ABCD1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH_ABCD2 = QLineSegment3D<T>(POINT_B_ABCD, POINT_A_EFGH);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT_DFGC_ABHE1 = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_DFGC_ABHE2 = POINT_B_ABHE;
    const T EXPECTED_FIRSTPOINT_ADFE_BCHG1 = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_ADFE_BCHG2 = POINT_B_BCHG;
    const T EXPECTED_FIRSTPOINT_EFGH_ABCD1 = POINT_A_EFGH;
    const T EXPECTED_FIRSTPOINT_EFGH_ABCD2 = POINT_B_ABCD;

	// [Execution]
    T vFirstIntersectionDFGC_ABHE1 = T::GetNullVector();
    T vFirstIntersectionDFGC_ABHE2 = T::GetNullVector();
    T vFirstIntersectionADFE_BCHG1 = T::GetNullVector();
    T vFirstIntersectionADFE_BCHG2 = T::GetNullVector();
    T vFirstIntersectionEFGH_ABCD1 = T::GetNullVector();
    T vFirstIntersectionEFGH_ABCD2 = T::GetNullVector();

    EQIntersections eContainedInDFGC_ABHE1 = LINE_SEGMENT_IN_DFGC_ABHE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC_ABHE1);
    EQIntersections eContainedInDFGC_ABHE2 = LINE_SEGMENT_IN_DFGC_ABHE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC_ABHE2);
    EQIntersections eContainedInADFE_BCHG1 = LINE_SEGMENT_IN_ADFE_BCHG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE_BCHG1);
    EQIntersections eContainedInADFE_BCHG2 = LINE_SEGMENT_IN_ADFE_BCHG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE_BCHG2);
    EQIntersections eContainedInEFGH_ABCD1 = LINE_SEGMENT_IN_EFGH_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH_ABCD1);
    EQIntersections eContainedInEFGH_ABCD2 = LINE_SEGMENT_IN_EFGH_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH_ABCD2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInDFGC_ABHE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInDFGC_ABHE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE_BCHG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE_BCHG2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH_ABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH_ABCD2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC_ABHE1 == EXPECTED_FIRSTPOINT_DFGC_ABHE1);
    BOOST_CHECK(vFirstIntersectionDFGC_ABHE2 == EXPECTED_FIRSTPOINT_DFGC_ABHE2);
    BOOST_CHECK(vFirstIntersectionADFE_BCHG1 == EXPECTED_FIRSTPOINT_ADFE_BCHG1);
    BOOST_CHECK(vFirstIntersectionADFE_BCHG2 == EXPECTED_FIRSTPOINT_ADFE_BCHG2);
    BOOST_CHECK(vFirstIntersectionEFGH_ABCD1 == EXPECTED_FIRSTPOINT_EFGH_ABCD1);
    BOOST_CHECK(vFirstIntersectionEFGH_ABCD2 == EXPECTED_FIRSTPOINT_EFGH_ABCD2);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment belongs to a face of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineSegmentBelongsToHexahedronFace_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT_DFGC1 = LINE_SEGMENT_IN_DFGC1.A;
    const T EXPECTED_FIRSTPOINT_DFGC2 = LINE_SEGMENT_IN_DFGC2.A;
    const T EXPECTED_FIRSTPOINT_ADFE1 = LINE_SEGMENT_IN_ADFE1.A;
    const T EXPECTED_FIRSTPOINT_ADFE2 = LINE_SEGMENT_IN_ADFE2.A;
    const T EXPECTED_FIRSTPOINT_AEHB1 = LINE_SEGMENT_IN_AEHB1.A;
    const T EXPECTED_FIRSTPOINT_AEHB2 = LINE_SEGMENT_IN_AEHB2.A;
    const T EXPECTED_FIRSTPOINT_CGHB1 = LINE_SEGMENT_IN_CGHB1.A;
    const T EXPECTED_FIRSTPOINT_CGHB2 = LINE_SEGMENT_IN_CGHB2.A;
    const T EXPECTED_FIRSTPOINT_ABCD1 = LINE_SEGMENT_IN_ABCD1.A;
    const T EXPECTED_FIRSTPOINT_ABCD2 = LINE_SEGMENT_IN_ABCD2.A;
    const T EXPECTED_FIRSTPOINT_EFGH1 = LINE_SEGMENT_IN_EFGH1.A;
    const T EXPECTED_FIRSTPOINT_EFGH2 = LINE_SEGMENT_IN_EFGH2.A;

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    EQIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1);
    EQIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2);
    EQIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1);
    EQIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2);
    EQIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1);
    EQIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2);
    EQIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1);
    EQIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2);
    EQIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1);
    EQIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2);
    EQIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1);
    EQIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC1);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC2);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE1);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE2);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB1);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB2);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB1);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB2);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD1);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD2);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH1);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH2);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of a line segment is contained in the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndpointIsContainedInHexahedron_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_D);

    const T POINT_A = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B = POINT_A.Lerp(SQFloat::_2, EXPECTED_FIRSTPOINT);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A, POINT_B);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(HEXAHEDRON, vFirstIntersection1);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(HEXAHEDRON, vFirstIntersection2);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment is contained in an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndpointBelongsToEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_POINT_B_DFGC = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_AEHB = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_ABCD = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_EFGH = QVector3(SQFloat::_0, -SQFloat::_1, SQFloat::_0);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB1 = QLineSegment3D<T>(POINT_A_IN_AB, 
                                                                    POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB2 = QLineSegment3D<T>(POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC1 = QLineSegment3D<T>(POINT_A_IN_BC, 
                                                                    POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC2 = QLineSegment3D<T>(POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD1 = QLineSegment3D<T>(POINT_A_IN_CD, 
                                                                    POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD2 = QLineSegment3D<T>(POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA1 = QLineSegment3D<T>(POINT_A_IN_DA, 
                                                                    POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA2 = QLineSegment3D<T>(POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF1 = QLineSegment3D<T>(POINT_A_IN_EF, 
                                                                    POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF2 = QLineSegment3D<T>(POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG1 = QLineSegment3D<T>(POINT_A_IN_FG, 
                                                                    POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG2 = QLineSegment3D<T>(POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH1 = QLineSegment3D<T>(POINT_A_IN_GH, 
                                                                    POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH2 = QLineSegment3D<T>(POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE1 = QLineSegment3D<T>(POINT_A_IN_HE, 
                                                                    POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE2 = QLineSegment3D<T>(POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF1 = QLineSegment3D<T>(POINT_A_IN_DF, 
                                                                    POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF2 = QLineSegment3D<T>(POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE1 = QLineSegment3D<T>(POINT_A_IN_AE, 
                                                                    POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE2 = QLineSegment3D<T>(POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH1 = QLineSegment3D<T>(POINT_A_IN_BH, 
                                                                    POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH2 = QLineSegment3D<T>(POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG1 = QLineSegment3D<T>(POINT_A_IN_CG, 
                                                                    POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG2 = QLineSegment3D<T>(POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = POINT_A_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = POINT_A_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = POINT_A_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = POINT_A_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = POINT_A_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = POINT_A_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = POINT_A_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = POINT_A_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = POINT_A_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = POINT_A_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = POINT_A_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = POINT_A_IN_CG;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1;
    T vFirstIntersectionBC1;
    T vFirstIntersectionCD1;
    T vFirstIntersectionDA1;
    T vFirstIntersectionEF1;
    T vFirstIntersectionFG1;
    T vFirstIntersectionGH1;
    T vFirstIntersectionHE1;
    T vFirstIntersectionDF1;
    T vFirstIntersectionAE1;
    T vFirstIntersectionBH1;
    T vFirstIntersectionCG1;
    T vFirstIntersectionAB2;
    T vFirstIntersectionBC2;
    T vFirstIntersectionCD2;
    T vFirstIntersectionDA2;
    T vFirstIntersectionEF2;
    T vFirstIntersectionFG2;
    T vFirstIntersectionGH2;
    T vFirstIntersectionHE2;
    T vFirstIntersectionDF2;
    T vFirstIntersectionAE2;
    T vFirstIntersectionBH2;
    T vFirstIntersectionCG2;
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC2);
    EQIntersections eEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD1);
    EQIntersections eEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD2);
    EQIntersections eEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA1);
    EQIntersections eEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA2);
    EQIntersections eEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF1);
    EQIntersections eEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF2);
    EQIntersections eEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG1);
    EQIntersections eEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG2);
    EQIntersections eEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH1);
    EQIntersections eEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH2);
    EQIntersections eEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE1);
    EQIntersections eEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE2);
    EQIntersections eEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF1);
    EQIntersections eEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF2);
    EQIntersections eEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE1);
    EQIntersections eEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE2);
    EQIntersections eEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH1);
    EQIntersections eEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH2);
    EQIntersections eEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG1);
    EQIntersections eEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD1 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA1 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF1 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG1 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH1 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE1 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF1 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE1 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH1 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG1 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD2 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA2 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF2 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG2 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH2 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE2 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF2 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE2 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH2 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG2 == EXPECTED_FIRSTPOINT_CG);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SQFloat::_0_25, VERTEX_B);
    const T POINT_B_IN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB = QLineSegment3D<T>(POINT_A_IN_AB, POINT_B_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_C);
    const T POINT_B_IN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC = QLineSegment3D<T>(POINT_A_IN_BC, POINT_B_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_D);
    const T POINT_B_IN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD = QLineSegment3D<T>(POINT_A_IN_CD, POINT_B_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B_IN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA = QLineSegment3D<T>(POINT_A_IN_DA, POINT_B_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SQFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF = QLineSegment3D<T>(POINT_A_IN_EF, POINT_B_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SQFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG = QLineSegment3D<T>(POINT_A_IN_FG, POINT_B_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SQFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH = QLineSegment3D<T>(POINT_A_IN_GH, POINT_B_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SQFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE = QLineSegment3D<T>(POINT_A_IN_HE, POINT_B_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SQFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF = QLineSegment3D<T>(POINT_A_IN_DF, POINT_B_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SQFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE = QLineSegment3D<T>(POINT_A_IN_AE, POINT_B_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH = QLineSegment3D<T>(POINT_A_IN_BH, POINT_B_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG = QLineSegment3D<T>(POINT_A_IN_CG, POINT_B_IN_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = LINE_SEGMENT_IN_AB.A;
    const T EXPECTED_FIRSTPOINT_BC = LINE_SEGMENT_IN_BC.A;
    const T EXPECTED_FIRSTPOINT_CD = LINE_SEGMENT_IN_CD.A;
    const T EXPECTED_FIRSTPOINT_DA = LINE_SEGMENT_IN_DA.A;
    const T EXPECTED_FIRSTPOINT_EF = LINE_SEGMENT_IN_EF.A;
    const T EXPECTED_FIRSTPOINT_FG = LINE_SEGMENT_IN_FG.A;
    const T EXPECTED_FIRSTPOINT_GH = LINE_SEGMENT_IN_GH.A;
    const T EXPECTED_FIRSTPOINT_HE = LINE_SEGMENT_IN_HE.A;
    const T EXPECTED_FIRSTPOINT_DF = LINE_SEGMENT_IN_DF.A;
    const T EXPECTED_FIRSTPOINT_AE = LINE_SEGMENT_IN_AE.A;
    const T EXPECTED_FIRSTPOINT_BH = LINE_SEGMENT_IN_BH.A;
    const T EXPECTED_FIRSTPOINT_CG = LINE_SEGMENT_IN_CG.A;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    EQIntersections eEndpointContainedInAB = LINE_SEGMENT_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB);
    EQIntersections eEndpointContainedInBC = LINE_SEGMENT_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC);
    EQIntersections eEndpointContainedInCD = LINE_SEGMENT_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD);
    EQIntersections eEndpointContainedInDA = LINE_SEGMENT_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA);
    EQIntersections eEndpointContainedInEF = LINE_SEGMENT_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF);
    EQIntersections eEndpointContainedInFG = LINE_SEGMENT_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG);
    EQIntersections eEndpointContainedInGH = LINE_SEGMENT_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH);
    EQIntersections eEndpointContainedInHE = LINE_SEGMENT_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE);
    EQIntersections eEndpointContainedInDF = LINE_SEGMENT_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF);
    EQIntersections eEndpointContainedInAE = LINE_SEGMENT_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE);
    EQIntersections eEndpointContainedInBH = LINE_SEGMENT_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH);
    EQIntersections eEndpointContainedInCG = LINE_SEGMENT_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
}

/// <summary>
/// Checks that it returns one intersection point when the line segment intersects with an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_q POINT_A_OVER_COMPONENTS[]  = { (float_q)1.5, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_BELOW_COMPONENTS[] = { (float_q)1.5, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_LEFT_COMPONENTS[]  = { SQFloat::_0, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_RIGHT_COMPONENTS[] = { SQFloat::_3, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_OVER  = T(POINT_A_OVER_COMPONENTS);  // For edges of face ABCD
    const T POINT_A_BELOW = T(POINT_A_BELOW_COMPONENTS); // For edges of face EFGH
    const T POINT_A_LEFT  = T(POINT_A_LEFT_COMPONENTS);  // For edges of face ADFE
    const T POINT_A_RIGHT = T(POINT_A_RIGHT_COMPONENTS); // For edges of face CGHB

    const T POINT_B_TO_AB = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B));
    const QLineSegment3D<T> LINE_SEGMENT_TO_AB = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_AB);

    const T POINT_B_TO_BC = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C));
    const QLineSegment3D<T> LINE_SEGMENT_TO_BC = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_BC);

    const T POINT_B_TO_CD = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D));
    const QLineSegment3D<T> LINE_SEGMENT_TO_CD = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_CD);

    const T POINT_B_TO_DA = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A));
    const QLineSegment3D<T> LINE_SEGMENT_TO_DA = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_DA);

    const T POINT_B_TO_EF = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F));
    const QLineSegment3D<T> LINE_SEGMENT_TO_EF = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_EF);

    const T POINT_B_TO_FG = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G));;
    const QLineSegment3D<T> LINE_SEGMENT_TO_FG = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_FG);

    const T POINT_B_TO_GH = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H));
    const QLineSegment3D<T> LINE_SEGMENT_TO_GH = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_GH);

    const T POINT_B_TO_HE = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E));
    const QLineSegment3D<T> LINE_SEGMENT_TO_HE = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_HE);

    const T POINT_B_TO_DF = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F));
    const QLineSegment3D<T> LINE_SEGMENT_TO_DF = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_DF);

    const T POINT_B_TO_AE = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E));
    const QLineSegment3D<T> LINE_SEGMENT_TO_AE = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_AE);

    const T POINT_B_TO_BH = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H));
    const QLineSegment3D<T> LINE_SEGMENT_TO_BH = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_BH);

    const T POINT_B_TO_CG = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G));
    const QLineSegment3D<T> LINE_SEGMENT_TO_CG = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const T EXPECTED_FIRSTPOINT_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const T EXPECTED_FIRSTPOINT_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const T EXPECTED_FIRSTPOINT_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    EQIntersections eIntersectsWithAB = LINE_SEGMENT_TO_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB);
    EQIntersections eIntersectsWithBC = LINE_SEGMENT_TO_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC);
    EQIntersections eIntersectsWithCD = LINE_SEGMENT_TO_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD);
    EQIntersections eIntersectsWithDA = LINE_SEGMENT_TO_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA);
    EQIntersections eIntersectsWithEF = LINE_SEGMENT_TO_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF);
    EQIntersections eIntersectsWithFG = LINE_SEGMENT_TO_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG);
    EQIntersections eIntersectsWithGH = LINE_SEGMENT_TO_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH);
    EQIntersections eIntersectsWithHE = LINE_SEGMENT_TO_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE);
    EQIntersections eIntersectsWithDF = LINE_SEGMENT_TO_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF);
    EQIntersections eIntersectsWithAE = LINE_SEGMENT_TO_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE);
    EQIntersections eIntersectsWithBH = LINE_SEGMENT_TO_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH);
    EQIntersections eIntersectsWithCG = LINE_SEGMENT_TO_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCG, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
}

/// <summary>
/// Checks that it returns one intersection when an endopoint of the line segment and a vertex of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenEndpointAndHexahedronVertexCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_POINT_B_DFGC = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_AEHB = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QLineSegment3D<T> LINE_SEGMENT_FROM_A1 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_A2 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_B1 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_B2 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_C1 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_C2 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_D1 = QLineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_D2 = QLineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_E1 = QLineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_E2 = QLineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_F1 = QLineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_F2 = QLineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_G1 = QLineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_G2 = QLineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_H1 = QLineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_H2 = QLineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA1;
    T vFirstIntersectionB1;
    T vFirstIntersectionC1;
    T vFirstIntersectionD1;
    T vFirstIntersectionE1;
    T vFirstIntersectionF1;
    T vFirstIntersectionG1;
    T vFirstIntersectionH1;
    T vFirstIntersectionA2;
    T vFirstIntersectionB2;
    T vFirstIntersectionC2;
    T vFirstIntersectionD2;
    T vFirstIntersectionE2;
    T vFirstIntersectionF2;
    T vFirstIntersectionG2;
    T vFirstIntersectionH2;
    EQIntersections eEndpointAndACoincide1 = LINE_SEGMENT_FROM_A1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA1);
    EQIntersections eEndpointAndACoincide2 = LINE_SEGMENT_FROM_A2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA2);
    EQIntersections eEndpointAndBCoincide1 = LINE_SEGMENT_FROM_B1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB1);
    EQIntersections eEndpointAndBCoincide2 = LINE_SEGMENT_FROM_B2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB2);
    EQIntersections eEndpointAndCCoincide1 = LINE_SEGMENT_FROM_C1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC1);
    EQIntersections eEndpointAndCCoincide2 = LINE_SEGMENT_FROM_C2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC2);
    EQIntersections eEndpointAndDCoincide1 = LINE_SEGMENT_FROM_D1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD1);
    EQIntersections eEndpointAndDCoincide2 = LINE_SEGMENT_FROM_D2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD2);
    EQIntersections eEndpointAndECoincide1 = LINE_SEGMENT_FROM_E1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE1);
    EQIntersections eEndpointAndECoincide2 = LINE_SEGMENT_FROM_E2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE2);
    EQIntersections eEndpointAndFCoincide1 = LINE_SEGMENT_FROM_F1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF1);
    EQIntersections eEndpointAndFCoincide2 = LINE_SEGMENT_FROM_F2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF2);
    EQIntersections eEndpointAndGCoincide1 = LINE_SEGMENT_FROM_G1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG1);
    EQIntersections eEndpointAndGCoincide2 = LINE_SEGMENT_FROM_G2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG2);
    EQIntersections eEndpointAndHCoincide1 = LINE_SEGMENT_FROM_H1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH1);
    EQIntersections eEndpointAndHCoincide2 = LINE_SEGMENT_FROM_H2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointAndACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndCCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndDCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndDCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndECoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndECoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndFCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndFCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndGCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndGCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndHCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndHCoincide2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA1 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB1 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC1 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD1 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE1 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF1 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG1 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH1 == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vFirstIntersectionA2 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB2 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC2 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD2 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE2 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF2 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG2 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH2 == EXPECTED_FIRSTPOINT_H);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenLineSegmentEndpointsCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_COMPONENTS_CONTAINED[] = { (float_q)1.5, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q POINT_COMPONENTS_IN_EDGE[] = { (float_q)1.5, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EDGE = QLineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_q POINT_COMPONENTS_IN_FACE[] = { (float_q)1.5, (float_q)1.5, SQFloat::_4, SQFloat::_1 };
    const T POINT_IN_FACE(POINT_COMPONENTS_IN_FACE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FACE = QLineSegment3D<T>(POINT_IN_FACE, POINT_IN_FACE);

    const float_q POINT_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_Infinite;
    const EQIntersections EXPECTED_RESULT_IN_EDGE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_IN_FACE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = EQIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_IN_FACE = POINT_IN_FACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vIntersectionContained = T::GetNullVector();
    T vIntersectionInEdge = T::GetNullVector();
    T vIntersectionInFace = T::GetNullVector();
    T vIntersectionNotContained = T::GetNullVector();

    const EQIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(HEXAHEDRON, vIntersectionContained);
    const EQIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(HEXAHEDRON, vIntersectionInEdge);
    const EQIntersections eResultInFace = LINE_SEGMENT_IN_FACE.IntersectionPoint(HEXAHEDRON, vIntersectionInFace);
    const EQIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(HEXAHEDRON, vIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultInEdge, EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK_EQUAL(eResultInFace, EXPECTED_RESULT_IN_FACE);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vIntersectionInFace == EXPECTED_POINT_IN_FACE);
    BOOST_CHECK(vIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns two intersection points when a common line segment and a common hexahedron intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenCommonLineSegmentIntersectsWithCommonHexahedron_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_0, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const float_q FIRSTPOINT_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const float_q SECONDPOINT_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_FIRSTPOINT = T(FIRSTPOINT_COMPONENTS);
    const T EXPECTED_SECONDPOINT = T(SECONDPOINT_COMPONENTS);
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenLineSegmentIntersectsWithHexahedronVertex_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_q POINT_A_COMPONENTS_LEFT[] = { SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_LEFT(POINT_A_COMPONENTS_LEFT);

    const float_q POINT_A_COMPONENTS_RIGHT[] = { SQFloat::_3, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_RIGHT(POINT_A_COMPONENTS_RIGHT);

    const T POINT_B_A = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_A);
    const T POINT_B_B = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_B);
    const T POINT_B_C = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_C);
    const T POINT_B_D = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_D);
    const T POINT_B_E = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_E);
    const T POINT_B_F = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_F);
    const T POINT_B_G = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_G);
    const T POINT_B_H = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_H);

    const QLineSegment3D<T> LINE_SEGMENT_A = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_A);
    const QLineSegment3D<T> LINE_SEGMENT_B = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_B);
    const QLineSegment3D<T> LINE_SEGMENT_C = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_C);
    const QLineSegment3D<T> LINE_SEGMENT_D = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_D);
    const QLineSegment3D<T> LINE_SEGMENT_E = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_E);
    const QLineSegment3D<T> LINE_SEGMENT_F = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_F);
    const QLineSegment3D<T> LINE_SEGMENT_G = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_G);
    const QLineSegment3D<T> LINE_SEGMENT_H = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_H);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionA, vSecondIntersectionA;
    T vFirstIntersectionB, vSecondIntersectionB;
    T vFirstIntersectionC, vSecondIntersectionC;
    T vFirstIntersectionD, vSecondIntersectionD;
    T vFirstIntersectionE, vSecondIntersectionE;
    T vFirstIntersectionF, vSecondIntersectionF;
    T vFirstIntersectionG, vSecondIntersectionG;
    T vFirstIntersectionH, vSecondIntersectionH;
    EQIntersections eIntersectsWithA = LINE_SEGMENT_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA, vSecondIntersectionA);
    EQIntersections eIntersectsWithB = LINE_SEGMENT_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB, vSecondIntersectionB);
    EQIntersections eIntersectsWithC = LINE_SEGMENT_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC, vSecondIntersectionC);
    EQIntersections eIntersectsWithD = LINE_SEGMENT_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD, vSecondIntersectionD);
    EQIntersections eIntersectsWithE = LINE_SEGMENT_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE, vSecondIntersectionE);
    EQIntersections eIntersectsWithF = LINE_SEGMENT_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF, vSecondIntersectionF);
    EQIntersections eIntersectsWithG = LINE_SEGMENT_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG, vSecondIntersectionG);
    EQIntersections eIntersectsWithH = LINE_SEGMENT_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH, vSecondIntersectionH);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithH, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionG == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionH == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when a common line segment and a common hexahedron would intersect if the line segment was lengthened.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithHexahedronButWouldDoIfLineSegmentWasLengthened_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_0, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT = T::GetNullVector();
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;

    T vFirstIntersection = T::GetNullVector();
    T vSecondIntersection = T::GetNullVector();

	// [Execution]
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment belongs to a face of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenAnEndpointIsContainedInHexahedronFace_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC + QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE + QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB + QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB + QVector3(SQFloat::_0, SQFloat::_0, -SQFloat::_1);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD + QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH + QVector3(SQFloat::_0, -SQFloat::_1, SQFloat::_0);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = POINT_A_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = POINT_A_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = POINT_A_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = POINT_A_EFGH;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    T vSecondIntersectionDFGC1 = T::GetNullVector();
    T vSecondIntersectionDFGC2 = T::GetNullVector();
    T vSecondIntersectionADFE1 = T::GetNullVector();
    T vSecondIntersectionADFE2 = T::GetNullVector();
    T vSecondIntersectionAEHB1 = T::GetNullVector();
    T vSecondIntersectionAEHB2 = T::GetNullVector();
    T vSecondIntersectionCGHB1 = T::GetNullVector();
    T vSecondIntersectionCGHB2 = T::GetNullVector();
    T vSecondIntersectionABCD1 = T::GetNullVector();
    T vSecondIntersectionABCD2 = T::GetNullVector();
    T vSecondIntersectionEFGH1 = T::GetNullVector();
    T vSecondIntersectionEFGH2 = T::GetNullVector();
    EQIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1, vSecondIntersectionDFGC1);
    EQIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2, vSecondIntersectionDFGC2);
    EQIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1, vSecondIntersectionADFE1);
    EQIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2, vSecondIntersectionADFE2);
    EQIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1, vSecondIntersectionAEHB1);
    EQIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2, vSecondIntersectionAEHB2);
    EQIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1, vSecondIntersectionCGHB1);
    EQIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2, vSecondIntersectionCGHB2);
    EQIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1, vSecondIntersectionABCD1);
    EQIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2, vSecondIntersectionABCD2);
    EQIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1, vSecondIntersectionEFGH1);
    EQIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2, vSecondIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vSecondIntersectionDFGC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDFGC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionADFE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionADFE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAEHB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAEHB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCGHB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCGHB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionABCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionABCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEFGH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEFGH2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment belongs to a face of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenLineSegmentBelongsToHexahedronFace_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = QLineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = QLineSegment3D<T>(POINT_B_DFGC, POINT_A_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = QLineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = QLineSegment3D<T>(POINT_B_ADFE, POINT_A_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = QLineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = QLineSegment3D<T>(POINT_B_AEHB, POINT_A_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = QLineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = QLineSegment3D<T>(POINT_B_CGHB, POINT_A_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = QLineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = QLineSegment3D<T>(POINT_B_ABCD, POINT_A_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = QLineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = QLineSegment3D<T>(POINT_B_EFGH, POINT_A_EFGH);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT_DFGC1 = LINE_SEGMENT_IN_DFGC1.A;
    const T EXPECTED_FIRSTPOINT_DFGC2 = LINE_SEGMENT_IN_DFGC2.A;
    const T EXPECTED_FIRSTPOINT_ADFE1 = LINE_SEGMENT_IN_ADFE1.A;
    const T EXPECTED_FIRSTPOINT_ADFE2 = LINE_SEGMENT_IN_ADFE2.A;
    const T EXPECTED_FIRSTPOINT_AEHB1 = LINE_SEGMENT_IN_AEHB1.A;
    const T EXPECTED_FIRSTPOINT_AEHB2 = LINE_SEGMENT_IN_AEHB2.A;
    const T EXPECTED_FIRSTPOINT_CGHB1 = LINE_SEGMENT_IN_CGHB1.A;
    const T EXPECTED_FIRSTPOINT_CGHB2 = LINE_SEGMENT_IN_CGHB2.A;
    const T EXPECTED_FIRSTPOINT_ABCD1 = LINE_SEGMENT_IN_ABCD1.A;
    const T EXPECTED_FIRSTPOINT_ABCD2 = LINE_SEGMENT_IN_ABCD2.A;
    const T EXPECTED_FIRSTPOINT_EFGH1 = LINE_SEGMENT_IN_EFGH1.A;
    const T EXPECTED_FIRSTPOINT_EFGH2 = LINE_SEGMENT_IN_EFGH2.A;
    const T EXPECTED_SECONDPOINT_DFGC1 = LINE_SEGMENT_IN_DFGC1.B;
    const T EXPECTED_SECONDPOINT_DFGC2 = LINE_SEGMENT_IN_DFGC2.B;
    const T EXPECTED_SECONDPOINT_ADFE1 = LINE_SEGMENT_IN_ADFE1.B;
    const T EXPECTED_SECONDPOINT_ADFE2 = LINE_SEGMENT_IN_ADFE2.B;
    const T EXPECTED_SECONDPOINT_AEHB1 = LINE_SEGMENT_IN_AEHB1.B;
    const T EXPECTED_SECONDPOINT_AEHB2 = LINE_SEGMENT_IN_AEHB2.B;
    const T EXPECTED_SECONDPOINT_CGHB1 = LINE_SEGMENT_IN_CGHB1.B;
    const T EXPECTED_SECONDPOINT_CGHB2 = LINE_SEGMENT_IN_CGHB2.B;
    const T EXPECTED_SECONDPOINT_ABCD1 = LINE_SEGMENT_IN_ABCD1.B;
    const T EXPECTED_SECONDPOINT_ABCD2 = LINE_SEGMENT_IN_ABCD2.B;
    const T EXPECTED_SECONDPOINT_EFGH1 = LINE_SEGMENT_IN_EFGH1.B;
    const T EXPECTED_SECONDPOINT_EFGH2 = LINE_SEGMENT_IN_EFGH2.B;

    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    T vSecondIntersectionDFGC1 = T::GetNullVector();
    T vSecondIntersectionDFGC2 = T::GetNullVector();
    T vSecondIntersectionADFE1 = T::GetNullVector();
    T vSecondIntersectionADFE2 = T::GetNullVector();
    T vSecondIntersectionAEHB1 = T::GetNullVector();
    T vSecondIntersectionAEHB2 = T::GetNullVector();
    T vSecondIntersectionCGHB1 = T::GetNullVector();
    T vSecondIntersectionCGHB2 = T::GetNullVector();
    T vSecondIntersectionABCD1 = T::GetNullVector();
    T vSecondIntersectionABCD2 = T::GetNullVector();
    T vSecondIntersectionEFGH1 = T::GetNullVector();
    T vSecondIntersectionEFGH2 = T::GetNullVector();

	// [Execution]
    EQIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1, vSecondIntersectionDFGC1);
    EQIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2, vSecondIntersectionDFGC2);
    EQIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1, vSecondIntersectionADFE1);
    EQIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2, vSecondIntersectionADFE2);
    EQIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1, vSecondIntersectionAEHB1);
    EQIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2, vSecondIntersectionAEHB2);
    EQIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1, vSecondIntersectionCGHB1);
    EQIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2, vSecondIntersectionCGHB2);
    EQIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1, vSecondIntersectionABCD1);
    EQIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2, vSecondIntersectionABCD2);
    EQIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1, vSecondIntersectionEFGH1);
    EQIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2, vSecondIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK_EQUAL(eContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eContainedInEFGH2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC1);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC2);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE1);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE2);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB1);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB2);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB1);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB2);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD1);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD2);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH1);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH2);
    BOOST_CHECK(vSecondIntersectionDFGC1 == EXPECTED_SECONDPOINT_DFGC1);
    BOOST_CHECK(vSecondIntersectionDFGC2 == EXPECTED_SECONDPOINT_DFGC2);
    BOOST_CHECK(vSecondIntersectionADFE1 == EXPECTED_SECONDPOINT_ADFE1);
    BOOST_CHECK(vSecondIntersectionADFE2 == EXPECTED_SECONDPOINT_ADFE2);
    BOOST_CHECK(vSecondIntersectionAEHB1 == EXPECTED_SECONDPOINT_AEHB1);
    BOOST_CHECK(vSecondIntersectionAEHB2 == EXPECTED_SECONDPOINT_AEHB2);
    BOOST_CHECK(vSecondIntersectionCGHB1 == EXPECTED_SECONDPOINT_CGHB1);
    BOOST_CHECK(vSecondIntersectionCGHB2 == EXPECTED_SECONDPOINT_CGHB2);
    BOOST_CHECK(vSecondIntersectionABCD1 == EXPECTED_SECONDPOINT_ABCD1);
    BOOST_CHECK(vSecondIntersectionABCD2 == EXPECTED_SECONDPOINT_ABCD2);
    BOOST_CHECK(vSecondIntersectionEFGH1 == EXPECTED_SECONDPOINT_EFGH1);
    BOOST_CHECK(vSecondIntersectionEFGH2 == EXPECTED_SECONDPOINT_EFGH2);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of a line segment is contained in the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyOneEndpointIsContainedInHexahedron_Test, TQTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_D);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    const T POINT_A = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_G);
    const T POINT_B = POINT_A.Lerp(SQFloat::_2, EXPECTED_FIRSTPOINT);
    const QLineSegment3D<T> LINE_SEGMENT1 = QLineSegment3D<T>(POINT_A, POINT_B);
    const QLineSegment3D<T> LINE_SEGMENT2 = QLineSegment3D<T>(POINT_A, POINT_B);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vSecondIntersection1 = T::GetNullVector();
    T vSecondIntersection2 = T::GetNullVector();
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(HEXAHEDRON, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(HEXAHEDRON, vFirstIntersection2, vSecondIntersection2);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment is contained in an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyOneEndpointBelongsToEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_POINT_B_DFGC = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_AEHB = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_ABCD = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_EFGH = QVector3(SQFloat::_0, -SQFloat::_1, SQFloat::_0);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB1 = QLineSegment3D<T>(POINT_A_IN_AB, 
                                                                    POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB2 = QLineSegment3D<T>(POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC1 = QLineSegment3D<T>(POINT_A_IN_BC, 
                                                                    POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC2 = QLineSegment3D<T>(POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD1 = QLineSegment3D<T>(POINT_A_IN_CD, 
                                                                    POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD2 = QLineSegment3D<T>(POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA1 = QLineSegment3D<T>(POINT_A_IN_DA, 
                                                                    POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA2 = QLineSegment3D<T>(POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF1 = QLineSegment3D<T>(POINT_A_IN_EF, 
                                                                    POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF2 = QLineSegment3D<T>(POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG1 = QLineSegment3D<T>(POINT_A_IN_FG, 
                                                                    POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG2 = QLineSegment3D<T>(POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH1 = QLineSegment3D<T>(POINT_A_IN_GH, 
                                                                    POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH2 = QLineSegment3D<T>(POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE1 = QLineSegment3D<T>(POINT_A_IN_HE, 
                                                                    POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE2 = QLineSegment3D<T>(POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF1 = QLineSegment3D<T>(POINT_A_IN_DF, 
                                                                    POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF2 = QLineSegment3D<T>(POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE1 = QLineSegment3D<T>(POINT_A_IN_AE, 
                                                                    POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE2 = QLineSegment3D<T>(POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH1 = QLineSegment3D<T>(POINT_A_IN_BH, 
                                                                    POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH2 = QLineSegment3D<T>(POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG1 = QLineSegment3D<T>(POINT_A_IN_CG, 
                                                                    POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG2 = QLineSegment3D<T>(POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = POINT_A_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = POINT_A_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = POINT_A_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = POINT_A_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = POINT_A_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = POINT_A_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = POINT_A_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = POINT_A_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = POINT_A_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = POINT_A_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = POINT_A_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = POINT_A_IN_CG;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1, vSecondIntersectionAB1 = T::GetNullVector();
    T vFirstIntersectionBC1, vSecondIntersectionBC1 = T::GetNullVector();
    T vFirstIntersectionCD1, vSecondIntersectionCD1 = T::GetNullVector();
    T vFirstIntersectionDA1, vSecondIntersectionDA1 = T::GetNullVector();
    T vFirstIntersectionEF1, vSecondIntersectionEF1 = T::GetNullVector();
    T vFirstIntersectionFG1, vSecondIntersectionFG1 = T::GetNullVector();
    T vFirstIntersectionGH1, vSecondIntersectionGH1 = T::GetNullVector();
    T vFirstIntersectionHE1, vSecondIntersectionHE1 = T::GetNullVector();
    T vFirstIntersectionDF1, vSecondIntersectionDF1 = T::GetNullVector();
    T vFirstIntersectionAE1, vSecondIntersectionAE1 = T::GetNullVector();
    T vFirstIntersectionBH1, vSecondIntersectionBH1 = T::GetNullVector();
    T vFirstIntersectionCG1, vSecondIntersectionCG1 = T::GetNullVector();
    T vFirstIntersectionAB2, vSecondIntersectionAB2 = T::GetNullVector();
    T vFirstIntersectionBC2, vSecondIntersectionBC2 = T::GetNullVector();
    T vFirstIntersectionCD2, vSecondIntersectionCD2 = T::GetNullVector();
    T vFirstIntersectionDA2, vSecondIntersectionDA2 = T::GetNullVector();
    T vFirstIntersectionEF2, vSecondIntersectionEF2 = T::GetNullVector();
    T vFirstIntersectionFG2, vSecondIntersectionFG2 = T::GetNullVector();
    T vFirstIntersectionGH2, vSecondIntersectionGH2 = T::GetNullVector();
    T vFirstIntersectionHE2, vSecondIntersectionHE2 = T::GetNullVector();
    T vFirstIntersectionDF2, vSecondIntersectionDF2 = T::GetNullVector();
    T vFirstIntersectionAE2, vSecondIntersectionAE2 = T::GetNullVector();
    T vFirstIntersectionBH2, vSecondIntersectionBH2 = T::GetNullVector();
    T vFirstIntersectionCG2, vSecondIntersectionCG2 = T::GetNullVector();
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC2, vSecondIntersectionBC2);
    EQIntersections eEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD1, vSecondIntersectionCD1);
    EQIntersections eEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD2, vSecondIntersectionCD2);
    EQIntersections eEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA1, vSecondIntersectionDA1);
    EQIntersections eEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA2, vSecondIntersectionDA2);
    EQIntersections eEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF1, vSecondIntersectionEF1);
    EQIntersections eEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF2, vSecondIntersectionEF2);
    EQIntersections eEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG1, vSecondIntersectionFG1);
    EQIntersections eEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG2, vSecondIntersectionFG2);
    EQIntersections eEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH1, vSecondIntersectionGH1);
    EQIntersections eEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH2, vSecondIntersectionGH2);
    EQIntersections eEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE1, vSecondIntersectionHE1);
    EQIntersections eEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE2, vSecondIntersectionHE2);
    EQIntersections eEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF1, vSecondIntersectionDF1);
    EQIntersections eEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF2, vSecondIntersectionDF2);
    EQIntersections eEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE1, vSecondIntersectionAE1);
    EQIntersections eEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE2, vSecondIntersectionAE2);
    EQIntersections eEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH1, vSecondIntersectionBH1);
    EQIntersections eEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH2, vSecondIntersectionBH2);
    EQIntersections eEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG1, vSecondIntersectionCG1);
    EQIntersections eEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG2, vSecondIntersectionCG2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD1 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA1 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF1 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG1 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH1 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE1 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF1 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE1 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH1 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG1 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD2 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA2 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF2 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG2 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH2 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE2 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF2 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE2 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH2 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG2 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment is contained in an edge of the hexahedron and the other is inside the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyOneEndpointBelongsToEdgeOfHexahedronAndTheOtherIsInsideTheHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T CENTER_POINT = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_G);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB1 = QLineSegment3D<T>(POINT_A_IN_AB, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC1 = QLineSegment3D<T>(POINT_A_IN_BC, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD1 = QLineSegment3D<T>(POINT_A_IN_CD, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA1 = QLineSegment3D<T>(POINT_A_IN_DA, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF1 = QLineSegment3D<T>(POINT_A_IN_EF, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG1 = QLineSegment3D<T>(POINT_A_IN_FG, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH1 = QLineSegment3D<T>(POINT_A_IN_GH, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE1 = QLineSegment3D<T>(POINT_A_IN_HE, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF1 = QLineSegment3D<T>(POINT_A_IN_DF, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE1 = QLineSegment3D<T>(POINT_A_IN_AE, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH1 = QLineSegment3D<T>(POINT_A_IN_BH, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG1 = QLineSegment3D<T>(POINT_A_IN_CG, CENTER_POINT);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG2 = QLineSegment3D<T>(CENTER_POINT, POINT_A_IN_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = POINT_A_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = POINT_A_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = POINT_A_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = POINT_A_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = POINT_A_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = POINT_A_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = POINT_A_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = POINT_A_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = POINT_A_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = POINT_A_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = POINT_A_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = POINT_A_IN_CG;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1, vSecondIntersectionAB1 = T::GetNullVector();
    T vFirstIntersectionBC1, vSecondIntersectionBC1 = T::GetNullVector();
    T vFirstIntersectionCD1, vSecondIntersectionCD1 = T::GetNullVector();
    T vFirstIntersectionDA1, vSecondIntersectionDA1 = T::GetNullVector();
    T vFirstIntersectionEF1, vSecondIntersectionEF1 = T::GetNullVector();
    T vFirstIntersectionFG1, vSecondIntersectionFG1 = T::GetNullVector();
    T vFirstIntersectionGH1, vSecondIntersectionGH1 = T::GetNullVector();
    T vFirstIntersectionHE1, vSecondIntersectionHE1 = T::GetNullVector();
    T vFirstIntersectionDF1, vSecondIntersectionDF1 = T::GetNullVector();
    T vFirstIntersectionAE1, vSecondIntersectionAE1 = T::GetNullVector();
    T vFirstIntersectionBH1, vSecondIntersectionBH1 = T::GetNullVector();
    T vFirstIntersectionCG1, vSecondIntersectionCG1 = T::GetNullVector();
    T vFirstIntersectionAB2, vSecondIntersectionAB2 = T::GetNullVector();
    T vFirstIntersectionBC2, vSecondIntersectionBC2 = T::GetNullVector();
    T vFirstIntersectionCD2, vSecondIntersectionCD2 = T::GetNullVector();
    T vFirstIntersectionDA2, vSecondIntersectionDA2 = T::GetNullVector();
    T vFirstIntersectionEF2, vSecondIntersectionEF2 = T::GetNullVector();
    T vFirstIntersectionFG2, vSecondIntersectionFG2 = T::GetNullVector();
    T vFirstIntersectionGH2, vSecondIntersectionGH2 = T::GetNullVector();
    T vFirstIntersectionHE2, vSecondIntersectionHE2 = T::GetNullVector();
    T vFirstIntersectionDF2, vSecondIntersectionDF2 = T::GetNullVector();
    T vFirstIntersectionAE2, vSecondIntersectionAE2 = T::GetNullVector();
    T vFirstIntersectionBH2, vSecondIntersectionBH2 = T::GetNullVector();
    T vFirstIntersectionCG2, vSecondIntersectionCG2 = T::GetNullVector();
    EQIntersections eEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EQIntersections eEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EQIntersections eEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EQIntersections eEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC2, vSecondIntersectionBC2);
    EQIntersections eEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD1, vSecondIntersectionCD1);
    EQIntersections eEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD2, vSecondIntersectionCD2);
    EQIntersections eEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA1, vSecondIntersectionDA1);
    EQIntersections eEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA2, vSecondIntersectionDA2);
    EQIntersections eEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF1, vSecondIntersectionEF1);
    EQIntersections eEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF2, vSecondIntersectionEF2);
    EQIntersections eEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG1, vSecondIntersectionFG1);
    EQIntersections eEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG2, vSecondIntersectionFG2);
    EQIntersections eEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH1, vSecondIntersectionGH1);
    EQIntersections eEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH2, vSecondIntersectionGH2);
    EQIntersections eEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE1, vSecondIntersectionHE1);
    EQIntersections eEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE2, vSecondIntersectionHE2);
    EQIntersections eEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF1, vSecondIntersectionDF1);
    EQIntersections eEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF2, vSecondIntersectionDF2);
    EQIntersections eEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE1, vSecondIntersectionAE1);
    EQIntersections eEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE2, vSecondIntersectionAE2);
    EQIntersections eEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH1, vSecondIntersectionBH1);
    EQIntersections eEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH2, vSecondIntersectionBH2);
    EQIntersections eEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG1, vSecondIntersectionCG1);
    EQIntersections eEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG2, vSecondIntersectionCG2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD1 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA1 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF1 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG1 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH1 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE1 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF1 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE1 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH1 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG1 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD2 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA2 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF2 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG2 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH2 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE2 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF2 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE2 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH2 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG2 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SQFloat::_0_25, VERTEX_B);
    const T POINT_B_IN_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AB = QLineSegment3D<T>(POINT_A_IN_AB, POINT_B_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_C);
    const T POINT_B_IN_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BC = QLineSegment3D<T>(POINT_A_IN_BC, POINT_B_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_D);
    const T POINT_B_IN_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CD = QLineSegment3D<T>(POINT_A_IN_CD, POINT_B_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SQFloat::_0_25, VERTEX_A);
    const T POINT_B_IN_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DA = QLineSegment3D<T>(POINT_A_IN_DA, POINT_B_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SQFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EF = QLineSegment3D<T>(POINT_A_IN_EF, POINT_B_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SQFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FG = QLineSegment3D<T>(POINT_A_IN_FG, POINT_B_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SQFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_GH = QLineSegment3D<T>(POINT_A_IN_GH, POINT_B_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SQFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_HE = QLineSegment3D<T>(POINT_A_IN_HE, POINT_B_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SQFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const QLineSegment3D<T> LINE_SEGMENT_IN_DF = QLineSegment3D<T>(POINT_A_IN_DF, POINT_B_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SQFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const QLineSegment3D<T> LINE_SEGMENT_IN_AE = QLineSegment3D<T>(POINT_A_IN_AE, POINT_B_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SQFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const QLineSegment3D<T> LINE_SEGMENT_IN_BH = QLineSegment3D<T>(POINT_A_IN_BH, POINT_B_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SQFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const QLineSegment3D<T> LINE_SEGMENT_IN_CG = QLineSegment3D<T>(POINT_A_IN_CG, POINT_B_IN_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = LINE_SEGMENT_IN_AB.A;
    const T EXPECTED_FIRSTPOINT_BC = LINE_SEGMENT_IN_BC.A;
    const T EXPECTED_FIRSTPOINT_CD = LINE_SEGMENT_IN_CD.A;
    const T EXPECTED_FIRSTPOINT_DA = LINE_SEGMENT_IN_DA.A;
    const T EXPECTED_FIRSTPOINT_EF = LINE_SEGMENT_IN_EF.A;
    const T EXPECTED_FIRSTPOINT_FG = LINE_SEGMENT_IN_FG.A;
    const T EXPECTED_FIRSTPOINT_GH = LINE_SEGMENT_IN_GH.A;
    const T EXPECTED_FIRSTPOINT_HE = LINE_SEGMENT_IN_HE.A;
    const T EXPECTED_FIRSTPOINT_DF = LINE_SEGMENT_IN_DF.A;
    const T EXPECTED_FIRSTPOINT_AE = LINE_SEGMENT_IN_AE.A;
    const T EXPECTED_FIRSTPOINT_BH = LINE_SEGMENT_IN_BH.A;
    const T EXPECTED_FIRSTPOINT_CG = LINE_SEGMENT_IN_CG.A;
    const T EXPECTED_SECONDPOINT_AB = LINE_SEGMENT_IN_AB.B;
    const T EXPECTED_SECONDPOINT_BC = LINE_SEGMENT_IN_BC.B;
    const T EXPECTED_SECONDPOINT_CD = LINE_SEGMENT_IN_CD.B;
    const T EXPECTED_SECONDPOINT_DA = LINE_SEGMENT_IN_DA.B;
    const T EXPECTED_SECONDPOINT_EF = LINE_SEGMENT_IN_EF.B;
    const T EXPECTED_SECONDPOINT_FG = LINE_SEGMENT_IN_FG.B;
    const T EXPECTED_SECONDPOINT_GH = LINE_SEGMENT_IN_GH.B;
    const T EXPECTED_SECONDPOINT_HE = LINE_SEGMENT_IN_HE.B;
    const T EXPECTED_SECONDPOINT_DF = LINE_SEGMENT_IN_DF.B;
    const T EXPECTED_SECONDPOINT_AE = LINE_SEGMENT_IN_AE.B;
    const T EXPECTED_SECONDPOINT_BH = LINE_SEGMENT_IN_BH.B;
    const T EXPECTED_SECONDPOINT_CG = LINE_SEGMENT_IN_CG.B;
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    T vSecondIntersectionCD = T::GetNullVector();
    T vSecondIntersectionDA = T::GetNullVector();
    T vSecondIntersectionEF = T::GetNullVector();
    T vSecondIntersectionFG = T::GetNullVector();
    T vSecondIntersectionGH = T::GetNullVector();
    T vSecondIntersectionHE = T::GetNullVector();
    T vSecondIntersectionDF = T::GetNullVector();
    T vSecondIntersectionAE = T::GetNullVector();
    T vSecondIntersectionBH = T::GetNullVector();
    T vSecondIntersectionCG = T::GetNullVector();
    EQIntersections eEndpointContainedInAB = LINE_SEGMENT_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EQIntersections eEndpointContainedInBC = LINE_SEGMENT_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EQIntersections eEndpointContainedInCD = LINE_SEGMENT_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EQIntersections eEndpointContainedInDA = LINE_SEGMENT_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EQIntersections eEndpointContainedInEF = LINE_SEGMENT_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EQIntersections eEndpointContainedInFG = LINE_SEGMENT_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EQIntersections eEndpointContainedInGH = LINE_SEGMENT_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EQIntersections eEndpointContainedInHE = LINE_SEGMENT_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EQIntersections eEndpointContainedInDF = LINE_SEGMENT_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EQIntersections eEndpointContainedInAE = LINE_SEGMENT_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EQIntersections eEndpointContainedInBH = LINE_SEGMENT_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EQIntersections eEndpointContainedInCG = LINE_SEGMENT_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointContainedInCG, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT_DA);
    BOOST_CHECK(vSecondIntersectionEF == EXPECTED_SECONDPOINT_EF);
    BOOST_CHECK(vSecondIntersectionFG == EXPECTED_SECONDPOINT_FG);
    BOOST_CHECK(vSecondIntersectionGH == EXPECTED_SECONDPOINT_GH);
    BOOST_CHECK(vSecondIntersectionHE == EXPECTED_SECONDPOINT_HE);
    BOOST_CHECK(vSecondIntersectionDF == EXPECTED_SECONDPOINT_DF);
    BOOST_CHECK(vSecondIntersectionAE == EXPECTED_SECONDPOINT_AE);
    BOOST_CHECK(vSecondIntersectionBH == EXPECTED_SECONDPOINT_BH);
    BOOST_CHECK(vSecondIntersectionCG == EXPECTED_SECONDPOINT_CG);
}

/// <summary>
/// Checks that it returns one intersection point when the line segment intersects with an edge of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfHexahedron_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_q POINT_A_OVER_COMPONENTS[]  = { (float_q)1.5, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_BELOW_COMPONENTS[] = { (float_q)1.5, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_LEFT_COMPONENTS[]  = { SQFloat::_0, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const float_q POINT_A_RIGHT_COMPONENTS[] = { SQFloat::_3, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const T POINT_A_OVER  = T(POINT_A_OVER_COMPONENTS);  // For edges of face ABCD
    const T POINT_A_BELOW = T(POINT_A_BELOW_COMPONENTS); // For edges of face EFGH
    const T POINT_A_LEFT  = T(POINT_A_LEFT_COMPONENTS);  // For edges of face ADFE
    const T POINT_A_RIGHT = T(POINT_A_RIGHT_COMPONENTS); // For edges of face CGHB

    const T POINT_B_TO_AB = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B));
    const QLineSegment3D<T> LINE_SEGMENT_TO_AB = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_AB);

    const T POINT_B_TO_BC = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C));
    const QLineSegment3D<T> LINE_SEGMENT_TO_BC = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_BC);

    const T POINT_B_TO_CD = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D));
    const QLineSegment3D<T> LINE_SEGMENT_TO_CD = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_CD);

    const T POINT_B_TO_DA = POINT_A_OVER.Lerp(SQFloat::_2, VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A));
    const QLineSegment3D<T> LINE_SEGMENT_TO_DA = QLineSegment3D<T>(POINT_A_OVER, POINT_B_TO_DA);

    const T POINT_B_TO_EF = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F));
    const QLineSegment3D<T> LINE_SEGMENT_TO_EF = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_EF);

    const T POINT_B_TO_FG = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G));;
    const QLineSegment3D<T> LINE_SEGMENT_TO_FG = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_FG);

    const T POINT_B_TO_GH = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H));
    const QLineSegment3D<T> LINE_SEGMENT_TO_GH = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_GH);

    const T POINT_B_TO_HE = POINT_A_BELOW.Lerp(SQFloat::_2, VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E));
    const QLineSegment3D<T> LINE_SEGMENT_TO_HE = QLineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_HE);

    const T POINT_B_TO_DF = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F));
    const QLineSegment3D<T> LINE_SEGMENT_TO_DF = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_DF);

    const T POINT_B_TO_AE = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E));
    const QLineSegment3D<T> LINE_SEGMENT_TO_AE = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_AE);

    const T POINT_B_TO_BH = POINT_A_LEFT.Lerp(SQFloat::_2, VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H));
    const QLineSegment3D<T> LINE_SEGMENT_TO_BH = QLineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_BH);

    const T POINT_B_TO_CG = POINT_A_RIGHT.Lerp(SQFloat::_2, VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G));
    const QLineSegment3D<T> LINE_SEGMENT_TO_CG = QLineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_CG);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CD = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_D);
    const T EXPECTED_FIRSTPOINT_DA = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_A);
    const T EXPECTED_FIRSTPOINT_EF = VERTEX_E.Lerp(SQFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_FG = VERTEX_F.Lerp(SQFloat::_0_5, VERTEX_G);
    const T EXPECTED_FIRSTPOINT_GH = VERTEX_G.Lerp(SQFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_HE = VERTEX_H.Lerp(SQFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_DF = VERTEX_D.Lerp(SQFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_AE = VERTEX_A.Lerp(SQFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_BH = VERTEX_B.Lerp(SQFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_CG = VERTEX_C.Lerp(SQFloat::_0_5, VERTEX_G);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    T vSecondIntersectionCD = T::GetNullVector();
    T vSecondIntersectionDA = T::GetNullVector();
    T vSecondIntersectionEF = T::GetNullVector();
    T vSecondIntersectionFG = T::GetNullVector();
    T vSecondIntersectionGH = T::GetNullVector();
    T vSecondIntersectionHE = T::GetNullVector();
    T vSecondIntersectionDF = T::GetNullVector();
    T vSecondIntersectionAE = T::GetNullVector();
    T vSecondIntersectionBH = T::GetNullVector();
    T vSecondIntersectionCG = T::GetNullVector();
    EQIntersections eIntersectsWithAB = LINE_SEGMENT_TO_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EQIntersections eIntersectsWithBC = LINE_SEGMENT_TO_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EQIntersections eIntersectsWithCD = LINE_SEGMENT_TO_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EQIntersections eIntersectsWithDA = LINE_SEGMENT_TO_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EQIntersections eIntersectsWithEF = LINE_SEGMENT_TO_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EQIntersections eIntersectsWithFG = LINE_SEGMENT_TO_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EQIntersections eIntersectsWithGH = LINE_SEGMENT_TO_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EQIntersections eIntersectsWithHE = LINE_SEGMENT_TO_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EQIntersections eIntersectsWithDF = LINE_SEGMENT_TO_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EQIntersections eIntersectsWithAE = LINE_SEGMENT_TO_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EQIntersections eIntersectsWithBH = LINE_SEGMENT_TO_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EQIntersections eIntersectsWithCG = LINE_SEGMENT_TO_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK_EQUAL(eIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eIntersectsWithCG, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection when an endopoint of the line segment and a vertex of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenEndpointAndHexahedronVertexCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QVector3 RELATIVE_POSITION_OF_POINT_B_DFGC = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 RELATIVE_POSITION_OF_POINT_B_AEHB = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QLineSegment3D<T> LINE_SEGMENT_FROM_A1 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_A2 = QLineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_B1 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_B2 = QLineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_C1 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_C2 = QLineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_D1 = QLineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_D2 = QLineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_E1 = QLineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_E2 = QLineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_F1 = QLineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_F2 = QLineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_G1 = QLineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_G2 = QLineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_H1 = QLineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const QLineSegment3D<T> LINE_SEGMENT_FROM_H2 = QLineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA1, vSecondIntersectionA1 = T::GetNullVector();
    T vFirstIntersectionB1, vSecondIntersectionB1 = T::GetNullVector();
    T vFirstIntersectionC1, vSecondIntersectionC1 = T::GetNullVector();
    T vFirstIntersectionD1, vSecondIntersectionD1 = T::GetNullVector();
    T vFirstIntersectionE1, vSecondIntersectionE1 = T::GetNullVector();
    T vFirstIntersectionF1, vSecondIntersectionF1 = T::GetNullVector();
    T vFirstIntersectionG1, vSecondIntersectionG1 = T::GetNullVector();
    T vFirstIntersectionH1, vSecondIntersectionH1 = T::GetNullVector();
    T vFirstIntersectionA2, vSecondIntersectionA2 = T::GetNullVector();
    T vFirstIntersectionB2, vSecondIntersectionB2 = T::GetNullVector();
    T vFirstIntersectionC2, vSecondIntersectionC2 = T::GetNullVector();
    T vFirstIntersectionD2, vSecondIntersectionD2 = T::GetNullVector();
    T vFirstIntersectionE2, vSecondIntersectionE2 = T::GetNullVector();
    T vFirstIntersectionF2, vSecondIntersectionF2 = T::GetNullVector();
    T vFirstIntersectionG2, vSecondIntersectionG2 = T::GetNullVector();
    T vFirstIntersectionH2, vSecondIntersectionH2 = T::GetNullVector();
    EQIntersections eEndpointAndACoincide1 = LINE_SEGMENT_FROM_A1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA1, vSecondIntersectionA1);
    EQIntersections eEndpointAndACoincide2 = LINE_SEGMENT_FROM_A2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA2, vSecondIntersectionB1);
    EQIntersections eEndpointAndBCoincide1 = LINE_SEGMENT_FROM_B1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB1, vSecondIntersectionC1);
    EQIntersections eEndpointAndBCoincide2 = LINE_SEGMENT_FROM_B2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB2, vSecondIntersectionD1);
    EQIntersections eEndpointAndCCoincide1 = LINE_SEGMENT_FROM_C1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC1, vSecondIntersectionE1);
    EQIntersections eEndpointAndCCoincide2 = LINE_SEGMENT_FROM_C2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC2, vSecondIntersectionF1);
    EQIntersections eEndpointAndDCoincide1 = LINE_SEGMENT_FROM_D1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD1, vSecondIntersectionG1);
    EQIntersections eEndpointAndDCoincide2 = LINE_SEGMENT_FROM_D2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD2, vSecondIntersectionH1);
    EQIntersections eEndpointAndECoincide1 = LINE_SEGMENT_FROM_E1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE1, vSecondIntersectionA2);
    EQIntersections eEndpointAndECoincide2 = LINE_SEGMENT_FROM_E2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE2, vSecondIntersectionB2);
    EQIntersections eEndpointAndFCoincide1 = LINE_SEGMENT_FROM_F1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF1, vSecondIntersectionC2);
    EQIntersections eEndpointAndFCoincide2 = LINE_SEGMENT_FROM_F2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF2, vSecondIntersectionD2);
    EQIntersections eEndpointAndGCoincide1 = LINE_SEGMENT_FROM_G1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG1, vSecondIntersectionE2);
    EQIntersections eEndpointAndGCoincide2 = LINE_SEGMENT_FROM_G2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG2, vSecondIntersectionF2);
    EQIntersections eEndpointAndHCoincide1 = LINE_SEGMENT_FROM_H1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH1, vSecondIntersectionG2);
    EQIntersections eEndpointAndHCoincide2 = LINE_SEGMENT_FROM_H2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH2, vSecondIntersectionH2);

    // [Verification]
    BOOST_CHECK_EQUAL(eEndpointAndACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndCCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndDCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndDCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndECoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndECoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndFCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndFCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndGCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndGCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndHCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eEndpointAndHCoincide2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA1 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB1 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC1 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD1 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE1 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF1 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG1 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH1 == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vFirstIntersectionA2 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB2 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC2 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD2 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE2 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF2 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG2 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH2 == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vSecondIntersectionA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionG2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionH2 == EXPECTED_SECONDPOINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_AssertionFailsWhenLineSegmentEndpointsCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_A);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // [Preparation]
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_3, SQFloat::_3, SQFloat::_1, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q VERTEX_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // [Preparation]
    const float_q POINT_COMPONENTS_CONTAINED[] = { (float_q)1.5, (float_q)1.5, SQFloat::_2, SQFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_CONTAINED = QLineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q POINT_COMPONENTS_IN_EDGE[] = { (float_q)1.5, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_EDGE = QLineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_q POINT_COMPONENTS_IN_FACE[] = { (float_q)1.5, (float_q)1.5, SQFloat::_4, SQFloat::_1 };
    const T POINT_IN_FACE(POINT_COMPONENTS_IN_FACE);
    const QLineSegment3D<T> LINE_SEGMENT_IN_FACE = QLineSegment3D<T>(POINT_IN_FACE, POINT_IN_FACE);

    const float_q POINT_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const QLineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_q VERTEX_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_B_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_C_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_D_COMPONENTS[] = { SQFloat::_2, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_E_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_F_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VERTEX_G_COMPONENTS[] = { SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VERTEX_H_COMPONENTS[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const QBaseHexahedron<T> HEXAHEDRON = QBaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_Infinite;
    const EQIntersections EXPECTED_RESULT_IN_EDGE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_IN_FACE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = EQIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_IN_FACE = POINT_IN_FACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionContained = T::GetNullVector();
    T vFirstIntersectionInEdge = T::GetNullVector();
    T vFirstIntersectionInFace = T::GetNullVector();
    T vFirstIntersectionNotContained = T::GetNullVector();
    T vSecondIntersectionContained = T::GetNullVector();
    T vSecondIntersectionInEdge = T::GetNullVector();
    T vSecondIntersectionInFace = T::GetNullVector();
    T vSecondIntersectionNotContained = T::GetNullVector();

    const EQIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(HEXAHEDRON, vFirstIntersectionContained, vSecondIntersectionContained);
    const EQIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionInEdge, vSecondIntersectionInEdge);
    const EQIntersections eResultInFace = LINE_SEGMENT_IN_FACE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionInFace, vSecondIntersectionInFace);
    const EQIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(HEXAHEDRON, vFirstIntersectionNotContained, vSecondIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultInEdge, EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK_EQUAL(eResultInFace, EXPECTED_RESULT_IN_FACE);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vFirstIntersectionInFace == EXPECTED_POINT_IN_FACE);
    BOOST_CHECK(vFirstIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vSecondIntersectionInFace == EXPECTED_POINT_IN_FACE);
    BOOST_CHECK(vSecondIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns the distance to the furthest endpoint of the segment when the line and the plane don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MaxDistance_ReturnsTheDistanceToTheFurthestEndpointWhenLineAndPlaneDoNotIntersect_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_9, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_8, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = PLANE.PointDistance(LINE_SEGMENT.A);

	// [Execution]
    float_q fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the endpoints of the segment when the line and the plane are parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( MaxDistance_ReturnsTheDistanceToEndpointsWhenLineAndPlaneAreParallel, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d * SQFloat::_2, PLANE.b * -PLANE.d * SQFloat::_2, PLANE.c * -PLANE.d * SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d * SQFloat::_2 - SQFloat::_2, PLANE.b * -PLANE.d * SQFloat::_2 + SQFloat::_1, PLANE.c * -PLANE.d * SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = SQFloat::Abs(PLANE.d);

	// [Execution]
    float_q fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the line belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( MaxDistance_ReturnsZeroWhenLineBelongsToPlane, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SQFloat::_2, PLANE.b * -PLANE.d + SQFloat::_1, PLANE.c * -PLANE.d, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// [Execution]
    float_q fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the furthest endpoint of the segment when the line and the plane intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MaxDistance_ReturnsTheDistanceToTheFurthestEndpointWhenLineAndPlaneIntersect, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    const float_q POINT_A_COMPONENTS[] = { -SQFloat::_9, -SQFloat::_6, -SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_8, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = PLANE.PointDistance(LINE_SEGMENT.A);

	// [Execution]
    float_q fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( MaxDistance_AssertionFailsWhenPlaneIsNull, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const float_q POINT_A_COMPONENTS[] = { -SQFloat::_9, -SQFloat::_6, -SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_8, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.MaxDistance(NULL_PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns the distance to the closest endpoint of the segment when the line and the plane don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance_ReturnsTheDistanceToTheClosestEndpointWhenLineAndPlaneDoNotIntersect_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    const float_q POINT_A_COMPONENTS[] = { SQFloat::_9, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_8, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = PLANE.PointDistance(LINE_SEGMENT.B);

	// [Execution]
    float_q fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the endpoints of the segment when the line and the plane are parallel.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance_ReturnsTheDistanceToEndpointsWhenLineAndPlaneAreParallel, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d * SQFloat::_2, PLANE.b * -PLANE.d * SQFloat::_2, PLANE.c * -PLANE.d * SQFloat::_2, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d * SQFloat::_2 - SQFloat::_2, PLANE.b * -PLANE.d * SQFloat::_2 + SQFloat::_1, PLANE.c * -PLANE.d * SQFloat::_2, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = SQFloat::Abs(PLANE.d);

	// [Execution]
    float_q fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the line belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance_ReturnsZeroWhenLineBelongsToPlane, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    
    const float_q POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SQFloat::_2, PLANE.b * -PLANE.d + SQFloat::_1, PLANE.c * -PLANE.d, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// [Execution]
    float_q fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the furthest endpoint of the segment when the line and the plane intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance_ReturnsZeroWhenLineAndPlaneIntersect, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_1, -SQFloat::_1).Normalize();
    const float_q POINT_A_COMPONENTS[] = { -SQFloat::_9, -SQFloat::_6, -SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_8, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// [Execution]
    float_q fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance_AssertionFailsWhenPlaneIsNull, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const QPlane NULL_PLANE = QPlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const float_q POINT_A_COMPONENTS[] = { -SQFloat::_9, -SQFloat::_6, -SQFloat::_7, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_8, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.MinDistance(NULL_PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception must be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the line segment is correctly projected to the plane when it is in its negative side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_LineSegmentIsProjectedWhenItIsInNegativeSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_5, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_COMPONENTS_A[] = { (float_q)1.8095238095238098, (float_q)-3.3809523809523805, (float_q)6.238095238095239, SQFloat::_1 };
    const float_q EXPECTED_COMPONENTS_B[] = { (float_q)2.0952380952380958, (float_q)-1.8095238095238084, (float_q)5.3809523809523832, SQFloat::_1 };

    const QLineSegment3D<T> EXPECTED_LINE_SEGMENT = QLineSegment3D<T>(T(EXPECTED_COMPONENTS_A), T(EXPECTED_COMPONENTS_B));

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

	// [Execution]
    QLineSegment3D<T> projectedLineSegment = LINE_SEGMENT.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedLineSegment.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedLineSegment.A == EXPECTED_LINE_SEGMENT.A);
    BOOST_CHECK(projectedLineSegment.B == EXPECTED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the line segment is correctly projected to the plane when it is in its positive side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_LineSegmentIsProjectedWhenItIsInPositiveSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_COMPONENTS_A[] = { (float_q)-0.28571428571428581, (float_q)-5.5714285714285712, (float_q)-2.1428571428571432, SQFloat::_1 };
    const float_q EXPECTED_COMPONENTS_B[] = { (float_q)-0.95238095238095255, (float_q)4.0952380952380949, (float_q)-6.8095238095238102, SQFloat::_1 };
    const QLineSegment3D<T> EXPECTED_LINE_SEGMENT = QLineSegment3D<T>(T(EXPECTED_COMPONENTS_A), T(EXPECTED_COMPONENTS_B));

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, SQFloat::_10).Normalize();

	// [Execution]
    QLineSegment3D<T> projectedLineSegment = LINE_SEGMENT.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedLineSegment.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedLineSegment.A == EXPECTED_LINE_SEGMENT.A);
    BOOST_CHECK(projectedLineSegment.B == EXPECTED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the line segment is correctly projected to the plane when it intersects with the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_LineSegmentIsProjectedWhenItIntersectsWithPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_COMPONENTS_A[] = { SQFloat::_0, -SQFloat::_5, SQFloat::_0, SQFloat::_1 };
    const float_q EXPECTED_COMPONENTS_B[] = { (float_q)0.78571428571428581, (float_q)-4.4285714285714288, (float_q)-0.64285714285714235, SQFloat::_1 };
    const QLineSegment3D<T> EXPECTED_LINE_SEGMENT = QLineSegment3D<T>(T(EXPECTED_COMPONENTS_A), T(EXPECTED_COMPONENTS_B));

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

	// [Execution]
    QLineSegment3D<T> projectedLineSegment = LINE_SEGMENT.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedLineSegment.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedLineSegment.A == EXPECTED_LINE_SEGMENT.A);
    BOOST_CHECK(projectedLineSegment.B == EXPECTED_LINE_SEGMENT.B);
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

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

	// [Execution]
    QLineSegment3D<T> resultNonNotmalized = LINE_SEGMENT.ProjectToPlane(NONNORMALIZED_PLANE);
    QLineSegment3D<T> resultNormalized = LINE_SEGMENT.ProjectToPlane(NORMALIZED_PLANE);

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
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const QBasePlane NULL_PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.ProjectToPlane(NULL_PLANE);
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
/// Checks that it returns "negative side" when the line segment is "behind" the plane and doesn't intersect with it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheLineSegmentIsBehindPlaneAndTheyDoNotIntersect_Test, TQTemplateTypes )
{
    //     A        |
    //      \       |
    //       \      |-->
    //        B     |
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// [Execution]
    EQSpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the line segment is "in front" the plane and doesn't intersect with it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheLineSegmentIsInFrontPlaneAndTheyDoNotIntersect_Test, TQTemplateTypes )
{
    //    |         A
    //    |          \
    //    |-->        \
    //    |            B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// [Execution]
    EQSpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the line segment intersects with the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheLineSegmentIntersectsWithThePlane_Test, TQTemplateTypes )
{
    //     |  A
    //     | /
    //     |/
    //     |
    //    /|
    //   B |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { -SQFloat::_3, -SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_BothSides;

	// [Execution]
    EQSpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when the line segment belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsContainedWhenTheLineSegmentBelongsToPlane_Test, TQTemplateTypes )
{
    //       |
    //       A
    //       |
    //       B-->
    //       C
    //       |
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    LINE_SEGMENT = LINE_SEGMENT.ProjectToPlane(PLANE);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_Contained;

	// [Execution]
    EQSpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the line segment is "behind" the plane and one vertex belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheLineSegmentIsBehindPlaneAndOneVertexBelongsToPlane_Test, TQTemplateTypes )
{
    //     A  |
    //      \ |
    //       \|-->
    //        B
    //        |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// [Execution]
    EQSpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the line segment is "in front" of the plane and one vertex belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheLineSegmentIsInFrontPlaneAndOneVertexBelongsToPlane_Test, TQTemplateTypes )
{
    //    |  A
    //    | /
    //    |/-->
    //    B
    //    |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// [Execution]
    EQSpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is not different when the plane is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ResultIsNotDifferentWhenPlaneIsNotNormalized_Test, TQTemplateTypes )
{
    //     A  |
    //      \ |
    //       \|-->
    //        B
    //        |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane NONNORMALIZED_PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10);
    const QPlane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

	// [Execution]
    EQSpaceRelation eResultNonNotmalized = LINE_SEGMENT.SpaceRelation(NONNORMALIZED_PLANE);
    EQSpaceRelation eResultNormalized = LINE_SEGMENT.SpaceRelation(NORMALIZED_PLANE);

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
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const QBasePlane NULL_PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.SpaceRelation(NULL_PLANE);
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
/// Template method used by Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

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

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)6.0658639918226491, SQFloat::_8, (float_q)-10.419417382415922, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)3.5909902576697323, SQFloat::_8, (float_q)-8.6516504294495533, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that all the endpoints of the line segment are moved to the coordinate origin when transformation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_LineSegmentIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    QSpaceConversionMatrix CONVERSION = QSpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_7, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QLineSegment3D<T> EXPECTED_LINE_SEGMENT = QLineSegment3D<T>(POINT_A.Transform(CONVERSION),
                                                                      POINT_B.Transform(CONVERSION));

	// [Execution]
    QLineSegment3D<T> lineSegment = LINE_SEGMENT.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK(lineSegment == EXPECTED_LINE_SEGMENT);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_LineSegmentDoesNotChangeWhenTransformedByIdentityMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QSpaceConversionMatrix IDENTITY_MATRIX = QSpaceConversionMatrix::GetIdentity();

	const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_7, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QLineSegment3D<T> EXPECTED_LINE_SEGMENT = LINE_SEGMENT;

	// [Execution]
    QLineSegment3D<T> lineSegment = LINE_SEGMENT.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(lineSegment == EXPECTED_LINE_SEGMENT);
}

/// <summary>
/// Checks that the line segment is nullified when the matrix equals null.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_EndpointsAreNullifiedWhenMatrixIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QSpaceConversionMatrix NULL_MATRIX = QMatrix4x4::GetNullMatrix();

	const float_q POINT_A_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q POINT_B_COMPONENTS[] = { SQFloat::_5, SQFloat::_7, SQFloat::_9, SQFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(POINT_A, POINT_B);

    const QLineSegment3D<T> EXPECTED_LINE_SEGMENT = QLineSegment3D<T>(T::GetNullVector(), T::GetNullVector());

	// [Execution]
    QLineSegment3D<T> lineSegment = LINE_SEGMENT.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(lineSegment == EXPECTED_LINE_SEGMENT);
}

/// <summary>
/// Template method used by TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

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

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_3, SQFloat::_7, -SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)0.52512626584708322, SQFloat::_7, (float_q)-1.2322330470336311, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsNull_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that all the endpoints of the line segment are moved to the position of the pivot point when transformation is null.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that a common line segment is correctly translated using common translation vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const QVector3 TRANSLATION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QVector3 TRANSLATION = QVector3::GetNullVector();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly translated using common translation values.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_q TRANSLATION_X = SQFloat::_1;
    const float_q TRANSLATION_Y = SQFloat::_2;
    const float_q TRANSLATION_Z = SQFloat::_3;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const float_q TRANSLATION_X = SQFloat::_0;
    const float_q TRANSLATION_Y = SQFloat::_0;
    const float_q TRANSLATION_Z = SQFloat::_0;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Template method used by Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly translated using common translation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetNullMatrix();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that a line segment is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_LineSegmentIsNotRotatedWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_LineSegmentIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
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
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { 0.70710659f, -SQFloat::_4, -2.1213202f, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { -1.4142138f, -SQFloat::_4, -2.8284268f, SQFloat::_1 };
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { 0.70710678118654768, -SQFloat::_4, -2.1213203435596428, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { -1.4142135623730949, -SQFloat::_4, -2.8284271247461907, SQFloat::_1 };
#endif

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_LineSegmentIsNotRotatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_LineSegmentIsCorrectlyTransformedByCommonQuaternions_Test, TQTemplateTypes )
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
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)0.29289321881345243, (float_q)1.2928932188134525, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)-1.1213203435596424, (float_q)2.7071067811865479, SQFloat::_4, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_LineSegmentIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_LineSegmentIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
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
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)-1.1213203435596424, SQFloat::_1, (float_q)2.2928932188134521, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when the rotation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_LineSegmentIsNotRotateWithPivotdWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the rotation matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    
    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_8, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the components of the scaling vector equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_LineSegmentIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    const QVector3 SCALE = QVector3::GetNullVector();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling values.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_8, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the values equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_LineSegmentIsNotScaledWhenValuesEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the values equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenValuesEqualZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_8, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_LineSegmentIsNotScaledWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetIdentity();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    
    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_6, SQFloat::_0, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the components of the scaling vector equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_LineSegmentIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToPivotPositionWhenVectorIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    const QVector3 SCALE = QVector3::GetNullVector();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling values.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_6, SQFloat::_0, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the values equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_LineSegmentIsNotScaledWhenValuesEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the values equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedPivotPositionWhenValuesEqualZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_6, SQFloat::_0, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_LineSegmentIsNotTranslatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetIdentity();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };

    const QLineSegment3D<T> LINE_SEGMENT = QLineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    QLineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

// [TODO] Thund: Protected methods has not been tested yet.
// [TODO] Thund: Some additional tests could be added for IntersectionPoint that receives a QBaseHexahedron:
//                  -Two endpoints coinciding with 2 different vertices

// End - Test Suite: QLineSegment3D
QTEST_SUITE_END()
