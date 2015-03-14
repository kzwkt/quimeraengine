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

#ifndef __QCALLSTACKTRACER__
#define __QCALLSTACKTRACER__

#include <boost/shared_ptr.hpp>

#include "SystemDefinitions.h"
#include "QCallTrace.h"
#include "QAbstractCallStackTracePrinter.h"
#include "QCallStackTrace.h"
#include "QThread.h"
#include "QSharedMutex.h"
#include "QDictionary.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

/// <summary>
/// Builds and stores the function call stack traces of every thread in a single process. It can also print the call stack trace of a thread, using a custom printer.
/// </summary>
/// <remarks>
/// It is a singleton.<br/>
/// It is thread-safe.
/// </remarks>
class QE_LAYER_SYSTEM_SYMBOLS QCallStackTracer
{
    // CONSTRUCTORS
    // ---------------
protected:

    typedef Kinesis::QuimeraEngine::Tools::Containers::QDictionary<Kinesis::QuimeraEngine::System::Threading::QThread::Id, QCallStackTrace*> CallStackTraceContainer;


    // CONSTRUCTORS
    // ---------------
private:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QCallStackTracer();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Gets the instance of the call stack tracer.
    /// </summary>
    /// <returns>
    /// A unique instance of the call stack tracer.
    /// </returns>
    static QCallStackTracer* Get();
    
    /// <summary>
    /// Adds a function call trace to the top of the call stack for the current thread.
    /// </summary>
    /// <param name="trace">[IN] A function call trace.</param>
    void AddTrace(const QCallTrace &trace);

    /// <summary>
    /// Removes a function call trace from the top of the call stack for the current thread. If there are no traces for the current thread, it will fail.
    /// </summary>
    void RemoveLastTrace();

    /// <summary>
    /// Uses a custom printer to send the information of the call stack trace of the current thread to an output channel with a concrete format.
    /// </summary>
    /// <remarks>
    /// If there is not printer assigned, it does nothing.<br/>
    /// If there are no traces for the current thread, it prints a message warning about that.
    /// </remarks>
    virtual void Dump();


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the custom call stack trace printer used for dumping the call stack trace information.
    /// </summary>
    /// <returns>
    /// The custom printer used by the call stack tracer.
    /// </returns>
    boost::shared_ptr<QAbstractCallStackTracePrinter> GetPrinter() const;
    
    /// <summary>
    /// Sets the custom call stack trace printer used for dumping the call stack trace information.
    /// </summary>
    /// <param name="pPrinter">[IN] The custom printer to be used by the tracer. It can be null. It will be stored in a shared smart pointer.</param>
    void SetPrinter(const boost::shared_ptr<QAbstractCallStackTracePrinter> &pPrinter);
    
    /// <summary>
    /// Sets the custom call stack trace printer used for dumping the call stack trace information.
    /// </summary>
    /// <param name="pPrinter">[IN] The custom printer to be used by the tracer. It can be null. It will be stored in a shared smart pointer.</param>
    void SetPrinter(QAbstractCallStackTracePrinter* pPrinter);


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// A dictionary which contains every call stack trace associated to its thread Id.
    /// </summary>
    CallStackTraceContainer m_callStackTraces;
    
    /// <summary>
    /// The custom printer to be used by the tracer.
    /// </summary>
    boost::shared_ptr<QAbstractCallStackTracePrinter> m_pPrinter;

    // Synchronization
    
    /// <summary>
    /// Mutex to synchronize the access to the call stack trace dictionary.
    /// </summary>
    mutable Kinesis::QuimeraEngine::System::Threading::QSharedMutex m_callStackTracesMutex;
    
    /// <summary>
    /// Mutex to synchronize the access to the printer.
    /// </summary>
    mutable Kinesis::QuimeraEngine::System::Threading::QSharedMutex m_printerMutex;
};

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCALLSTACKTRACER__
