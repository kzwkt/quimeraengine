// [TERMS&CONDITIONS]

#include "TestConfiguration/ETATConfigNodeType.h"


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

ETATConfigNodeType::TNameValuePair ETATConfigNodeType::sm_arValueName[] =
    {
        std::pair<wxString, ETATConfigNodeType::EnumType>(wxT("E_ROOT"),    ETATConfigNodeType::E_ROOT),
        std::pair<wxString, ETATConfigNodeType::EnumType>(wxT("E_HEADER"),    ETATConfigNodeType::E_HEADER),
        std::pair<wxString, ETATConfigNodeType::EnumType>(wxT("E_VALUE"),    ETATConfigNodeType::E_VALUE),
    };

ETATConfigNodeType::TNameValueMap ETATConfigNodeType::sm_mapValueName(
        ETATConfigNodeType::sm_arValueName ,
        &ETATConfigNodeType::sm_arValueName[0] + sizeof(ETATConfigNodeType::sm_arValueName) / sizeof(ETATConfigNodeType::sm_arValueName[0])
    );


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
