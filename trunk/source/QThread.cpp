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

#include "QThread.h"

#include "SQInteger.h"
#include "SQThisThread.h"

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    #include <pthread.h>
    #include <errno.h>
#endif

using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;


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
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QThread::~QThread()
{
    QE_ASSERT_ERROR(!this->IsAlive(), "The thread handler was destroyed while the thread was still alive.");
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QThread::Interrupt()
{
    QE_ASSERT_ERROR(this->IsAlive(), "The thread cannot be interrupted, it is not running.");
    
    m_thread.interrupt();
}

void QThread::Join()
{
    QE_ASSERT_ERROR(SQThisThread::GetId() != this->GetId(), "Deadlock detected: The thread is trying to wait for itself to finish.");
    QE_ASSERT_ERROR(!SQThisThread::IsInterrupted(), "The thread that is calling this method of this instance was interrupted.");

    m_thread.join();
}

string_q QThread::ToString() const
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
    os << this->GetId();
    string_q strId(os.str().c_str());
    strResult.Append(SQInteger::ToString(SQInteger::FromHexadecimalString<IdInteger>(strId)));
    strResult.Append(STRING_PART3);
    return strResult;
}

#if defined(QE_OS_WINDOWS)

EQThreadPriority QThread::_ConvertFromNativePriority(const int nNativePriority)
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

int QThread::_ConvertToNativePriority(const EQThreadPriority &ePriority)
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

#elif defined(QE_OS_LINUX)

