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

#include "QTranslationMatrix.h"
#include "QTranslationMatrixWhiteBox.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QTransformationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;
using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
using Kinesis::QuimeraEngine::Tools::Math::Test::QTranslationMatrixWhiteBox;
using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

typedef boost::mpl::list<QMatrix4x3, QMatrix4x4> TQTemplateTypes;

QTEST_SUITE_BEGIN( QTranslationMatrix_TestSuite )

/// <summary>
/// Utility function: This function does nothing, it's intended to skip the filling of a fourth column.
/// </summary>
static void FillFourthColumnIfExists(QMatrix4x3 &matrix, const float_q &_03, const float_q &_13, const float_q &_23, const float_q &_33)
{
}

/// <summary>
/// Utility function: This function fills the fourth column of a matrix with arbitrary values.
/// </summary>
static void FillFourthColumnIfExists(QMatrix4x4 &matrix, const float_q &_03, const float_q &_13, const float_q &_23, const float_q &_33)
{
    matrix.ij[0][3] = _03;
    matrix.ij[1][3] = _13;
    matrix.ij[2][3] = _23;
    matrix.ij[3][3] = _33;
}

/// <summary>
/// Utility function: This function does nothing, it's intended to skip the ckecking of a fourth column.
/// </summary>
static void CheckFourthColumnIfExists(const QMatrix4x3 &matrixA, const QMatrix4x3 &matrixB)
{
}

/// <summary>
/// Utility function: Checks if the fourth column of 2 matrices is the same.
/// </summary>
static void CheckFourthColumnIfExists(const QMatrix4x4 &matrixA, const QMatrix4x4 &matrixB)
{
    BOOST_CHECK( SQFloat::AreEqual( matrixA.ij[0][3], matrixB.ij[0][3] ));
    BOOST_CHECK( SQFloat::AreEqual( matrixA.ij[1][3], matrixB.ij[1][3] ));
    BOOST_CHECK( SQFloat::AreEqual( matrixA.ij[2][3], matrixB.ij[2][3] ));
    BOOST_CHECK( SQFloat::AreEqual( matrixA.ij[3][3], matrixB.ij[3][3] ));
}

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaventChanged_Test, TQTemplateTypes )
{
    // Preparation
    const T EXPECTED_VALUE(QTranslationMatrix<T>::GetIdentity());

    // Execution
    QTranslationMatrix<T> matrixUT;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_EveryElementCopiedToCorrespondingElement_Test, TQTemplateTypes )
{
    // Preparation
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT(EXPECTED_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the translation matrix is correctly built from its three displacement values.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_TranslationMatrixCorrectlyBuiltFromThreeValues_Test, TQTemplateTypes )
{
    // Preparation
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that identity matrix is obtained when the three displacement values are zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_IdentityMatrixObtainedWhenThreeValuesAreZero_Test, TQTemplateTypes )
{
    // Preparation
    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTranslationMatrix<T> matrixUT(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the translation matrix is correctly built from a 3D vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_TranslationMatrixCorrectlyBuiltFrom3DVector_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    T EXPECTED_VALUE;
    const QBaseVector3 TRANSLATION(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT(TRANSLATION);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that identity matrix is obtained when the 3D vector is a zero vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_IdentityMatrixObtainedWhen3DVectorIsZeroVector_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 ZERO_VECTOR = QVector3::GetZeroVector();
	const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTranslationMatrix<T> matrixUT(ZERO_VECTOR);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the translation matrix is correctly built from a 4D vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_TranslationMatrixCorrectlyBuiltFrom4DVector_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    T EXPECTED_VALUE;
    const QBaseVector4 TRANSLATION(SQFloat::_2, SQFloat::_3, SQFloat::_4, SQFloat::_5);

    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT(TRANSLATION);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that identity matrix is obtained when the 4D vector is a zero vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_IdentityMatrixObtainedWhen4DVectorIsZeroVector_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QVector4 ZERO_VECTOR = QVector4::GetZeroVector();
	const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTranslationMatrix<T> matrixUT(ZERO_VECTOR);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that w value from a 4D vector doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_WValueFrom4DVectorDoesNotParticipate_Test, TQTemplateTypes )
{
	// Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const QBaseVector4 TRANSLATIONA(SQFloat::_2, SQFloat::_3, SQFloat::_4, SQFloat::_5);
	const QBaseVector4 TRANSLATIONB(SQFloat::_2, SQFloat::_3, SQFloat::_4, SQFloat::_9);

    // Execution
    QTranslationMatrix<T> matrixAUT(TRANSLATIONA);
	QTranslationMatrix<T> matrixBUT(TRANSLATIONB);

	// Verification
	BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test, TQTemplateTypes )
{
    // Preparation
    const T EXPECTED_VALUE = T::GetIdentity();

	// Execution
    QTranslationMatrix<T> matrixUT = QTranslationMatrix<T>::GetIdentity();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that two translation matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct1_TranslationMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    QTranslationMatrix<T> OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QTranslationMatrix<QMatrix4x3> OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    QTranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that two translation matrices product is commutative.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct1_TranslationMatricesProductIsCommutative_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    QTranslationMatrix<T> OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QTranslationMatrix<QMatrix4x3> OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    // Execution
    QTranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;
    QTranslationMatrix<QMatrix4x3> matrixUT2 = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], matrixUT2.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], matrixUT2.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], matrixUT2.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], matrixUT2.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], matrixUT2.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], matrixUT2.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], matrixUT2.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], matrixUT2.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], matrixUT2.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], matrixUT2.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], matrixUT2.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], matrixUT2.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, OPERAND1);
}

