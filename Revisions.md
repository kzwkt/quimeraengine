# Revisiones #

## Revisión de código ##

### ¿Para qué? ###
Todos somos humanos e imperfectos, todos tenemos días mejores o peores. El código libre de errores es una utopía. Para reducir el riesgo de pifias e incoherencia y asegurar una calidad mínima, es necesario revisar el trabajo realizado y rechazar aquél que no cumpla las expectativas marcadas antes de añadirlo al producto. La experiencia no deja lugar a dudas, la revisión de código es fundamental.

### ¿Cuándo? ###
Cada vez que se considera terminado el desarrollo de una tarea, antes de cualquier subida de código.

### ¿Quién? ###
El código de cualquier miembro del equipo debe ser revisado. Las revisiones las hará siempre otro miembro del equipo distinto de quien hizo el desarrollo, a ser posible alguien con más experiencia o veteranía en el proyecto.

### ¿En qué consiste? ###
  * Revisión del cumplimiento de las convenciones de nombres, de estilo y de patrones.
  * Revisión de la documentación, de que se usan las estructuras aconsejadas para ello, lo descrito corresponde con la realidad, y la gramática es correcta.
  * Revisión de uso de assertions cuando existen situaciones potencialmente peligrosas que deben ser notificadas.
  * Revisión del grado de finalización de la tarea, todo lo que aparezca en la descripción y documentación de la tarea debe existir en el trabajo entregado.
  * Revisión de que los tests relacionados hayan sido actualizados.
  * Revisión de que todos los tests provistos pasan.
  * Revisión de que hay suficiente cobertura de test.
  * Revisión de que el código compila y no se añaden warnings no justificadas.
  * Detección de problemas fácilmente visibles de rendimiento o errores potenciales.
  * Revisión de que se usan las clases ya conocidas y no se repite código.

## Revisión de tests ##

No hay manera de estar seguro de que el producto funciona correctamente si no se tiene la certeza de que los tests que deben confirmarlo cumplen su objetivo. Por ello, se hace necesaria la revisión de los tests implementados, de la misma manera que se hiciera con el código del producto final. Sin embargo, dado que el coste de desarrollo de los tests es elevado, y nunca debería sobrepasar (salvo caso de vida o muerte) el coste del propio producto, se impone una relajación en cuanto a la cantidad de características del código a comprobar, a saber:

  * Revisión de que los tests que no funcionan, de forma justificada, estén marcados con una etiqueta TODO y su explicación.
  * Revisión de que los tests hagan lo que dice su enunciado.
  * Revisión de que todos los métodos estén cubiertos.
  * Revisión de que todos los tests que se supone que deben pasar, pasen. Comprobar esto con todos los compiladores soportados.
  * Revisión de errores de convención de tests.
  * No es necesario profundizar en errores de convenciones de código de desarrollo normal.