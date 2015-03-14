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

#ifndef __QDATETIMENOW__
#define __QDATETIMENOW__

#include "SystemDefinitions.h"

#include "QDateTime.h"

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

namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{

/// <summary>
/// Represents the system date and time (including time zone and DST) at the moment it is instanced.
/// </summary>
/// <remarks>
/// It is immutable, an instance cannot be modified.<br/>
/// It is wall-clock time, not monotonic, so it is affected by time zone and DST delays besides operating system settings.<br/>
/// The resolution of the clock depends on the operating system, being it between several microseconds and 100 nanoseconds.
/// </remarks>
class QE_LAYER_SYSTEM_SYMBOLS QDateTimeNow : public Kinesis::QuimeraEngine::Tools::Time::QDateTime
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor that gets the system date and time along with the system time zone.
    /// </summary>
    QDateTimeNow();

    /// <summary>
    /// Constructor that gets the system date and time and receives the time zone to be applied.
    /// </summary>
    /// <param name="pTimeZone">The time zone to apply to the system time. If it is null, the time will be UTC.</param>
    QDateTimeNow(const Kinesis::QuimeraEngine::Tools::Time::QTimeZone* pTimeZone);

private:

    // Hidden, not allowed
    QDateTimeNow(const QDateTimeNow &);


    // METHODS
    // ---------------
private:

    // Hidden, not allowed
    QDateTimeNow operator=(const QDateTimeNow &);

protected:

    /// <summary>
    /// Gets the system date and time as UTC from the current operating system.
    /// </summary>
    /// <returns>
    /// The system date and time.
    /// </returns>
    static QDateTime GetSystemUtcDateTime();

};

} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QDATETIMENOW__
