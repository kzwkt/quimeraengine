// RTTI.cpp : Defines the entry point for the console application.
//
// Macros to speed up code writting
// Multi-inheritance is also supported in macros


#include "stdafx.h"
#include <string>


#define RTTI_SUPPORT_ROOT(className)                            \
    static const DataType* TYPE;                                \
                                                                \
    virtual const DataType* GetType() const                     \
    {                                                           \
        return className::TYPE;                                 \
    }                                                           \
                                                                \
    template<class T>                                           \
    bool IsDerived() const                                      \
    {                                                           \
        return this->IsDerivedInternal(T::TYPE);                \
    }                                                           \
                                                                \
    virtual bool IsDerivedInternal(const DataType* dt) const    \
    {                                                           \
        return dt == className::TYPE;                           \
    }

#define RTTI_SUPPORT_1_BASE_CLASS(className, baseClassName)          \
    static const DataType* TYPE;                                \
                                                                \
    virtual const DataType* GetType() const                     \
    {                                                           \
        return className::TYPE;                                 \
    }                                                           \
                                                                \
    virtual bool IsDerivedInternal(const DataType* dt) const    \
    {                                                           \
        if(dt == className::TYPE)                               \
            return true;                                        \
        else                                                    \
            return baseClassName::IsDerivedInternal(dt);        \
    }

#define RTTI_SUPPORT_2_BASE_CLASSES(className, baseClassName1, baseClassName2)          \
    static const DataType* TYPE;                                \
                                                                \
    virtual const DataType* GetType() const                     \
    {                                                           \
        return className::TYPE;                                 \
    }                                                           \
                                                                \
    virtual bool IsDerivedInternal(const DataType* dt) const    \
    {                                                           \
        return dt == className::TYPE ||                               \
               baseClassName1::IsDerivedInternal(dt) ||        \
               baseClassName2::IsDerivedInternal(dt);           \
    }

#define RTTI_SUPPORT_3_BASE_CLASSES(className, baseClassName1, baseClassName2, baseClassName3)          \
    static const DataType* TYPE;                                \
                                                                \
    virtual const DataType* GetType() const                     \
    {                                                           \
        return className::TYPE;                                 \
    }                                                           \
                                                                \
    virtual bool IsDerivedInternal(const DataType* dt) const    \
    {                                                           \
        return dt == className::TYPE ||                               \
               baseClassName1::IsDerivedInternal(dt) ||        \
               baseClassName2::IsDerivedInternal(dt) ||         \
               baseClassName3::IsDerivedInternal(dt) ||;           \
    }

#define RTTI_SUPPORT_4_BASE_CLASSES(className, baseClassName1, baseClassName2, baseClassName3, baseClassName4)          \
    static const DataType* TYPE;                                \
                                                                \
    virtual const DataType* GetType() const                     \
    {                                                           \
        return className::TYPE;                                 \
    }                                                           \
                                                                \
    virtual bool IsDerivedInternal(const DataType* dt) const    \
    {                                                           \
        return dt == className::TYPE ||                               \
               baseClassName1::IsDerivedInternal(dt) ||        \
               baseClassName2::IsDerivedInternal(dt) ||         \
               baseClassName3::IsDerivedInternal(dt) ||           \
               baseClassName4::IsDerivedInternal(dt);           \
    }

#define RTTI_SUPPORT_CPP(className)                             \
    const DataType* className::TYPE = new DataType(#className);


class DataType
{
public:

    DataType(const std::string &strName) : m_strName(strName)
    {
    }

    const std::string& GetName() const
    {
        return m_strName;
    }

private:

    std::string m_strName;
};


class QObject
{
protected:

    virtual bool IsDerivedInternal(const DataType*) const=0;

public:

    virtual const DataType* GetType() const=0;
    
    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    template<class T>
    T* As()
    {
        return this->IsDerivedInternal(T::TYPE) ? 
                          static_cast<T*>(this) : 
                                           NULL ;
    }

    template<class T>
    const T* As() const
    {
        return this->IsDerivedInternal(T::TYPE) ? 
                    static_cast<const T*>(this) : 
                                           NULL ;
    }
};

class RootClass : public QObject
{
public:

    RTTI_SUPPORT_ROOT(RootClass)
};

RTTI_SUPPORT_CPP(RootClass)


class DerivedClassLvl1 : public RootClass
{
public:

    void VirtualMethod()
    {
    }

    RTTI_SUPPORT_1_BASE_CLASS(DerivedClassLvl1, RootClass)
};

RTTI_SUPPORT_CPP(DerivedClassLvl1)

    
class Interface : public QObject
{
public:

   RTTI_SUPPORT_ROOT(Interface)
};

RTTI_SUPPORT_CPP(Interface)


class OtherDerivedClassLvl1 : public RootClass, public Interface
{
public:

    RTTI_SUPPORT_2_BASE_CLASSES(OtherDerivedClassLvl1, RootClass, Interface)
};

RTTI_SUPPORT_CPP(OtherDerivedClassLvl1)



class DerivedClassLvl2 : public DerivedClassLvl1
{
public:

   RTTI_SUPPORT_1_BASE_CLASS(DerivedClassLvl2, DerivedClassLvl1)
};

RTTI_SUPPORT_CPP(DerivedClassLvl2)

    




#include <windows.h>
#include <iostream>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
	std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}


void Function1(RootClass* r)
{
    StartCounter();

    for(unsigned int i = 0; i < unsigned int(-1); i++)
        Interface* p = dynamic_cast<Interface*>(r);
        //Interface* p = r->As<Interface>();

    std::cout << GetCounter() <<"\n";
}

int main(int argc, char* argv[])
{
    RootClass* r = new OtherDerivedClassLvl1();

    //r->As<DerivedClassLvl2>();

    //std::cout << r->As<DerivedClassLvl2>()->GetType()->GetName() <<"\n";
    char x[3];
    std::cin >> x;
    Interface* p = r->As<Interface>();
    if(x[0] == 'y')
    {
        Function1(new OtherDerivedClassLvl1());
    }
    else
    {
        Function1(new DerivedClassLvl1());
    }
    
    // 12500
    // 48322
    // 91281
    std::system("pause");

    //Function1(r);
	return 0;
}