
#ifndef __QCALLTRACE__
#define __QCALLTRACE__

#include <string>

#include "QTypeIdentifier.h"


class QCallTrace
{
public:

    QCallTrace(const std::string &className, const std::string &functionSignature) : m_functionSignature(functionSignature),
                                                                                     m_className(className),
                                                                                     m_pParameters(NULL),
                                                                                     m_numParameters(0)
    {
        
    }

    QCallTrace(const std::string &className, const std::string &functionSignature, const QTypeIdentifier* pParams, const unsigned int numParams) : 
                                                                                                                     m_functionSignature(functionSignature),
                                                                                                                     m_className(className),
                                                                                                                     m_pParameters(pParams),
                                                                                                                     m_numParameters(numParams)
    {
        
    }

    QCallTrace(const std::string &className, const std::string &functionSignature, const QTypeIdentifier* pParams, const unsigned int numParams, BaseClass* pObject) : 
                                                                                                                     m_functionSignature(functionSignature),
                                                                                                                     m_className(className),
                                                                                                                     m_pParameters(pParams),
                                                                                                                     m_numParameters(numParams),
                                                                                                                     m_objectInformation(pObject->ToString())
    {
        
    }

    QCallTrace(const std::string &className, const std::string &functionSignature, const QTypeIdentifier param1, const QTypeIdentifier param2, const QTypeIdentifier param3) : 
                                                                                                                     m_functionSignature(functionSignature),
                                                                                                                     m_className(className)
    {
        static const QTypeIdentifier params[3] = {param1, param2, param3};
        m_pParameters = params;
        m_numParameters = 3;
    }

    std::string m_functionSignature;

    std::string m_className;

    std::string m_objectInformation;

    const QTypeIdentifier* m_pParameters;

    unsigned int m_numParameters;

};


#endif // __QCALLTRACE__