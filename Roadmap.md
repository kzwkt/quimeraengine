# Hoja de Ruta #

<p align='center'><img src='http://quimeraengine.googlecode.com/svn/wiki/images/Roadmap.png' /></p>

## Gestación ##

  * **Idea:** Todo proyecto surge a partir de una idea, una visión, la imaginación de una obra. A su vez, la idea nace fundamentada en unos conocimientos previos y en una vaga previsión de su factibilidad. En nuestro caso la idea es una librería que actúa como motor o núcleo sobre el que edificar videojuegos de forma mucho más sencilla que si dicho motor no existiera.
  * **Formación:** Llevar a cabo cualquier proyecto tecnológico requiere una serie de conocimientos complejos, cuya base todo el equipo debe adquirir para avanzar como una sola fuerza. Es necesario un periodo de tiempo en el que cada miembro aprenda lo que necesite y una documentación técnica o fuente de información común.
  * **Definición:** Se trata del establecimiento de prioridades y objetivos trasversales a todo el proyecto, el dibujo de los límites del mismo, su silueta y las convenciones utilizadas durante su desarrollo.
  * **Investigación:** Una vez que el equipo tiene una formación básica en la tecnología principal sobre la que se sustenta el proyecto, es momento de investigar las herramientas técnicas disponibles que puedan ayudar a su éxito. Existen una serie de librerías open source bajo licencia que permite su uso comercial y multiplataforma, que bien usadas acelerarán el desarrollo de nuestro software. Es necesario conocerlas, aprender cómo funcionan y compararlas con soluciones similares.
  * **Preparación Entorno:** Un buen entorno de trabajo es vital para que el equipo pueda trabajar cómodamente, sin más obstáculos que los propios de las tareas. Es necesario establecer el proceso de trabajo basado en herramientas a las que todo el mundo tenga acceso para gestionar el código fuente, las tareas y la documentación.
  * **Selección de Tecnologías:** Después de las investigaciones es hora de tomar decisiones acerca de qué tecnologías integrarán el cuerpo del proyecto. Cada miembro del equipo debería ocuparse de llevar una investigación exhaustiva de alguna tecnología concreta, para luego explicarla a los demás. Dado que somos pocos, las decisiones las tomaremos entre todos, teniendo yo la última palabra en caso de discrepancias o indecisión.
  * **Ensayos:** Para comprobar que el sistema de trabajo funciona antes de empezar con el desarrollo puro y duro, se harán unas jornadas de prueba en la que intervendrán todos los elementos posibles, incluyendo pruebas de carga. Quizá nos demos cuenta en ese momento que hay cosas inviables, inútiles o sin definir.


## Fase 0 ##

  * **Diseño General:** Primeros diagramas UML de la "carcasa" de la API. Es un diseño concreto pero escueto, presentando las clases principales del sistema y definiendo a grandes rasgos el estilo de la interfaz.
  * **Registro de las Primeras Tareas:** Dará comienzo oficialmente el desarrollo de Quimera Engine, registrando las primeras tareas relacionadas con pruebas de concepto necesarias para desarrollar la infraestructura del sistema, abriendo el repositorio de código y haciendo pública la existencia del proyectp.
  * **Desarrollo Infraestructura:** Desarrollo de pruebas de concepto necesarias e implementaciones reales de ciertos apartados del motor básicos para facilitar el resto del desarrollo, como son: logging, profiling, input, estructuras matemáticas... Se detallará más cuando se acerque el momento.
  * **Pruebas Intensivas:** Antes de continuar a la siguiente fase es imprescindible haber testeado al máximo todo lo desarrollado, que constituye no sólo los cimientos, sino también los ladrillos y el cemento. Se creará una batería de unit tests para todas las clases auxiliares y se realizarán exploratory, stress y endurance tests para las secciones del motor implementadas. No se pueden permitir errores.


## Fase 1 ##

  * **Diseño API Gráfica:** Contando con las herramientas y los materiales fabricados en la fase anterior, ya se puede acometer la sección del motor más interesante. Se diseñarán ciertas partes básicas para que sea posible representar un texto en pantalla.
  * **Desarrollo Inicialización:** Implementación de las clases que permitan la inicialización de la sección gráfica.
  * **Desarrollo Infraestructura:** Implementación de las clases que permitan la gestión de varios tipos de contenido, como textos.