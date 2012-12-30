// [TERMS&CONDITIONS]

#include "TestExecution/TATTestResultLoaderFactory.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

ITATTestResultLoader* TATTestResultLoaderFactory::CreateConfigLoader(const ETATResultSource& eSource) const
{
    switch(eSource)
    {
    case ETATResultSource::E_XmlFile:
        return this->CreateTestResultLoaderFromXmlFile();
        break;
    default:
        return NULL;
        break;
    }
}

ITATTestResultLoader* TATTestResultLoaderFactory::CreateTestResultLoaderFromXmlFile() const
{
    return new TATTestResultLoader();
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
