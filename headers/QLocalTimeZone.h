//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __QLOCALTIMEZONE__
#define __QLOCALTIMEZONE__

#include "SystemDefinitions.h"

#ifdef QE_COMPILER_MSVC
    #pragma warning( push )
    #pragma warning( disable: 4251 ) // This warning occurs when using a template specialization as attribute
#endif

#include <map>
#include "DataTypesDefinitions.h"

// Forward declarations
// ---------------------
namespace Kinesis
{
    namespace QuimeraEngine
    {
        namespace Tools
        {
            namespace Time
            {
                class QTimeZone;
            }
        }
    }
}

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{

/// <summary>
/// Represents the local time zone, got from the operative system.
/// </summary>
/// <remarks>
/// When it is instanced, it asks the operative system for the configuration about the time zone and stores an equivalent QTimeZone instance.
/// From that moment, it acts just as an envelope of that instance.
/// </remarks>
class QE_LAYER_SYSTEM_SYMBOLS QLocalTimeZone
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. The current time zone is obtained from the operative system and stored.
	/// </summary>
    /// <remarks>
	/// If there is any problem when finding out the time zone, a null pointer will be stored.
	/// </remarks>
	QLocalTimeZone();


    // METHODS
	// ---------------
protected:

#ifdef QE_OS_WINDOWS

    /// <summary>
    /// The current time zone is obtained from the operative system.
    /// </summary>
    /// <returns>
	/// The equivalent QTimeZone instance. If there was any problem when finding out the time zone, a null pointer will be returned.
	/// </returns>
    static const Kinesis::QuimeraEngine::Tools::Time::QTimeZone* GetCurrentTimeZoneOnWindows();

    /// <summary>
    /// Gets the time zone Id of the IANA/Olson database from a Windows time zone key name.
    /// </summary>
    /// <remarks>
	/// All the equivalences have been obtained from the Unicode Common Locale Data Repository http://www.unicode.org/cldr/charts/24/supplemental/zone_tzid.html.
	/// </remarks>
    /// <param name="strTimeZoneKeyName">A Windows time zone key name.</param>
    /// <returns>
	/// The equivalent time zone ID. If there is no equivalence, it returns an empty string.
	/// </returns>
    static const string_q GetWindowsEquivalentTimeZoneId(const string_q &strTimeZoneKeyName);
	
#elif defined(QE_OS_LINUX)

    /// <summary>
    /// The current time zone is obtained from the operative system.
    /// </summary>
    /// <returns>
	/// The equivalent QTimeZone instance. If there was any problem when finding out the time zone, a null pointer will be returned.
	/// </returns>
    static const Kinesis::QuimeraEngine::Tools::Time::QTimeZone* GetCurrentTimeZoneOnLinux();
		
#elif defined(QE_OS_MAC)

    /// <summary>
    /// The current time zone is obtained from the operative system.
    /// </summary>
    /// <returns>
	/// The equivalent QTimeZone instance. If there was any problem when finding out the time zone, a null pointer will be returned.
	/// </returns>
    static const Kinesis::QuimeraEngine::Tools::Time::QTimeZone* GetCurrentTimeZoneOnMac();
	
#endif


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the stored time zone.
    /// </summary>
    /// <returns>
	/// The time zone. If there was any problem when finding out the time zone, a null pointer will be returned.
	/// </returns>
    const Kinesis::QuimeraEngine::Tools::Time::QTimeZone* Get() const;


	// ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// The local time zone.
    /// </summary>
    const Kinesis::QuimeraEngine::Tools::Time::QTimeZone* m_pTimeZone;
    
#ifdef QE_OS_WINDOWS

    /// <summary>
    /// A dictionary with the equivalences between IANA/Olson time zone IDs and Windows time zone keys. 
    /// </summary>
    static const std::map<string_q, string_q> WINDOWS_TZID_MAPPINGS; // [TODO] Thund: Replace with QDictionary, when it exists

    /// <summary>
    /// An array with all the pairs used in the time zone IDs dictionary.
    /// </summary>
    static const std::pair<string_q, string_q> WINDOWS_TZID_MAPPINGS_ARRAY[];

#endif

};

} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#ifdef QE_COMPILER_MSVC
    #pragma warning( pop )
#endif

#endif // __QLOCALTIMEZONE__
