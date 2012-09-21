// [TERMS&CONDITIONS]

#ifndef __TATNODE__
#define __TATNODE__

#include <wx/string.h>
#include <map>
#include <list>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Represents a N-ary tree node. A node is identified by its name. A node can have more than 
/// one child with the same name.
/// </summary>
class TATNode
{
    // TYPEDEFS
    // ---------------
public:

    typedef std::multimap<const wxString, TATNode*> TNodeCollection;
    typedef std::pair<const wxString, TATNode*> TNodeNamePair;
    typedef std::list<wxString> TNodeNameList;
    typedef std::pair<TNodeCollection::const_iterator, TNodeCollection::const_iterator> TNodeRange;

    
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATNode();

    /// <summary>
    /// Constructor that receives the node's name.
    /// </summary>
    /// <param name="strName">The name that identifies the node.</param>
    TATNode(const wxString strName);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATNode();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Adds a node to the children list.
    /// </summary>
    /// <remarks>
    /// The node to be added can't be the same as the parent node. Due to this class' simplicity,
    /// no cycles checking is performed so be careful not to add the same node as ascendant or descendant
    /// of itself.
    /// </remarks>
    /// <param name="pChildNode">The node to be added. Null values are not added.</param>
    void AddChild(TATNode* pChildNode);

    /// <summary>
    /// Adds a node collection to the children list.
    /// </summary>
    /// <remarks>
    /// The parent node can't be contained in the collection. Due to this class' simplicity,
    /// no cycles checking is performed so be careful not to add the same node as ascendant or descendant
    /// of itself.
    /// </remarks>
    /// <param name="children">The node collection to be added. Null values are not added.</param>
    void AddChildren(const TNodeCollection& children);

    /// <summary>
    /// Gets child nodes by their name.
    /// </summary>
    /// <param name="strChildName">The name of the child node/s to be retrieved.</param>
    /// <returns>
    /// The child nodes whose name matches the given one.
    /// </returns>
    TNodeCollection GetChild(const wxString& strChildName) const;

    /// <summary>
    /// Removes all child nodes identified by a given name.
    /// </summary>
    /// <param name="strChildName">The name of the children to be removed. If the node is not found, nothing happens.</param>
    void RemoveChild(const wxString& strChildName);

    /// <summary>
    /// Removes a set of child nodes whose names are included in the given list.
    /// </summary>
    /// <param name="childrenNames">The list of child node's names. If nodes are not found, nothing happens.</param>
    void RemoveChildren(const TNodeNameList& childrenNames);

    /// <summary>
    /// Checks if there is a child node whose name coincides with the given name.
    /// </summary>
    /// <param name="strChildName">The name of the child node to check for existence.</param>
    /// <returns>
    /// True when there is a child node with the given name; false otherwise.
    /// </returns>
    bool HasChild(const wxString& strChildName) const;


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the name of the node.
    /// </summary>
    /// <returns>
    /// The name of the node.
    /// </returns>
    wxString GetName() const;

    /// <summary>
    /// Sets the name of the node.
    /// </summary>
    /// <param name="strName">The new name of the node.</param>
    void SetName(const wxString& strName);

    /// <summary>
    /// Gets the collection of child nodes.
    /// </summary>
    /// <returns>
    /// A collection of child nodes.
    /// </returns>
    const TNodeCollection& GetChildren() const;
    
    /// <summary>
    /// Checks if the node has children.
    /// </summary>
    /// <returns>
    /// True when there is, at least, one child node; false otherwise.
    /// </returns>
    bool HasChildren() const;


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The name of the node.
    /// </summary>
    wxString m_strName;

    /// <summary>
    /// The collection of child nodes.
    /// </summary>
    TNodeCollection m_children;
    
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATNODE__
