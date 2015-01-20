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

#include "QCallStackTracer.h"

#include "SQThisThread.h"
#include "QScopedExclusiveLock.h"
#include "QScopedSharedLock.h"

using Kinesis::QuimeraEngine::System::Threading::SQThisThread;
using Kinesis::QuimeraEngine::System::Threading::QThread;
using Kinesis::QuimeraEngine::System::Threading::QScopedExclusiveLock;
using Kinesis::QuimeraEngine::System::Threading::QSharedMutex;
using Kinesis::QuimeraEngine::System::Threading::QScopedSharedLock;

#ifdef GetPrinter // On Windows, the API maps the GetPrinter definition to either GetPrinterA or GetPrinterW function names, which prevents the GetPrinter method from being declared
    #undef GetPrinter
#endif
#ifdef SetPrinter // On Windows, the API maps the SetPrinter definition to either SetPrinterA or SetPrinterW function names, which prevents the SetPrinter method from being declared
    #undef SetPrinter
#endif

namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QCallStackTracer::QCallStackTracer() : m_pPrinter((QAbstractCallStackTracePrinter*)null_q)
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

QCallStackTracer* QCallStackTracer::Get()
{
    static QCallStackTracer callStackTracerInstance;

    return &callStackTracerInstance;
}

void QCallStackTracer::AddTrace(const QCallTrace &trace)
{
    QThread::Id threadId = SQThisThread::GetId();

    // ---------- Critical section -----------
    {
        QScopedExclusiveLock<QSharedMutex> exclusiveLock(m_callStackTracesMutex);

        CallStackTraceContainer::iterator itCallStackTrace = m_callStackTraces.find(threadId);

        const bool CALLSTACKTRACE_DOES_NOT_EXIST = itCallStackTrace == m_callStackTraces.end();

        if(CALLSTACKTRACE_DOES_NOT_EXIST)
        {
            // Creates a new call stack trace
            QCallStackTrace* pNewCallStackTrace = new QCallStackTrace(SQThisThread::ToString());
            itCallStackTrace = m_callStackTraces.insert(CallStackTracePair(threadId, pNewCallStackTrace)).first;
        }

        itCallStackTrace->second->Push(trace);

    } // --------- Critical section ----------
}

void QCallStackTracer::RemoveLastTrace()
{
    QThread::Id threadId = SQThisThread::GetId();

    // ---------- Critical section -----------
    {
        QScopedExclusiveLock<QSharedMutex> exclusiveLock(m_callStackTracesMutex);
        CallStackTraceContainer::iterator itCallStackTrace = m_callStackTraces.find(threadId);
        itCallStackTrace->second->Pop();

        // If there are no more traces in the call stack of the current thread, the stack is completely removed
        if(itCallStackTrace->second->GetCount() == 0)
            m_callStackTraces.erase(itCallStackTrace);

    } // --------- Critical section ----------
}

void QCallStackTracer::Dump()
{
    if(m_pPrinter != null_q)
    {
        QThread::Id threadId = SQThisThread::GetId();

        // ---------- Critical section -----------
        {
            QScopedSharedLock<QSharedMutex> sharedLock(m_callStackTracesMutex);

            CallStackTraceContainer::iterator itCallStackTrace = m_callStackTraces.find(threadId);
            const bool CALLSTACKTRACE_EXISTS = itCallStackTrace != m_callStackTraces.end();

            if(CALLSTACKTRACE_EXISTS)
                m_pPrinter->PrintCallStackTrace(*itCallStackTrace->second);

        } // --------- Critical section ----------
    }
    else
    {
        static const string_q NO_TRACES_MESSAGE1("There are no call stack traces for the current thread (");
        static const string_q NO_TRACES_MESSAGE2(").");
        m_pPrinter->PrintString(NO_TRACES_MESSAGE1 + SQThisThread::ToString() + NO_TRACES_MESSAGE2);
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

boost::shared_ptr<QAbstractCallStackTracePrinter> QCallStackTracer::GetPrinter() const
{
    boost::shared_ptr<QAbstractCallStackTracePrinter> pPrinter;

    // ---------- Critical section -----------
    {
        QScopedSharedLock<QSharedMutex> sharedLock(m_printerMutex);

        pPrinter = m_pPrinter;

    } // ---------- Critical section -----------

    return pPrinter;
}

void QCallStackTracer::SetPrinter(const boost::shared_ptr<QAbstractCallStackTracePrinter> &pPrinter)
{
    // ---------- Critical section -----------
    {
        QScopedExclusiveLock<QSharedMutex> exclusiveLock(m_printerMutex);
        m_pPrinter = pPrinter;

    } // ---------- Critical section -----------
}

void QCallStackTracer::SetPrinter(QAbstractCallStackTracePrinter* pPrinter)
{
    this->SetPrinter(boost::shared_ptr<QAbstractCallStackTracePrinter>(pPrinter));
}

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
