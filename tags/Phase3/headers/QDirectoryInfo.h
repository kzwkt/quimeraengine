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

#ifndef __QDIRECTORYINFO__
#define __QDIRECTORYINFO__

#include "SystemDefinitions.h"

#include "QPath.h"
#include "QDateTime.h"


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

/// <summary>
/// Stores information about a directory in the file system.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QDirectoryInfo
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives all the information about the directory.
    /// </summary>
    /// <param name="path">[IN] The absolute path to the directory.</param>
    /// <param name="creationDate">[IN] The date and time of the directory's creation.</param>
    QDirectoryInfo(const Kinesis::QuimeraEngine::System::IO::FileSystem::QPath &path,
                   const Kinesis::QuimeraEngine::Tools::Time::QDateTime &creationDate);


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the absolute path to the directory.
    /// </summary>
    /// <returns>
    /// The absolute path to the directory.
    /// </returns>
    const Kinesis::QuimeraEngine::System::IO::FileSystem::QPath& GetPath() const;
    
    /// <summary>
    /// Gets the date and time of the directory's creation.
    /// </summary>
    /// <returns>
    /// The date and time of the directory's creation.
    /// </returns>
    const Kinesis::QuimeraEngine::Tools::Time::QDateTime& GetCreationDate() const;


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The absolute path to the directory.
    /// </summary>
    Kinesis::QuimeraEngine::System::IO::FileSystem::QPath m_path;

    /// <summary>
    /// The date and time of the directory's creation.
    /// </summary>
    Kinesis::QuimeraEngine::Tools::Time::QDateTime m_creationDate;

};

} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QDIRECTORYINFO__
