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

#ifndef __EQFILEOPENMODE__
#define __EQFILEOPENMODE__

#include <map>
#include <vector>

#include "Assertions.h"
#include "DataTypesDefinitions.h"
#include "SystemDefinitions.h"

#ifdef QE_COMPILER_MSVC
    // This warning appears when instancing a template to create a data member and that template instance is not exported.
    // In this case, it is not important since the data member is not accessible.
    #pragma warning( disable : 4251 ) // http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#endif

using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Common::DataTypes::enum_int_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace IO
{
namespace FileSystem
{

/// <summary>
/// Specifies how a file has to be opened.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS EQFileOpenMode
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_Append = QE_ENUMERATION_MIN_VALUE, /*!< The file is opened, if it exists, and the position pointer of the stream is set to the end. If the file does not exist, an error will occur. */
        E_Create, /*!< The file is created, if it does not exist. If it already exists, an error will occur. */
        E_CreateOrOverwrite, /*!< The file is created, if it does not exist. If it already exists, it will be overwritten. */
        E_Open, /*!< The file is opened, if it exists. If it does not exist, an error will occur. */
        E_OpenOrCreate, /*!< The file is opened, if it exists, or created, if it does not. */

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE /*!< Not valid value. */
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<string_q, EQFileOpenMode::EnumType> TNameValueMap;
    typedef std::pair<string_q, EQFileOpenMode::EnumType> TNameValuePair;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    inline EQFileOpenMode(const EQFileOpenMode::EnumType eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    inline EQFileOpenMode(const enum_int_q nValue) : m_value(scast_q(nValue, const EQFileOpenMode::EnumType))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">[IN] The name of a valid enumeration value.</param>
    inline explicit EQFileOpenMode(const string_q &strValueName)
    {
        *this = strValueName;
    }
    
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    inline EQFileOpenMode(const EQFileOpenMode &eValue) : m_value(eValue.m_value)
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
    inline EQFileOpenMode& operator=(const enum_int_q nValue)
    {
        m_value = scast_q(nValue, const EQFileOpenMode::EnumType);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQFileOpenMode& operator=(const string_q &strValueName)
    {
        if(EQFileOpenMode::sm_mapValueName.find(strValueName) != EQFileOpenMode::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = EQFileOpenMode::_NotEnumValue;

        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQFileOpenMode& operator=(const EQFileOpenMode::EnumType eValue)
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
    inline EQFileOpenMode& operator=(const EQFileOpenMode &eValue)
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
    bool operator==(const EQFileOpenMode &eValue) const
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
        if(EQFileOpenMode::sm_mapValueName.find(strValueName) != EQFileOpenMode::sm_mapValueName.end())
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
    inline bool operator==(const enum_int_q nValue) const
    {
        return m_value == scast_q(nValue, const EQFileOpenMode::EnumType);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const EQFileOpenMode::EnumType eValue) const
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
            const size_t ENUM_ARRAY_COUNT = EQFileOpenMode::sm_mapValueName.size();

            // An empty enumeration makes no sense
            QE_ASSERT_ERROR(ENUM_ARRAY_COUNT > 0, "An empty enumeration makes no sense");

            for(size_t i = 0; i < ENUM_ARRAY_COUNT; ++i)
                arValues.push_back(EQFileOpenMode::sm_arValueName[i].second);
        }

        return arValues;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator EQFileOpenMode::EnumType() const
    {
        return m_value;
    }
    
    /// <summary>
    /// Casting operator that converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, then returns an empty string.
    /// </returns>
    operator const string_q() const
    {
        return ConvertToString(m_value, EQFileOpenMode::sm_mapValueName);
    }
    
    /// <summary>
    /// Converts the enumerated type value into its corresponding integer number.
    /// </summary>
    /// <returns>
    /// The integer number which corresponds to the contained enumeration value.
    /// </returns>
    enum_int_q ToInteger() const
    {
        return scast_q(m_value, enum_int_q);
    }

    /// <summary>
    /// Converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    const string_q ToString() const
    {
        return ConvertToString(m_value, EQFileOpenMode::sm_mapValueName);
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
    const string_q& ConvertToString(const EQFileOpenMode::EnumType eValue, const TNameValueMap& nameValueDictionary) const
    {
        TNameValueMap::const_iterator itValueName = nameValueDictionary.begin();
        TNameValueMap::const_iterator itValueNameEnd = nameValueDictionary.end();

        while(itValueName != itValueNameEnd && itValueName->second != eValue)
            ++itValueName;

        if(itValueName != itValueNameEnd)
            return itValueName->first;
        else
        {
            static const string_q EMPTY_STRING; 
            return EMPTY_STRING;
        }
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
    EQFileOpenMode::EnumType m_value;

};


} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQFILEOPENMODE__
