// [TERMS&CONDITIONS]

#ifndef __TATTESTAUTOMATIONTOOLEXECUTION__
#define __TATTESTAUTOMATIONTOOLEXECUTION__



namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Manages the business logic of a functional sector of the application in a UI-independent way.
/// Provides functionality related to the execution of the tests.
/// </summary>
class  TATTestAutomationToolExecution
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATTestAutomationToolExecution();


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATTestAutomationToolExecution();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Releases all the resources.
    /// </summary>
    void Destroy();


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:


};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATTESTAUTOMATIONTOOLEXECUTION__
