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

#ifndef __QBASETRIANGLE__
#define __QBASETRIANGLE__

#include "Assertions.h"
#include "SQFloat.h"
#include "SQVF32.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a triangle in the space.
/// </summary>
/// <typeparam name="VectorType">Allowed types: QBaseVector2, QBaseVector3, QBaseVector4, QVector2, QVector3, QVector4.</typeparam>
template <class VectorType>
class QBaseTriangle
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QBaseTriangle() : A(SQFloat::_0), B(SQFloat::_0), C(SQFloat::_0)
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="triangle">[IN] The triangle from which we want to create a copy in the resident triangle.</param>
    QBaseTriangle(const QBaseTriangle &triangle) : A(triangle.A), B(triangle.B), C(triangle.C)
    {
    }

    /// <summary>
    /// Constructor from three vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    QBaseTriangle(const VectorType &vA, const VectorType &vB, const VectorType &vC) :
                            A(vA), B(vB), C(vC)
    {
    }

    /// <summary>
    /// Constructor from a pointer to floating point values to define each vertex.
    /// </summary>
    /// <remarks>
    /// Pointer must have two, three or four values depending on VectorType.
    /// </remarks>
    /// <param name="arValuesA">[IN] Array of values that define the vertex A. If the pointer is null, the behavior  
    /// is undefined.</param>
    /// <param name="arValuesB">[IN] Array of values that define the vertex B. If the pointer is null, the behavior  
    /// is undefined.</param>
    /// <param name="arValuesC">[IN] Array of values that define the vertex C. If the pointer is null, the behavior 
    /// is undefined.</param>
    QBaseTriangle(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC)
    {
        // Checkout to ensure pointers are not null.
        QE_ASSERT( (arValuesA != null_q) && (arValuesB != null_q) && (arValuesC != null_q) , "Input values must not be null");

        A = VectorType(arValuesA);
        B = VectorType(arValuesB);
        C = VectorType(arValuesC);
    }

    /// <summary>
    /// Constructor from three 4x32 packed floating point values to define each vertex.
    /// </summary>
    /// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
    /// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
    /// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
    QBaseTriangle(const vf32_q &valueA, const vf32_q &valueB, const vf32_q &valueC) :
                             A(valueA), B(valueB), C(valueC)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two triangles.
    /// </summary>
    /// <param name="triangle">[IN] Triangle with which to compare.</param>
    /// <returns>
    /// True if triangles are the same, false otherwise.
    /// </returns>
    bool operator==(const QBaseTriangle<VectorType> &triangle) const
    {
        return ( this->A == triangle.A && this->B == triangle.B && this->C == triangle.C );
    }

    /// <summary>
    /// Inequality operator. Compares two triangles.
    /// </summary>
    /// <param name="triangle">[IN] Triangle with which to compare.</param>
    /// <returns>
    /// True if triangles are not the same, false otherwise.
    /// </returns>
    bool operator!=(const QBaseTriangle<VectorType> &triangle) const
    {
        return !(*this == triangle);
    }


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents a vextex of the triangle.
    /// </summary>
    VectorType A;

    /// <summary>
    /// Vector which represents a vextex of the triangle.
    /// </summary>
    VectorType B;

    /// <summary>
    /// Vector which represents a vextex of the triangle.
    /// </summary>
    VectorType C;

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

template class QE_LAYER_TOOLS_SYMBOLS QBaseTriangle<Kinesis::QuimeraEngine::Tools::Math::QVector2>;
template class QE_LAYER_TOOLS_SYMBOLS QBaseTriangle<Kinesis::QuimeraEngine::Tools::Math::QVector3>;
template class QE_LAYER_TOOLS_SYMBOLS QBaseTriangle<Kinesis::QuimeraEngine::Tools::Math::QVector4>;

#endif // QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASETRIANGLE__
