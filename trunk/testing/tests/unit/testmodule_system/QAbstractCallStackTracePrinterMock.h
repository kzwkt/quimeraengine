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

#ifndef __QABSTRACTCALLSTACKTRACEPRINTERMOCK__
#define __QABSTRACTCALLSTACKTRACEPRINTERMOCK__

#include "QAbstractCallStackTracePrinter.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{
namespace Test
{

/// <summary>
/// Sends the printed text to a string so it can be compared in unit tests.
/// </summary>
class QAbstractCallStackTracePrinterMock : public QAbstractCallStackTracePrinter
{

    QE_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(QAbstractCallStackTracePrinterMock, QAbstractCallStackTracePrinter);


    // CONSTRUCTORS
	// ---------------
public:

    QAbstractCallStackTracePrinterMock()
    {
    }


    // METHODS
	// ---------------
public:

    // Implementation that prints the text to a string
    void PrintString(const string_q &strText)
    {
        m_strPrintedText.Append(strText);
    }

    string_q GetPrintedText() const
    {
        return m_strPrintedText;
    }

    string_q ToString() const
    {
        return "";
    }


    // ATTRIBUTES
	// ---------------
private:

    string_q m_strPrintedText;
};

QE_RTTI_SUPPORT_TYPE_DEFINITION(QAbstractCallStackTracePrinterMock);

} //namespace Test
} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis


#endif // __QABSTRACTCALLSTACKTRACEPRINTERMOCK__
