// MultithreadingSynchronization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Poco/Condition.h"
#include "Poco/Activity.h"

class SynchronizedClass
{
public:

    // Activity's default constructor is private, so it must be initialized immediately
    SynchronizedClass() : _activity1(this, &SynchronizedClass::Thread1Method),
                          _activity2(this, &SynchronizedClass::Thread2Method)
    {
    }

    // Stops all threads inside
    ~SynchronizedClass()
    {
        if(_activity1.isRunning())
        {
            _activity1.stop();
            _activity1.wait();
        }
        if(_activity2.isRunning())
        {
            _activity2.stop();
            _activity2.wait();
        }
    }

    // Calls Thread1Method
    void ExecuteThread1()
    {
        if(_activity1.isStopped())
            _activity1.start();
    }

    // Calls Thread2Method
    void ExecuteThread2()
    {
        if(_activity2.isStopped())
            _activity2.start();
    }

    // Waits until all threads stop
    void Wait()
    {
        _activity1.wait();
        _activity2.wait();
    }

    // A flag used in this example to increase the probabilities that the wait method is called before sygnal method
    // Note that this is not a good way to assure that occurs
    static bool s_bThread1IsWaiting;

protected:

    // A shared condition that tells waiting threads when do they can continue working
    static Poco::Condition s_condition;

    void Thread1Method()
    {
        ::OutputDebugStringW(L"Init Thread 1\n");

        Poco::Mutex mutex;
        SynchronizedClass::s_bThread1IsWaiting = true;

        // Thread1 waits for the mutex to be released by another thread sygnal
        SynchronizedClass::s_condition.wait(mutex);

        ::OutputDebugStringW(L"Final Thread 1\n");
    }

    void Thread2Method()
    {
        ::OutputDebugStringW(L"Init Thread 2\n");

        for(unsigned int i = 0; i < 500; i++)
        {
            ::OutputDebugStringW(L"* Does something while Thread1 waits ");
        }

        // The last locked mutex is now unlocked
        SynchronizedClass::s_condition.signal();

        ::OutputDebugStringW(L"Final Thread 2\n");
    }

    // Thread encapsulations
    Poco::Activity<SynchronizedClass> _activity1;
    Poco::Activity<SynchronizedClass> _activity2;

};

Poco::Condition SynchronizedClass::s_condition;

bool SynchronizedClass::s_bThread1IsWaiting = false;


int _tmain(int argc, _TCHAR* argv[])
{
    SynchronizedClass syncObject;

    syncObject.ExecuteThread1();
    syncObject.ExecuteThread2();

    syncObject.Wait();

	return 0;
}

