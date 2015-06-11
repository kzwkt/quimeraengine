# s11n #

## Descripción ##
Página oficial: [s11n](http://s11n.net/)

Librería de código abierto para serialización. Su autor, debido a una enfermedad, parece que ha abandonado el proyecto, por lo que de momento parece que está sin soporte.

La librería ofrece diversas opciones de serialización, siempre en modo texto:

  * compact (also called 51191011)
  * expat (IF s11n was built with libexpat support)
  * funtxt
  * funxml
  * parens
  * simplexml
  * wesnoth

No serializa en forma binaria. La serialización puede hacerse tanto de forma intrusiva (declarando dos operadores dentro de la clase, uno para serializar y otro para deserializar) como de forma no intrusiva.

Diseñada para entornos Linux, tiene bastantes problemas para ejecutarse en windows. Se ha extractado [Aquí](POCs11nPorta.md) el apartado de Windows de su [manual de portabilidad](http://s11n.net/download/libs11n-porting-guide-20070207.pdf).

Aunque no se ha conseguido generar una DLL que funcione para Windows, sí se ha conseguido generar una Prueba de Concepto que funciona con la restricción de incluir todo el código de la librería en el mismo proyecto que el código de ejemplo.

La Prueba de Concepto consiste en la serialización intrusiva de una clase sencilla:

## Declaración de la clase ##
```
#include <s11n.net/s11n/s11nlite.hpp> // s11nlite framework

// Clase que se va a serializar
class gps_position
{
	public:
		
		// Inicialización
		gps_position(){};
		gps_position(int d, int m, float s) : degrees(d), minutes(m), seconds(s) {}
		
		// Operador para serializar
		bool operator()( s11nlite::node_type & src ) const;

		// Operador para deserializar
		bool operator()( const s11nlite::node_type & dest );
		

	private:
		int degrees;
		int minutes;
		float seconds;
};

// Registro de la clase en la librería
#define S11N_TYPE gps_position
#define S11N_TYPE_NAME "gps_position"
#include <s11n.net/s11n/reg_s11n_traits.hpp>
```

## Implementación de la clase ##
```
#include "gps_position.h"

// Operador de serialización. 
bool gps_position::operator()( s11nlite::node_type & node ) const
{
        typedef s11n::node_traits<s11nlite::node_type> NT;
        NT::class_name( node, "gps_position" );
	NT::set( node, "Degrees", this->degrees );
	NT::set( node, "Minutes", this->minutes );
	NT::set( node, "Seconds", this->seconds );
	
	//Para serializar listas o vectores
        //s11n::list::serialize_list( node, "vector", this->m_vec );
    
	// Para serializar mapas
        //s11n::map::serialize_map( node, "themap", this->m_map );
    
        return true;
}

// Operador de deserialización
bool gps_position::operator()( const s11nlite::node_type & node )
{
        // now get our data:
        typedef s11n::node_traits<s11nlite::node_type> NT;
        this->degrees = NT::get( node, "Degrees", this->degrees);
        this->minutes = NT::get( node, "Minutes", this->minutes);
	this->seconds = NT::get( node, "Seconds", this->seconds);

	// Deserializar un vector o una lista
	//s11n::list::deserialize_list( node,  "vector", this->m_vec );
    
	//Deserializar un map
        //s11n::map::deserialize_map( node,  "themap", this->m_map );

        return true;
}
```

## Utilización ##
```
#include <s11n.net/s11n/s11nlite.hpp> // s11nlite framework
#include <s11n.net/s11n/micro_api.hpp> // minimalistic s11n API

// proxys para los tipos de datos usados
#include <s11n.net/s11n/proxy/std/map.hpp> // ... map
#include <s11n.net/s11n/proxy/pod/int.hpp> // ... int
#include <s11n.net/s11n/proxy/pod/float.hpp> // ... float
#include <s11n.net/s11n/proxy/pod/string.hpp> // ... string

#include "gps_position.h"

int main( void )
{
   
        s11nlite::serializer_class( "simplexml" ); // define output format
        try
        {
		gps_position p(25, 3, 35.6f);
		std::string myfile = "gps.s11n";

		// Serialización
		s11nlite::micro_api<gps_position> micro;
		micro.save( p, myfile );

		// Deserialización
		gps_position * q = s11nlite::load_serializable<gps_position>( myfile );
     
        }
        catch( const std::exception & ex )
        {
                std::cerr << "EXCEPTION: " << ex.what() << "\n";
                return 1;
        }
        return 0;
}
```