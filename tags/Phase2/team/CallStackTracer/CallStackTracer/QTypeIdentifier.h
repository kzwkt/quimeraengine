
#ifndef __QTYPEIDENTIFIER__
#define __QTYPEIDENTIFIER__

#include <string>
#include <sstream>
#include "BaseClass.h"

class QTypeIdentifier
{
public:

    template<class T>
    explicit QTypeIdentifier(T v)
    {
        this->FillValues(v);
    }

    bool Internal(BaseClass* v)
    {
        m_pName = v->GetType();
        std::ostringstream st;
        st << v->ToString();
        m_strValue = st.str();
        return true;
    }

    bool Internal(void* v)
    {
        return false;
    }

private:

    template<class T>
    void FillValues(T v)
    {
        m_pName = "Unknown";
        std::ostringstream st;
        st << &v;
        m_strValue = st.str();
    }

    template<class T>
    void FillValues(T* v)
    {
        if(!Internal(v))
        {
            m_pName = "Pointer";
            std::ostringstream st;
            st << v;
            m_strValue = st.str();
        }
    }

public:

    std::string m_pName;
    std::string m_strValue;
};

template<>
void QTypeIdentifier::FillValues<int>(int v)
{
    m_pName = "int";
    std::ostringstream st;
    st << v;
    m_strValue = st.str();
}

template<>
void QTypeIdentifier::FillValues<float>(float v)
{
    m_pName = "float";
    std::ostringstream st;
    st << v;
    m_strValue = st.str();
}

template<>
void QTypeIdentifier::FillValues<double>(double v)
{
    m_pName = "double";
    std::ostringstream st;
    st << v;
    m_strValue = st.str();
}

template<>
void QTypeIdentifier::FillValues<char>(char v)
{
    m_pName = "char";
    std::ostringstream st;
    st << v;
    m_strValue = st.str();
}
/*
#include "BaseClass.h"

template<>
void QTypeIdentifier::FillValues<BaseClass>(BaseClass* v)
{
    m_pName = v->GetType();
    std::ostringstream st;
    st << v->ToString();
    m_strValue = st.str();
}
*/
template<>
void QTypeIdentifier::FillValues<void>(void* v)
{
    m_pName = "void*";
    std::ostringstream st;
    st << v;
    m_strValue = st.str();
}

/*
template<class T>
class QTypeIdentifierTemplate : public QTypeIdentifier
{
};

template<>
class QTypeIdentifierTemplate<int> : public QTypeIdentifier
{
public:

    QTypeIdentifierTemplate(int value) : QTypeIdentifier("int")
    {
    }
};

template<>
class QTypeIdentifierTemplate<float> : public QTypeIdentifier
{
public:

    QTypeIdentifierTemplate(int value) : QTypeIdentifier("float")
    {
    }
};

template<>
class QTypeIdentifierTemplate<double> : public QTypeIdentifier
{
public:

    QTypeIdentifierTemplate(int value) : QTypeIdentifier("double")
    {
    }
};

template<>
class QTypeIdentifierTemplate<char> : public QTypeIdentifier
{
public:

    QTypeIdentifierTemplate(int value) : QTypeIdentifier("char")
    {
    }
};*/

#endif // __QTYPEIDENTIFIER__