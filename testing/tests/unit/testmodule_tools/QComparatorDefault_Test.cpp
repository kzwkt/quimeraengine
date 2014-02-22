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

#include "QComparatorDefault.h"

using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
using Kinesis::QuimeraEngine::Tools::Containers::QComparatorDefault;


QTEST_SUITE_BEGIN( QComparatorDefault_TestSuite )

/// <summary>
/// Checks that method compare returns right value when left operand is greater than right operand.
/// </summary>
QTEST_CASE ( Compare_ReturnsPositiveOneWhenLeftOperandIsGreaterThanRightOperand_Test )
{
    // [Preparation]
    const i8_q EXPECTED_VALUE_OF_COMPARISON = 1;
    const i8_q LEFT_OPERAND = 10;
    const i8_q RIGHT_OPERAND = 5;

    QComparatorDefault<const i8_q&> comparator;

    // [Execution]
    i8_q comparisonResult = comparator.Compare(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL( comparisonResult, EXPECTED_VALUE_OF_COMPARISON );
}

/// <summary>
/// Checks that method compare returns right value when left operand is lower than right operand.
/// </summary>
QTEST_CASE ( Compare_ReturnsNegativeOneWhenLeftOperandIsLowerThanRightOperand_Test )
{
    // [Preparation]
    const i8_q EXPECTED_VALUE_OF_COMPARISON = -1;
    const i8_q LEFT_OPERAND = 5;
    const i8_q RIGHT_OPERAND = 10;

    QComparatorDefault<i8_q> comparator;

    // [Execution]
    i8_q comparisonResult = comparator.Compare(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL( comparisonResult, EXPECTED_VALUE_OF_COMPARISON );

}

/// <summary>
/// Checks that method compare returns right value when left operand is equal to right operand.
/// </summary>
// [Preparation]
QTEST_CASE ( Compare_ReturnsZeroWhenLeftOperandIsEqualToRightOperand_Test )
{
    const i8_q EXPECTED_VALUE_OF_COMPARISON = 0;
    const i8_q LEFT_OPERAND = 10;
    const i8_q RIGHT_OPERAND = 10;

    QComparatorDefault<i8_q> comparator;

    // [Execution]
    i8_q comparisonResult = comparator.Compare(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL( comparisonResult, EXPECTED_VALUE_OF_COMPARISON );
}

// End - Test Suite: QComparatorDefault
QTEST_SUITE_END()
