# Flujo de Trabajo #

## Gestión ##

La gestión y orden de tareas seguirá un patrón de micro-waterfall, esto es, se llevará a cabo la siguiente secuencia de tareas por cada nueva funcionalidad a añadir, en lugar de esperar a completar el mapa completo de funcionalidades del sistema:
  1. Propuesta
  1. Diseño
  1. Desarrollo
  1. Revisión
  1. Incorporación a la release

## Tarea de Desarrollo ##

<p align='center'><img src='http://quimeraengine.googlecode.com/svn/wiki/images/ProcesoTrabajo.png' /></p>
<br />
  1. Autoasignarse la tarea con más prioridad / Ser asignado a una tarea
  1. Cambiar el estado de la tarea a _Started_
  1. Obtener la última versión del código (_Checkout_ / _Update_)
  1. Realizar la tarea
  1. Cambiar el estado de la tarea a `ReadyForReview`
  1. Crear parche y enviar al reviewer (Create Patch... sobre la carpeta **trunk**), incluyendo el ID y el título de la tarea en el asunto del correo
  1. a `[`Correcto, estado de la tarea es _Done_`]`: _Update_ y _Commit_
  1. b `[`Incorrecto, estado de la tarea _Started_`]`: Vuelta al paso 3

## Nota ##

En las subidas, añadid a la "ignore list" los archivos con las siguientes extensiones: suo, sdf, opensdf. Y las siguientes carpetas: Debug, Release, obj, ipch.
Para hacerlo, pulsar botón derecho sobre el archivo (que debe estar dentro de una carpeta ya subida al repositorio) y en las opciones de Tortoise seleccionar "Add to ignore list". Aparecerán varios comandos: Para las carpetas elegid "Ignore items by name" o el nombre de la carpeta; para archivos elegid "Ignore items by extension" o la extensión del archivo.
Este paso puede hacerse antes del commit, añadiendo los archivos y luego ignorándolos, o después, subiendo sólo los archivos que nos interesan y posteriormente ir añadiendo los que no a la lista de ignorados.

El **comentario de las subidas** tendrá el formato siguiente: _Nº de tarea - Título de la tarea <salto de línea> Descripción breve de lo que se ha hecho._

## Tratamiento de errores encontrados durante el Desarrollo ##

<p align='center'><img src='http://quimeraengine.googlecode.com/svn/wiki/images/ProcesoTrabajoErrores.png' /></p>
<br />
  1. Se identifica la causa del supuesto error.
  1. Se crea un hilo en el foro, en la sección _Errores encontrados durante el desarrollo_.
  1. Se discute si se trata efectivamente de un error y si, en tal caso, debe acometerse directamente o tendrá mayores efectos.
  1. a `[`Sí`]`: Se decide qué hacer con él.
  1. b `[`No`]`: Se cierra el hilo.
  1. Se corrige.
  1. Se comenta la solución dada y se confirma que es la debida y que no tendrá efectos colaterales.
  1. a `[`Correcto`]`: Se cierra el hilo. _Update_ y _Commit_.
  1. b `[`Incorrecto`]`: Se busca una solución correcta o alternativa.

## Nota ##

Cuando se identifique un error, es recomendable hacer un _Update_, por si ya ha sido corregido en la revisión actual.

El **comentario de las subidas** tendrá el formato siguiente: _Error: Descripción muy corta <salto de línea> Descripción breve de lo que se ha hecho._

## Etapas por cada fase ##

Cada fase tiene un propósito determinado o se dedica a un campo del proyecto concreto (infraestructura, gráficos, comunicaciones, integración, rencimiento, etc.) y, a su vez, atraviesa varias etapas de producción siguiendo la siguiente secuencia:

<p align='center'><img src='http://quimeraengine.googlecode.com/svn/wiki/images/PhaseStages.png' /></p>

  1. Initialization: Los responsables ultiman los diseños e insertan las tareas. Los miembros del equipo las ojean y se las asignan. Se aclara de dónde sacar la información, se solucionan carencias de comunicación y otros aspectos no identificados durante el diseño.
  1. Development: Se acometen las tareas hasta que cada miembro del equipo estima que ha acabado según lo que su tarea requería, tal y como muestra el esquema del flujo de tabajo para una tarea de desarrollo.
  1. Unit tests: Cada vez que se añada código al repositorio hay que comprobar que no se rompe ninguna otra funcionalidad, ejecutando los unit tests o creándolos en caso de que no existan aún.
  1. General Review: Los responsables revisarán el código procurando la coherencia, buscando partes no testeadas, que falten o sean incorrectas en el contexto actual.
  1. Performance Tests: Sobre todo en la fase 0, se tendrá en cuenta el rendimiento, realizándose tests intensivos para medir los tiempos de ejecución del código.
  1. Optimization: Si los datos arrojados por los tests de rendimiento no son satisfactorios (porque hayan empeorado o porque suponga un obstáculo para la escalabilidad, dado el hardware actual), se procederá a una optimización puntual o general.