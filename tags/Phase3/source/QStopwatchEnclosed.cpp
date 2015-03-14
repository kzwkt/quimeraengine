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

#include "QStopwatchEnclosed.h"

#include "SQFloat.h"
#include "MathDefinitions.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::Time::QTimeSpan;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QStopwatchEnclosed::QStopwatchEnclosed() : m_fTimeLapse(SQFloat::_0),
                                           m_eBehavior(EQStopwatchEnclosedBehavior::E_Clamped)
{
}

QStopwatchEnclosed::QStopwatchEnclosed(const QTimeSpan &timeLapseLength, const EQStopwatchEnclosedBehavior &eBehavior) : 
                                                                                                    m_fTimeLapse(0),
                                                                                                    m_eBehavior(eBehavior)
{
    this->SetTimeLapseLength(timeLapseLength);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float_q QStopwatchEnclosed::GetProgression() const
{
    QE_ASSERT_WARNING(m_fTimeLapse != SQFloat::_0, "The time lapse's length has not been set yet.");

    float_q fResult = 0.0f;

    switch(m_eBehavior)
    {
    case EQStopwatchEnclosedBehavior::E_Clamped:
        fResult = SQFloat::Clamp(this->GetElapsedTimeAsFloat() / m_fTimeLapse, SQFloat::_0, SQFloat::_1);
        break;
    case EQStopwatchEnclosedBehavior::E_Proportional:
        fResult = this->GetElapsedTimeAsFloat() / m_fTimeLapse;
        break;
    case EQStopwatchEnclosedBehavior::E_Cyclic:
        fResult = fmod_q(this->GetElapsedTimeAsFloat() / m_fTimeLapse, SQFloat::_1);
        break;
    default:
        break;
    }

    return fResult;
}

float_q QStopwatchEnclosed::GetPercentage() const
{
    QE_ASSERT_WARNING(m_fTimeLapse != SQFloat::_0, "The time lapse's length has not been set yet.");

    static const float_q ONE_HUNDRED = 100.0;
    float_q fResult = 0.0f;

    switch(m_eBehavior)
    {
    case EQStopwatchEnclosedBehavior::E_Clamped:
        fResult = SQFloat::Clamp(this->GetElapsedTimeAsFloat() / m_fTimeLapse * ONE_HUNDRED, SQFloat::_0, ONE_HUNDRED);
        break;
    case EQStopwatchEnclosedBehavior::E_Proportional:
        fResult = this->GetElapsedTimeAsFloat() / m_fTimeLapse * ONE_HUNDRED;
        break;
    case EQStopwatchEnclosedBehavior::E_Cyclic:
        fResult = fmod_q(this->GetElapsedTimeAsFloat() / m_fTimeLapse * ONE_HUNDRED, ONE_HUNDRED);
        break;
    default:
        break;
    }

    return fResult;
}

    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QStopwatchEnclosed::SetTimeLapseLength(const QTimeSpan &length)
{
    QE_ASSERT_WARNING(length.GetHundredsOfNanoseconds() > 0, "The input time lapse's length should be greater than zero.");

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    m_fTimeLapse = scast_q(length.GetMilliseconds(), float_q);
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    static const float_q HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000.0;
    m_fTimeLapse = scast_q(length.GetHundredsOfNanoseconds(), float_q) / HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND;
#endif
}

QTimeSpan QStopwatchEnclosed::GetTimeLapseLength() const
{
    using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;

#if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
    static const u64_q HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000ULL;
    return QTimeSpan(scast_q(m_fTimeLapse, pointer_uint_q) * HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND);
#elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
    static const float_q HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000.0;
    return QTimeSpan(scast_q(m_fTimeLapse * HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND, pointer_uint_q));
#endif
}

void QStopwatchEnclosed::SetBehavior(const EQStopwatchEnclosedBehavior &eBehavior)
{
    m_eBehavior = eBehavior;
}

EQStopwatchEnclosedBehavior QStopwatchEnclosed::GetBehavior() const
{
    return m_eBehavior;
}


} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
