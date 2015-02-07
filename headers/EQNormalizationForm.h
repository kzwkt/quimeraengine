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

#ifndef __EQNORMALIZATIONFORM__
#define __EQNORMALIZATIONFORM__

//#include "Assertions.h"
#include "DataTypesDefinitions.h"
#include "CommonDefinitions.h"
#include "QBasicArray.h"
#include <cstring>

using Kinesis::QuimeraEngine::Common::DataTypes::enum_int_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Enumeration of the existing Unicode normalization forms.
/// </summary>
class QE_LAYER_COMMON_SYMBOLS EQNormalizationForm
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_C = QE_ENUMERATION_MIN_VALUE, /*!< Canonical decomposition followed by canonical composition (NFC). */
        E_D,                            /*!< Canonical decomposition (NFD). */
        // These options will be available in the future:
        //E_KC,                           /*!< Not supported yet. Compatibility decomposition followed by canonical composition (NFKC). */
        //E_KD,                           /*!< Not supported yet. Compatibility decomposition (NFKD). */

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE /*!< Not valid value. */
    };


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    EQNormalizationForm(const EQNormalizationForm::EnumType eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    EQNormalizationForm(const enum_int_q nValue) : m_value(scast_q(nValue, const EQNormalizationForm::EnumType))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. <br/>Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="szValueName">[IN] The name of a valid enumeration value.</param>
    EQNormalizationForm(const char* szValueName)
    {
        *this = szValueName;
    }
    
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    EQNormalizationForm(const EQNormalizationForm &eValue) : m_value(eValue.m_value)
    {
    }

    /// <summary>
    /// Assignation operator that accepts an integer number that corresponds to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    EQNormalizationForm& operator=(const enum_int_q nValue)
    {
        m_value = scast_q(nValue, const EQNormalizationForm::EnumType);
        return *this;
    }

    /// <summary>
    /// Assignation operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="szValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    EQNormalizationForm& operator=(const char* szValueName)
    {
        bool bMatchFound = false;
        unsigned int uEnumStringIndex = 0;

        while(!bMatchFound && uEnumStringIndex < EQNormalizationForm::_GetNumberOfValues())
        {
            bMatchFound = strcmp(sm_arStrings[uEnumStringIndex], szValueName) == 0;
            ++uEnumStringIndex;
        }

        // Commented to avoid a mutual inclusion with assertions
        //QE_ASSERT_ERROR(uEnumStringIndex < EQNormalizationForm::_GetNumberOfValues(), "The input string does not correspond to any valid enumeration value.");

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
    EQNormalizationForm& operator=(const EQNormalizationForm::EnumType eValue)
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
    EQNormalizationForm& operator=(const EQNormalizationForm &eValue)
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
    bool operator==(const EQNormalizationForm &eValue) const
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

        while(!bMatchFound && uEnumStringIndex < EQNormalizationForm::_GetNumberOfValues())
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
        return m_value == scast_q(nValue, const EQNormalizationForm::EnumType);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const EQNormalizationForm::EnumType eValue) const
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
    bool operator!=(const EQNormalizationForm &eValue) const
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
        return m_value != scast_q(nValue, const EQNormalizationForm::EnumType);
    }

    /// <summary>
    /// Inequality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// False if it equals the contained value. True otherwise.
    /// </returns>
    bool operator!=(const EQNormalizationForm::EnumType eValue) const
    {
        return m_value != eValue;
    }
    
    /// <summary>
    /// Retrieves a list of all the values of the enumeration.
    /// </summary>
    /// <returns>
    /// A list of all the values of the enumeration.
    /// </returns>
    static const Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray<const EnumType> GetValues()
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;
        static const QBasicArray<const EnumType> ARRAY_OF_VALUES(sm_arValues, EQNormalizationForm::_GetNumberOfValues());
        return ARRAY_OF_VALUES;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    operator EQNormalizationForm::EnumType() const
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
    inline static const char* _ConvertToString(const EQNormalizationForm::EnumType eValue)
    {
        // Commented to avoid a mutual inclusion with assertions
        //QE_ASSERT_ERROR(scast_q(eValue, unsigned int) < EQNormalizationForm::_GetNumberOfValues(), "The enumeration value is not valid.");

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
    static const EQNormalizationForm::EnumType sm_arValues[];

    /// <summary>
    /// The contained enumeration value.
    /// </summary>
    EQNormalizationForm::EnumType m_value;

};

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQNORMALIZATIONFORM__
