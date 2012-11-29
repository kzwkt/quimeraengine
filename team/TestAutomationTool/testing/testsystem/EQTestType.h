// [TERMS&CONDITIONS]

#ifndef __ETATTESTTYPE__
#define __ETATTESTTYPE__

#include <map>

#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Test
{

/// <summary>
/// Represents the types of test available in the testing system.
/// </summary>
class ETATTestType
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_UnitTest = 0 ,/*!< Unit test. */
        E_PerformanceTest,/*!< Performance test. */
        E_EnduranceTest,/*!< Endurance test. */

        _NotEnumValue = -1 /*!< Not valid value. */
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<wxString, ETATTestType::EnumType> TNameValueMap;
    typedef std::pair<wxString, ETATTestType::EnumType> TNameValuePair;


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">A valid enumeration value.</param>
    inline ETATTestType(const ETATTestType::EnumType &eValue) : m_value(eValue) 
    {}

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">An integer number.</param>
    template<typename IntegerType>
    inline ETATTestType(const IntegerType &nValue) : m_value(static_cast<const ETATTestType::EnumType>(nValue))
    {}

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">The name of a valid enumeration value.</param>
    inline ETATTestType(const wxString &strValueName)
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
    inline ETATTestType& operator=(const IntegerType &nValue)
    {
        m_value = static_cast<const ETATTestType::EnumType>(nValue);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline ETATTestType& operator=(const wxString &strValueName)
    {
        if(ETATTestType::sm_mapValueName.find(strValueName) != ETATTestType::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = ETATTestType::_NotEnumValue;

        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="nValue">A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline ETATTestType& operator=(const ETATTestType::EnumType &eValue)
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
    inline bool operator==(const wxString &strValueName) const
    {
        if(ETATTestType::sm_mapValueName.find(strValueName) != ETATTestType::sm_mapValueName.end())
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
        return m_value == static_cast<const ETATTestType::EnumType>(nValue);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const ETATTestType::EnumType &eValue) const
    {
        return m_value == eValue;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator ETATTestType::EnumType() const
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
    operator const wxString() const
    {
        return ConvertToString(m_value, ETATTestType::sm_mapValueName);
    }

    /// <summary>
    /// Converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    const wxString ToString() const
    {
        return ConvertToString(m_value, ETATTestType::sm_mapValueName);
    }

private:

    // <summary>
    // Uses an enumerated value as a key to retrieve his own string representation from a dictionary.
    // </summary>
    // <param name="eValue">The enumeration value.</param>
    // <param name="nameValueDictionary">The dictionary where enumeration's string representations are stored.</param>
    // <returns>
    // The enumerated value's string representation.
    // </returns>
    const wxString& ConvertToString(const ETATTestType::EnumType& eValue, const TNameValueMap& nameValueDictionary) const
    {
        TNameValueMap::const_iterator itValueName = nameValueDictionary.begin();
        TNameValueMap::const_iterator itValueNameEnd = nameValueDictionary.end();

        while(itValueName != itValueNameEnd && itValueName->second != eValue)
            ++itValueName;

        if(itValueName != itValueNameEnd)
            return itValueName->first;
        else
            return wxT(""); // [TODO] Thund: Esto debe cambiarse por una constante de QString.
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
    ETATTestType::EnumType m_value;

};

} //namespace Test
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __ETATTESTTYPE__
