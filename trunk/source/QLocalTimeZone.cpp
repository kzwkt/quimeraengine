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

#include "QLocalTimeZone.h"

#include "SQTimeZoneFactory.h"
#include "Assertions.h"

#if defined(QE_COMPILER_GCC) && defined(QE_OS_WINDOWS) // Only when using MinGW
    #include <Windows.h>
    #include "Workarounds/WinBase_Workarounds.h"
#elif defined(QE_OS_LINUX)
    #include <fstream>
    #include "EQComparisonType.h"
#endif

using Kinesis::QuimeraEngine::Tools::Time::SQTimeZoneFactory;
using Kinesis::QuimeraEngine::Tools::Time::QTimeZone;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Timing
{
    
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

#ifdef QE_OS_WINDOWS

const std::pair<string_q, string_q> QLocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY[] =
    {
        std::pair<string_q, string_q>(QE_L("AUS Central Standard Time"),    QE_L("Australia/Darwin")),
        std::pair<string_q, string_q>(QE_L("AUS Eastern Standard Time"),    QE_L("Australia/Sydney")),
        std::pair<string_q, string_q>(QE_L("Afghanistan Standard Time"),    QE_L("Asia/Kabul")),
        std::pair<string_q, string_q>(QE_L("Alaskan Standard Time"),    QE_L("America/Anchorage")),
        std::pair<string_q, string_q>(QE_L("Arab Standard Time"),    QE_L("Asia/Riyadh")),
        std::pair<string_q, string_q>(QE_L("Arabian Standard Time"),    QE_L("Asia/Dubai")),
        std::pair<string_q, string_q>(QE_L("Arabic Standard Time"),    QE_L("Asia/Baghdad")),
        std::pair<string_q, string_q>(QE_L("Argentina Standard Time"),    QE_L("America/Buenos_Aires")),
        std::pair<string_q, string_q>(QE_L("Atlantic Standard Time"),    QE_L("America/Halifax")),
        std::pair<string_q, string_q>(QE_L("Azerbaijan Standard Time"),    QE_L("Asia/Baku")),
        std::pair<string_q, string_q>(QE_L("Azores Standard Time"),    QE_L("Atlantic/Azores")),
        std::pair<string_q, string_q>(QE_L("Bahia Standard Time"),    QE_L("America/Bahia")),
        std::pair<string_q, string_q>(QE_L("Bangladesh Standard Time"),    QE_L("Asia/Dhaka")),
        std::pair<string_q, string_q>(QE_L("Canada Central Standard Time"),    QE_L("America/Regina")),
        std::pair<string_q, string_q>(QE_L("Cape Verde Standard Time"),    QE_L("Atlantic/Cape_Verde")),
        std::pair<string_q, string_q>(QE_L("Caucasus Standard Time"),    QE_L("Asia/Yerevan")),
        std::pair<string_q, string_q>(QE_L("Cen. Australia Standard Time"),    QE_L("Australia/Adelaide")),
        std::pair<string_q, string_q>(QE_L("Central America Standard Time"),    QE_L("America/Guatemala")),
        std::pair<string_q, string_q>(QE_L("Central Asia Standard Time"),    QE_L("Asia/Almaty")),
        std::pair<string_q, string_q>(QE_L("Central Brazilian Standard Time"),    QE_L("America/Cuiaba")),
        std::pair<string_q, string_q>(QE_L("Central Europe Standard Time"),    QE_L("Europe/Budapest")),
        std::pair<string_q, string_q>(QE_L("Central European Standard Time"),    QE_L("Europe/Warsaw")),
        std::pair<string_q, string_q>(QE_L("Central Pacific Standard Time"),    QE_L("Pacific/Guadalcanal")),
        std::pair<string_q, string_q>(QE_L("Central Standard Time"),    QE_L("America/Chicago")),
        std::pair<string_q, string_q>(QE_L("Central Standard Time (Mexico)"),    QE_L("America/Mexico_City")),
        std::pair<string_q, string_q>(QE_L("China Standard Time"),    QE_L("Asia/Shanghai")),
        std::pair<string_q, string_q>(QE_L("Dateline Standard Time"),    QE_L("Etc/GMT+12")),
        std::pair<string_q, string_q>(QE_L("E. Africa Standard Time"),    QE_L("Africa/Nairobi")),
        std::pair<string_q, string_q>(QE_L("E. Australia Standard Time"),    QE_L("Australia/Brisbane")),
        std::pair<string_q, string_q>(QE_L("E. Europe Standard Time"),    QE_L("Asia/Nicosia")),
        std::pair<string_q, string_q>(QE_L("E. South America Standard Time"),    QE_L("America/Sao_Paulo")),
        std::pair<string_q, string_q>(QE_L("Eastern Standard Time"),    QE_L("America/New_York")),
        std::pair<string_q, string_q>(QE_L("Egypt Standard Time"),    QE_L("Africa/Cairo")),
        std::pair<string_q, string_q>(QE_L("Ekaterinburg Standard Time"),    QE_L("Asia/Yekaterinburg")),
        std::pair<string_q, string_q>(QE_L("FLE Standard Time"),    QE_L("Europe/Kiev")),
        std::pair<string_q, string_q>(QE_L("Fiji Standard Time"),    QE_L("Pacific/Fiji")),
        std::pair<string_q, string_q>(QE_L("GMT Standard Time"),    QE_L("Europe/London")),
        std::pair<string_q, string_q>(QE_L("GTB Standard Time"),    QE_L("Europe/Bucharest")),
        std::pair<string_q, string_q>(QE_L("Georgian Standard Time"),    QE_L("Asia/Tbilisi")),
        std::pair<string_q, string_q>(QE_L("Greenland Standard Time"),    QE_L("America/Godthab")),
        std::pair<string_q, string_q>(QE_L("Greenwich Standard Time"),    QE_L("Atlantic/Reykjavik")),
        std::pair<string_q, string_q>(QE_L("Hawaiian Standard Time"),    QE_L("Pacific/Honolulu")),
        std::pair<string_q, string_q>(QE_L("India Standard Time"),    QE_L("Asia/Calcutta")),
        std::pair<string_q, string_q>(QE_L("Iran Standard Time"),    QE_L("Asia/Tehran")),
        std::pair<string_q, string_q>(QE_L("Israel Standard Time"),    QE_L("Asia/Jerusalem")),
        std::pair<string_q, string_q>(QE_L("Jordan Standard Time"),    QE_L("Asia/Amman")),
        std::pair<string_q, string_q>(QE_L("Kaliningrad Standard Time"),    QE_L("Europe/Kaliningrad")),
        std::pair<string_q, string_q>(QE_L("Korea Standard Time"),    QE_L("Asia/Seoul")),
        std::pair<string_q, string_q>(QE_L("Libya Standard Time"),    QE_L("Africa/Tripoli")),
        std::pair<string_q, string_q>(QE_L("Magadan Standard Time"),    QE_L("Asia/Magadan")),
        std::pair<string_q, string_q>(QE_L("Mauritius Standard Time"),    QE_L("Indian/Mauritius")),
        std::pair<string_q, string_q>(QE_L("Middle East Standard Time"),    QE_L("Asia/Beirut")),
        std::pair<string_q, string_q>(QE_L("Montevideo Standard Time"),    QE_L("America/Montevideo")),
        std::pair<string_q, string_q>(QE_L("Morocco Standard Time"),    QE_L("Africa/Casablanca")),
        std::pair<string_q, string_q>(QE_L("Mountain Standard Time"),    QE_L("America/Denver")),
        std::pair<string_q, string_q>(QE_L("Mountain Standard Time (Mexico)"),    QE_L("America/Chihuahua")),
        std::pair<string_q, string_q>(QE_L("Myanmar Standard Time"),    QE_L("Asia/Rangoon")),
        std::pair<string_q, string_q>(QE_L("N. Central Asia Standard Time"),    QE_L("Asia/Novosibirsk")),
        std::pair<string_q, string_q>(QE_L("Namibia Standard Time"),    QE_L("Africa/Windhoek")),
        std::pair<string_q, string_q>(QE_L("Nepal Standard Time"),    QE_L("Asia/Katmandu")),
        std::pair<string_q, string_q>(QE_L("New Zealand Standard Time"),    QE_L("Pacific/Auckland")),
        std::pair<string_q, string_q>(QE_L("Newfoundland Standard Time"),    QE_L("America/St_Johns")),
        std::pair<string_q, string_q>(QE_L("North Asia East Standard Time"),    QE_L("Asia/Irkutsk")),
        std::pair<string_q, string_q>(QE_L("North Asia Standard Time"),    QE_L("Asia/Krasnoyarsk")),
        std::pair<string_q, string_q>(QE_L("Pacific SA Standard Time"),    QE_L("America/Santiago")),
        std::pair<string_q, string_q>(QE_L("Pacific Standard Time"),    QE_L("America/Los_Angeles")),
        std::pair<string_q, string_q>(QE_L("Pacific Standard Time (Mexico)"),    QE_L("America/Santa_Isabel")),
        std::pair<string_q, string_q>(QE_L("Pakistan Standard Time"),    QE_L("Asia/Karachi")),
        std::pair<string_q, string_q>(QE_L("Paraguay Standard Time"),    QE_L("America/Asuncion")),
        std::pair<string_q, string_q>(QE_L("Romance Standard Time"),    QE_L("Europe/Paris")),
        std::pair<string_q, string_q>(QE_L("Russian Standard Time"),    QE_L("Europe/Moscow")),
        std::pair<string_q, string_q>(QE_L("SA Eastern Standard Time"),    QE_L("America/Cayenne")),
        std::pair<string_q, string_q>(QE_L("SA Pacific Standard Time"),    QE_L("America/Bogota")),
        std::pair<string_q, string_q>(QE_L("SA Western Standard Time"),    QE_L("America/La_Paz")),
        std::pair<string_q, string_q>(QE_L("SE Asia Standard Time"),    QE_L("Asia/Bangkok")),
        std::pair<string_q, string_q>(QE_L("Samoa Standard Time"),    QE_L("Pacific/Apia")),
        std::pair<string_q, string_q>(QE_L("Singapore Standard Time"),    QE_L("Asia/Singapore")),
        std::pair<string_q, string_q>(QE_L("South Africa Standard Time"),    QE_L("Africa/Johannesburg")),
        std::pair<string_q, string_q>(QE_L("Sri Lanka Standard Time"),    QE_L("Asia/Colombo")),
        std::pair<string_q, string_q>(QE_L("Syria Standard Time"),    QE_L("Asia/Damascus")),
        std::pair<string_q, string_q>(QE_L("Taipei Standard Time"),    QE_L("Asia/Taipei")),
        std::pair<string_q, string_q>(QE_L("Tasmania Standard Time"),    QE_L("Australia/Hobart")),
        std::pair<string_q, string_q>(QE_L("Tokyo Standard Time"),    QE_L("Asia/Tokyo")),
        std::pair<string_q, string_q>(QE_L("Tonga Standard Time"),    QE_L("Pacific/Tongatapu")),
        std::pair<string_q, string_q>(QE_L("Turkey Standard Time"),    QE_L("Europe/Istanbul")),
        std::pair<string_q, string_q>(QE_L("US Eastern Standard Time"),    QE_L("America/Indianapolis")),
        std::pair<string_q, string_q>(QE_L("US Mountain Standard Time"),    QE_L("America/Phoenix")),
        std::pair<string_q, string_q>(QE_L("UTC"),    QE_L("America/Danmarkshavn")),
        std::pair<string_q, string_q>(QE_L("UTC+12"),    QE_L("Pacific/Tarawa")),
        std::pair<string_q, string_q>(QE_L("UTC-02"),    QE_L("America/Noronha")),
        std::pair<string_q, string_q>(QE_L("UTC-11"),    QE_L("Pacific/Midway")),
        std::pair<string_q, string_q>(QE_L("Ulaanbaatar Standard Time"),    QE_L("Asia/Ulaanbaatar")),
        std::pair<string_q, string_q>(QE_L("Venezuela Standard Time"),    QE_L("America/Caracas")),
        std::pair<string_q, string_q>(QE_L("Vladivostok Standard Time"),    QE_L("Asia/Vladivostok")),
        std::pair<string_q, string_q>(QE_L("W. Australia Standard Time"),    QE_L("Australia/Perth")),
        std::pair<string_q, string_q>(QE_L("W. Central Africa Standard Time"),    QE_L("Africa/Lagos")),
        std::pair<string_q, string_q>(QE_L("W. Europe Standard Time"),    QE_L("Europe/Berlin")),
        std::pair<string_q, string_q>(QE_L("West Asia Standard Time"),    QE_L("Asia/Tashkent")),
        std::pair<string_q, string_q>(QE_L("West Pacific Standard Time"),    QE_L("Pacific/Port_Moresby")),
        std::pair<string_q, string_q>(QE_L("Yakutsk Standard Time"),    QE_L("Asia/Yakutsk")),
        std::pair<string_q, string_q>(QE_L("Kamchatka Standard Time"),    QE_L("Asia/Kamchatka")),
    };

const std::map<string_q, string_q> QLocalTimeZone::WINDOWS_TZID_MAPPINGS (
                                        QLocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY,
                                        &QLocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY[0] + sizeof(QLocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY) / sizeof(QLocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY[0])
                                                                         );

#endif


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QLocalTimeZone::QLocalTimeZone()
{

#if   defined(QE_OS_WINDOWS)

    m_pTimeZone = QLocalTimeZone::GetCurrentTimeZoneOnWindows();

#elif defined(QE_OS_LINUX)

    m_pTimeZone = QLocalTimeZone::GetCurrentTimeZoneOnLinux();

#elif defined(QE_OS_MAC)

    m_pTimeZone = QLocalTimeZone::GetCurrentTimeZoneOnMac();

#endif

    
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

#ifdef QE_OS_WINDOWS

const QTimeZone* QLocalTimeZone::GetCurrentTimeZoneOnWindows()
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

    // Gets the time zone information from Windows
    DYNAMIC_TIME_ZONE_INFORMATION tzInfo;
    GetDynamicTimeZoneInformation(&tzInfo);

    // Converts the time zone key name to a Unicode string
    string_q strWindowsTimeZoneId(rcast_q(tzInfo.TimeZoneKeyName, i8_q*), 
                                  wcslen(tzInfo.TimeZoneKeyName) * 2U, // There are 2 chars in one wchar_t
                                  EQTextEncoding::E_UTF16LE);

    // Gets the equivalent time zone ID in the IANA/Olson database
    string_q strTimeZoneId = QLocalTimeZone::GetWindowsEquivalentTimeZoneId(strWindowsTimeZoneId);

    // Gets the time zone instance
    return SQTimeZoneFactory::GetTimeZoneById(strTimeZoneId);
}

const string_q QLocalTimeZone::GetWindowsEquivalentTimeZoneId(const string_q &strTimeZoneKeyName)
{
    std::map<string_q, string_q>::const_iterator itFoundId = QLocalTimeZone::WINDOWS_TZID_MAPPINGS.find(strTimeZoneKeyName);

    string_q strEquivalentId;

    if(itFoundId != QLocalTimeZone::WINDOWS_TZID_MAPPINGS.end())
    {
        strEquivalentId = itFoundId->second;
    }
    else
    {
        QE_ASSERT(false, "The Windows time zone key has no known equivalence");
        strEquivalentId = string_q::GetEmpty();
    }

    return strEquivalentId;
}

#elif defined(QE_OS_LINUX)

const QTimeZone* QLocalTimeZone::GetCurrentTimeZoneOnLinux()
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    
    static const char* TIME_ZONE_CONFIGURATION_FILE = "/etc/timezone";
    const QTimeZone* pTimeZone = null_q;
    
    // [TODO] Thund: Replace with QFileStream
    // This file exists on Ubuntu but it is not assured that it exists in other distributions
    std::ifstream file (TIME_ZONE_CONFIGURATION_FILE, std::ios::in|std::ios::binary|std::ios::ate);
    
    if (file.is_open())
    {
        // Loads the entire content of the file into a string
        file.seekg(0, std::ios::end);
        size_t uSize = file.tellg();
        char *szContents = new char[uSize];
        file.seekg(0, std::ios::beg);
        file.read(szContents, uSize);
        file.close();
        
        // The time zone name ends with a carriage return character
        static const string_q CARRIAGE_RETURN = "\n";
        
        string_q strTimeZoneId = szContents;
        int nLastCharPosition = strTimeZoneId.IndexOf(CARRIAGE_RETURN, EQComparisonType::E_BinaryCaseSensitive) - 1;
        pTimeZone = SQTimeZoneFactory::GetTimeZoneById(strTimeZoneId.Substring(0, nLastCharPosition));
        
        delete[] szContents;
    }
    else
    {
        QE_ASSERT(false, "The time zone could not be retrieved from the operative system configuration file");
    }
    
	return pTimeZone;
}

