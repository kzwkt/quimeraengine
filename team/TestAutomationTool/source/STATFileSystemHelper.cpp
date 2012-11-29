// [TERMS&CONDITIONS]

#include "STATFileSystemHelper.h"

#include <wx/filefn.h>
#include <wx/textfile.h>
#include "ExternalDefinitions.h"

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
        return wxRenameFile(strFilePath, wxPathOnly(strFilePath) + strNewFileName, false);
    else
        return false;
}

bool STATFileSystemHelper::Execute(const wxString& strFilePath, const wxString& strParams)
{
    if(wxFileExists(strFilePath))
    {
        try
        {
            system((strFilePath + wxT(" ") + strParams).c_str());
        }
        catch(...)
        {
            return false;
        }

        return true;
    }
    else
        return false;
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
