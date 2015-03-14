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
class TATKeyValueNode;

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

    /// <summary>
    /// Access to the configuration source and transforms that information into a value tree.
    /// </summary>
    virtual void Load()=0;

    /// <summary>
    /// Returns the component to its initial status (value tree will be deleted, for example).
    /// </summary>
    virtual void Reset()=0;


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
	/// Gets the value tree generated after parsing the configuration source.
	/// </summary>
    /// <returns>
    /// A value tree.
    /// </returns>
    virtual TATKeyValueNode* GetValueTree() const=0;

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
