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

#include "QLineSegment.h"
#include "QLineSegmentWhiteBox.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QBaseOrb.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QLineSegment;
using Kinesis::QuimeraEngine::Tools::Math::Test::QLineSegmentWhiteBox;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector2, QVector3, QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QLineSegment_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// Execution
    QLineSegment<T> lineSegmentUT;

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if copy constructor sets segment's points properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const QLineSegment<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if points are copied cortectly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const QBaseLineSegment<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// Execution
    QLineSegment<T> lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a unit-length line which point A is placed at origin and point B is contained in the positive X axis.
/// </summary>
QTEST_CASE_TEMPLATE ( GetUnitLine_AUnitLengthSegmentPlacedAtOriginAndContainedInPositiveXAxisIsReturned_Test, TQTemplateTypes )
{
    // Preparation
    const T EXPECTED_VALUE_FOR_A = T::GetZeroVector();
    const T EXPECTED_VALUE_FOR_B = T::GetUnitVectorX();

	// Execution
    QLineSegment<T> lineSegmentUT = QLineSegment<T>::GetUnitLine();

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a zero-length line which points A and B are placed at origin.
/// </summary>
QTEST_CASE_TEMPLATE ( GetLineZero_AZeroLengthSegmentPlacedAtOriginIsReturned_Test, TQTemplateTypes )
{
    // Preparation
    const T EXPECTED_VALUE_FOR_A = T::GetZeroVector();
    const T EXPECTED_VALUE_FOR_B = T::GetZeroVector();

	// Execution
    QLineSegment<T> lineSegmentUT = QLineSegment<T>::GetLineZero();

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line is correctly assigned to another line.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_LineIsAssignedProperlyToAnother_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const QBaseLineSegment<T> OTHER_LINE = QBaseLineSegment<T>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment<T> lineSegmentUT;
    lineSegmentUT = OTHER_LINE;

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the correct length is returned when using a common line segment.
/// </summary>
QTEST_CASE_TEMPLATE ( GetLength_TheCorrectLengthIsReturnedForCommonLine_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const float_q EXPECTED_LENGTH = VALUE_FOR_A.Distance(VALUE_FOR_B);

    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// Execution
    float_q fLength = LINE_SEGMENT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the W components of line points doesn't affect the result when using 4D vectors.
/// </summary>
QTEST_CASE ( GetLength_WComponentDoesNotAffectTheResult_Test )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_2 };
    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_9 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_3 };

    const QVector4 VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const QVector4 VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QVector4 VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const QVector4 VALUE_FOR_B2(VECTOR_COMPONENTS_B2);

    const QLineSegment<QVector4> LINE_SEGMENT1 = QLineSegment<QVector4>(VALUE_FOR_A1, VALUE_FOR_B1);
    const QLineSegment<QVector4> LINE_SEGMENT2 = QLineSegment<QVector4>(VALUE_FOR_A2, VALUE_FOR_B2);

	// Execution
    float_q fLength1 = LINE_SEGMENT1.GetLength();
    float_q fLength2 = LINE_SEGMENT2.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the length is always a positive value.
/// </summary>
QTEST_CASE_TEMPLATE ( GetLength_IsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>( VALUE_FOR_A,  VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(-VALUE_FOR_A,  VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>( VALUE_FOR_A, -VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(-VALUE_FOR_A, -VALUE_FOR_B);

	// Execution
    float_q fLengthBothPositive = LINE_SEGMENT1.GetLength();
    float_q fLengthANegative = LINE_SEGMENT2.GetLength();
    float_q fLengthBNegative = LINE_SEGMENT3.GetLength();
    float_q fLengthBothNegative = LINE_SEGMENT4.GetLength();

    // Verification
    BOOST_CHECK(SQFloat::IsPositive(fLengthBothPositive));
    BOOST_CHECK(SQFloat::IsPositive(fLengthANegative));
    BOOST_CHECK(SQFloat::IsPositive(fLengthBNegative));
    BOOST_CHECK(SQFloat::IsPositive(fLengthBothNegative));
}

/// <summary>
/// Checks that zero is returned when A and B points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetLength_ReturnsZeroWhenBothPointsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B = VALUE_FOR_A;
    const float_q EXPECTED_LENGTH = SQFloat::_0;

    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// Execution
    float_q fLength = LINE_SEGMENT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the same length is returned whether the name has each point.
/// </summary>
QTEST_CASE_TEMPLATE ( GetLength_PointsOrderDoesNotMatter_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_2[] = { -SQFloat::_4, -SQFloat::_5, -SQFloat::_6, -SQFloat::_8 };

    const T VALUE_FOR_1(VECTOR_COMPONENTS_1);
    const T VALUE_FOR_2(VECTOR_COMPONENTS_2);

    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_1, VALUE_FOR_2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_2, VALUE_FOR_1);

	// Execution
    float_q fLength1 = LINE_SEGMENT1.GetLength();
    float_q fLength2 = LINE_SEGMENT2.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the correct center point of the line is calculated for a common segment.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCenter_TheCenterIsCorrectlyCalculatedForCommonLine_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const T EXPECTED_CENTER = VALUE_FOR_A + (VALUE_FOR_B - VALUE_FOR_A) * SQFloat::_0_5;

    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// Execution
    T vCenter = LINE_SEGMENT.GetCenter();

    // Verification
    BOOST_CHECK(vCenter == EXPECTED_CENTER);
}

/// <summary>
/// Checks that the name of the line's points doesn't matter.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCenter_PointsOrderDoesNotMatter_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_2[] = { -SQFloat::_4, -SQFloat::_5, -SQFloat::_6, -SQFloat::_8 };

    const T VALUE_FOR_1(VECTOR_COMPONENTS_1);
    const T VALUE_FOR_2(VECTOR_COMPONENTS_2);

    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_1, VALUE_FOR_2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_2, VALUE_FOR_1);

	// Execution
    T vCenter1 = LINE_SEGMENT1.GetCenter();
    T vCenter2 = LINE_SEGMENT2.GetCenter();

    // Verification
    BOOST_CHECK(vCenter1 == vCenter2);
}

/// <summary>
/// Checks that when the line segment's end points coincide the center also coincides with them.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCenter_CenterEqualsSegmentEndPointsWhenTheyCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B = VALUE_FOR_A;

    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// Execution
    T vCenter = LINE_SEGMENT.GetCenter();

    // Verification
    BOOST_CHECK(vCenter == VALUE_FOR_A);
    BOOST_CHECK(vCenter == VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns False when lines don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenLinesDoNotIntersect_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when lines intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TQTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when lines coincide totally.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesCoincideTotally_Test, TQTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3 = LINE_SEGMENT1.Intersection(LINE_SEGMENT3); // II
    bool bResult4 = LINE_SEGMENT3.Intersection(LINE_SEGMENT1); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenAnEndPointIsContainedInTheOtherLine_Test, TQTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3 = LINE_SEGMENT1.Intersection(LINE_SEGMENT4); // II
    bool bResult4 = LINE_SEGMENT4.Intersection(LINE_SEGMENT1); // II
    bool bResult5 = LINE_SEGMENT3.Intersection(LINE_SEGMENT2); // III
    bool bResult6 = LINE_SEGMENT2.Intersection(LINE_SEGMENT3); // III
    bool bResult7 = LINE_SEGMENT3.Intersection(LINE_SEGMENT4); // IV
    bool bResult8 = LINE_SEGMENT4.Intersection(LINE_SEGMENT3); // IV

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the 2 lines share only one of their end points.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesShareOneEndPointOnly_Test, TQTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegment<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegment<T> LINE_SEGMENT6 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_q VECTOR_COMPONENTS_A4[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B4[] = { SQFloat::_6, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const QLineSegment<T> LINE_SEGMENT7 = QLineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const QLineSegment<T> LINE_SEGMENT8 = QLineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1  = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2  = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3  = LINE_SEGMENT1.Intersection(LINE_SEGMENT4); // II
    bool bResult4  = LINE_SEGMENT4.Intersection(LINE_SEGMENT1); // II
    bool bResult5  = LINE_SEGMENT3.Intersection(LINE_SEGMENT2); // III
    bool bResult6  = LINE_SEGMENT2.Intersection(LINE_SEGMENT3); // III
    bool bResult7  = LINE_SEGMENT3.Intersection(LINE_SEGMENT4); // IV
    bool bResult8  = LINE_SEGMENT4.Intersection(LINE_SEGMENT3); // IV
    bool bResult9  = LINE_SEGMENT1.Intersection(LINE_SEGMENT5); // V
    bool bResult10 = LINE_SEGMENT5.Intersection(LINE_SEGMENT1); // V
    bool bResult11 = LINE_SEGMENT1.Intersection(LINE_SEGMENT6); // VI
    bool bResult12 = LINE_SEGMENT6.Intersection(LINE_SEGMENT1); // VI
    bool bResult13 = LINE_SEGMENT3.Intersection(LINE_SEGMENT5); // VII
    bool bResult14 = LINE_SEGMENT5.Intersection(LINE_SEGMENT3); // VII
    bool bResult15 = LINE_SEGMENT3.Intersection(LINE_SEGMENT6); // VIII
    bool bResult16 = LINE_SEGMENT6.Intersection(LINE_SEGMENT3); // VIII
    bool bResult17 = LINE_SEGMENT1.Intersection(LINE_SEGMENT7); // IX
    bool bResult18 = LINE_SEGMENT7.Intersection(LINE_SEGMENT1); // IX
    bool bResult19 = LINE_SEGMENT3.Intersection(LINE_SEGMENT7); // X
    bool bResult20 = LINE_SEGMENT7.Intersection(LINE_SEGMENT3); // X
    bool bResult21 = LINE_SEGMENT1.Intersection(LINE_SEGMENT8); // XI
    bool bResult22 = LINE_SEGMENT8.Intersection(LINE_SEGMENT1); // XI
    bool bResult23 = LINE_SEGMENT3.Intersection(LINE_SEGMENT8); // XII
    bool bResult24 = LINE_SEGMENT8.Intersection(LINE_SEGMENT3); // XII

    // Verification
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult9,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult10, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult11, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult12, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult13, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult14, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult15, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult16, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult17, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult18, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult19, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult20, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult21, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult22, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult23, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult24, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // A2---(A1B1)---B2
    //
    //        I

    // Preparation
    float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsExpectedResultsWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // A2---(A1B1)---B2
    //
    //        I

    // Preparation
    float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_q VECTOR_COMPONENTS_A3B3[] = { SQFloat::_6, SQFloat::_8, SQFloat::_9, SQFloat::_1 };
    const T VALUE_FOR_A3B3(VECTOR_COMPONENTS_A3B3);
    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_A3B3, VALUE_FOR_A3B3);

    const bool EXPECTED_RESULT_WHEN_INTERSECT = true;
    const bool EXPECTED_RESULT_WHEN_DONT_INTERSECT = false;

	// Execution
    bool bResultIntersection1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);
    bool bResultIntersection2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1);
    bool bResultNoIntersection1 = LINE_SEGMENT3.Intersection(LINE_SEGMENT2);
    bool bResultNoIntersection2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT3);

    // Verification
    BOOST_CHECK_EQUAL(bResultIntersection1, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(bResultIntersection2, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(bResultNoIntersection1, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK_EQUAL(bResultNoIntersection2, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when the segment doesn't intersect the other but would do it if it was lengthened to the infinite.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenSegmentDoesNotIntersectButWouldDoIfTheyHadInfiniteLength_Test, TQTemplateTypes )
{
    // A1       A2
    //  \      /
    //   B1   /
    //    ·  /
    //     ·/
    //     /·
    //   B2  ·

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1);

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesCoincidePartially_Test, TQTemplateTypes )
{
    //
    // A1---A2---B1---B2    A1---B2---B1---A2    B1---A2---A1---B2    B1---B2---A1---A2
    //
    //         I                   II                   III                  IV

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3 = LINE_SEGMENT1.Intersection(LINE_SEGMENT4); // II
    bool bResult4 = LINE_SEGMENT4.Intersection(LINE_SEGMENT1); // II
    bool bResult5 = LINE_SEGMENT3.Intersection(LINE_SEGMENT2); // III
    bool bResult6 = LINE_SEGMENT2.Intersection(LINE_SEGMENT3); // III
    bool bResult7 = LINE_SEGMENT3.Intersection(LINE_SEGMENT4); // IV
    bool bResult8 = LINE_SEGMENT4.Intersection(LINE_SEGMENT3); // IV

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one line is totally contained in the other.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenOneSegmentIsContainedInTheOther_Test, TQTemplateTypes )
{
    //
    // A1---A2---B2---B1    A1---A3----B1B3    A1---B3---B1A3    B1---A3---A1B3    B1---B3---A1A3
    //
    //         I                  II                 III               IV                V

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegment<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3  = LINE_SEGMENT1.Intersection(LINE_SEGMENT4);// II
    bool bResult4  = LINE_SEGMENT4.Intersection(LINE_SEGMENT1);// II
    bool bResult5  = LINE_SEGMENT1.Intersection(LINE_SEGMENT5);// III
    bool bResult6  = LINE_SEGMENT5.Intersection(LINE_SEGMENT1);// III
    bool bResult7  = LINE_SEGMENT3.Intersection(LINE_SEGMENT4);// IV
    bool bResult8  = LINE_SEGMENT4.Intersection(LINE_SEGMENT3);// IV
    bool bResult9  = LINE_SEGMENT3.Intersection(LINE_SEGMENT5);// V
    bool bResult10 = LINE_SEGMENT5.Intersection(LINE_SEGMENT3);// V

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult9, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult10, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line doesn't intersect the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenLineDoesNotIntersectTheOrb_Test, TQTemplateTypes )
{
    // A1           ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       B1

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_10, SQFloat::_10, SQFloat::_10, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one end point is inside the orb and the other is outside it.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenOnlyOneEndPointIsInsideTheOrb_Test, TQTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------|-B1  |    B1---------|-A1  |
    //             \___/                 \___/
    //
    //        I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the line is tangent to the orb by only one end point.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsTangentToTheOrbByAnEndPoint_Test, TQTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------B1 x  |    B1---------A1 x  |
    //             \___/                 \___/
    //
    //        I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsContainedInTheOrb_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /            \
    //        |  A1---B1   |
    //        \            /
    //          ` ______ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_3 );

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the line is contained in the orb and only one end point coincides with the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsContainedInTheOrbAndOneEndPointCoincidesWithTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ______                ______
    //          ´        `            ´        `
    //        /           \         /           \
    //        |      A1---B1        |      B1---A1
    //        \           /         \           /
    //          ` _____ ´             ` _____ ´
    //
    //              I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the orb and the 2 end points coincide with the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsContainedInTheOrbAndTheTwoEndPointsCoincideWithTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //       A1-----------B1
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects the orb in two points (and the line is not contained in the orb).
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIntersectsTheOrbInTwoPoints_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //   A1------------------B1
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is tangent to the orb (the tangent point is not A or B).
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsTangentToTheOrb_Test, TQTemplateTypes )
{
    //        A1   _____
    //        |  ´       `
    //        |/           \
    //        |      x     |
    //        |\           /
    //        B1 ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the segment does not intersect the orb but would do it if the segment had an infinite length.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenTheSegmentDoesNotIntersectTheOrbButWouldDoIfItWasInifinite_Test, TQTemplateTypes )
{
    //                ___
    //              /     \
    // A1----B1····|···x···|····
    //              \ ___ /
    //
    //         I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = {-SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TQTemplateTypes )
{
    //
    // A1----------x-------B1
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_0 );

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.Intersection(ORB);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.Intersection(ORB);
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
/// Checks that an assertion fails when the length of the line equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheLengthOfSegmentEqualsZero_Test, TQTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_7 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT1.Intersection(ORB);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsExpectedResultsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //
    // A1----------x-------B1
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB_CONTAINED = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_CONTAINED), SQFloat::_0 );

    float_q VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SQFloat::_9, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB_NOT_CONTAINED = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED), SQFloat::_0 );

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// Execution
    bool bResultContained = LINE_SEGMENT.Intersection(ORB_CONTAINED);
    bool bResultNotContained = LINE_SEGMENT.Intersection(ORB_NOT_CONTAINED);

    // Verification
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection2_ReturnsExpectedResultsWhenTheLengthOfSegmentEqualsZero_Test, TQTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;

    // Preparation
    const float_q VECTOR_COMPONENTS_CONTAINED[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T POINT_CONTAINED(VECTOR_COMPONENTS_CONTAINED);
    const QLineSegment<T> LINE_SEGMENT_CONTAINED = QLineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q VECTOR_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_4, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(VECTOR_COMPONENTS_NOT_CONTAINED);
    const QLineSegment<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// Execution
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(ORB);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(ORB);
    
    // Verification
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it doesn't return any intersection point when line segments don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_NoIntersectionPointReturnedWhenLinesDoNotIntersect_Test, TQTemplateTypes )
{
    // A1-------B1
    //
    // A2-------B2

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that the output point doesn't change when there is no intersection.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_OutputPointIsNotModifiedWhenThereIsNoIntersection_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_8, -SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT);

    // Verification
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when lines intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_OneIntersectionPointIsReturnedWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TQTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_EXPECTED[] = { SQFloat::_1 + SQFloat::_0_5, SQFloat::_1 + SQFloat::_0_5, SQFloat::_4 + SQFloat::_0_5, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when lines coincide totally.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsInfinitePointsWhenLinesCoincideTotally_Test, TQTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT3 = T::GetZeroVector();
    T OUTPUT_POINT4 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    EQIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT3); // II
    EQIntersections eResult4 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT4); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenAnEndPointIsContainedInTheOtherLine_Test, TQTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_EXPECTED[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT3 = T::GetZeroVector();
    T OUTPUT_POINT4 = T::GetZeroVector();
    T OUTPUT_POINT5 = T::GetZeroVector();
    T OUTPUT_POINT6 = T::GetZeroVector();
    T OUTPUT_POINT7 = T::GetZeroVector();
    T OUTPUT_POINT8 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    EQIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT3); // II
    EQIntersections eResult4 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT4); // II
    EQIntersections eResult5 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT5); // III
    EQIntersections eResult6 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT6); // III
    EQIntersections eResult7 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT7); // IV
    EQIntersections eResult8 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT8); // IV

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the 2 lines share only one of their end points.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenLinesShareOneEndPointOnly_Test, TQTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegment<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegment<T> LINE_SEGMENT6 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const float_q VECTOR_COMPONENTS_A4[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B4[] = { SQFloat::_6, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const QLineSegment<T> LINE_SEGMENT7 = QLineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const QLineSegment<T> LINE_SEGMENT8 = QLineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const float_q VECTOR_COMPONENTS_EXPECTED1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_EXPECTED2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT3 = T::GetZeroVector();
    T OUTPUT_POINT4 = T::GetZeroVector();
    T OUTPUT_POINT5 = T::GetZeroVector();
    T OUTPUT_POINT6 = T::GetZeroVector();
    T OUTPUT_POINT7 = T::GetZeroVector();
    T OUTPUT_POINT8 = T::GetZeroVector();
    T OUTPUT_POINT9 = T::GetZeroVector();
    T OUTPUT_POINT10 = T::GetZeroVector();
    T OUTPUT_POINT11 = T::GetZeroVector();
    T OUTPUT_POINT12 = T::GetZeroVector();
    T OUTPUT_POINT13 = T::GetZeroVector();
    T OUTPUT_POINT14 = T::GetZeroVector();
    T OUTPUT_POINT15 = T::GetZeroVector();
    T OUTPUT_POINT16 = T::GetZeroVector();
    T OUTPUT_POINT17 = T::GetZeroVector();
    T OUTPUT_POINT18 = T::GetZeroVector();
    T OUTPUT_POINT19 = T::GetZeroVector();
    T OUTPUT_POINT20 = T::GetZeroVector();
    T OUTPUT_POINT21 = T::GetZeroVector();
    T OUTPUT_POINT22 = T::GetZeroVector();
    T OUTPUT_POINT23 = T::GetZeroVector();
    T OUTPUT_POINT24 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    EQIntersections eResult2  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    EQIntersections eResult3  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT3); // II
    EQIntersections eResult4  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT4); // II
    EQIntersections eResult5  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT5); // III
    EQIntersections eResult6  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT6); // III
    EQIntersections eResult7  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT7); // IV
    EQIntersections eResult8  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT8); // IV
    EQIntersections eResult9  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT5, OUTPUT_POINT9); // V
    EQIntersections eResult10 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT10); // V
    EQIntersections eResult11 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT6, OUTPUT_POINT11); // VI
    EQIntersections eResult12 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT12); // VI
    EQIntersections eResult13 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT5, OUTPUT_POINT13); // VII
    EQIntersections eResult14 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT14); // VII
    EQIntersections eResult15 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT6, OUTPUT_POINT15); // VIII
    EQIntersections eResult16 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT16); // VIII
    EQIntersections eResult17 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT7, OUTPUT_POINT17); // IX
    EQIntersections eResult18 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT18); // IX
    EQIntersections eResult19 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT7, OUTPUT_POINT19); // X
    EQIntersections eResult20 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT20); // X
    EQIntersections eResult21 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT8, OUTPUT_POINT21); // XI
    EQIntersections eResult22 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT22); // XI
    EQIntersections eResult23 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT8, OUTPUT_POINT23); // XII
    EQIntersections eResult24 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT24); // XII

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult9, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult10, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult11, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult12, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult13, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult14, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult15, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult16, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult17, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult18, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult19, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult20, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult21, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult22, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult23, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult24, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT11 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT12 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT13 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT14 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT15 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT16 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT17 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT18 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT19 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT20 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT21 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT22 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT23 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT24 == EXPECTED_POINT2);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // A2---(A1B1)---B2
    //
    //        I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsExpectedResultsWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // A2---(A1B1)---B2
    //
    //        I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    const float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_q VECTOR_COMPONENTS_A3B3[] = { SQFloat::_6, SQFloat::_8, SQFloat::_9, SQFloat::_1 };
    const T VALUE_FOR_A3B3(VECTOR_COMPONENTS_A3B3);
    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_A3B3, VALUE_FOR_A3B3);

    const EQIntersections EXPECTED_RESULT_WHEN_INTERSECT = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_WHEN_DONT_INTERSECT = EQIntersections::E_None;

    const T EXPECTED_INTERSECTION_POINT = VALUE_FOR_A1B1;
    const T EXPECTED_NO_INTERSECTION_POINT = T::GetZeroVector();

	// Execution
    T vIntersection1 = T::GetZeroVector();
    T vIntersection2 = T::GetZeroVector();
    T vNoIntersection1 = T::GetZeroVector();
    T vNoIntersection2 = T::GetZeroVector();
    
    EQIntersections eResultIntersection1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, vIntersection1);
    EQIntersections eResultIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, vIntersection2);
    EQIntersections eResultNoIntersection1 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, vNoIntersection1);
    EQIntersections eResultNoIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, vNoIntersection2);

    // Verification
    BOOST_CHECK_EQUAL(eResultIntersection1, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(eResultIntersection2, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(eResultNoIntersection1, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK_EQUAL(eResultNoIntersection2, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK(vIntersection1 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vNoIntersection1 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vNoIntersection2 == EXPECTED_NO_INTERSECTION_POINT);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it doesn't return any intersection point when the segment doesn't intersect the other but would do it if it was lengthened to the infinite.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoPointWhenSegmentDoesNotIntersectButWouldDoIfTheyHadInfiniteLength_Test, TQTemplateTypes )
{
    // A1       A2
    //  \      /
    //   B1   /
    //    ·  /
    //     ·/
    //     /·
    //   B2  ·

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoPointsWhenLinesCoincidePartially_Test, TQTemplateTypes )
{
    // A2---A1---B1---B2  I
    //
    // A2---B1---A1---B2  II
    //
    // A2---A1---B2---B1  III
    //
    // A2---B1---B2---A1  IV
    //
    // B2---A1---A2---B1  V
    //
    // B2---B1---A2---A1  VI
    //
    // A1---A2---B2---B1  VII
    //
    // A1---B2---A2---B1  VIII

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q FIRST_POSITION_COMPONENTS[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q SECOND_POSITION_COMPONENTS[] = { SQFloat::_2, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q THIRD_POSITION_COMPONENTS[] = { SQFloat::_3, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q FOURTH_POSITION_COMPONENTS[] = { SQFloat::_4, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);
    const T FOURTH_POSITION = T(FOURTH_POSITION_COMPONENTS);

    const QLineSegment<T> LINE_SEGMENTA_1 = QLineSegment<T>(SECOND_POSITION, THIRD_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_1 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_2 = QLineSegment<T>(THIRD_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_2 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_3 = QLineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_3 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_4 = QLineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_4 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_5 = QLineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_5 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_6 = QLineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_6 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_7 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_7 = QLineSegment<T>(SECOND_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_8 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_8 = QLineSegment<T>(THIRD_POSITION, SECOND_POSITION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const T EXPECTED_POINT1 = SECOND_POSITION;
    const T EXPECTED_POINT2 = THIRD_POSITION;
    const T EXPECTED_POINT3 = SECOND_POSITION;
    const T EXPECTED_POINT4 = THIRD_POSITION;
    const T EXPECTED_POINT5 = SECOND_POSITION;
    const T EXPECTED_POINT6 = THIRD_POSITION;
    const T EXPECTED_POINT7 = SECOND_POSITION;
    const T EXPECTED_POINT8 = SECOND_POSITION;
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();
    T OUTPUT_POINT3 = T::GetZeroVector();
    T OUTPUT_POINT4 = T::GetZeroVector();
    T OUTPUT_POINT5 = T::GetZeroVector();
    T OUTPUT_POINT6 = T::GetZeroVector();
    T OUTPUT_POINT7 = T::GetZeroVector();
    T OUTPUT_POINT8 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_POINT1); // I
    EQIntersections eResult2 = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_POINT2); // II
    EQIntersections eResult3 = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_POINT3); // III
    EQIntersections eResult4 = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_POINT4); // IV
    EQIntersections eResult5 = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_POINT5); // V
    EQIntersections eResult6 = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_POINT6); // VI
    EQIntersections eResult7 = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_POINT7); // VII
    EQIntersections eResult8 = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_POINT8); // VIII

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT3);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT4);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT5);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT6);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT7);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT8);
}

/// <summary>
/// Checks that it returns two intersection points when one line is totally contained in the other.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoPointsWhenOneSegmentIsContainedInTheOther_Test, TQTemplateTypes )
{
    // A1A2---B1---B2  I
    //
    // A1A2---B2---B1  II
    //
    // B1B2---A1---A2  III
    //
    // B1B2---A2---A1  IV
    //
    // A1B2---B1---A2  V
    //
    // A1B2---A2---B1  VI
    //
    // A2B1---A1---B2  VII
    //
    // A2B1---B2---A1  VIII
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q FIRST_POSITION_COMPONENTS[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q SECOND_POSITION_COMPONENTS[] = { SQFloat::_2, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q THIRD_POSITION_COMPONENTS[] = { SQFloat::_3, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);

    const QLineSegment<T> LINE_SEGMENTA_1 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_1 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_2 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_2 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_3 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_3 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_4 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_4 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_5 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_5 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_6 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_6 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_7 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_7 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_8 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_8 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const T EXPECTED_POINT1 = FIRST_POSITION;
    const T EXPECTED_POINT2 = FIRST_POSITION;
    const T EXPECTED_POINT3 = SECOND_POSITION;
    const T EXPECTED_POINT4 = SECOND_POSITION;
    const T EXPECTED_POINT5 = FIRST_POSITION;
    const T EXPECTED_POINT6 = FIRST_POSITION;
    const T EXPECTED_POINT7 = SECOND_POSITION;
    const T EXPECTED_POINT8 = SECOND_POSITION;
    T OUTPUT_POINT1  = T::GetZeroVector();
    T OUTPUT_POINT2  = T::GetZeroVector();
    T OUTPUT_POINT3  = T::GetZeroVector();
    T OUTPUT_POINT4  = T::GetZeroVector();
    T OUTPUT_POINT5  = T::GetZeroVector();
    T OUTPUT_POINT6  = T::GetZeroVector();
    T OUTPUT_POINT7  = T::GetZeroVector();
    T OUTPUT_POINT8  = T::GetZeroVector();

	// Execution
    EQIntersections eResult1  = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_POINT1);// I
    EQIntersections eResult2  = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_POINT2);// II
    EQIntersections eResult3  = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_POINT3);// III
    EQIntersections eResult4  = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_POINT4);// IV
    EQIntersections eResult5  = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_POINT5);// V
    EQIntersections eResult6  = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_POINT6);// VI
    EQIntersections eResult7  = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_POINT7);// VII
    EQIntersections eResult8  = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_POINT8);// VIII

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT3);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT4);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT5);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT6);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT7);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT8);
}

