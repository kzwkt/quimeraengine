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
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QTimeZone::QTimeZone(const string_q &strId, const string_q &strName,
                     const QTimeSpan &timeZoneOffset, const bool bIsTimeZoneOffsetNegative,
                     const QTimeZone::QDstInformation &dstInformation, const bool bHasDstOffset) :

            m_strName(strName),
            m_strId(strId),
            m_dstInformation(dstInformation),
            m_timeZoneOffset(timeZoneOffset),
            m_bTzOffsetIsNegative(bIsTimeZoneOffsetNegative),
            m_bHasDstOffset(bHasDstOffset)
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void QTimeZone::CalculateOffset(const QDateTime &dateTime, QTimeSpan &offset, bool &bIsNegative) const
{
    QE_ASSERT(dateTime != QDateTime::GetUndefinedDate(), "The input date is undefined");

    QTimeSpan dstOffset(0);

    offset = m_timeZoneOffset;

    if(m_bHasDstOffset)
    {
        // [TODO] Thund: Uncomment when GetYear exists
        /*QDateTime startDateTime = m_dstInformation.GetStartInYear(dateTime.GetYear());
        QDateTime endDateTime = m_dstInformation.GetEndInYear(dateTime.GetYear());

        if(dateTime >= startDateTime && dateTime < endDateTime)
        {
            if(!m_bTzOffsetIsNegative && !m_dstInformation.IsOffsetNegative())
            {
                // Both offsets are positive, they are summed
                offset += m_dstInformation.GetOffset();
                bIsNegative = false;
            }
            else if(m_bTzOffsetIsNegative && m_dstInformation.IsOffsetNegative())
            {
                // Both are negative, they are summed
                offset += m_dstInformation.GetOffset();
                bIsNegative = true;
            }
            else if(m_timeZoneOffset >= m_dstInformation.GetOffset())
            {
                // Time zone offset is bigger or equals the DST offset, the result is the difference
                offset -= m_dstInformation.GetOffset();
                bIsNegative = m_bTzOffsetIsNegative;
            }
            else
            {
                // Time zone offset is smaller than the DST offset, the result is the difference
                offset = m_dstInformation.GetOffset() - offset;
                bIsNegative = m_dstInformation.IsOffsetNegative();
            }
        }
        else
        {*/
            bIsNegative = m_bTzOffsetIsNegative;
        /*}*/
    }
    else
    {
        bIsNegative = m_bTzOffsetIsNegative;
    }
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QTimeSpan& QTimeZone::GetTimeZoneOffset() const
{
    return m_timeZoneOffset;
}


const string_q& QTimeZone::GetName() const
{
    return m_strName;
}

const string_q& QTimeZone::GetId() const
{
    return m_strId;
}

const bool QTimeZone::IsTimeZoneOffsetNegative() const
{
    return m_bTzOffsetIsNegative;
}

const QTimeZone::QDstInformation& QTimeZone::GetDstInfo() const
{
    return m_dstInformation;
}

const bool QTimeZone::HasDstOffset() const
{
    return m_bHasDstOffset;
}

} //namespace Time
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
