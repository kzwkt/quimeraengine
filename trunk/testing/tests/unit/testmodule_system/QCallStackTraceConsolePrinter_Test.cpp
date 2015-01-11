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

#include "QCallStackTraceConsolePrinter.h"
#include "QCallStackTracePlainTextFormatter.h"

using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTraceConsolePrinter;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTracePlainTextFormatter;


QTEST_SUITE_BEGIN( QCallStackTraceConsolePrinter_TestSuite )
    
/// <summary>
/// Checks that the formatter is correctly stored.
/// </summary>
QTEST_CASE ( Constructor_FormatterIsStored_Test )
{
    using Kinesis::QuimeraEngine::System::Diagnosis::IQCallStackTraceFormatter;

    // [Preparation]
    boost::shared_ptr<IQCallStackTraceFormatter> pFormatter(new QCallStackTracePlainTextFormatter());
    
    // [Execution]
    QCallStackTraceConsolePrinter printer(pFormatter);
    
    // [Verification]
    BOOST_CHECK(printer.GetFormatter() == pFormatter);
}


// End - Test Suite: QCallStackTraceConsolePrinter
QTEST_SUITE_END()
