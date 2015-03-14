//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __EQENUMERATION__
#define __EQENUMERATION__

#include <map>
#include <vector>

#include "DataTypesDefinitions.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

/// <summary>
/// Mocked-up enumeration to test the EQEnumeration template in which are based all the enumeration
/// classes in Quimera Engine.
/// </summary>
class EQEnumerationMock
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_Value1 = QE_ENUMERATION_MIN_VALUE ,/*!< Mocked value 1 */
        E_Value2,/*!< Mocked value 1 */
        E_Value3,/*!< Mocked value 1 */

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE /*!< Not valid value. */
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<string_q, EQEnumerationMock::EnumType> TNameValueMap;
    typedef std::pair<string_q, EQEnumerationMock::EnumType> TNameValuePair;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    inline EQEnumerationMock(const EQEnumerationMock::EnumType &eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    template<typename IntegerType>
    inline EQEnumerationMock(const IntegerType &nValue) : m_value(scast_q(nValue, const EQEnumerationMock::EnumType))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">[IN] The name of a valid enumeration value.</param>
    inline EQEnumerationMock(const string_q &strValueName)
    {
        *this = strValueName;
    }
    
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    inline EQEnumerationMock(const EQEnumerationMock &eValue) : m_value(eValue.m_value)
    {
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assign operator that accepts an integer number that corresponds to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    template<typename IntegerType>
    inline EQEnumerationMock& operator=(const IntegerType &nValue)
    {
        m_value = scast_q(nValue, const EQEnumerationMock::EnumType);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQEnumerationMock& operator=(const string_q &strValueName)
    {
        if(EQEnumerationMock::sm_mapValueName.find(strValueName) != EQEnumerationMock::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = EQEnumerationMock::_NotEnumValue;

        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQEnumerationMock& operator=(const EQEnumerationMock::EnumType &eValue)
    {
        m_value = eValue;
        return *this;
    }
    
    /// <summary>
    /// Assign operator that accepts another enumeration.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQEnumerationMock& operator=(const EQEnumerationMock &eValue)
    {
        m_value = eValue.m_value;
        return *this;
    }

    /// <summary>
    /// Equality operator that receives another enumeration.
    /// </summary>
    /// <param name="eValue">[IN] The other enumeration.</param>
    /// <returns>
    /// True if it equals the enumeration value. False otherwise.
    /// </returns>
    bool operator==(const EQEnumerationMock &eValue) const
    {
        return m_value == eValue.m_value;
    }

    /// <summary>
    /// Equality operator that accepts the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// True if the name corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    inline bool operator==(const string_q &strValueName) const
    {
        if(EQEnumerationMock::sm_mapValueName.find(strValueName) != EQEnumerationMock::sm_mapValueName.end())
            return m_value == sm_mapValueName[strValueName];
        else
            return false;
    }

    /// <summary>
    /// Equality operator that accepts an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    /// <returns>
    /// True if the number corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    template<typename IntegerType>
    inline bool operator==(const IntegerType &nValue) const
    {
        return m_value == scast_q(nValue, const EQEnumerationMock::EnumType);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const EQEnumerationMock::EnumType &eValue) const
    {
        return m_value == eValue;
    }

    /// <summary>
    /// Retrieves a list of all the values of the enumeration.
    /// </summary>
    /// <returns>
    /// A list of all the values of the enumeration.
    /// </returns>
    static const std::vector<EnumType>& GetValues()
    {
        static std::vector<EnumType> arValues;

        // If it's not been initialized yet...
        if(arValues.empty())
        {
            const size_t ENUM_ARRAY_COUNT = EQEnumerationMock::sm_mapValueName.size();

            // An empty enumeration makes no sense
            QE_ASSERT(ENUM_ARRAY_COUNT > 0);

            for(size_t i = 0; i < ENUM_ARRAY_COUNT; ++i)
                arValues.push_back(EQEnumerationMock::sm_arValueName[i].second);
        }

        return arValues;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator EQEnumerationMock::EnumType() const
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
    operator const string_q() const
    {
        return ConvertToString(m_value, EQEnumerationMock::sm_mapValueName);
    }

    /// <summary>
    /// Converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    const string_q ToString() const
    {
        return ConvertToString(m_value, EQEnumerationMock::sm_mapValueName);
    }

private:

    // <summary>
    // Uses an enumerated value as a key to retrieve his own string representation from a dictionary.
    // </summary>
    // <param name="eValue">[IN] The enumeration value.</param>
    // <param name="nameValueDictionary">[IN] The dictionary where enumeration's string representations are stored.</param>
    // <returns>
    // The enumerated value's string representation.
    // </returns>
    const string_q& ConvertToString(const EQEnumerationMock::EnumType& eValue, const TNameValueMap& nameValueDictionary) const
    {
        TNameValueMap::const_iterator itValueName = nameValueDictionary.begin();
        TNameValueMap::const_iterator itValueNameEnd = nameValueDictionary.end();

        while(itValueName != itValueNameEnd && itValueName->second != eValue)
            ++itValueName;

        if(itValueName != itValueNameEnd)
            return itValueName->first;
        else
            { static const string_q EMPTY_STRING; return EMPTY_STRING; }// [TODO] Thund: This must be replaced by a QString constant.
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
    EQEnumerationMock::EnumType m_value;

};


// CONSTANTS INITIALIZATION
// ----------------------------

EQEnumerationMock::TNameValuePair EQEnumerationMock::sm_arValueName[] =
    {
        std::pair<string_q, EQEnumerationMock::EnumType>(QE_L("Value1"),    EQEnumerationMock::E_Value1),
        std::pair<string_q, EQEnumerationMock::EnumType>(QE_L("Value2"),    EQEnumerationMock::E_Value2),
        std::pair<string_q, EQEnumerationMock::EnumType>(QE_L("Value3"),    EQEnumerationMock::E_Value3),
    };

EQEnumerationMock::TNameValueMap EQEnumerationMock::sm_mapValueName(
        EQEnumerationMock::sm_arValueName ,
        &EQEnumerationMock::sm_arValueName[0] + sizeof(EQEnumerationMock::sm_arValueName) / sizeof(EQEnumerationMock::sm_arValueName[0])
    );



} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQENUMERATION__
