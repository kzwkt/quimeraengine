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

#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

QTEST_SUITE_BEGIN( QAssertException_TestSuite )

/// <summary>
/// Checks that all the input parameters are correctly stored.
/// </summary>
QTEST_CASE ( Constructor_AllInputDataIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_q EXPECTED_CONDITION("Condition");
    const string_q EXPECTED_MESSAGE("Message");
    const int EXPECTED_LINE_NUMBER(123456);
    const string_q EXPECTED_FILE_NAME("FileName");

    // [Execution]
    QAssertException assertException(EXPECTED_CONDITION, EXPECTED_MESSAGE, EXPECTED_LINE_NUMBER, EXPECTED_FILE_NAME);
    
    // [Verification]
    BOOST_CHECK(assertException.GetCondition() == EXPECTED_CONDITION);
    BOOST_CHECK(assertException.GetMessage() == EXPECTED_MESSAGE);
    BOOST_CHECK(assertException.GetLineNumber() == EXPECTED_LINE_NUMBER);
    BOOST_CHECK(assertException.GetFileName() == EXPECTED_FILE_NAME);
}

// End - Test Suite: QAssertException
QTEST_SUITE_END()
