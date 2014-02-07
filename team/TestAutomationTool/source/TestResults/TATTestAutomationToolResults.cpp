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

#include "TestResults/TATTestAutomationToolResults.h"

#include <algorithm>
#include <boost/property_tree/detail/xml_parser_error.hpp>

#include "ExternalDefinitions.h"
#include "STATFileSystemHelper.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestAutomationToolResults::TATTestAutomationToolResults() : m_pTestResultLoader(NULL)
{
    // Subscribes to thread events
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestAutomationToolResults::~TATTestAutomationToolResults()
{
    this->Destroy();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestAutomationToolResults::Destroy()
{
    if(m_pTestResultLoader != NULL)
    {
        delete m_pTestResultLoader;
        m_pTestResultLoader = NULL;
    }
}

std::list<wxString> TATTestAutomationToolResults::ReadTestResultFiles(const wxString& strFolderPath) const
{
    return STATFileSystemHelper::ListFolderContent(strFolderPath, wxT("xml"));
}

std::list<TATTestResultInfo> TATTestAutomationToolResults::ParseAllTestResultFiles(const wxString& strTestResultsPath)
{
    // Obtains a list with all the existent result files
    std::list<wxString> testResultFiles = this->ReadTestResultFiles(strTestResultsPath);
    // The list of results
    std::list<TATTestResultInfo> resultList;

    // Removes previous test results from the loader
    this->GetTestResultLoader()->Clear();

    if(testResultFiles.empty())
    {
        wxMessageOutputMessageBox::Get()->Printf(wxString(wxT("No result files were found at '")).
                                                 Append(strTestResultsPath).
                                                 Append(wxT("'.")));
    }

    // Checks if there are new files to parse
    std::list<wxString> parsedResultFiles;

    for(std::list<wxString>::const_iterator iResultFilePath = testResultFiles.begin(); iResultFilePath != testResultFiles.end(); ++iResultFilePath)
    {
        if(std::find(parsedResultFiles.begin(), parsedResultFiles.end(), strTestResultsPath + *iResultFilePath) == parsedResultFiles.end())
        {
            TATTestResultInfo result = this->ParseTestResultFile(strTestResultsPath + *iResultFilePath, wxString(""), wxString(""), wxString(""), wxString(""));
            resultList.push_back(result);

            // Saves the path of the file in the list of parsed files
            parsedResultFiles.push_back(strTestResultsPath + *iResultFilePath);
        }
    }

    return resultList;
}

TATTestResultInfo TATTestAutomationToolResults::ParseTestResultFile(const wxString& strTestResultFilePath,
                                                                    const wxString& strCompilationConfig,
                                                                    const wxString& strCompilerName,
                                                                    const wxString& strFlagCombinationName,
                                                                    const wxString& strFlagCombinationValues)
{
    // [TODO] Thund: This method has to be split and refactored, there is no time to do it at the moment
    // [TODO] Thund: It would be good to localize all the literals of this method

    const int SUCCESS = 0;

    bool bResultFileParsingFailed = false;

    try
    {
        this->LoadAndParseTestResultFile(strTestResultFilePath);
    }
    catch(const boost::property_tree::xml_parser::xml_parser_error &ex)
    {
        bResultFileParsingFailed = true;

        wxMessageOutputMessageBox::Get()->Printf(wxString(wxT("Failed to parse the result file:")) + ex.what());
    }

    TATTestResultInfo resultInfo;

    if(!bResultFileParsingFailed)
    {
        // Notifies that there is new content in the test result tree
        resultInfo.SetCompilationConfiguration(strCompilationConfig);
        resultInfo.SetCompilerName(strCompilerName);
        resultInfo.SetFlagCombinationName(strFlagCombinationName);
        resultInfo.SetFlagCombinationValues(strFlagCombinationValues);

        if(this->GetTestResultLoader()->GetTestResultTree() && this->GetTestResultLoader()->GetTestResultTree()->HasChildren())
        {
            // Gets the last added result tree and stores it into the event argument
            // It's assumed that the result tree contains, at least, the last added tree
            TATTestResultNode* pNewTestResultTree = dynamic_cast<TATTestResultNode*>(this->GetTestResultLoader()->GetTestResultTree()->GetChildren().rbegin()->second);
            resultInfo.SetResultTree(pNewTestResultTree);
        }
        else
        {
            wxMessageOutputMessageBox::Get()->Printf(wxT("Failed to create the result tree."));

            resultInfo.SetResultTree(NULL);
        }
    }

    return resultInfo;
}

void TATTestAutomationToolResults::LoadAndParseTestResultFile(const wxString &strTestResultFilePath)
{
    this->GetTestResultLoader()->Load(strTestResultFilePath);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		EVENT HANDLERS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

wxString TATTestAutomationToolResults::GetTestResultsPath() const
{
    return m_strTestResultsPath;
}

void TATTestAutomationToolResults::SetTestResultsPath(const wxString& strTestResultsPath)
{
    m_strTestResultsPath = strTestResultsPath;
}

ITATTestResultLoader* TATTestAutomationToolResults::GetTestResultLoader() const
{
    return m_pTestResultLoader;
}

void TATTestAutomationToolResults::SetTestResultLoader(ITATTestResultLoader* pTestResultLoader)
{
    m_pTestResultLoader = pTestResultLoader;
}


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
