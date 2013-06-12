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

#ifndef __QBASEORB__
#define __QBASEORB__

#include "SQFloat.h"
#include "SQVF32.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a orb in the space, defined by its center point and radius.<br>
/// Center point may be expressed as 2D or 3D point or vector, depending on the parameter of the template,
/// which may be 2D vector, 3D vector or 4D vector.<br>
/// Radius is expressed as a floating point value.<br>
/// Remember that a orb is the locus of points equidistant from a given one.
/// </summary>
template <class VectorType>
class QDllExport QBaseOrb
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseOrb() : Center(SQFloat::_0), Radius(SQFloat::_0)
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="orb">[IN] The orb from which we want to create a copy in the resident orb.</param>
    inline QBaseOrb(const QBaseOrb &orb) : Center(orb.Center), Radius(orb.Radius)
    {
    }

    /// <summary>
    /// Constructor from a vector which defines center point and a floating point value which
    /// defines the radius of the orb.
    /// </summary>
    /// <param name="vCenter">[IN] Vector to define the center of the orb.</param>
    /// <param name="fRadius">[IN] Floating point value to define the radius of the orb.</param>
    inline QBaseOrb(const VectorType &vCenter, const float_q &fRadius) : Center(vCenter), Radius(fRadius) { }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two orbs.
    /// </summary>
    /// <param name="orb">[IN] Orb with which to compare.</param>
    /// <returns>
    /// True if orbs are the same, false otherwise.
    /// </returns>
    inline bool operator== (const QBaseOrb<VectorType> &orb) const
    {
        return this->Center == orb.Center && SQFloat::AreEqual(this->Radius, orb.Radius);
    }

    /// <summary>
    /// Inequality operator. Compares two orbs.
    /// </summary>
    /// <param name="orb">[IN] Orb with which to compare.</param>
    /// <returns>
    /// True if orbs are not the same, false otherwise.
    /// </returns>
    inline bool operator!= (const QBaseOrb<VectorType> &orb) const
    {
        return !(*this == orb);
    }


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents the center point of orb.
    /// </summary>
    VectorType Center;

    /// <summary>
    /// Floating point value representig the radius of the orb.
    /// </summary>
    float_q Radius;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEORB__

