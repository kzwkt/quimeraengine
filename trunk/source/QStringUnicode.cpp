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

#include "Assertions.h"


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



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QStringUnicode::QStringUnicode() : m_strString("") // [TODO] Thund: Replace "" with Empty() when it exists
{

}

QStringUnicode::QStringUnicode(const QStringUnicode &strString)
{
    m_strString = strString.m_strString;
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

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
