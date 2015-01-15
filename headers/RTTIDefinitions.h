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

#ifndef __RTTIDEFINITIONS__
#define __RTTIDEFINITIONS__

#include "QType.h"

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that serve as interfaces that are root classes: 
// It defines the following class elements:
// -An empty constructor
// -An empty virtual destructor
// -The As template method: Casts the object to a different type that is either an ascendant or a valid descendant. 
//                          It returns null if the destination type is not allowed.
// -The Is template method: Checks whether the object is an instance of a given class or any of its descendent 
//                          (returns True in that case).
// -The GetTypeClass static method: Gets information about the data type of the class. Returns an instance of QType 
//                                  which holds the information about the class and is unique during the application's lifecycle.
// -The internal _OverrideIs virtual method: Checks whether the object is an instance of a given class or any of its 
//                                           descendent. It is called from the Is method and must be overriden in every derived class.
// And just declares:
// -The GetTypeObject pure virtual method: Gets information about the data type of the object. This method must be 
//                                         overriden in every derived class. Returns an instance of QType which holds the information  
//                                         about the class of the object and is unique during the application's lifecycle.
// -The ToString pure virtual method: Obtains a string that represents the state of the object or its name.
// -The _OBJECT_TYPE static data member: The information about the data type of the class. It is unique during 
//                                       the application's lifecycle.
// This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_INTERFACE(className)                                                            \
                                                                                                        \
protected:                                                                                              \
                                                                                                        \
    className()                                                                                         \
    {                                                                                                   \
    }                                                                                                   \
                                                                                                        \
private:                                                                                                \
                                                                                                        \
    className(const className&);                                                                        \
                                                                                                        \
    className& operator=(const className&);                                                             \
                                                                                                        \
public:                                                                                                 \
                                                                                                        \
    virtual ~className()                                                                                \
    {                                                                                                   \
    }                                                                                                   \
                                                                                                        \
    template<class DestinationT>                                                                        \
    DestinationT* As()                                                                                  \
    {                                                                                                   \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                        \
                                                               rcast_q(this, DestinationT*) :           \
                                                               null_q;                                  \
    }                                                                                                   \
                                                                                                        \
    template<class DestinationT>                                                                        \
    const DestinationT* As() const                                                                      \
    {                                                                                                   \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                        \
                                                               rcast_q(this, const DestinationT*) :     \
                                                               null_q;                                  \
    }                                                                                                   \
                                                                                                        \
    template<class T>                                                                                   \
    bool Is() const                                                                                     \
    {                                                                                                   \
        return this->_OverrideIs(T::GetTypeClass());                                                    \
    }                                                                                                   \
                                                                                                        \
    virtual Kinesis::QuimeraEngine::Common::DataTypes::string_q ToString() const=0;                     \
                                                                                                        \
protected:                                                                                              \
                                                                                                        \
    virtual bool _OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const       \
    {                                                                                                   \
        return className::_OBJECT_TYPE == pType;                                                        \
    }                                                                                                   \
                                                                                                        \
public:                                                                                                 \
                                                                                                        \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                       \
    {                                                                                                   \
        return className::_OBJECT_TYPE;                                                                 \
    }                                                                                                   \
                                                                                                        \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const=0;            \
                                                                                                        \
private:                                                                                                \
                                                                                                        \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* _OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for abstract classes that are root classes: 
// It defines the following class elements:
// -The As template method: Casts the object to a different type that is either an ascendant or a valid descendant. 
//                          It returns null if the destination type is not allowed.
// -The Is template method: Checks whether the object is an instance of a given class or any of its descendent 
//                          (returns True in that case).
// -The GetTypeClass static method: Gets information about the data type of the class. Returns an instance of QType 
//                                  which holds the information about the class and is unique during the application's lifecycle.
// -The internal _OverrideIs virtual method: Checks whether the object is an instance of a given class or any of its 
//                                           descendent. It is called from the Is method and must be overriden in every derived class.
// And just declares:
// -The default constructor.
// -A virtual destructor.
// -The GetTypeObject pure virtual method: Gets information about the data type of the object. This method must be 
//                                         overriden in every derived class. Returns an instance of QType which holds the information  
//                                         about the class of the object and is unique during the application's lifecycle.
// -The ToString pure virtual method: Obtains a string that represents the state of the object or its name.
// -The _OBJECT_TYPE static data member: The information about the data type of the class. It is unique during 
//                                       the application's lifecycle.
// This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_ABSTRACT_CLASS(className)                                                       \
                                                                                                        \
