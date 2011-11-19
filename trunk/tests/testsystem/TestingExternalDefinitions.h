// [TERMS&CONDITIONS]

#ifndef __TESTINGEXTERNALDEFINITIONS__
#define __TESTINGEXTERNALDEFINITIONS__

// --------------------------------------------------------------------------------------------------------
// QTEST_SUITE_BEGIN: Use this macro to start defining a test suite.
// TestSuiteName: The name of the test suite (without quotation marks).
// --------------------------------------------------------------------------------------------------------
#define QTEST_SUITE_BEGIN( TestSuiteName ) BOOST_AUTO_TEST_SUITE( TestSuiteName )

// --------------------------------------------------------------------------------------------------------
// QTEST_CASE: Use this macro to define the header of a new test case, for testing a function or method.
//             It must be enclosed between QTEST_SUITE_BEGIN and QTEST_SUITE_END macros.
// TestCaseName: The name of the test case, as descriptive as possible (without quotation marks).
// --------------------------------------------------------------------------------------------------------
#define QTEST_CASE( TestCaseName ) BOOST_AUTO_TEST_CASE( TestCaseName )

// --------------------------------------------------------------------------------------------------------
// QTEST_SUITE_END: Use this macro to finish defining a test suite.
// --------------------------------------------------------------------------------------------------------
#define QTEST_SUITE_END( ) BOOST_AUTO_TEST_SUITE_END( )


#endif // __TESTINGEXTERNALDEFINITIONS__
