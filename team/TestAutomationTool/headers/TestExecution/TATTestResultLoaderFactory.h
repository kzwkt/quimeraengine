// [TERMS&CONDITIONS]

#ifndef __TATTESTRESULTLOADERFACTORY__
#define __TATTESTRESULTLOADERFACTORY__

#include "TestExecution/ETATResultSource.h"
#include "TestExecution/ITATTestResultLoader.h"
#include "TestExecution/TATTestResultLoader.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Creates test result loader implementations.
/// </summary>
class TATTestResultLoaderFactory
{
	// METHODS
	// ---------------
public:

    /// <summary>
	/// Creates a test result loader whose implementation depends on the source of the result.
	/// </summary>
    /// <param name="eSource">The source of the result (a file, a database, a web service, or whatever is allowed).</param>
    /// <returns>
    /// The implementation for the test result loader.
    /// </returns>
    ITATTestResultLoader* CreateConfigLoader(const ETATResultSource& eSource) const;

protected:

    /// <summary>
	/// Creates a test result loader whose source is an XML file.
	/// </summary>
    /// <returns>
    /// The implementation for the test result loader.
    /// </returns>
    ITATTestResultLoader* CreateTestResultLoaderFromXmlFile() const;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTLOADERFACTORY__