/// <summary>
/// Checks that two translation matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct2_TranslationMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    QTranslationMatrix<T> OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    QTranslationMatrix<QMatrix4x4> OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    QTranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that two translation matrices product is commutative.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct2_TranslationMatricesProductIsCommutative_Test, TQTemplateTypes )
{
   // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    QTranslationMatrix<T> OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QTranslationMatrix<QMatrix4x4> OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    // Execution
    QTranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;
    QTranslationMatrix<QMatrix4x4> matrixUT2 = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], matrixUT2.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], matrixUT2.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], matrixUT2.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], matrixUT2.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], matrixUT2.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], matrixUT2.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], matrixUT2.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], matrixUT2.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], matrixUT2.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], matrixUT2.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], matrixUT2.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], matrixUT2.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, OPERAND1);
    CheckFourthColumnIfExists(matrixUT2, OPERAND2);
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct2_FourthColumnOfLeftOperandDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<QMatrix4x4> OPERANDA1 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTranslationMatrix<T> OPERANDA2;
    OPERANDA2.ij[0][0] = SQFloat::_1;
    OPERANDA2.ij[0][1] = SQFloat::_2;
    OPERANDA2.ij[0][2] = SQFloat::_3;
    OPERANDA2.ij[1][0] = SQFloat::_4;
    OPERANDA2.ij[1][1] = SQFloat::_5;
    OPERANDA2.ij[1][2] = SQFloat::_6;
    OPERANDA2.ij[2][0] = SQFloat::_7;
    OPERANDA2.ij[2][1] = SQFloat::_8;
    OPERANDA2.ij[2][2] = SQFloat::_9;
    OPERANDA2.ij[3][0] = SQFloat::_10;
    OPERANDA2.ij[3][1] = (float_q)11.0f;
    OPERANDA2.ij[3][2] = (float_q)12.0f;

    QTranslationMatrix<QMatrix4x4> OPERANDB1 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    QTranslationMatrix<T> OPERANDB2 = OPERANDA2;

    // Execution
    QTranslationMatrix<QMatrix4x4> matrixAUT = OPERANDA1 * OPERANDA2;
    QTranslationMatrix<QMatrix4x4> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct2_FourthColumnOfRightOperandDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SQFloat::_1;
    OPERANDA1.ij[0][1] = SQFloat::_2;
    OPERANDA1.ij[0][2] = SQFloat::_3;
    OPERANDA1.ij[1][0] = SQFloat::_4;
    OPERANDA1.ij[1][1] = SQFloat::_5;
    OPERANDA1.ij[1][2] = SQFloat::_6;
    OPERANDA1.ij[2][0] = SQFloat::_7;
    OPERANDA1.ij[2][1] = SQFloat::_8;
    OPERANDA1.ij[2][2] = SQFloat::_9;
    OPERANDA1.ij[3][0] = SQFloat::_10;
    OPERANDA1.ij[3][1] = (float_q)11.0f;
    OPERANDA1.ij[3][2] = (float_q)12.0f;

    QTranslationMatrix<QMatrix4x4> OPERANDA2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTranslationMatrix<T> OPERANDB1 = OPERANDA1;

    QTranslationMatrix<QMatrix4x4> OPERANDB2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    // Execution
    QTranslationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    QTranslationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that a translation matrix and a 3x3 scale matrix are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct3_TranslationMatrixAnd3x3ScaleMatrixAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_3);

    QTranslationMatrix<T> OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_10;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT = OPERAND1 * SCALE;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that only the diagonal of the scaling matrix participates in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct3_OnlyTheDiagonalOfScalingMatrixMatters_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    QTranslationMatrix<T> OPERANDA1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    QScalingMatrix3x3 OPERANDA2;
    OPERANDA2.ij[0][0] = (float_q)17.0f;
    OPERANDA2.ij[0][1] = (float_q)18.0f;
    OPERANDA2.ij[0][2] = (float_q)19.0f;
    OPERANDA2.ij[1][0] = (float_q)20.0f;
    OPERANDA2.ij[1][1] = (float_q)21.0f;
    OPERANDA2.ij[1][2] = (float_q)22.0f;
    OPERANDA2.ij[2][0] = (float_q)23.0f;
    OPERANDA2.ij[2][1] = (float_q)24.0f;
    OPERANDA2.ij[2][2] = (float_q)25.0f;

    QTranslationMatrix<T> OPERANDB1 = OPERANDA1;

    QScalingMatrix3x3 OPERANDB2;
    OPERANDB2.ij[0][0] = (float_q)17.0f;
    OPERANDB2.ij[0][1] = (float_q)26.0f;
    OPERANDB2.ij[0][2] = (float_q)27.0f;
    OPERANDB2.ij[1][0] = (float_q)28.0f;
    OPERANDB2.ij[1][1] = (float_q)21.0f;
    OPERANDB2.ij[1][2] = (float_q)29.0f;
    OPERANDB2.ij[2][0] = (float_q)30.0f;
    OPERANDB2.ij[2][1] = (float_q)31.0f;
    OPERANDB2.ij[2][2] = (float_q)25.0f;

    // Execution
    QTransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    QTransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE( OperatorProduct3_FourthColumnOfLeftOperandDoesntMatter )
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_3);

    QTranslationMatrix<QMatrix4x4> OPERANDA1(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    FillFourthColumnIfExists(OPERANDA1, SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QTranslationMatrix<QMatrix4x4> OPERANDB1 = OPERANDA1;
    FillFourthColumnIfExists(OPERANDB1, SQFloat::_2, SQFloat::_3, SQFloat::_4, SQFloat::_5);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixAUT = OPERANDA1 * SCALE;
    QTransformationMatrix<QMatrix4x4> matrixBUT = OPERANDB1 * SCALE;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that a translation matrix and a 3x3 rotation matrix are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct4_TranslationMatrixAnd3x3RotationMatrixAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    QTranslationMatrix<T> OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    QRotationMatrix3x3 ROTATION;
    ROTATION.ij[0][0] = (float_q)10.0f;
    ROTATION.ij[0][1] = (float_q)11.0f;
    ROTATION.ij[0][2] = (float_q)12.0f;
    ROTATION.ij[1][0] = (float_q)13.0f;
    ROTATION.ij[1][1] = (float_q)14.0f;
    ROTATION.ij[1][2] = (float_q)15.0f;
    ROTATION.ij[2][0] = (float_q)16.0f;
    ROTATION.ij[2][1] = (float_q)17.0f;
    ROTATION.ij[2][2] = (float_q)18.0f;

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)10.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)11.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)12.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)13.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)14.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)15.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)16.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)17.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)18.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)84.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)90.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)96.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT = OPERAND1 * ROTATION;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE( OperatorProduct4_FourthColumnOfLeftOperandDoesntMatter )
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    QRotationMatrix3x3 ROTATION;
    ROTATION.ij[0][0] = (float_q)10.0f;
    ROTATION.ij[0][1] = (float_q)11.0f;
    ROTATION.ij[0][2] = (float_q)12.0f;
    ROTATION.ij[1][0] = (float_q)13.0f;
    ROTATION.ij[1][1] = (float_q)14.0f;
    ROTATION.ij[1][2] = (float_q)15.0f;
    ROTATION.ij[2][0] = (float_q)16.0f;
    ROTATION.ij[2][1] = (float_q)17.0f;
    ROTATION.ij[2][2] = (float_q)18.0f;

    QTranslationMatrix<QMatrix4x4> OPERANDA1(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    FillFourthColumnIfExists(OPERANDA1, SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QTranslationMatrix<QMatrix4x4> OPERANDB1 = OPERANDA1;
    FillFourthColumnIfExists(OPERANDB1, SQFloat::_2, SQFloat::_3, SQFloat::_4, SQFloat::_5);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixAUT = OPERANDA1 * ROTATION;
    QTransformationMatrix<QMatrix4x4> matrixBUT = OPERANDB1 * ROTATION;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that a translation matrix and a transformation matrix are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct5_TranslationMatrixAndTransformationMatrixAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTranslationMatrix<T> OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    QTransformationMatrix<T> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_4;
    OPERAND2.ij[0][1] = SQFloat::_1;
    OPERAND2.ij[0][2] = SQFloat::_2;
    OPERAND2.ij[1][0] = SQFloat::_3;
    OPERAND2.ij[1][1] = SQFloat::_5;
    OPERAND2.ij[1][2] = SQFloat::_4;
    OPERAND2.ij[2][0] = SQFloat::_5;
    OPERAND2.ij[2][1] = SQFloat::_6;
    OPERAND2.ij[2][2] = SQFloat::_3;
    OPERAND2.ij[3][0] = SQFloat::_4;
    OPERAND2.ij[3][1] = SQFloat::_10;
    OPERAND2.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_2;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_3;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_4;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_6;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][0] = (float_q)29.0;
    EXPECTED_VALUE.ij[3][1] = (float_q)39.0;
    EXPECTED_VALUE.ij[3][2] = (float_q)28.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE( OperatorProduct5_FourthColumnOfLeftOperandDoesntMatter, TQTemplateTypes )
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTranslationMatrix<QMatrix4x4> OPERANDA1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    QTransformationMatrix<T> OPERANDA2;
    OPERANDA2.ij[0][0] = SQFloat::_4;
    OPERANDA2.ij[0][1] = SQFloat::_0;
    OPERANDA2.ij[0][2] = SQFloat::_0;
    OPERANDA2.ij[1][0] = SQFloat::_0;
    OPERANDA2.ij[1][1] = SQFloat::_5;
    OPERANDA2.ij[1][2] = SQFloat::_0;
    OPERANDA2.ij[2][0] = SQFloat::_0;
    OPERANDA2.ij[2][1] = SQFloat::_0;
    OPERANDA2.ij[2][2] = SQFloat::_3;
    OPERANDA2.ij[3][0] = SQFloat::_4;
    OPERANDA2.ij[3][1] = SQFloat::_10;
    OPERANDA2.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(OPERANDA2, SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QTranslationMatrix<QMatrix4x4> OPERANDB1 = OPERANDA1;
    FillFourthColumnIfExists(OPERANDB1, SQFloat::_2, SQFloat::_3, SQFloat::_4, SQFloat::_5);

    QTransformationMatrix<T> OPERANDB2 = OPERANDA2;

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixAUT = OPERANDA1 * OPERANDA2;
    QTransformationMatrix<QMatrix4x4> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE( OperatorProduct5_FourthColumnOfRightOperandDoesntMatter, TQTemplateTypes )
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QTranslationMatrix<QMatrix4x4> OPERANDA1(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    QTransformationMatrix<T> OPERANDA2;
    OPERANDA2.ij[0][0] = SQFloat::_4;
    OPERANDA2.ij[0][1] = SQFloat::_0;
    OPERANDA2.ij[0][2] = SQFloat::_0;
    OPERANDA2.ij[1][0] = SQFloat::_0;
    OPERANDA2.ij[1][1] = SQFloat::_5;
    OPERANDA2.ij[1][2] = SQFloat::_0;
    OPERANDA2.ij[2][0] = SQFloat::_0;
    OPERANDA2.ij[2][1] = SQFloat::_0;
    OPERANDA2.ij[2][2] = SQFloat::_3;
    OPERANDA2.ij[3][0] = SQFloat::_4;
    OPERANDA2.ij[3][1] = SQFloat::_10;
    OPERANDA2.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(OPERANDA2, SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QTranslationMatrix<QMatrix4x4> OPERANDB1 = OPERANDA1;

    QTransformationMatrix<T> OPERANDB2 = OPERANDA2;
    FillFourthColumnIfExists(OPERANDB2, SQFloat::_2, SQFloat::_3, SQFloat::_4, SQFloat::_5);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixAUT = OPERANDA1 * OPERANDA2;
    QTransformationMatrix<QMatrix4x4> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that product assignation operator works in the right way.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation1_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_2;
    OPERAND1.ij[3][1] = SQFloat::_3;
    OPERAND1.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = SQFloat::_3;
    OPERAND2.ij[3][1] = SQFloat::_4;
    OPERAND2.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a 4x3 translation matrix can be multiplied by itself (same object instance).
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_CanBeMultipliedByItself_Test )
{
     // Preparation
    QTranslationMatrix<QMatrix4x3> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_2;
    OPERAND1.ij[3][1] = SQFloat::_3;
    OPERAND1.ij[3][2] = SQFloat::_4;

    QTranslationMatrix<QMatrix4x3> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_6;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_8;

    // Execution
    QTranslationMatrix<QMatrix4x3> matrixUT = OPERAND1;
    matrixUT *= OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <summary>
/// Checks if this is a commutative operation (using a 4x3 translation matrix operator).
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation1_IsCommutative_Test, TQTemplateTypes )
{
     // Preparation
    QTranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_2;
    OPERAND1.ij[3][1] = SQFloat::_3;
    OPERAND1.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = SQFloat::_3;
    OPERAND2.ij[3][1] = SQFloat::_4;
    OPERAND2.ij[3][2] = SQFloat::_5;

    // Execution
    QTranslationMatrix<T> matrixAUT = OPERAND1;
    matrixAUT *= OPERAND2;
    QTranslationMatrix<QMatrix4x3> matrixBUT = OPERAND2;
    matrixBUT *= OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[0][0], matrixBUT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[0][1], matrixBUT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[0][2], matrixBUT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[1][0], matrixBUT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[1][1], matrixBUT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[1][2], matrixBUT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[2][0], matrixBUT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[2][1], matrixBUT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[2][2], matrixBUT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[3][0], matrixBUT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[3][1], matrixBUT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[3][2], matrixBUT.ij[3][2]) );
    CheckFourthColumnIfExists(matrixAUT, OPERAND1);
}

/// <summary>
/// Checks that a 4x4 translation matrix can be multiplied by itself (same object instance).
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_CanBeMultipliedByItself_Test )
{
     // Preparation
    QTranslationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_2;
    OPERAND1.ij[3][1] = SQFloat::_3;
    OPERAND1.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x4> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_6;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_8;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<QMatrix4x4> matrixUT = OPERAND1;
    matrixUT *= OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks if this is a commutative operation (using a 4x4 translation matrix operator).
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation2_IsCommutative_Test, TQTemplateTypes )
{
     // Preparation
    QTranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_2;
    OPERAND1.ij[3][1] = SQFloat::_3;
    OPERAND1.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = SQFloat::_3;
    OPERAND2.ij[3][1] = SQFloat::_4;
    OPERAND2.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixAUT = OPERAND1;
    matrixAUT *= OPERAND2;
    QTranslationMatrix<QMatrix4x4> matrixBUT = OPERAND2;
    matrixBUT *= OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[0][0], matrixBUT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[0][1], matrixBUT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[0][2], matrixBUT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[1][0], matrixBUT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[1][1], matrixBUT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[1][2], matrixBUT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[2][0], matrixBUT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[2][1], matrixBUT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[2][2], matrixBUT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[3][0], matrixBUT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[3][1], matrixBUT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixAUT.ij[3][2], matrixBUT.ij[3][2]) );
    CheckFourthColumnIfExists(matrixAUT, OPERAND1);
    CheckFourthColumnIfExists(matrixBUT, OPERAND2);
}

