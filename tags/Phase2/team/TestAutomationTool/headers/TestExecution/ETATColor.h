//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __ETATCOLOR__
#define __ETATCOLOR__

#include <map>
#include <vector>

#include <wx/string.h>


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Represents a color.
/// </summary>
class ETATColor
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_Black  = 0, /*!< Black color => ARGB(255, 0, 0, 0). */
        E_White  = 1, /*!< White color => ARGB(255, 255, 255, 255). */
        E_Red    = 2, /*!< Red color => ARGB(255, 255, 0, 0). */
        E_Yellow = 3, /*!< Yellow color => ARGB(255, 255, 255, 0). */
        E_Blue   = 4, /*!< Blue color => ARGB(255, 0, 0, 255). */
        E_Green  = 5, /*!< Green color => ARGB(255, 0, 255, 0). */
        E_Purple = 6, /*!< Purple color => ARGB(255, 255, 0, 255). */
        E_Grey   = 7, /*!< Gray color => ARGB(255, 127, 127, 127). */

        _NotEnumValue = 0xFFFFFFFF /*!< Not valid value. */
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<wxString, ETATColor::EnumType> TNameValueMap;
    typedef std::pair<wxString, ETATColor::EnumType> TNameValuePair;
    typedef unsigned int TEnumInt;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    inline ETATColor(const ETATColor::EnumType &eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    inline ETATColor(const TEnumInt &nValue) : m_value(static_cast<const ETATColor::EnumType>(nValue))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">[IN] The name of a valid enumeration value.</param>
    inline ETATColor(const wxString &strValueName)
    {
        *this = strValueName;
    }
    
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    inline ETATColor(const ETATColor &eValue) : m_value(eValue.m_value)
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
    inline ETATColor& operator=(const TEnumInt &nValue)
    {
        m_value = static_cast<const ETATColor::EnumType>(nValue);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline ETATColor& operator=(const wxString &strValueName)
    {
        if(ETATColor::sm_mapValueName.find(strValueName) != ETATColor::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = ETATColor::_NotEnumValue;

        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline ETATColor& operator=(const ETATColor::EnumType &eValue)
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
    inline ETATColor& operator=(const ETATColor &eValue)
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
    bool operator==(const ETATColor &eValue) const
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
    inline bool operator==(const wxString &strValueName) const
    {
        if(ETATColor::sm_mapValueName.find(strValueName) != ETATColor::sm_mapValueName.end())
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
    inline bool operator==(const TEnumInt &nValue) const
    {
        return m_value == static_cast<const ETATColor::EnumType>(nValue);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const ETATColor::EnumType &eValue) const
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
            const size_t ENUM_ARRAY_COUNT = ETATColor::sm_mapValueName.size();

            // An empty enumeration makes no sense
            wxASSERT(ENUM_ARRAY_COUNT > 0);

            for(size_t i = 0; i < ENUM_ARRAY_COUNT; ++i)
                arValues.push_back(ETATColor::sm_arValueName[i].second);
        }

        return arValues;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator ETATColor::EnumType() const
    {
        return m_value;
    }
    
    /// <summary>
    /// Casting operator that converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    operator const wxString() const
    {
        return ConvertToString(m_value, ETATColor::sm_mapValueName);
    }
        
    /// <summary>
    /// Converts the enumerated type value into its corresponding integer number.
    /// </summary>
    /// <returns>
    /// The integer number which corresponds to the contained enumeration value.
    /// </returns>
    TEnumInt ToInteger() const
    {
        return static_cast<TEnumInt>(m_value);
    }

    /// <summary>
    /// Converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    const wxString ToString() const
    {
        return ConvertToString(m_value, ETATColor::sm_mapValueName);
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
    const wxString& ConvertToString(const ETATColor::EnumType& eValue, const TNameValueMap& nameValueDictionary) const
    {
        TNameValueMap::const_iterator itValueName = nameValueDictionary.begin();
        TNameValueMap::const_iterator itValueNameEnd = nameValueDictionary.end();

        while(itValueName != itValueNameEnd && itValueName->second != eValue)
            ++itValueName;

        if(itValueName != itValueNameEnd)
            return itValueName->first;
        else
            { static const wxString EMPTY_STRING; return EMPTY_STRING; }// [TODO] Thund: This must be replaced by a QString constant.
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
    ETATColor::EnumType m_value;

};


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __ETATCOLOR__
