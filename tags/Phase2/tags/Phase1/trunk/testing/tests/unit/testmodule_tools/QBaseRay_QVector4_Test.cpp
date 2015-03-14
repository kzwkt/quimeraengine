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
// IMPORTANT NOTE: Whatever the test you modify in this file, replicate the same changes in the QBaseRay_Test.cpp file!
//                 They had to be split because the template has 2 parameters that are not assured to be the same type.
// !!!

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QBaseRay.h"
#include "QVector4.h"
#include "QVector3.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseRay;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;

QTEST_SUITE_BEGIN( QBaseRay_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const QVector4 EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    QBaseRay<QVector4, QVector3> rayUT;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const QVector4 EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    QBaseRay<QVector4, QVector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    QBaseRay<QVector4, QVector3> rayUT(EXPECTED_RAY);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreSetProperly_Test )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const QVector4 EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    QBaseRay<QVector4, QVector3> rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
QTEST_CASE ( Constructor3_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const QVector4 INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const QVector3 INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const QVector4 UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const QVector3 UNEXPECTED_VALUE_FOR_DIRECTION = INPUT_VALUE_FOR_DIRECTION.Normalize();

	// [Execution]
    QBaseRay<QVector4, QVector3> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::_0), QVector3(SQFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), QVector3(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5));
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::_0), QVector3(SQFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), QVector3(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::_0), QVector3(SQFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
QTEST_CASE ( OperatorEquality_FalseWhenOperandsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) * SQFloat::_3 ); // LEFT_OPERAND's direction x3

	// [Execution] / Verification
    BOOST_CHECK( !(LEFT_OPERAND == RIGHT_OPERAND) );
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND =  QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), QVector3(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), QVector3(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::_0), QVector3(SQFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
QTEST_CASE ( OperatorInequality_TrueWhenOperandsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const QBaseRay<QVector4, QVector3> LEFT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon) );
    const QBaseRay<QVector4, QVector3> RIGHT_OPERAND = QBaseRay<QVector4, QVector3>( QVector4(SQFloat::Epsilon), QVector3(SQFloat::Epsilon * SQFloat::_3) ); // LEFT_OPERAND's direction x3

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

// End - Test Suite: QBaseRay
QTEST_SUITE_END()
