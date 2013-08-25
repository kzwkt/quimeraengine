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

#ifndef __QBASELINESEGMENT__
#define __QBASELINESEGMENT__

#include "SQFloat.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a segment of straight line in the space, defined by the points at both ends.<br/>
/// These points may be expressed as 2D or 3D points or vectors, depending on the template parameter,
/// which may be 2D vector, 3D vector or 4D vector.
/// </summary>
template <class VectorType>
class QBaseLineSegment
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseLineSegment() : A(SQFloat::_0), B(SQFloat::_0) { }

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="segment">[IN] The segment from which we want to create a copy in the resident segment.</param>
	inline QBaseLineSegment(const QBaseLineSegment &segment) : A(segment.A), B(segment.B)
	{
	}

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define end A.</param>
    /// <param name="vB">[IN] Vector to define end B.</param>
    inline QBaseLineSegment(const VectorType &vA, const VectorType &vB) : A(vA), B(vB)  { }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two line segments.
    /// </summary>
    /// <param name="segment">[IN] Line segment with which to compare.</param>
    /// <returns>
    /// True if line segments are the same, false otherwise.
    /// </returns>
    inline bool operator==(const QBaseLineSegment<VectorType> &segment) const
    {
        return ( this->A == segment.A && this->B == segment.B );
    }

    /// <summary>
    /// Inequality operator. Compares two line segments.
    /// </summary>
    /// <param name="segment">[IN] Line segment with which to compare.</param>
    /// <returns>
    /// True if line segments are not the same, false otherwise.
    /// </returns>
    inline bool operator!=(const QBaseLineSegment<VectorType> &segment) const
    {
        return !(*this == segment);
    }


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents a end of the segment.
    /// </summary>
    VectorType A;

    /// <summary>
    /// Vector which represents the other end of the segment.
    /// </summary>
    VectorType B;
};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASELINESEGMENT__
