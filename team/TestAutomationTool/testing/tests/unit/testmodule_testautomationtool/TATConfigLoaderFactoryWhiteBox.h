// [TERMS&CONDITIONS]

#ifndef __TATCONFIGLOADERFACTORYWHITEBOX__
#define __TATCONFIGLOADERFACTORYWHITEBOX__

#include "TestConfiguration/TATConfigLoaderFactory.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATConfigLoaderFactory for testing purposes.
/// </summary>
class TATConfigLoaderFactoryWhiteBox : public TATConfigLoaderFactory
{
	// METHODS
	// ---------------
public:

    // Exposed methods
    ITATConfigLoader* CreateConfigLoaderFromIniFile() const
    {
        return TATConfigLoaderFactory::CreateConfigLoaderFromIniFile();
    }
    
    TATRuleNode* CreateRuleTree() const
    {
        return TATConfigLoaderFactory::CreateRuleTree();
    }

};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGLOADERFACTORYWHITEBOX__
