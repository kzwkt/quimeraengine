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

#include "SQThisThread.h"

#include "Assertions.h"
#include <sstream>

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    #include <pthread.h>
#endif

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Threading
{


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void SQThisThread::Yield()
{
    boost::this_thread::yield();
}

void SQThisThread::Sleep(const Kinesis::QuimeraEngine::Tools::Time::QTimeSpan &duration)
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(duration.GetMilliseconds()));
}
    
string_q SQThisThread::ToString()
{
#if defined(QE_OS_WINDOWS)
    typedef DWORD IdInteger;
#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    typedef pid_t IdInteger;
#endif

    static const string_q STRING_PART1 = "Thread(";
    static const string_q STRING_PART3 = ")";
    string_q strResult = STRING_PART1;
    std::string strOutput;
    std::stringstream os(strOutput);
    os << SQThisThread::GetId();
    string_q strId(os.str().c_str());
    strResult.Append(string_q::FromInteger(strId.ToIntegerFromHexadecimal<IdInteger>()));
    strResult.Append(STRING_PART3);
    return strResult;
}

#if defined(QE_OS_WINDOWS)

EQThreadPriority SQThisThread::_ConvertFromNativePriority(const int nNativePriority)
{
    EQThreadPriority ePriority = EQThreadPriority::E_Normal;

    switch(nNativePriority)
    {
    case THREAD_PRIORITY_HIGHEST:
        ePriority = EQThreadPriority::E_Highest;
        break;
    case THREAD_PRIORITY_ABOVE_NORMAL:
        ePriority = EQThreadPriority::E_High;
        break;
    case THREAD_PRIORITY_NORMAL:
        ePriority = EQThreadPriority::E_Normal;
        break;
    case THREAD_PRIORITY_BELOW_NORMAL:
        ePriority = EQThreadPriority::E_Low;
        break;
    case THREAD_PRIORITY_LOWEST:
        ePriority = EQThreadPriority::E_Lowest;
        break;
    }

    return ePriority;
}

