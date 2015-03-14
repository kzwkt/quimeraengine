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

#ifndef __QBASEQUADRILATERAL__
#define __QBASEQUADRILATERAL__

#include "QVector2.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a four-sided polygon. The quadrilateral is defined by its four vertices.
/// </summary>
class QE_LAYER_TOOLS_SYMBOLS QBaseQuadrilateral
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QBaseQuadrilateral();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral from which we want to create a copy in the resident quadrilateral.</param>
    QBaseQuadrilateral(const QBaseQuadrilateral &quad);

    /// <summary>
    /// Constructor from four vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    /// <param name="vD">[IN] Vector to define vertex D.</param>
    QBaseQuadrilateral(const QVector2 &vA, const QVector2 &vB, const QVector2 &vC, const QVector2 &vD);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two quadrilaterals.
    /// </summary>
    /// <param name="quad">[IN] Quadrilateral with which to compare.</param>
    /// <returns>
    /// True if quadrilaterals are the same, false otherwise.
    /// </returns>
    bool operator==(const QBaseQuadrilateral &quad) const;

    /// <summary>
    /// Inequality operator. Compares two quadrilaterals.
    /// </summary>
    /// <param name="quad">[IN] Quadrilateral with which to compare.</param>
    /// <returns>
    /// True if quadrilaterals are not the same, false otherwise.
    /// </returns>
    bool operator!=(const QBaseQuadrilateral &quad) const;


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents a vextex of the polygon.
    /// </summary>
    QVector2 A;

    /// <summary>
    /// Vector which represents a vextex of the polygon.
    /// </summary>
    QVector2 B;

    /// <summary>
    /// Vector which represents a vextex of the polygon.
    /// </summary>
    QVector2 C;

    /// <summary>
    /// Vector which represents a vextex of the polygon.
    /// </summary>
    QVector2 D;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEQUADRILATERAL__
