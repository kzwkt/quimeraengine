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

#include "QUri.h"

#include "SQInteger.h"
#include "EQComparisonType.h"
#include "EQTextEncoding.h"

using Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray;
using Kinesis::QuimeraEngine::Common::DataTypes::char_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace IO
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QUri::TBitField QUri::FLAG_SCHEME_IS_DEFINED    = 0x01; // 0000 0001
const QUri::TBitField QUri::FLAG_AUTHORITY_IS_DEFINED = 0x02; // 0000 0010
const QUri::TBitField QUri::FLAG_QUERY_IS_DEFINED     = 0x04; // 0000 0100
const QUri::TBitField QUri::FLAG_FRAGMENT_IS_DEFINED  = 0x08; // 0000 1000
const QUri::TBitField QUri::FLAG_USERINFO_IS_DEFINED  = 0x10; // 0001 0000
const QUri::TBitField QUri::FLAG_HOST_IS_DEFINED      = 0x20; // 0010 0000
const QUri::TBitField QUri::FLAG_PORT_IS_DEFINED      = 0x40; // 0100 0000


const string_q QUri::SINGLE_DOT_SEGMENT = ".";
const string_q QUri::DOUBLE_DOT_SEGMENT = "..";
const string_q QUri::DOUBLE_SLASH = "//";

