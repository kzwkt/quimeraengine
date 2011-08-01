// [TERMS&CONDITIONS]

#include "EQIntersections.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
EQIntersections::TNameValuePair EQIntersections::sm_arValueName[] =
    {
        std::pair<string_q, EQIntersections::EnumType>(QE_L("None"),    EQIntersections::E_None),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("One"), EQIntersections::E_One),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("Two"), EQIntersections::E_Two),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("More"), EQIntersections::E_More),
        std::pair<string_q, EQIntersections::EnumType>(QE_L("Infinite"),    EQIntersections::E_Infinite)
    };

EQIntersections::TNameValueMap EQIntersections::sm_mapValueName(
        EQIntersections::sm_arValueName ,
        &EQIntersections::sm_arValueName[0] + sizeof(EQIntersections::sm_arValueName) / sizeof(EQIntersections::sm_arValueName[0])
    );


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
