// [TERMS&CONDITIONS]

#ifndef __TATNODEMOCK__
#define __TATNODEMOCK__

#include "TATNode.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// A mock derived from TATNode for testing purposes.
/// </summary>
class TATNodeMock : public TATNode
{
	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATNodeMock()
    {
        sm_nDestructorCallCounter++;
    }
    

	// ATTRIBUTES
	// ---------------
public:

    /// <summary>
	/// Counter used for testing purposes, to know when destructor is called.
	/// </summary>	
    static int sm_nDestructorCallCounter;
    
};


// Static attributes initialization
int TATNodeMock::sm_nDestructorCallCounter = 0;


} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATNODEMOCK__