#elif defined(QE_OS_MAC)

const QTimeZone* QLocalTimeZone::GetCurrentTimeZoneOnMac()
{
    // [TODO] Thund: It is possible that localtime is not a link but a file. If this fails in the future,
    //               add the code to handle that situation (use S_ISLINK, lstat, etc.)
    
    static const unsigned int ENOUGH_LENGTH_FOR_TZ_ID = 256U;
    static const char* TIME_ZONE_CONFIGURATION_FILE = "/etc/localtime";
    static const char* TIME_ZONE_REAL_PATH = "/usr/share/zoneinfo/";
    static const unsigned int TIME_ZONE_REAL_PATH_LENGTH = 20U;
    
    const QTimeZone* pTimeZone = null_q;
    char szFilename[ENOUGH_LENGTH_FOR_TZ_ID];
 
    int nSize = readlink(TIME_ZONE_CONFIGURATION_FILE, szFilename, ENOUGH_LENGTH_FOR_TZ_ID);
    
    if (nSize > 0)
    {
        szFilename[nSize] = '\0';
        pTimeZone = SQTimeZoneFactory::GetTimeZoneById(szFilename + TIME_ZONE_REAL_PATH_LENGTH);
    }
    
    return pTimeZone;
}

#endif


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QTimeZone* QLocalTimeZone::Get() const
{
    return m_pTimeZone;
}


} //namespace Timing
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
