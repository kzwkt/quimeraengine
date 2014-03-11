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

#include "QTimeSpan.h"

using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;

QTEST_SUITE_BEGIN( QTimeSpan_TestSuite )

/// <summary>
/// Checks constructor with no parameters.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 0;
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);
 
	// [Execution]
    QTimeSpan timeSpan;
    
    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
}

/// <summary>
/// Checks constructor with one parameter. Checks if the class member is set correctly
/// </summary>
QTEST_CASE ( Constructor2_ParameterIsProperlyAssigned_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 15;
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpan(EXPECTED_VALUE_FOR_TIMESPAN);
    
    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
}

/// <summary>
/// Checks constructor with several values as parameters.
/// These values represent days, hours, minutes, seconds, mseconds, microseconds and hundreds of nanosecs
/// </summary>
QTEST_CASE ( Constructor3_InstanceIsCorrectlyConstructedWhenUsingCommonTimeValues_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 1;
    const u64_q VALUE_FOR_HOURS = 1;
    const u64_q VALUE_FOR_MINUTES = 1;
    const u64_q VALUE_FOR_SECONDS = 1;
    const u64_q VALUE_FOR_MSECONDS = 1;
    const u64_q VALUE_FOR_MICROSECONDS = 1;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1;
    //days * 24 = hours
    //hours * 60 = minutes
    //minutes * 60 = seconds
    //seconds * 1000 = mseconds
    //microseconds * 1000 = microsecs
    //microsecs * 10 = hundreds of nanosecs
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 900610010011;
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);


    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED
/// <summary>
/// Checks if the overflow when passing parameter bigger than the maximum allowed provokes the return of max value.
/// </summary>
QTEST_CASE ( Constructor3_MaximumValueIsAssignedWhenParametersProduceOverflow_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 100000000000;
    const u64_q VALUE_FOR_HOURS = 1;
    const u64_q VALUE_FOR_MINUTES = 1;
    const u64_q VALUE_FOR_SECONDS = 1;
    const u64_q VALUE_FOR_MSECONDS = 1;
    const u64_q VALUE_FOR_MICROSECONDS = 1;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = -1;
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);

    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
   
}

/// <summary>
/// Checks if the overflow when computing the sum of all parameters provokes the return of max value.
/// </summary>
/// <remarks>
/// The values used in the test are computed as follows: e.g std::numeric_limits<u64_q>::max() / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND - 1: (max value allowed divided by amount of hundreds of nanosecond of every parameter ) minus one.
/// </remarks>
QTEST_CASE ( Constructor3_MaximumValueIsAssignedWhenAdditionOfParametersProduceOverflow_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 21350397;
    const u64_q VALUE_FOR_HOURS = 512409556;
    const u64_q VALUE_FOR_MINUTES = 30744573455;
    const u64_q VALUE_FOR_SECONDS = 1844674407369;
    const u64_q VALUE_FOR_MSECONDS = 1844674407370954;
    const u64_q VALUE_FOR_MICROSECONDS = 1844674407370955160;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1000000000000000000;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = -1;
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);

    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
   
}

#endif

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the constructor fails whith overflow when passing parameter bigger the the maximum allowed.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenOverflowWithParameterOccurs_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 100000000000;
    const u64_q VALUE_FOR_HOURS = 1;
    const u64_q VALUE_FOR_MINUTES = 1;
    const u64_q VALUE_FOR_SECONDS = 1;
    const u64_q VALUE_FOR_MSECONDS = 1;
    const u64_q VALUE_FOR_MICROSECONDS = 1;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);
    }
    catch(...) // [TODO] [raul]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if the assertion inside the constructor fails whith overflow when computing the sum of all parameters.
/// </summary>
/// <remarks>
/// The values used in the test are computed as follows: e.g std::numeric_limits<u64_q>::max() / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND - 1: (max value allowed divided by amount of hundreds of nanosecond of every parameter ) minus one.
/// </remarks>
QTEST_CASE ( Constructor3_AssertionFailsWhenOverflowWithAdditionOccurs_Test )
{
    // [Preparation]
    const u64_q VALUE_FOR_DAYS = 21350397;
    const u64_q VALUE_FOR_HOURS = 512409556;
    const u64_q VALUE_FOR_MINUTES = 30744573455;
    const u64_q VALUE_FOR_SECONDS = 1844674407369;
    const u64_q VALUE_FOR_MSECONDS = 1844674407370954;
    const u64_q VALUE_FOR_MICROSECONDS = 1844674407370955160;
    const u64_q VALUE_FOR_HUNDREDSNANOSECS = 1000000000000000000;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QTimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS, 
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);
    }
    catch(...) // [TODO] [raul]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if copy constructor works properly. 
/// </summary>
QTEST_CASE ( Constructor4_QTimeSpanIsCopiedCorrectly_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 150;
    QTimeSpan timeSpanOriginal(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpanResult(timeSpanOriginal);
    
    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanOriginal);
}

