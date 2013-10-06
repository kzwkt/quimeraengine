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

#include "QBaseQuadrilateral.h"

#include "QVector2.h"
#include "SQFloat.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseQuadrilateral;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;

QTEST_SUITE_BEGIN( QBaseQuadrilateral_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;
    
    // [Execution]
    QBaseQuadrilateral quadrilateralUT;
    
    // [Verification]
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
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_6, SQFloat::_7);
    
    const QBaseQuadrilateral QUAD_TO_COPY = QBaseQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                               EXPECTED_VALUE_FOR_B,
                                                               EXPECTED_VALUE_FOR_C, 
                                                               EXPECTED_VALUE_FOR_D);

    // [Execution]
    QBaseQuadrilateral quadrilateralUT = QUAD_TO_COPY;
    
    // [Verification]
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
QTEST_CASE ( Constructor3_ValuesAreCorrectlySet_Test )
{
	// [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_D = QVector2(SQFloat::_6, SQFloat::_7);
    
    // [Execution]
    QBaseQuadrilateral quadrilateralUT = QBaseQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                            EXPECTED_VALUE_FOR_B,
                                                            EXPECTED_VALUE_FOR_C,
                                                            EXPECTED_VALUE_FOR_D);

    // [Verification]
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
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon), 
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon), 
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0), 
                                                                QVector2(SQFloat::_0, SQFloat::_0), 
                                                                QVector2(SQFloat::_0, SQFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5), 
                                                               QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5), 
                                                               QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5), 
                                                               QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0), 
                                                                QVector2(SQFloat::_0, SQFloat::_0), 
                                                                QVector2(SQFloat::_0, SQFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                               QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(!(LEFT_OPERAND == RIGHT_OPERAND));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                                QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                                QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                                QVector2(SQFloat::Epsilon, SQFloat::Epsilon));

    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon * SQFloat::_0_5));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5),
                                                               QVector2(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5,
                                                                        SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0),
                                                                QVector2(SQFloat::_0, SQFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const QBaseQuadrilateral LEFT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                               QVector2(SQFloat::Epsilon, SQFloat::Epsilon));

    const QBaseQuadrilateral RIGHT_OPERAND = QBaseQuadrilateral(QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                                QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                                QVector2(SQFloat::Epsilon, SQFloat::Epsilon),
                                                                QVector2(SQFloat::Epsilon, SQFloat::Epsilon));

    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseQuadrilateral
QTEST_SUITE_END()
