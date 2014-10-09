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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;
#include <boost/mpl/list.hpp>

#include "../../testsystem/TestingExternalDefinitions.h"

#include "SQTypeExtensions.h"

#include "QDerivedFromObject.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQTypeExtensions;
using Kinesis::QuimeraEngine::Common::DataTypes::Test::QDerivedFromObject;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Core::QObject;
using Kinesis::QuimeraEngine::Common::DataTypes::QType;

typedef boost::mpl::list<bool, u8_q, i8_q, u16_q, i16_q, u32_q, i32_q, u64_q, i64_q, f32_q, f64_q, string_q> TQTemplateBasicTypes;

// This struct is used as example of "custom type", not a QObject, not a basic type, not a string_q.
struct CustomType
{
};
    

QTEST_SUITE_BEGIN( SQTypeExtensions_TestSuite )

/// <summary>
/// Checks that a valid type is found when using basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType1_ValidTypeIsFoundWhenUsingBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T object;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is not found when using custom types.
/// </summary>
QTEST_CASE ( FindType1_ValidTypeIsNotFoundWhenUsingCustomTypes_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    CustomType object;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to non-constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType2_ValidTypeIsFoundWhenUsingPointerToNonConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T object;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(&object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using null pointers to non-constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType2_ValidTypeIsFoundWhenUsingNullPointerToNonConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T* pObject = null_q;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(pObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to non-constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType2_ValidTypeIsFoundWhenUsingPointersToPointerToNonConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T object;
    T* pObject = &object;;
    T** ppObject = &pObject;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to non-constant class derived from QObject.
/// </summary>
QTEST_CASE ( FindType2_ValidTypeIsFoundWhenUsingPointerToNonConstantQObjectDerived_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    QObject* pObject = new QDerivedFromObject();

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(pObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);

    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that a the type of QObject is returned when using null pointers to non-constant class derived from QObject.
/// </summary>
QTEST_CASE ( FindType2_QObjectTypeIsReturnedWhenUsingNullPointerToNonConstantQObjectDerived_Test )
{
    // [Preparation]
    const QType* OBJECT_TYPE = QObject::GetTypeClass();
    QDerivedFromObject* pObject = null_q;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(pObject);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, OBJECT_TYPE);
}

/// <summary>
/// Checks that a valid type is found when using pointers pointer to non-constant class derived from QObject.
/// </summary>
QTEST_CASE ( FindType2_ValidTypeIsFoundWhenUsingPointerToPointerToNonConstantQObjectDerived_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    QObject* pObject = new QDerivedFromObject();
    QObject** ppObject = &pObject;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);

    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that a valid type is not found when using pointers to non-constant custom types.
/// </summary>
QTEST_CASE ( FindType2_ValidTypeIsNotFoundWhenUsingPointerToNonConstantCustomType_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    CustomType object;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(&object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointerToConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    const T object = T();

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(&object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using null pointers to constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingNullPointerToConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    const T* pObject = null_q;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(pObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointersToPointerToConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    const T object = T();
    const T* pObject = &object;;
    const T** ppObject = &pObject;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to constant class derived from QObject.
/// </summary>
QTEST_CASE ( FindType3_ValidTypeIsFoundWhenUsingPointerToConstantQObjectDerived_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    const QObject* pObject = new QDerivedFromObject();

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(pObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);

    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that a the type of QObject is returned when using null pointers to constant class derived from QObject.
/// </summary>
QTEST_CASE ( FindType3_QObjectTypeIsReturnedWhenUsingNullPointerToConstantQObjectDerived_Test )
{
    // [Preparation]
    const QType* OBJECT_TYPE = QObject::GetTypeClass();
    const QDerivedFromObject* pObject = null_q;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(pObject);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, OBJECT_TYPE);
}

/// <summary>
/// Checks that a valid type is found when using pointers pointer to constant class derived from QObject.
/// </summary>
QTEST_CASE ( FindType3_ValidTypeIsFoundWhenUsingPointerToPointerToConstantQObjectDerived_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    const QObject* pObject = new QDerivedFromObject();
    const QObject** ppObject = &pObject;

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);

    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that a valid type is not found when using pointers to constant custom types.
/// </summary>
QTEST_CASE ( FindType3_ValidTypeIsNotFoundWhenUsingPointerToConstantCustomType_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    const CustomType object = CustomType();

    // [Execution]
    const QType* pType = SQTypeExtensions::FindType(&object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

// End - Test Suite: SQTypeExtensions
QTEST_SUITE_END()
