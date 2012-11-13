// [TERMS&CONDITIONS]

#ifndef __TATCONFIGLOADERFROMINIFILE__
#define __TATCONFIGLOADERFROMINIFILE__

#include "TestConfiguration/ITATConfigLoader.h"

#include <wx/string.h>


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
protected:
        
    /// <summary>
	/// Releases all the resources.
	/// </summary>
    void Destroy();


	// PROPERTIES
	// ---------------
public:

    //! @copydoc ITATConfigLoader::GetRuleTree()
    virtual TATRuleNode* GetRuleTree() const;

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

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGLOADERFROMINIFILE__
