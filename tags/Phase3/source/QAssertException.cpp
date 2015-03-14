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

#include "QAssertException.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace Exceptions
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QAssertException::QAssertException(const string_q &strCondition, const string_q &strMessage, const int nLineNumber, const string_q &strFileName) :
                                                                                                m_strCondition(strCondition),
                                                                                                m_strMessage(strMessage),
                                                                                                m_nLineNumber(nLineNumber),
                                                                                                m_strFileName(strFileName)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

string_q QAssertException::GetCondition() const
{
    return m_strCondition;
}

string_q QAssertException::GetMessage() const
{
    return m_strMessage;
}

int QAssertException::GetLineNumber() const
{
    return m_nLineNumber;
}

string_q QAssertException::GetFileName() const
{
    return m_strFileName;
}

} //namespace Exceptions
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
