// [TERMS&CONDITIONS]

#ifndef __QBASEVECTOR2__
#define __QBASEVECTOR2__

#include "Configuration.h"

using namespace Kinesis::QuimeraEngine::Core::Configuration;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// It represents the basic form of a two-dimensional vector with two components: x and y.
/// </summary>
class QDllExport QBaseVector2
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Override default constructor. Sets attributes to zero.
	/// </summary>
	inline QBaseVector2 () : x(0), y(0) {}

	/// <summary>
	/// Constructor that receives 2 FloatTypes, one for each vector components.
	/// </summary>
	inline QBaseVector2 (const float_q &mx, const float_q &my) : x(mx), y(my) {}

	/// <summary>
	/// Constructor that receives only 1 FloatType. Set all attributes to that value.
	/// </summary>
	inline explicit QBaseVector2 (const float_q &mxy) : x(mxy), y(mxy) {}

	/// <summary>
	/// Constructor that receives a pointer-to-FloatType. The pointer should point to a dynamically allocated 2-FloatTypes array.
	/// </summary>
	inline explicit QBaseVector2 (const float_q *pxy) : x(pxy[0]), y(pxy[1]) {}

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Vector's x coordinate.
	/// </summary>
	float_q x;

	/// <summary>
	/// Vector's y coordinate.
	/// </summary>
	float_q y;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEVECTOR2__