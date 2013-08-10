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

#include "QHexahedron.h"

using Kinesis::QuimeraEngine::Tools::Math::QHexahedron;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector3, QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QHexahedron_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // Preparation
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

	// Execution
    QHexahedron<T> hexahedronUT;

    // Verification
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
    // Preparation
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

    const QHexahedron<T> EXPECTED_HEXAHEDRON(EXPECTED_VALUE_FOR_A,
                                             EXPECTED_VALUE_FOR_B,
                                             EXPECTED_VALUE_FOR_C,
                                             EXPECTED_VALUE_FOR_D,
                                             EXPECTED_VALUE_FOR_E,
                                             EXPECTED_VALUE_FOR_F,
                                             EXPECTED_VALUE_FOR_G,
                                             EXPECTED_VALUE_FOR_H);

	// Execution
    QHexahedron<T> hexahedronUT(EXPECTED_HEXAHEDRON);

    // Verification
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
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // Preparation
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

	// Execution
    QHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A,
                                EXPECTED_VALUE_FOR_B,
                                EXPECTED_VALUE_FOR_C,
                                EXPECTED_VALUE_FOR_D,
                                EXPECTED_VALUE_FOR_E,
                                EXPECTED_VALUE_FOR_F,
                                EXPECTED_VALUE_FOR_G,
                                EXPECTED_VALUE_FOR_H);

    // Verification
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
QTEST_CASE_TEMPLATE ( Constructor5_ItsBuiltCorrectlyFromTwoCommonPoints_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
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

	// Execution
    QHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A,
                                EXPECTED_VALUE_FOR_G);

    // Verification
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
QTEST_CASE_TEMPLATE ( Constructor5_AllPointsCoincideWhenInputPointsCoincide_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
    float_q VECTOR_COMPONENTS_EVERY_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_ALL_POINTS(VECTOR_COMPONENTS_EVERY_POINT);

	// Execution
    QHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_ALL_POINTS,
                                EXPECTED_VALUE_FOR_ALL_POINTS);

    // Verification
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
QTEST_CASE_TEMPLATE ( Constructor6_ItsBuiltCorrectlyFromCommonLengthsAndCentralPoint_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
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

	// Execution
    QHexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

    // Verification
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
QTEST_CASE_TEMPLATE ( Constructor6_AllPointsCoincideWithCoordinateOriginWhenLengthsEqualZero_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
    const T EXPECTED_VALUE_FOR_ALL_POINTS = T::GetZeroVector();

    const float_q INPUT_X = SQFloat::_0;
    const float_q INPUT_Y = SQFloat::_0;
    const float_q INPUT_Z = SQFloat::_0;
    const T INPUT_CENTER = T::GetZeroVector();

	// Execution
    QHexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

    // Verification
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
/// Checks if it returns a unit cube set at the coordinate origin.
/// </summary>
QTEST_CASE_TEMPLATE ( GetUnitCube_ItReturnsWhatExpected_Test, TQTemplateTypes )
{
    // Preparation
    const float_q POINT_COMPONENTS_A[] = {-SQFloat::_0_5, SQFloat::_0_5, SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_B[] = {-SQFloat::_0_5, SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_C[] = {SQFloat::_0_5, SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_D[] = {SQFloat::_0_5, SQFloat::_0_5, SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_E[] = {-SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_F[] = {SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_G[] = {SQFloat::_0_5, -SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };
    const float_q POINT_COMPONENTS_H[] = {-SQFloat::_0_5, -SQFloat::_0_5, -SQFloat::_0_5, SQFloat::_1 };

    const QHexahedron<T> UNIT_CUBE = QHexahedron<T>( T(POINT_COMPONENTS_A),
                                                     T(POINT_COMPONENTS_B),
                                                     T(POINT_COMPONENTS_C),
                                                     T(POINT_COMPONENTS_D),
                                                     T(POINT_COMPONENTS_E),
                                                     T(POINT_COMPONENTS_F),
                                                     T(POINT_COMPONENTS_G),
                                                     T(POINT_COMPONENTS_H) );

	// Execution
    QHexahedron<T> hexahedron = QHexahedron<T>::GetUnitCube();

    // Verification
    BOOST_CHECK(hexahedron.A == UNIT_CUBE.A);
    BOOST_CHECK(hexahedron.B == UNIT_CUBE.B);
    BOOST_CHECK(hexahedron.C == UNIT_CUBE.C);
    BOOST_CHECK(hexahedron.D == UNIT_CUBE.D);
    BOOST_CHECK(hexahedron.E == UNIT_CUBE.E);
    BOOST_CHECK(hexahedron.F == UNIT_CUBE.F);
    BOOST_CHECK(hexahedron.G == UNIT_CUBE.G);
    BOOST_CHECK(hexahedron.H == UNIT_CUBE.H);
}

/// <summary>
/// Checks if points are correctly copied.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBaseHexahedron;

    // Preparation
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

	// Execution
    QHexahedron<T> hexahedronUT;
    hexahedronUT = EXPECTED_HEXAHEDRON;

    // Verification
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
/// Checks that the hexahedron is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_HexahedronIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // Preparation
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

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)-5.5511151231257827e-017, (float_q)-0.70710678118654746, (float_q)-0.50000000000000011, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)0.70710678118654746, (float_q)-2.7755575615628914e-017, (float_q)-0.49999999999999994, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)1.6653345369377348e-016, (float_q)0.70710678118654757, (float_q)-0.49999999999999989, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { (float_q)-0.70710678118654735, (float_q)1.2490009027033011e-016, (float_q)-0.50000000000000011, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { (float_q)-1.6653345369377348e-016, (float_q)-0.70710678118654757, (float_q)0.49999999999999989, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { (float_q)-0.70710678118654746, (float_q)2.7755575615628914e-017, (float_q)0.49999999999999994, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { (float_q)5.5511151231257827e-017, (float_q)0.70710678118654746, (float_q)0.50000000000000011, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { (float_q)0.70710678118654735, (float_q)-1.2490009027033011e-016, (float_q)0.50000000000000011, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);

}

/// <summary>
/// Checks that a hexahedron is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_HexahedronIsNotRotatedWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion::GetIdentity();

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q NULL_VECTOR_COMPONENTS[] = {SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that the hexahedron is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_HexahedronIsCorrectlyTransformedByCommonQuaternions_Test, TQTemplateTypes )
{
    // Preparation
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

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)3.8284271247461898, (float_q)2.707106781186547, (float_q)4.5, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)4.5355339059327378, (float_q)3.414213562373094, (float_q)4.5, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)3.8284271247461898, (float_q)4.1213203435596419, (float_q)4.5, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { (float_q)3.1213203435596424, (float_q)3.4142135623730945, (float_q)4.5, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { (float_q)3.8284271247461898, (float_q)2.7071067811865466, (float_q)5.5, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { (float_q)3.1213203435596424, (float_q)3.4142135623730945, (float_q)5.5, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { (float_q)3.8284271247461898, (float_q)4.1213203435596419, (float_q)5.5, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { (float_q)4.5355339059327378, (float_q)3.4142135623730940, (float_q)5.5, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not rotated when the quaternion equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_HexahedronIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion::GetIdentity();

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the position of the pivot point when the quaternion is null.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QQuaternion ROTATION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_D = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_E = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_F = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_G = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_H = PIVOT_POINT;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly translated using common translation vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_5, SQFloat::_7, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_4, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_5, SQFloat::_3, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { SQFloat::_0, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_3, SQFloat::_7, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const QVector3 TRANSLATION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate1_HexahedronIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QVector3 TRANSLATION = QVector3::GetZeroVector();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly translated using common translation values.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonValues_Test, TQTemplateTypes )
{
    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_5, SQFloat::_7, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_4, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_5, SQFloat::_3, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { SQFloat::_0, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_3, SQFloat::_7, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_q TRANSLATION_X = SQFloat::_1;
    const float_q TRANSLATION_Y = SQFloat::_2;
    const float_q TRANSLATION_Z = SQFloat::_3;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate2_HexahedronIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_q TRANSLATION_X = SQFloat::_0;
    const float_q TRANSLATION_Y = SQFloat::_0;
    const float_q TRANSLATION_Z = SQFloat::_0;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_4,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_8,  SQFloat::_6,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_6,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_10, (float_q)18.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_4,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_2,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_4,  (float_q)12.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_2,  (float_q)12.0, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q NULL_VECTOR_COMPONENTS[] = {SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

    const QVector3 SCALE = QVector3::GetZeroVector();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_4,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_8,  SQFloat::_6,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_6,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_10, (float_q)18.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_4,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_2,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_4,  (float_q)12.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_2,  (float_q)12.0, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q NULL_VECTOR_COMPONENTS[] = {SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_6,  SQFloat::_0,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_4,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_8, (float_q)12.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_0,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2,  SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_0,  SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const QVector3 SCALE = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QVector3 SCALE = QVector3::GetVectorOfOnes();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const QVector3 SCALE = QVector3::GetZeroVector();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.B == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.C == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.D == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.E == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.F == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.G == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.H == PIVOT_POINT);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_6,  SQFloat::_0,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_4,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_8, (float_q)12.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_0,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2,  SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_0,  SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_2;
    const float_q SCALE_Z = SQFloat::_3;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_q SCALE_X = SQFloat::_1;
    const float_q SCALE_Y = SQFloat::_1;
    const float_q SCALE_Z = SQFloat::_1;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_q SCALE_X = SQFloat::_0;
    const float_q SCALE_Y = SQFloat::_0;
    const float_q SCALE_Z = SQFloat::_0;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.B == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.C == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.D == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.E == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.F == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.G == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.H == PIVOT_POINT);
}

/// <summary>
/// Checks that it returns the expected list of planes from a common hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPlanes_ReturnsExpectedPlanesFromCommonHexahedron_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const QPlane EXPECTED_PLANE_ABCD = QPlane(SQFloat::_0,  SQFloat::_1,  SQFloat::_0, -SQFloat::_0_5);
    const QPlane EXPECTED_PLANE_EFGH = QPlane(SQFloat::_0,  -SQFloat::_1, SQFloat::_0, -SQFloat::_0_5);
    const QPlane EXPECTED_PLANE_AEFD = QPlane(SQFloat::_0,  SQFloat::_0,  SQFloat::_1, -SQFloat::_0_5);
    const QPlane EXPECTED_PLANE_ABHE = QPlane(-SQFloat::_1, SQFloat::_0,  SQFloat::_0, -SQFloat::_0_5);
    const QPlane EXPECTED_PLANE_BCGH = QPlane(SQFloat::_0,  SQFloat::_0, -SQFloat::_1, -SQFloat::_0_5);
    const QPlane EXPECTED_PLANE_CDFG = QPlane(SQFloat::_1,  SQFloat::_0,  SQFloat::_0, -SQFloat::_0_5);

	// Execution
    QPlane arOutputPlanes[6];
    HEXAHEDRON.GetPlanes(arOutputPlanes);

    // Verification
    BOOST_CHECK(arOutputPlanes[0] == EXPECTED_PLANE_ABCD);
    BOOST_CHECK(arOutputPlanes[1] == EXPECTED_PLANE_EFGH);
    BOOST_CHECK(arOutputPlanes[2] == EXPECTED_PLANE_AEFD);
    BOOST_CHECK(arOutputPlanes[3] == EXPECTED_PLANE_ABHE);
    BOOST_CHECK(arOutputPlanes[4] == EXPECTED_PLANE_BCGH);
    BOOST_CHECK(arOutputPlanes[5] == EXPECTED_PLANE_CDFG);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPlanes_AssertionFailsWhenAllVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // Preparation
    const float_q POINT_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);
    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;
    QPlane arOutputPlanes[6];

    try
    {
        HEXAHEDRON.GetPlanes(arOutputPlanes);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the list of planes is null.
/// </summary>
QTEST_CASE_TEMPLATE ( GetPlanes_AssertionFailsWhenListOfPlanesIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();
    const bool ASSERTION_FAILED = true;
    QPlane* pNullList = null_q;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.GetPlanes(pNullList);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns True when a common point is inside the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenCommonPointIsInsideTheHexahedron_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT = HEXAHEDRON.A.Lerp(SQFloat::_0_5, HEXAHEDRON.G);
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = HEXAHEDRON.Contains(POINT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the point belongs to one of the faces of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenPointBelongsToAFaceOfHexahedron_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT_ABCD = HEXAHEDRON.A.Lerp(SQFloat::_0_5, HEXAHEDRON.C);
    const T POINT_EFGH = HEXAHEDRON.E.Lerp(SQFloat::_0_5, HEXAHEDRON.G);
    const T POINT_AEFD = HEXAHEDRON.A.Lerp(SQFloat::_0_5, HEXAHEDRON.F);
    const T POINT_ABHE = HEXAHEDRON.A.Lerp(SQFloat::_0_5, HEXAHEDRON.H);
    const T POINT_BCGH = HEXAHEDRON.B.Lerp(SQFloat::_0_5, HEXAHEDRON.G);
    const T POINT_CDFG = HEXAHEDRON.C.Lerp(SQFloat::_0_5, HEXAHEDRON.F);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultABCD = HEXAHEDRON.Contains(POINT_ABCD);
    bool bResultEFGH = HEXAHEDRON.Contains(POINT_EFGH);
    bool bResultAEFD = HEXAHEDRON.Contains(POINT_AEFD);
    bool bResultABHE = HEXAHEDRON.Contains(POINT_ABHE);
    bool bResultBCGH = HEXAHEDRON.Contains(POINT_BCGH);
    bool bResultCDFG = HEXAHEDRON.Contains(POINT_CDFG);

    // Verification
    BOOST_CHECK_EQUAL(bResultABCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultEFGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAEFD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultABHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBCGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCDFG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the point belongs to one of the edges of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenPointBelongsToAnEdgeOfHexahedron_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT_AB = HEXAHEDRON.A.Lerp(SQFloat::_0_5, HEXAHEDRON.B);
    const T POINT_BC = HEXAHEDRON.B.Lerp(SQFloat::_0_5, HEXAHEDRON.C);
    const T POINT_CD = HEXAHEDRON.C.Lerp(SQFloat::_0_5, HEXAHEDRON.D);
    const T POINT_DA = HEXAHEDRON.D.Lerp(SQFloat::_0_5, HEXAHEDRON.A);
    const T POINT_EF = HEXAHEDRON.E.Lerp(SQFloat::_0_5, HEXAHEDRON.F);
    const T POINT_FG = HEXAHEDRON.F.Lerp(SQFloat::_0_5, HEXAHEDRON.G);
    const T POINT_GH = HEXAHEDRON.G.Lerp(SQFloat::_0_5, HEXAHEDRON.H);
    const T POINT_HE = HEXAHEDRON.H.Lerp(SQFloat::_0_5, HEXAHEDRON.E);
    const T POINT_AE = HEXAHEDRON.A.Lerp(SQFloat::_0_5, HEXAHEDRON.E);
    const T POINT_DF = HEXAHEDRON.D.Lerp(SQFloat::_0_5, HEXAHEDRON.F);
    const T POINT_BH = HEXAHEDRON.B.Lerp(SQFloat::_0_5, HEXAHEDRON.H);
    const T POINT_CG = HEXAHEDRON.C.Lerp(SQFloat::_0_5, HEXAHEDRON.G);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultAB = HEXAHEDRON.Contains(POINT_AB);
    bool bResultBC = HEXAHEDRON.Contains(POINT_BC);
    bool bResultCD = HEXAHEDRON.Contains(POINT_CD);
    bool bResultDA = HEXAHEDRON.Contains(POINT_DA);
    bool bResultEF = HEXAHEDRON.Contains(POINT_EF);
    bool bResultFG = HEXAHEDRON.Contains(POINT_FG);
    bool bResultGH = HEXAHEDRON.Contains(POINT_GH);
    bool bResultHE = HEXAHEDRON.Contains(POINT_HE);
    bool bResultAE = HEXAHEDRON.Contains(POINT_AE);
    bool bResultDF = HEXAHEDRON.Contains(POINT_DF);
    bool bResultBH = HEXAHEDRON.Contains(POINT_BH);
    bool bResultCG = HEXAHEDRON.Contains(POINT_CG);

    // Verification
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common point is outside the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenCommonPointIsOutsideTheHexahedron_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT = HEXAHEDRON.A.Lerp(SQFloat::_2, HEXAHEDRON.G);
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = HEXAHEDRON.Contains(POINT);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the point coincides with a vertex of the hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenPointCoincidesWithVertex_Test, TQTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_0, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT_A = HEXAHEDRON.A;
    const T POINT_B = HEXAHEDRON.B;
    const T POINT_C = HEXAHEDRON.C;
    const T POINT_D = HEXAHEDRON.D;
    const T POINT_E = HEXAHEDRON.E;
    const T POINT_F = HEXAHEDRON.F;
    const T POINT_G = HEXAHEDRON.G;
    const T POINT_H = HEXAHEDRON.H;

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultA = HEXAHEDRON.Contains(POINT_A);
    bool bResultB = HEXAHEDRON.Contains(POINT_B);
    bool bResultC = HEXAHEDRON.Contains(POINT_C);
    bool bResultD = HEXAHEDRON.Contains(POINT_D);
    bool bResultE = HEXAHEDRON.Contains(POINT_E);
    bool bResultF = HEXAHEDRON.Contains(POINT_F);
    bool bResultG = HEXAHEDRON.Contains(POINT_G);
    bool bResultH = HEXAHEDRON.Contains(POINT_H);

    // Verification
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_AssertionFailsWhenAllVerticesCoincide_Test, TQTemplateTypes )
{

    // Preparation
    const float_q POINT_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.Contains(POINT);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that it returns "both sides" when the hexahedron and the plane intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsBothSidesWhenHexahedronAndPlaneIntersect_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_2);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_BothSides;

	// Execution
    EQSpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the hexahedron is completely in the positive side of the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsPositiveSideWhenHexahedronIsInPositiveSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_2);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// Execution
    EQSpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the hexahedron is completely in the negtive side of the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsNegativeSideWhenHexahedronIsInNegativeSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_10);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// Execution
    EQSpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when the hexahedron is completely contained in the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsContainedWhenHexahedronBelongsToPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_1);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_Contained;

	// Execution
    EQSpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when some part of the hexahedron belongs to the plane and the rest belongs to the positive side.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsPositiveSideWhenSomePartOfTheHexahedronBelongsToPlaneAndTheRestToPositiveSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_5, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_5, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_5, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_5, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_1);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_PositiveSide;

	// Execution
    EQSpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when some part of the hexahedron belongs to the plane and the rest belongs to the negative side.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsNegativeSideWhenSomePartOfTheHexahedronBelongsToPlaneAndTheRestToNegativeSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::EQSpaceRelation;
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_1);

    const EQSpaceRelation EXPECTED_RESULT = EQSpaceRelation::E_NegativeSide;

	// Execution
    EQSpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // Verification
    BOOST_CHECK_EQUAL(eResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_AssertionFailsWhenAllVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_1);
    const float_q POINT_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.SpaceRelation(PLANE);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( SpaceRelation_AssertionFailsWhenThePlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.SpaceRelation(PLANE);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the hexahedron is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_HexahedronIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // Preparation
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

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)0.70710678118654746, (float_q)-0.5, (float_q)2.4894981252573997e-017, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)0.70710678118654746, (float_q)0.5, (float_q)8.6127321209941663e-017, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)5.5511151231257821e-017, (float_q)0.5, (float_q)-0.70710678118654746, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { (float_q)5.5511151231257827e-017, (float_q)-0.49999999999999994, (float_q)-0.70710678118654746, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { (float_q)-5.5511151231257821e-017, (float_q)-0.5, (float_q)0.70710678118654746, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { (float_q)-0.70710678118654746, (float_q)-0.5, (float_q)-8.6127321209941663e-017, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { (float_q)-0.70710678118654746, (float_q)0.5, (float_q)-2.4894981252573997e-017, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { (float_q)-5.5511151231257827e-017, (float_q)0.49999999999999994, (float_q)0.70710678118654746, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not rotated when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_HexahedronIsNotRotatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetIdentity();

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q NULL_VECTOR_COMPONENTS[] = {SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1};

    const T EXPECTED_VALUE_FOR_A = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_B = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_C = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_D = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_E = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_F = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_G = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_H = T(NULL_VECTOR_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the hexahedron is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_HexahedronIsCorrectlyTransformedByCommonRotationMatrix_Test, TQTemplateTypes )
{
    // Preparation
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

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)0.99999999999999978, (float_q)4.5, (float_q)5.1213203435596428, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)0.99999999999999978, (float_q)5.5, (float_q)5.1213203435596428, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)0.29289321881345232, (float_q)5.5, (float_q)4.4142135623730949, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { (float_q)0.29289321881345232, (float_q)4.5, (float_q)4.4142135623730949, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { (float_q)0.29289321881345232, (float_q)4.5, (float_q)5.8284271247461898, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { (float_q)-0.41421356237309515, (float_q)4.5, (float_q)5.1213203435596419, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { (float_q)-0.41421356237309515, (float_q)5.5, (float_q)5.1213203435596419, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { (float_q)0.29289321881345232, (float_q)5.5, (float_q)5.8284271247461898, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not rotated when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_HexahedronIsNotRotatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetIdentity();

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the position of the pivot point when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPointWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_D = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_E = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_F = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_G = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_H = PIVOT_POINT;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Template method used by Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3, SQFloat::_1, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0, SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_3, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_3, SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_5, SQFloat::_7, SQFloat::_9, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_4, SQFloat::_4, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_5, SQFloat::_3, SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { SQFloat::_0, SQFloat::_4, SQFloat::_7, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_3, SQFloat::_7, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly translated using common translation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetZeroMatrix();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when translation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_CommonHexahedronIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_4,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_8,  SQFloat::_6,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_6,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_10, (float_q)18.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_4,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_2,  SQFloat::_9,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_4,  (float_q)12.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_2,  (float_q)12.0, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when the matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_HexahedronIsNotTranslatedWhenMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetIdentity();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the matrix equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TQTemplateTypes )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q NULL_VECTOR_COMPONENTS[] = {SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_4, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_5, SQFloat::_6, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2, SQFloat::_4, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_1, SQFloat::_4, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_1,  SQFloat::_2,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_3,  SQFloat::_6,  SQFloat::_0,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_2,  SQFloat::_4,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4,  SQFloat::_8, (float_q)12.0, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_3,  SQFloat::_2,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4,  SQFloat::_0,  SQFloat::_3,   SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { -SQFloat::_1, SQFloat::_2,  SQFloat::_6, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_0,  SQFloat::_0,  SQFloat::_6, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetIdentity();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3::GetZeroMatrix();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.B == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.C == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.D == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.E == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.F == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.G == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.H == PIVOT_POINT);
}

/// <summary>
/// Template method used by Transform_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)3.1490485194281401, (float_q)4.5, (float_q)-6.9722718241315027, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)3.1490485194281401, (float_q)3.5, (float_q)-6.9722718241315027, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)2.9722718241315027, (float_q)3.5, (float_q)-7.1490485194281401, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { (float_q)2.9722718241315027, (float_q)4.5, (float_q)-7.1490485194281401, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { (float_q)1.0277281758684971, (float_q)4.5, (float_q)-4.8509514805718599, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { (float_q)0.8509514805718601, (float_q)4.5, (float_q)-5.0277281758684973, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { (float_q)0.8509514805718601, (float_q)3.5, (float_q)-5.0277281758684973, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { (float_q)1.0277281758684971, (float_q)3.5, (float_q)-4.8509514805718599, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

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

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q NULL_VECTOR_COMPONENTS[] = {SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1};

    const T EXPECTED_VALUE_FOR_A = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_B = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_C = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_D = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_E = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_F = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_G = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_H = T(NULL_VECTOR_COMPONENTS);

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetZeroMatrix();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that all the vertices of the hexahedron are moved to the coordinate origin when transformation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( Transform_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { (float_q)0.083184527605490999, (float_q)3.5, (float_q)0.44714555828441904, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { (float_q)0.083184527605490999, (float_q)2.5, (float_q)0.44714555828441904, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { (float_q)-0.093592167691145978, (float_q)2.5, (float_q)0.27036886298778207, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { (float_q)-0.093592167691145978, (float_q)3.5, (float_q)0.27036886298778207, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { (float_q)-2.0381358159541509, (float_q)3.4999999999999996, (float_q)2.5684659018440614, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { (float_q)-2.2149125112507884, (float_q)3.4999999999999996, (float_q)2.391689206547424, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { (float_q)-2.2149125112507884, (float_q)2.4999999999999996, (float_q)2.391689206547424, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { (float_q)-2.0381358159541509, (float_q)2.4999999999999996, (float_q)2.5684659018440614, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

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

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly transformed using common transformation matrix.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_D = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_E = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_F = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_G = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_H = PIVOT_POINT;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetZeroMatrix();

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that all the vertices of the hexahedron are moved to the coordinate origin when transformation is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    // Preparation
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const QTransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

    const float_q PIVOT_COMPONENTS[] = {SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not transformed when matrix equals identity.
/// </summary>
QTEST_CASE_TEMPLATE ( TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, QMatrix4x4>();
}

/// <summary>
/// Checks that it returns true when the hexahedrons share one vertex.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenHexahedronsShareVertex_Test, TQTemplateTypes )
{
    // Explanation: Let's say we have a cube compound of 19 smaller cubes (every face is made of 9 smaller faces).
    //              We take the central cube as the operand 1.
    //              The operand 2 will be one of the other cubes that only shares one vertex with the central one.
    //              So we have 8 cubes that can act as the operand 2, at the corners of the main cube.
    //              This way we can test for the intersection of the shared vertices.
    //              To test all the possible vertex intersections between operands 2 and operand 1, we can
    //              rotate every operand 2 eight times, once for every vertex, keeping the operand 1 fixed.
    //              Since it's a commutative operation, we can skip calculations for 4 of the operands 2. Notice
    //              that inverting the operands we are testing the same case as if we used the opposite small cube.

    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q QUARTER_ROTATION = SQAngle::_90;
    const float_q HALF_ROTATION = SQAngle::_180;
    const float_q THREEQUARTERS_ROTATION = SQAngle::_270;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q QUARTER_ROTATION = SQAngle::_HalfPi;
    const float_q HALF_ROTATION = SQAngle::_Pi;
    const float_q THREEQUARTERS_ROTATION = SQAngle::_3HalfsPi;
#endif

    const QHexahedron<T> HEXAHEDRON2 = QHexahedron<T>::GetUnitCube();
    const QHexahedron<T> HEXAHEDRON1 = HEXAHEDRON2;

    const QVector3 TRANSLATION_POS1 = QVector3(-SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector3 TRANSLATION_POS2 = QVector3(-SQFloat::_1, -SQFloat::_1, SQFloat::_1);
    const QVector3 TRANSLATION_POS3 = QVector3(-SQFloat::_1, SQFloat::_1, -SQFloat::_1);
    const QVector3 TRANSLATION_POS4 = QVector3(-SQFloat::_1, -SQFloat::_1, -SQFloat::_1);

    const QHexahedron<T> HEXAHEDRON1_POS1_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS1);
    const QHexahedron<T> HEXAHEDRON1_POS1_ROT2 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS1);
    const QHexahedron<T> HEXAHEDRON1_POS1_ROT3 = HEXAHEDRON1.Rotate(QQuaternion(HALF_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS1);
    const QHexahedron<T> HEXAHEDRON1_POS1_ROT4 = HEXAHEDRON1.Rotate(QQuaternion(THREEQUARTERS_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS1);
    const QHexahedron<T> HEXAHEDRON1_POS1_ROT5 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS1);
    const QHexahedron<T> HEXAHEDRON1_POS1_ROT6 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS1);
    const QHexahedron<T> HEXAHEDRON1_POS1_ROT7 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS1);
    const QHexahedron<T> HEXAHEDRON1_POS1_ROT8 = HEXAHEDRON1.Rotate(QQuaternion(-QUARTER_ROTATION, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS1);

    const QHexahedron<T> HEXAHEDRON1_POS2_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS2);
    const QHexahedron<T> HEXAHEDRON1_POS2_ROT2 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS2);
    const QHexahedron<T> HEXAHEDRON1_POS2_ROT3 = HEXAHEDRON1.Rotate(QQuaternion(HALF_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS2);
    const QHexahedron<T> HEXAHEDRON1_POS2_ROT4 = HEXAHEDRON1.Rotate(QQuaternion(THREEQUARTERS_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS2);
    const QHexahedron<T> HEXAHEDRON1_POS2_ROT5 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS2);
    const QHexahedron<T> HEXAHEDRON1_POS2_ROT6 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS2);
    const QHexahedron<T> HEXAHEDRON1_POS2_ROT7 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS2);
    const QHexahedron<T> HEXAHEDRON1_POS2_ROT8 = HEXAHEDRON1.Rotate(QQuaternion(-QUARTER_ROTATION, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS2);

    const QHexahedron<T> HEXAHEDRON1_POS3_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS3);
    const QHexahedron<T> HEXAHEDRON1_POS3_ROT2 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS3);
    const QHexahedron<T> HEXAHEDRON1_POS3_ROT3 = HEXAHEDRON1.Rotate(QQuaternion(HALF_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS3);
    const QHexahedron<T> HEXAHEDRON1_POS3_ROT4 = HEXAHEDRON1.Rotate(QQuaternion(THREEQUARTERS_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS3);
    const QHexahedron<T> HEXAHEDRON1_POS3_ROT5 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS3);
    const QHexahedron<T> HEXAHEDRON1_POS3_ROT6 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS3);
    const QHexahedron<T> HEXAHEDRON1_POS3_ROT7 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS3);
    const QHexahedron<T> HEXAHEDRON1_POS3_ROT8 = HEXAHEDRON1.Rotate(QQuaternion(-QUARTER_ROTATION, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS3);

    const QHexahedron<T> HEXAHEDRON1_POS4_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS4);
    const QHexahedron<T> HEXAHEDRON1_POS4_ROT2 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS4);
    const QHexahedron<T> HEXAHEDRON1_POS4_ROT3 = HEXAHEDRON1.Rotate(QQuaternion(HALF_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS4);
    const QHexahedron<T> HEXAHEDRON1_POS4_ROT4 = HEXAHEDRON1.Rotate(QQuaternion(THREEQUARTERS_ROTATION, SQFloat::_0, SQFloat::_0)).Translate(TRANSLATION_POS4);
    const QHexahedron<T> HEXAHEDRON1_POS4_ROT5 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS4);
    const QHexahedron<T> HEXAHEDRON1_POS4_ROT6 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS4);
    const QHexahedron<T> HEXAHEDRON1_POS4_ROT7 = HEXAHEDRON1.Rotate(QQuaternion(QUARTER_ROTATION, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS4);
    const QHexahedron<T> HEXAHEDRON1_POS4_ROT8 = HEXAHEDRON1.Rotate(QQuaternion(-QUARTER_ROTATION, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION_POS4);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultP1R1 = HEXAHEDRON1_POS1_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP1R2 = HEXAHEDRON1_POS1_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP1R3 = HEXAHEDRON1_POS1_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP1R4 = HEXAHEDRON1_POS1_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP1R5 = HEXAHEDRON1_POS1_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP1R6 = HEXAHEDRON1_POS1_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP1R7 = HEXAHEDRON1_POS1_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP1R8 = HEXAHEDRON1_POS1_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP2R1 = HEXAHEDRON1_POS2_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP2R2 = HEXAHEDRON1_POS2_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP2R3 = HEXAHEDRON1_POS2_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP2R4 = HEXAHEDRON1_POS2_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP2R5 = HEXAHEDRON1_POS2_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP2R6 = HEXAHEDRON1_POS2_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP2R7 = HEXAHEDRON1_POS2_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP2R8 = HEXAHEDRON1_POS2_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP3R1 = HEXAHEDRON1_POS3_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP3R2 = HEXAHEDRON1_POS3_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP3R3 = HEXAHEDRON1_POS3_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP3R4 = HEXAHEDRON1_POS3_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP3R5 = HEXAHEDRON1_POS3_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP3R6 = HEXAHEDRON1_POS3_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP3R7 = HEXAHEDRON1_POS3_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP3R8 = HEXAHEDRON1_POS3_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP4R1 = HEXAHEDRON1_POS4_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP4R2 = HEXAHEDRON1_POS4_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP4R3 = HEXAHEDRON1_POS4_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP4R4 = HEXAHEDRON1_POS4_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP4R5 = HEXAHEDRON1_POS4_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP4R6 = HEXAHEDRON1_POS4_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP4R7 = HEXAHEDRON1_POS4_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP4R8 = HEXAHEDRON1_POS4_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP5R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT1);
    bool bResultP5R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT2);
    bool bResultP5R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT3);
    bool bResultP5R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT4);
    bool bResultP5R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT5);
    bool bResultP5R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT6);
    bool bResultP5R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT7);
    bool bResultP5R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT8);

    bool bResultP6R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT1);
    bool bResultP6R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT2);
    bool bResultP6R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT3);
    bool bResultP6R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT4);
    bool bResultP6R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT5);
    bool bResultP6R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT6);
    bool bResultP6R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT7);
    bool bResultP6R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT8);

    bool bResultP7R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT1);
    bool bResultP7R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT2);
    bool bResultP7R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT3);
    bool bResultP7R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT4);
    bool bResultP7R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT5);
    bool bResultP7R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT6);
    bool bResultP7R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT7);
    bool bResultP7R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT8);

    bool bResultP8R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT1);
    bool bResultP8R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT2);
    bool bResultP8R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT3);
    bool bResultP8R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT4);
    bool bResultP8R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT5);
    bool bResultP8R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT6);
    bool bResultP8R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT7);
    bool bResultP8R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT8);

    // Verification
    BOOST_CHECK_EQUAL(bResultP1R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP3R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP4R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP5R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP6R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP7R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP8R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the hexahedrons coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenHexahedronsCoincide_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON1 = QHexahedron<T>::GetUnitCube();
    const QHexahedron<T> HEXAHEDRON2 = HEXAHEDRON1;

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one of the hexahedrons in inside the other.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOneHexahedronsIsInsideTheOther_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON1 = QHexahedron<T>::GetUnitCube();
    const QHexahedron<T> HEXAHEDRON2 = HEXAHEDRON1.Scale(SQFloat::_0_5, SQFloat::_0_5, SQFloat::_0_5);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one of the hexahedrons intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenHexahedronsIntersect_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON1 = QHexahedron<T>::GetUnitCube();
    const QHexahedron<T> HEXAHEDRON2 = HEXAHEDRON1.Translate(SQFloat::_0_5, SQFloat::_0_5, SQFloat::_0_5);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when one of the hexahedrons intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenHexahedronsIntersect_Test, TQTemplateTypes )
{
    // Preparation
    const QHexahedron<T> HEXAHEDRON1 = QHexahedron<T>::GetUnitCube();
    const QHexahedron<T> HEXAHEDRON2 = HEXAHEDRON1.Translate(SQFloat::_10, SQFloat::_0, SQFloat::_0);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the the face of one hexahedron is pierced by a corner of the other hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenTheFaceOfOneHexahedronIsPiercedByACornerOfTheOther_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q QUARTER_ROTATION = SQAngle::_90;
    const float_q HALF_ROTATION = SQAngle::_180;
    const float_q THREEQUARTERS_ROTATION = SQAngle::_270;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q QUARTER_ROTATION = SQAngle::_HalfPi;
    const float_q HALF_ROTATION = SQAngle::_Pi;
    const float_q THREEQUARTERS_ROTATION = SQAngle::_3HalfsPi;
#endif

    const QHexahedron<T> HEXAHEDRON2 = QHexahedron<T>::GetUnitCube();
    const QHexahedron<T> HEXAHEDRON1 = QHexahedron<T>::GetUnitCube().Rotate(QQuaternion(SQAngle::_QuarterPi, SQAngle::_QuarterPi, SQFloat::_0));

    // Faces
    const QVector3 TRANSLATION = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QHexahedron<T> HEXAHEDRON1_ROT1 = HEXAHEDRON1.Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT2 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT3 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT4 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, -QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT5 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, SQFloat::_0, QUARTER_ROTATION)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT6 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, SQFloat::_0, -QUARTER_ROTATION)).Translate(TRANSLATION);

    // Corners
    const QHexahedron<T> HEXAHEDRON2_ROT1 = HEXAHEDRON2;
    const QHexahedron<T> HEXAHEDRON2_ROT2 = HEXAHEDRON2.Rotate(QQuaternion(QUARTER_ROTATION, SQFloat::_0, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT3 = HEXAHEDRON2.Rotate(QQuaternion(HALF_ROTATION, SQFloat::_0, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT4 = HEXAHEDRON2.Rotate(QQuaternion(THREEQUARTERS_ROTATION, SQFloat::_0, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT5 = HEXAHEDRON2.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT6 = HEXAHEDRON2.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT7 = HEXAHEDRON2.Rotate(QQuaternion(QUARTER_ROTATION, QUARTER_ROTATION, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT8 = HEXAHEDRON2.Rotate(QQuaternion(-QUARTER_ROTATION, HALF_ROTATION, SQFloat::_0));

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultH1R1_H2R1 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R2_H2R1 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R3_H2R1 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R4_H2R1 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R5_H2R1 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R6_H2R1 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT1);

    bool bResultH1R1_H2R2 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R2_H2R2 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R3_H2R2 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R4_H2R2 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R5_H2R2 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R6_H2R2 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT2);

    bool bResultH1R1_H2R3 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R2_H2R3 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R3_H2R3 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R4_H2R3 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R5_H2R3 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R6_H2R3 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT3);

    bool bResultH1R1_H2R4 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R2_H2R4 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R3_H2R4 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R4_H2R4 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R5_H2R4 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R6_H2R4 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT4);

    bool bResultH1R1_H2R5 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R2_H2R5 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R3_H2R5 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R4_H2R5 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R5_H2R5 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R6_H2R5 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT5);

    bool bResultH1R1_H2R6 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R2_H2R6 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R3_H2R6 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R4_H2R6 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R5_H2R6 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R6_H2R6 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT6);

    bool bResultH1R1_H2R7 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R2_H2R7 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R3_H2R7 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R4_H2R7 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R5_H2R7 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R6_H2R7 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT7);

    bool bResultH1R1_H2R8 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R2_H2R8 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R3_H2R8 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R4_H2R8 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R5_H2R8 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R6_H2R8 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT8);

    // Verification
    BOOST_CHECK_EQUAL(bResultH1R1_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R1, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R2, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R3, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R5, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R6, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R7, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one hexahedron is pierced by an edge of the other hexahedron.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenTheOneHexahedronIsPiercedByAnEdgeOfTheOther_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // Preparation
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion INITIAL_ROTATION = QQuaternion(SQAngle::_45, SQAngle::_45, SQFloat::_0);
    const float_q QUARTER_ROTATION = SQAngle::_90;
    const float_q HALF_ROTATION = SQAngle::_180;
    const float_q THREEQUARTERS_ROTATION = SQAngle::_270;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion INITIAL_ROTATION = QQuaternion(SQAngle::_QuarterPi, SQAngle::_QuarterPi, SQFloat::_0);
    const float_q QUARTER_ROTATION = SQAngle::_HalfPi;
    const float_q HALF_ROTATION = SQAngle::_Pi;
    const float_q THREEQUARTERS_ROTATION = SQAngle::_3HalfsPi;
#endif

    const QHexahedron<T> HEXAHEDRON2 = QHexahedron<T>::GetUnitCube();
    const QHexahedron<T> HEXAHEDRON1 = QHexahedron<T>::GetUnitCube().Rotate(INITIAL_ROTATION);
    
    // Faces
    const QVector3 TRANSLATION = QVector3((float_q)0.6, (float_q)1.0, SQFloat::_0);
    const QHexahedron<T> HEXAHEDRON1_ROT1 = HEXAHEDRON1.Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT2 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT3 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT4 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, -QUARTER_ROTATION, SQFloat::_0)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT5 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, SQFloat::_0, QUARTER_ROTATION)).Translate(TRANSLATION);
    const QHexahedron<T> HEXAHEDRON1_ROT6 = HEXAHEDRON1.Rotate(QQuaternion(SQFloat::_0, SQFloat::_0, -QUARTER_ROTATION)).Translate(TRANSLATION);

    // Corners
    const QHexahedron<T> HEXAHEDRON2_ROT1 = HEXAHEDRON2;
    const QHexahedron<T> HEXAHEDRON2_ROT2 = HEXAHEDRON2.Rotate(QQuaternion(QUARTER_ROTATION, SQFloat::_0, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT3 = HEXAHEDRON2.Rotate(QQuaternion(HALF_ROTATION, SQFloat::_0, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT4 = HEXAHEDRON2.Rotate(QQuaternion(THREEQUARTERS_ROTATION, SQFloat::_0, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT5 = HEXAHEDRON2.Rotate(QQuaternion(SQFloat::_0, QUARTER_ROTATION, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT6 = HEXAHEDRON2.Rotate(QQuaternion(SQFloat::_0, HALF_ROTATION, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT7 = HEXAHEDRON2.Rotate(QQuaternion(QUARTER_ROTATION, QUARTER_ROTATION, SQFloat::_0));
    const QHexahedron<T> HEXAHEDRON2_ROT8 = HEXAHEDRON2.Rotate(QQuaternion(-QUARTER_ROTATION, HALF_ROTATION, SQFloat::_0));

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultH1R1_H2R1 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R2_H2R1 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R3_H2R1 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R4_H2R1 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R5_H2R1 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R6_H2R1 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT1);

    bool bResultH1R1_H2R2 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R2_H2R2 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R3_H2R2 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R4_H2R2 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R5_H2R2 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R6_H2R2 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT2);

    bool bResultH1R1_H2R3 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R2_H2R3 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R3_H2R3 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R4_H2R3 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R5_H2R3 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R6_H2R3 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT3);

    bool bResultH1R1_H2R4 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R2_H2R4 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R3_H2R4 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R4_H2R4 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R5_H2R4 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R6_H2R4 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT4);

    bool bResultH1R1_H2R5 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R2_H2R5 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R3_H2R5 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R4_H2R5 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R5_H2R5 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R6_H2R5 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT5);

    bool bResultH1R1_H2R6 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R2_H2R6 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R3_H2R6 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R4_H2R6 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R5_H2R6 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R6_H2R6 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT6);

    bool bResultH1R1_H2R7 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R2_H2R7 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R3_H2R7 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R4_H2R7 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R5_H2R7 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R6_H2R7 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT7);

    bool bResultH1R1_H2R8 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R2_H2R8 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R3_H2R8 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R4_H2R8 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R5_H2R8 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R6_H2R8 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT8);

    // Verification
    BOOST_CHECK_EQUAL(bResultH1R1_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R1, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R2, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R3, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R5, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R6, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R7, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenAllVerticesCoincide_Test, TQTemplateTypes )
{
    // Preparation
    const float_q POINT_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const QHexahedron<T> HEXAHEDRON1 = QHexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);
    const QHexahedron<T> HEXAHEDRON2 = QHexahedron<T>::GetUnitCube();

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed1 = false;

    try
    {
        HEXAHEDRON1.Intersection(HEXAHEDRON2);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        HEXAHEDRON2.Intersection(HEXAHEDRON1);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed2 = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the hexahedron is correctly projected to a plane when they intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_IsCorrectlyProjectedWhenHexahedronAndPlaneIntersect_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_2);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_2, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> EXPECTED_RESULT = QHexahedron<T>(T(EXPECTED_VECTOR_COMPONENTS_A),
                                                          T(EXPECTED_VECTOR_COMPONENTS_B),
                                                          T(EXPECTED_VECTOR_COMPONENTS_C),
                                                          T(EXPECTED_VECTOR_COMPONENTS_D),
                                                          T(EXPECTED_VECTOR_COMPONENTS_E),
                                                          T(EXPECTED_VECTOR_COMPONENTS_F),
                                                          T(EXPECTED_VECTOR_COMPONENTS_G),
                                                          T(EXPECTED_VECTOR_COMPONENTS_H));

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

/// <summary>
/// Checks that the hexahedron is correctly projected to a plane when it's in the positive side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_IsCorrectlyProjectedWhenHexahedronIsInPositiveSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_2);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, -SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_2, -SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_4, -SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4, -SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_1, -SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4, -SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { SQFloat::_4, -SQFloat::_2, SQFloat::_1, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_1, -SQFloat::_2, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> EXPECTED_RESULT = QHexahedron<T>(T(EXPECTED_VECTOR_COMPONENTS_A),
                                                          T(EXPECTED_VECTOR_COMPONENTS_B),
                                                          T(EXPECTED_VECTOR_COMPONENTS_C),
                                                          T(EXPECTED_VECTOR_COMPONENTS_D),
                                                          T(EXPECTED_VECTOR_COMPONENTS_E),
                                                          T(EXPECTED_VECTOR_COMPONENTS_F),
                                                          T(EXPECTED_VECTOR_COMPONENTS_G),
                                                          T(EXPECTED_VECTOR_COMPONENTS_H));

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

/// <summary>
/// Checks that the hexahedron is correctly projected to a plane when it's in the negative side.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_IsCorrectlyProjectedWhenHexahedronIsInNegativeSide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_3, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_3, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_10);

    const float_q EXPECTED_VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_10, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_10, SQFloat::_2, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_10, SQFloat::_2, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_10, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_10, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_10, SQFloat::_3, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_10, SQFloat::_1, SQFloat::_1 };
    const float_q EXPECTED_VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_10, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> EXPECTED_RESULT = QHexahedron<T>(T(EXPECTED_VECTOR_COMPONENTS_A),
                                                          T(EXPECTED_VECTOR_COMPONENTS_B),
                                                          T(EXPECTED_VECTOR_COMPONENTS_C),
                                                          T(EXPECTED_VECTOR_COMPONENTS_D),
                                                          T(EXPECTED_VECTOR_COMPONENTS_E),
                                                          T(EXPECTED_VECTOR_COMPONENTS_F),
                                                          T(EXPECTED_VECTOR_COMPONENTS_G),
                                                          T(EXPECTED_VECTOR_COMPONENTS_H));

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

