//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "SQInternalLogger.h"

#include "EQTextEncoding.h"
#include "QBasicArray.h"

#if defined(QE_COMPILER_MSVC)
    #define NOMINMAX // This definition is necessary to bypass the min and max macros defined in Windows headers
    #include "windows.h"
#elif defined(QE_COMPILER_GCC)
    #include <iostream>
#endif

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QDelegate<void (const string_q&)> SQInternalLogger::Log = SQInternalLogger::DefaultLogFunction;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void SQInternalLogger::DefaultLogFunction(const string_q &strMessage)
{
    // [TODO] Thund: In order to optimize this method, a configurable buffer could be used to avoid reserving and freeing memory on every
    //               string conversion. This may require to add an overload to QStringUncode::ToBytes that receives that buffer.
    
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QStringUnicode;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;
    
    #if defined(QE_OS_WINDOWS)
        static const EQTextEncoding OS_WCHAR_ENCODING = EQTextEncoding::E_UTF16LE;
    #elif defined(QE_OS_LINUX)
        static const EQTextEncoding OS_WCHAR_ENCODING = EQTextEncoding::E_UTF32LE;
    #elif defined(QE_OS_MAC)
        static const EQTextEncoding OS_WCHAR_ENCODING = EQTextEncoding::E_UTF32LE;
    #endif
    
    // Depending on the compiler, a different function is used to print the error message to the console
    
    #if defined(QE_COMPILER_MSVC)
        #if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
            
            QBasicArray<i8_q> arBytes = strMessage.ToBytes(OS_WCHAR_ENCODING);
            ::OutputDebugStringW(rcast_q(arBytes.Get(), wchar_t*));
                
        #elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
            ::OutputDebugStringA(strMessage);
        #endif

    #elif defined(QE_COMPILER_GCC)
        #if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE

            QBasicArray<i8_q> arBytes = strMessage.ToBytes(OS_WCHAR_ENCODING); // [TODO] Thund: Change this to use either LE or BE depending on the machine
            std::wcout << rcast_q(arBytes.Get(), wchar_t*);
            std::wcout.flush();
                
        #elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
            std::cout << strMessage;
            std::cout.flush();
        #endif
        
    #endif
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void SQInternalLogger::SetLogFunction(QDelegate<void (const string_q&)> loggingFunction)
{
    SQInternalLogger::Log = loggingFunction;
}


} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis


