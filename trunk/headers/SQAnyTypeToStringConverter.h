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

#ifndef __SQANYTYPETOSTRINGCONVERTER__
#define __SQANYTYPETOSTRINGCONVERTER__

#include "SystemDefinitions.h"

#include "DataTypesDefinitions.h"
#include "SQInteger.h"
#include "QObject.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Provides utilities to convert any data type to its representation as string.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS SQAnyTypeToStringConverter
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQAnyTypeToStringConverter();
    

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Converts an instance of any type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// Any type that does not belong to the list of recognized types (see next) will not be converted.
    /// Instead, a string containing the text "<Unknown>" will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
    /// <param name="object">[IN] The instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_q Convert(const T &object)
    {
        // See template specializations below.
        static const string_q UNKNOWN_TYPE("<Unknown>");
        return UNKNOWN_TYPE;
    }
    
    /// <summary>
    /// Converts a pointer-to-non-constant-type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// The string will contain both the memory address contained in the pointer (hexadecimal number, using the suffix "0x") and 
    /// the representation as a string of the instance it points to, in that order, separated with a white-space. If the pointer points to another pointer, 
    /// then both will be dereferenced; this is the maximum number of dereferences supported. Example: int** --> "0x10AFB34D 0x90AFB11A 256".<br/>
    /// If the pointer is null, the resultant string will only contain the text "<Null>".<br/>
    /// Any type that does not belong to the list of recognized types (see next) will not be converted.
    /// Instead, a string containing the text "<Unknown>" will be returned after the memory address.
    /// </remarks>
    /// <typeparam name="T">The type of the pointer to be converted. Recognized types are: pointers to non-constant basic data types, 
    /// pointers to non-constant string_q, pointers to non-constant QObject or derived classes, pointers to already mentioned types.</typeparam>
    /// <param name="pObject">[IN] The pointer to the instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_q Convert(T* pObject)
    {
        return SQAnyTypeToStringConverter::Convert(ccast_q(pObject, const T*));
    }
    
    /// <summary>
    /// Converts a pointer-to-constant-type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// The string will contain both the memory address contained in the pointer (hexadecimal number, using the suffix "0x") and 
    /// the representation as a string of the instance it points to, in that order, separated with a white-space. If the pointer points to another pointer, 
    /// then both will be dereferenced; this is the maximum number of dereferences supported. Example: int** --> "0x10AFB34D 0x90AFB11A 256".<br/>
    /// If the pointer is null, the resultant string will only contain the text "<Null>".<br/>
    /// Any type that does not belong to the list of recognized types (see next) will not be converted.
    /// Instead, a string containing the text "<Unknown>" will be returned after the memory address.
    /// </remarks>
    /// <typeparam name="T">The type of the pointer to be converted. Recognized types are: pointers to constant basic data types, 
    /// pointers to constant string_q, pointers to constant QObject or derived classes, pointers to already mentioned types.</typeparam>
    /// <param name="pObject">[IN] The pointer to the instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_q Convert(const T* pObject)
    {
        using Kinesis::QuimeraEngine::Core::QObject;

        static const string_q HEXADECIMAL_PREFIX("0x");
        static const string_q WHITESPACE(" ");
        static const string_q NULL_POINTER("<Null>");
        
        string_q strResult;

        if(pObject != null_q)
        {
            // Prints the memory address to which the pointer points
            strResult.Append(HEXADECIMAL_PREFIX);
            strResult.Append(SQInteger::ToStringHexadecimal(rcast_q(pObject, pointer_uint_q)));
            strResult.Append(WHITESPACE);

            if(IsObject(pObject))
                // It is a pointer to an instance of a class derived from QObject
                strResult.Append(((const QObject*)pObject)->ToString());
            else
                // It is a pointer to either a basic data type or an unknown type
                strResult.Append(SQAnyTypeToStringConverter::Convert(*pObject));
        }
        else
        {
            // It is a null pointer
            strResult.Append(NULL_POINTER);
        }

        return strResult;
    }

private:
    
    /// <summary>
    /// Acts as a filter through overloading, used to determine whether a pointer is derived from QObject or not.
    /// </summary>
    /// <param name="pObject">[IN] The input pointer.</param>
    /// <returns>
    /// Always false.
    /// </returns>
    static bool IsObject(const void* pObject);
    
    /// <summary>
    /// Acts as a filter through overloading, used to determine whether a pointer is derived from QObject or not.
    /// </summary>
    /// <param name="pObject">[IN] The input pointer.</param>
    /// <returns>
    /// Always true.
    /// </returns>
    static bool IsObject(const Kinesis::QuimeraEngine::Core::QObject* pObject);
};


// SPECIALIZATIONS
// ---------------

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const bool &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const u8_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const u16_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const u32_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const u64_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const i8_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const i16_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const i32_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const i64_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const f32_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const f64_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const vf32_q &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS string_q SQAnyTypeToStringConverter::Convert(const string_q &object);


} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQANYTYPETOSTRINGCONVERTER__
