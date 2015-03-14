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

#ifndef __TOOLSDEFINITIONS__
#define __TOOLSDEFINITIONS__

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
#if defined(QE_PREPROCESSOR_EXPORTLIB_TOOLS) // Specified as a preprocessor definition when compiling as a dynamic link library
    #define QE_LAYER_TOOLS_SYMBOLS QE_EXPORT_SYMBOLS
    #define QE_LAYER_TOOLS_EXTERN QE_EXPORT_SYMBOLS_EXTERN
#elif defined(QE_PREPROCESSOR_IMPORTLIB_TOOLS) || defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE) // Specified as a preprocessor definition when compiling the client system
    #define QE_LAYER_TOOLS_SYMBOLS QE_IMPORT_SYMBOLS
    #define QE_LAYER_TOOLS_EXTERN QE_IMPORT_SYMBOLS_EXTERN
#else // Static library
    #define QE_LAYER_TOOLS_SYMBOLS
    #define QE_LAYER_TOOLS_EXTERN
#endif

// ----------------------------------------------------------------------------------------------------------------
// Template specialization flag: Defined only when it is necessary to export template specializations.
// ----------------------------------------------------------------------------------------------------------------
// Exporting template specialization is necessary only when compiling as a DLL with MSVC compiler, and not when
// creating a static library or when another compiler is used.
// When compiling to a binary file, all the symbols that may be used by the clients of the library
// must be exposed, or exported, so they can be seen by those clients.
// Since template classes are not compiled until they are instanced somewhere, they are not exported
// in the same way the normal classes are (using QE_LAYER_TOOLS_SYMBOLS). These templates are instanced, in fact,
// internally, when they are used by other classes of the library. However:
//      1- The client can't find those instances since the template specialization types are not exported.
//      2- Even exporting those types, if the client links a type exported in a header file and then
//         tries to create an instance of the same class locally, a "duplicated symbols" error will occur.
// As a solution to both problems, the compiler is forced to create and export all the template
// specializations allowed by the library, which are put together in a single header file. Additionaly,
// an implementation file had to be included just to tell the compiler to compile the header file.
// Finally, it's important to include this header file wherever any of the template classes listed here
// are used in every client's compilation unit. This way, only the symbols exported by the library are
// linked, avoiding duplicity issues.
//
// Note: This file does nothing when not compiling as a DLL.
//
// Note 2: If you want to know why this is not necessary for GCC, please read: http://gcc.gnu.org/onlinedocs/gcc/Template-Instantiation.html
//         Some people say that this issue could be "fixed" if using /FORCE:MULTIPLE linker option.

#if defined(QE_COMPILER_MSVC)
    // If exporting or importing symbols (when compiling as dynamically linked library)
    #if defined(QE_PREPROCESSOR_EXPORTLIB_TOOLS) || defined(QE_PREPROCESSOR_IMPORTLIB_TOOLS) || defined(QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE)
        #define QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION
    #endif // QE_PREPROCESSOR_EXPORTLIB_TOOLS) || QE_PREPROCESSOR_IMPORTLIB_TOOLS || QE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
#endif // QE_COMPILER_MSVC

#endif // __TOOLSDEFINITIONS__
