// [TERMS&CONDITIONS]

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

    const std::list< std::map<wxString, wxString> >& GetExpectedFlagCombinations() const
    {
        return m_flagCombinations;
    }
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLCONFIGURATIONWHITEBOX__
