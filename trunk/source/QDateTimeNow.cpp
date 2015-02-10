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

#include "QDateTimeNow.h"

#include "QLocalTimeZone.h"
#include "QTimeZone.h"

using Kinesis::QuimeraEngine::Tools::Time::QDateTime;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;
using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
#elif defined(QE_OS_MAC)
    #include <sys/time.h>
#endif


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QDateTimeNow::QDateTimeNow() : QDateTime(QDateTimeNow::GetSystemUtcDateTime(), QLocalTimeZone().Get())
{
}
    
QDateTimeNow::QDateTimeNow(const QTimeZone* pTimeZone) : QDateTime(QDateTimeNow::GetSystemUtcDateTime(), pTimeZone)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

#if defined(QE_OS_WINDOWS)

QDateTime QDateTimeNow::GetSystemUtcDateTime()
{
    // GetSystemTimeAsFileTime returns the number of hundreds of nanosecond since January 1, 1601 (UTC)
    static const QDateTime SYSTEM_EPOCH(1601, 1, 1, QTimeZone::UTC);

    // Gets the raw data from the system
    FILETIME fileTime;
    GetSystemTimeAsFileTime(&fileTime); // 100 ns resolution on Windows 7

    // Uses an intermediate structure to extract the number of hundreds of nanoseconds
    ULARGE_INTEGER uTimePassedSinceEpochInHundredsOfNanoseconds;
    uTimePassedSinceEpochInHundredsOfNanoseconds.LowPart = fileTime.dwLowDateTime;
    uTimePassedSinceEpochInHundredsOfNanoseconds.HighPart = fileTime.dwHighDateTime;

    // Builds a time span from the obtained data
    QTimeSpan uTimeSinceEpoch(uTimePassedSinceEpochInHundredsOfNanoseconds.QuadPart);

    // The result is the system epoch plus the time passed since then
    return SYSTEM_EPOCH + uTimeSinceEpoch;
}

#elif defined(QE_OS_LINUX)

QDateTime QDateTimeNow::GetSystemUtcDateTime()
{
    // clock_gettime gets the number of seconds passed since January 1, 1970 (UTC)
    static const QDateTime SYSTEM_EPOCH(1970, 1, 1);
    
    timespec timeData;
    clock_gettime(CLOCK_REALTIME, &timeData);
    // Note: errors are not checked since any of the 3 conditions for it to fail are not met
        
    static const u64_q HUNDREDS_OF_NANOSECOND_PER_SECOND = 10000000ULL;
    QTimeSpan uTimeSinceEpoch(scast_q(timeData.tv_sec, u64_q) * HUNDREDS_OF_NANOSECOND_PER_SECOND + 
                              scast_q(timeData.tv_nsec, u64_q) / 100ULL ); // The resolution of QDateTime is 100 ns
    
    return SYSTEM_EPOCH + uTimeSinceEpoch;
}

#elif defined(QE_OS_MAC)

QDateTime QDateTimeNow::GetSystemUtcDateTime()
{
    // gettimeofday gets the number of seconds passed since January 1, 1970 (UTC)
    static const QDateTime SYSTEM_EPOCH(1970, 1, 1);
    
    // Note: This is an alternative, greater resolution but much slower
    //
    // Includes: 
    // #include <time.h>
    // #include <sys/time.h>
    // #include <mach/clock.h>
    // #include <mach/mach.h>
    //
    // clock_serv_t clockId;
    // host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clockId);
    // 
    // mach_timespec_t timeData;
    // clock_get_time(clockId, &timeData);
    // 
    // mach_port_deallocate(mach_task_self(), clockId);
    //
    // timeData.tv_nsec must be divided by 100
    
    timeval timeData;
    gettimeofday(&timeData, null_q);
    
    static const u64_q HUNDREDS_OF_NANOSECOND_PER_SECOND = 10000000ULL;
    QTimeSpan uTimeSinceEpoch(scast_q(timeData.tv_sec, u64_q) * HUNDREDS_OF_NANOSECOND_PER_SECOND + 
                              scast_q(timeData.tv_usec, u64_q) * 10ULL ); // The resolution of QDateTime is 100 ns and timeData's is 1000 ns so 1000 / 100 = 10
    
    return SYSTEM_EPOCH + uTimeSinceEpoch;
}

#endif

} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
