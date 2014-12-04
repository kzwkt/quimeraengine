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

#include "QThread.h"

#include "SQInteger.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;


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
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QThread::~QThread()
{
    QE_ASSERT_ERROR(!this->IsAlive(), "The thread handler was destroyed while the thread was still alive.");
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QThread::Interrupt()
{
    QE_ASSERT_ERROR(this->IsAlive(), "The thread cannot be interrupted, it is not running.");
    
    m_thread.interrupt();
}

void QThread::Join()
{
    // [TODO] Thund: Replace with SQThisThread::GetId()
    QE_ASSERT_ERROR(boost::this_thread::get_id() != this->GetId(), "Deadlock detected: The thread is trying to wait for itself to finish.");
    // [TODO] Thund: Replace with SQThisThread::IsInterrupted()
    QE_ASSERT_ERROR(!boost::this_thread::interruption_requested(), "The thread that is calling this method of this instance was interrupted.");

    m_thread.join();
}

string_q QThread::ToString() const
{
    static const string_q STRING_PART1 = "Thread(";
    static const string_q STRING_PART3 = ")";
    string_q strResult = STRING_PART1;
    strResult.Append(SQInteger::ToString(this->GetNativeHandle()));
    strResult.Append(STRING_PART3);
    return strResult;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool QThread::IsAlive() const
{
    return m_thread.joinable();
}

bool QThread::IsInterrupted() const
{
    return m_thread.interruption_requested();
}

QThread::Id QThread::GetId() const
{
    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to get the Id of a not-running thread.");

    return m_thread.get_id();
}

QThread::NativeThreadHandle QThread::GetNativeHandle() const
{
    QE_ASSERT_ERROR(this->IsAlive(), "It is not possible to get the native handle of a not-running thread.");

    QThread* pNonConstThis = ccast_q(this, QThread*); // This cast is necessary because the function is const but the Boost's native_handle function is not

    return pNonConstThis->m_thread.native_handle();
}


} //namespace Threading
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
