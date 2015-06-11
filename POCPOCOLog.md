# Logging con POCO #


# Introducción #

Bajo el core Foundation de POCO C++, nos encontramos el framework de Logging. Éste nos permite el control de logs de nuestra aplicación estableciendo prioridades, estrategias y formatos de salida para los mismos.

**Message**:
Se trata del mensaje a enviar mediante el objeto Logger a través de un canal con destino, por ejemplo, un fichero.
Namespace : _POCO:Message_
Include: _#include "Poco/Message.h"_

Un mensaje está compuesto por:
  * **Prioridad** (Priority): Consta de varios niveles:
    * PRIO\_FATAL (prioridad más alta)
    * PRIO\_CRITICAL
    * PRIO\_ERROR
    * PRIO\_WARNING
    * PRIO\_NOTICE
    * PRIO\_INFORMATION
    * PRIO\_DEBUG
    * PRIO\_TRACE (prioridad más baja)

  * **Origen** (Source): Describe el origen de un mensaje de log.

  * **Texto del mensaje** (Text): El mensaje a registrar por el log.

  * **Fecha y hora** (Timestamp): La fecha y hora en que se creó, con un máximo de precisión de microsegundos.

  * **Proceso e identificador de hilo** (PID & TID): El PID almacena el ID del proceso en el sistema. El TID almacena el número de serie del hilo actual. Ambos lo hacen en variables del tipo long.

  * **Parámetros** (Parameters): Un mensaje puede almacenar un número arbitrario de pares nombre-valor, también formados por cadenas arbitrarias. Se les hace referencia mediante un formato y a través de  un operador de índice.

# Declaración #

_POCO:: Logger_ será nuestra clase de partida para el control de logging una vez añadida la cabecera correspondiente: #include "Poco/Logger.h". Cada _logger_ tiene un canal asociado, mediante el cual ofrece el mensaje al destino (un archivo, por ejemplo).

Declarando un loger:
```
#include "Poco/Logger.h"
using Poco::Logger;
int main(int argc, char** argv)
{
Logger& logger = Logger::get("TestLogger");
logger.information("This is an informational message");
logger.warning("This is a warning message");
return 0;
}
```

Cada _logger_ está conectado a un _channel_, el cual está encargado de entregar el mensaje a su destino.
Namespace: Poco::ConsoleChannel
Archivo de cabecera: #include "Poco/ConsoleChannel.h"

Declaración de un log para escritura en un archivo:
```
#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

using Poco::Logger;
using Poco::FileChannel;
using Poco::AutoPtr;

int main(int argc, char** argv)
{
   AutoPtr<FileChannel> pChannel(new FileChannel);
   pChannel->setProperty("path", "sample.log");
   pChannel->setProperty("rotation", "2 K");
   pChannel->setProperty("archive", "timestamp");

   Logger::root().setChannel(pChannel);

   Logger& logger = Logger::get("TestLogger"); // inherits root channel

   for (int i = 0; i < 100; ++i)
      logger.information("Testing FileChannel");

return 0;
}
```


**Canales asíncronos.**
_Poco::AsyncChannel_ permite ejecutar un canal en un hilo distinto. Los mensajes son almacenados en una cola FIFO, a dónde los irá a extraer cada hilo para enviarlos a otro canal.

```
#include "Poco/Logger.h"
#include "Poco/AsyncChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/AutoPtr.h"

using Poco::Logger;
using Poco::AsyncChannel;
using Poco::ConsoleChannel;
using Poco::AutoPtr;

int main(int argc, char** argv)
{
   AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
   AutoPtr<AsyncChannel> pAsync(new AsyncChannel(pCons));

   Logger::root().setChannel(pAsync);

   Logger& logger = Logger::get("TestLogger");

   for (int i = 0; i < 10; ++i)
      logger.information("This is a test");

   return 0;
}
```


_Poco::SplitterChannel_ reenvía un mensaje a uno o varios de los demás canales.
```

#include "Poco/Logger.h"
#include "Poco/SplitterChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/SimpleFileChannel.h"
#include "Poco/AutoPtr.h"

using Poco::Logger;
using Poco::SplitterChannel;
using Poco::ConsoleChannel;
using Poco::SimpleFileChannel;
using Poco::AutoPtr;

int main(int argc, char** argv)
{
   AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
   AutoPtr<SimpleFileChannel> pFile(new SimpleFileChannel("test.log"));
   AutoPtr<SplitterChannel> pSplitter(new SplitterChannel);
   pSplitter->addChannel(pCons);
   pSplitter->addChannel(pFile);

   Logger::root().setChannel(pSplitter);
   Logger::root().information("This is a test");

   return 0;
}
```

_Poco::LogStream_ proporciona una interfaz ostream a Logger, mediante la cabecera _#include "Poco/LogStream.h"_. También consta de prioridades al igual que Message (ver documentación para detalles).

```
#include "Poco/LogStream.h"
#include "Poco/Logger.h"

using Poco::Logger;
using Poco::LogStream;

int main(int argc, char** argv)
{
   Logger& logger = Logger::get("TestLogger");
   LogStream lstr(logger);

   lstr << "This is a test" << std::endl;

   return 0;
}
```

_Poco:: FormattingChannel_ y _Poco:: Formatter_ son responsables del formato de mensajes del Logger. El primero pasa cada mensaje que recibe a través de un _Poco:: Formatter_ , antes de propagar el mensaje al canal siguiente. Archivos de cabecera:
_#include "Poco/FormattingChannel.h"_  y  _#include "Poco/Formatter.h"_.

_Poco:: PatternFormatter_ da formato a mensajes de acuerdo a un patrón al estilo printf. Archivo de cabecera: _# Include "Poco / PatternFormatter.h"_

```
#include "Poco/ConsoleChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"

using Poco::ConsoleChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::Logger;
using Poco::AutoPtr;

int main(int argc, char** argv)
{
   AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
   AutoPtr<PatternFormatter> pPF(new PatternFormatter);
   pPF->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
   AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pCons));

   Logger::root().setChannel(pFC);
   Logger::get("TestChannel").information("This is a test");

   return 0;
}
```


# Rendimiento #
  * El nombre del Logger es una clave, de modo que cuanto más largo sea éste, más afectará a las operaciones de búsqueda.
  * Evitar llamar frecuentemente Logger::get(). Es mucho mejor llamarlo una vez por cada logger que se vaya a utilizar y, a continuación, almacenar la referencia al registro para su uso posterior.
  * El rendimiento del logging depende de la cantidad de canales a utilizar. El rendimiento de éstos es altamente dependiente del sistema.

Para más detalles de rendimiento consultar el manual de referencia.



# Páginas web de interés #
  * [Descarga de POCO](http://sourceforge.net/projects/poco/files/sources/poco-1.3.6/poco-1.3.6p2.zip/download)

  * [POCO Logging](http://pocoproject.org/slides/110-Logging.pdf)

  * [POCO](http://pocoproject.org/index.html)