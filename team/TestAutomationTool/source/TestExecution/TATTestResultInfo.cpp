// [TERMS&CONDITIONS]

#include "TestExecution/TATTestResultInfo.h"

#include "TestExecution/TATTestResultNode.h"

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
