// [TERMS&CONDITIONS]

#ifndef __TATCONFIGNODE__
#define __TATCONFIGNODE__

#include "TATNode.h"
#include "TestConfiguration/ETATConfigNodeType.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// A node of a configuration tree. It's the base class for nodes that are intended to store configuration
/// information depending on their type. There are 3 types of configuration node: Root, Header and Value.
/// </summary>
class TATConfigNode : public TATNode
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATConfigNode();


	// METHODS
	// ---------------
public:

    /// <summary>
	/// Obtains a list of child nodes whose type matches the one being searched.
	/// </summary>
    /// <param name="type">The node type to search for.</param>
    /// <returns>
    /// A list of child nodes. If no child node is found, an empty list is returned.
    /// </returns>
    TATNode::TNodeCollection GetChildrenByType(const ETATConfigNodeType& type) const;


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// Gets the node's type.
	/// </summary>
    ETATConfigNodeType GetType() const;

    /// <summary>
	/// Sets the node's type.
	/// </summary>
    void SetType(const ETATConfigNodeType& type);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
	/// The node's type.
	/// </summary>
    ETATConfigNodeType m_type;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGNODE__
