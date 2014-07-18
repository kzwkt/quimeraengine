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

#ifndef __QOBJECT__
#define __QOBJECT__

#include "SystemDefinitions.h"

#include "QType.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Core
{

/// <summary>
/// The root class for all the high-level interfaces and classes in the engine. It provides support for
/// Quimera Engine's Runtime Type Information (RTTI) and string representation of objects.
/// </summary>
/// <remarks>
/// QObject must only be derived using public virtual inheritance.<br/>
/// It is an abstract class so it cannot be instanced.<br/>
/// It is thread-safe.
/// </remarks>
class QE_LAYER_SYSTEM_SYMBOLS QObject
{
    // CONSTRUCTORS
    // ---------------
protected:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QObject();

private:

    // Hidden, operation not allowed
    QObject(const QObject&);

    // Hidden, operation not allowed
    QObject& operator=(const QObject &);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>        
    virtual ~QObject();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Casts the object to a different QObject-derived class.
    /// </summary>
    /// <remarks>
    /// Only castings to classes that are either ascendants or descendants are allowed. Castings to
    /// void* are not allowed either.<br/>
    /// Use the Is method if your intention is to check whether an object is or inherits from a class.
    /// </remarks>
    /// <typeparam name="DestinationT">The destination type (not a pointer to it).</typeparam>
    /// <returns>
    /// A pointer to the casted object. If the casting was not possible, it returns null.
    /// </returns>
    template<class DestinationT>
    DestinationT* As()
    {
        return this->OverrideIs(DestinationT::GetTypeClass()) ?
                                                              rcast_q(this, DestinationT*) :
                                                              null_q;
    }

    /// <summary>
    /// Casts the object to a different QObject-derived class when object is constant.
    /// </summary>
    /// <remarks>
    /// Only castings to classes that are either ancestors or descendents are allowed. Castings to
    /// void* are not allowed either.<br/>
    /// Use the Is method if your intention is to check whether an object is or inherits from a class.
    /// </remarks>
    /// <typeparam name="DestinationT">The destination type (not a pointer to it).</typeparam>
    /// <returns>
    /// A constant pointer to the casted constant object. If the casting was not possible, it returns null.
    /// </returns>
    template<class DestinationT>
    const DestinationT* As() const
    {
        return this->OverrideIs(DestinationT::GetTypeClass()) ?
                                                              rcast_q(this, const DestinationT*) :
                                                              null_q;
    }

    /// <summary>
    /// Checks whether the object is an instance of a given class or any of its descendent.
    /// </summary>
    /// <typeparam name="T">The type which may or may not match the object's type or one of its ancestors.</typeparam>
    /// <returns>
    /// True if the object is an instance of the class or any of its ancestors; False otherwise.
    /// </returns>
    template<class T>
    bool Is() const
    {
        return this->OverrideIs(T::GetTypeClass());
    }

protected:

    /// <summary>
    /// Checks whether the object is an instance of a given class or any of its descendent.
    /// </summary>
    /// <remarks>
    /// It is called from the Is method and must be overriden in every derived class.
    /// </remarks>
    /// <param name="pType">[IN] The type which may or may not match the object's type or one of its ancestors.</param>
    /// <returns>
    /// True if the object is an instance of the class or any of its ancestors; False otherwise.
    /// </returns>
    virtual bool OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const=0;


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets information about the data type of the class.
    /// </summary>
    /// <returns>
    /// An instance of QType which holds the information about the class and is unique during the application's lifecycle.
    /// </returns>
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass();

    /// <summary>
    /// Gets information about the data type of the object.
    /// </summary>
    /// <remarks>
    /// This method must be overriden in every derived class.
    /// </remarks>
    /// <returns>
    /// An instance of QType which holds the information about the class of the object and is unique during the application's lifecycle.
    /// </returns>
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const=0;


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The information about the data type of the class. It is unique during the application's lifecycle.
    /// </summary>
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* OBJECT_TYPE;

};

} //namespace Core
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QOBJECT__
