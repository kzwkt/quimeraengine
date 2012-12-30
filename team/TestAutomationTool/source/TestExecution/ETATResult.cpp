// [TERMS&CONDITIONS]

#include "TestExecution/ETATResult.h"

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

ETATResult::TNameValuePair ETATResult::sm_arValueName[] =
    {
        std::pair<wxString, ETATResult::EnumType>(wxT("E_Success"),  ETATResult::E_Success),
        std::pair<wxString, ETATResult::EnumType>(wxT("E_Fail"),     ETATResult::E_Fail),
        std::pair<wxString, ETATResult::EnumType>(wxT("E_Error"),    ETATResult::E_Error),
        std::pair<wxString, ETATResult::EnumType>(wxT("E_NoResult"), ETATResult::E_NoResult),
    };

ETATResult::TNameValueMap ETATResult::sm_mapValueName(
        ETATResult::sm_arValueName ,
        &ETATResult::sm_arValueName[0] + sizeof(ETATResult::sm_arValueName) / sizeof(ETATResult::sm_arValueName[0])
    );

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