/// <summary>
/// Checks that it doesn't return any intersection point when line segments don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_NoIntersectionPointReturnedWhenLinesDoNotIntersect_Test, TQTemplateTypes )
{
    // A1-------B1
    //
    // A2-------B2

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetZeroVector();
    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    T OUTPUT_FIRSTPOINT = T::GetZeroVector();
    T OUTPUT_SECONDPOINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT, OUTPUT_SECONDPOINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that the output point doesn't change when there is no intersection.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_OutputPointIsNotModifiedWhenThereIsNoIntersection_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_8, -SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT = T::GetZeroVector();
    T OUTPUT_SECONDPOINT = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT, OUTPUT_SECONDPOINT);

    // Verification
    BOOST_CHECK(OUTPUT_FIRSTPOINT == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when lines intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_OneIntersectionPointIsReturnedWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TQTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_EXPECTED[] = { SQFloat::_1 + SQFloat::_0_5, SQFloat::_1 + SQFloat::_0_5, SQFloat::_4 + SQFloat::_0_5, SQFloat::_1 };
    const T EXPECTED_FIRSTPOINT = T(VECTOR_COMPONENTS_EXPECTED);
    const T EXPECTED_SECONDPOINT = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT = T::GetZeroVector();
    T OUTPUT_SECONDPOINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT, OUTPUT_SECONDPOINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when lines coincide totally.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsInfinitePointsWhenLinesCoincideTotally_Test, TQTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT1 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT2 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT3 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT4 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT1 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT2 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT3 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT4 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
    EQIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // II
    EQIntersections eResult4 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndPointIsContainedInTheOtherLine_Test, TQTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_EXPECTED[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_FIRSTPOINT = T(VECTOR_COMPONENTS_EXPECTED);
    const T EXPECTED_SECONDPOINT = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT1 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT2 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT3 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT4 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT5 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT6 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT7 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT8 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT1 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT2 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT3 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT4 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT5 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT6 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT7 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT8 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
    EQIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // II
    EQIntersections eResult4 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // II
    EQIntersections eResult5 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5); // III
    EQIntersections eResult6 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6); // III
    EQIntersections eResult7 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7); // IV
    EQIntersections eResult8 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8); // IV

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the 2 lines share only one of their end points.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenLinesShareOneEndPointOnly_Test, TQTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegment<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegment<T> LINE_SEGMENT6 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const float_q VECTOR_COMPONENTS_A4[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B4[] = { SQFloat::_6, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const QLineSegment<T> LINE_SEGMENT7 = QLineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const QLineSegment<T> LINE_SEGMENT8 = QLineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const float_q VECTOR_COMPONENTS_EXPECTED1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_EXPECTED2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    const T EXPECTED_SECONDPOINT = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT1 = T::GetZeroVector();    T OUTPUT_SECONDPOINT1 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT2 = T::GetZeroVector();    T OUTPUT_SECONDPOINT2 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT3 = T::GetZeroVector();    T OUTPUT_SECONDPOINT3 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT4 = T::GetZeroVector();    T OUTPUT_SECONDPOINT4 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT5 = T::GetZeroVector();    T OUTPUT_SECONDPOINT5 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT6 = T::GetZeroVector();    T OUTPUT_SECONDPOINT6 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT7 = T::GetZeroVector();    T OUTPUT_SECONDPOINT7 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT8 = T::GetZeroVector();    T OUTPUT_SECONDPOINT8 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT9 = T::GetZeroVector();    T OUTPUT_SECONDPOINT9 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT10 = T::GetZeroVector();   T OUTPUT_SECONDPOINT10 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT11 = T::GetZeroVector();   T OUTPUT_SECONDPOINT11 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT12 = T::GetZeroVector();   T OUTPUT_SECONDPOINT12 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT13 = T::GetZeroVector();   T OUTPUT_SECONDPOINT13 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT14 = T::GetZeroVector();   T OUTPUT_SECONDPOINT14 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT15 = T::GetZeroVector();   T OUTPUT_SECONDPOINT15 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT16 = T::GetZeroVector();   T OUTPUT_SECONDPOINT16 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT17 = T::GetZeroVector();   T OUTPUT_SECONDPOINT17 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT18 = T::GetZeroVector();   T OUTPUT_SECONDPOINT18 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT19 = T::GetZeroVector();   T OUTPUT_SECONDPOINT19 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT20 = T::GetZeroVector();   T OUTPUT_SECONDPOINT20 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT21 = T::GetZeroVector();   T OUTPUT_SECONDPOINT21 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT22 = T::GetZeroVector();   T OUTPUT_SECONDPOINT22 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT23 = T::GetZeroVector();   T OUTPUT_SECONDPOINT23 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT24 = T::GetZeroVector();   T OUTPUT_SECONDPOINT24 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EQIntersections eResult2  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
    EQIntersections eResult3  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // II
    EQIntersections eResult4  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // II
    EQIntersections eResult5  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5); // III
    EQIntersections eResult6  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6); // III
    EQIntersections eResult7  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7); // IV
    EQIntersections eResult8  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8); // IV
    EQIntersections eResult9  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT5, OUTPUT_FIRSTPOINT9, OUTPUT_SECONDPOINT9); // V
    EQIntersections eResult10 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT10, OUTPUT_SECONDPOINT10); // V
    EQIntersections eResult11 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT6, OUTPUT_FIRSTPOINT11, OUTPUT_SECONDPOINT11); // VI
    EQIntersections eResult12 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT12, OUTPUT_SECONDPOINT12); // VI
    EQIntersections eResult13 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT5, OUTPUT_FIRSTPOINT13, OUTPUT_SECONDPOINT13); // VII
    EQIntersections eResult14 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT14, OUTPUT_SECONDPOINT14); // VII
    EQIntersections eResult15 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT6, OUTPUT_FIRSTPOINT15, OUTPUT_SECONDPOINT15); // VIII
    EQIntersections eResult16 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT16, OUTPUT_SECONDPOINT16); // VIII
    EQIntersections eResult17 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT7, OUTPUT_FIRSTPOINT17, OUTPUT_SECONDPOINT17); // IX
    EQIntersections eResult18 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT18, OUTPUT_SECONDPOINT18); // IX
    EQIntersections eResult19 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT7, OUTPUT_FIRSTPOINT19, OUTPUT_SECONDPOINT19); // X
    EQIntersections eResult20 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT20, OUTPUT_SECONDPOINT20); // X
    EQIntersections eResult21 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT8, OUTPUT_FIRSTPOINT21, OUTPUT_SECONDPOINT21); // XI
    EQIntersections eResult22 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT22, OUTPUT_SECONDPOINT22); // XI
    EQIntersections eResult23 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT8, OUTPUT_FIRSTPOINT23, OUTPUT_SECONDPOINT23); // XII
    EQIntersections eResult24 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT24, OUTPUT_SECONDPOINT24); // XII

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult9, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult10, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult11, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult12, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult13, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult14, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult15, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult16, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult17, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult18, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult19, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult20, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult21, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult22, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult23, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult24, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT9 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT10 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT11 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT12 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT13 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT14 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT15 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT16 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT17 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT18 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT19 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT20 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT21 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT22 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT23 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT24 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT9 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT10 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT11 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT12 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT13 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT14 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT15 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT16 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT17 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT18 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT19 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT20 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT21 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT22 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT23 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT24 == EXPECTED_SECONDPOINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // A2---(A1B1)---B2
    //
    //        I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT1 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT1 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT2 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT2 = T::GetZeroVector();

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsExpectedResultsWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // A2---(A1B1)---B2
    //
    //        I

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    const float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_q VECTOR_COMPONENTS_A3B3[] = { SQFloat::_6, SQFloat::_8, SQFloat::_9, SQFloat::_1 };
    const T VALUE_FOR_A3B3(VECTOR_COMPONENTS_A3B3);
    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_A3B3, VALUE_FOR_A3B3);

    const EQIntersections EXPECTED_RESULT_WHEN_INTERSECT = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_WHEN_DONT_INTERSECT = EQIntersections::E_None;

    const T EXPECTED_INTERSECTION_POINT = VALUE_FOR_A1B1;
    const T EXPECTED_NO_INTERSECTION_POINT = T::GetZeroVector();

	// Execution
    T vFirstIntersection1 = T::GetZeroVector();
    T vSecondIntersection1 = T::GetZeroVector();
    T vFirstIntersection2 = T::GetZeroVector();
    T vSecondIntersection2 = T::GetZeroVector();
    T vFirstNoIntersection1 = T::GetZeroVector();
    T vSecondNoIntersection1 = T::GetZeroVector();
    T vFirstNoIntersection2 = T::GetZeroVector();
    T vSecondNoIntersection2 = T::GetZeroVector();
    
    EQIntersections eResultIntersection1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, vFirstIntersection1, vSecondIntersection1);
    EQIntersections eResultIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, vFirstIntersection2, vSecondIntersection2);
    EQIntersections eResultNoIntersection1 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, vFirstNoIntersection1, vSecondNoIntersection1);
    EQIntersections eResultNoIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, vFirstNoIntersection2, vSecondNoIntersection2);

    // Verification
    BOOST_CHECK_EQUAL(eResultIntersection1, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(eResultIntersection2, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(eResultNoIntersection1, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK_EQUAL(eResultNoIntersection2, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vFirstNoIntersection1 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vFirstNoIntersection2 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vSecondNoIntersection1 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vSecondNoIntersection2 == EXPECTED_NO_INTERSECTION_POINT);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it doesn't return any intersection point when the segment doesn't intersect the other but would do it if it was lengthened to the infinite.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoPointWhenSegmentDoesNotIntersectButWouldDoIfTheyHadInfiniteLength_Test, TQTemplateTypes )
{
    // A1       A2
    //  \      /
    //   B1   /
    //    ·  /
    //     ·/
    //     /·
    //   B2  ·

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT1 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT1 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT2 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoPointsWhenLinesCoincidePartially_Test, TQTemplateTypes )
{
    // A2---A1---B1---B2  I
    //
    // A2---B1---A1---B2  II
    //
    // A2---A1---B2---B1  III
    //
    // A2---B1---B2---A1  IV
    //
    // B2---A1---A2---B1  V
    //
    // B2---B1---A2---A1  VI
    //
    // A1---A2---B2---B1  VII
    //
    // A1---B2---A2---B1  VIII

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q FIRST_POSITION_COMPONENTS[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q SECOND_POSITION_COMPONENTS[] = { SQFloat::_2, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q THIRD_POSITION_COMPONENTS[] = { SQFloat::_3, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q FOURTH_POSITION_COMPONENTS[] = { SQFloat::_4, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);
    const T FOURTH_POSITION = T(FOURTH_POSITION_COMPONENTS);

    const QLineSegment<T> LINE_SEGMENTA_1 = QLineSegment<T>(SECOND_POSITION, THIRD_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_1 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_2 = QLineSegment<T>(THIRD_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_2 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_3 = QLineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_3 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_4 = QLineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_4 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_5 = QLineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_5 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_6 = QLineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_6 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_7 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_7 = QLineSegment<T>(SECOND_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_8 = QLineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_8 = QLineSegment<T>(THIRD_POSITION, SECOND_POSITION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT1 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT2 = THIRD_POSITION;
    const T EXPECTED_FIRSTPOINT3 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT4 = THIRD_POSITION;
    const T EXPECTED_FIRSTPOINT5 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT6 = THIRD_POSITION;
    const T EXPECTED_FIRSTPOINT7 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT8 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT1 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT2 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT3 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT4 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT5 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT6 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT7 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT8 = THIRD_POSITION;
    T OUTPUT_FIRSTPOINT1 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT2 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT3 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT4 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT5 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT6 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT7 = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT8 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT1 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT2 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT3 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT4 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT5 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT6 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT7 = T::GetZeroVector();
    T OUTPUT_SECONDPOINT8 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EQIntersections eResult2 = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // II
    EQIntersections eResult3 = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // III
    EQIntersections eResult4 = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // IV
    EQIntersections eResult5 = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5); // V
    EQIntersections eResult6 = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6); // VI
    EQIntersections eResult7 = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7); // VII
    EQIntersections eResult8 = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8); // VIII

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_FIRSTPOINT4);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_FIRSTPOINT5);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_FIRSTPOINT6);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_FIRSTPOINT7);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_FIRSTPOINT8);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT3);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT4);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT5);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT6);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT7);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT8);
}

