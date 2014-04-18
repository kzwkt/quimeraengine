// DelegatesAndEvents.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/function.hpp>

class TestClassBase
{
public:

    virtual int TestMethod(int i)
    {
        return 5;
    }
};


class TestClass : public TestClassBase
{
public:
    TestClass(int i)
    {
        x = i;
    }

    int x;

    int TestMethod(int i)
    {
        return 6;
    }
};

template<class T>
class QDelegate
{
};


int _tmain(int argc, _TCHAR* argv[])
{
    TestClassBase t = TestClass(9);
    boost::function<int (int)> f = std::bind1st(std::mem_fun(&TestClassBase::TestMethod), &t);
    f(2);
    //f(&t, 2);

    //pFunction(0);
    // QDelegate<int()(int)> delegate = &t.TestMethod;
	return 0;
}

