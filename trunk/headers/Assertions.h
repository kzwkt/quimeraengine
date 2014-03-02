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

#ifndef __ASSERTIONS__
#define __ASSERTIONS__

#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"

// Depending on the compiler, a different function is used to print the error message to the console
#if   defined(QE_COMPILER_MSVC)
    #define NOMINMAX // This definition is necessary to bypass the min and max macros defined in Windows headers
    #include "windows.h"

    #if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
        #define QE_CONSOLE_PRINT(strMessage) ::OutputDebugStringW(strMessage)
    #elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_SBCS
        #define QE_CONSOLE_PRINT(strMessage) ::OutputDebugStringA(strMessage)
    #endif

#elif defined(QE_COMPILER_GCC)
    #include <iostream>
    #define QE_CONSOLE_PRINT(strMessage) std::cout << strMessage
#endif

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT != QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS // This is used for testing purposes
        #include <exception>
        // TODO [Thund]: Create an special exception class for this
        #define QE_ASSERT(expression, strErrorMessage)                          \
                {                                                               \
                    if(!(expression))                                           \
                    {                                                           \
                        QE_CONSOLE_PRINT(QE_L("!! QE ASSERTION FAILED !!: "));  \
                        QE_CONSOLE_PRINT(QE_L(strErrorMessage));                \
                        QE_CONSOLE_PRINT(QE_L("\n"));                           \
                        throw new std::exception();                             \
                    }                                                           \
                }
    #else

        #ifdef QE_COMPILER_GCC

            /// <summary>
            /// Special behaviour for using GDB so it stops at the line the assertion fails and let the
            /// developer to continue debugging from there on advance.
            /// </summary>
            QE_LAYER_COMMON_SYMBOLS void QE_ASSERT_FAILED();

            #define QE_ASSERT(expression, strErrorMessage)                                  \
                             {                                                              \
                                 if(!(expression))                                          \
                                 {                                                          \
                                     QE_CONSOLE_PRINT(QE_L("!! QE ASSERTION FAILED !!: ")); \
                                     QE_CONSOLE_PRINT(QE_L(strErrorMessage));               \
                                     QE_CONSOLE_PRINT(QE_L("\n"));                          \
                                     QE_ASSERT_FAILED();                                    \
                                 }                                                          \
                             }
        #else
            #include <boost/assert.hpp>

            #ifdef BOOST_ASSERT

                #define QE_ASSERT(expression, strErrorMessage)                          \
                        {                                                               \
                            if(!(expression))                                           \
                            {                                                           \
                                QE_CONSOLE_PRINT(QE_L("!! QE ASSERTION FAILED !!: "));  \
                                QE_CONSOLE_PRINT(QE_L(strErrorMessage));                \
                                QE_CONSOLE_PRINT(QE_L("\n"));                           \
                                BOOST_ASSERT(expression);                               \
                            }                                                           \
                        }
            #else
                #define QE_ASSERT(expression, strErrorMessage) ;
            #endif
        #endif
    #endif

#else

    #define QE_ASSERT(expression, strErrorMessage) ;

#endif

#endif // __ASSERTIONS__
