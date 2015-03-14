// RTTI.cpp : Defines the entry point for the console application.
//

// This implementation is fast, no virtual functions but cannot detect inheritance downwards the type of the pointer used


#include "stdafx.h"
#include <string>


class DataType
{
public:

    DataType(const std::string &strName) : m_strName(strName)
    {
        m_nTypeId = sm_nTypeIdCounter++;
    }

    const std::string& GetName() const
    {
        return m_strName;
    }

    bool operator==(const DataType &otherType) const
    {
        return otherType.m_nTypeId == m_nTypeId;
    }

    bool operator!=(const DataType &otherType) const
    {
        return otherType.m_nTypeId != m_nTypeId;
    }

private:

    static int sm_nTypeIdCounter;
    int m_nTypeId;
    std::string m_strName;
};

int DataType::sm_nTypeIdCounter = 0;



class RootClass
{
public:

    virtual void VirtualMethod()=0;

    static const DataType& GetTypeInternal()
    {
        static const DataType TYPE("RootClass");
        return TYPE;
    }

    const DataType& GetType() const
    {
        return RootClass::GetTypeInternal();
    }

    template<class T>
    bool IsDerived() const
    {
        return T::GetTypeInternal() == RootClass::GetTypeInternal();
    }

};

class DerivedClassLvl1 : public RootClass
{
public:

    void VirtualMethod()
    {
    }

    static const DataType& GetTypeInternal()
    {
        static const DataType TYPE("DerivedClassLvl1");
        return TYPE;
    }

    const DataType& GetType() const
    {
        return DerivedClassLvl1::GetTypeInternal();
    }

    template<class T>
    bool IsDerived() const
    {
        if(T::GetTypeInternal() == DerivedClassLvl1::GetTypeInternal())
            return true;
        else
            return RootClass::IsDerived<T>();
    }
};

class OtherDerivedClassLvl1 : public RootClass
{
public:

    static const DataType& GetTypeInternal()
    {
        static const DataType TYPE("OtherDerivedClassLvl1");
        return TYPE;
    }

    const DataType& GetType() const
    {
        return OtherDerivedClassLvl1::GetTypeInternal();
    }

    template<class T>
    bool IsDerived() const
    {
        if(T::GetTypeInternal() == OtherDerivedClassLvl1::GetTypeInternal())
            return true;
        else
            return RootClass::IsDerived<T>();
    }
};

class DerivedClassLvl2 : public DerivedClassLvl1
{
public:

    static const DataType& GetTypeInternal()
    {
        static const DataType TYPE("DerivedClassLvl2");
        return TYPE;
    }

    const DataType& GetType() const
    {
        return DerivedClassLvl2::GetTypeInternal();
    }

    template<class T>
    bool IsDerived() const
    {
        if(T::GetTypeInternal() == DerivedClassLvl2::GetTypeInternal())
            return true;
        else
            return DerivedClassLvl1::IsDerived<T>();
    }
};


void Function1(RootClass* r)
{
    // bResult SHOULD be true since input type is actually DerivedClassLvl2 which derives from DerivedClassLvl1
    // but since RootClass in an upper position in the hierarchy, it does not work
    bool bResult = r->IsDerived<DerivedClassLvl1>();
    DerivedClassLvl1* d = dynamic_cast<DerivedClassLvl1*>(r);
}

int main(int argc, char* argv[])
{
    RootClass* r = new DerivedClassLvl2();
    Function1(r);
	return 0;
}