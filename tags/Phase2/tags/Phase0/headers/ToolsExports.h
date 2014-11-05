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

// About this file
// This file is necessary only when compiling as a DLL with MSVC compiler, and not when
// creating a static library or when another compiler is used.
// When compiling to a binary file, all the symbols that may be used by the clients of the library
// must be exposed, or exported, so they can be seen by those clients.
// Since template classes are not compiled until they are instanced somewhere, they are not exported
// in the same way the normal classes are (using QDllExport). These templates are instanced, in fact,
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

#ifndef __TOOLSEXPORTS__
#define __TOOLSEXPORTS__

#include "InternalDefinitions.h"

#ifdef QE_COMPILER_MSVC

// warning C4231: nonstandard extension used : 'extern' before template explicit instantiation
#pragma QE_DISABLE_WARNING(4231)

// If exporting or importing symbols (when compiling as dynamically linked library)
#if defined(QE_PREPROCESSOR_COMPILER_SHAREDLIB) || defined(QE_PREPROCESSOR_COMPILER_IMPORT)


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    MATH			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

// Templates
#include "QSphere.h"
#include "QLineSegment3D.h"
#include "QRay3D.h"
#include "QTriangle3D.h"
#include "QHexahedron.h"
#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"

// Template parameters
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

QE_DLLIMPORT_EXTERN template class QDllExport QBaseOrb<QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseOrb<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseOrb<QVector4>;
QE_DLLIMPORT_EXTERN template class QDllExport QOrb<QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QOrb<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QOrb<QVector4>;
QE_DLLIMPORT_EXTERN template class QDllExport QSphere<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QSphere<QVector4>;

QE_DLLIMPORT_EXTERN template class QDllExport QBaseLineSegment<QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseLineSegment<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseLineSegment<QVector4>;
QE_DLLIMPORT_EXTERN template class QDllExport QLineSegment<QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QLineSegment<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QLineSegment<QVector4>;
QE_DLLIMPORT_EXTERN template class QDllExport QLineSegment3D<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QLineSegment3D<QVector4>;

QE_DLLIMPORT_EXTERN template class QDllExport QBaseRay<QVector2, QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseRay<QVector3, QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseRay<QVector4, QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QRay<QVector2, QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QRay<QVector3, QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QRay<QVector4, QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QRay3D<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QRay3D<QVector4>;

QE_DLLIMPORT_EXTERN template class QDllExport QBaseTriangle<QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseTriangle<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseTriangle<QVector4>;
QE_DLLIMPORT_EXTERN template class QDllExport QTriangle<QVector2>;
QE_DLLIMPORT_EXTERN template class QDllExport QTriangle<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QTriangle<QVector4>;
QE_DLLIMPORT_EXTERN template class QDllExport QTriangle3D<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QTriangle3D<QVector4>;

QE_DLLIMPORT_EXTERN template class QDllExport QBaseHexahedron<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QBaseHexahedron<QVector4>;
QE_DLLIMPORT_EXTERN template class QDllExport QHexahedron<QVector3>;
QE_DLLIMPORT_EXTERN template class QDllExport QHexahedron<QVector4>;

QE_DLLIMPORT_EXTERN template class QDllExport QTransformationMatrix<QMatrix4x3>;
QE_DLLIMPORT_EXTERN template class QDllExport QTransformationMatrix<QMatrix4x4>;

QE_DLLIMPORT_EXTERN template class QDllExport QTranslationMatrix<QMatrix4x3>;
QE_DLLIMPORT_EXTERN template class QDllExport QTranslationMatrix<QMatrix4x4>;

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // QE_PREPROCESSOR_COMPILER_SHAREDLIB || QE_PREPROCESSOR_COMPILER_IMPORT

#endif // QE_COMPILER_MSVC

#endif // __TOOLSEXPORTS__

