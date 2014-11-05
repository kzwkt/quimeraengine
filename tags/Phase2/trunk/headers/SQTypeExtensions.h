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

#ifndef __SQTYPEEXTENSIONS__
#define __SQTYPEEXTENSIONS__

#include "SystemDefinitions.h"

#include "DataTypesDefinitions.h"
#include "QObject.h"
#include "QType.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

/// <summary>
/// Provides some extensions for the QType class that can not be implemented in lower layers.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS SQTypeExtensions
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQTypeExtensions();


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Gets the type information of an object.
    /// </summary>
    /// <remarks>
    /// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
    /// Instead, a null pointer will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
    /// <param name="object">[IN] The object whose type information is to be retrieved.</param>
    /// <returns>
    /// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
    /// </returns>
    template<class T>
    static const QType* FindType(const T &object)
    {
        // See template specializations below.
        return null_q;
    }
    
    /// <summary>
    /// Gets the type information of an non-constant object provided as a pointer.
    /// </summary>
    /// <remarks>
    /// Note that it returns the pointed type, instead of treating the pointer-to-type as a type itself. The same applies for pointers-to-pointer.<br/>
    /// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
    /// Instead, a null pointer will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: pointers to basic data types, pointers to 
    /// string_q and pointers to QObject or derived classes.</typeparam>
    /// <param name="pObject">[IN] A pointer to the object whose type information is to be retrieved. If it is null, the type information will be obtained anyway; in the
    /// case it points to QObject type or any derived class, the type information returned will belong to the type pointed by the pointer (QObject, for example).</param>
    /// <returns>
    /// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
    /// </returns>
    template<class T>
    static const QType* FindType(T* pObject)
    {
        return SQTypeExtensions::FindType(ccast_q(pObject, const T*));
    }
    
    /// <summary>
    /// Gets the type information of a constant object provided as a pointer.
    /// </summary>
    /// <remarks>
    /// Note that it returns the pointed type, instead of treating the pointer-to-type as a type itself. The same applies for pointers-to-pointer.<br/>
    /// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
    /// Instead, a null pointer will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: pointers to constant basic data types, pointers to 
    /// constant string_q and pointers to constant QObject or derived classes.</typeparam>
    /// <param name="pObject">[IN] A pointer to the object whose type information is to be retrieved. If it is null, the type information will be obtained anyway; in the
    /// case it points to QObject type or any derived class, the type information returned will belong to the type pointed by the pointer (QObject, for example).</param>
    /// <returns>
    /// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
    /// </returns>
    template<class T>
    static const QType* FindType(const T* pObject)
    {
        using Kinesis::QuimeraEngine::Core::QObject;

        const QType* pType = null_q;

        if(IsObject(pObject))
        {
            // It is a pointer to an instance of a class derived from QObject

            if(pObject != null_q)
                pType = ((const QObject*)pObject)->GetTypeObject();
            else
                pType = QObject::GetTypeClass();
        }
        else
        {
            // It is a pointer to either a basic data type or an unknown type
            pType = SQTypeExtensions::FindType(*pObject);
        }

        return pType;
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
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const bool &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const u8_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const u16_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const u32_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const u64_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const i8_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const i16_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const i32_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const i64_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const f32_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const f64_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const vf32_q &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_q.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of QType that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
QE_LAYER_SYSTEM_SYMBOLS const QType* SQTypeExtensions::FindType(const string_q &object);

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQTYPEEXTENSIONS__
