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

#include "QBaseHexahedron.h"
#include "QVector3.h"
#include "QVector4.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector3, QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QBaseHexahedron_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_D[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_E[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_F[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_G[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };
    float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

	// [Execution]
    QBaseHexahedron<T> hexahedronUT;

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if copy constructor sets hexahedron's points properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_1, -SQFloat::_2, -SQFloat::_3, -SQFloat::_4 };
    float_q VECTOR_COMPONENTS_D[] = { -SQFloat::_5, -SQFloat::_6, -SQFloat::_7, -SQFloat::_8 };
    float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1 - SQFloat::_0_5, SQFloat::_2 - SQFloat::_0_5, SQFloat::_3 - SQFloat::_0_5, SQFloat::_4 - SQFloat::_0_5 };
    float_q VECTOR_COMPONENTS_F[] = { SQFloat::_5 - SQFloat::_0_5, SQFloat::_6 - SQFloat::_0_5, SQFloat::_7 - SQFloat::_0_5, SQFloat::_8 - SQFloat::_0_5 };
    float_q VECTOR_COMPONENTS_G[] = { SQFloat::_1 + SQFloat::_0_5, SQFloat::_2 + SQFloat::_0_5, SQFloat::_3 + SQFloat::_0_5, SQFloat::_4 + SQFloat::_0_5 };
    float_q VECTOR_COMPONENTS_H[] = { SQFloat::_5 + SQFloat::_0_5, SQFloat::_6 + SQFloat::_0_5, SQFloat::_7 + SQFloat::_0_5, SQFloat::_8 + SQFloat::_0_5 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

    const QBaseHexahedron<T> EXPECTED_HEXAHEDRON(EXPECTED_VALUE_FOR_A, 
                                                 EXPECTED_VALUE_FOR_B, 
                                                 EXPECTED_VALUE_FOR_C, 
                                                 EXPECTED_VALUE_FOR_D, 
                                                 EXPECTED_VALUE_FOR_E, 
                                                 EXPECTED_VALUE_FOR_F, 
                                                 EXPECTED_VALUE_FOR_G, 
                                                 EXPECTED_VALUE_FOR_H);

	// [Execution]
    QBaseHexahedron<T> hexahedronUT(EXPECTED_HEXAHEDRON);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { -SQFloat::_1, -SQFloat::_2, -SQFloat::_3, -SQFloat::_4 };
    float_q VECTOR_COMPONENTS_D[] = { -SQFloat::_5, -SQFloat::_6, -SQFloat::_7, -SQFloat::_8 };
    float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1 - SQFloat::_0_5, SQFloat::_2 - SQFloat::_0_5, SQFloat::_3 - SQFloat::_0_5, SQFloat::_4 - SQFloat::_0_5 };
    float_q VECTOR_COMPONENTS_F[] = { SQFloat::_5 - SQFloat::_0_5, SQFloat::_6 - SQFloat::_0_5, SQFloat::_7 - SQFloat::_0_5, SQFloat::_8 - SQFloat::_0_5 };
    float_q VECTOR_COMPONENTS_G[] = { SQFloat::_1 + SQFloat::_0_5, SQFloat::_2 + SQFloat::_0_5, SQFloat::_3 + SQFloat::_0_5, SQFloat::_4 + SQFloat::_0_5 };
    float_q VECTOR_COMPONENTS_H[] = { SQFloat::_5 + SQFloat::_0_5, SQFloat::_6 + SQFloat::_0_5, SQFloat::_7 + SQFloat::_0_5, SQFloat::_8 + SQFloat::_0_5 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

	// [Execution]
    QBaseHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A, 
                                    EXPECTED_VALUE_FOR_B, 
                                    EXPECTED_VALUE_FOR_C, 
                                    EXPECTED_VALUE_FOR_D, 
                                    EXPECTED_VALUE_FOR_E, 
                                    EXPECTED_VALUE_FOR_F, 
                                    EXPECTED_VALUE_FOR_G, 
                                    EXPECTED_VALUE_FOR_H);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if the hexahedron is correctly built from 2 common points that represent two of the opposite vertices.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ItsBuiltCorrectlyFromTwoCommonPoints_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_2, SQFloat::_1, SQFloat::_4 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_2, SQFloat::_1, SQFloat::_4 };
    float_q VECTOR_COMPONENTS_D[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_0, SQFloat::_3, SQFloat::_9 };
    float_q VECTOR_COMPONENTS_F[] = { SQFloat::_3, SQFloat::_0, SQFloat::_3, SQFloat::_9 };
    float_q VECTOR_COMPONENTS_G[] = { SQFloat::_3, SQFloat::_0, SQFloat::_1, SQFloat::_9 };
    float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_0, SQFloat::_1, SQFloat::_9 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

	// [Execution]
    QBaseHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A, 
                                    EXPECTED_VALUE_FOR_G);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if all the points of the hexahedron coincide in space when A and G points are the same.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_AllPointsCoincideWhenInputPointsCoincide_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    float_q VECTOR_COMPONENTS_EVERY_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_ALL_POINTS(VECTOR_COMPONENTS_EVERY_POINT);

	// [Execution]
    QBaseHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_ALL_POINTS, 
                                    EXPECTED_VALUE_FOR_ALL_POINTS);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_ALL_POINTS);
}

/// <summary>
/// Checks if the hexahedron is correctly built from 3 common dimension lengths values and a central point.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_ItsBuiltCorrectlyFromCommonLengthsAndCentralPoint_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_1, SQFloat::_2, SQFloat::_1, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_2, SQFloat::_1, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, -SQFloat::_2, SQFloat::_3, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, -SQFloat::_2, SQFloat::_1, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, -SQFloat::_2, SQFloat::_1, SQFloat::_10 };
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2 + SQFloat::_0_5, SQFloat::_0, SQFloat::_2, SQFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

    const float_q INPUT_X = SQFloat::_3;
    const float_q INPUT_Y = SQFloat::_4;
    const float_q INPUT_Z = SQFloat::_2;
    const T INPUT_CENTER(VECTOR_COMPONENTS_CENTER);

	// [Execution]
    QBaseHexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if the hexahedron is correctly built from 3 common dimension lengths values and a central point.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor5_AllPointsCoincideWithCoordinateOriginWhenLengthsEqualZero_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    const T EXPECTED_VALUE_FOR_ALL_POINTS = T::GetNullVector();

    const float_q INPUT_X = SQFloat::_0;
    const float_q INPUT_Y = SQFloat::_0;
    const float_q INPUT_Z = SQFloat::_0;
    const T INPUT_CENTER = T::GetNullVector();

	// [Execution]
    QBaseHexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_ALL_POINTS);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND = QBaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND =  QBaseHexahedron<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5), 
                                                                T(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5) );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TQTemplateTypes )
{
    // [Preparation]
    const QBaseHexahedron<T> LEFT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );
    const QBaseHexahedron<T> RIGHT_OPERAND = QBaseHexahedron<T>( T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon), T(SQFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseHexahedron
QTEST_SUITE_END()
