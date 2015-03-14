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

#include "QTimeZone.h"

#include "Assertions.h"
#include "SQInteger.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Time
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QTimeZone::QDstInformation::QDstInformation(boost::local_time::time_zone_ptr pTimeZone)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    QE_ASSERT_ERROR(pTimeZone != boost::local_time::time_zone_ptr((boost::local_time::time_zone_ptr::element_type*) null_q), "Input time zone data must not be null");

    if(pTimeZone->has_dst())
    {
        m_bIsNegative = pTimeZone->dst_offset().is_negative();

        // The time offset to apply when DST is active
        m_offset = QTimeSpan(0,
                             SQInteger::Abs(pTimeZone->dst_offset().hours()),
                             SQInteger::Abs(pTimeZone->dst_offset().minutes()),
                             SQInteger::Abs(pTimeZone->dst_offset().seconds()),
                             0,
                             0,
                             0);
        
        m_pTimeZone = pTimeZone;
    }
    else
    {
        m_offset = QTimeSpan(0);
        m_bIsNegative = false;
        m_pTimeZone = boost::local_time::time_zone_ptr((boost::local_time::time_zone_ptr::element_type*) null_q);
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QDateTime QTimeZone::QDstInformation::GetStartInYear(const int nYear) const
{
    QE_ASSERT_ERROR(nYear != 0, "The input year cannot be zero");

    if(m_pTimeZone->has_dst() && nYear != 0)
    {
        // Does it return local time? or utc time?
        boost::posix_time::ptime startTime = m_pTimeZone->dst_local_start_time(nYear);

        return QDateTime(nYear,
                         startTime.date().month(),
                         startTime.date().day(),
                         startTime.time_of_day().hours(),
                         startTime.time_of_day().minutes(), 
                         startTime.time_of_day().seconds(), 0, 0, 0, 0);
    }
    else
    {
        return QDateTime::GetUndefinedDate();
    }
}

QDateTime QTimeZone::QDstInformation::GetEndInYear(const int nYear) const
{
    QE_ASSERT_ERROR(nYear != 0, "The input year cannot be zero");

    if(m_pTimeZone->has_dst() && nYear != 0)
    {
        boost::posix_time::ptime endTime = m_pTimeZone->dst_local_end_time(nYear);

        return QDateTime(nYear,
                         endTime.date().month(),
                         endTime.date().day(),
                         endTime.time_of_day().hours(),
                         endTime.time_of_day().minutes(), 
                         endTime.time_of_day().seconds(), 0, 0, 0, 0);
    }
    else
    {
        return QDateTime::GetUndefinedDate();
    }
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QTimeSpan& QTimeZone::QDstInformation::GetOffset() const
{
    return m_offset;
}

const bool QTimeZone::QDstInformation::IsOffsetNegative() const
{
    return m_bIsNegative;
}


} //namespace Time
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
