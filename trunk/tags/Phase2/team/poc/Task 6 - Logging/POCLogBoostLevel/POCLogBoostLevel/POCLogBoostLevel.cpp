/*******************  POC de Logging por prioridades **************************

	En principio funciona así. Hay estos niveles (prioridades) por defecto:
    
        - debug (menor nivel/prioridad),
        - info,
        - warning ,
        - error ,
        - fatal (mayor nivel/prioridad)

	Sujetos a estas notas:

		Depending on which level is enabled for your application, some messages will 
		reach the log: those messages having at least that level. For instance, 
		if info level is enabled, all logged messages will reach the log.
		If warning level is enabled, all messages are logged, but the warnings. 
		If debug level is enabled, messages that have levels debug, error, fatal will be logged.

	Es decir, en principio tu defines el nivel mínimo de los niveles que se loggan.
*******************************************************************************/

//Forzamos a que coja librerias dinamicas y no estáticas 
//(esto depende de como lo hayas intalado)
#define BOOST_DYN_LINK 1

//Sólo es necesario incluir esta cabecera. Según escenarios se deberán incluir
//otras, viene bastante claro en la documentación
#include <boost/logging/format/named_write.hpp>

//Abreviatura
typedef boost::logging::named_logger<>::type logger_type;

//Macro para generar la salida
#define L_(lvl) BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_log_level(), lvl )

//Macro para apuntar al controlador de niveles
BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
//Macro para definir el logger
BOOST_DEFINE_LOG(g_l, logger_type)

void test_mul_levels_one_logger() {
	//Creamos el formato del logger y especificamos la salida
    // formatting    : time [idx] message \n
    // destinations  : console, file "out.txt" and debug window
    g_l()->writer().write("%time%($hh:$mm.$ss.$mili) [%idx%] |\n", "cout file(out.txt) debug");
    g_l()->mark_as_initialized();

	//Le damos un numerito para añadir a la entrada del log 
	//No es el indice, que va expresado en el formato como [%idx%]
    int i = 1;

	//Voy añadiendo entradas especificando el nivel al que pertenece
	//Primero con level por defecto
    L_(debug) << "Debug logger (lvl default) " << i++;
    L_(info) << "Info logger (lvl default) " << i++;
	L_(warning) << "Warning logger (lvl default) " << i++;
	L_(error) << "Error logger (lvl default) " << i++;
	L_(fatal) << "Fatal logger (lvl default) " << i++;

    using namespace boost::logging;
	//Definimos level debug
	g_log_level()->set_enabled(level::debug);
    L_(debug) << "Debug logger (lvl debug) " << i++;
    L_(info) << "Info logger (lvl debug) " << i++;
	L_(warning) << "Warning logger (lvl debug) " << i++;
	L_(error) << "Error logger (lvl debug) " << i++;
	L_(fatal) << "Fatal logger (lvl debug) " << i++;

    //Definimos level info
	g_log_level()->set_enabled(level::info);
    L_(debug) << "Debug logger (lvl info) " << i++;
    L_(info) << "Info logger (lvl info) " << i++;
	L_(warning) << "Warning logger (lvl info) " << i++;
	L_(error) << "Error logger (lvl info) " << i++;
	L_(fatal) << "Fatal logger (lvl info) " << i++;

	//Definimos level warning
	g_log_level()->set_enabled(level::warning);
    L_(debug) << "Debug logger (lvl warning) " << i++;
    L_(info) << "Info logger (lvl warning) " << i++;
	L_(warning) << "Warning logger (lvl warning) " << i++;
	L_(error) << "Error logger (lvl warning) " << i++;
	L_(fatal) << "Fatal logger (lvl warning) " << i++;

	//Definimos level error
	g_log_level()->set_enabled(level::error);
    L_(debug) << "Debug logger (lvl error) " << i++;
    L_(info) << "Info logger (lvl error) " << i++;
	L_(warning) << "Warning logger (lvl error) " << i++;
	L_(error) << "Error logger (lvl error) " << i++;
	L_(fatal) << "Fatal logger (lvl error) " << i++;

	//Definimos level fatal
	g_log_level()->set_enabled(level::fatal);
    L_(debug) << "Debug logger (lvl fatal) " << i++;
    L_(info) << "Info logger (lvl fatal) " << i++;
	L_(warning) << "Warning logger (lvl fatal) " << i++;
	L_(error) << "Error logger (lvl fatal) " << i++;
	L_(fatal) << "Fatal logger (lvl fatal) " << i++;
}

int main() {
	//Multiples niveles/prioridades en un solo logger
    test_mul_levels_one_logger();
}



