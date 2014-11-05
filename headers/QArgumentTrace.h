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

#ifndef __QARGUMENTTRACE__
#define __QARGUMENTTRACE__

#include "SystemDefinitions.h"

#include "DataTypesDefinitions.h"
#include "SQTypeExtensions.h"
#include "SQAnyTypeToStringConverter.h"
#include "SQInteger.h"

// Forward declarations
// ----------------------
namespace Kinesis 
{ 
    namespace QuimeraEngine 
    { 
        namespace Common 
        { 
            namespace DataTypes 
            {
                class QType;
            }
        }
    }
}


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

/// <summary>
/// Small component used to trace all the information about a function argument.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QArgumentTrace
{
    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives a function argument.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// If the type of the argument is not a basic type (u8_q, u16_q, u32_q, u64_q, i8_q, i16_q, i32_q, i64_q, f32_q, f64_q or bool), a string_q, a pointer
    /// to any of the previous types nor a pointer to QObject or derived classes then a special format will be used:<br/>
    /// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
    /// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// In the case of pointers to QObject or derived classes, the ToString method of the instance is called to obtain its value. If the pointer is null the 
    /// type retrieved by default will be QObject.<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - i32_q i = 3 / i32 / "3"<br/>
    /// - i32_q* pInt = &i / i32* / "0x######## 3"<br/>
    /// - const i32_q ci = 3 / i32 / "3"<br/>
    /// - const i32_q* pInt = &ci / const i32* / "0x######## 3"<br/>
    /// - const i32_q** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
    /// - string_q strInt = "text" / string / "text"<br/>
    /// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
    /// - i32_q* pNull = null_q / i32* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="argument">[IN] The argument to be traced.</param>
    template<class T>
    QArgumentTrace(const T &argument) : m_pType(Kinesis::QuimeraEngine::Common::DataTypes::SQTypeExtensions::FindType(argument)),
                                        m_strTypeName(string_q::GetEmpty()),
                                        m_strValue(Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter::Convert(argument))
    {
        this->_FillTypeName(argument);
    }
    
    /// <summary>
    /// Constructor that receives a function argument.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// If the type of the argument is not a basic type (u8_q, u16_q, u32_q, u64_q, i8_q, i16_q, i32_q, i64_q, f32_q, f64_q or bool), a string_q, a pointer
    /// to any of the previous types nor a pointer to QObject or derived classes then a special format will be used:<br/>
    /// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
    /// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// In the case of pointers to QObject or derived classes, the ToString method of the instance is called to obtain its value. If the pointer is null the 
    /// type retrieved by default will be QObject.<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / Value):<br/>
    /// - i32_q i = 3 / i32 / "3"<br/>
    /// - i32_q* pInt = &i / i32* / "0x######## 3"<br/>
    /// - const i32_q ci = 3 / i32 / "3"<br/>
    /// - const i32_q* pInt = &ci / const i32* / "0x######## 3"<br/>
    /// - const i32_q** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
    /// - string_q strInt = "text" / string / text<br/>
    /// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
    /// - i32_q* pNull = null_q / i32* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    QArgumentTrace(T* pArgument) : m_pType(Kinesis::QuimeraEngine::Common::DataTypes::SQTypeExtensions::FindType(pArgument)),
                                   m_strTypeName(string_q::GetEmpty()),
                                   m_strValue(Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter::Convert(pArgument))
    {
        this->_FillTypeName(pArgument);
    }
    
    /// <summary>
    /// Constructor that receives a function argument.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// If the type of the argument is not a basic type (u8_q, u16_q, u32_q, u64_q, i8_q, i16_q, i32_q, i64_q, f32_q, f64_q or bool), a string_q, a pointer
    /// to any of the previous types nor a pointer to QObject or derived classes then a special format will be used:<br/>
    /// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
    /// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// In the case of pointers to QObject or derived classes, the ToString method of the instance is called to obtain its value. If the pointer is null the 
    /// type retrieved by default will be QObject.<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / Value):<br/>
    /// - i32_q i = 3 / i32 / "3"<br/>
    /// - i32_q* pInt = &i / i32* / "0x######## 3"<br/>
    /// - const i32_q ci = 3 / i32 / "3"<br/>
    /// - const i32_q* pInt = &ci / const i32* / "0x######## 3"<br/>
    /// - const i32_q** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
    /// - string_q strInt = "text" / string / "text"<br/>
    /// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
    /// - i32_q* pNull = null_q / i32* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    QArgumentTrace(const T* pArgument) : m_pType(Kinesis::QuimeraEngine::Common::DataTypes::SQTypeExtensions::FindType(pArgument)),
                                         m_strTypeName(string_q::GetEmpty()),
                                         m_strValue(Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter::Convert(pArgument))
    {
        this->_FillTypeName(pArgument);
    }
    

    // METHODS
    // ---------------
private:
    
    /// <summary>
    /// Fills the type name of the argument.
    /// </summary>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name=".">[IN] Not used.</param>
    template<class T>
    void _FillTypeName(const T&)
    {
        using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

        static const string_q UNKNOWN_TYPE_PART1("<Unknown type (size: ");
        static const string_q UNKNOWN_TYPE_PART2(")>");

        if(m_pType)
        {
            m_strTypeName.Append(m_pType->GetName());
        }
        else
        {
            m_strTypeName.Append(UNKNOWN_TYPE_PART1);
            m_strTypeName.Append(SQInteger::ToString(sizeof(T)));
            m_strTypeName.Append(UNKNOWN_TYPE_PART2);
        }
    }
    
    /// <summary>
    /// Fills the type name of the argument.
    /// </summary>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    void _FillTypeName(T* pArgument)
    {
        static const string_q ASTERISK("*");

        this->_FillTypeName(*pArgument);
        m_strTypeName.Append(ASTERISK);
    }
    
    /// <summary>
    /// Fills the type name of the argument.
    /// </summary>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    void _FillTypeName(const T* pArgument)
    {
        static const string_q CONSTANT("const ");
        static const string_q ASTERISK("*");

        if(m_strTypeName.IsEmpty())
            m_strTypeName.Append(CONSTANT);

        this->_FillTypeName(*pArgument);
        m_strTypeName.Append(ASTERISK);
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the name of the type of the argument.
    /// </summary>
    /// <returns>
    /// The argument type name. If the type of the argument is not recognized, this name will follow a special format.
    /// </returns>
    const Kinesis::QuimeraEngine::Common::DataTypes::string_q& GetTypeName() const;

    /// <summary>
    /// Gets the value of the argument.
    /// </summary>
    /// <returns>
    /// The value of the argument, as a text string. If the type of the argument is not recognized, this value will follow a special format.
    /// </returns>
    const Kinesis::QuimeraEngine::Common::DataTypes::string_q& GetValue() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The type of the argument.
    /// </summary>
    const Kinesis::QuimeraEngine::Common::DataTypes::QType* m_pType;

    /// <summary>
    /// The name of the type of the argument.
    /// </summary>
    Kinesis::QuimeraEngine::Common::DataTypes::string_q m_strTypeName;

    /// <summary>
    /// The value of the argument.
    /// </summary>
    Kinesis::QuimeraEngine::Common::DataTypes::string_q m_strValue;

};

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QARGUMENTTRACE__
