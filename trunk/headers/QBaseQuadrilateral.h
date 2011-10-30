// [TERMS&CONDITIONS]

#ifndef __QBASEQUADRILATERAL__
#define __QBASEQUADRILATERAL__

#include "QFloat.h"
#include "QVF32.h"
#include "QVector2.h"

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
/// Class which represents a four-sided polygon. The quadrilateral is defined by its four vertices.
/// </summary>
class QDllExport QBaseQuadrilateral
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseQuadrilateral()
    :
    A(QFloat::_0),
    B(QFloat::_0),
    C(QFloat::_0),
    D(QFloat::_0)
    { }

    /// <summary>
    /// Constructor from four vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    /// <param name="vD">[IN] Vector to define vertex D.</param>
    inline QBaseQuadrilateral(const QVector2 &vA,
                              const QVector2 &vB,
                              const QVector2 &vC,
                              const QVector2 &vD)
    :
    A(vA),
    B(vB),
    C(vC),
    D(vD)
    { }

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
    inline bool operator == (const QBaseQuadrilateral &quad) const
    {
        return ( this->A == quad.A && this->B == quad.B && this->C == quad.C && this->D == quad.D );
    }

    /// <summary>
    /// Inequality operator. Compares two quadrilaterals.
    /// </summary>
    /// <param name="quad">[IN] Quadrilateral with which to compare.</param>
    /// <returns>
    /// True if quadrilaterals are not the same, false otherwise.
    /// </returns>
    inline bool operator != (const QBaseQuadrilateral &quad) const
    {
        return !(*this == quad);
    }

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
