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

#include "QType.h"
#include "SQVF32.h"
#include "QAssertException.h"
#include "RTTITestClasses.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Common::DataTypes::QType;
using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Common::Test::InterfaceMock1;
using Kinesis::QuimeraEngine::Common::Test::DerivedFromInterfaceA;

// Type used in some tests as a non-basic type nor string
struct NonBasicType
{
};
    
typedef boost::mpl::list<bool, u8_q, i8_q, u16_q, i16_q, u32_q, i32_q, u64_q, i64_q, f32_q, f64_q, string_q> TQTemplateBasicTypes;

    
QTEST_SUITE_BEGIN( QType_TestSuite )

/// <summary>
/// Checks that every argument is correctly set to the class attributes.
/// </summary>
QTEST_CASE ( Constructor_ValuesAreCorrectlySet_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    const string_q EXPECTED_NAME(QE_L("TYPE NAME"));

	// [Execution]
    QType type(EXPECTED_NAME);
    
    // [Verification]
    string_q strName = type.GetName();

    BOOST_CHECK(strName == EXPECTED_NAME);
}

/// <summary>
/// Checks that it returns True when instances are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenInstancesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType& RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenInstancesAreNotEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME1"));
    const QType RIGHT_OPERAND(QE_L("TYPE NAME2"));
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are not equal, even if their attributes are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenInstancesAreNotEqualEvenIfAttributesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenInstancesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType& RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when instances are not equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenInstancesAreNotEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME1"));
    const QType RIGHT_OPERAND(QE_L("TYPE NAME2"));
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when instances are not equal, even if their attributes are equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenInstancesAreNotEqualEvenIfAttributesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetName_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns8BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "u8";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<u8_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns8BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "i8";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<i8_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns16BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "u16";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<u16_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns16BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "i16";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<i16_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns32BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "u32";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<u32_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns32BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "i32";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<i32_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns64BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "u64";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<u64_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns64BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "i64";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<i64_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns32BitsFloatingPointType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "f32";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<f32_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns64BitsFloatingPointType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "f64";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<f64_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_Returns4x32BitsPackedFloatingPointType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "vf32";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<vf32_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_ReturnsStringType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "string";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<string_q>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
QTEST_CASE ( FindType1_ReturnsVoidType_Test )
{
    // [Preparation]
    const string_q EXPECTED_TYPE = "void";

	// [Execution]
    const QType* pQTypePointer = QType::FindType<void>();
    string_q strType = pQTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that null pointer is returned when non basic type is passed.
/// </summary>
QTEST_CASE ( FindType1_ReturnsNullPointerWithNonBasicType_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;

	// [Execution]
    const QType* pQTypePointer = QType::FindType<NonBasicType>();
    
    // [Verification]
    BOOST_CHECK(pQTypePointer == NULL_POINTER);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing zero elements as initial capacity.
/// </summary>
QTEST_CASE ( FindType1_AssertionThrownWithNonBasicType_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QType::FindType<NonBasicType>();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that a valid type is found when using basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType2_ValidTypeIsFoundWhenUsingBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T object;

    // [Execution]
    const QType* pType = QType::FindType(object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is not found when using custom types.
/// </summary>
QTEST_CASE ( FindType2_ValidTypeIsNotFoundWhenUsingNonBasicTypes_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    NonBasicType object;

    // [Execution]
    const QType* pType = QType::FindType(object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to non-constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointerToNonConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T object;

    // [Execution]
    const QType* pType = QType::FindType(&object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using null pointers to non-constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingNullPointerToNonConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T* pObject = null_q;

    // [Execution]
    const QType* pType = QType::FindType(pObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to non-constant basic types or string.
/// </summary>
QTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointersToPointerToNonConstantBasicTypesOrString_Test, TQTemplateBasicTypes )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    T object;
    T* pObject = &object;;
    T** ppObject = &pObject;

    // [Execution]
    const QType* pType = QType::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is not found when using pointers to non-constant custom types.
/// </summary>
QTEST_CASE ( FindType3_ValidTypeIsNotFoundWhenUsingPointerToNonConstantNonBasicType_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    NonBasicType object;

    // [Execution]
    const QType* pType = QType::FindType(&object);

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
    const QType* pType = QType::FindType(&object);

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
    const QType* pType = QType::FindType(pObject);

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
    const QType* pType = QType::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is not found when using pointers to constant custom types.
/// </summary>
QTEST_CASE ( FindType3_ValidTypeIsNotFoundWhenUsingPointerToConstantNonBasicType_Test )
{
    // [Preparation]
    const QType* NULL_POINTER = null_q;
    const NonBasicType object = NonBasicType();

    // [Execution]
    const QType* pType = QType::FindType(&object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

// End - Test Suite: QType
QTEST_SUITE_END()
