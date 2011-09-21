// [TERMS&CONDITIONS]

#ifndef __QBOOLEAN__
#define __QBOOLEAN__

#include "DataTypesDefinitions.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace DataTypes
{

/// <summary>
/// Helper class that offers functionality related to boolean types.
/// </summary>
class QDllExport QBoolean
{
	// CONSTRUCTORS
	// ---------------
private:

	// Default constructor (hidden).
    QBoolean();


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Converts an input boolean type to an output string type.
	/// </summary>
	/// <returns>
	/// The strings "true" or "false".
	/// </returns>
	static string_q ToString(const bool& bValue);
};


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBOOLEAN__
