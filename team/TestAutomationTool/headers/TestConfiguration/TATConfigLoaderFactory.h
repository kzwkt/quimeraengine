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

#ifndef __TATCONFIGLOADERFACTORY__
#define __TATCONFIGLOADERFACTORY__

#include "TestConfiguration/TATConfigLoaderFromIniFile.h"
#include "TestConfiguration/ETATConfigurationSource.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

class ITATConfigLoader;
class TATRuleNode;

/// <summary>
/// Factory class for creating configuration loader implementations.
/// </summary>
class TATConfigLoaderFactory
{

    // METHODS
	// ---------------
public:

    /// <summary>
	/// Creates a configuration loader whose implementation depends on the source of the configuration.
	/// </summary>
    /// <param name="source">The source of the configuration (a file, a database, a web service, or whatever is allowed).</param>
    /// <returns>
    /// The implementation for the configuration loader.
    /// </returns>
    ITATConfigLoader* CreateConfigLoader(const ETATConfigurationSource& source) const;

protected:

    /// <summary>
	/// Creates a configuration loader whose source is an INI file.
	/// </summary>
    /// <returns>
    /// The implementation for the configuration loader.
    /// </returns>
    ITATConfigLoader* CreateConfigLoaderFromIniFile() const;
    
    /// <summary>
	/// Creates a rule tree to be used by a configuration loader for parsing a configuration source.
	/// </summary>
    /// <returns>
    /// The complete rule tree to be used by any configuration loader.
    /// </returns>
    TATRuleNode* CreateRuleTree() const;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGLOADERFACTORY__