/// <summary>
/// Checks that product assignation operator works in the right way.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation3_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_2;
    OPERAND1.ij[3][1] = SQFloat::_3;
    OPERAND1.ij[3][2] = SQFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = SQFloat::_3;
    OPERAND2.ij[3][1] = SQFloat::_4;
    OPERAND2.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation4_FourthColumnOfRightOperandDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SQFloat::_1;
    OPERANDA1.ij[0][1] = SQFloat::_0;
    OPERANDA1.ij[0][2] = SQFloat::_0;
    OPERANDA1.ij[1][0] = SQFloat::_0;
    OPERANDA1.ij[1][1] = SQFloat::_1;
    OPERANDA1.ij[1][2] = SQFloat::_0;
    OPERANDA1.ij[2][0] = SQFloat::_0;
    OPERANDA1.ij[2][1] = SQFloat::_0;
    OPERANDA1.ij[2][2] = SQFloat::_1;
    OPERANDA1.ij[3][0] = SQFloat::_3;
    OPERANDA1.ij[3][1] = SQFloat::_4;
    OPERANDA1.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(OPERANDA1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x4> OPERANDA2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                         (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                         (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTranslationMatrix<T> OPERANDB1 = OPERANDA1;

    QTranslationMatrix<QMatrix4x4> OPERANDB2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                         (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                         (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    // Execution
    QTranslationMatrix<T> matrixAUT = OPERANDA1;
    matrixAUT *= OPERANDA2;
    QTranslationMatrix<T> matrixBUT = OPERANDB1;
    matrixBUT *= OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that only the third first elements of the fourth row of the operands participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation5_OnlyFourthRowElementsOfOperandsParticipate_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SQFloat::_1;
    OPERANDA1.ij[0][1] = SQFloat::_0;
    OPERANDA1.ij[0][2] = SQFloat::_0;
    OPERANDA1.ij[1][0] = SQFloat::_0;
    OPERANDA1.ij[1][1] = SQFloat::_1;
    OPERANDA1.ij[1][2] = SQFloat::_0;
    OPERANDA1.ij[2][0] = SQFloat::_0;
    OPERANDA1.ij[2][1] = SQFloat::_0;
    OPERANDA1.ij[2][2] = SQFloat::_1;
    OPERANDA1.ij[3][0] = SQFloat::_3;
    OPERANDA1.ij[3][1] = SQFloat::_4;
    OPERANDA1.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(OPERANDA1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x4> OPERANDA2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                         (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                         (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTranslationMatrix<T> OPERANDB1 = OPERANDA1;

    QTranslationMatrix<QMatrix4x4> OPERANDB2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)7.0f, (float_q)8.0f, (float_q)9.0f, (float_q)7.0f,
                                                                                         (float_q)2.0f, (float_q)1.0f, (float_q)2.0f, (float_q)8.0f,
                                                                                         (float_q)3.0f, (float_q)4.0f, (float_q)5.0f, (float_q)3.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    // Execution
    QTranslationMatrix<T> matrixAUT = OPERANDA1;
    matrixAUT *= OPERANDA2;
    QTranslationMatrix<T> matrixBUT = OPERANDB1;
    matrixBUT *= OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_9;
    MATRIX.ij[3][0] = SQFloat::_10;
    MATRIX.ij[3][1] = (float_q)11.0f;
    MATRIX.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    const QTranslationMatrix<T> EXPECTED_VALUE = MATRIX;

    // Execution
    QTranslationMatrix<T> matrixUT;
    matrixUT = MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the translation matrix is correctly inverted.
/// </summary>
QTEST_CASE_TEMPLATE ( Invert_TranslationMatrixIsCorrectlyInverted_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_0;
    MATRIX.ij[0][2] = SQFloat::_0;
    MATRIX.ij[1][0] = SQFloat::_0;
    MATRIX.ij[1][1] = SQFloat::_1;
    MATRIX.ij[1][2] = SQFloat::_0;
    MATRIX.ij[2][0] = SQFloat::_0;
    MATRIX.ij[2][1] = SQFloat::_0;
    MATRIX.ij[2][2] = SQFloat::_1;
    MATRIX.ij[3][0] = SQFloat::_3;
    MATRIX.ij[3][1] = SQFloat::_4;
    MATRIX.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = -SQFloat::_3;
    EXPECTED_VALUE.ij[3][1] = -SQFloat::_4;
    EXPECTED_VALUE.ij[3][2] = -SQFloat::_5;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrix<T> matrixUT = MATRIX.Invert();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column (when using 4x4 matrices) doesn't participate in the invert operation.
/// </summary>
QTEST_CASE ( Invert_FourthColumnDoesntParticipate_Test )
{
    // Preparation
    QTranslationMatrix<QMatrix4x4> MATRIX1;
    MATRIX1.ij[0][0] = SQFloat::_1;
    MATRIX1.ij[0][1] = SQFloat::_0;
    MATRIX1.ij[0][2] = SQFloat::_0;
    MATRIX1.ij[1][0] = SQFloat::_0;
    MATRIX1.ij[1][1] = SQFloat::_1;
    MATRIX1.ij[1][2] = SQFloat::_0;
    MATRIX1.ij[2][0] = SQFloat::_0;
    MATRIX1.ij[2][1] = SQFloat::_0;
    MATRIX1.ij[2][2] = SQFloat::_1;
    MATRIX1.ij[3][0] = SQFloat::_3;
    MATRIX1.ij[3][1] = SQFloat::_4;
    MATRIX1.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<QMatrix4x4> MATRIX2;
    MATRIX2.ij[0][0] = SQFloat::_1;
    MATRIX2.ij[0][1] = SQFloat::_0;
    MATRIX2.ij[0][2] = SQFloat::_0;
    MATRIX2.ij[1][0] = SQFloat::_0;
    MATRIX2.ij[1][1] = SQFloat::_1;
    MATRIX2.ij[1][2] = SQFloat::_0;
    MATRIX2.ij[2][0] = SQFloat::_0;
    MATRIX2.ij[2][1] = SQFloat::_0;
    MATRIX2.ij[2][2] = SQFloat::_1;
    MATRIX2.ij[3][0] = SQFloat::_3;
    MATRIX2.ij[3][1] = SQFloat::_4;
    MATRIX2.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX2, SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    // Execution
    QTranslationMatrix<QMatrix4x4> matrixAUT = MATRIX1.Invert();
    QTranslationMatrix<QMatrix4x4> matrixBUT = MATRIX2.Invert();

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

// <summary>
/// Checks that it returns always True.
/// </summary>
QTEST_CASE_TEMPLATE ( HasInverse_AlwaysReturnsTrue_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> MATRIX1;
    MATRIX1.ij[0][0] = SQFloat::_1;
    MATRIX1.ij[0][1] = SQFloat::_0;
    MATRIX1.ij[0][2] = SQFloat::_0;
    MATRIX1.ij[1][0] = SQFloat::_0;
    MATRIX1.ij[1][1] = SQFloat::_1;
    MATRIX1.ij[1][2] = SQFloat::_0;
    MATRIX1.ij[2][0] = SQFloat::_0;
    MATRIX1.ij[2][1] = SQFloat::_0;
    MATRIX1.ij[2][2] = SQFloat::_1;
    MATRIX1.ij[3][0] = SQFloat::_3;
    MATRIX1.ij[3][1] = SQFloat::_4;
    MATRIX1.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<T> MATRIX2;
    MATRIX2.ij[0][0] = SQFloat::_1;
    MATRIX2.ij[0][1] = SQFloat::_2;
    MATRIX2.ij[0][2] = SQFloat::_3;
    MATRIX2.ij[1][0] = SQFloat::_4;
    MATRIX2.ij[1][1] = SQFloat::_5;
    MATRIX2.ij[1][2] = SQFloat::_6;
    MATRIX2.ij[2][0] = SQFloat::_7;
    MATRIX2.ij[2][1] = SQFloat::_8;
    MATRIX2.ij[2][2] = SQFloat::_9;
    MATRIX2.ij[3][0] = SQFloat::_10;
    MATRIX2.ij[3][1] = (float_q)11.0f;
    MATRIX2.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX2, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bResultAUT = MATRIX1.HasInverse();
    bool bResultBUT = MATRIX2.HasInverse();

    // Verification
    BOOST_CHECK_EQUAL(bResultAUT, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bResultBUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that 3 translation values are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation1_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_0;
    MATRIX.ij[0][2] = SQFloat::_0;
    MATRIX.ij[1][0] = SQFloat::_0;
    MATRIX.ij[1][1] = SQFloat::_1;
    MATRIX.ij[1][2] = SQFloat::_0;
    MATRIX.ij[2][0] = SQFloat::_0;
    MATRIX.ij[2][1] = SQFloat::_0;
    MATRIX.ij[2][2] = SQFloat::_1;
    MATRIX.ij[3][0] = SQFloat::_3;
    MATRIX.ij[3][1] = SQFloat::_4;
    MATRIX.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    const float_q EXPECTED_VALUE_X = MATRIX.ij[3][0];
    const float_q EXPECTED_VALUE_Y = MATRIX.ij[3][1];
    const float_q EXPECTED_VALUE_Z = MATRIX.ij[3][2];

    // Execution
    float_q fTranslationXUT = SQFloat::_0;
    float_q fTranslationYUT = SQFloat::_0;
    float_q fTranslationZUT = SQFloat::_0;
    MATRIX.GetTranslation(fTranslationXUT, fTranslationYUT, fTranslationZUT);

    // Verification
    BOOST_CHECK_EQUAL(fTranslationXUT, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(fTranslationYUT, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(fTranslationZUT, EXPECTED_VALUE_Z);
}

/// <summary>
/// Checks that 3 translation values equal zero when transformation matrix is the identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation1_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> MATRIX = T::GetIdentity();

    const float_q EXPECTED_VALUE_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_Z = SQFloat::_0;

    // Execution
    float_q fTranslationXUT = SQFloat::_1;
    float_q fTranslationYUT = SQFloat::_1;
    float_q fTranslationZUT = SQFloat::_1;
    MATRIX.GetTranslation(fTranslationXUT, fTranslationYUT, fTranslationZUT);

    // Verification
    BOOST_CHECK_EQUAL(fTranslationXUT, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(fTranslationYUT, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(fTranslationZUT, EXPECTED_VALUE_Z);
}

/// <summary>
/// Checks that translation vector is correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation2_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    QTranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_0;
    MATRIX.ij[0][2] = SQFloat::_0;
    MATRIX.ij[1][0] = SQFloat::_0;
    MATRIX.ij[1][1] = SQFloat::_1;
    MATRIX.ij[1][2] = SQFloat::_0;
    MATRIX.ij[2][0] = SQFloat::_0;
    MATRIX.ij[2][1] = SQFloat::_0;
    MATRIX.ij[2][2] = SQFloat::_1;
    MATRIX.ij[3][0] = SQFloat::_3;
    MATRIX.ij[3][1] = SQFloat::_4;
    MATRIX.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    const QBaseVector3 EXPECTED_VALUE(MATRIX.ij[3][0], MATRIX.ij[3][1], MATRIX.ij[3][2]);

    // Execution
    QBaseVector3 vTranslationUT(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    MATRIX.GetTranslation(vTranslationUT);

    // Verification
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that 3 translation values equal zero when translation matrix is the identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation2_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    QTranslationMatrix<T> MATRIX = T::GetIdentity();

    const QBaseVector3 EXPECTED_VALUE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    // Execution
    QBaseVector3 vTranslationUT(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    MATRIX.GetTranslation(vTranslationUT);

    // Verification
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that translation vector is correctly extracted from a common translation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    QTranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_0;
    MATRIX.ij[0][2] = SQFloat::_0;
    MATRIX.ij[1][0] = SQFloat::_0;
    MATRIX.ij[1][1] = SQFloat::_1;
    MATRIX.ij[1][2] = SQFloat::_0;
    MATRIX.ij[2][0] = SQFloat::_0;
    MATRIX.ij[2][1] = SQFloat::_0;
    MATRIX.ij[2][2] = SQFloat::_1;
    MATRIX.ij[3][0] = SQFloat::_3;
    MATRIX.ij[3][1] = SQFloat::_4;
    MATRIX.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    const QBaseVector4 EXPECTED_VALUE(MATRIX.ij[3][0], MATRIX.ij[3][1], MATRIX.ij[3][2], SQFloat::_0);

    // Execution
    QBaseVector4 vTranslationUT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // Verification
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
    BOOST_CHECK_EQUAL(vTranslationUT.w, EXPECTED_VALUE.w);
}

/// <summary>
/// Checks that w value of the translation vector is always zero.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation3_WValueIsAlwaysZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    QTranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_9;
    MATRIX.ij[3][0] = SQFloat::_3;
    MATRIX.ij[3][1] = SQFloat::_4;
    MATRIX.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<T> MATRIX2 = MATRIX;
    MATRIX2.ij[3][0] = -SQFloat::_1;
    MATRIX2.ij[3][1] = -SQFloat::_2;
    MATRIX2.ij[3][2] = -SQFloat::_3;

    const float_q EXPECTED_VALUE = SQFloat::_0;

    // Execution
    QBaseVector4 vTranslationUT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);
    float_q fWValue = vTranslationUT.w;

    QBaseVector4 vTranslationUT2(SQFloat::_3, SQFloat::_4, SQFloat::_5, SQFloat::_6);
    MATRIX2.GetTranslation(vTranslationUT2);
    float_q fWValue2 = vTranslationUT2.w;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fWValue, EXPECTED_VALUE) );
    BOOST_CHECK( SQFloat::AreEqual(fWValue2, EXPECTED_VALUE) );
}

/// <summary>
/// Checks that 3 translation values equal zero when translation matrix is the identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    QTranslationMatrix<T> MATRIX = T::GetIdentity();

    const QBaseVector4 EXPECTED_VALUE(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    // Execution
    QBaseVector4 vTranslationUT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // Verification
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
    BOOST_CHECK_EQUAL(vTranslationUT.w, EXPECTED_VALUE.w);
}

QTEST_CASE_TEMPLATE ( GetDeterminant_ResultIsAlwaysOne_Test, TQTemplateTypes )
{
    // Preparation
    QTranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_9;
    MATRIX.ij[3][0] = SQFloat::_3;
    MATRIX.ij[3][1] = SQFloat::_4;
    MATRIX.ij[3][2] = SQFloat::_5;
    FillFourthColumnIfExists(MATRIX, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    const float_q EXPECTED_VALUE = 1;

    // Execution
    float_q fDeterminant = MATRIX.GetDeterminant();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fDeterminant, EXPECTED_VALUE) );
}

/// <summary>
/// Template method used by ProductOperatorImp_MatricesAreCorrectlyMultiplied_Test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductOperatorImp_MatricesAreCorrectlyMultiplied_Template()
{
    // Preparation
    QTranslationMatrixWhiteBox<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_1;
    OPERAND1.ij[3][1] = SQFloat::_2;
    OPERAND1.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<MatrixType> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = SQFloat::_4;
    OPERAND2.ij[3][1] = SQFloat::_5;
    OPERAND2.ij[3][2] = SQFloat::_6;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrixWhiteBox<T> OPERATOR1_MATRIX(OPERAND1);
    QTranslationMatrix<T> matrixUT = OPERATOR1_MATRIX.template ProductOperatorImp<MatrixType>(OPERAND2);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that two translation matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductOperatorImp_MatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp_MatricesAreCorrectlyMultiplied_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp_MatricesAreCorrectlyMultiplied_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by ProductOperatorImp_TranslationMatricesProductIsCommutative_Test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductOperatorImp_TranslationMatricesProductIsCommutative_Template()
{
    // Preparation
    QTranslationMatrixWhiteBox<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_1;
    OPERAND1.ij[3][1] = SQFloat::_2;
    OPERAND1.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<MatrixType> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = -SQFloat::_4;
    OPERAND2.ij[3][1] = -SQFloat::_5;
    OPERAND2.ij[3][2] = -SQFloat::_6;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrixWhiteBox<T> OPERATOR1_MATRIX(OPERAND1);
    QTranslationMatrix<T> matrixUT = OPERATOR1_MATRIX.template ProductOperatorImp<MatrixType>(OPERAND2);

    QTranslationMatrixWhiteBox<MatrixType> OPERATOR2_MATRIX(OPERAND2);
    QTranslationMatrix<MatrixType> matrixUT2 = OPERATOR2_MATRIX.template ProductOperatorImp<T>(OPERAND1);

     // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], matrixUT2.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], matrixUT2.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], matrixUT2.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], matrixUT2.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], matrixUT2.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], matrixUT2.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], matrixUT2.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], matrixUT2.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], matrixUT2.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], matrixUT2.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], matrixUT2.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], matrixUT2.ij[3][2]) );
}

/// <summary>
/// Checks that product between translation matrices is commutative.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductOperatorImp_TranslationMatricesProductIsCommutative_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp_TranslationMatricesProductIsCommutative_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp_TranslationMatricesProductIsCommutative_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Template()
{
    // Preparation
    QTranslationMatrixWhiteBox<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_1;
    OPERAND1.ij[3][1] = SQFloat::_2;
    OPERAND1.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<MatrixType> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = SQFloat::_4;
    OPERAND2.ij[3][1] = SQFloat::_5;
    OPERAND2.ij[3][2] = SQFloat::_6;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrixWhiteBox<T> matrixUT(OPERAND1);
    matrixUT.template ProductAssignationOperatorImp<MatrixType>(OPERAND2);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that product assignation operator works in the right way.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by ProductAssignationOperatorImp_IsCommutative_Test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductAssignationOperatorImp_IsCommutative_Template()
{
    // Preparation
    QTranslationMatrixWhiteBox<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_0;
    OPERAND1.ij[0][2] = SQFloat::_0;
    OPERAND1.ij[1][0] = SQFloat::_0;
    OPERAND1.ij[1][1] = SQFloat::_1;
    OPERAND1.ij[1][2] = SQFloat::_0;
    OPERAND1.ij[2][0] = SQFloat::_0;
    OPERAND1.ij[2][1] = SQFloat::_0;
    OPERAND1.ij[2][2] = SQFloat::_1;
    OPERAND1.ij[3][0] = SQFloat::_1;
    OPERAND1.ij[3][1] = SQFloat::_2;
    OPERAND1.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(OPERAND1, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    QTranslationMatrix<MatrixType> OPERAND2;
    OPERAND2.ij[0][0] = SQFloat::_1;
    OPERAND2.ij[0][1] = SQFloat::_0;
    OPERAND2.ij[0][2] = SQFloat::_0;
    OPERAND2.ij[1][0] = SQFloat::_0;
    OPERAND2.ij[1][1] = SQFloat::_1;
    OPERAND2.ij[1][2] = SQFloat::_0;
    OPERAND2.ij[2][0] = SQFloat::_0;
    OPERAND2.ij[2][1] = SQFloat::_0;
    OPERAND2.ij[2][2] = SQFloat::_1;
    OPERAND2.ij[3][0] = -SQFloat::_4;
    OPERAND2.ij[3][1] = -SQFloat::_5;
    OPERAND2.ij[3][2] = -SQFloat::_6;
    FillFourthColumnIfExists(OPERAND2, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTranslationMatrixWhiteBox<T> matrixUT(OPERAND1);
    matrixUT.template ProductAssignationOperatorImp<MatrixType>(OPERAND2);

    QTranslationMatrixWhiteBox<MatrixType> matrixUT2(OPERAND2);
    matrixUT2.template ProductAssignationOperatorImp<T>(OPERAND1);

     // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], matrixUT2.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], matrixUT2.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], matrixUT2.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], matrixUT2.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], matrixUT2.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], matrixUT2.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], matrixUT2.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], matrixUT2.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], matrixUT2.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], matrixUT2.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], matrixUT2.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], matrixUT2.ij[3][2]) );
}

/// <summary>
/// Checks if this is a commutative operation.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductAssignationOperatorImp_IsCommutative_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductAssignationOperatorImp_IsCommutative_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductAssignationOperatorImp_IsCommutative_Template<T, QMatrix4x4>();
}

// End - Test Suite: QTranslationMatrix
QTEST_SUITE_END()
