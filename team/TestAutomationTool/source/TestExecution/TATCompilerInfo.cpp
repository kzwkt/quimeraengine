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

#include "TestExecution/TATCompilerInfo.h"


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

TATCompilerInfo::TATCompilerInfo()
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

TATCompilerInfo::~TATCompilerInfo()
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

bool TATCompilerInfo::operator==(const TATCompilerInfo& compilerInfo) const
{
    return  (m_strBuildCommand == compilerInfo.m_strBuildCommand) &&
            (m_strBuildParams == compilerInfo.m_strBuildParams) &&
            (m_strCleanCommand == compilerInfo.m_strCleanCommand) &&
            (m_strCleanParams == compilerInfo.m_strCleanParams) &&
            (m_strCompilerPath == compilerInfo.m_strCompilerPath) &&
            (m_strFileSpecifier == compilerInfo.m_strFileSpecifier) &&
            (m_strName == compilerInfo.m_strName) &&
            (m_sutProjectsToCompile == compilerInfo.m_sutProjectsToCompile) &&
            (m_testModulesExecutionInfos == compilerInfo.m_testModulesExecutionInfos);
}

bool TATCompilerInfo::operator!=(const TATCompilerInfo& compilerInfo) const
{
    return !((m_strBuildCommand == compilerInfo.m_strBuildCommand) &&
             (m_strBuildParams == compilerInfo.m_strBuildParams) &&
             (m_strCleanCommand == compilerInfo.m_strCleanCommand) &&
             (m_strCleanParams == compilerInfo.m_strCleanParams) &&
             (m_strCompilerPath == compilerInfo.m_strCompilerPath) &&
             (m_strFileSpecifier == compilerInfo.m_strFileSpecifier) &&
             (m_strName == compilerInfo.m_strName) &&
             (m_sutProjectsToCompile == compilerInfo.m_sutProjectsToCompile) &&
             (m_testModulesExecutionInfos == compilerInfo.m_testModulesExecutionInfos));
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

wxString TATCompilerInfo::GetName() const
{
    return m_strName;
}

void TATCompilerInfo::SetName(const wxString& strCompilerName)
{
    m_strName = strCompilerName;
}

wxString TATCompilerInfo::GetBuildCommand() const
{
    return m_strBuildCommand;
}

void TATCompilerInfo::SetBuildCommand(const wxString& strCommandName)
{
    m_strBuildCommand = strCommandName;
}

wxString TATCompilerInfo::GetCleanCommand() const
{
    return m_strCleanCommand;
}

void TATCompilerInfo::SetCleanCommand(const wxString& strCommandName)
{
    m_strCleanCommand = strCommandName;
}

wxString TATCompilerInfo::GetBuildParams() const
{
    return m_strBuildParams;
}

void TATCompilerInfo::SetBuildParams(const wxString& strParams)
{
    m_strBuildParams = strParams;
}

wxString TATCompilerInfo::GetCleanParams() const
{
    return m_strCleanParams;
}

void TATCompilerInfo::SetCleanParams(const wxString& strParams)
{
    m_strCleanParams = strParams;
}

wxString TATCompilerInfo::GetFileSpecifier() const
{
    return m_strFileSpecifier;
}

void TATCompilerInfo::SetFileSpecifier(const wxString& strToken)
{
    m_strFileSpecifier = strToken;
}

wxString TATCompilerInfo::GetCompilerPath() const
{
    return m_strCompilerPath;
}

void TATCompilerInfo::SetCompilerPath(const wxString& strCompilerPath)
{
    m_strCompilerPath = strCompilerPath;
}

std::list<wxString> TATCompilerInfo::GetSUTProjects() const
{
    return m_sutProjectsToCompile;
}

void TATCompilerInfo::SetSUTProjects(const std::list<wxString>& sutProjectsToCompile)
{
    m_sutProjectsToCompile = sutProjectsToCompile;
}

std::list<TATTestModulesExecutionInfo> TATCompilerInfo::GetTestModulesExecutionInfo() const
{
    return m_testModulesExecutionInfos;
}

void TATCompilerInfo::SetTestModulesExecutionInfo(const std::list<TATTestModulesExecutionInfo>& testModulesExecutionInfos)
{
    m_testModulesExecutionInfos = testModulesExecutionInfos;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
