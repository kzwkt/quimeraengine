
#ifndef __QCALLSTACKTRACE__
#define __QCALLSTACKTRACE__

#include <vector>

#include "QCallTrace.h"

class QCallStackTrace
{
public:

    void Add(const QCallTrace &trace)
    {
        m_stack.push_back(trace);
    }

    void Remove()
    {
        m_stack.pop_back();
    }

    std::vector<QCallTrace>::const_iterator GetStackStartIterator() const
    {
        return m_stack.begin();
    }

    std::vector<QCallTrace>::const_iterator GetStackEndIterator() const
    {
        return m_stack.end();
    }

    size_t GetSize() const
    {
        return m_stack.size();
    }

    int ThreadId;

private:

    std::vector<QCallTrace> m_stack;

};


#endif // __QCALLSTACKTRACE__