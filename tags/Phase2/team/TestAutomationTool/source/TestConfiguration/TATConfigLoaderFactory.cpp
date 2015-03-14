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

#include "TestConfiguration/TATConfigLoaderFactory.h"

#include "TestConfiguration/ITATConfigLoader.h"
#include "TestConfiguration/TATRuleNode.h"

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

ITATConfigLoader* TATConfigLoaderFactory::CreateConfigLoader(const ETATConfigurationSource& source) const
{
    switch(source)
    {
    case ETATConfigurationSource::E_INI_FILE:
        return CreateConfigLoaderFromIniFile();
    default:
        return NULL;
    }
}

ITATConfigLoader* TATConfigLoaderFactory::CreateConfigLoaderFromIniFile() const
{
    return new TATConfigLoaderFromIniFile(this->CreateRuleTree());
}

TATRuleNode* TATConfigLoaderFactory::CreateRuleTree() const
{
    // Root node
    // Its name is ROOT. It can appear only once, is obligatory and can't be empty.
    TATRuleNode* pRuleTree = new TATRuleNode(wxT("ROOT"), 1, false, true, ETATConfigNodeType::E_ROOT);

    // -Compiler node
    // This section describes the configuration parameters for a given compiler. There can be as many compiler 
    // settings sections as compilers are supported by the SUT. The header of this section is preceded by a “C”, 
    // followed by the name of the compiler.
    TATRuleNode* pCompilerNode = new TATRuleNode(wxT("C"), 0, false, true, ETATConfigNodeType::E_HEADER);

    // --CompilerPath node
    // Absolute path to the compiler (executable file). It must appear once and only once. It can’t be empty.
    pCompilerNode->AddChild( new TATRuleNode(wxT("CompilerPath"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --CompilerBuildCommand node
    // The name of the command that the compiler uses for cleaning intermediate and binary compilation files. 
    // It must appear once and only once. It can’t be empty.
    pCompilerNode->AddChild( new TATRuleNode(wxT("CompilerCleanCommand"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --CompilerBuildCommand
    // The name of the command that the compiler uses for compiling. It must appear once and only once. It can’t be empty.
    pCompilerNode->AddChild( new TATRuleNode(wxT("CompilerBuildCommand"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --CompilerBuildParams
    // Compilation options, known by the compiler that will be added every time the SUT is compiled. It must appear once and only once, 
    // although it can be empty.
    pCompilerNode->AddChild( new TATRuleNode(wxT("CompilerBuildParams"), 1, true, true, ETATConfigNodeType::E_VALUE) );
    
    // --CompilerCleanParams
    // Compilation options, known by the compiler that will be added every time the SUT is cleaned. It must appear once and only once, 
    // although it can be empty.
    pCompilerNode->AddChild( new TATRuleNode(wxT("CompilerCleanParams"), 1, true, true, ETATConfigNodeType::E_VALUE) );
    
    // --CompilerFileSpecifier
    // Token known by the compiler that will be added before the path of the project file. It must appear once and only once, 
    // although it can be empty.
    pCompilerNode->AddChild( new TATRuleNode(wxT("CompilerFileSpecifier"), 1, true, true, ETATConfigNodeType::E_VALUE) );

    // -Project settings node
    // This section describes the configuration parameters for a given project (a solution or a workspace). 
    // There can be as many project settings sections as compilers are supported by the SUT. The header of this section is preceded 
    // by a “P”, followed by the name of the project.
    TATRuleNode* pProjectNode = new TATRuleNode(wxT("P"), 0, false, true, ETATConfigNodeType::E_HEADER);

    // --CompilationInfoPath
    // Relative path to the solution file (for Visual Studio, for example) or to a Make file. It must appear once and only once. 
    // It can’t be empty.
    pProjectNode->AddChild( new TATRuleNode(wxT("CompilationInfoPath"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --Compiler
    // The name of the compiler used to compile the project. It has to coincide with the header value of one of the declared 
    // compiler settings. It can appear once and only once.
    pProjectNode->AddChild( new TATRuleNode(wxT("Compiler"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // -Flag settings
    // This section is formed a set of possible values for a given flag, defined in the Configuration.h file of the SUT. 
    // There can be as many flag settings sections as flags are defined in the mentioned file. The header of this section 
    // is preceded by an “F”, followed by the name of the flag (must be exact).
    TATRuleNode* pFlagNode = new TATRuleNode(wxT("F"), 0, false, false, ETATConfigNodeType::E_HEADER);

    // --Option
    // A possible value for the flag. It must appear 1 to N times, and can’t be empty.
    pFlagNode->AddChild( new TATRuleNode( wxT("Option"), 0, false, true, ETATConfigNodeType::E_VALUE) );

    // -SUT settings
    // This section provides with some information about the SUT. It must appear once and only once. The header is fixed, 
    // compound of an “S” and the word “SUT”.
    TATRuleNode* pSUTNode = new TATRuleNode(wxT("S"), 1, false, true, ETATConfigNodeType::E_HEADER);

    // --ConfigurationFilePath
    // The relative path of the configuration file of the SUT, in this case, the “Configuration.h” file. 
    // It must appear once and only once, and it can’t be empty.
    pSUTNode->AddChild( new TATRuleNode( wxT("ConfigurationFilePath"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --CompilerConfiguration
    // The name of a compilation configuration that is considered in the file specified in CompilationInfoPath. 
    // It can appear 1 to N times and can’t be empty.
    pSUTNode->AddChild( new TATRuleNode( wxT("CompilerConfiguration"), 0, false, true, ETATConfigNodeType::E_VALUE) );

    // -Test system settings
    // This section groups some parameters and information about the testing system that is to be executed. 
    // There can be as many test system settings sections as compilers are supported by the test system. 
    // The header of this section is preceded by a “T”, followed by the test type (Performance, Unit, Endurance, etc.).
    TATRuleNode* pTestSystemNode = new TATRuleNode(wxT("T"), 0, false, true, ETATConfigNodeType::E_HEADER);

    // --TestModulesPath
    // The relative path to the executable test modules. It must appear once and only once, and it can’t be empty.
    pTestSystemNode->AddChild( new TATRuleNode(wxT("TestModulesPath"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --ResultsPath
    // The relative path to the test result files. It must appear once and only once, and it can’t be empty.
    pTestSystemNode->AddChild( new TATRuleNode(wxT("ResultsPath"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --CompilationInfoPath
    // Relative path to the solution file (for Visual Studio, for example) or to a Make file. It must appear once and only once. 
    // It can’t be empty.
    pTestSystemNode->AddChild( new TATRuleNode(wxT("CompilationInfoPath"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    // --Compiler
    // The name of the compiler used to compile the project. It has to coincide with the header value of one of the declared compiler settings. 
    // It can appear once and only once.
    pTestSystemNode->AddChild( new TATRuleNode(wxT("Compiler"), 1, false, true, ETATConfigNodeType::E_VALUE) );

    pRuleTree->AddChild( pCompilerNode );
    pRuleTree->AddChild( pProjectNode );
    pRuleTree->AddChild( pFlagNode );
    pRuleTree->AddChild( pSUTNode );
    pRuleTree->AddChild( pTestSystemNode );

    return pRuleTree;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
