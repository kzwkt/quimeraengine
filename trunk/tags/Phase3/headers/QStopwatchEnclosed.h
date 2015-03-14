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

#ifndef __QSTOPWATCHENCLOSED__
#define __QSTOPWATCHENCLOSED__

#include "SystemDefinitions.h"
#include "QStopwatch.h"
#include "QTimeSpan.h"
#include "EQStopwatchEnclosedBehavior.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{

/// <summary>
/// Represents a stopwatch that allows calculating, given the length of a time lapse, the amount of time passed in proportion to that time lapse.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QStopwatchEnclosed : public QStopwatch
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    /// <remarks>
    /// By default, the time lapse's length equals zero and the selected behavior is Clamped.
    /// </remarks>
    QStopwatchEnclosed();
    
    /// <summary>
    /// Constructor that receives the length of the time lapse and the behavior of the proportion calculation algorithm.
    /// </summary>
    /// <param name="timeLapseLength">[IN] The length of the time lapse. It should be greater than zero.</param>
    /// <param name="eBehavior">[IN] The behavior of the algorithm.</param>
    QStopwatchEnclosed(const Kinesis::QuimeraEngine::Tools::Time::QTimeSpan &timeLapseLength, const EQStopwatchEnclosedBehavior &eBehavior);


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calculates how much time has passed since the last time the stopwatch was set and its proportion with respect to the length of 
    /// the stored time lapse. Zero means no time progress whereas one means exactly a time lapse has passed.
    /// </summary>
    /// <remarks>
    /// The formula utilized to do this calculation depends on the chosen behavior (see <see cref="SetBehavior"/> method).<br/>
    /// Note that the precision of the result is millisecond-based in case single precision compilation is performed.
    /// </remarks>
    /// <returns>
    /// A floating point number from zero to infinite. Depending on the selected behavior, the range of values may be limited to [0.0, 1.0].
    /// </returns>
    Kinesis::QuimeraEngine::Common::DataTypes::float_q GetProgression() const;
    
    /// <summary>
    /// Calculates how much time has passed since the last time the stopwatch was set and its proportion, as a percentage, with respect to the length of 
    /// the stored time lapse. Zero means no time progress whereas one hundred means exactly a time lapse has passed.
    /// </summary>
    /// <remarks>
    /// The formula utilized to do this calculation depends on the chosen behavior (see <see cref="SetBehavior" /> method).<br/>
    /// Note that the precision of the result is millisecond-based in case single precision compilation is performed.
    /// </remarks>
    /// <returns>
    /// A floating point number from zero to infinite. Depending on the selected behavior, the range of values may be limited to [0.0, 100.0].
    /// </returns>
    Kinesis::QuimeraEngine::Common::DataTypes::float_q GetPercentage() const;


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Sets the time lapse that serves as reference when calculating the proportion of time passed.
    /// </summary>
    /// <remarks>
    /// Note that it will be stored with millisecond precision in case single precision compilation is performed.
    /// </remarks>
    /// <param name="length">[IN] The length of the time lapse. It should be greater than zero.</param>
    void SetTimeLapseLength(const Kinesis::QuimeraEngine::Tools::Time::QTimeSpan &length);

    /// <summary>
    /// Gets the time lapse that serves as reference when calculating the proportion of time passed.
    /// </summary>
    /// <remarks>
    /// Note that its precision is limited to millisecond in case single precision compilation is performed.
    /// </remarks>
    /// <returns>
    /// The length of the time lapse.
    /// </returns>
    Kinesis::QuimeraEngine::Tools::Time::QTimeSpan GetTimeLapseLength() const;
    
    /// <summary>
    /// Sets the behavior of the time proportion calculation algorithm.
    /// </summary>
    /// <param name="eBehavior">[IN] The behavior of the algorithm.</param>
    void SetBehavior(const EQStopwatchEnclosedBehavior &eBehavior);
    
    /// <summary>
    /// Gets the behavior of the time proportion calculation algorithm.
    /// </summary>
    /// <returns>
    /// The behavior of the algorithm.
    /// </returns>
    EQStopwatchEnclosedBehavior GetBehavior() const;


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The time lapse that serves as reference when calculating the proportion of time passed.
    /// </summary>
    Kinesis::QuimeraEngine::Common::DataTypes::float_q m_fTimeLapse;

    /// <summary>
    /// The behavior of the time proportion calculation algorithm.
    /// </summary>
    EQStopwatchEnclosedBehavior m_eBehavior;

};

} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSTOPWATCHENCLOSED__
