// [TERMS&CONDITIONS]

#ifndef __STATAPPSETTINGS__
#define __STATAPPSETTINGS__

#include <wx/string.h>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Class that stores application settings.
/// </summary>
class STATAppSettings
{
	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor.
	/// </summary>
	STATAppSettings();


	// DESTRUCTOR
	// ---------------
private:

	/// <summary>
	/// Destructor.
	/// </summary>		
	~STATAppSettings();


	// METHODS
	// ---------------
public:


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// The full path (including file name) where the test configuration file can be found.
	/// </summary>
    /// <returns>
    /// The full path (including file name) where the test configuration file can be found.
    /// </returns>
    static const wxString& GetConfigurationFilePath();


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
	/// The full path (including file name) where the test configuration file can be found.
	/// </summary>
    static const wxString m_strConfigurationFilePath;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __STATAPPSETTINGS__
