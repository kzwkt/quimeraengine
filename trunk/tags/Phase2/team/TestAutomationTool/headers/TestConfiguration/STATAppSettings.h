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

#ifndef __STATAPPSETTINGS__
#define __STATAPPSETTINGS__

#include <wx/string.h>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Class that stores application settings.
/// </summary>
class STATAppSettings
{
	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor.
	/// </summary>
	STATAppSettings();


	// DESTRUCTOR
	// ---------------
private:

	/// <summary>
	/// Destructor.
	/// </summary>		
	~STATAppSettings();


	// METHODS
	// ---------------
public:


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// The full path (including file name) where the test configuration file can be found.
	/// </summary>
    /// <returns>
    /// The full path (including file name) where the test configuration file can be found.
    /// </returns>
    static const wxString& GetConfigurationFilePath();


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
	/// The full path (including file name) where the test configuration file can be found.
	/// </summary>
    static const wxString sm_strConfigurationFilePath;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __STATAPPSETTINGS__
