// [TERMS&CONDITIONS]

#include "QBoolean.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace DataTypes
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

string_q QBoolean::ToString(const bool& bValue)
{
    if (bValue)
    {
        return QE_L("true");
    }
    else
    {
        return QE_L("false");
    }
}

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
