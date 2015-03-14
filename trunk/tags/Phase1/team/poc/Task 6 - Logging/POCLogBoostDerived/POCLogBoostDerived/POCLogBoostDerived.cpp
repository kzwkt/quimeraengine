/*******************  POC de Logging derivando clases **************************

	En principio funciona así. Hay dos tipos de "Manipulators", que funcionan igual,
	aunque cada uno tiene su template: Formatters y Destinations. Crear tus propios
	manipulators, tienes que derivarlos de formatter::class_ o de destination::class_.

	Dentro de tu clase, tienes que definir el operator (), pasandole (param msg) para que 
	le concatene lo que tu quieras.  msg es el mensaje que va a ser escrito en el logger:

	void operator()(param msg) const {
		...

		msg = loquesea + msg;
	}

	El tipo param es un std::string&

	Para poder usar después add_formatter o add_destination, hay que definir el logger como
	de tipo logger_format_write:

	typedef  boost::logging::logger_format_write<> logger_type;
	...

	BOOST_DEFINE_LOG(g_l, logger_type)

	Luego ya es crear una instancia de tu clase y añadir el formater.

	ms_since_start p;
	g_l()->writer().add_formatter(p);

	Los formatters aparecen en orden inverso al orden en que se añaden, osea que el primero que se
	añade aparece justo antes del mensaje, y el último aparece al principio de la línea.


*******************************************************************************/

//Forzamos a que coja librerias dinamicas y no estáticas 
//(esto depende de como lo hayas intalado)
#define BOOST_DYN_LINK 1

//Sólo es necesario incluir esta cabecera. Según escenarios se deberán incluir
//otras, viene bastante claro en la documentación
#include <boost/logging/format/named_write.hpp>
#include <time.h>

using namespace boost::logging;

//Abreviatura
typedef  boost::logging::logger_format_write<> logger_type;

//Macro para generar la salida
#define L_(lvl) BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_log_level(), lvl )

//Macro para apuntar al controlador de niveles
BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
//Macro para definir el logger
BOOST_DEFINE_LOG(g_l, logger_type)

//Formatter derivado: milisegundos desde que se inició el programa hasta el registro en el log
struct ms_since_start : formatter::class_<ms_since_start, formatter::implement_op_equal::no_context> 
{
	clock_t c_start;

	ms_since_start() : c_start( clock() * CLK_TCK) {};

    // param = std::string&
    // (in other words, it's the arg_type from your formatter base class)
    void operator()(param msg) const 
	{
        std::ostringstream out;

		clock_t c_end = clock() * CLK_TCK;
		clock_t resta = (clock_t)((c_end - c_start)*0.001f);

		out << "[" << (resta) << "] ";
        msg = out.str() + msg;
    }
};

//Función para crear un delay entre escrituras en el log
void do_sleep(clock_t ms) 
{
	clock_t t1, t2;

	t1 = clock()*CLK_TCK;
	t2 = clock()*CLK_TCK;
	
	while (t2 - t1 < ms*1000)
		t2 = clock()*CLK_TCK;

}

//logger
void test_mul_levels_one_logger() 
{
	//Instancia del formatter derivado
	ms_since_start p;
		
	// Añadimos varios formatters, algunos "named" y el derivado, y un destination
	g_l()->writer().add_formatter(p);
	g_l()->writer().add_formatter( formatter::idx(), "[%] "  );
	g_l()->writer().add_formatter( formatter::high_precision_time("$hh:$mm.$ss.$mili ") );
    g_l()->writer().add_formatter( formatter::append_newline() );
    g_l()->writer().add_destination( destination::file("out.txt") );

	//Marcamos el logger para que escriba en él, si no lo hacemos difiere la escritura hasta
	//que encuentre esta llamada o acabe el programa (creo, tb puede ser cuando salga del dominio)
    g_l()->mark_as_initialized();

	//Le damos un numerito para añadir a la entrada del log 
    int i = 1;

	//Voy añadiendo entradas especificando el nivel al que pertenece
	//Primero con level por defecto
    L_(debug) << "Debug logger (lvl default) " << i++;
    L_(info) << "Info logger (lvl default) " << i++;
	L_(warning) << "Warning logger (lvl default) " << i++;
	L_(error) << "Error logger (lvl default) " << i++;
	L_(fatal) << "Fatal logger (lvl default) " << i++;

	//Delay
	do_sleep(1000);

   	//Definimos level debug
	g_log_level()->set_enabled(level::debug);
    L_(debug) << "Debug logger (lvl debug) " << i++;
    L_(info) << "Info logger (lvl debug) " << i++;
	L_(warning) << "Warning logger (lvl debug) " << i++;
	L_(error) << "Error logger (lvl debug) " << i++;
	L_(fatal) << "Fatal logger (lvl debug) " << i++;

	do_sleep(1000);

    //Definimos level info
	g_log_level()->set_enabled(level::info);
    L_(debug) << "Debug logger (lvl info) " << i++;
    L_(info) << "Info logger (lvl info) " << i++;
	L_(warning) << "Warning logger (lvl info) " << i++;
	L_(error) << "Error logger (lvl info) " << i++;
	L_(fatal) << "Fatal logger (lvl info) " << i++;

	do_sleep(1000);

	//Definimos level warning
	g_log_level()->set_enabled(level::warning);
    L_(debug) << "Debug logger (lvl warning) " << i++;
    L_(info) << "Info logger (lvl warning) " << i++;
	L_(warning) << "Warning logger (lvl warning) " << i++;
	L_(error) << "Error logger (lvl warning) " << i++;
	L_(fatal) << "Fatal logger (lvl warning) " << i++;

	do_sleep(1000);

	//Definimos level error
	g_log_level()->set_enabled(level::error);
    L_(debug) << "Debug logger (lvl error) " << i++;
    L_(info) << "Info logger (lvl error) " << i++;
	L_(warning) << "Warning logger (lvl error) " << i++;
	L_(error) << "Error logger (lvl error) " << i++;
	L_(fatal) << "Fatal logger (lvl error) " << i++;

	do_sleep(1000);

	//Definimos level fatal
	g_log_level()->set_enabled(level::fatal);
    L_(debug) << "Debug logger (lvl fatal) " << i++;
    L_(info) << "Info logger (lvl fatal) " << i++;
	L_(warning) << "Warning logger (lvl fatal) " << i++;
	L_(error) << "Error logger (lvl fatal) " << i++;
	L_(fatal) << "Fatal logger (lvl fatal) " << i++;
}

int main() {
	//Multiples niveles/prioridades en un solo logger, con formatter derivado
    test_mul_levels_one_logger();
}



