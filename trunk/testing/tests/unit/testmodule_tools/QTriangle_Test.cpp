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

#include "QTriangle.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "SQAngle.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QTriangle;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector2, QVector3, QVector4> TQTemplateTypes;

QTEST_SUITE_BEGIN( QTriangle_TestSuite )

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
    QTriangle<T> triangleUT;

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
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QTriangle<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// Execution
    QTriangle<T> triangleUT(EXPECTED_TRIANGLE);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle's points properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QBaseTriangle<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// Execution
    QTriangle<T> triangleUT(EXPECTED_TRIANGLE);

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
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// Execution
    QTriangle<T> triangleUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// Execution
    QTriangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if an assertion fails when the input parameters are null pointers.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_AssertionFailsWhenInputValuesAreNull_Test, TQTemplateTypes )
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
        QTriangle<T> triangleUT(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        QTriangle<T> triangleUT(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        QTriangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
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
QTEST_CASE_TEMPLATE ( Constructor6_ValuesAreSetProperly_Test, TQTemplateTypes )
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
    QTriangle<T> triangleUT(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly assigned to another triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_TriangleIsAssignedProperlyToAnother_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QBaseTriangle<T> OTHER_TRIANGLE = QBaseTriangle<T>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// Execution
    QTriangle<T> triangleUT;
    triangleUT = OTHER_TRIANGLE;

    // Verification
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the correct surface is calculated.
/// </summary>
QTEST_CASE_TEMPLATE ( GetSurface_SurfaceIsCorrectlyCalculatedWhenUsingCommonTriangle_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VALUE = (float_q)12.0;

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_q fSurface = triangleUT.GetSurface();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fSurface, EXPECTED_VALUE) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetSurface_AssertionFailsWhenAllPointsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetSurface();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected angle is returned when using a common triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( GetAngleA_CorrectAngleIsReturnedWhenUsingCommonTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_VALUE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_VALUE = SQAngle::_45;
#endif

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_q fAngle = triangleUT.GetAngleA();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fAngle, EXPECTED_VALUE) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetAngleA_AssertionFailsWhenAllPointsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetAngleA();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected angle is returned when using a common triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( GetAngleB_CorrectAngleIsReturnedWhenUsingCommonTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_VALUE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_VALUE = SQAngle::_45;
#endif

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_q fAngle = triangleUT.GetAngleB();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fAngle, EXPECTED_VALUE) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetAngleB_AssertionFailsWhenAllPointsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetAngleB();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected angle is returned when using a common triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( GetAngleC_CorrectAngleIsReturnedWhenUsingCommonTriangle_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EXPECTED_VALUE = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EXPECTED_VALUE = SQAngle::_45;
#endif

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_q fAngle = triangleUT.GetAngleC();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fAngle, EXPECTED_VALUE) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetAngleC_AssertionFailsWhenAllPointsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetAngleC();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected incenter is obtained for a common triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( GetIncenter_CorrectIncenterObtainedWhenUsingCommonTriangle_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    
    float_q VECTOR_COMPONENTS_EXPECTED[] = { (float_q)2.4142135623730954, (float_q)1.5857864376269049, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    T vIncenter = triangleUT.GetIncenter();

    // Verification
    BOOST_CHECK(vIncenter == EXPECTED_POINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetIncenter_AssertionFailsWhenAllPointsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetIncenter();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected centroid is obtained for a common triangle.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCentroid_CorrectCentroidObtainedWhenUsingCommonTriangle_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    
    float_q VECTOR_COMPONENTS_EXPECTED[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    T vCentroid = triangleUT.GetCentroid();

    // Verification
    BOOST_CHECK(vCentroid == EXPECTED_POINT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCentroid_AssertionFailsWhenAllPointsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// Execution
    const QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetCentroid();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_0, SQFloat::_0_5, SQFloat::_0_25 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    QTriangle<T> triangleUT = QTriangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    const string_q A_STRING = VALUE_FOR_A.ToString();
    const string_q B_STRING = VALUE_FOR_B.ToString();
    const string_q C_STRING = VALUE_FOR_C.ToString();
    const string_q EXPECTED_STRING = QE_L("T(a(") + A_STRING + QE_L("),b(") + B_STRING + QE_L("),c(") + C_STRING + QE_L("))");

	// Execution
    string_q strReturnedString = triangleUT.ToString();

    // Verification
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: QTriangle
QTEST_SUITE_END()
