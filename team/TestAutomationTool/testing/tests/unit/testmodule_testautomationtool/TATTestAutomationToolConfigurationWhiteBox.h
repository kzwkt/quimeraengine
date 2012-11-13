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

    // Method needed for tests
    ITATConfigLoader* GetExpectedConfigLoader() const
    {
        return m_pConfigLoader;
    }

};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLCONFIGURATIONWHITEBOX__
