// MultithreadingEncapsulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// --------------- Singleton Declaration --------------------

class Singleton
{
private:

    Singleton(){}
    virtual ~Singleton(){}

    Singleton& operator=(const Singleton &singleton){}
    Singleton(const Singleton &singleton){}

public:

    static volatile Singleton* Get();

    void DoSomethingConcurrently()
    {
        // Mutex
    }

private:

    static volatile Singleton* s_pInstance;
};


volatile Singleton* Singleton::s_pInstance = 0;

volatile Singleton* Singleton::Get()
{
    if(!s_pInstance)
        s_pInstance = new Singleton();

    return s_pInstance;
}

// ---------------------- Global Functions To Run In Other Threads -----------------------

void func1()
{
    Singleton::Get()->DoSomethingConcurrently();
}

void funct2()
{
    Singleton::Get()->DoSomethingConcurrently();
}


// ------------------------ Main -----------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
    
}

