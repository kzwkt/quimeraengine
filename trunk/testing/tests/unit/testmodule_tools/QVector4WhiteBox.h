// [TERMS&CONDITIONS]

#ifndef __QVECTOR4WHITEBOX__
#define __QVECTOR4WHITEBOX__

#include "QVector4.h"

using Kinesis::QuimeraEngine::Tools::Math::QVector4;

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
/// Class intented to be used to expose protected methods of QVector4 for testing purposes.
/// </summary>
class QDllExport QVector4WhiteBox : public QVector4
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QVector4WhiteBox();

    // Necessary for testing
    QVector4WhiteBox(const QVector4& vVector) : QVector4(vVector)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QBaseVector4& operator=(const QVector4 &vVector)
    {
        return QVector4::operator=(vVector);
    }

    // Exposed method
    template <class MatrixType>
	QVector4 TransformImp(const QTranslationMatrix<MatrixType> &translation) const
    {
        return QVector4::TransformImp(translation);
    }

    // Exposed method
    template <class MatrixType>
	QVector4 TransformImp(const QTransformationMatrix<MatrixType> &transformation) const
    {
        return QVector4::TransformImp(transformation);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVECTOR4WHITEBOX__
