// [TERMS&CONDITIONS]

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
