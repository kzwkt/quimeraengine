
#ifndef __QCALLSTACKTRACER__
#define __QCALLSTACKTRACER__

#include <map>

#include "QCallStackTrace.h"
#include "QTracePrinter.h"

class QCallStackTracer
{
public:

    QCallStackTracer(const QTracePrinter &printer) : m_printer(printer)
    {
    }

    void Add(const int threadId, const QCallTrace &trace)
    {
        std::map<int, QCallStackTrace>::iterator it;
        if((it = m_callStackTraces.find(threadId)) != m_callStackTraces.end())
        {
            m_callStackTraces[threadId].Add(trace);
        }
        else
        {
            m_callStackTraces[threadId].Add(trace);
            m_callStackTraces[threadId].ThreadId = threadId;
        }
    }

    void Remove(const int threadId)
    {
        m_callStackTraces[threadId].Remove();

        if(m_callStackTraces[threadId].GetSize() == 0)
            m_callStackTraces.erase(threadId);
    }

    void Dump()
    {
        for(std::map<int, QCallStackTrace>::const_iterator it = m_callStackTraces.begin(); it != m_callStackTraces.end(); ++it)
        {
            m_printer.Print(it->second);
        }
    }


private:

    QTracePrinter m_printer;
    std::map<int, QCallStackTrace> m_callStackTraces;

};


#endif // __QCALLSTACKTRACER__