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

#include "ToolsExports.h"

#include "QLineSegment2D.h"
#include "QTransformationMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QLineSegment2D;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;

QTEST_SUITE_BEGIN( QLineSegment2D_TestSuite )


/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2::GetZeroVector();
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2::GetZeroVector();

	// Execution
    QLineSegment2D lineSegmentUT;

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if copy constructor sets segment's points properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B(SQFloat::_4, SQFloat::_5);

    const QLineSegment2D EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D lineSegmentUT(EXPECTED_LINESEGMENT);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if points are copied cortectly.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B(SQFloat::_4, SQFloat::_5);

    const QBaseLineSegment<QVector2> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D lineSegmentUT(EXPECTED_LINESEGMENT);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B(SQFloat::_4, SQFloat::_5);

	// Execution
    QLineSegment2D lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a unit-length line which point A is placed at origin and point B is contained in the positive X axis.
/// </summary>
QTEST_CASE ( GetUnitLine_AUnitLengthSegmentPlacedAtOriginAndContainedInPositiveXAxisIsReturned_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2::GetZeroVector();
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2::GetUnitVectorX();

	// Execution
    QLineSegment2D lineSegmentUT = QLineSegment2D::GetUnitLine();

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a zero-length line which points A and B are placed at origin.
/// </summary>
QTEST_CASE ( GetLineZero_AZeroLengthSegmentPlacedAtOriginIsReturned_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2::GetZeroVector();
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2::GetZeroVector();

	// Execution
    QLineSegment2D lineSegmentUT = QLineSegment2D::GetLineZero();

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line is correctly assigned to another line.
/// </summary>
QTEST_CASE ( OperatorAssignation_LineIsAssignedProperlyToAnother_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A(SQFloat::_1, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B(SQFloat::_4, SQFloat::_5);

    const QBaseLineSegment<QVector2> OTHER_LINE = QBaseLineSegment<QVector2>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D lineSegmentUT;
    lineSegmentUT = OTHER_LINE;

    // Verification
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns True when the line intersects with a vertex of the triangle.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenLineIntersectsWithVertex_Test )
{
    //
    //       LA----A-----LB          A                   A
    //            / \               / \     LA    LA    / \
    //           /   \             /   \   /       \   /   \
    //          /     \           /     \ /         \ /     \
    //         C-------B         C-------B           C-------B
    //                                  /             \
    //                                LB               LB
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A - QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B - QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultA = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultB = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultC = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // Verification
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with the triangle at two points.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenLineIntersectsWithTriangleTwice_Test )
{
    //
    //             A                 A                A
    //            / \               / \  LA       LA / \
    //       LA--x---x--LB         /   \/          \/   \
    //          /     \           /    /\          /\    \
    //         C-------B         C----x--B        C--x----B
    //                               /                \
    //                             LB                  LB
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.C) + QVector2(-SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B) + QVector2(SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B) + QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C) + QVector2(SQFloat::_0, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C) + QVector2(SQFloat::_0, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A) + QVector2(-SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAC_AB = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultBA_BC = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultCB_CA = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // Verification
    BOOST_CHECK_EQUAL(bResultAC_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCB_CA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the triangle.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenLineIsContainedInTriangle_Test )
{
    //            A
    //           / \
    //          /   \
    //         /     \
    //        /       \
    //       / LA--LB  \
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the segmetn is inside of the triangle.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenOnlyOneEndpointIsInsideTheTriangle_Test )
{
    //
    //             A                 A  LA            A
    //            / \               / \/             / \
    //       LA--x-LB\             /  /\            /LB \
    //          /     \           /  LB \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LA
    //
    //             I                III               V
    //
    //             A                 A  LB            A
    //            / \               / \/             / \
    //       LB--x-LA\             /  /\            /LA \
    //          /     \           /  LA \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LB
    //
    //            II                 IV                VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B1 = QVector2(-SQFloat::_2, SQFloat::_3);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B2 = QVector2(SQFloat::_3, SQFloat::_3);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B3 = QVector2(SQFloat::_2, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAC1 = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultAC2 = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultAB1 = LINE_SEGMENT3.Intersection(TRIANGLE); // III
    bool bResultAB2 = LINE_SEGMENT4.Intersection(TRIANGLE); // IV
    bool bResultBC1 = LINE_SEGMENT5.Intersection(TRIANGLE); // V
    bool bResultBC2 = LINE_SEGMENT6.Intersection(TRIANGLE); // VI

    // Verification
    BOOST_CHECK_EQUAL(bResultAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the triangle don't intersect.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsFalseWhenLineAndTriangleDoNotIntersect_Test )
{
    //            A
    //           / \
    //          /   \    LA
    //         /     \    \
    //        /       \    \
    //       /         \    LB
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_3, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_5, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the triangle don't intersect but would do if the line was infinite.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsFalseWhenLineAndTriangleDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    //            A         LA
    //           / \       /
    //          /   \    LB
    //         /     \  .
    //        /       \.
    //       /        .\
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE); // I

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two vertices of the triangle.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenLineIntersectsTwoVertices_Test )
{
    //           LA                                        LA
    //            \                                       /
    //             A                 A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B     LB--C-------B--LA       C-------B
    //                  \                           /
    //                   LB                       LB
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.A);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.B);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.C);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAB = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultBC = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultCA = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // Verification
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenLineBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /   \             /   \               /   \
    //          /     LB          /     \            LB     \
    //         C-------B         C-LA-LB-B           C-------B
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.B).Normalize();
    const QVector2 ENDPOINT_B1 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.A).Normalize();
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.C).Normalize();
    const QVector2 ENDPOINT_B2 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.B).Normalize();
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.A).Normalize();
    const QVector2 ENDPOINT_B3 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.C).Normalize();
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAB = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultBC = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultCA = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // Verification
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the an end point of the line coincides with a vertex of the triangle.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenAnEndpointCoincidesWithVertex_Test )
{
    //           LA
    //            \
    //             ALB               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLB--LA      CLB-----B
    //                                              /
    //                                            LA
    //
    //             I                III                  V
    //
    //           LB
    //            \
    //             ALA               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLA--LB      CLA-----B
    //                                              /
    //                                            LB
    //
    //             II               IV                   VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultA1 = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultA2 = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultB1 = LINE_SEGMENT3.Intersection(TRIANGLE); // III
    bool bResultB2 = LINE_SEGMENT4.Intersection(TRIANGLE); // IV
    bool bResultC1 = LINE_SEGMENT5.Intersection(TRIANGLE); // V
    bool bResultC2 = LINE_SEGMENT6.Intersection(TRIANGLE); // VI

    // Verification
    BOOST_CHECK_EQUAL(bResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC2, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( Intersection1_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(TRIANGLE);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the triangle coincide.
/// </summary>
QTEST_CASE ( Intersection1_AssertionFailsWhenAllVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX = QVector2(SQFloat::_1, SQFloat::_2);
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX, VERTEX, VERTEX);

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(TRIANGLE);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when only one point of the line segment belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( Intersection1_ReturnsTrueWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA--LB          / \           LB---LA \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LA----B           C-------B
    //                               \
    //                                LB
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB--LA          / \           LA---LB \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LB----B           C-------B
    //                               \
    //                                LA
    //             II                IV                  VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B) + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C) + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A) + QVector2(-SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAB1 = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultAB2 = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultBC1 = LINE_SEGMENT3.Intersection(TRIANGLE); // III
    bool bResultBC2 = LINE_SEGMENT4.Intersection(TRIANGLE); // IV
    bool bResultCA1 = LINE_SEGMENT5.Intersection(TRIANGLE); // V
    bool bResultCA2 = LINE_SEGMENT6.Intersection(TRIANGLE); // VI

    // Verification
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsWithVertex_Test )
{
    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A - QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 ENDPOINT_B1 = QUAD.A + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B2 = QUAD.B + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C - QVector2(-SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = QUAD.C + QVector2(-SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B4 = QUAD.D + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultA = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultB = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultC = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultD = LINE_SEGMENT4.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two contiguous edges of the qudrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsWithTwoContiguousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A.Lerp(SQFloat::_0_5, QUAD.D) + QVector2(-SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B1 = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B) + QVector2(SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B.Lerp(SQFloat::_0_5, QUAD.A) + QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B2 = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C) + QVector2(SQFloat::_0, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C.Lerp(SQFloat::_0_5, QUAD.B) + QVector2(SQFloat::_0, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D) + QVector2(-SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D.Lerp(SQFloat::_0_5, QUAD.C) + QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B4 = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A) + QVector2(-SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAD_AB = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultBA_BC = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultCB_CD = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultDA_AB = LINE_SEGMENT4.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultAD_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA_AB, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenLineIsContainedInQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the segment is inside of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenOnlyOneEndpointIsInsideTheQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B1 = QVector2(-SQFloat::_2, SQFloat::_3);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B2 = QVector2(SQFloat::_3, SQFloat::_3);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B3 = QVector2(SQFloat::_4, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B4 = QVector2(SQFloat::_2, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAD1 = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultAD2 = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultAB1 = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultAB2 = LINE_SEGMENT4.Intersection(QUAD);
    bool bResultBC1 = LINE_SEGMENT5.Intersection(QUAD);
    bool bResultBC2 = LINE_SEGMENT6.Intersection(QUAD);
    bool bResultCD1 = LINE_SEGMENT7.Intersection(QUAD);
    bool bResultCD2 = LINE_SEGMENT8.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultAD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the quadrilateral don't intersect.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsFalseWhenLineAndQuadrilateralDoNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_4, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_5, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the quadrilateral don't intersect but would do if the line was infinite.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsFalseWhenLineAndQuadrilateralDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_3, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = LINE_SEGMENT.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two contiguous vertices of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsTwoContiguousVertices_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const QVector2 ENDPOINT_B1 = QUAD.B + (QUAD.B - QUAD.A);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const QVector2 ENDPOINT_B2 = QUAD.C + (QUAD.C - QUAD.B);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const QVector2 ENDPOINT_B3 = QUAD.D + (QUAD.D - QUAD.C);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const QVector2 ENDPOINT_B4 = QUAD.A + (QUAD.A - QUAD.D);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAB = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultBC = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultCD = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultDA = LINE_SEGMENT4.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenLineBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_4, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A - (QUAD.A - QUAD.B).Normalize();
    const QVector2 ENDPOINT_B1 = QUAD.B - (QUAD.B - QUAD.A).Normalize();
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B - (QUAD.B - QUAD.C).Normalize();
    const QVector2 ENDPOINT_B2 = QUAD.C - (QUAD.C - QUAD.B).Normalize();
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C - (QUAD.C - QUAD.D).Normalize();
    const QVector2 ENDPOINT_B3 = QUAD.D - (QUAD.D - QUAD.C).Normalize();
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D - (QUAD.D - QUAD.A).Normalize();
    const QVector2 ENDPOINT_B4 = QUAD.A - (QUAD.A - QUAD.D).Normalize();
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAB = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultBC = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultCD = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultDA = LINE_SEGMENT4.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the an end point of the line coincides with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenAnEndpointCoincidesWithVertex_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const QVector2 ENDPOINT_B1 = QUAD.A;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const QVector2 ENDPOINT_B2 = QUAD.B;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const QVector2 ENDPOINT_B3 = QUAD.C;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const QVector2 ENDPOINT_B4 = QUAD.D;
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultA1 = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultA2 = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultB1 = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultB2 = LINE_SEGMENT4.Intersection(QUAD);
    bool bResultC1 = LINE_SEGMENT5.Intersection(QUAD);
    bool bResultC2 = LINE_SEGMENT6.Intersection(QUAD);
    bool bResultD1 = LINE_SEGMENT7.Intersection(QUAD);
    bool bResultD2 = LINE_SEGMENT8.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two non-contiguous edges of the qudrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsWithTwoNonContiguousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A.Lerp(SQFloat::_0_5, QUAD.D) + QVector2(-SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B1 = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C) + QVector2(SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B) + QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B2 = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D) + QVector2(SQFloat::_0, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAD_BC = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultAB_CD = LINE_SEGMENT2.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultAD_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB_CD, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( Intersection2_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_3),
                                                       QVector2(SQFloat::_1, SQFloat::_1),
                                                       QVector2(SQFloat::_3, SQFloat::_1));

    const QVector2 ENDPOINT = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(QUAD);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( Intersection2_AssertionFailsWhenAllVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX = QVector2(SQFloat::_1, SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX, VERTEX, VERTEX, VERTEX);

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(QUAD);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when only one point of the line segment belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( Intersection2_ReturnsTrueWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 ENDPOINT_B1 = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B) + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 ENDPOINT_B2 = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C) + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 ENDPOINT_B3 = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D) + QVector2(-SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);
    const QVector2 ENDPOINT_B4 = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A) + QVector2(-SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAB1 = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultAB2 = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultBC1 = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultBC2 = LINE_SEGMENT4.Intersection(QUAD);
    bool bResultCD1 = LINE_SEGMENT5.Intersection(QUAD);
    bool bResultCD2 = LINE_SEGMENT6.Intersection(QUAD);
    bool bResultDA1 = LINE_SEGMENT7.Intersection(QUAD);
    bool bResultDA2 = LINE_SEGMENT8.Intersection(QUAD);

    // Verification
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a line segment is correctly rotated.
/// </summary>
QTEST_CASE ( Rotate_IsCorrectlyRotatedWhenUsingCommonAngle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_5, SQFloat::_0);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Rotate(ANGLE);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when angle is zero.
/// </summary>
QTEST_CASE ( Rotate_IsNotRotatedWhenAngleIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const float_q ANGLE = SQFloat::_0;

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Rotate(ANGLE);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly translated.
/// </summary>
QTEST_CASE ( Translate1_IsCorrectlyTranslatedWhenUsingCommonTranslationVector_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);

    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_4);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
QTEST_CASE ( Translate1_IsNotTranslatedWhenTranslationIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);

    const QVector2 TRANSLATION_VECTOR = QVector2::GetZeroVector();

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    const QLineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly translated.
/// </summary>
QTEST_CASE ( Translate2_IsCorrectlyTranslatedWhenUsingCommonTranslationValues_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);

    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_4);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    const QLineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
QTEST_CASE ( Translate2_IsNotTranslatedWhenTranslationIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);

    const QVector2 TRANSLATION_VECTOR = QVector2::GetZeroVector();

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    const QLineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly scaled.
/// </summary>
QTEST_CASE ( Scale1_TriangleIsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_10 + SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_4, SQFloat::_10 + SQFloat::_6);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled if scalation is one.
/// </summary>
QTEST_CASE ( Scale1_IsNotScaledIfScalationIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly scaled.
/// </summary>
QTEST_CASE ( Scale2_IsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_10 + SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_4, SQFloat::_10 + SQFloat::_6);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled if scale equals one.
/// </summary>
QTEST_CASE ( Scale2_IsNotScaledIfScalationIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly transformed.
/// </summary>
QTEST_CASE ( Transform_IsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 INIT_POS_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 INIT_POS_B = QVector2(SQFloat::_3, SQFloat::_4);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 Scale = QVector2(SQFloat::_2, SQFloat::_0_5);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, Scale);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);

    const QLineSegment2D LINE = QLineSegment2D(INIT_POS_A, INIT_POS_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Transform(TRANSFORMATION_MATRIX);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform_DoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that all the endpoints of the line segment are moved to the coordinate origin.
/// </summary>
QTEST_CASE ( Transform_EndpointsAreMovedToCoordinateOriginWhenTransfomedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2::GetZeroVector();
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2::GetZeroVector();

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly rotated with pivot point.
/// </summary>
QTEST_CASE ( RotateWithPivot_IsCorrectlyRotated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_1, SQFloat::_2);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, -SQFloat::_1);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    QLineSegment2D returnedLine = LINE.RotateWithPivot(ANGLE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated with a pivot when angle is zero.
/// </summary>
QTEST_CASE ( RotateWithPivot_IsNotRotatedWithPivotWhenAngleIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q ANGLE = SQFloat::_0;

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.RotateWithPivot(ANGLE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly scaled with a pivot.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_IsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    QLineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled with a pivot if Scale is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_IsNotScaledWithPivotIfScaleIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled with a pivot if Scale is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_IsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const QLineSegment2D LINE = QLineSegment2D(POINT_A, POINT_B);

	// Execution
    QLineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled with a pivot if Scale is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_IsNotScaledWithPivotIfScaleIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly transformed with a pivot.
/// </summary>
QTEST_CASE ( TransformWithPivot_IsCorrectlyTransformedWithPivot_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // Preparation
    const QVector2 INIT_POS_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 INIT_POS_B = QVector2(SQFloat::_3, SQFloat::_4);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 Scale = QVector2(SQFloat::_2, SQFloat::_0_5);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, Scale);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_3, SQFloat::_5);

    const QLineSegment2D LINE = QLineSegment2D(INIT_POS_A, INIT_POS_B);

	// Execution
    QLineSegment2D returnedLine = LINE.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix with a pivot point.
/// </summary>
QTEST_CASE ( TransformWithPivot_DoesntChangeWhenTransformedWithPivotByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_6);

    const QLineSegment2D LINE = QLineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the pivot point when transforming by a zero matrix.
/// </summary>
QTEST_CASE ( TransformWithPivot_EndpointsAreMovedToPivotPointWhenTransformedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_6);

    const QLineSegment2D LINE = QLineSegment2D(VALUE_FOR_A, VALUE_FOR_B);

	// Execution
    QLineSegment2D returnedLine = LINE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedLine.A == PIVOT_POINT);
    BOOST_CHECK(returnedLine.B == PIVOT_POINT);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //
    //       LA----A-----LB          A                   A
    //            / \               / \     LA    LA    / \
    //           /   \             /   \   /       \   /   \
    //          /     \           /     \ /         \ /     \
    //         C-------B         C-------B           C-------B
    //                                  /             \
    //                                LB               LB
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A - QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B - QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINTA = TRIANGLE.A;
    const QVector2 EXPECTED_POINTB = TRIANGLE.B;
    const QVector2 EXPECTED_POINTC = TRIANGLE.C;

	// Execution
    QVector2 vPointA;
    QVector2 vPointB;
    QVector2 vPointC;
    EQIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointA); // I
    EQIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointB); // II
    EQIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointC); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC, EXPECTED_RESULT);
    BOOST_CHECK(vPointA == EXPECTED_POINTA);
    BOOST_CHECK(vPointB == EXPECTED_POINTB);
    BOOST_CHECK(vPointC == EXPECTED_POINTC);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with the triangle at two points.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenLineIntersectsWithTriangleTwice_Test )
{
    //
    //             A                 A                A
    //            / \               / \  LA       LA / \
    //       LA--x---x--LB         /   \/          \/   \
    //          /     \           /    /\          /\    \
    //         C-------B         C----x--B        C--x----B
    //                               /                \
    //                             LB                  LB
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 MIDPOINT_CA = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CA;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CA;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_BC;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AC = MIDPOINT_CA;
    const QVector2 EXPECTED_POINT_BA = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_CB = MIDPOINT_BC;

	// Execution
    QVector2 vPointAC;
    QVector2 vPointBA;
    QVector2 vPointCB;
    EQIntersections eResultAC_AB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAC); // I
    EQIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointBA); // II
    EQIntersections eResultCB_CA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointCB); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultAC_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCB_CA, EXPECTED_RESULT);
    BOOST_CHECK(vPointAC == EXPECTED_POINT_AC);
    BOOST_CHECK(vPointBA == EXPECTED_POINT_BA);
    BOOST_CHECK(vPointCB == EXPECTED_POINT_CB);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsInfiniteIntersectionsWhenLineIsContainedInTriangle_Test )
{
    //            A
    //           / \
    //          /   \
    //         /     \
    //        /       \
    //       / LA--LB  \
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segmetn is inside of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheTriangle_Test )
{
    //
    //             A                 A  LA            A
    //            / \               / \/             / \
    //       LA--x-LB\             /  /\            /LB \
    //          /     \           /  LB \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LA
    //
    //             I                III               V
    //
    //             A                 A  LB            A
    //            / \               / \/             / \
    //       LB--x-LA\             /  /\            /LA \
    //          /     \           /  LA \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LB
    //
    //            II                 IV                VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 POINT_INSIDE_TRIANGLE = QVector2(SQFloat::_1, SQFloat::_2);

    const QVector2 ENDPOINT_A1 = POINT_INSIDE_TRIANGLE;
    const QVector2 ENDPOINT_B1 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SQFloat::_2;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = POINT_INSIDE_TRIANGLE;
    const QVector2 ENDPOINT_B2 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B) - POINT_INSIDE_TRIANGLE) * SQFloat::_2;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = POINT_INSIDE_TRIANGLE;
    const QVector2 ENDPOINT_B3 = POINT_INSIDE_TRIANGLE + (TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SQFloat::_2;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINT_AC1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_POINT_AC2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_POINT_AB1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_POINT_AB2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_POINT_BC1 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_POINT_BC2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);

	// Execution
    QVector2 vPointAC1;
    QVector2 vPointAC2;
    QVector2 vPointAB1;
    QVector2 vPointAB2;
    QVector2 vPointBC1;
    QVector2 vPointBC2;
    EQIntersections eResultAC1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAC1); // I
    EQIntersections eResultAC2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAC2); // II
    EQIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointAB1); // III
    EQIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointAB2); // IV
    EQIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointBC1); // V
    EQIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointBC2); // VI

    // Verification
    BOOST_CHECK_EQUAL(eResultAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK(vPointAC1 == EXPECTED_POINT_AC1);
    BOOST_CHECK(vPointAC2 == EXPECTED_POINT_AC2);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersect_Test )
{
    //            A
    //           / \
    //          /   \    LA
    //         /     \    \
    //        /       \    \
    //       /         \    LB
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_3, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_5, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect but would do if the line was infinite.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    //            A         LA
    //           / \       /
    //          /   \    LB
    //         /     \  .
    //        /       \.
    //       /        .\
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersctions when the line intersects with two vertices of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenLineIntersectsTwoVertices_Test )
{
    //           LA                                        LB
    //            \                                       /
    //             A                 A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B     LB--C-------B--LA       C-------B
    //                  \                           /
    //                   LB                       LA
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.A);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.B);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.C);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AB = TRIANGLE.A;
    const QVector2 EXPECTED_POINT_BC = TRIANGLE.B;
    const QVector2 EXPECTED_POINT_CA = TRIANGLE.C;

	// Execution
    QVector2 vPointAB;
    QVector2 vPointBC;
    QVector2 vPointCA;
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB); // I
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointBC); // II
    EQIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointCA); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCA, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCA == EXPECTED_POINT_CA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /   \             /   \               /   \
    //          /     LB          /     \            LB     \
    //         C-------B         C-LA-LB-B           C-------B
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.B).Normalize();
    const QVector2 ENDPOINT_B1 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.A).Normalize();
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.C).Normalize();
    const QVector2 ENDPOINT_B2 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.B).Normalize();
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.A).Normalize();
    const QVector2 ENDPOINT_B3 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.C).Normalize();
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_POINT_AB = LINE_SEGMENT1.A;
    const QVector2 EXPECTED_POINT_BC = LINE_SEGMENT2.A;
    const QVector2 EXPECTED_POINT_CA = LINE_SEGMENT3.A;

	// Execution
    QVector2 vPointAB = QVector2::GetZeroVector();
    QVector2 vPointBC = QVector2::GetZeroVector();
    QVector2 vPointCA = QVector2::GetZeroVector();
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB); // I
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointBC); // II
    EQIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointCA); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCA, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCA == EXPECTED_POINT_CA);
}

/// <summary>
/// Checks that it returns one intersection point when the an end point of the line coincides with a vertex of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    //           LA
    //            \
    //             ALB               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLB--LA      CLB-----B
    //                                              /
    //                                            LA
    //
    //             I                III                  V
    //
    //           LB
    //            \
    //             ALA               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLA--LB      CLA-----B
    //                                              /
    //                                            LB
    //
    //             II               IV                   VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINT_A1 = TRIANGLE.A;
    const QVector2 EXPECTED_POINT_A2 = TRIANGLE.A;
    const QVector2 EXPECTED_POINT_B1 = TRIANGLE.B;
    const QVector2 EXPECTED_POINT_B2 = TRIANGLE.B;
    const QVector2 EXPECTED_POINT_C1 = TRIANGLE.C;
    const QVector2 EXPECTED_POINT_C2 = TRIANGLE.C;

	// Execution
    QVector2 vPointA1;
    QVector2 vPointA2;
    QVector2 vPointB1;
    QVector2 vPointB2;
    QVector2 vPointC1;
    QVector2 vPointC2;
    EQIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointA1); // I
    EQIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointA2); // II
    EQIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointB1); // III
    EQIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointB2); // IV
    EQIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointC1); // V
    EQIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointC2); // VI

    // Verification
    BOOST_CHECK_EQUAL(eResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC2, EXPECTED_RESULT);
    BOOST_CHECK(vPointA1 == EXPECTED_POINT_A1);
    BOOST_CHECK(vPointA2 == EXPECTED_POINT_A2);
    BOOST_CHECK(vPointB1 == EXPECTED_POINT_B1);
    BOOST_CHECK(vPointB2 == EXPECTED_POINT_B2);
    BOOST_CHECK(vPointC1 == EXPECTED_POINT_C1);
    BOOST_CHECK(vPointC2 == EXPECTED_POINT_C2);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint1_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the triangle coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint1_AssertionFailsWhenAllVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX = QVector2(SQFloat::_1, SQFloat::_2);
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX, VERTEX, VERTEX);

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA--LB          / \           LB---LA \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LA----B           C-------B
    //                               \
    //                                LB
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB--LA          / \           LA---LB \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LB----B           C-------B
    //                               \
    //                                LA
    //             II                IV                  VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B) + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C) + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A) + QVector2(-SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINT_AB1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_POINT_AB2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_POINT_BC1 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_POINT_BC2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_POINT_CA1 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 EXPECTED_POINT_CA2 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);

	// Execution
    QVector2 vPointAB1;
    QVector2 vPointAB2;
    QVector2 vPointBC1;
    QVector2 vPointBC2;
    QVector2 vPointCA1;
    QVector2 vPointCA2;
    EQIntersections bResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB1); // I
    EQIntersections bResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAB2); // II
    EQIntersections bResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointBC1); // III
    EQIntersections bResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointBC2); // IV
    EQIntersections bResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointCA1); // V
    EQIntersections bResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointCA2); // VI

    // Verification
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA2, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCA1 == EXPECTED_POINT_CA1);
    BOOST_CHECK(vPointCA2 == EXPECTED_POINT_CA2);
}

