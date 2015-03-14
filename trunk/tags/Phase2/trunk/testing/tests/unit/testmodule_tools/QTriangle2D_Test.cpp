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

#include "QTriangle2D.h"

#include "QTransformationMatrix3x3.h"
#include "SQAngle.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QTriangle2D;

QTEST_SUITE_BEGIN( QTriangle2D_TestSuite )

/// <summary>
/// Checks that default values haven't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2::GetNullVector();
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2::GetNullVector();
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2::GetNullVector();

	// [Execution]
    QTriangle2D triangleUT;
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_8);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_9, SQFloat::_6);

    const QTriangle2D TRIANGLE_TO_COPY = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    QTriangle2D triangleUT(TRIANGLE_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if base type constructor sets triangle components properly.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_5, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_4);

    const QBaseTriangle<QVector2> BASE_TRIANGLE_TO_COPY = QBaseTriangle<QVector2>(EXPECTED_VALUE_FOR_A,
                                                                                  EXPECTED_VALUE_FOR_B,
                                                                                  EXPECTED_VALUE_FOR_C);

	// [Execution]
    QTriangle2D triangleUT(BASE_TRIANGLE_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_5, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_8);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
QTEST_CASE ( Constructor5_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_5, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_8);

    const float_q VECTOR_COMPONENTS_A[] = { EXPECTED_VALUE_FOR_A.x, EXPECTED_VALUE_FOR_A.y};
    const float_q VECTOR_COMPONENTS_B[] = { EXPECTED_VALUE_FOR_B.x, EXPECTED_VALUE_FOR_B.y};
    const float_q VECTOR_COMPONENTS_C[] = { EXPECTED_VALUE_FOR_C.x, EXPECTED_VALUE_FOR_C.y};

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if an assertion fails when the input parameters are null pointers.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenInputValuesAreNull_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_5, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_8);

    float_q VECTOR_COMPONENTS_A[] = { EXPECTED_VALUE_FOR_A.x, EXPECTED_VALUE_FOR_A.y};
    float_q VECTOR_COMPONENTS_B[] = { EXPECTED_VALUE_FOR_B.x, EXPECTED_VALUE_FOR_B.y};
    float_q VECTOR_COMPONENTS_C[] = { EXPECTED_VALUE_FOR_C.x, EXPECTED_VALUE_FOR_C.y};

    float_q* NULL_POINTER = null_q;

    const bool ASSERTION_FAILED_WHEN_A_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_B_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_C_IS_NULL = true;

	// [Execution]
    bool bAssertionFailedWhenAIsNull = false;

    try
    {
        QTriangle2D triangleUT = QTriangle2D(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(...) 
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        QTriangle2D triangleUT = QTriangle2D(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(...) 
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        QTriangle2D triangleUT = QTriangle2D(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
    }
    catch(...) 
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
/// Checks that every value is set to correct component.
/// </summary>
QTEST_CASE ( Constructor6_ValuesAreCorrectlySet_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;
    using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;

    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_5, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_4, SQFloat::_8);

    vf32_q INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C;

    SQVF32::Pack(EXPECTED_VALUE_FOR_A.x, EXPECTED_VALUE_FOR_A.y, SQFloat::_0, SQFloat::_0, INPUT_FVECTOR_A);
    SQVF32::Pack(EXPECTED_VALUE_FOR_B.x, EXPECTED_VALUE_FOR_B.y, SQFloat::_0, SQFloat::_0, INPUT_FVECTOR_B);
    SQVF32::Pack(EXPECTED_VALUE_FOR_C.x, EXPECTED_VALUE_FOR_C.y, SQFloat::_0, SQFloat::_0, INPUT_FVECTOR_C);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly assigned to another triangle.
/// </summary>
QTEST_CASE ( OperatorAssignation_TriangleIsAssignedProperlyToAnother_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseTriangle;

    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_5, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_4);

    const QBaseTriangle<QVector2> OTHER_TRIANGLE = QBaseTriangle<QVector2>(EXPECTED_VALUE_FOR_A,
                                                                           EXPECTED_VALUE_FOR_B,
                                                                           EXPECTED_VALUE_FOR_C);

	// [Execution]
    QTriangle2D triangleUT;
    triangleUT = OTHER_TRIANGLE;
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly transformed.
/// </summary>
QTEST_CASE ( Transform_TriangleIsCorrectlyTransformed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 INIT_POS_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 INIT_POS_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 INIT_POS_C = QVector2(SQFloat::_2, SQFloat::_6);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);
   
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_7);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(INIT_POS_A, INIT_POS_B, INIT_POS_C);
    triangleUT = triangleUT.Transform(TRANSFORMATION_MATRIX);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform_TriangleDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_7);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Transform(TRANSFORMATION);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the coordinate origin.
/// </summary>
QTEST_CASE ( Transform_AllVerticesAreMovedToCoordinateOriginWhenTransfomedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2::GetNullVector();
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2::GetNullVector();
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2::GetNullVector();

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetNullMatrix();

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Transform(TRANSFORMATION);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly transformed with a pivot.
/// </summary>
QTEST_CASE ( TransformWithPivot_TriangleIsCorrectlyTransformedWithPivot_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // [Preparation]
    const QVector2 INIT_POS_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 INIT_POS_B = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 INIT_POS_C = QVector2(SQFloat::_2, SQFloat::_6);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);
   
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_2);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_3, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(INIT_POS_A, INIT_POS_B, INIT_POS_C);
    triangleUT = triangleUT.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle doesn't change when it's transformed by an identity matrix with a pivot point.
/// </summary>
QTEST_CASE ( TransformWithPivot_TriangleDoesntChangeWhenTransformedWithPivotByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_7);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_6);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the pivot point when transforming by a zero matrix.
/// </summary>
QTEST_CASE ( TransformWithPivot_AllVerticesAreMovedToPivotPointWhenTransformedByZeroMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    // [Preparation]
    const QVector2 VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_5);
    const QVector2 VALUE_FOR_B = QVector2(-SQFloat::_1, SQFloat::_9);
    const QVector2 VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_7);

    const QTransformationMatrix3x3 TRANSFORMATION = QMatrix3x3::GetNullMatrix();

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_3, SQFloat::_6);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    triangleUT = triangleUT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == PIVOT_POINT);
    BOOST_CHECK(triangleUT.B == PIVOT_POINT);
    BOOST_CHECK(triangleUT.C == PIVOT_POINT);
}

