
#ifndef __QSCOPEDCALLSTACKNOTIFIER__
#define __QSCOPEDCALLSTACKNOTIFIER__

#include <string>

#include "QCallStackTracer.h"
#include "QCallTrace.h"


class QScopedCallStackNotifier
{
public:

    QScopedCallStackNotifier(const QCallTrace& trace, QCallStackTracer& tracer) : m_pTracer(&tracer)
    {
        tracer.Add(1, trace);
    }

    ~QScopedCallStackNotifier()
    {
        m_pTracer->Remove(1);
    }

private:


    QCallStackTracer* m_pTracer;

};


#endif // __QSCOPEDCALLSTACKNOTIFIER__