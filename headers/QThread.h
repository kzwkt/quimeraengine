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

#ifndef __QTHREAD__
#define __QTHREAD__

#include "SystemDefinitions.h"
#include "QDelegate.h"
#include "QTimeSpan.h"
#include <boost/thread.hpp>


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Threading
{

/// <summary>
/// Represents a thread in the operating system.
/// </summary>
/// <remarks>
/// A thread starts running when an instance of this class is created.<br/>
/// Every instance creates and controls one thread, and every thread is controlled by only one instance. Threads cannot be copied.<br/>
/// The priority and the stack size of the thread can be configured. Besides, a function can be set to be executed when the thread finishes his job.<br/>
/// It is not possible to set another thread to sleep, use SQThisThread::Sleep method so the thread sets to sleep itself.<br/>
/// This class acts as an extended wrapper of the Boost's thread class.
/// </remarks>
class QE_LAYER_SYSTEM_SYMBOLS QThread
{
    // TYPEDEFS
    // ---------------
public:

    typedef boost::thread::native_handle_type NativeThreadHandle;
    typedef boost::thread::id Id;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    template<class ReturnValueT>
    explicit QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT ()> function) : 
                                                                                            m_thread(function)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T)> function, Argument1T& p1) : 
                                                                                            m_thread(function, p1)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param2T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument2T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    /// <param name="p2">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T, class Param2T, class Argument2T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T, Param2T)> function, Argument1T p1, Argument2T p2) : 
                                                                                            m_thread(function, p1, p2)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param2T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument2T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param3T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument3T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    /// <param name="p2">[IN] A value to be passed as function argument.</param>
    /// <param name="p3">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T, class Param2T, class Argument2T, class Param3T, class Argument3T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T, Param2T, Param3T)> function, Argument1T p1, Argument2T p2, Argument3T p3) : 
                                                                                            m_thread(function, p1, p2, p3)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param2T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument2T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param3T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument3T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param4T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument4T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    /// <param name="p2">[IN] A value to be passed as function argument.</param>
    /// <param name="p3">[IN] A value to be passed as function argument.</param>
    /// <param name="p4">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T, class Param2T, class Argument2T, class Param3T, class Argument3T, class Param4T, class Argument4T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T, Param2T, Param3T, Param4T)> function, 
                                                            Argument1T p1, Argument2T p2, Argument3T p3, Argument4T p4) : 
                                                                                            m_thread(function, p1, p2, p3, p4)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param2T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument2T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param3T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument3T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param4T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument4T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param5T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument5T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    /// <param name="p2">[IN] A value to be passed as function argument.</param>
    /// <param name="p3">[IN] A value to be passed as function argument.</param>
    /// <param name="p4">[IN] A value to be passed as function argument.</param>
    /// <param name="p5">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T, class Param2T, class Argument2T, class Param3T, class Argument3T, class Param4T, class Argument4T, 
                                 class Param5T, class Argument5T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T, Param2T, Param3T, Param4T, Param5T)> function, 
                                                            Argument1T p1, Argument2T p2, Argument3T p3, Argument4T p4, Argument5T p5) : 
                                                                                            m_thread(function, p1, p2, p3, p4, p5)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param2T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument2T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param3T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument3T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param4T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument4T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param5T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument5T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param6T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument6T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    /// <param name="p2">[IN] A value to be passed as function argument.</param>
    /// <param name="p3">[IN] A value to be passed as function argument.</param>
    /// <param name="p4">[IN] A value to be passed as function argument.</param>
    /// <param name="p5">[IN] A value to be passed as function argument.</param>
    /// <param name="p6">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T, class Param2T, class Argument2T, class Param3T, class Argument3T, class Param4T, class Argument4T, 
                                 class Param5T, class Argument5T, class Param6T, class Argument6T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T, Param2T, Param3T, Param4T, Param5T, Param6T)> function, 
                                                            Argument1T p1, Argument2T p2, Argument3T p3, Argument4T p4, Argument5T p5, Argument6T p6) : 
                                                                                            m_thread(function, p1, p2, p3, p4, p5, p6)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param2T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument2T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param3T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument3T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param4T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument4T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param5T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument5T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param6T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument6T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param7T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument7T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    /// <param name="p2">[IN] A value to be passed as function argument.</param>
    /// <param name="p3">[IN] A value to be passed as function argument.</param>
    /// <param name="p4">[IN] A value to be passed as function argument.</param>
    /// <param name="p5">[IN] A value to be passed as function argument.</param>
    /// <param name="p6">[IN] A value to be passed as function argument.</param>
    /// <param name="p7">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T, class Param2T, class Argument2T, class Param3T, class Argument3T, class Param4T, class Argument4T, 
                                 class Param5T, class Argument5T, class Param6T, class Argument6T, class Param7T, class Argument7T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T)> function, 
                                                            Argument1T p1, Argument2T p2, Argument3T p3, Argument4T p4, Argument5T p5, Argument6T p6, Argument7T p7) : 
                                                                                            m_thread(function, p1, p2, p3, p4, p5, p6, p7)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

    /// <summary>
    /// Constructor that recieves a pointer to a function and values for its paramters. A new thread will be created by the operating system and the function 
    /// will be executed on it.
    /// </summary>
    /// <remarks>
    /// Note that every parameter is copied. This is not a problem when using basic data types but it may be when using complex class instances; use the ref_q function
    /// to get a reference to a value before passing it in order to avoid the copy. Besides take into account that the reference will be used in another thread,
    /// so the instance it refers to must exist during the execution of that thread. For example, if the function f() creates an instance c of class C, and then passes it
    /// to this constructor as a reference using ref_q(c), when the function f exits, c will be destroyed and the thread may continue its execution with an invalid reference.
    /// </remarks>
    /// <typeparam name="ReturnValueT">The type of return value of the function.</typeparam>
    /// <typeparam name="Param1T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument1T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param2T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument2T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param3T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument3T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param4T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument4T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param5T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument5T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param6T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument6T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param7T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument7T">The type of the instance to be passed as parameter.</typeparam>
    /// <typeparam name="Param8T">The type of the function parameter.</typeparam>
    /// <typeparam name="Argument8T">The type of the instance to be passed as parameter.</typeparam>
    /// <param name="function">[IN] A delegate that contains the function to be executed. It must not be null.</param>
    /// <param name="p1">[IN] A value to be passed as function argument.</param>
    /// <param name="p2">[IN] A value to be passed as function argument.</param>
    /// <param name="p3">[IN] A value to be passed as function argument.</param>
    /// <param name="p4">[IN] A value to be passed as function argument.</param>
    /// <param name="p5">[IN] A value to be passed as function argument.</param>
    /// <param name="p6">[IN] A value to be passed as function argument.</param>
    /// <param name="p7">[IN] A value to be passed as function argument.</param>
    /// <param name="p8">[IN] A value to be passed as function argument.</param>
    template<class ReturnValueT, class Param1T, class Argument1T, class Param2T, class Argument2T, class Param3T, class Argument3T, class Param4T, class Argument4T, 
                                 class Param5T, class Argument5T, class Param6T, class Argument6T, class Param7T, class Argument7T, class Param8T, class Argument8T>
    QThread(const Kinesis::QuimeraEngine::Common::QDelegate<ReturnValueT (Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T)> function, 
                                                            Argument1T p1, Argument2T p2, Argument3T p3, Argument4T p4, Argument5T p5, Argument6T p6, Argument7T p7, Argument8T p8) : 
                                                                                            m_thread(function, p1, p2, p3, p4, p5, p6, p7, p8)
    {
        QE_ASSERT_ERROR(!function.IsNull(), "The input delegate cannot be null, the thread will not execute.");
    }

