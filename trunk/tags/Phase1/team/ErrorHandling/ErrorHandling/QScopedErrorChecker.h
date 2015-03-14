

#ifndef __QSCOPEDERRORCHECKER__
#define __QSCOPEDERRORCHECKER__

#include <queue>
#include "QErrorHandler.h"
#include "QException.h"

class QScopedErrorChecker
{
public:

    QScopedErrorChecker(std::queue<std::string> callStackTrace)
    {
        m_bSuccessful = false;
        m_bErrorSet = false;
        QErrorHandler::Get()->DiscardErrors();
        m_callStackTrace = callStackTrace;
        m_exception = QException(callStackTrace, "", 0);
    }

    ~QScopedErrorChecker()
    {
        if(!m_bSuccessful)
        {
            QErrorHandler::Get()->AddError(m_exception);
        }
    }

    void SetError(QException exception)
    {
        m_bErrorSet = true;
        m_exception = exception;
    }

    void Success()
    {
        if(!m_bErrorSet)
        {
            m_bSuccessful = true;
        }
    }

protected:

    bool m_bSuccessful;
    bool m_bErrorSet;
    QException m_exception;
    std::queue<std::string> m_callStackTrace;
};


#endif // __QSCOPEDERRORCHECKER__