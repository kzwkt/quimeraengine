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

#include "QLocalTimeZone.h"

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
#endif

#include "QLocalTimeZoneWhiteBox.h"
#include "QTimeZone.h"
#include "EQTextEncoding.h"

using Kinesis::QuimeraEngine::System::Timing::QLocalTimeZone;
using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;
using Kinesis::QuimeraEngine::System::Timing::Test::QLocalTimeZoneWhiteBox;


QTEST_SUITE_BEGIN( QLocalTimeZone_TestSuite )
    
/// <summary>
/// Checks that it stores a valid time zone.
/// </summary>
QTEST_CASE ( Constructor_ItStoresValidTimeZone_Test )
{
    // [Preparation]
    const QTimeZone* NOT_VALID_TIMEZONE = null_q;

	// [Execution]
    QLocalTimeZone localTimezone;
    
    // [Verification]
    const QTimeZone* pStoredTimeZone = localTimezone.Get();
    
    BOOST_CHECK_NE(pStoredTimeZone, NOT_VALID_TIMEZONE);
}

#if defined(QE_OS_WINDOWS) && QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input time zone key is not valid.
/// </summary>
QTEST_CASE ( GetWindowsEquivalentTimeZoneId_AssertionFailsWhenInputTimeZoneKeyIsNotValid_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const string_q NOT_VALID_TIMEZONE_KEY("ABCDEF");

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QLocalTimeZoneWhiteBox::GetWindowsEquivalentTimeZoneId(NOT_VALID_TIMEZONE_KEY);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif defined(QE_OS_WINDOWS) && QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that all the time zones of the current Windows version have an equivalent time zone id in the internal database.
/// </summary>
QTEST_CASE ( GetWindowsEquivalentTimeZoneId_WindowsEquivalencesVerification_Test )
{
    using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

    // [Preparation]
    const char* SUB_KEY = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones";
    PHKEY handle = new HKEY();
    char* szName = new char[255];
    DWORD uValueLength = 255;

    const bool ALL_TIMEZONES_HAVE_EQUIVALENCES = false;

    // Some time zones are not supported so they must be skipped
    std::vector<string_q> arUnsupportedTimeZones;
    arUnsupportedTimeZones.push_back(QE_L("Bahia Standard Time"));
    arUnsupportedTimeZones.push_back(QE_L("Dateline Standard Time"));
    arUnsupportedTimeZones.push_back(QE_L("Mid-Atlantic Standard Time"));
    arUnsupportedTimeZones.push_back(QE_L("Pacific Standard Time (Mexico)"));
    
	// [Execution]

    // Gets opens the registry key where all the time zones are stored
    LONG uRes = RegOpenKeyExA(HKEY_LOCAL_MACHINE, SUB_KEY, 0, KEY_READ | KEY_QUERY_VALUE, handle);

    int nKeyIndex = 0;
    std::vector<string_q>::const_iterator itTimeZoneName;
    bool bSomeTimeZonesHaveNoEquivalent = false;

    do
    {
        uRes = RegEnumKeyA(*handle, nKeyIndex, szName, uValueLength);
        nKeyIndex++;

        string_q strTimeZoneRegKeyName(szName);

        // The time zone is skipped if not supported
        {
            itTimeZoneName = arUnsupportedTimeZones.begin();

            while(itTimeZoneName != arUnsupportedTimeZones.end() && *itTimeZoneName != strTimeZoneRegKeyName)
                ++itTimeZoneName;

            if(itTimeZoneName != arUnsupportedTimeZones.end())
                continue;
        }

        string_q strTimeZoneId = QLocalTimeZoneWhiteBox::GetWindowsEquivalentTimeZoneId(strTimeZoneRegKeyName);

        if(strTimeZoneId.IsEmpty())
            bSomeTimeZonesHaveNoEquivalent = true;

        // Uncomment this for a quick review of which
        //if(strTimeZoneId.IsEmpty())
        //{
        //    ::OutputDebugStringA(QE_L("FAILED: "));
        //}

        //::OutputDebugStringA(szName);
        //::OutputDebugStringA(QE_L("\n"));

    } while(uRes == 0);

    // [Verification]
    BOOST_CHECK_EQUAL(!bSomeTimeZonesHaveNoEquivalent, ALL_TIMEZONES_HAVE_EQUIVALENCES);

	// [Cleaning]
    RegCloseKey(*handle);
    delete handle;
    delete[] szName;
}

/// <summary>
/// Checks that it returns an empty string when the input time zone key is not valid.
/// </summary>
QTEST_CASE ( GetWindowsEquivalentTimeZoneId_ItReturnsEmptyStringWhenInputTimeZoneKeyIsNotValid_Test )
{
    // [Preparation]
    const string_q NOT_VALID_TIMEZONE_KEY("ABCDEF");
    const string_q EMPTY_STRING(string_q::GetEmpty());

	// [Execution]
    string_q strEquivalentTimeZoneId = QLocalTimeZoneWhiteBox::GetWindowsEquivalentTimeZoneId(NOT_VALID_TIMEZONE_KEY);
    
    // [Verification]
    BOOST_CHECK(strEquivalentTimeZoneId == EMPTY_STRING);
}

#endif

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( Get_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: QLocalTimeZone
QTEST_SUITE_END()