private:

    // Hidden
    QThread(const QThread&);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor. It should not be called if the thread is still alive.
    /// </summary>
    ~QThread();


    // METHODS
    // ---------------
private:

    // Hidden
    QThread& operator=(const QThread&);

public:

    /// <summary>
    /// Interrupts the thread's execution. 
    /// </summary>
    /// <remarks>
    /// The thread will stop as soon as it reaches any interruption point (it sleeps, yields, waits for joinning or waits for a condition). No exception will be thrown, 
    /// the interruption just will make an assertion fail.<br/>
    /// This method should not be called if the thread is not running.
    /// </remarks>
    void Interrupt();

    /// <summary>
    /// Makes the calling thread wait for the thread of the instance to finish.
    /// </summary>
    /// <remarks>
    /// If this method is called from a thread that has been interrupted, an assertion will fail.<br/>
    /// The thread from which this method is called must be different from the thread the instance is handling or a deadlock will occur.
    /// </remarks>
    void Join();

    /// <summary>
    /// Generates a string representation of the thread.
    /// </summary>
    /// <remarks>
    /// This method should not be called if the thread is not running.
    /// </remarks>
    /// <returns>
    /// A string that contains the representation of the thread with the format: "Thread(#)", where # means the thread's id.
    /// </returns>
    string_q ToString() const;
    

    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Indicates whether the thread is running or not.
    /// </summary>
    /// <returns>
    /// True if the thread is still running; False otherwise.
    /// </returns>
    bool IsAlive() const;

    /// <summary>
    /// Indicates whether the thread was interrupted or not (it may be still running).
    /// </summary>
    /// <returns>
    /// True if the thread was interrupted; False otherwise.
    /// </returns>
    bool IsInterrupted() const;

    /// <summary>
    /// Gets the ID of the thread using a platform abstraction structure.
    /// </summary>
    /// <remarks>
    /// This method should not be called if the thread is not running.
    /// </remarks>
    /// <returns>
    /// A platform abstraction structure that contains the thread's ID.
    /// </returns>
    QThread::Id GetId() const;

    /// <summary>
    /// Gets a native handle of the thread using platform specific type.
    /// </summary>
    /// <remarks>
    /// Examples of handle types: HANDLE on Windows, pthread_t on Unix-based systems like Linux or Mac.<br/>
    /// This method should not be called if the thread is not running.
    /// </remarks>
    /// <returns>
    /// The thread's ID.
    /// </returns>
    QThread::NativeThreadHandle GetNativeHandle() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The wrapped thread handler.
    /// </summary>
    boost::thread m_thread;

};

} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTHREAD__
