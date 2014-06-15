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

#ifndef __CALLCOUNTER__
#define __CALLCOUNTER__


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools    
{
namespace Containers
{
namespace Test
{

/// <summary>
/// Counts the number of calls to 4 methods: default constructor, copy constructor, destructor and assignment operator.
/// It should be Reset before it is used to assure a clean test scenario.
/// </summary>
class CallCounter
{
	// CONSTRUCTORS
	// ---------------

public:

    CallCounter()
    {
        CallCounter::sm_uConstructorCalls++;
    }

    CallCounter(const CallCounter&)
    {
        CallCounter::sm_uCopyConstructorCalls++;
    }
	
	// DESTRUCTOR
	// ---------------

public:

    ~CallCounter()
    {
        CallCounter::sm_uDestructorCalls++;
    }


	// METHODS
	// ---------------

public:

    CallCounter& operator=(const CallCounter&)
    {
        CallCounter::sm_uAssignmentCalls++;
        return *this;
    }

    static void ResetCounters()
    {
        CallCounter::sm_uConstructorCalls = 0;
        CallCounter::sm_uDestructorCalls = 0;
        CallCounter::sm_uCopyConstructorCalls = 0;
        CallCounter::sm_uAssignmentCalls = 0;
    }


    // PROPERTIES
	// ---------------

public:

    static unsigned int GetConstructorCallsCount()
    {
        return CallCounter::sm_uConstructorCalls;
    }

    static unsigned int GetCopyConstructorCallsCount()
    {
        return CallCounter::sm_uCopyConstructorCalls;
    }

    static unsigned int GetDestructorCallsCount()
    {
        return CallCounter::sm_uDestructorCalls;
    }

    static unsigned int GetAssignmentCallsCount()
    {
        return CallCounter::sm_uAssignmentCalls;
    }
    
    // ATTRIBUTES
	// ---------------

private:

    static unsigned int sm_uConstructorCalls;
    static unsigned int sm_uCopyConstructorCalls;
    static unsigned int sm_uDestructorCalls;
    static unsigned int sm_uAssignmentCalls;

};

    
// ATTRIBUTES INITIALIZATION
// -----------------------------
unsigned int CallCounter::sm_uConstructorCalls = 0;
unsigned int CallCounter::sm_uDestructorCalls = 0;
unsigned int CallCounter::sm_uCopyConstructorCalls = 0;
unsigned int CallCounter::sm_uAssignmentCalls = 0;


} //namespace Test
} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __CALLCOUNTER__
