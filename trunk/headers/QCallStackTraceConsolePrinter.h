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

#ifndef __QCALLSTACKTRACECONSOLEPRINTER__
#define __QCALLSTACKTRACECONSOLEPRINTER__

#include "SystemDefinitions.h"

#include "QAbstractCallStackTracePrinter.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

/// <summary>
/// A call stack trace printer implementation that sends text to a console.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QCallStackTraceConsolePrinter : public QAbstractCallStackTracePrinter
{
    QE_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(QCallStackTraceConsolePrinter, QAbstractCallStackTracePrinter);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A trace formatter.</param>
    QCallStackTraceConsolePrinter(IQCallStackTraceFormatter* pFormatter);
    
    /// <summary>
    /// Constructor that receives a formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A trace formatter.</param>
    QCallStackTraceConsolePrinter(boost::shared_ptr<IQCallStackTraceFormatter> &pFormatter);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~QCallStackTraceConsolePrinter();


    // METHODS
    // ---------------
public:

    /// @copydoc QAbstractCallStackTracePrinter::PrintString
    virtual void PrintString(const string_q &strText);

    /// @copydoc QAbstractCallStackTracePrinter::ToString
    virtual string_q ToString() const;

};

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCALLSTACKTRACECONSOLEPRINTER__
