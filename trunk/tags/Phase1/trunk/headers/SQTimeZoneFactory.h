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

#ifndef __SQTIMEZONEFACTORY__
#define __SQTIMEZONEFACTORY__

#include <boost/date_time/local_time/local_time.hpp>
#include "DataTypesDefinitions.h"
#include "ToolsDefinitions.h"

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Time
{

// Forward declarations
class QTimeZone;

/// <summary>
/// A factory of time zones.
/// </summary>
/// <remarks>
/// The only purpose of the class is to create time zones based on the data provided by the IANA/Olson time zone database
/// (http://www.iana.org/time-zones). The internal database is not initialized until the first time the user gets a time zone.
/// Note that the internal copy of the database may not be 100% complete and does not take into account historical DST changes.
/// </remarks>
class QE_LAYER_TOOLS_SYMBOLS SQTimeZoneFactory
{

	// CONSTRUCTORS
	// ---------------
private:

	// Hidden
	SQTimeZoneFactory();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Creates a time zone for a given region Id.
    /// </summary>
    /// <remarks>
    /// Once a time zone is created, it is cached internally so this method just returns a pointer to it in following calls.
    /// </remarks>
    /// <param name="strId">[IN] A region Id of the IANA/Olson time zone database.</param>
    /// <returns>
    /// A fully filled time zone instance. If the region Id is not valid, it returns null.
    /// </returns>
    static const QTimeZone* GetTimeZoneById(const string_q &strId);

private:

    /// <summary>
    /// Creates a time zone database from a text source.
    /// </summary>
    /// <param name="szSource">[IN] The source database, as a text string.</param>
    /// <param name="database">[OUT] The Boost time zone database object to be filled.</param>
    /// <returns>
    /// True if the database was filled; False otherwise.
    /// </returns>
    static bool Initialize(const char* szSource, boost::local_time::tz_database &database);


	// ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// The IANA/Olson database, reduced and reordered, copied from Boost's data file.
    /// </summary>
    static const char* TIME_ZONE_DATABASE;
};

} //namespace Time
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQTIMEZONEFACTORY__
