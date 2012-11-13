// [TERMS&CONDITIONS]

#ifndef __ITATCONFIGLOADER__
#define __ITATCONFIGLOADER__

#include <wx/string.h>

    
namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class TATRuleNode;

/// <summary>
/// Loads the test system configuration.
/// </summary>
class ITATConfigLoader
{
	// CONSTRUCTORS
	// ---------------
protected:

	/// <summary>
	/// Default constructor.
	/// </summary>
	ITATConfigLoader(){};


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~ITATConfigLoader(){};


	// METHODS
	// ---------------
public:


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// Gets the rule tree used to parse the configuration source.
	/// </summary>
    /// <returns>
    /// A rule tree.
    /// </returns>
    virtual TATRuleNode* GetRuleTree() const=0;

    /// <summary>
	/// Gets the configuration source. It can be a file name, a connection string, a URL... it depends
    /// on the implementation.
	/// </summary>
    /// <returns>
    /// The configuration source.
    /// </returns>
    virtual wxString GetSource() const=0;

    /// <summary>
	/// Sets the configuration source. It can be a file name, a connection string, a URL... it depends
    /// on the implementation.
	/// </summary>
    /// <param name="strSource">The configuration source.</param>
    virtual void SetSource(const wxString& strSource)=0;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __ITATCONFIGLOADER__
