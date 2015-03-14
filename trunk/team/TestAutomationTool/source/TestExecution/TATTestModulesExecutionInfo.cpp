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

#include "TestExecution/TATTestModulesExecutionInfo.h"


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



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestModulesExecutionInfo::TATTestModulesExecutionInfo()
{
}
	
	
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestModulesExecutionInfo::~TATTestModulesExecutionInfo()
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

bool TATTestModulesExecutionInfo::operator==(const TATTestModulesExecutionInfo& executionInfo) const
{
    return (m_strResultsPath == executionInfo.m_strResultsPath) &&
           (m_strTestModulesPath == executionInfo.m_strTestModulesPath) &&
           (m_strTestProjectPath == executionInfo.m_strTestProjectPath);
}

bool TATTestModulesExecutionInfo::operator!=(const TATTestModulesExecutionInfo& executionInfo) const
{
    return !((m_strResultsPath == executionInfo.m_strResultsPath) &&
             (m_strTestModulesPath == executionInfo.m_strTestModulesPath) &&
             (m_strTestProjectPath == executionInfo.m_strTestProjectPath));
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

wxString TATTestModulesExecutionInfo::GetTestModulesPath() const
{
    return m_strTestModulesPath;
}

void TATTestModulesExecutionInfo::SetTestModulesPath(const wxString& strTestModulesPath)
{
    m_strTestModulesPath = strTestModulesPath;
}

wxString TATTestModulesExecutionInfo::GetResultsPath() const
{
    return m_strResultsPath;
}

void TATTestModulesExecutionInfo::SetResultsPath(const wxString& strResultsPath)
{
    m_strResultsPath = strResultsPath;
}

wxString TATTestModulesExecutionInfo::GetTestProjectPath() const
{
    return m_strTestProjectPath;
}

void TATTestModulesExecutionInfo::SetTestProjectPath(const wxString& strTestProjectPath)
{
    m_strTestProjectPath = strTestProjectPath;
}

wxString TATTestModulesExecutionInfo::GetBuildParams() const
{
    return m_strBuildParams;
}

void TATTestModulesExecutionInfo::SetBuildParams(const wxString& strParams)
{
    m_strBuildParams = strParams;
}

wxString TATTestModulesExecutionInfo::GetCleanParams() const
{
    return m_strCleanParams;
}

void TATTestModulesExecutionInfo::SetCleanParams(const wxString& strParams)
{
    m_strCleanParams = strParams;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
