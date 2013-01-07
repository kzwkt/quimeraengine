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

    if(strSource.size() > 0 && strSeparator.size() > 0)
    {
        const int LENGTH = strSource.size();

        int nCurrentPos = 0;
        int nLastFoundPos = 0;

        do
        {
            // Searches for the next separator
            nCurrentPos = strSource.find(strSeparator, nCurrentPos);

            // No separator found
            if(nCurrentPos == -1)
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
    }
    else if(strSource.size() > 0 && strSeparator.size() == 0)
    {
        // The full string is returned
        result.push_back(strSource);
    }

    return result;
}
    

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