/// <summary>
/// Checks that the correct circumcenter is calculated.
/// </summary>
QTEST_CASE ( GetCircumcenter_CircumcenterIsCorrectlyCalculatedWhenUsingCommonTriangle_Test )
{
   // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 POINT_B = QVector2(SQFloat::_5, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_3, SQFloat::_4);

    const QVector2 EXPECTED_VALUE_CIRCUMCENTER = QVector2(SQFloat::_3, SQFloat::_2);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    QVector2 circumcenter = triangleUT.GetCircumcenter();
    
    // [Verification]
    BOOST_CHECK(circumcenter.x == EXPECTED_VALUE_CIRCUMCENTER.x);
    BOOST_CHECK(circumcenter.y == EXPECTED_VALUE_CIRCUMCENTER.y);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE ( GetCircumcenter_AssertionFailsWhenAllPointsCoincide_Test )
{
    // [Preparation]
    const QVector2 POINT = QVector2(SQFloat::_2, SQFloat::_2);
    QTriangle2D TRIANGLE = QTriangle2D(POINT, POINT, POINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        TRIANGLE.GetCircumcenter();
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
/// Checks that the correct orthocenter is calculated.
/// </summary>
QTEST_CASE ( GetOrthocenter_OrthocenterIsCorrectlyCalculatedWhenUsingCommonTriangle_Test )
{
    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_2, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_3);
    const QVector2 POINT_C = QVector2(SQFloat::_3, SQFloat::_4);

    const QVector2 EXPECTED_VALUE_ORTHOCENTER = QVector2(SQFloat::_3, -SQFloat::_2);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    QVector2 orthocenter = triangleUT.GetOrthocenter();
    
    // [Verification]
    BOOST_CHECK(orthocenter.x == EXPECTED_VALUE_ORTHOCENTER.x);
    BOOST_CHECK(orthocenter.y == EXPECTED_VALUE_ORTHOCENTER.y);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE ( GetOrthocenter_AssertionFailsWhenAllPointsCoincide_Test )
{
   // [Preparation]
    const QVector2 POINT = QVector2(SQFloat::_2, SQFloat::_2);
    QTriangle2D TRIANGLE = QTriangle2D(POINT, POINT, POINT);
    
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
/// Checks that a triangle is correctly translated.
/// </summary>
QTEST_CASE ( Translate1_TriangleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_4, SQFloat::_5);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);

    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_4);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
QTEST_CASE ( Translate1_TriangleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);

    const QVector2 TRANSLATION_VECTOR = QVector2::GetNullVector();

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly translated.
/// </summary>
QTEST_CASE ( Translate2_TriangleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_4, SQFloat::_5);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);

    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_4);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
