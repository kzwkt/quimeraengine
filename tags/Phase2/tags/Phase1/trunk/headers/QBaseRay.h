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

#ifndef __QBASERAY__
#define __QBASERAY__

#include "SQFloat.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
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
/// Implements the funcionality of a ray, which is a vector located at a point.
/// </summary>
/// <typeparam name="VectorTypeOrigin">Allowed types: QBaseVector2, QBaseVector3, QBaseVector4, QVector2, QVector3, QVector4.</typeparam>
/// <typeparam name="VectorTypeDirection">Allowed types: QBaseVector2 (when VectorTypeOrigin is QBaseVector2), QBaseVector3 (when VectorTypeOrigin is QBaseVector3 or QBaseVector4), 
/// QVector2 (when VectorTypeOrigin is QVector2), QVector3 (when VectorTypeOrigin is QVector3 or QVector4).</typeparam>
template<class VectorTypeOrigin, class VectorTypeDirection>
class QBaseRay
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QBaseRay() : Origin(SQFloat::_0), Direction(SQFloat::_0)
    {
    }

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="ray">[IN] The ray from which we want to create a copy in the resident ray.</param>
	QBaseRay(const QBaseRay &ray) : Origin(ray.Origin), Direction(ray.Direction)
	{
	}

	/// <summary>
	/// Constructor from a point and a vector.
	/// </summary>
	/// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    /// <param name="vOrigin">[IN] Point where the vector is located.</param>
	/// <param name="vDirection">[IN] A vector which defines the direction of the ray.</param>
	QBaseRay (const VectorTypeOrigin &vOrigin, const VectorTypeDirection &vDirection) :
                        Origin(vOrigin), Direction(vDirection)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two rays.
    /// </summary>
    /// <remarks>
    /// If rays are not normalized, it may occur that 2 similar rays (but not exactly equal) are considered different.
    /// </remarks>
    /// <param name="ray">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are the same, false otherwise.
    /// </returns>
    bool operator==(const QBaseRay<VectorTypeOrigin, VectorTypeDirection> &ray) const
    {
        return ( this->Origin == ray.Origin && this->Direction == ray.Direction );
    }

    /// <summary>
    /// Inequality operator. Compares two rays.
    /// </summary>
    /// <remarks>
    /// If rays are not normalized, it may occur that 2 similar rays (but not exactly equal) are considered different.
    /// </remarks>
    /// <param name="ray">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are not the same, false otherwise.
    /// </returns>
    bool operator!=(const QBaseRay<VectorTypeOrigin, VectorTypeDirection> &ray) const
    {
        return !(*this == ray);
    }

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Point where the vector is located.
	/// </summary>
	VectorTypeOrigin Origin;

	/// <summary>
	/// Vector which defines the direction of the ray.
	/// </summary>
	VectorTypeDirection Direction;

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

template class QE_LAYER_TOOLS_SYMBOLS QBaseRay<Kinesis::QuimeraEngine::Tools::Math::QVector2, Kinesis::QuimeraEngine::Tools::Math::QVector2>;
template class QE_LAYER_TOOLS_SYMBOLS QBaseRay<Kinesis::QuimeraEngine::Tools::Math::QVector3, Kinesis::QuimeraEngine::Tools::Math::QVector3>;
template class QE_LAYER_TOOLS_SYMBOLS QBaseRay<Kinesis::QuimeraEngine::Tools::Math::QVector4, Kinesis::QuimeraEngine::Tools::Math::QVector3>;

#endif // QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASERAY__
