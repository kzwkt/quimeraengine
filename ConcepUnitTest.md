# Conceptos básicos acerca del Unit Testing #

## Qué es ##

La traducción literal es prueba unitaria y, como su nombre indica, se trata de probar una y sólo una cosa. Esto no quiere decir que debamos ejecutar sólo una cosa, o que sólo verifiquemos un número; quiere decir que tengamos en mente un único objetivo a la hora de planear la prueba. En términos más concretos, un _unit test_ podría consistir en comprobar que cuando paso un vector A(1, 2, 3) a la función "Suma" de otro vector B(4, 5, 6), el resultado será C(5, 7, 9). Entiéndase como resultado una respuesta esperada, ni siquiera tiene que ser un valor de retorno, sino un cambio en alguna parte que nos permita saber que la maquinaria se movió de la forma planificada.
Para que una prueba unitaria sea lo más concreta, mantenible, legible y fiable, debe tener unas características:

  * **Independiente**: Deben existir las mínimas dependencias posibles, esto es, cuantos menos elementos reales participen mejor. Lo ideal es que sólo interviniera la clase o función que estamos testeando, pero esto no siempre es posible, por lo que hay que evitar implicar a muchas otras clases para conseguir la finalidad del test. De lo contrario, posiblemente estemos haciendo algo mal (no está clara la finalidad, o el diseño de las clases es demasiado acoplado). La independencia también se refiere a los medios físicos, es decir, hay que evitar las lecturas de disco o de señales de red, que pueden relentizar indefinidamente el test o hacerlo fallar por causas ajenas a la funcionalidad; para ello se utilizan los _mocks_, que serán explicados más adelante. Tampoco cabe depender de la hora actual, ya que siempre será distinta. Inevitablemente, a veces deberemos confiar en que las partes de las que dependemos funcionan correctamente (estas deberán tener sus propios tests).
  * **Repetible**: Un _unit test_ debe poder ser repetido tantas veces como queramos sin que ello afecte al resultado. Si el test depende de datos precalculados, estos deben ser siempre los mismos al inicio del test. Esto implica el cálculo anterior o la restauración posterior de los mismos. Si se crea una fila en una BD, esta deberá ser borrada al finalizar la prueba. Aquí también influye la independencia.
  * **Estructurada**: Las pruebas deberían seguir siempre el mismo patrón definido, teniendo, como mínimo 3 fases: Preparación, Ejecución y Verificación. Durante la Preparación se definen los datos de entrada y se calculan; en la ejecución tiene lugar el proceso del cual queremos obtener un resultado esperado; en la verificación, ese resultado es comparado con los valores que se esperan y se lanzan los mensajes notificando el éxito o fracaso de la prueba.
  * **Documentada**: Todos los comentarios y aclaraciones posibles deberían acompañar a cada prueba, con el fin de poder verificar en el futuro si el resultado esperado es correcto. Como mínimo, deberían describirse los datos de entrada y los datos de salida.


## Por qué ##
Las baterías de _unit tests_ se convierten a veces en un coñazo, tal como pueda ser la documentación. A los programadores nos gusta programar y diseñar y ver cosas funcionando, pero no nos suele hacer gracia ponernos a explicar cosas ni hacer pruebas repetitivas. Sin embargo, todos sabemos lo importante que es la documentación en una librería (casi más que lo bien hecha que esté la librería, para algunos), y debemos entender lo importante que es el _unit testing_. Los _unit tests_ no sirven para comprobar que lo que acabamos de picar funciona, para eso simplemente tenemos que usarlo en una aplicación de prueba y comprobar que no haga cosas raras. El verdadero propósito de los _unit tests_ es verificar que, al igual que funcionaba la primera vez que se desarrolló, hoy día, tras X cambios, sigue funcionando exactamente igual de bien. Y bien quiere decir de la forma esperada, devolviendo los mismos resultados a partir de las mismas entradas. Da mucha alegría tener una batería de tests preparada y ejecutarla justo antes de subir código. Supongamos que en ese momento saltan 5 fallos y ninguno lo provocan métodos de la recién creada clase; sin embargo, los cambios que se hicieron para integrar la clase sí que han hecho que el comportamiento de otras clases cambie y resulte ser incorrecto; en ese momento uno se bendice a sí mismo, arregla los fallos, vuelve a ejecutar los tests y, si todo es un éxito, sube con la máxima tranquilidad de que hay un 90% (por usar un porcentaje alto) de posibilidades de que no hayas introducido un bug que, de otra manera, aparecería 2 semanas después volviendo loco a todo el equipo. Hay otro gran beneficio derivado de tener una buena batería de tests, y que normalmente se pasa por alto: sin quererlo ni beberlo, hemos generado una invaluable documentación de casos de uso que nos puede ayudar a completar la documentación oficial o incluso a darnos cuenta de fallos de usabilidad.


