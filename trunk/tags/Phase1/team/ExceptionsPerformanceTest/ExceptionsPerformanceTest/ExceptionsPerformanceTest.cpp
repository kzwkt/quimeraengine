// PruebasExcepciones.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#ifdef WIN32

#include <sys/timeb.h>

#endif

class ClassWithDestructor
{
public:

    static bool DestructorCalled;

    ~ClassWithDestructor()
    {
        ClassWithDestructor::DestructorCalled = true;
    }
};

bool ClassWithDestructor::DestructorCalled = false;


unsigned long GetMillisecondsNow()
{
#ifdef WIN32
	__timeb32 TB;
	_ftime32_s(&TB);
	
	return (unsigned long)(TB.time * (unsigned long)1000 + (unsigned long)TB.millitm);
#else
	return -1;
#endif
}

#define WITH_EXCEPTIONS

void funcThrowException()
{
    ClassWithDestructor thisObjectDestructorShouldBeCalled;
    #ifdef WITH_EXCEPTIONS
        throw int();
    #endif
    return;
}

int funcReturnCode()
{
    ClassWithDestructor thisObjectDestructorShouldBeCalled;
    return 0;
}

void funcDoesntThrowException()
{
    ClassWithDestructor thisObjectDestructorShouldBeCalled;
    return;
}

void funcWithExceptionsNotThrown()
{
    ClassWithDestructor thisObjectDestructorShouldBeCalled;
    #ifdef WITH_EXCEPTIONS
        if(false)
            throw int();
    #endif
    return;
}

void funcWithUnexpectedExcention()
{
    ClassWithDestructor thisObjectDestructorShouldBeCalled;
    int j = 0;
    int i = 1 / j;
    return;
}

int _tmain(int argc, _TCHAR* argv[])
{
    unsigned long milliseconds = 0;

    milliseconds = GetMillisecondsNow();
    for(unsigned int i = 0; i < 1000000000; ++i)
    {
        funcDoesntThrowException();
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcDoesntThrowException:" << milliseconds << "\n";

    //----------------------------------------------------------------------------------------------------------------

    milliseconds = GetMillisecondsNow();
    
    for(unsigned int i = 0; i < 1000000000; ++i)
    {
        funcReturnCode();
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcReturnCode:" << milliseconds << "\n";

    //----------------------------------------------------------------------------------------------------------------

    milliseconds = GetMillisecondsNow();

    bool bExecuted = false;
    ClassWithDestructor::DestructorCalled = false;

    for(unsigned int i = 0; i < 10000; ++i)
    {
        #ifdef WITH_EXCEPTIONS
            try
            {
        #endif
                funcThrowException();
        #ifdef WITH_EXCEPTIONS
            }
            catch(int)
            {
                bExecuted = true;
            }
        #endif
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcThrowException (catch specific):" << milliseconds << " x 100000\n";

    if(bExecuted)
        std::cout << "** Catch executed **\n";

    if(ClassWithDestructor::DestructorCalled)
        std::cout << "** Destructor Called **\n";

    //----------------------------------------------------------------------------------------------------------------

    milliseconds = GetMillisecondsNow();

    bExecuted = false;
    ClassWithDestructor::DestructorCalled = false;

    for(unsigned int i = 0; i < 1000000000; ++i)
    {
        #ifdef WITH_EXCEPTIONS
            try
            {
        #endif
                funcWithExceptionsNotThrown();
        #ifdef WITH_EXCEPTIONS
            }
            catch(int)
            {
                bExecuted = true;
            }
        #endif

    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcWithExceptionsNotThrown (catch specific):" << milliseconds << "\n";

    if(bExecuted)
        std::cout << "** Catch executed **\n";

    if(ClassWithDestructor::DestructorCalled)
        std::cout << "** Destructor Called **\n";

    //----------------------------------------------------------------------------------------------------------------

    milliseconds = GetMillisecondsNow();

    bExecuted = false;
    ClassWithDestructor::DestructorCalled = false;

    for(unsigned int i = 0; i < 10000; ++i)
    {
        #ifdef WITH_EXCEPTIONS
            try
            {
        #endif
                funcThrowException();
        #ifdef WITH_EXCEPTIONS
            }
            catch(...)
            {
                bExecuted = true;
            }
        #endif
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcThrowException (catch all):" << milliseconds << " x 100000\n";

    if(bExecuted)
        std::cout << "** Catch executed **\n";

    if(ClassWithDestructor::DestructorCalled)
        std::cout << "** Destructor Called **\n";

    //----------------------------------------------------------------------------------------------------------------

    milliseconds = GetMillisecondsNow();

    bExecuted = false;
    ClassWithDestructor::DestructorCalled = false;

    for(unsigned int i = 0; i < 1000000000; ++i)
    {
        #ifdef WITH_EXCEPTIONS
            try
            {
        #endif
                funcWithExceptionsNotThrown();
        #ifdef WITH_EXCEPTIONS
            }
            catch(...)
            {
                bExecuted = true;
            }
        #endif

    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcWithExceptionsNotThrown (catch all):" << milliseconds << "\n";

    if(bExecuted)
        std::cout << "** Catch executed **\n";

    if(ClassWithDestructor::DestructorCalled)
        std::cout << "** Destructor Called **\n";

    //----------------------------------------------------------------------------------------------------------------

    milliseconds = GetMillisecondsNow();

    bExecuted = false;
    ClassWithDestructor::DestructorCalled = false;

    for(unsigned int i = 0; i < 10000; ++i)
    {
        #ifdef WITH_EXCEPTIONS
            try
            {
        #endif
                funcWithUnexpectedExcention();
        #ifdef WITH_EXCEPTIONS
            }
            catch(...)
            {
                bExecuted = true;
            }
        #endif
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcWithUnexpectedExcention (catch all):" << milliseconds << " x 100000\n";

    if(bExecuted)
        std::cout << "** Catch executed **\n";

    if(ClassWithDestructor::DestructorCalled)
        std::cout << "** Destructor Called **\n";

    std::system("pause");

	return 0;
}

