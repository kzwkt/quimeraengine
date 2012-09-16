// [TERMS&CONDITIONS]

#ifndef __SQBOOLEAN__
#define __SQBOOLEAN__

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
class QDllExport SQBoolean
{
	// CONSTRUCTORS
	// ---------------
private:

	// Default constructor (hidden).
    SQBoolean();


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Converts an input boolean type to an output string type.
	/// </summary>
    /// <param name="bValue">[IN] The boolean value to be converted.</param>
	/// <returns>
	/// The strings "true" or "false".
	/// </returns>
	static string_q ToString(const bool& bValue);
};


} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQBOOLEAN__
