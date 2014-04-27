// CallStackTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "QCallStackTracer.h"
#include "QScopedCallStackNotifier.h"
#include "QTraceFormatter.h"
#include "QTracePrinter.h"
#include "BaseClass.h"

class Formatt : public QTraceFormatter
{
public:
    virtual void FormatTrace(const QCallTrace &trace, std::string &strTrace) const
    {
    }
};

QTraceFormatter FORMATTER;
QTracePrinter PRINTER(&FORMATTER);
QCallStackTracer TRACER(&PRINTER);


#define TRACE_OBJECT_METHOD_3PARAMS(functionSignature, param1, param2, param3)                                   \
    const QTypeIdentifier params[3] = { QTypeIdentifier(param1), QTypeIdentifier(param2), QTypeIdentifier(param3) }; \
    QScopedCallStackNotifier notifier(QCallTrace(GetTypeClass(), functionSignature, params, 3, this), TRACER);

#define TRACE_METHOD_3PARAMS(className, functionSignature, param1, param2, param3)                                   \
    const QTypeIdentifier params[3] = { QTypeIdentifier(param1), QTypeIdentifier(param2), QTypeIdentifier(param3) }; \
    QScopedCallStackNotifier notifier(QCallTrace(className, functionSignature, params, 3), TRACER);

#define TRACE_FUNCTION(functionSignature, param1, param2, param3) \
    const QTypeIdentifier params[3] = { QTypeIdentifier(param1), QTypeIdentifier(param2), QTypeIdentifier(param3) }; \
    QScopedCallStackNotifier notifier(QCallTrace("", functionSignature, params, 3), TRACER);


class SomeClass : public BaseClass
{
public:

    int GetValue()
    {
        TRACE_OBJECT_METHOD_3PARAMS("int GetValue()", 0, 0, 0);
        //QScopedCallStackNotifier notifier(QCallTrace("SomeClass", "int GetValue()"), TRACER);
        TRACER.Dump();
        throw;
        return m_value;
    }

    static std::string GetTypeClass()
    {
        return "SomeClass";
    }

    virtual std::string GetType()
    {
        return "SomeClass";
    }

    virtual std::string ToString()
    {
        return "SomeClass: m_value=3";
    }

private:

    int m_value;
};

template<class T>
void TemplateFunc(T o)
{
    QTypeIdentifier params[1] = { QTypeIdentifier(o) };
    QScopedCallStackNotifier notifier(QCallTrace("", "template<class T> void TemplateFunc(T o)", params, 1), TRACER);
    std::cout << o->GetValue();
}

int ParametersFunc(int i, SomeClass* o, float f)
{
    // With params in a macro version:
    TRACE_FUNCTION("int ParametersFunc(int i, SomeClass* o, float f)", i, o, f);

    // With params version:
    //QScopedCallStackNotifier notifier(QCallTrace("", "int ParametersFunc(int i, SomeClass* o, float f)", QTypeIdentifier(i), QTypeIdentifier(o->As<BaseClass>()), QTypeIdentifier(f)), TRACER);

    // With param list version:
    //QTypeIdentifier params[2] = { QTypeIdentifier(i), QTypeIdentifier(o) };
    //QScopedCallStackNotifier notifier(QCallTrace("", "int ParametersFunc(int i, SomeClass o)", params, 2), TRACER);
    TemplateFunc(o);
    return i;
}

void VoidFunc()
{
    QScopedCallStackNotifier notifier(QCallTrace("", "void VoidFunc()"), TRACER);
    int x = ParametersFunc(3, &SomeClass(), 3.4);
}


void TerminateFunction()
{
    TRACER.Dump();
}

void ExitFunction()
{
    TRACER.Dump();
}


int _tmain(int argc, _TCHAR* argv[])
{
    std::set_terminate(&TerminateFunction);
    std::atexit(&ExitFunction);

    QTypeIdentifier params[2] = { QTypeIdentifier(argc), QTypeIdentifier(argv) };
    QScopedCallStackNotifier notifier(QCallTrace("", "int _tmain(int argc, _TCHAR* argv[])", params, 2), TRACER);

    VoidFunc();
    system("pause");
	return 0;
}
/*
Call stack trace for Thread: 1
-->int _tmain(int argc, _TCHAR* argv[])
  |  -{0}int=1
  |  -{1}Pointer=00674760
  -->void VoidFunc()
    -->int ParametersFunc(int i, QObject* o, float f)
      |  -{0}int=3
      |  -{1}ObjectDerivedClass=ObjectDerivedClass: m_value=3
      |  -{2}float=3.4
      -->template<class T> void TemplateFunc(T o)
        |  -{0}ObjectDerivedClass=ObjectDerivedClass: m_value=3
        -->ObjectDerivedClass::int GetValue(int i, int x, int n)
             -{0}int=234
             -{1}int=3
             -{2}int=5
             this->ToString()=ObjectDerivedClass: m_value=3

End of stack trace information.
*/