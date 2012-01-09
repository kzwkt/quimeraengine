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
namespace NAMESPACE
{

/// <summary>
/// [DOC]
/// </summary>
class EQEnumeration
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_<> = QE_ENUMERATION_MIN_VALUE ,/*!< [DOC] */

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE /*!< Not valid value. */
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<string_q, EQEnumeration::EnumType> TNameValueMap;
    typedef std::pair<string_q, EQEnumeration::EnumType> TNameValuePair;


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">A valid enumeration value.</param>
    inline EQEnumeration(const EQEnumeration::EnumType &eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">An integer number.</param>
    template<typename IntegerType>
    inline EQEnumeration(const IntegerType &nValue) : m_value(scast_q(nValue, const EQEnumeration::EnumType))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">The name of a valid enumeration value.</param>
    inline EQEnumeration(const string_q &strValueName)
    {
        *this = strValueName;
    }

    /// <summary>
    /// Assign operator that accepts an integer number that corresponds to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">An integer number.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    template<typename IntegerType>
    inline EQEnumeration& operator=(const IntegerType &nValue)
    {
        m_value = scast_q(nValue, const EQEnumeration::EnumType);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQEnumeration& operator=(const string_q &strValueName)
    {
        if(EQEnumeration::sm_mapValueName.find(strValueName) != EQEnumeration::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = EQEnumeration::_NotEnumValue;

        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="eValue">A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQEnumeration& operator=(const EQEnumeration::EnumType &eValue)
    {
        m_value = eValue;
        return *this;
    }

    /// <summary>
    /// Equality operator that accepts the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">The enumeration value name.</param>
    /// <returns>
    /// True if the name corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    inline bool operator==(const string_q &strValueName) const
    {
        if(EQEnumeration::sm_mapValueName.find(strValueName) != EQEnumeration::sm_mapValueName.end())
            return m_value == sm_mapValueName[strValueName];
        else
            return false;
    }

    /// <summary>
    /// Equality operator that accepts an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">An integer number.</param>
    /// <returns>
    /// True if the number corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    template<typename IntegerType>
    inline bool operator==(const IntegerType &nValue) const
    {
        return m_value == scast_q(nValue, const EQEnumeration::EnumType);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const EQEnumeration::EnumType &eValue) const
    {
        return m_value == eValue;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator EQEnumeration::EnumType() const
    {
        return m_value;
    }

    /// <summary>
    /// Casting operator that converts the enumerated type value into its corresponding integer number.
    /// </summary>
    /// <returns>
    /// The integer number which corresponds to the contained enumeration value.
    /// </returns>
    template<typename IntegerType>
    operator IntegerType() const
    {
        return scast_q(m_value, IntegerType);
    }

    /// <summary>
    /// Casting operator that converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
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

    /// <summary>
    /// Converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    const string_q& ToString()
    {
        return *this;
    }


    // ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// A list of enumeration values with their names.
    /// </summary>
    static TNameValuePair sm_arValueName[];  REMEMBER TO INITIALIZE IT IN THE CPP FILE

    /// <summary>
    /// The dictionary which contains each enumeration value by its name.
    /// </summary>
    static TNameValueMap  sm_mapValueName;  REMEMBER TO INITIALIZE IT IN THE CPP FILE

    /// <summary>
    /// The contained enumeration value.
    /// </summary>
    EQEnumeration::EnumType m_value;

};


// CONSTANTS INITIALIZATION
// ----------------------------
THIS MUST BE PLACED IN THE CPP FILE
EQEnumeration::TNameValuePair EQEnumeration::sm_arValueName[] =
    {
        std::pair<string_q, EQEnumeration::EnumType>(QE_L("<>"),    EQEnumeration::E_<>),
    };

EQEnumeration::TNameValueMap EQEnumeration::sm_mapValueName(
        EQEnumeration::sm_arValueName ,
        &EQEnumeration::sm_arValueName[0] + sizeof(EQEnumeration::sm_arValueName) / sizeof(EQEnumeration::sm_arValueName[0])
    );



} //namespace NAMESPACE
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQENUMERATION__
