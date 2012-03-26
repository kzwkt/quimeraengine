// [TERMS&CONDITIONS]

#ifndef __QQUATERNIONWHITEBOX__
#define __QQUATERNIONWHITEBOX__

#include "QQuaternion.h"

using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

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
/// Class intented to be used to expose protected methods of QQuaternion for testing purposes.
/// </summary>
class QDllExport QQuaternionWhiteBox : public QQuaternion
{
	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	QQuaternionWhiteBox()
    {
    }

    // Necessary for testing
    QQuaternionWhiteBox(const QQuaternion& qQuaternion) : QQuaternion(qQuaternion)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QBaseQuaternion& operator=(const QQuaternion &qQuaternion)
    {
        return QBaseQuaternion::operator=(qQuaternion);
    }

    // Exposed method
    template <class MatrixType>
	void QQuaternionImp(const QTransformationMatrix<MatrixType> &transformation)
    {
        return QQuaternion::QQuaternionImp<MatrixType>(transformation);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QQUATERNIONWHITEBOX__
