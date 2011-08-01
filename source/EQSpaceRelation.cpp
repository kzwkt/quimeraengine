// [TERMS&CONDITIONS]

#include "EQSpaceRelation.h"

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
EQSpaceRelation::TNameValuePair EQSpaceRelation::sm_arValueName[] =
    {
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("Contained"),    EQSpaceRelation::E_Contained),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("PositiveSide"), EQSpaceRelation::E_PositiveSide),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("NegativeSide"), EQSpaceRelation::E_NegativeSide),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("BothSides"),    EQSpaceRelation::E_BothSides)
    };

EQSpaceRelation::TNameValueMap EQSpaceRelation::sm_mapValueName(
        EQSpaceRelation::sm_arValueName ,
        &EQSpaceRelation::sm_arValueName[0] + sizeof(EQSpaceRelation::sm_arValueName) / sizeof(EQSpaceRelation::sm_arValueName[0])
    );

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
