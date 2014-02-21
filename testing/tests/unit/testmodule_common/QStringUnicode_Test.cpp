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

#include "QStringUnicode.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QStringUnicode;



QTEST_SUITE_BEGIN( QStringUnicode_TestSuite )

/// <summary>
/// Checks that the default constructor creates an empty string.
/// </summary>
QTEST_CASE ( Constructor1_DefaultConstructorCreatesEmptyString_Test )
{
    QStringUnicode s;
    // [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented

    // [Preparation]
    /*const QStringUnicode EXPECTED_RESULT("");

	// [Execution]
    QStringUnicode strString;
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that the copy of a string is equal to the original.
/// </summary>
QTEST_CASE ( Constructor2_CopiedStringIsEqualToOriginal_Test )
{
    // [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented

    // [Preparation]
    /*const QStringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    QStringUnicode strString(EXPECTED_RESULT);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that the assigned string is equal to the copied string.
/// </summary>
QTEST_CASE ( OperatorAssignation_CopiedStringIsEqualToOriginal_Test )
{
    // [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented

    // [Preparation]
    /*const QStringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    QStringUnicode strString;
    strString = EXPECTED_RESULT;
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that it returns the expected result when using common input positions.
/// </summary>
QTEST_CASE ( Substring_ReturnsExpectedResultWhenUsingCommonInputPositions_Test )
{
    // [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented

    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("EFGH");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION + 4;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the start position is greater than the last position.
/// </summary>
QTEST_CASE ( Substring_AssertionFailsWhenStartPositionIsGreaterThanLastPosition_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION - 2;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);*/
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an empty string is returned when the start position is greater than the last position.
/// </summary>
QTEST_CASE ( Substring_ReturnsEmptyStringWhenStartPositionIsGreaterThanLastPosition_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION - 2;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

#endif

/// <summary>
/// Checks that an empty string is returned when start position equals last position.
/// </summary>
QTEST_CASE ( Substring_ReturnsEmptyStringWhenStartPositionEqualsLastPosition_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
QTEST_CASE ( Substring_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 1;
    const unsigned int LAST_POSITION = 3;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that it returns the rest of the string when the last position is out of the string's bounds.
/// </summary>
QTEST_CASE ( Substring_ReturnsTheRestOfTheStringWhenLastPositionIsOutOfBounds_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("FGHIJKLMN");
    const unsigned int START_POSITION = 5;
    const unsigned int LAST_POSITION = SOURCE_STRING.GetLength() + 10;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that an empty string is returned when the start position is out of the string's bounds.
/// </summary>
QTEST_CASE ( Substring_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = SOURCE_STRING.GetLength();
    const unsigned int LAST_POSITION = START_POSITION + 2;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that the obtained iterator points to the first position when the string is not empty.
/// </summary>
QTEST_CASE ( GetConstCharIterator_IteratorPointsToFirstPositionWhenStringIsNotEmpty_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    QStringUnicode::QConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    EXPECTED_ITERATOR.MoveFirst();

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);*/
}

/// <summary>
/// Checks that the obtained iterator points to the end position when the string is empty.
/// </summary>
QTEST_CASE ( GetConstCharIterator_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("");
    const QStringUnicode::QConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    const bool IS_END = true;

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();
    
    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);*/
}

/// <summary>
/// Checks that it returns zero when the string is empty.
/// </summary>
QTEST_CASE ( GetLength_ReturnsZeroWhenStringIsEmpty_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("");
    const QStringUnicode::QConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    const bool IS_END = true;

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();
    
    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);*/
}

/// <summary>
/// Checks that it returns the expected result value when using a common non-empty string.
/// </summary>
QTEST_CASE ( GetLength_ReturnsCorrectValueWhenUsingCommonString_Test )
{// [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented
    // [Preparation]
    /*const QStringUnicode SOURCE_STRING("ABC");
    const unsigned int EXPECTED_LENGTH = 3;

	// [Execution]
    unsigned int nLength = SOURCE_STRING.GetLength();
    
    // [Verification]
    BOOST_CHECK_EQUAL(nLength, EXPECTED_LENGTH);*/
}

// End - Test Suite: QStringUnicode
QTEST_SUITE_END()
