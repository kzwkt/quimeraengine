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

#ifndef __QSPACECONVERSIONMATRIXWHITEBOX__
#define __QSPACECONVERSIONMATRIXWHITEBOX__

#include "QSpaceConversionMatrix.h"

using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

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
/// Class intented to be used to expose protected methods of QSpaceConversionMatrix for testing purposes.
/// </summary>
class QSpaceConversionMatrixWhiteBox : public QSpaceConversionMatrix
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QSpaceConversionMatrixWhiteBox()
    {
    }

    // Necessary for testing
    QSpaceConversionMatrixWhiteBox(const QSpaceConversionMatrix& matrix) : QSpaceConversionMatrix(matrix)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    template <class MatrixType>
    void SetWorldSpaceMatrixImp(const QTranslationMatrix<MatrixType> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
    {
        QSpaceConversionMatrix::SetWorldSpaceMatrix(translation, rotation, scale);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSPACECONVERSIONMATRIXWHITEBOX__
