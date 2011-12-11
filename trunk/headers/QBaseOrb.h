// [TERMS&CONDITIONS]

#ifndef __QBASEORB__
#define __QBASEORB__

#include "SQFloat.h"
#include "SQVF32.h"
#include "QConvertible.h"

using Kinesis::QuimeraEngine::Core::QConvertible;
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
/// Class which represents a orb in the space, defined by its center point and radius.
/// Center point may be expressed as 2D or 3D point or vector, depending on the parameter of the template,
/// which may be 2D vector, 3D vector or 4D vector.
/// Radius is expressed as a floating point value.
/// Remember that a orb is the locus of points equidistant from a given one.
/// </summary>
template <class VectorType>
class QDllExport QBaseOrb : public QConvertible
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseOrb() : Center(SQFloat::_0), Radius(SQFloat::_0) { }

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
    inline bool operator == (const QBaseOrb<VectorType> &orb) const
    {
        return this->Center == orb.Center && SQFloat::AreEquals(this->Radius, orb.Radius);
    }

    /// <summary>
    /// Inequality operator. Compares two orbs.
    /// </summary>
    /// <param name="orb">[IN] Orb with which to compare.</param>
    /// <returns>
    /// True if orbs are not the same, false otherwise.
    /// </returns>
    inline bool operator != (const QBaseOrb<VectorType> &orb) const
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