QTEST_CASE ( Translate2_TriangleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_4, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_9);

    const QVector2 TRANSLATION_VECTOR = QVector2::GetNullVector();

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly rotated.
/// </summary>
QTEST_CASE ( Rotate_TriangleIsCorrectlyRotated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_0, SQFloat::_5);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_5, SQFloat::_0);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when angle is zero.
/// </summary>
QTEST_CASE ( Rotate_TriangleIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_5, SQFloat::_0);
    const float_q ANGLE = SQFloat::_0;

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly rotated with pivot point.
/// </summary>
QTEST_CASE ( RotateWithPivot_TriangleIsCorrectlyRotated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(-SQFloat::_2, SQFloat::_2);
    const QVector2 POINT_C = QVector2(SQFloat::_0, SQFloat::_5);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_1, SQFloat::_2);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_1, -SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_2, SQFloat::_1);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated with a pivot when angle is zero.
/// </summary>
QTEST_CASE ( RotateWithPivot_TriangleIsNotRotatedWithPivotWhenAngleIsZero_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(-SQFloat::_3, SQFloat::_1);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(-SQFloat::_2, -SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(-SQFloat::_5, SQFloat::_0);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q ANGLE = SQFloat::_0;

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly scaled.
/// </summary>
QTEST_CASE ( Scale1_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_10 + SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_4, SQFloat::_10 + SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_4, SQFloat::_10 + SQFloat::_10);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled if Scale is one.
/// </summary>
QTEST_CASE ( Scale1_TriangleIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly scaled.
/// </summary>
QTEST_CASE ( Scale2_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_2, SQFloat::_10 + SQFloat::_2);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_4, SQFloat::_10 + SQFloat::_6);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_4, SQFloat::_10 + SQFloat::_10);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled if scale equals one.
/// </summary>
QTEST_CASE ( Scale2_TriangleIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly scaled with a pivot.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_2, SQFloat::_10 + SQFloat::_1);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled with a pivot if Scale is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_TriangleIsNotScaledWithPivotIfScaleIsOne_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled with a pivot if Scale is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 POINT_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 POINT_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 POINT_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_0, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_10 + SQFloat::_2, SQFloat::_10 + SQFloat::_1);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled with a pivot if Scale is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_TriangleIsNotScaledWithPivotIfScaleIsOne_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_A = QVector2(SQFloat::_1, SQFloat::_3);
    const QVector2 EXPECTED_VALUE_FOR_B = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 EXPECTED_VALUE_FOR_C = QVector2(SQFloat::_7, SQFloat::_5);

    const QVector2 SCALING_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

    const QVector2 PIVOT_POINT = QVector2(SQFloat::_2, SQFloat::_3);

	// [Execution]
    QTriangle2D triangleUT = QTriangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

// End - Test Suite: QTriangle2D
QTEST_SUITE_END()