protected:                                                                                              \
                                                                                                        \
    className();                                                                                        \
                                                                                                        \
private:                                                                                                \
                                                                                                        \
    className(const className&);                                                                        \
                                                                                                        \
    className& operator=(const className&);                                                             \
                                                                                                        \
public:                                                                                                 \
                                                                                                        \
    virtual ~className();                                                                               \
                                                                                                        \
    template<class DestinationT>                                                                        \
    DestinationT* As()                                                                                  \
    {                                                                                                   \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                        \
                                                               rcast_q(this, DestinationT*) :           \
                                                               null_q;                                  \
    }                                                                                                   \
                                                                                                        \
    template<class DestinationT>                                                                        \
    const DestinationT* As() const                                                                      \
    {                                                                                                   \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                        \
                                                               rcast_q(this, const DestinationT*) :     \
                                                               null_q;                                  \
    }                                                                                                   \
                                                                                                        \
    template<class T>                                                                                   \
    bool Is() const                                                                                     \
    {                                                                                                   \
        return this->_OverrideIs(T::GetTypeClass());                                                    \
    }                                                                                                   \
                                                                                                        \
    virtual Kinesis::QuimeraEngine::Common::DataTypes::string_q ToString() const=0;                     \
                                                                                                        \
protected:                                                                                              \
                                                                                                        \
    virtual bool _OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const       \
    {                                                                                                   \
        return className::_OBJECT_TYPE == pType;                                                        \
    }                                                                                                   \
                                                                                                        \
public:                                                                                                 \
                                                                                                        \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                       \
    {                                                                                                   \
        return className::_OBJECT_TYPE;                                                                 \
    }                                                                                                   \
                                                                                                        \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const=0;            \
                                                                                                        \
private:                                                                                                \
                                                                                                        \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* _OBJECT_TYPE;


// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 1 class that provides RTTI functionalities: 
// It automates the overriding of base class's virtual methods.
// This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName: The name of the base class from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(className, baseClassName)                              \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    template<class DestinationT>                                                                    \
    DestinationT* As()                                                                              \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, DestinationT*) :       \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class DestinationT>                                                                    \
    const DestinationT* As() const                                                                  \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, const DestinationT*) : \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class T>                                                                               \
    bool Is() const                                                                                 \
    {                                                                                               \
        return this->_OverrideIs(T::GetTypeClass());                                                \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool _OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const   \
    {                                                                                               \
        return className::_OBJECT_TYPE == pType ||                                                  \
                baseClassName::_OverrideIs(pType);                                                  \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* _OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 2 classes that provides RTTI functionalities: 
// It automates the overriding of base class's virtual methods.
// This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the base classes from which the class inherits.
// -baseClassName2: The name of one of the base classes from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_2_CLASSES(className, baseClassName1, baseClassName2)           \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    template<class DestinationT>                                                                    \
    DestinationT* As()                                                                              \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, DestinationT*) :       \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class DestinationT>                                                                    \
    const DestinationT* As() const                                                                  \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, const DestinationT*) : \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class T>                                                                               \
    bool Is() const                                                                                 \
    {                                                                                               \
        return this->_OverrideIs(T::GetTypeClass());                                                \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool _OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const   \
    {                                                                                               \
        return className::_OBJECT_TYPE == pType    ||                                               \
                baseClassName1::_OverrideIs(pType) ||                                               \
                baseClassName2::_OverrideIs(pType);                                                 \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* _OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 3 classes that provides RTTI functionalities: 
// It automates the overriding of base class's virtual methods.
// This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the base classes from which the class inherits.
// -baseClassName2: The name of one of the base classes from which the class inherits.
// -baseClassName3: The name of one of the base classes from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_3_CLASSES(className, baseClassName1, baseClassName2, baseClassName3) \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    template<class DestinationT>                                                                    \
    DestinationT* As()                                                                              \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, DestinationT*) :       \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class DestinationT>                                                                    \
    const DestinationT* As() const                                                                  \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, const DestinationT*) : \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class T>                                                                               \
    bool Is() const                                                                                 \
    {                                                                                               \
        return this->_OverrideIs(T::GetTypeClass());                                                \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool _OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const   \
    {                                                                                               \
        return className::_OBJECT_TYPE == pType    ||                                               \
                baseClassName1::_OverrideIs(pType) ||                                               \
                baseClassName2::_OverrideIs(pType) ||                                               \
                baseClassName3::_OverrideIs(pType);                                                 \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* _OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 4 classes that provides RTTI functionalities: 
// It automates the overriding of base class's virtual methods.
// This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the base classes from which the class inherits.
// -baseClassName2: The name of one of the base classes from which the class inherits.
// -baseClassName3: The name of one of the base classes from which the class inherits.
// -baseClassName4: The name of one of the base classes from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_4_CLASSES(className, baseClassName1, baseClassName2, baseClassName3, baseClassName4) \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    template<class DestinationT>                                                                    \
    DestinationT* As()                                                                              \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, DestinationT*) :       \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class DestinationT>                                                                    \
    const DestinationT* As() const                                                                  \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, const DestinationT*) : \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class T>                                                                               \
    bool Is() const                                                                                 \
    {                                                                                               \
        return this->_OverrideIs(T::GetTypeClass());                                                \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool _OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const   \
    {                                                                                               \
        return className::_OBJECT_TYPE == pType    ||                                               \
                baseClassName1::_OverrideIs(pType) ||                                               \
                baseClassName2::_OverrideIs(pType) ||                                               \
                baseClassName3::_OverrideIs(pType) ||                                               \
                baseClassName4::_OverrideIs(pType);                                                 \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* _OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 5 classes that provides RTTI functionalities: 
// It automates the overriding of base class's virtual methods.
// This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the base classes from which the class inherits.
// -baseClassName2: The name of one of the base classes from which the class inherits.
// -baseClassName3: The name of one of the base classes from which the class inherits.
// -baseClassName4: The name of one of the base classes from which the class inherits.
// -baseClassName5: The name of one of the base classes from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_5_CLASSES(className, baseClassName1, baseClassName2, baseClassName3, baseClassName4, baseClassName5) \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    template<class DestinationT>                                                                    \
    DestinationT* As()                                                                              \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, DestinationT*) :       \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class DestinationT>                                                                    \
    const DestinationT* As() const                                                                  \
    {                                                                                               \
        return this->_OverrideIs(DestinationT::GetTypeClass()) ?                                    \
                                                               rcast_q(this, const DestinationT*) : \
                                                               null_q;                              \
    }                                                                                               \
                                                                                                    \
    template<class T>                                                                               \
    bool Is() const                                                                                 \
    {                                                                                               \
        return this->_OverrideIs(T::GetTypeClass());                                                \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::_OBJECT_TYPE;                                                             \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool _OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const   \
    {                                                                                               \
        return className::_OBJECT_TYPE == pType    ||                                               \
                baseClassName1::_OverrideIs(pType) ||                                               \
                baseClassName2::_OverrideIs(pType) ||                                               \
                baseClassName3::_OverrideIs(pType) ||                                               \
                baseClassName4::_OverrideIs(pType) ||                                               \
                baseClassName5::_OverrideIs(pType);                                                 \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* _OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities to define the instance of QType.
// -className: The name of the class inside which the QType instance is declared.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_TYPE_DEFINITION(className) const Kinesis::QuimeraEngine::Common::DataTypes::QType* className::_OBJECT_TYPE = new Kinesis::QuimeraEngine::Common::DataTypes::QType(QE_L(#className));



#endif // __RTTIDEFINITIONS__
