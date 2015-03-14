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

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive directly from QObject: It automates the
// overriding of QObject's virtual methods and the definition of the Kinesis::QuimeraEngine::Common::DataTypes::QType instance associated to the class.
// This macro must be placed inside the class. Note that the macro includes visibility modifiers that may
// affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_OBJECT(className)                                              \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const    \
    {                                                                                               \
        return className::OBJECT_TYPE == pType;                                                     \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from either an interface or a class that inherits 
// from QObject: It automates the overriding of QObject's virtual methods and the definition of the Kinesis::QuimeraEngine::Common::DataTypes::QType instance 
// associated to the class. This macro must be placed inside the class. Note that the macro includes visibility 
// modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName: The name of the class (derived from QObject) or interface from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(className, baseClassName)                              \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const    \
    {                                                                                               \
        return className::OBJECT_TYPE == pType ||                                                   \
                baseClassName::OverrideIs(pType);                                                   \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 2 classes that may be either an interface or 
// a class that inherits from QObject: It automates the overriding of QObject's virtual methods and the definition 
// of the QType instance associated to the class. This macro must be placed inside the class. Note that the macro 
// includes visibility modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName2: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_2_CLASSES(className, baseClassName1, baseClassName2) \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const    \
    {                                                                                               \
        return className::OBJECT_TYPE == pType    ||                                                \
                baseClassName1::OverrideIs(pType) ||                                                \
                baseClassName2::OverrideIs(pType);                                                  \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 3 classes that may be either an interface or 
// a class that inherits from QObject: It automates the overriding of QObject's virtual methods and the definition 
// of the QType instance associated to the class. This macro must be placed inside the class. Note that the macro 
// includes visibility modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName2: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName3: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_3_CLASSES(className, baseClassName1, baseClassName2, baseClassName3) \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const    \
    {                                                                                               \
        return className::OBJECT_TYPE == pType    ||                                                \
                baseClassName1::OverrideIs(pType) ||                                                \
                baseClassName2::OverrideIs(pType) ||                                                \
                baseClassName3::OverrideIs(pType);                                                  \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 4 classes that may be either an interface or 
// a class that inherits from QObject: It automates the overriding of QObject's virtual methods and the definition 
// of the QType instance associated to the class. This macro must be placed inside the class. Note that the macro 
// includes visibility modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName2: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName3: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName4: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_4_CLASSES(className, baseClassName1, baseClassName2, baseClassName3, baseClassName4) \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const    \
    {                                                                                               \
        return className::OBJECT_TYPE == pType    ||                                                \
                baseClassName1::OverrideIs(pType) ||                                                \
                baseClassName2::OverrideIs(pType) ||                                                \
                baseClassName3::OverrideIs(pType) ||                                                \
                baseClassName4::OverrideIs(pType);                                                  \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities for classes that derive from 5 classes that may be either an interface or 
// a class that inherits from QObject: It automates the overriding of QObject's virtual methods and the definition 
// of the QType instance associated to the class. This macro must be placed inside the class. Note that the macro 
// includes visibility modifiers that may affect the subsequent class' members.
// -className: The name of the class inside which this macro is placed.
// -baseClassName1: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName2: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName3: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName4: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// -baseClassName5: The name of one of the classes (derived from QObject) or interfaces from which the class inherits.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_DERIVED_FROM_5_CLASSES(className, baseClassName1, baseClassName2, baseClassName3, baseClassName4, baseClassName5) \
                                                                                                    \
public:                                                                                             \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeClass()                   \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
    virtual const Kinesis::QuimeraEngine::Common::DataTypes::QType* GetTypeObject() const           \
    {                                                                                               \
        return className::OBJECT_TYPE;                                                              \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
                                                                                                    \
    virtual bool OverrideIs(const Kinesis::QuimeraEngine::Common::DataTypes::QType* pType) const    \
    {                                                                                               \
        return className::OBJECT_TYPE == pType    ||                                                \
                baseClassName1::OverrideIs(pType) ||                                                \
                baseClassName2::OverrideIs(pType) ||                                                \
                baseClassName3::OverrideIs(pType) ||                                                \
                baseClassName4::OverrideIs(pType) ||                                                \
                baseClassName5::OverrideIs(pType);                                                  \
    }                                                                                               \
                                                                                                    \
    static const Kinesis::QuimeraEngine::Common::DataTypes::QType* OBJECT_TYPE;

// --------------------------------------------------------------------------------------------------------
// Quimera Engine's RTTI utilities to define the instance of QType.
// -className: The name of the class inside which the QType instance is declared.
// --------------------------------------------------------------------------------------------------------
#define QE_RTTI_SUPPORT_TYPE_DEFINITION(className) const Kinesis::QuimeraEngine::Common::DataTypes::QType* className::OBJECT_TYPE = new Kinesis::QuimeraEngine::Common::DataTypes::QType(QE_L(#className));



#endif // __RTTIDEFINITIONS__
