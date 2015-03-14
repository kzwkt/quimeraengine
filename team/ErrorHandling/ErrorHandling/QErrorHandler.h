
#include <map>
#include <vector>

#include "QException.h"
#include "boost/thread.hpp"
#include <Windows.h>

#ifndef __QERRORHANDLER__
#define __QERRORHANDLER__

class QErrorHandler
{
private:

    QErrorHandler()
    {
    }

public:

    static QErrorHandler* Get()
    {
        return sm_pInstance;
    }

    void AddError(const QException &exception)
    {
        boost::thread::id threadId = boost::this_thread::get_id(); 
        
        std::map<boost::thread::id, std::vector<QException> >::iterator it;

        ::OutputDebugStringA("An exception occurred: Exception message... at function \n");

        std::queue<std::string> callStackTrace = exception.GetCallStackTrace();
        size_t length = callStackTrace.size();
        for(int i = 0; i < length; ++i)
        {
            std::string strTrace = callStackTrace.front();
            callStackTrace.pop();

            for(int j = 0; j <= i; j++)
            {
                ::OutputDebugStringA("-");
            }

            ::OutputDebugStringA(strTrace.c_str());
            ::OutputDebugStringA("\n");
        }

        ::OutputDebugStringA("at file \"");
        ::OutputDebugStringA(exception.GetFileName().c_str());
        ::OutputDebugStringA("\", line ");
        char* aux = new char[6];
        itoa(exception.GetLineNumber(), aux, 10);
        ::OutputDebugStringA(aux);
        delete[] aux;
        ::OutputDebugStringA("\n");

        if((it = m_errorBags.find(threadId)) != m_errorBags.end())
        {
            (*it).second.insert((*it).second.begin(), exception);
        }
        else
        {
            typedef std::vector<QException> ArrayOfExceptions;
            std::pair< boost::thread::id, ArrayOfExceptions > newEntry = std::make_pair<boost::thread::id, ArrayOfExceptions>(threadId, ArrayOfExceptions());
            newEntry.second.push_back(exception);
            m_errorBags.insert(newEntry);
        }
    }

    void DiscardErrors()
    {
        boost::thread::id threadId = boost::this_thread::get_id();

        std::map<boost::thread::id, std::vector<QException> >::iterator it;

        if((it = m_errorBags.find(threadId)) != m_errorBags.end())
        {
            (*it).second.clear();
        }
    }

    bool HasErrors() const
    {
        boost::thread::id threadId = boost::this_thread::get_id();

        std::map<boost::thread::id, std::vector<QException> >::const_iterator it;

        bool bHasErrors = false;

        if((it = m_errorBags.find(threadId)) != m_errorBags.end())
        {
            bHasErrors = !(*it).second.empty();
        }

        return bHasErrors;
    }

    QException GetError(const int index)
    {
        boost::thread::id threadId = boost::this_thread::get_id();

        typedef std::vector<QException> ArrayOfExceptions;
        std::map<boost::thread::id, ArrayOfExceptions >::iterator it;

        QException exception;

        if((it = m_errorBags.find(threadId)) != m_errorBags.end())
        {
            exception = (*it).second[index];
        }

        return exception;
    }

private:

    static QErrorHandler* sm_pInstance;

    std::map<boost::thread::id, std::vector<QException> > m_errorBags;
};


#endif // __QERRORHANDLER__