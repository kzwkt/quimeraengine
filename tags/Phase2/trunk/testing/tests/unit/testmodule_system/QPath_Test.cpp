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

#include "QPath.h"

#include "EQComparisonType.h"

using Kinesis::QuimeraEngine::System::IO::FileSystem::QPath;

QTEST_SUITE_BEGIN( QPath_TestSuite )

/// <summary>
/// Checks that the resultant path equals "./" when the input string is empty.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsDotAndSeparatorWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_PATH("./");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the resultant path equals "/" when the input string has hostname.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsSeparatorWhenPathIsEmptyAndHasHostname_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname");
    const string_q EXPECTED_PATH("/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path only has hostname.
/// </summary>
QTEST_CASE ( Constructor_HostnameIsWhatExpectedWhenInputOnlyContainsHostname_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname");
    const string_q EXPECTED_HOSTNAME("hostname");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the resultant path equals input string when it is just a separator.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputIsSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/");
    const string_q EXPECTED_PATH("/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path has hostname and path is a separator.
/// </summary>
QTEST_CASE ( Constructor_HostnameIsWhatExpectedWhenInputContainsHostnameAndPathSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/");
    const string_q EXPECTED_HOSTNAME("hostname");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has hostname and path is a separator.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsHostnameAndPathSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/");
    const string_q EXPECTED_DIRECTORY("/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that the directory of the resultant path is what expected when input hostname has an at sign.
/// </summary>
QTEST_CASE ( Constructor_AtSignsAreAllowedInHostnames_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//user@hostname/");
    const string_q EXPECTED_HOSTNAME("user@hostname");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input directory is a tilde ("~").
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsTildeDirectoryOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("~/");
    const string_q EXPECTED_DIRECTORY("~/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when the directory starts with a tilde ("~").
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputDirectoryStartsWithTilde_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("~/path/");
    const string_q EXPECTED_DIRECTORY("~/path/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#endif

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has hostname and a common directory.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsHostnameAndCommonDirectory_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/path1/path2/");
    const string_q EXPECTED_DIRECTORY("/path1/path2/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path has hostname, directory and filename.
/// </summary>
QTEST_CASE ( Constructor_HostnameIsWhatExpectedWhenInputContainsHostnameDirectoryAndFilename_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/path1/filename.ext");
    const string_q EXPECTED_HOSTNAME("hostname");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has hostname, directory and filename.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsHostnameDirectoryAndFilename_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/path1/filename.ext");
    const string_q EXPECTED_DIRECTORY("/path1/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the filename of the resultant path is what expected when input path has hostname, directory and filename.
/// </summary>
QTEST_CASE ( Constructor_FilenameIsWhatExpectedWhenInputContainsHostnameDirectoryAndFilename_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/path1/filename.ext");
    const string_q EXPECTED_FILENAME("filename.ext");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetFilename() == EXPECTED_FILENAME);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has directory that starts with separator.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsDirectoryWithLeadingSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/path1/");
    const string_q EXPECTED_DIRECTORY("/path1/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the filename of the resultant path is what expected when input path has directory that starts with separator and has filename.
/// </summary>
QTEST_CASE ( Constructor_FilenameIsWhatExpectedWhenInputContainsDirectoryWithLeadingSeparatorAndFilename_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/path1/filename.ext");
    const string_q EXPECTED_FILENAME("filename.ext");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetFilename() == EXPECTED_FILENAME);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has relative directory that contains one dot segment.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsRelativeDirectoryWithOnlyOneDotSegment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("./");
    const string_q EXPECTED_DIRECTORY("./");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has relative directory that contains two dot segment.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsRelativeDirectoryWithTwoDotSegments_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("./../");
    const string_q EXPECTED_DIRECTORY("./../");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has relative directory that contains only two dot segment.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsRelativeDirectoryContainsOnlyTwoDotSegments_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("../");
    const string_q EXPECTED_DIRECTORY("../");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the input directory is not resolved when it contains dot segments.
/// </summary>
QTEST_CASE ( Constructor_InputDirectoryIsNotResolvedWhenItContainsDotSegments_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("./../path/../");
    const string_q EXPECTED_DIRECTORY("./../path/../");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path contains a drive and a directory.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsDriveAndDirectory_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("X:/path1/");
    const string_q EXPECTED_DIRECTORY("X:/path1/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path contains a drive and a directory without separation.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsDriveAndDirectoryWithoutSeparation_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("X:path1/");
    const string_q EXPECTED_DIRECTORY("X:path1/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path contains a drive only.
/// </summary>
QTEST_CASE ( Constructor_DirectoryIsWhatExpectedWhenInputContainsDriveOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("X:/");
    const string_q EXPECTED_DIRECTORY("X:/");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#endif

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains an IP enclosed into square brackets.
/// </summary>
QTEST_CASE ( Constructor_HostnameIsWhatExpectedWhenInputContainsIpEnclosedIntoSquareBrackets_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//[255.255.255.255]/");
    const string_q EXPECTED_HOSTNAME("[255.255.255.255]");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains an IP enclosed into square brackets and numbers are zeroes.
/// </summary>
QTEST_CASE ( Constructor_HostnameIsWhatExpectedWhenInputContainsIpEnclosedIntoSquareBracketsAndNumbersAreZeroes_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//[0.0.0.0]/");
    const string_q EXPECTED_HOSTNAME("[0.0.0.0]");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains an IP without square brackets.
/// </summary>
QTEST_CASE ( Constructor_HostnameIsWhatExpectedWhenInputContainsIpWithoutSquareBrackets_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.255.255.255/");
    const string_q EXPECTED_HOSTNAME("255.255.255.255");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains all the allowed characters.
/// </summary>
QTEST_CASE ( Constructor_HostnameIsWhatExpectedWhenInputContainsAllAllowedCharacters_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//ABCDEFGHIJKLMNOPQRSTUVWXYZ-abcdefghijklmnopqrstuvwxyz0123456789/");
    const string_q EXPECTED_HOSTNAME("ABCDEFGHIJKLMNOPQRSTUVWXYZ-abcdefghijklmnopqrstuvwxyz0123456789");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the filename of the resultant path is what expected when input path only contains a filename.
/// </summary>
QTEST_CASE ( Constructor_FilenameIsWhatExpectedWhenInputContainsFilenameOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("filename.ext");
    const string_q EXPECTED_FILENAME("filename.ext");

    // [Execution]
    QPath path(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetFilename() == EXPECTED_FILENAME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when hostname is empty.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenHostnameIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when hostname is empty and the path is a separator.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenHostnameIsEmptyAndPathIsSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("///");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when hostname starts with an hyphen ("-").
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenHostnameStartsWithHyphen_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//-hostname/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the IP starts with a square bracket ("[") but does not end with another square bracket ("]").
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenIpStartsWithSquareBracketButDoesNotEndWithAnotherSquareBracket_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//[255.255.255.255/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the IP ends with a square bracket ("]") but does not start with another square bracket ("[").
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenIpEndsWithSquareBracketButDoesNotStartWithAnotherSquareBracket_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.255.255.255]/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when an IP contains letters.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenIpContainsLetters_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255a.255.255.255/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a hostname contains dots.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenHostnameContainsDots_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//host.name/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when an IP contains hyphens ("-").
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenIpContainsHyphen_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255-.255.255.255/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the one of the parts of the IP is greater than 255.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenOneNumberOfIpIsGreaterThan255_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.256.255.255/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of one of the parts of the IP is greater than 3.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenLengthOfOnePartOfIpIsGreaterThan3_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.0000.255.255/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a hostname contains square brackets ("[", "]").
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenHostnameContainsSquareBracket_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname]/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a number of the IP is missing.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenOneNumberOfIpIsMissing_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.255.255/");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a all the numbers of the IP are empty.
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenNumbersOfTheIpAreEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.../");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the filename is too large (larger than 255 characters).
/// </summary>
QTEST_CASE ( Constructor_AssertionFailsWhenFilenameIsTooLarge_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/path/0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QPath path(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that an assertion fails when the path contains invalid characters.
    /// </summary>
    QTEST_CASE ( Constructor_AssertionFailsWhenPathContainsInvalidCharacters_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("start?\"<>|:end/");
        const bool ASSERTION_FAILED = true;

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            QPath path(INPUT_STRING);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }

    #endif

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that invalid characters are removed from the directory.
    /// </summary>
    QTEST_CASE ( Constructor_InvalidCharactersAreRemovedFromDirectory_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("/start?\"<>|:end/");
        const string_q EXPECTED_DIRECTORY("/startend/");

        // [Execution]
        QPath path(INPUT_STRING);

        // [Verification]
        BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
    }

    #endif
    
    /// <summary>
    /// Checks that invalid characters are removed from the hostname.
    /// </summary>
    QTEST_CASE ( Constructor_InvalidCharactersAreRemovedFromHostname_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("//abc_def?ghi#/");
        const string_q EXPECTED_HOSTNAME("abcdefghi");

        // [Execution]
        QPath path(INPUT_STRING);

        // [Verification]
        BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
    }

#endif
    
/// <summary>
/// Checks that the path is correctly copied.
/// </summary>
QTEST_CASE ( OperatorAssignment_PathIsCorrectlyCopied_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/path/filename.ext");
    const QPath EXPECTED_PATH(INPUT_STRING);
    const QPath SOURCE_PATH(INPUT_STRING);
    QPath path("/");

    // [Execution]
    path = SOURCE_PATH;

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that it returns True when paths are exactly the same.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenPathsAreExactlyEqual_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/path/filename.ext");
    const QPath PATH1(INPUT_STRING);
    const QPath PATH2(INPUT_STRING);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = PATH1 == PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that path comparisons are case-insensitive.
/// </summary>
QTEST_CASE ( OperatorEquality_PathComparisonsAreCaseInsensitive_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hoStname/PAth/filEName.eXt");
    const string_q INPUT_STRING2("//hostnaMe/path/filenaME.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = PATH1 == PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that path comparisons are case-sensitive.
/// </summary>
QTEST_CASE ( OperatorEquality_PathComparisonsAreCaseSensitive_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hoStname/PAth/filEName.eXt");
    const string_q INPUT_STRING2("//hostnaMe/path/filenaME.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = PATH1 == PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when hostnames are different.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenHostnamesAreDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hostname1/path/filename.ext");
    const string_q INPUT_STRING2("//hostname2/path/filename.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = PATH1 == PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when directories are different.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenDirectoriesAreDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hostname/path1/filename.ext");
    const string_q INPUT_STRING2("//hostname/path2/filename.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = PATH1 == PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when filenames are different.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenFilenamesAreDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hostname/path/filename1.ext");
    const string_q INPUT_STRING2("//hostname/path/filename2.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = PATH1 == PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when paths are exactly the same.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenPathsAreExactlyEqual_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname/path/filename.ext");
    const QPath PATH1(INPUT_STRING);
    const QPath PATH2(INPUT_STRING);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = PATH1 != PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that path comparisons are case-insensitive.
/// </summary>
QTEST_CASE ( OperatorInequality_PathComparisonsAreCaseInsensitive_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hoStname/PAth/filEName.eXt");
    const string_q INPUT_STRING2("//hostnaMe/path/filenaME.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = PATH1 != PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that path comparisons are case-sensitive.
/// </summary>
QTEST_CASE ( OperatorInequality_PathComparisonsAreCaseSensitive_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hoStname/PAth/filEName.eXt");
    const string_q INPUT_STRING2("//hostnaMe/path/filenaME.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = PATH1 != PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when hostnames are different.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenHostnamesAreDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hostname1/path/filename.ext");
    const string_q INPUT_STRING2("//hostname2/path/filename.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = PATH1 != PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when directories are different.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenDirectoriesAreDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hostname/path1/filename.ext");
    const string_q INPUT_STRING2("//hostname/path2/filename.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = PATH1 != PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when filenames are different.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenFilenamesAreDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1("//hostname/path/filename1.ext");
    const string_q INPUT_STRING2("//hostname/path/filename2.ext");
    const QPath PATH1(INPUT_STRING1);
    const QPath PATH2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = PATH1 != PATH2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that nothing is done when the path is the root directory "/".
/// </summary>
QTEST_CASE ( RemoveLastDirectory_NothingHappensWhenPathIsJustASeparator_Test )
{
    // [Preparation]
    QPath path("/");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that nothing is done when the path is the relative directory "./".
/// </summary>
QTEST_CASE ( RemoveLastDirectory_NothingHappensWhenDirectoryIsOneDot_Test )
{
    // [Preparation]
    QPath path("./");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that nothing is done when the path is the relative directory "../".
/// </summary>
QTEST_CASE ( RemoveLastDirectory_NothingHappensWhenDirectoryIsTwoDots_Test )
{
    // [Preparation]
    QPath path("../");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that nothing is done when the path is relative and only has one segment.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_NothingHappensWhenPathIsRelativeAndOnlyHasOneSegment_Test )
{
    // [Preparation]
    QPath path("path/");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the root directory remains when removing all the common directories.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_RootDirectoryRemainsWhenRemovingAllDirectories_Test )
{
    // [Preparation]
    QPath path("/path/");
    const QPath EXPECTED_PATH("/");

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the last directory is correctly removed and a triling separator is kept at the end.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_LastDirectoryIsCorrectlyRemovedAndTrailingSeparatorIsKept_Test )
{
    // [Preparation]
    QPath path("/path1/path2/");
    const QPath EXPECTED_PATH("/path1/");

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the last directory is correctly removed when it is a dot segment.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_LastDirectoryIsCorrectlyRemovedWhenItIsDotSegment_Test )
{
    // [Preparation]
    QPath path("/path1/path2/../");
    const QPath EXPECTED_PATH("/path1/path2/");

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the filename is not affected by this operation.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_FilenameIsNotAffected_Test )
{
    // [Preparation]
    QPath path("/path1/path2/filename");
    const QPath EXPECTED_PATH("/path1/filename");

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the hostname is not affected by this operation.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_HostnameIsNotAffected_Test )
{
    // [Preparation]
    QPath path("//hostname/");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that nothing is done when the directory is just a drive "x:/".
/// </summary>
QTEST_CASE ( RemoveLastDirectory_NothingHappensWhenDirectoryIsDrive_Test )
{
    // [Preparation]
    QPath path("x:/");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the last directory is removed when the path starts with a drive.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_LastDirectoryIsRemovedWhenPathStartsWithDrive_Test )
{
    // [Preparation]
    QPath path("x:/p1/p2/");
    const QPath EXPECTED_PATH("x:/p1/");

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that nothing is done when the directory is just a tilde "~/".
/// </summary>
QTEST_CASE ( RemoveLastDirectory_NothingHappensWhenDirectoryIsTilde_Test )
{
    // [Preparation]
    QPath path("~/");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

#endif

/// <summary>
/// Checks that nothing is done when the path only contains a filename.
/// </summary>
QTEST_CASE ( RemoveLastDirectory_NothingHappensWhenPathOnlyContainsFilename_Test )
{
    // [Preparation]
    QPath path("filename");
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.RemoveLastDirectory();

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the resultant directory ends with a separator.
/// </summary>
QTEST_CASE ( AppendDirectory_ResultantDirectoryEndsWithSeparator_Test )
{
    // [Preparation]
    QPath path("/path/");
    const string_q DIRECTORY("path2");
    const QPath EXPECTED_PATH("/path/path2/");

    // [Execution]
    path.AppendDirectory(DIRECTORY);

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that the operation does not affect the filename.
/// </summary>
QTEST_CASE ( AppendDirectory_FilenameIsNotAffected_Test )
{
    // [Preparation]
    QPath path("/path/filename");
    const string_q DIRECTORY("path2");
    const QPath EXPECTED_PATH("/path/path2/filename");

    // [Execution]
    path.AppendDirectory(DIRECTORY);

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

/// <summary>
/// Checks that dot segments can be added.
/// </summary>
QTEST_CASE ( AppendDirectory_DotSegmentsCanBeAdded_Test )
{
    // [Preparation]
    QPath path("/path/");
    const string_q DIRECTORY1("..");
    const string_q DIRECTORY2(".");
    const QPath EXPECTED_PATH("/path/.././");

    // [Execution]
    path.AppendDirectory(DIRECTORY1);
    path.AppendDirectory(DIRECTORY2);

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input string is empty.
/// </summary>
QTEST_CASE ( AppendDirectory_AssertionFailsWhenInputIsEmpty_Test )
{
    // [Preparation]
    QPath path("/path/");
    const string_q DIRECTORY = string_q::GetEmpty();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.AppendDirectory(DIRECTORY);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the directory name contains a slash ("/").
/// </summary>
QTEST_CASE ( AppendDirectory_AssertionFailsWhenContainsSlashes_Test )
{
    // [Preparation]
    QPath path("/path/");
    const string_q DIRECTORY("direc/tory");
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.AppendDirectory(DIRECTORY);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

    #if defined(QE_OS_WiNDOWS)

    /// <summary>
    /// Checks that an assertion fails when the directory name contains a backslash ("\\").
    /// </summary>
    QTEST_CASE ( AppendDirectory_AssertionFailsWhenContainsBackslashes_Test )
    {
        // [Preparation]
        QPath path("/path/");
        const string_q DIRECTORY("direc\\tory");
        const bool ASSERTION_FAILED = true;

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            path.AppendDirectory(DIRECTORY);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }
    
    /// <summary>
    /// Checks that an assertion fails when the directory name contains invalid characters.
    /// </summary>
    QTEST_CASE ( AppendDirectory_AssertionFailsWhenContainsInvalidCharacters_Test )
    {
        // [Preparation]
        QPath path("/path/");
        const string_q DIRECTORY("start?\"<>|:end");
        const bool ASSERTION_FAILED = true;

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            path.AppendDirectory(DIRECTORY);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }

    #endif

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that nothing is done when the input is empty.
/// </summary>
QTEST_CASE ( AppendDirectory_NothingHappensWhenInputIsEmpty_Test )
{
    // [Preparation]
    QPath path("/path/");
    const string_q DIRECTORY = string_q::GetEmpty();
    const QPath EXPECTED_PATH(path);

    // [Execution]
    path.AppendDirectory(DIRECTORY);

    // [Verification]
    BOOST_CHECK(path == EXPECTED_PATH);
}

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that invalid characters are removed from the name.
    /// </summary>
    QTEST_CASE ( AppendDirectory_InvalidCharactersAreRemoved_Test )
    {
        // [Preparation]
        QPath path("/path/");
        const string_q DIRECTORY("start?\"<>|:/\\end");
        const QPath EXPECTED_PATH("/path/startend/");

        // [Execution]
        path.AppendDirectory(DIRECTORY);

        // [Verification]
        BOOST_CHECK(path == EXPECTED_PATH);
    }

    #elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

    /// <summary>
    /// Checks that invalid characters are removed from the name.
    /// </summary>
    QTEST_CASE ( AppendDirectory_InvalidCharactersAreRemoved_Test )
    {
        // [Preparation]
        QPath path("/path/");
        const string_q DIRECTORY("start/end");
        const QPath EXPECTED_PATH("/path/startend/");

        // [Execution]
        path.AppendDirectory(DIRECTORY);

        // [Verification]
        BOOST_CHECK(path == EXPECTED_PATH);
    }

    #endif

#endif

/// <summary>
/// Checks that the filename is replaced when input path only contains filename.
/// </summary>
QTEST_CASE ( Resolve_FilenameIsReplacedWhenInputPathOnlyContainsFilename_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "g";
    const string_q EXPECTED_PATH = "//a/b/c/g";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the leading single dot segment is just removed.
/// </summary>
QTEST_CASE ( Resolve_LeadingSingleDotSegmentIsJustRemoved_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "./g";
    const string_q EXPECTED_PATH = "//a/b/c/g";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that a directory is added and the filename remains the same when the input contains just one directory.
/// </summary>
QTEST_CASE ( Resolve_DirectoryIsAddedAndFilenameRemainsSameWhenInputContainsJustOneDirectory_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "g/";
    const string_q EXPECTED_PATH = "//a/b/c/g/d";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that a single dot is treated as a filename.
/// </summary>
QTEST_CASE ( Resolve_SingleDotIsTreatedAsFilename_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = ".";
    const string_q EXPECTED_PATH = "//a/b/c/.";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that a single dot segment does nothing.
/// </summary>
QTEST_CASE ( Resolve_SingleDotSegmentDoesNothing_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "./";
    const string_q EXPECTED_PATH = "//a/b/c/d";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that two dots ("..") are treated as a filename.
/// </summary>
QTEST_CASE ( Resolve_TwoDotsAreTreatedAsFilename_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "..";
    const string_q EXPECTED_PATH = "//a/b/c/..";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the last directory is removed when the input path contains a two-dots segment.
/// </summary>
QTEST_CASE ( Resolve_LastDirectoryIsRemovedWhenInputPathContainsTwoDotsSegment_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "../";
    const string_q EXPECTED_PATH = "//a/b/d";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the last directory is removed and the filename is replaced when the input path contains a two-dots segment and a filename.
/// </summary>
QTEST_CASE ( Resolve_LastDirectoryIsRemovedAndFilenameIsReplacedWhenInputPathContainsTwoDotsSegmentAndFilename_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "../g";
    const string_q EXPECTED_PATH = "//a/b/g";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the last directory is removed and the filename is replaced when the input path contains a two-dots segment and a filename compound of two dots.
/// </summary>
QTEST_CASE ( Resolve_LastDirectoryIsRemovedAndFilenameIsReplacedWhenInputPathContainsTwoDotsSegmentAndFilenameCompoundOfTwoDots_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "../..";
    const string_q EXPECTED_PATH = "//a/b/..";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that several last directories are removed when the input path contains several concatenated two-dots segments.
/// </summary>
QTEST_CASE ( Resolve_SeveralLastDirectoriesAreRemovedWhenInputPathContainsSeveralConcatenatedTwoDotSegments_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "../../";
    const string_q EXPECTED_PATH = "//a/d";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that several last directories are removed and filename is replaced when the input path contains several concatenated two-dots segments and a filename.
/// </summary>
QTEST_CASE ( Resolve_SeveralLastDirectoriesAreRemovedAndFilenameIsReplacedWhenInputPathContainsSeveralConcatenatedTwoDotSegmentsAndFilename_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "../../g";
    const string_q EXPECTED_PATH = "//a/g";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that exceeding two-dots segments are ignored.
/// </summary>
QTEST_CASE ( Resolve_ExceedingTwoDotsSegmentsAreIgnored_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "../../../g";
    const string_q EXPECTED_PATH = "//a/g";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the leading single-dot segment is removed and the two-dots segments imply the removal of the last directory when they are concatenated in the input path.
/// </summary>
QTEST_CASE ( Resolve_SingleDotSegmentIsRemovedAndTwoDotsSegmentRemovesLastDirectoryWhenTheyAreConcatenatedInInputPath_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "./../g";
    const string_q EXPECTED_PATH = "//a/b/g";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that single-dot segments are resolved when they appear in the middle of the input path.
/// </summary>
QTEST_CASE ( Resolve_SingleDotSegmentIsResolvedWhenItAppearsInTheMiddleOfTheInputPath_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "g/./h";
    const string_q EXPECTED_PATH = "//a/b/c/g/h";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

/// <summary>
/// Checks that two-dots segments are resolved when they appear in the middle of the input path.
/// </summary>
QTEST_CASE ( Resolve_TwoDotSegmentIsResolvedWhenItAppearsInTheMiddleOfTheInputPath_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q RELATIVE_PATH = "g/../h";
    const string_q EXPECTED_PATH = "//a/b/c/h";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that the drive is not removed when the input path contains two-dots segments.
/// </summary>
QTEST_CASE ( Resolve_DriveIsNotRemovedWhenInputPathContainsTwoDotSegment_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "x:/";
    const string_q RELATIVE_PATH = "../";
    const string_q EXPECTED_PATH = "x:/";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that the tilde is not removed when the input path contains two-dots segments.
/// </summary>
QTEST_CASE ( Resolve_TildeIsNotRemovedWhenInputPathContainsTwoDotSegments_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "~/";
    const string_q RELATIVE_PATH = "../";
    const string_q EXPECTED_PATH = "~/";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath relativePath(RELATIVE_PATH);
    const QPath EXPECTED_RESULT(EXPECTED_PATH);

    // [Execution]
    absolutePath.Resolve(relativePath);
    
    // [Verification]
    BOOST_CHECK(absolutePath == EXPECTED_RESULT);
}

#endif

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails whent he input PATH is not relative.
/// </summary>
QTEST_CASE ( Resolve_AssertionFailsWhenInputPathIsNotRelative_Test )
{
    // [Preparation]
    const string_q ABSOLUTE_PATH = "//a/b/c/d";
    const string_q INPUT_PATH = "//z/x/7";
    QPath absolutePath(ABSOLUTE_PATH);
    QPath inputPath(INPUT_PATH);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.Resolve(inputPath);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the resident path is not absolute.
/// </summary>
QTEST_CASE ( Resolve_AssertionFailsWhenResidentPathIsNotAbsolute_Test )
{
    // [Preparation]
    const string_q RELATIVE_PATH = "a/b/c/d";
    const string_q INPUT_PATH = "z/x/7";
    QPath relativePath(RELATIVE_PATH);
    QPath inputPath(INPUT_PATH);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        relativePath.Resolve(inputPath);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input string is empty.
/// </summary>
QTEST_CASE ( Resolve_AssertionFailsWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_q EMPTY_PATH = string_q::GetEmpty();
    const string_q INPUT_PATH = "/a/b/c";
    QPath absolutePath(EMPTY_PATH);
    QPath inputPath(INPUT_PATH);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.Resolve(inputPath);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that the drive is not changed when the input path is absolute, starting with a separator.
    /// </summary>
    QTEST_CASE ( Resolve_DriveRemainsTheSameWhenInputPathIsAbsoluteWithLeadingSeparator_Test )
    {
        // [Preparation]
        const string_q ABSOLUTE_PATH = "x:/path1/";
        const string_q RELATIVE_PATH = "/path2/";
        const string_q EXPECTED_PATH = "x:/path2/";
        QPath absolutePath(ABSOLUTE_PATH);
        QPath relativePath(RELATIVE_PATH);
        const QPath EXPECTED_RESULT(EXPECTED_PATH);

        // [Execution]
        absolutePath.Resolve(relativePath);
        
        // [Verification]
        BOOST_CHECK(absolutePath == EXPECTED_RESULT);
    }
    
    #endif
    
#endif

/// <summary>
/// Checks that it returns a valid path.
/// </summary>
QTEST_CASE ( GetAbsolutePath_GetsValidPath_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q ORIGINAL_PATH = "./../../path/";
    QPath absolutePath(ORIGINAL_PATH);
    const string_q EXPECTED_PATH(ORIGINAL_PATH);

    // [Execution]
    string_q strPath = absolutePath.GetAbsolutePath();
    
    // [Verification]
    bool bIsValid = !strPath.IsEmpty()                                                  && 
                    strPath.Contains("/path/", EQComparisonType::E_BinaryCaseSensitive) && 
                    !strPath.Contains("/../",  EQComparisonType::E_BinaryCaseSensitive) && 
                    !strPath.Contains("/./",   EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bIsValid);
}

/// <summary>
/// Checks that the filename remains the same.
/// </summary>
QTEST_CASE ( GetAbsolutePath_FilenameRemainsTheSame_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "path/filename";
    QPath absolutePath(ORIGINAL_PATH);
    const string_q EXPECTED_PATH(ORIGINAL_PATH);

    // [Execution]
    string_q strPath = absolutePath.GetAbsolutePath();
    
    // [Verification]
    QPath path(strPath);
    bool bFilenameHasNotChanged = path.GetFilename() == "filename";
    BOOST_CHECK(bFilenameHasNotChanged);
}

/// <summary>
/// Checks that the resident path is returned instead when it is absolute.
/// </summary>
QTEST_CASE ( GetAbsolutePath_ReturnsResidentPathWhenItIsAbsolute_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path/filename";
    QPath absolutePath(ORIGINAL_PATH);
    const string_q EXPECTED_PATH(ORIGINAL_PATH);

    // [Execution]
    string_q strPath = absolutePath.GetAbsolutePath();
    
    // [Verification]
    BOOST_CHECK(strPath == ORIGINAL_PATH);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that paths with a leading separator are treated as if they had the same drive as the current directory.
/// </summary>
QTEST_CASE ( GetRelativePath_PathWithLeadingSeparatorIsTreatedAsIfItHadSameDriveAsCurrentDirectory_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path1/path2/";
    const string_q EXPECTED_PATH_START = "./../../";
    QPath absolutePath(ORIGINAL_PATH);
    const string_q EXPECTED_PATH(ORIGINAL_PATH);

    // [Execution]
    string_q strPath = absolutePath.GetRelativePath();
    
    // [Verification]
    string_q strStart = strPath.Substring(0, EXPECTED_PATH_START.GetLength() - 1U);
    BOOST_CHECK(strStart == EXPECTED_PATH_START);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that returns a valid relative path.
/// </summary>
QTEST_CASE ( GetRelativePath_ReturnsValidRelativePath_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path1/path2/";
    const string_q EXPECTED_PATH_START = "./../../";
    QPath absolutePath(ORIGINAL_PATH);
    const string_q EXPECTED_PATH(ORIGINAL_PATH);

    // [Execution]
    string_q strPath = absolutePath.GetRelativePath();
    
    // [Verification]
    string_q strStart = strPath.Substring(0, EXPECTED_PATH_START.GetLength() - 1U);
    BOOST_CHECK(strStart == EXPECTED_PATH_START);
}

#endif

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when resident path is not absolute.
/// </summary>
QTEST_CASE ( GetRelativePath_AssertionFailsWhenResidentPathIsNotAbsolute_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "./";
    QPath absolutePath(ORIGINAL_PATH);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.GetRelativePath();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when hostnames are different.
/// </summary>
QTEST_CASE ( GetRelativePath_AssertionFailsWhenHostnamesAreDifferent_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "//h------ostname/path1/";
    QPath absolutePath(ORIGINAL_PATH);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.GetRelativePath();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that an assertion fails when the drive of the resident path is different from the drive of the current working directory.
    /// </summary>
    QTEST_CASE ( GetRelativePath_AssertionFailsWhenResidentDriveIsDifferentFromCurrentDirectoryDrive_Test )
    {
        // [Preparation]
        const string_q ORIGINAL_PATH = "_:/path1/path2/filename";
        QPath absolutePath(ORIGINAL_PATH);
        const bool ASSERTION_FAILED = true;

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            absolutePath.GetRelativePath();
        }
        catch(...)
        {
            bAssertionFailed = true;
        }
    
        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }

    #endif

#endif
    
#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that paths with a leading separator are treated as if they had the same drive as the current directory.
/// </summary>
QTEST_CASE ( GetRelativePathTo_PathWithLeadingSeparatorIsTreatedAsIfItHadSameDriveAsCurrentDirectory_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path1/path2/";
    const string_q INPUT_STRING = "x:/p1/p2/";
    const string_q EXPECTED_STRING = "./../../p1/p2/";
    QPath absolutePath(ORIGINAL_PATH);
    const QPath INPUT_PATH(INPUT_STRING);
    const string_q EXPECTED_PATH(EXPECTED_STRING);

    // [Execution]
    string_q strPath = absolutePath.GetRelativePathTo(INPUT_PATH);
    
    // [Verification]
    BOOST_CHECK(strPath == EXPECTED_PATH);
}

/// <summary>
/// Checks that it returns a valid relative path when paths have the same drive.
/// </summary>
QTEST_CASE ( GetRelativePathTo_ReturnsValidRelativePathWhenPathsHaveSameDrive_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "x:/path1/path2/";
    const string_q INPUT_PATH_STRING = "x:/p1/p2/";
    const string_q EXPECTED_PATH = "./../../p1/p2/";
    QPath absolutePath(ORIGINAL_PATH);
    const QPath INPUT_PATH(INPUT_PATH_STRING);

    // [Execution]
    string_q strPath = absolutePath.GetRelativePathTo(INPUT_PATH);
    
    // [Verification]
    BOOST_CHECK(strPath == EXPECTED_PATH);
}

#endif

/// <summary>
/// Checks that returns a valid relative path when paths start with separator.
/// </summary>
QTEST_CASE ( GetRelativePathTo_ReturnsValidRelativePathWhenPathsStartWithSeparator_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path1/path2/";
    const string_q INPUT_PATH_STRING = "/p1/p2/";
    const string_q EXPECTED_PATH = "./../../p1/p2/";
    QPath absolutePath(ORIGINAL_PATH);
    const QPath INPUT_PATH(INPUT_PATH_STRING);

    // [Execution]
    string_q strPath = absolutePath.GetRelativePathTo(INPUT_PATH);
    
    // [Verification]
    BOOST_CHECK(strPath == EXPECTED_PATH);
}

/// <summary>
/// Checks that it returns a valid relative path when paths have the same hostname.
/// </summary>
QTEST_CASE ( GetRelativePathTo_ReturnsValidRelativePathWhenPathsHaveSameHostname_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "//hostname/path1/path2/";
    const string_q INPUT_PATH_STRING = "//hostname/p1/p2/";
    const string_q EXPECTED_PATH = "./../../p1/p2/";
    QPath absolutePath(ORIGINAL_PATH);
    const QPath INPUT_PATH(INPUT_PATH_STRING);

    // [Execution]
    string_q strPath = absolutePath.GetRelativePathTo(INPUT_PATH);
    
    // [Verification]
    BOOST_CHECK(strPath == EXPECTED_PATH);
}

/// <summary>
/// Checks that it returns a dot segment when paths are equal.
/// </summary>
QTEST_CASE ( GetRelativePathTo_ReturnsDotSegmentWhenPathsAreEqual_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path1/path2/";
    const string_q INPUT_PATH_STRING = ORIGINAL_PATH;
    const string_q EXPECTED_PATH = "./";
    QPath absolutePath(ORIGINAL_PATH);
    const QPath INPUT_PATH(INPUT_PATH_STRING);

    // [Execution]
    string_q strPath = absolutePath.GetRelativePathTo(INPUT_PATH);
    
    // [Verification]
    BOOST_CHECK(strPath == EXPECTED_PATH);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when resident path is not absolute.
/// </summary>
QTEST_CASE ( GetRelativePathTo_AssertionFailsWhenResidentPathIsNotAbsolute_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "./";
    const string_q INPUT_PATH_STRING = "/";
    QPath absolutePath(ORIGINAL_PATH);
    QPath inputPath(INPUT_PATH_STRING);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.GetRelativePathTo(inputPath);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input path is not absolute.
/// </summary>
QTEST_CASE ( GetRelativePathTo_AssertionFailsWhenInputPathIsNotAbsolute_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path/";
    const string_q INPUT_PATH_STRING = "./";
    QPath absolutePath(ORIGINAL_PATH);
    QPath inputPath(INPUT_PATH_STRING);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.GetRelativePathTo(inputPath);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input path is empty.
/// </summary>
QTEST_CASE ( GetRelativePathTo_AssertionFailsWhenInputPathIsEmpty_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "/path/";
    const string_q INPUT_PATH_STRING = string_q::GetEmpty();
    QPath absolutePath(ORIGINAL_PATH);
    QPath inputPath(INPUT_PATH_STRING);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.GetRelativePathTo(inputPath);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when hostnames are different.
/// </summary>
QTEST_CASE ( GetRelativePathTo_AssertionFailsWhenHostnamesAreDifferent_Test )
{
    // [Preparation]
    const string_q ORIGINAL_PATH = "//hostname1/path1/";
    const string_q INPUT_PATH_STRING = "//hostname2/path1/";
    QPath absolutePath(ORIGINAL_PATH);
    QPath inputPath(INPUT_PATH_STRING);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absolutePath.GetRelativePathTo(inputPath);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that an assertion fails when the drive of the resident path is different from the drive of the current working directory.
    /// </summary>
    QTEST_CASE ( GetRelativePathTo_AssertionFailsWhenResidentDriveIsDifferentFromCurrentDirectoryDrive_Test )
    {
        // [Preparation]
        const string_q ORIGINAL_PATH = "a:/path1/path2/filename";
        const string_q INPUT_PATH_STRING = "b:/path1/path2/filename";
        QPath absolutePath(ORIGINAL_PATH);
        QPath inputPath(INPUT_PATH_STRING);
        const bool ASSERTION_FAILED = true;

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            absolutePath.GetRelativePathTo(inputPath);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }
    
        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }

    #endif

#endif

/// <summary>
/// Checks that it returns empty when path is compound of a separator only.
/// </summary>
QTEST_CASE ( GetLastDirectory_ReturnsEmptyWhenPathIsOneSeparator_Test )
{
    // [Preparation]
    const QPath SOURCE_PATH("/");
    const string_q EXPECTED_RESULT = string_q::GetEmpty();

    // [Execution]
    string_q strResult = SOURCE_PATH.GetLastDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns a dot followed by a separator when path is compound of a dot followed by a separator.
/// </summary>
QTEST_CASE ( GetLastDirectory_ReturnsDotWhenPathIsOneDotAndOneSeparator_Test )
{
    // [Preparation]
    const QPath SOURCE_PATH("./");
    const string_q EXPECTED_RESULT(".");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetLastDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that it returns a drive when the path is compound of a drive and a separator only.
/// </summary>
QTEST_CASE ( GetLastDirectory_ReturnsDriveWhenPathIsJustADriveAndSeparator_Test )
{
    // [Preparation]
    const QPath SOURCE_PATH("x:/");
    const string_q EXPECTED_RESULT("x:");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetLastDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that it returns a tilde (~) when path is compound of a tilde followed by a separator only.
/// </summary>
QTEST_CASE ( GetLastDirectory_ReturnsTildeWhenPathIsTildeAndSeparator_Test )
{
    // [Preparation]
    const QPath SOURCE_PATH("~/");
    const string_q EXPECTED_RESULT("~");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetLastDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns the last directory as if the filename didn't exist.
/// </summary>
QTEST_CASE ( GetLastDirectory_ReturnsLastDirectoryIgnoringTheFilename_Test )
{
    // [Preparation]
    const QPath SOURCE_PATH("/p1/p2/f");
    const string_q EXPECTED_RESULT("p2");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetLastDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the last directory when there is no filename.
/// </summary>
QTEST_CASE ( GetLastDirectory_ReturnsLastDirectoryWhenThereIsNoFilename_Test )
{
    // [Preparation]
    const QPath SOURCE_PATH("/p1/p2/");
    const string_q EXPECTED_RESULT("p2");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetLastDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns empty there is only hostname.
/// </summary>
QTEST_CASE ( GetLastDirectory_ReturnsEmptyWhenPathContainsHostnameOnly_Test )
{
    // [Preparation]
    const QPath SOURCE_PATH("//hostname");
    const string_q EXPECTED_RESULT = string_q::GetEmpty();

    // [Execution]
    string_q strResult = SOURCE_PATH.GetLastDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns expected path when it only contains a directory.
/// </summary>
QTEST_CASE ( ToString_ReturnsExpectedPathWhenItOnlyContainsDirectory_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/directory/");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns expected path when it only contains a filename.
/// </summary>
QTEST_CASE ( ToString_ReturnsExpectedPathWhenItOnlyContainsFilename_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("./filename.ext");
    const QPath SOURCE_PATH("filename.ext");

    // [Execution]
    string_q strResult = SOURCE_PATH.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns expected path when it only contains a host5name.
/// </summary>
QTEST_CASE ( ToString_ReturnsExpectedPathWhenItOnlyContainsHostname_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("//hostname/");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns expected path when it contains a hostname, directories and a filename.
/// </summary>
QTEST_CASE ( ToString_ReturnsExpectedPathWhenItContainsHostnameDirectoryAndFilename_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("//hostname/directory/filename.ext");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns expected path when it contains just one separator.
/// </summary>
QTEST_CASE ( ToString_ReturnsExpectedPathWhenItContainsOneSeparator_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns expected path when it contains just one dot followed by a separator.
/// </summary>
QTEST_CASE ( ToString_ReturnsExpectedPathWhenItContainsOneDotAndSeparator_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("./");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that it returns True when the path has drive.
/// </summary>
QTEST_CASE ( IsAbsolute_ReturnsTrueWhenPathHasDrive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("x:/");

    // [Execution]
    bool bResult = SOURCE_PATH.IsAbsolute();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)
    
/// <summary>
/// Checks that it returns False when the path starts with a tilde.
/// </summary>
QTEST_CASE ( IsAbsolute_ReturnsFalseWhenPathStartsWithTilde_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("~/");

    // [Execution]
    bool bResult = SOURCE_PATH.IsAbsolute();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the path starts with a separator.
/// </summary>
QTEST_CASE ( IsAbsolute_ReturnsTrueWhenPathStartsWithSeparator_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("/");

    // [Execution]
    bool bResult = SOURCE_PATH.IsAbsolute();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the path has hostname.
/// </summary>
QTEST_CASE ( IsAbsolute_ReturnsTrueWhenPathHasHostname_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("//hostname");

    // [Execution]
    bool bResult = SOURCE_PATH.IsAbsolute();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path only has filename.
/// </summary>
QTEST_CASE ( IsAbsolute_ReturnsFalseWhenPathOnlyHasFilename_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("filename");

    // [Execution]
    bool bResult = SOURCE_PATH.IsAbsolute();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path starts with dot segments.
/// </summary>
QTEST_CASE ( IsAbsolute_ReturnsFalseWhenPathStartsWithDotSegments_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("./../");

    // [Execution]
    bool bResult = SOURCE_PATH.IsAbsolute();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path starts with directory name without leading separator.
/// </summary>
QTEST_CASE ( IsAbsolute_ReturnsFalseWhenPathStartsWithDirectoryWithoutSeparator_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("path/");

    // [Execution]
    bool bResult = SOURCE_PATH.IsAbsolute();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected value when the path contains directory and filename.
/// </summary>
QTEST_CASE ( GetFilenameWithoutExtension_ReturnsExpectedResultWhenPathHasDirectoryAndFilename_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "filename";
    const QPath SOURCE_PATH("path/filename");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFilenameWithoutExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected value when the path only has filename.
/// </summary>
QTEST_CASE ( GetFilenameWithoutExtension_ReturnsExpectedResultWhenPathOnlyHasFilename_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "filename";
    const QPath SOURCE_PATH("filename");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFilenameWithoutExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value does not include the extension.
/// </summary>
QTEST_CASE ( GetFilenameWithoutExtension_ReturnedFilenameDoesNotIncludeExtension_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "filename";
    const QPath SOURCE_PATH("filename.ext");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFilenameWithoutExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value does not contain the separation dot when extension is empty and dot is present.
/// </summary>
QTEST_CASE ( GetFilenameWithoutExtension_ReturnedFilenameDoesNotIncludeTheDotWhenExtensionIsEmpty_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "filename";
    const QPath SOURCE_PATH("filename.");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFilenameWithoutExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns empty when the path contains a file extension only.
/// </summary>
QTEST_CASE ( GetFilenameWithoutExtension_ReturnsEmptyWhenItContainsFileExtensionOnly_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = string_q::GetEmpty();
    const QPath SOURCE_PATH(".ext");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFilenameWithoutExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetFilename_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns empty when there is no file extension.
/// </summary>
QTEST_CASE ( GetFileExtension_ReturnsEmptyWhenExtensionIsNotPresent_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = string_q::GetEmpty();
    const QPath SOURCE_PATH("filename");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFileExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected extension when the filename contains a extension.
/// </summary>
QTEST_CASE ( GetFileExtension_ReturnsExpectedExtensionWhenFilenameContainsExtension_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("ext");
    const QPath SOURCE_PATH("filename.ext");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFileExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns empty when there is no file extension but the separation dot is.
/// </summary>
QTEST_CASE ( GetFileExtension_ReturnsEmptyWhenExtensionIsNotPresentButDotIs_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = string_q::GetEmpty();
    const QPath SOURCE_PATH("filename.");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetFileExtension();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns a separator when the path is only one separator.
/// </summary>
QTEST_CASE ( GetDirectory_ReturnsSeparatorWhenPathIsOnlyOneSeparator_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.GetDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it only returns the directory when path also contains hostname and filename.
/// </summary>
QTEST_CASE ( GetDirectory_ReturnsDirectoryWhenPathAlsoContainsHostnameAndFilename_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/directory1/directory2/");
    const QPath SOURCE_PATH("//hostname/directory1/directory2/filename.ext");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the directory without leading separator when the path does not start with a separator.
/// </summary>
QTEST_CASE ( GetDirectory_ReturnsDirectoryWithoutLeadingSeparatorWhenPathDoesNotHaveLeadingSeparator_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("directory1/directory2/");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.GetDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns one separator when the path only contains a hostname.
/// </summary>
QTEST_CASE ( GetDirectory_ReturnsOneSeparatorWhenPathOnlyContainsHostname_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/");
    const QPath SOURCE_PATH("//hostname");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetDirectory();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the hostname and one separator when the path only contains a hostname.
/// </summary>
QTEST_CASE ( GetRoot_ReturnsHostnameFollowedByOneSeparatorWhenPathOnlyContainsHostname_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("//hostname/");
    const QPath SOURCE_PATH("//hostname");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetRoot();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that it returns the drive and a separator when the path contains a drive and other directories.
/// </summary>
QTEST_CASE ( GetRoot_ReturnsDriveAndSeparatorWhenPathContainsDriveAndOtherDirectories_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("x:/");
    const QPath SOURCE_PATH("x:/directory/");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetRoot();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that it returns a separator when the path contains a tilde and other directories.
/// </summary>
QTEST_CASE ( GetRoot_ReturnsSeparatorWhenPathContainsTildeAndOtherDirectories_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/");
    const QPath SOURCE_PATH("~/directory/");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetRoot();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns a separator when the path only contains one separator.
/// </summary>
QTEST_CASE ( GetRoot_ReturnsSeparatorWhenPathOnlyContainsSeparator_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/");
    const QPath SOURCE_PATH(EXPECTED_RESULT);

    // [Execution]
    string_q strResult = SOURCE_PATH.GetRoot();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the hostname and the last directory when the path contains hostname and directories.
/// </summary>
QTEST_CASE ( GetRoot_ReturnsHostnameAndLastDirectoryWhenPathContainsHostnameAndDirectories_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("//hostname/directory1/");
    const QPath SOURCE_PATH("//hostname/directory1/directory2/");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetRoot();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the hostname and the last directory when the path contains hostname and one directory.
/// </summary>
QTEST_CASE ( GetRoot_ReturnsHostnameAndLastDirectoryWhenPathContainsHostnameAndOneDirectory_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("//hostname/directory/");
    const QPath SOURCE_PATH("//hostname/directory/");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetRoot();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns a separator when the path starts with a separator and contains several directories.
/// </summary>
QTEST_CASE ( GetRoot_ReturnsSeparatorWhenPathStartsWithSeparatorAndHasSeveralDirectories_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("/");
    const QPath SOURCE_PATH("/directory1/directory2/");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetRoot();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns a the hostname without separators.
/// </summary>
QTEST_CASE ( GetHostname_ReturnsTheHostnameWithoutSeparators_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT("hostname");
    const QPath SOURCE_PATH("//hostname/directory/filename.ext");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetHostname();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns empty when the path has not a hostname.
/// </summary>
QTEST_CASE ( GetHostname_ReturnsEmptyWhenPathHasNotHostname_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = string_q::GetEmpty();
    const QPath SOURCE_PATH("/directory/filename.ext");

    // [Execution]
    string_q strResult = SOURCE_PATH.GetHostname();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path does not contain a filename.
/// </summary>
QTEST_CASE ( IsFile_ReturnsFalseWhenPathDoesNotContainFilename_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("/directory/");

    // [Execution]
    bool bResult = SOURCE_PATH.IsFile();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the path contains a filename.
/// </summary>
QTEST_CASE ( IsFile_ReturnsTrueWhenPathContainsFilename_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("/directory/filename.ext");

    // [Execution]
    bool bResult = SOURCE_PATH.IsFile();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path contains a filename.
/// </summary>
QTEST_CASE ( IsDirectory_ReturnsFalseWhenPathContainsFilename_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("/directory/filename.ext");

    // [Execution]
    bool bResult = SOURCE_PATH.IsDirectory();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the path does not contain a filename.
/// </summary>
QTEST_CASE ( IsDirectory_ReturnsTrueWhenPathDoesNotContainFilename_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("/directory/");

    // [Execution]
    bool bResult = SOURCE_PATH.IsDirectory();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that it returns True when the path contains a drive.
/// </summary>
QTEST_CASE ( HasDrive_ReturnsTrueWhenPathContainsDrive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("x:/directory/filename.ext");

    // [Execution]
    bool bResult = SOURCE_PATH.HasDrive();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path does not contain a drive.
/// </summary>
QTEST_CASE ( HasDrive_ReturnsFalseWhenPathDoesNotContainDrive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("/directory/filename.ext");

    // [Execution]
    bool bResult = SOURCE_PATH.HasDrive();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#else

/// <summary>
/// Checks that it returns False.
/// </summary>
QTEST_CASE ( HasDrive_ReturnsFalse_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("x:/directory/filename.ext");

    // [Execution]
    bool bResult = SOURCE_PATH.HasDrive();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the path contains a hostname.
/// </summary>
QTEST_CASE ( HasHostname_ReturnsTrueWhenPathContainsHostname_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("//hostname/directory/filename.ext");

    // [Execution]
    bool bResult = SOURCE_PATH.HasHostname();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path does not contain a hostname.
/// </summary>
QTEST_CASE ( HasHostname_ReturnsFalseWhenPathDoesNotContainHostname_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("/directory/filename.ext");

    // [Execution]
    bool bResult = SOURCE_PATH.HasHostname();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the path only contains a separator.
/// </summary>
QTEST_CASE ( HasRoot_ReturnsTrueWhenPathOnlyContainsSeparator_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("/");

    // [Execution]
    bool bResult = SOURCE_PATH.HasRoot();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the path contains hostname.
/// </summary>
QTEST_CASE ( HasRoot_ReturnsTrueWhenPathContainsHostname_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("//hostname");

    // [Execution]
    bool bResult = SOURCE_PATH.HasRoot();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that it returns True when the path contains a drive.
/// </summary>
QTEST_CASE ( HasRoot_ReturnsTrueWhenPathContainsDrive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("x:/directory/");

    // [Execution]
    bool bResult = SOURCE_PATH.HasRoot();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path does not start with a drive nor a separator.
/// </summary>
QTEST_CASE ( HasRoot_ReturnsFalseWhenPathDoesNotBeginWithDriveNorSeparator_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("directory/");

    // [Execution]
    bool bResult = SOURCE_PATH.HasRoot();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that it returns True when the path starts with a tilde.
/// </summary>
QTEST_CASE ( HasRoot_ReturnsTrueWhenPathBeginsWithTilde_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("~/directory/");

    // [Execution]
    bool bResult = SOURCE_PATH.HasRoot();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path does not start with a tilde nor a separator.
/// </summary>
QTEST_CASE ( HasRoot_ReturnsFalseWhenPathDoesNotBeginWithTildeNorSeparator_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const QPath SOURCE_PATH("directory/");

    // [Execution]
    bool bResult = SOURCE_PATH.HasRoot();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the path starts with a separator.
/// </summary>
QTEST_CASE ( HasRoot_ReturnsTrueWhenPathStartsWithSeparator_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const QPath SOURCE_PATH("/directory/");

    // [Execution]
    bool bResult = SOURCE_PATH.HasRoot();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the filename is correctly set when the path contains a directory and a filename.
/// </summary>
QTEST_CASE ( SetFilename_FilenameIsCorrectlySetWhenPathContainsDirectoryAndFilename_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/directory/filename.ext");
    const string_q INPUT_FILENAME("xxx");
    const string_q EXPECTED_RESULT("/directory/xxx.ext");
    
    // [Execution]
    SOURCE_PATH.SetFilename(INPUT_FILENAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the filename is correctly set when the path is a separator.
/// </summary>
QTEST_CASE ( SetFilename_FilenameIsCorrectlySetWhenPathIsASeparator_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/");
    const string_q INPUT_FILENAME("filename");
    const string_q EXPECTED_RESULT("/filename");
    
    // [Execution]
    SOURCE_PATH.SetFilename(INPUT_FILENAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the extension is not changed.
/// </summary>
QTEST_CASE ( SetFilename_ExtensionIsNotChanged_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/filename.ext");
    const string_q INPUT_FILENAME("xxx");
    const string_q EXPECTED_RESULT("/xxx.ext");
    
    // [Execution]
    SOURCE_PATH.SetFilename(INPUT_FILENAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the filename is changed when the path has no extension.
/// </summary>
QTEST_CASE ( SetFilename_FilenameIsChangedWhenItHasNoExtension_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/filename");
    const string_q INPUT_FILENAME("xxx");
    const string_q EXPECTED_RESULT("/xxx");
    
    // [Execution]
    SOURCE_PATH.SetFilename(INPUT_FILENAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the filename is empty when using an empty input string.
/// </summary>
QTEST_CASE ( SetFilename_FilenameIsEmptyWhenUsingEmptyInputString_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_FILENAME = string_q::GetEmpty();
    QPath path("/filename");

    // [Execution]
    path.SetFilename(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetFilename() == EXPECTED_FILENAME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

   #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that an assertion fails when the input contains invalid characters.
    /// </summary>
    QTEST_CASE ( SetFilename_AssertionFailsWhenInputContainsInvalidCharacters_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("start?\"<>|:end/");
        const bool ASSERTION_FAILED = true;
        QPath path("/");

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            path.SetFilename(INPUT_STRING);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }

    #endif
    
/// <summary>
/// Checks that an assertion fails when the filename is too large (larger than 255 characters).
/// </summary>
QTEST_CASE ( SetFilename_AssertionFailsWhenFilenameIsTooLarge_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetFilename(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the filename contains a separator.
/// </summary>
QTEST_CASE ( SetFilename_AssertionFailsWhenFilenameContainsSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("filen/ame");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetFilename(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that invalid characters are removed from the filename.
    /// </summary>
    QTEST_CASE ( SetFilename_InvalidCharactersAreRemovedFromFilename_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("start?\"<>|:end/");
        const string_q EXPECTED_FILENAME("startend");
        QPath path("/");

        // [Execution]
        path.SetFilename(INPUT_STRING);

        // [Verification]
        BOOST_CHECK(path.GetFilenameWithoutExtension() == EXPECTED_FILENAME);
    }

    #endif

#endif

/// <summary>
/// Checks that the filename and the extension are set when the path has no extension.
/// </summary>
QTEST_CASE ( SetFilenameAndExtension_FilenameAndExtensionAreSetWhenPathHasNoExtension_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/filename");
    const string_q INPUT_FILENAME("xxx.ext");
    const string_q EXPECTED_RESULT("/xxx.ext");
    
    // [Execution]
    SOURCE_PATH.SetFilenameAndExtension(INPUT_FILENAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the filename and the extension are set when the path has filename and extension.
/// </summary>
QTEST_CASE ( SetFilenameAndExtension_FilenameAndExtensionAreChangedWhenPathHasFilenameAndExtension_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/filename.ext");
    const string_q INPUT_FILENAME("xxx.yyy");
    const string_q EXPECTED_RESULT("/xxx.yyy");
    
    // [Execution]
    SOURCE_PATH.SetFilenameAndExtension(INPUT_FILENAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the filename and the extension are set when the path has directory, filename and extension.
/// </summary>
QTEST_CASE ( SetFilenameAndExtension_FilenameAndExtensionAreChangedWhenPathHasDirectoryAndFilenameAndExtension_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/directory1/directory2/filename.ext");
    const string_q INPUT_FILENAME("xxx.yyy");
    const string_q EXPECTED_RESULT("/directory1/directory2/xxx.yyy");
    
    // [Execution]
    SOURCE_PATH.SetFilenameAndExtension(INPUT_FILENAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the filename and the extension are empty when using an empty input string.
/// </summary>
QTEST_CASE ( SetFilenameAndExtension_HostnameIsEmptyWhenUsingEmptyInputString_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_FILENAME = string_q::GetEmpty();
    QPath path("/filename.ext");

    // [Execution]
    path.SetFilenameAndExtension(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetFilename() == EXPECTED_FILENAME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

   #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that an assertion fails when the input contains invalid characters.
    /// </summary>
    QTEST_CASE ( SetFilenameAndExtension_AssertionFailsWhenInputContainsInvalidCharacters_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("start?\"<>|:e.nd/");
        const bool ASSERTION_FAILED = true;
        QPath path("/");

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            path.SetFilenameAndExtension(INPUT_STRING);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }

    #endif
    
/// <summary>
/// Checks that an assertion fails when the filename is too large (larger than 255 characters).
/// </summary>
QTEST_CASE ( SetFilenameAndExtension_AssertionFailsWhenFilenameIsTooLarge_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetFilenameAndExtension(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the filename contains a separator.
/// </summary>
QTEST_CASE ( SetFilenameAndExtension_AssertionFailsWhenFilenameContainsSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("filen/ame");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetFilenameAndExtension(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that invalid characters are removed from the filename.
    /// </summary>
    QTEST_CASE ( SetFilenameAndExtension_InvalidCharactersAreRemovedFromFilenameAndExtension_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("start?\"<>|:e.nd/");
        const string_q EXPECTED_FILENAME("starte.nd");
        QPath path("/");

        // [Execution]
        path.SetFilenameAndExtension(INPUT_STRING);

        // [Verification]
        BOOST_CHECK(path.GetFilename() == EXPECTED_FILENAME);
    }

    #endif

#endif

/// <summary>
/// Checks that the hostname is correctly set when path has hostname and directory.
/// </summary>
QTEST_CASE ( SetHostname_HostnameIsCorrectlySetWhenPathHasHostnameAndDirectory_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("//hostname/directory1/directory2/");
    const string_q INPUT_HOSTNAME("xxx");
    const string_q EXPECTED_RESULT("//xxx/directory1/directory2/");
    
    // [Execution]
    SOURCE_PATH.SetHostname(INPUT_HOSTNAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the hostname is correctly set when path does not have hostname.
/// </summary>
QTEST_CASE ( SetHostname_HostnameIsCorrectlySetWhenPathDoesNotHaveHostname_Test )
{
    // [Preparation]
    QPath SOURCE_PATH("/directory1/directory2/");
    const string_q INPUT_HOSTNAME("xxx");
    const string_q EXPECTED_RESULT("//xxx/directory1/directory2/");
    
    // [Execution]
    SOURCE_PATH.SetHostname(INPUT_HOSTNAME);
    
    // [Verification]
    string_q strResult = SOURCE_PATH.ToString();
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has hostname and path is a separator.
/// </summary>
QTEST_CASE ( SetHostname_AtSignsAreAllowedInHostnames_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("user@hostname");
    const string_q EXPECTED_HOSTNAME("user@hostname");
    QPath path("/");

    // [Execution]
    path.SetHostname(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

#endif

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains an IP enclosed into square brackets.
/// </summary>
QTEST_CASE ( SetHostname_HostnameIsWhatExpectedWhenInputContainsIpEnclosedIntoSquareBrackets_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("[255.255.255.255]");
    const string_q EXPECTED_HOSTNAME("[255.255.255.255]");
    QPath path("/");

    // [Execution]
    path.SetHostname(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains an IP enclosed into square brackets and numbers are zeroes.
/// </summary>
QTEST_CASE ( SetHostname_HostnameIsWhatExpectedWhenInputContainsIpEnclosedIntoSquareBracketsAndNumbersAreZeroes_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("[0.0.0.0]");
    const string_q EXPECTED_HOSTNAME("[0.0.0.0]");
    QPath path("/");

    // [Execution]
    path.SetHostname(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains an IP without square brackets.
/// </summary>
QTEST_CASE ( SetHostname_HostnameIsWhatExpectedWhenInputContainsIpWithoutSquareBrackets_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("255.255.255.255");
    const string_q EXPECTED_HOSTNAME("255.255.255.255");
    QPath path("/");

    // [Execution]
    path.SetHostname(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the hostname of the resultant path is what expected when input path contains all the allowed characters.
/// </summary>
QTEST_CASE ( SetHostname_HostnameIsWhatExpectedWhenInputContainsAllAllowedCharacters_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZ-abcdefghijklmnopqrstuvwxyz0123456789");
    const string_q EXPECTED_HOSTNAME("ABCDEFGHIJKLMNOPQRSTUVWXYZ-abcdefghijklmnopqrstuvwxyz0123456789");
    QPath path("/");

    // [Execution]
    path.SetHostname(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

/// <summary>
/// Checks that the hostname is empty when using an empty input string.
/// </summary>
QTEST_CASE ( SetHostname_HostnameIsEmptyWhenUsingEmptyInputString_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_HOSTNAME = string_q::GetEmpty();
    QPath path("//hostname/");

    // [Execution]
    path.SetHostname(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that an assertion fails whent he path contains a drive.
    /// </summary>
    QTEST_CASE ( SetHostname_AssertionFailsWhenPathContainsDrive_Test )
    {
        // [Preparation]
        QPath SOURCE_PATH("x:/directory1/directory2/");
        const string_q INPUT_HOSTNAME("xxx");
    
        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            SOURCE_PATH.SetHostname(INPUT_HOSTNAME);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK(bAssertionFailed);
    }

    #endif
    
/// <summary>
/// Checks that an assertion fails when hostname starts with an hyphen ("-").
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenHostnameStartsWithHyphen_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//-hostname/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the IP starts with a square bracket ("[") but does not end with another square bracket ("]").
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenIpStartsWithSquareBracketButDoesNotEndWithAnotherSquareBracket_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//[255.255.255.255/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the IP ends with a square bracket ("]") but does not start with another square bracket ("[").
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenIpEndsWithSquareBracketButDoesNotStartWithAnotherSquareBracket_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.255.255.255]/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when an IP contains letters.
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenIpContainsLetters_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255a.255.255.255/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a hostname contains dots.
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenHostnameContainsDots_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//host.name/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when an IP contains hyphens ("-").
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenIpContainsHyphen_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255-.255.255.255/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the one of the parts of the IP is greater than 255.
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenOneNumberOfIpIsGreaterThan255_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.256.255.255/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of one of the parts of the IP is greater than 3.
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenLengthOfOnePartOfIpIsGreaterThan3_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.0000.255.255/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a hostname contains square brackets ("[", "]").
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenHostnameContainsSquareBracket_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//hostname]/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a number of the IP is missing.
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenOneNumberOfIpIsMissing_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.255.255/");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a all the numbers of the IP are empty.
/// </summary>
QTEST_CASE ( SetHostname_AssertionFailsWhenNumbersOfTheIpAreEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//255.../");
    const bool ASSERTION_FAILED = true;
    QPath path("/");

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        path.SetHostname(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    /// <summary>
    /// Checks that invalid characters are removed from the hostname.
    /// </summary>
    QTEST_CASE ( SetHostname_InvalidCharactersAreRemovedFromHostname_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("//abc_def?ghi#/");
        const string_q EXPECTED_HOSTNAME("abcdefghi");

        // [Execution]
        QPath path(INPUT_STRING);

        // [Verification]
        BOOST_CHECK(path.GetHostname() == EXPECTED_HOSTNAME);
    }

#endif

/// <summary>
/// Checks that the resultant path equals "./" when the input string is empty and the path does not contain a hostname.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsDotAndSeparatorWhenInputIsEmptyAndPathHasNoHostname_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_PATH("./");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the resultant path equals "/" when the input string is empty and the path contains a hostname.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsSeparatorWhenInputIsEmptyAndPathHasHostname_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_PATH("/");
    QPath path("//hostname/dir/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the resultant path equals input string when it is just a separator.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputIsSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/");
    const string_q EXPECTED_PATH("/");
    QPath path("/dir/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has relative directory that contains one dot segment.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputContainsRelativeDirectoryWithOnlyOneDotSegment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("./");
    const string_q EXPECTED_DIRECTORY("./");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has relative directory that contains two dot segment.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputContainsRelativeDirectoryWithTwoDotSegments_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("./../");
    const string_q EXPECTED_DIRECTORY("./../");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path has relative directory that contains only two dot segment.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputContainsRelativeDirectoryContainsOnlyTwoDotSegments_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("../");
    const string_q EXPECTED_DIRECTORY("../");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the input directory is not resolved when it contains dot segments.
/// </summary>
QTEST_CASE ( SetDirectory_InputDirectoryIsNotResolvedWhenItContainsDotSegments_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("./../path/../");
    const string_q EXPECTED_DIRECTORY("./../path/../");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#if defined(QE_OS_WINDOWS)

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path contains a drive and a directory.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputContainsDriveAndDirectory_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("X:/path1/");
    const string_q EXPECTED_DIRECTORY("X:/path1/");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path contains a drive and a directory without separation.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputContainsDriveAndDirectoryWithoutSeparation_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("X:path1/");
    const string_q EXPECTED_DIRECTORY("X:path1/");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when input path contains a drive only.
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputContainsDriveOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("X:/");
    const string_q EXPECTED_DIRECTORY("X:/");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#elif defined(QE_OS_LINUX) || defined(QE_OS_MAC)

/// <summary>
/// Checks that the directory of the resultant path is what expected when input directory is a tilde ("~").
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputContainsTildeDirectoryOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("~/");
    const string_q EXPECTED_DIRECTORY("~/");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

/// <summary>
/// Checks that the directory of the resultant path is what expected when the directory starts with a tilde ("~").
/// </summary>
QTEST_CASE ( SetDirectory_DirectoryIsWhatExpectedWhenInputDirectoryStartsWithTilde_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("~/path/");
    const string_q EXPECTED_DIRECTORY("~/path/");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#endif

/// <summary>
/// Checks that a trailing separator is appended when the input directory hasn't it.
/// </summary>
QTEST_CASE ( SetDirectory_ATrailingSeparatorIsAppendedWhenInputHasNotIt_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/directory");
    const string_q EXPECTED_DIRECTORY("/directory/");
    QPath path("/");

    // [Execution]
    path.SetDirectory(INPUT_STRING);

    // [Verification]
    BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that an assertion fails when the path contains invalid characters.
    /// </summary>
    QTEST_CASE ( SetDirectory_AssertionFailsWhenPathContainsInvalidCharacters_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("start?\"<>|:end/");
        const bool ASSERTION_FAILED = true;
        QPath path("/");

        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            path.SetDirectory(INPUT_STRING);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    }

    /// <summary>
    /// Checks that an assertion fails whent he path contains a hostname and the input string contains a drive.
    /// </summary>
    QTEST_CASE ( SetDirectory_AssertionFailsWhenPathContainsHostnameAndInputContainsDrive_Test )
    {
        // [Preparation]
        QPath SOURCE_PATH("//hostname/");
        const string_q INPUT_DIRECTORY("x:/");
    
        // [Execution]
        bool bAssertionFailed = false;

        try
        {
            SOURCE_PATH.SetDirectory(INPUT_DIRECTORY);
        }
        catch(...)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK(bAssertionFailed);
    }
    
    #endif

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if defined(QE_OS_WINDOWS)

    /// <summary>
    /// Checks that invalid characters are removed from the directory.
    /// </summary>
    QTEST_CASE ( SetDirectory_InvalidCharactersAreRemovedFromDirectory_Test )
    {
        // [Preparation]
        const string_q INPUT_STRING("/start?\"<>|:end/");
        const string_q EXPECTED_DIRECTORY("/startend/");
        QPath path("/");

        // [Execution]
        path.SetDirectory(INPUT_STRING);

        // [Verification]
        BOOST_CHECK(path.GetDirectory() == EXPECTED_DIRECTORY);
    }

    #endif

#endif

// End - Test Suite: QPath
QTEST_SUITE_END()
