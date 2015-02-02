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

#include "QStopwatch.h"

#include "MathDefinitions.h"


using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{
    
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

#if defined(QE_OS_WINDOWS)

    LARGE_INTEGER QStopwatch::sm_frequency;

#elif defined(QE_OS_MAC)

    mach_timebase_info_data_t QStopwatch::sm_timebaseInfo;

#endif
    

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QStopwatch::QStopwatch() : m_uReferenceTime(0)
{
    static bool bInitialized = false;

    // Initializes auxiliar data
    if(!bInitialized)
    {
#if defined(QE_OS_WINDOWS)

        ::QueryPerformanceFrequency(&sm_frequency);

#elif defined(QE_OS_LINUX)

#elif defined(QE_OS_MAC)

        if(sm_timebaseInfo.denom == 0)
            ::mach_timebase_info(&sm_timebaseInfo);
#endif
        bInitialized = true;
    }
}
    
    
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

u64_q QStopwatch::_GetCurrentInstant()
{

#ifdef QE_OS_WINDOWS

    static const u64_q NANOSECONDS_IN_SECOND = 1000000000ULL;

    LARGE_INTEGER ticks;
    ::QueryPerformanceCounter(&ticks);

    return ticks.QuadPart * NANOSECONDS_IN_SECOND / sm_frequency.QuadPart;

#elif defined(QE_OS_LINUX)

    static const u64_q NANOSECONDS_IN_SECOND = 1000000000ULL;
    
    timespec timeSpecData;
    ::clock_gettime(CLOCK_MONOTONIC_RAW, &timeSpecData);

    return timeSpecData.tv_sec * NANOSECONDS_IN_SECOND + timeSpecData.tv_nsec;

#elif defined (QE_OS_MAC)

    u64_q uRawTime = ::mach_absolute_time();

    return uRawTime * sm_timebaseInfo.numer / sm_timebaseInfo.denom ;

#endif

}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float_q QStopwatch::GetElapsedTimeAsFloat() const
{
    QE_ASSERT_WARNING(m_uReferenceTime > 0, "The stopwatch has not been set.");

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    static const u64_q HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000ULL;
    return scast_q((QStopwatch::_GetCurrentInstant() - m_uReferenceTime) / HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND, float_q);
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    static const float_q HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000.0;
    return scast_q(QStopwatch::_GetCurrentInstant() - m_uReferenceTime, float_q) / HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND;
#endif
}

u64_q QStopwatch::GetElapsedTimeAsInteger() const
{
    QE_ASSERT_WARNING(m_uReferenceTime > 0, "The stopwatch has not been set.");

    return QStopwatch::_GetCurrentInstant() - m_uReferenceTime;
}

QTimeSpan QStopwatch::GetElapsedTimeAsTimeSpan() const
{
    QE_ASSERT_WARNING(m_uReferenceTime > 0, "The stopwatch has not been set.");

    static const u64_q HUNDRED_OF_NANOSECONDS = 100ULL;
    return QTimeSpan((QStopwatch::_GetCurrentInstant() - m_uReferenceTime) / HUNDRED_OF_NANOSECONDS);
}

void QStopwatch::Set()
{
    m_uReferenceTime = QStopwatch::_GetCurrentInstant();
}

} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
