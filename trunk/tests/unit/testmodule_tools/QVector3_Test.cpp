// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../common/QuimeraEngineFixtures.h"

#include "QVector3.h"
using Kinesis::QuimeraEngine::Tools::Math::QVector3;

QE_TEST_SUITE_FIXTURE( QVector3_TestSuite_Fixture, "QVector3" )

BOOST_FIXTURE_TEST_SUITE( QVector3_TestSuite, QVector3_TestSuite_Fixture )

/// <summary>
/// Verifies whether the default constructor set all components to zero.
/// </summary>
BOOST_AUTO_TEST_CASE ( Constructor_0_Test )
{
    // Preparation
    QVector3 target;

    // Verification
    BOOST_CHECK_EQUAL( target.x, QFloat::_0 );
    BOOST_CHECK_EQUAL( target.y, QFloat::_0 );
    BOOST_CHECK_EQUAL( target.z, QFloat::_0 );
}

/// <summary>
/// Verifies whether the constructor set all components to a concrete value.
/// </summary>
BOOST_AUTO_TEST_CASE ( Constructor_1_Test )
{
    // Preparation
    QVector3 target(QFloat::_0_5);
    
    // Verification
    BOOST_CHECK_EQUAL( target.x, QFloat::_0_5 );
    BOOST_CHECK_EQUAL( target.y, QFloat::_0_5 );
    BOOST_CHECK_EQUAL( target.z, QFloat::_0_5 );
}

/// <summary>
/// Verifies that the assert fails when the vector is divided by zero.
/// </summary>
BOOST_AUTO_TEST_CASE ( OperatorDivision_DividedByZeroAssertionFails_Test )
{
    // Preparation
    QVector3 target;
    
    // Verification
    BOOST_CHECK_NO_THROW( target /= QFloat::_0 )
    /*try
    {
        ;
    }
    catch(...)
    {
        BOOST_MESSAGE("Assertion Failed");
    }*/
}

// End - Test Suite: QVector3
BOOST_AUTO_TEST_SUITE_END()
