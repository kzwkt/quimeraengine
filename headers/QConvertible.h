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

#ifndef __QCONVERTIBLE__
#define __QCONVERTIBLE__

#include "InternalDefinitions.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Core
{

/// <summary>
/// Adds the capability to derived classes for converting itself to any other type. Conversions are
/// not real data translations but reference type conversions.
/// </summary>
class QDllExport QConvertible
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	QConvertible()
    {
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Converts the reference to the object to a reference of different type to the object.
    /// One must be careful when using this method, the object type size has to equals the target type size.
    /// </summary>
    /// <returns>A reference to the object but using a different type. It's worth to remark that the reference
    /// points to the original object.</returns>
    template<class TargetType>
    TargetType& As()
    {
        return rcast_q(*this, TargetType&);
    }

    /// <summary>
    /// Converts the reference to the object to a reference of different type to the object.
    /// One must be careful when using this method, the object type size has to equals the target type size.
    /// </summary>
    /// <returns>A reference to the object but using a different type. It's worth to remark that the reference
    /// points to the original object.</returns>
    template<class TargetType>
    TargetType& As() const
    {
        return rcast_q(*this, TargetType&);
    }

    /// <summary>
    /// Converts the reference to the object to a pointer of different type to the object.
    /// One must be careful when using this method, the object type size has to equals the target type size.
    /// </summary>
    /// <returns>A pointer to the object but using a different type. It's worth to remark that the pionter
    /// points to the original object.</returns>
    template<class TargetType>
    TargetType* AsPtr()
    {
        return rcast_q(this, TargetType*);
    }

    /// <summary>
    /// Converts the reference to the object to a pointer of different type to the object.
    /// One must be careful when using this method, the object type size has to equals the target type size.
    /// </summary>
    /// <returns>A pointer to the object but using a different type. It's worth to remark that the pionter
    /// points to the original object.</returns>
    template<class TargetType>
    TargetType* AsPtr() const
    {
        return rcast_q(this, TargetType*);
    }
};

} //namespace Core
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCONVERTIBLE__
