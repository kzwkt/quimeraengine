// [TERMS&CONDITIONS]

#ifndef __EQSPACERELATION__
#define __EQSPACERELATION__

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
class EQSpaceRelation
{
    // ENUMERATIONS
    // ---------------
public:


    /// <summary>
    /// [DOC]
    /// </summary>
    enum EnumType
    {
        E_Contained = QE_ENUMERATION_MIN_VALUE,
        E_PositiveSide,
        E_NegativeSide,
        E_BothSides,
        
        _NotEnumValue = QE_ENUMERATION_MAX_VALUE
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<string_q, EQSpaceRelation::EnumType> TNameValueMap;
    typedef std::pair<string_q, EQSpaceRelation::EnumType> TNameValuePair;


	// METHODS
	// ---------------
public:


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="eValue">[DOC]</param>
    inline EQSpaceRelation(const EQSpaceRelation::EnumType &eValue) : m_value(eValue) 
    {}


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="nValue">[DOC]</param>
    template<typename IntegerType>
    inline EQSpaceRelation(const IntegerType &nValue) : m_value(static_cast<const EQSpaceRelation::EnumType>(nValue))
    {}


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="strValueName">[DOC]</param>
    inline EQSpaceRelation(const string_q &strValueName)
    {
        *this = strValueName;
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="nValue">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
    template<typename IntegerType>
    inline EQSpaceRelation& operator=(const IntegerType &nValue)
    {
        m_value = static_cast<const EQSpaceRelation::EnumType>(nValue);
        return *this;
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="strValueName">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
    inline EQSpaceRelation& operator=(const string_q &strValueName)
    {
        if(EQSpaceRelation::sm_mapValueName.find(strValueName) != EQSpaceRelation::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = EQSpaceRelation::_NotEnumValue;

        return *this;
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="eValue">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
    inline EQSpaceRelation& operator=(const EQSpaceRelation::EnumType &eValue)
    {
        m_value = eValue;
        return *this;
    }
    

    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="strValueName">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
    inline bool operator==(const string_q &strValueName) const
    {
        if(EQSpaceRelation::sm_mapValueName.find(strValueName) != EQSpaceRelation::sm_mapValueName.end())
            return m_value == sm_mapValueName[strValueName];
        else
            return false;
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="nValue">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
    template<typename IntegerType>
    inline bool operator==(const IntegerType &nValue) const
    {
        return m_value == static_cast<const EQSpaceRelation::EnumType>(nValue);
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <param name="eValue">[DOC]</param>
    /// <returns>
    /// [DOC]
    /// </returns>
    bool operator==(const EQSpaceRelation::EnumType &eValue) const
    {
        return m_value == eValue;
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <returns>
    /// [DOC]
    /// </returns>
    inline operator EQSpaceRelation::EnumType() const
    {
        return m_value;
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <returns>
    /// [DOC]
    /// </returns>
    template<typename IntegerType>
    operator IntegerType() const
    {
        return static_cast<IntegerType>(m_value);
    }


    /// <summary>
    /// [DOC]
    /// </summary>
    /// <returns>
    /// [DOC]
    /// </returns>
    operator const string_q&() const
    {
        TNameValueMap::iterator itValueName = EQSpaceRelation::sm_mapValueName.begin();
        TNameValueMap::const_iterator itValueNameEnd = EQSpaceRelation::sm_mapValueName.end();

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


    /// <summary>
    /// [DOC]
    /// </summary>
    static TNameValuePair sm_arValueName[];
    
    /// <summary>
    /// [DOC]
    /// </summary>
    static TNameValueMap  sm_mapValueName;

    /// <summary>
    /// [DOC]
    /// </summary>
    EQSpaceRelation::EnumType m_value;

};


// CONSTANTS INITIALIZATION
// ----------------------------

EQSpaceRelation::TNameValuePair EQSpaceRelation::sm_arValueName[] =
    {
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("Contained"),    EQSpaceRelation::E_Contained),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("PositiveSide"), EQSpaceRelation::E_PositiveSide),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("NegativeSide"), EQSpaceRelation::E_NegativeSide),
        std::pair<string_q, EQSpaceRelation::EnumType>(QE_L("BothSides"),    EQSpaceRelation::E_BothSides)
    };

EQSpaceRelation::TNameValueMap EQSpaceRelation::sm_mapValueName(
        EQSpaceRelation::sm_arValueName ,
        &EQSpaceRelation::sm_arValueName[0] + sizeof(EQSpaceRelation::sm_arValueName) / sizeof(EQSpaceRelation::sm_arValueName[0])
    );



} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQSPACERELATION__
