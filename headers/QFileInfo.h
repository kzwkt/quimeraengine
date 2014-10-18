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

#ifndef __QFILEINFO__
#define __QFILEINFO__

#include "SystemDefinitions.h"

#include "DataTypesDefinitions.h"
#include "QDateTime.h"
#include "QPath.h"


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
/// Stores information about a file in the file system.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QFileInfo
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives all the information about a file.
    /// </summary>
    /// <param name="path">[IN] The absolute path to the file.</param>
    /// <param name="uSize">[IN] The size of the file, in bytes.</param>
    /// <param name="creationDate">[IN] The date and time of the file's creation.</param>
    /// <param name="lastModificationDate">[IN] The date and time of the file's last modification.</param>
    /// <param name="bIsReadOnly">[IN] The ability of the file to be modified. True if it is read-only, False otherwise.</param>
    QFileInfo(const QPath &path, 
              const Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q uSize,
              const Kinesis::QuimeraEngine::Tools::Time::QDateTime &creationDate,
              const Kinesis::QuimeraEngine::Tools::Time::QDateTime &lastModificationDate,
              const bool bIsReadOnly);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Indicates whether the file can be modified or not.
    /// </summary>
    /// <returns>
    /// True if it is read-only, False otherwise.
    /// </returns>
    const bool IsReadOnly() const;
    
    /// <summary>
    /// Gets the date and time of the file's last modification.
    /// </summary>
    /// <returns>
    /// The date and time of the file's last modification.
    /// </returns>
    const Kinesis::QuimeraEngine::Tools::Time::QDateTime& GetLastModificationDate() const;
    
    /// <summary>
    /// Gets the date and time of the file's creation.
    /// </summary>
    /// <returns>
    /// The date and time of the file's creation.
    /// </returns>
    const Kinesis::QuimeraEngine::Tools::Time::QDateTime& GetCreationDate() const;
    
    /// <summary>
    /// Gets the size of the file, in bytes.
    /// </summary>
    /// <returns>
    /// The size of the file, in bytes.
    /// </returns>
    const Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q GetSize() const;
    
    /// <summary>
    /// Gets the absolute path to the file.
    /// </summary>
    /// <returns>
    /// The absolute path to the file.
    /// </returns>
    const QPath& GetPath() const;


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The absolute path to the file.
    /// </summary>
    QPath m_path;
    
    /// <summary>
    /// The size of the file, in bytes.
    /// </summary>
    Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q m_uSize;

    /// <summary>
    /// The date and time of the file's creation.
    /// </summary>
    Kinesis::QuimeraEngine::Tools::Time::QDateTime m_creationDate;
    
    /// <summary>
    /// The date and time of the file's last modification.
    /// </summary>
    Kinesis::QuimeraEngine::Tools::Time::QDateTime m_lastModificationDate;
        
    /// <summary>
    /// Indicates whether the file can be modified or not.
    /// </summary>
    bool m_bIsReadOnly;
};

} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QFILEINFO__
