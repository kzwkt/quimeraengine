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

#ifndef __TATTESTAUTOMATIONTOOLCONFIGURATIONWHITEBOX__
#define __TATTESTAUTOMATIONTOOLCONFIGURATIONWHITEBOX__

#include "TestConfiguration/TATTestAutomationToolConfiguration.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATTestAutomationToolConfiguration for testing purposes.
/// </summary>
class TATTestAutomationToolConfigurationWhiteBox : public TATTestAutomationToolConfiguration
{
	// METHODS
	// ---------------
public:

    // Exposed methods
    void Destroy()
    {
        TATTestAutomationToolConfiguration::Destroy();
    }

    void CombineFlags(const std::list<TATKeyValueNode*>& flags)
    {
        TATTestAutomationToolConfiguration::CombineFlags(flags);
    }

    void CombineFlagValue(std::list<TATKeyValueNode*>::const_iterator flagToCombine,
                          std::list<TATKeyValueNode*>::const_iterator flagListEnd,
                          std::map<wxString, wxString>& flagCombination,
                          std::list< std::map<wxString, wxString> >& flagCombinations) const
    {
        TATTestAutomationToolConfiguration::CombineFlagValue(flagToCombine, flagListEnd, flagCombination, flagCombinations);
    }

    // Method needed for tests
    ITATConfigLoader* GetExpectedConfigLoader() const
    {
        return m_pConfigLoader;
    }

    const std::map< wxString, std::map<wxString, wxString> >& GetExpectedFlagCombinations() const
    {
        return m_flagCombinations;
    }

    void SetExpectedFlagCombinations(const TATTestAutomationToolConfiguration::TFlagCombinationCollection& flagCombinations)
    {
        m_flagCombinations = flagCombinations;
    }
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLCONFIGURATIONWHITEBOX__
