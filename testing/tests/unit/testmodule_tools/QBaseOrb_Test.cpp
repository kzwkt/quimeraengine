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

#include "QBaseOrb.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"

using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector2, QVector3, QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QBaseOrb_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// Execution
    QBaseOrb<T> orbUT;

    // Verification
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets orb's point and radius properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

    const QBaseOrb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// Execution
    QBaseOrb<T> orbUT(EXPECTED_ORB);

    // Verification
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_5;

	// Execution
    QBaseOrb<T> orbUT(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

    // Verification
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND = QBaseOrb<T>( T::GetZeroVector(), SQFloat::_0 );
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T::GetZeroVector(), SQFloat::_0 );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5);
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T::GetZeroVector(), SQFloat::_0 );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5);
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T::GetZeroVector(), SQFloat::_0 );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon), SQFloat::Epsilon );
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon), SQFloat::Epsilon );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND =  QBaseOrb<T>( T(SQFloat::Epsilon), SQFloat::Epsilon );
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon), SQFloat::Epsilon );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5);
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon), SQFloat::Epsilon );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5 );
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T::GetZeroVector(), SQFloat::_0 );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseOrb<T> LEFT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon), SQFloat::Epsilon );
    const QBaseOrb<T> RIGHT_OPERAND = QBaseOrb<T>( T(SQFloat::Epsilon), SQFloat::Epsilon );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseOrb
QTEST_SUITE_END()
