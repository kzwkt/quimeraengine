// [TERMS&CONDITIONS]

#include "TestExecution/ETATColor.h"

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

ETATColor::TNameValuePair ETATColor::sm_arValueName[] =
    {
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Black"),  ETATColor::E_Black),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_White"),  ETATColor::E_White),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Red"),    ETATColor::E_Red),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Yellow"), ETATColor::E_Yellow),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Blue"),   ETATColor::E_Blue),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Green"),  ETATColor::E_Green),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Purple"), ETATColor::E_Purple),
        std::pair<wxString, ETATColor::EnumType>(wxT("E_Grey"),   ETATColor::E_Grey),
    };

ETATColor::TNameValueMap ETATColor::sm_mapValueName(
        ETATColor::sm_arValueName ,
        &ETATColor::sm_arValueName[0] + sizeof(ETATColor::sm_arValueName) / sizeof(ETATColor::sm_arValueName[0])
    );

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