EQThreadPriority QThread::_ConvertFromNativePriority(const int nNativePriority, const int nPolicy)
{
    // On Linux, there are different thread scheduling policies which have different priority ranges. In order to provide a concrete and unified set of priorities,
    // we sacrified configuration flexibility (only SCHED_OTHER is used) and "accuracy", so different priorities for different policies may be the same when seen from
    // the user interface point of view. Priority ranges are obtained from the OS and then divided in 3 parts: High, Normal and Low, with two ends: Highest and Lowest
    // for either the maximum and the minimum priority, respectively.

    // The priority range available depends on the Linux distribution
    static const int MIN_PRIORITY = sched_get_priority_min(nPolicy);
    static const int MAX_PRIORITY = sched_get_priority_max(nPolicy);

    EQThreadPriority ePriority = EQThreadPriority::E_Normal;

    // Maximum is not assured to be higher than minimum
    if(MAX_PRIORITY >= MIN_PRIORITY)
    {
        if(nNativePriority > MIN_PRIORITY / 2 && nNativePriority < MAX_PRIORITY / 2)
        {
            ePriority = EQThreadPriority::E_Normal;
        }
        else if(nNativePriority == MAX_PRIORITY)
        {
            ePriority = EQThreadPriority::E_Highest;
        }
        else if(nNativePriority >= MAX_PRIORITY / 2 && nNativePriority < MAX_PRIORITY)
        {
            ePriority = EQThreadPriority::E_High;
        }
        else if(nNativePriority > MIN_PRIORITY && nNativePriority <= MIN_PRIORITY / 2)
        {
            ePriority = EQThreadPriority::E_Low;
        }
        else if(nNativePriority == MIN_PRIORITY)
        {
            ePriority = EQThreadPriority::E_Lowest;
        }
    }
    else // MAX_PRIORITY < MIN_PRIORITY
    {
        if(nNativePriority > MAX_PRIORITY / 2 && nNativePriority < MIN_PRIORITY / 2)
        {
            ePriority = EQThreadPriority::E_Normal;
        }
        else if(nNativePriority == MAX_PRIORITY)
        {
            ePriority = EQThreadPriority::E_Highest;
        }
        else if(nNativePriority > MAX_PRIORITY && nNativePriority <= MAX_PRIORITY / 2)
        {
            ePriority = EQThreadPriority::E_High;
        }
        else if(nNativePriority < MIN_PRIORITY && nNativePriority >= MIN_PRIORITY / 2)
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

int QThread::_ConvertToNativePriority(const EQThreadPriority &ePriority)
{
    int nNativePriority = 0;

    // The priority range available depends on the Linux distribution
    static const int MIN_PRIORITY = sched_get_priority_min(SCHED_OTHER);
    static const int MAX_PRIORITY = sched_get_priority_max(SCHED_OTHER);

    switch(ePriority)
    {
    case EQThreadPriority::E_Highest:
        nNativePriority = MAX_PRIORITY;
        break;
    case EQThreadPriority::E_High:
        nNativePriority = MAX_PRIORITY / 2;
        break;
    case EQThreadPriority::E_Normal:
        nNativePriority = 0;
        break;
    case EQThreadPriority::E_Low:
        nNativePriority = MIN_PRIORITY / 2;
        break;
    case EQThreadPriority::E_Lowest:
        nNativePriority = MIN_PRIORITY;
        break;
    default:
        break;
    }

    return nNativePriority;
}

#elif defined(QE_OS_MAC)

EQThreadPriority QThread::_ConvertFromNativePriority(const int nNativePriority)
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

int QThread::_ConvertToNativePriority(const EQThreadPriority &ePriority)
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

bool QThread::IsAlive() const
{
    return m_thread.joinable();
}

bool QThread::IsInterrupted() const
{
    return m_thread.interruption_requested();
}

QThread::Id QThread::GetId() const
{
    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to get the Id of a not-running thread.");

    return m_thread.get_id();
}

QThread::NativeThreadHandle QThread::GetNativeHandle() const
{
    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to get the native handle of a not-running thread.");

    QThread* pNonConstThis = ccast_q(this, QThread*); // This cast is necessary because the function is const but the Boost's native_handle function is not (without known reason)

    return pNonConstThis->m_thread.native_handle();
}

#if defined(QE_OS_WINDOWS)

EQThreadPriority QThread::GetPriority() const
{
    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to get the priority of a not-running thread.");

    int nNativePriority = ::GetThreadPriority(this->GetNativeHandle());
    return QThread::_ConvertFromNativePriority(nNativePriority);
}

void QThread::SetPriority(const EQThreadPriority &ePriority)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to get the priority of a not-running thread.");

    int nNativePriority = QThread::_ConvertToNativePriority(ePriority);
    BOOL uResult = ::SetThreadPriority(QThread::GetNativeHandle(), nNativePriority);
    
    QE_ASSERT_WARNING(uResult != 0, string_q("An unexpected error ocurred when attempting to set the priority of the ") + this->ToString() + " to " + ePriority.ToString() + ". The error code is:" + SQInteger::ToString(::GetLastError()) + ".");
}

#elif defined(QE_OS_LINUX)

EQThreadPriority QThread::GetPriority() const
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;
    
    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to get the priority of a not-running thread.");
    
    sched_param schedulingPolicy;
    int nPolicy;
    
    int nResult = pthread_getschedparam(this->GetNativeHandle(), &nPolicy, &schedulingPolicy);
    int nNativePriority = schedulingPolicy.__sched_priority;
    
    QE_ASSERT_WARNING(nResult == 0, string_q("An unexpected error ocurred when attempting to get the priority of the ") + this->ToString() + ". The error code is:" + SQInteger::ToString(errno) + ".");
    
    return QThread::_ConvertFromNativePriority(nNativePriority, nPolicy);
}

void QThread::SetPriority(const EQThreadPriority &ePriority)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;
    
    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to set the priority of a not-running thread.");

    int nNativePriority = QThread::_ConvertToNativePriority(ePriority);
    
    sched_param schedulingPolicy;
    schedulingPolicy.__sched_priority = nNativePriority;
    
    int nResult = pthread_setschedparam(this->GetNativeHandle(), SCHED_OTHER, &schedulingPolicy);
    
    QE_ASSERT_WARNING(nResult == 0, string_q("An unexpected error ocurred when attempting to set the priority of the ") + this->ToString() + " to " + ePriority.ToString() + ". The error code is:" + SQInteger::ToString(errno) + ".");
}

#elif defined(QE_OS_MAC)

EQThreadPriority QThread::GetPriority() const
{
}

void QThread::SetPriority(const EQThreadPriority &ePriority)
{
}

#endif

} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
