// [TERMS&CONDITIONS]

#include "TestExecution/TATTestResultConsultant.h"

#include "TestExecution/TATTestResultNode.h"
#include "TestExecution/ETATTestResultNodeType.h"

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

int TATTestResultConsultant::GetTestModuleCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    switch(pNode->GetNodeType())
    {
    case ETATTestResultNodeType::E_Root:
        {
            TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

            for(; iChild != pNode->GetChildren().end(); ++iChild)
            {
                nCount += this->GetTestModuleCount(dynamic_cast<TATTestResultNode*>(iChild->second));
            }
        }
        break;
    case ETATTestResultNodeType::E_Module:
        nCount = 1;
        break;
    default:
        nCount = -1;
        break;
    }

    return nCount;
}

int TATTestResultConsultant::GetTestSuiteCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    switch(pNode->GetNodeType())
    {
    case ETATTestResultNodeType::E_Module:
        nCount = static_cast<int>(pNode->GetChildren().size());
        break;
    case ETATTestResultNodeType::E_Suite:
        nCount = 1;
        break;
    case ETATTestResultNodeType::E_Case:
    case ETATTestResultNodeType::E_Result:
        nCount = -1;
        break;
    default:
        TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

        for(; iChild != pNode->GetChildren().end(); ++iChild)
        {
            nCount += this->GetTestSuiteCount(dynamic_cast<TATTestResultNode*>(iChild->second));
        }
        break;
    }

    return nCount;
}

int TATTestResultConsultant::GetTestCaseCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    switch(pNode->GetNodeType())
    {
    case ETATTestResultNodeType::E_Suite:
        nCount = static_cast<int>(pNode->GetChildren().size());
        break;
    case ETATTestResultNodeType::E_Case:
        nCount = 1;
        break;
    case ETATTestResultNodeType::E_Result:
        nCount = -1;
        break;
    default:
        TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

        for(; iChild != pNode->GetChildren().end(); ++iChild)
        {
            nCount += this->GetTestCaseCount(dynamic_cast<TATTestResultNode*>(iChild->second));
        }
        break;
    }

    return nCount;
}

int TATTestResultConsultant::GetTestResultCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    switch(pNode->GetNodeType())
    {
    case ETATTestResultNodeType::E_Case:
        nCount = static_cast<int>(pNode->GetChildren().size());
        break;
    case ETATTestResultNodeType::E_Result:
        nCount = 1;
        break;
    default:
        TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

        for(; iChild != pNode->GetChildren().end(); ++iChild)
        {
            nCount += this->GetTestResultCount(dynamic_cast<TATTestResultNode*>(iChild->second));
        }
        break;
    }

    return nCount;
}

int TATTestResultConsultant::GetFailedTestModuleCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    switch(pNode->GetNodeType())
    {
    case ETATTestResultNodeType::E_Root:
        {
            TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

            for(; iChild != pNode->GetChildren().end(); ++iChild)
            {
                nCount += dynamic_cast<TATTestResultNode*>(iChild->second)->HasErrors() ? 1 : 0;
            }
        }
        break;
    case ETATTestResultNodeType::E_Module:
        nCount = pNode->HasErrors() ? 1 : 0;
        break;
    default:
        nCount = -1;
        break;
    }

    return nCount;
}

int TATTestResultConsultant::GetFailedTestSuiteCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    switch(pNode->GetNodeType())
    {
    case ETATTestResultNodeType::E_Suite:
        nCount = pNode->HasErrors() ? 1 : 0;
        break;
    case ETATTestResultNodeType::E_Case:
    case ETATTestResultNodeType::E_Result:
        nCount = -1;
        break;
    default:
        TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

        for(; iChild != pNode->GetChildren().end(); ++iChild)
        {
            nCount += this->GetFailedTestSuiteCount(dynamic_cast<TATTestResultNode*>(iChild->second));
        }
        break;
    }

    return nCount;
}

int TATTestResultConsultant::GetFailedTestCaseCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    switch(pNode->GetNodeType())
    {
    case ETATTestResultNodeType::E_Case:
        nCount = pNode->HasErrors() ? 1 : 0;
        break;
    case ETATTestResultNodeType::E_Result:
        nCount = -1;
        break;
    default:
        TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

        for(; iChild != pNode->GetChildren().end(); ++iChild)
        {
            nCount += this->GetFailedTestCaseCount(dynamic_cast<TATTestResultNode*>(iChild->second));
        }
        break;
    }

    return nCount;
}

int TATTestResultConsultant::GetFailedTestResultCount(TATTestResultNode* pNode) const
{
    int nCount = 0;

    if(pNode->GetNodeType() == ETATTestResultNodeType::E_Result)
    {
        nCount = pNode->HasErrors() ? 1 : 0;
    }
    else
    {
        TATTestResultNode::TNodeCollection::const_iterator iChild = pNode->GetChildren().begin();

        for(; iChild != pNode->GetChildren().end(); ++iChild)
        {
            nCount += this->GetFailedTestResultCount(dynamic_cast<TATTestResultNode*>(iChild->second));
        }
    }

    return nCount;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################



} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
