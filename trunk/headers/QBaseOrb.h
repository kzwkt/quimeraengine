// [TERMS&CONDITIONS]

#ifndef __QBASEORB__
#define __QBASEORB__

#include "QFloat.h"
#include "QVF32.h"

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
class QDllExport QBaseOrb
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseOrb() : P(QFloat::_0), Radius(QFloat::_0) { }

    /// <summary>
    /// Constructor from a vector which defines center point and a floating point value which 
    /// defines the radius of the orb.
    /// </summary>
    /// <param name="vP">[IN] Vector to define the center of the orb.</param>
    /// <param name="fRadius">[IN] Floating point value to define the radius of the orb.</param>
    inline QBaseOrb(const VectorType &vP, const float_q &fRadius) : P(vP), Radius(fRadius) { }

 
    // ATTRIBUTES
    // ---------------
public:
       
    /// <summary>
    /// Vector which represents the center point of orb.
    /// </summary>
    VectorType P;

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

