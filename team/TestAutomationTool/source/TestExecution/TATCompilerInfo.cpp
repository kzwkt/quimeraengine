// [TERMS&CONDITIONS]

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
