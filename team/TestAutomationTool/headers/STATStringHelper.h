// [TERMS&CONDITIONS]

#ifndef __STATSTRINGHELPER__
#define __STATSTRINGHELPER__

#include <list>
#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Helper class that provides several utility methods to work with strings.
/// </summary>
class STATStringHelper
{
	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	STATStringHelper();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Given a source string and a separator token, it returns a list with every string chunk separated by the 
    /// separator token (not included) in the source string.
    /// </summary>
    /// <param name="strSource">The source string to be split.</param>
    /// <param name="strSeparator">The token that acts as separator inside the source string.</param>
    /// <returns>
    /// Returns a list with every string chunk separated by the separator token (not included) in the source string.
    /// If the separator is not found or is empty, then only one entry is returned, containing the source string.
    /// If the source string is empty, an empty list is returned.
    /// </returns>
    static std::list<wxString> Split(const wxString& strSource, const wxString& strSeparator);

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __STATSTRINGHELPER__
