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
    /*QStringUnicode EXPECTED_RESULT("");

	// [Execution]
    QStringUnicode string;
    
    // [Verification]
    BOOST_CHECK(string == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that the copy of a string is equal to the original.
/// </summary>
QTEST_CASE ( Constructor2_CopiedStringIsEqualToOriginal_Test )
{
    // [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented

    // [Preparation]
    /*QStringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    QStringUnicode string(EXPECTED_RESULT);
    
    // [Verification]
    BOOST_CHECK(string == EXPECTED_RESULT);*/
}

/// <summary>
/// Checks that the assigned string is equal to the copied string.
/// </summary>
QTEST_CASE ( OperatorAssignation_CopiedStringIsEqualToOriginal_Test )
{
    // [TODO] Thund: Uncomment when a constructor that receives a character array or another initialization mechanism is implemented

    // [Preparation]
    /*QStringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    QStringUnicode string;
    string = EXPECTED_RESULT;
    
    // [Verification]
    BOOST_CHECK(string == EXPECTED_RESULT);*/
}

// End - Test Suite: QStringUnicode
QTEST_SUITE_END()
