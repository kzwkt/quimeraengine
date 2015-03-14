// RTTI.cpp : Defines the entry point for the console application.
//
// Added As(), now TYPE is got directly without any static method and the counter is deactivated


#include "stdafx.h"
#include <string>



class DataType
{
public:

    DataType(const std::string &strName) : m_strName(strName)
    {
        //m_nTypeId = sm_nTypeIdCounter++;
    }

    const std::string& GetName() const
    {
        return m_strName;
    }
    /*
    bool operator==(const DataType &otherType) const
    {
        return otherType.m_nTypeId == m_nTypeId;
    }

    bool operator!=(const DataType &otherType) const
    {
        return otherType.m_nTypeId != m_nTypeId;
    }
    */
private:

    //static int sm_nTypeIdCounter;
    //int m_nTypeId;
    std::string m_strName;
};

//int DataType::sm_nTypeIdCounter = 0;


class QObject
{
protected:

    virtual bool IsDerivedInternal(const DataType*) const=0;

public:

    virtual const DataType* GetType() const=0;

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

   // static const DataType* GetTypeInternal()
   // {
        static const DataType* TYPE;
   //     return &TYPE;
   // }

    virtual const DataType* GetType() const
    {
        return RootClass::TYPE;
    }

    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::TYPE);
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        return dt == RootClass::TYPE;
    }

};

const DataType* RootClass::TYPE = new DataType("RootClass");


class DerivedClassLvl1 : public RootClass
{
public:

    void VirtualMethod()
    {
    }

    //static const DataType* GetTypeInternal()
    //{
        static const DataType* TYPE;
    //    return &TYPE;
    //}

    virtual const DataType* GetType() const
    {
        return DerivedClassLvl1::TYPE;
    }

    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        if(dt == DerivedClassLvl1::TYPE)
            return true;
        else
            return RootClass::IsDerivedInternal(dt);
    }
};

const DataType* DerivedClassLvl1::TYPE = new DataType("DerivedClassLvl1");



class OtherDerivedClassLvl1 : public RootClass
{
public:

    //static const DataType* GetTypeInternal()
    //{

        static const DataType* TYPE;
    //    return &TYPE;
    //}

    virtual const DataType* GetType() const
    {
        return OtherDerivedClassLvl1::TYPE;
    }

    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        if(dt == OtherDerivedClassLvl1::TYPE)
            return true;
        else
            return RootClass::IsDerivedInternal(dt);
    }
};

const DataType* OtherDerivedClassLvl1::TYPE = new DataType("OtherDerivedClassLvl1");



class DerivedClassLvl2 : public DerivedClassLvl1
{
public:

   // static const DataType* GetTypeInternal()
   // {
        static const DataType* TYPE;
   //     return &TYPE;
   // }

    virtual const DataType* GetType() const
    {
        return DerivedClassLvl2::TYPE;
    }
    
    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        if(dt == DerivedClassLvl2::TYPE)
            return true;
        else
            return DerivedClassLvl1::IsDerivedInternal(dt);
    }
};

const DataType* DerivedClassLvl2::TYPE = new DataType("DerivedClassLvl2");



void Function1(RootClass* r)
{
    bool bResult = r->IsDerived<DerivedClassLvl1>();
}

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


int main(int argc, char* argv[])
{
    QObject* r = new OtherDerivedClassLvl1();

    r->As<DerivedClassLvl2>();

    StartCounter();

    for(unsigned int i = 0; i < unsigned int(-1); i++)
        //DerivedClassLvl2* p = dynamic_cast<DerivedClassLvl2*>(r);
        DerivedClassLvl2* p = r->As<DerivedClassLvl2>();

    std::cout << GetCounter() <<"\n";
    // 12500
    // 48322
    // 91281
    std::system("pause");

    //Function1(r);
	return 0;
}