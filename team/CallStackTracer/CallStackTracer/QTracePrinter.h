
#ifndef __QTRACEPRINTER__
#define __QTRACEPRINTER__

#include <Windows.h>
#include "QCallStackTrace.h"
#include "QTraceFormatter.h"

class QTracePrinter
{
public:

    QTracePrinter(const QTraceFormatter* pFormatter) : m_pFormatter(pFormatter)
    {
    }

    void Print(const QCallStackTrace &trace) const
    {
        std::string strOutput;
        std::string strFormattedOutput;
        m_pFormatter->FormatCallStackTraceHeader(trace, strFormattedOutput);
        strOutput = strFormattedOutput;
        ::OutputDebugStringA(strOutput.c_str());
        std::cout << strOutput;

        for(std::vector<QCallTrace>::const_iterator it = trace.GetStackStartIterator(); it != trace.GetStackEndIterator(); ++it)
        {
            this->Print(*it);
        }
        
        m_pFormatter->FormatCallStackTraceFooter(trace, strFormattedOutput);
        strOutput = strFormattedOutput;
        ::OutputDebugStringA(strOutput.c_str());
        std::cout << strOutput;
    }

    void Print(const QCallTrace &trace) const
    {
        std::string strOutput;
        std::string strFormattedOutput;
        m_pFormatter->FormatTraceHeader(trace, strFormattedOutput);
        strOutput += strFormattedOutput;
        m_pFormatter->FormatTrace(trace, strFormattedOutput);
        strOutput += strFormattedOutput;
        m_pFormatter->FormatTraceFooter(trace, strFormattedOutput);
        strOutput += strFormattedOutput;
        ::OutputDebugStringA(strOutput.c_str());
        std::cout << strOutput;
    }
    
private:

    const QTraceFormatter* m_pFormatter;

};


#endif // __QTRACEPRINTER__