/// <summary>
/// Checks that it returns two intersection points when one line is totally contained in the other.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoPointsWhenOneSegmentIsContainedInTheOther_Test, TQTemplateTypes )
{
    // A1A2---B1---B2  I
    //
    // A1A2---B2---B1  II
    //
    // B1B2---A1---A2  III
    //
    // B1B2---A2---A1  IV
    //
    // A1B2---B1---A2  V
    //
    // A1B2---A2---B1  VI
    //
    // A2B1---A1---B2  VII
    //
    // A2B1---B2---A1  VIII
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q FIRST_POSITION_COMPONENTS[] = { SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q SECOND_POSITION_COMPONENTS[] = { SQFloat::_2, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const float_q THIRD_POSITION_COMPONENTS[] = { SQFloat::_3, SQFloat::_0, SQFloat::_0, SQFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);

    const QLineSegment<T> LINE_SEGMENTA_1 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_1 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_2 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_2 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_3 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_3 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_4 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_4 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_5 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_5 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_6 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_6 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_7 = QLineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_7 = QLineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const QLineSegment<T> LINE_SEGMENTA_8 = QLineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const QLineSegment<T> LINE_SEGMENTB_8 = QLineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT1 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT2 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT3 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT4 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT5 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT6 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT7 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT8 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT1 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT2 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT3 = FIRST_POSITION;
    const T EXPECTED_SECONDPOINT4 = FIRST_POSITION;
    const T EXPECTED_SECONDPOINT5 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT6 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT7 = FIRST_POSITION;
    const T EXPECTED_SECONDPOINT8 = FIRST_POSITION;
    T OUTPUT_FIRSTPOINT1  = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT2  = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT3  = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT4  = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT5  = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT6  = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT7  = T::GetZeroVector();
    T OUTPUT_FIRSTPOINT8  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT1  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT2  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT3  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT4  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT5  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT6  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT7  = T::GetZeroVector();
    T OUTPUT_SECONDPOINT8  = T::GetZeroVector();

	// Execution
    EQIntersections eResult1  = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1);// I
    EQIntersections eResult2  = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2);// II
    EQIntersections eResult3  = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3);// III
    EQIntersections eResult4  = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4);// IV
    EQIntersections eResult5  = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5);// V
    EQIntersections eResult6  = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6);// VI
    EQIntersections eResult7  = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7);// VII
    EQIntersections eResult8  = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8);// VIII

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult8, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_FIRSTPOINT4);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_FIRSTPOINT5);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_FIRSTPOINT6);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_FIRSTPOINT7);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_FIRSTPOINT8);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT3);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT4);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT5);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT6);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT7);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT8);
}

