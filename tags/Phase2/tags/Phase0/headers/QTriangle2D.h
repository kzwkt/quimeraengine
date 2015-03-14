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

#ifndef __QTRIANGLE2D__
#define __QTRIANGLE2D__

#include "QTriangle.h"

#include "QVector2.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward declarations
// ---------------------
class QTransformationMatrix3x3;


/// <summary>
/// Class which represents a triangle in 2D.
/// </summary>
class QDllExport QTriangle2D : public QTriangle<QVector2>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QTriangle2D();

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="triangle">[IN] The 2D triangle from which we want to create a copy in the resident 2D triangle.</param>
	QTriangle2D(const QTriangle2D &triangle);

	/// <summary>
	/// Base type constructor.
	/// </summary>
	/// <param name="triangle">[IN] The 2D triangle in which we want resident 2D triangle to be based.</param>
	QTriangle2D(const QBaseTriangle<QVector2> &triangle);

	/// <summary>
	/// Constructor from three 2D vectors, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] 2D Vector which defines vertex A.</param>
	/// <param name="vB">[IN] 2D Vector which defines vertex B.</param>
	/// <param name="vC">[IN] 2D Vector which defines vertex C.</param>
	QTriangle2D(const QVector2 &vA, const QVector2 &vB, const QVector2 &vC);

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex.
    /// </summary>
    /// <remarks>
	/// Each pointer references to an array which has at least two elements.
    /// </remarks>
	/// <param name="arValuesA">[IN] Array of components of the vertex A. If it is null, the behavior is undefined.</param>
	/// <param name="arValuesB">[IN] Array of components of the vertex B. If it is null, the behavior is undefined.</param>
	/// <param name="arValuesC">[IN] Array of components of the vertex C. If it is null, the behavior is undefined.</param>
	QTriangle2D(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC);

	/// <summary>
	/// Constructor from three 4x32 packed floating point values, one for each vertex.
	/// </summary>
	/// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
	QTriangle2D(const vf32_q &valueA, const vf32_q &valueB, const vf32_q &valueC);


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assignation operator. Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="triangle">[IN] Triangle that is assigned to current triangle.</param>
    /// <returns>
    /// A reference to the triangle.
    /// </returns>
	QTriangle2D& operator=(const QBaseTriangle<QVector2> &triangle);

	/// <summary>
	/// Receives a transformation matrix and applies its transformations to the resident triangle.
    /// </summary>
    /// <remarks>
	/// The origin of transformations is the coordinate axis origin.
	/// </remarks>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	QTriangle2D Transform(const QTransformationMatrix3x3 &transformation) const;

	/// <summary>
	/// Receives a transformation matrix and a 2D vector (transformation pivot) and applies the transformations
	/// to the resident triangle.
    /// </summary>
    /// <remarks>
	/// The origin of transformations is the vector type point received as parameter.
	/// </remarks>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="vPivot">[IN] 2D Vector Pivot used for the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	QTriangle2D TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const;

	/// <summary>
	/// Calculates the circumcenter of the triangle.
	/// </summary>
    /// <remarks>
    /// If any of the vertices of the triangle coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The circumcenter.
    /// </returns>
	QVector2 GetCircumcenter() const;

	/// <summary>
	/// Calculates the orthocenter of the triangle.
	/// </summary>
    /// <remarks>
    /// If any of the vertices of the triangle coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The orthocenter.
    /// </returns>
	QVector2 GetOrthocenter() const;

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    QTriangle2D Translate(const QBaseVector2 &vTranslation) const;

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
	QTriangle2D Translate(const float_q &fTranslationX, const float_q &fTranslationY) const;

    /// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided angle
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	QTriangle2D Rotate(const float_q &fRotationAngle) const;

    /// <summary>
	/// This method transforms the resident triangle by rotating it an amount defined by a rotation angle
	/// around a pivot point (as center of rotation).
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	QTriangle2D RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot) const;

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	QTriangle2D Scale(const QBaseVector2 &vScale) const;

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	QTriangle2D Scale(const float_q &fScaleX, const float_q &fScaleY) const;

    /// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	QTriangle2D ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const;

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	QTriangle2D ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot) const;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE2D__
