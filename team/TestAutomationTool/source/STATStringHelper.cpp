//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

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
