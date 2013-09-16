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

#include "QVector2.h"
#include "SQAngle.h"
#include "QBaseMatrix2x2.h"
#include "QMatrix3x3.h"
#include "QTransformationMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;

QTEST_SUITE_BEGIN( QVector2_TestSuite )

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);
    const float_q  SCALAR = SQFloat::_0_5;

	// Execution
    QVector2 vVectorUT = SCALAR * VECTOR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

	// Execution
    QVector2 vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if copy constructor sets vector components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    const QVector2 VECTOR_TO_COPY(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y);

	// Execution
    QVector2 vVectorUT = VECTOR_TO_COPY;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if every input vector's component is copied to the right target vector's component.
/// </summary>
QTEST_CASE ( Constructor3_VectorComponentsAreCopiedToRightComponents_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector2;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    QBaseVector2 BASEVECTOR(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y);

	// Execution
    QVector2 vVectorUT(BASEVECTOR);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if values used as parameters are properly set to vector components.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

	// Execution
    QVector2 vVectorUT(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if the value provided is set to all the vector components.
/// </summary>
QTEST_CASE ( Constructor5_ValueIsSetForAllComponents_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_5;

	// Execution
    QVector2 vVectorUT(EXPECTED_VALUE_FOR_ALL);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if the vector components are set to the correct floats stored in a valid memory space.
/// </summary>
QTEST_CASE ( Constructor6_VectorComponentsAreFilledWithValidReferenceTo2Floats_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    float_q* VALID_ARRAY_OF_2_FLOATS = new float_q[2];
    VALID_ARRAY_OF_2_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_2_FLOATS[1] = EXPECTED_VALUE_FOR_Y;

	// Execution
    QVector2 vVectorUT(VALID_ARRAY_OF_2_FLOATS);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);

    // Cleaning
    delete[] VALID_ARRAY_OF_2_FLOATS;
}

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenPointerIsNull_Test )
{
    // Preparation
    const float_q* NULL_ARRAY = null_q;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QVector2 vVectorUT(NULL_ARRAY);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if vector components are set to the correct values packed in a valid vf32 object.
/// </summary>
QTEST_CASE ( Constructor7_VectorComponentsAreSetToValidVF32PackedValues_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

	vf32_q PACK;
	SQVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, SQFloat::_0, SQFloat::_0, PACK);

	// Execution
	QVector2 vVectorUT(PACK);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a vector with all components set to zero.
/// </summary>
QTEST_CASE ( GetZeroVector_ReturnsANullVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

	// Execution
    QVector2 vVectorUT = QVector2::GetZeroVector();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a vector with all components set to one.
/// </summary>
QTEST_CASE ( GetVectorOfOnes_ReturnsAVectorOfOnes_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

	// Execution
    QVector2 vVectorUT = QVector2::GetVectorOfOnes();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to positive direction.
/// </summary>
QTEST_CASE ( GetUnitVectorX_ReturnsAUnitVectorThatPointsToPositiveDirectionOfXAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

	// Execution
    QVector2 vVectorUT = QVector2::GetUnitVectorX();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to positive direction.
/// </summary>
QTEST_CASE ( GetUnitVectorY_ReturnsAUnitVectorThatPointsToPositiveDirectionOfYAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

	// Execution
    QVector2 vVectorUT = QVector2::GetUnitVectorY();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to negative direction.
/// </summary>
QTEST_CASE ( GetUnitVectorInvX_ReturnsAUnitVectorThatPointsToNegativeDirectionOfXAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

	// Execution
    QVector2 vVectorUT = QVector2::GetUnitVectorInvX();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to negative direction.
/// </summary>
QTEST_CASE ( GetUnitVectorInvY_ReturnsAUnitVectorThatPointsToNegativeDirectionOfYAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_1;
	// Execution
    QVector2 vVectorUT = QVector2::GetUnitVectorInvY();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
QTEST_CASE ( OperatorAddition_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3 + SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_5;

    const QVector2 OPERAND1 = QVector2(SQFloat::_0_25, SQFloat::_1);
    const QVector2 OPERAND2 = QVector2(SQFloat::_3, SQFloat::_4);

	// Execution
    QVector2 vVectorUT = OPERAND1 + OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorAddition_VectorIsCorrectlyAddedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    const QVector2 OPERAND = QVector2(SQFloat::_0_25, SQFloat::_1);

	// Execution
    QVector2 vVectorUT = OPERAND + OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtraction_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_2 - SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_3;

    const QVector2 OPERAND1 = QVector2(SQFloat::_0_5, SQFloat::_1);
    const QVector2 OPERAND2 = QVector2(SQFloat::_3, SQFloat::_4);

	// Execution
    QVector2 vVectorUT = OPERAND1 - OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorSubtraction_VectorIsCorrectlySubtractedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

    const QVector2 OPERAND = QVector2(-SQFloat::_0_25, SQFloat::_1);

	// Execution
    QVector2 vVectorUT = OPERAND - OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProduct1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_0);
    const float_q  SCALAR = SQFloat::_0_5;

	// Execution
    QVector2 vVectorUT = VECTOR * SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorProduct2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = 10;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    QVector2 vVectorUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
QTEST_CASE ( OperatorProduct2_ProductIsCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = 10;

    const QVector2 OPERAND1 = QVector2(-SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    QVector2 vVector1UT = OPERAND1 * OPERAND2;
    QVector2 vVector2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
QTEST_CASE ( OperatorProduct2_VectorCanBeMultipliedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_4;

    const QVector2 OPERAND = QVector2(-SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT = OPERAND * OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 2 rows and 2 columns.
/// </summary>
QTEST_CASE ( OperatorProduct3_VectorIsCorrectlyMultipliedByMatrix2x2_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = 4;
    const float_q EXPECTED_VALUE_FOR_Y = 7;

    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QBaseMatrix2x2 MATRIX = QBaseMatrix2x2(SQFloat::_0, SQFloat::_1,
                                                 SQFloat::_2, SQFloat::_3);

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT = VECTOR * MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivision1_VectorIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);
    const float_q  SCALAR = SQFloat::_2;

	// Execution
    QVector2 vVectorUT = VECTOR / SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that there is an assertion that warns when the divisor equals zero.
/// </summary>
QTEST_CASE ( OperatorDivision1_AssertionFailsWhenDivisorEqualsZero_Test )
{
    // Preparation
    const float_q  SCALAR = SQFloat::_0;

    // Execution
    bool bAssertionFailed = false;

    try
    {
        QVector2 vVectorUT;
        vVectorUT / SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that every component of one operand is divided by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorDivision2_VectorIsCorrectlyDividedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = 2;

    const QVector2 OPERAND1 = QVector2(SQFloat::_2, SQFloat::_8);
    const QVector2 OPERAND2 = QVector2(SQFloat::_2, SQFloat::_4);

	// Execution
    QVector2 vVectorUT = OPERAND1 / OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
QTEST_CASE ( OperatorDivision2_DivisionIsNotCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.4;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    QVector2 vVector1UT = OPERAND1 / OPERAND2;
    QVector2 vVector2UT = OPERAND2 / OPERAND1;

    // Verification
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_NE(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_NE(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be divided by itself.
/// </summary>
QTEST_CASE ( OperatorDivision2_VectorCanBeDividedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

    const QVector2 OPERAND = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT = OPERAND / OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
QTEST_CASE ( OperatorDivision2_AssertionFailsWhenAnyComponentEqualsZero_Test )
{
    // Preparation
    const QVector2 OPERAND_WITH_ZERO_X = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 OPERAND_WITH_ZERO_Y = QVector2(SQFloat::_1, SQFloat::_0);

	// Execution
    bool bAssertionFailedWhenXEqualsZero = false;
    bool bAssertionFailedWhenYEqualsZero = false;

    QVector2 vVectorUT;

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_X;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenXEqualsZero = true;
    }

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_Y;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenYEqualsZero = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailedWhenXEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenYEqualsZero);
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3 + SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_5;

    const QVector2 OPERAND1 = QVector2(SQFloat::_0_25, SQFloat::_1);
    const QVector2 OPERAND2 = QVector2(SQFloat::_3, SQFloat::_4);

	// Execution
    QVector2 vVectorUT = OPERAND1;
    vVectorUT += OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_VectorIsCorrectlyAddedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    const QVector2 OPERAND = QVector2(SQFloat::_0_25, SQFloat::_1);

	// Execution
    QVector2 vVectorUT = OPERAND;
    vVectorUT += OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_VectorObjectIsCorrectlyAddedAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    const QVector2 OPERAND = QVector2(SQFloat::_0_25, SQFloat::_1);

	// Execution
    QVector2 vVectorUT = OPERAND;
    vVectorUT += vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)-2.75;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_3;

    const QVector2 OPERAND1 = QVector2(SQFloat::_0_25, SQFloat::_1);
    const QVector2 OPERAND2 = QVector2(SQFloat::_3, SQFloat::_4);

	// Execution
    QVector2 vVectorUT = OPERAND1;
    vVectorUT -= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_VectorIsCorrectlySubtractedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

    const QVector2 OPERAND = QVector2(SQFloat::_0_25, SQFloat::_1);

	// Execution
    QVector2 vVectorUT = OPERAND;
    vVectorUT -= OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_VectorObjectIsCorrectlySubtractedAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

    const QVector2 OPERAND = QVector2(SQFloat::_0_25, SQFloat::_1);

	// Execution
    QVector2 vVectorUT = OPERAND;
    vVectorUT -= vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_0);
    const float_q  SCALAR = SQFloat::_0_5;

	// Execution
    QVector2 vVectorUT = VECTOR;
    vVectorUT *= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector component is multiplied and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_VectorComponentIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)24;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)36;

    const QVector2 VECTOR = QVector2(SQFloat::_2, SQFloat::_3);

	// Execution
    QVector2 vVectorUT = VECTOR;
    vVectorUT *= vVectorUT.x; // x2  Now x==4,    y==6
    vVectorUT *= vVectorUT.y; // x6  Now x==24,   y==36

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = 10;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    QVector2 vVectorUT = OPERAND1;
    vVectorUT *= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_ProductIsCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = 10;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    QVector2 vVector1UT = OPERAND1;
    vVector1UT *= OPERAND2;
    QVector2 vVector2UT = OPERAND2;
    vVector2UT *= OPERAND1;

    // Verification
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_VectorCanBeMultipliedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_4;

    const QVector2 OPERAND = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT = OPERAND;
    vVectorUT *= OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a vector object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_VectorObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_9;

    const QVector2 OPERAND = QVector2(SQFloat::_2, SQFloat::_3);

	// Execution
    QVector2 vVectorUT = OPERAND;
    vVectorUT *= vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 2 rows and 2 columns.
/// </summary>
QTEST_CASE ( OperatorProductAssignation3_VectorIsCorrectlyMultipliedByMatrix2x2_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = 4;
    const float_q EXPECTED_VALUE_FOR_Y = 7;

    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QBaseMatrix2x2 MATRIX = QBaseMatrix2x2(SQFloat::_0, SQFloat::_1,
                                                 SQFloat::_2, SQFloat::_3);

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT = VECTOR;
    vVectorUT *= MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_VectorIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);
    const float_q  SCALAR = SQFloat::_2;

	// Execution
    QVector2 vVectorUT = VECTOR;
    vVectorUT /= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that there is an assertion that warns when the divisor equals zero.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_AssertionFailsWhenDivisorEqualsZero_Test )
{
    // Preparation
    const float_q  SCALAR = SQFloat::_0;

    // Execution
    bool bAssertionFailed = false;

    try
    {
        QVector2 vVectorUT;
        vVectorUT /= SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that a vector component is divided and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_VectorComponentIsCorrectlyDividedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

    const QVector2 VECTOR = QVector2(SQFloat::_2, SQFloat::_4);

	// Execution
    QVector2 vVectorUT = VECTOR;
    vVectorUT /= vVectorUT.x; // :2 Now x==1,    y==2
    vVectorUT /= vVectorUT.y; // :2 Now x==0.5,  y==1

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that every component of one operand is divided by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_VectorIsCorrectlyDividedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = 2;

    const QVector2 OPERAND1 = QVector2(SQFloat::_2, SQFloat::_8);
    const QVector2 OPERAND2 = QVector2(SQFloat::_2, SQFloat::_4);

	// Execution
    QVector2 vVectorUT = OPERAND1;
    vVectorUT /= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_DivisionIsNotCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.4;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    QVector2 vVector1UT = OPERAND1;
    vVector1UT /= OPERAND2;
    QVector2 vVector2UT = OPERAND2;
    vVector2UT /= OPERAND1;

    // Verification
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_NE(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_NE(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be divided by itself.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_VectorCanBeDividedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;

    QVector2 vVectorUT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    vVectorUT /= vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_AssertionFailsWhenAnyComponentEqualsZero_Test )
{
    // Preparation
    const QVector2 OPERAND_WITH_ZERO_X = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 OPERAND_WITH_ZERO_Y = QVector2(SQFloat::_1, SQFloat::_0);

	// Execution
    bool bAssertionFailedWhenXEqualsZero = false;
    bool bAssertionFailedWhenYEqualsZero = false;

    QVector2 vVectorUT;

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_X;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenXEqualsZero = true;
    }

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_Y;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenYEqualsZero = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailedWhenXEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenYEqualsZero);
}

/// <summary>
/// Checks that a vector is correctly assigned to another vector.
/// </summary>
QTEST_CASE ( OperatorAssignation_VectorIsAssignedProperlyToAnother_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT;
    vVectorUT = VECTOR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that all vector components are correctly negated.
/// </summary>
QTEST_CASE ( OperatorUnaryMinus_ComponentsAreNegated_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;

    const QVector2 VECTOR = QVector2(SQFloat::_1, -SQFloat::_2);

	// Execution
    QVector2 vVectorUT = -VECTOR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the length of the vector is correctly calculated.
/// </summary>
QTEST_CASE ( GetLength_LengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // Preparation
    const float_q EXPECTED_LENGTH = SQFloat::_5;

    const QVector2 VECTOR = QVector2(SQFloat::_4, SQFloat::_3);

	// Execution
    float_q fLengthUT = VECTOR.GetLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that the squared length of the vector is correctly calculated.
/// </summary>
QTEST_CASE ( GetSquaredLength_SquaredLengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE = (float_q)25.0;

    const QVector2 VECTOR = QVector2(SQFloat::_4, SQFloat::_3);

	// Execution
    float_q fSquaredLengthUT = VECTOR.GetSquaredLength();

    // Verification
    BOOST_CHECK_EQUAL(fSquaredLengthUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the perpendicular of the vector is correctly calculated.
/// </summary>
QTEST_CASE ( GetPerpendicular_PerpendicularOfACommonVectorIsCalculatedCorrectly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_4;

    const QVector2 VECTOR = QVector2(SQFloat::_4, SQFloat::_3);

	// Execution
	QVector2 vPerpendicularVectorUT = VECTOR.GetPerpendicular();

    // Verification
    BOOST_CHECK_EQUAL(vPerpendicularVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vPerpendicularVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a common vector becomes a unit vector.
/// </summary>
QTEST_CASE ( Normalize_CommonVectorIsCorrectlyNormalized_Test )
{
    // Preparation
    const float_q EXPECTED_SQUAREDLENGTH = SQFloat::_1;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT = VECTOR.Normalize();

    // Verification
    float_q fSquaredLength = vVectorUT.GetSquaredLength();

    BOOST_CHECK(SQFloat::AreEqual(fSquaredLength, EXPECTED_SQUAREDLENGTH));
}

/// <summary>
/// Checks that the assertion fails when a null vector is to be normalized.
/// </summary>
QTEST_CASE ( Normalize_AssertionFailsWhenNullVectorIsToBeNormalized_Test )
{
    // Preparation
    const QVector2 VECTOR = QVector2(SQFloat::_0, SQFloat::_0);

	// Execution
    bool bAssertionFailed = false;

    try
    {
        VECTOR.Normalize();
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that all vector components are set to one.
/// </summary>
QTEST_CASE ( ResetToOne_AllVectorComponentsAreSetToOne_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_1;

    const QVector2 VECTOR = QVector2(SQFloat::_1, -SQFloat::_2);

	// Execution
    QVector2 vVectorUT = VECTOR;
    vVectorUT.ResetToOne();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that all vector components are set to zero.
/// </summary>
QTEST_CASE ( ResetToZero_AllVectorComponentsAreSetToZero_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    const QVector2 VECTOR = QVector2(SQFloat::_1, -SQFloat::_2);

	// Execution
    QVector2 vVectorUT = VECTOR;
    vVectorUT.ResetToZero();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that it returns true when all vector components equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenAllVectorComponentsEqualZero_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = true;

    const QVector2 VECTOR = QVector2(SQFloat::_0, SQFloat::_0);

	// Execution
    bool bResult = VECTOR.IsZero();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when not all vector components equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsFalseWhenNotAllVectorComponentsEqualZero_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = false;

    const QVector2 VECTOR_X_NOT_EQUAL_ZERO = QVector2(SQFloat::_1, SQFloat::_0);
    const QVector2 VECTOR_Y_NOT_EQUAL_ZERO = QVector2(SQFloat::_0, SQFloat::_1);


	// Execution
    bool bResult = VECTOR_X_NOT_EQUAL_ZERO.IsZero();
    bResult |= VECTOR_Y_NOT_EQUAL_ZERO.IsZero();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when all vector components equal one.
/// </summary>
QTEST_CASE ( IsVectorOfOnes_ReturnsTrueWhenAllVectorComponentsEqualOne_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = true;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_1);

	// Execution
    bool bResult = VECTOR.IsVectorOfOnes();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when not all vector components equal one.
/// </summary>
QTEST_CASE ( IsVectorOfOnes_ReturnsFalseWhenNotAllVectorComponentsEqualOne_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = false;

    const QVector2 VECTOR_X_NOT_EQUAL_ONE = QVector2(SQFloat::_0, SQFloat::_1);
    const QVector2 VECTOR_Y_NOT_EQUAL_ONE = QVector2(SQFloat::_1, SQFloat::_0);

	// Execution
    bool bResult = VECTOR_X_NOT_EQUAL_ONE.IsVectorOfOnes();
    bResult |= VECTOR_Y_NOT_EQUAL_ONE.IsVectorOfOnes();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned dot product result for 2 common vectors equals the expected value.
/// </summary>
QTEST_CASE ( DotProduct_ReturnsDotProductFor2CommonVectors_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = (float_q)14.0;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    float_q fResultUT = OPERAND1.DotProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
QTEST_CASE ( DotProduct_DotProductIsCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = (float_q)14.0;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_4, SQFloat::_5);

	// Execution
    float_q fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when vectors are orthogonal.
/// </summary>
QTEST_CASE ( DotProduct_DotProductEqualsZeroWhenVectorsAreOrthogonal_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QVector2 OPERAND1 = QVector2(SQFloat::_3, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_2, -SQFloat::_3);

	// Execution
    float_q fResultUT = OPERAND1.DotProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for 2 common vectors equals the expected value.
/// </summary>
QTEST_CASE ( DotProductAngle_ReturnsAngleBetween2CommonVectors_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_45;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
    #endif

    const QVector2 OPERAND1 = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_0, SQFloat::_1);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
QTEST_CASE ( DotProductAngle_DotProductAngleIsCommutative_Test )
{
    // Preparation
    const QVector2 OPERAND1 = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_0, SQFloat::_1);
    
	// Execution
    float_q fResult1UT = OPERAND1.DotProductAngle(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProductAngle(OPERAND1);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the angle equals zero when vectors are parallel.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleEqualsZeroWhenVectorsAreParallel_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_1);
    const QVector2 OPERAND2 = QVector2(SQFloat::_2, SQFloat::_2);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when vectors are orthogonal.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleEqualsHalfPiRadiansOr90DegreesWhenVectorsAreOrthogonal_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_90;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_HalfPi;
    #endif

    const QVector2 OPERAND1 = QVector2(SQFloat::_2, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_1, -SQFloat::_1);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when vectors are opposite.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleEqualsPiRadiansOr180DegreesWhenVectorsAreOpposite_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_180;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_Pi;
    #endif

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(-SQFloat::_1, -SQFloat::_2);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleIsAlwaysPositive_Test )
{
    // Preparation
    const QVector2 OPERAND_IN_I_QUADRANT_1 = QVector2(SQFloat::_2, SQFloat::_1);
    const QVector2 OPERAND_IN_I_QUADRANT_2 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND_IN_II_QUADRANT_1 = QVector2(-SQFloat::_2, SQFloat::_1);
    const QVector2 OPERAND_IN_II_QUADRANT_2 = QVector2(-SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND_IN_III_QUADRANT_1 = QVector2(-SQFloat::_2, -SQFloat::_1);
    const QVector2 OPERAND_IN_III_QUADRANT_2 = QVector2(-SQFloat::_1, -SQFloat::_2);
    const QVector2 OPERAND_IN_IV_QUADRANT_1 = QVector2(SQFloat::_2, -SQFloat::_1);
    const QVector2 OPERAND_IN_IV_QUADRANT_2 = QVector2(SQFloat::_1, -SQFloat::_2);


	// Execution
    float_q fResult1_1UT = OPERAND_IN_I_QUADRANT_1.DotProductAngle(OPERAND_IN_II_QUADRANT_1);
    float_q fResult2_1UT = OPERAND_IN_I_QUADRANT_1.DotProductAngle(OPERAND_IN_II_QUADRANT_2);
    float_q fResult3_1UT = OPERAND_IN_I_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_1UT = OPERAND_IN_I_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_1UT = OPERAND_IN_I_QUADRANT_1.DotProductAngle(OPERAND_IN_IV_QUADRANT_1);
    float_q fResult6_1UT = OPERAND_IN_I_QUADRANT_1.DotProductAngle(OPERAND_IN_IV_QUADRANT_2);

    float_q fResult1_2UT = OPERAND_IN_I_QUADRANT_2.DotProductAngle(OPERAND_IN_II_QUADRANT_1);
    float_q fResult2_2UT = OPERAND_IN_I_QUADRANT_2.DotProductAngle(OPERAND_IN_II_QUADRANT_2);
    float_q fResult3_2UT = OPERAND_IN_I_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_2UT = OPERAND_IN_I_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_2UT = OPERAND_IN_I_QUADRANT_2.DotProductAngle(OPERAND_IN_IV_QUADRANT_1);
    float_q fResult6_2UT = OPERAND_IN_I_QUADRANT_2.DotProductAngle(OPERAND_IN_IV_QUADRANT_2);

    float_q fResult1_3UT = OPERAND_IN_II_QUADRANT_1.DotProductAngle(OPERAND_IN_I_QUADRANT_1);
    float_q fResult2_3UT = OPERAND_IN_II_QUADRANT_1.DotProductAngle(OPERAND_IN_I_QUADRANT_2);
    float_q fResult3_3UT = OPERAND_IN_II_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_3UT = OPERAND_IN_II_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_3UT = OPERAND_IN_II_QUADRANT_1.DotProductAngle(OPERAND_IN_IV_QUADRANT_1);
    float_q fResult6_3UT = OPERAND_IN_II_QUADRANT_1.DotProductAngle(OPERAND_IN_IV_QUADRANT_2);

    float_q fResult1_4UT = OPERAND_IN_II_QUADRANT_2.DotProductAngle(OPERAND_IN_I_QUADRANT_1);
    float_q fResult2_4UT = OPERAND_IN_II_QUADRANT_2.DotProductAngle(OPERAND_IN_I_QUADRANT_2);
    float_q fResult3_4UT = OPERAND_IN_II_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_4UT = OPERAND_IN_II_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_4UT = OPERAND_IN_II_QUADRANT_2.DotProductAngle(OPERAND_IN_IV_QUADRANT_1);
    float_q fResult6_4UT = OPERAND_IN_II_QUADRANT_2.DotProductAngle(OPERAND_IN_IV_QUADRANT_2);

    float_q fResult1_5UT = OPERAND_IN_III_QUADRANT_1.DotProductAngle(OPERAND_IN_II_QUADRANT_1);
    float_q fResult2_5UT = OPERAND_IN_III_QUADRANT_1.DotProductAngle(OPERAND_IN_II_QUADRANT_2);
    float_q fResult3_5UT = OPERAND_IN_III_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_5UT = OPERAND_IN_III_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_5UT = OPERAND_IN_III_QUADRANT_1.DotProductAngle(OPERAND_IN_IV_QUADRANT_1);
    float_q fResult6_5UT = OPERAND_IN_III_QUADRANT_1.DotProductAngle(OPERAND_IN_IV_QUADRANT_2);

    float_q fResult1_6UT = OPERAND_IN_III_QUADRANT_2.DotProductAngle(OPERAND_IN_II_QUADRANT_1);
    float_q fResult2_6UT = OPERAND_IN_III_QUADRANT_2.DotProductAngle(OPERAND_IN_II_QUADRANT_2);
    float_q fResult3_6UT = OPERAND_IN_III_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_6UT = OPERAND_IN_III_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_6UT = OPERAND_IN_III_QUADRANT_2.DotProductAngle(OPERAND_IN_IV_QUADRANT_1);
    float_q fResult6_6UT = OPERAND_IN_III_QUADRANT_2.DotProductAngle(OPERAND_IN_IV_QUADRANT_2);

    float_q fResult1_7UT = OPERAND_IN_IV_QUADRANT_1.DotProductAngle(OPERAND_IN_II_QUADRANT_1);
    float_q fResult2_7UT = OPERAND_IN_IV_QUADRANT_1.DotProductAngle(OPERAND_IN_II_QUADRANT_2);
    float_q fResult3_7UT = OPERAND_IN_IV_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_7UT = OPERAND_IN_IV_QUADRANT_1.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_7UT = OPERAND_IN_IV_QUADRANT_1.DotProductAngle(OPERAND_IN_I_QUADRANT_1);
    float_q fResult6_7UT = OPERAND_IN_IV_QUADRANT_1.DotProductAngle(OPERAND_IN_I_QUADRANT_2);

    float_q fResult1_8UT = OPERAND_IN_IV_QUADRANT_2.DotProductAngle(OPERAND_IN_II_QUADRANT_1);
    float_q fResult2_8UT = OPERAND_IN_IV_QUADRANT_2.DotProductAngle(OPERAND_IN_II_QUADRANT_2);
    float_q fResult3_8UT = OPERAND_IN_IV_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_1);
    float_q fResult4_8UT = OPERAND_IN_IV_QUADRANT_2.DotProductAngle(OPERAND_IN_III_QUADRANT_2);
    float_q fResult5_8UT = OPERAND_IN_IV_QUADRANT_2.DotProductAngle(OPERAND_IN_I_QUADRANT_1);
    float_q fResult6_8UT = OPERAND_IN_IV_QUADRANT_2.DotProductAngle(OPERAND_IN_I_QUADRANT_2);

    // Verification
    BOOST_CHECK( SQFloat::IsPositive(fResult1_1UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_1UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_1UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_1UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_1UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_1UT) );

    BOOST_CHECK( SQFloat::IsPositive(fResult1_2UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_2UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_2UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_2UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_2UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_2UT) );

    BOOST_CHECK( SQFloat::IsPositive(fResult1_3UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_3UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_3UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_3UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_3UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_3UT) );

    BOOST_CHECK( SQFloat::IsPositive(fResult1_4UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_4UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_4UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_4UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_4UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_4UT) );

    BOOST_CHECK( SQFloat::IsPositive(fResult1_5UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_5UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_5UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_5UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_5UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_5UT) );

    BOOST_CHECK( SQFloat::IsPositive(fResult1_6UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_6UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_6UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_6UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_6UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_6UT) );

    BOOST_CHECK( SQFloat::IsPositive(fResult1_7UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_7UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_7UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_7UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_7UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_7UT) );

    BOOST_CHECK( SQFloat::IsPositive(fResult1_8UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2_8UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult3_8UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult4_8UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult5_8UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult6_8UT) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when vector are not opposite.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleIsLowerThanPiRadiansOr180DegreesWhenVectorsAreNotOpposite_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_180;
    #else
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_Pi;
    #endif

    const QVector2 OPERAND_IN_I_QUADRANT = QVector2(SQFloat::_2, SQFloat::_1);
    const QVector2 OPERAND_IN_II_QUADRANT = QVector2(-SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND_IN_III_QUADRANT = QVector2(-SQFloat::_1, -SQFloat::_2);
    const QVector2 OPERAND_IN_IV_QUADRANT = QVector2(SQFloat::_2, -SQFloat::_1);

	// Execution
    float_q fResult1UT = OPERAND_IN_I_QUADRANT.DotProductAngle(OPERAND_IN_II_QUADRANT);
    float_q fResult2UT = OPERAND_IN_I_QUADRANT.DotProductAngle(OPERAND_IN_III_QUADRANT);
    float_q fResult3UT = OPERAND_IN_I_QUADRANT.DotProductAngle(OPERAND_IN_IV_QUADRANT);


    // Verification
    BOOST_CHECK( SQFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessThan(fResult3UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that a correct vector is obtained as result of interpolating between 2 common vectors.
/// </summary>
QTEST_CASE ( Lerp_CorrectLerpedVectorIsObtainedForTwoCommonVectors_Test )
{
    // Preparation
    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 EXPECTED_RESULT = QVector2(SQFloat::_2, SQFloat::_3);

	// Execution
    QVector2 vVectorUT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent vectors is the same vector.
/// </summary>
QTEST_CASE ( Lerp_InterpolatingTwoEquivalentVectorsGivesSameVector_Test )
{
    // Preparation
    const QVector2 EXPECTED_RESULT = QVector2(SQFloat::_1, SQFloat::_2);

	// Execution
    QVector2 vVectorUT = EXPECTED_RESULT.Lerp(SQFloat::_0_5, EXPECTED_RESULT);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the result of interpolating just in the middle between 2 opposite vectors is a null vector.
/// </summary>
QTEST_CASE ( Lerp_InterpolatingInTheMiddleOfTwoOppositeVectorsGivesNullVector_Test )
{
    // Preparation
    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = -OPERAND1;
    const QVector2 EXPECTED_RESULT = QVector2::GetZeroVector();

	// Execution
    QVector2 vVectorUT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the vector obtained when using a non-null vector and a null vector is just the proportion of the non-null vector.
/// </summary>
QTEST_CASE ( Lerp_WhenUsedNonNullVectorAndNullVectorTheResultIsAScaledNonNullVector_Test )
{
    // Preparation
    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2::GetZeroVector();
    const QVector2 EXPECTED_RESULT = OPERAND1 * (SQFloat::_1 - SQFloat::_0_25);

	// Execution
    QVector2 vVectorUT = OPERAND1.Lerp(SQFloat::_0_25, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that when the proportion equals 0, the returned vector is the resident vector.
/// </summary>
QTEST_CASE ( Lerp_ProportionZeroMeansResidentVector_Test )
{
    // Preparation
    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 EXPECTED_RESULT = OPERAND1;

	// Execution
    QVector2 vVectorUT = OPERAND1.Lerp(SQFloat::_0, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned vector is the input vector.
/// </summary>
QTEST_CASE ( Lerp_ProportionOneMeansInputVector_Test )
{
    // Preparation
    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 OPERAND2 = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 EXPECTED_RESULT = OPERAND2;

	// Execution
    QVector2 vVectorUT = OPERAND1.Lerp(SQFloat::_1, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the distance between 2 common vectors equals the expected value.
/// </summary>
QTEST_CASE ( Distance_ReturnsDistanceBetween2CommonVectors_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_5;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_4);
    const QVector2 OPERAND2 = QVector2(SQFloat::_5, SQFloat::_1);

	// Execution
    float_q fResultUT = OPERAND1.Distance(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the distance between 2 common vectors is conmutative.
/// </summary>
QTEST_CASE ( Distance_DistanceBetween2CommonVectorsIsConmutative_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_5;

    const QVector2 OPERAND1 = QVector2(SQFloat::_1, SQFloat::_4);
    const QVector2 OPERAND2 = QVector2(SQFloat::_5, SQFloat::_1);

	// Execution
    float_q fResultUT1 = OPERAND1.Distance(OPERAND2);
    float_q fResultUT2 = OPERAND2.Distance(OPERAND1);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT1, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResultUT2, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the distance equals zero when both vectors are the same.
/// </summary>
QTEST_CASE ( Distance_ExactlyZeroWhenTwoVectorsAreTheSame_Test )
{
    // Preparation
    const QVector2 OPERAND = QVector2(SQFloat::_1, SQFloat::_2);
    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fDistanceUT = OPERAND.Distance(OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(fDistanceUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks the distance between 2 opposite vectors equals the sume of their lengths.
/// </summary>
QTEST_CASE ( Distance_ForTwoOppositeVectorsResultEqualsSumOfTheirLengths_Test )
{
    // Preparation
    const QVector2 OPERAND = QVector2(SQFloat::_3, SQFloat::_4);
    const QVector2 OPPOSITE_OPERAND = QVector2(-SQFloat::_1 - SQFloat::_0_5, -SQFloat::_2);
    const float_q EXPECTED_RESULT = SQFloat::_7 + SQFloat::_0_5;

	// Execution
    float_q fDistancerUT = OPERAND.Distance(OPPOSITE_OPERAND);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fDistancerUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks if vector is correctly rotated the given angle.
/// </summary>
QTEST_CASE ( Transform1_VectorIsCorrectlyRotatedTheGivenAngle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 OPERAND = QVector2(SQFloat::_3, SQFloat::_4);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q TEST_ANGLE = SQAngle::_90;
    #else
        const float_q TEST_ANGLE = SQAngle::_HalfPi;
    #endif

    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y =  SQFloat::_3;

    // Execution
    QVector2 vVectorUT = OPERAND.Transform(TEST_ANGLE);

    // Verification
    BOOST_CHECK(SQFloat::AreEqual(vVectorUT.x, EXPECTED_VALUE_FOR_X));
    BOOST_CHECK(SQFloat::AreEqual(vVectorUT.y, EXPECTED_VALUE_FOR_Y));
}

/// <summary>
/// Checks if vector is not modified if the given angle is 0º.
/// </summary>
QTEST_CASE ( Transform1_VectorIsNotRotatedByZeroAngle_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QVector2 OPERAND = QVector2(SQFloat::_3, SQFloat::_4);

    const float_q TEST_ANGLE = SQFloat::_0;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_4;

    // Execution
    QVector2 vVectorUT = OPERAND.Transform(TEST_ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if vector is correctly transformed by an arbitrary transformation matrix.
/// </summary>
QTEST_CASE ( Transform2_VectorIsCorrectlyTransformedByAMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);
    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #else
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_5;

    // Execution
    QVector2 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vVectorUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(vVectorUT.y, EXPECTED_VALUE_FOR_Y) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform2_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);
    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3::GetIdentity();
    const QVector2 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector2 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
}

/// <summary>
/// Checks that the vector is nulled when the transformation matrix is null.
/// </summary>
QTEST_CASE ( Transform2_VectorIsNullWhenTransformationMatrixIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    const QVector2 VECTOR = QVector2(SQFloat::_1, SQFloat::_2);
    const QTransformationMatrix3x3 NULL_MATRIX = reinterpret_cast<const QTransformationMatrix3x3 &> (QMatrix3x3::GetZeroMatrix());
    const QVector2 EXPECTED_RESULT = QVector2::GetZeroVector();

	// Execution
    QVector2 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the string returned is the expected one.
/// </summary>
QTEST_CASE ( ToString_StringIsCorrectlyGenerated_Test )
{
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    // Preparation
    const string_q EXPECTED_RESULT = QE_L("V2(1,0.5)");

    const QVector2 OPERAND = QVector2(SQFloat::_1, SQFloat::_0_5);

	// Execution
    string_q fResultUT = OPERAND.ToString();

    // Verification
    BOOST_CHECK ( fResultUT == EXPECTED_RESULT );
}

// End - Test Suite: QVector2
QTEST_SUITE_END()
