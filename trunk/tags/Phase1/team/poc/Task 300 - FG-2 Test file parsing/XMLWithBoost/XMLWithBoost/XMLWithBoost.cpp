// XMLWithBoost.cpp : Defines the entry point for the console application.
//

// EXAMPLE: http://akrzemi1.wordpress.com/2011/07/13/parsing-xml-with-boost/

#include "stdafx.h"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time.hpp>
#include <boost/foreach.hpp>

typedef boost::gregorian::date Date;

// STRUCTURE TO PARSE TO
struct Flight
{
    std::string  carrier;
    unsigned     number;
    Date         date;
    bool         cancelled;
};

typedef std::vector<Flight> Sked;

// DATE CONVERSION TOOLS
std::locale isoDateLocale() {
    typedef boost::date_time::date_facet<Date, char> tOFacet;
    typedef boost::date_time::date_input_facet<Date, char> tIFacet;

    std::locale loc;
    loc = std::locale( loc, new tIFacet("%Y-%m-%d") );
    loc = std::locale( loc, new tOFacet("%Y-%m-%d") );
    return loc;
}

class DateTranslator 
{
    std::locale locale_; // implementation detail

public:
    typedef std::string  internal_type;
    typedef Date         external_type;

    DateTranslator();
    boost::optional<external_type> get_value( internal_type const &v );
    boost::optional<internal_type> put_value( external_type const& v );
};

DateTranslator::DateTranslator()
{
    locale_ = isoDateLocale();
}

boost::optional<DateTranslator::external_type> 
DateTranslator::get_value( internal_type const& v )
{ 
    std::istringstream stream(v);
    stream.imbue(locale_);
    external_type vAns;
    if( stream >> vAns ) {
        return vAns;
    }
    else {
        return boost::none;
    }
}

boost::optional<DateTranslator::internal_type> 
DateTranslator::put_value(external_type const& v)
{ 
    std::ostringstream ans;
    ans.imbue(locale_);
    ans << v;
    return ans.str();
}


// MAIN FUNCTION - EXECUTES THE PARSING
Sked read( std::istream & is )
{
    DateTranslator tr;

    // populate tree structure pt
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(is, pt);

    // traverse pt
    Sked ans;
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("sked") ) {
        if( v.first == "flight" ) {
            Flight f;
            f.carrier = v.second.get<std::string>("carrier");
            f.number = v.second.get<unsigned>("number");
            f.date = v.second.get<Date>("date", tr);
            f.cancelled = v.second.get("<xmlattr>.cancelled", false);
            ans.push_back(f);
        }
    }

    return ans;
}

// MAIN
int _tmain(int argc, _TCHAR* argv[])
{
    std::ifstream inputFile;
    inputFile.open("XMLFile.xml", std::ios_base::in);
    
    Sked res = read(inputFile);
    
	return 0;
}

