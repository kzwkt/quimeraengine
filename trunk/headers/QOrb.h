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

#ifndef __QORB__
#define __QORB__

#include "QBaseOrb.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents an orb in the space, defined by its center point and radius.<br>
/// Center point may be expressed as 2D or 3D point or vector, depending on the parameter of the template,
/// which may be 2D vector, 3D vector or 4D vector.<br>
/// Radius is expressed as a floating point value which is always nonnegative.<br>
/// Remember that an orb is the sum of equidistant points from a given one.
/// </summary>
template <class VectorType>
class QDllExport QOrb : public QBaseOrb<VectorType>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QBaseOrb<VectorType>::Center;
    using QBaseOrb<VectorType>::Radius;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QOrb()
    {
    }

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="orb">[IN] The orb from which we want to create a copy in the resident orb.</param>
	inline QOrb(const QOrb<VectorType> &orb) : QBaseOrb<VectorType>(orb)
    {
    }

	/// <summary>
	/// Base type constructor.
	/// </summary>
	/// <param name="orb">[IN] The orb in which we want resident orb to be based.</param>
	inline QOrb(const QBaseOrb<VectorType> &orb) : QBaseOrb<VectorType>(orb)
    {
    }

    /// <summary>
    /// Constructor from a vector which defines the center point and a floating point value which
    /// defines the radius for the orb.
    /// </summary>
    /// <param name="vCenter">[IN] Vector to define the center of the orb.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    inline QOrb(const VectorType &vCenter, const float_q &fRadius) : QBaseOrb<VectorType>(vCenter, fRadius)
    {
    }


    // PROPERTIES
    // ---------------
public:

	/// <summary>
    /// Gets a "unit orb" placed in the center of coordinates and whose radius equals to 1.
	/// </summary>
	/// <returns>
	/// A unit orb.
	/// </returns>
    inline static const QOrb<VectorType>& GetUnitOrb()
    {
        static const QOrb<VectorType> UNITORB(VectorType::GetZeroVector(), SQFloat::_1);
        return UNITORB;
    }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assigning operator.
	/// </summary>
    /// <param name="orb">[IN] The orb to be copied from.</param>
    /// <returns>
	/// A reference to the modified orb.
	/// </returns>
    inline QOrb& operator=(const QBaseOrb<VectorType> &orb)
    {
        QBaseOrb<VectorType>::operator=(orb);
        return *this;
    }

	/// <summary>
	/// This method receives a point and determines if the point is contained into the orb.
	/// </summary>
    /// <remarks>
    /// If the radius of the orb equals zero, the orb will be considered as a point (which is wrong).
    /// </remarks>
    /// <param name="vPoint">[IN] The point to be tested.</param>
	/// <returns>
	/// True if the point is inside the orb (or if it belongs to its bounds). Otherwise returns false.
	/// </returns>
    inline bool Contains(const VectorType &vPoint) const
    {
        // If the radius of the orb equals zero, it doesn't exist
        QE_ASSERT( SQFloat::IsNotZero(this->Radius) );

        // The point is inside the orb whenever the minimum squared distance between the point and
        // the center point of the orb is lower or equals the whole square radius of the orb.
        VectorType vDistance(vPoint - this->Center);
        return SQFloat::IsLessOrEquals(vDistance.GetSquaredLength(), Radius * Radius);
    }

	/// <summary>
	/// This method receives another orb and computes whether this orb intersects the resident one or not.
	/// </summary>
    /// <remarks>
    /// If the radius of the orb equals zero, the orb will be considered as a point (which is wrong).
    /// </remarks>
    /// <param name="orb">[IN] The orb to be checked for intersections.</param>
	/// <returns>
	/// True if they intersect to each other (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
    inline bool Intersection(const QBaseOrb<VectorType> &orb) const
    {
        // If the radius of the orb equals zero, it doesn't exist
        QE_ASSERT( SQFloat::IsNotZero(this->Radius) && SQFloat::IsNotZero(orb.Radius) );

        // An intersection between the two orbs is considered if the minimum squared distance
		// between their center points is lower or equals the square sum of their radius.
        VectorType vDistance(orb.Center - this->Center);
        float_q    fRadiusSum = Radius + orb.Radius;
        return SQFloat::IsLessOrEquals(vDistance.GetSquaredLength(), fRadiusSum * fRadiusSum);
    }

	/// <summary>
	/// Converts the orb into a string with the following format:<br/>
	/// "OB(c($Center),r($Radius))".<br/>
    /// Where "$" means "string representation of attribute".
	/// </summary>
	/// <returns>
	/// The string with the specified format.
	/// </returns>
	string_q ToString() const
	{
		return QE_L("OB(c(") + this->Center.ToString() + QE_L("),r(") + SQFloat::ToString(this->Radius) + QE_L("))");
	}

};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QORB__
