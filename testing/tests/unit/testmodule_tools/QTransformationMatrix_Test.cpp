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

#include "QTransformationMatrix.h"
#include "QTransformationMatrixWhiteBox.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QQuaternion.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
using Kinesis::QuimeraEngine::Tools::Math::Test::QTransformationMatrixWhiteBox;
using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

typedef boost::mpl::list<QMatrix4x3, QMatrix4x4> TQTemplateTypes;

QTEST_SUITE_BEGIN( QTransformationMatrix_TestSuite )

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
    const T EXPECTED_VALUE(QTransformationMatrix<T>::GetIdentity());

    // Execution
    QTransformationMatrix<T> matrixUT;

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
/// Checks if copy constructor copies every matrix element properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_EveryMatrixElementCopiedProperly_Test, TQTemplateTypes )
{
    // Preparation
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_6;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_7;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_9;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_10;
    EXPECTED_VALUE.ij[2][2] = (float_q)11.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)13.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)14.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)15.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)23.0f);

    const QTransformationMatrix<T> MATRIX_TO_COPY(EXPECTED_VALUE);

    // Execution
    QTransformationMatrix<T> matrixUT = MATRIX_TO_COPY;

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
QTEST_CASE_TEMPLATE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test, TQTemplateTypes )
{
    // Preparation
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_5;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_6;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_7;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_9;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_10;
    EXPECTED_VALUE.ij[2][2] = (float_q)11.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)13.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)14.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)15.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)23.0f);

    // Execution
    QTransformationMatrix<T> matrixUT(EXPECTED_VALUE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QBaseVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_CorrectResultObtainedWhenOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion ROTATION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_CorrectResultObtainedWhenOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseVector3 SCALE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    T EXPECTED_VALUE = T::GetZeroMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ResultIsDifferentDependingOnQuaternionNormalization_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion NOT_NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixFromNormalizedQuaternionUT(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    QTransformationMatrix<T> matrixFromNotNormalizedQuaternionUT(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // Verification
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_FollowsLeftHandedRules_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    const QTransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, QQuaternion(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0), SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, QQuaternion(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0), SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, QQuaternion(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE), SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_CompositionOrderIsScaleRotationTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QTransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, QQuaternion::GetIdentity(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<T> ROTATION_MATRIX(QVector3::GetZeroVector(), ROTATION, QVector3::GetVectorOfOnes());
    const QTransformationMatrix<T> SCALE_MATRIX(QVector3::GetZeroVector(), QQuaternion::GetIdentity(), SCALE);

    const QTransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QTransformationMatrix<T> matrixUT = QTransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector4 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QBaseQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QBaseVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector4 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_CorrectResultObtainedWhenOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QQuaternion ROTATION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_CorrectResultObtainedWhenOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseVector3 SCALE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    T EXPECTED_VALUE = T::GetZeroMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_ResultIsDifferentDependingOnQuaternionNormalization_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QQuaternion NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion NOT_NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixFromNormalizedQuaternionUT(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    QTransformationMatrix<T> matrixFromNotNormalizedQuaternionUT(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // Verification
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_FollowsLeftHandedRules_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    const QTransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, QQuaternion(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0), SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, QQuaternion(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0), SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, QQuaternion(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE), SCALE);

    const QVector4 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1, SQFloat::_1);
    const QVector4 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1, SQFloat::_1);
    const QVector4 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    const QVector4 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_1);
    const QVector4 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector4 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_1);

    // Execution
    QVector4 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector4 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector4 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_CompositionOrderIsScaleRotationTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QVector4 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QTransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, QQuaternion::GetIdentity(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<T> ROTATION_MATRIX(QVector4::GetZeroVector(), ROTATION, QVector3::GetVectorOfOnes());
    const QTransformationMatrix<T> SCALE_MATRIX(QVector4::GetZeroVector(), QQuaternion::GetIdentity(), SCALE);

    const QTransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QTransformationMatrix<T> matrixUT = QTransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the same result is obtained whether the translation vector's fourth component equals zero or one.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_FourthComponentOfTranslationVectorDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector4 TRANSLATION_W_ONE(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1);
    const QBaseVector4 TRANSLATION_W_ZERO(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QBaseVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    // Execution
    QTransformationMatrix<T> matrixVectorWOneUT(TRANSLATION_W_ONE, ROTATION, SCALE);
    QTransformationMatrix<T> matrixVectorWZeroUT(TRANSLATION_W_ZERO, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[0][0], matrixVectorWZeroUT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[0][1], matrixVectorWZeroUT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[0][2], matrixVectorWZeroUT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[1][0], matrixVectorWZeroUT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[1][1], matrixVectorWZeroUT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[1][2], matrixVectorWZeroUT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[2][0], matrixVectorWZeroUT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[2][1], matrixVectorWZeroUT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[2][2], matrixVectorWZeroUT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[3][0], matrixVectorWZeroUT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[3][1], matrixVectorWZeroUT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixVectorWOneUT.ij[3][2], matrixVectorWZeroUT.ij[3][2]) );
    CheckFourthColumnIfExists(matrixVectorWOneUT, matrixVectorWZeroUT);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QBaseVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_CorrectResultObtainedWhenOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion ROTATION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_CorrectResultObtainedWhenOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseVector3 SCALE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    T EXPECTED_VALUE = T::GetZeroMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_ResultIsDifferentDependingOnQuaternionNormalization_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion NOT_NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixFromNormalizedQuaternionUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                              NORMALIZED_QUATERNION.x, NORMALIZED_QUATERNION.y, NORMALIZED_QUATERNION.z, NORMALIZED_QUATERNION.w,
                                                              SCALE.x, SCALE.y, SCALE.z);
    QTransformationMatrix<T> matrixFromNotNormalizedQuaternionUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                                 NOT_NORMALIZED_QUATERNION.x, NOT_NORMALIZED_QUATERNION.y, NOT_NORMALIZED_QUATERNION.z, NOT_NORMALIZED_QUATERNION.w,
                                                                 SCALE.x, SCALE.y, SCALE.z);

    // Verification
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_FollowsLeftHandedRules_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    const QQuaternion ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0);
    const QQuaternion ROTATION_QUATERNION_AROUND_Y(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0);
    const QQuaternion ROTATION_QUATERNION_AROUND_Z(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE);

    const QTransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                     ROTATION_QUATERNION_AROUND_X.x, ROTATION_QUATERNION_AROUND_X.y, ROTATION_QUATERNION_AROUND_X.z, ROTATION_QUATERNION_AROUND_X.w,
                                                     SCALE.x, SCALE.y, SCALE.z);
    const QTransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                     ROTATION_QUATERNION_AROUND_Y.x, ROTATION_QUATERNION_AROUND_Y.y, ROTATION_QUATERNION_AROUND_Y.z, ROTATION_QUATERNION_AROUND_Y.w,
                                                     SCALE.x, SCALE.y, SCALE.z);
    const QTransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                     ROTATION_QUATERNION_AROUND_Z.x, ROTATION_QUATERNION_AROUND_Z.y, ROTATION_QUATERNION_AROUND_Z.z, ROTATION_QUATERNION_AROUND_Z.w,
                                                     SCALE.x, SCALE.y, SCALE.z);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor6_CompositionOrderIsScaleRotationTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QVector3 ZERO_VECTOR = QVector3::GetZeroVector();
    const QQuaternion IDENTITY_QUATERNION = QQuaternion::GetIdentity();
    const QVector3 VECTOR_OF_ONES = QVector3::GetVectorOfOnes();

    const QTransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                      IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                                                      VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    const QTransformationMatrix<T> ROTATION_MATRIX(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                                                   ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                                   VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    const QTransformationMatrix<T> SCALE_MATRIX(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                                                IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                                                SCALE.x, SCALE.y, SCALE.z);

    const QTransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QTransformationMatrix<T> matrixUT = QTransformationMatrix<T>(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                                 ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                                                 SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_CorrectResultObtainedWhenOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize());
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_CorrectResultObtainedWhenOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    const T TRANSLATION = T::GetZeroMatrix();
    const QMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();
    const QMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();

    T EXPECTED_VALUE = T::GetZeroMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_FollowsLeftHandedRules_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Y(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Z(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE);

    const QTransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor7_CompositionOrderIsScaleRotationTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const T NEUTRAL_TRANSLATION = T::GetZeroMatrix();
    const QRotationMatrix3x3 NEUTRAL_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 NEUTRAL_SCALE = QScalingMatrix3x3::GetIdentity();

    const QTransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    const QTransformationMatrix<T> ROTATION_MATRIX(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    const QTransformationMatrix<T> SCALE_MATRIX(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const QTransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_CorrectResultObtainedWhenOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize());
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_CorrectResultObtainedWhenOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    const T TRANSLATION = T::GetZeroMatrix();
    const QMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();
    const QMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();

    T EXPECTED_VALUE = T::GetZeroMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_FollowsLeftHandedRules_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Y(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Z(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE);

    const QTransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    const QTransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor8_CompositionOrderIsScaleRotationTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const T NEUTRAL_TRANSLATION = T::GetZeroMatrix();
    const QRotationMatrix3x3 NEUTRAL_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 NEUTRAL_SCALE = QScalingMatrix3x3::GetIdentity();

    const QTransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    const QTransformationMatrix<T> ROTATION_MATRIX(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    const QTransformationMatrix<T> SCALE_MATRIX(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const QTransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QTransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Template method used by QTransformationMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void QTransformationMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.template QTransformationMatrixImp<MatrixType>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE_TEMPLATE ( QTransformationMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QTransformationMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QTransformationMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by QTransformationMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void QTransformationMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.template QTransformationMatrixImp<MatrixType>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE_TEMPLATE ( QTransformationMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QTransformationMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QTransformationMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.template QTransformationMatrixImp<MatrixType>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize());
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.template QTransformationMatrixImp<MatrixType>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.template QTransformationMatrixImp<MatrixType>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE_TEMPLATE ( QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QTransformationMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by QTransformationMatrixImp_ZeroMatrixIsObtainedWhenInputsEqualZero_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void QTransformationMatrixImp_ZeroMatrixIsObtainedWhenInputsEqualZero_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    const MatrixType TRANSLATION = MatrixType::GetZeroMatrix();
    const QMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();
    const QMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();

    T EXPECTED_VALUE = T::GetZeroMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.template QTransformationMatrixImp<MatrixType>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( QTransformationMatrixImp_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QTransformationMatrixImp_ZeroMatrixIsObtainedWhenInputsEqualZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QTransformationMatrixImp_ZeroMatrixIsObtainedWhenInputsEqualZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by QTransformationMatrixImp_CompositionOrderIsScaleRotationTranslation_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void QTransformationMatrixImp_CompositionOrderIsScaleRotationTranslation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QTranslationMatrix<MatrixType> NEUTRAL_TRANSLATION = QTranslationMatrix<MatrixType>::GetZeroMatrix();
    const QRotationMatrix3x3 NEUTRAL_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 NEUTRAL_SCALE = QScalingMatrix3x3::GetIdentity();

    QTransformationMatrixWhiteBox<T> TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.template QTransformationMatrixImp<MatrixType>(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    QTransformationMatrixWhiteBox<T> ROTATION_MATRIX;
    ROTATION_MATRIX.template QTransformationMatrixImp<MatrixType>(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    QTransformationMatrixWhiteBox<T> SCALE_MATRIX;
    SCALE_MATRIX.template QTransformationMatrixImp<MatrixType>(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const QTransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.template QTransformationMatrixImp<MatrixType>(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE_TEMPLATE ( QTransformationMatrixImp_CompositionOrderIsScaleRotationTranslation_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    QTransformationMatrixImp_CompositionOrderIsScaleRotationTranslation_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    QTransformationMatrixImp_CompositionOrderIsScaleRotationTranslation_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
QTEST_CASE_TEMPLATE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test, TQTemplateTypes )
{
    // Preparation
    const T EXPECTED_VALUE = T::GetIdentity();

	// Execution
    QTransformationMatrix<T> matrixUT = QTransformationMatrix<T>::GetIdentity();

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct1_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)126.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)132.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)138.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)306.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)321.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)336.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)486.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)510.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)534.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)692.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)726.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)760.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;
    FillFourthColumnIfExists(OPERAND2, (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)126.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)132.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)138.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)306.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)321.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)336.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)486.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)510.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)534.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)692.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)726.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)760.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct2_FourthColumnOfRightOperandDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERANDA2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTransformationMatrix<T> OPERANDB1 = OPERANDA1;

    QTransformationMatrix<QMatrix4x4> OPERANDB2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    // Execution
    QTransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    QTransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( OperatorProduct2_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERAND2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                              (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                              (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                              (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_6;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_7;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_8;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_9;
    EXPECTED_VALUE.ij[3][0] = (float_q)36.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)38.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)40.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
/// Checks that only the fourth row of the translation matrix participates in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct3_OnlyTheFourthRowOfTranslationMatrixMatters_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x3> OPERANDA2 = QTranslationMatrix<QMatrix4x3>(QMatrix4x3((float_q)17.0f, (float_q)18.0f, (float_q)19.0f,
                                                                                         (float_q)20.0f, (float_q)21.0f, (float_q)22.0f,
                                                                                         (float_q)23.0f, (float_q)24.0f, (float_q)25.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f));

    QTransformationMatrix<T> OPERANDB1 = OPERANDA1;

    QTranslationMatrix<QMatrix4x3> OPERANDB2 = QTranslationMatrix<QMatrix4x3>(QMatrix4x3((float_q)37.0f, (float_q)38.0f, (float_q)39.0f,
                                                                                         (float_q)40.0f, (float_q)41.0f, (float_q)42.0f,
                                                                                         (float_q)43.0f, (float_q)44.0f, (float_q)45.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f));

    // Execution
    QTransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    QTransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( OperatorProduct3_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x4> OPERAND2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                        (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                        (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                        (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}


/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct4_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;
    FillFourthColumnIfExists(OPERAND2, (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_6;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_7;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_8;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_9;
    EXPECTED_VALUE.ij[3][0] = (float_q)36.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)38.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)40.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
/// Checks that only the fourth row of the translation matrix participates in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct4_OnlyTheFourthRowOfTranslationMatrixMatters_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    QTransformationMatrix<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x4> OPERANDA2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                         (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                         (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    QTransformationMatrix<T> OPERANDB1;
    OPERANDB1.ij[0][0] = SQFloat::_1;
    OPERANDB1.ij[0][1] = SQFloat::_2;
    OPERANDB1.ij[0][2] = SQFloat::_3;
    OPERANDB1.ij[1][0] = SQFloat::_4;
    OPERANDB1.ij[1][1] = SQFloat::_5;
    OPERANDB1.ij[1][2] = SQFloat::_6;
    OPERANDB1.ij[2][0] = SQFloat::_7;
    OPERANDB1.ij[2][1] = SQFloat::_8;
    OPERANDB1.ij[2][2] = SQFloat::_9;
    OPERANDB1.ij[3][0] = SQFloat::_10;
    OPERANDB1.ij[3][1] = (float_q)11.0f;
    OPERANDB1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERANDB1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x4> OPERANDB2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)37.0f, (float_q)38.0f, (float_q)39.0f, (float_q)49.0f,
                                                                                         (float_q)40.0f, (float_q)41.0f, (float_q)42.0f, (float_q)50.0f,
                                                                                         (float_q)43.0f, (float_q)44.0f, (float_q)45.0f, (float_q)51.0f,
                                                                                         (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)52.0f));

    // Execution
    QTransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    QTransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( OperatorProduct4_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x4> OPERAND2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                        (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                        (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                        (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct5_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QRotationMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)126.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)132.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)138.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)306.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)321.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)336.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)486.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)510.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)534.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)666.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)699.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)732.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( OperatorProduct5_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QRotationMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct6_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QScalingMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)17.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)42.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)75.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)68.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)105.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)150.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)119.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)168.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)225.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)170.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)231.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)300.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( OperatorProduct6_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QScalingMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that only the diagonal of the scaling matrix participates in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProduct6_OnlyTheDiagonalOfScalingMatrixMatters_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    QTransformationMatrix<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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

    QTransformationMatrix<T> OPERANDB1 = OPERANDA1;

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation1_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)126.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)132.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)138.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)306.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)321.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)336.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)486.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)510.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)534.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)692.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)726.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)760.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QTransformationMatrix<T> matrixUT = OPERAND1;
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
/// Checks that a transformation matrix can be multiplied by itself (same object instance).
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_CanBeMultipliedByItself_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x3> OPERAND;
    OPERAND.ij[0][0] = SQFloat::_1;
    OPERAND.ij[0][1] = SQFloat::_2;
    OPERAND.ij[0][2] = SQFloat::_3;
    OPERAND.ij[1][0] = SQFloat::_4;
    OPERAND.ij[1][1] = SQFloat::_5;
    OPERAND.ij[1][2] = SQFloat::_6;
    OPERAND.ij[2][0] = SQFloat::_7;
    OPERAND.ij[2][1] = SQFloat::_8;
    OPERAND.ij[2][2] = SQFloat::_9;
    OPERAND.ij[3][0] = SQFloat::_10;
    OPERAND.ij[3][1] = (float_q)11.0f;
    OPERAND.ij[3][2] = (float_q)12.0f;

    QTransformationMatrix<QMatrix4x3> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)30.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)36.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)42.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)66.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)81.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)96.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)102.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)126.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)150.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)148.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)182.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)216.0f;

    // Execution
    QTransformationMatrix<QMatrix4x3> matrixUT = OPERAND;
    matrixUT *= matrixUT;

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorProductAssignation2_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;
    FillFourthColumnIfExists(OPERAND2, (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)126.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)132.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)138.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)306.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)321.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)336.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)486.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)510.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)534.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)692.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)726.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)760.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QTransformationMatrix<T> matrixUT = OPERAND1;
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
QTEST_CASE_TEMPLATE ( OperatorProductAssignation2_FourthColumnOfRightOperandDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERANDA2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTransformationMatrix<T> OPERANDB1 = OPERANDA1;

    QTransformationMatrix<QMatrix4x4> OPERANDB2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    // Execution
    QTransformationMatrix<T> matrixAUT = OPERANDA1;
    matrixAUT *= OPERANDA2;
    QTransformationMatrix<T> matrixBUT = OPERANDB1;
    matrixBUT *= OPERANDB2;

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( OperatorProductAssignation2_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERAND2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                              (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                              (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                              (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that a transformation matrix can be multiplied by itself (same object instance).
/// </summary>
QTEST_CASE( OperatorProductAssignation2_CanBeMultipliedByItself_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND;
    OPERAND.ij[0][0] = SQFloat::_1;
    OPERAND.ij[0][1] = SQFloat::_2;
    OPERAND.ij[0][2] = SQFloat::_3;
    OPERAND.ij[1][0] = SQFloat::_4;
    OPERAND.ij[1][1] = SQFloat::_5;
    OPERAND.ij[1][2] = SQFloat::_6;
    OPERAND.ij[2][0] = SQFloat::_7;
    OPERAND.ij[2][1] = SQFloat::_8;
    OPERAND.ij[2][2] = SQFloat::_9;
    OPERAND.ij[3][0] = SQFloat::_10;
    OPERAND.ij[3][1] = (float_q)11.0f;
    OPERAND.ij[3][2] = (float_q)12.0f;
    OPERAND.ij[0][3] = (float_q)13.0f;
    OPERAND.ij[1][3] = (float_q)14.0f;
    OPERAND.ij[2][3] = (float_q)15.0f;
    OPERAND.ij[3][3] = (float_q)16.0f;

    QTransformationMatrix<QMatrix4x4> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)30.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)36.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)42.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)66.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)81.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)96.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)102.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)126.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)150.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)148.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)182.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)216.0f;
    EXPECTED_VALUE.ij[0][3] = (float_q)13.0f;
    EXPECTED_VALUE.ij[1][3] = (float_q)14.0f;
    EXPECTED_VALUE.ij[2][3] = (float_q)15.0f;
    EXPECTED_VALUE.ij[3][3] = (float_q)16.0f;

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = OPERAND;
    matrixUT *= matrixUT;

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
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> MATRIX;
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

    const QTransformationMatrix<T> EXPECTED_VALUE = MATRIX;

    // Execution
    QTransformationMatrix<T> matrixUT;
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
/// Checks that the determinant of a common matrix is correctly obtained.
/// </summary>
QTEST_CASE_TEMPLATE ( GetDeterminant_ItsCorrectlyCalculatedForCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_0;
    MATRIX.ij[3][0] = SQFloat::_10;
    MATRIX.ij[3][1] = (float_q)11.0f;
    MATRIX.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    const float_q EXPECTED_VALUE = (float_q)27.0f;

    // Execution
    float_q fResultUT = MATRIX.GetDeterminant();

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the identity equals one.
/// </summary>
QTEST_CASE_TEMPLATE ( GetDeterminant_DeterminantOfIdentityEqualsOne_Test, TQTemplateTypes )
{
    // Preparation
    const QTransformationMatrix<T> IDENTITY = QTransformationMatrix<T>::GetIdentity();
    const float_q EXPECTED_VALUE = SQFloat::_1;

    // Execution
    float_q fResultUT = IDENTITY.GetDeterminant();

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that only the inner 3x3 matrix participates in the determinant calculus.
/// </summary>
QTEST_CASE_TEMPLATE ( GetDeterminant_OnlyInner3x3MatrixMatters_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> MATRIX1;
    MATRIX1.ij[0][0] = SQFloat::_1;
    MATRIX1.ij[0][1] = SQFloat::_2;
    MATRIX1.ij[0][2] = SQFloat::_3;
    MATRIX1.ij[1][0] = SQFloat::_4;
    MATRIX1.ij[1][1] = SQFloat::_5;
    MATRIX1.ij[1][2] = SQFloat::_6;
    MATRIX1.ij[2][0] = SQFloat::_7;
    MATRIX1.ij[2][1] = SQFloat::_8;
    MATRIX1.ij[2][2] = SQFloat::_0;
    MATRIX1.ij[3][0] = SQFloat::_10;
    MATRIX1.ij[3][1] = (float_q)11.0f;
    MATRIX1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<T> MATRIX2;
    MATRIX2.ij[0][0] = SQFloat::_1;
    MATRIX2.ij[0][1] = SQFloat::_2;
    MATRIX2.ij[0][2] = SQFloat::_3;
    MATRIX2.ij[1][0] = SQFloat::_4;
    MATRIX2.ij[1][1] = SQFloat::_5;
    MATRIX2.ij[1][2] = SQFloat::_6;
    MATRIX2.ij[2][0] = SQFloat::_7;
    MATRIX2.ij[2][1] = SQFloat::_8;
    MATRIX2.ij[2][2] = SQFloat::_0;
    MATRIX2.ij[3][0] = (float_q)17.0f;
    MATRIX2.ij[3][1] = (float_q)18.0f;
    MATRIX2.ij[3][2] = (float_q)19.0f;
    FillFourthColumnIfExists(MATRIX2, (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)23.0f);

    // Execution
    float_q fResult1UT = MATRIX1.GetDeterminant();
    float_q fResult2UT = MATRIX2.GetDeterminant();

    // Verification
    BOOST_CHECK_EQUAL(fResult1UT, fResult2UT);
}

/// <summary>
/// Checks that it returns True when the determinant of the matrix doesn't equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( HasInverse_ReturnsTrueWhenDeterminantIsNotZero_Test, TQTemplateTypes )
{
    // Preparation
    const QTransformationMatrix<T> MATRIX = QTransformationMatrix<T>::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // Execution
    bool bResultUT = MATRIX.HasInverse();

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the determinant of the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( HasInverse_ReturnsFalseWhenDeterminantIsZero_Test, TQTemplateTypes )
{
    // Preparation
    const QTransformationMatrix<T> MATRIX(T::GetZeroMatrix());
    const bool EXPECTED_VALUE = false;

    // Execution
    bool bResultUT = MATRIX.HasInverse();

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common matrix is correctly inverted.
/// </summary>
QTEST_CASE_TEMPLATE ( Invert_CommonMatrixIsCorrectlyInverted_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_0;
    MATRIX.ij[3][0] = SQFloat::_10;
    MATRIX.ij[3][1] = (float_q)11.0f;
    MATRIX.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-1.7777778f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.88888890f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.11111111f;
    EXPECTED_VALUE.ij[1][0] = (float_q)1.5555556f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-0.77777779f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.22222222f;
    EXPECTED_VALUE.ij[2][0] = (float_q)-0.11111111f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.22222222f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-0.11111111f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][1] = -SQFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QTransformationMatrix<T> matrixUT = MATRIX.Invert();

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
/// Checks that the fourth column is just copied to the resultant matrix and doesn't participate in the operation.
/// </summary>
QTEST_CASE ( Invert_FourthColumnIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> MATRIX1;
    MATRIX1.ij[0][0] = SQFloat::_1;
    MATRIX1.ij[0][1] = SQFloat::_2;
    MATRIX1.ij[0][2] = SQFloat::_3;
    MATRIX1.ij[1][0] = SQFloat::_4;
    MATRIX1.ij[1][1] = SQFloat::_5;
    MATRIX1.ij[1][2] = SQFloat::_6;
    MATRIX1.ij[2][0] = SQFloat::_7;
    MATRIX1.ij[2][1] = SQFloat::_8;
    MATRIX1.ij[2][2] = SQFloat::_0;
    MATRIX1.ij[3][0] = SQFloat::_10;
    MATRIX1.ij[3][1] = (float_q)11.0f;
    MATRIX1.ij[3][2] = (float_q)12.0f;
    MATRIX1.ij[0][3] = (float_q)13.0f;
    MATRIX1.ij[1][3] = (float_q)14.0f;
    MATRIX1.ij[2][3] = (float_q)15.0f;
    MATRIX1.ij[3][3] = (float_q)16.0f;

    QTransformationMatrix<QMatrix4x4> MATRIX2;
    MATRIX2.ij[0][0] = SQFloat::_1;
    MATRIX2.ij[0][1] = SQFloat::_2;
    MATRIX2.ij[0][2] = SQFloat::_3;
    MATRIX2.ij[1][0] = SQFloat::_4;
    MATRIX2.ij[1][1] = SQFloat::_5;
    MATRIX2.ij[1][2] = SQFloat::_6;
    MATRIX2.ij[2][0] = SQFloat::_7;
    MATRIX2.ij[2][1] = SQFloat::_8;
    MATRIX2.ij[2][2] = SQFloat::_0;
    MATRIX2.ij[3][0] = SQFloat::_10;
    MATRIX2.ij[3][1] = (float_q)11.0f;
    MATRIX2.ij[3][2] = (float_q)12.0f;
    MATRIX2.ij[0][3] = (float_q)17.0f;
    MATRIX2.ij[1][3] = (float_q)18.0f;
    MATRIX2.ij[2][3] = (float_q)19.0f;
    MATRIX2.ij[3][3] = (float_q)20.0f;

    // Execution
    QTransformationMatrix<QMatrix4x4> matrix1UT = MATRIX1.Invert();
    QTransformationMatrix<QMatrix4x4> matrix2UT = MATRIX2.Invert();

    // Verification
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][0], matrix2UT.ij[0][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][1], matrix2UT.ij[0][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][2], matrix2UT.ij[0][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][0], matrix2UT.ij[1][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][1], matrix2UT.ij[1][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][2], matrix2UT.ij[1][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][0], matrix2UT.ij[2][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][1], matrix2UT.ij[2][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][2], matrix2UT.ij[2][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][0], matrix2UT.ij[3][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][1], matrix2UT.ij[3][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][2], matrix2UT.ij[3][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][3], MATRIX1.ij[0][3]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][3], MATRIX1.ij[1][3]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][3], MATRIX1.ij[2][3]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][3], MATRIX1.ij[3][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[0][3], MATRIX2.ij[0][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[1][3], MATRIX2.ij[1][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[2][3], MATRIX2.ij[2][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[3][3], MATRIX2.ij[3][3]);

}

/// <summary>
/// Checks that 3 translation values are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation1_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_0;
    MATRIX.ij[3][0] = SQFloat::_10;
    MATRIX.ij[3][1] = (float_q)11.0f;
    MATRIX.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
    QTransformationMatrix<T> MATRIX = T::GetIdentity();

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

    QTransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_0;
    MATRIX.ij[3][0] = SQFloat::_10;
    MATRIX.ij[3][1] = (float_q)11.0f;
    MATRIX.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

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
/// Checks that 3 translation values equal zero when transformation matrix is the identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation2_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    QTransformationMatrix<T> MATRIX = T::GetIdentity();

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
/// Checks that translation vector is correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    QTransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SQFloat::_1;
    MATRIX.ij[0][1] = SQFloat::_2;
    MATRIX.ij[0][2] = SQFloat::_3;
    MATRIX.ij[1][0] = SQFloat::_4;
    MATRIX.ij[1][1] = SQFloat::_5;
    MATRIX.ij[1][2] = SQFloat::_6;
    MATRIX.ij[2][0] = SQFloat::_7;
    MATRIX.ij[2][1] = SQFloat::_8;
    MATRIX.ij[2][2] = SQFloat::_0;
    MATRIX.ij[3][0] = SQFloat::_10;
    MATRIX.ij[3][1] = (float_q)11.0f;
    MATRIX.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(MATRIX, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    const QBaseVector4 EXPECTED_VALUE(MATRIX.ij[3][0], MATRIX.ij[3][1], MATRIX.ij[3][2], SQFloat::_0);

    // Execution
    QBaseVector4 vTranslationUT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // Verification
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that 3 translation values equal zero when transformation matrix is the identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    QTransformationMatrix<T> MATRIX = T::GetIdentity();

    const QBaseVector4 EXPECTED_VALUE(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    // Execution
    QBaseVector4 vTranslationUT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // Verification
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix represents a rotation and a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale1_ValuesAreCorrectlyExtractedWhenMatrixContainsRotationAndScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

    const QRotationMatrix3x3 ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QScalingMatrix3x3 SCALE(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    float_q fScaleXUT = SQFloat::_0;
    float_q fScaleYUT = SQFloat::_0;
    float_q fScaleZUT = SQFloat::_0;

    QTransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fScaleXUT, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SQFloat::AreEqual(fScaleYUT, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SQFloat::AreEqual(fScaleZUT, EXPECTED_VALUE_FOR_Z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale1_ValuesAreCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

    const QScalingMatrix3x3 SCALE(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * QRotationMatrix3x3::GetIdentity();
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    float_q fScaleXUT = SQFloat::_0;
    float_q fScaleYUT = SQFloat::_0;
    float_q fScaleZUT = SQFloat::_0;

    QTransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // Verification
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that obtained values equal 1 when matrix is identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale1_ValuesEqualOneWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    float_q fScaleXUT = SQFloat::_0;
    float_q fScaleYUT = SQFloat::_0;
    float_q fScaleZUT = SQFloat::_0;

    QTransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // Verification
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale1_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

    const QRotationMatrix3x3 ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QScalingMatrix3x3 SCALE(-EXPECTED_VALUE_FOR_X, -EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * QRotationMatrix3x3::GetIdentity();
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    float_q fScaleXUT = SQFloat::_0;
    float_q fScaleYUT = SQFloat::_0;
    float_q fScaleZUT = SQFloat::_0;

    QTransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // Verification
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix represents a rotation and a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale2_ValuesAreCorrectlyExtractedWhenMatrixContainsRotationAndScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QBaseVector3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QRotationMatrix3x3 ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QScalingMatrix3x3 SCALE(EXPECTED_VALUE.x, EXPECTED_VALUE.y, EXPECTED_VALUE.z);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vScale;

    QTransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(vScale);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScale.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScale.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScale.z, EXPECTED_VALUE.z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale2_ValuesAreCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QBaseVector3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QRotationMatrix3x3 ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QScalingMatrix3x3 SCALE(EXPECTED_VALUE.x, EXPECTED_VALUE.y, EXPECTED_VALUE.z);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * QRotationMatrix3x3::GetIdentity();
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vScale;

    QTransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(vScale);

    // Verification
    BOOST_CHECK_EQUAL(vScale.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vScale.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vScale.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that obtained values equal 1 when matrix is identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale2_ValuesEqualOneWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QBaseVector3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QBaseVector3 vScale;

    QTransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetScale(vScale);

    // Verification
    BOOST_CHECK_EQUAL(vScale.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vScale.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vScale.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( GetScale2_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const QBaseVector3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QRotationMatrix3x3 ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QScalingMatrix3x3 SCALE(-EXPECTED_VALUE.x, -EXPECTED_VALUE.y, EXPECTED_VALUE.z);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * QRotationMatrix3x3::GetIdentity();
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vScale;

    QTransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(vScale);

    // Verification
    BOOST_CHECK_EQUAL(vScale.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vScale.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vScale.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that obtained angles equal expected values when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation1_AnglesAreCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ROTATION_X = SQAngle::_45;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_60;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_90;
    #else
        const float_q EXPECTED_ROTATION_X = SQAngle::_QuarterPi;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_ThirdPi;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_HalfPi;
    #endif

    QTransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_q)0.61237252f;
    ROTATION.ij[0][1] = (float_q)0.70710653f;
    ROTATION.ij[0][2] = (float_q)0.35355330f;
    ROTATION.ij[1][0] = (float_q)-0.49999982f;
    ROTATION.ij[1][1] = (float_q)3.2782555e-007f;
    ROTATION.ij[1][2] = (float_q)0.86602509f;
    ROTATION.ij[2][0] = (float_q)0.61237222f;
    ROTATION.ij[2][1] = (float_q)-0.70710659f;
    ROTATION.ij[2][2] = (float_q)0.35355362f;
    ROTATION.ij[3][0] = SQFloat::_10;
    ROTATION.ij[3][1] = (float_q)11.0f;
    ROTATION.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(ROTATION, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    float_q fRotationXUT = SQFloat::_0;
    float_q fRotationYUT = SQFloat::_0;
    float_q fRotationZUT = SQFloat::_0;

    ROTATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fRotationXUT, EXPECTED_ROTATION_X) );
    BOOST_CHECK( SQFloat::AreEqual(fRotationYUT, EXPECTED_ROTATION_Y) );
    BOOST_CHECK( SQFloat::AreEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained angles don't equal expected values due to gimbal lock limitation.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation1_AnglesAreNotWhatExpectedWhenGimbalLockOccurs_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ROTATION_X = SQAngle::_90;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_90;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_60;
    #else
        const float_q EXPECTED_ROTATION_X = SQAngle::_HalfPi;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_HalfPi;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_ThirdPi;
    #endif

    // By rotating 90º (or PI/2) two gimbals, they become alligned so rotating any of them results in the same transformation
    QTransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_q)0.86602545f;
    ROTATION.ij[0][1] = (float_q)-3.7855173e-008f;
    ROTATION.ij[0][2] = (float_q)-0.5f;
    ROTATION.ij[1][0] = (float_q)0.5f;
    ROTATION.ij[1][1] = (float_q)-2.1855692e-008f;
    ROTATION.ij[1][2] = (float_q)0.86602545f;
    ROTATION.ij[2][0] = (float_q)-4.3711388e-008f;
    ROTATION.ij[2][1] = (float_q)-1.0f;
    ROTATION.ij[2][2] = (float_q)1.9106855e-015f;
    ROTATION.ij[3][0] = SQFloat::_10;
    ROTATION.ij[3][1] = (float_q)11.0f;
    ROTATION.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(ROTATION, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    float_q fRotationXUT = SQFloat::_0;
    float_q fRotationYUT = SQFloat::_0;
    float_q fRotationZUT = SQFloat::_0;

    ROTATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(fRotationXUT, EXPECTED_ROTATION_X) ||
                 SQFloat::AreNotEqual(fRotationYUT, EXPECTED_ROTATION_Y) ||
                 SQFloat::AreNotEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained angles equal expected values when transformation matrix represents a rotation and a positive scale.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation1_AnglesAreCorrectlyExtractedWhenMatrixContainsRotationAndPositiveScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ROTATION_X = SQAngle::_45;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_60;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_90;
    #else
        const float_q EXPECTED_ROTATION_X = SQAngle::_QuarterPi;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_ThirdPi;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION_X, EXPECTED_ROTATION_Y, EXPECTED_ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    float_q fRotationXUT = SQFloat::_0;
    float_q fRotationYUT = SQFloat::_0;
    float_q fRotationZUT = SQFloat::_0;

    ADAPTED_TRANSFORMATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fRotationXUT, EXPECTED_ROTATION_X) );
    BOOST_CHECK( SQFloat::AreEqual(fRotationYUT, EXPECTED_ROTATION_Y) );
    BOOST_CHECK( SQFloat::AreEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ROTATION_X = SQAngle::_45;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_60;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_90;
    #else
        const float_q EXPECTED_ROTATION_X = SQAngle::_QuarterPi;
        const float_q EXPECTED_ROTATION_Y = SQAngle::_ThirdPi;
        const float_q EXPECTED_ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION_X, EXPECTED_ROTATION_Y, EXPECTED_ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    float_q fRotationXUT = SQFloat::_0;
    float_q fRotationYUT = SQFloat::_0;
    float_q fRotationZUT = SQFloat::_0;

    ADAPTED_TRANSFORMATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(fRotationXUT, EXPECTED_ROTATION_X) );
    BOOST_CHECK( SQFloat::AreNotEqual(fRotationYUT, EXPECTED_ROTATION_Y) );
    BOOST_CHECK( SQFloat::AreNotEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained values equal 0 when matrix is identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation1_ValuesEqualZeroWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    // Execution
    float_q fRotationXUT = SQFloat::_0;
    float_q fRotationYUT = SQFloat::_0;
    float_q fRotationZUT = SQFloat::_0;

    QTransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // Verification
    BOOST_CHECK_EQUAL( fRotationXUT, EXPECTED_VALUE_FOR_ALL );
    BOOST_CHECK_EQUAL( fRotationYUT, EXPECTED_VALUE_FOR_ALL );
    BOOST_CHECK_EQUAL( fRotationZUT, EXPECTED_VALUE_FOR_ALL );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QQuaternion EXPECTED_VALUE(ROTATION_X, ROTATION_Y, ROTATION_Z);

    QTransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_q)0.61237252f;
    ROTATION.ij[0][1] = (float_q)0.70710653f;
    ROTATION.ij[0][2] = (float_q)0.35355330f;
    ROTATION.ij[1][0] = (float_q)-0.49999982f;
    ROTATION.ij[1][1] = (float_q)3.2782555e-007f;
    ROTATION.ij[1][2] = (float_q)0.86602509f;
    ROTATION.ij[2][0] = (float_q)0.61237222f;
    ROTATION.ij[2][1] = (float_q)-0.70710659f;
    ROTATION.ij[2][2] = (float_q)0.35355362f;
    ROTATION.ij[3][0] = SQFloat::_10;
    ROTATION.ij[3][1] = (float_q)11.0f;
    ROTATION.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(ROTATION, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QQuaternion qRotationUT;
    ROTATION.GetRotation(qRotationUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix represents a rotation and a positive scale.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation2_RotationIsCorrectlyExtractedWhenMatrixContainsRotationAndPositiveScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QQuaternion EXPECTED_VALUE(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QQuaternion qRotationUT;
    ADAPTED_TRANSFORMATION.GetRotation(qRotationUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QQuaternion EXPECTED_VALUE(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QQuaternion qRotationUT;
    ADAPTED_TRANSFORMATION.GetRotation(qRotationUT);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that obtained value is an identity quaternion when matrix is identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation2_ValueEqualsIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();
    const QQuaternion IDENTITY = QQuaternion::GetIdentity();

    // Execution
    QQuaternion qRotationUT;

    QTransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetRotation(qRotationUT);

    // Verification
    BOOST_CHECK_EQUAL( qRotationUT.x, IDENTITY.x );
    BOOST_CHECK_EQUAL( qRotationUT.y, IDENTITY.y );
    BOOST_CHECK_EQUAL( qRotationUT.z, IDENTITY.z );
    BOOST_CHECK_EQUAL( qRotationUT.w, IDENTITY.w );
}

/// <summary>
/// Checks that obtained angle and rotation axis equal expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation3_RotationAngleAndAxisAreCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ANGLE = SQAngle::_60;
    #else
        const float_q EXPECTED_ANGLE = SQAngle::_ThirdPi;
    #endif

    const QVector3 EXPECTED_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();

    QTransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_q)0.53571427f;
    ROTATION.ij[0][1] = (float_q)0.76579368f;
    ROTATION.ij[0][2] = (float_q)-0.35576719f;
    ROTATION.ij[1][0] = (float_q)-0.62293649f;
    ROTATION.ij[1][1] = (float_q)0.64285713f;
    ROTATION.ij[1][2] = (float_q)0.44574076f;
    ROTATION.ij[2][0] = (float_q)0.57005292f;
    ROTATION.ij[2][1] = (float_q)-0.017169312f;
    ROTATION.ij[2][2] = (float_q)0.82142854f;
    ROTATION.ij[3][0] = SQFloat::_10;
    ROTATION.ij[3][1] = (float_q)11.0f;
    ROTATION.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(ROTATION, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QVector3 vAxisUT;
    float_q fAngleUT = SQFloat::_0;
    ROTATION.GetRotation(fAngleUT, vAxisUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SQFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained angle and axis equal expected values when transformation matrix represents a rotation and a positive scale.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation3_RotationIsCorrectlyExtractedWhenMatrixContainsRotationAndPositiveScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ANGLE = SQAngle::_60;
    #else
        const float_q EXPECTED_ANGLE = SQAngle::_ThirdPi;
    #endif

    const QVector3 EXPECTED_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();

    const QRotationMatrix3x3 ROTATION(QBaseMatrix3x3((float_q)0.53571427f,  (float_q)0.76579368f,   (float_q)-0.35576719f,
                                                     (float_q)-0.62293649f, (float_q)0.64285713f,   (float_q)0.44574076f,
                                                     (float_q)0.57005292f,  (float_q)-0.017169312f, (float_q)0.82142854f));

    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QVector3 vAxisUT;
    float_q fAngleUT = SQFloat::_0;
    ADAPTED_TRANSFORMATION.GetRotation(fAngleUT, vAxisUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SQFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation3_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ANGLE = SQAngle::_60;
    #else
        const float_q EXPECTED_ANGLE = SQAngle::_ThirdPi;
    #endif

    const QVector3 EXPECTED_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();

    const QRotationMatrix3x3 ROTATION(QBaseMatrix3x3((float_q)0.53571427f,  (float_q)0.76579368f,   (float_q)-0.35576719f,
                                                     (float_q)-0.62293649f, (float_q)0.64285713f,   (float_q)0.44574076f,
                                                     (float_q)0.57005292f,  (float_q)-0.017169312f, (float_q)0.82142854f));

    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QVector3 vAxisUT;
    float_q fAngleUT = SQFloat::_0;
    ADAPTED_TRANSFORMATION.GetRotation(fAngleUT, vAxisUT);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SQFloat::AreNotEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained axis is a null vector and the obtained angle equals zero when the matrix contains scaling data and the original rotation was neutral.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation3_NullVectorAndZeroAngleAreObtainedWhenMatrixContainsPositiveScaleAndNeutralRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ANGLE = SQAngle::_60;
    #else
        const float_q EXPECTED_ANGLE = SQAngle::_ThirdPi;
    #endif

    const QVector3 EXPECTED_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();

    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3::GetIdentity();

    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QVector3 vAxisUT;
    float_q fAngleUT = SQFloat::_0;
    ADAPTED_TRANSFORMATION.GetRotation(fAngleUT, vAxisUT);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SQFloat::AreNotEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained axis is a null vector and the obtained angle equals zero when the matrix is the identity.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation3_NullVectorAndZeroAngleAreObtainedWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_ANGLE = SQAngle::_60;
    #else
        const float_q EXPECTED_ANGLE = SQAngle::_ThirdPi;
    #endif

    const QVector3 EXPECTED_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();

    QTransformationMatrix<T> IDENTITY = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QVector3 vAxisUT;
    float_q fAngleUT = SQFloat::_0;
    IDENTITY.GetRotation(fAngleUT, vAxisUT);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SQFloat::AreNotEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SQFloat::AreNotEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that the obtained axis is normalized.
/// </summary>
QTEST_CASE_TEMPLATE ( GetRotation3_ResultantAxisIsNormalized_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 EXPECTED_AXIS = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3).Normalize();

    QTransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_q)0.53571427f;
    ROTATION.ij[0][1] = (float_q)0.76579368f;
    ROTATION.ij[0][2] = (float_q)-0.35576719f;
    ROTATION.ij[1][0] = (float_q)-0.62293649f;
    ROTATION.ij[1][1] = (float_q)0.64285713f;
    ROTATION.ij[1][2] = (float_q)0.44574076f;
    ROTATION.ij[2][0] = (float_q)0.57005292f;
    ROTATION.ij[2][1] = (float_q)-0.017169312f;
    ROTATION.ij[2][2] = (float_q)0.82142854f;
    ROTATION.ij[3][0] = SQFloat::_10;
    ROTATION.ij[3][1] = (float_q)11.0f;
    ROTATION.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(ROTATION, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QVector3 vAxisUT;
    QVector3 vNormalizedAxis;
    float_q fAngleAux = SQFloat::_0;
    ROTATION.GetRotation(fAngleAux, vAxisUT);

    vNormalizedAxis = vAxisUT.Normalize();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.x, vNormalizedAxis.x) );
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.y, vNormalizedAxis.y) );
    BOOST_CHECK( SQFloat::AreEqual(vAxisUT.z, vNormalizedAxis.z) );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationUT;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationUT, qRotationUT, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation vector is null when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_TranslationVectorIsNullWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QBaseVector3 vTranslationUT;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationUT, qRotationAux, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
}

/// <summary>
/// Checks that rotation quaternion equals identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_RotationQuaternionEqualsIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QQuaternion EXPECTED_ROTATION = QQuaternion::GetIdentity();

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that scaling vector's components equal one when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_ScalingVectorComponentsEqualOneWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 EXPECTED_SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleUT;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(QBaseVector3(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6));

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose1_ValuesAreCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion EXPECTED_ROTATION = QQuaternion::GetIdentity();
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector4 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_0);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(QBaseVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4));
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector4 vTranslationUT;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationUT, qRotationUT, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.w, EXPECTED_TRANSLATION.w) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation vector is null when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_TranslationVectorIsNullWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector4 EXPECTED_TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QBaseVector4 vTranslationUT;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationUT, qRotationAux, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
}

/// <summary>
/// Checks that rotation quaternion equals identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_RotationQuaternionEqualsIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QQuaternion EXPECTED_ROTATION = QQuaternion::GetIdentity();

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QBaseVector4 vTranslationAux;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that scaling vector's components equal one when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_ScalingVectorComponentsEqualOneWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 EXPECTED_SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QBaseVector4 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleUT;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector4 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector4 vTranslationAux;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreNotEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector4 EXPECTED_TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector4 vTranslationAux;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector4 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(QBaseVector3(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6));

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector4 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose2_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QBaseVector4 EXPECTED_TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion EXPECTED_ROTATION = QQuaternion::GetIdentity();
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const QRotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector4 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose3_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x3> EXPECTED_TRANSLATION(TRANSLATION, QRotationMatrix3x3::GetIdentity(), QScalingMatrix3x3::GetIdentity());
    const QTransformationMatrix<QMatrix4x3> EXPECTED_ROTATION(QTranslationMatrix<QMatrix4x3>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());
    const QTransformationMatrix<QMatrix4x3> EXPECTED_SCALE(QTranslationMatrix<QMatrix4x3>::GetIdentity(), QRotationMatrix3x3::GetIdentity(), SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x3> translationUT;
    QTransformationMatrix<QMatrix4x3> rotationUT;
    QTransformationMatrix<QMatrix4x3> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose3_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    const QTransformationMatrix<QMatrix4x3> EXPECTED_TRANSFORMATIONS_VALUE = QTransformationMatrix<QMatrix4x3>::GetIdentity();

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QTransformationMatrix<QMatrix4x3> translationUT;
    QTransformationMatrix<QMatrix4x3> rotationUT;
    QTransformationMatrix<QMatrix4x3> scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( rotationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( scaleUT == EXPECTED_TRANSFORMATIONS_VALUE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose3_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x3> EXPECTED_ROTATION(QTranslationMatrix<QMatrix4x3>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x3> translationAux;
    QTransformationMatrix<QMatrix4x3> rotationUT;
    QTransformationMatrix<QMatrix4x3> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose3_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<QMatrix4x3> EXPECTED_ROTATION(QTranslationMatrix<QMatrix4x3>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x3> translationAux;
    QTransformationMatrix<QMatrix4x3> rotationUT;
    QTransformationMatrix<QMatrix4x3> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose3_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x3> EXPECTED_SCALE(TRANSLATION, ROTATION, QScalingMatrix3x3(SQFloat::_4, SQFloat::_5, SQFloat::_6));

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x3> translationAux;
    QTransformationMatrix<QMatrix4x3> rotationAux;
    QTransformationMatrix<QMatrix4x3> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose3_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x3> EXPECTED_SCALE(TRANSLATION, ROTATION, SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x3> translationAux;
    QTransformationMatrix<QMatrix4x3> rotationAux;
    QTransformationMatrix<QMatrix4x3> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose4_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> EXPECTED_TRANSLATION(TRANSLATION, QRotationMatrix3x3::GetIdentity(), QScalingMatrix3x3::GetIdentity());
    const QTransformationMatrix<QMatrix4x4> EXPECTED_ROTATION(QTranslationMatrix<QMatrix4x4>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());
    const QTransformationMatrix<QMatrix4x4> EXPECTED_SCALE(QTranslationMatrix<QMatrix4x4>::GetIdentity(), QRotationMatrix3x3::GetIdentity(), SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x4> translationUT;
    QTransformationMatrix<QMatrix4x4> rotationUT;
    QTransformationMatrix<QMatrix4x4> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose4_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    const QTransformationMatrix<QMatrix4x4> EXPECTED_TRANSFORMATIONS_VALUE = QTransformationMatrix<QMatrix4x4>::GetIdentity();

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QTransformationMatrix<QMatrix4x4> translationUT;
    QTransformationMatrix<QMatrix4x4> rotationUT;
    QTransformationMatrix<QMatrix4x4> scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( rotationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( scaleUT == EXPECTED_TRANSFORMATIONS_VALUE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose4_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> EXPECTED_ROTATION(QTranslationMatrix<QMatrix4x4>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x4> translationAux;
    QTransformationMatrix<QMatrix4x4> rotationUT;
    QTransformationMatrix<QMatrix4x4> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose4_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<QMatrix4x4> EXPECTED_ROTATION(QTranslationMatrix<QMatrix4x4>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x4> translationAux;
    QTransformationMatrix<QMatrix4x4> rotationUT;
    QTransformationMatrix<QMatrix4x4> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose4_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> EXPECTED_SCALE(TRANSLATION, ROTATION, QScalingMatrix3x3(SQFloat::_4, SQFloat::_5, SQFloat::_6));

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x4> translationAux;
    QTransformationMatrix<QMatrix4x4> rotationAux;
    QTransformationMatrix<QMatrix4x4> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose4_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> EXPECTED_SCALE(TRANSLATION, ROTATION, SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<QMatrix4x4> translationAux;
    QTransformationMatrix<QMatrix4x4> rotationAux;
    QTransformationMatrix<QMatrix4x4> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose5_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = EXPECTED_SCALE * EXPECTED_ROTATION * EXPECTED_TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x3> translationUT;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose5_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    const QTranslationMatrix<QMatrix4x3> EXPECTED_TRANSLATION = QTranslationMatrix<QMatrix4x3>::GetIdentity();
    const QRotationMatrix3x3 EXPECTED_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 EXPECTED_SCALE = QScalingMatrix3x3::GetIdentity();

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QTranslationMatrix<QMatrix4x3> translationUT;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose5_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x3> translationAux;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleAux;
    TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose5_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x3> translationAux;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleAux;
    TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose5_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x3> translationAux;
    QRotationMatrix3x3 rotationAux;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose5_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = EXPECTED_SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x3> translationAux;
    QRotationMatrix3x3 rotationAux;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose6_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = EXPECTED_SCALE * EXPECTED_ROTATION * EXPECTED_TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x4> translationUT;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose6_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    const QTranslationMatrix<QMatrix4x4> EXPECTED_TRANSLATION = QTranslationMatrix<QMatrix4x4>::GetIdentity();
    const QRotationMatrix3x3 EXPECTED_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 EXPECTED_SCALE = QScalingMatrix3x3::GetIdentity();

    const QTransformationMatrix<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QTranslationMatrix<QMatrix4x4> translationUT;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose6_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x4> translationAux;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose6_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x4> translationAux;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose6_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x4> translationAux;
    QRotationMatrix3x3 rotationAux;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( Decompose6_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = EXPECTED_SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<QMatrix4x4> translationAux;
    QRotationMatrix3x3 rotationAux;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that the hand convention of the transformations represented by the matrix are correctly switched.
/// </summary>
QTEST_CASE_TEMPLATE ( SwitchHandConvention_MatrixHandConventionIsCorrectlySwitched_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, -SQFloat::_3); // Z-axis is inverted
    const QQuaternion EXPECTED_ROTATION = QQuaternion(ROTATION_X, ROTATION_Y, ROTATION_Z).Invert(); // Rotations are all inverted
    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6); // Scale remains the same

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(QBaseVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3));
    const QRotationMatrix3x3 ROTATION(QQuaternion(ROTATION_X, ROTATION_Y, ROTATION_Z));
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationUT;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationUT, qRotationUT, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that the translation over Z axis is inverted.
/// </summary>
QTEST_CASE_TEMPLATE ( SwitchHandConvention_TranslationZComponentIsInverted_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QBaseVector3 EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, -SQFloat::_3); // Z-axis is inverted

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(QBaseVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3));
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationUT;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleAux;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationUT, qRotationAux, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
}

/// <summary>
/// Checks that rotations are inverted.
/// </summary>
QTEST_CASE_TEMPLATE ( SwitchHandConvention_RotationsAreInverted_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QQuaternion EXPECTED_ROTATION = QQuaternion(ROTATION_X, ROTATION_Y, ROTATION_Z).Invert(); // Rotations are all inverted

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(QBaseVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0));
    const QRotationMatrix3x3 ROTATION(QQuaternion(ROTATION_X, ROTATION_Y, ROTATION_Z));
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationUT;
    QBaseVector3 vScaleAux;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SQFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that the scale is not affected by the hand convention.
/// </summary>
QTEST_CASE_TEMPLATE ( SwitchHandConvention_ScaleDoesntChange_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QBaseVector3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6); // Scale remains the same

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(QBaseVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0));
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleUT;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SQFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that the assertion fails when the scale contained in the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( SwitchHandConvention_AssertionFailsWhenScaleEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const bool EXPECTED_VALUE = true;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(QBaseVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3));
    const QRotationMatrix3x3 ROTATION(QQuaternion(ROTATION_X, ROTATION_Y, ROTATION_Z));
    const QScalingMatrix3x3 SCALE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QBaseVector3 vTranslationAux;
    QQuaternion qRotationAux;
    QBaseVector3 vScaleAux;
    bool bAssertionFailed = false;

    try
    {
        ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationAux, qRotationAux, vScaleAux);
    }
    catch(...) // TODO [avillalba]: A concrete exception should be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the correct rotation is obtained when using a common transformation matrix that contains positive scale.
/// </summary>
QTEST_CASE_TEMPLATE ( ToRotationMatrix3x3_CorrectRotationIsObtainedWhenUsingCommonMatrixWithPositiveScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QRotationMatrix3x3 rotationUT = ADAPTED_TRANSFORMATION.ToRotationMatrix3x3();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[0][0], EXPECTED_ROTATION.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[0][1], EXPECTED_ROTATION.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[0][2], EXPECTED_ROTATION.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[1][0], EXPECTED_ROTATION.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[1][1], EXPECTED_ROTATION.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[1][2], EXPECTED_ROTATION.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[2][0], EXPECTED_ROTATION.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[2][1], EXPECTED_ROTATION.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[2][2], EXPECTED_ROTATION.ij[2][2]) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( ToRotationMatrix3x3_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QRotationMatrix3x3 rotationUT = ADAPTED_TRANSFORMATION.ToRotationMatrix3x3();

    // Verification
    BOOST_CHECK(rotationUT != EXPECTED_ROTATION);
}

/// <summary>
/// Checks that the obtained rotation matrix equals identity when transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( ToRotationMatrix3x3_ObtainedRotationEqualsIdentityWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    const QRotationMatrix3x3 EXPECTED_ROTATION = QRotationMatrix3x3::GetIdentity();

    QTransformationMatrixWhiteBox<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QRotationMatrix3x3 rotationUT = TRANSFORMATION.ToRotationMatrix3x3();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[0][0], EXPECTED_ROTATION.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[0][1], EXPECTED_ROTATION.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[0][2], EXPECTED_ROTATION.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[1][0], EXPECTED_ROTATION.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[1][1], EXPECTED_ROTATION.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[1][2], EXPECTED_ROTATION.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[2][0], EXPECTED_ROTATION.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[2][1], EXPECTED_ROTATION.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(rotationUT.ij[2][2], EXPECTED_ROTATION.ij[2][2]) );
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QBaseVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_CorrectResultObtainedWhenOnlyContainsRotation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion ROTATION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_CorrectResultObtainedWhenOnlyContainsScale_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseVector3 SCALE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    T EXPECTED_VALUE = T::GetZeroMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_ResultIsDifferentDependingOnQuaternionNormalization_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion NOT_NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixFromNormalizedQuaternionUT;
    matrixFromNormalizedQuaternionUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                NORMALIZED_QUATERNION.x, NORMALIZED_QUATERNION.y, NORMALIZED_QUATERNION.z, NORMALIZED_QUATERNION.w,
                                                SCALE.x, SCALE.y, SCALE.z);

    QTransformationMatrixWhiteBox<T> matrixFromNotNormalizedQuaternionUT;
    matrixFromNotNormalizedQuaternionUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                   NOT_NORMALIZED_QUATERNION.x, NOT_NORMALIZED_QUATERNION.y, NOT_NORMALIZED_QUATERNION.z, NOT_NORMALIZED_QUATERNION.w,
                                                   SCALE.x, SCALE.y, SCALE.z);

    // Verification
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_FollowsLeftHandedRules_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    const QQuaternion ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0);
    const QQuaternion ROTATION_QUATERNION_AROUND_Y(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0);
    const QQuaternion ROTATION_QUATERNION_AROUND_Z(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE);

    QTransformationMatrixWhiteBox<T> ROTATION_AROUND_X;
    ROTATION_AROUND_X.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                 ROTATION_QUATERNION_AROUND_X.x, ROTATION_QUATERNION_AROUND_X.y, ROTATION_QUATERNION_AROUND_X.z, ROTATION_QUATERNION_AROUND_X.w,
                                 SCALE.x, SCALE.y, SCALE.z);
    QTransformationMatrixWhiteBox<T> ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                 ROTATION_QUATERNION_AROUND_Y.x, ROTATION_QUATERNION_AROUND_Y.y, ROTATION_QUATERNION_AROUND_Y.z, ROTATION_QUATERNION_AROUND_Y.w,
                                 SCALE.x, SCALE.y, SCALE.z);
    QTransformationMatrixWhiteBox<T> ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                 ROTATION_QUATERNION_AROUND_Z.x, ROTATION_QUATERNION_AROUND_Z.y, ROTATION_QUATERNION_AROUND_Z.z, ROTATION_QUATERNION_AROUND_Z.w,
                                 SCALE.x, SCALE.y, SCALE.z);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE_TEMPLATE ( Initialize_CompositionOrderIsScaleRotationTranslation_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QVector3 ZERO_VECTOR = QVector3::GetZeroVector();
    const QQuaternion IDENTITY_QUATERNION = QQuaternion::GetIdentity();
    const QVector3 VECTOR_OF_ONES = QVector3::GetVectorOfOnes();

    QTransformationMatrixWhiteBox<T> TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                  IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                                  VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    QTransformationMatrixWhiteBox<T> ROTATION_MATRIX;
    ROTATION_MATRIX.Initialize(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                               ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                               VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    QTransformationMatrixWhiteBox<T> SCALE_MATRIX;
    SCALE_MATRIX.Initialize(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                            IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                            SCALE.x, SCALE.y, SCALE.z);

    const QTransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
/// Template method used by ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Template()
{
    // Preparation
    QTransformationMatrixWhiteBox<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<MatrixType> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;
    FillFourthColumnIfExists(OPERAND2, (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)126.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)132.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)138.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)306.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)321.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)336.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)486.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)510.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)534.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)692.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)726.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)760.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QTransformationMatrix<T> matrixUT;
    OPERAND1.ProductOperatorImp(OPERAND2, matrixUT);

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductOperatorImp1_FourthColumnOfRightOperandDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrixWhiteBox<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERANDA2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTransformationMatrixWhiteBox<T> OPERANDB1 = OPERANDA1;

    QTransformationMatrix<QMatrix4x4> OPERANDB2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    // Execution
    QTransformationMatrix<T> matrixAUT;
    QTransformationMatrix<T> matrixBUT;
    OPERANDA1.ProductOperatorImp(OPERANDA2, matrixAUT);
    OPERANDB1.ProductOperatorImp(OPERANDB2, matrixBUT);

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( ProductOperatorImp1_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrixWhiteBox<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERAND2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                              (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                              (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                              (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT;
    OPERAND1.ProductOperatorImp(OPERAND2, matrixUT);

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Template method used by ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Template()
{
    // Preparation
    QTransformationMatrixWhiteBox<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SQFloat::_4;
    EXPECTED_VALUE.ij[1][1] = SQFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SQFloat::_6;
    EXPECTED_VALUE.ij[2][0] = SQFloat::_7;
    EXPECTED_VALUE.ij[2][1] = SQFloat::_8;
    EXPECTED_VALUE.ij[2][2] = SQFloat::_9;
    EXPECTED_VALUE.ij[3][0] = (float_q)36.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)38.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)40.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QTransformationMatrix<T> matrixUT;
    OPERAND1.ProductOperatorImp(OPERAND2, matrixUT);

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by ProductOperatorImp2_OnlyTheFourthRowOfTranslationMatrixMatters_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductOperatorImp2_OnlyTheFourthRowOfTranslationMatrixMatters_Template()
{
    // Preparation
    QTransformationMatrixWhiteBox<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<T> OPERANDA2;
    OPERANDA2.ij[0][0] = (float_q)17.0f;
    OPERANDA2.ij[0][1] = (float_q)18.0f;
    OPERANDA2.ij[0][2] = (float_q)19.0f;
    OPERANDA2.ij[1][0] = (float_q)20.0f;
    OPERANDA2.ij[1][1] = (float_q)21.0f;
    OPERANDA2.ij[1][2] = (float_q)22.0f;
    OPERANDA2.ij[2][0] = (float_q)23.0f;
    OPERANDA2.ij[2][1] = (float_q)24.0f;
    OPERANDA2.ij[2][2] = (float_q)25.0f;
    OPERANDA2.ij[3][0] = (float_q)26.0f;
    OPERANDA2.ij[3][1] = (float_q)27.0f;
    OPERANDA2.ij[3][2] = (float_q)28.0f;
    FillFourthColumnIfExists(OPERANDA2, (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f);

    QTransformationMatrixWhiteBox<T> OPERANDB1 = OPERANDA1;

    QTranslationMatrix<T> OPERANDB2;
    OPERANDB2.ij[0][0] = (float_q)33.0f;
    OPERANDB2.ij[0][1] = (float_q)34.0f;
    OPERANDB2.ij[0][2] = (float_q)35.0f;
    OPERANDB2.ij[1][0] = (float_q)36.0f;
    OPERANDB2.ij[1][1] = (float_q)37.0f;
    OPERANDB2.ij[1][2] = (float_q)38.0f;
    OPERANDB2.ij[2][0] = (float_q)39.0f;
    OPERANDB2.ij[2][1] = (float_q)40.0f;
    OPERANDB2.ij[2][2] = (float_q)41.0f;
    OPERANDB2.ij[3][0] = (float_q)26.0f;
    OPERANDB2.ij[3][1] = (float_q)27.0f;
    OPERANDB2.ij[3][2] = (float_q)28.0f;
    FillFourthColumnIfExists(OPERANDB2, (float_q)45.0f, (float_q)46.0f, (float_q)47.0f, (float_q)48.0f);

    // Execution
    QTransformationMatrix<T> matrixAUT;
    OPERANDA1.ProductOperatorImp(OPERANDA2, matrixAUT);
    QTransformationMatrix<T> matrixBUT;
    OPERANDB1.ProductOperatorImp(OPERANDB2, matrixBUT);

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that only the fourth row of the translation matrix participates in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductOperatorImp2_OnlyTheFourthRowOfTranslationMatrixMatters_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp2_OnlyTheFourthRowOfTranslationMatrixMatters_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp2_OnlyTheFourthRowOfTranslationMatrixMatters_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( ProductOperatorImp2_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrixWhiteBox<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTranslationMatrix<QMatrix4x4> OPERAND2 = QTranslationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                        (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                        (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                        (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT;
    OPERAND1.ProductOperatorImp(OPERAND2, matrixUT);

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Template method used by ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Template()
{
    // Preparation
    QTransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = (float_q)17.0f;
    OPERAND2.ij[0][1] = (float_q)18.0f;
    OPERAND2.ij[0][2] = (float_q)19.0f;
    OPERAND2.ij[1][0] = (float_q)20.0f;
    OPERAND2.ij[1][1] = (float_q)21.0f;
    OPERAND2.ij[1][2] = (float_q)22.0f;
    OPERAND2.ij[2][0] = (float_q)23.0f;
    OPERAND2.ij[2][1] = (float_q)24.0f;
    OPERAND2.ij[2][2] = (float_q)25.0f;
    OPERAND2.ij[3][0] = (float_q)26.0f;
    OPERAND2.ij[3][1] = (float_q)27.0f;
    OPERAND2.ij[3][2] = (float_q)28.0f;
    FillFourthColumnIfExists(OPERAND2, (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f);

    QTransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)126.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)132.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)138.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)306.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)321.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)336.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)486.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)510.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)534.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)692.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)726.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)760.0f;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    // Execution
    QTransformationMatrixWhiteBox<T> matrixUT = OPERAND1;
    matrixUT.ProductAssignationOperatorImp(OPERAND2);

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductAssignationOperatorImp_CommonMatricesAreCorrectlyMultiplied_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
QTEST_CASE_TEMPLATE ( ProductAssignationOperatorImp_FourthColumnOfRightOperandDoesntMatter_Test, TQTemplateTypes )
{
    // Preparation
    QTransformationMatrix<T> OPERANDA1;
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
    FillFourthColumnIfExists(OPERANDA1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERANDA2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    QTransformationMatrix<T> OPERANDB1 = OPERANDA1;

    QTransformationMatrix<QMatrix4x4> OPERANDB2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)37.0f,
                                                                                               (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)38.0f,
                                                                                               (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)39.0f,
                                                                                               (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)40.0f));

    // Execution
    QTransformationMatrixWhiteBox<T> matrixAUT = OPERANDA1;
    matrixAUT.ProductAssignationOperatorImp(OPERANDA2);
    QTransformationMatrixWhiteBox<T> matrixBUT = OPERANDB1;
    matrixBUT.ProductAssignationOperatorImp(OPERANDB2);

    // Verification
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
QTEST_CASE( ProductAssignationOperatorImp_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SQFloat::_1;
    OPERAND1.ij[0][1] = SQFloat::_2;
    OPERAND1.ij[0][2] = SQFloat::_3;
    OPERAND1.ij[1][0] = SQFloat::_4;
    OPERAND1.ij[1][1] = SQFloat::_5;
    OPERAND1.ij[1][2] = SQFloat::_6;
    OPERAND1.ij[2][0] = SQFloat::_7;
    OPERAND1.ij[2][1] = SQFloat::_8;
    OPERAND1.ij[2][2] = SQFloat::_9;
    OPERAND1.ij[3][0] = SQFloat::_10;
    OPERAND1.ij[3][1] = (float_q)11.0f;
    OPERAND1.ij[3][2] = (float_q)12.0f;
    FillFourthColumnIfExists(OPERAND1, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    QTransformationMatrix<QMatrix4x4> OPERAND2 = QTransformationMatrix<QMatrix4x4>(QMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)29.0f,
                                                                                              (float_q)20.0f, (float_q)21.0f, (float_q)22.0f, (float_q)30.0f,
                                                                                              (float_q)23.0f, (float_q)24.0f, (float_q)25.0f, (float_q)31.0f,
                                                                                              (float_q)26.0f, (float_q)27.0f, (float_q)28.0f, (float_q)32.0f));

    // Execution
    QTransformationMatrixWhiteBox<QMatrix4x4> matrixUT = OPERAND1;
    matrixUT.ProductAssignationOperatorImp(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Template method used by ProductAssignationOperatorImp_CanBeMultipliedByItself_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void ProductAssignationOperatorImp_CanBeMultipliedByItself_Template()
{
    // Preparation
    QTransformationMatrix<QMatrix4x4> OPERAND;
    OPERAND.ij[0][0] = SQFloat::_1;
    OPERAND.ij[0][1] = SQFloat::_2;
    OPERAND.ij[0][2] = SQFloat::_3;
    OPERAND.ij[1][0] = SQFloat::_4;
    OPERAND.ij[1][1] = SQFloat::_5;
    OPERAND.ij[1][2] = SQFloat::_6;
    OPERAND.ij[2][0] = SQFloat::_7;
    OPERAND.ij[2][1] = SQFloat::_8;
    OPERAND.ij[2][2] = SQFloat::_9;
    OPERAND.ij[3][0] = SQFloat::_10;
    OPERAND.ij[3][1] = (float_q)11.0f;
    OPERAND.ij[3][2] = (float_q)12.0f;
    OPERAND.ij[0][3] = (float_q)13.0f;
    OPERAND.ij[1][3] = (float_q)14.0f;
    OPERAND.ij[2][3] = (float_q)15.0f;
    OPERAND.ij[3][3] = (float_q)16.0f;

    QTransformationMatrix<QMatrix4x4> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)30.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)36.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)42.0f;
    EXPECTED_VALUE.ij[1][0] = (float_q)66.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)81.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)96.0f;
    EXPECTED_VALUE.ij[2][0] = (float_q)102.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)126.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)150.0f;
    EXPECTED_VALUE.ij[3][0] = (float_q)148.0f;
    EXPECTED_VALUE.ij[3][1] = (float_q)182.0f;
    EXPECTED_VALUE.ij[3][2] = (float_q)216.0f;
    EXPECTED_VALUE.ij[0][3] = (float_q)13.0f;
    EXPECTED_VALUE.ij[1][3] = (float_q)14.0f;
    EXPECTED_VALUE.ij[2][3] = (float_q)15.0f;
    EXPECTED_VALUE.ij[3][3] = (float_q)16.0f;

    // Execution
    QTransformationMatrixWhiteBox<QMatrix4x4> matrixUT = OPERAND;
    matrixUT.ProductAssignationOperatorImp(matrixUT);

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
/// Checks that a transformation matrix can be multiplied by itself (same object instance).
/// </summary>
QTEST_CASE_TEMPLATE ( ProductAssignationOperatorImp_CanBeMultipliedByItself_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductAssignationOperatorImp_CanBeMultipliedByItself_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductAssignationOperatorImp_CanBeMultipliedByItself_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp1_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp1_TransformationsAreCorrectlyExtractedFromCommonMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<MatrixType> EXPECTED_TRANSLATION(TRANSLATION, QRotationMatrix3x3::GetIdentity(), QScalingMatrix3x3::GetIdentity());
    const QTransformationMatrix<MatrixType> EXPECTED_ROTATION(QTranslationMatrix<QMatrix4x4>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());
    const QTransformationMatrix<MatrixType> EXPECTED_SCALE(QTranslationMatrix<T>::GetIdentity(), QRotationMatrix3x3::GetIdentity(), SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<MatrixType> translationUT;
    QTransformationMatrix<MatrixType> rotationUT;
    QTransformationMatrix<MatrixType> scaleUT;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp1_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp1_TransformationsAreCorrectlyExtractedFromCommonMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp1_TransformationsAreCorrectlyExtractedFromCommonMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp1_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp1_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Template()
{
    // Preparation
    const QTransformationMatrix<MatrixType> EXPECTED_TRANSFORMATIONS_VALUE = QTransformationMatrix<MatrixType>::GetIdentity();

    const QTransformationMatrixWhiteBox<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QTransformationMatrix<MatrixType> translationUT;
    QTransformationMatrix<MatrixType> rotationUT;
    QTransformationMatrix<MatrixType> scaleUT;
    TRANSFORMATION.DecomposeImp(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( rotationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( scaleUT == EXPECTED_TRANSFORMATIONS_VALUE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp1_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp1_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp1_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<MatrixType> EXPECTED_ROTATION(QTranslationMatrix<MatrixType>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<MatrixType> translationAux;
    QTransformationMatrix<MatrixType> rotationUT;
    QTransformationMatrix<MatrixType> scaleAux;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp1_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp1_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<MatrixType> EXPECTED_ROTATION(QTranslationMatrix<MatrixType>::GetIdentity(), ROTATION, QScalingMatrix3x3::GetIdentity());

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<MatrixType> translationAux;
    QTransformationMatrix<MatrixType> rotationUT;
    QTransformationMatrix<MatrixType> scaleAux;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp1_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp1_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp1_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp1_ReturnedScaleIsAlwaysPositive_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp1_ReturnedScaleIsAlwaysPositive_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<MatrixType> EXPECTED_SCALE(TRANSLATION, ROTATION, QScalingMatrix3x3(SQFloat::_4, SQFloat::_5, SQFloat::_6));

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<MatrixType> translationAux;
    QTransformationMatrix<MatrixType> rotationAux;
    QTransformationMatrix<MatrixType> scaleUT;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp1_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp1_ReturnedScaleIsAlwaysPositive_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp1_ReturnedScaleIsAlwaysPositive_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp1_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp1_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<MatrixType> EXPECTED_SCALE(TRANSLATION, ROTATION, SCALE);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTransformationMatrix<MatrixType> translationAux;
    QTransformationMatrix<MatrixType> rotationAux;
    QTransformationMatrix<MatrixType> scaleUT;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp1_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp1_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp1_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp2_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp2_TransformationsAreCorrectlyExtractedFromCommonMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<MatrixType> EXPECTED_TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = EXPECTED_SCALE * EXPECTED_ROTATION * EXPECTED_TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<MatrixType> translationUT;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp2_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp2_TransformationsAreCorrectlyExtractedFromCommonMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp2_TransformationsAreCorrectlyExtractedFromCommonMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp2_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp2_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Template()
{
    // Preparation
    const QTranslationMatrix<MatrixType> EXPECTED_TRANSLATION = QTranslationMatrix<MatrixType>::GetIdentity();
    const QRotationMatrix3x3 EXPECTED_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 EXPECTED_SCALE = QScalingMatrix3x3::GetIdentity();

    const QTransformationMatrixWhiteBox<T> TRANSFORMATION = QTransformationMatrix<T>::GetIdentity();

    // Execution
    QTranslationMatrix<MatrixType> translationUT;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleUT;
    TRANSFORMATION.DecomposeImp(translationUT, rotationUT, scaleUT);

    // Verification
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp2_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp2_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp2_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<MatrixType> translationAux;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleAux;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<MatrixType> translationAux;
    QRotationMatrix3x3 rotationUT;
    QScalingMatrix3x3 scaleAux;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationUT, scaleAux);

    // Verification
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp2_ReturnedScaleIsAlwaysPositive_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp2_ReturnedScaleIsAlwaysPositive_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(-SQFloat::_4, -SQFloat::_5, -SQFloat::_6);

    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<MatrixType> translationAux;
    QRotationMatrix3x3 rotationAux;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp2_ReturnedScaleIsAlwaysPositive_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp2_ReturnedScaleIsAlwaysPositive_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp2_ReturnedScaleIsAlwaysPositive_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by DecomposeImp2_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void DecomposeImp2_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 EXPECTED_SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = EXPECTED_SCALE * ROTATION * TRANSLATION;
    QTransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // Execution
    QTranslationMatrix<MatrixType> translationAux;
    QRotationMatrix3x3 rotationAux;
    QScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.DecomposeImp(translationAux, rotationAux, scaleUT);

    // Verification
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
QTEST_CASE_TEMPLATE ( DecomposeImp2_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TQTemplateTypes )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    DecomposeImp2_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    DecomposeImp2_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Template<T, QMatrix4x4>();
}

// End - Test Suite: QTransformationMatrix
QTEST_SUITE_END()
