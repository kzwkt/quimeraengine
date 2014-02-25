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

#ifndef __EQTREETRAVERSALORDER__
#define __EQTREETRAVERSALORDER__

#include <map>
#include <vector>

#include "Assertions.h"
#include "DataTypesDefinitions.h"
#include "ToolsDefinitions.h"

#ifdef QE_COMPILER_MSVC
#pragma warning( disable : 4251 ) // http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#endif


using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Common::DataTypes::enum_int_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

/// <summary>
/// Enumerates the amount of different tree traversals across a tree data structure.
/// </summary>
class QE_LAYER_TOOLS_SYMBOLS EQTreeTraversalOrder
{
    // ENUMERATIONS
    // ---------------
public:

    /// <summary>
    /// The encapsulated enumeration.
    /// </summary>
    enum EnumType
    {
        // For more info about the different searchs, please visit:
        // http://en.wikipedia.org/wiki/Tree_traversal
        // http://en.wikipedia.org/wiki/Breadth-first_search
        // 
        E_DepthFirstInOrder    = QE_ENUMERATION_MIN_VALUE, /*!< First in-order search*/
        E_DepthFirstPreOrder,                              /*!< First in pre-order search*/
        E_DepthFirstPostOrder,                             /*!< First in post-order search*/
        E_BreadthFirst,                                    /*!< Breadth-first search (BFS)*/
        _NotEnumValue          = QE_ENUMERATION_MAX_VALUE  /*!< Not valid value. */
    };

    // TYPEDEFS
    // ---------------
public:

    typedef std::map<string_q,  EQTreeTraversalOrder::EnumType> TNameValueMap;
    typedef std::pair<string_q, EQTreeTraversalOrder::EnumType> TNameValuePair;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Constructor that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    inline EQTreeTraversalOrder(const EQTreeTraversalOrder::EnumType &eValue) : m_value(eValue)
    {
    }

    /// <summary>
    /// Constructor that receives an integer number which must correspond to a valid enumeration value.
    /// </summary>
    /// <param name="nValue">[IN] An integer number.</param>
    inline EQTreeTraversalOrder(const enum_int_q &nValue) : m_value(scast_q(nValue, const EQTreeTraversalOrder::EnumType))
    {
    }

    /// <summary>
    /// Constructor that receives the name of a valid enumeration value. Note that enumeration value names don't include
    /// the enumeration prefix.
    /// </summary>
    /// <param name="strValueName">[IN] The name of a valid enumeration value.</param>
    inline explicit EQTreeTraversalOrder(const string_q &strValueName)
    {
        *this = strValueName;
    }
    
    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="eValue">[IN] Another enumeration.</param>
    inline EQTreeTraversalOrder(const EQTreeTraversalOrder &eValue) : m_value(eValue.m_value)
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
    inline EQTreeTraversalOrder& operator=(const enum_int_q &nValue)
    {
        m_value = scast_q(nValue, const EQTreeTraversalOrder::EnumType);
        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value name.
    /// </summary>
    /// <param name="strValueName">[IN] The enumeration value name.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQTreeTraversalOrder& operator=(const string_q &strValueName)
    {
        if(EQTreeTraversalOrder::sm_mapValueName.find(strValueName) != EQTreeTraversalOrder::sm_mapValueName.end())
            m_value = sm_mapValueName[strValueName];
        else
            m_value = EQTreeTraversalOrder::_NotEnumValue;

        return *this;
    }

    /// <summary>
    /// Assign operator that accepts a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] A valid enumeration value.</param>
    /// <returns>
    /// The enumerated type itself.
    /// </returns>
    inline EQTreeTraversalOrder& operator=(const EQTreeTraversalOrder::EnumType &eValue)
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
    inline EQTreeTraversalOrder& operator=(const EQTreeTraversalOrder &eValue)
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
    bool operator==(const EQTreeTraversalOrder &eValue) const
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
        if(EQTreeTraversalOrder::sm_mapValueName.find(strValueName) != EQTreeTraversalOrder::sm_mapValueName.end())
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
    inline bool operator==(const enum_int_q &nValue) const
    {
        return m_value == scast_q(nValue, const EQTreeTraversalOrder::EnumType);
    }

    /// <summary>
    /// Equality operator that receives a valid enumeration value.
    /// </summary>
    /// <param name="eValue">[IN] The enumeration value.</param>
    /// <returns>
    /// True if it equals the contained value. False otherwise.
    /// </returns>
    bool operator==(const EQTreeTraversalOrder::EnumType &eValue) const
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
            const size_t ENUM_ARRAY_COUNT = EQTreeTraversalOrder::sm_mapValueName.size();

            // An empty enumeration makes no sense
            QE_ASSERT(ENUM_ARRAY_COUNT > 0, "An empty enumeration makes no sense");

            for(size_t i = 0; i < ENUM_ARRAY_COUNT; ++i)
                arValues.push_back(EQTreeTraversalOrder::sm_arValueName[i].second);
        }

        return arValues;
    }

    /// <summary>
    /// Casting operator that converts the class capsule into a valid enumeration value.
    /// </summary>
    /// <returns>
    /// The contained enumeration value.
    /// </returns>
    inline operator EQTreeTraversalOrder::EnumType() const
    {
        return m_value;
    }
    
    /// <summary>
    /// Casting operator that converts the enumerated type value into its corresponding name.
    /// </summary>
    /// <returns>
    /// The contained enumeration value name. If the enumeration value is not valid, the returns an empty string.
    /// </returns>
    operator const string_q() const
    {
        return ConvertToString(m_value, EQTreeTraversalOrder::sm_mapValueName);
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
        return ConvertToString(m_value, EQTreeTraversalOrder::sm_mapValueName);
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
    const string_q& ConvertToString(const EQTreeTraversalOrder::EnumType& eValue, const TNameValueMap& nameValueDictionary) const
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
    EQTreeTraversalOrder::EnumType m_value;
};


} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __EQTREETRAVERSALORDER__
