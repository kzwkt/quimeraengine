// ErrorHandling.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <exception>
#include <iostream>

#include <stdio.h>
#include <Windows.h>
#include <queue>
#include "QErrorHandler.h"
#include "QException.h"
#include "QScopedErrorChecker.h"
#include <exception>

class QType
{
public:

    QType(const std::string name)
    {
        m_name = name;
    }

    std::string GetName() const
    {
        return m_name;
    }

    std::string m_name;
};


std::queue<std::string> CALL_STACK_TRACE;

class QScopedCallStackTrace
{
public:

    QScopedCallStackTrace(std::string newTrace)
    {
        CALL_STACK_TRACE.push(newTrace);
    }
    QScopedCallStackTrace(const QType* classType, std::string newTrace)
    {
        CALL_STACK_TRACE.push(classType->GetName() + "::" + newTrace);
    }
    ~QScopedCallStackTrace()
    {
        if(!CALL_STACK_TRACE.empty())
            CALL_STACK_TRACE.pop();
    }
};

#include <fstream>

void onTerminate()
{
    std::ofstream file1;
    file1.open("new.txt");
    file1 << "Terminate\n";
    file1 << CALL_STACK_TRACE.front();
    file1.close();
    system("pause");
}

class errorCaller
{
public:

    errorCaller()
    {
     //   throw;
        set_terminate(onTerminate);
    }
};
errorCaller yeah;



class destructor1
{
public:
    ~destructor1()
    {
    }
};
class destructor2
{
public:
    ~destructor2()
    {
    }
};
class destructor3
{
public:
    destructor3()
    {
        //throw;
    }
};




void function()
{
    QScopedCallStackTrace t("void function()");
    QScopedErrorChecker s(CALL_STACK_TRACE);
    
    s.Success();
}

int functionError(int index)
{
    QScopedCallStackTrace t("int functionError(int index)");
    QScopedErrorChecker s(CALL_STACK_TRACE);

    std::vector<int> array(10);
    int result = 0;

    if(index >= array.size())
    {
        QException ex(CALL_STACK_TRACE, __FILE__, __LINE__);
        s.SetError(ex);
    }
    else
    {
        result = array[index];
    }

    s.Success();

    return result;
}

void functionException()
{
    QScopedCallStackTrace t("void functionException()");
    QScopedErrorChecker s(CALL_STACK_TRACE);
    destructor1 x;
    throw destructor3();

    s.Success();
}

void functionCaller()
{
    QScopedCallStackTrace t("void functionCaller()");
    QScopedErrorChecker s(CALL_STACK_TRACE);

    functionError(11);
    destructor2 x;
    functionException();

    s.Success();
}


class ClassA
{
public:

    void MethodA()
    {
        QScopedCallStackTrace t(this->GetType(), "void MethodA()");

        this->MethodB(0, 0);

    }

    void MethodB(int i, float x)
    {
        QScopedCallStackTrace t(this->GetType(), "void MethodB(int i, float x)");
        QScopedErrorChecker s(CALL_STACK_TRACE);
        int* pi = NULL;
        throw int(0);
    }

    const QType* GetType() const
    {
        return TYPE;
    }

    static const QType* TYPE;
};

const QType* ClassA::TYPE = new QType("ClassA");


errorCaller yeah2;
int _tmain(int argc, _TCHAR* argv[])/* try*/
{

    ClassA a;

    a.MethodA();



    //std::set_unexpected(onUnexpected); deprecated

    //std::terminate();

    /*function();

    QErrorHandler* pErrorHandler = QErrorHandler::Get();

    if(pErrorHandler->HasErrors())
    {
        QException ex = pErrorHandler->GetError(0);
    }

    int value = functionError(10);

    if(pErrorHandler->HasErrors())
    {
        value = 3;
    }

    int value2 = functionError(1);

    if(pErrorHandler->HasErrors())
    {
        value2 = 3;
    }

    functionCaller();

    if(pErrorHandler->HasErrors())
    {
        value2 = 5;
    }

    functionException();*/
    throw;
	return 0;
}
/*catch(...)
{
}*/

