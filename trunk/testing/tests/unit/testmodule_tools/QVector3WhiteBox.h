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
class QVector3WhiteBox : public QVector3
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
    QBaseVector3& operator=(const QVector3 &vVector)
    {
        return QVector3::operator=(vVector);
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