/// <summary>
/// Checks assignment operator. 
/// </summary>
QTEST_CASE ( AssignmentOperator_AssignmentOperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 150;
    QTimeSpan timeSpanOriginal(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpanAssigned = timeSpanOriginal;
    
    // [Verification]
    BOOST_CHECK(timeSpanAssigned == timeSpanOriginal);
}

/// <summary>
/// Checks that addition and assignment operator works properly.
/// The addition is performed and the result is assigned to the first time span instance.
/// </summary>
QTEST_CASE ( AdditionAndAssignmentOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_q TIMESPAN_VALUE_TO_ADD = 15;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 25;
    QTimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    QTimeSpan timeSpanToAdd(TIMESPAN_VALUE_TO_ADD);
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN); 

	// [Execution]
    timeSpanOriginal += timeSpanToAdd;
    
    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the operator fails when the addition of the two operands provokes an overflow.
/// </summary>
QTEST_CASE ( AdditionAndAssignmentOperator_AssertionFailsWhenAdditionProvokesOverflow_Test)
{
    // [Preparation]
    bool bAssertionFailed = false;
    QTimeSpan timeSpanOriginal(-1);
    QTimeSpan timeSpanToAdd(-1);

	// [Execution]
    try
    {
        timeSpanOriginal += timeSpanToAdd;
    }
    catch(...) // [TODO] [raul]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED
/// <summary>
/// Checks if the overflow when trying to add time span bigger than the maximum allowed provokes the return of max value.
/// </summary>
QTEST_CASE ( AdditionAndAssignmentOperator_MaximumValueIsAssignedWhenAdditionProducesOverflow_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = -1;
    QTimeSpan timeSpanOriginal(-1);
    QTimeSpan timeSpanToAdd(-1);
     //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN); 

	// [Execution]
    timeSpanOriginal += timeSpanToAdd;

    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
   
}

#endif

/// <summary>
/// Checks addition operator. The addition is correctly performed and result is assigned to a new instance.  
/// </summary>
QTEST_CASE ( AdditionOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_q TIMESPAN_VALUE_TO_ADD = 15;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 25;
    QTimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    QTimeSpan timeSpanToAdd(TIMESPAN_VALUE_TO_ADD);
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN); 


	// [Execution]
    QTimeSpan timeSpanResult = timeSpanOriginal + timeSpanToAdd;
    
    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanExpectedResult);
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the operator fails when the addition of the two operands provokes an overflow.
/// </summary>
QTEST_CASE ( AdditionOperator_AssertionFailsWhenAdditionProvokesOverflow_Test )
{
    // [Preparation]
    bool bAssertionFailed = false;
    QTimeSpan timeSpanOriginal(-1);
    QTimeSpan timeSpanToAdd(-1);

	// [Execution]
    try
    {
        QTimeSpan timeSpanResult = timeSpanOriginal + timeSpanToAdd;
    }
    catch(...) // [TODO] [raul]: Only must catch the proper exception class, not implemented yet.
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks if the overflow when trying to add time span bigger than the maximum allowed provokes the return of max value.
/// </summary>
QTEST_CASE ( AdditionOperator_MaximumValueIsAssignedWhenAdditionProducesOverflow_Test )
{
    // [Preparation]
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = -1;
    QTimeSpan timeSpanOriginal(-1);
    QTimeSpan timeSpanToAdd(-1);
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    QTimeSpan timeSpanResult = timeSpanOriginal + timeSpanToAdd;

    // [Verification]
    // [TODO] [raul] To uncomment this line the getter must be implemented in class QTimeSpan.
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
   
}

#endif

/// <summary>
/// Checks subtraction operator. The subtraction is correctly done and result is assigned to new instance.
/// </summary>
QTEST_CASE ( SubtractionOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN = 15;
    const u64_q TIMESPAN_VALUE_TO_SUBSTRACT = 10;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 5;
    QTimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    QTimeSpan timeSpanToSubstract(TIMESPAN_VALUE_TO_SUBSTRACT);
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN); 

	// [Execution]
    QTimeSpan timeSpanResult = timeSpanOriginal - timeSpanToSubstract;
    
    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanExpectedResult);
}

/// <summary>
/// Checks subtraction operator. 
/// In this case checks that if you substract a bigger value the result is the absolute value. 
/// </summary>
QTEST_CASE ( SubtractionOperator_OperationIsDoneCorrectlyWhenSecondOperatorIsBigger_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_q TIMESPAN_VALUE_TO_SUBSTRACT = 15;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 5;
    QTimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    QTimeSpan timeSpanToSubstract(TIMESPAN_VALUE_TO_SUBSTRACT);
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN); 

	// [Execution]
    QTimeSpan timeSpanResult = timeSpanOriginal - timeSpanToSubstract;
    
    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanExpectedResult);
}

