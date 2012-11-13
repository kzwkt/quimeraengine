// [TERMS&CONDITIONS]

#ifndef __TATCONFIGLOADERFROMINIFILEWHITEBOX__
#define __TATCONFIGLOADERFROMINIFILEWHITEBOX__

#include "TestConfiguration/TATConfigLoaderFromIniFile.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATConfigLoaderFromIniFile for testing purposes.
/// </summary>
class TATConfigLoaderFromIniFileWhiteBox : public TATConfigLoaderFromIniFile
{
    // CONSTRUCTORS
    // ---------------
public:

    // Necessary for testing purposes
    TATConfigLoaderFromIniFileWhiteBox(TATRuleNode* pRuleTree) : TATConfigLoaderFromIniFile(pRuleTree)
    {
    }


	// METHODS
	// ---------------
public:

    // Exposed methods
    void Destroy()
    {
        TATConfigLoaderFromIniFile::Destroy();
    }
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGLOADERFROMINIFILEWHITEBOX__
