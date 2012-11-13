// [TERMS&CONDITIONS]

#include "TestConfiguration/ETATConfigurationSource.h"


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

ETATConfigurationSource::TNameValuePair ETATConfigurationSource::sm_arValueName[] =
    {
        std::pair<wxString, ETATConfigurationSource::EnumType>(wxT("INI_FILE"),    ETATConfigurationSource::E_INI_FILE),
    };

ETATConfigurationSource::TNameValueMap ETATConfigurationSource::sm_mapValueName(
        ETATConfigurationSource::sm_arValueName ,
        &ETATConfigurationSource::sm_arValueName[0] + sizeof(ETATConfigurationSource::sm_arValueName) / sizeof(ETATConfigurationSource::sm_arValueName[0])
    );


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