const string_q QUri::CHAR_COLON = ":";
const string_q QUri::CHAR_SLASH = "/";
const string_q QUri::CHAR_QUESTION_MARK = "?";
const string_q QUri::CHAR_NUMBER_SIGN   = "#";
const string_q QUri::CHAR_OPENING_SQUARE_BRACKET = "[";
const string_q QUri::CHAR_CLOSING_SQUARE_BRACKET = "]";
const string_q QUri::CHAR_AT_SIGN = "@";
const string_q QUri::CHAR_EXCLAMATION_MARK = "!";
const string_q QUri::CHAR_DOLLAR_SIGN = "$";
const string_q QUri::CHAR_AMPERSAND   = "&";
const string_q QUri::CHAR_APOSTROPHE  = "'";
const string_q QUri::CHAR_COMMA       = ",";
const string_q QUri::CHAR_OPENING_PARENTHESES = "(";
const string_q QUri::CHAR_CLOSING_PARENTHESES = ")";
const string_q QUri::CHAR_SEMICOLON    = ";";
const string_q QUri::CHAR_ASTERISK     = "*";
const string_q QUri::CHAR_EQUAL_SIGN   = "=";
const string_q QUri::CHAR_PLUS_SIGN    = "+";
const string_q QUri::CHAR_PERCENT_SIGN = "%";


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QUri::QUri(const string_q &strUri) : m_strOriginalString(strUri), 
                                     m_definedComponents(0)
{
    QE_ASSERT_ERROR(!strUri.IsEmpty(), "The input string cannot be empty. Empty URIs are not valid.");

    m_strOriginalString = strUri;
    this->DecomposeUri(strUri);
    this->Normalize();
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QUri& QUri::operator=(const QUri &uri)
{
    if(this != &uri)
    {
        m_strHost = uri.m_strHost;
        m_arPathSegments = uri.m_arPathSegments;
        m_strFragment = uri.m_strFragment;
        m_strQuery = uri.m_strQuery;
        m_strScheme = uri.m_strScheme;
        m_strUserInfo = uri.m_strUserInfo;
        m_strPort = uri.m_strPort;
        m_strOriginalString = uri.m_strOriginalString;
        m_definedComponents = uri.m_definedComponents;
    }

    return *this;
}

QUri& QUri::operator=(const string_q &strUri)
{
    QE_ASSERT_ERROR(!strUri.IsEmpty(), "The input string cannot be empty. Empty URIs are not valid.");

    // The URI is reset to default values
    m_strHost = string_q::GetEmpty();
    m_arPathSegments.Clear();
    m_strFragment = string_q::GetEmpty();
    m_strQuery = string_q::GetEmpty();
    m_strScheme = string_q::GetEmpty();
    m_strUserInfo = string_q::GetEmpty();
    m_strPort = string_q::GetEmpty();;
    m_strOriginalString = string_q::GetEmpty();
    m_definedComponents = 0;

    // Creates the new URI
    m_strOriginalString = strUri;
    this->DecomposeUri(strUri);
    this->Normalize();
    return *this;
}

bool QUri::operator==(const QUri &uri) const
{
    return m_strHost == uri.m_strHost                     &&
           m_arPathSegments == uri.m_arPathSegments       &&
           m_strFragment == uri.m_strFragment             &&
           m_strQuery == uri.m_strQuery                   &&
           m_strScheme == uri.m_strScheme                 &&
           m_strUserInfo == uri.m_strUserInfo             &&
           m_strPort == uri.m_strPort                     &&
           m_definedComponents == uri.m_definedComponents;
}

bool QUri::operator!=(const QUri &uri) const
{
    return m_strHost != uri.m_strHost                     ||
           m_arPathSegments != uri.m_arPathSegments       ||
           m_strFragment != uri.m_strFragment             ||
           m_strQuery != uri.m_strQuery                   ||
           m_strScheme != uri.m_strScheme                 ||
           m_strUserInfo != uri.m_strUserInfo             ||
           m_strPort != uri.m_strPort                     ||
           m_definedComponents != uri.m_definedComponents;
}

void QUri::Resolve(const QUri &relativeUri)
{
    QE_ASSERT_ERROR(relativeUri.IsRelative(), "The input URI must be relative.");
    QE_ASSERT_ERROR(!this->IsRelative(), "The URI must be absolute to serve as a base URI.");

    // This class considers as a relative URI anyone that has no scheme. Therefore, the scheme is not checked but ignored.

    if(QUri::FLAG_AUTHORITY_IS_DEFINED & relativeUri.m_definedComponents)
    {
        m_strHost     = relativeUri.m_strHost;
        m_strPort     = relativeUri.m_strPort;
        m_strUserInfo = relativeUri.m_strUserInfo;
        m_strQuery    = relativeUri.m_strQuery;
        m_arPathSegments    = relativeUri.m_arPathSegments;
        m_definedComponents = relativeUri.m_definedComponents | QUri::FLAG_SCHEME_IS_DEFINED; // The relative URI does not have scheme
    }
    else
    {
        if(relativeUri.GetPath().IsEmpty())
        {
            // Uses the base path

            if(QUri::FLAG_QUERY_IS_DEFINED & relativeUri.m_definedComponents)
            {
                m_strQuery = relativeUri.m_strQuery;
                m_definedComponents |= QUri::FLAG_QUERY_IS_DEFINED;
            }
            // If not, it uses the base query
        }
        else
        {
            // If the relative URI starts with a slash ("/")
            if(relativeUri.m_arPathSegments[0].IsEmpty() && relativeUri.m_arPathSegments.GetCount() > 1U)
            {
                m_arPathSegments = relativeUri.m_arPathSegments;
            }
            else
            {
                // Merges the paths

                // The last segment will be replaced with the first segment of the relative URI
                m_arPathSegments.Remove(m_arPathSegments.GetCount() - 1U); 

                for(QDynamicArray<string_q>::QArrayIterator itRelativeSegment = relativeUri.m_arPathSegments.GetFirst(); !itRelativeSegment.IsEnd(); ++itRelativeSegment)
                    m_arPathSegments.Add(*itRelativeSegment);

                QUri::RemoveDotSegments(m_arPathSegments);

            }
            
            // Removes the starting dot segments
            QUri::RemoveFirstDotSegments(m_arPathSegments);

            // Uses the query of the relative URI or none
            if(QUri::FLAG_QUERY_IS_DEFINED & relativeUri.m_definedComponents)
            {
                m_strQuery = relativeUri.m_strQuery;
                m_definedComponents |= QUri::FLAG_QUERY_IS_DEFINED;
            }
            else
            {
                m_strQuery = string_q::GetEmpty();
                m_definedComponents &= ~QUri::FLAG_QUERY_IS_DEFINED;
            }
        }

        // Uses the base authority
    }

    // Uses the base scheme
    
    // Uses the fragment of the relative URI or none
    if(QUri::FLAG_FRAGMENT_IS_DEFINED & relativeUri.m_definedComponents)
    {
        m_strFragment = relativeUri.m_strFragment;
        m_definedComponents |= QUri::FLAG_FRAGMENT_IS_DEFINED;
    }
    else
    {
        m_strFragment = string_q::GetEmpty();
        m_definedComponents &= ~QUri::FLAG_FRAGMENT_IS_DEFINED;
    }

    // The original string is reset
    m_strOriginalString = string_q::GetEmpty();
}

string_q QUri::ToString() const
{
    string_q strUri;

    if(QUri::FLAG_SCHEME_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(m_strScheme);
        strUri.Append(QUri::CHAR_COLON);
    }

    if(QUri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(QUri::DOUBLE_SLASH);

        if(QUri::FLAG_USERINFO_IS_DEFINED & m_definedComponents)
        {
            strUri.Append(m_strUserInfo);
            strUri.Append(QUri::CHAR_AT_SIGN);
        }

        if(QUri::FLAG_HOST_IS_DEFINED & m_definedComponents)
        {
            strUri.Append(m_strHost);
        }

        if(QUri::FLAG_PORT_IS_DEFINED & m_definedComponents)
        {
            strUri.Append(QUri::CHAR_COLON);
            strUri.Append(m_strPort);
        }
    }

    strUri.Append(this->GetPath());
    
    if(QUri::FLAG_QUERY_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(QUri::CHAR_QUESTION_MARK);
        strUri.Append(m_strQuery);
    }

    if(QUri::FLAG_FRAGMENT_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(QUri::CHAR_NUMBER_SIGN);
        strUri.Append(m_strFragment);
    }

    return strUri;
}

void QUri::EncodePathSegment(const string_q &strInput, string_q &strOutput)
{
    static const bool IS_PATH_SEGMENT = true;
    QUri::Encode(IS_PATH_SEGMENT, strInput, strOutput);
}

void QUri::EncodeQueryOrFragment(const string_q &strInput, string_q &strOutput)
{
    static const bool IS_NOT_PATH_SEGMENT = false;
    QUri::Encode(IS_NOT_PATH_SEGMENT, strInput, strOutput);
}

void QUri::Encode(const bool bIsPathSegment, const string_q &strInput, string_q &strOutput)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;
    using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;

    if(!strInput.IsEmpty())
    {
        string_q strResult;

        unsigned int uUTF8CodeunitsCount = 0;
        u8_q* arUTF8Codeunits = null_q;
        string_q strHexadecimal;

        string_q::QConstCharIterator it = strInput.GetConstCharIterator(0);

        for(; !it.IsEnd(); ++it)
        {
            char_q currentChar = it.GetChar();

            // Checks if the character must be encoded or not
            if(QUri::IsEncodable(currentChar, bIsPathSegment))
            {
                // Encodes the character in UTF8
                string_q strCurrentCharacter(currentChar);
                arUTF8Codeunits = rcast_q(strCurrentCharacter.ToBytes(EQTextEncoding::E_UTF8, uUTF8CodeunitsCount), u8_q*);

                // Adds the code units as hexadecimal values
                for(unsigned int iCodeunit = 0; iCodeunit < uUTF8CodeunitsCount - 1U; ++iCodeunit) // -1U to skip the null terminator
                {
                    // Adds the '%'
                    strResult.Append(QUri::CHAR_PERCENT_SIGN);

                    strHexadecimal = SQInteger::ToStringHexadecimal(arUTF8Codeunits[iCodeunit]);
                    strResult.Append(strHexadecimal);
                }

                delete[] arUTF8Codeunits;
                arUTF8Codeunits = null_q;
            }
            else
            {
                strResult.Append(currentChar);
            }
        }

        strOutput = strResult;
    }
    else
    {
        strOutput = strInput;
    }
}

void QUri::Decode(const string_q &strInput, string_q &strOutput)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;

    static unsigned int PERCENT_ENCODED_LENGTH = 3U; // "%FF"
    
    if(strInput.GetLength() >= PERCENT_ENCODED_LENGTH && strInput.Contains(QUri::CHAR_PERCENT_SIGN, EQComparisonType::E_BinaryCaseSensitive))
    {
        string_q strResult;

        unsigned int uLastPercentPosition = 0;
        unsigned int uCurrentPercentPosition = 0;

        u8_q* arCodeUnits = new u8_q[strInput.GetLength() / PERCENT_ENCODED_LENGTH];
        u8_q uCurrentCodeUnit = 0;
        bool bPendingCharacters = false;

        // Searches for every percent sign ("%")
        while( (uCurrentPercentPosition = strInput.IndexOf(QUri::CHAR_PERCENT_SIGN, EQComparisonType::E_BinaryCaseSensitive, uLastPercentPosition)) 
               != string_q::PATTERN_NOT_FOUND)
        {
            // Percent-encoded values represent code units of UTF8 characters, 
            // so it is necessary to know where does the sequence starts at and how long it is
            // The sequence is interrupted when the next percent-encoded value is not contiguous to the last one
            if(uCurrentPercentPosition != 0)
            {
                if(uCurrentPercentPosition == uLastPercentPosition)
                {
                    // Next code unit in the sequence
                    ++uCurrentCodeUnit;
                }
                else
                {
                    if(bPendingCharacters)
                    {
                        // Adds the characters without encoding
                        strResult.Append( string_q(rcast_q(arCodeUnits, i8_q*), uCurrentCodeUnit + 1U, EQTextEncoding::E_UTF8) );
                        bPendingCharacters = false;
                    }

                    // Resets the sequence length counter
                    uCurrentCodeUnit = 0;

                    // Adds all the text between the current percent sign and the last percen-encoded value
                    strResult.Append( strInput.Substring(uLastPercentPosition, uCurrentPercentPosition - 1U) );
                }
            }

            // Gets the UTF8 code unit from the percent-encoded value
            QUri::CreateIntegerFromHexadecimalString(strInput.Substring(uCurrentPercentPosition + QUri::CHAR_PERCENT_SIGN.GetLength(), 
                                                                        uCurrentPercentPosition + PERCENT_ENCODED_LENGTH - 1U), 
                                                     arCodeUnits[uCurrentCodeUnit]);

            bPendingCharacters = true;

            // Gets the position after the current percent-encoded value in the string
            uLastPercentPosition = uCurrentPercentPosition + PERCENT_ENCODED_LENGTH;
        }

        // Adds the last decoded UTF8 characters without encoding
        if(bPendingCharacters)
            strResult.Append( string_q(rcast_q(arCodeUnits, i8_q*), uCurrentCodeUnit + 1U, EQTextEncoding::E_UTF8) );

        delete[] arCodeUnits;

        // If there is text left after the last percent-encoded value found, adds it to the result
        if(uLastPercentPosition != strInput.GetLength() - PERCENT_ENCODED_LENGTH - 1U)
            strResult.Append( strInput.Substring(uLastPercentPosition) );

        // If there were not any separator in the path, just sets the whole input string
        if(strResult.IsEmpty() && !strInput.IsEmpty())
            strOutput = strInput;
        else
            strOutput = strResult;
    }
    else
    {
        strOutput = strInput;
    }
}

void QUri::DecomposeUri(const string_q &strInputUri)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    int nSchemeEndPosition      = strInputUri.IndexOf(QUri::CHAR_COLON, EQComparisonType::E_BinaryCaseSensitive);
    int nAuthorityStartPosition = strInputUri.IndexOf(QUri::DOUBLE_SLASH, EQComparisonType::E_BinaryCaseSensitive);
    int nQueryStartPosition     = strInputUri.IndexOf(QUri::CHAR_QUESTION_MARK, EQComparisonType::E_BinaryCaseSensitive);
    int nFragmentStartPosition  = strInputUri.IndexOf(QUri::CHAR_NUMBER_SIGN, EQComparisonType::E_BinaryCaseSensitive);
    int nPathStartPosition      = string_q::PATTERN_NOT_FOUND;

    // Gets the scheme
    // If there is a scheme termination (":") and it's placed before the authority separator ("//") and the path separator ("/")
    if(nSchemeEndPosition != string_q::PATTERN_NOT_FOUND &&
       !((nAuthorityStartPosition != string_q::PATTERN_NOT_FOUND && nAuthorityStartPosition == 0) ||
        (nPathStartPosition != string_q::PATTERN_NOT_FOUND && nSchemeEndPosition > nPathStartPosition))
      )
    {
        m_definedComponents |= QUri::FLAG_SCHEME_IS_DEFINED;
        m_strScheme = strInputUri.Substring(0, nSchemeEndPosition - 1U);
    }

    // Decomposes the authority component
    // If it starts with a double slash ("//"), it is a relative URI reference so there is no scheme
    if(nAuthorityStartPosition != string_q::PATTERN_NOT_FOUND)
    {
        m_definedComponents |= QUri::FLAG_AUTHORITY_IS_DEFINED;
        nPathStartPosition = strInputUri.IndexOf(QUri::CHAR_SLASH, EQComparisonType::E_BinaryCaseSensitive, nAuthorityStartPosition + QUri::DOUBLE_SLASH.GetLength());

        this->DecomposeAuthority(strInputUri, nAuthorityStartPosition, nPathStartPosition, nQueryStartPosition, nFragmentStartPosition, m_definedComponents);
    }
    else if(nSchemeEndPosition != string_q::PATTERN_NOT_FOUND && 
            nSchemeEndPosition != strInputUri.GetLength() - 1U)
    {
        // The authority is not defined, the scheme is defined and is not alone
        nPathStartPosition = nSchemeEndPosition + 1U;
    }

    // Decomposes de path

    // If there is no scheme nor authority, the first part must be the first segment of the path (in a relative-path reference)
    if(!((QUri::FLAG_SCHEME_IS_DEFINED | QUri::FLAG_AUTHORITY_IS_DEFINED) & m_definedComponents))
        nPathStartPosition = 0;

    if(nQueryStartPosition != 0 && nFragmentStartPosition != 0)
        this->DecomposePath(strInputUri, nPathStartPosition, nQueryStartPosition, nFragmentStartPosition);
    
    // Gets de query
    // If there is a query separator ("?")
    if(nQueryStartPosition != string_q::PATTERN_NOT_FOUND)
    {
        m_definedComponents |= QUri::FLAG_QUERY_IS_DEFINED;

        int nQueryEndPosition = 0;

        if(nFragmentStartPosition != string_q::PATTERN_NOT_FOUND)
            nQueryEndPosition = nFragmentStartPosition - 1U;
        else
            nQueryEndPosition = strInputUri.GetLength() - 1U;

        m_strQuery = strInputUri.Substring(nQueryStartPosition + QUri::CHAR_QUESTION_MARK.GetLength(), nQueryEndPosition);
    }
    
    // Gets de fragment
    // If there is a fragment separator ("#")
    if(nFragmentStartPosition != string_q::PATTERN_NOT_FOUND)
    {
        m_definedComponents |= QUri::FLAG_FRAGMENT_IS_DEFINED;
        m_strFragment = strInputUri.Substring(nFragmentStartPosition + QUri::CHAR_NUMBER_SIGN.GetLength());
    }
}

