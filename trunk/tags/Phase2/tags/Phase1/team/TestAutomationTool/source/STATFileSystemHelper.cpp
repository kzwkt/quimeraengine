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

#include "STATFileSystemHelper.h"

#include <vector>

#include <stdio.h>

#ifdef TAT_OS_WINDOWS
    #include <process.h>
#elif defined(TAT_OS_LINUX)
    #include <unistd.h>
#endif


#include <wx/filefn.h>
#include <wx/textfile.h>
#include <wx/dir.h>

#include "ExternalDefinitions.h"
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
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

#ifdef TAT_OS_WINDOWS
    const wxString STATFileSystemHelper::sm_strExecutableFileExtension = wxT("exe");
#elif defined(TAT_OS_LINUX)
    const wxString STATFileSystemHelper::sm_strExecutableFileExtension = wxT("sh");
// TODO [Thund]: Port for Mac
#endif


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

bool STATFileSystemHelper::Read(const wxString& strFilePath, wxString& strReadStream)
{
    bool bSuccess = true;

    strReadStream = wxT("");
    wxTextFile file(strFilePath);

    if(file.Exists() && file.Open(strFilePath))
    {
        wxString strCompleteFile = wxT("");
        const size_t LINE_COUNT_IN_FILE = file.GetLineCount();

        try
        {
            for(size_t i = 0; i < LINE_COUNT_IN_FILE; ++i)
            {
                strCompleteFile += file.GetLine(i);

                if(i < LINE_COUNT_IN_FILE - 1)
                {
                    // Only appends new line characters when not reading the last line
                    strCompleteFile += TAT_NEWLINE_TOKEN;
                }
            }
        }
        catch(std::exception ex)
        {
            bSuccess = false;
        }

        file.Close();

        strReadStream = strCompleteFile;
    }
    else
    {
        bSuccess = false;
    }

    return bSuccess;
}

bool STATFileSystemHelper::Delete(const wxString& strFilePath)
{
    if(wxFileExists(strFilePath))
        return wxRemoveFile(strFilePath);
    else
        return false;
}

bool STATFileSystemHelper::Move(const wxString& strFromFilePath, const wxString& strToFilePath)
{
    if(wxFileExists(strFromFilePath) && wxDirExists(wxPathOnly(strToFilePath)))
    {
        if(wxCopyFile(strFromFilePath, strToFilePath, true))
        {
            return wxRemoveFile(strFromFilePath);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool STATFileSystemHelper::Rename(const wxString& strFilePath, const wxString& strNewFileName)
{
    if(wxFileExists(strFilePath))
        return wxRenameFile(strFilePath, wxPathOnly(strFilePath) + wxT("/") + strNewFileName, false);
    else
        return false;
}

bool STATFileSystemHelper::Execute(const wxString& strFilePath, const wxString& strParams, TATShellProcess::ITATShellProcessListener* pListener)
{
    // A very interesting link: http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044654269&id=1043284392
    // Nice information for getting the console output: http://stackoverflow.com/questions/2033878/cross-platform-redirect-of-standard-input-and-output-of-spawned-process-in-nativ

    bool bResult = false;

    try
    {
        TATShellProcess buildingProcess(strFilePath + wxT(" ") + strParams,
                                        pListener);
        buildingProcess.Execute(true);

        bResult = true;
    }
    catch(...)
    {
        bResult = false;
    }

    return bResult;
}

bool STATFileSystemHelper::Exists(const wxString& strFilePath)
{
    return wxFileExists(strFilePath);
}

bool STATFileSystemHelper::Copy(const wxString& strFromFilePath, const wxString& strToFilePath)
{
    if(wxFileExists(strFromFilePath) && wxDirExists(wxPathOnly(strToFilePath)))
        return wxCopyFile(strFromFilePath, strToFilePath, true);
    else
        return false;
}

bool STATFileSystemHelper::Write(const wxString& strFilePath, const wxString& strTextContent)
{
    bool bResult = true;
    wxTextFile file(strFilePath);

    if(wxFileExists(strFilePath))
    {
        bResult = wxRemoveFile(strFilePath);
    }

    if(bResult)
    {
        bResult = file.Create();

        if(bResult)
        {
            bResult = file.Open();

            std::list<wxString> textLines = STATStringHelper::Split(strTextContent, TAT_NEWLINE_TOKEN);

            for(std::list<wxString>::const_iterator iLine = textLines.begin(); iLine != textLines.end(); ++iLine)
            {
                file.AddLine(*iLine);
            }

            if(bResult)
            {
                file.Write();
            }
        }
    }

    return bResult;
}

std::list<wxString> STATFileSystemHelper::ListFolderContent(const wxString& strFolderToExplore, const wxString& strExtensionFilter)
{
    std::list<wxString> result;

    const wxString EXTENSION_FILTER = strExtensionFilter == wxT("") ?
                                            wxT("") :
                                            wxT("*.") + strExtensionFilter;

    wxDir directory(strFolderToExplore);

    wxString strCurrentFileName;
    bool bFileExists = directory.GetFirst(&strCurrentFileName, EXTENSION_FILTER, wxDIR_FILES);

    while(bFileExists)
    {
        result.push_back(strCurrentFileName);
        bFileExists = directory.GetNext(&strCurrentFileName);
    }

    return result;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const wxString& STATFileSystemHelper::GetExecutableFileExtension()
{
    return STATFileSystemHelper::sm_strExecutableFileExtension;
}


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