/// <summary>
/// Checks that it returns no intersection points when the line doesn't intersect the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_NoIntersectionPointsAreReturnedWhenLineDoesNotIntersectTheOrb_Test, TQTemplateTypes )
{
    // A1           ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       B1

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_10, SQFloat::_10, SQFloat::_10, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1F = EXPECTED_POINT;
    T OUTPUT_POINT1S = EXPECTED_POINT;

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT);
}


/// <summary>
/// Checks that it returns True when only one end point is inside the orb and the other is outside it.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionPointWhenOnlyOneEndPointIsInsideTheOrb_Test, TQTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------|-B1  |    B1---------|-A1  |
    //             \___/                 \___/
    //
    //        I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetZeroVector();
    T OUTPUT_POINT1F = T::GetZeroVector();
    T OUTPUT_POINT1S = T::GetZeroVector();
    T OUTPUT_POINT2F = T::GetZeroVector();
    T OUTPUT_POINT2S = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINTS);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb by only one end point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrbByAnEndPoint_Test, TQTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------B1 x  |    B1---------A1 x  |
    //             \___/                 \___/
    //
    //        I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetZeroVector();
    T OUTPUT_POINT1F = T::GetZeroVector();
    T OUTPUT_POINT1S = T::GetZeroVector();
    T OUTPUT_POINT2F = T::GetZeroVector();
    T OUTPUT_POINT2S = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINTS);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the orb. Output points should not change.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsInfiniteIntersectionsWhenTheLineIsContainedInTheOrb_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //        |  A1---B1  |
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_3 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINTF = EXPECTED_POINT;
    T OUTPUT_POINTS = EXPECTED_POINT;

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns oen intersection point when the line is contained in the orb and only one end point coincides with the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenTheLineIsContainedInTheOrbAndOneEndPointCoincidesWithTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ______                ______
    //          ´        `            ´        `
    //        /           \         /           \
    //        |      A1---B1        |      B1---A1
    //        \           /         \           /
    //          ` _____ ´             ` _____ ´
    //
    //              I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetZeroVector();
    T OUTPUT_POINT1F = T::GetZeroVector();
    T OUTPUT_POINT1S = T::GetZeroVector();
    T OUTPUT_POINT2F = T::GetZeroVector();
    T OUTPUT_POINT2S = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINTS);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns two intersection points when the line is contained in the orb and the 2 end points coincide with the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenTheLineIsContainedInTheOrbAndTheTwoEndPointsCoincideWithTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //       A1-----------B1
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    float_q VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTS = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    T OUTPUT_POINTF = T::GetZeroVector();
    T OUTPUT_POINTS = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects the orb in two points (and the line is not contained in the orb).
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenTheLineIntersectsTheOrbInTwoPoints_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //   A1------------------B1
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    float_q VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTS = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    T OUTPUT_POINTF = T::GetZeroVector();
    T OUTPUT_POINTS = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb (the tangent point is not A or B).
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrb_Test, TQTemplateTypes )
{
    //        A1   _____
    //        |  ´       `
    //        |/           \
    //        |      x     |
    //        |\           /
    //        B1 ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetZeroVector();
    T OUTPUT_POINTF = T::GetZeroVector();
    T OUTPUT_POINTS = EXPECTED_POINTS;

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns no intersection points when the segment does not intersect the orb but would do it if the segment had an infinite length.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_NoIntersectionIsReturnedWhenTheSegmentDoesNotIntersectTheOrbButWouldDoIfItWasInifinite_Test, TQTemplateTypes )
{
    //                ___
    //              /     \
    // A1----B1····|···x···|····
    //              \ ___ /
    //
    //         I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = {-SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1F = EXPECTED_POINT;
    T OUTPUT_POINT1S = EXPECTED_POINT;
    T OUTPUT_POINT2F = EXPECTED_POINT;
    T OUTPUT_POINT2S = EXPECTED_POINT;

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TQTemplateTypes )
{
    //
    // A1----------x-------B1
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_0 );

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1F = EXPECTED_POINT;
    T OUTPUT_POINT1S = EXPECTED_POINT;
    T OUTPUT_POINT2F = EXPECTED_POINT;
    T OUTPUT_POINT2S = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection point when the length of the line equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheLengthOfSegmentEqualsZero_Test, TQTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_7 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINTF = EXPECTED_POINT;
    T OUTPUT_POINTS = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINT);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsExpectedResultsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //
    // A1----------x-------B1
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB_CONTAINED = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_CONTAINED), SQFloat::_0 );

    float_q VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SQFloat::_9, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB_NOT_CONTAINED = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED), SQFloat::_0 );

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_One;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = false;
    const T EXPECTED_POINT_CONTAINED = T(VECTOR_COMPONENTS_CENTER_CONTAINED);
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetZeroVector();

	// Execution
    T vPointContained = T::GetZeroVector();
    T vPointNotContained = T::GetZeroVector();
    EQIntersections eResultContained = LINE_SEGMENT.IntersectionPoint(ORB_CONTAINED, vPointContained);
    EQIntersections eResultNotContained = LINE_SEGMENT.IntersectionPoint(ORB_NOT_CONTAINED, vPointNotContained);

    // Verification
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsExpectedResultsWhenTheLengthOfSegmentEqualsZero_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q VECTOR_COMPONENTS_CONTAINED[] = { (float_q)2.5, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T POINT_CONTAINED(VECTOR_COMPONENTS_CONTAINED);
    const QLineSegment<T> LINE_SEGMENT_CONTAINED = QLineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q VECTOR_COMPONENTS_IN_SURFACE[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T POINT_IN_SURFACE(VECTOR_COMPONENTS_IN_SURFACE);
    const QLineSegment<T> LINE_SEGMENT_IN_SURFACE = QLineSegment<T>(POINT_IN_SURFACE, POINT_IN_SURFACE);

    const float_q VECTOR_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_4, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(VECTOR_COMPONENTS_NOT_CONTAINED);
    const QLineSegment<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_Infinite;
    const EQIntersections EXPECTED_RESULT_IN_SURFACE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = EQIntersections::E_None;
    const T EXPECTED_POINT_CONTAINED = T::GetZeroVector();
    const T EXPECTED_POINT_IN_SURFACE = POINT_IN_SURFACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetZeroVector();

	// Execution
    T vPointContained = T::GetZeroVector();
    T vPointInSurface = T::GetZeroVector();
    T vPointNotContained = T::GetZeroVector();

    EQIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(ORB, vPointContained);
    EQIntersections eResultInSurface = LINE_SEGMENT_IN_SURFACE.IntersectionPoint(ORB, vPointInSurface);
    EQIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(ORB, vPointNotContained);
    
    // Verification
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultInSurface, EXPECTED_RESULT_IN_SURFACE);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vPointInSurface == EXPECTED_POINT_IN_SURFACE);
    BOOST_CHECK(vPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the first point returned is which is nearer to A end point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint3_FirstPointIsNearerToAThanSecondPoint_Test, TQTemplateTypes )
{
    //               ______                       ______
    //             ´        `                   ´        `
    //           /           \                /           \
    //   A1--------------------B1    B1---------------------A1
    //           \           /                \           /
    //             ` _____ ´                    ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT1F = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    float_q VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT1S = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    const T EXPECTED_POINT2F = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    const T EXPECTED_POINT2S = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    T OUTPUT_POINT1F = T::GetZeroVector();
    T OUTPUT_POINT1S = T::GetZeroVector();
    T OUTPUT_POINT2F = T::GetZeroVector();
    T OUTPUT_POINT2S = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S);

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT1F);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT1S);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINT2F);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINT2S);
}

/// <summary>
/// Checks that it returns no intersection points when the line doesn't intersect the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_NoIntersectionPointsAreReturnedWhenLineDoesNotIntersectTheOrb_Test, TQTemplateTypes )
{
    // A1           ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       B1

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_10, SQFloat::_10, SQFloat::_10, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}


