// [TERMS&CONDITIONS]

#include "EQTestType.h"

namespace Kinesis
{
namespace QuimeraEngine
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
    
EQTestType::TNameValuePair EQTestType::sm_arValueName[] =
    {
        std::pair<string_q, EQTestType::EnumType>(QE_L("UnitTest"),    EQTestType::E_UnitTest),
        std::pair<string_q, EQTestType::EnumType>(QE_L("PerformanceTest"),    EQTestType::E_PerformanceTest),
        std::pair<string_q, EQTestType::EnumType>(QE_L("EnduranceTest"),    EQTestType::E_EnduranceTest),
    };

EQTestType::TNameValueMap EQTestType::sm_mapValueName(
        EQTestType::sm_arValueName ,
        &EQTestType::sm_arValueName[0] + sizeof(EQTestType::sm_arValueName) / sizeof(EQTestType::sm_arValueName[0])
    );


} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis
