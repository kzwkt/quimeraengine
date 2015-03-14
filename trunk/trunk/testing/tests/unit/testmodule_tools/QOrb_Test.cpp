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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QOrb.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseOrb;
using Kinesis::QuimeraEngine::Tools::Math::QOrb;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;

typedef boost::mpl::list<QVector2, QVector3, QVector4> TQTemplateTypes;


QTEST_SUITE_BEGIN( QOrb_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QOrb<T> orbUT;

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets orb's center and radius properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_5;

    const QOrb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QOrb<T> orbUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets orb's point and radius properly.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_5;

    const QBaseOrb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QOrb<T> orbUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
QTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_5;

	// [Execution]
    QOrb<T> orbUT(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned orb has not changed since the last time the test was executed.
/// </summary>
QTEST_CASE_TEMPLATE ( GetUnitOrb_ValueHasNotChanged_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS[] = { SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;


	// [Execution]
    QOrb<T> orbUT = QOrb<T>::GetUnitOrb();

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a orb is correctly assigned to another orb.
/// </summary>
QTEST_CASE_TEMPLATE ( OperatorAssignation_OrbIsAssignedProperlyToAnother_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_4;

    const QBaseOrb<T> OTHER_ORB = QBaseOrb<T>(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QOrb<T> orbUT;
    orbUT = OTHER_ORB;

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that it returns false when the orb doesn't contain the point.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenTheOrbDoesNotContainThePoint_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_POINT[] = { SQFloat::_9, SQFloat::_8, SQFloat::_7, SQFloat::_1 };

    const QOrb<T> ORB( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );
    const T POINT = T(VECTOR_COMPONENTS_POINT);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bIsContained = ORB.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bIsContained, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the orb contains the point (and it doesn't lay on the surface).
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenTheOrbContainsThePoint_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_2, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_POINT[] = { SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1 };

    const QOrb<T> ORB( T(VECTOR_COMPONENTS_CENTER), SQFloat::_2 );
    const T POINT = T(VECTOR_COMPONENTS_POINT);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIsContained = ORB.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bIsContained, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the point lies on the surface of the orb.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenThePointLiesOnTheSurfaceOfTheOrb_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_POINT[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const QOrb<T> ORB( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );
    const T POINT = T(VECTOR_COMPONENTS_POINT);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIsContained = ORB.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bIsContained, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_AssertionFailsWhenRadiusEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const QOrb<T> ORB( T(VECTOR_COMPONENTS), SQFloat::_0 );
    const T POINT = T(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ORB.Contains(POINT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when all points coincide.
/// </summary>
QTEST_CASE_TEMPLATE ( Contains_ReturnsExpectedResultWhenRadiusEqualsZero_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    float_q VECTOR1_COMPONENTS[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_7 };
    float_q VECTOR2_COMPONENTS[] = { SQFloat::_4, SQFloat::_2, SQFloat::_3, SQFloat::_7 };

    const QOrb<T> ORB( T(VECTOR1_COMPONENTS), SQFloat::_0 );
    const T POINT_COINCIDENT = T(VECTOR1_COMPONENTS);
    const T POINT_NOT_COINCIDENT = T(VECTOR2_COMPONENTS);

    const bool EXPECTED_RESULT_COINCIDENT = true;
    const bool EXPECTED_RESULT_NOT_COINCIDENT = false;

	// [Execution]
    bool bResultCoincident = ORB.Contains(POINT_COINCIDENT);
    bool bResultNotCoincident = ORB.Contains(POINT_NOT_COINCIDENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultCoincident, EXPECTED_RESULT_COINCIDENT);
    BOOST_CHECK_EQUAL(bResultNotCoincident, EXPECTED_RESULT_NOT_COINCIDENT);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns false when orbs don't intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenOrbsDoNotIntersect_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_CENTER2[] = { SQFloat::_9, SQFloat::_9, SQFloat::_9, SQFloat::_1 };

    const QOrb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SQFloat::_1 );
    const QOrb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SQFloat::_1 );

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs intersect.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOrbsIntersect_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_CENTER2[] = { SQFloat::_2, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const QOrb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SQFloat::_1 );
    const QOrb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs are tangent.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOrbsAreTangent_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_CENTER2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const QOrb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SQFloat::_1 );
    const QOrb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs are the same.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOrbsAreTheSame_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const QOrb<T> ORB1( T(VECTOR_COMPONENTS_CENTER), SQFloat::_1 );
    const QOrb<T> ORB2 = ORB1;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs are tangent.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOneOrbIsContainedInOther_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_CENTER2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const QOrb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SQFloat::_9 );
    const QOrb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SQFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of one of the orbs equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenRadiusEqualsZero_Test, TQTemplateTypes )
{
    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_CENTER2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const QOrb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SQFloat::_0 );
    const QOrb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SQFloat::_1 );

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        ORB1.Intersection(ORB2);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        ORB2.Intersection(ORB1);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the radius of one of the orbs equals zero.
/// </summary>
QTEST_CASE_TEMPLATE ( Intersection_ReturnsExpectedResultWhenRadiusEqualsZero_Test, TQTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER1[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_1 };
    float_q VECTOR_COMPONENTS_CENTER2[] = { SQFloat::_3, SQFloat::_2, SQFloat::_3, SQFloat::_1 };

    const QOrb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SQFloat::_0 );
    const QOrb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SQFloat::_1 );
    const QOrb<T> ORB3( T(VECTOR_COMPONENTS_CENTER2), SQFloat::_2 );

    const bool EXPECTE_RESULT_INTERSECTION = true;
    const bool EXPECTE_RESULT_NO_INTERSECTION = false;

	// [Execution]
    bool bResultNoIntersection = ORB1.Intersection(ORB2);
    bool bResultIntersection = ORB1.Intersection(ORB3);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultIntersection, EXPECTE_RESULT_INTERSECTION);
    BOOST_CHECK_EQUAL(bResultNoIntersection, EXPECTE_RESULT_NO_INTERSECTION);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    float_q VECTOR_COMPONENTS_CENTER[] = { SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4 };
    const T VECTOR_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_q RADIUS = SQFloat::_5;
    const QOrb<T> ORB( VECTOR_FOR_CENTER, RADIUS );

    const string_q CENTER_STRING = VECTOR_FOR_CENTER.ToString();
    const string_q EXPECTED_STRING = string_q("OB(c(") + CENTER_STRING + QE_L("),r(") + string_q::FromFloat(RADIUS) + QE_L("))");

	// [Execution]
    string_q strReturnedString = ORB.ToString();

    // [Verification]
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: QOrb
QTEST_SUITE_END()
