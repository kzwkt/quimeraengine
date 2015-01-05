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

#ifndef __QFILESTREAMWHITEBOX__
#define __QFILESTREAMWHITEBOX__

#include "QFileStream.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System    
{
namespace IO
{
namespace FileSystem
{
namespace Test
{

/// <summary>
/// Class to be used in QFileStream tests to manipulate internal members.
/// </summary>
class QFileStreamWhiteBox : public QFileStream
{
	// CONSTRUCTORS
	// ---------------
public:
	// Necessary for testing
    QFileStreamWhiteBox(const string_q &strFilePath, const EQFileOpenMode &eOpenMode, const pointer_uint_q uInitialCapacity, EQFileSystemError &errorInfo) : 
                                                                                                QFileStream(strFilePath, eOpenMode, uInitialCapacity, errorInfo),
                                                                                                m_bPendingBytesFlagWhenDestroyed(true)

    {
    }

	// DESTRUCTOR
	// ---------------
public:

    ~QFileStreamWhiteBox()
    {
        if(!m_bPendingBytesFlagWhenDestroyed)
        {
            m_bIsWritePending = false;
        }
    }


	// METHODS
	// ---------------
public:

    // Sets the behavior of the destructor, True means that the destructor will flush the content if there are pending bytes
    void SetPendingBytesFlagWhenDestroyed(const bool bValue)
    {
        m_bPendingBytesFlagWhenDestroyed = bValue;
    }

	// ATTRIBUTES
	// ---------------
private:

    bool m_bPendingBytesFlagWhenDestroyed;
};

} //namespace Test
} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QFILESTREAMWHITEBOX__
