
#ifndef __QTRACEPRINTER__
#define __QTRACEPRINTER__

#include <Windows.h>
#include "QCallStackTrace.h"
#include "QTraceFormatter.h"

class QTracePrinter
{
public:

    QTracePrinter(const QTraceFormatter &formatter) : m_formatter(formatter)
    {
    }

    void Print(const QCallStackTrace &trace)
    {
        std::string strOutput;
        std::string strFormattedOutput;
        m_formatter.FormatCallStackTraceHeader(trace, strFormattedOutput);
        strOutput = strFormattedOutput;
        ::OutputDebugStringA(strOutput.c_str());
        std::cout << strOutput;

        for(std::vector<QCallTrace>::const_iterator it = trace.GetStackStartIterator(); it != trace.GetStackEndIterator(); ++it)
        {
            this->Print(*it);
        }
        
        m_formatter.FormatCallStackTraceFooter(trace, strFormattedOutput);
        strOutput = strFormattedOutput;
        ::OutputDebugStringA(strOutput.c_str());
        std::cout << strOutput;
    }

    void Print(const QCallTrace &trace)
    {
        std::string strOutput;
        std::string strFormattedOutput;
        m_formatter.FormatTraceHeader(trace, strFormattedOutput);
        strOutput += strFormattedOutput;
        m_formatter.FormatTrace(trace, strFormattedOutput);
        strOutput += strFormattedOutput;
        m_formatter.FormatTraceFooter(trace, strFormattedOutput);
        strOutput += strFormattedOutput;
        ::OutputDebugStringA(strOutput.c_str());
        std::cout << strOutput;
    }
    
private:

    QTraceFormatter m_formatter;

};


#endif // __QTRACEPRINTER__