/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherIsInsideTheTriangle_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /  /\             / LB\               / \ \
    //          /  LB \           / /   \             /   LB\
    //         C-------B         C-LA----B           C-------B
    //
    //
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB              / \                LB \
    //           /  /\             / LA\               / \ \
    //          /  LA \           / /   \             /   LA\
    //         C-------B         C-LB----B           C-------B
    //
    //
    //             II                IV                  VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 TRIANGLE_CENTER = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B).Lerp(SQFloat::_0_5, TRIANGLE.C);

    const QVector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE_CENTER;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE_CENTER;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE_CENTER;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_POINT_AB1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_POINT_AB2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_POINT_BC1 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_POINT_BC2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_POINT_CA1 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 EXPECTED_POINT_CA2 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);

	// Execution
    QVector2 vPointAB1;
    QVector2 vPointAB2;
    QVector2 vPointBC1;
    QVector2 vPointBC2;
    QVector2 vPointCA1;
    QVector2 vPointCA2;
    EQIntersections bResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB1); // I
    EQIntersections bResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAB2); // II
    EQIntersections bResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointBC1); // III
    EQIntersections bResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointBC2); // IV
    EQIntersections bResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointCA1); // V
    EQIntersections bResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointCA2); // VI

    // Verification
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA2, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCA1 == EXPECTED_POINT_CA1);
    BOOST_CHECK(vPointCA2 == EXPECTED_POINT_CA2);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
