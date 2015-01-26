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

#include "QBasicArray.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


QTEST_SUITE_BEGIN( QBasicArray_TestSuite )

/// <summary>
/// Checks that input values are correctly stored.
/// </summary>
QTEST_CASE ( Constructor1_CommonValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];

    // [Execution]
    QBasicArray<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
}

/// <summary>
/// Checks that input values are correctly stored when they are null and zero.
/// </summary>
QTEST_CASE ( Constructor1_InputValuesAreCorrectlyStoredWhenTheyAreNullAndZero_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 0;
    const int* ARRAY = null_q;

    // [Execution]
    QBasicArray<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( Get_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetCount_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns the correct number of bytes.
/// </summary>
QTEST_CASE ( GetSize_ReturnsCorrectNumberOfBytes_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const QBasicArray<const int> INSTANCE(ARRAY, COUNT);
    const pointer_uint_q EXPECTED_SIZE = 16U;

    // [Execution]
    pointer_uint_q uSize = INSTANCE.GetSize();

    // [Verification]
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
}

/// <summary>
/// Checks that it returns zero when the number of elements stored in the wrapper is zero.
/// </summary>
QTEST_CASE ( GetSize_ReturnsZeroWhenWrapperContainsZeroArrayElements_Test )
{
    // [Preparation]
    const pointer_uint_q COUNT = 0;
    const int* ARRAY = null_q;
    const QBasicArray<const int> INSTANCE(ARRAY, COUNT);
    const pointer_uint_q EXPECTED_SIZE = 0;

    // [Execution]
    pointer_uint_q uSize = INSTANCE.GetSize();

    // [Verification]
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
}

// End - Test Suite: QBasicArray
QTEST_SUITE_END()
