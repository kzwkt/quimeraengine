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

#ifndef __QTRANSLATIONMATRIXWHITEBOX__
#define __QTRANSLATIONMATRIXWHITEBOX__

#include "QTranslationMatrix.h"

using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of QTranslationMatrix for testing purposes.
/// </summary>
template<class MatrixType>
class QDllExport QTranslationMatrixWhiteBox : public QTranslationMatrix<MatrixType>
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QTranslationMatrixWhiteBox() : QTranslationMatrix<MatrixType>()
    {
    }

    // Necessary for testing
    QTranslationMatrixWhiteBox(const QTranslationMatrix<MatrixType>& matrix) : QTranslationMatrix<MatrixType>(matrix)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QTranslationMatrix<MatrixType> operator=(const QTranslationMatrix<MatrixType> &matrix)
    {
        return QTranslationMatrix<MatrixType>::operator=(matrix);
    }

    // Exposed methods
    template <class MatrixTypeParam>
    QTranslationMatrix<MatrixType> ProductOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix) const
    {
        return QTranslationMatrix<MatrixType>::ProductOperatorImp(matrix);
    }

    template <class MatrixTypeParam>
    void ProductAssignationOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix)
    {
        QTranslationMatrix<MatrixType>::ProductAssignationOperatorImp(matrix);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSLATIONMATRIXWHITEBOX__
