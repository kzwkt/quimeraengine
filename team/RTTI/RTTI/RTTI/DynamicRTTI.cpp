// RTTI.cpp : Defines the entry point for the console application.
//
// This implementation works perfectly, not needing either dynamic_cast nor typeid, but it uses virtual methods


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


class QObject
{
protected:

    virtual bool IsDerivedInternal(const DataType*) const=0;

public:

    virtual const DataType* GetType() const=0;
};

class RootClass : public QObject
{
public:

    virtual void VirtualMethod()=0;

    static const DataType* GetTypeInternal()
    {
        static const DataType TYPE("RootClass");
        return &TYPE;
    }

    virtual const DataType* GetType() const
    {
        return RootClass::GetTypeInternal();
    }

    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        return dt == RootClass::GetTypeInternal();
    }

};

class DerivedClassLvl1 : public RootClass
{
public:

    void VirtualMethod()
    {
    }

    static const DataType* GetTypeInternal()
    {
        static const DataType TYPE("DerivedClassLvl1");
        return &TYPE;
    }

    virtual const DataType* GetType() const
    {
        return DerivedClassLvl1::GetTypeInternal();
    }

    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        if(dt == DerivedClassLvl1::GetTypeInternal())
            return true;
        else
            return RootClass::IsDerivedInternal(dt);
    }
};

class OtherDerivedClassLvl1 : public RootClass
{
public:

    static const DataType* GetTypeInternal()
    {
        static const DataType TYPE("OtherDerivedClassLvl1");
        return &TYPE;
    }

    virtual const DataType* GetType() const
    {
        return OtherDerivedClassLvl1::GetTypeInternal();
    }

    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        if(dt == OtherDerivedClassLvl1::GetTypeInternal())
            return true;
        else
            return RootClass::IsDerivedInternal(dt);
    }
};

class DerivedClassLvl2 : public DerivedClassLvl1
{
public:

    static const DataType* GetTypeInternal()
    {
        static const DataType TYPE("DerivedClassLvl2");
        return &TYPE;
    }

    virtual const DataType* GetType() const
    {
        return DerivedClassLvl2::GetTypeInternal();
    }
    
    template<class T>
    bool IsDerived() const
    {
        return this->IsDerivedInternal(T::GetTypeInternal());
    }

    virtual bool IsDerivedInternal(const DataType* dt) const
    {
        if(dt == DerivedClassLvl2::GetTypeInternal())
            return true;
        else
            return DerivedClassLvl1::IsDerivedInternal(dt);
    }
};


void Function1(RootClass* r)
{
    bool bResult = r->IsDerived<DerivedClassLvl1>();
    DerivedClassLvl1* d = dynamic_cast<DerivedClassLvl1*>(r);
}

int main(int argc, char* argv[])
{
    RootClass* r = new DerivedClassLvl2();
    Function1(r);
	return 0;
}