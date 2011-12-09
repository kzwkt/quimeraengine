// [TERMS&CONDITIONS]

#ifndef __QBASELINESEGMENT__
#define __QBASELINESEGMENT__

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

// Forward declarations
// ----------------------
class QVector2;
class QVector3;
class QVector4;

/// <summary>
/// Class which represents a segment of straight line in the space, defined by the points at both ends.
/// These points may be expressed as 2D or 3D points or vectors, depending on the template parameter,
/// which may be 2D vector, 3D vector or 4D vector.
/// </summary>
template <class VectorType>
class QDllExport QBaseLineSegment
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseLineSegment () : A(SQFloat::_0), B(SQFloat::_0) { }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define end A.</param>
    /// <param name="vB">[IN] Vector to define end B.</param>
    inline QBaseLineSegment (const VectorType &vA, const VectorType &vB) : A(vA), B(vB)  { }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two line segments.
    /// </summary>
    /// <param name="ls">[IN] Line segment with which to compare.</param>
    /// <returns>
    /// True if line segments are the same, false otherwise.
    /// </returns>
    inline bool operator == (const QBaseLineSegment<VectorType> &ls) const
    {
        return ( this->A == ls.A && this->B == ls.B );
    }

    /// <summary>
    /// Inequality operator. Compares two line segments.
    /// </summary>
    /// <param name="ls">[IN] Line segment with which to compare.</param>
    /// <returns>
    /// True if line segments are not the same, false otherwise.
    /// </returns>
    inline bool operator != (const QBaseLineSegment<VectorType> &ls) const
    {
        return !(*this == ls);
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

// TYPEDEFS
// ---------------

typedef QBaseLineSegment<QVector2> QBaseLineSegment2;
typedef QBaseLineSegment<QVector3> QBaseLineSegment3;
typedef QBaseLineSegment<QVector4> QBaseLineSegment4;

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASELINESEGMENT__
