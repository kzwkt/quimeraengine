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

#include "QQuadrilateral.h"
#include "QTransformationMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;
using Kinesis::QuimeraEngine::Tools::Math::QQuadrilateral;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;

QTEST_SUITE_BEGIN( QQuadrilateral_TestSuite )


/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;
    
    // Execution
    QQuadrilateral quadrilateralUT;
    
    // Verification
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if copy constructor sets quadrilateral components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_6, SQFloat::_7);
    
    const QQuadrilateral QUAD_TO_COPY = QQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                       EXPECTED_VALUE_FOR_B,
                                                       EXPECTED_VALUE_FOR_C, 
                                                       EXPECTED_VALUE_FOR_D);

    // Execution
    QQuadrilateral quadrilateralUT = QUAD_TO_COPY;
    
    // Verification
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks if base copy constructor sets quadrilateral components properly.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_6, SQFloat::_7);
    
    const QBaseQuadrilateral QUAD_TO_COPY = QBaseQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                               EXPECTED_VALUE_FOR_B,
                                                               EXPECTED_VALUE_FOR_C, 
                                                               EXPECTED_VALUE_FOR_D);

    // Execution
    QQuadrilateral quadrilateralUT = QUAD_TO_COPY;
    
    // Verification
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreCorrectlySet_Test )
{
	// Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_6, SQFloat::_7);
    
    // Execution
    QQuadrilateral quadrilateralUT = QQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                    EXPECTED_VALUE_FOR_B,
                                                    EXPECTED_VALUE_FOR_C,
                                                    EXPECTED_VALUE_FOR_D);

    // Verification
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks that it returns a square whose edges' length equal one.
/// </summary>
QTEST_CASE ( GetUnitSquare_ReturnsTheExpectedSquare_Test )
{
	// Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_0_5, SQFloat::_0_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_0_5, SQFloat::_0_5);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_0_5, -SQFloat::_0_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(-SQFloat::_0_5, -SQFloat::_0_5);
    
    // Execution
    QQuadrilateral quadrilateralUT = QQuadrilateral::GetUnitSquare();

    // Verification
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks if assignation operator sets quadrilateral components properly.
/// </summary>
QTEST_CASE ( AssignationOperator_ValuesAreCopiedProperly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_6, SQFloat::_7);
    
    const QBaseQuadrilateral QUAD_TO_COPY = QBaseQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                               EXPECTED_VALUE_FOR_B,
                                                               EXPECTED_VALUE_FOR_C, 
                                                               EXPECTED_VALUE_FOR_D);

    // Execution
    QQuadrilateral quadrilateralUT;
    quadrilateralUT = QUAD_TO_COPY;
    
    // Verification
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks that it returns False when the point doesn't belong to the quadrilateral.
/// </summary>
QTEST_CASE ( Contains_ReturnsFalseWhenThePointIsNotInsideTheQuadrilateral_Test )
{
    //   A----------B
    //   |          |
    //   |          |   P
    //   |          |
    //   |          |
    //   D----------C
    //

    // Preparation
    const QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    const QVector2 POINT = QVector2(SQFloat::_3, SQFloat::_4);

    const bool EXPECTED_RESULT = false;

    // Execution
    bool bResult = QUAD.Contains(POINT);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the point belongs to one of the edges of the quadrilateral.
/// </summary>
QTEST_CASE ( Contains_ReturnsTrueWhenThePointBelongsToAnEdgeOfQuadrilateral_Test )
{
    //   A----P-----B   A----------B   A----------B   A----------B
    //   |          |   |          |   |          |   |          |
    //   |          |   |          P   |          |   |          |
    //   |          |   |          |   |          |   P          |
    //   |          |   |          |   |          |   |          |
    //   D----------C   D----------C   D----P-----C   D----------C
    //
    //        I              II             III           IV

    // Preparation
    const QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    const QVector2 POINT_AB = QUAD.A.Lerp(SQFloat::_0_25, QUAD.B);
    const QVector2 POINT_BC = QUAD.B.Lerp(SQFloat::_0_25, QUAD.C);
    const QVector2 POINT_CD = QUAD.C.Lerp(SQFloat::_0_25, QUAD.D);
    const QVector2 POINT_DA = QUAD.D.Lerp(SQFloat::_0_25, QUAD.A);

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResultAB = QUAD.Contains(POINT_AB); // I
    bool bResultBC = QUAD.Contains(POINT_BC); // II
    bool bResultCD = QUAD.Contains(POINT_CD); // III
    bool bResultDA = QUAD.Contains(POINT_DA); // IV
    
    // Verification
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the point coincides with one of the vertices of the quadrilateral.
/// </summary>
QTEST_CASE ( Contains_ReturnsTrueWhenThePointCoincidesWithVertexOfQuadrilateral_Test )
{
    //   AP---------B   A----------BP  A----------B   A----------B
    //   |          |   |          |   |          |   |          |
    //   |          |   |          |   |          |   |          |
    //   |          |   |          |   |          |   |          |
    //   |          |   |          |   |          |   |          |
    //   D----------C   D----------C   D----------CP  DP---------C
    //
    //        I              II             III           IV

    // Preparation
    const QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    const QVector2 POINT_A = QUAD.A;
    const QVector2 POINT_B = QUAD.B;
    const QVector2 POINT_C = QUAD.C;
    const QVector2 POINT_D = QUAD.D;

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResultA = QUAD.Contains(POINT_A); // I
    bool bResultB = QUAD.Contains(POINT_B); // II
    bool bResultC = QUAD.Contains(POINT_C); // III
    bool bResultD = QUAD.Contains(POINT_D); // IV
    
    // Verification
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the point belongs to the quadrilateral.
/// </summary>
QTEST_CASE ( Contains_ReturnsTrueWhenThePointIsInsideTheQuadrilateral_Test )
{
    //   A----------B
    //   |          |
    //   |       P  |
    //   |          |
    //   |          |
    //   D----------C
    //

    // Preparation
    const QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    const QVector2 POINT = QVector2(SQFloat::_0_25, SQFloat::_0_25);

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResult = QUAD.Contains(POINT);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( Contains_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // Preparation
    const QVector2 QUAD_POINT = QVector2(SQFloat::_1, SQFloat::_2);
    const QQuadrilateral QUAD = QQuadrilateral(QUAD_POINT, QUAD_POINT, QUAD_POINT, QUAD_POINT);
    const QVector2 POINT = QVector2(SQFloat::_0_25, SQFloat::_0_25);

    const bool ASSERTION_FAILED = true;

    // Execution
    bool bAssertionFailed = false;

    try
    {
        QUAD.Contains(POINT);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns what expected when the quadrilateral is complex (two opposite edges intersect).
/// </summary>
QTEST_CASE ( Contains_ReturnsWhatExpectedWhenTheQuadrilateralIsComplex_Test )
{
    //    A----B      A----B
    //     \  /        \ P/
    //      \/  P       \/
    //      /\          /\
    //     /  \        /  \
    //    C----D      C----D
    //
    //      I           II

    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    const QVector2 AUX = QUAD.C;
    QUAD.C = QUAD.D;
    QUAD.D = AUX;
    const QVector2 POINT_OUTSIDE = QVector2(SQFloat::_0_25, SQFloat::_0);
    const QVector2 POINT_INSIDE = QVector2(SQFloat::_0, SQFloat::_0_25);

    const bool EXPECTED_RESULT_OUTSIDE = false;
    const bool EXPECTED_RESULT_INSIDE = true;

    // Execution
    bool bResultOutside = QUAD.Contains(POINT_OUTSIDE); // I
    bool bResultInside = QUAD.Contains(POINT_INSIDE); // II
    
    // Verification
    BOOST_CHECK_EQUAL(bResultOutside, EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK_EQUAL(bResultInside, EXPECTED_RESULT_INSIDE);
}

/// <summary>
/// Checks that it returns what expected when the quadrilateral is concave.
/// </summary>
QTEST_CASE ( Contains_ReturnsWhatExpectedWhenTheQuadrilateralIsConcave_Test )
{
    //       B            B
    //      /|           /|
    //     / C P        / C
    //    /   \        / P \
    //   A-----D      A-----D
    //
    //      I           II

    // Preparation
    QQuadrilateral QUAD = QQuadrilateral(QVector2(SQFloat::_1, SQFloat::_1),
                                         QVector2(SQFloat::_4, SQFloat::_5),
                                         QVector2(SQFloat::_3, SQFloat::_2),
                                         QVector2(SQFloat::_4, SQFloat::_1));

    const QVector2 POINT_OUTSIDE = QUAD.C + QVector2(SQFloat::_0_25, SQFloat::_0);
    const QVector2 POINT_INSIDE = QVector2(SQFloat::_2, SQFloat::_2);

    const bool EXPECTED_RESULT_OUTSIDE = false;
    const bool EXPECTED_RESULT_INSIDE = true;

    // Execution
    bool bResultOutside = QUAD.Contains(POINT_OUTSIDE); // I
    bool bResultInside = QUAD.Contains(POINT_INSIDE);   // II
    
    // Verification
    BOOST_CHECK_EQUAL(bResultOutside, EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK_EQUAL(bResultInside, EXPECTED_RESULT_INSIDE);
}

/// <summary>
/// Checks that it returns False when the quadrilaterals doesn't intersect.
/// </summary>
QTEST_CASE ( Intersection_ReturnsFalseWhenQuadrilateralsDoesNotIntersect_Test )
{
    //   A----------B   A----------B
    //   |          |   |          |
    //   |    1     |   |    2     |
    //   |          |   |          |
    //   |          |   |          |
    //   D----------C   D----------C
    //

    // Preparation
    const QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    const QQuadrilateral QUAD2 = QUAD1.Translate(SQFloat::_10, SQFloat::_10);

    const bool EXPECTED_RESULT = false;

    // Execution
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilaterals intersect.
/// </summary>
QTEST_CASE ( Intersection_ReturnsTrueWhenQuadrilateralsIntersect_Test )
{
    //   A----------B
    //   |          |
    //   |    1     |
    //   |     A----------B
    //   |     |    |     |
    //   D-----|----C     |
    //         |    2     |
    //         |          |
    //         D----------C
    
    // Preparation
    const QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    const QQuadrilateral QUAD2 = QUAD1.Translate(SQFloat::_0_5, SQFloat::_0_5);

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilaterals share one vertex.
/// </summary>
QTEST_CASE ( Intersection_ReturnsTrueWhenQuadrilateralsShareVertex_Test )
{
    //   A----------B
    //   |          |
    //   |    1     |
    //   |          |
    //   |          |
    //   D----------CA----B
    //               | 2  |
    //               |    |
    //               D----C
    
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q QUARTER_ROTATION = SQAngle::_90;
    const float_q HALF_ROTATION = SQAngle::_180;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q QUARTER_ROTATION = SQAngle::_HalfPi;
    const float_q HALF_ROTATION = SQAngle::_Pi;
#endif

    const QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    const QQuadrilateral QUAD2 = QUAD1;

    const QQuadrilateral QUAD1_ROT1 = QUAD1;
    const QQuadrilateral QUAD1_ROT2 = QUAD1.Rotate(QUARTER_ROTATION);
    const QQuadrilateral QUAD1_ROT3 = QUAD1.Rotate(HALF_ROTATION);
    const QQuadrilateral QUAD1_ROT4 = QUAD1.Rotate(-QUARTER_ROTATION);

    const QQuadrilateral QUAD2_ROT1 = QUAD2.Translate(SQFloat::_1, SQFloat::_1);
    const QQuadrilateral QUAD2_ROT2 = QUAD2.Rotate(QUARTER_ROTATION).Translate(SQFloat::_1, SQFloat::_1);
    const QQuadrilateral QUAD2_ROT3 = QUAD2.Rotate(HALF_ROTATION).Translate(SQFloat::_1, SQFloat::_1);
    const QQuadrilateral QUAD2_ROT4 = QUAD2.Rotate(-QUARTER_ROTATION).Translate(SQFloat::_1, SQFloat::_1);

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResultQ1R1_Q2R1 = QUAD1_ROT1.Intersection(QUAD2_ROT1);
    bool bResultQ1R1_Q2R2 = QUAD1_ROT1.Intersection(QUAD2_ROT2);
    bool bResultQ1R1_Q2R3 = QUAD1_ROT1.Intersection(QUAD2_ROT3);
    bool bResultQ1R1_Q2R4 = QUAD1_ROT1.Intersection(QUAD2_ROT4);

    bool bResultQ1R2_Q2R1 = QUAD1_ROT2.Intersection(QUAD2_ROT1);
    bool bResultQ1R2_Q2R2 = QUAD1_ROT2.Intersection(QUAD2_ROT2);
    bool bResultQ1R2_Q2R3 = QUAD1_ROT2.Intersection(QUAD2_ROT3);
    bool bResultQ1R2_Q2R4 = QUAD1_ROT2.Intersection(QUAD2_ROT4);

    bool bResultQ1R3_Q2R1 = QUAD1_ROT3.Intersection(QUAD2_ROT1);
    bool bResultQ1R3_Q2R2 = QUAD1_ROT3.Intersection(QUAD2_ROT2);
    bool bResultQ1R3_Q2R3 = QUAD1_ROT3.Intersection(QUAD2_ROT3);
    bool bResultQ1R3_Q2R4 = QUAD1_ROT3.Intersection(QUAD2_ROT4);

    bool bResultQ1R4_Q2R1 = QUAD1_ROT4.Intersection(QUAD2_ROT1);
    bool bResultQ1R4_Q2R2 = QUAD1_ROT4.Intersection(QUAD2_ROT2);
    bool bResultQ1R4_Q2R3 = QUAD1_ROT4.Intersection(QUAD2_ROT3);
    bool bResultQ1R4_Q2R4 = QUAD1_ROT4.Intersection(QUAD2_ROT4);
    
    // Verification
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the corner of a quadrilateral intersects with the edge of the other quadrilateral.
/// </summary>
QTEST_CASE ( Intersection_ReturnsTrueWhenOneQuadrilateralCornerIntersectsWithAnEdgeOfTheOther_Test )
{
    //   A----------B A____________B
    //   |          |/            /
    //   |    1     /     2      /
    //   |         /|           /
    //   |        D_|__________C
    //   |          |
    //   |          |
    //   D----------C
    
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q INITIAL_ROTATION = SQAngle::_45;
    const float_q QUARTER_ROTATION = SQAngle::_90;
    const float_q HALF_ROTATION = SQAngle::_180;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q INITIAL_ROTATION = SQAngle::_QuarterPi;
    const float_q QUARTER_ROTATION = SQAngle::_HalfPi;
    const float_q HALF_ROTATION = SQAngle::_Pi;
#endif

    const QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    const QQuadrilateral QUAD2 = QUAD1.Rotate(QUARTER_ROTATION);

    const QQuadrilateral QUAD1_ROT1 = QUAD1;
    const QQuadrilateral QUAD1_ROT2 = QUAD1.Rotate(QUARTER_ROTATION);
    const QQuadrilateral QUAD1_ROT3 = QUAD1.Rotate(HALF_ROTATION);
    const QQuadrilateral QUAD1_ROT4 = QUAD1.Rotate(-QUARTER_ROTATION);

    const QQuadrilateral QUAD2_ROT1 = QUAD2                          .Translate(SQFloat::_1, SQFloat::_0);
    const QQuadrilateral QUAD2_ROT2 = QUAD2.Rotate(QUARTER_ROTATION) .Translate(SQFloat::_1, SQFloat::_0);
    const QQuadrilateral QUAD2_ROT3 = QUAD2.Rotate(HALF_ROTATION)    .Translate(SQFloat::_1, SQFloat::_0);
    const QQuadrilateral QUAD2_ROT4 = QUAD2.Rotate(-QUARTER_ROTATION).Translate(SQFloat::_1, SQFloat::_0);

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResultQ1R1_Q2R1 = QUAD1_ROT1.Intersection(QUAD2_ROT1);
    bool bResultQ1R1_Q2R2 = QUAD1_ROT1.Intersection(QUAD2_ROT2);
    bool bResultQ1R1_Q2R3 = QUAD1_ROT1.Intersection(QUAD2_ROT3);
    bool bResultQ1R1_Q2R4 = QUAD1_ROT1.Intersection(QUAD2_ROT4);

    bool bResultQ1R2_Q2R1 = QUAD1_ROT2.Intersection(QUAD2_ROT1);
    bool bResultQ1R2_Q2R2 = QUAD1_ROT2.Intersection(QUAD2_ROT2);
    bool bResultQ1R2_Q2R3 = QUAD1_ROT2.Intersection(QUAD2_ROT3);
    bool bResultQ1R2_Q2R4 = QUAD1_ROT2.Intersection(QUAD2_ROT4);

    bool bResultQ1R3_Q2R1 = QUAD1_ROT3.Intersection(QUAD2_ROT1);
    bool bResultQ1R3_Q2R2 = QUAD1_ROT3.Intersection(QUAD2_ROT2);
    bool bResultQ1R3_Q2R3 = QUAD1_ROT3.Intersection(QUAD2_ROT3);
    bool bResultQ1R3_Q2R4 = QUAD1_ROT3.Intersection(QUAD2_ROT4);

    bool bResultQ1R4_Q2R1 = QUAD1_ROT4.Intersection(QUAD2_ROT1);
    bool bResultQ1R4_Q2R2 = QUAD1_ROT4.Intersection(QUAD2_ROT2);
    bool bResultQ1R4_Q2R3 = QUAD1_ROT4.Intersection(QUAD2_ROT3);
    bool bResultQ1R4_Q2R4 = QUAD1_ROT4.Intersection(QUAD2_ROT4);
    
    // Verification
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one of the vertices of a quadrilateral belongs to the edge of the other quadrilateral (excluding coincidental vertices).
/// </summary>
QTEST_CASE ( Intersection_ReturnsTrueWhenOneQuadrilateralVertexBelongsToAnEdgeOfTheOther_Test )
{
    //   A----------B   A____________B
    //   |          |  /            /
    //   |    1     | /     2      /
    //   |          |/            /
    //   |          D____________C
    //   |          |
    //   |          |
    //   D----------C
    
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q INITIAL_ROTATION = SQAngle::_45;
    const float_q QUARTER_ROTATION = SQAngle::_90;
    const float_q HALF_ROTATION = SQAngle::_180;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q INITIAL_ROTATION = SQAngle::_QuarterPi;
    const float_q QUARTER_ROTATION = SQAngle::_HalfPi;
    const float_q HALF_ROTATION = SQAngle::_Pi;
#endif

    const QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    const QQuadrilateral QUAD2 = QUAD1.Rotate(INITIAL_ROTATION);

    const float_q QUAD2_RADIUS = (QUAD2.A - QUAD2.C).GetLength() / 2;
    const float_q QUAD1_AB_LENGTH = (QUAD1.A - QUAD1.B).GetLength();
    const QVector2 QUAD2_POSITION = QVector2(QUAD1_AB_LENGTH / 2 + QUAD2_RADIUS, SQFloat::_0);

    const QQuadrilateral QUAD1_ROT1 = QUAD1;
    const QQuadrilateral QUAD1_ROT2 = QUAD1.Rotate(QUARTER_ROTATION);
    const QQuadrilateral QUAD1_ROT3 = QUAD1.Rotate(HALF_ROTATION);
    const QQuadrilateral QUAD1_ROT4 = QUAD1.Rotate(-QUARTER_ROTATION);

    const QQuadrilateral QUAD2_ROT1 = QUAD2                          .Translate(QUAD2_POSITION);
    const QQuadrilateral QUAD2_ROT2 = QUAD2.Rotate(QUARTER_ROTATION) .Translate(QUAD2_POSITION);
    const QQuadrilateral QUAD2_ROT3 = QUAD2.Rotate(HALF_ROTATION)    .Translate(QUAD2_POSITION);
    const QQuadrilateral QUAD2_ROT4 = QUAD2.Rotate(-QUARTER_ROTATION).Translate(QUAD2_POSITION);

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResultQ1R1_Q2R1 = QUAD1_ROT1.Intersection(QUAD2_ROT1);
    bool bResultQ1R1_Q2R2 = QUAD1_ROT1.Intersection(QUAD2_ROT2);
    bool bResultQ1R1_Q2R3 = QUAD1_ROT1.Intersection(QUAD2_ROT3);
    bool bResultQ1R1_Q2R4 = QUAD1_ROT1.Intersection(QUAD2_ROT4);

    bool bResultQ1R2_Q2R1 = QUAD1_ROT2.Intersection(QUAD2_ROT1);
    bool bResultQ1R2_Q2R2 = QUAD1_ROT2.Intersection(QUAD2_ROT2);
    bool bResultQ1R2_Q2R3 = QUAD1_ROT2.Intersection(QUAD2_ROT3);
    bool bResultQ1R2_Q2R4 = QUAD1_ROT2.Intersection(QUAD2_ROT4);

    bool bResultQ1R3_Q2R1 = QUAD1_ROT3.Intersection(QUAD2_ROT1);
    bool bResultQ1R3_Q2R2 = QUAD1_ROT3.Intersection(QUAD2_ROT2);
    bool bResultQ1R3_Q2R3 = QUAD1_ROT3.Intersection(QUAD2_ROT3);
    bool bResultQ1R3_Q2R4 = QUAD1_ROT3.Intersection(QUAD2_ROT4);

    bool bResultQ1R4_Q2R1 = QUAD1_ROT4.Intersection(QUAD2_ROT1);
    bool bResultQ1R4_Q2R2 = QUAD1_ROT4.Intersection(QUAD2_ROT2);
    bool bResultQ1R4_Q2R3 = QUAD1_ROT4.Intersection(QUAD2_ROT3);
    bool bResultQ1R4_Q2R4 = QUAD1_ROT4.Intersection(QUAD2_ROT4);
    
    // Verification
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilaterals coincide.
/// </summary>
QTEST_CASE ( Intersection_ReturnsTrueWhenQuadrilateralsCoincide_Test )
{
    //   AA---------BB
    //   |          |
    //   |  1 & 2   |
    //   |          |
    //   |          |
    //   DD---------CC
    
    // Preparation
    const QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    const QQuadrilateral QUAD2 = QUAD1;

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one quadrilateral contains the other.
/// </summary>
QTEST_CASE ( Intersection_ReturnsTrueWhenOneQuadrilateralContainsTheOther_Test )
{
    //   A----------B
    //   |    1     |
    //   |  A----B  |
    //   |  | 2  |  |
    //   |  D----C  |
    //   D----------C
    
    // Preparation
    const QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    const QQuadrilateral QUAD2 = QUAD1.Scale(SQFloat::_0_5, SQFloat::_0_5);

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);
    
    // Verification
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
QTEST_CASE ( Intersection_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // Preparation
    const QVector2 POINT = QVector2(SQFloat::_1, SQFloat::_2);
    const QQuadrilateral QUAD1 = QQuadrilateral(POINT, POINT, POINT, POINT);
    const QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.Intersection(QUAD2);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.Intersection(QUAD1);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns True when the quadrilateral is complex.
/// </summary>
QTEST_CASE ( IsCrossed_ReturnsTrueWhenQuadrilateralIsComplex_Test )
{
    //   A----B
    //    \  /
    //     \/
    //     /\
    //    /  \
    //   D----C
    
    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    QVector2 AUX = QUAD.B;
    QUAD.B = QUAD.A;
    QUAD.A = AUX;

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResult = QUAD.IsCrossed();
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the quadrilateral is not complex.
/// </summary>
QTEST_CASE ( IsCrossed_ReturnsFalseWhenQuadrilateralIsNotComplex_Test )
{
    //   A----B
    //   |    |
    //   |    |
    //   |    |
    //   |    |
    //   D----C
    
    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();

    const bool EXPECTED_RESULT = false;

    // Execution
    bool bResult = QUAD.IsCrossed();
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilateral is convex.
/// </summary>
QTEST_CASE ( IsConvex_ReturnsTrueWhenQuadrilateralIsConvex_Test )
{
    //   A----B
    //   |    |
    //   |    |
    //   |    |
    //   |    |
    //   D----C
    
    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResult = QUAD.IsConvex();
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the quadrilateral is not convex.
/// </summary>
QTEST_CASE ( IsConvex_ReturnsFalseWhenQuadrilateralIsNotConvex_Test )
{
    //   A
    //   |\
    //   | B-C
    //   |  /
    //   | /
    //   |/
    //   D
    
    // Preparation
    QQuadrilateral QUAD = QQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                         QVector2(SQFloat::_2, SQFloat::_2),
                                         QVector2(SQFloat::_3, SQFloat::_2),
                                         QVector2(SQFloat::_1, SQFloat::_0));

    const bool EXPECTED_RESULT = false;

    // Execution
    bool bResult = QUAD.IsConvex();
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilateral is concave.
/// </summary>
QTEST_CASE ( IsConcave_ReturnsTrueWhenQuadrilateralIsConcave_Test )
{
    //   A
    //   |\
    //   | B-C
    //   |  /
    //   | /
    //   |/
    //   D
    
    // Preparation
    QQuadrilateral QUAD = QQuadrilateral(QVector2(SQFloat::_1, SQFloat::_3),
                                         QVector2(SQFloat::_2, SQFloat::_2),
                                         QVector2(SQFloat::_3, SQFloat::_2),
                                         QVector2(SQFloat::_1, SQFloat::_0));

    const bool EXPECTED_RESULT = true;

    // Execution
    bool bResult = QUAD.IsConcave();
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the quadrilateral is not concave.
/// </summary>
QTEST_CASE ( IsConcave_ReturnsFalseWhenQuadrilateralIsNotConcave_Test )
{
    //   A----B
    //   |    |
    //   |    |
    //   |    |
    //   |    |
    //   D----C

    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();

    const bool EXPECTED_RESULT = false;

    // Execution
    bool bResult = QUAD.IsConcave();
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected angle of a common corner.
/// </summary>
QTEST_CASE ( GetAngleA_ReturnsExpectedAngleForCommonCorner_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    QUAD.B = QVector2(SQFloat::_0, SQFloat::_0);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_RESULT = SQAngle::_45;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
#endif

    // Execution
    float_q fResult = QUAD.GetAngleA();
    
    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
QTEST_CASE ( GetAngleA_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.A = QVector2(SQFloat::_2, -SQFloat::_2);

    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.A = QVector2(SQFloat::_0, -SQFloat::_0_5);
    QUAD2.B = QVector2(SQFloat::_2, -SQFloat::_0_5);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q STRAIGHT_ANGLE = SQAngle::_180;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q STRAIGHT_ANGLE = SQAngle::_Pi;
#endif

    // Execution
    float_q fResult1 = QUAD1.GetAngleA(); // Corner in opposite side
    float_q fResult2 = QUAD2.GetAngleA(); // Straight angle
    
    // Verification
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
QTEST_CASE ( GetAngleA_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.B = QUAD1.A;
    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.C = QUAD2.A;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleA();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleA();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns the expected angle of a common corner.
/// </summary>
QTEST_CASE ( GetAngleB_ReturnsExpectedAngleForCommonCorner_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    QUAD.A = QVector2(SQFloat::_0, SQFloat::_0);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_RESULT = SQAngle::_45;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
#endif

    // Execution
    float_q fResult = QUAD.GetAngleB();
    
    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
QTEST_CASE ( GetAngleB_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.B = QVector2(-SQFloat::_2, -SQFloat::_2);

    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.C = QVector2(SQFloat::_2, SQFloat::_0_5);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q STRAIGHT_ANGLE = SQAngle::_180;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q STRAIGHT_ANGLE = SQAngle::_Pi;
#endif

    // Execution
    float_q fResult1 = QUAD1.GetAngleB(); // Corner in opposite side
    float_q fResult2 = QUAD2.GetAngleB(); // Straight angle
    
    // Verification
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
QTEST_CASE ( GetAngleB_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.A = QUAD1.B;
    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.C = QUAD2.B;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleB();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleB();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns the expected angle of a common corner.
/// </summary>
QTEST_CASE ( GetAngleC_ReturnsExpectedAngleForCommonCorner_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    QUAD.B = QVector2(SQFloat::_0, SQFloat::_0);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_RESULT = SQAngle::_45;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
#endif

    // Execution
    float_q fResult = QUAD.GetAngleC();
    
    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
QTEST_CASE ( GetAngleC_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.C = QVector2(-SQFloat::_2, SQFloat::_2);

    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.B = QVector2(SQFloat::_2, -SQFloat::_0_5);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q STRAIGHT_ANGLE = SQAngle::_180;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q STRAIGHT_ANGLE = SQAngle::_Pi;
#endif

    // Execution
    float_q fResult1 = QUAD1.GetAngleC(); // Corner in opposite side
    float_q fResult2 = QUAD2.GetAngleC(); // Straight angle
    
    // Verification
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
QTEST_CASE ( GetAngleC_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.B = QUAD1.C;
    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.D = QUAD2.C;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleC();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleC();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns the expected angle of a common corner.
/// </summary>
QTEST_CASE ( GetAngleD_ReturnsExpectedAngleForCommonCorner_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD = QQuadrilateral::GetUnitSquare();
    QUAD.A = QVector2(SQFloat::_0, SQFloat::_0);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_RESULT = SQAngle::_45;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
#endif

    // Execution
    float_q fResult = QUAD.GetAngleD();
    
    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
QTEST_CASE ( GetAngleD_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.D = QVector2(SQFloat::_2, SQFloat::_2);

    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.A = QVector2(-SQFloat::_2, -SQFloat::_0_5);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q STRAIGHT_ANGLE = SQAngle::_180;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q STRAIGHT_ANGLE = SQAngle::_Pi;
#endif

    // Execution
    float_q fResult1 = QUAD1.GetAngleD(); // Corner in opposite side
    float_q fResult2 = QUAD2.GetAngleD(); // Straight angle
    
    // Verification
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
QTEST_CASE ( GetAngleD_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // Preparation
    QQuadrilateral QUAD1 = QQuadrilateral::GetUnitSquare();
    QUAD1.C = QUAD1.D;
    QQuadrilateral QUAD2 = QQuadrilateral::GetUnitSquare();
    QUAD2.A = QUAD2.D;

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleD();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleD();
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that a quadrilateral is correctly rotated.
/// </summary>
QTEST_CASE ( Rotate_QuadrilateralIsCorrectlyRotated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 POINT_D = QVector2(-SQFloat::_1, SQFloat::_2);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_5, SQFloat::_0);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(-SQFloat::_2, -SQFloat::_1);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    QQuadrilateral result = QUAD.Rotate(ANGLE);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not rotated when angle is zero.
/// </summary>
QTEST_CASE ( Rotate_QuadrilateralIsNotRotatedWhenAngleIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_5, SQFloat::_0);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_2, SQFloat::_1);
    const float_q ANGLE = SQFloat::_0;

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// Execution
    QQuadrilateral result = QUAD.Rotate(ANGLE);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly translated.
/// </summary>
QTEST_CASE ( Translate1_QuadrilateralIsCorrectlyTranslated_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_0, SQFloat::_1);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_3, SQFloat::_5);

    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_4);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    QQuadrilateral result = QUAD.Translate(TRANSLATION_VECTOR);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not translated when translation is zero.
/// </summary>
QTEST_CASE ( Translate1_QuadrilateralIsNotTranslatedWhenTranslationIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_3, SQFloat::_5);

    const QVector2 TRANSLATION_VECTOR = QVector2::GetZeroVector();

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// Execution
    QQuadrilateral result = QUAD.Translate(TRANSLATION_VECTOR);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly translated.
/// </summary>
QTEST_CASE ( Translate2_QuadrilateralIsCorrectlyTranslated_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_0, SQFloat::_1);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_3, SQFloat::_5);

    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_4);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    QQuadrilateral result = QUAD.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not translated when translation is zero.
/// </summary>
QTEST_CASE ( Translate2_QuadrilateralIsNotTranslatedWhenTranslationIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_3, SQFloat::_5);

    const QVector2 TRANSLATION_VECTOR = QVector2::GetZeroVector();

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// Execution
    QQuadrilateral result = QUAD.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
QTEST_CASE ( Scale1_QuadrilateralIsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_10 + SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_4, SQFloat::_10 + SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_4, SQFloat::_10 + SQFloat::_10);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_4, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    QQuadrilateral result = QUAD.Scale(SCALING_VECTOR);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if Scale is one.
/// </summary>
QTEST_CASE ( Scale1_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_4, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// Execution
    QQuadrilateral result = QUAD.Scale(SCALING_VECTOR);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the coordinates origin when the scale equals zero.
/// </summary>
QTEST_CASE ( Scale1_AllVerticesAreMovedToCoordinatesOriginWhenScaleEqualsZero_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 EXPECTED_VALUE_FOR_ALL = QVector2::GetZeroVector();

    const QVector2 SCALING_VECTOR = QVector2::GetZeroVector();

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    QQuadrilateral result = QUAD.Scale(SCALING_VECTOR);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
QTEST_CASE ( Scale2_QuadrilateralIsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_10 + SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_4, SQFloat::_10 + SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_4, SQFloat::_10 + SQFloat::_10);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_4, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    QQuadrilateral result = QUAD.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if scale equals one.
/// </summary>
QTEST_CASE ( Scale2_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_4, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// Execution
    QQuadrilateral result = QUAD.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the coordinates origin when the scale equals zero.
/// </summary>
QTEST_CASE ( Scale2_AllVerticesAreMovedToCoordinatesOriginWhenScaleEqualsZero_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 EXPECTED_VALUE_FOR_ALL = QVector2::GetZeroVector();

    const QVector2 SCALING_VECTOR = QVector2::GetZeroVector();

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    QQuadrilateral result = QUAD.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that a quadrilateral is correctly transformed.
/// </summary>
QTEST_CASE ( Transform_QuadrilateralIsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 INIT_POS_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 INIT_POS_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 INIT_POS_C = QVector2(SQFloat::_2, SQFloat::_6);
    const QVector2 INIT_POS_D = QVector2(SQFloat::_0, SQFloat::_2);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);
   
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_0, SQFloat::_3);

    const QQuadrilateral QUAD = QQuadrilateral(INIT_POS_A, INIT_POS_B, INIT_POS_C, INIT_POS_D);

	// Execution
    const QQuadrilateral result = QUAD.Transform(TRANSFORMATION_MATRIX);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that the quadrilateral doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform_QuadrilateralDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(-SQFloat::_1, SQFloat::_2);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// Execution
    const QQuadrilateral result = QUAD.Transform(TRANSFORMATION);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices of the quadrilateral are moved to the coordinate origin.
/// </summary>
QTEST_CASE ( Transform_AllVerticesAreMovedToCoordinateOriginWhenTransfomedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 EXPECTED_RESULT_ALL = QVector2::GetZeroVector();

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// Execution
    const QQuadrilateral result = QUAD.Transform(TRANSFORMATION);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_RESULT_ALL);
    BOOST_CHECK(result.B == EXPECTED_RESULT_ALL);
    BOOST_CHECK(result.C == EXPECTED_RESULT_ALL);
    BOOST_CHECK(result.D == EXPECTED_RESULT_ALL);
}

/// <summary>
/// Checks that a quadrilateral is correctly rotated.
/// </summary>
QTEST_CASE ( RotateWithPivot_QuadrilateralIsCorrectlyRotated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 POINT_D = QVector2(-SQFloat::_1, SQFloat::_2);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, -SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_1, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_2, -SQFloat::_3);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const QVector2 PIVOT = QVector2(SQFloat::_3, SQFloat::_1);

	// Execution
    QQuadrilateral result = QUAD.RotateWithPivot(ANGLE, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not rotated when angle is zero.
/// </summary>
QTEST_CASE ( RotateWithPivot_QuadrilateralIsNotRotatedWhenAngleIsZero_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_5, SQFloat::_0);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_2, SQFloat::_1);
    const float_q ANGLE = SQFloat::_0;

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const QVector2 PIVOT = QVector2(SQFloat::_3, SQFloat::_1);

	// Execution
    QQuadrilateral result = QUAD.RotateWithPivot(ANGLE, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_QuadrilateralIsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_3, SQFloat::_10);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_3, SQFloat::_10 + SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_3, -SQFloat::_6);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QQuadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if Scale is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_4, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QQuadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the position of the pivot point when the scale equals zero.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_AllVerticesAreMovedToPositionOfPivotWhenScaleEqualsZero_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2::GetZeroVector();

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QQuadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == PIVOT);
    BOOST_CHECK(result.B == PIVOT);
    BOOST_CHECK(result.C == PIVOT);
    BOOST_CHECK(result.D == PIVOT);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_QuadrilateralIsCorrectlyScaled_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_3, SQFloat::_10);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_3, SQFloat::_10 + SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_3, -SQFloat::_6);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QQuadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if scale equals one.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_4, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QQuadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the position of the pivot point when the scale equals zero.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_AllVerticesAreMovedToPositionOfPivotWhenScaleEqualsZero_Test )
{
    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QVector2 SCALING_VECTOR = QVector2::GetZeroVector();

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QQuadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == PIVOT);
    BOOST_CHECK(result.B == PIVOT);
    BOOST_CHECK(result.C == PIVOT);
    BOOST_CHECK(result.D == PIVOT);
}

/// <summary>
/// Checks that a quadrilateral is correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot_QuadrilateralIsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 INIT_POS_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 INIT_POS_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 INIT_POS_C = QVector2(SQFloat::_2, SQFloat::_6);
    const QVector2 INIT_POS_D = QVector2(SQFloat::_0, SQFloat::_2);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);
   
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_0, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_2, SQFloat::_3);

    const QQuadrilateral QUAD = QQuadrilateral(INIT_POS_A, INIT_POS_B, INIT_POS_C, INIT_POS_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    const QQuadrilateral result = QUAD.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that the quadrilateral doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( TransformWithPivot_QuadrilateralDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // Preparation
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_0, SQFloat::_1);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

    const QQuadrilateral QUAD = QQuadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    const QQuadrilateral result = QUAD.TransformWithPivot(TRANSFORMATION, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices of the quadrilateral are moved to the position of the pivot when transformation is null.
/// </summary>
QTEST_CASE ( TransformWithPivot_AllVerticesAreMovedToPositionOfPivotWhenTransfomedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // Preparation
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);
    const QVector2 POINT_D = QVector2(SQFloat::_2, SQFloat::_0);

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetZeroMatrix();

    const QQuadrilateral QUAD = QQuadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const QVector2 PIVOT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    const QQuadrilateral result = QUAD.TransformWithPivot(TRANSFORMATION, PIVOT);
    
    // Verification
    BOOST_CHECK(result.A == PIVOT);
    BOOST_CHECK(result.B == PIVOT);
    BOOST_CHECK(result.C == PIVOT);
    BOOST_CHECK(result.D == PIVOT);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // Preparation
    QQuadrilateral QUAD = QQuadrilateral(QVector2(SQFloat::_0_25, (float_q)-0.000002f),
                                         QVector2((float_q)40000.0, SQFloat::_0),
                                         QVector2(SQFloat::_3, SQFloat::_2),
                                         QVector2(SQFloat::_1, -SQFloat::_0));

#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    const string_q EXPECTED_STRING_FORM = QE_L("QL(a(V2(0.25,-1.99999999e-006)),b(V2(40000,0)),c(V2(3,2)),d(V2(1,-0)))");
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    const string_q EXPECTED_STRING_FORM = QE_L("QL(a(V2(0.25,-1.9999999949504854e-006)),b(V2(40000,0)),c(V2(3,2)),d(V2(1,-0)))");
#endif

	// Execution
    QQuadrilateral quadrilateralUT = QUAD;
    string_q strStringForm = quadrilateralUT.ToString();

    // Verification
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// [TODO] Thund: Protected methods have not been tested yet, they were postponed

// End - Test Suite: QQuadrilateral
QTEST_SUITE_END()
