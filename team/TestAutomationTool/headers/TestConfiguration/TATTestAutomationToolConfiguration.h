// [TERMS&CONDITIONS]

#ifndef __TATTESTAUTOMATIONTOOLCONFIGURATION__
#define __TATTESTAUTOMATIONTOOLCONFIGURATION__

#include <list>

#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class ITATConfigLoader;

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
    /// <param name="strConfigurationSource">The source of the configuration (a file path, a connection string, etc.)</param>    
    void LoadConfiguration(const wxString& strConfigurationSource);

protected:

    /// <summary>
    /// Generates a list of flag values combinations.
    /// </summary>
    void CombineFlags();

    /// <summary>
    /// Releases all the resources.
    /// </summary>
    void Destroy();


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the list of selected compiler configurations.
    /// </summary>
    /// <returns>
    /// A list of the name of the selected compiler configurations.
    /// </returns>
    std::list<wxString> GetCompilerConfigurationSelection() const;

    /// <summary>
    /// Gets the list of selected flag value combinations.
    /// </summary>
    /// <returns>
    /// A list of the name of the selected flag combinations.
    /// </returns>
    std::list<wxString> GetFlagCombinationSelection() const;

    /// <summary>
    /// Gets the generated list of flag value combinations.
    /// </summary>
    /// <returns>
    /// A list of all the flag value combinations possible.
    /// </returns>
    std::list<wxString> GetFlagCombinations() const;

    /// <summary>
    /// Gets an instance of a configuration loader.
    /// </summary>
    /// <returns>
    /// The configuration loader.
    /// </returns>
    ITATConfigLoader* GetConfigLoader() const;


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
