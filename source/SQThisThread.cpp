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

#include "SQInteger.h"
#include <sstream>

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    #include <pthread.h>
#endif


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
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

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
    strResult.Append(SQInteger::ToString(SQInteger::FromHexadecimalString<IdInteger>(strId)));
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

#elif defined(QE_OS_LINUX)

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

int SQThisThread::_ConvertToNativePriority(const EQThreadPriority ePriority)
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

#elif defined(QE_OS_MAC)

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

int SQThisThread::_ConvertToNativePriority(const EQThreadPriority ePriority)
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
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    int nNativePriority = SQThisThread::_ConvertToNativePriority(ePriority);
    BOOL uResult = ::SetThreadPriority(SQThisThread::GetNativeHandle(), nNativePriority);
    
    QE_ASSERT_WARNING(uResult != 0, string_q("An unexpected error ocurred when attempting to set the priority of the ") + SQThisThread::ToString() + " to " + ePriority.ToString() + ". The error code is:" + SQInteger::ToString(::GetLastError()) + ".");
}

#elif defined(QE_OS_LINUX)

EQThreadPriority SQThisThread::GetPriority()
{
}

void SQThisThread::SetPriority(const EQThreadPriority &ePriority)
{
}

EQThreadPriority SQThisThread::_ConvertFromNativePriority(const int nNativePriority)
{
}

#elif defined(QE_OS_MAC)

EQThreadPriority SQThisThread::GetPriority()
{
}

void SQThisThread::SetPriority(const EQThreadPriority &ePriority)
{
}

EQThreadPriority SQThisThread::_ConvertFromNativePriority(const int nNativePriority)
{
}

#endif

} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
