// PruebasExcepciones.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#ifdef WIN32

#include <sys/timeb.h>

#endif

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
    #ifdef WITH_EXCEPTIONS
        throw int();
    #endif
}

int funcReturnCode()
{
    return 0;
}

void funcDoesntThrowException()
{
    return;
}

void funcWithExceptionsNotThrown()
{
    #ifdef WITH_EXCEPTIONS
        if(false)
            throw int();
    #endif
}

int _tmain(int argc, _TCHAR* argv[])
{
    unsigned long milliseconds = 0;

    milliseconds = GetMillisecondsNow();
    for(unsigned int i = 0; i < 10000000; ++i)
    {
        funcDoesntThrowException();
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcDoesntThrowException:" << milliseconds << "\n";

    milliseconds = GetMillisecondsNow();
    
    for(unsigned int i = 0; i < 10000000; ++i)
    {
        funcReturnCode();
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcReturnCode:" << milliseconds << "\n";

    milliseconds = GetMillisecondsNow();

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
            
            }
        #endif
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcThrowException (catch specific):" << milliseconds << " x 1000\n";

    milliseconds = GetMillisecondsNow();

    for(unsigned int i = 0; i < 10000000; ++i)
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
            
            }
        #endif

    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcWithExceptionsNotThrown (catch specific):" << milliseconds << "\n";

    milliseconds = GetMillisecondsNow();

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
            
            }
        #endif
    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcThrowException (catch all):" << milliseconds << " x 1000\n";

    milliseconds = GetMillisecondsNow();

    for(unsigned int i = 0; i < 10000000; ++i)
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
            
            }
        #endif

    }

    milliseconds = GetMillisecondsNow() - milliseconds;
    
    std::cout << "funcWithExceptionsNotThrown (catch all):" << milliseconds << "\n";

    std::system("pause");

	return 0;
}