/// <summary>
/// Checks that the hexahedron doesn't change when it already belongs to the plane.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_ItDoesNotChangeWhenItAlreadyBelongsToPlane_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_1, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_1);

    const QHexahedron<T> EXPECTED_RESULT = HEXAHEDRON;

	// Execution
    QHexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // Verification
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_AssertionFailsWhenAllVerticesCoincide_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QPlane;

    // Preparation
    const QPlane PLANE = QPlane(SQFloat::_0, SQFloat::_1, SQFloat::_0, -SQFloat::_1);
    const float_q POINT_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.ProjectToPlane(PLANE);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
QTEST_CASE_TEMPLATE ( ProjectToPlane_AssertionFailsWhenThePlaneIsNull_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::Math::QBasePlane;

    // Preparation
    const float_q VECTOR_COMPONENTS_A[] = { SQFloat::_2, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_B[] = { SQFloat::_2, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_C[] = { SQFloat::_4, SQFloat::_0, SQFloat::_2, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_D[] = { SQFloat::_4, SQFloat::_0, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_E[] = { SQFloat::_1, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_F[] = { SQFloat::_4, SQFloat::_1, SQFloat::_3, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_G[] = { SQFloat::_4, SQFloat::_1, SQFloat::_1, SQFloat::_1 };
    const float_q VECTOR_COMPONENTS_H[] = { SQFloat::_1, SQFloat::_1, SQFloat::_0, SQFloat::_1 };

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const QBasePlane PLANE = QBasePlane(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);

    const bool ASSERTION_FAILED = true;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.ProjectToPlane(PLANE);
    }
    catch(...) // [TODO] Thund: Use a concrete exception type when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TQTemplateTypes )
{
    // Preparation
    float_q VECTOR_COMPONENTS_A[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_B[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_C[] = { SQFloat::_9, SQFloat::_0, SQFloat::_0_5, SQFloat::_0_25 };
    float_q VECTOR_COMPONENTS_D[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_E[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    float_q VECTOR_COMPONENTS_F[] = { SQFloat::_9, SQFloat::_0, SQFloat::_0_5, SQFloat::_0_25 };
    float_q VECTOR_COMPONENTS_G[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR_COMPONENTS_H[] = { SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_8 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T VALUE_FOR_H(VECTOR_COMPONENTS_H);

    const QHexahedron<T> HEXAHEDRON = QHexahedron<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C, VALUE_FOR_D,
                                                     VALUE_FOR_E, VALUE_FOR_F, VALUE_FOR_G, VALUE_FOR_H);

    const string_q A_STRING = VALUE_FOR_A.ToString();
    const string_q B_STRING = VALUE_FOR_B.ToString();
    const string_q C_STRING = VALUE_FOR_C.ToString();
    const string_q D_STRING = VALUE_FOR_D.ToString();
    const string_q E_STRING = VALUE_FOR_E.ToString();
    const string_q F_STRING = VALUE_FOR_F.ToString();
    const string_q G_STRING = VALUE_FOR_G.ToString();
    const string_q H_STRING = VALUE_FOR_H.ToString();

    const string_q EXPECTED_STRING = QE_L("HX(a(") + A_STRING + QE_L("),b(") + B_STRING + QE_L("),c(") + C_STRING + QE_L("),d(") + D_STRING + QE_L("),") +
                                     QE_L(   "e(") + E_STRING + QE_L("),f(") + F_STRING + QE_L("),g(") + G_STRING + QE_L("),h(") + H_STRING + QE_L("))");

	// Execution
    string_q strReturnedString = HEXAHEDRON.ToString();

    // Verification
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: QHexahedron
QTEST_SUITE_END()
