# Eternity 4.0 #

## Descripción ##
Sencilla librería para serialización. Admite serialización binaria, xml y MFC, solamente intrusiva.

Está sin soporte desde hace en torno a un año.

Página oficial: [http://sourceforge.net/projects/eternity-it/](http://sourceforge.net/projects/eternity-it/)

Se deja un extracto de la guía oficial, clara y concisa, en esta [página](POCEternityManual.md).

La [Prueba de Concepto](http://code.google.com/p/quimeraengine/source/browse/#svn/team/poc/Task%207%20-%20Serialization/POCEternity) consiste en la de/serialización de una clase sencilla:

## Declaración de la clase ##
```
#include "eternity\eternity.hpp"

// Clase que se va a serializar
class gps_position
{
        public:
                
                // Inicialización
                gps_position(){};
                gps_position(int d, int m, float s) : degrees(d), minutes(m), seconds(s) {}
                
		// Métodos de de/serialización
                void xml_serialize( eternity::xml_archive &xml ) ;
		void bin_serialize( eternity::bin_archive &stream ) ;


        private:
                int degrees;
                int minutes;
                float seconds;
};
```

## Implementación de la clase ##
```
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
```

## Utilización ##
```
#include "gps_position.h"

int main( void )
{
   
        try
        {
                gps_position p(25, 3, 35.6f);
                std::string myfile = "gps_position.xml";
		eternity::xml_archive xml;
				
                // Serialización xml
		xml.open(myfile, eternity::archive::store);
		p.xml_serialize(xml);
		xml.close();

                // Deserialización xml
		gps_position q;

		xml.open(myfile, eternity::archive::load);
		q.xml_serialize(xml);
		xml.close();

		eternity::file_archive bin;
		myfile = "gps_position.bin";

		// Serialización binaria
		bin.open(myfile, eternity::archive::store);
		p.bin_serialize(bin);
		bin.close();

                // Deserialización binaria
		gps_position r;

		bin.open(myfile, eternity::archive::load);
		r.bin_serialize(bin);
		bin.close();
        }
        catch( const std::exception & ex )
        {
                std::cerr << "EXCEPTION: " << ex.what() << "\n";
                return 1;
        }
        return 0;
}
```