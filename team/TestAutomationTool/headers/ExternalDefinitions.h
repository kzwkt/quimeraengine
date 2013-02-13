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

#ifndef __EXTERNALDEFINITIONS__
#define __EXTERNALDEFINITIONS__

#include <wx/string.h>

//------------------------
// OS Detection
//------------------------

#ifdef _WIN32
    #define TAT_OS_WINDOWS 32    // Windows 32 bits
#elif defined(_WIN64)
    #define TAT_OS_WINDOWS 64    // Windows 64 bits
#elif defined(__i386) && defined(__linux__)
    #define TAT_OS_LINUX 32      // Linux 32 bits
#elif defined(LINUX64) && defined(__linux__)
    #define TAT_OS_LINUX 64      // Linux 64 bits
#else
    #error Unknown operative system.
// [TODO] Thund: Complete the list, including: Linux 32 bits, Linux 64 bits and MacOS
#endif

//-------------------------
// New line characters
//-------------------------

#ifdef TAT_OS_WINDOWS
    const wxString TAT_NEWLINE_TOKEN = wxT("\r\n");
#elif defined(TAT_OS_LINUX)
    const wxString TAT_NEWLINE_TOKEN = wxT("\n");
#else
    const wxString TAT_NEWLINE_TOKEN = wxT("\r");
#endif

#endif // __EXTERNALDEFINITIONS__