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

#ifndef __SQTHISTHREAD__
#define __SQTHISTHREAD__

#include "SystemDefinitions.h"

#include "QThread.h"
#include "QTimeSpan.h"
#include "QDelegate.h"
#include "EQThreadPriority.h"

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
    #undef Yield // This definition appears in Windows headers which prevents us to use the name "Yield" as the name of a method
#endif

using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Threading
{
    
/// <summary>
/// Represents the current thread in the operating system.
/// </summary>
/// <remarks>
/// This class acts as an extended wrapper of the Boost's this_thread namespace.
/// </remarks>
class QE_LAYER_SYSTEM_SYMBOLS SQThisThread
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQThisThread();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Makes the calling thread yield execution to any other waiting thread (the operating system decides which one).
    /// </summary>
    static void Yield();
    
    /// <summary>
    /// Suspends the calling thread for a given amount of time.
    /// </summary>
    /// <param name="duration">[IN] The amount of time the thread will be suspended, with millisecond precision.</param>
    static void Sleep(const Kinesis::QuimeraEngine::Tools::Time::QTimeSpan &duration);
    
    /// <summary>
    /// Generates a string representation of the calling thread.
    /// </summary>
    /// <returns>
    /// A string that contains the representation of the thread with the format: "Thread(#)", where # means the thread's id.
    /// </returns>
    static string_q ToString();

private:

#if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Converts a priority value coming from the operating system API to EQThreadPriority equivalent.
    /// </summary>
    /// <param name="nNativePriority">[IN] A native priority value.</param>
    /// <returns>
    /// The corresponding thread priority value.
    /// </returns>
    static EQThreadPriority _ConvertFromNativePriority(const int nNativePriority);
    
    /// <summary>
    /// Converts a priority value coming from the engine to the operating system API's equivalent.
    /// </summary>
    /// <param name="ePriority">[IN] A thread priority.</param>
    /// <returns>
    /// The corresponding native priority value.
    /// </returns>
    static int _ConvertToNativePriority(const EQThreadPriority &ePriority);
    
#elif defined(QE_OS_LINUX)

    /// <summary>
    /// Converts a priority value coming from the operating system API to EQThreadPriority equivalent.
    /// </summary>
    /// <param name="nNativePriority">[IN] A native priority value.</param>
    /// <param name="nPolicy">[IN] The scheduling policy. Depending on whether it is FIFO, RoundRobin, OTHER or NORMAL, the range of priority values change.</param>
    /// <returns>
    /// The corresponding thread priority value.
    /// </returns>
    static EQThreadPriority _ConvertFromNativePriority(const int nNativePriority, const int nPolicy);
    
    /// <summary>
    /// Converts a priority value coming from the engine to the operating system API's equivalent.
    /// </summary>
    /// <param name="ePriority">[IN] A thread priority.</param>
    /// <returns>
    /// The corresponding native priority value for a NORMAL or OTHER policy.
    /// </returns>
    static int _ConvertToNativePriority(const EQThreadPriority &ePriority);

#endif

    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Indicates whether the thread was interrupted or not.
    /// </summary>
    /// <returns>
    /// True if the thread was interrupted; False otherwise.
    /// </returns>
    static bool IsInterrupted();
    
    /// <summary>
    /// Gets the ID of the thread using a platform abstraction structure.
    /// </summary>
    /// <returns>
    /// A platform abstraction structure that contains the thread's ID.
    /// </returns>
    static QThread::Id GetId();
    
    /// <summary>
    /// Gets a native handle of the thread using platform specific type.
    /// </summary>
    /// <remarks>
    /// Examples of handle types: HANDLE on Windows, pthread_t on Unix-based systems like Linux or Mac.
    /// </remarks>
    /// <returns>
    /// The thread's handle.
    /// </returns>
    static QThread::NativeThreadHandle GetNativeHandle();
    
    /// <summary>
    /// Stores a function to be called when the thread finishes.
    /// </summary>
    /// <param name="function">[IN] The function to be executed, with neither parameters nor return value.</param>
    static void SetExitFunction(const Kinesis::QuimeraEngine::Common::QDelegate<void()> function);
    
    /// <summary>
    /// Gets the priority the operating system gives to the calling thread.
    /// </summary>
    /// <returns>
    /// The priority of the thread.
    /// </returns>
    static EQThreadPriority GetPriority();
    
    /// <summary>
    /// Sets the priority the operating system must give to the calling thread.
    /// </summary>
    /// <remarks>
    /// The current user must have permissions to adjust thread priorities.
    /// </remarks>
    /// <param name="ePriority">[IN] The new priority of the thread.</param>
    static void SetPriority(const EQThreadPriority &ePriority);
};

} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQTHISTHREAD__
