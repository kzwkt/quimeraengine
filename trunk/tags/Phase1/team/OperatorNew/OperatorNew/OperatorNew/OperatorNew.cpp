// OperatorNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include "..\NewInDll\NewInDll.h"

#include <vector>
#include "..\NewInDll2\Heap.h"
#include "..\NewInDll\heap2.h"

class ccc
{
public:

    ccc()
    {

    }

    ~ccc()
    {
    }

    ccc(const ccc &c)
    {
        
    }

    ccc& operator=(const ccc &c)
    {
        return *this;
    }

    void* operator new(const size_t s)
    {
        return malloc(s);
    }

    void operator delete(void* p)
    {
        free(p);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    delete Heap::GetMemory();
    int i3 = *Heap2::GetMemory();
    int i2 = *Heap::GetMemory();
    //ccc* x = new ccc();
    int* i = new int();
    delete i;
    /*
    std::vector<ccc> v(10);
    v.pop_back();*/

	return 0;
}

