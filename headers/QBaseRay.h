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

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASERAY__
