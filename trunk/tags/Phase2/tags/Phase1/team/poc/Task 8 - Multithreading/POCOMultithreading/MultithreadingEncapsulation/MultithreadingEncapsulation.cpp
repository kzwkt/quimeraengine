// MultithreadingEncapsulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Poco/Mutex.h"
#include "Poco/Runnable.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

// --------------- Singleton Declaration --------------------

// A thread-safe Singleton pattern implementation sample
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
        // Declares a mutex (mutual exclusion)
        Poco::Mutex mutex;

        // No other thread will be able to execute the next line until the mutex is unlocked by a previous thread
        mutex.lock();

        ::OutputDebugStringW(L"Something done.\n");

        mutex.unlock();
    }

private:

    static volatile Singleton* s_pInstance;
};


volatile Singleton* Singleton::s_pInstance = 0;

Singleton* Singleton::Get()
{
    if(!s_pInstance)
    {
        // The ScopedLock object locks the mutex until is destroyed due to leaving the variable scope
        Poco::Mutex mutex;
        Poco::Mutex::ScopedLock lock(mutex);

        if(!s_pInstance)
            s_pInstance = new Singleton();
    }

    return const_cast<Singleton*>(s_pInstance);
}

// ---------------------- Global Functions To Run In Other Threads -----------------------

class RunnableFunc1 : public Poco::Runnable
{
    // The method run is called internally when you start the associated thread
    void run()
    {
        Singleton::Get()->DoSomethingConcurrently();
    }
};

class RunnableFunc2 : public Poco::Runnable
{
    // The method run is called internally when you start the associated thread
    void run()
    {
        Singleton::Get()->DoSomethingConcurrently();
    }
};

// ------------------------ Main -----------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
    // Encapsulated functions
    RunnableFunc1 func1;
    RunnableFunc2 func2;
    
    // This creates the data structures, but not runs OS threads
    Poco::Thread* thread = new Poco::Thread();
    Poco::Thread* thread2 = new Poco::Thread();

    // Calls functions in other threads
    thread->start(func1);
    thread2->start(func2);

    // Releases threads usage
    thread->join();
    thread2->join();
}

