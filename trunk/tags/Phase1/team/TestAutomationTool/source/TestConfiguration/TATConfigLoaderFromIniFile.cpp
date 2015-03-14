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

#include "TestConfiguration/TATConfigLoaderFromIniFile.h"

#include "TestConfiguration/TATRuleNode.h"
#include "TestConfiguration/TATKeyValueNode.h"
#include "STATFileSystemHelper.h"
#include "STATStringHelper.h"
#include "ExternalDefinitions.h"
#include "TestConfiguration/TATValidationException.h"

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

const wxString TATConfigLoaderFromIniFile::KEYVALUE_SEPARATOR_TOKEN = wxT("=");
const wxString TATConfigLoaderFromIniFile::HEADER_OPENING_TOKEN = wxT("[");
const wxString TATConfigLoaderFromIniFile::HEADER_CLOSING_TOKEN = wxT("]");

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATConfigLoaderFromIniFile::TATConfigLoaderFromIniFile(TATRuleNode* pRuleTree) : m_strSource(wxT("")),
                                                                                 m_pRuleTree(pRuleTree),
                                                                                 m_pValueTree(NULL)
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

TATConfigLoaderFromIniFile::~TATConfigLoaderFromIniFile()
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

void TATConfigLoaderFromIniFile::Destroy()
{
    if(m_pRuleTree != NULL)
    {
        delete m_pRuleTree;
        m_pRuleTree = NULL;
    }

    if(m_pValueTree != NULL)
    {
        delete m_pValueTree;
        m_pValueTree = NULL;
    }
}

void TATConfigLoaderFromIniFile::Load()
{
    // First, resets the contents
    this->Reset();

    wxString strConfigurationFile;
    
    // Reads the configuration file
    if(STATFileSystemHelper::Read(this->GetSource(), strConfigurationFile))
    {
        // Splits the file into lines so it can be read easier
        std::list<wxString> lines = STATStringHelper::Split(strConfigurationFile, TAT_NEWLINE_TOKEN);

        if(lines.size() > 0)
        {
            // Creates the value tree
            m_pValueTree = new TATKeyValueNode(wxT("ROOT"), ETATConfigNodeType::E_ROOT, wxT(""));

            TATKeyValueNode* pCurrentHeaderValueNode = NULL; // Stores last visited header in the value tree
            TATRuleNode* pCurrentHeaderRuleNode = NULL; // Stores last visited header in the rule tree

            // Evaluates line by line, creating key-value nodes
            for(std::list<wxString>::iterator iLine = lines.begin(); iLine != lines.end(); ++iLine)
            {
                // Skips empty lines
                if(iLine->IsEmpty() || iLine->GetChar(0) == wxT(';'))
                    continue;

                // Extract the information from the text line
                wxString strNodeName = this->GetNameOfNode(*iLine);
                wxString strNodeValue = this->GetValueOfNode(*iLine);
                ETATConfigNodeType eNodeType = this->GetTypeOfNode(*iLine);

                // Creates the node
                TATKeyValueNode* pNode = new TATKeyValueNode(strNodeName, eNodeType, strNodeValue);

                // Appends the node wherever it corresponds
                if(eNodeType == ETATConfigNodeType::E_HEADER)
                {
                    m_pValueTree->AddChild(pNode);
                    pCurrentHeaderValueNode = pNode;

                    // Applies the rules
                    TATRuleNode::TNodeCollection headerRules = m_pRuleTree->GetChild(strNodeName);

                    if(headerRules.size() == 1) // Only one rule per header
                    {
                        TATRuleNode* pRuleNode = dynamic_cast<TATRuleNode*>(headerRules.begin()->second);
                        this->ApplyRule(pNode, pRuleNode, m_pValueTree);

                        pCurrentHeaderRuleNode = pRuleNode;
                    }
                    else
                    {
                        throw TATValidationException("MULTIPLE_RULES", strNodeName);
                    }
                }
                else // Value node assumed
                {
                    pCurrentHeaderValueNode->AddChild(pNode);

                    // Applies the rules
                    TATRuleNode::TNodeCollection valueRules = pCurrentHeaderRuleNode->GetChild(strNodeName);

                    if(valueRules.size() == 1) // Only one rule per header
                    {
                        TATRuleNode* pRuleNode = dynamic_cast<TATRuleNode*>(valueRules.begin()->second);
                        this->ApplyRule(pNode, pRuleNode, pCurrentHeaderValueNode);
                    }
                    else
                    {
                        throw TATValidationException("MULTIPLE_RULES", strNodeName);
                    }
                }
            }

            // Apply final rules to the entire value tree
            this->ApplyFinalRules(m_pRuleTree, m_pValueTree);
        }
    }
    else
    {
        throw std::exception(); // [TODO] Thund: Create a concrete exception for this
    }
}

