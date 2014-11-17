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

#include "QTriangle3D.h"

#include "QVector3.h"
#include "QVector4.h"
#include "SQAngle.h"
#include "QMatrix4x3.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTranslationMatrix.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QTriangle3D;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector3, QVector4> TQTemplateTypes;

QTEST_SUITE_BEGIN( QTriangle3D_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

	const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> triangleUT;

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle's points properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QTriangle3D<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    QTriangle3D<T> triangleUT(EXPECTED_TRIANGLE);

    // [Verification]
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

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QBaseTriangle<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    QTriangle3D<T> triangleUT(EXPECTED_TRIANGLE);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> triangleUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    // [Verification]
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
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    float_q* NULL_POINTER = null_q;

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED_WHEN_A_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_B_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_C_IS_NULL = true;

	// [Execution]
    bool bAssertionFailedWhenAIsNull = false;

    try
    {
        QTriangle3D<T> triangleUT(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        QTriangle3D<T> triangleUT(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        QTriangle3D<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenCIsNull = true;
    }

    // [Verification]
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
    using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;
    using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    vf32_q INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C;

    SQVF32::Pack(VECTOR_COMPONENTS_A[0], VECTOR_COMPONENTS_A[1], VECTOR_COMPONENTS_A[2], VECTOR_COMPONENTS_A[3], INPUT_FVECTOR_A);
    SQVF32::Pack(VECTOR_COMPONENTS_B[0], VECTOR_COMPONENTS_B[1], VECTOR_COMPONENTS_B[2], VECTOR_COMPONENTS_B[3], INPUT_FVECTOR_B);
    SQVF32::Pack(VECTOR_COMPONENTS_C[0], VECTOR_COMPONENTS_C[1], VECTOR_COMPONENTS_C[2], VECTOR_COMPONENTS_C[3], INPUT_FVECTOR_C);

	// [Execution]
    QTriangle3D<T> triangleUT(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);

    // [Verification]
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

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QBaseTriangle<T> OTHER_TRIANGLE = QBaseTriangle<T>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    QTriangle3D<T> triangleUT;
    triangleUT = OTHER_TRIANGLE;

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the normal of a common triangle is correctly calculated.
/// </summary>
QTEST_CASE_TEMPLATE ( GetNormal_ReturnsExpectedNormalFromCommonTriangle_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_3, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_9 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    const QVector3 EXPECTED_NORMAL = QVector3(-0.30151135f, 0.30151135f, 0.90453398f);
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    const QVector3 EXPECTED_NORMAL = QVector3((float_q)-0.30151134457776363, (float_q)0.30151134457776363, (float_q)0.90453403373329089);
#endif

	// [Execution]
    QVector3 vNormal = TRIANGLE.GetNormal();

    // [Verification]
    BOOST_CHECK(vNormal.x == EXPECTED_NORMAL.x);
    BOOST_CHECK(vNormal.y == EXPECTED_NORMAL.y);
    BOOST_CHECK(vNormal.z == EXPECTED_NORMAL.z);
}

/// <summary>
/// Checks that the result depends on the order of the points that compound the triangle, following left-handed rules.
/// </summary>
QTEST_CASE_TEMPLATE ( GetNormal_FollowsLeftHandedRules_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_0, SQFloat::_1, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_0, SQFloat::_2, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_0, SQFloat::_1, SQFloat::_9 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

	// [Execution]
    QVector3 vNormal = TRIANGLE.GetNormal();

    // [Verification]
    BOOST_CHECK(SQFloat::IsGreaterOrEquals(vNormal.y, SQFloat::_0));
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when, at least, two of the vertices of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetNormal_AssertionFailsWhenTwoVerticesCoincide_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const bool ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE = true;

    const QTriangle3D<T> TRIANGLE_A_AND_B(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);
    const QTriangle3D<T> TRIANGLE_B_AND_C(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_B);
    const QTriangle3D<T> TRIANGLE_C_AND_A(VECTOR_COMPONENTS_C, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    bool bAssertionFailedWhenABCoincide = false;

    try
    {
        TRIANGLE_A_AND_B.GetNormal();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenABCoincide = true;
    }

    bool bAssertionFailedWhenBCCoincide = false;

    try
    {
        TRIANGLE_B_AND_C.GetNormal();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenBCCoincide = true;
    }

    bool bAssertionFailedWhenCACoincide = false;

    try
    {
        TRIANGLE_C_AND_A.GetNormal();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenCACoincide = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenABCoincide, ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBCCoincide, ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCACoincide, ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE);
}

/// <summary>
/// Checks that an assertion fails when the vertices of the triangle are aligned.
/// </summary>
QTEST_CASE_TEMPLATE ( GetNormal_AssertionFailsWhenVerticesAreAligned_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10 };

    const QTriangle3D<T> TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.GetNormal();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the normal is normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( GetNormal_ResultIsNormalized_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_2, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_3, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_9 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

	// [Execution]
    QVector3 vNormal = TRIANGLE.GetNormal();

    // [Verification]
    BOOST_CHECK(vNormal == vNormal.Normalize());
}

/// <summary>
/// Checks that the circumcenter of a common triangle is correctly calculated.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCircumcenter_ReturnsExpectedResultFromCommonTriangle_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    const float_q CIRCUMCENTER_COMPONENTS[] = { (float_q)2.214285714285714, (float_q)1.9285714285714288, (float_q)3.6428571428571428, SQFloat::_1 };
    const T EXPECTED_CIRCUMCENTER = T(CIRCUMCENTER_COMPONENTS);

	// [Execution]
    T vCircumcenter = TRIANGLE.GetCircumcenter();

    // [Verification]
    BOOST_CHECK(vCircumcenter == EXPECTED_CIRCUMCENTER);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when, at least, two of the vertices of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCircumcenter_AssertionFailsWhenTwoVerticesCoincide_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const bool ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE = true;

    const QTriangle3D<T> TRIANGLE_A_AND_B(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);
    const QTriangle3D<T> TRIANGLE_B_AND_C(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_B);
    const QTriangle3D<T> TRIANGLE_C_AND_A(VECTOR_COMPONENTS_C, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    bool bAssertionFailedWhenABCoincide = false;

    try
    {
        TRIANGLE_A_AND_B.GetCircumcenter();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenABCoincide = true;
    }

    bool bAssertionFailedWhenBCCoincide = false;

    try
    {
        TRIANGLE_B_AND_C.GetCircumcenter();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenBCCoincide = true;
    }

    bool bAssertionFailedWhenCACoincide = false;

    try
    {
        TRIANGLE_C_AND_A.GetCircumcenter();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenCACoincide = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenABCoincide, ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBCCoincide, ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCACoincide, ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE);
}

/// <summary>
/// Checks that an assertion fails when the vertices of the triangle are aligned.
/// </summary>
QTEST_CASE_TEMPLATE ( GetCircumcenter_AssertionFailsWhenVerticesAreAligned_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10 };

    const QTriangle3D<T> TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.GetCircumcenter();
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that W component of the output point depends on the value of the W component of the vertices of the triangle.
/// </summary>
QTEST_CASE ( GetCircumcenter_OutputWComponentDependsOnInputVertices_Test)
{
    // [Preparation]
    const QVector4 VALUE_FOR_A(SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1);
    const QVector4 VALUE_FOR_B(SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1);
    const QVector4 VALUE_FOR_C(SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1);

    const QTriangle3D<QVector4> TRIANGLE1 = QTriangle3D<QVector4>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    QTriangle3D<QVector4> TRIANGLE2 = TRIANGLE1;
    TRIANGLE2.A.w = SQFloat::_2;
    TRIANGLE2.B.w = SQFloat::_3;
    TRIANGLE2.C.w = SQFloat::_4;

	// [Execution]
    QVector4 vCircumcenter1 = TRIANGLE1.GetCircumcenter();
    QVector4 vCircumcenter2 = TRIANGLE2.GetCircumcenter();

    // [Verification]
    BOOST_CHECK( SQFloat::AreNotEqual(vCircumcenter1.w, vCircumcenter2.w) );
}

/// <summary>
/// Checks that a common triangle is correctly translated using common translation vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const QVector3 TRANSLATION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_TriangleIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QVector3 TRANSLATION = QVector3::GetNullVector();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly translated using common translation values.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_q TRANSLATION_X = SQFloat::_1;
    const float_q TRANSLATION_Y = SQFloat::_2;
    const float_q TRANSLATION_Z = SQFloat::_3;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_TriangleIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const float_q TRANSLATION_X = SQFloat::_0;
    const float_q TRANSLATION_Y = SQFloat::_0;
    const float_q TRANSLATION_Z = SQFloat::_0;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Template method used by Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_5, SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly translated using common translation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetNullMatrix();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_TriangleIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QQuaternion ROTATION = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)-3.5355339059327378, (float_q)-2.1213203435596419, (float_q)-2.0000000000000009, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)-4.9497474683058327, (float_q)-0.7071067811865468, (float_q)-1.0000000000000007, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)-3.5355339059327373, (float_q)-0.70710678118654668, (float_q)-3.0000000000000004, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_TriangleIsNotRotatedWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_TriangleIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { 0.70710659f, -SQFloat::_4, -2.1213202f, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { -1.4142138f, -SQFloat::_4, -2.8284268f, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { 0.70710647f, -SQFloat::_3, -3.5355337f, SQFloat::_1 };
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)0.70710678118654768, -SQFloat::_4, (float_q)-2.1213203435596428, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)-1.4142135623730949, -SQFloat::_4, (float_q)-2.8284271247461907, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)0.70710678118654791, -SQFloat::_3, (float_q)-3.5355339059327378, SQFloat::_1 };
#endif

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_TriangleIsNotRotatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_TriangleIsCorrectlyTransformedByCommonQuaternions_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QQuaternion ROTATION = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)0.29289321881345243, (float_q)1.2928932188134525, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)-1.1213203435596424, (float_q)2.7071067811865479, SQFloat::_4, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)0.29289321881345276, (float_q)2.7071067811865479, SQFloat::_2, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_TriangleIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    
    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_CommonTriangleIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_8, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_6, SQFloat::_9, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the components of the scaling vector equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_TriangleIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    const QVector3 SCALE = QVector3::GetNullVector();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling values.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_CommonTriangleIsCorrectlyScaledWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_8, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_6, SQFloat::_9, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the values equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_TriangleIsNotScaledWhenValuesEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the values equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenValuesEqualZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_CommonTriangleIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_4, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_8, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_6, SQFloat::_9, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_TriangleIsNotScaledWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetIdentity();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    
    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonTriangleIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_6, SQFloat::_0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_4, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the components of the scaling vector equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_TriangleIsNotTranslatedWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToPivotPositionWhenVectorIsNull_Test, TQTemplateTypes )
{
    // [Preparation]
    const QVector3 SCALE = QVector3::GetNullVector();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling values.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonTriangleIsCorrectlyScaledWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_6, SQFloat::_0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_4, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the values equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_TriangleIsNotScaledWhenValuesEqualOne_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the values equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedPivotPositionWhenValuesEqualZero_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Template method used by Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)6.0658639918226491, SQFloat::_8, (float_q)-10.419417382415922, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)3.5909902576697323, SQFloat::_8, (float_q)-8.6516504294495533, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)8.0104076400856545, SQFloat::_7, (float_q)-12.717514421272202, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the coordinate origin when transformation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_TriangleIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)-1.1213203435596424, SQFloat::_1, (float_q)2.2928932188134521, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_1, SQFloat::_2, (float_q)1.5857864376269051, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the rotation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_TriangleIsNotRotateWithPivotdWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3::GetIdentity();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the rotation matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    
    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonTriangleIsCorrectlyScaledWhenUsingCommonMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_6, SQFloat::_0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_4, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_TriangleIsNotTranslatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetIdentity();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetNullMatrix();
    
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_0 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_0 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Template method used by TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_3, SQFloat::_7, -SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)0.52512626584708322, SQFloat::_7, (float_q)-1.2322330470336311, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)4.9445436482630054, SQFloat::_6, (float_q)-5.2980970388562802, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the position of the pivot point when transformation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_IsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    QSpaceConversionMatrix CONVERSION = QSpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    const float_q POINT_COMPONENTS_A[] = {-SQFloat::_0_5,  SQFloat::_0_5,  SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_B[] = {-SQFloat::_0_5,  SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_C[] = { SQFloat::_0_5,  SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const T POINT_A(POINT_COMPONENTS_A);
    const T POINT_B(POINT_COMPONENTS_B);
    const T POINT_C(POINT_COMPONENTS_C);
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(POINT_A, POINT_B, POINT_C);
    
    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)0.22360679774997894, (float_q)0.81989159174992277, (float_q)3.1666666666666665, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)-0.22360679774997902, (float_q)1.4161763857498666, (float_q)3.833333333333333, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)-1.1180339887498949, (float_q)1.1180339887498947, (float_q)3.5, SQFloat::_1 };
    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const QTriangle3D<T> EXPECTED_TRIANGLE = QTriangle3D<T>(EXPECTED_VALUE_FOR_A,
                                                            EXPECTED_VALUE_FOR_B,
                                                            EXPECTED_VALUE_FOR_C);

	// [Execution]
    QTriangle3D<T> triangle = TRIANGLE.Transform(CONVERSION);
    	
    // [Verification]
    BOOST_CHECK(triangle == EXPECTED_TRIANGLE);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_LineSegmentDoesNotChangeWhenTransformedByIdentityMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QSpaceConversionMatrix IDENTITY_MATRIX = QSpaceConversionMatrix::GetIdentity();

    const float_q POINT_COMPONENTS_A[] = {-SQFloat::_0_5,  SQFloat::_0_5,  SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_B[] = {-SQFloat::_0_5,  SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_C[] = { SQFloat::_0_5,  SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const T POINT_A(POINT_COMPONENTS_A);
    const T POINT_B(POINT_COMPONENTS_B);
    const T POINT_C(POINT_COMPONENTS_C);
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(POINT_A, POINT_B, POINT_C);

    const QTriangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;

	// [Execution]
    QTriangle3D<T> triangle = TRIANGLE.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(triangle == EXPECTED_TRIANGLE);
}

/// <summary>
/// Checks that the line segment is nullified when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform2_EndpointsAreNullifiedWhenMatrixIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QSpaceConversionMatrix NULL_MATRIX = QMatrix4x4::GetNullMatrix();

    const float_q POINT_COMPONENTS_A[] = {-SQFloat::_0_5,  SQFloat::_0_5,  SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_B[] = {-SQFloat::_0_5,  SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_C[] = { SQFloat::_0_5,  SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const T POINT_A(POINT_COMPONENTS_A);
    const T POINT_B(POINT_COMPONENTS_B);
    const T POINT_C(POINT_COMPONENTS_C);
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(POINT_A, POINT_B, POINT_C);

    const QTriangle3D<T> EXPECTED_TRIANGLE = QTriangle3D<T>(T::GetNullVector(), T::GetNullVector(), T::GetNullVector());

	// [Execution]
    QTriangle3D<T> triangle = TRIANGLE.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(triangle == EXPECTED_TRIANGLE);
}

/// <summary>
/// Checks that it returns "negative side" when the triangle is "behind" the plane and doesn't intersect with it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheTriangleIsBehindPlaneAndTheyDoNotIntersect_Test, TQTemplateTypes )
{
    //     A        |
    //    / \       |
    //   /   \      |-->
    //  C-----B     |
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, -SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// [Execution]
    EQSpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the triangle is "in front" the plane and doesn't intersect with it.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheTriangleIsInFrontPlaneAndTheyDoNotIntersect_Test, TQTemplateTypes )
{
    //    |         A
    //    |        / \
    //    |-->    /   \
    //    |      C-----B
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// [Execution]
    EQSpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the triangle intersects with the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheTriangleIntersectsWithThePlane_Test, TQTemplateTypes )
{
    //     |  A
    //     | / \
    //     |/   \
    //     |-->  \
    //    /|      \
    //   C-|-------B

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, -SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_BothSides;

	// [Execution]
    EQSpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when the triangle belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsContainedWhenTheTriangleBelongsToPlane_Test, TQTemplateTypes )
{
    //       |
    //       A
    //       |
    //       B-->
    //       C
    //       |
    //

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, -SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    TRIANGLE = TRIANGLE.ProjectToPlane(PLANE);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_Contained;

	// [Execution]
    EQSpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the triangle is "behind" the plane and one vertex belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheTriangleIsBehindPlaneAndOneVertexBelongsToPlane_Test, TQTemplateTypes )
{
    //     A  |
    //    / \ |
    //   /   \|-->
    //  C-----B
    //        |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// [Execution]
    EQSpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the triangle is "in front" of the plane and one vertex belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheTriangleIsInFrontPlaneAndOneVertexBelongsToPlane_Test, TQTemplateTypes )
{
    //    |  A
    //    | / \
    //    |/-->\
    //    C-----B
    //    |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// [Execution]
    EQSpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is not different when the plane is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_ResultIsNotDifferentWhenPlaneIsNotNormalized_Test, TQTemplateTypes )
{
    //     A  |
    //    / \ |
    //   /   \|-->
    //  C-----B
    //        |

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane NONNORMALIZED_PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10);
    const QPlane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    EQSpaceRelation eResultNonNotmalized = TRIANGLE.SpaceRelation(NONNORMALIZED_PLANE);
    EQSpaceRelation eResultNormalized = TRIANGLE.SpaceRelation(NORMALIZED_PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(eResultNonNotmalized, eResultNormalized);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE( SpaceRelation_AssertionFailsWhenPlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const QBasePlane NULL_PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.SpaceRelation(NULL_PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns the expected extruded triangle when the input value is positive.
/// </summary>
QTEST_CASE_TEMPLATE( Extrude_ReturnsWhatExpectedWhenInputValueIsPositive_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q INPUT_VALUE = SQFloat::_3;
    const QVector3 DISPLACEMENT = TRIANGLE.GetNormal() * INPUT_VALUE;
    QTriangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;
    EXPECTED_TRIANGLE.A += DISPLACEMENT;
    EXPECTED_TRIANGLE.B += DISPLACEMENT;
    EXPECTED_TRIANGLE.C += DISPLACEMENT;
    
	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Extrude(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that it returns the expected extruded triangle when the input value is negative.
/// </summary>
QTEST_CASE_TEMPLATE( Extrude_ReturnsWhatExpectedWhenInputValueIsNegative_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q INPUT_VALUE = -SQFloat::_3;
    const QVector3 DISPLACEMENT = TRIANGLE.GetNormal() * INPUT_VALUE;
    QTriangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;
    EXPECTED_TRIANGLE.A += DISPLACEMENT;
    EXPECTED_TRIANGLE.B += DISPLACEMENT;
    EXPECTED_TRIANGLE.C += DISPLACEMENT;
    
	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Extrude(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that it returns the expected extruded triangle when the input value is negative.
/// </summary>
QTEST_CASE_TEMPLATE( Extrude_TriangleDoesNotChangeWhenInputValueIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q INPUT_VALUE = SQFloat::_0;
    const QTriangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;
    
	// [Execution]
    QTriangle3D<T> returnedTriangle = TRIANGLE.Extrude(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_TRIANGLE.C);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when, at least, two of the vertices of the triangle coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Extrude_AssertionFailsWhenTwoVerticesCoincide_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0_5, SQFloat::_0, SQFloat::_9, SQFloat::_10 };

    const bool ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE = true;

    const QTriangle3D<T> TRIANGLE_A_AND_B(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);
    const QTriangle3D<T> TRIANGLE_B_AND_C(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_B);
    const QTriangle3D<T> TRIANGLE_C_AND_A(VECTOR_COMPONENTS_C, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q INPUT_VALUE = -SQFloat::_3;

	// [Execution]
    bool bAssertionFailedWhenABCoincide = false;

    try
    {
        TRIANGLE_A_AND_B.Extrude(INPUT_VALUE);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenABCoincide = true;
    }

    bool bAssertionFailedWhenBCCoincide = false;

    try
    {
        TRIANGLE_B_AND_C.Extrude(INPUT_VALUE);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenBCCoincide = true;
    }

    bool bAssertionFailedWhenCACoincide = false;

    try
    {
        TRIANGLE_C_AND_A.Extrude(INPUT_VALUE);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailedWhenCACoincide = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenABCoincide, ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBCCoincide, ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCACoincide, ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE);
}

/// <summary>
/// Checks that an assertion fails when the vertices of the triangle are aligned.
/// </summary>
QTEST_CASE_TEMPLATE ( Extrude_AssertionFailsWhenVerticesAreAligned_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_7, SQFloat::_8, SQFloat::_9, SQFloat::_10 };

    const QTriangle3D<T> TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);

    const float_q INPUT_VALUE = -SQFloat::_3;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.Extrude(INPUT_VALUE);
    }
    catch(...) // [TODO] Thund: A concrete type of exception will be caught in the future
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the correct orthocenter is calculated.
/// </summary>
QTEST_CASE_TEMPLATE ( GetOrthocenter_OrthocenterIsCorrectlyCalculatedWhenUsingCommonTriangle_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { -SQFloat::_2, SQFloat::_3, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_4, SQFloat::_6, SQFloat::_1 };

    const T POINT_A = T(VECTOR_COMPONENTS_A);
    const T POINT_B = T(VECTOR_COMPONENTS_B);
    const T POINT_C = T(VECTOR_COMPONENTS_C);

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(POINT_A, POINT_B, POINT_C);

    const float_q EXPECTED_VALUE_COMPONENTES[] = { SQFloat::_3, -SQFloat::_2, SQFloat::_6, SQFloat::_1 };
    const T EXPECTED_VALUE_ORTHOCENTER = T(EXPECTED_VALUE_COMPONENTES);

	// [Execution]
    T orthocenter = TRIANGLE.GetOrthocenter();
    
    // [Verification]
    BOOST_CHECK(orthocenter == EXPECTED_VALUE_ORTHOCENTER);
}

/// <summary>
/// Checks that the W component of the vertices affects the result.
/// </summary>
QTEST_CASE ( GetOrthocenter_WComponentAffectsResult_Test )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_6, SQFloat::_7 };
    const float_q VECTOR_COMPONENTS_B[] = { -SQFloat::_2, SQFloat::_3, SQFloat::_6, SQFloat::_8 };
    const float_q VECTOR_COMPONENTS_C1[] = { SQFloat::_3, SQFloat::_4, SQFloat::_6, SQFloat::_10 };
    const float_q VECTOR_COMPONENTS_C2[] = { SQFloat::_3, SQFloat::_4, SQFloat::_6, SQFloat::_3 };

    const QVector4 POINT_A = QVector4(VECTOR_COMPONENTS_A);
    const QVector4 POINT_B = QVector4(VECTOR_COMPONENTS_B);
    const QVector4 POINT_C1 = QVector4(VECTOR_COMPONENTS_C1);
    const QVector4 POINT_C2 = QVector4(VECTOR_COMPONENTS_C2);

    const QTriangle3D<QVector4> TRIANGLE1 = QTriangle3D<QVector4>(POINT_A, POINT_B, POINT_C1);
    const QTriangle3D<QVector4> TRIANGLE2 = QTriangle3D<QVector4>(POINT_A, POINT_B, POINT_C2);
    
    // [Execution]
    QVector4 orthocenter1 = TRIANGLE1.GetOrthocenter();
    QVector4 orthocenter2 = TRIANGLE2.GetOrthocenter();
    
    // [Verification]
    BOOST_CHECK( SQFloat::AreNotEqual(orthocenter1.w, orthocenter2.w) );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetOrthocenter_AssertionFailsWhenAllPointsCoincide_Test, TQTemplateTypes )
{
    // [Preparation]
    const float_q VECTOR_COMPONENTS[] = { SQFloat::_2, SQFloat::_3, SQFloat::_6, SQFloat::_7 };
    const T POINT = T(VECTOR_COMPONENTS);

    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(POINT, POINT, POINT);
    
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        TRIANGLE.GetOrthocenter();
    }
    catch(...) // [TODO] Thund: Use a concrete exception when implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the triangle is correctly projected to the plane when it is in its negative side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_TriangleIsProjectedWhenItIsInNegativeSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_5, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, -SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_COMPONENTS_A[] = { (float_q)1.8095238095238098, (float_q)-3.3809523809523805, (float_q)6.238095238095239, SQFloat::_1 };
    const float_q EXPECTED_COMPONENTS_B[] = { (float_q)2.0952380952380958, (float_q)-1.8095238095238084, (float_q)5.3809523809523832, SQFloat::_1 };
#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    const float_q EXPECTED_COMPONENTS_C[] = { -0.66666698f, -0.333334f, 5.3333321f, SQFloat::_1 };
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    const float_q EXPECTED_COMPONENTS_C[] = { (float_q)-0.66666666666666652, (float_q)-0.33333333333333304, (float_q)5.3333333333333339, SQFloat::_1 };
#endif
    const QTriangle3D<T> EXPECTED_TRIANGLE = QTriangle3D<T>(EXPECTED_COMPONENTS_A, EXPECTED_COMPONENTS_B, EXPECTED_COMPONENTS_C);

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10).Normalize();

	// [Execution]
    QTriangle3D<T> projectedTriangle = TRIANGLE.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedTriangle.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(projectedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(projectedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that the triangle is correctly projected to the plane when it is in its positive side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_TriangleIsProjectedWhenItIsInPositiveSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_COMPONENTS_A[] = { (float_q)-0.28571428571428581, (float_q)-5.5714285714285712, (float_q)-2.1428571428571432, SQFloat::_1 };
    const float_q EXPECTED_COMPONENTS_B[] = { (float_q)-0.95238095238095255, (float_q)4.0952380952380949, (float_q)-6.8095238095238102, SQFloat::_1 };
    const float_q EXPECTED_COMPONENTS_C[] = { (float_q)-3.5238095238095237, (float_q)3.9523809523809521, (float_q)-6.0952380952380958, SQFloat::_1 };
    const QTriangle3D<T> EXPECTED_TRIANGLE = QTriangle3D<T>(EXPECTED_COMPONENTS_A, EXPECTED_COMPONENTS_B, EXPECTED_COMPONENTS_C);

    const QPlane PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, SQFloat::_10).Normalize();

	// [Execution]
    QTriangle3D<T> projectedTriangle = TRIANGLE.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedTriangle.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(projectedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(projectedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that the triangle is correctly projected to the plane when it intersects with the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_TriangleIsProjectedWhenItIntersectsWithPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, -SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, -SQFloat::_6, -SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_3, -SQFloat::_5, -SQFloat::_4, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_q EXPECTED_COMPONENTS_A[] = { SQFloat::_0, -SQFloat::_5, SQFloat::_0, SQFloat::_1 };
    const float_q EXPECTED_COMPONENTS_B[] = { (float_q)0.78571428571428581, (float_q)-4.4285714285714288, (float_q)-0.64285714285714235, SQFloat::_1 };
#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    const float_q EXPECTED_COMPONENTS_C[] = { -1.9285716f, -2.8571432f, -0.78571475f, SQFloat::_1 };
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    const float_q EXPECTED_COMPONENTS_C[] = { (float_q)-1.9285714285714284, (float_q)-2.8571428571428568, (float_q)-0.78571428571428514, SQFloat::_1 };
#endif
    const QTriangle3D<T> EXPECTED_TRIANGLE = QTriangle3D<T>(EXPECTED_COMPONENTS_A, EXPECTED_COMPONENTS_B, EXPECTED_COMPONENTS_C);

    const QPlane PLANE = QPlane(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10).Normalize();

	// [Execution]
    QTriangle3D<T> projectedTriangle = TRIANGLE.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //EQSpaceRelation eResult = projectedTriangle.SpaceRelation(PLANE);
    //BOOST_CHECK_EQUAL(eResult, EQSpaceRelation::E_Contained);
    BOOST_CHECK(projectedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(projectedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(projectedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that the result is different when the plane is not normalized.
/// </summary>
QTEST_CASE_TEMPLATE( ProjectToPlane_ResultIsDifferentWhenPlaneIsNotNormalized_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;

    // [Preparation]
    const QPlane NONNORMALIZED_PLANE = QPlane(SQFloat::_0_5, SQFloat::_1, SQFloat::_2, -SQFloat::_10);
    const QPlane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    QTriangle3D<T> resultNonNotmalized = TRIANGLE.ProjectToPlane(NONNORMALIZED_PLANE);
    QTriangle3D<T> resultNormalized = TRIANGLE.ProjectToPlane(NORMALIZED_PLANE);

    // [Verification]
    BOOST_CHECK(resultNonNotmalized != resultNormalized);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE( ProjectToPlane_AssertionFailsWhenPlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // [Preparation]
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const QTriangle3D<T> TRIANGLE = QTriangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const QBasePlane NULL_PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.ProjectToPlane(NULL_PLANE);
    }
    catch(...) // [TODO] Thund: A concrete exception has to be defined for this
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// End - Test Suite: QTriangle3D
QTEST_SUITE_END()
