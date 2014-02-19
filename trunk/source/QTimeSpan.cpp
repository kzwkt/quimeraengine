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

#include <limits>

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
const u64_q QTimeSpan::MSECONDS_PER_SECOND = 1000;
const u64_q QTimeSpan::MICROSECONDS_PER_MSECOND = 1000;

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

       
QTimeSpan::QTimeSpan(const u64_q uDays, const u64_q uHours, const u64_q uMinutes, const u64_q uSeconds, const u64_q uMiliseconds, const u64_q uMicroseconds, const u64_q uHundredsNanoseconds)
{
   
   
    // Constants containing the max value for each parameter.
    // Remember we have to convert them to hundreds of nanoseconds.
    const u64_q MAX_MICROSECONDS = std::numeric_limits<u64_q>::max() / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND;
    const u64_q MAX_MSECONDS = std::numeric_limits<u64_q>::max() / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MICROSECONDS_PER_MSECOND );
    const u64_q MAX_SECONDS = std::numeric_limits<u64_q>::max() / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MSECONDS_PER_SECOND * MICROSECONDS_PER_MSECOND);
    const u64_q MAX_MINUTES = std::numeric_limits<u64_q>::max() / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * SECONDS_PER_MINUTE * MSECONDS_PER_SECOND * MICROSECONDS_PER_MSECOND);
    const u64_q MAX_HOURS = std::numeric_limits<u64_q>::max() / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MSECONDS_PER_SECOND * MICROSECONDS_PER_MSECOND);
    const u64_q MAX_DAYS = std::numeric_limits<u64_q>::max() / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MSECONDS_PER_SECOND * MICROSECONDS_PER_MSECOND);

    bool bNotGreaterThanMaxValue = (uDays <= MAX_DAYS                && 
                                   uHours <= MAX_HOURS              && 
                                   uMinutes <= MAX_MINUTES          && 
                                   uSeconds <= MAX_SECONDS          && 
                                   uMiliseconds <= MAX_MSECONDS     &&  
                                   uMicroseconds <= MAX_MICROSECONDS && 
                                   uHundredsNanoseconds <= std::numeric_limits<u64_q>::max());

    // Assertion to verify that we will not get overflow while calculating the time span
    QE_ASSERT(bNotGreaterThanMaxValue == true, "Parameters must be lower than maximum values"); 

    // To avoid overflow if it happens return max value allowed
    if (!bNotGreaterThanMaxValue)
    {
          m_uTimeSpan = std::numeric_limits<u64_q>::max();
    }
    else
    {
        u64_q uMicrosecondsToHundreds = HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * uMicroseconds;
        u64_q uMsecondsToHundreds = HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MICROSECONDS_PER_MSECOND * uMiliseconds;
        u64_q uSecondsToHundreds = HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MSECONDS_PER_SECOND * uSeconds * MICROSECONDS_PER_MSECOND;
        u64_q uMinutesToHundreds = HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * SECONDS_PER_MINUTE * uMinutes * MSECONDS_PER_SECOND * MICROSECONDS_PER_MSECOND;
        u64_q uHoursToHundreds = HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MINUTES_PER_HOUR * uHours * SECONDS_PER_MINUTE * MSECONDS_PER_SECOND * MICROSECONDS_PER_MSECOND;
        u64_q uDaysToHundreds = HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * HOURS_PER_DAY * uDays * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MSECONDS_PER_SECOND * MICROSECONDS_PER_MSECOND;
    
        // Now check that we will not have overflow with the addition either
        bNotGreaterThanMaxValue = uMicrosecondsToHundreds <= (std::numeric_limits<u64_q>::max() - uHundredsNanoseconds ) &&
                                 uMsecondsToHundreds <= (std::numeric_limits<u64_q>::max() - (uHundredsNanoseconds + uMicrosecondsToHundreds)) &&
                                 uSecondsToHundreds <= (std::numeric_limits<u64_q>::max() - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMsecondsToHundreds)) &&
                                 uMinutesToHundreds <= (std::numeric_limits<u64_q>::max() - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMsecondsToHundreds + uSecondsToHundreds)) &&
                                 uHoursToHundreds <= (std::numeric_limits<u64_q>::max() - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMsecondsToHundreds + uSecondsToHundreds + uMinutesToHundreds)) &&
                                 uDaysToHundreds <= (std::numeric_limits<u64_q>::max() - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMsecondsToHundreds + uSecondsToHundreds + uMinutesToHundreds + uHoursToHundreds));
    
        QE_ASSERT(bNotGreaterThanMaxValue == true, "The converted values must be low enough to avoid overflow");

        // To avoid overflow if it happens return max value allowed
        if (!bNotGreaterThanMaxValue)
        {
           m_uTimeSpan = std::numeric_limits<u64_q>::max();
        }
        else
        {
           // Add all the parameters 
           m_uTimeSpan = uHundredsNanoseconds + uMicrosecondsToHundreds +
                         uMsecondsToHundreds + uSecondsToHundreds +
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

} //namespace Time
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis