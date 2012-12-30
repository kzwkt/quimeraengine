// [TERMS&CONDITIONS]

#ifndef __TATTESTRESULTLOADERFACTORYWHITEBOX__
#define __TATTESTRESULTLOADERFACTORYWHITEBOX__

#include "TestExecution/TATTestResultLoaderFactory.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATTestResultLoaderFactory for testing purposes.
/// </summary>
class TATTestResultLoaderFactoryWhiteBox : public TATTestResultLoaderFactory
{
public:

    using TATTestResultLoaderFactory::CreateTestResultLoaderFromXmlFile;
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTRESULTLOADERFACTORYWHITEBOX__
