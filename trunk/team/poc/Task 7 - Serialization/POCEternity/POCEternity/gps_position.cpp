#include "gps_position.h"

// Método de de/serialización
void gps_position::xml_serialize( eternity::xml_archive &xml) 
{
	if (xml.is_loading())
	{
		xml.read("degrees", degrees, 0);
		xml.read("minutes", minutes, 0);
		xml.read("seconds", seconds, 0);
	}
	else
	{
		xml.write("degrees", degrees);
		xml.write("minutes", minutes);
		xml.write("seconds", seconds);
	}
}

void gps_position::bin_serialize( eternity::bin_archive &stream)
{
	if (stream.is_loading())
	{
		stream >> degrees;
		stream >> minutes;
		stream >> seconds;
	}
	else
	{
		stream << degrees;
		stream << minutes;
		stream << seconds;
	}
}