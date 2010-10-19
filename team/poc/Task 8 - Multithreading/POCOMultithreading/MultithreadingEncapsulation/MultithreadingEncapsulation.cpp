// MultithreadingEncapsulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Poco/ThreadPool.h"
#include "Poco/ScopedLock.h"

// --------------- Singleton Declaration --------------------

class Singleton
{
private:

    Singleton(){}
    virtual ~Singleton(){}

    Singleton& operator=(const Singleton &singleton){}
    Singleton(const Singleton &singleton){}

public:

    static Singleton* Get();

    void DoSomethingConcurrently()
    {
        // Mutex
    }

private:

    static volatile Singleton* s_pInstance;
};


volatile Singleton* Singleton::s_pInstance = 0;

Singleton* Singleton::Get()
{
    Poco::Mutex mutex;
    Poco::Mutex::ScopedLock lock(mutex);

    if(!s_pInstance)
        s_pInstance = new Singleton();

    return const_cast<Singleton*>(s_pInstance);
}

// ---------------------- Global Functions To Run In Other Threads -----------------------

class RunnableFunc1 : public Poco::Runnable
{
    void run()
    {
        Singleton::Get()->DoSomethingConcurrently();
    }
};

class RunnableFunc2 : public Poco::Runnable
{
    void run()
    {
        Singleton::Get()->DoSomethingConcurrently();
    }
};

void func3()
{
}

// ------------------------ Main -----------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
    RunnableFunc1 func1;
    RunnableFunc2 func2;

    Poco::Thread* thread = new Poco::Thread();
    Poco::Thread* thread2 = new Poco::Thread();
    thread->start(func1);
    thread2->start(func2);

    thread->join();
    thread2->join();
}

