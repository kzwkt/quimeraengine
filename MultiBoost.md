# Multihilo con Boost C++ #

## Descripción ##

Boost es un conjunto de bibliotecas de software libre y revisión por pares preparadas para extender las capacidades del lenguaje de programación C++. Su licencia, de tipo BSD, permite que sea utilizada en cualquier tipo de proyectos, ya sean comerciales o no. Extraído de: Wikipedia

La librería que nos interese se llama Thread, y aparece bajo el namespace boost::thread. La librería originalmente fue escrito y diseñado por William E. Kempf y actualmente lo lleva Anthony Williams. La versión usada en ésta prueba de concepto es la 1.44.

La clase boost::thread es el responsable de lanzar y manejar los threads. Cada objeto boost::thread representa un hilo simple de ejecución. Los objetos boost::thread no es copiable. Usa los interfaces que le proporciona el S.O. para la creación y el manejo.

## Creación de hilo ##

Un objteto boost::thread se crea pasandle una función o método que queremos ejecutarlo en un hilo. Existe varios método para ello que lo vamos a ver:
  * **`A Thread Function`** Estamos en el caso cuando queremos ejecutar una función en un hilo separado, para ello solamente es necesario pasar la función a lanzar en el constructor del hilo.
```
void funcion_a_ejecutar()
{
}

boost::thread  func_thread (funcion_a_ejecutar);
```

  * **`Function with Arguments`** Si queremos pasar parámetros a la función que se ejecutará en un hilo aparte. Se consigue añadiendo los parámetros al constructor del hilo.
```
void funcion_a_ejecutar(param_1, param_2)
{
}

boost::thread func_thread (funcion_a_ejecutar, param_1, param_2);
```

  * **`Functor`** Un functor sirve para encapsular una función que será llamada en el hilo en un objeto. La clase define un metodo especial sobrecargando la función **`operator()`** que será llamada cuando el functor sea llamada.
```
class Worker
{
 ..... // El constructor
  
 void operator() ()
 {
   // Tareas a realizar por la función
 }
 
}

int main ()
{
  Worker w(); 

  boost::thread workerThread(w);
  .....
}
```

  * **`Object method `** Con frecuencia es conveniente definir un objeto con un método de instancia que se ejecuta en su propio hilo. En primer lugar, tenemos que especificar el método que vamos a utilizar y através del operador & para pasar la dirección del método. El segundo parámetro tiene que ser el puntero del objeto en si. Detrás vendrá todos los parámetros necesarios para invocar al método.
```
  //Objeto Worker 
  Worker w(param1); 

  boost::thread workerThread (&Worker::metodo_a_invocar, &w, param1);
```

## Mecanismos de sincronización ##

Para evitar problemas de concurrencia en el acceso a recursos por parte de varios hilos de ejecución, se utilizan ciertos mecanismos:

  * **`Mutex`:** Es el típico candado de dos estados: abierto / cerrado.
  * **`Condition Variables`:** Proviene un mecanismo para que un thread espere la notificación por otro thread que una condición particular sea cierto. Un hilo crea un Mutex y luego llama a wait. Si la condición no es cierta sigue llamando a wait hasta que se cumpla la condición.

## Métodos estáticos de hilo ##

La clase Thread expone varios métodos estáticos que nos sirven para manipular el hilo desde del cual los llamamos:

  * **`current`:** Devuelve un Thread que encapsula el hilo actual.
  * **`sleep`:** Pausa la ejecución del hilo actual durante un tiempo determinado.
  * **`yield`:** Permite que la CPU en uso por el hilo actual sea usada por otros hilos.
  * **`currentTid`:** El identificador otorgado por el sistema operativo al hilo actual.
  * **`get_id`:** Devuelve el id del thread que se esta ejecutando.
  * **`interruption_point()`:** Verifica si el thread actual ha tenido alguna interrupción.
  * **`interruption_requested()`:** Devuelve true si la interrupción ha sido capturado en el thread actual, en otro caso falso.
  * **`interruption_enabled()`:** Devuelve true si la interrupción esta activada en el thread actual.
  * **`sleep()`:** Pausa la ejecución del hilo actual durante un tiempo determinado.
  * **`yield()`:** Permite que la CPU en uso por el hilo actual sea usada por otros hilos.
  * **`disable_interruption`:** Desactiva las interrupciones en el constructor y lo vuelve a activar en el destructor del thread.
  * **`restore_interruption`:** Devuelve el estado de las interrupciones que se guardó en el constructor.


## Grupo de thread ##

  * **`thread_group`:** thread\_group prevé una coleción de thread que están relacionados de alguna manera. Nuevo thread se pueden agregar al grupo con funciones miembro add\_thread y create\_thread.

## Código fuente de la Prueba de concepto ##
https://quimeraengine.googlecode.com/svn/team/poc/Task%208%20-%20Multithreading

## Enlaces de interés ##
  * [Web oficial de BOOST](http://www.boost.org/)
  * [Documentación de la sección de Threading](http://www.boost.org/doc/libs/1_44_0/doc/html/thread.html)