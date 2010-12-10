// [TERMS&CONDITIONS]

#ifndef __QBASESTRAIGHTLINE__
#define __QBASESTRAIGHTLINE__

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
/// Class which represents a segment of straight line in the space, defined by the poins at both ends. 
/// These points may be expressed as 2D or 3D points or vectors, depending on the template parameter, 
/// which may be 2D vector, 3D vector or 4D vector.
/// </summary>
template <class VectorType>
class QDllExport QBaseStraightLine
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseStraightLine () : A(QFloat::_0), B(QFloat::_0) { }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define end A.</param>
    /// <param name="vB">[IN] Vector to define end B.</param>
    inline QBaseStraightLine (const VectorType &vA, const VectorType &vB) : A(vA), B(vB)  { }

 
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

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASESTRAIGHTLINE__

