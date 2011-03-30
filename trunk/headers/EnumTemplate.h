// [TERMS&CONDITIONS]

#ifndef __EQENUMERATION__
#define __EQENUMERATION__

#include <map>

#include "DataTypesDefinitions.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// [DOC]
/// </summary>
class EQEnumeration
{
    // ENUMERATIONS
    // ---------------
public:

    enum EnumType
    {
        E_<> = QE_ENUMERATION_MIN_VALUE,

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<string_q, EQEnumeration::EnumType> TNameValueMap;
    typedef std::pair<string_q, EQEnumeration::EnumType> TNameValuePair;


	// METHODS
	// ---------------
public:

    inline EQEnumeration(const EQEnumeration::EnumType &eValue) : m_value(eValue) 
    {}

    template<typename IntegerType>
    inline EQEnumeration(const IntegerType &nValue) : m_value(static_cast<const EQEnumeration::EnumType>(nValue))
    {}

    inline EQEnumeration(const string_q &strValueName)
    {
        *this = strValueName;
    }

    template<typename IntegerType>
    inline EQEnumeration& operator=(const IntegerType &nValue)
    {
        m_value = static_cast<const EQEnumeration::EnumType>(nValue);
        return *this;
    }

    inline EQEnumeration& operator=(const string_q &strValueName)
    {
        if(EQEnumeration::sm_mapValueName.find(strValueName) != EQEnumeration::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = EQEnumeration::_NotEnumValue;

        return *this;
    }

    inline EQEnumeration& operator=(const EQEnumeration::EnumType &eValue)
    {
        m_value = eValue;
        return *this;
    }
    
    inline bool operator==(const string_q &strValueName) const
    {
        if(EQEnumeration::sm_mapValueName.find(strValueName) != EQEnumeration::sm_mapValueName.end())
            return m_value == sm_mapValueName[strValueName];
        else
            return false;
    }

    template<typename IntegerType>
    inline bool operator==(const IntegerType &nValue) const
    {
        return m_value == static_cast<const EQEnumeration::EnumType>(nValue);
    }

    bool operator==(const EQEnumeration::EnumType &eValue) const
    {
        return m_value == eValue;
    }

    inline operator EQEnumeration::EnumType() const
    {
        return m_value;
    }

    template<typename IntegerType>
    operator IntegerType() const
    {
        return static_cast<IntegerType>(m_value);
    }

    operator const string_q&() const
    {
        TNameValueMap::iterator itValueName = EQEnumeration::sm_mapValueName.begin();
        TNameValueMap::const_iterator itValueNameEnd = EQEnumeration::sm_mapValueName.end();

        while(itValueName != itValueNameEnd && itValueName->second != m_value)
            ++itValueName;
   
        if(itValueName != itValueNameEnd)
            return itValueName->first;
        else
            return QE_L(""); // [TODO] Thund: Esto debe cambiarse por una constante de QString.
    }


    // ATTRIBUTES
	// ---------------
private:

    static TNameValuePair sm_arValueName[];
    static TNameValueMap  sm_mapValueName;
   
    EQEnumeration::EnumType m_value;

};


// CONSTANTS INITIALIZATION
// ----------------------------

EQEnumeration::TNameValuePair EQEnumeration::sm_arValueName[] =
    {
        std::pair<string_q, EQEnumeration::EnumType>(QE_L("<>"),    EQEnumeration::E_<>),
    };

EQEnumeration::TNameValueMap EQEnumeration::sm_mapValueName(
        EQEnumeration::sm_arValueName ,
        &EQEnumeration::sm_arValueName[0] + sizeof(EQEnumeration::sm_arValueName) / sizeof(EQEnumeration::sm_arValueName[0])
    );



} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQENUMERATION__