QTEST_CASE ( IntersectionPoint1_ReturnedPointIsTheClosestOneToEndpointA_Test )
{
    //
    //             A
    //            / \  LA
    //           /   \/
    //          /    /\
    //         C----x--B
    //             /
    //            LB
    //
    //             I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const QVector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// Execution
    QVector2 vPointAB;
    LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAB); // I

    // Verification
    BOOST_CHECK(vPointAB == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vPointAB != FARTHEST_INTERSECTION_TO_A);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //
    //       LA----A-----LB          A                   A
    //            / \               / \     LA    LA    / \
    //           /   \             /   \   /       \   /   \
    //          /     \           /     \ /         \ /     \
    //         C-------B         C-------B           C-------B
    //                                  /             \
    //                                LB               LB
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A - QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B - QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINTA = TRIANGLE.A;
    const QVector2 EXPECTED_FIRSTPOINTB = TRIANGLE.B;
    const QVector2 EXPECTED_FIRSTPOINTC = TRIANGLE.C;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointA;
    QVector2 vFirstPointB;
    QVector2 vFirstPointC;
    QVector2 vSecondPointA;
    QVector2 vSecondPointB;
    QVector2 vSecondPointC;
    EQIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointA, vSecondPointA); // I
    EQIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointB, vSecondPointB); // II
    EQIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointC, vSecondPointC); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA == EXPECTED_FIRSTPOINTA);
    BOOST_CHECK(vFirstPointB == EXPECTED_FIRSTPOINTB);
    BOOST_CHECK(vFirstPointC == EXPECTED_FIRSTPOINTC);
    BOOST_CHECK(vSecondPointA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with the triangle at two points.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineIntersectsWithTriangleTwice_Test )
{
    //
    //             A                 A                A
    //            / \               / \  LA       LA / \
    //       LA--x---x--LB         /   \/          \/   \
    //          /     \           /    /\          /\    \
    //         C-------B         C----x--B        C--x----B
    //                               /                \
    //                             LB                  LB
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 MIDPOINT_CA = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CA;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CA;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_BC;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_FIRSTPOINT_AC_AB = MIDPOINT_CA;
    const QVector2 EXPECTED_FIRSTPOINT_BA_BC = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_CB_CA = MIDPOINT_BC;
    const QVector2 EXPECTED_SECONDPOINT_AC_AB = MIDPOINT_AB;
    const QVector2 EXPECTED_SECONDPOINT_BA_BC = MIDPOINT_BC;
    const QVector2 EXPECTED_SECONDPOINT_CB_CA = MIDPOINT_CA;

	// Execution
    QVector2 vFirstPointAC_AB;
    QVector2 vFirstPointBA_BC;
    QVector2 vFirstPointCB_CA;
    QVector2 vSecondPointAC_AB;
    QVector2 vSecondPointBA_BC;
    QVector2 vSecondPointCB_CA;
    EQIntersections eResultAC_AB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAC_AB, vSecondPointAC_AB); // I
    EQIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointBA_BC, vSecondPointBA_BC); // II
    EQIntersections eResultCB_CA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointCB_CA, vSecondPointCB_CA); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultAC_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCB_CA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAC_AB == EXPECTED_FIRSTPOINT_AC_AB);
    BOOST_CHECK(vFirstPointBA_BC == EXPECTED_FIRSTPOINT_BA_BC);
    BOOST_CHECK(vFirstPointCB_CA == EXPECTED_FIRSTPOINT_CB_CA);
    BOOST_CHECK(vSecondPointAC_AB == EXPECTED_SECONDPOINT_AC_AB);
    BOOST_CHECK(vSecondPointBA_BC == EXPECTED_SECONDPOINT_BA_BC);
    BOOST_CHECK(vSecondPointCB_CA == EXPECTED_SECONDPOINT_CB_CA);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsInfiniteIntersectionsWhenLineIsContainedInTriangle_Test )
{
    //            A
    //           / \
    //          /   \
    //         /     \
    //        /       \
    //       / LA--LB  \
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPoint = QVector2::GetZeroVector();
    QVector2 vSecondPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segmetn is inside of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheTriangle_Test )
{
    //
    //             A                 A  LA            A
    //            / \               / \/             / \
    //       LA--x-LB\             /  /\            /LB \
    //          /     \           /  LB \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LA
    //
    //             I                III               V
    //
    //             A                 A  LB            A
    //            / \               / \/             / \
    //       LB--x-LA\             /  /\            /LA \
    //          /     \           /  LA \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LB
    //
    //            II                 IV                VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 POINT_INSIDE_TRIANGLE = QVector2(SQFloat::_1, SQFloat::_2);

    const QVector2 ENDPOINT_A1 = POINT_INSIDE_TRIANGLE;
    const QVector2 ENDPOINT_B1 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SQFloat::_2;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = POINT_INSIDE_TRIANGLE;
    const QVector2 ENDPOINT_B2 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B) - POINT_INSIDE_TRIANGLE) * SQFloat::_2;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = POINT_INSIDE_TRIANGLE;
    const QVector2 ENDPOINT_B3 = POINT_INSIDE_TRIANGLE + (TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SQFloat::_2;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINT_AC1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_FIRSTPOINT_AC2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_FIRSTPOINT_AB1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_FIRSTPOINT_AB2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_FIRSTPOINT_BC1 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_FIRSTPOINT_BC2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointAC1;
    QVector2 vFirstPointAC2;
    QVector2 vFirstPointAB1;
    QVector2 vFirstPointAB2;
    QVector2 vFirstPointBC1;
    QVector2 vFirstPointBC2;
    QVector2 vSecondPointAC1;
    QVector2 vSecondPointAC2;
    QVector2 vSecondPointAB1;
    QVector2 vSecondPointAB2;
    QVector2 vSecondPointBC1;
    QVector2 vSecondPointBC2;
    EQIntersections eResultAC1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAC1, vSecondPointAC1); // I
    EQIntersections eResultAC2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointAC2, vSecondPointAC2); // II
    EQIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointAB1, vSecondPointAB1); // III
    EQIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointAB2, vSecondPointAB2); // IV
    EQIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointBC1, vSecondPointBC1); // V
    EQIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointBC2, vSecondPointBC2); // VI

    // Verification
    BOOST_CHECK_EQUAL(eResultAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAC1 == EXPECTED_FIRSTPOINT_AC1);
    BOOST_CHECK(vFirstPointAC2 == EXPECTED_FIRSTPOINT_AC2);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vSecondPointAC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersect_Test )
{
    //            A
    //           / \
    //          /   \    LA
    //         /     \    \
    //        /       \    \
    //       /         \    LB
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_3, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_5, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPoint = QVector2::GetZeroVector();
    QVector2 vSecondPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect but would do if the line was infinite.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    //            A         LA
    //           / \       /
    //          /   \    LB
    //         /     \  .
    //        /       \.
    //       /        .\
    //      C-----------B
    //
    //            I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPoint = QVector2::GetZeroVector();
    QVector2 vSecondPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersctions when the line intersects with two vertices of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineIntersectsTwoVertices_Test )
{
    //           LA                                        LB
    //            \                                       /
    //             A                 A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B     LB--C-------B--LA       C-------B
    //                  \                           /
    //                   LB                       LA
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.A);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.B);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.C);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_FIRSTPOINT_AB = TRIANGLE.A;
    const QVector2 EXPECTED_FIRSTPOINT_BC = TRIANGLE.B;
    const QVector2 EXPECTED_FIRSTPOINT_CA = TRIANGLE.C;
    const QVector2 EXPECTED_SECONDPOINT_AB = TRIANGLE.B;
    const QVector2 EXPECTED_SECONDPOINT_BC = TRIANGLE.C;
    const QVector2 EXPECTED_SECONDPOINT_CA = TRIANGLE.A;

	// Execution
    QVector2 vFirstPointAB;
    QVector2 vFirstPointBC;
    QVector2 vFirstPointCA;
    QVector2 vSecondPointAB;
    QVector2 vSecondPointBC;
    QVector2 vSecondPointCA;
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB, vSecondPointAB); // I
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointBC, vSecondPointBC); // II
    EQIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointCA, vSecondPointCA); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCA == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCA == EXPECTED_SECONDPOINT_CA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /   \             /   \               /   \
    //          /     LB          /     \            LB     \
    //         C-------B         C-LA-LB-B           C-------B
    //
    //             I                II                   III

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.B).Normalize();
    const QVector2 ENDPOINT_B1 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.A).Normalize();
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.C).Normalize();
    const QVector2 ENDPOINT_B2 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.B).Normalize();
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.A).Normalize();
    const QVector2 ENDPOINT_B3 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.C).Normalize();
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;

    const QVector2 EXPECTED_FIRSTPOINT_AB = ENDPOINT_A1;
    const QVector2 EXPECTED_SECONDPOINT_AB = ENDPOINT_B1;
    const QVector2 EXPECTED_FIRSTPOINT_BC = ENDPOINT_A2;
    const QVector2 EXPECTED_SECONDPOINT_BC = ENDPOINT_B2;
    const QVector2 EXPECTED_FIRSTPOINT_CA = ENDPOINT_A3;
    const QVector2 EXPECTED_SECONDPOINT_CA = ENDPOINT_B3;

	// Execution
    QVector2 vFirstPointAB = QVector2::GetZeroVector();
    QVector2 vFirstPointBC = QVector2::GetZeroVector();
    QVector2 vFirstPointCA = QVector2::GetZeroVector();
    QVector2 vSecondPointAB = QVector2::GetZeroVector();
    QVector2 vSecondPointBC = QVector2::GetZeroVector();
    QVector2 vSecondPointCA = QVector2::GetZeroVector();
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB, vSecondPointAB); // I
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointBC, vSecondPointBC); // II
    EQIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointCA, vSecondPointCA); // III

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCA == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCA == EXPECTED_SECONDPOINT_CA);
}

/// <summary>
/// Checks that it returns one intersection point when the an end point of the line coincides with a vertex of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    //           LA
    //            \
    //             ALB               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLB--LA      CLB-----B
    //                                              /
    //                                            LA
    //
    //             I                III                  V
    //
    //           LB
    //            \
    //             ALA               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLA--LB      CLA-----B
    //                                              /
    //                                            LB
    //
    //             II               IV                   VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINT_A1 = TRIANGLE.A;
    const QVector2 EXPECTED_FIRSTPOINT_A2 = TRIANGLE.A;
    const QVector2 EXPECTED_FIRSTPOINT_B1 = TRIANGLE.B;
    const QVector2 EXPECTED_FIRSTPOINT_B2 = TRIANGLE.B;
    const QVector2 EXPECTED_FIRSTPOINT_C1 = TRIANGLE.C;
    const QVector2 EXPECTED_FIRSTPOINT_C2 = TRIANGLE.C;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointA1  = QVector2::GetZeroVector();
    QVector2 vFirstPointA2  = QVector2::GetZeroVector();
    QVector2 vFirstPointB1  = QVector2::GetZeroVector();
    QVector2 vFirstPointB2  = QVector2::GetZeroVector();
    QVector2 vFirstPointC1  = QVector2::GetZeroVector();
    QVector2 vFirstPointC2  = QVector2::GetZeroVector();
    QVector2 vSecondPointA1 = QVector2::GetZeroVector();
    QVector2 vSecondPointA2 = QVector2::GetZeroVector();
    QVector2 vSecondPointB1 = QVector2::GetZeroVector();
    QVector2 vSecondPointB2 = QVector2::GetZeroVector();
    QVector2 vSecondPointC1 = QVector2::GetZeroVector();
    QVector2 vSecondPointC2 = QVector2::GetZeroVector();
    EQIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointA1, vSecondPointA1); // I
    EQIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointA2, vSecondPointA2); // II
    EQIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointB1, vSecondPointB1); // III
    EQIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointB2, vSecondPointB2); // IV
    EQIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointC1, vSecondPointC1); // V
    EQIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointC2, vSecondPointC2); // VI

    // Verification
    BOOST_CHECK_EQUAL(eResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA1 == EXPECTED_FIRSTPOINT_A1);
    BOOST_CHECK(vFirstPointA2 == EXPECTED_FIRSTPOINT_A2);
    BOOST_CHECK(vFirstPointB1 == EXPECTED_FIRSTPOINT_B1);
    BOOST_CHECK(vFirstPointB2 == EXPECTED_FIRSTPOINT_B2);
    BOOST_CHECK(vFirstPointC1 == EXPECTED_FIRSTPOINT_C1);
    BOOST_CHECK(vFirstPointC2 == EXPECTED_FIRSTPOINT_C2);
    BOOST_CHECK(vSecondPointA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC2 == EXPECTED_SECONDPOINT);
}


