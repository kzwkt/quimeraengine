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

#ifndef __QLINESEGMENTWHITEBOX__
#define __QLINESEGMENTWHITEBOX__

#include "QLineSegment.h"

using Kinesis::QuimeraEngine::Tools::Math::QLineSegment;

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
/// Class intented to be used to expose protected methods of QLineSegment for testing purposes.
/// </summary>
template<class VectorType>
class QLineSegmentWhiteBox : public QLineSegment<VectorType>
{
	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	QLineSegmentWhiteBox()
    {
    }

    // Necessary for testing
    QLineSegmentWhiteBox(const QLineSegment<VectorType>& lineSegment) : QLineSegment<VectorType>(lineSegment)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    QLineSegment<VectorType>& operator=(const QLineSegment<VectorType> &lineSegment)
    {
        return QLineSegment<VectorType>::operator=(lineSegment);
    }

    // Exposed method
	void GetClosestPoints(const QBaseLineSegment<VectorType> &segment,
						  VectorType& vClosestPtInS1ToS2, VectorType& vClosestPtInS2ToS1) const
    {
        QLineSegment<VectorType>::GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);
    }
};

} //namespace Test
} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENTWHITEBOX__
