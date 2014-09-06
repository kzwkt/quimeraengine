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

#ifndef __QTYPE__
#define __QTYPE__

#include "CommonDefinitions.h"
#include "DataTypesDefinitions.h"
#include "Assertions.h"

#ifdef QE_COMPILER_MSVC
    // This warning appears when instancing a template to create a data member and that template instance is not exported.
    // In this case, it is not important since the data member is not accessible.
    #pragma warning( disable : 4251 ) // http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#endif


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Describes a data type.
/// </summary>
/// <remarks>
/// QType instances are intended to be unique for every class for which they are defined. Do not create
/// any instance unless you are defining a new class.<br/>
/// This class is immutable and it is not intended to be derived.
/// </remarks>
class QE_LAYER_COMMON_SYMBOLS QType
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives the type's information.
    /// </summary>
    /// <param name="strName">The unqualified name of the type.</param>
    explicit QType(const string_q &strName);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator that checks if two instances are the same or not.
    /// </summary>
    /// <param name="type">The other instance to compare to.</param>
    /// <returns>
    /// True if both instances are equal (same memory address); False otherwise.
    /// </returns>
    bool operator==(const QType &type) const;

    /// <summary>
    /// Inequality operator that checks if two instances are different or not.
    /// </summary>
    /// <param name="type">The other instance to compare to.</param>
    /// <returns>
    /// True if instances are not equal (different memory address); False otherwise.
    /// </returns>
    bool operator!=(const QType &type) const;
    
    /// <summary>
    /// Obtains the type information of a given basic C++ type.
    /// </summary>
    /// <typeparam name="T">The type whose information is to be obtained.</typeparam>
    /// <returns>
    /// The type information. The same instance will be returned always for each type, they are stored statically.
    /// </returns>
    template<class T>
    static const QType* FindType()
    {
       // This method will give an error always since it will be called 
       // with non basic data type. See template specializations below.
       QE_ASSERT_ERROR(false, "Error!: The type used as template parameter is not a basic data type.");
       return null_q;
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the unqualified name of the type.
    /// </summary>
    /// <returns>
    /// The unqualified name of the type.
    /// </returns>
    const string_q& GetName() const;



    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The unqualified name of the type.
    /// </summary>
    const string_q m_strName;
    
    /// <summary>
    /// QType instance for boolean type.
    /// </summary>
    static const QType* TYPE_INSTANCE_BOOL;

    /// <summary>
    /// QType instance for unsigned 8-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_U8;

    /// <summary>
    /// QType instance for signed 8-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_I8;

    /// <summary>
    /// QType instance for unsigned 16-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_U16;

    /// <summary>
    /// QType instance for signed 16-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_I16;

    /// <summary>
    /// QType instance for unsigned 32-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_U32;

    /// <summary>
    /// QType instance for signed 32-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_I32;

    /// <summary>
    /// QType instance for unsigned 64-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_U64;

    /// <summary>
    /// QType instance for signed 64-bits integer type.
    /// </summary>
    static const QType* TYPE_INSTANCE_I64;

    /// <summary>
    /// QType instance for 32-bits floating point number type.
    /// </summary>
    static const QType* TYPE_INSTANCE_F32;

    /// <summary>
    /// QType instance for 64-bits floating point number type.
    /// </summary>
    static const QType* TYPE_INSTANCE_F64;

    /// <summary>
    /// QType instance for 4 x 32-bits packed floating point numbers type.
    /// </summary>
    static const QType* TYPE_INSTANCE_VF32;
    

};


// SPECIALIZATIONS
// ---------------

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<bool>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u8_q>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i8_q>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u16_q>();
    
/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i16_q>();
    
/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u32_q>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i32_q>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u64_q>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i64_q>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::f32_q>();

/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::f64_q>();
    
/// <summary>
/// Obtains the type information of a given basic C++ type.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained.</typeparam>
/// <returns>
/// The type information. The same instance will be returned always for each type, they are stored statically.
/// </returns>
template<>
QE_LAYER_COMMON_SYMBOLS const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::vf32_q>();
    

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTYPE__
