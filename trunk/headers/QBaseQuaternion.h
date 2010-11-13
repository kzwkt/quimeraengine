// [TERMS&CONDITIONS]

#ifndef __QBASEQUATERNION__
#define __QBASEQUATERNION__

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
/// It represents the basic form of a quaternion with its four components: x, y, z and w.
/// </summary>
class QBaseQuaternion
{
	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Quaternion's x component.
	/// </summary>
	float_q x;

	/// <summary>
	/// Quaternion's y component.
	/// </summary>
	float_q y;

	/// <summary>
	/// Quaternion's z component.
	/// </summary>
	float_q z;
	
	/// <summary>
	/// Quaternion's w component.
	/// </summary>
	float_q w;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEQUATERNION__
