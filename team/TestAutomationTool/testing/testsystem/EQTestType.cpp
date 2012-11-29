// [TERMS&CONDITIONS]

#include "EQTestType.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Test
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
    
ETATTestType::TNameValuePair ETATTestType::sm_arValueName[] =
    {
        std::pair<wxString, ETATTestType::EnumType>(wxT("UnitTest"),    ETATTestType::E_UnitTest),
        std::pair<wxString, ETATTestType::EnumType>(wxT("PerformanceTest"),    ETATTestType::E_PerformanceTest),
        std::pair<wxString, ETATTestType::EnumType>(wxT("EnduranceTest"),    ETATTestType::E_EnduranceTest),
    };

ETATTestType::TNameValueMap ETATTestType::sm_mapValueName(
        ETATTestType::sm_arValueName ,
        &ETATTestType::sm_arValueName[0] + sizeof(ETATTestType::sm_arValueName) / sizeof(ETATTestType::sm_arValueName[0])
    );


} //namespace Test
} //namespace TestAutomationTool
} //namespace Kinesis
