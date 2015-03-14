// SpeedTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

class TestClass
{
public:

    float x, y, z;

    TestClass() : x(0), y(0), z(0)
    {
    }

    TestClass(float xx, float yy, float zz) : x(xx), y(yy), z(zz)
    {
    }

    inline void Test1(const TestClass& testObj)
    {
        x = this->y * testObj.z - this->z * testObj.y;
        y = this->z * testObj.x - this->x * testObj.z;
        z = this->x * testObj.y - this->y * testObj.x;
    }

    inline TestClass Test2(const TestClass& testObj)
    {
        return TestClass(
            this->y * testObj.z - this->z * testObj.y,
            this->z * testObj.x - this->x * testObj.z,
            this->x * testObj.y - this->y * testObj.x);
    }

    inline void Test3(const TestClass& testObj, TestClass& output)
    {
        output.x = this->y * testObj.z - this->z * testObj.y;
        output.y = this->z * testObj.x - this->x * testObj.z;
        output.z = this->x * testObj.y - this->y * testObj.x;
    }

    inline void Test4(const TestClass& testObj)
    {
        TestClass aux(testObj);
        x = this->y * aux.z - this->z * aux.y;
        y = this->z * aux.x - this->x * aux.z;
        z = this->x * aux.y - this->y * aux.x;
    }

    inline void Test5(const TestClass testObj)
    {
        x = this->y * testObj.z - this->z * testObj.y;
        y = this->z * testObj.x - this->x * testObj.z;
        z = this->x * testObj.y - this->y * testObj.x;
    }

    inline void Test6(const TestClass& testObj, TestClass& output)
    {
        output = *this;
        output.Test1(testObj);
    }

    inline void Test7(const TestClass* testObj, TestClass* output)
    {
        output->x = this->y * testObj->z - this->z * testObj->y;
        output->y = this->z * testObj->x - this->x * testObj->z;
        output->z = this->x * testObj->y - this->y * testObj->x;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    TestClass obj1(4, 5, 6);
    TestClass obj2(1, 2, 3);
    TestClass obj3;

    obj1.Test1(obj2);
    obj1 = obj1.Test2(obj2);
    obj1.Test3(obj2, obj3);

    const long long LOOP_COUNT_MAX = 5000000ll;

    std::cout << sizeof(long long) << "\n";

    while(true)
    {

    LARGE_INTEGER lA;
    LARGE_INTEGER lB;
    QueryPerformanceCounter(&lA);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        obj1.Test1(obj2);
    }
    //18446744073709551616
    QueryPerformanceCounter(&lB);

    std::cout << (lB.HighPart - lA.HighPart) << (lB.LowPart - lA.LowPart) << "\n";

    LARGE_INTEGER l2A;
    LARGE_INTEGER l2B;
    QueryPerformanceCounter(&l2A);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        obj3 = obj1.Test2(obj2);
    }

    QueryPerformanceCounter(&l2B);

    std::cout << (l2B.HighPart - l2A.HighPart) << (l2B.LowPart - l2A.LowPart) << "\n";

    LARGE_INTEGER l3A;
    LARGE_INTEGER l3B;
    QueryPerformanceCounter(&l3A);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        obj1.Test3(obj2, obj3);
    }

    QueryPerformanceCounter(&l3B);

    std::cout << (l3B.HighPart - l3A.HighPart) << (l3B.LowPart - l3A.LowPart) << "\n";

    LARGE_INTEGER l4A;
    LARGE_INTEGER l4B;
    QueryPerformanceCounter(&l4A);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        obj1.Test4(obj2);
    }

    QueryPerformanceCounter(&l4B);

    std::cout << (l4B.HighPart - l4A.HighPart) << (l4B.LowPart - l4A.LowPart) << "\n";

    LARGE_INTEGER l5A;
    LARGE_INTEGER l5B;
    QueryPerformanceCounter(&l5A);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        obj1.Test5(obj2);
    }

    QueryPerformanceCounter(&l5B);

    std::cout << (l5B.HighPart - l5A.HighPart) << (l5B.LowPart - l5A.LowPart) << "\n";

    LARGE_INTEGER l6A;
    LARGE_INTEGER l6B;
    QueryPerformanceCounter(&l6A);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        obj1.Test6(obj2, obj3);
    }

    QueryPerformanceCounter(&l6B);

    std::cout << (l6B.HighPart - l6A.HighPart) << (l6B.LowPart - l6A.LowPart) << "\n";

    LARGE_INTEGER l7A;
    LARGE_INTEGER l7B;
    QueryPerformanceCounter(&l7A);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        TestClass& obj = obj1.Test2(obj2);
    }

    QueryPerformanceCounter(&l7B);

    std::cout << (l7B.HighPart - l7A.HighPart) << (l7B.LowPart - l7A.LowPart) << "\n";

    LARGE_INTEGER l8A;
    LARGE_INTEGER l8B;
    QueryPerformanceCounter(&l8A);

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        TestClass obj = obj1.Test2(obj2);
    }

    QueryPerformanceCounter(&l8B);

    std::cout << (l8B.HighPart - l8A.HighPart) << (l8B.LowPart - l8A.LowPart) << "\n";

    LARGE_INTEGER l9A;
    LARGE_INTEGER l9B;
    QueryPerformanceCounter(&l9A);

    TestClass* pObj1 = new TestClass(), *pObj2 = new TestClass();

    for(long long i = 0ll; i < LOOP_COUNT_MAX; ++i)
    {
        obj1.Test7(pObj1, pObj2);
    }

    QueryPerformanceCounter(&l9B);

    std::cout << (l9B.HighPart - l9A.HighPart) << (l9B.LowPart - l9A.LowPart) << "\n";

    std::system("pause");

    }

	return 0;
}

