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

#include "QStringUnicode.h"

#include <cstring> // Needed for strlen function
#include "Assertions.h"

#include "unicode/ucnv.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const int QStringUnicode::LENGTH_NULL_TERMINATED = -1;
const QCharUnicode QStringUnicode::CHAR_BOM_LE(0xFFFE);
const QCharUnicode QStringUnicode::CHAR_BOM_BE(0xFEFF);


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QStringUnicode::QStringUnicode() : m_strString()
{
}

QStringUnicode::QStringUnicode(const QStringUnicode &strString)
{
    m_strString = strString.m_strString;
}

QStringUnicode::QStringUnicode(const i8_q* arBytes,
                               const int nLength,
                               const EQTextEncoding eEncoding)
{
    // Only ASCII and ISO 8859-1 encodings can be used along with null-terminated strings' length calculation
    QE_ASSERT(((eEncoding == EQTextEncoding::E_ASCII || eEncoding == EQTextEncoding::E_ISO88591) &&
              nLength == QStringUnicode::LENGTH_NULL_TERMINATED) ||
              nLength != QStringUnicode::LENGTH_NULL_TERMINATED, "Only ASCII and ISO 8859-1 encodings can be used along with null-terminated strings' length calculation");

    UErrorCode errorCode = U_ZERO_ERROR;
    UConverter* pConverter = QStringUnicode::GetConverter(eEncoding);

    int nActualLength = nLength;

    if(nLength == QStringUnicode::LENGTH_NULL_TERMINATED &&
       (eEncoding == EQTextEncoding::E_ASCII || eEncoding == EQTextEncoding::E_ISO88591))
        nActualLength = strlen(arBytes);

    m_strString = icu::UnicodeString(arBytes, nActualLength, pConverter, errorCode);
}

QStringUnicode::QStringUnicode(const QCharUnicode &character) : m_strString(UChar(character.GetCodePoint()))
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QStringUnicode& QStringUnicode::operator=(const QStringUnicode &strString)
{
    // [TODO] Thund: Currently, this operator will invalidate any interator that may be pointing to the string.
    //               In the future we should look for a solution, if there is any.
    m_strString = strString.m_strString;
    return *this;
}

bool QStringUnicode::operator==(const QStringUnicode &strString) const
{
    return (m_strString == strString.m_strString) != FALSE;
}

bool QStringUnicode::operator!=(const QStringUnicode &strString) const
{
    return (m_strString != strString.m_strString) != FALSE;
}

QStringUnicode QStringUnicode::operator+(const QStringUnicode &strString) const
{
    QStringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    strNewString.m_strString += strString.m_strString;
    return strNewString;
}

QCharUnicode QStringUnicode::operator[](const unsigned int uIndex) const
{
    // It is not possible to retrieve any character if the string is empty
    QE_ASSERT(!this->IsEmpty(), "It is not possible to retrieve any character if the string is empty");

    // Index out of bounds: The index must be lower than the length of the string
    QE_ASSERT(!this->IsEmpty() && uIndex < this->GetLength(), "Index out of bounds: The index must be lower than the length of the string");

    QCharUnicode charUnicode = m_strString.char32At(uIndex);
    return charUnicode;
}

QStringUnicode QStringUnicode::Substring(const unsigned int uStartPosition, const unsigned int uLastPosition) const
{
    // The start position index must be lower or equal than the last position index
    QE_ASSERT(uStartPosition <= uLastPosition, "The start position index must be lower or equal than the last position index");

    QStringUnicode strResult;
    m_strString.extract(uStartPosition, uLastPosition - uStartPosition, strResult.m_strString);

    return strResult;
}

QStringUnicode::QConstCharIterator QStringUnicode::GetConstCharIterator() const
{
    return QStringUnicode::QConstCharIterator(*this);
}