/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherIsInsideTheTriangle_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /  /\             / LB\               / \ \
    //          /  LB \           / /   \             /   LB\
    //         C-------B         C-LA----B           C-------B
    //
    //
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB              / \                LB \
    //           /  /\             / LA\               / \ \
    //          /  LA \           / /   \             /   LA\
    //         C-------B         C-LB----B           C-------B
    //
    //
    //             II                IV                  VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 TRIANGLE_CENTER = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B).Lerp(SQFloat::_0_5, TRIANGLE.C);

    const QVector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE_CENTER;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE_CENTER;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE_CENTER;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINT_AB1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_FIRSTPOINT_AB2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_FIRSTPOINT_BC1 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_FIRSTPOINT_BC2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_FIRSTPOINT_CA1 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 EXPECTED_FIRSTPOINT_CA2 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointAB1;
    QVector2 vFirstPointAB2;
    QVector2 vFirstPointBC1;
    QVector2 vFirstPointBC2;
    QVector2 vFirstPointCA1;
    QVector2 vFirstPointCA2;
    QVector2 vSecondPointAB1 = QVector2::GetZeroVector();
    QVector2 vSecondPointAB2 = QVector2::GetZeroVector();
    QVector2 vSecondPointBC1 = QVector2::GetZeroVector();
    QVector2 vSecondPointBC2 = QVector2::GetZeroVector();
    QVector2 vSecondPointCA1 = QVector2::GetZeroVector();
    QVector2 vSecondPointCA2 = QVector2::GetZeroVector();
    EQIntersections bResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB1, vSecondPointAB1); // I
    EQIntersections bResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointAB2, vSecondPointAB2); // II
    EQIntersections bResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointBC1, vSecondPointBC1); // III
    EQIntersections bResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointBC2, vSecondPointBC2); // IV
    EQIntersections bResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointCA1, vSecondPointCA1); // V
    EQIntersections bResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointCA2, vSecondPointCA2); // VI

    // Verification
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCA1 == EXPECTED_FIRSTPOINT_CA1);
    BOOST_CHECK(vFirstPointCA2 == EXPECTED_FIRSTPOINT_CA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA2 == EXPECTED_SECONDPOINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint2_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vFirstPoint, vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the triangle coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint2_AssertionFailsWhenAllVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    const QVector2 VERTEX = QVector2(SQFloat::_1, SQFloat::_2);
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(VERTEX, VERTEX, VERTEX);

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vFirstPoint, vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA--LB          / \           LB---LA \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LA----B           C-------B
    //                               \
    //                                LB
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB--LA          / \           LA---LB \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LB----B           C-------B
    //                               \
    //                                LA
    //             II                IV                  VI

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B) + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C) + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A) + QVector2(-SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;

    const QVector2 EXPECTED_FIRSTPOINT_AB1 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_FIRSTPOINT_AB2 = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 EXPECTED_FIRSTPOINT_BC1 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_FIRSTPOINT_BC2 = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);
    const QVector2 EXPECTED_FIRSTPOINT_CA1 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 EXPECTED_FIRSTPOINT_CA2 = TRIANGLE.C.Lerp(SQFloat::_0_5, TRIANGLE.A);
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointAB1;
    QVector2 vFirstPointAB2;
    QVector2 vFirstPointBC1;
    QVector2 vFirstPointBC2;
    QVector2 vFirstPointCA1;
    QVector2 vFirstPointCA2;
    QVector2 vSecondPointAB1;
    QVector2 vSecondPointAB2;
    QVector2 vSecondPointBC1;
    QVector2 vSecondPointBC2;
    QVector2 vSecondPointCA1;
    QVector2 vSecondPointCA2;
    EQIntersections bResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB1, vSecondPointAB1); // I
    EQIntersections bResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointAB2, vSecondPointAB2); // II
    EQIntersections bResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointBC1, vSecondPointBC1); // III
    EQIntersections bResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointBC2, vSecondPointBC2); // IV
    EQIntersections bResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointCA1, vSecondPointCA1); // V
    EQIntersections bResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointCA2, vSecondPointCA2); // VI

    // Verification
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCA1 == EXPECTED_FIRSTPOINT_CA1);
    BOOST_CHECK(vFirstPointCA2 == EXPECTED_FIRSTPOINT_CA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
QTEST_CASE ( IntersectionPoint2_ReturnedPointIsTheClosestOneToEndpointA_Test )
{
    //
    //             A
    //            / \  LA
    //           /   \/
    //          /    /\
    //         C----x--B
    //             /
    //            LB
    //
    //             I

    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseTriangle<QVector2> TRIANGLE = QBaseTriangle<QVector2>(QVector2(SQFloat::_1, SQFloat::_3),
                                                                     QVector2(SQFloat::_3, SQFloat::_2),
                                                                     QVector2(-SQFloat::_1, SQFloat::_0));

    const QVector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SQFloat::_0_5, TRIANGLE.B);
    const QVector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SQFloat::_0_5, TRIANGLE.C);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const QVector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// Execution
    QVector2 vFirstPoint, vSecondPoint;
    LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // Verification
    BOOST_CHECK(vFirstPoint == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vFirstPoint != FARTHEST_INTERSECTION_TO_A);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A - QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B1 = QUAD.A + QVector2(SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B2 = QUAD.B + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C - QVector2(-SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = QUAD.C + QVector2(-SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B4 = QUAD.D + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT_A = QUAD.A;
    const QVector2 EXPECTED_POINT_B = QUAD.B;
    const QVector2 EXPECTED_POINT_C = QUAD.C;
    const QVector2 EXPECTED_POINT_D = QUAD.D;

	// Execution
    QVector2 vPointA;
    QVector2 vPointB;
    QVector2 vPointC;
    QVector2 vPointD;
    EQIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointA);
    EQIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointB);
    EQIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointC);
    EQIntersections eResultD = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointD);

    // Verification
    BOOST_CHECK_EQUAL(eResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultD, EXPECTED_RESULT);
    BOOST_CHECK(vPointA == EXPECTED_POINT_A);
    BOOST_CHECK(vPointB == EXPECTED_POINT_B);
    BOOST_CHECK(vPointC == EXPECTED_POINT_C);
    BOOST_CHECK(vPointD == EXPECTED_POINT_D);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with two contiguous edges of the qudrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoContiguousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_DA;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CD;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_BC;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_DA;
    const QVector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_CD;
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_POINT_AD_AB = MIDPOINT_DA;
    const QVector2 EXPECTED_POINT_BA_BC = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_CB_CD = MIDPOINT_BC;
    const QVector2 EXPECTED_POINT_DC_DA = MIDPOINT_CD;

	// Execution
    QVector2 vPointAD_AB;
    QVector2 vPointBA_BC;
    QVector2 vPointCB_CD;
    QVector2 vPointDA_AB;
    EQIntersections eResultAD_AB = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAD_AB);
    EQIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointBA_BC);
    EQIntersections eResultCB_CD = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointCB_CD);
    EQIntersections eResultDA_AB = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointDA_AB);

    // Verification
    BOOST_CHECK_EQUAL(eResultAD_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vPointAD_AB == EXPECTED_POINT_AD_AB);
    BOOST_CHECK(vPointBA_BC == EXPECTED_POINT_BA_BC);
    BOOST_CHECK(vPointCB_CD == EXPECTED_POINT_CB_CD);
    BOOST_CHECK(vPointDA_AB == EXPECTED_POINT_DC_DA);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsInfiniteIntersectionsWhenLineIsContainedInQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segment is inside of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);
    const QVector2 POINT_INSIDE = QVector2(SQFloat::_1, SQFloat::_2);

    const QVector2 ENDPOINT_A1 = POINT_INSIDE;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = POINT_INSIDE;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = POINT_INSIDE;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = POINT_INSIDE;
    const QVector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT_AD_AB1 = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_BA_BC1 = MIDPOINT_BC;
    const QVector2 EXPECTED_POINT_CB_CD1 = MIDPOINT_CD;
    const QVector2 EXPECTED_POINT_DC_DA1 = MIDPOINT_DA;
    const QVector2 EXPECTED_POINT_AD_AB2 = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_BA_BC2 = MIDPOINT_BC;
    const QVector2 EXPECTED_POINT_CB_CD2 = MIDPOINT_CD;
    const QVector2 EXPECTED_POINT_DC_DA2 = MIDPOINT_DA;

	// Execution
    QVector2 vPointAD1;
    QVector2 vPointBA1;
    QVector2 vPointCB1;
    QVector2 vPointDA1;
    QVector2 vPointAD2;
    QVector2 vPointBA2;
    QVector2 vPointCB2;
    QVector2 vPointDA2;
    EQIntersections eResultAD1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAD1);
    EQIntersections eResultAD2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAD2);
    EQIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointBA1);
    EQIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointBA2);
    EQIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointCB1);
    EQIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointCB2);
    EQIntersections eResultCD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointDA1);
    EQIntersections eResultCD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointDA2);

    // Verification
    BOOST_CHECK_EQUAL(eResultAD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD2, EXPECTED_RESULT);
    BOOST_CHECK(vPointAD1 == EXPECTED_POINT_AD_AB1);
    BOOST_CHECK(vPointBA1 == EXPECTED_POINT_BA_BC1);
    BOOST_CHECK(vPointCB1 == EXPECTED_POINT_CB_CD1);
    BOOST_CHECK(vPointDA1 == EXPECTED_POINT_DC_DA1);
    BOOST_CHECK(vPointAD2 == EXPECTED_POINT_AD_AB2);
    BOOST_CHECK(vPointBA2 == EXPECTED_POINT_BA_BC2);
    BOOST_CHECK(vPointCB2 == EXPECTED_POINT_CB_CD2);
    BOOST_CHECK(vPointDA2 == EXPECTED_POINT_DC_DA2);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_4, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_5, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect but would do if the line was infinite.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_3, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_POINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two contiguous vertices of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineIntersectsTwoContiguousVertices_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const QVector2 ENDPOINT_B1 = QUAD.B + (QUAD.B - QUAD.A);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const QVector2 ENDPOINT_B2 = QUAD.C + (QUAD.C - QUAD.B);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const QVector2 ENDPOINT_B3 = QUAD.D + (QUAD.D - QUAD.C);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const QVector2 ENDPOINT_B4 = QUAD.A + (QUAD.A - QUAD.D);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_POINT_AB = QUAD.A;
    const QVector2 EXPECTED_POINT_BC = QUAD.B;
    const QVector2 EXPECTED_POINT_CD = QUAD.C;
    const QVector2 EXPECTED_POINT_DA = QUAD.D;

	// Execution
    QVector2 vPointAB;
    QVector2 vPointBC;
    QVector2 vPointCD;
    QVector2 vPointDA;
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB);
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointBC);
    EQIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointCD);
    EQIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointDA);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCD == EXPECTED_POINT_CD);
    BOOST_CHECK(vPointDA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_4, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A - (QUAD.A - QUAD.B).Normalize();
    const QVector2 ENDPOINT_B1 = QUAD.B - (QUAD.B - QUAD.A).Normalize();
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B - (QUAD.B - QUAD.C).Normalize();
    const QVector2 ENDPOINT_B2 = QUAD.C - (QUAD.C - QUAD.B).Normalize();
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C - (QUAD.C - QUAD.D).Normalize();
    const QVector2 ENDPOINT_B3 = QUAD.D - (QUAD.D - QUAD.C).Normalize();
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D - (QUAD.D - QUAD.A).Normalize();
    const QVector2 ENDPOINT_B4 = QUAD.A - (QUAD.A - QUAD.D).Normalize();
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_POINT_AB = LINE_SEGMENT1.A;
    const QVector2 EXPECTED_POINT_BC = LINE_SEGMENT2.A;
    const QVector2 EXPECTED_POINT_CD = LINE_SEGMENT3.A;
    const QVector2 EXPECTED_POINT_DA = LINE_SEGMENT4.A;

	// Execution
    QVector2 vPointAB;
    QVector2 vPointBC;
    QVector2 vPointCD;
    QVector2 vPointDA;
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB);
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointBC);
    EQIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointCD);
    EQIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointDA);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCD == EXPECTED_POINT_CD);
    BOOST_CHECK(vPointDA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns one intersection when the an end point of the line coincides with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const QVector2 ENDPOINT_B1 = QUAD.A;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const QVector2 ENDPOINT_B2 = QUAD.B;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const QVector2 ENDPOINT_B3 = QUAD.C;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const QVector2 ENDPOINT_B4 = QUAD.D;
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT_A1 = QUAD.A;
    const QVector2 EXPECTED_POINT_B1 = QUAD.B;
    const QVector2 EXPECTED_POINT_C1 = QUAD.C;
    const QVector2 EXPECTED_POINT_D1 = QUAD.D;
    const QVector2 EXPECTED_POINT_A2 = QUAD.A;
    const QVector2 EXPECTED_POINT_B2 = QUAD.B;
    const QVector2 EXPECTED_POINT_C2 = QUAD.C;
    const QVector2 EXPECTED_POINT_D2 = QUAD.D;

	// Execution
    QVector2 vPointA1;
    QVector2 vPointB1;
    QVector2 vPointC1;
    QVector2 vPointD1;
    QVector2 vPointA2;
    QVector2 vPointB2;
    QVector2 vPointC2;
    QVector2 vPointD2;
    EQIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointA1);
    EQIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointA2);
    EQIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointB1);
    EQIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointB2);
    EQIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointC1);
    EQIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointC2);
    EQIntersections eResultD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointD1);
    EQIntersections eResultD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointD2);

    // Verification
    BOOST_CHECK_EQUAL(eResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultD2, EXPECTED_RESULT);
    BOOST_CHECK(vPointA1 == EXPECTED_POINT_A1);
    BOOST_CHECK(vPointB1 == EXPECTED_POINT_B1);
    BOOST_CHECK(vPointC1 == EXPECTED_POINT_C1);
    BOOST_CHECK(vPointD1 == EXPECTED_POINT_D1);
    BOOST_CHECK(vPointA2 == EXPECTED_POINT_A2);
    BOOST_CHECK(vPointB2 == EXPECTED_POINT_B2);
    BOOST_CHECK(vPointC2 == EXPECTED_POINT_C2);
    BOOST_CHECK(vPointD2 == EXPECTED_POINT_D2);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoNonContiguousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_BC;
    const QVector2 ENDPOINT_B1 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_DA;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CD;
    const QVector2 ENDPOINT_B2 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_POINT_AD_BC = MIDPOINT_DA;
    const QVector2 EXPECTED_POINT_AB_CD = MIDPOINT_AB;

	// Execution
    QVector2 vPointAD_BC;
    QVector2 vPointAB_CD;
    EQIntersections eResultAD_BC = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAD_BC);
    EQIntersections eResultAB_CD = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAB_CD);

    // Verification
    BOOST_CHECK_EQUAL(eResultAD_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB_CD, EXPECTED_RESULT);
    BOOST_CHECK(vPointAD_BC == EXPECTED_POINT_AD_BC);
    BOOST_CHECK(vPointAB_CD == EXPECTED_POINT_AB_CD);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint3_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_3),
                                                       QVector2(SQFloat::_1, SQFloat::_1),
                                                       QVector2(SQFloat::_3, SQFloat::_1));

    const QVector2 ENDPOINT = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint3_AssertionFailsWhenAllVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX = QVector2(SQFloat::_1, SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX, VERTEX, VERTEX, VERTEX);

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_CD;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CD + QVector2(-SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = MIDPOINT_DA;
    const QVector2 ENDPOINT_B4 = MIDPOINT_DA + QVector2(-SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT_AB1 = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_BC1 = MIDPOINT_BC;
    const QVector2 EXPECTED_POINT_CD1 = MIDPOINT_CD;
    const QVector2 EXPECTED_POINT_DA1 = MIDPOINT_DA;
    const QVector2 EXPECTED_POINT_AB2 = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_BC2 = MIDPOINT_BC;
    const QVector2 EXPECTED_POINT_CD2 = MIDPOINT_CD;
    const QVector2 EXPECTED_POINT_DA2 = MIDPOINT_DA;

	// Execution
    QVector2 vPointAB1;
    QVector2 vPointBC1;
    QVector2 vPointCD1;
    QVector2 vPointDA1;
    QVector2 vPointAB2;
    QVector2 vPointBC2;
    QVector2 vPointCD2;
    QVector2 vPointDA2;
    EQIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB1);
    EQIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAB2);
    EQIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointBC1);
    EQIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointBC2);
    EQIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointCD1);
    EQIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointCD2);
    EQIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointDA1);
    EQIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointDA2);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA2, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointCD1 == EXPECTED_POINT_CD1);
    BOOST_CHECK(vPointDA1 == EXPECTED_POINT_DA1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCD2 == EXPECTED_POINT_CD2);
    BOOST_CHECK(vPointDA2 == EXPECTED_POINT_DA2);
}

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral and the other endpoint is inside the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherEndpointIsInsideTheQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 CENTER_POINT = QUAD.A.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_CD;
    const QVector2 ENDPOINT_B3 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = MIDPOINT_DA;
    const QVector2 ENDPOINT_B4 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_POINT_AB1 = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_BC1 = MIDPOINT_BC;
    const QVector2 EXPECTED_POINT_CD1 = MIDPOINT_CD;
    const QVector2 EXPECTED_POINT_DA1 = MIDPOINT_DA;
    const QVector2 EXPECTED_POINT_AB2 = MIDPOINT_AB;
    const QVector2 EXPECTED_POINT_BC2 = MIDPOINT_BC;
    const QVector2 EXPECTED_POINT_CD2 = MIDPOINT_CD;
    const QVector2 EXPECTED_POINT_DA2 = MIDPOINT_DA;

	// Execution
    QVector2 vPointAB1;
    QVector2 vPointBC1;
    QVector2 vPointCD1;
    QVector2 vPointDA1;
    QVector2 vPointAB2;
    QVector2 vPointBC2;
    QVector2 vPointCD2;
    QVector2 vPointDA2;
    EQIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB1);
    EQIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAB2);
    EQIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointBC1);
    EQIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointBC2);
    EQIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointCD1);
    EQIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointCD2);
    EQIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointDA1);
    EQIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointDA2);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA2, EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointCD1 == EXPECTED_POINT_CD1);
    BOOST_CHECK(vPointDA1 == EXPECTED_POINT_DA1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCD2 == EXPECTED_POINT_CD2);
    BOOST_CHECK(vPointDA2 == EXPECTED_POINT_DA2);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
