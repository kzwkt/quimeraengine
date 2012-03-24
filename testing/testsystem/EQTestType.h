// [TERMS&CONDITIONS]

#ifndef __EQTESTTYPE__
#define __EQTESTTYPE__

#include <map>

#include "DataTypesDefinitions.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

/// <summary>
/// Represents the types of test available in the testing system.
/// </summary>
class EQTestType
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_UnitTest = QE_ENUMERATION_MIN_VALUE ,/*!< Unit test. */
        E_PerformanceTest,/*!< Performance test. */
        E_EnduranceTest,/*!< Endurance test. */

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE /*!< Not valid value. */
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<string_q, EQTestType::EnumType> TNameValueMap;
    typedef std::pair<string_q, EQTestType::EnumType> TNameValuePair;


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">A valid enumeration value.</param>
    inline EQTestType(const EQTestType::EnumType &eValue) : m_value(eValue) 
    {}

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">An integer number.</param>
    template<typename IntegerType>
    inline EQTestType(const IntegerType &nValue) : m_value(static_cast<const EQTestType::EnumType>(nValue))
    {}

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">The name of a valid enumeration value.</param>
    inline EQTestType(const string_q &strValueName)
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
    inline EQTestType& operator=(const IntegerType &nValue)
    {
        m_value = static_cast<const EQTestType::EnumType>(nValue);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQTestType& operator=(const string_q &strValueName)
    {
        if(EQTestType::sm_mapValueName.find(strValueName) != EQTestType::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = EQTestType::_NotEnumValue;

        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="nValue">A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQTestType& operator=(const EQTestType::EnumType &eValue)
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
        if(EQTestType::sm_mapValueName.find(strValueName) != EQTestType::sm_mapValueName.end())
            return m_value == sm_mapValueName[strValueName];
        else
            return false;
    }

    /// <summary>
    /// Equality operator that accepts an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="strValueName">An integer number.</param>
    /// <returns>
    /// True if the number corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    template<typename IntegerType>
    inline bool operator==(const IntegerType &nValue) const
    {
        return m_value == static_cast<const EQTestType::EnumType>(nValue);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const EQTestType::EnumType &eValue) const
    {
        return m_value == eValue;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator EQTestType::EnumType() const
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
        return static_cast<IntegerType>(m_value);
    }

    /// <summary>
    /// Casting operator that converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    operator const string_q() const
    {
        TNameValueMap::iterator itValueName = EQTestType::sm_mapValueName.begin();
        TNameValueMap::const_iterator itValueNameEnd = EQTestType::sm_mapValueName.end();

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
    const string_q ToString()
    {
        return *this;
    }


    // ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// A list of enumeration values with their names.
    /// </summary>
    static TNameValuePair sm_arValueName[];

    /// <summary>
    /// The dictionary which contains each enumeration value by its name.
    /// </summary>
    static TNameValueMap  sm_mapValueName;

    /// <summary>
    /// The contained enumeration value.
    /// </summary>
    EQTestType::EnumType m_value;

};

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQTESTTYPE__
