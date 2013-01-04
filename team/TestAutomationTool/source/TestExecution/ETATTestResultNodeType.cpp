// [TERMS&CONDITIONS]

#include "TestExecution/ETATTestResultNodeType.h"

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

ETATTestResultNodeType::TNameValuePair ETATTestResultNodeType::sm_arValueName[] =
    {
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Result"), ETATTestResultNodeType::E_Result),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Case"),   ETATTestResultNodeType::E_Case),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Suite"),  ETATTestResultNodeType::E_Suite),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Module"), ETATTestResultNodeType::E_Module),
        std::pair<wxString, ETATTestResultNodeType::EnumType>(wxT("E_Root"),   ETATTestResultNodeType::E_Root),
    };

ETATTestResultNodeType::TNameValueMap ETATTestResultNodeType::sm_mapValueName(
        ETATTestResultNodeType::sm_arValueName ,
        &ETATTestResultNodeType::sm_arValueName[0] + sizeof(ETATTestResultNodeType::sm_arValueName) / sizeof(ETATTestResultNodeType::sm_arValueName[0])
    );

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
