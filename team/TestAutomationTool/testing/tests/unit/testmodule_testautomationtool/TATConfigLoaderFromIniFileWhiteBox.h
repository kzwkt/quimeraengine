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
