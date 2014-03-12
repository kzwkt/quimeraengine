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


#include "QTimeSpan.h"
#include "Assertions.h"


using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Time
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
const u64_q QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND = 10;
const u64_q QTimeSpan::HOURS_PER_DAY = 24;
const u64_q QTimeSpan::MINUTES_PER_HOUR = 60;
const u64_q QTimeSpan::SECONDS_PER_MINUTE = 60;
const u64_q QTimeSpan::MILLISECONDS_PER_SECOND = 1000;
const u64_q QTimeSpan::MICROSECONDS_PER_MILLISECOND = 1000;
const u64_q QTimeSpan::MAXIMUM_VALUE = -1;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

       
QTimeSpan::QTimeSpan(const u64_q uDays, const u64_q uHours, const u64_q uMinutes, const u64_q uSeconds, const u64_q uMilliseconds, const u64_q uMicroseconds, const u64_q uHundredsNanoseconds)
{
    // Constants containing the max value for each parameter.
    // Remember we have to convert them to hundreds of nanoseconds.
    const u64_q MAX_MICROSECONDS = MAXIMUM_VALUE / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND;
    const u64_q MAX_MILLISECONDS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MICROSECONDS_PER_MILLISECOND );
    const u64_q MAX_SECONDS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);
    const u64_q MAX_MINUTES = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);
    const u64_q MAX_HOURS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);
    const u64_q MAX_DAYS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);

    bool bNotGreaterThanMaxValue = (uDays <= MAX_DAYS                && 
                                   uHours <= MAX_HOURS               && 
                                   uMinutes <= MAX_MINUTES           && 
                                   uSeconds <= MAX_SECONDS           && 
                                   uMilliseconds <= MAX_MILLISECONDS &&  
                                   uMicroseconds <= MAX_MICROSECONDS && 
                                   uHundredsNanoseconds <= MAXIMUM_VALUE);

    // Assertion to verify that we will not get overflow while calculating the time span
    QE_ASSERT(bNotGreaterThanMaxValue == true, "Parameters must be lower than maximum values"); 

    // To avoid overflow if it happens return max value allowed
    if (!bNotGreaterThanMaxValue)
    {
          m_uTimeSpan = MAXIMUM_VALUE;
    }
    else
    {
        u64_q uMicrosecondsToHundreds = QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * uMicroseconds;
        u64_q uMillisecondsToHundreds = QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * QTimeSpan::MICROSECONDS_PER_MILLISECOND * uMilliseconds;
        u64_q uSecondsToHundreds = QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * QTimeSpan::MILLISECONDS_PER_SECOND * uSeconds * QTimeSpan::MICROSECONDS_PER_MILLISECOND;
        u64_q uMinutesToHundreds = QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * QTimeSpan::SECONDS_PER_MINUTE * uMinutes * QTimeSpan::MILLISECONDS_PER_SECOND * QTimeSpan::MICROSECONDS_PER_MILLISECOND;
        u64_q uHoursToHundreds = QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * QTimeSpan::MINUTES_PER_HOUR * uHours * QTimeSpan::SECONDS_PER_MINUTE * QTimeSpan::MILLISECONDS_PER_SECOND * QTimeSpan::MICROSECONDS_PER_MILLISECOND;
        u64_q uDaysToHundreds = QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * QTimeSpan::HOURS_PER_DAY * uDays * QTimeSpan::MINUTES_PER_HOUR * QTimeSpan::SECONDS_PER_MINUTE * QTimeSpan::MILLISECONDS_PER_SECOND * QTimeSpan::MICROSECONDS_PER_MILLISECOND;
    
        // Now check that we will not have overflow with the addition either
        bNotGreaterThanMaxValue = uMicrosecondsToHundreds <= (MAXIMUM_VALUE - uHundredsNanoseconds ) &&
                                  uMillisecondsToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds)) &&
                                  uSecondsToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds)) &&
                                  uMinutesToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds + uSecondsToHundreds)) &&
                                  uHoursToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds + uSecondsToHundreds + uMinutesToHundreds)) &&
                                  uDaysToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds + uSecondsToHundreds + uMinutesToHundreds + uHoursToHundreds));
    
        QE_ASSERT(bNotGreaterThanMaxValue == true, "The converted values must be low enough to avoid overflow");

        // To avoid overflow if it happens return max value allowed
        if (!bNotGreaterThanMaxValue)
        {
           m_uTimeSpan = MAXIMUM_VALUE;
        }
        else
        {
           // Add all the parameters 
           m_uTimeSpan = uHundredsNanoseconds + uMicrosecondsToHundreds +
                         uMillisecondsToHundreds + uSecondsToHundreds +
                         uMinutesToHundreds + uHoursToHundreds + uDaysToHundreds;
        }
    }

}
        
        
QTimeSpan::QTimeSpan(const QTimeSpan& timeSpan)
{
    m_uTimeSpan = timeSpan.m_uTimeSpan;
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |           METHODS		     |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QTimeSpan& QTimeSpan::operator= (const QTimeSpan& timeSpan)
{
    m_uTimeSpan = timeSpan.m_uTimeSpan;
    return *this;
}

QTimeSpan QTimeSpan::operator+ (const QTimeSpan& timeSpan) const
{
    return QTimeSpan(*this) += timeSpan; 
}

QTimeSpan& QTimeSpan::operator+= (const QTimeSpan& timeSpan)
{
    bool bNotGreaterThanMaxValue = ((QTimeSpan::MAXIMUM_VALUE  - this->m_uTimeSpan) >= timeSpan.m_uTimeSpan);
    // Assertion to verify that we will not get overflow while calculating the time span
    QE_ASSERT(bNotGreaterThanMaxValue == true, "The addition of the two timespan objects can not be higher than maximum value"); 
    
    if (bNotGreaterThanMaxValue)
    {
        this->m_uTimeSpan += timeSpan.m_uTimeSpan;        
    }
    else
    {
        this->m_uTimeSpan = QTimeSpan::MAXIMUM_VALUE;
    }
     
    return *this;
}

QTimeSpan& QTimeSpan::operator-= (const QTimeSpan& timeSpan)
{    
    this->m_uTimeSpan = (this->m_uTimeSpan < timeSpan.m_uTimeSpan) ? (timeSpan.m_uTimeSpan - this->m_uTimeSpan) : (this->m_uTimeSpan - timeSpan.m_uTimeSpan);
    return *this;
}

QTimeSpan QTimeSpan::operator- (const QTimeSpan& timeSpan) const
{
    return QTimeSpan(*this) -= timeSpan;
}

bool QTimeSpan::operator> (const QTimeSpan& timeSpan) const
{
    return (this->m_uTimeSpan > timeSpan.m_uTimeSpan);
}

bool QTimeSpan::operator>= (const QTimeSpan& timeSpan) const 
{
    return (this->m_uTimeSpan >= timeSpan.m_uTimeSpan);
}

bool QTimeSpan::operator< (const QTimeSpan& timeSpan) const
{
    return (this->m_uTimeSpan < timeSpan.m_uTimeSpan);
}

bool QTimeSpan::operator<= (const QTimeSpan& timeSpan) const
{
    return (this->m_uTimeSpan <= timeSpan.m_uTimeSpan);
}

u32_q QTimeSpan::GetDays() const
{
    return scast_q(m_uTimeSpan / (QTimeSpan::HOURS_PER_DAY * 
                                  QTimeSpan::MINUTES_PER_HOUR * 
                                  QTimeSpan::SECONDS_PER_MINUTE * 
                                  QTimeSpan::MILLISECONDS_PER_SECOND * 
                                  QTimeSpan::MICROSECONDS_PER_MILLISECOND *
                                  QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND), u32_q);
}

u32_q QTimeSpan::GetHours() const
{
    return scast_q(m_uTimeSpan / (QTimeSpan::MINUTES_PER_HOUR * 
                                  QTimeSpan::SECONDS_PER_MINUTE * 
                                  QTimeSpan::MILLISECONDS_PER_SECOND * 
                                  QTimeSpan::MICROSECONDS_PER_MILLISECOND *
                                  QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND), u32_q);
}

u32_q QTimeSpan::GetMinutes() const
{
    return scast_q(m_uTimeSpan / (QTimeSpan::SECONDS_PER_MINUTE * 
                                  QTimeSpan::MILLISECONDS_PER_SECOND * 
                                  QTimeSpan::MICROSECONDS_PER_MILLISECOND *
                                  QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND), u32_q);
}

u64_q QTimeSpan::GetSeconds() const
{
    return m_uTimeSpan / (QTimeSpan::MILLISECONDS_PER_SECOND * 
                          QTimeSpan::MICROSECONDS_PER_MILLISECOND *
                          QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND);
}

u64_q QTimeSpan::GetMilliseconds() const
{
    return m_uTimeSpan / (QTimeSpan::MICROSECONDS_PER_MILLISECOND *
                          QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND);
}

u64_q QTimeSpan::GetMicroseconds() const
{
    return m_uTimeSpan / QTimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND;
}

u64_q QTimeSpan::GetHundredsOfNanoseconds() const
{
    return m_uTimeSpan;
}

} //namespace Time
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis