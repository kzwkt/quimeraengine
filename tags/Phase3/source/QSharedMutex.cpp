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

#include "QSharedMutex.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Threading
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QSharedMutex::~QSharedMutex()
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QSharedMutex::Lock()
{
    m_sharedMutex.lock();
}

void QSharedMutex::LockShared()
{
    m_sharedMutex.lock_shared();
}

void QSharedMutex::Unlock()
{
    m_sharedMutex.unlock();
}

void QSharedMutex::UnlockShared()
{
    m_sharedMutex.unlock_shared();
}

bool QSharedMutex::TryLock()
{
    return m_sharedMutex.try_lock();
}

bool QSharedMutex::TryLockShared()
{
    return m_sharedMutex.try_lock_shared();
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

boost::shared_mutex& QSharedMutex::GetWrappedObject()
{
    return m_sharedMutex;
}

const boost::shared_mutex& QSharedMutex::GetWrappedObject() const
{
    return m_sharedMutex;
}


} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
