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

#include "QAlignment.h"

using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;


QTEST_SUITE_BEGIN( QAlignment_TestSuite )


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the alignment value passed to the constructor is not a power of two.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenAlignmentValueIsNotPowerOfTwo_Test )
{
    // [Preparation]
    const u32_q  ALIGNMENT_VALUE_NON_POWER_OF_TWO = 5;

    const bool ASSERTION_FAILED                   = true;

	// [Execution]
    bool bAssertionFailed01                       = false;

    try
    {
        QAlignment align_001(ALIGNMENT_VALUE_NON_POWER_OF_TWO);
    }
    catch(...)
    {
        bAssertionFailed01 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed01, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if constructor sets the alignment value properly.
/// </summary>
QTEST_CASE ( Constructor_CorrectAlignmentValueIsSet_Test )
{
    // [Preparation]
    unsigned int uAlignmentValue01            = 0;
    const u32_q  ALIGNMENT_VALUE_POWER_OF_TWO = 8;

	// [Execution]
    QAlignment align_001(ALIGNMENT_VALUE_POWER_OF_TWO);

    // [Verification]
    uAlignmentValue01 = align_001;
    BOOST_CHECK(ALIGNMENT_VALUE_POWER_OF_TWO == uAlignmentValue01 );
}

/// <summary>
/// Checks if conversion operator works properly.
/// </summary>
QTEST_CASE ( OperatorCastToUnsignedInt_CorrectAlignmentValueIsReturned_Test )
{
    // [Preparation]
    unsigned int       uAlignmentValue02            = 0;
    const unsigned int ALIGNMENT_VALUE_POWER_OF_TWO = 4;

	// [Execution]
    QAlignment align_002(ALIGNMENT_VALUE_POWER_OF_TWO);

    // [Verification]
    uAlignmentValue02 = align_002;
    BOOST_CHECK(ALIGNMENT_VALUE_POWER_OF_TWO == uAlignmentValue02 );
}


// End - Test Suite: QAlignment
QTEST_SUITE_END()