QTEST_CASE ( IntersectionPoint3_ReturnedPointIsTheClosestOneToEndpointA_Test )
{

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const QVector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// Execution
    QVector2 vFirstPoint;
    LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPoint); // I

    // Verification
    BOOST_CHECK(vFirstPoint == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vFirstPoint != FARTHEST_INTERSECTION_TO_A);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A - QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 ENDPOINT_B1 = QUAD.A + QVector2(SQFloat::_1, SQFloat::_0);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B2 = QUAD.B + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C - QVector2(-SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B3 = QUAD.C + QVector2(-SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D - QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 ENDPOINT_B4 = QUAD.D + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT_A = QUAD.A;
    const QVector2 EXPECTED_FIRSTPOINT_B = QUAD.B;
    const QVector2 EXPECTED_FIRSTPOINT_C = QUAD.C;
    const QVector2 EXPECTED_FIRSTPOINT_D = QUAD.D;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointA, vSecondPointA;
    QVector2 vFirstPointB, vSecondPointB;
    QVector2 vFirstPointC, vSecondPointC;
    QVector2 vFirstPointD, vSecondPointD;
    EQIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointA, vSecondPointA);
    EQIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointB, vSecondPointB);
    EQIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointC, vSecondPointC);
    EQIntersections eResultD = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointD, vSecondPointD);

    // Verification
    BOOST_CHECK_EQUAL(eResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultD, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstPointB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstPointC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstPointD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vSecondPointA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointD == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with two contiguous edges of the qudrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoContiguousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_DA;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CD;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_BC;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_DA;
    const QVector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_CD;
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_FIRSTPOINT_AD_AB = MIDPOINT_DA;
    const QVector2 EXPECTED_FIRSTPOINT_BA_BC = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_CB_CD = MIDPOINT_BC;
    const QVector2 EXPECTED_FIRSTPOINT_DC_DA = MIDPOINT_CD;
    const QVector2 EXPECTED_SECONDPOINT_AD_AB = MIDPOINT_AB;
    const QVector2 EXPECTED_SECONDPOINT_BA_BC = MIDPOINT_BC;
    const QVector2 EXPECTED_SECONDPOINT_CB_CD = MIDPOINT_CD;
    const QVector2 EXPECTED_SECONDPOINT_DC_DA = MIDPOINT_DA;

	// Execution
    QVector2 vFirstPointAD_AB;
    QVector2 vFirstPointBA_BC;
    QVector2 vFirstPointCB_CD;
    QVector2 vFirstPointDA_AB;
    QVector2 vSecondPointAD_AB;
    QVector2 vSecondPointBA_BC;
    QVector2 vSecondPointCB_CD;
    QVector2 vSecondPointDA_AB;
    EQIntersections eResultAD_AB = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAD_AB, vSecondPointAD_AB);
    EQIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointBA_BC, vSecondPointBA_BC);
    EQIntersections eResultCB_CD = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointCB_CD, vSecondPointCB_CD);
    EQIntersections eResultDA_AB = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointDA_AB, vSecondPointDA_AB);

    // Verification
    BOOST_CHECK_EQUAL(eResultAD_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA_AB, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAD_AB == EXPECTED_FIRSTPOINT_AD_AB);
    BOOST_CHECK(vFirstPointBA_BC == EXPECTED_FIRSTPOINT_BA_BC);
    BOOST_CHECK(vFirstPointCB_CD == EXPECTED_FIRSTPOINT_CB_CD);
    BOOST_CHECK(vFirstPointDA_AB == EXPECTED_FIRSTPOINT_DC_DA);
    BOOST_CHECK(vSecondPointAD_AB == EXPECTED_SECONDPOINT_AD_AB);
    BOOST_CHECK(vSecondPointBA_BC == EXPECTED_SECONDPOINT_BA_BC);
    BOOST_CHECK(vSecondPointCB_CD == EXPECTED_SECONDPOINT_CB_CD);
    BOOST_CHECK(vSecondPointDA_AB == EXPECTED_SECONDPOINT_DC_DA);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsInfiniteIntersectionsWhenLineIsContainedInQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_2, SQFloat::_2);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Infinite;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPoint = QVector2::GetZeroVector();
    QVector2 vSecondPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segment is inside of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);
    const QVector2 POINT_INSIDE = QVector2(SQFloat::_1, SQFloat::_2);

    const QVector2 ENDPOINT_A1 = POINT_INSIDE;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = POINT_INSIDE;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = POINT_INSIDE;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = POINT_INSIDE;
    const QVector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - POINT_INSIDE;
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT_AD_AB1 = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BA_BC1 = MIDPOINT_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CB_CD1 = MIDPOINT_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DC_DA1 = MIDPOINT_DA;
    const QVector2 EXPECTED_FIRSTPOINT_AD_AB2 = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BA_BC2 = MIDPOINT_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CB_CD2 = MIDPOINT_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DC_DA2 = MIDPOINT_DA;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointAD1, vSecondPointAD1;
    QVector2 vFirstPointBA1, vSecondPointBA1;
    QVector2 vFirstPointCB1, vSecondPointCB1;
    QVector2 vFirstPointDA1, vSecondPointDA1;
    QVector2 vFirstPointAD2, vSecondPointAD2;
    QVector2 vFirstPointBA2, vSecondPointBA2;
    QVector2 vFirstPointCB2, vSecondPointCB2;
    QVector2 vFirstPointDA2, vSecondPointDA2;
    EQIntersections eResultAD1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAD1, vSecondPointAD1);
    EQIntersections eResultAD2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAD2, vSecondPointAD2);
    EQIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointBA1, vSecondPointBA1);
    EQIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointBA2, vSecondPointBA2);
    EQIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointCB1, vSecondPointCB1);
    EQIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointCB2, vSecondPointCB2);
    EQIntersections eResultCD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointDA1, vSecondPointDA1);
    EQIntersections eResultCD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointDA2, vSecondPointDA2);

    // Verification
    BOOST_CHECK_EQUAL(eResultAD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAD1 == EXPECTED_FIRSTPOINT_AD_AB1);
    BOOST_CHECK(vFirstPointBA1 == EXPECTED_FIRSTPOINT_BA_BC1);
    BOOST_CHECK(vFirstPointCB1 == EXPECTED_FIRSTPOINT_CB_CD1);
    BOOST_CHECK(vFirstPointDA1 == EXPECTED_FIRSTPOINT_DC_DA1);
    BOOST_CHECK(vFirstPointAD2 == EXPECTED_FIRSTPOINT_AD_AB2);
    BOOST_CHECK(vFirstPointBA2 == EXPECTED_FIRSTPOINT_BA_BC2);
    BOOST_CHECK(vFirstPointCB2 == EXPECTED_FIRSTPOINT_CB_CD2);
    BOOST_CHECK(vFirstPointDA2 == EXPECTED_FIRSTPOINT_DC_DA2);
    BOOST_CHECK(vSecondPointAD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersect_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_4, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_5, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPoint = QVector2::GetZeroVector();
    QVector2 vSecondPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect but would do if the line was infinite.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_3, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_None;
    const QVector2 EXPECTED_FIRSTPOINT = QVector2::GetZeroVector();
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPoint = QVector2::GetZeroVector();
    QVector2 vSecondPoint = QVector2::GetZeroVector();
    EQIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two contiguous vertices of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineIntersectsTwoContiguousVertices_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const QVector2 ENDPOINT_B1 = QUAD.B + (QUAD.B - QUAD.A);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const QVector2 ENDPOINT_B2 = QUAD.C + (QUAD.C - QUAD.B);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const QVector2 ENDPOINT_B3 = QUAD.D + (QUAD.D - QUAD.C);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const QVector2 ENDPOINT_B4 = QUAD.A + (QUAD.A - QUAD.D);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_FIRSTPOINT_AB = QUAD.A;
    const QVector2 EXPECTED_FIRSTPOINT_BC = QUAD.B;
    const QVector2 EXPECTED_FIRSTPOINT_CD = QUAD.C;
    const QVector2 EXPECTED_FIRSTPOINT_DA = QUAD.D;
    const QVector2 EXPECTED_SECONDPOINT_AB = QUAD.B;
    const QVector2 EXPECTED_SECONDPOINT_BC = QUAD.C;
    const QVector2 EXPECTED_SECONDPOINT_CD = QUAD.D;
    const QVector2 EXPECTED_SECONDPOINT_DA = QUAD.A;

	// Execution
    QVector2 vFirstPointAB, vSecondPointAB;
    QVector2 vFirstPointBC, vSecondPointBC;
    QVector2 vFirstPointCD, vSecondPointCD;
    QVector2 vFirstPointDA, vSecondPointDA;
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB, vSecondPointAB);
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointBC, vSecondPointBC);
    EQIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointCD, vSecondPointCD);
    EQIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointDA, vSecondPointDA);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstPointDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondPointDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_4, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A - (QUAD.A - QUAD.B).Normalize();
    const QVector2 ENDPOINT_B1 = QUAD.B - (QUAD.B - QUAD.A).Normalize();
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = QUAD.B - (QUAD.B - QUAD.C).Normalize();
    const QVector2 ENDPOINT_B2 = QUAD.C - (QUAD.C - QUAD.B).Normalize();
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 ENDPOINT_A3 = QUAD.C - (QUAD.C - QUAD.D).Normalize();
    const QVector2 ENDPOINT_B3 = QUAD.D - (QUAD.D - QUAD.C).Normalize();
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const QVector2 ENDPOINT_A4 = QUAD.D - (QUAD.D - QUAD.A).Normalize();
    const QVector2 ENDPOINT_B4 = QUAD.A - (QUAD.A - QUAD.D).Normalize();
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_FIRSTPOINT_AB = LINE_SEGMENT1.A;
    const QVector2 EXPECTED_FIRSTPOINT_BC = LINE_SEGMENT2.A;
    const QVector2 EXPECTED_FIRSTPOINT_CD = LINE_SEGMENT3.A;
    const QVector2 EXPECTED_FIRSTPOINT_DA = LINE_SEGMENT4.A;
    const QVector2 EXPECTED_SECONDPOINT_AB = LINE_SEGMENT1.B;
    const QVector2 EXPECTED_SECONDPOINT_BC = LINE_SEGMENT2.B;
    const QVector2 EXPECTED_SECONDPOINT_CD = LINE_SEGMENT3.B;
    const QVector2 EXPECTED_SECONDPOINT_DA = LINE_SEGMENT4.B;

	// Execution
    QVector2 vFirstPointAB, vSecondPointAB;
    QVector2 vFirstPointBC, vSecondPointBC;
    QVector2 vFirstPointCD, vSecondPointCD;
    QVector2 vFirstPointDA, vSecondPointDA;
    EQIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB, vSecondPointAB);
    EQIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointBC, vSecondPointBC);
    EQIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointCD, vSecondPointCD);
    EQIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointDA, vSecondPointDA);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstPointDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondPointDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns one intersection when the an end point of the line coincides with a vertex of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const QVector2 ENDPOINT_B1 = QUAD.A;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const QVector2 ENDPOINT_B2 = QUAD.B;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const QVector2 ENDPOINT_B3 = QUAD.C;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const QVector2 ENDPOINT_B4 = QUAD.D;
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT_A1 = QUAD.A;
    const QVector2 EXPECTED_FIRSTPOINT_B1 = QUAD.B;
    const QVector2 EXPECTED_FIRSTPOINT_C1 = QUAD.C;
    const QVector2 EXPECTED_FIRSTPOINT_D1 = QUAD.D;
    const QVector2 EXPECTED_FIRSTPOINT_A2 = QUAD.A;
    const QVector2 EXPECTED_FIRSTPOINT_B2 = QUAD.B;
    const QVector2 EXPECTED_FIRSTPOINT_C2 = QUAD.C;
    const QVector2 EXPECTED_FIRSTPOINT_D2 = QUAD.D;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointA1;
    QVector2 vFirstPointB1;
    QVector2 vFirstPointC1;
    QVector2 vFirstPointD1;
    QVector2 vFirstPointA2;
    QVector2 vFirstPointB2;
    QVector2 vFirstPointC2;
    QVector2 vFirstPointD2;
    QVector2 vSecondPointA1 = QVector2::GetZeroVector();
    QVector2 vSecondPointB1 = QVector2::GetZeroVector();
    QVector2 vSecondPointC1 = QVector2::GetZeroVector();
    QVector2 vSecondPointD1 = QVector2::GetZeroVector();
    QVector2 vSecondPointA2 = QVector2::GetZeroVector();
    QVector2 vSecondPointB2 = QVector2::GetZeroVector();
    QVector2 vSecondPointC2 = QVector2::GetZeroVector();
    QVector2 vSecondPointD2 = QVector2::GetZeroVector();
    EQIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointA1, vSecondPointA1);
    EQIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointA2, vSecondPointA2);
    EQIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointB1, vSecondPointB1);
    EQIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointB2, vSecondPointB2);
    EQIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointC1, vSecondPointC1);
    EQIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointC2, vSecondPointC2);
    EQIntersections eResultD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointD1, vSecondPointD1);
    EQIntersections eResultD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointD2, vSecondPointD2);

    // Verification
    BOOST_CHECK_EQUAL(eResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultD2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA1 == EXPECTED_FIRSTPOINT_A1);
    BOOST_CHECK(vFirstPointB1 == EXPECTED_FIRSTPOINT_B1);
    BOOST_CHECK(vFirstPointC1 == EXPECTED_FIRSTPOINT_C1);
    BOOST_CHECK(vFirstPointD1 == EXPECTED_FIRSTPOINT_D1);
    BOOST_CHECK(vFirstPointA2 == EXPECTED_FIRSTPOINT_A2);
    BOOST_CHECK(vFirstPointB2 == EXPECTED_FIRSTPOINT_B2);
    BOOST_CHECK(vFirstPointC2 == EXPECTED_FIRSTPOINT_C2);
    BOOST_CHECK(vFirstPointD2 == EXPECTED_FIRSTPOINT_D2);
    BOOST_CHECK(vSecondPointA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointD2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoNonContiguousEdges_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_BC;
    const QVector2 ENDPOINT_B1 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_DA;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CD;
    const QVector2 ENDPOINT_B2 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_Two;
    const QVector2 EXPECTED_FIRSTPOINT_AD_BC = MIDPOINT_DA;
    const QVector2 EXPECTED_FIRSTPOINT_AB_CD = MIDPOINT_AB;
    const QVector2 EXPECTED_SECONDPOINT_AD_BC = MIDPOINT_BC;
    const QVector2 EXPECTED_SECONDPOINT_AB_CD = MIDPOINT_CD;

	// Execution
    QVector2 vFirstPointAD_BC, vSecondPointAD_BC;
    QVector2 vFirstPointAB_CD, vSecondPointAB_CD;
    EQIntersections eResultAD_BC = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAD_BC, vSecondPointAD_BC);
    EQIntersections eResultAB_CD = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAB_CD, vSecondPointAB_CD);

    // Verification
    BOOST_CHECK_EQUAL(eResultAD_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB_CD, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAD_BC == EXPECTED_FIRSTPOINT_AD_BC);
    BOOST_CHECK(vFirstPointAB_CD == EXPECTED_FIRSTPOINT_AB_CD);
    BOOST_CHECK(vSecondPointAD_BC == EXPECTED_SECONDPOINT_AD_BC);
    BOOST_CHECK(vSecondPointAB_CD == EXPECTED_SECONDPOINT_AB_CD);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint4_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_3),
                                                       QVector2(SQFloat::_1, SQFloat::_1),
                                                       QVector2(SQFloat::_3, SQFloat::_1));

    const QVector2 ENDPOINT = QVector2(SQFloat::_4, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vFirstPoint;
    QVector2 vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( IntersectionPoint4_AssertionFailsWhenAllVerticesCoincide_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 VERTEX = QVector2(SQFloat::_1, SQFloat::_2);
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(VERTEX, VERTEX, VERTEX, VERTEX);

    const QVector2 ENDPOINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 ENDPOINT_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QLineSegment2D LINE_SEGMENT = QLineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QVector2 vFirstPoint;
    QVector2 vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);
    }
    catch(...) // [TODO] Thund: Use a concrete exception when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = MIDPOINT_AB + QVector2(SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + QVector2(SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_CD;
    const QVector2 ENDPOINT_B3 = MIDPOINT_CD + QVector2(-SQFloat::_1, -SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = MIDPOINT_DA;
    const QVector2 ENDPOINT_B4 = MIDPOINT_DA + QVector2(-SQFloat::_1, SQFloat::_1);
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT_AB1 = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BC1 = MIDPOINT_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CD1 = MIDPOINT_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DA1 = MIDPOINT_DA;
    const QVector2 EXPECTED_FIRSTPOINT_AB2 = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BC2 = MIDPOINT_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CD2 = MIDPOINT_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DA2 = MIDPOINT_DA;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointAB1;
    QVector2 vFirstPointBC1;
    QVector2 vFirstPointCD1;
    QVector2 vFirstPointDA1;
    QVector2 vFirstPointAB2;
    QVector2 vFirstPointBC2;
    QVector2 vFirstPointCD2;
    QVector2 vFirstPointDA2;
    QVector2 vSecondPointAB1 = QVector2::GetZeroVector();
    QVector2 vSecondPointBC1 = QVector2::GetZeroVector();
    QVector2 vSecondPointCD1 = QVector2::GetZeroVector();
    QVector2 vSecondPointDA1 = QVector2::GetZeroVector();
    QVector2 vSecondPointAB2 = QVector2::GetZeroVector();
    QVector2 vSecondPointBC2 = QVector2::GetZeroVector();
    QVector2 vSecondPointCD2 = QVector2::GetZeroVector();
    QVector2 vSecondPointDA2 = QVector2::GetZeroVector();
    EQIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB1, vSecondPointAB1);
    EQIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAB2, vSecondPointAB2);
    EQIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointBC1, vSecondPointBC1);
    EQIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointBC2, vSecondPointBC2);
    EQIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointCD1, vSecondPointCD1);
    EQIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointCD2, vSecondPointCD2);
    EQIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointDA1, vSecondPointDA1);
    EQIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointDA2, vSecondPointDA2);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointCD1 == EXPECTED_FIRSTPOINT_CD1);
    BOOST_CHECK(vFirstPointDA1 == EXPECTED_FIRSTPOINT_DA1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCD2 == EXPECTED_FIRSTPOINT_CD2);
    BOOST_CHECK(vFirstPointDA2 == EXPECTED_FIRSTPOINT_DA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral and the other endpoint is inside the quadrilateral.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherEndpointIsInsideTheQuadrilateral_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 CENTER_POINT = QUAD.A.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);
    const QVector2 MIDPOINT_CD = QUAD.C.Lerp(SQFloat::_0_5, QUAD.D);
    const QVector2 MIDPOINT_DA = QUAD.D.Lerp(SQFloat::_0_5, QUAD.A);

    const QVector2 ENDPOINT_A1 = MIDPOINT_AB;
    const QVector2 ENDPOINT_B1 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT1 = QLineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const QVector2 ENDPOINT_A2 = MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT3 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const QLineSegment2D LINE_SEGMENT4 = QLineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const QVector2 ENDPOINT_A3 = MIDPOINT_CD;
    const QVector2 ENDPOINT_B3 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT5 = QLineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const QLineSegment2D LINE_SEGMENT6 = QLineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const QVector2 ENDPOINT_A4 = MIDPOINT_DA;
    const QVector2 ENDPOINT_B4 = CENTER_POINT;
    const QLineSegment2D LINE_SEGMENT7 = QLineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const QLineSegment2D LINE_SEGMENT8 = QLineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EQIntersections EXPECTED_RESULT = EQIntersections::E_One;
    const QVector2 EXPECTED_FIRSTPOINT_AB1 = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BC1 = MIDPOINT_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CD1 = MIDPOINT_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DA1 = MIDPOINT_DA;
    const QVector2 EXPECTED_FIRSTPOINT_AB2 = MIDPOINT_AB;
    const QVector2 EXPECTED_FIRSTPOINT_BC2 = MIDPOINT_BC;
    const QVector2 EXPECTED_FIRSTPOINT_CD2 = MIDPOINT_CD;
    const QVector2 EXPECTED_FIRSTPOINT_DA2 = MIDPOINT_DA;
    const QVector2 EXPECTED_SECONDPOINT = QVector2::GetZeroVector();

	// Execution
    QVector2 vFirstPointAB1;
    QVector2 vFirstPointBC1;
    QVector2 vFirstPointCD1;
    QVector2 vFirstPointDA1;
    QVector2 vFirstPointAB2;
    QVector2 vFirstPointBC2;
    QVector2 vFirstPointCD2;
    QVector2 vFirstPointDA2;
    QVector2 vSecondPointAB1 = QVector2::GetZeroVector();
    QVector2 vSecondPointBC1 = QVector2::GetZeroVector();
    QVector2 vSecondPointCD1 = QVector2::GetZeroVector();
    QVector2 vSecondPointDA1 = QVector2::GetZeroVector();
    QVector2 vSecondPointAB2 = QVector2::GetZeroVector();
    QVector2 vSecondPointBC2 = QVector2::GetZeroVector();
    QVector2 vSecondPointCD2 = QVector2::GetZeroVector();
    QVector2 vSecondPointDA2 = QVector2::GetZeroVector();
    EQIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB1, vSecondPointAB1);
    EQIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAB2, vSecondPointAB2);
    EQIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointBC1, vSecondPointBC1);
    EQIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointBC2, vSecondPointBC2);
    EQIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointCD1, vSecondPointCD1);
    EQIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointCD2, vSecondPointCD2);
    EQIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointDA1, vSecondPointDA1);
    EQIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointDA2, vSecondPointDA2);

    // Verification
    BOOST_CHECK_EQUAL(eResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(eResultDA2, EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointCD1 == EXPECTED_FIRSTPOINT_CD1);
    BOOST_CHECK(vFirstPointDA1 == EXPECTED_FIRSTPOINT_DA1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCD2 == EXPECTED_FIRSTPOINT_CD2);
    BOOST_CHECK(vFirstPointDA2 == EXPECTED_FIRSTPOINT_DA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
QTEST_CASE ( IntersectionPoint4_ReturnedPointIsTheClosestOneToEndpointA_Test )
{

    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
    using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;

    // Preparation
    const QBaseQuadrilateral QUAD = QBaseQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                                       QVector2(SQFloat::_3, SQFloat::_2),
                                                       QVector2(SQFloat::_3, SQFloat::_0),
                                                       QVector2(-SQFloat::_1, SQFloat::_1));

    const QVector2 MIDPOINT_AB = QUAD.A.Lerp(SQFloat::_0_5, QUAD.B);
    const QVector2 MIDPOINT_BC = QUAD.B.Lerp(SQFloat::_0_5, QUAD.C);

    const QVector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const QVector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const QLineSegment2D LINE_SEGMENT2 = QLineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const QVector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const QVector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// Execution
    QVector2 vFirstPoint, vSecondPoint;
    LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint); // I

    // Verification
    BOOST_CHECK(vFirstPoint == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vFirstPoint != FARTHEST_INTERSECTION_TO_A);
}

// [TODO] Thund: It's necessary to test whether one intersection is returned or not when 
//               the line is partially contained in an edge.

// End - Test Suite: QLineSegment2D
QTEST_SUITE_END()
