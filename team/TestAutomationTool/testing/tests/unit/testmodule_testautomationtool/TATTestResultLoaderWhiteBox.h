// [TERMS&CONDITIONS]

#ifndef __TATTESTRESULTLOADERWHITEBOX__
#define __TATTESTRESULTLOADERWHITEBOX__

#include "TestExecution/TATTestResultLoader.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATTestResultLoader for testing purposes.
/// </summary>
class TATTestResultLoaderWhiteBox : public TATTestResultLoader
{
public:

    using TATTestResultLoader::Destroy;
    using TATTestResultLoader::ParseXmlToTree;

    // PROPERTIES
    // -------------
public:

    void SetTestResultTree_ForTestingPurposes(TATTestResultNode* pTestResultTree)
    {
        m_pTestResultTree = pTestResultTree;
    }
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTLOADERWHITEBOX__