void QUri::DecomposeAuthority(const string_q &strInputUri, 
                              const int nAuthorityStartPosition, 
                              const int nPathStartPosition, 
                              const int nQueryStartPosition, 
                              const int nFragmentStartPosition, 
                              QUri::TBitField &definedComponents)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    int nAuthorityEndPosition = 0;

    if(nPathStartPosition != string_q::PATTERN_NOT_FOUND)
        nAuthorityEndPosition = nPathStartPosition - 1U;
    else if(nQueryStartPosition != string_q::PATTERN_NOT_FOUND)
        nAuthorityEndPosition = nQueryStartPosition - 1U;
    else if(nFragmentStartPosition != string_q::PATTERN_NOT_FOUND)
        nAuthorityEndPosition = nFragmentStartPosition - 1U;
    else
        nAuthorityEndPosition = strInputUri.GetLength() - 1U;

    string_q strAuthority(strInputUri.Substring(nAuthorityStartPosition + QUri::DOUBLE_SLASH.GetLength(), nAuthorityEndPosition));

    int nUserInfoEndPosition = strAuthority.IndexOf(QUri::CHAR_AT_SIGN, EQComparisonType::E_BinaryCaseSensitive);
    int nHostStartPosition = 0;

    // If there is a user info separator ("@")
    if(nUserInfoEndPosition != string_q::PATTERN_NOT_FOUND)
    {
        // Gets the user info
        m_strUserInfo = strAuthority.Substring(0, nUserInfoEndPosition - 1U);
        definedComponents |= QUri::FLAG_USERINFO_IS_DEFINED;

        nHostStartPosition = nUserInfoEndPosition + QUri::CHAR_AT_SIGN.GetLength();
    }

    int nIPv6EndPosition = strAuthority.IndexOf(QUri::CHAR_CLOSING_SQUARE_BRACKET, EQComparisonType::E_BinaryCaseSensitive);
    int nPortStartPosition = string_q::PATTERN_NOT_FOUND;

    // Disambiguates among colons of an IPv6 sub-component and the colon that separates the port
    if(nIPv6EndPosition != string_q::PATTERN_NOT_FOUND)
    {
        nPortStartPosition = strAuthority.IndexOf(QUri::CHAR_COLON, 
                                                    EQComparisonType::E_BinaryCaseSensitive, 
                                                    nIPv6EndPosition + QUri::CHAR_CLOSING_SQUARE_BRACKET.GetLength());
    }
    else
    {
        nPortStartPosition = strAuthority.IndexOf(QUri::CHAR_COLON, EQComparisonType::E_BinaryCaseSensitive);
    }

    int nHostEndPosition = 0;

    // If there is a port separator (":")
    if(nPortStartPosition != string_q::PATTERN_NOT_FOUND)
    {
        // Gets the port
        m_strPort = strAuthority.Substring(nPortStartPosition + QUri::CHAR_COLON.GetLength());
        definedComponents |= QUri::FLAG_PORT_IS_DEFINED;

        nHostEndPosition = nPortStartPosition - 1U;
    }
    else
    {
        nHostEndPosition = strAuthority.GetLength() - 1U;
    }

    // Gets the host
    m_strHost = strAuthority.Substring(nHostStartPosition, nHostEndPosition);
    definedComponents |= QUri::FLAG_HOST_IS_DEFINED;
}

void QUri::DecomposePath(const string_q &strInputUri, 
                         const int nPathStartPosition, 
                         const int nQueryStartPosition, 
                         const int nFragmentStartPosition)
{
    // Note: When the path starts with a slash, an empty segment is added at the start; 
    //       when the path ends with a slash, an empty segment is added at the end

    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    if(nPathStartPosition != string_q::PATTERN_NOT_FOUND)
    {
        int nPathEndPosition = 0;

        if(nQueryStartPosition != string_q::PATTERN_NOT_FOUND)
            nPathEndPosition = nQueryStartPosition - 1U;
        else if(nFragmentStartPosition != string_q::PATTERN_NOT_FOUND)
            nPathEndPosition = nFragmentStartPosition - 1U;
        else
            nPathEndPosition = strInputUri.GetLength() - 1U;

        string_q strPath(strInputUri.Substring(nPathStartPosition, nPathEndPosition));

        unsigned int uSegments = 0;
        string_q* arSegments = strPath.Split(QUri::CHAR_SLASH, uSegments);

        m_arPathSegments.Clear();

        for(unsigned int i = 0; i < uSegments; ++i)
            m_arPathSegments.Add(arSegments[i]);

        delete[] arSegments;
    }
}

void QUri::RemoveDotSegments(Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray<string_q> &arPathSegments)
{
    pointer_uint_q i = 0;

    while(i < arPathSegments.GetCount())
    {
        if(arPathSegments[i] == QUri::SINGLE_DOT_SEGMENT && i > 0)
        {
            // If the dot segment appears the first, it is not removed
            // If the dot segment appears the last, it is replaced by an empty string
            if(i == arPathSegments.GetCount() - 1U)
                arPathSegments[i] = string_q::GetEmpty();
            else
                arPathSegments.Remove(i);
        }
        else if(i > 0                                            && 
                arPathSegments[i] == QUri::DOUBLE_DOT_SEGMENT    && 
                arPathSegments[i-1U] != QUri::DOUBLE_DOT_SEGMENT && 
                arPathSegments[i-1U] != QUri::SINGLE_DOT_SEGMENT && 
                !arPathSegments[i-1U].IsEmpty())
        {
            // The dot segments formed by 2 dots that appear at the beginning of relative URIs must not be removed
            // Two dot segments must not remove previous dot segments nor empty segments

            // Removes ".."
            arPathSegments.Remove(i);

            // If the previous segment is now the last one, it is replaced with an empty segment
            // If not, it is removed
            --i;
            if(i == arPathSegments.GetCount() - 1U)
                arPathSegments[i] = string_q::GetEmpty();
            else
                arPathSegments.Remove(i);
        }
        else
        {
            // It is not a dot segment, it moves next
            ++i;
        }
    }
}

void QUri::Normalize()
{
    this->NormalizeScheme();
    this->NormalizeUserInfo();
    this->NormalizeHost();
    this->NormalizePort();
    this->NormalizePath();
    this->NormalizeQuery();
    this->NormalizeFragment();
}

void QUri::NormalizeScheme()
{
    if(QUri::FLAG_SCHEME_IS_DEFINED & m_definedComponents)
        m_strScheme = m_strScheme.ToLowerCase();
}

void QUri::NormalizeUserInfo()
{
    if(QUri::FLAG_USERINFO_IS_DEFINED & m_definedComponents)
        m_strUserInfo = m_strUserInfo.ToLowerCase();
}

void QUri::NormalizeHost()
{
    if(QUri::FLAG_HOST_IS_DEFINED & m_definedComponents)
        m_strHost = m_strHost.ToLowerCase();
}

void QUri::NormalizePort()
{
    // Empty
}

void QUri::NormalizePath()
{
    if(!m_arPathSegments.IsEmpty())
    {
        QUri::RemoveDotSegments(m_arPathSegments);
        
        for(QDynamicArray<string_q>::QArrayIterator it = m_arPathSegments.GetFirst(); !it.IsEnd(); ++it)
        {
            if(!it->IsEmpty())
            {
                // First decodes the string to remove possible percent-encoded unreserved character
                QUri::Decode(*it, *it);
                // Then it encodes everything
                QUri::EncodePathSegment(*it, *it);
            }
        }
    }
}

void QUri::NormalizeQuery()
{
    if(QUri::FLAG_QUERY_IS_DEFINED & m_definedComponents)
    {
        // First decodes the string to remove possible percent-encoded unreserved character
        QUri::Decode(m_strQuery, m_strQuery);
        // Then it encodes everything
        QUri::EncodeQueryOrFragment(m_strQuery, m_strQuery);
    }
}

void QUri::NormalizeFragment()
{
    if(QUri::FLAG_FRAGMENT_IS_DEFINED & m_definedComponents)
    {
        // First decodes the string to remove possible percent-encoded unreserved character
        QUri::Decode(m_strFragment, m_strFragment);
        // Then it encodes everything
        QUri::EncodeQueryOrFragment(m_strFragment, m_strFragment);
    }
}

bool QUri::IsEncodable(const char_q &character, const bool bIsPathSegment)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;

    static const char_q CHAR_HYPHEN                          = '-';
    static const char_q CHAR_DOT                             = '.';
    static const codepoint_q CODEPOINT_FIRST_NUMBER          = '0';
    static const codepoint_q CODEPOINT_LAST_NUMBER           = '9';
    static const codepoint_q CODEPOINT_FIRST_ALPHA_UPPERCASE = 'A';
    static const codepoint_q CODEPOINT_LAST_ALPHA_UPPERCASE  = 'Z';
    static const char_q CHAR_UNDERSCORE                      = '_';
    static const codepoint_q CODEPOINT_FIRST_ALPHA_LOWERCASE = 'a';
    static const codepoint_q CODEPOINT_LAST_ALPHA_LOWERCASE  = 'z';
    static const char_q CHAR_TILDE                           = '~';

    codepoint_q codePoint = character.GetCodePoint();

    return codePoint > CHAR_TILDE.GetCodePoint()                // It's not an allowed ASCII character
           ||
           ((codePoint < CODEPOINT_FIRST_NUMBER ||
            (codePoint > CODEPOINT_LAST_NUMBER && codePoint < CODEPOINT_FIRST_ALPHA_UPPERCASE) ||
            (codePoint > CODEPOINT_LAST_ALPHA_UPPERCASE && codePoint < CODEPOINT_FIRST_ALPHA_LOWERCASE) ||
             codePoint > CODEPOINT_LAST_ALPHA_LOWERCASE)        // It's not an alpha or number chracter
           &&
           character != CHAR_UNDERSCORE                   &&    // It's not other allowed character
           character != CHAR_TILDE                        &&
           character != CHAR_DOT                          &&
           character != CHAR_HYPHEN                       &&
           character != QUri::CHAR_AT_SIGN[0]             &&
           character != QUri::CHAR_COLON[0]               &&
           (bIsPathSegment ||                                   // Allowed characters only for query and fragment
             (character != QUri::CHAR_QUESTION_MARK[0] && 
              character != QUri::CHAR_SLASH[0]))          &&
           character != QUri::CHAR_AMPERSAND[0]           &&    // It's not a sub-delim character
           character != QUri::CHAR_APOSTROPHE[0]          &&
           character != QUri::CHAR_ASTERISK[0]            &&
           character != QUri::CHAR_CLOSING_PARENTHESES[0] &&
           character != QUri::CHAR_COMMA[0]               &&
           character != QUri::CHAR_DOLLAR_SIGN[0]         &&
           character != QUri::CHAR_EQUAL_SIGN[0]          &&
           character != QUri::CHAR_EXCLAMATION_MARK[0]    &&
           character != QUri::CHAR_OPENING_PARENTHESES[0] &&
           character != QUri::CHAR_PERCENT_SIGN[0]        &&
           character != QUri::CHAR_PLUS_SIGN[0]           &&
           character != QUri::CHAR_SEMICOLON[0]);
}

