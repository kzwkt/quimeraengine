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

#ifndef __TESTAUTOMATIONTOOL_CONFIGURATION__
#define __TESTAUTOMATIONTOOL_CONFIGURATION__

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Test
{
namespace Configuration
{

// --------------------------------------------------------------------------------------------------------
// Character Set: Specifies the character set used throughout the engine. It can be single-byte: 8 bits, 
// to represente ANSI characteres; multi-byte: 8 and 16 bits mixed, used by Windows systems (aka DBCS) to represent
// any existent alphabets; or Unicode: 16-bits characteres to also represent all existent alphabets.
//
// How to use it: Write a char width definition value as the default width definition.
// --------------------------------------------------------------------------------------------------------
#define TAT_CONFIG_CHARACTERSET_SBCS 0x0    // Single-Byte Character Set
#define TAT_CONFIG_CHARACTERSET_MBCS 0x1    // Multi-Byte Character Set [TODO] Thund: Not supported yet, will be available only for Windows OS.
#define TAT_CONFIG_CHARACTERSET_UNICODE 0x2 // Unicode (2-bytes character set)

#define TAT_CONFIG_CHARACTERSET_DEFAULT TAT_CONFIG_CHARACTERSET_UNICODE // [Configurable]

// --------------------------------------------------------------------------------------------------------
// Asserts behavior: Specifies the behavior of assertions throughout the engine. Assertions can be disabled
// or be replaced by exceptions, for example.
//
// How to use it: Write a behavior value as the default definition.
// --------------------------------------------------------------------------------------------------------
#define TAT_CONFIG_ASSERTSBEHAVIOR_ENABLED 0x0
#define TAT_CONFIG_ASSERTSBEHAVIOR_DISABLED 0x1
#define TAT_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS 0x2

#define TAT_CONFIG_ASSERTSBEHAVIOR_DEFAULT TAT_CONFIG_ASSERTSBEHAVIOR_ENABLED // [Configurable]

}//namespace Configuration
}//namespace Test
}//namespace TestAutomationTool
}//namespace Kinesis

#endif // __TESTAUTOMATIONTOOL_CONFIGURATION__