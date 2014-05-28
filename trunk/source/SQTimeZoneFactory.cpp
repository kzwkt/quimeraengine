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

#include "SQTimeZoneFactory.h"

#include <map> // [TODO] Thund: Replace this with QBinarySearchTree or QDictionary

#include "QDateTime.h"
#include "QTimeZone.h"
#include "Assertions.h"
#include "EQTextEncoding.h"
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
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QTimeZone* SQTimeZoneFactory::GetTimeZoneById(const string_q &strId)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    static bool bTimeZoneDatabaseInitialized = false;
    static boost::local_time::tz_database timeZoneDatabase;
    static std::map<string_q, QTimeZone*> timeZones;// [TODO] Thund: Replace this with QBinarySearchTree or QDictionary

    QTimeZone* pTimeZoneResult = null_q;

    // Initializes the time zone database
    if(!bTimeZoneDatabaseInitialized)
    {
        bTimeZoneDatabaseInitialized = SQTimeZoneFactory::Initialize(SQTimeZoneFactory::TIME_ZONE_DATABASE, timeZoneDatabase);
    }

    std::map<string_q, QTimeZone*>::iterator timeZoneIterator = timeZones.find(strId);

    if(timeZoneIterator != timeZones.end())
    {
        // If the time zone already existed, it is returned directly
        pTimeZoneResult = timeZoneIterator->second;
    }
    else
    {
#if QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_UNICODE
        unsigned int uOutputAux = 0;
        i8_q* szId = strId.ToBytes(EQTextEncoding::E_ASCII, uOutputAux);
        boost::local_time::time_zone_ptr pTimeZone = timeZoneDatabase.time_zone_from_region(strId.ToBytes(EQTextEncoding::E_ASCII, uOutputAux));
        delete[] szId;
#elif QE_CONFIG_CHARACTERSET_DEFAULT == QE_CONFIG_CHARACTERSET_ASCII
        boost::local_time::time_zone_ptr pTimeZone = timeZoneDatabase.time_zone_from_region(strId);
#endif

        QE_ASSERT(pTimeZone != null_q, "The provided ID does not match any time zone available");
        
        // Copies the time zone information
        if(pTimeZone != null_q)
        {
            const string_q TIMEZONE_NAME = pTimeZone->std_zone_abbrev().c_str();
            const bool IS_TZ_NEGATIVE    = pTimeZone->base_utc_offset().is_negative();

            const QTimeSpan TIMEZONE_OFFSET = QTimeSpan(0,
                                                        SQInteger::Abs(pTimeZone->base_utc_offset().hours()),
                                                        SQInteger::Abs(pTimeZone->base_utc_offset().minutes()),
                                                        SQInteger::Abs(pTimeZone->base_utc_offset().seconds()),
                                                        0, 
                                                        0, 
                                                        0);

            QTimeZone::QDstInformation dstInfo(pTimeZone);

            pTimeZoneResult = new QTimeZone(strId, 
                                            TIMEZONE_NAME, 
                                            TIMEZONE_OFFSET, 
                                            IS_TZ_NEGATIVE,
                                            dstInfo,
                                            pTimeZone->has_dst());

            timeZones.insert(std::pair<string_q, QTimeZone*>(strId, pTimeZoneResult));
        }
    }

    return pTimeZoneResult;
}

bool SQTimeZoneFactory::Initialize(const char* szSource, boost::local_time::tz_database &database)
{
    bool bResult = false;
    std::istringstream dataBaseStream;
    dataBaseStream.str(szSource);

    try
    {
        database.load_from_stream(dataBaseStream);
        bResult = true;
    }
    catch(const boost::local_time::bad_field_count &)
    {
        const bool EXCEPTION_LOADING_TIMEZONE_DATABASE = false;
        QE_ASSERT(EXCEPTION_LOADING_TIMEZONE_DATABASE, "A boost::local_time::bad_field_count exception was thrown when loading the time zone database from the stream");
    }

    return bResult;
}

} //namespace Time
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
