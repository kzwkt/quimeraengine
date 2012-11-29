// [TERMS&CONDITIONS]

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
    TATValidationException(const wxString& strErrorCode, const wxString& strNodeName) : m_strNodeName(strNodeName)
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
