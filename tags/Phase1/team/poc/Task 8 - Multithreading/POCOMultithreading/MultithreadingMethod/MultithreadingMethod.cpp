// MultithreadingMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Poco/ThreadPool.h"
#include "Poco/Activity.h"

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
        Poco::Mutex mutex;
        Poco::Mutex::ScopedLock lock(mutex);

        if(!s_pInstance)
            s_pInstance = new Singleton();
    }

    return const_cast<Singleton*>(s_pInstance);
}

// ---------------------- Class Whose Methods Run In Other Threads -----------------------

class ExampleClass
{
public:

    // Activity's default constructor is private, so it must be initialized immediately
    ExampleClass() : _activity1(this, &ExampleClass::RunnableMethod1),
                     _activity2(this, &ExampleClass::RunnableMethod2)
    {
    }

    void RunnableMethod1_InOtherThread()
    {
        // Calls RunnableMethod1 in another thread
        _activity1.start();
    }

    void RunnableMethod2_InOtherThread()
    {
        // Calls RunnableMethod2 in another thread
        _activity2.start();
    }

    void StopOtherThreads()
    {
        // Stops all threads
        _activity1.stop();
        _activity2.stop();

        // Waits until threads are stopped
        _activity1.wait();
        _activity2.wait();
    }

protected:

    // Method to be called by another thread
    void RunnableMethod1()
    {
        Singleton::Get()->DoSomethingConcurrently();
    }

    // Method to be called by another thread
    void RunnableMethod2()
    {
        Singleton::Get()->DoSomethingConcurrently();
    }

    // Method encapsulations
    Poco::Activity<ExampleClass> _activity1;
    Poco::Activity<ExampleClass> _activity2;
};

// ------------------------ Main -----------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
    ExampleClass sample;

    sample.RunnableMethod1_InOtherThread();
    sample.RunnableMethod2_InOtherThread();

    sample.StopOtherThreads();
}