void TATConfigLoaderFromIniFile::Reset()
{
    if(m_pValueTree != NULL)
    {
        delete m_pValueTree;
        m_pValueTree = NULL;
    }
}

void TATConfigLoaderFromIniFile::ApplyRule(TATKeyValueNode* pValueNode, TATRuleNode* pRuleNode, TATKeyValueNode* pRootNode)
{
    // Checks for maximum occurrences
    if(pRuleNode->GetMaxCount() > 0)
    {
        TATConfigNode::TNodeCollection configNodes = pRootNode->GetChild(pRuleNode->GetName());

        if(configNodes.size() > pRuleNode->GetMaxCount())
        {
            throw TATValidationException("MAXCOUNT", pRuleNode->GetName());
        }
    }

    // Checks whether the value is empty
    if(!pRuleNode->GetCanBeEmpty() && pValueNode->GetValue().empty())
    {
        throw TATValidationException("CANTBEEMPTY", pRuleNode->GetName());
    }
}

void TATConfigLoaderFromIniFile::ApplyFinalRules(TATRuleNode* pRuleTree, TATKeyValueNode* pValueTree)
{
    // Walks through the rule tree
    for(TATRuleNode::TNodeCollection::const_iterator iRule = pRuleTree->GetChildren().begin(); iRule != pRuleTree->GetChildren().end(); ++iRule)
    {
        // Checks if every obligatory node is in the value tree
        TATRuleNode* pRuleNode = dynamic_cast<TATRuleNode*>(iRule->second);
        TATKeyValueNode::TNodeCollection valueNodes = pValueTree->GetChild(pRuleNode->GetName());

        if(pRuleNode->GetIsObligatory() && valueNodes.empty())
        {
            throw TATValidationException("ISOBLIGATORY", pRuleNode->GetName());
        }

        for(TATRuleNode::TNodeCollection::const_iterator iHeader = valueNodes.begin(); iHeader != valueNodes.end(); ++iHeader)
        {
            TATKeyValueNode* pHeaderNode = dynamic_cast<TATKeyValueNode*>(iHeader->second);

            // Checks the same for every rule inside the header
            for(TATRuleNode::TNodeCollection::const_iterator iRuleInside = pRuleNode->GetChildren().begin(); iRuleInside != pRuleNode->GetChildren().end(); ++iRuleInside)
            {
                TATRuleNode* pRuleNodeInsideHeader = dynamic_cast<TATRuleNode*>(iRuleInside->second);
                if(pRuleNodeInsideHeader->GetIsObligatory())
                {
                    TATKeyValueNode::TNodeCollection valueNodes = pHeaderNode->GetChild(pRuleNodeInsideHeader->GetName());

                    if(valueNodes.empty())
                    {
                        throw TATValidationException("ISOBLIGATORY", pRuleNodeInsideHeader->GetName());
                    }
                }
            }
        }
    }
}

ETATConfigNodeType TATConfigLoaderFromIniFile::GetTypeOfNode(const wxString& strLine) const
{
    if(strLine.substr(0, HEADER_OPENING_TOKEN.size()) == HEADER_OPENING_TOKEN)
    {
        return ETATConfigNodeType::E_HEADER;
    }
    else
    {
        return ETATConfigNodeType::E_VALUE;
    }
}

wxString TATConfigLoaderFromIniFile::GetNameOfNode(const wxString& strLine) const
{
    wxString strName;
    wxString strLineWithoutBrackets;

    // Extract the line from the brackets (headers only)
    if(GetTypeOfNode(strLine) == ETATConfigNodeType::E_HEADER)
    {
        size_t nClosingPos = strLine.find_first_of(TATConfigLoaderFromIniFile::HEADER_CLOSING_TOKEN, TATConfigLoaderFromIniFile::HEADER_OPENING_TOKEN.size());

        if(nClosingPos == wxString::npos)
            throw new std::exception(); // [TODO] Thund: Create a concrete exception explaining that a closing bracket is missing

        strLineWithoutBrackets = strLine.substr(TATConfigLoaderFromIniFile::HEADER_OPENING_TOKEN.size(), nClosingPos - TATConfigLoaderFromIniFile::HEADER_OPENING_TOKEN.size());
    }
    else // Value node assumed
    {
        strLineWithoutBrackets = strLine;
    }

    size_t nSeparatorPos = strLineWithoutBrackets.find_first_of(KEYVALUE_SEPARATOR_TOKEN);

    if(nSeparatorPos == wxString::npos)
        throw new std::exception(); // [TODO] Thund: Create a concrete exception explaining that the separator is missing

    strName = strLineWithoutBrackets.substr(0, nSeparatorPos);

    return strName;
}

wxString TATConfigLoaderFromIniFile::GetValueOfNode(const wxString& strLine) const
{
    wxString strValue;
    wxString strLineWithoutBrackets;

    // Extract the line from the brackets (headers only)
    if(GetTypeOfNode(strLine) == ETATConfigNodeType::E_HEADER)
    {
        size_t nClosingPos = strLine.find_first_of(TATConfigLoaderFromIniFile::HEADER_CLOSING_TOKEN, TATConfigLoaderFromIniFile::HEADER_OPENING_TOKEN.size());

        if(nClosingPos == wxString::npos)
            throw new std::exception(); // [TODO] Thund: Create a concrete exception explaining that a closing bracket is missing

        strLineWithoutBrackets = strLine.substr(TATConfigLoaderFromIniFile::HEADER_OPENING_TOKEN.size(), nClosingPos - TATConfigLoaderFromIniFile::HEADER_OPENING_TOKEN.size());
    }
    else // Value node assumed
    {
        strLineWithoutBrackets = strLine;
    }

    size_t nSeparatorPos = strLineWithoutBrackets.find_first_of(KEYVALUE_SEPARATOR_TOKEN);

    if(nSeparatorPos == wxString::npos)
        throw new std::exception(); // [TODO] Thund: Create a concrete exception explaining that the separator is missing

    // If it's a value node, the quotes have to be removed
    if(GetTypeOfNode(strLine) == ETATConfigNodeType::E_VALUE)
    {
        const size_t QUOTES_SIZE = 1; // " = 1 character
        const size_t VALUE_WITHOUT_QUOTES_POS = nSeparatorPos + KEYVALUE_SEPARATOR_TOKEN.size() + QUOTES_SIZE;

        if(VALUE_WITHOUT_QUOTES_POS >= strLineWithoutBrackets.size())
        {
            // It's likely that the value is empty and no quotes were written there
            strValue = wxT("");
        }
        else
        {
            strValue = strLineWithoutBrackets.substr(VALUE_WITHOUT_QUOTES_POS, strLineWithoutBrackets.size() - VALUE_WITHOUT_QUOTES_POS - QUOTES_SIZE);
        }
    }
    else // Header node assumed
    {
        strValue = strLineWithoutBrackets.substr(nSeparatorPos + KEYVALUE_SEPARATOR_TOKEN.size());
    }

    return strValue;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATRuleNode* TATConfigLoaderFromIniFile::GetRuleTree() const
{
    return m_pRuleTree;
}

TATKeyValueNode* TATConfigLoaderFromIniFile::GetValueTree() const
{
    return m_pValueTree;
}

wxString TATConfigLoaderFromIniFile::GetSource() const
{
    return m_strSource;
}

void TATConfigLoaderFromIniFile::SetSource(const wxString& strSource)
{
    m_strSource = strSource;
}


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
