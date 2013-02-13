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