/// <summary>
/// Checks that it returns True when only one end point is inside the orb and the other is outside it.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionPointWhenOnlyOneEndPointIsInsideTheOrb_Test, TQTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------|-B1  |    B1---------|-A1  |
    //             \___/                 \___/
    //
    //        I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb by only one end point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrbByAnEndPoint_Test, TQTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------B1 x  |    B1---------A1 x  |
    //             \___/                 \___/
    //
    //        I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the orb. Output points should not change.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsInfiniteIntersectionsWhenTheLineIsContainedInTheOrb_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //        |  A1---B1  |
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_3 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns oen intersection point when the line is contained in the orb and only one end point coincides with the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenTheLineIsContainedInTheOrbAndOneEndPointCoincidesWithTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ______                ______
    //          ´        `            ´        `
    //        /           \         /           \
    //        |      A1---B1        |      B1---A1
    //        \           /         \           /
    //          ` _____ ´             ` _____ ´
    //
    //              I                    II

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line is contained in the orb and the 2 end points coincide with the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenTheLineIsContainedInTheOrbAndTheTwoEndPointsCoincideWithTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //       A1-----------B1
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects the orb in two points (and the line is not contained in the orb).
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenTheLineIntersectsTheOrbInTwoPoints_Test, TQTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //   A1------------------B1
    //        \           /
    //          ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb (the tangent point is not A or B).
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrb_Test, TQTemplateTypes )
{
    //        A1   _____
    //        |  ´       `
    //        |/           \
    //        |      x     |
    //        |\           /
    //        B1 ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetZeroVector();

	// Execution
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the segment does not intersect the orb but would do it if the segment had an infinite length.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_NoIntersectionIsReturnedWhenTheSegmentDoesNotIntersectTheOrbButWouldDoIfItWasInifinite_Test, TQTemplateTypes )
{
    //                ___
    //              /     \
    // A1----B1····|···x···|····
    //              \ ___ /
    //
    //         I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = {-SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1 = EXPECTED_POINT;
    T OUTPUT_POINT2 = EXPECTED_POINT;

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TQTemplateTypes )
{
    //
    // A1----------x-------B1
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_0 );

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT1 = EXPECTED_POINT;
    T OUTPUT_POINT2 = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenTheLengthOfSegmentEqualsZero_Test, TQTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_7 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const T EXPECTED_POINT = T::GetZeroVector();
    T OUTPUT_POINT = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsExpectedResultsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //
    // A1----------x-------B1
    //

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_q VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB_CONTAINED = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_CONTAINED), SQFloat::_0 );

    float_q VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SQFloat::_9, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB_NOT_CONTAINED = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED), SQFloat::_0 );

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_One;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = false;
    const T EXPECTED_FIRSTPOINT_CONTAINED = T(VECTOR_COMPONENTS_CENTER_CONTAINED);
    const T EXPECTED_SECONDPOINT_CONTAINED = T::GetZeroVector();
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetZeroVector();

	// Execution
    T vFirstPointContained = T::GetZeroVector();
    T vFirstPointNotContained = T::GetZeroVector();
    T vSecondPointContained = T::GetZeroVector();
    T vSecondPointNotContained = T::GetZeroVector();
    EQIntersections eResultContained = LINE_SEGMENT.IntersectionPoint(ORB_CONTAINED, vFirstPointContained, vSecondPointContained);
    EQIntersections eResultNotContained = LINE_SEGMENT.IntersectionPoint(ORB_NOT_CONTAINED, vFirstPointNotContained, vSecondPointNotContained);

    // Verification
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstPointContained == EXPECTED_FIRSTPOINT_CONTAINED);
    BOOST_CHECK(vFirstPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondPointContained == EXPECTED_SECONDPOINT_CONTAINED);
    BOOST_CHECK(vSecondPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsExpectedResultsWhenTheLengthOfSegmentEqualsZero_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const float_q VECTOR_COMPONENTS_CONTAINED[] = { (float_q)2.5, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T POINT_CONTAINED(VECTOR_COMPONENTS_CONTAINED);
    const QLineSegment<T> LINE_SEGMENT_CONTAINED = QLineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_q VECTOR_COMPONENTS_IN_SURFACE[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T POINT_IN_SURFACE(VECTOR_COMPONENTS_IN_SURFACE);
    const QLineSegment<T> LINE_SEGMENT_IN_SURFACE = QLineSegment<T>(POINT_IN_SURFACE, POINT_IN_SURFACE);

    const float_q VECTOR_COMPONENTS_NOT_CONTAINED[] = { SQFloat::_4, SQFloat::_6, SQFloat::_7, SQFloat::_1 };
    const T POINT_NOT_CONTAINED(VECTOR_COMPONENTS_NOT_CONTAINED);
    const QLineSegment<T> LINE_SEGMENT_NOT_CONTAINED = QLineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT_CONTAINED = EQIntersections::E_Infinite;
    const EQIntersections EXPECTED_RESULT_IN_SURFACE = EQIntersections::E_Two;
    const EQIntersections EXPECTED_RESULT_NOT_CONTAINED = EQIntersections::E_None;
    const T EXPECTED_POINT_CONTAINED = T::GetZeroVector();
    const T EXPECTED_POINT_IN_SURFACE = POINT_IN_SURFACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetZeroVector();

	// Execution
    T vFirstPointContained = T::GetZeroVector();
    T vSecondPointContained = T::GetZeroVector();
    T vFirstPointInSurface = T::GetZeroVector();
    T vSecondPointInSurface = T::GetZeroVector();
    T vFirstPointNotContained = T::GetZeroVector();
    T vSecondPointNotContained = T::GetZeroVector();

    EQIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(ORB, vFirstPointContained, vSecondPointContained);
    EQIntersections eResultInSurface = LINE_SEGMENT_IN_SURFACE.IntersectionPoint(ORB, vFirstPointInSurface, vSecondPointInSurface);
    EQIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(ORB, vFirstPointNotContained, vSecondPointNotContained);
    
    // Verification
    BOOST_CHECK_EQUAL(eResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(eResultInSurface, EXPECTED_RESULT_IN_SURFACE);
    BOOST_CHECK_EQUAL(eResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstPointInSurface == EXPECTED_POINT_IN_SURFACE);
    BOOST_CHECK(vFirstPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondPointInSurface == EXPECTED_POINT_IN_SURFACE);
    BOOST_CHECK(vSecondPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the point returned is which is nearer to A end point.
/// </summary>
QTEST_CASE_TEMPLATE ( IntersectionPoint4_FirstPointIsNearerToA_Test, TQTemplateTypes )
{
    //               ______                       ______
    //             ´        `                   ´        `
    //           /           \                /           \
    //   A1--------------------B1    B1---------------------A1
    //           \           /                \           /
    //             ` _____ ´                    ` _____ ´

    using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    QBaseOrb<T> ORB = QBaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    float_q VECTOR_COMPONENTS_OUTPUT_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    float_q VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SQFloat::_3, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    T OUTPUT_POINT1 = T::GetZeroVector();
    T OUTPUT_POINT2 = T::GetZeroVector();

	// Execution
    EQIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1);
    EQIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2);

    // Verification
    BOOST_CHECK_EQUAL(eResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResult2, EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns the expected distance when lines don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsExpectedDistanceWhenLinesDoNotIntersect_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_6, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_2, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_q EXPECTED_RESULT = sqrt_q(SQFloat::_0_5);

	// Execution
    float_q fResult = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when lines intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TQTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when lines coincide totally.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesCoincideTotally_Test, TQTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_q fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_q fResult3 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT3); // II
    float_q fResult4 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT1); // II

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult4, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenAnEndPointIsContainedInTheOtherLine_Test, TQTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_q fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_q fResult3 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4); // II
    float_q fResult4 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1); // II
    float_q fResult5 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT2); // III
    float_q fResult6 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT3); // III
    float_q fResult7 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4); // IV
    float_q fResult8 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3); // IV

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult4, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult5, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult6, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult7, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult8, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the 2 lines share only one of their end points.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesShareOneEndPointOnly_Test, TQTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegment<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegment<T> LINE_SEGMENT6 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_q VECTOR_COMPONENTS_A4[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B4[] = { SQFloat::_6, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const QLineSegment<T> LINE_SEGMENT7 = QLineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const QLineSegment<T> LINE_SEGMENT8 = QLineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult1  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_q fResult2  = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_q fResult3  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4); // II
    float_q fResult4  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1); // II
    float_q fResult5  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT2); // III
    float_q fResult6  = LINE_SEGMENT2.MinDistance(LINE_SEGMENT3); // III
    float_q fResult7  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4); // IV
    float_q fResult8  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3); // IV
    float_q fResult9  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT5); // V
    float_q fResult10 = LINE_SEGMENT5.MinDistance(LINE_SEGMENT1); // V
    float_q fResult11 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT6); // VI
    float_q fResult12 = LINE_SEGMENT6.MinDistance(LINE_SEGMENT1); // VI
    float_q fResult13 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT5); // VII
    float_q fResult14 = LINE_SEGMENT5.MinDistance(LINE_SEGMENT3); // VII
    float_q fResult15 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT6); // VIII
    float_q fResult16 = LINE_SEGMENT6.MinDistance(LINE_SEGMENT3); // VIII
    float_q fResult17 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT7); // IX
    float_q fResult18 = LINE_SEGMENT7.MinDistance(LINE_SEGMENT1); // IX
    float_q fResult19 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT7); // X
    float_q fResult20 = LINE_SEGMENT7.MinDistance(LINE_SEGMENT3); // X
    float_q fResult21 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT8); // XI
    float_q fResult22 = LINE_SEGMENT8.MinDistance(LINE_SEGMENT1); // XI
    float_q fResult23 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT8); // XII
    float_q fResult24 = LINE_SEGMENT8.MinDistance(LINE_SEGMENT3); // XII

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult1,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult2,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult3,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult4,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult5,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult6,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult7,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult8,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult9,  EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult10, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult11, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult12, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult13, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult14, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult15, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult16, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult17, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult18, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult19, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult20, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult21, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult22, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult23, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult24, EXPECTED_RESULT) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // A1------B1  (A2B2)
    //
    //        I

    // Preparation
    float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_7, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the length of one of the segments equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsExpectedResultWhenTheLengthOfOneSegmentEqualsZero_Test, TQTemplateTypes )
{
    // A1------B1  (A2B2)
    //
    //        I

    // Preparation
    float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_7, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_q EXPECTED_RESULT = SQFloat::_3;

	// Execution
    float_q fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_q fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I

    // Verification
    BOOST_CHECK_EQUAL(fResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(fResult2, EXPECTED_RESULT);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns zero when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesCoincidePartially_Test, TQTemplateTypes )
{
    //
    // A1---A2---B1---B2    A1---B2---B1---A2    B1---A2---A1---B2    B1---B2---A1---A2
    //
    //         I                   II                   III                  IV

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_q fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_q fResult3 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4); // II
    float_q fResult4 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1); // II
    float_q fResult5 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT2); // III
    float_q fResult6 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT3); // III
    float_q fResult7 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4); // IV
    float_q fResult8 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3); // IV

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult4, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult5, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult6, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult7, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult8, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when one line is totally contained in the other.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenOneSegmentIsContainedInTheOther_Test, TQTemplateTypes )
{
    //
    // A1---A2---B2---B1    A1---A3----B1B3    A1---B3---B1A3    B1---A3---A1B3    B1---B3---A1A3
    //
    //         I                  II                 III               IV                V

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegment<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegment<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegment<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_q fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_q fResult3  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4);// II
    float_q fResult4  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1);// II
    float_q fResult5  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT5);// III
    float_q fResult6  = LINE_SEGMENT5.MinDistance(LINE_SEGMENT1);// III
    float_q fResult7  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4);// IV
    float_q fResult8  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3);// IV
    float_q fResult9  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT5);// V
    float_q fResult10 = LINE_SEGMENT5.MinDistance(LINE_SEGMENT3);// V

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult4, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult5, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult6, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult7, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult8, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult9, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult10, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the expected distance when lines don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance2_ReturnsExpectedDistanceWhenLineAndPointDoNotIntersect_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_6, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_P[] = { SQFloat::_2, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const float_q EXPECTED_RESULT = sqrt_q(SQFloat::_0_5);

	// Execution
    float_q fResult = LINE_SEGMENT1.MinDistance(POINT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the point is contained in the line (not including A, and B points in this case).
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance2_ReturnsZeroWhenThePointIsContainedInTheLine_Test, TQTemplateTypes )
{
    //
    // A1---P---B1    B1---P---A1
    //
    //      I             II

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    float_q VECTOR_COMPONENTS_P[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult1 = LINE_SEGMENT1.MinDistance(POINT); // I
    float_q fResult2 = LINE_SEGMENT2.MinDistance(POINT); // II

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult2, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the point concides with one of the the segment's end points.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance2_ReturnsZeroWhenSegmentEndPointCoincidesWithPoint_Test, TQTemplateTypes )
{
    //
    // A1P---B1    B1P---A1
    //
    //     I          II

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    float_q VECTOR_COMPONENTS_P[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fResult1 = LINE_SEGMENT1.MinDistance(POINT); // I
    float_q fResult2 = LINE_SEGMENT2.MinDistance(POINT); // II

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SQFloat::AreEqual(fResult2, EXPECTED_RESULT) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of the segment equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance2_AssertionFailsWhenTheLengthOfTheSegmentEqualsZero_Test, TQTemplateTypes )
{
    // P  (A1B1)
    //
    //     I

    // Preparation
    float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_7, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_q VECTOR_COMPONENTS_P[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT1.MinDistance(POINT); // I
    }
    catch(...) // [TODO] Thund: A concrete exception type has to be defined for this
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the length of the segment equals zero, even if they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( MinDistance2_ReturnsExpectedResultWhenTheLengthOfTheSegmentEqualsZero_Test, TQTemplateTypes )
{
    // P  (A1B1)
    //
    //      I

    // Preparation
    const float_q VECTOR_COMPONENTS_A1B1[] = { SQFloat::_7, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const QLineSegment<T> LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    const float_q POINT_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T POINT = T(POINT_COMPONENTS);

    const float_q EXPECTED_RESULT = SQFloat::_3;

	// Execution
    float_q fResult = LINE_SEGMENT.MinDistance(POINT); // I

    // Verification
    BOOST_CHECK_EQUAL(fResult, EXPECTED_RESULT);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value.
/// </summary>
QTEST_CASE_TEMPLATE ( Lengthen_ItIsLengthenedTheCorrectAmountWhenUsingCommonValue_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_2;
    const float_q EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is not lengthened when the input factor equals one.
/// </summary>
QTEST_CASE_TEMPLATE ( Lengthen_LengthDoesNotChangeWhenValueEqualsOne_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_1;
    const float_q ORIGINAL_LENGTH = lineSegmentUT.GetLength();
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, ORIGINAL_LENGTH) );
}

/// <summary>
/// Checks that the length of the segment equals zero when the input value equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Lengthen_LengthEqualsZeroWhenInputValueEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);

    const float_q FACTOR = SQFloat::_0;
    const float_q EXPECTED_LENGTH = SQFloat::_0;
    float_q fSegmentLength = SQFloat::_0;
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

	// Execution
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is lengthened from its center.
/// </summary>
QTEST_CASE_TEMPLATE ( Lengthen_SegmentIsLengthenedFromCenter_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const T SEGMENT_CENTER = lineSegmentUT.GetCenter();
    const float_q FACTOR = SQFloat::_0;

	// Execution
    lineSegmentUT.Lengthen(FACTOR);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == SEGMENT_CENTER);
    BOOST_CHECK(lineSegmentUT.B == SEGMENT_CENTER);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value when it's positive and lower than one.
/// </summary>
QTEST_CASE_TEMPLATE ( Lengthen_ItIsLengthenedTheCorrectAmountWhenValueIsPositiveAndLowerThanOne_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_0_5;
    const float_q EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is flipped when the input value is negative.
/// </summary>
QTEST_CASE_TEMPLATE ( Lengthen_ItIsFlippedWhenInputValueIsNegative_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> FLIPPED_LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = -SQFloat::_1;

	// Execution
    lineSegmentUT.Lengthen(FACTOR);

    // Verification
    BOOST_CHECK(lineSegmentUT.A ==  FLIPPED_LINE_SEGMENT.A);
    BOOST_CHECK(lineSegmentUT.B ==  FLIPPED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromA_ItIsLengthenedTheCorrectAmountWhenUsingCommonValue_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_2;
    const float_q EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is not lengthened when the input factor equals one.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromA_LengthDoesNotChangeWhenValueEqualsOne_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_1;
    const float_q ORIGINAL_LENGTH = lineSegmentUT.GetLength();
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, ORIGINAL_LENGTH) );
}

/// <summary>
/// Checks that the length of the segment equals zero when the input value equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromA_LengthEqualsZeroWhenInputValueEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);

    const float_q FACTOR = SQFloat::_0;
    const float_q EXPECTED_LENGTH = SQFloat::_0;
    float_q fSegmentLength = SQFloat::_0;
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

	// Execution
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is lengthened from its A end point.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromA_SegmentIsLengthenedFromA_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const T SEGMENT_A = lineSegmentUT.A;
    const float_q FACTOR = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromA(FACTOR);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == SEGMENT_A);
    BOOST_CHECK(lineSegmentUT.B == SEGMENT_A);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value when it's positive and lower than one.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromA_ItIsLengthenedTheCorrectAmountWhenValueIsPositiveAndLowerThanOne_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_0_5;
    const float_q EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is flipped when the input value is negative.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromA_ItIsFlippedWhenInputValueIsNegative_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> FLIPPED_LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_A1 + VALUE_FOR_A1 - VALUE_FOR_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = -SQFloat::_1;

	// Execution
    lineSegmentUT.LengthenFromA(FACTOR);

    // Verification
    BOOST_CHECK(lineSegmentUT.A ==  FLIPPED_LINE_SEGMENT.A);
    BOOST_CHECK(lineSegmentUT.B ==  FLIPPED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromB_ItIsLengthenedTheCorrectAmountWhenUsingCommonValue_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_2;
    const float_q EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is not lengthened when the input factor equals one.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromB_LengthDoesNotChangeWhenValueEqualsOne_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_1;
    const float_q ORIGINAL_LENGTH = lineSegmentUT.GetLength();
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, ORIGINAL_LENGTH) );
}

/// <summary>
/// Checks that the length of the segment equals zero when the input value equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromB_LengthEqualsZeroWhenInputValueEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);

    const float_q FACTOR = SQFloat::_0;
    const float_q EXPECTED_LENGTH = SQFloat::_0;
    float_q fSegmentLength = SQFloat::_0;
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

	// Execution
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is lengthened from its B end point.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromB_SegmentIsLengthenedFromB_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const T SEGMENT_A = lineSegmentUT.B;
    const float_q FACTOR = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromB(FACTOR);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == SEGMENT_A);
    BOOST_CHECK(lineSegmentUT.B == SEGMENT_A);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value when it's positive and lower than one.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromB_ItIsLengthenedTheCorrectAmountWhenValueIsPositiveAndLowerThanOne_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = SQFloat::_0_5;
    const float_q EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_q fSegmentLength = SQFloat::_0;

	// Execution
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is flipped when the input value is negative.
/// </summary>
QTEST_CASE_TEMPLATE ( LengthenFromB_ItIsFlippedWhenInputValueIsNegative_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegment<T> FLIPPED_LINE_SEGMENT = QLineSegment<T>(VALUE_FOR_B1 + VALUE_FOR_B1 - VALUE_FOR_A1, VALUE_FOR_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_q FACTOR = -SQFloat::_1;

	// Execution
    lineSegmentUT.LengthenFromB(FACTOR);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == FLIPPED_LINE_SEGMENT.A);
    BOOST_CHECK(lineSegmentUT.B == FLIPPED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    QLineSegment<T> lineSegmentUT = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const string_q A_STRING = VALUE_FOR_A1.ToString();
    const string_q B_STRING = VALUE_FOR_B1.ToString();
    const string_q EXPECTED_STRING = string_q(QE_L("LS(a(")) + A_STRING + string_q(QE_L("),b(")) + B_STRING + string_q(QE_L("))"));

	// Execution
    string_q strReturnedString = lineSegmentUT.ToString();

    // Verification
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

/// <summary>
/// Checks that expected points are returned when line segments don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_ExpectedPointsAreReturnedWhenLinesDoNotIntersect_Test, TQTemplateTypes )
{
    // A1-------B1
    //
    // A2-------B2

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_q VECTOR_COMPONENTS_EXPECTED1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_EXPECTED2[] = { (float_q)0.2, (float_q)2.4, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT = T::GetZeroVector();
    T S2TOS1_POINT = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT, S2TOS1_POINT);

    // Verification
    BOOST_CHECK(S1TOS2_POINT == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the intersection point when lines intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_ObtainedPointsCoincideWithIntersectionPointWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TQTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_q VECTOR_COMPONENTS_EXPECTED1[] = { (float_q)1.5, (float_q)1.5, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_EXPECTED2[] = { (float_q)1.5, (float_q)1.5, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT = T::GetZeroVector();
    T S2TOS1_POINT = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT, S2TOS1_POINT);

    // Verification
    BOOST_CHECK(S1TOS2_POINT == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide when lines intersect somewhere between A and B, both not included.
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_ObtainedPointsCoincideWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TQTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_1, SQFloat::_1, SQFloat::_6, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegment<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    T S1TOS2_POINT = T::GetZeroVector();
    T S2TOS1_POINT = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT, S2TOS1_POINT);

    // Verification
    BOOST_CHECK(S1TOS2_POINT == S2TOS1_POINT);
}

/// <summary>
/// Checks that both returned points coincide with the end point A of the segment whose method is being called when lines coincide totally.
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsCoincideWithEndPointAWhenLinesCoincideTotally_Test, TQTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    float_q VECTOR_COMPONENTS_EXPECTED1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_EXPECTED2[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetZeroVector();
    T S2TOS1_POINT1 = T::GetZeroVector();
    T S1TOS2_POINT2 = T::GetZeroVector();
    T S2TOS1_POINT2 = T::GetZeroVector();
    T S1TOS2_POINT3 = T::GetZeroVector();
    T S2TOS1_POINT3 = T::GetZeroVector();
    T S1TOS2_POINT4 = T::GetZeroVector();
    T S2TOS1_POINT4 = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II

    // Verification
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the intersection point when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_ObtainedPointsCoincideWithIntersectionPointWhenAnEndPointIsContainedInTheOtherLine_Test, TQTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_q VECTOR_COMPONENTS_EXPECTED[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);
    T S1TOS2_POINT1 = T::GetZeroVector();
    T S2TOS1_POINT1 = T::GetZeroVector();
    T S1TOS2_POINT2 = T::GetZeroVector();
    T S2TOS1_POINT2 = T::GetZeroVector();
    T S1TOS2_POINT3 = T::GetZeroVector();
    T S2TOS1_POINT3 = T::GetZeroVector();
    T S1TOS2_POINT4 = T::GetZeroVector();
    T S2TOS1_POINT4 = T::GetZeroVector();
    T S1TOS2_POINT5 = T::GetZeroVector();
    T S2TOS1_POINT5 = T::GetZeroVector();
    T S1TOS2_POINT6 = T::GetZeroVector();
    T S2TOS1_POINT6 = T::GetZeroVector();
    T S1TOS2_POINT7 = T::GetZeroVector();
    T S2TOS1_POINT7 = T::GetZeroVector();
    T S1TOS2_POINT8 = T::GetZeroVector();
    T S2TOS1_POINT8 = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT5, S2TOS1_POINT5); // III
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT6, S2TOS1_POINT6); // III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7); // IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8); // IV

    // Verification
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT);
}

/// <summary>
/// Checks that obtained points coincide with the shared end point when the 2 lines share only one of their end points.
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsCoincideWithSharedEndPointWhenLinesShareOneEndPointOnly_Test, TQTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT6 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_q VECTOR_COMPONENTS_A4[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B4[] = { SQFloat::_6, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT7 = QLineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT8 = QLineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    float_q VECTOR_COMPONENTS_EXPECTED1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_EXPECTED2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetZeroVector();    T S2TOS1_POINT1 = T::GetZeroVector();
    T S1TOS2_POINT2 = T::GetZeroVector();    T S2TOS1_POINT2 = T::GetZeroVector();
    T S1TOS2_POINT3 = T::GetZeroVector();    T S2TOS1_POINT3 = T::GetZeroVector();
    T S1TOS2_POINT4 = T::GetZeroVector();    T S2TOS1_POINT4 = T::GetZeroVector();
    T S1TOS2_POINT5 = T::GetZeroVector();    T S2TOS1_POINT5 = T::GetZeroVector();
    T S1TOS2_POINT6 = T::GetZeroVector();    T S2TOS1_POINT6 = T::GetZeroVector();
    T S1TOS2_POINT7 = T::GetZeroVector();    T S2TOS1_POINT7 = T::GetZeroVector();
    T S1TOS2_POINT8 = T::GetZeroVector();    T S2TOS1_POINT8 = T::GetZeroVector();
    T S1TOS2_POINT9 = T::GetZeroVector();    T S2TOS1_POINT9 = T::GetZeroVector();
    T S1TOS2_POINT10 = T::GetZeroVector();    T S2TOS1_POINT10 = T::GetZeroVector();
    T S1TOS2_POINT11 = T::GetZeroVector();    T S2TOS1_POINT11 = T::GetZeroVector();
    T S1TOS2_POINT12 = T::GetZeroVector();    T S2TOS1_POINT12 = T::GetZeroVector();
    T S1TOS2_POINT13 = T::GetZeroVector();    T S2TOS1_POINT13 = T::GetZeroVector();
    T S1TOS2_POINT14 = T::GetZeroVector();    T S2TOS1_POINT14 = T::GetZeroVector();
    T S1TOS2_POINT15 = T::GetZeroVector();    T S2TOS1_POINT15 = T::GetZeroVector();
    T S1TOS2_POINT16 = T::GetZeroVector();    T S2TOS1_POINT16 = T::GetZeroVector();
    T S1TOS2_POINT17 = T::GetZeroVector();    T S2TOS1_POINT17 = T::GetZeroVector();
    T S1TOS2_POINT18 = T::GetZeroVector();    T S2TOS1_POINT18 = T::GetZeroVector();
    T S1TOS2_POINT19 = T::GetZeroVector();    T S2TOS1_POINT19 = T::GetZeroVector();
    T S1TOS2_POINT20 = T::GetZeroVector();    T S2TOS1_POINT20 = T::GetZeroVector();
    T S1TOS2_POINT21 = T::GetZeroVector();    T S2TOS1_POINT21 = T::GetZeroVector();
    T S1TOS2_POINT22 = T::GetZeroVector();    T S2TOS1_POINT22 = T::GetZeroVector();
    T S1TOS2_POINT23 = T::GetZeroVector();    T S2TOS1_POINT23 = T::GetZeroVector();
    T S1TOS2_POINT24 = T::GetZeroVector();    T S2TOS1_POINT24 = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT5, S2TOS1_POINT5); // III
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT6, S2TOS1_POINT6); // III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7); // IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8); // IV
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT9, S2TOS1_POINT9); // V
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT10, S2TOS1_POINT10); // V
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT6, S1TOS2_POINT11, S2TOS1_POINT11); // VI
    LINE_SEGMENT6.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT12, S2TOS1_POINT12); // VI
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT13, S2TOS1_POINT13); // VII
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT14, S2TOS1_POINT14); // VII
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT6, S1TOS2_POINT15, S2TOS1_POINT15); // VIII
    LINE_SEGMENT6.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT16, S2TOS1_POINT16); // VIII
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT7, S1TOS2_POINT17, S2TOS1_POINT17); // IX
    LINE_SEGMENT7.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT18, S2TOS1_POINT18); // IX
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT7, S1TOS2_POINT19, S2TOS1_POINT19); // X
    LINE_SEGMENT7.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT20, S2TOS1_POINT20); // X
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT8, S1TOS2_POINT21, S2TOS1_POINT21); // XI
    LINE_SEGMENT8.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT22, S2TOS1_POINT22); // XI
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT8, S1TOS2_POINT23, S2TOS1_POINT23); // XII
    LINE_SEGMENT8.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT24, S2TOS1_POINT24); // XII

    // Verification
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT11 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT11 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT12 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT12 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT13 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT13 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT14 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT14 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT15 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT15 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT16 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT16 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT17 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT17 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT18 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT18 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT19 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT19 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT20 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT20 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT21 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT21 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT22 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT22 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT23 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT23 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT24 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT24 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the closest ones to A (in the instance which method is being executed) that is contained in the
/// other line when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsAreTheClosestToAInsideTheOtherLineWhenLinesCoincidePartially_Test, TQTemplateTypes )
{
    //
    // A1---A2---B1---B2    A1---B2---B1---A2    B1---A2---A1---B2    B1---B2---A1---A2
    //
    //         I                   II                   III                  IV

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_q VECTOR_COMPONENTS_EXPECTED1[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_EXPECTED2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetZeroVector();    T S2TOS1_POINT1 = T::GetZeroVector();
    T S1TOS2_POINT2 = T::GetZeroVector();    T S2TOS1_POINT2 = T::GetZeroVector();
    T S1TOS2_POINT3 = T::GetZeroVector();    T S2TOS1_POINT3 = T::GetZeroVector();
    T S1TOS2_POINT4 = T::GetZeroVector();    T S2TOS1_POINT4 = T::GetZeroVector();
    T S1TOS2_POINT5 = T::GetZeroVector();    T S2TOS1_POINT5 = T::GetZeroVector();
    T S1TOS2_POINT6 = T::GetZeroVector();    T S2TOS1_POINT6 = T::GetZeroVector();
    T S1TOS2_POINT7 = T::GetZeroVector();    T S2TOS1_POINT7 = T::GetZeroVector();
    T S1TOS2_POINT8 = T::GetZeroVector();    T S2TOS1_POINT8 = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT5, S2TOS1_POINT5); // III
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT6, S2TOS1_POINT6); // III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7); // IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8); // IV

    // Verification
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the closest ones to A (in the instance which method is being executed) that is contained in the
/// other line when one line is totally contained in the other.
/// </summary>
QTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsAreTheClosestToAInsideTheOtherLineWhenOneSegmentIsContainedInTheOther_Test, TQTemplateTypes )
{
    //
    // A1---A2---B2---B1    A1---A3----B1B3    A1---B3---B1A3    B1---A3---A1B3    B1---B3---A1A3
    //
    //         I                  II                 III               IV                V

    // Preparation
    float_q VECTOR_COMPONENTS_A1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B1[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT1 = QLineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_q VECTOR_COMPONENTS_A2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT2 = QLineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_q VECTOR_COMPONENTS_A3[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B3[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const QLineSegmentWhiteBox<T> LINE_SEGMENT3 = QLineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT4 = QLineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const QLineSegmentWhiteBox<T> LINE_SEGMENT5 = QLineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_q VECTOR_COMPONENTS_EXPECTED1[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_EXPECTED2[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetZeroVector();    T S2TOS1_POINT1 = T::GetZeroVector();
    T S1TOS2_POINT2 = T::GetZeroVector();    T S2TOS1_POINT2 = T::GetZeroVector();
    T S1TOS2_POINT3 = T::GetZeroVector();    T S2TOS1_POINT3 = T::GetZeroVector();
    T S1TOS2_POINT4 = T::GetZeroVector();    T S2TOS1_POINT4 = T::GetZeroVector();
    T S1TOS2_POINT5 = T::GetZeroVector();    T S2TOS1_POINT5 = T::GetZeroVector();
    T S1TOS2_POINT6 = T::GetZeroVector();    T S2TOS1_POINT6 = T::GetZeroVector();
    T S1TOS2_POINT7 = T::GetZeroVector();    T S2TOS1_POINT7 = T::GetZeroVector();
    T S1TOS2_POINT8 = T::GetZeroVector();    T S2TOS1_POINT8 = T::GetZeroVector();
    T S1TOS2_POINT9 = T::GetZeroVector();    T S2TOS1_POINT9 = T::GetZeroVector();
    T S1TOS2_POINT10 = T::GetZeroVector();   T S2TOS1_POINT10 = T::GetZeroVector();

	// Execution
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1);// I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2);// I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3);// II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4);// II
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT5, S2TOS1_POINT5);// III
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT6, S2TOS1_POINT6);// III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7);// IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8);// IV
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT9, S2TOS1_POINT9);// V
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT10, S2TOS1_POINT10);// V

    // Verification
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT10 == EXPECTED_POINT2);
}

// End - Test Suite: QLineSegment
QTEST_SUITE_END()
