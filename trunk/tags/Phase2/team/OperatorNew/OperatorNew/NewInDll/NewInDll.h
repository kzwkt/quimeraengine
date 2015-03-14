// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the NEWINDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NEWINDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef NEWINDLL_EXPORTS
#define NEWINDLL_API __declspec(dllexport)
#else
#define NEWINDLL_API __declspec(dllimport)
#endif


#ifndef __HEAP__
#define __HEAP__

#include <malloc.h>
#include <new>
#include <iostream>

void* operator new(const size_t uSize)
{
    std::cout << "YEAH";
    return malloc(uSize);
}

void* operator new[](const size_t uSize)
{
    return malloc(uSize);
}

void operator delete(void* p, const std::nothrow_t& nothrow_constant)
{
    return free(p);
}

void operator delete (void* ptr) throw()
{
    return free(ptr);
}

void operator delete[](void* p, const std::nothrow_t& nothrow_constant)
{
    return free(p);
}

#endif