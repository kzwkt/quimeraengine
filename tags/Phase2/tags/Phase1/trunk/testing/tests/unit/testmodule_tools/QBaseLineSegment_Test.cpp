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

#include "QBaseLineSegment.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseLineSegment;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector2, QVector3, QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QBaseLineSegment_TestSuite )

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
    QBaseLineSegment<T> lineSegmentUT;

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

    const QBaseLineSegment<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    QBaseLineSegment<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// [Execution]
    QBaseLineSegment<T> lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND = QBaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5));
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND =  QBaseLineSegment<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseLineSegment<T> LEFT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseLineSegment<T> RIGHT_OPERAND = QBaseLineSegment<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseLineSegment
QTEST_SUITE_END()
