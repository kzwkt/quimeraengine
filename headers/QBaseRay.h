// [TERMS&CONDITIONS]

#ifndef __QBASERAY__
#define __QBASERAY__

#include "QFloat.h"

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
/// Implements the funcionality of a ray, which is a vector located at a point.
/// </summary>
template<class VectorTypePoint, class VectorTypeDirection>
class QDllExport QBaseRay
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QBaseRay() : Point(QFloat::_0), Direction(QFloat::_0) { }

	/// <summary>
	/// Constructor from a point and a vector.
	/// </summary>
	/// <param name="vPoint">[IN] Point where the vector is located.</param>
	/// <param name="vDirection">[IN] A vector which defines the direction of the ray.</param>
	inline QBaseRay (const VectorTypePoint &vPoint, const VectorTypeDirection &vDirection) : Point(vPoint), Direction(vDirection)	{ }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two rays.
    /// </summary>
    /// <param name="r">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are the same, false otherwise.
    /// </returns>
    inline bool operator == (const QBaseRay<VectorTypePoint, VectorTypeDirection> &r) const
    {
        return ( this->Point == r.Point && this->Direction == r.Direction );
    }

    /// <summary>
    /// Inequality operator. Compares two rays.
    /// </summary>
    /// <param name="r">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are not the same, false otherwise.
    /// </returns>
    inline bool operator != (const QBaseRay<VectorTypePoint, VectorTypeDirection> &r) const
    {
        return !(*this == r);
    }

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Point where the vector is located.
	/// </summary>
	VectorTypePoint Point;

	/// <summary>
	/// Vector which defines the direction of the ray.
	/// </summary>
	VectorTypeDirection Direction;

};

// TYPEDEFS
// ---------------

typedef QBaseRay<QVector2, QVector2> QBaseRay2;
typedef QBaseRay<QVector3, QVector3> QBaseRay3;
typedef QBaseRay<QVector4, QVector3> QBaseRay4;

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASERAY__
