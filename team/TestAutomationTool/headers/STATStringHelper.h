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

#ifndef __STATSTRINGHELPER__
#define __STATSTRINGHELPER__

#include <list>
#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Helper class that provides several utility methods to work with strings.
/// </summary>
class STATStringHelper
{
	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	STATStringHelper();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Given a source string and a separator token, it returns a list with every string chunk separated by the 
    /// separator token (not included) in the source string.
    /// </summary>
    /// <param name="strSource">The source string to be split.</param>
    /// <param name="strSeparator">The token that acts as separator inside the source string.</param>
    /// <returns>
    /// Returns a list with every string chunk separated by the separator token (not included) in the source string.
    /// If the separator is not found or is empty, then only one entry is returned, containing the source string.
    /// If the source string is empty, an empty list is returned.
    /// </returns>
    static std::list<wxString> Split(const wxString& strSource, const wxString& strSeparator);

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __STATSTRINGHELPER__
