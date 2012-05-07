// [TERMS&CONDITIONS]

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
