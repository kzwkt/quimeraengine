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

#include "QBaseTriangle.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector2, QVector3, QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QBaseTriangle_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// Execution
    QBaseTriangle<T> triangleUT;

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle's points properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QBaseTriangle<T> EXPECTED_TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// Execution
    QBaseTriangle<T> triangleUT(EXPECTED_TRIANGLE);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// Execution
    QBaseTriangle<T> triangleUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// Execution
    QBaseTriangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if an assertion fails when the input parameters are null pointers.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_AssertionFailsWhenInputValuesAreNull_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    float_q* NULL_POINTER = null_q;

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED_WHEN_A_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_B_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_C_IS_NULL = true;

	// Execution
    bool bAssertionFailedWhenAIsNull = false;

    try
    {
        QBaseTriangle<T> triangleUT(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        QBaseTriangle<T> triangleUT(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        QBaseTriangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenCIsNull = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailedWhenAIsNull, ASSERTION_FAILED_WHEN_A_IS_NULL);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBIsNull, ASSERTION_FAILED_WHEN_B_IS_NULL);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCIsNull, ASSERTION_FAILED_WHEN_C_IS_NULL);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;
    using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    vf32_q INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C;

    SQVF32::Pack(VECTOR_COMPONENTS_A[0], VECTOR_COMPONENTS_A[1], VECTOR_COMPONENTS_A[2], VECTOR_COMPONENTS_A[3], INPUT_FVECTOR_A);
    SQVF32::Pack(VECTOR_COMPONENTS_B[0], VECTOR_COMPONENTS_B[1], VECTOR_COMPONENTS_B[2], VECTOR_COMPONENTS_B[3], INPUT_FVECTOR_B);
    SQVF32::Pack(VECTOR_COMPONENTS_C[0], VECTOR_COMPONENTS_C[1], VECTOR_COMPONENTS_C[2], VECTOR_COMPONENTS_C[3], INPUT_FVECTOR_C);

	// Execution
    QBaseTriangle<T> triangleUT(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND = QBaseTriangle<T>( T::GetZeroVector(), T::GetZeroVector(), T::GetZeroVector() );
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T::GetZeroVector(), T::GetZeroVector(), T::GetZeroVector() );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5));
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T::GetZeroVector(), T::GetZeroVector(), T::GetZeroVector() );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T::GetZeroVector(), T::GetZeroVector(), T::GetZeroVector() );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND =  QBaseTriangle<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T::GetZeroVector(), T::GetZeroVector(), T::GetZeroVector() );

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // Preparation
    const QBaseTriangle<T> LEFT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseTriangle<T> RIGHT_OPERAND = QBaseTriangle<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseTriangle
QTEST_SUITE_END()
