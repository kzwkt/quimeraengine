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

#ifndef __COREDEFINITIONS__
#define __COREDEFINITIONS__

#include "InternalDefinitions.h"

// --------------------------------------------------------------------------------------------------------
// Library importation / exportation switches: These definitions indicate whether the library is being compiled
// as a dynamic link library or a static library and if its symbols are being imported or exported.
// The switch is set as a preprocessor definition in the compiler options.
// --------------------------------------------------------------------------------------------------------
// Technical explanation (only on Windows, when compiling as DLLs):
// -----------------------------------------------------------------
// Why do we use a different "switch" (macro) for every library instead of using only one to export or import the symbols
// of all of them?
// The problem is that some libraries depend on others. For example, library A depends on B, so when compiling B, the symbols
// of B must be exported but, when compiling A, those symbols must be imported and A's symbols must be exported. If we use the 
// same macro for A and B, how do we import B's symbols and export A's at the same time?
// This way, A uses a preprocessor definition to tell the compiler that the symbols of B are needed to be imported, and another
// preprocessor definition to tell it that the symbols of A are to be exported; maybe, a third library, C, needs to import A's symbols.
// This could seem complex but it is not at all. Just add the macros for all the Quimera Engine libraries to be imported and then
// add a macro for exporting the symbols of the library being compiled.
// In order to simplify the process for final users, a client application or library has only to use one macro, QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE,
// to import the symbols of all the Quimera Engine libraries linked.
#ifdef QE_PREPROCESSOR_EXPORTLIB_CORE // Specified as a preprocessor definition when compiling as a dynamic link library
    #define QE_LAYER_CORE_SYMBOLS QE_EXPORT_SYMBOLS
    #define QE_LAYER_CORE_EXTERN QE_EXPORT_SYMBOLS_EXTERN
#elif defined(QE_PREPROCESSOR_IMPORTLIB_CORE) || defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE) // Specified as a preprocessor definition when compiling the client system
    #define QE_LAYER_CORE_SYMBOLS QE_IMPORT_SYMBOLS
    #define QE_LAYER_CORE_EXTERN QE_IMPORT_SYMBOLS_EXTERN
#else // Static library
    #define QE_LAYER_CORE_SYMBOLS
    #define QE_LAYER_CORE_EXTERN
#endif


#endif // __COREDEFINITIONS__