int SQThisThread::_ConvertToNativePriority(const EQThreadPriority &ePriority)
{
    int nNativePriority = 0;

    switch(ePriority)
    {
    case EQThreadPriority::E_Highest:
        nNativePriority = THREAD_PRIORITY_HIGHEST;
        break;
    case EQThreadPriority::E_High:
        nNativePriority = THREAD_PRIORITY_ABOVE_NORMAL;
        break;
    case EQThreadPriority::E_Normal:
        nNativePriority = THREAD_PRIORITY_NORMAL;
        break;
    case EQThreadPriority::E_Low:
        nNativePriority = THREAD_PRIORITY_BELOW_NORMAL;
        break;
    case EQThreadPriority::E_Lowest:
        nNativePriority = THREAD_PRIORITY_LOWEST;
        break;
    default:
        break;
    }

    return nNativePriority;
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

EQThreadPriority SQThisThread::_ConvertFromNativePriority(const int nNativePriority, const int nPolicy)
{
    // On Linux, there are different thread scheduling policies which have different priority ranges. In order to provide a concrete and unified set of priorities,
    // we sacrified configuration flexibility (only SCHED_OTHER is used) and "accuracy", so different priorities for different policies may be the same when seen from
    // the user interface point of view. Priority ranges are obtained from the OS and then divided in 3 parts: High, Normal and Low, with two ends: Highest and Lowest
    // for either the maximum and the minimum priority, respectively.

    // The priority range available depends on the Linux distribution
    static const int MIN_PRIORITY = sched_get_priority_min(nPolicy);
    static const int MAX_PRIORITY = sched_get_priority_max(nPolicy);

    EQThreadPriority ePriority = EQThreadPriority::E_Normal;

    // Maximum is not assured to be higher than minimum, and they may be negative or positive
    if(MAX_PRIORITY > MIN_PRIORITY)
    {
        const int RANGE_PART = (MAX_PRIORITY - MIN_PRIORITY) / 3;
        const int LOW_PRIORITY_LIMIT = MIN_PRIORITY + RANGE_PART;
        const int HIGH_PRIORITY_LIMIT = MAX_PRIORITY - RANGE_PART;
        
        if(nNativePriority > LOW_PRIORITY_LIMIT && nNativePriority < HIGH_PRIORITY_LIMIT)
        {
            ePriority = EQThreadPriority::E_Normal;
        }
        else if(nNativePriority == MAX_PRIORITY)
        {
            ePriority = EQThreadPriority::E_Highest;
        }
        else if(nNativePriority >= HIGH_PRIORITY_LIMIT && nNativePriority < MAX_PRIORITY)
        {
            ePriority = EQThreadPriority::E_High;
        }
        else if(nNativePriority > MIN_PRIORITY && nNativePriority <= LOW_PRIORITY_LIMIT)
        {
            ePriority = EQThreadPriority::E_Low;
        }
        else if(nNativePriority == MIN_PRIORITY)
        {
            ePriority = EQThreadPriority::E_Lowest;
        }
    }
    else if(MAX_PRIORITY < MIN_PRIORITY)
    {
        const int RANGE_PART = (MIN_PRIORITY - MAX_PRIORITY) / 3;
        const int LOW_PRIORITY_LIMIT = MIN_PRIORITY - RANGE_PART;
        const int HIGH_PRIORITY_LIMIT = MAX_PRIORITY + RANGE_PART;
        
        if(nNativePriority > HIGH_PRIORITY_LIMIT && nNativePriority < LOW_PRIORITY_LIMIT / 2)
        {
            ePriority = EQThreadPriority::E_Normal;
        }
        else if(nNativePriority == MAX_PRIORITY)
        {
            ePriority = EQThreadPriority::E_Highest;
        }
        else if(nNativePriority <= HIGH_PRIORITY_LIMIT && nNativePriority > MAX_PRIORITY)
        {
            ePriority = EQThreadPriority::E_High;
        }
        else if(nNativePriority < MIN_PRIORITY && nNativePriority >= LOW_PRIORITY_LIMIT)
        {
            ePriority = EQThreadPriority::E_Low;
        }
        else if(nNativePriority == MIN_PRIORITY)
        {
            ePriority = EQThreadPriority::E_Lowest;
        }
    }

    return ePriority;
}

int SQThisThread::_ConvertToNativePriority(const EQThreadPriority &ePriority)
{
    int nNativePriority = 0;

    // The priority range available depends on the Linux distribution
    static const int MIN_PRIORITY = sched_get_priority_min(SCHED_OTHER);
    static const int MAX_PRIORITY = sched_get_priority_max(SCHED_OTHER);
    
    int nRangePart = 0;
    int nLowPriorityLimit = 0;
    int nHighPriorityLimit = 0;
    
    if(MAX_PRIORITY >= MIN_PRIORITY)
    {
        nRangePart = (MAX_PRIORITY - MIN_PRIORITY) / 3;
        nLowPriorityLimit = MIN_PRIORITY + nRangePart;
        nHighPriorityLimit = MAX_PRIORITY - nRangePart;
    }
    else
    {
        nRangePart = (MIN_PRIORITY - MAX_PRIORITY) / 3;
        nLowPriorityLimit = MIN_PRIORITY - nRangePart;
        nHighPriorityLimit = MAX_PRIORITY + nRangePart;
    }
    
    switch(ePriority)
    {
    case EQThreadPriority::E_Highest:
        nNativePriority = MAX_PRIORITY;
        break;
    case EQThreadPriority::E_High:
        nNativePriority = nHighPriorityLimit;
        break;
    case EQThreadPriority::E_Normal:
        nNativePriority = 0;
        break;
    case EQThreadPriority::E_Low:
        nNativePriority = nLowPriorityLimit;
        break;
    case EQThreadPriority::E_Lowest:
        nNativePriority = MIN_PRIORITY;
        break;
    default:
        break;
    }

    return nNativePriority;
}

#endif

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool SQThisThread::IsInterrupted()
{
    return boost::this_thread::interruption_requested();
}

QThread::Id SQThisThread::GetId()
{
    return boost::this_thread::get_id();
}

#if defined(QE_OS_WINDOWS)

QThread::NativeThreadHandle SQThisThread::GetNativeHandle()
{
    return ::GetCurrentThread();
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

QThread::NativeThreadHandle SQThisThread::GetNativeHandle()
{
    return pthread_self();
}

#endif

void SQThisThread::SetExitFunction(const Kinesis::QuimeraEngine::Common::QDelegate<void()> function)
{
    boost::this_thread::at_thread_exit(function);
}

#if defined(QE_OS_WINDOWS)

EQThreadPriority SQThisThread::GetPriority()
{
    int nNativePriority = ::GetThreadPriority(SQThisThread::GetNativeHandle());
    return SQThisThread::_ConvertFromNativePriority(nNativePriority);
}

void SQThisThread::SetPriority(const EQThreadPriority &ePriority)
{
    int nNativePriority = SQThisThread::_ConvertToNativePriority(ePriority);
    BOOL uResult = ::SetThreadPriority(SQThisThread::GetNativeHandle(), nNativePriority);
    
    QE_ASSERT_WARNING(uResult != 0, string_q("An unexpected error ocurred when attempting to set the priority of the ") + SQThisThread::ToString() + " to " + ePriority.ToString() + ". The error code is:" + string_q::FromInteger(::GetLastError()) + ".");
}

#elif defined(QE_OS_LINUX)

EQThreadPriority SQThisThread::GetPriority()
{
    sched_param schedulingPolicy;
    int nPolicy;
    
    int nResult = pthread_getschedparam(SQThisThread::GetNativeHandle(), &nPolicy, &schedulingPolicy);
    int nNativePriority = schedulingPolicy.__sched_priority;
    
    QE_ASSERT_WARNING(nResult == 0, string_q("An unexpected error ocurred when attempting to get the priority of the ") + SQThisThread::ToString() + ". The error code is:" + string_q::FromInteger(errno) + ".");
    
    return SQThisThread::_ConvertFromNativePriority(nNativePriority, nPolicy);
}

void SQThisThread::SetPriority(const EQThreadPriority &ePriority)
{
    int nNativePriority = SQThisThread::_ConvertToNativePriority(ePriority);
    
    sched_param schedulingPolicy;
    schedulingPolicy.__sched_priority = nNativePriority;
    
    int nResult = pthread_setschedparam(SQThisThread::GetNativeHandle(), SCHED_OTHER, &schedulingPolicy);
    
    QE_ASSERT_WARNING(nResult == 0, string_q("An unexpected error ocurred when attempting to set the priority of the ") + SQThisThread::ToString() + " to " + ePriority.ToString() + ". The error code is:" + string_q::FromInteger(errno) + ".");
}

#elif defined(QE_OS_MAC)

EQThreadPriority SQThisThread::GetPriority()
{
    sched_param schedulingPolicy;
    int nPolicy;
    
    int nResult = pthread_getschedparam(SQThisThread::GetNativeHandle(), &nPolicy, &schedulingPolicy);
    int nNativePriority = schedulingPolicy.sched_priority;
    
    QE_ASSERT_WARNING(nResult == 0, string_q("An unexpected error ocurred when attempting to get the priority of the ") + SQThisThread::ToString() + ". The error code is:" + string_q::FromInteger(errno) + ".");
    
    return SQThisThread::_ConvertFromNativePriority(nNativePriority, nPolicy);
}

void SQThisThread::SetPriority(const EQThreadPriority &ePriority)
{
    int nNativePriority = SQThisThread::_ConvertToNativePriority(ePriority);
    
    sched_param schedulingPolicy;
    schedulingPolicy.sched_priority = nNativePriority;
    
    int nResult = pthread_setschedparam(SQThisThread::GetNativeHandle(), SCHED_OTHER, &schedulingPolicy);
    
    QE_ASSERT_WARNING(nResult == 0, string_q("An unexpected error ocurred when attempting to set the priority of the ") + SQThisThread::ToString() + " to " + ePriority.ToString() + ". The error code is:" + string_q::FromInteger(errno) + ".");
}

#endif

} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
