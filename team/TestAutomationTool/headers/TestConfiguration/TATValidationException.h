//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __TATVALIDATIONEXCEPTION__
#define __TATVALIDATIONEXCEPTION__

#include <wx/string.h>
#include <exception>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// This exception is intended to be thrown when the validation of a node fails.
/// </summary>
class TATValidationException : public std::exception
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    TATValidationException()
    {
    }
    
    /// <summary>
    /// Constructor that receives the error code and the node name.
    /// </summary>
    /// <param name="strErrorCode">An error code.</param>
    /// <param name="strNodeName">The name of the node which validation failed.</param>
    TATValidationException(const wxString& strErrorCode, const wxString& strNodeName) : m_strNodeName(strNodeName),
                                                                                        m_strErrorCode(strErrorCode)
    {
    }


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATValidationException() throw()
    {
    }


	// METHODS
	// ---------------
public:


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the node of the name whose validation failed.
    /// </summary>
    /// <returns>
    /// The name of the node.
    /// </returns>
    const wxString& GetNodeName() const
    {
       return m_strNodeName;
    }

    /// <summary>
    /// Gets the error code.
    /// </summary>
    /// <returns>
    /// The error code.
    /// </returns>
    /// <exception cref="throw"></exception>
    virtual const char* what() const throw()
    {
        return m_strErrorCode.ToUTF8().data();
    }


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The name of the node.
    /// </summary>
    wxString m_strNodeName;

    /// <summary>
    /// The error code.
    /// </summary>
    wxString m_strErrorCode;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATVALIDATIONEXCEPTION__
