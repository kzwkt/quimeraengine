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
// IMPORTANT NOTE: Whatever the test you modify in this file, replicate the same changes in the QBaseRay_QVector4_Test.cpp file!
//                 They had to be split because the template has 2 parameters that are not assured to be the same type.
// !!!

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QBaseRay.h"
#include "QVector2.h"
#include "QVector3.h"

using Kinesis::QuimeraEngine::Tools::Math::QBaseRay;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;

typedef boost::mpl::list<QVector2, QVector3> TQTemplateTypes;


QTEST_SUITE_BEGIN( QBaseRay_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// Execution
    QBaseRay<T, T> rayUT;

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
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    QBaseRay<T, T> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// Execution
    QBaseRay<T, T> rayUT(EXPECTED_RAY);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// Execution
    QBaseRay<T, T> rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // Verification
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_ORIGIN[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3 };
    float_q VECTOR_COMPONENTS_DIRECTION[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6 };

    const T INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const T UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const T UNEXPECTED_VALUE_FOR_DIRECTION = INPUT_VALUE_FOR_DIRECTION.Normalize();

	// Execution
    QBaseRay<T, T> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // Verification
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::_0), T(SQFloat::_0) );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5));
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::_0), T(SQFloat::_0) );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::_0), T(SQFloat::_0) );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsAreSimilarButNotEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) * SQFloat::_3 ); // LEFT_OPERAND's direction x3

	// Execution / Verification
    BOOST_CHECK( !(LEFT_OPERAND == RIGHT_OPERAND) );
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND =  QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::_0), T(SQFloat::_0) );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsAreSimilarButNotEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseRay<T, T> LEFT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseRay<T, T> RIGHT_OPERAND = QBaseRay<T, T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon * SQFloat::_3) ); // LEFT_OPERAND's direction x3

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

// End - Test Suite: QBaseRay
QTEST_SUITE_END()
