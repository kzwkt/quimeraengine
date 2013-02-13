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