void QUri::RemoveFirstDotSegments(Kinesis::QuimeraEngine::Tools::Containers::QDynamicArray<string_q> &arPathSegments)
{
    pointer_uint_q uAbsoluteSegment = 0;

    // If the first segment is empty, it must be ignored
    if(!arPathSegments.IsEmpty() && arPathSegments[0].IsEmpty())
        ++uAbsoluteSegment;

    // While the segment is a dot segment, remove it
    while(uAbsoluteSegment < arPathSegments.GetCount() && 
            (arPathSegments[uAbsoluteSegment] == QUri::DOUBLE_DOT_SEGMENT || arPathSegments[uAbsoluteSegment] == QUri::SINGLE_DOT_SEGMENT))
    {
        arPathSegments.Remove(uAbsoluteSegment);
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

string_q QUri::GetAuthority() const
{
    string_q strResult;

    if(QUri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        if(QUri::FLAG_USERINFO_IS_DEFINED & m_definedComponents)
        {
            strResult.Append(m_strUserInfo);
            strResult.Append(QUri::CHAR_AT_SIGN);
        }

        if(QUri::FLAG_HOST_IS_DEFINED & m_definedComponents)
        {
            strResult.Append(m_strHost);
        }

        if(QUri::FLAG_PORT_IS_DEFINED & m_definedComponents)
        {
            strResult.Append(QUri::CHAR_COLON);
            strResult.Append(m_strPort);
        }
    }

    return strResult;
}

string_q QUri::GetFragment() const
{
    return m_strFragment;
}

string_q QUri::GetHost() const
{
    return m_strHost;
}

string_q QUri::GetPath() const
{
    string_q strPath;

    if(!m_arPathSegments.IsEmpty())
    {
        QDynamicArray<string_q>::QArrayIterator it = m_arPathSegments.GetFirst();
        QDynamicArray<string_q>::QArrayIterator itLast = m_arPathSegments.GetLast();

        // If the authority is defined or the path begins with an empty segment, adds a slash at the beginning
        if((QUri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents) || 
           (it->IsEmpty() && m_arPathSegments.GetCount() > 1U))
        {
            strPath.Append(QUri::CHAR_SLASH);
            strPath.Append(*it);
            ++it;
        }

        for(; !it.IsEnd(); ++it)
        {
            strPath.Append(*it);

            if(it != itLast)
                strPath.Append(QUri::CHAR_SLASH);
        }
    }

    return strPath;
}

string_q QUri::GetPort() const
{
    return m_strPort;
}

string_q QUri::GetQuery() const
{
    return m_strQuery;
}

string_q QUri::GetScheme() const
{
    return m_strScheme;
}

string_q QUri::GetUserInfo() const
{
    return m_strUserInfo;
}

string_q QUri::GetOriginalString() const
{
    return m_strOriginalString;
}

QDynamicArray<string_q> QUri::GetPathSegments() const
{
    return m_arPathSegments;
}

bool QUri::IsRelative() const
{
    return !(m_definedComponents & QUri::FLAG_SCHEME_IS_DEFINED);
}

void QUri::SetAuthority(const string_q &strAuthority)
{
    if(strAuthority.IsEmpty())
    {
        m_definedComponents &= ~(QUri::FLAG_AUTHORITY_IS_DEFINED | QUri::FLAG_USERINFO_IS_DEFINED | QUri::FLAG_HOST_IS_DEFINED | QUri::FLAG_PORT_IS_DEFINED);
        m_strHost = string_q::GetEmpty();
        m_strUserInfo = string_q::GetEmpty();
        m_strPort = string_q::GetEmpty();
    }
    else
    {
        m_definedComponents |= QUri::FLAG_AUTHORITY_IS_DEFINED | QUri::FLAG_HOST_IS_DEFINED;
        this->DecomposeAuthority(QUri::DOUBLE_SLASH + strAuthority, 0, string_q::PATTERN_NOT_FOUND, string_q::PATTERN_NOT_FOUND, string_q::PATTERN_NOT_FOUND, m_definedComponents);
        this->NormalizeUserInfo();
        this->NormalizeHost();
        this->NormalizePort();

        // If the path does not start with a slash
        if(!m_arPathSegments.IsEmpty() && m_arPathSegments[0] != string_q::GetEmpty())
        {
            // Adds an empty segment at the beginning, which means adding a starting slash
            m_arPathSegments.Insert(string_q::GetEmpty(), 0);
        }
    }

    m_strOriginalString = string_q::GetEmpty();
}

void QUri::SetFragment(const string_q &strFragment)
{
    if(strFragment.IsEmpty())
    {
        m_definedComponents &= ~QUri::FLAG_FRAGMENT_IS_DEFINED;
        m_strFragment = string_q::GetEmpty();
    }
    else
    {
        m_definedComponents |= QUri::FLAG_FRAGMENT_IS_DEFINED;
        m_strFragment = strFragment;
        this->NormalizeFragment();
    }

    m_strOriginalString = string_q::GetEmpty();
}

void QUri::SetHost(const string_q &strHost)
{
    if(strHost.IsEmpty())
    {
        // The entire authority will be undefined
        this->SetAuthority(strHost);
    }
    else
    {
        // If the host was already defined, it takes the new value
        if(m_definedComponents & QUri::FLAG_HOST_IS_DEFINED)
        {
            m_strHost = strHost;
            this->NormalizeHost();
            m_strOriginalString = string_q::GetEmpty();
        }
        else
        {
            // If not, the authority is defined using the new value
            this->SetAuthority(strHost);
        }
    }
}

void QUri::SetPath(const string_q &strPath)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    string_q strAdjustedInput = strPath;

    if(strAdjustedInput.IsEmpty())
    {
        if(QUri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
            strAdjustedInput = QUri::CHAR_SLASH;
        else
            strAdjustedInput = QUri::SINGLE_DOT_SEGMENT;
    }
    else if((QUri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents) && strAdjustedInput[0] != QUri::CHAR_SLASH[0])
    {
        // The authority is defined and the input path does not start with a slash ("/"), a slash is added at the start
        strAdjustedInput = QUri::CHAR_SLASH + strAdjustedInput;
    }

    this->DecomposePath(strAdjustedInput, 0, string_q::PATTERN_NOT_FOUND, string_q::PATTERN_NOT_FOUND);
    this->NormalizePath();

    if(!this->IsRelative())
    {
        QUri::RemoveFirstDotSegments(m_arPathSegments);
    }
    else if(!m_arPathSegments.IsEmpty() && m_arPathSegments[0].Contains(QUri::CHAR_COLON, EQComparisonType::E_BinaryCaseSensitive))
    {
        // The path cannot start with a segment that contains a colon when there is no scheme
        // A starting single dot segment is added ("./")
        m_arPathSegments.Insert(QUri::SINGLE_DOT_SEGMENT, 0);
    }

    m_strOriginalString = string_q::GetEmpty();
}

void QUri::SetQuery(const string_q &strQuery)
{
    if(strQuery.IsEmpty())
    {
        m_definedComponents &= ~QUri::FLAG_QUERY_IS_DEFINED;
        m_strQuery = string_q::GetEmpty();
    }
    else
    {
        m_definedComponents |= QUri::FLAG_QUERY_IS_DEFINED;
        m_strQuery = strQuery;
        this->NormalizeQuery();
    }

    m_strOriginalString = string_q::GetEmpty();
}

void QUri::SetPort(const string_q &strPort)
{
    if(QUri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        if(strPort.IsEmpty())
        {
            m_definedComponents &= ~QUri::FLAG_PORT_IS_DEFINED;
            m_strPort = string_q::GetEmpty();
        }
        else
        {
            m_definedComponents |= QUri::FLAG_PORT_IS_DEFINED;
            m_strPort = strPort;
            this->NormalizePort();
        }

        m_strOriginalString = string_q::GetEmpty();
    }
}

void QUri::SetScheme(const string_q &strScheme)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    if(strScheme.IsEmpty())
    {
        m_definedComponents &= ~QUri::FLAG_SCHEME_IS_DEFINED;
        m_strScheme = string_q::GetEmpty();

        // The path cannot start with a segment that contains a colon when there is no scheme
        if(!m_arPathSegments.IsEmpty() && m_arPathSegments[0].Contains(QUri::CHAR_COLON, EQComparisonType::E_BinaryCaseSensitive))
        {
            // A starting single dot segment is added ("./")
            m_arPathSegments.Insert(QUri::SINGLE_DOT_SEGMENT, 0);
        }
    }
    else
    {
        m_definedComponents |= QUri::FLAG_SCHEME_IS_DEFINED;
        m_strScheme = strScheme;
        this->NormalizeScheme();

        // The path may need to be adjusted if it begins with dot segments
        QUri::RemoveFirstDotSegments(m_arPathSegments);
    }

    m_strOriginalString = string_q::GetEmpty();
}

void QUri::SetUserInfo(const string_q &strUserInfo)
{
    if(QUri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        if(strUserInfo.IsEmpty())
        {
            m_definedComponents &= ~QUri::FLAG_USERINFO_IS_DEFINED;
            m_strUserInfo = string_q::GetEmpty();
        }
        else
        {
            m_definedComponents |= QUri::FLAG_USERINFO_IS_DEFINED;
            m_strUserInfo = strUserInfo;
            this->NormalizeUserInfo();
        }

        m_strOriginalString = string_q::GetEmpty();
    }
}

} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
