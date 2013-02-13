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