/// <summary>
/// Checks subtraction and assignment operator.
/// The subtraction is performed and the result is assigned to the first operand.
/// </summary>
QTEST_CASE ( SubtractionAndAssignmentOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN = 15;
    const u64_q TIMESPAN_VALUE_TO_SUBSTRACT = 10;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 5;
    QTimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    QTimeSpan timeSpanToSubstract(TIMESPAN_VALUE_TO_SUBSTRACT);
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN); 

	// [Execution]
    timeSpanOriginal -= timeSpanToSubstract;
    
    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
}

/// <summary>
/// Checks subtraction operator. 
/// In this case checks that if you subtract a bigger value the result is the absolute value and the it is assigned to first operand.
/// </summary>
QTEST_CASE ( SubtractionAndAssignmentOperator_OperationIsDoneCorrectlyWhenSecondOperatorIsBigger_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_q TIMESPAN_VALUE_TO_ADD = 15;
    const u64_q EXPECTED_VALUE_FOR_TIMESPAN = 5;
    QTimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    QTimeSpan timeSpanToAdd(TIMESPAN_VALUE_TO_ADD);
    //QTimeSpan object to perform the comparison.
    QTimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    timeSpanOriginal -= timeSpanToAdd;
    
    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
}

/// <summary>
/// Checks equality operator. Compares to instances and check that the return value is true as they are equal.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsTrueWhenComparingTwoEqualValues_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 15;
    const bool EXPECTED_RESULT = true;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 == timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks equality operator. This case checks than the return value is false when the values are not equal. 
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenComparingTwoDifferentValues_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = false;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 == timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks inequality operator. This test checks that the return value is false when comparing two equal values.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsFalseWhenComparingTwoEqualValues_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 15;
    const bool EXPECTED_VALUE = false;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = (timeSpan1 != timeSpan2);
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks inequality operator. This test checks that the return value is true when comparing two different values.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenComparingTwoDifferentValues_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = (timeSpan1 != timeSpan2);
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than operator. 
/// This test checks that the return value is true since first operator is bigger than the second one.
/// </summary>
QTEST_CASE ( GreaterThanOperator_ReturnsTrueWhenFirstValueGreater_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 > timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than operator. 
/// This test checks that the return value is false since first operator is not bigger than the second one.
/// </summary>
QTEST_CASE ( GreaterThanOperator_ReturnsFalseWhenFirstValueNotGreater_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 16;
    const bool EXPECTED_RESULT = false;

    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 > timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than or equals to operator. 
/// First value bigger than the second one, the test checks that the return value is true.
/// </summary>
QTEST_CASE ( GreaterThanOrEqualsOperator_ReturnsTrueWhenFirstValueGreater_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;

    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 >= timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than or equals to operator. 
/// First value equal to the second one, this test checks that the return value is true.
/// </summary>
QTEST_CASE ( GreaterThanOrEqualsOperator_ReturnsTrueWhenFirstValueEqualToSecondValue_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 15;
    const bool EXPECTED_RESULT = true;

    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 >= timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than or equals to operator. 
/// First value lower than the second one, this test checks that the return value is false.
/// </summary>
QTEST_CASE ( GreaterThanOperator_ReturnsFalseWhenFirstValueLowerThanSecondValue_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 19;
    const bool EXPECTED_RESULT = false;

    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 >= timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than operator. 
//  First value lower than the second one, this test checks that the return value is true.
/// </summary>
QTEST_CASE ( LowerThanOperator_ReturnsTrueWhenFirstValueLowerThanSecondValue_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 9;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 < timeSpan2;
    
    // [Verification]
     BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than operator. 
/// First value not lower than the second one, this test checks that the return value is false.
/// </summary>
QTEST_CASE ( LowerThanOperator_ReturnsFalseWhenFirstValueNotLowerThanSecondOne_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 11;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = false;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 < timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than or equals to operator. 
/// First value lower than the second one, this test will check that the return value is true.
/// </summary>
QTEST_CASE ( LowerThanOrEquals_Operator_ReturnsTrueWhenFirstValueLowerThanSecondValue_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 9;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 <= timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than or equals to operator. 
/// First value equal than the second one, this test will check that the return value is true.
/// </summary>
QTEST_CASE ( LowerThanOrEqualsOperator_ReturnsTrueWhenFirstValueEqualToSeCondValue_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 10;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 <= timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than or equals to operator. 
/// First value bigger than the second one, so this test checks that the return value is false.
/// </summary>
QTEST_CASE ( LowerThanOrEqualsOperator_ReturnsFalseWhenFirstValueGreaterThanSeCondValue_Test )
{
    // [Preparation]
    const u64_q INITIAL_VALUE_FOR_TIMESPAN1 = 12;
    const u64_q INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_VALUE = false;
    QTimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    QTimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 <= timeSpan2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_VALUE);
}

// End - Test Suite: QTimeSpan
QTEST_SUITE_END()