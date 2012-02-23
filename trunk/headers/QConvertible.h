// [TERMS&CONDITIONS]

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
    inline TargetType& As()
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
    inline TargetType& As() const
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
    inline TargetType* AsPtr()
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
    inline TargetType* AsPtr() const
    {
        return rcast_q(this, TargetType*);
    }
};

} //namespace Core
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCONVERTIBLE__
