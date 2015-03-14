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
