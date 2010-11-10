// [TERMS&CONDITIONS]

#ifndef __QBASEVECTOR3__
#define __QBASEVECTOR3__

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
/// It represents the basic form of a three-dimensional vector with three components: x, y and z.
/// </summary>
class QBaseVector3
{
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

	/// <summary>
	/// Vector's z coordinate.
	/// </summary>
	float_q z;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEVECTOR3__
