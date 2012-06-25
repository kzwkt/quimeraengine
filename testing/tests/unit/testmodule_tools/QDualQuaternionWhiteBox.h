// [TERMS&CONDITIONS]

#ifndef __QDUALQUATERNIONWHITEBOX__
#define __QDUALQUATERNIONWHITEBOX__

#include "QDualQuaternion.h"

using Kinesis::QuimeraEngine::Tools::Math::QDualQuaternion;

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
/// Class intented to be used to expose protected methods of QDualQuaternion for testing purposes.
/// </summary>
class QDllExport QDualQuaternionWhiteBox : public QDualQuaternion
{
	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	QDualQuaternionWhiteBox()
    {
    }

    // Necessary for testing
    QDualQuaternionWhiteBox(const QDualQuaternion& dualQuaternion) : QDualQuaternion(dualQuaternion)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QBaseDualQuaternion& operator=(const QDualQuaternion &dualQuaternion)
    {
        return QBaseDualQuaternion::operator=(dualQuaternion);
    }

    // Exposed method
    template <class VectorType>
	void QDualQuaternionImp(const QBaseQuaternion &qRotation, const VectorType &vTranslation)
    {
        return QDualQuaternion::QDualQuaternionImp<VectorType>(qRotation, vTranslation);
    }

    template <class VectorType>
	void QDualQuaternionImp(const VectorType &vTranslation, const QBaseQuaternion &qRotation)
    {
        return QDualQuaternion::QDualQuaternionImp<VectorType>(vTranslation, qRotation);
    }

    template <class VectorType>
    QDualQuaternion TransformRotationFirstImp(const QBaseQuaternion &qRotation, const VectorType &vTranslation) const
    {
        return QDualQuaternion::TransformRotationFirstImp(qRotation, vTranslation);
    }

    template <class VectorType>
    QDualQuaternion TransformTranslationFirstImp(const VectorType &vTranslation, const QBaseQuaternion &qRotation) const
    {
        return QDualQuaternion::TransformTranslationFirstImp(vTranslation, qRotation);
    }

};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QDUALQUATERNIONWHITEBOX__
