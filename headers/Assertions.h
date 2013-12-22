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

#include "CommonDefinitions.h"

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT != QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS // This is used for testing purposes
        #include <exception>
        #define QE_ASSERT(expr) { if(!(expr)) throw new std::exception(); } // TODO [Thund]: Create an special exception class for this
    #else

        #ifdef QE_COMPILER_GCC

            /// <summary>
            /// Special behaviour for using GDB so it stops at the line the assertion fails and let the
            /// developer to continue debugging from there on advance.
            /// </summary>
            QE_LAYER_COMMON_SYMBOLS void QE_ASSERT_FAILED();

            #define QE_ASSERT(expr) (expr) ? (void(0)) : QE_ASSERT_FAILED(); // This sentence makes GDB to stop at the failing line and continue the execution later
        #else
            #include <boost/assert.hpp>

            #ifdef BOOST_ASSERT
                #define QE_ASSERT(expr) BOOST_ASSERT(expr);
            #else
                #define QE_ASSERT(expr) ;
            #endif
        #endif
    #endif

#else

    #define QE_ASSERT(expr) ;

#endif

#endif // __ASSERTIONS__
