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

#ifndef __TATCONFIGLOADERFROMINIFILE__
#define __TATCONFIGLOADERFROMINIFILE__

#include "TestConfiguration/ITATConfigLoader.h"

#include <wx/string.h>

#include "TestConfiguration/ETATConfigNodeType.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class TATRuleNode;

/// <summary>
/// Component that parses an INI file that contains configuration values following a defined format. To
/// acomplish that, the configuration loader uses a set of rules to validate and identify every configuration
/// parameter.
/// </summary>
class TATConfigLoaderFromIniFile : public ITATConfigLoader
{
    // CONSTANTS
    // ---------------
protected:

    /// <summary>
	/// The token to be used as key/value separator.
	/// </summary>
    static const wxString KEYVALUE_SEPARATOR_TOKEN;

    /// <summary>
	/// The token to mark the beginning of a header name.
	/// </summary>
    static const wxString HEADER_OPENING_TOKEN;

    /// <summary>
	/// The token to mark the ending of a header name.
	/// </summary>
    static const wxString HEADER_CLOSING_TOKEN;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Constructor that receives a rule tree.
	/// </summary>
    /// <param name="pRuleTree">A rule tree. It should't be null.</param>
	TATConfigLoaderFromIniFile(TATRuleNode* pRuleTree);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATConfigLoaderFromIniFile();


	// METHODS
	// ---------------
public:

    //! @copydoc ITATConfigLoader::Load()
    virtual void Load();

    //! @copydoc ITATConfigLoader::Reset()
    virtual void Reset();

protected:

    /// <summary>
	/// Releases all the resources.
	/// </summary>
    void Destroy();

    /// <summary>
    /// Validates a node of a value tree based on a rule. If the validation fails, an exception is thrown.
    /// </summary>
    /// <param name="pValueNode">The value node to validate.</param>
    /// <param name="pRuleNode">The validation rule.</param>
    /// <param name="pRootNode">The parent of the value node.</param>
    void ApplyRule(TATKeyValueNode* pValueNode, TATRuleNode* pRuleNode, TATKeyValueNode* pRootNode);

    /// <summary>
    /// Validates the nodes of a value tree, applying some rules after the tree has been created.
    /// </summary>
    /// <param name="pRuleTree">A rule tree.</param>
    /// <param name="pValueTree">The value tree to validate.</param>
    void ApplyFinalRules(TATRuleNode* pRuleTree, TATKeyValueNode* pValueTree);

    /// <summary>
    /// Identifies which type of node does a line of text represents.
    /// </summary>
    /// <param name="strLine">A line of text.</param>
    /// <returns>
    /// The type of the node represented.
    /// </returns>
    ETATConfigNodeType GetTypeOfNode(const wxString& strLine) const;

    /// <summary>
    /// Extracts the "name" part from a line of text that is supossed to be divided by an equals (=) character.
    /// </summary>
    /// <param name="strLine">A line of text.</param>
    /// <returns>
    /// The name of the node represented by the line.
    /// </returns>
    wxString GetNameOfNode(const wxString& strLine) const;

    /// <summary>
    /// Extracts the "value" part from a line of text that is supposed to be divided by an equals (=) character.
    /// </summary>
    /// <param name="strLine">A line of text.</param>
    /// <returns>
    /// The value of the node represented by the line.
    /// </returns>
    wxString GetValueOfNode(const wxString& strLine) const;


	// PROPERTIES
	// ---------------
public:

    //! @copydoc ITATConfigLoader::GetRuleTree()
    virtual TATRuleNode* GetRuleTree() const;

    //! @copydoc ITATConfigLoader::GetValueTree()
    virtual TATKeyValueNode* GetValueTree() const;

    //! @copydoc ITATConfigLoader::GetSource()
    virtual wxString GetSource() const;

    //! @copydoc ITATConfigLoader::SetSource(const wxString&)
    virtual void SetSource(const wxString& strSource);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
	/// The configuration source.
	/// </summary>
    wxString m_strSource;

    /// <summary>
	/// The rule tree.
	/// </summary>
    TATRuleNode* m_pRuleTree;

    /// <summary>
    /// The value tree.
    /// </summary>
    TATKeyValueNode* m_pValueTree;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGLOADERFROMINIFILE__
