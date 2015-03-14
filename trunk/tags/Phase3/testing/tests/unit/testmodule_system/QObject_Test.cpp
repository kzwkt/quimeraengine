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

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QObject.h"

#include "QObjectTestClasses.h"

using Kinesis::QuimeraEngine::Core::QObject;
using Kinesis::QuimeraEngine::Core::Test::QObjectMockA;
using Kinesis::QuimeraEngine::Core::Test::QObjectMockB;
using Kinesis::QuimeraEngine::Core::Test::QObjectMockInterface;
using Kinesis::QuimeraEngine::Core::Test::QObjectMockDerivedA;


QTEST_SUITE_BEGIN( QObject_TestSuite )


/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the pointed type.
/// </summary>
QTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsAncestor_Test )
{
    // [Preparation]
    QObjectMockDerivedA* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockA AncestorType;

	// [Execution]
    AncestorType* pResult = OBJECT->As<AncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination is a descendent of the pointed type.
/// </summary>
QTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsDescendent_Test )
{
    // [Preparation]
    QObject* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockDerivedA DescendentType;

	// [Execution]
    DescendentType* pResult = OBJECT->As<DescendentType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is the same as object's type.
/// </summary>
QTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsSameAsObjects_Test )
{
    // [Preparation]
    typedef QObjectMockA SameType;
    SameType* OBJECT = new SameType();
    
	// [Execution]
    SameType* pResult = OBJECT->As<SameType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the actual object's type.
/// </summary>
QTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsAncestorOfObjectNotPointer_Test )
{
    // [Preparation]
    QObject* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockInterface OtherBranchAncestorType;

	// [Execution]
    OtherBranchAncestorType* pResult = OBJECT->As<OtherBranchAncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns a null pointer when the destination type belongs to a different branch in the class hierarchy.
/// </summary>
QTEST_CASE ( As1_ReturnsNullWhenDestinationTypeBelongsToDifferentHierarchyBranch_Test )
{
    // [Preparation]
    QObjectMockA* OBJECT = new QObjectMockA();
    typedef QObjectMockB OtherBranchType;

	// [Execution]
    OtherBranchType* pResult = OBJECT->As<OtherBranchType>();

    // [Verification]
    BOOST_CHECK(pResult == null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns null when the destination type is a descendent of the type of the object.
/// </summary>
QTEST_CASE ( As1_ReturnsNullWhenDestinationTypeIsDescendentOfObjectType_Test )
{
    // [Preparation]
    QObjectMockA* OBJECT = new QObjectMockA();
    typedef QObjectMockDerivedA DescendentOfObjectType;

	// [Execution]
    DescendentOfObjectType* pResult = OBJECT->As<DescendentOfObjectType>();

    // [Verification]
    BOOST_CHECK(pResult == null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the pointed type.
/// </summary>
QTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsAncestor_Test )
{
    // [Preparation]
    const QObjectMockDerivedA* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockA AncestorType;

	// [Execution]
    const AncestorType* pResult = OBJECT->As<AncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination is a descendent of the pointed type.
/// </summary>
QTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsDescendent_Test )
{
    // [Preparation]
    const QObject* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockDerivedA DescendentType;

	// [Execution]
    const DescendentType* pResult = OBJECT->As<DescendentType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is the same as object's type.
/// </summary>
QTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsSameAsObjects_Test )
{
    // [Preparation]
    typedef QObjectMockA SameType;
    const SameType* OBJECT = new SameType();
    
	// [Execution]
    const SameType* pResult = OBJECT->As<SameType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the actual object's type.
/// </summary>
QTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsAncestorOfObjectNotPointer_Test )
{
    // [Preparation]
    const QObject* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockInterface OtherBranchAncestorType;

	// [Execution]
    const OtherBranchAncestorType* pResult = OBJECT->As<OtherBranchAncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns a null pointer when the destination type belongs to a different branch in the class hierarchy.
/// </summary>
QTEST_CASE ( As2_ReturnsNullWhenDestinationTypeBelongsToDifferentHierarchyBranch_Test )
{
    // [Preparation]
    const QObjectMockA* OBJECT = new QObjectMockA();
    typedef QObjectMockB OtherBranchType;

	// [Execution]
    const OtherBranchType* pResult = OBJECT->As<OtherBranchType>();

    // [Verification]
    BOOST_CHECK(pResult == null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns null when the destination type is a descendent of the type of the object.
/// </summary>
QTEST_CASE ( As2_ReturnsNullWhenDestinationTypeIsDescendentOfObjectType_Test )
{
    // [Preparation]
    const QObjectMockA* OBJECT = new QObjectMockA();
    typedef QObjectMockDerivedA DescendentOfObjectType;

	// [Execution]
    const DescendentOfObjectType* pResult = OBJECT->As<DescendentOfObjectType>();

    // [Verification]
    BOOST_CHECK(pResult == null_q);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination type is an ancestor of the pointed type.
/// </summary>
QTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsAncestor_Test )
{
    // [Preparation]
    QObjectMockDerivedA* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockA AncestorType;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<AncestorType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination is a descendent of the pointed type.
/// </summary>
QTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsDescendent_Test )
{
    // [Preparation]
    QObject* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockDerivedA DescendentType;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<DescendentType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination type is the same as object's type.
/// </summary>
QTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsSameAsObjects_Test )
{
    // [Preparation]
    typedef QObjectMockA SameType;
    SameType* OBJECT = new SameType();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<SameType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination type is an ancestor of the actual object's type.
/// </summary>
QTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsAncestorOfObjectNotPointer_Test )
{
    // [Preparation]
    QObject* OBJECT = new QObjectMockDerivedA();
    typedef QObjectMockInterface OtherBranchAncestorType;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<OtherBranchAncestorType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns False when the destination type belongs to a different branch in the class hierarchy.
/// </summary>
QTEST_CASE ( Is_ReturnsFalseWhenDestinationTypeBelongsToDifferentHierarchyBranch_Test )
{
    // [Preparation]
    QObjectMockA* OBJECT = new QObjectMockA();
    typedef QObjectMockB OtherBranchType;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OBJECT->Is<OtherBranchType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns False when the destination type is a descendent of the type of the object.
/// </summary>
QTEST_CASE ( Is_ReturnsFalseWhenDestinationTypeIsDescendentOfObjectType_Test )
{
    // [Preparation]
    QObjectMockA* OBJECT = new QObjectMockA();
    typedef QObjectMockDerivedA DescendentOfObjectType;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OBJECT->Is<DescendentOfObjectType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

// End - Test Suite: QObject
QTEST_SUITE_END()
