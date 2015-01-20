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

#ifndef __QSCOPEDLOCKPAIR__
#define __QSCOPEDLOCKPAIR__

#include "SystemDefinitions.h"
#include "QMutex.h"
#include "Assertions.h"
#include <boost/thread/locks.hpp>

namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Threading
{

/// <summary>
/// Allows two mutexes to be locked at the same time, which will be unlocked when the control flow leaves the scope where the wrapping 
/// instance was declared. Mutexes are locked/unlocked in an exclusive way.
/// </summary>
/// <remarks>
/// This class is not thread-safe.
/// </remarks>
/// <typeparam name="Mutex1T">Optional. The type of a mutex to be locked. By default, it is QMutex.</typeparam>
/// <typeparam name="Mutex2T">Optional. The type of a mutex to be locked. By default, it is QMutex.</typeparam>
template<class Mutex1T=QMutex, class Mutex2T=QMutex>
class QScopedLockPair
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives two mutexes, optionally locking them at the same time (see remarks).
    /// </summary>
    /// <remarks>
    /// Mutexes are locked sequentially and, if one of them was already locked by another thread, it waits until that mutex is unlocked by its owner.
    /// </remarks>
    /// <param name="mutex1">[IN] A mutex to be wrapped into a scope.</param>
    /// <param name="mutex2">[IN] A mutex to be wrapped into a scope.</param>
    /// <param name="bLock">[Optional][IN] Indicates whether the mutexes have to be locked when the wrapper is created; if not, they can be locked later. 
    /// By default, the mutexex are locked.</param>
    QScopedLockPair(Mutex1T &mutex1, Mutex2T &mutex2, bool bLock=true) : m_mutex1(mutex1.GetWrappedObject()),
                                                                         m_mutex2(mutex2.GetWrappedObject()),
                                                                         m_bIsOwner(false)
    {
        QE_ASSERT_ERROR(&mutex1 != &mutex2, "Both input mutexes are the same.");

        if(bLock)
            this->Lock();
    }
    

    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor. If mutexex were locked, they will be unlocked one after the other.
    /// </summary>
    ~QScopedLockPair()
    {
        if(m_bIsOwner)
            this->Unlock();
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Locks the mutexes in an exclusive way, at the same time (see remarks).
    /// </summary>
    /// <remarks>
    /// Mutexes are locked sequentially and, if one of them was already locked by another thread, it waits until that mutex is unlocked by its owner.<br/>
    /// If the mutexes were already locked by the current thread, this method cannot be called again.
    /// </remarks>
    void Lock()
    {
        QE_ASSERT_ERROR(!this->IsOwner(), "The lock already owns the mutexes. This operation could lead to a dead-lock.");

        boost::lock(m_mutex1, m_mutex2);

        m_bIsOwner = true;
    }
    
    /// <summary>
    /// Unlocks the mutexes in an exclusive way.
    /// </summary>
    /// <remarks>
    /// Mutexes are not unlocked at the same time.<br/>
    /// Locks can only unlock mutexes they locked before.
    /// </remarks>
    void Unlock()
    {
        QE_ASSERT_ERROR(this->IsOwner(), "The lock does not own the mutexes. Locks can only unlock mutexes they locked before.");

        m_mutex1.unlock();
        m_mutex2.unlock();

        m_bIsOwner = false;
    }
    
    /// <summary>
    /// Locks the mutexes in an exclusive way. If one of the mutexes is already locked by other threads, it returns immediately (see remarks).
    /// </summary>
    /// <remarks>
    /// Mutexes are locked sequentially, but they will be immediately unlocked if one of them was already locked by another thread.<br/>
    /// If the mutexes were already locked by the current thread, this method cannot be called again.
    /// </remarks>
    /// <returns>
    /// True if the mutexes have been locked by the calling thread; False otherwise.
    /// </returns>
    bool TryLock()
    {
        QE_ASSERT_ERROR(!this->IsOwner(), "The lock already owns the mutexes. This operation could lead to a dead-lock.");

        return boost::try_lock(m_mutex1, m_mutex2) == -1;
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Indicates whether the lock owns both mutexes.
    /// </summary>
    /// <returns>
    /// True if the lock owns both mutexes; False otherwise.
    /// </returns>
    bool IsOwner() const
    {
        return m_bIsOwner;
    }
    

    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The first wrapped mutex instance.
    /// </summary>
    typename Mutex1T::WrappedType& m_mutex1;
    
    /// <summary>
    /// The second wrapped mutex instance.
    /// </summary>
    typename Mutex2T::WrappedType& m_mutex2;
    
    /// <summary>
    /// Indicates whether the lock owns both mutexes.
    /// </summary>
    bool m_bIsOwner;
};

} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSCOPEDLOCKPAIR__
