# Loogging con Boost #

## Descripción ##

Boost es un conjunto de bibliotecas de software libre y revisión por pares preparadas para extender las capacidades del lenguaje de programación C++. Su licencia, de tipo BSD, permite que sea utilizada en cualquier tipo de proyectos, ya sean comerciales o no. Extraído de: Wikipedia.

La librería que nos interesa se llama Logging, y aparece bajo el namespace boost::logging.


## Declaración ##

Declaración de un log, sin niveles, para una aplicación simple sin usar un thread separado para el logging:
```
#ifndef __LOGGING_HPP__
#define __LOGGING_HPP__

#include <boost/logging/format_fwd.hpp>

using namespace boost::logging;
using namespace boost::logging::scenario::usage;

typedef use<
    filter_::change::single_thread, // how often does the filter change?
    filter_::level::no_levels,      // does the filter use levels?
    logger_::change::single_thread, // how often does the logger change?
    logger_::favor::correctness     // what does the logger favor?
  > finder;

BOOST_DECLARE_LOG_FILTER( g_log_filter, finder::filter )
BOOST_DECLARE_LOG( g_log, finder::logger )

#define L_ BOOST_LOG_USE_LOG_IF_FILTER( g_log(), g_log_filter()->is_enabled() )

void initialize_logs();

#endif // __LOGGING_HPP__
```


## Inicialización ##
```
#include "logging.hpp"
#include <boost/logging/format_ts.hpp>
#include <boost/thread/xtime.hpp>

BOOST_DEFINE_LOG_FILTER( g_log_filter, finder::filter )

BOOST_DEFINE_LOG( g_log, finder::logger )

void initialize_logs()
{
  g_log()->writer().add_formatter( formatter::idx(), "[%] "  );
  g_log()->writer().add_formatter( formatter::time("$hh:$mm.$ss ") );
  g_log()->writer().add_formatter( formatter::append_newline() );

  typedef detail::flag<destination::file_settings> flag;
  destination::file_settings file_settings;
  file_settings.initial_overwrite = flag::t<bool>( &file_settings, true );
  g_log()->writer().add_destination(
      destination::file( "app_debug.txt", file_settings )
    );
  g_log()->writer().add_destination(
      destination::cerr
    );

  g_log()->turn_cache_off(); // for showing output immediately
  g_log()->mark_as_initialized();
}
```


## Formatos de salida y definiciones ##
Namespace: boost::logging::formatter Namespace Reference => Formatter is a manipulator. It allows you to format the message before writing it to the destination(s).
```
struct      msg_type
     what is the default type of your string, in formatter_base ? See BOOST_LOG_FORMAT_MSG More...
struct      base
     What to use as base class, for your formatter classes. More...
struct      class_
     Use this when implementing your own formatter class. More...
struct      idx_t
     prefixes each message with an index. More...
struct      append_newline_t
     Appends a new line. More...
struct      append_newline_if_needed_t
     Appends a new line, if not already there. More...
struct      high_precision_time_t
     Prefixes the message with a high-precision time (. You pass the format string at construction. More...
struct      named_spacer_t
     Allows you to contain multiple formatters, and specify a spacer between them. You have a spacer string, and within it, you can escape your contained formatters. More...
struct      spacer_t
     Prepends some info, and appends some info to an existing formatter. More...
struct      uses_tag
     Specifies that a formatter class handles a certain tag class. More...
struct      thread_id_t
     Writes the thread_id to the log. More...
struct      time_t
     Prefixes the message with the time. You pass the format string at construction. More...
struct      time_strf_t
     Prefixes the message with the time, by using strftime function. You pass the format string at construction. More...

Namespaces
namespace      convert
     Allows format convertions - In case you`'`re using a formatter that does not match your string type.
namespace      tag
     Classes that process the tags coming with the library.

Typedefs
typedef
boost::logging::manipulator::implement_op_equal     implement_op_equal
typedef
boost::logging::manipulator::is_generic     is_generic
typedef idx_t     idx
     idx_t with default values. See idx_t
typedef append_newline_t     append_newline
     append_newline_t with default values. See append_newline_t
typedef
append_newline_if_needed_t     append_newline_if_needed
     append_newline_if_needed_t with default values. See append_newline_if_needed_t
typedef
high_precision_time_t     high_precision_time
     high_precision_time_t with default values. See high_precision_time_t
typedef named_spacer_t     named_spacer
     named_spacer_t with default values. See named_spacer_t
typedef thread_id_t     thread_id
     thread_id_t with default values. See thread_id_t
typedef time_t     time
     time_t with default values. See time_t
typedef time_strf_t     time_strf
     time_strf_t with default values. See time_strf_t

Functions
template<class original_formatter>
detail::find_spacer
< original_formatter >
::type     spacer (const original_formatter &fmt, const char_type *format_str)
```


## Logging por prioridades ##

```
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
    L_(debug) << "Debug logger (lvl default)" << i++;
    L_(info) << "Info logger " << i++;
   L_(warning) << "Warning logger " << i++;
   L_(error) << "Error logger " << i++;
   L_(fatal) << "Fatal logger " << i++;

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
```

## Logging personalizado derivando una clase de la librería. ##
```
Creating your own formatter and/or destination class(es)
To create your formatter class, you need to derive from formatter::class_. You will need to implement operator()(arg_type)
(arg_type is the argument from your formatter base class)

// milliseconds since start of the program
struct ms_since_start : formatter::class_<ms_since_start, formatter::implement_op_equal::no_context> {
    time_t m_start;
    ms_since_start : m_start( time(0) ) {}

    // param = std::string& 
    // (in other words, it's the arg_type from your formatter base class)
    void operator()(param msg) const {
        std::ostringstream out;
        time_t now = time(0);
        out << "[" << (now-start) << "] ";
        msg = out.str() + msg;
    }
};

To create your destination class, you need to derive from destination::class_. You will need to implement operator()(arg_type)
(arg_type is the argument from your destination base class)

struct to_hwnd : destination::class_<to_hwnd, destination::implement_op_equal::has_context> {
    HWND h;
    to_hwnd(HWND h) : h(h) {}

    bool operator==(const to_hwnd& other) { return h == other.h; }

    // param = const std::string& 
    // (in other words, it's the arg_type from your destination base class)
    void operator()(param msg) const {
        ::SetWindowText(h, msg.c_str());
    }
};
```


## Niveles de log ##
Nos indican la prioridad con la que se mostrarán los errores predominando el más restrictivo. Se muestra su definición:
```
namespace level {
    /** the higher the level , the more critical the error */
    typedef unsigned int type;

    enum {
        disable_all = (type)-1,
        enable_all = 0,
        debug = 1000,
        info = 2000,
        warning = 3000,
        error = 4000,
        fatal = 5000
    };
```


## Creación de niveles ##
```
/*Yes, you can create your own levels. From what I understand, you don't actually want levels, you want some sort of flag that is just on or off.
If for a given value, the flag matches that value, you want to do logging.

First, you can create your own filter class to do whatever you want.

In your case, I guess you want something like this:
*/
struct flag_filter {
int flag;
flag_filter(int flag = 0) : flag(flag) {}
bool is_enabled(int f) { return f == flag; }
};

// in your code, some constants
const int request = 1;
const int session = 2;
const int answer = 3;
...

// your macro

... whatever log_type might be
BOOST_DEFINE_LOG(g_l, log_type)
BOOST_DEFINE_LOG_FILTER(g_log_filter, flag_filter )

#define L_(f) BOOST_LOG_USE_LOG_IF_FILTER(g_l(), g_log_filter()->is_enabled(f) )

// in your code
L_(request) << "new request"...;
L_(session) << "new user" << username << ...
L_(answer) << "answering to user" << ...
```


# Multithreading #
El logging de Boost nos permite el multithreading, a continuación se detallan espacios de nombres y su función:
  * _boost::logging::scenario::usage::logger`_`::favor::correctness_: All messages will be logged. This is the default for multi-threaded application.
  * _boost::logging::scenario::usage::logger`_`::change::often< cache\_period\_secs >_: Optimize for often change. Does per-thread caching. At a given period, it re-synchronizes. This is the default, for multi-threaded applications.
  * _boost::logging::scenario::usage::logger`_`::change::set\_once\_when\_multiple\_threads_: Set only once, when there could be multiple thread running.
  * _boost::logging::scenario::usage::filter`_`::change::set\_once\_when\_multiple\_threads_: Set only once, when there could be multiple thread running.
  * _boost::logging::lock\_resource\_finder::tss\_once\_init< mutex >_: Allows you to initialize this resource once even if multiple threads are running. Then, all threads will use the initialized value.
  * _boost::logging::scenario::ts::filter`_`_: Filter thread-safety.
  * _boost::logging::writer::threading::no`_`ts_:Not thread-safe.
  * _boost::logging::writer::on\_dedicated\_thread< msg\_type, base\_type >_: Performs all writes on a dedicated thread - very efficient and thread-safe.
  * _boost::logging::writer::threading::on\_dedicated\_thread_:Thread-safe write on a dedicated thread. Very efficient. Formatting & writing to destinations happens on the dedicated thread.

Para ver los miembros en hilos exclusivos, ver el manual en http://torjo.com/log2/doc/html/annotated.html