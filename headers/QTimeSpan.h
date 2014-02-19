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

#ifndef __QTIMESPAN__
#define __QTIMESPAN__

#include "DataTypesDefinitions.h"
#include "ToolsDefinitions.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Time
{


/// <summary>
/// Class that represents a time span with an accuracy of hundreds of nanoseconds.
/// </summary>
class QE_LAYER_TOOLS_SYMBOLS QTimeSpan
{
    
    // CONSTANTS
    // ---------------
private:    
    
    /// <summary>
    /// Constant representing the factor to convert from microseconds to hundreds of nanoseconds.
    /// </summary>
    static const Kinesis::QuimeraEngine::Common::DataTypes::u64_q HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND;

    /// <summary>
    /// Constant representing the factor to convert from days to hours.
    /// </summary>
    static const Kinesis::QuimeraEngine::Common::DataTypes::u64_q HOURS_PER_DAY;

    /// <summary>
    /// Constant representing the factor to convert from hours to minutes.
    /// </summary>
    static const Kinesis::QuimeraEngine::Common::DataTypes::u64_q MINUTES_PER_HOUR;

    /// <summary>
    /// Constant representing the factor to convert from minutes to seconds.
    /// </summary>
    static const Kinesis::QuimeraEngine::Common::DataTypes::u64_q SECONDS_PER_MINUTE;

    /// <summary>
    /// Constant representing the factor to convert from seconds to milliseconds.
    /// </summary>
    static const Kinesis::QuimeraEngine::Common::DataTypes::u64_q MSECONDS_PER_SECOND;

    /// <summary>
    /// Constant representing the factor to convert from milliseconds to nanoseconds.
    /// </summary>
    static const Kinesis::QuimeraEngine::Common::DataTypes::u64_q MICROSECONDS_PER_MSECOND;

    // CONSTRUCTORS
	// ---------------
public:
        
    /// <summary>
	/// Default constructor.
	/// </summary>
    inline QTimeSpan() : m_uTimeSpan(0)
    {
    }

    /// <summary>
	/// Constructor that receives a value containing a time span.
	/// </summary>
	/// <param name="uTimeValue">[IN] Value containing a time span in hundreds of nanoseconds.</param>
    explicit inline QTimeSpan(const Kinesis::QuimeraEngine::Common::DataTypes::u64_q &uTimeValue) : m_uTimeSpan(uTimeValue)
    {
    }

    /// <summary>
	/// Constructor from different units of time. 
	/// </summary>
    /// <remarks> 
    /// If the number of days, hours, etc. exceeds the maximum quantity of time that a QTimeSpan can represent, then it will be set to the maximum value possible. 
	/// </remarks>
    /// <param name="uDays">[IN] Number of days.</param>
    /// <param name="uHours">[IN] Number of hours.</param>
    /// <param name="uMinutes">[IN] Number of minutes.</param>
    /// <param name="uSeconds">[IN] Number of seconds.</param>
    /// <param name="uMilliseconds">[IN] Number of milliseconds.</param>
    /// <param name="uMicroseconds">[IN] Number of microseconds.</param>
    /// <param name="uHundredsNanoseconds">[IN] Number of hundreds of nanoseconds.</param>
    QTimeSpan(const Kinesis::QuimeraEngine::Common::DataTypes::u64_q uDays, 
              const Kinesis::QuimeraEngine::Common::DataTypes::u64_q uHours, 
              const Kinesis::QuimeraEngine::Common::DataTypes::u64_q uMinutes, 
              const Kinesis::QuimeraEngine::Common::DataTypes::u64_q uSeconds, 
              const Kinesis::QuimeraEngine::Common::DataTypes::u64_q uMilliseconds, 
              const Kinesis::QuimeraEngine::Common::DataTypes::u64_q uMicroseconds, 
              const Kinesis::QuimeraEngine::Common::DataTypes::u64_q uHundredsNanoseconds);
       
    /// <summary>
	/// Copy constructor. Copies the content of the given time span.
	/// </summary>
	/// <param name="timeSpan">[IN] Time span instance that will be used to copy from.</param>
    QTimeSpan(const QTimeSpan& timeSpan);
      
    // METHODS
    // --------------
public:

    /// <summary>
    /// Assignment operator. Assigns the provided timeSpan object to the resident time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to be copied from.</param>
    /// <returns>
    /// Reference to the assigned time span.
    /// </returns>
    QTimeSpan& operator= (const QTimeSpan& timeSpan);


    // ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// Variable representing a time span in hundreds of nanoseconds. Using unsigned long long(64 bits).
    /// </summary>
    Kinesis::QuimeraEngine::Common::DataTypes::u64_q m_uTimeSpan;

};

} //namespace Time
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTIMESPAN__