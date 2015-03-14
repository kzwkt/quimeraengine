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

#ifndef __TATRULENODE__
#define __TATRULENODE__

#include "TestConfiguration/TATConfigNode.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// A node of a rule tree. Represents a parsing rule, i. e. a set of conditions that a parser uses to
/// read and validate data from a formatted source. A rule indicates whether an incoming configuration 
/// node's value can be empty, must be present or can appear once or more times.
/// </summary>
class TATRuleNode : public TATConfigNode
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATRuleNode();

    /// <summary>
	/// Constructor that receives all the information a rule node can store but child nodes.
	/// </summary>
    /// <param name="strName">The name of the node.</param>
    /// <param name="nMaxCount">Maximum times a node of certain type can appear. Zero means infinite.</param>
    /// <param name="bCanBeEmpty">Indicates whether the node's value can be empty or not.</param>
    /// <param name="bIsObligatory">Indicates whether the node is mandatory or not.</param>
    /// <param name="type">The type of the node.</param>
    TATRuleNode(const wxString& strName, const int nMaxCount, const bool& bCanBeEmpty, const bool& bIsObligatory, const ETATConfigNodeType& type);


	// METHODS
	// ---------------
public:


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// Gets the maximum times the type of the node can appear in the same scope of the tree.
	/// </summary>
    /// <returns>
    /// Returns the number of times. Zero means infinite.
    /// </returns>
    int GetMaxCount() const;

    /// <summary>
	/// Sets the maximum times the type of the node can appear in the same scope of the tree
	/// </summary>
    /// <param name="nMaCount">Maximum times a node of certain type can appear. Zero means infinite.</param>
    void SetMaxCount(const int& nMaxCount);

    /// <summary>
	/// Gets whether the node must appear in the rule tree or not.
	/// </summary>
    /// <returns>
    /// True if the node is obligatory, false otherwise.
    /// </returns>
    bool GetIsObligatory() const;

    /// <summary>
	/// Sets whether the node must appear in the rule tree or not.
	/// </summary>
    /// <param name="bIsObligatory">Indicates whether the node is mandatory or not.</param>
    void SetIsObligatory(const bool& bIsObligatory);

    /// <summary>
	/// Gets whether the node's value can be empty or not.
	/// </summary>
    /// <returns>
    /// True if the node's value can be empty, false otherwise.
    /// </returns>
    bool GetCanBeEmpty() const;

    /// <summary>
	/// Sets whether the node's value can be empty or not.
	/// </summary>
    /// <param name="bCanBeEmpty">Indicates whether the node's value can be empty or not.</param>
    void SetCanBeEmpty(const bool& bCanBeEmpty);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
	/// Indicates whether the node's value can be empty or not.
	/// </summary>
    bool m_bCanBeEmpty;

    /// <summary>
	/// Indicates whether the node is mandatory or not.
	/// </summary>
    bool m_bIsObligatory;

    /// <summary>
	/// Maximum times a node of certain type can appear. Zero means infinite.
	/// </summary>
    int m_nMaxCount;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATRULENODE__
