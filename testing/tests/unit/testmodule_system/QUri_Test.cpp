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

#include "QUri.h"

#include "QUriWhiteBox.h"
#include "QDynamicArray.h"

using Kinesis::QuimeraEngine::System::IO::QUri;
using Kinesis::QuimeraEngine::System::IO::Test::QUriWhiteBox;

QTEST_SUITE_BEGIN( QUri_TestSuite )

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input string is empty.
/// </summary>
QTEST_CASE ( Constructor1_AssertionFailsWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QUri uri(INPUT_STRING);
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
/// Checks that all the URI componets are empty when an empty string is used as input.
/// </summary>
QTEST_CASE ( Constructor1_AllComponentsAreEmptyWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_VALUE = string_q::GetEmpty();

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetFragment()  == EXPECTED_VALUE);
}

#endif

/// <summary>
/// Checks that the scheme has the expected value when the input string only contains a scheme.
/// </summary>
QTEST_CASE ( Constructor1_SchemeIsWhatExpectedWhenInputContainsSchemeOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme:";
    const string_q EXPECTED_VALUE = "scheme";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority have the expected value when the input string only contains a scheme and the authority.
/// </summary>
QTEST_CASE ( Constructor1_SchemeAndAuthorityAreWhatExpectedWhenInputContainsSchemeAndAuthorityOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://authority";
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "authority";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority and the path have the expected value when the input string contains the scheme, the authority and the path.
/// </summary>
QTEST_CASE ( Constructor1_SchemeAuthorityAndPathAreWhatExpectedWhenInputContainsSchemeAuthorityAndPath_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://authority/path";
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "authority";
    const string_q EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority and the path have the expected value when the input string contains an IPv6 as host and a port.
/// </summary>
QTEST_CASE ( Constructor1_SchemeAuthorityAndPathAreWhatExpectedWhenInputContainsIPv6AndPort_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://[fe80::4cf7:6fe6:453f:8129]:port/pat:h";
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_HOST_VALUE = "[fe80::4cf7:6fe6:453f:8129]";
    const string_q EXPECTED_PORT_VALUE = "port";
    const string_q EXPECTED_PATH_VALUE = "/pat:h";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetHost()   == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()   == EXPECTED_PORT_VALUE);
    BOOST_CHECK(uri.GetPath()   == EXPECTED_PATH_VALUE);
    string_q u = uri.GetPath();
}

/// <summary>
/// Checks that the scheme, the authority, the path and the query have the expected value when the input string contains the scheme, the authority, the path and the query.
/// </summary>
QTEST_CASE ( Constructor1_SchemeAuthorityPathAndQueryAreWhatExpectedWhenInputContainsSchemeAuthorityPathAndQuery_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://authority/path?query";
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "authority";
    const string_q EXPECTED_PATH_VALUE = "/path";
    const string_q EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the scheme and the path have the expected value when the input string contains the scheme and the path only.
/// </summary>
QTEST_CASE ( Constructor1_SchemeAndPathAreWhatExpectedWhenInputContainsSchemeAndPathOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme:/pathsegment1/pathsegment2";
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_PATH_VALUE = "/pathsegment1/pathsegment2";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetPath()   == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the host has the expected value when the authority is formed only by a host.
/// </summary>
QTEST_CASE ( Constructor1_HostIsWhatExpectedWhenAuthorityIsFormedOnlyByHost_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://authority/path";
    const string_q EXPECTED_HOST_VALUE = "authority";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetHost() == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information and the host have the expected value when the authority is formed only by a host and the user information.
/// </summary>
QTEST_CASE ( Constructor1_UserInfoAndHostAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoAndHost_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "//userinfo@host";
    const string_q EXPECTED_USERINFO_VALUE = "userinfo";
    const string_q EXPECTED_HOST_VALUE = "host";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information, the port and the host have the expected value when the authority is formed only by a host, the port and the user information.
/// </summary>
QTEST_CASE ( Constructor1_UserInfoHostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoHostAndPort_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "//userinfo@host:port";
    const string_q EXPECTED_USERINFO_VALUE = "userinfo";
    const string_q EXPECTED_HOST_VALUE = "host";
    const string_q EXPECTED_PORT_VALUE = "port";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()     == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the port and the host have the expected value when the authority is formed only by a host and the port.
/// </summary>
QTEST_CASE ( Constructor1_HostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByHostAndPort_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "//host:port";
    const string_q EXPECTED_HOST_VALUE = "host";
    const string_q EXPECTED_PORT_VALUE = "port";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetHost() == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort() == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the authority and the path have the expected value when the URI is formed only by the authority and the path.
/// </summary>
QTEST_CASE ( Constructor1_AuthorityAndPathAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndPath_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "//userinfo@host:port/path";
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_q EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the authority and the query have the expected value when the URI is formed only by the authority and the query.
/// </summary>
QTEST_CASE ( Constructor1_AuthorityAndQueryAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndQuery_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "//userinfo@host:port?query";
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_q EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the authority and the fragment have the expected value when the URI is formed only by the authority and the fragment.
/// </summary>
QTEST_CASE ( Constructor1_AuthorityAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndFragment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "//userinfo@host:port#fragment";
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_q EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    string_q c = uri.GetAuthority();
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetFragment()  == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path does not start with a slash when it does not start with a slash in the input string.
/// </summary>
QTEST_CASE ( Constructor1_PathDoesNotStartWithSlashWhenUriIsFormedOnlyByPathWhichDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "segment1/segment2";
    const string_q EXPECTED_PATH_VALUE = "segment1/segment2";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path starts with a slash when it starts with a slash in the input string.
/// </summary>
QTEST_CASE ( Constructor1_PathStartsWithSlashWhenUriIsFormedOnlyByPathWhichStartsWithSlash_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "/segment1/segment2";
    const string_q EXPECTED_PATH_VALUE = "/segment1/segment2";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path does not include the initial dot segment when it starts with one dot.
/// </summary>
QTEST_CASE ( Constructor1_PathDoesNotIncludeDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithOneDot_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "./segment1/segment2";
    const string_q EXPECTED_PATH_VALUE = "segment1/segment2";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path does not include the initial dot segment when it starts with two dots.
/// </summary>
QTEST_CASE ( Constructor1_PathDoesNotIncludeDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithTwoDots_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "../segment1/segment2";
    const string_q EXPECTED_PATH_VALUE = "../segment1/segment2";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path and the query have the expected value when the URI is formed only by the path and the query.
/// </summary>
QTEST_CASE ( Constructor1_PathAndQueryAreWhatExpectedWhenUriIsFormedOnlyByPathAndQuery_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "path1/path2?query=value";
    const string_q EXPECTED_PATH_VALUE = "path1/path2";
    const string_q EXPECTED_QUERY_VALUE = "query=value";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()  == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery() == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the path and the fragment have the expected value when the URI is formed only by the path and the fragment.
/// </summary>
QTEST_CASE ( Constructor1_PathAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByPathAndFragment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "path1/path2#fragment";
    const string_q EXPECTED_PATH_VALUE = "path1/path2";
    const string_q EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path is empty and starts with a slash when the URI only contains a single slash.
/// </summary>
QTEST_CASE ( Constructor1_PathIsEmptyAndStartsWithSlashWhenUriContainsOnlyOneSlash_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "/";
    const string_q EXPECTED_PATH_VALUE = "/";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
QTEST_CASE ( Constructor1_PathQueryAndFragmentAreEncoded_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    string_q INPUT_STRING = "scheme://userinfo@authority:port/p<a th1/pa[]t{}h2?qu ery=va<lue#fra{gment";
    INPUT_STRING.Append(char_q(0x0470)); // CYRILLIC CAPITAL LETTER PSI, UTF8: D1 B0
    INPUT_STRING.Append(char_q(0x01C2)); // LATIN LETTER ALVEOLAR CLICK, UTF8: C7 82

    const string_q EXPECTED_PATH_VALUE = "/p%3Ca%20th1/pa%5B%5Dt%7B%7Dh2";
    const string_q EXPECTED_QUERY_VALUE = "qu%20ery=va%3Clue";
    const string_q EXPECTED_FRAGMENT_VALUE = "fra%7Bgment%D1%B0%C7%82";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the question mark ("?") and the slash ("/") are allowed in both the query and the fragment.
/// </summary>
QTEST_CASE ( Constructor1_QuestionMarkAndSlashAreAllowedInQueryAndFragment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://userinfo@authority:port/path1/path2?que?r/y=value#fr?ag/ment";
    const string_q EXPECTED_QUERY_VALUE = "que?r/y=value";
    const string_q EXPECTED_FRAGMENT_VALUE = "fr?ag/ment";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
QTEST_CASE ( Constructor1_InputCharactersThatShouldNotBeEncodedAreDecoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://userinfo@authority:port/pa%42th1/pa%50th2?que%43ry=value#fr%51agment";

    const string_q EXPECTED_PATH_VALUE = "/paBth1/paPth2";
    const string_q EXPECTED_QUERY_VALUE = "queCry=value";
    const string_q EXPECTED_FRAGMENT_VALUE = "frQagment";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are lowercased.
/// </summary>
QTEST_CASE ( Constructor1_SchemeAndAuthorityAreLowercased_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "SCHEME://UserInfo@HOST:1234/path1/path2?query=value#fragment";

    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:1234";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are not encoded.
/// </summary>
QTEST_CASE ( Constructor1_SchemeAndAuthorityAreNotEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "sch eme://user<info@auth ority:port/path1/path2?query=value#fragment";
    
    const string_q EXPECTED_SCHEME_VALUE = "sch eme";
    const string_q EXPECTED_AUTHORITY_VALUE = "user<info@auth ority:port";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are not lowercased.
/// </summary>
QTEST_CASE ( Constructor1_PathQueryAndFragmentAreNotLowercased_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://userinfo@authority:port/PATH1/pAth2?querY=vaLlue#FRAGMENt";

    const string_q EXPECTED_PATH_VALUE = "/PATH1/pAth2";
    const string_q EXPECTED_QUERY_VALUE = "querY=vaLlue";
    const string_q EXPECTED_FRAGMENT_VALUE = "FRAGMENt";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are not lowercased.
/// </summary>
QTEST_CASE ( Constructor1_DotSegmentsAreRemoved_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://userinfo@authority/path1/./path2/../path3";

    const string_q EXPECTED_PATH_VALUE = "/path1/path3";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path contains one segment when the URI does not contain any separator.
/// </summary>
QTEST_CASE ( Constructor1_ThePathContainsOneSegmentWhenTheUriDoesNotContainAnySeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "schemeauthoritypath";
    const string_q EXPECTED_PATH_VALUE = "schemeauthoritypath";

    // [Execution]
    QUri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the URI is correctly copied.
/// </summary>
QTEST_CASE ( Constructor2_TheUriIsCorrectlyCopied_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "scheme://authority/path?query#fragment";
    const QUri ORIGINAL_URI(INPUT_STRING);

    // [Execution]
    QUri uri(ORIGINAL_URI);
    
    // [Verification]
    BOOST_CHECK(uri == ORIGINAL_URI);
    BOOST_CHECK(uri.GetOriginalString() == INPUT_STRING);
}

/// <summary>
/// Checks that the URI is correctly copied.
/// </summary>
QTEST_CASE ( AssignmentOperator1_TheUriIsCorrectlyCopied_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    const string_q INPUT_STRING2 = "scheme://authority/path?query#fragment";
    QUri uri(INPUT_STRING1);
    const QUri ORIGINAL_URI(INPUT_STRING2);

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri == ORIGINAL_URI);
    BOOST_CHECK(uri.GetOriginalString() == INPUT_STRING2);
}

/// <summary>
/// Checks that the scheme has the expected value when the input string only contains a scheme.
/// </summary>
QTEST_CASE ( AssignmentOperator2_SchemeIsWhatExpectedWhenInputContainsSchemeOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme:";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_VALUE = "scheme";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority have the expected value when the input string only contains a scheme and the authority.
/// </summary>
QTEST_CASE ( AssignmentOperator2_SchemeAndAuthorityAreWhatExpectedWhenInputContainsSchemeAndAuthorityOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://authority";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "authority";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority and the path have the expected value when the input string contains the scheme, the authority and the path.
/// </summary>
QTEST_CASE ( AssignmentOperator2_SchemeAuthorityAndPathAreWhatExpectedWhenInputContainsSchemeAuthorityAndPath_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://authority/path";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "authority";
    const string_q EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority, the path and the query have the expected value when the input string contains the scheme, the authority, the path and the query.
/// </summary>
QTEST_CASE ( AssignmentOperator2_SchemeAuthorityPathAndQueryAreWhatExpectedWhenInputContainsSchemeAuthorityPathAndQuery_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://authority/path?query";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "authority";
    const string_q EXPECTED_PATH_VALUE = "/path";
    const string_q EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the scheme and the path have the expected value when the input string contains the scheme and the path only.
/// </summary>
QTEST_CASE ( AssignmentOperator2_SchemeAndPathAreWhatExpectedWhenInputContainsSchemeAndPathOnly_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme:/pathsegment1/pathsegment2";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_PATH_VALUE = "/pathsegment1/pathsegment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetPath()   == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the host has the expected value when the authority is formed only by a host.
/// </summary>
QTEST_CASE ( AssignmentOperator2_HostIsWhatExpectedWhenAuthorityIsFormedOnlyByHost_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://authority/path";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_HOST_VALUE = "authority";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetHost() == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information and the host have the expected value when the authority is formed only by a host and the user information.
/// </summary>
QTEST_CASE ( AssignmentOperator2_UserInfoAndHostAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoAndHost_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "//userinfo@host";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_USERINFO_VALUE = "userinfo";
    const string_q EXPECTED_HOST_VALUE = "host";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information, the port and the host have the expected value when the authority is formed only by a host, the port and the user information.
/// </summary>
QTEST_CASE ( AssignmentOperator2_UserInfoHostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoHostAndPort_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "//userinfo@host:port";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_USERINFO_VALUE = "userinfo";
    const string_q EXPECTED_HOST_VALUE = "host";
    const string_q EXPECTED_PORT_VALUE = "port";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()     == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the port and the host have the expected value when the authority is formed only by a host and the port.
/// </summary>
QTEST_CASE ( AssignmentOperator2_HostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByHostAndPort_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "//host:port";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_HOST_VALUE = "host";
    const string_q EXPECTED_PORT_VALUE = "port";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()     == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the authority and the path have the expected value when the URI is formed only by the authority and the path.
/// </summary>
QTEST_CASE ( AssignmentOperator2_AuthorityAndPathAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndPath_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "//userinfo@host:port/path";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_q EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the authority and the query have the expected value when the URI is formed only by the authority and the query.
/// </summary>
QTEST_CASE ( AssignmentOperator2_AuthorityAndQueryAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndQuery_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "//userinfo@host:port?query";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_q EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the authority and the fragment have the expected value when the URI is formed only by the authority and the fragment.
/// </summary>
QTEST_CASE ( AssignmentOperator2_AuthorityAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndFragment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "//userinfo@host:port#fragment";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_q EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    string_q c = uri.GetAuthority();
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetFragment()  == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path does not start with a slash when it does not start with a slash in the input string.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathDoesNotStartWithSlashWhenUriIsFormedOnlyByPathWhichDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "segment1/segment2";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path starts with a slash when it starts with a slash in the input string.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathStartsWithSlashWhenUriIsFormedOnlyByPathWhichStartsWithSlash_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "/segment1/segment2";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "/segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path does not include the initial dot segment when it starts with one dot.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathDoesNotIncludeDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithOneDot_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "./segment1/segment2";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path includes the initial dot segment when it starts with two dots.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathIncludesDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithTwoDots_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "../segment1/segment2";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "../segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path and the query have the expected value when the URI is formed only by the path and the query.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathAndQueryAreWhatExpectedWhenUriIsFormedOnlyByPathAndQuery_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "path1/path2?query=value";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "path1/path2";
    const string_q EXPECTED_QUERY_VALUE = "query=value";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()  == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery() == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the path and the fragment have the expected value when the URI is formed only by the path and the fragment.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByPathAndFragment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "path1/path2#fragment";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "path1/path2";
    const string_q EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path is empty and starts with a slash when the URI only contains a single slash.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathIsEmptyAndStartsWithSlashWhenUriContainsOnlyOneSlash_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "/";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "/";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathQueryAndFragmentAreEncoded_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    string_q INPUT_STRING2 = "scheme://userinfo@authority:port/p<a th1/pa[]t{}h2?qu ery=va<lue#fra{gment";
    INPUT_STRING2.Append(char_q(0x0470)); // CYRILLIC CAPITAL LETTER PSI, UTF8: D1 B0
    INPUT_STRING2.Append(char_q(0x01C2)); // LATIN LETTER ALVEOLAR CLICK, UTF8: C7 82
    const QUri ORIGINAL_URI(INPUT_STRING2);

    const string_q EXPECTED_PATH_VALUE = "/p%3Ca%20th1/pa%5B%5Dt%7B%7Dh2";
    const string_q EXPECTED_QUERY_VALUE = "qu%20ery=va%3Clue";
    const string_q EXPECTED_FRAGMENT_VALUE = "fra%7Bgment%D1%B0%C7%82";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the question mark ("?") and the slash ("/") are allowed in both the query and the fragment.
/// </summary>
QTEST_CASE ( AssignmentOperator2_QuestionMarkAndSlashAreAllowedInQueryAndFragment_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://userinfo@authority:port/path1/path2?que?r/y=value#fr?ag/ment";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_QUERY_VALUE = "que?r/y=value";
    const string_q EXPECTED_FRAGMENT_VALUE = "fr?ag/ment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
QTEST_CASE ( AssignmentOperator2_InputCharactersThatShouldNotBeEncodedAreDecoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://userinfo@authority:port/pa%42th1/pa%50th2?que%43ry=value#fr%51agment";
    const QUri ORIGINAL_URI(INPUT_STRING2);

    const string_q EXPECTED_PATH_VALUE = "/paBth1/paPth2";
    const string_q EXPECTED_QUERY_VALUE = "queCry=value";
    const string_q EXPECTED_FRAGMENT_VALUE = "frQagment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are lowercased.
/// </summary>
QTEST_CASE ( AssignmentOperator2_SchemeAndAuthorityAreLowercased_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "SCHEME://UserInfo@HOST:1234/path1/path2?query=value#fragment";
    const QUri ORIGINAL_URI(INPUT_STRING2);

    const string_q EXPECTED_SCHEME_VALUE = "scheme";
    const string_q EXPECTED_AUTHORITY_VALUE = "userinfo@host:1234";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are not encoded.
/// </summary>
QTEST_CASE ( AssignmentOperator2_SchemeAndAuthorityAreNotEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "sch eme://user<info@auth ority:port/path1/path2?query=value#fragment";
    const QUri ORIGINAL_URI(INPUT_STRING2);

    const string_q EXPECTED_SCHEME_VALUE = "sch eme";
    const string_q EXPECTED_AUTHORITY_VALUE = "user<info@auth ority:port";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are not lowercased.
/// </summary>
QTEST_CASE ( AssignmentOperator2_PathQueryAndFragmentAreNotLowercased_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://userinfo@authority:port/PATH1/pAth2?querY=vaLlue#FRAGMENt";
    const QUri ORIGINAL_URI(INPUT_STRING2);

    const string_q EXPECTED_PATH_VALUE = "/PATH1/pAth2";
    const string_q EXPECTED_QUERY_VALUE = "querY=vaLlue";
    const string_q EXPECTED_FRAGMENT_VALUE = "FRAGMENt";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are not lowercased.
/// </summary>
QTEST_CASE ( AssignmentOperator2_DotSegmentsAreRemoved_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "scheme://userinfo@authority/path1/./path2/../path3";
    const QUri ORIGINAL_URI(INPUT_STRING2);

    const string_q EXPECTED_PATH_VALUE = "/path1/path3";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path contains one segment when the URI does not contain any separator.
/// </summary>
QTEST_CASE ( AssignmentOperator2_ThePathContainsOneSegmentWhenTheUriDoesNotContainAnySeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "xxx";
    QUri uri(INPUT_STRING1);
    const string_q INPUT_STRING2 = "schemeauthoritypath";
    const QUri ORIGINAL_URI(INPUT_STRING2);
    const string_q EXPECTED_PATH_VALUE = "schemeauthoritypath";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that it returns True when URIs are equal although the original strings are not equal.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsTrueWhenUrisAreEqualAlthoughOriginalStringWasNotEqual_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const string_q INPUT_STRING2 = "scheme://authority/path/path3?qu ery#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when URIs are equal and original strings were equal.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsTrueWhenUrisAreEqualAndOriginalStringWasEqual_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const QUri URI1(INPUT_STRING);
    const QUri URI2(INPUT_STRING);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the scheme is different.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenSchemeIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme1://authority/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme2://authority/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the host is different.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenHostIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority1/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme://authority2/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the user information is different.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenUserInfoIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://userinfo1@authority/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme://userinfo2@authority/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the port is different.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenPortIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority:port1/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme://authority:port2/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path is different.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenPathIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority/path1?query#fragment";
    const string_q INPUT_STRING2 = "scheme://authority/path2?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the query is different.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenQueryIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority/path?query1#fragment";
    const string_q INPUT_STRING2 = "scheme://authority/path?query2#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the fragment is different.
/// </summary>
QTEST_CASE ( EqualityOperator_ReturnsFalseWhenFragmentIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority/path?query#fragment1";
    const string_q INPUT_STRING2 = "scheme://authority/path?query#fragment2";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when URIs are equal although the original strings are not equal.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsFalseWhenUrisAreEqualAlthoughOriginalStringWasNotEqual_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const string_q INPUT_STRING2 = "scheme://authority/path/path3?qu ery#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when URIs are equal and original strings were equal.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsFalseWhenUrisAreEqualAndOriginalStringWasEqual_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const QUri URI1(INPUT_STRING);
    const QUri URI2(INPUT_STRING);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the scheme is different.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenSchemeIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme1://authority/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme2://authority/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the host is different.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenHostIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority1/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme://authority2/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the user information is different.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenUserInfoIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://userinfo1@authority/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme://userinfo2@authority/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the port is different.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenPortIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority:port1/path?query#fragment";
    const string_q INPUT_STRING2 = "scheme://authority:port2/path?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the path is different.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenPathIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority/path1?query#fragment";
    const string_q INPUT_STRING2 = "scheme://authority/path2?query#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the query is different.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenQueryIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority/path?query1#fragment";
    const string_q INPUT_STRING2 = "scheme://authority/path?query2#fragment";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the fragment is different.
/// </summary>
QTEST_CASE ( InequalityOperator_ReturnsTrueWhenFragmentIsDifferent_Test )
{
    // [Preparation]
    const string_q INPUT_STRING1 = "scheme://authority/path?query#fragment1";
    const string_q INPUT_STRING2 = "scheme://authority/path?query#fragment2";
    const QUri URI1(INPUT_STRING1);
    const QUri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that question marks ("?") and slashes ("/") are encoded.
/// </summary>
QTEST_CASE ( EncodePathSegment_QuestionMarkAndSlashAreEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "/?";
    const string_q EXPECTED_STRING = "%2F%3F";
    string_q strResult;

    // [Execution]
    QUri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the characters that are allowed in the path are not encoded.
/// </summary>
QTEST_CASE ( EncodePathSegment_AllowedCharsAreNotEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~&'*(),$=!+;:@";
    const string_q EXPECTED_STRING = INPUT_STRING;
    string_q strResult;

    // [Execution]
    QUri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that Unicode (non-ASCII) characters are encoded.
/// </summary>
QTEST_CASE ( EncodePathSegment_UnicodeCharsAreEncoded_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    string_q INPUT_STRING;
    INPUT_STRING.Append(char_q(0x00D1)); // LATIN CAPITAL LETTER N WITH TILDE, UTF8: C3 91
    INPUT_STRING.Append(char_q(0x10A3)); // GEORGIAN CAPITAL LETTER DON, UTF8: E1 82 A3
    INPUT_STRING.Append(char_q(0x16E3)); // RUNIC LETTER CALC, UTF8: E1 9B A3
    INPUT_STRING.Append(char_q(0xFF96)); // HALFWIDTH KATAKANA LETTER YO, UTF8: EF BE 96
    const string_q EXPECTED_STRING = "%C3%91%E1%82%A3%E1%9B%A3%EF%BE%96";
    string_q strResult;

    // [Execution]
    QUri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the ASCII characters that are not allowed in the path are encoded.
/// </summary>
QTEST_CASE ( EncodePathSegment_AsciiNotAllowedCharsAreEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "<> \\[]{}\"|";
    const string_q EXPECTED_STRING = "%3C%3E%20%5C%5B%5D%7B%7D%22%7C";
    string_q strResult;

    // [Execution]
    QUri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the percent sign ("%") is not encoded.
/// </summary>
QTEST_CASE ( EncodePathSegment_PercentSignIsNotEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "%";
    const string_q EXPECTED_STRING = "%";
    string_q strResult;

    // [Execution]
    QUri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the input string can be also the output string.
/// </summary>
QTEST_CASE ( EncodePathSegment_InputStringCanBeAlsoOutputString_Test )
{
    // [Preparation]
    string_q strInputOutput = "123 456";
    const string_q EXPECTED_STRING = "123%20456";

    // [Execution]
    QUri::EncodePathSegment(strInputOutput, strInputOutput);
    
    // [Verification]
    BOOST_CHECK(strInputOutput == EXPECTED_STRING);
}

/// <summary>
/// Checks that the output string equals empty when the input string is empty.
/// </summary>
QTEST_CASE ( EncodePathSegment_OutputStringEqualsEmptyWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_STRING = string_q::GetEmpty();
    string_q strResult = "123456";

    // [Execution]
    QUri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that question marks ("?") and slashes ("/") are not encoded.
/// </summary>
QTEST_CASE ( EncodeQueryOrFragment_QuestionMarkAndSlashAreNotEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "/?";
    const string_q EXPECTED_STRING = "/?";
    string_q strResult;

    // [Execution]
    QUri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the characters that are allowed in the path are not encoded.
/// </summary>
QTEST_CASE ( EncodeQueryOrFragment_AllowedCharsAreNotEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~&'*(),$=!+;:@";
    const string_q EXPECTED_STRING = INPUT_STRING;
    string_q strResult;

    // [Execution]
    QUri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that Unicode (non-ASCII) characters are encoded.
/// </summary>
QTEST_CASE ( EncodeQueryOrFragment_UnicodeCharsAreEncoded_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    string_q INPUT_STRING;
    INPUT_STRING.Append(char_q(0x00D1)); // LATIN CAPITAL LETTER N WITH TILDE, UTF8: C3 91
    INPUT_STRING.Append(char_q(0x10A3)); // GEORGIAN CAPITAL LETTER DON, UTF8: E1 82 A3
    INPUT_STRING.Append(char_q(0x16E3)); // RUNIC LETTER CALC, UTF8: E1 9B A3
    INPUT_STRING.Append(char_q(0xFF96)); // HALFWIDTH KATAKANA LETTER YO, UTF8: EF BE 96
    const string_q EXPECTED_STRING = "%C3%91%E1%82%A3%E1%9B%A3%EF%BE%96";
    string_q strResult;

    // [Execution]
    QUri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the ASCII characters that are not allowed in the path are encoded.
/// </summary>
QTEST_CASE ( EncodeQueryOrFragment_AsciiNotAllowedCharsAreEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "<> \\[]{}\"|";
    const string_q EXPECTED_STRING = "%3C%3E%20%5C%5B%5D%7B%7D%22%7C";
    string_q strResult;

    // [Execution]
    QUri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the percent sign ("%") is not encoded.
/// </summary>
QTEST_CASE ( EncodeQueryOrFragment_PercentSignIsNotEncoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "%";
    const string_q EXPECTED_STRING = "%";
    string_q strResult;

    // [Execution]
    QUri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the input string can be also the output string.
/// </summary>
QTEST_CASE ( EncodeQueryOrFragment_InputStringCanBeAlsoOutputString_Test )
{
    // [Preparation]
    string_q strInputOutput = "123 456";
    const string_q EXPECTED_STRING = "123%20456";

    // [Execution]
    QUri::EncodeQueryOrFragment(strInputOutput, strInputOutput);
    
    // [Verification]
    BOOST_CHECK(strInputOutput == EXPECTED_STRING);
}

/// <summary>
/// Checks that the output string equals empty when the input string is empty.
/// </summary>
QTEST_CASE ( EncodeQueryOrFragment_OutputStringEqualsEmptyWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_STRING = string_q::GetEmpty();
    string_q strResult = "123456";

    // [Execution]
    QUri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the allowed characters are decoded.
/// </summary>
QTEST_CASE ( Decode_AllowedCharactersAreDecoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "%41%61%2B";
    const string_q EXPECTED_STRING = "Aa+";
    string_q strResult;

    // [Execution]
    QUri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the not allowed ASCII characters are decoded.
/// </summary>
QTEST_CASE ( Decode_AsciiNotAllowedCharactersAreDecoded_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = "%20%3C%7B";
    const string_q EXPECTED_STRING = " <{";
    string_q strResult;

    // [Execution]
    QUri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the Unicode characters are decoded.
/// </summary>
QTEST_CASE ( Decode_UnicodeCharactersAreDecoded_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const string_q INPUT_STRING = "%C9%AC%CD%9C%D9%82";
    string_q EXPECTED_STRING;
    EXPECTED_STRING.Append(char_q(0x026C)); // LATIN SMALL LETTER L WITH BELT, UTF8: C9 AC
    EXPECTED_STRING.Append(char_q(0x035C)); // COMBINING DOUBLE BREVE BELOW, UTF8: CD 9C
    EXPECTED_STRING.Append(char_q(0x0642)); // ARABIC LETTER QAF, UTF8: D9 82
    string_q strResult;

    // [Execution]
    QUri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the input string can be also the output string.
/// </summary>
QTEST_CASE ( Decode_InputStringCanBeAlsoOutputString_Test )
{
    // [Preparation]
    string_q strInputOutput = "123%20456";
    const string_q EXPECTED_STRING = "123 456";

    // [Execution]
    QUri::Decode(strInputOutput, strInputOutput);
    
    // [Verification]
    BOOST_CHECK(strInputOutput == EXPECTED_STRING);
}

/// <summary>
/// Checks that the output string equals empty when the input string is empty.
/// </summary>
QTEST_CASE ( Decode_OutputStringEqualsEmptyWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING = string_q::GetEmpty();
    const string_q EXPECTED_STRING = string_q::GetEmpty();
    string_q strResult = "123456";

    // [Execution]
    QUri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that a common hexadecimal value is correctly converted to an integer.
/// </summary>
QTEST_CASE ( CreateIntegerFromHexadecimalString_CreatesIntegerFromCommonHexadecimalValue_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "6AC5FF01";
    const u32_q EXPECTED_VALUE = 0x6AC5FF01;
    u32_q uResult = 0;

    // [Execution]
    QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING, uResult);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a zero hexadecimal value is correctly converted to an integer.
/// </summary>
QTEST_CASE ( CreateIntegerFromHexadecimalString_CreatesIntegerFromHexadecimalValueWhenItEqualsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "00000000";
    const u32_q EXPECTED_VALUE = 0;
    u32_q uResult = 0;

    // [Execution]
    QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING, uResult);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a maximum hexadecimal value is correctly converted to an integer.
/// </summary>
QTEST_CASE ( CreateIntegerFromHexadecimalString_CreatesIntegerFromHexadecimalValueWhenItEqualsMaximum_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "FFFFFFFF";
    const u32_q EXPECTED_VALUE = 0xFFFFFFFF;
    u32_q uResult = 0;

    // [Execution]
    QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING, uResult);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it can create integers of different sizes.
/// </summary>
QTEST_CASE ( CreateIntegerFromHexadecimalString_CreatesIntegersOfDifferentSizes_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

    // [Preparation]
    const string_q INPUT_STRING_8BITS  = "2A";
    const string_q INPUT_STRING_16BITS = "6AC5";
    const string_q INPUT_STRING_32BITS = "6AC5FF01";
    const string_q INPUT_STRING_64BITS = "6AC5FF016AC5FF01";
    const u8_q  EXPECTED_VALUE_8BITS  = 0x2AU;
    const u16_q EXPECTED_VALUE_16BITS = 0x6AC5U;
    const u32_q EXPECTED_VALUE_32BITS = 0x6AC5FF01U;
    const u64_q EXPECTED_VALUE_64BITS = 0x6AC5FF016AC5FF01ULL;
    u8_q  uResult8Bits  = 0;
    u16_q uResult16Bits = 0;
    u32_q uResult32Bits = 0;
    u64_q uResult64Bits = 0;

    // [Execution]
    QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING_8BITS,  uResult8Bits);
    QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING_16BITS, uResult16Bits);
    QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING_32BITS, uResult32Bits);
    QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING_64BITS, uResult64Bits);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult8Bits,  EXPECTED_VALUE_8BITS);
    BOOST_CHECK_EQUAL(uResult16Bits, EXPECTED_VALUE_16BITS);
    BOOST_CHECK_EQUAL(uResult32Bits, EXPECTED_VALUE_32BITS);
    BOOST_CHECK_EQUAL(uResult64Bits, EXPECTED_VALUE_64BITS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when string's length does not correspond to the integer type's size.
/// </summary>
QTEST_CASE ( CreateIntegerFromHexadecimalString_AssertionFailsWhenInputStringLengthDoesNotCorrspondToIntegerSize_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "A45F";
    const bool ASSERTION_FAILED = true;
    u32_q uResult32Bits = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QUriWhiteBox::CreateIntegerFromHexadecimalString(INPUT_STRING, uResult32Bits);
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
/// Checks that single dot segments are removed when they appear the first.
/// </summary>
QTEST_CASE ( RemoveDotSegments_SingleDotSegmentsAreRemovedWhenTheyAppearTheFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q SINGLE_DOT(".");

    QDynamicArray<string_q> inputArrayWithSingleDot(3);
    inputArrayWithSingleDot.Add(SINGLE_DOT);
    inputArrayWithSingleDot.Add("path1");
    inputArrayWithSingleDot.Add("path2");

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithSingleDot);
    
    // [Verification]
    bool bSingleDotSegmentWasRemoved = inputArrayWithSingleDot[0] != SINGLE_DOT;

    for(QDynamicArray<string_q>::QArrayIterator it = inputArrayWithSingleDot.GetFirst(); !it.IsEnd(); ++it)
        bSingleDotSegmentWasRemoved = bSingleDotSegmentWasRemoved && *it != SINGLE_DOT;

    BOOST_CHECK(bSingleDotSegmentWasRemoved);
}

/// <summary>
/// Checks that double dot segments are not removed when they appear the first.
/// </summary>
QTEST_CASE ( RemoveDotSegments_DoubleDotSegmentsAreNotRemovedWhenTheyAppearTheFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q DOUBLE_DOT("..");

    QDynamicArray<string_q> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    bool bDoubleDotSegmentWasNotRemoved = inputArrayWithDoubleDot[0] == DOUBLE_DOT;

    BOOST_CHECK(bDoubleDotSegmentWasNotRemoved);
}

/// <summary>
/// Checks that contiguous double dot segments are not removed when they appear the first.
/// </summary>
QTEST_CASE ( RemoveDotSegments_ContiguousDoubleDotSegmentsAreNotRemovedWhenTheyAppearTheFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q DOUBLE_DOT("..");

    QDynamicArray<string_q> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    bool bDoubleDotSegmentWasNotRemoved = inputArrayWithDoubleDot[0] == DOUBLE_DOT && 
                                          inputArrayWithDoubleDot[1] == DOUBLE_DOT;

    BOOST_CHECK(bDoubleDotSegmentWasNotRemoved);
}

/// <summary>
/// Checks that it works as expected when there are several double dot segments after one common segment at the beginning.
/// </summary>
QTEST_CASE ( RemoveDotSegments_WorksAsExpectedWhenThereAreSeveralDoubleDotSegmentsAfterOneCommonSegmentAtTheBeginning_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q DOUBLE_DOT("..");

    const string_q EXPECTED_FIRST_SEGMENT = DOUBLE_DOT;
    const pointer_uint_q EXPECTED_COUNT = 1;
    QDynamicArray<string_q> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    string_q strFirstElement = inputArrayWithDoubleDot[0];
    pointer_uint_q uCount = inputArrayWithDoubleDot.GetCount();

    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(strFirstElement == EXPECTED_FIRST_SEGMENT);
}

/// <summary>
/// Checks that it works as expected when there are more double dot segments than common segments at the beginning.
/// </summary>
QTEST_CASE ( RemoveDotSegments_WorksAsExpectedWhenThereAreMoreDoubleDotSegmentsThanCommonSegmentsAtTheBeginning_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q DOUBLE_DOT("..");

    const string_q EXPECTED_FIRST_SEGMENT = DOUBLE_DOT;
    const pointer_uint_q EXPECTED_COUNT = 1;
    QDynamicArray<string_q> inputArrayWithDoubleDot(5);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    string_q strFirstElement = inputArrayWithDoubleDot[0];
    pointer_uint_q uCount = inputArrayWithDoubleDot.GetCount();

    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(strFirstElement == EXPECTED_FIRST_SEGMENT);
}

/// <summary>
/// Checks that dot segments are not removed when the path is compound only of double dot segments.
/// </summary>
QTEST_CASE ( RemoveDotSegments_DotSegmentsAreNotRemovedWhenPathIsCompoundOnlyOfDoubleDotSegments_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q DOUBLE_DOT("..");

    const pointer_uint_q EXPECTED_COUNT = 3;
    QDynamicArray<string_q> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    pointer_uint_q uCount = inputArrayWithDoubleDot.GetCount();

    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that single dot segments are removed when they appear in between of contiguous double dot segments which appear the first.
/// </summary>
QTEST_CASE ( RemoveDotSegments_SingleDotSegmentsAreRemovedWhenTheyAppearBetweenContiguousDoubleDotSegmentsThatAppearTheFirst_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q SINGLE_DOT(".");
    const string_q DOUBLE_DOT("..");

    QDynamicArray<string_q> inputArrayWithDoubleDot(5);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(SINGLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    bool bSingleDotSegmentWasRemoved = inputArrayWithDoubleDot[0] == DOUBLE_DOT && 
                                          inputArrayWithDoubleDot[1] == DOUBLE_DOT;

    BOOST_CHECK(bSingleDotSegmentWasRemoved);
}

/// <summary>
/// Checks that single dot segments are just removed.
/// </summary>
QTEST_CASE ( RemoveDotSegments_SingleDotSegmentsAreJustRemoved_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q SINGLE_DOT(".");

    QDynamicArray<string_q> inputArrayWithSingleDot(5);
    inputArrayWithSingleDot.Add(SINGLE_DOT);
    inputArrayWithSingleDot.Add("path1");
    inputArrayWithSingleDot.Add(SINGLE_DOT);
    inputArrayWithSingleDot.Add("path2");
    inputArrayWithSingleDot.Add(SINGLE_DOT);

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithSingleDot);
 
    // [Verification]
    bool bSingleDotSegmentWasRemoved = true;

    for(QDynamicArray<string_q>::QArrayIterator it = inputArrayWithSingleDot.GetFirst(); !it.IsEnd(); ++it)
        bSingleDotSegmentWasRemoved = bSingleDotSegmentWasRemoved && *it != SINGLE_DOT;

    BOOST_CHECK(bSingleDotSegmentWasRemoved);
}

/// <summary>
/// Checks that double dot segments imply previous segment to be removed.
/// </summary>
QTEST_CASE ( RemoveDotSegments_DoubleDotSegmentsImplyPreviousSegmentToBeRemoved_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q DOUBLE_DOT("..");
    const string_q SEGMENT_TO_BE_REMOVED("path2");

    QDynamicArray<string_q> inputArrayWithDoubleDots(4);
    inputArrayWithDoubleDots.Add("path1");
    inputArrayWithDoubleDots.Add(SEGMENT_TO_BE_REMOVED);
    inputArrayWithDoubleDots.Add(DOUBLE_DOT);
    inputArrayWithDoubleDots.Add("path3");

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDots);
 
    // [Verification]
    bool bDoubleDotSegmentWasRemoved = true;
    bool bSegmentPriorToDotSegmentWasRemoved = true;
    
    QDynamicArray<string_q>::QArrayIterator it = inputArrayWithDoubleDots.GetFirst();

    for(; !it.IsEnd(); ++it)
        bDoubleDotSegmentWasRemoved = bDoubleDotSegmentWasRemoved && *it != DOUBLE_DOT;

    for(it.MoveFirst(); !it.IsEnd(); ++it)
        bSegmentPriorToDotSegmentWasRemoved = bSegmentPriorToDotSegmentWasRemoved && *it != SEGMENT_TO_BE_REMOVED;

    BOOST_CHECK(bDoubleDotSegmentWasRemoved);
}

/// <summary>
/// Checks that dot segments can be concatenated.
/// </summary>
QTEST_CASE ( RemoveDotSegments_DotSegmentsCanBeConcatenated_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    const string_q SINGLE_DOT(".");
    const string_q DOUBLE_DOT("..");

    QDynamicArray<string_q> EXPECTED_ARRAY(8);
    EXPECTED_ARRAY.Add("path1");
    EXPECTED_ARRAY.Add("path4");
    
    QDynamicArray<string_q> inputArrayWithDots(2);
    inputArrayWithDots.Add("path1");
    inputArrayWithDots.Add("path2");
    inputArrayWithDots.Add(SINGLE_DOT);
    inputArrayWithDots.Add("path3");
    inputArrayWithDots.Add(SINGLE_DOT);
    inputArrayWithDots.Add(DOUBLE_DOT);
    inputArrayWithDots.Add(DOUBLE_DOT);
    inputArrayWithDots.Add("path4");

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(inputArrayWithDots);
 
    // [Verification]
    bool bResultantArrayIsWhatExpected = true;

    QDynamicArray<string_q>::QArrayIterator iExpected = EXPECTED_ARRAY.GetFirst();
    QDynamicArray<string_q>::QArrayIterator iResult = inputArrayWithDots.GetFirst();

    for(; !iExpected.IsEnd(); ++iExpected, ++iResult)
        bResultantArrayIsWhatExpected = bResultantArrayIsWhatExpected && *iExpected == *iResult;

    BOOST_CHECK(bResultantArrayIsWhatExpected);
}

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
QTEST_CASE ( RemoveDotSegments_NothingHappensWhenArrayIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    QDynamicArray<string_q> arEmptyArray(1);

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(arEmptyArray);
 
    // [Verification]
    BOOST_CHECK(arEmptyArray.IsEmpty());
}

/// <summary>
/// Checks that nothing happens when the array contains only an empty string.
/// </summary>
QTEST_CASE ( RemoveDotSegments_NothingHappensWhenArrayContainsOnlyAnEmptyString_Test )
{
    using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;

    // [Preparation]
    QDynamicArray<string_q> arEmptyArray(1);
    arEmptyArray.Add(string_q::GetEmpty());

    // [Execution]
    QUriWhiteBox::RemoveDotSegments(arEmptyArray);
 
    // [Verification]
    BOOST_CHECK(arEmptyArray[0].IsEmpty());
}

/// <summary>
/// Checks that the user information appears in the authority if it was defined.
/// </summary>
QTEST_CASE ( GetAuthority_UserInformationAppearsIfDefined_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//userinfo@host");
    const string_q EXPECTED_STRING("userinfo@host");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the host appears in the authority if it was defined.
/// </summary>
QTEST_CASE ( GetAuthority_HostAppearsIfDefined_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//host:port");
    const string_q EXPECTED_STRING("host:port");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the port appears in the authority if it was defined.
/// </summary>
QTEST_CASE ( GetAuthority_PortAppearsIfDefined_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//host:port");
    const string_q EXPECTED_STRING("host:port");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the authority does not include the initial separator.
/// </summary>
QTEST_CASE ( GetAuthority_AuthorityDoesNotIncludeInitialSeparator_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//authority");
    const string_q EXPECTED_STRING("authority");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the entire authority is correctly formed.
/// </summary>
QTEST_CASE ( GetAuthority_TheEntireAuthorityIsCorrectlyFormed_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("//userinfo@host:port");
    const string_q EXPECTED_STRING("userinfo@host:port");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result does not start with a slash when it is a relative path.
/// </summary>
QTEST_CASE ( GetPath_ItDoesNotStartWithSlashWhenIsRelativePath_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("path1/path/path3");
    const string_q EXPECTED_STRING("path1/path/path3");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result starts with a slash when it is an absolute path (relative reference URI).
/// </summary>
QTEST_CASE ( GetPath_ItStartsWithSlashWhenIsAbsolutePath_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/path1/path/path3");
    const string_q EXPECTED_STRING("/path1/path/path3");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result does not include any dot segment.
/// </summary>
QTEST_CASE ( GetPath_DotSegmentsAreRemoved_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/path1/../path/./path3");
    const string_q EXPECTED_STRING("/path/path3");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result ends with a slash when last segment is empty.
/// </summary>
QTEST_CASE ( GetPath_EndsWithSlashWhenLastSegmentIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_STRING("/path1/path/path3/");
    const string_q EXPECTED_STRING("/path1/path/path3/");
    QUri uri(INPUT_STRING);

    // [Execution]
    string_q strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns True when the URI has not got scheme.
/// </summary>
QTEST_CASE ( IsRelative_ReturnsTrueWhenSchemeIsNotPresent_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const string_q INPUT_STRING("//authority/path?query#fragment");
    QUri uri(INPUT_STRING);

    // [Execution]
    bool bResult = uri.IsRelative();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the URI has got scheme.
/// </summary>
QTEST_CASE ( IsRelative_ReturnsFalseWhenSchemeIsPresent_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const string_q INPUT_STRING("scheme://authority/path?query#fragment");
    QUri uri(INPUT_STRING);

    // [Execution]
    bool bResult = uri.IsRelative();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: QUri
QTEST_SUITE_END()
