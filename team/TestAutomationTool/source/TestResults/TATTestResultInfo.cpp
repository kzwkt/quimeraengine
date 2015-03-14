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

#include "TestResults/TATTestResultInfo.h"

#include "TestResults/TATTestResultNode.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
    
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |        CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestResultInfo::TATTestResultInfo() : m_pResultTree(NULL),
                                         m_strFlagCombinationName(wxT("")),
                                         m_strFlagCombinationValues(wxT("")),
                                         m_strCompilationConfiguration(wxT("")),
                                         m_strCompilerName(wxT(""))
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

wxString TATTestResultInfo::GetFlagCombinationName() const
{
    return m_strFlagCombinationName;
}

void TATTestResultInfo::SetFlagCombinationName(const wxString &strName)
{
    m_strFlagCombinationName = strName;
}

wxString TATTestResultInfo::GetFlagCombinationValues() const
{
    return m_strFlagCombinationValues;
}

void TATTestResultInfo::SetFlagCombinationValues(const wxString &strValues)
{
    m_strFlagCombinationValues = strValues;
}

wxString TATTestResultInfo::GetCompilationConfiguration() const
{
    return m_strCompilationConfiguration;
}

void TATTestResultInfo::SetCompilationConfiguration(const wxString &strConfiguration)
{
    m_strCompilationConfiguration = strConfiguration;
}

wxString TATTestResultInfo::GetCompilerName() const
{
    return m_strCompilerName;
}

void TATTestResultInfo::SetCompilerName(const wxString &strName)
{
    m_strCompilerName = strName;
}

TATTestResultNode* TATTestResultInfo::GetResultTree() const
{
    return m_pResultTree;
}

void TATTestResultInfo::SetResultTree(TATTestResultNode* pResultTree)
{
    m_pResultTree = pResultTree;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
