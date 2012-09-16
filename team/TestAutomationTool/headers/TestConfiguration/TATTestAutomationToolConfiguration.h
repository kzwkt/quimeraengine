// [TERMS&CONDITIONS]

#ifndef __TATTESTAUTOMATIONTOOLCONFIGURATION__
#define __TATTESTAUTOMATIONTOOLCONFIGURATION__

#include <list>

#include <wx\string.h>

#include "TestConfiguration\ITATConfigLoader.h"

using Kinesis::TestAutomationTool::Backend::ITATConfigLoader;

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Manages the business logic of a functional sector of the application in a UI-independent way.
/// Provides functionality related to the configuration of the tests.
/// </summary>
class TATTestAutomationToolConfiguration
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATTestAutomationToolConfiguration();


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATTestAutomationToolConfiguration();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Loads the test system configuration and parses it to create an internal data structure.
    /// </summary>
    void LoadConfiguration();

protected:

    /// <summary>
    /// Generates a list of flag values combinations.
    /// </summary>
    void CombineFlags();


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the list of selected compiler configurations.
    /// </summary>
    /// <returns>
    /// A list of the name of the selected compiler configurations.
    /// </returns>
    std::list<wxString> GetCompilerConfigurationSelection();

    /// <summary>
    /// Gets the list of selected flag value combinations.
    /// </summary>
    /// <returns>
    /// A list of the name of the selected flag combinations.
    /// </returns>
    std::list<wxString> GetFlagCombinationSelection();

    /// <summary>
    /// Gets the generated list of flag value combinations.
    /// </summary>
    /// <returns>
    /// A list of all the flag value combinations possible.
    /// </returns>
    std::list<wxString> GetFlagCombinations();

    /// <summary>
    /// Gets an instance of a configuration loader.
    /// </summary>
    /// <returns>
    /// The configuration loader.
    /// </returns>
    ITATConfigLoader* GetConfigLoader();


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// A list of the name of the selected compiler configurations.
    /// </summary>
    std::list<wxString> m_compilerConfigurationSelection;
    
    /// <summary>
    /// A list of the name of the selected flag combinations.
    /// </summary>
    std::list<wxString> m_flagCombinationSelection;
    
    /// <summary>
    /// A list of all the flag value combinations possible.
    /// </summary>
    std::list<wxString> m_flagCombinations;
    
    /// <summary>
    /// The configuration loader.
    /// </summary>
    ITATConfigLoader* m_pConfigLoader;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLCONFIGURATION__
