// [TERMS&CONDITIONS]

#ifndef __TATCONFIGLOADERFROMINIFILEWHITEBOX__
#define __TATCONFIGLOADERFROMINIFILEWHITEBOX__

#include "TestConfiguration/TATConfigLoaderFromIniFile.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATConfigLoaderFromIniFile for testing purposes.
/// </summary>
class TATConfigLoaderFromIniFileWhiteBox : public TATConfigLoaderFromIniFile
{
    // CONSTRUCTORS
    // ---------------
public:

    // Necessary for testing purposes
    TATConfigLoaderFromIniFileWhiteBox(TATRuleNode* pRuleTree) : TATConfigLoaderFromIniFile(pRuleTree)
    {
    }


	// METHODS
	// ---------------
public:

    // Exposed methods
    void Destroy()
    {
        TATConfigLoaderFromIniFile::Destroy();
    }

    void ApplyRule(TATKeyValueNode* pValueNode, TATRuleNode* pRuleNode, TATKeyValueNode* pRootNode)
    {
        TATConfigLoaderFromIniFile::ApplyRule(pValueNode, pRuleNode, pRootNode);
    }

    void ApplyFinalRules(TATRuleNode* pRuleTree, TATKeyValueNode* pValueTree)
    {
        TATConfigLoaderFromIniFile::ApplyFinalRules(pRuleTree, pValueTree);
    }

    ETATConfigNodeType GetTypeOfNode(const wxString& strLine) const
    {
        return TATConfigLoaderFromIniFile::GetTypeOfNode(strLine);
    }

    wxString GetNameOfNode(const wxString& strLine) const
    {
        return TATConfigLoaderFromIniFile::GetNameOfNode(strLine);
    }

    wxString GetValueOfNode(const wxString& strLine) const
    {
        return TATConfigLoaderFromIniFile::GetValueOfNode(strLine);
    }

    void SetValueTreeForTesting(TATKeyValueNode* pValueTree)
    {
        m_pValueTree = pValueTree;
    }
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATCONFIGLOADERFROMINIFILEWHITEBOX__
