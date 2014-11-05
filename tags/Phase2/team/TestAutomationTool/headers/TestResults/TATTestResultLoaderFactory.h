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

#ifndef __TATTESTRESULTLOADERFACTORY__
#define __TATTESTRESULTLOADERFACTORY__

#include "TestResults/ETATResultSource.h"
#include "TestResults/ITATTestResultLoader.h"
#include "TestResults/TATTestResultLoader.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Creates test result loader implementations.
/// </summary>
class TATTestResultLoaderFactory
{
	// METHODS
	// ---------------
public:

    /// <summary>
	/// Creates a test result loader whose implementation depends on the source of the result.
	/// </summary>
    /// <param name="eSource">The source of the result (a file, a database, a web service, or whatever is allowed).</param>
    /// <returns>
    /// The implementation for the test result loader.
    /// </returns>
    ITATTestResultLoader* CreateConfigLoader(const ETATResultSource& eSource) const;

protected:

    /// <summary>
	/// Creates a test result loader whose source is an XML file.
	/// </summary>
    /// <returns>
    /// The implementation for the test result loader.
    /// </returns>
    ITATTestResultLoader* CreateTestResultLoaderFromXmlFile() const;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTLOADERFACTORY__
