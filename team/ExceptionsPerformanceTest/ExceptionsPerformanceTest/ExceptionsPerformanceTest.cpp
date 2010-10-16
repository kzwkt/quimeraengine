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

void funcThrowException()
{
    throw int();
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
    if(false)
        throw int();
}

int _tmain(int argc, _TCHAR* argv[])
{
    unsigned long milliseconds = 0;

    milliseconds = GetMillisecondsNow();
    for(unsigned int i = 0; i < 10000000; ++i)
    {
        funcDoesntThrowException();
    }

    milliseconds -= GetMillisecondsNow();
    
    std::cout << "funcDoesntThrowException:" << milliseconds * -1Ul << "\n";

    milliseconds = GetMillisecondsNow();
    
    for(unsigned int i = 0; i < 10000000; ++i)
    {
        funcReturnCode();
    }

    milliseconds -= GetMillisecondsNow();
    
    std::cout << "funcReturnCode:" << milliseconds * -1Ul << "\n";

    milliseconds = GetMillisecondsNow();

    for(unsigned int i = 0; i < 10000; ++i)
    {

        try
        {
            funcThrowException();
        }
        catch(int)
        {
            
        }

    }

    milliseconds -= GetMillisecondsNow();
    
    std::cout << "funcThrowException (catch specific):" << milliseconds * -1Ul << " x 1000\n";

    milliseconds = GetMillisecondsNow();

    for(unsigned int i = 0; i < 10000000; ++i)
    {

        try
        {
            funcWithExceptionsNotThrown();
        }
        catch(int)
        {
            
        }

    }

    milliseconds -= GetMillisecondsNow();
    
    std::cout << "funcWithExceptionsNotThrown (catch specific):" << milliseconds * -1Ul << "\n";

    milliseconds = GetMillisecondsNow();

    for(unsigned int i = 0; i < 10000; ++i)
    {

        try
        {
            funcThrowException();
        }
        catch(...)
        {
            
        }

    }

    milliseconds -= GetMillisecondsNow();
    
    std::cout << "funcThrowException (catch all):" << milliseconds * -1Ul << " x 1000\n";

    milliseconds = GetMillisecondsNow();

    for(unsigned int i = 0; i < 10000000; ++i)
    {

        try
        {
            funcWithExceptionsNotThrown();
        }
        catch(...)
        {
            
        }

    }

    milliseconds -= GetMillisecondsNow();
    
    std::cout << "funcWithExceptionsNotThrown (catch all):" << milliseconds * -1Ul << "\n";

    std::system("pause");

	return 0;
}

