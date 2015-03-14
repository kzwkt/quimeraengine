
#ifndef __QEXCEPTION__
#define __QEXCEPTION__

#include <queue>
#include <string>


class QException
{
public:
    QException()
    {
    }

    QException(std::queue<std::string> callstacktrace, std::string fileName, int line)
    {
        m_callStackTrace = callstacktrace;
        m_fileName = fileName;
        m_lineNumber = line;
    }

    const std::queue<std::string>& GetCallStackTrace() const
    {
        return m_callStackTrace;
    }

    const int GetLineNumber() const
    {
        return m_lineNumber;
    }

    const std::string GetFileName() const
    {
        return m_fileName;
    }

protected:

    std::queue<std::string> m_callStackTrace;
    std::string m_fileName;
    int m_lineNumber;
};

#endif // __QEXCEPTION__