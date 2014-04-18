// TestingExceptionSupport.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "..\DllErrorHandling\ThrowingFromDll.h"

void onTerminate()
{
    std::cout << "TERMINATE";
    system("pause");
}

void main()
{
    std::set_terminate(&onTerminate);

    //try
    //{
        ThrowClass e(0);
    /*}
    catch(...)
    {*/
        std::cout << "yeah";
        system("pause");
    /*}*/
	return;
    
}

