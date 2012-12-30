// [TERMS&CONDITIONS]

#include "TestExecution/ETATResultSource.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

ETATResultSource::TNameValuePair ETATResultSource::sm_arValueName[] =
    {
        std::pair<wxString, ETATResultSource::EnumType>(wxT("E_XmlFile"), ETATResultSource::E_XmlFile),
    };

ETATResultSource::TNameValueMap ETATResultSource::sm_mapValueName(
        ETATResultSource::sm_arValueName ,
        &ETATResultSource::sm_arValueName[0] + sizeof(ETATResultSource::sm_arValueName) / sizeof(ETATResultSource::sm_arValueName[0])
    );

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
