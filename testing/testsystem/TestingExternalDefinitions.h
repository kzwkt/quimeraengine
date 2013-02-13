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
// QTEST_CASE_TEMPLATE: Use this macro to define the header of a new test case, for testing a template
//                      function or method.
//                      It must be enclosed between QTEST_SUITE_BEGIN and QTEST_SUITE_END macros.
// TestCaseName: The name of the test case, as descriptive as possible (without quotation marks).
// TemplateTypes: A list of types to be used as template parameter T.
// --------------------------------------------------------------------------------------------------------
#define QTEST_CASE_TEMPLATE( TestCaseName, TemplateTypes ) BOOST_AUTO_TEST_CASE_TEMPLATE( TestCaseName, T, TemplateTypes )

// --------------------------------------------------------------------------------------------------------
// QTEST_SUITE_END: Use this macro to finish defining a test suite.
// --------------------------------------------------------------------------------------------------------
#define QTEST_SUITE_END( ) BOOST_AUTO_TEST_SUITE_END( )


#endif // __TESTINGEXTERNALDEFINITIONS__
