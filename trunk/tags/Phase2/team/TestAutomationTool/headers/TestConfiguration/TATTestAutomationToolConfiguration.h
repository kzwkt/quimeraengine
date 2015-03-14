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

#ifndef __TATTESTAUTOMATIONTOOLCONFIGURATION__
#define __TATTESTAUTOMATIONTOOLCONFIGURATION__

#include <list>
#include <map>

#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class ITATConfigLoader;
class TATKeyValueNode;

/// <summary>
/// Manages the business logic of a functional sector of the application in a UI-independent way.
/// Provides functionality related to the configuration of the tests.
/// </summary>
class TATTestAutomationToolConfiguration
{
    // TYPEDEFS
    // ---------------
public:

    typedef std::map< wxString, std::map<wxString, wxString> > TFlagCombinationCollection;
    typedef std::pair< wxString, std::map<wxString, wxString> > TFlagCombination;

    
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

    /// <summary>
    /// Stores or removes a compiler configuration value in the list of selected values.
    /// </summary>
    /// <param name="strCompilerConfig">The value to be selected.</param>
    /// <param name="bSelected">True means selection while False means unselection.</param>
    void SelectCompilerConfiguration(const wxString& strCompilerConfig, const bool& bSelected);

    /// <summary>
    /// Stores or removes a flag combination in the list of selected combinations.
    /// </summary>
    /// <param name="strCompilerConfig">The flag combination to be selected.</param>
    /// <param name="bSelected">True means selection while False means unselection.</param>
    void SelectFlagCombination(const wxString& strFlagCombination, const bool& bSelected);

protected:

    /// <summary>
    /// Generates a list of flag values combinations.
    /// </summary>
    /// <param name="flags">List of flags to be combine.</param>
    void CombineFlags(const std::list<TATKeyValueNode*>& flags);

    /// <summary>
    /// Releases all the resources.
    /// </summary>
    void Destroy();

    /// <summary>
    /// Combines sets of flag values recursively, creating a cartesian product.
    /// </summary>
    /// <param name="flagToCombine">Flag whose values are to be combined.</param>
    /// <param name="flagListEnd">Marks the end of the flag list.</param>
    /// <param name="flagCombination">Current combination of flag values in process.</param>
    /// <param name="outFlagCombinations">Output parameter. It's the generated list of combinations.</param>
    void CombineFlagValue(std::list<TATKeyValueNode*>::const_iterator flagToCombine, 
                          std::list<TATKeyValueNode*>::const_iterator flagListEnd,
                          std::map<wxString, wxString> flagCombination,
                          std::list< std::map<wxString, wxString> >& outFlagCombinations) const;

	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets all the compiler configurations.
    /// </summary>
    /// <returns>
    /// A list of the name of all the compiler configurations available.
    /// </returns>
    std::list<wxString> GetCompilerConfigurations() const;

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
    /// Gets the generated collection of flag value combinations.
    /// </summary>
    /// <returns>
    /// A collection of all the flag value combinations possible.
    /// </returns>
    TFlagCombinationCollection GetFlagCombinations() const;

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
    /// A collection of all the flag value combinations possible.
    /// </summary>
    TFlagCombinationCollection m_flagCombinations;
    
    /// <summary>
    /// The configuration loader.
    /// </summary>
    ITATConfigLoader* m_pConfigLoader;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLCONFIGURATION__
