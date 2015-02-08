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

#include "Assertions.h"
#include "DataTypesDefinitions.h"
#include "SystemDefinitions.h"
#include "QArrayBasic.h"
#include <cstring>

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
        E_Create,                            /*!< The file is created, if it does not exist. If it already exists, an error will occur. */
        E_CreateOrOverwrite,                 /*!< The file is created, if it does not exist. If it already exists, it will be overwritten. */
        E_Open,                              /*!< The file is opened, if it exists. If it does not exist, an error will occur. */
        E_OpenOrCreate,                      /*!< The file is opened, if it exists, or created, if it does not. */

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE /*!< Not valid value. */
    };


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    EQFileOpenMode(const EQFileOpenMode::EnumType eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    EQFileOpenMode(const enum_int_q nValue) : m_value(scast_q(nValue, const EQFileOpenMode::EnumType))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. <br/>Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="szValueName">[IN] The name of a valid enumeration value.</param>
    EQFileOpenMode(const char* szValueName)
    {
        *this = szValueName;
    }
    
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    EQFileOpenMode(const EQFileOpenMode &eValue) : m_value(eValue.m_value)
    {
    }

    /// <summary>
    /// Assignation operator that accepts an integer number that corresponds to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    EQFileOpenMode& operator=(const enum_int_q nValue)
    {
        m_value = scast_q(nValue, const EQFileOpenMode::EnumType);
        return *this;
    }

    /// <summary>
    /// Assignation operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="szValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    EQFileOpenMode& operator=(const char* szValueName)
    {
        bool bMatchFound = false;
        unsigned int uEnumStringIndex = 0;

        while(!bMatchFound && uEnumStringIndex < EQFileOpenMode::_GetNumberOfValues())
        {
            bMatchFound = strcmp(sm_arStrings[uEnumStringIndex], szValueName) == 0;
            ++uEnumStringIndex;
        }

        QE_ASSERT_ERROR(uEnumStringIndex < EQFileOpenMode::_GetNumberOfValues(), "The input string does not correspond to any valid enumeration value.");

        m_value = sm_arValues[uEnumStringIndex - 1U];

        return *this;
    }

    /// <summary>
    /// Assignation operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    EQFileOpenMode& operator=(const EQFileOpenMode::EnumType eValue)
    {
        m_value = eValue;
        return *this;
    }
    
    /// <summary>
    /// Assignation operator that accepts another enumeration.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    EQFileOpenMode& operator=(const EQFileOpenMode &eValue)
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
    /// Equality operator that receives the name of a valid enumeration value.<br/>Note that enumeration value names do not include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="szValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// True if the name corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const char* szValueName) const
    {
        bool bMatchFound = false;
        unsigned int uEnumStringIndex = 0;

        while(!bMatchFound && uEnumStringIndex < EQFileOpenMode::_GetNumberOfValues())
        {
            bMatchFound = strcmp(sm_arStrings[m_value], szValueName) == 0;
            ++uEnumStringIndex;
        }

        return bMatchFound;
    }

    /// <summary>
    /// Equality operator that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    /// <returns>
    /// True if the number corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const enum_int_q nValue) const
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
    /// Inequality operator that receives another enumeration.
    /// </summary>
    /// <param name="eValue">[IN] The other enumeration.</param>
    /// <returns>
    /// False if it equals the enumeration value. True otherwise.
    /// </returns>
    bool operator!=(const EQFileOpenMode &eValue) const
    {
        return m_value != eValue.m_value;
    }

    /// <summary>
    /// Inequality operator that receives the name of a valid enumeration value.<br/>Note that enumeration value names do not include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="szValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// False if the name corresponds to a valid enumeration value and it equals the contained value. True otherwise.
    /// </returns>
    bool operator!=(const char* szValueName) const
    {
        return !(*this == szValueName);
    }

    /// <summary>
    /// Inequality operator that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    /// <returns>
    /// False if the number corresponds to a valid enumeration value and it equals the contained value. True otherwise.
    /// </returns>
    bool operator!=(const enum_int_q nValue) const
    {
        return m_value != scast_q(nValue, const EQFileOpenMode::EnumType);
    }

    /// <summary>
    /// Inequality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// False if it equals the contained value. True otherwise.
    /// </returns>
    bool operator!=(const EQFileOpenMode::EnumType eValue) const
    {
        return m_value != eValue;
    }
    
    /// <summary>
    /// Retrieves a list of all the values of the enumeration.
    /// </summary>
    /// <returns>
    /// A list of all the values of the enumeration.
    /// </returns>
    static const Kinesis::QuimeraEngine::Common::DataTypes::QArrayBasic<const EnumType> GetValues()
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::QArrayBasic;
        static const QArrayBasic<const EnumType> ARRAY_OF_VALUES(sm_arValues, EQFileOpenMode::_GetNumberOfValues());
        return ARRAY_OF_VALUES;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    operator EQFileOpenMode::EnumType() const
    {
        return m_value;
    }

    /// <summary>
    /// Casting operator that converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    operator const char*() const
    {
        return _ConvertToString(m_value);
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
    /// The contained enumeration value name. If the enumeration value is not valid, then returns an empty string.
    /// </returns>
    const char* ToString() const
    {
        return _ConvertToString(m_value);
    }

private:

    /// <summary>
    /// Uses an enumerated value as a key to retrieve his own string representation from a dictionary.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// The enumerated value's string representation.
    /// </returns>
    inline static const char* _ConvertToString(const EQFileOpenMode::EnumType eValue)
    {
        QE_ASSERT_ERROR(scast_q(eValue, unsigned int) < EQFileOpenMode::_GetNumberOfValues(), "The enumeration value is not valid.");

        return sm_arStrings[eValue];
    }
        
    /// <summary>
    /// Gets the number of values available in the enumeration.
    /// </summary>
    /// <returns>
    /// A number of values, without counting the _NotEnumValue value.
    /// </returns>
    static unsigned int _GetNumberOfValues();


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The string representation of every enumeration value.
    /// </summary>
    static const char* sm_arStrings[];

    /// <summary>
    /// A list with all enumeration values avalilable.
    /// </summary>
    static const EQFileOpenMode::EnumType sm_arValues[];

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