## Cómo ##

Usamos el **Unit Testing Framework** (UTF) de la librería **Boost**. Es bastante cómoda (una vez que entiendes cómo funciona), y se ajusta bien a los estándares del _testing_. Se organiza jerárquicamente en tres escalones:

  * **Test module**: Conceptualmente, agrupa todos los tests que tienen que ver con el mismo grupo de funcionalidad. Técnicamente es un conjunto de tests que comparten un mismo "espacio de compilación", lo que viene a ser un proyecto con un punto de entrada.
  * **Test suite**: Conceptualmente, agrupa todos los tests de un mismo espacio de nombres, que en nuestro caso es una clase. Técnicamente es un conjunto de tests que comparten la misma unidad de traducción, o mismo fichero CPP.
  * **Test case**: Conceptualmente, consta de un _unit test_, una única prueba sobre una función determinada, que puede ser una función global o el método de una clase. Técnicamente, es una función (normalmente sin entradas ni salidas) en cuyo interior se definen unos datos que serán procesados por aquel algoritmo cuyo funcionamiento quiere verificarse. El resultado del _unit test_ será notificado mediante _asserts_ propios de la librería de _Boost_. Puede haber muchos _test case_ por cada método bajo prueba.


## Fixtures ##

Una _fixture_ es como una agrupación de tests que comparten un proceso de inicio (_setup_) y uno de terminación (_teardown_). Podríamos decir que es como una _test suite_ con principio y fin. Aquí _Boost_ difiere de lo estándar, es decir, lo normal es que el _setup_ y el _teardown_ se ejecuten antes del primer test y después del último, únicamente. Sin embargo, _Boost_ hace que ambos procesos se ejecuten para cada test. También podemos definir _fixtures_ para uno o varios test concretos, así como uno global del _test module_.

## Mocks ##

Un _mock_ es algo falso, carente de funcionalidad, como una maqueta o emulación de algo real. De hecho, cuando "mockeamos" algo, la intención es que la réplica falsa nos devuelva lo que podría devolver la original en cierta situación que nos conviene para realizar una prueba determinada. Supongamos que tenemos que leer un archivo de texto del disco, lo cual nos limita en independencia; una manera de eliminar esa limitación es haciendo que el objeto que se encarga de leer en disco esté vacío y siempre devuelva la misma cadena de texto a nuestra conveniencia. Sustituir piezas del programa por _mocks_ a veces es bastante complicado, sobre todo si no contamos con mecanismos de reflexión en C++, aunque con un buen diseño, poco acoplado y modular, debería ser sencillo la mayoría de las veces cambiar una referencia a un objeto por otro que implemente la misma interfaz de distinta forma.


## Qué testear ##

  * **Happy path**: El "happy path" es el cercioramiento de que la funcionalidad produce un resultado normal a partir de una determinada entrada que no está pensada para provocar fallos o resultados específicos, una entrada que represente al 99% de las que llegarán en un entorno normal con un uso normal. Es la típica prueba que se hace para ver que funciona.
  * **Formato**: Consiste en asegurarse de que el resultado obtenido cumple un determinado formato en cuanto a tamaño, caracteres usados, orden de tokens, etc.
  * **Orden**: Verifica que el orden de los elementos retornados sea el esperado.
  * **Rango**: Se utilizan determinados rangos de valores, o valores que representen a esos rangos para provocar casos de uso específicos a los que podría enfrentarse la funcionalidad. Por ejemplo, pasarle un cero a una función que divide por el parámetro que recibe, o un puntero nulo a una función que espera un array, o un 2 a la función _acos()_. En estos caso se buscan los valores límite (_bounds_) y se crea un _test case_ por cada uno de ellos.
  * **Referencias**: Si la funcionalidad bajo prueba tiene alguna dependencia, se comprueba y confirma su comportamiento ante la carencia de tal elemento del que depende.
  * **Existencia**: Comprobar que el valor devuelto existe, es decir, no es un puntero nulo o una lista vacía.
  * **Excepciones**: No sólo se comprueba que los resultados sean buenos, sino también que sean malos. En los casos en que se lancen excepciones, hay que comprobar que efectivamente se lanzan. Lo mismo ocurre con los códigos de error. La idea no es que nuestra funcionalidad sea 100% robusta en el sentido de que nunca tire la aplicación, sino que estemos seguros de su comportamiento ante estados normales y estados anómalos.


## Lectura recomendada ##

  * Pragmatic Unit Testing in C# with NUnit, Second Edition.