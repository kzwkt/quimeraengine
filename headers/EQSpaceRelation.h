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
/// Enumerated type that represents a space relation between a geometric element (a point, a triangle, a line, etc.) and another one,
/// normally a plane.
/// </summary>
class EQSpaceRelation
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        E_Contained = QE_ENUMERATION_MIN_VALUE, /*!< The geometric element is fully contained in the plane. */
        E_PositiveSide, /*!< The geometric element is in front of the plane. */
        E_NegativeSide, /*!< The geometric element is in behind the plane. */
        E_BothSides, /*!< The geometric element intersects the plane. Part of the element is in front of the plane and other part is behind it. */

        _NotEnumValue = QE_ENUMERATION_MAX_VALUE /*!< Not valid value. */
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
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">A valid enumeration value.</param>
    inline EQSpaceRelation(const EQSpaceRelation::EnumType &eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">An integer number.</param>
    template<typename IntegerType>
    inline EQSpaceRelation(const IntegerType &nValue) : m_value(scast_q(nValue, const EQSpaceRelation::EnumType))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. <br>Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">The name of a valid enumeration value.</param>
    inline EQSpaceRelation(const string_q &strValueName)
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
    inline EQSpaceRelation& operator=(const IntegerType &nValue)
    {
        m_value = scast_q(nValue, const EQSpaceRelation::EnumType);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
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
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="eValue">A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQSpaceRelation& operator=(const EQSpaceRelation::EnumType &eValue)
    {
        m_value = eValue;
        return *this;
    }

    /// <summary>
    /// Equality operator that accepts the name of a valid enumeration value. <br>Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">The enumeration value name.</param>
    /// <returns>
    /// True if the name corresponds to a valid enumeration value and it equals the contained value. False otherwise.
    /// </returns>
    inline bool operator==(const string_q &strValueName) const
    {
        if(EQSpaceRelation::sm_mapValueName.find(strValueName) != EQSpaceRelation::sm_mapValueName.end())
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
        return m_value == scast_q(nValue, const EQSpaceRelation::EnumType);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const EQSpaceRelation::EnumType &eValue) const
    {
        return m_value == eValue;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator EQSpaceRelation::EnumType() const
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
        TNameValueMap::iterator itValueName = EQSpaceRelation::sm_mapValueName.begin();
        TNameValueMap::const_iterator itValueNameEnd = EQSpaceRelation::sm_mapValueName.end();

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
        return*this;
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
    EQSpaceRelation::EnumType m_value;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQSPACERELATION__
