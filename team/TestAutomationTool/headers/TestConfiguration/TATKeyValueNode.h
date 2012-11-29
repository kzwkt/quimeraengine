// [TERMS&CONDITIONS]

#ifndef __TATKEYVALUENODE__
#define __TATKEYVALUENODE__

#include "TestConfiguration/TATConfigNode.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// A configuration node compound by a key (the name) and a value.
/// </summary>
class TATKeyValueNode : public TATConfigNode
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATKeyValueNode();

    /// <summary>
    /// Constructor that receives all the information a key-value node needs.
    /// </summary>
    /// <param name="strName">The name of the node (the key).</param>
    /// <param name="eType">The type of the node.</param>
    /// <param name="strValue">The value of the node.</param>
    TATKeyValueNode(const wxString& strName, const ETATConfigNodeType& eType, const wxString& strValue);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATKeyValueNode();


	// METHODS
	// ---------------
public:


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the value of the node.
    /// </summary>
    /// <returns>
    /// The value of the node.
    /// </returns>
    wxString GetValue() const;

    /// <summary>
    /// Sets the value of te node.
    /// </summary>
    /// <param name="strValue">The value of the node.</param>
    void SetValue(const wxString& strValue);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The value of the node.
    /// </summary>
    wxString m_strValue;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATKEYVALUENODE__
