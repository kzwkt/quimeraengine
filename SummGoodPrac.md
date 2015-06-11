# Buenas prácticas y convenciones no clasificadas #

  * Poner el mínimo de inclusiones de cabeceras en archivos de cabecera (.h). Utilizar declaraciones adelantadas (forward declarations).
  * Poner toda la implementación posible en el archivo de implementación (.cpp) en lugar de en el de cabecera (.h).
  * No es necesario usar indentación en el código que va dentro de un namespace.
  * Cuando se usen tipos de la STL, especificar siempre el namespace. Ejemplo: std::string.
  * Usar siempre el tipo unsigned int para iteradores de tipo entero, salvo excepciones contadas.
  * Evitar los castings al estilo C, usar const\_cast, reinterpret\_cast, dynamic\_cast o static\_cast.
  * Poner el modificador const al final de la declaración de métodos que no modifiquen los atributos de la clase.
  * Poner el modificador const delante de los parámetros que no se vean afectados en el interior de las funciones, cuando sea posible.
  * En los casos en que se pueda usar polimorfismo, hacer virtual siempre el destructor.
  * Por defecto, los miembros no públicos serán protected.
  * Cuando se lancen excepciones, usar la más concreta disponible.
  * Inicializar siempre al declarar (RAII: Resource Acquisition Is Initialization).
  * Poner el tipo de excepciones que lanza un método en su declaración.
  * No usar nunca `ZeroMemory`, memcpy, etc. con tipos polimórficos.
  * Meter valores constantes en constantes, salvo casos concretos como el número cero, cadenas que sólo existen en un sitio (y jamás vayan a estar en más) o valores booleanos.
  * Se permiten bloques if sin llaves a menos que induzca a errores (evitarlo si hay bloques else cerca).
  * Se permiten condiciones sin signo de igualación, como los punteros nulos o los bool.
  * Los punteros se anulan con una constante para null, no con cero.
  * No usar breaks en bucles for, salvo casos excepcionales.
  * Después de usar delete, anular el puntero.
  * Evitar los tipos void`*` siempre que sea posible.
  * No pasar estructuras de la STL como parámetros por valor.
  * Usar etiquetas `[TODO]`, `[HACK]` y `[REVIEW]` en comentarios para indicar cosas por hacer, rodeos obligatorios que se han tomado y que seguramente se puedan mejorar en el futuro, y trozos de código que por desconocimiento o por prisas se han hecho peor de lo debido, respectivamente.
  * Usar la etiqueta `[DOC]` para indicar que falta completar la documentación de algún elemento del código.
  * Comentar código y documentación con //, no con /`*` `*`/. El código inservible, si fue anteriormente subido al repositorio, debe ser borrado.
  * En los comentarios con //, hay que dejar un espacio antes de empezar la frase.
  * Si el cuerpo de un método ocupa demasiado a lo alto, partirlo en 2 como mínimo, salvo pérdida de eficiencia en lugares críticos.
  * No hay límite establecido a lo ancho para una línea de código, aunque sería preferible que no se saliera de un monitor de 1024. En casos en los que se perjudique la legibilidad por partir la línea, se dejará en una, aunque sobrepase la recomendación.
  * Cuando se llame a un método, siempre debería ir precedido por su clase/interfaz, aunque se esté llamando desde su propia clase, en cuyo caso se usaría this.
  * Salvo estructuras especiales, todos los atributos no constantes de una clase que quieran hacerse públicos deben estar encapsulados por sus respectivas propiedades (Get / Set).
  * Preferir el uso del operador de multiplicación al de división. Motivos de eficiencia. Ejemplo: 1.0f `*` 0.5f en lugar de 1.0f / 2.0f.
  * En casos donde la velocidad sea extremadamente crítica, usar n >> 1 en lugar de n / 2 y n << 1 en lugar de n `*` 2, cuando se usen números enteros.
  * Guardar la condición de un bucle antes de que éste empiece, cuando se pueda. Un ejemplo de esto es el típico .Count() de una lista.
  * Usar string en lugar de char`*` siempre que se pueda, se asume la pérdida de rendimiento.
  * Usar vector en lugar de un array, siempre que se pueda. Se asume la pérdida de rendimiento. Aprovechar la dualidad de comportamiento de vector.
  * No usar myMap["clave"] == null. Usar el método find().
  * Cuidado con el orden de preferencia de los operadores lógicos y los de bit.
  * Retrasar al máximo posible la reserva de memoria.
  * Realizar comprobaciones de parámetros nulos y lanzar excepciones en los casos pertinentes. Por lo general se usarán Asserts.
  * Usar la notación de sufijos / prefijos de tipos constantes para evitar conversiones implícitas. Float: 1.0f; Long: 1L; Wchar\_t: L"String"; Unsigned: 1U...
  * Cada llave { } ocupará por sí sola una línea. Esto quiere decir que no se empezarán los bloques con una llave de apertura al final de una sentencia, se pondrá en la línea siguiente.
  * Especificar las rutas de los includes con barras (/) y no contrabarras (\).
  * Usar smart pointers siempre que se reserve un recurso. Evaluar si merece la pena su uso en cada vez que se necesite alojar memoria en el _heap_.
  * Usar explicit en los constructores de un solo parámetro de entrada.
  * El código más rápido es el que no se ejecuta.