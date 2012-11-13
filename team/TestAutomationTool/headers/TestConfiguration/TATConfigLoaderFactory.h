// [TERMS&CONDITIONS]

#ifndef __TATCONFIGLOADERFACTORY__
#define __TATCONFIGLOADERFACTORY__

#include "TestConfiguration/TATConfigLoaderFromIniFile.h"
#include "TestConfiguration/ETATConfigurationSource.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class ITATConfigLoader;
class TATRuleNode;

/// <summary>
/// Factory class for creating configuration loader implementations.
/// </summary>
class TATConfigLoaderFactory
{

    // METHODS
	// ---------------
public:

    /// <summary>
	/// Creates a configuration loader whose implementation depends on the source of the configuration.
	/// </summary>
    /// <param name="source">The source of the configuration (a file, a database, a web service, or whatever is allowed).</param>
    /// <returns>
    /// The implementation for the configuration loader.
    /// </returns>
    ITATConfigLoader* CreateConfigLoader(const ETATConfigurationSource& source) const;

protected:

    /// <summary>
	/// Creates a configuration loader whose source is an INI file.
	/// </summary>
    /// <returns>
    /// The implementation for the configuration loader.
    /// </returns>
    ITATConfigLoader* CreateConfigLoaderFromIniFile() const;
    
    /// <summary>
	/// Creates a rule tree to be used by a configuration loader for parsing a configuration source.
	/// </summary>
    /// <returns>
    /// The complete rule tree to be used by any configuration loader.
    /// </returns>
    TATRuleNode* CreateRuleTree() const;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGLOADERFACTORY__
