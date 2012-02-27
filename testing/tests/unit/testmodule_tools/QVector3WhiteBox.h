// [TERMS&CONDITIONS]

#ifndef __QVECTOR3WHITEBOX__
#define __QVECTOR3WHITEBOX__

#include "QVector3.h"

using Kinesis::QuimeraEngine::Tools::Math::QVector3;

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
/// Class intented to be used to expose protected methods of QVector3 for testing purposes.
/// </summary>
class QDllExport QVector3WhiteBox : public QVector3
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QVector3WhiteBox();

    // Necessary for testing
    QVector3WhiteBox(const QVector3& vVector) : QVector3(vVector)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QVector3WhiteBox& operator=(const QVector3 &vVector)
    {
        QVector3::operator=(vVector);
    }

    // Exposed method
    template <class MatrixType>
	QVector3 TransformImp(const QTranslationMatrix<MatrixType> &translation) const
    {
        return QVector3::TransformImp(translation);
    }

    // Exposed method
    template <class MatrixType>
	QVector3 TransformImp(const QTransformationMatrix<MatrixType> &transformation) const
    {
        return QVector3::TransformImp(transformation);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVECTOR3WHITEBOX__
