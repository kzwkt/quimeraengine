# Multihilo con POCO C++ #

## Descripción ##

POCO C++ dedica una sección de su librería Foundation, bajo el nombre de Threading, a la manipulación de hilos, haciendo muy sencillo el trabajo con los mismos y permitiendo la abstracción del sistema operativo. Soporta el sistema de hilos tradicional de Windows y el estándar [POSIX](http://es.wikipedia.org/wiki/POSIX), seguido por Linux, Mac OS X y Windows NT en adelante.

## Encapsulación de hilos ##

La clase principal que simboliza un hilo es **Thread**. Está compuesta por:

  * Un nombre opcional.
  * La prioridad en el sistema operativo.
  * Un ID único en la aplicación (no confundir con el otorgado por el sistema operativo).
  * Una pila, cuyo tamaño es configurable.
  * Un objeto que encapsula una función asignada al hilo.

No es posible asignar la referencia de una función directamente al Thread, sino que hay que encapsularla. Para ello hay distintas formas de proceder:

  * **`Runnable`:** Se trata de una clase que encapsula la llamada a una función en otro hilo. Para utilizarla hay que heredar de ella e implementar el método "run", que será ejecutado en otro hilo cuando se usen las instancias de la clase como parámetros de Thread:start.
  * **`RunnableAdapter`:** Es la versión no-intrusiva para encapsular un método de una clase ya implementada. Durante su creación especificamos la instancia de un objeto y una refrencia a uno de sus métodos, que será invocado en otro hilo mediante Thread::start.
  * **`ActiveMethod / ActiveResult`:** Se usan conjuntamente para encapsular la llamada a un método con un parámetro y que devuelva un resultado. `ActiveResult` contendrá el resultado o la excepción, según el caso, en cuanto el hilo lanzado termine. Normalemnte se espera a que ello ocurra antes de proseguir mediante el método "wait".
  * **`Activity`:** En lugar de utilizar Thread::start para invocar un determinado método en otro hilo, ofrece su propio método, de manera que es la clase misma quien ordena la ejecución. No necesita ser heredada.

## Mecanismos de sincronización ##

Para evitar problemas de concurrencia en el acceso a recursos por parte de varios hilos de ejecución, se utilizan ciertos mecanismos:

  * **`Mutex`:** Es el típico candado de dos estados: abierto / cerrado.
  * **`FastMutex`:** Igual que Mutex, pero no recomendado para uso en funciones recursivas.
  * **`Semaphore`:** Implementa un semáforo, que limita la cantidad de hilos que acceden a una zona de código determinada. Cada vez que se llama a "wait", se decrementa un contador interno y cuando se llama a "set" se incrementa. Si el contador es inferior a cero, el hilo espera a que vuelva a ser positivo.
  * **`ScopedMutex`:** Se usa en conjunto con un Mutex. Cuando se crea, bloquea el mutex y cuando se destruye lo desbloquea. Es ideal debido a que siempre liberará el mutex, aunque ocurra un error en la función. Se deduce que en la gran mayoría de los casos se declarará como variable local.
  * **`Condition`:** Dado un conjunto de hilos paralelos, es posible su sincronización de la siguiente manera: Un hilo crea un Mutex y lo introduce en la Condition (que utiliza una pila en su interior) mediante el método "wait"; con esto el mutex queda bloqueado y espera a que otro hilo lo desbloquee; cuando otro hilo llama al método "sygnal", el último mutex introducido se desbloquea, y el hilo que lo declaró puede continuar. Es posible desbloquear todos los mutex de la pila con el método "broadcast".

## Gestión de hilos ##

  * **`ThreadPool`:** Se trata de un depósito de instancias de Thread ya alojadas en memoria, al cual se le pide la ejecución de objetos Runnable y derivados, de manera que, internamente, utiliza el primer Thread que encuentre libre para lanzar el hilo de ejecución.

## Métodos estáticos de hilo ##

La clase Thread expone varios métodos estáticos que nos sirven para manipular el hilo desde del cual los llamamos:

  * **`current`:** Devuelve un Thread que encapsula el hilo actual.
  * **`sleep`:** Pausa la ejecución del hilo actual durante un tiempo determinado.
  * **`yield`:** Permite que la CPU en uso por el hilo actual sea usada por otros hilos.
  * **`currentTid`:** El identificador otorgado por el sistema operativo al hilo actual.

## Clases de ayuda ##

  * **`ErrorHandler`:** Actúa como un repositorio común de excepciones al que enviar información de errores ocurridos en todos los hilos (las excepciones ocurridas en un hilo no saltan al principal, el hilo muere y nada más), de manera que pueda ser gestionado por el hilo principal o por cualquier otro.

**Nota:** Todas las clases descritas residen en el namespace "Poco".

## Código fuente de la Prueba de concepto ##
https://quimeraengine.googlecode.com/svn/team/poc/Task%208%20-%20Multithreading

## Enlaces de interés ##
  * [Web oficial de POCO](http://pocoproject.org/)
  * [Documentación de la sección de Threading](http://pocoproject.org/slides/130-Threads.pdf)