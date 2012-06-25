// [TERMS&CONDITIONS]

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
class QDllExport QSpaceConversionMatrixWhiteBox : public QSpaceConversionMatrix
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
