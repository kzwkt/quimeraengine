// [TERMS&CONDITIONS]

#include "STATStringHelper.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

std::list<wxString> STATStringHelper::Split(const wxString& strSource, const wxString& strSeparator)
{
    std::list<wxString> result;

    const int LENGTH = strSource.size();

    int nCurrentPos = 0;
    int nLastFoundPos = 0;

    do
    {
        // Searches for the next separator
        nCurrentPos = strSource.find(strSeparator, nCurrentPos);

        // No separator found
        if(nCurrentPos == wxString::npos)
            break;

        // Saves the chuck of string from the last separator to the current one
        result.push_back(strSource.substr(nLastFoundPos, nCurrentPos - nLastFoundPos));

        // Step forward
        nCurrentPos += strSeparator.size();
        nLastFoundPos = nCurrentPos;

    } while(nCurrentPos < LENGTH);

    if(nLastFoundPos < LENGTH)
    {
        // Stores the last chunk (when the string doesn't ends with a separator)
        result.push_back(strSource.substr(nLastFoundPos));
    }

    return result;
}
    

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
