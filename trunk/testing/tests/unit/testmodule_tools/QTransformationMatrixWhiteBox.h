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

#ifndef __QTRANSFORMATIONMATRIXWHITEBOX__
#define __QTRANSFORMATIONMATRIXWHITEBOX__

#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

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
/// Class intented to be used to expose protected methods of QTransformationMatrix for testing purposes.
/// </summary>
template<class MatrixType>
class QDllExport QTransformationMatrixWhiteBox : public QTransformationMatrix<MatrixType>
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QTransformationMatrixWhiteBox() : QTransformationMatrix<MatrixType>()
    {
    }

    // Necessary for testing
    QTransformationMatrixWhiteBox(const QTransformationMatrix<MatrixType>& matrix) : QTransformationMatrix<MatrixType>(matrix)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    MatrixType& operator=(const QTransformationMatrix<MatrixType> &matrix)
    {
        return QTransformationMatrix<MatrixType>::operator=(matrix);
    }

    // Exposed methods
	template<class MatrixTypeParam>
    void QTransformationMatrixImp(const QTranslationMatrix<MatrixTypeParam> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
    {
        return QTransformationMatrix<MatrixType>::QTransformationMatrixImp(translation, rotation, scale);
    }

    QRotationMatrix3x3 ToRotationMatrix3x3() const
    {
        return QTransformationMatrix<MatrixType>::ToRotationMatrix3x3();
    }

    void Initialize(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ,
                    const float_q &fRotationX, const float_q &fRotationY, const float_q &fRotationZ, const float_q &fRotationW,
                    const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        QTransformationMatrix<MatrixType>::Initialize(fTranslationX, fTranslationY, fTranslationZ,
                                                      fRotationX, fRotationY, fRotationZ, fRotationW,
                                                      fScaleX, fScaleY, fScaleZ);
    }

    template <class MatrixTypeParam>
    void ProductOperatorImp(const QTransformationMatrix<MatrixTypeParam> &matrix, QTransformationMatrix<MatrixType> &outMatrix) const
    {
        QTransformationMatrix<MatrixType>::ProductOperatorImp(matrix, outMatrix);
    }

    template <class MatrixTypeParam>
    void ProductOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix, QTransformationMatrix<MatrixType> &outMatrix) const
    {
        QTransformationMatrix<MatrixType>::ProductOperatorImp(matrix, outMatrix);
    }

    template <class MatrixTypeParam>
    void ProductAssignationOperatorImp(const QTransformationMatrix<MatrixTypeParam> &matrix)
    {
        QTransformationMatrix<MatrixType>::ProductAssignationOperatorImp(matrix);
    }

    template <class MatrixTypeParam>
    void DecomposeImp(QTransformationMatrix<MatrixTypeParam> &translation,
                      QTransformationMatrix<MatrixTypeParam> &rotation,
                      QTransformationMatrix<MatrixTypeParam> &scale) const
    {
        QTransformationMatrix<MatrixType>::DecomposeImp(translation,
                                                        rotation,
                                                        scale);
    }

    template <class MatrixTypeParam>
    void DecomposeImp(QTranslationMatrix<MatrixTypeParam> &translation,
                      QRotationMatrix3x3 &rotation,
                      QScalingMatrix3x3 &scale) const
    {
        QTransformationMatrix<MatrixType>::DecomposeImp(translation,
                                                        rotation,
                                                        scale);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSFORMATIONMATRIXWHITEBOX__
