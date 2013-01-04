// [TERMS&CONDITIONS]

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




/*int GetResultCount() const;

    int GetResultCountOfType(ETATResult eResultType) const;*/