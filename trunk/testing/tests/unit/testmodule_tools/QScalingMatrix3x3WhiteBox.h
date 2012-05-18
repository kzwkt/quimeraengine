// [TERMS&CONDITIONS] 

#ifndef __QSCALINGMATRIX3X3WHITEBOX__
#define __QSCALINGMATRIX3X3WHITEBOX__

#include "QScalingMatrix3x3.h"

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
/// Class intented to be used to expose protected methods of QScalingMatrix3x3 for testing purposes.
/// </summary>
class QDllExport QScalingMatrix3x3WhiteBox : public QScalingMatrix3x3
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QScalingMatrix3x3WhiteBox();

    // Necessary for testing
    QScalingMatrix3x3WhiteBox(const QScalingMatrix3x3& matrix) : QScalingMatrix3x3(matrix)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QBaseMatrix3x3& operator=(const QScalingMatrix3x3 &matrix)
    {
        return QScalingMatrix3x3::operator=(matrix);
    }

    // Exposed method
    template <class MatrixType>
	QTransformationMatrix<MatrixType> ProductOperatorImp(const QTranslationMatrix<MatrixType> &translation) const
    {
        return QScalingMatrix3x3::ProductOperatorImp(translation);
    }

    // Exposed method
    template <class MatrixType>
	QTransformationMatrix<MatrixType> ProductOperatorImp(const QTransformationMatrix<MatrixType> &transformation) const
    {
        return QScalingMatrix3x3::ProductOperatorImp(transformation);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSCALINGMATRIX3X3WHITEBOX__
