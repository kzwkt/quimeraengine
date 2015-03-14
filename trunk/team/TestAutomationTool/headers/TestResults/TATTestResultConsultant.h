//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __TATTESTRESULTCONSULTANT__
#define __TATTESTRESULTCONSULTANT__

#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class TATTestResultNode;

/// <summary>
/// Extracts information from a test result tree.
/// </summary>
class TATTestResultConsultant
{
	// METHODS
	// ---------------
public:

    /// <summary>
    /// Gets the number of test modules in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree. It should be a test log or test module node.</param>
    /// <returns>
    /// The number of test modules in the tree.
    /// </returns>
    int GetTestModuleCount(TATTestResultNode* pNode) const;

    /// <summary>
    /// Gets the number of test suites in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree. It should be a test log, test module or test suite node.</param>
    /// <returns>
    /// The number of test suites in the tree.
    /// </returns>
    int GetTestSuiteCount(TATTestResultNode* pNode) const;

    /// <summary>
    /// Gets the number of test cases in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree. It should be a test log, test module, test suite or test case node.</param>
    /// <returns>
    /// The number of test cases in the tree.
    /// </returns>
    int GetTestCaseCount(TATTestResultNode* pNode) const;

    /// <summary>
    /// Gets the number of test results in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree.</param>
    /// <returns>
    /// The number of test results in the tree.
    /// </returns>
    int GetTestResultCount(TATTestResultNode* pNode) const;

    /// <summary>
    /// Gets the number of failed test modules in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree. It should be a test log or test module node.</param>
    /// <returns>
    /// The number of failed test modules in the tree.
    /// </returns>
    int GetFailedTestModuleCount(TATTestResultNode* pNode) const;

    /// <summary>
    /// Gets the number of failed test suites in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree. It should be a test log, test module or test suite node.</param>
    /// <returns>
    /// The number of failed test suites in the tree.
    /// </returns>
    int GetFailedTestSuiteCount(TATTestResultNode* pNode) const;

    /// <summary>
    /// Gets the number of failed test cases in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree. It should be a test log, test module, test suite or test case node.</param>
    /// <returns>
    /// The number of failed test cases in the tree.
    /// </returns>
    int GetFailedTestCaseCount(TATTestResultNode* pNode) const;

    /// <summary>
    /// Gets the number of failed test results in the tree.
    /// </summary>
    /// <param name="pNode">The test result tree.</param>
    /// <returns>
    /// The number of failed test results in the tree.
    /// </returns>
    int GetFailedTestResultCount(TATTestResultNode* pNode) const;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTCONSULTANT__
