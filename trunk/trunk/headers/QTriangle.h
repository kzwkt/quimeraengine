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

#ifndef __QTRIANGLE__
#define __QTRIANGLE__

#include "QBaseTriangle.h"

#include "Assertions.h"
#include "MathDefinitions.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Represents a triangle in the space.
/// </summary>
/// <remarks>
/// The triangle may be represented in either 2D or 3D (using either points or vectors), depending on the parameter of the template, which may be
/// 2D vector, 3D vector or 4D vector.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: QVector2, QVector3, QVector4.</typeparam>
template <class VectorT>
class QTriangle : public QBaseTriangle<VectorT>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QBaseTriangle<VectorT>::A;
    using QBaseTriangle<VectorT>::B;
    using QBaseTriangle<VectorT>::C;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QTriangle()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="triangle">[IN] The triangle from which we want to create a copy in the resident triangle.</param>
    QTriangle(const QTriangle<VectorT> &triangle) : QBaseTriangle<VectorT>(triangle)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="triangle">[IN] The triangle in which we want resident triangle to be based.</param>
    QTriangle(const QBaseTriangle<VectorT> &triangle) : QBaseTriangle<VectorT>(triangle)
    {
    }

    /// <summary>
    /// Constructor from three vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    QTriangle(const VectorT &vA, const VectorT &vB, const VectorT &vC) : QBaseTriangle<VectorT>(vA, vB, vC)
    {
    }

    /// <summary>
    /// Constructor from three pointer-to-float type, one for each vertex.
    /// </summary>
    /// <param name="arValuesA">[IN] Array of components of the vertex A. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesB">[IN] Array of components of the vertex B. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesC">[IN] Array of components of the vertex C. If it is null, the behavior is undefined.</param>
    QTriangle(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC) :
                         QBaseTriangle<VectorT>(arValuesA, arValuesB, arValuesC)
    {
    }

    /// <summary>
    /// Constructor from three 4x32 packed floating point values, one for each vertex.
    /// </summary>
    /// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
    /// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
    /// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
    QTriangle(const vf32_q valueA, const vf32_q valueB, const vf32_q valueC) : QBaseTriangle<VectorT>(valueA, valueB, valueC)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator.<br/>
    /// Assigns the provided triangle to the resident triangle.
    /// </summary>
    /// <param name="triangle">[IN] Triangle that will be assigned to current triangle.</param>
    /// <returns>
    /// The assigned value.
    /// </returns>
    QTriangle<VectorT>& operator=(const QBaseTriangle<VectorT> &triangle)
    {
        QBaseTriangle<VectorT>::operator=(triangle);
        return *this;
    }

    /// <summary>
    /// Calculates the surface of the triangle.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// The surface of the triangle in a float point type.
    /// </returns>
    float_q GetSurface() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        QE_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        VectorT u = B - A;
        VectorT v = C - A;

        float_q fSqrLengthU = u.GetSquaredLength();
        float_q fSqrLengthV = v.GetSquaredLength();

        float_q fDotProduct = u.DotProduct(v);

        return sqrt_q(fSqrLengthU * fSqrLengthV - (fDotProduct * fDotProduct)) * SQFloat::_0_5;
    }

    /// <summary>
    /// Calculates the angle formed by edges AB and AC.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
    float_q GetAngleA() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        QE_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        VectorT u = B - A;
        VectorT v = C - A;

        return u.AngleBetween(v);
    }

    /// <summary>
    /// Calculates the angle formed by edges BA and BC.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
    float_q GetAngleB() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        QE_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        VectorT u = A - B;
        VectorT v = C - B;

        return u.AngleBetween(v);
    }

    /// <summary>
    /// Calculates the angle formed by edges CB and CA.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
    float_q GetAngleC() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        QE_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        const VectorT u = A - C;
        const VectorT v = B - C;

        return u.AngleBetween(v);
    }

    /// <summary>
    /// Calculates the incenter of the triangle.
    /// </summary>
    /// <remarks>
    /// The incenter is the center of the incircle or inscribed circle of a triangle, which is 
    /// the largest circle contained in it; it touches (is tangent to) the three sides.<br/>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// </remarks>
    /// <returns>
    /// The incenter.
    /// </returns>
    VectorT GetIncenter() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        QE_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        const VectorT vtSideA = C - B;
        const VectorT vtSideB = A - C;
        const VectorT vtSideC = B - A;

        const float_q fLengthA = vtSideA.GetLength();
        const float_q fLengthB = vtSideB.GetLength();
        const float_q fLengthC = vtSideC.GetLength();

        const float_q fP = SQFloat::_1 / (fLengthA + fLengthB + fLengthC);

        return (fLengthA * A + fLengthB * B + fLengthC * C) * fP;
    }

    /// <summary>
    /// Calculates the centroid of the triangle.
    /// </summary>
    /// <remarks>
    /// The centroid or geomatric center is the arithmetic mean ("average") 
    /// position of all the points in the triangle. The centroid will always coincide with the first third of the segment
    /// that starts at the middle of an edge and ends in the opposite vertex.<br/>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// </remarks>
    /// <returns>
    /// The centroid.
    /// </returns>
    VectorT GetCentroid() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        QE_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        return (A + B + C) / SQFloat::_3;
    }

    /// <summary>
    /// Converts triangle into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "T(a($A),b($B),c($C))"<br/>
    /// Where "$" means "string representation of".
    /// </summary>
    /// <returns>
    /// The string in the specified format.
    /// </returns>
    string_q ToString() const
    {
        return string_q("T(a(") + A.ToString() + QE_L("),b(") + B.ToString() + QE_L("),c(") + C.ToString() + QE_L("))");
    }
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

template class QE_LAYER_TOOLS_SYMBOLS QTriangle<Kinesis::QuimeraEngine::Tools::Math::QVector2>;
template class QE_LAYER_TOOLS_SYMBOLS QTriangle<Kinesis::QuimeraEngine::Tools::Math::QVector3>;
template class QE_LAYER_TOOLS_SYMBOLS QTriangle<Kinesis::QuimeraEngine::Tools::Math::QVector4>;

#endif // QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTriangle__
