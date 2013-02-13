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

#ifndef __QROTATIONMATRIX3X3WHITEBOX__
#define __QROTATIONMATRIX3X3WHITEBOX__

#include "QRotationMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

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
/// Class intented to be used to expose protected methods of QRotationMatrix3x3 for testing purposes.
/// </summary>
class QDllExport QRotationMatrix3x3WhiteBox : public QRotationMatrix3x3
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QRotationMatrix3x3WhiteBox();

    // Necessary for testing
    QRotationMatrix3x3WhiteBox(const QRotationMatrix3x3& matrix) : QRotationMatrix3x3(matrix)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QBaseMatrix3x3& operator=(const QRotationMatrix3x3 &matrix)
    {
        return QRotationMatrix3x3::operator=(matrix);
    }

    // Exposed method
    template <class MatrixType>
	QTransformationMatrix<MatrixType> ProductOperatorImp(const QTranslationMatrix<MatrixType> &translation) const
    {
        return QRotationMatrix3x3::ProductOperatorImp(translation);
    }

    // Exposed method
    template <class MatrixType>
	QTransformationMatrix<MatrixType> ProductOperatorImp(const QTransformationMatrix<MatrixType> &transformation) const
    {
        return QRotationMatrix3x3::ProductOperatorImp(transformation);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QROTATIONMATRIX3X3WHITEBOX__