i8_q* QStringUnicode::ToBytes(const EQTextEncoding eEncoding, unsigned int &uOutputLength) const
{
    i8_q* pOutputBytes = null_q;
    uOutputLength = 0;

    const unsigned int CHARACTERS_COUNT = m_strString.countChar32(); // It does not include the final null character

    if(CHARACTERS_COUNT > 0)
    {
        UErrorCode errorCode = U_ZERO_ERROR;
        UConverter* pConverter = QStringUnicode::GetConverter(eEncoding);
        const unsigned int CODE_UNITS_COUNT = m_strString.length(); // It does not include the final null character

        // Depending on whether the string is already null-terminated or not, a null terminator will be added at the end
        // of the resultant array of bytes
        const unsigned int ADD_NULL_TERMINATION = m_strString.char32At(CHARACTERS_COUNT - 1) == 0 ? 0 : 1;

        // By default, it is assigned as if it was to be encoded in ASCII or ISO 8859-1 (8-bits per character)
        int32_t nRequiredLengthBytes = CHARACTERS_COUNT + ADD_NULL_TERMINATION;

        // Output size calculation for Unicode encoding forms
        switch(eEncoding)
        {
        case EQTextEncoding::E_UTF8:
            // It is not possible to know in advance how much memory the UTF-8 will require
            // (each character could be represented by 1, 2, 3 or 4 8-bits code units) so we reserve the maximum it would need
            nRequiredLengthBytes = sizeof(i32_q) * (CHARACTERS_COUNT + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF16:
            // We already know the number of 16 bits code units. A BOM character is added at the beginning
            nRequiredLengthBytes = sizeof(i16_q) * (CODE_UNITS_COUNT + 1 + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF16BE:
        case EQTextEncoding::E_UTF16LE:
            // We already know the number of 16 bits code units
            nRequiredLengthBytes = sizeof(i16_q) * (CODE_UNITS_COUNT + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF32:
            // The width of UTF32 characters is always 32 bits. A BOM character is added at the beginning
            nRequiredLengthBytes = sizeof(i32_q) * (CHARACTERS_COUNT + 1 + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF32BE:
        case EQTextEncoding::E_UTF32LE:
            // The width of UTF32 characters is always 32 bits
            nRequiredLengthBytes = sizeof(i32_q) * (CHARACTERS_COUNT + ADD_NULL_TERMINATION);
            break;
        }

        // Conversion from native encoding (UTF16) to input encoding
        const UChar* pBuffer = m_strString.getBuffer();
        pOutputBytes = new char[nRequiredLengthBytes];
        ucnv_reset(pConverter);
        uOutputLength = ucnv_fromUChars(pConverter, pOutputBytes, nRequiredLengthBytes, pBuffer, CODE_UNITS_COUNT, &errorCode);

        // If it was necessary to add a null terminator...
        if(ADD_NULL_TERMINATION == 1)
        {
            // The last character has to be set to zero (ICU adds only 1 byte at the end as the null terminator)
            // The last character has to be added to the output length
            switch(eEncoding)
            {
            case EQTextEncoding::E_ASCII:
            case EQTextEncoding::E_ISO88591:
            case EQTextEncoding::E_UTF8:
                // 8 bits character
                uOutputLength += sizeof(i8_q);
                memset(&pOutputBytes[uOutputLength - sizeof(i8_q)], 0, sizeof(i8_q));
                break;
            case EQTextEncoding::E_UTF16:
            case EQTextEncoding::E_UTF16BE:
            case EQTextEncoding::E_UTF16LE:
                // 16 bits character
                uOutputLength += sizeof(i16_q);
                memset(&pOutputBytes[uOutputLength - sizeof(i16_q)], 0, sizeof(i16_q));
                break;
            case EQTextEncoding::E_UTF32:
            case EQTextEncoding::E_UTF32BE:
            case EQTextEncoding::E_UTF32LE:
                // 32 bits character
                uOutputLength += sizeof(i32_q);
                memset(&pOutputBytes[uOutputLength - sizeof(i32_q)], 0, sizeof(i32_q));
                break;
            }
        }
    }

    return pOutputBytes;
}

UConverter* QStringUnicode::GetConverter(const EQTextEncoding eEncoding)
{
    static UErrorCode errorCode = U_ZERO_ERROR;
    static UConverter* const ASCII_CONVERTER    = ucnv_open("US-ASCII",    &errorCode);
    static UConverter* const ISO88591_CONVERTER = ucnv_open("ISO-8859-1",  &errorCode);
    static UConverter* const UTF8_CONVERTER     = ucnv_open("UTF8",        &errorCode);
    static UConverter* const UTF16_CONVERTER    = ucnv_open("UTF16",       &errorCode);
    static UConverter* const UTF32_CONVERTER    = ucnv_open("UTF32",       &errorCode);
    static UConverter* const UTF16BE_CONVERTER  = ucnv_open("UTF16BE",     &errorCode);
    static UConverter* const UTF16LE_CONVERTER  = ucnv_open("UTF16LE",     &errorCode);
    static UConverter* const UTF32BE_CONVERTER  = ucnv_open("UTF32BE",     &errorCode);
    static UConverter* const UTF32LE_CONVERTER  = ucnv_open("UTF32LE",     &errorCode);

    UConverter* pConverter = null_q;

    switch(eEncoding)
    {
    case EQTextEncoding::E_ASCII:
        pConverter = ASCII_CONVERTER;
        break;
    case EQTextEncoding::E_ISO88591:
        pConverter = ISO88591_CONVERTER;
        break;
    case EQTextEncoding::E_UTF8:
        pConverter = UTF8_CONVERTER;
        break;
    case EQTextEncoding::E_UTF16:
        pConverter = UTF16_CONVERTER;
        break;
    case EQTextEncoding::E_UTF32:
        pConverter = UTF32_CONVERTER;
        break;
    case EQTextEncoding::E_UTF16BE:
        pConverter = UTF16BE_CONVERTER;
        break;
    case EQTextEncoding::E_UTF16LE:
        pConverter = UTF16LE_CONVERTER;
        break;
    case EQTextEncoding::E_UTF32BE:
        pConverter = UTF32BE_CONVERTER;
        break;
    case EQTextEncoding::E_UTF32LE:
        pConverter = UTF32LE_CONVERTER;
        break;
    }

    return pConverter;
}

void QStringUnicode::Normalize(const EQNormalizationForm &eNormalizationForm)
{
    const icu::Normalizer2* pNormalizer = QStringUnicode::GetNormalilzer(eNormalizationForm);
    UErrorCode eErrorCode = U_ZERO_ERROR;
    
    UBool bIsNormalized = pNormalizer->isNormalized(m_strString, eErrorCode); // [TODO] Thund: Change this by a call to this->IsNormalized when implemented

    QE_ASSERT(U_SUCCESS(eErrorCode), "An error occurred when checking if the string was normalized"); // And this also.

    if(!bIsNormalized && U_SUCCESS(eErrorCode) != FALSE)
    {
        icu::UnicodeString strNormalized;
        pNormalizer->normalize(m_strString, strNormalized, eErrorCode);

        QE_ASSERT(U_SUCCESS(eErrorCode), "An error occurred when normalizing the string");

        if(U_SUCCESS(eErrorCode) != FALSE)
            m_strString = strNormalized;
    }
}

const icu::Normalizer2* QStringUnicode::GetNormalilzer(const EQNormalizationForm &eNormalizationForm)
{
    const icu::Normalizer2* pNormalizer = null_q;
    UErrorCode eErrorCode = U_ZERO_ERROR;

    switch(eNormalizationForm)
    {
    case EQNormalizationForm::E_C:
        pNormalizer = icu::Normalizer2::getNFCInstance(eErrorCode);
        break;
    case EQNormalizationForm::E_D:
        pNormalizer = icu::Normalizer2::getNFDInstance(eErrorCode);
        break;
    case EQNormalizationForm::E_KC:
    case EQNormalizationForm::E_KD:
        QE_ASSERT(false, "Normalization forms KC and KD are not supported currently");
        break;
    }

    QE_ASSERT(!U_FAILURE(eErrorCode), "An error ocurred when attempting to get a normalizer");

    return pNormalizer;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

unsigned int QStringUnicode::GetLength() const
{
    return scast_q(m_strString.countChar32(), unsigned int);
}

bool QStringUnicode::IsEmpty() const
{
    return m_strString.isEmpty() != FALSE;
}

const QStringUnicode& QStringUnicode::GetEmpty()
{
    static const QStringUnicode EMPTY_STRING;
    return EMPTY_STRING;
}


} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
