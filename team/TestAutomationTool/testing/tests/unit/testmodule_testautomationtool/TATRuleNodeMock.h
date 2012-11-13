// [TERMS&CONDITIONS]

#ifndef __TATRULENODMOCK__
#define __TATRULENODMOCK__

#include "TestConfiguration/TATRuleNode.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// A mock derived from TATRuleNode for testing purposes.
/// </summary>
class TATRuleNodeMock : public TATRuleNode
{
	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATRuleNodeMock()
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
int TATRuleNodeMock::sm_nDestructorCallCounter = 0;


} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATRULENODMOCK__