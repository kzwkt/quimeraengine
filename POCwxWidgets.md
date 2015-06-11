# wxWidgets #


## Descripción ##
wxWidgets es una librería que facilita la creación de interfaces gráficas en C++.

Hay bastante información sobre ella en la red. Se puede leer una descripción general en la [Wikipedia](http://es.wikipedia.org/wiki/WxWidgets).

Su página oficial es [wxWidgets](http://www.wxwidgets.org), de donde se puede descargar la librería.

Existen varias interfaces gráficas para el diseño de las ventanas o diálogos que compondrán la interfaz. Entre ellas está [wxFormBuilder](http://www.wxformbuilder.org/), bastante completa y con un estilo muy similar a Visual Studio 6.

Todas estas librerías se descargan en general como código fuente, lo que obliga a compilarlas para cada sistema operativo, etc.

Existe un pack de librerías, llamado [wxPack](http://wxpack.sourceforge.net/Main/Features), que facilita bastante la instalación y uso de estas librerías puesto que vienen precompiladas para VC y GCC, y permite una cierta personalización en la instalación.

## Instalación ##

Usando wxPack, nos evitamos tener que compilar las librerías, como hemos dicho. Simplemente descargamos la última versión e instalamos, eligiendo para wxWidgets el compilador que queramos, y las versiones dinámicas o estáticas:

![http://i50.tinypic.com/2rhmsmt.jpg](http://i50.tinypic.com/2rhmsmt.jpg)

## Creación de un proyecto nuevo ##

Desde `CodeBlocks`, se crea un proyecto nuevo, apareciendo el diálogo en el que se puede elegir el tipo de proyecto. Elegimos wxWidgets:

![http://i46.tinypic.com/2je2xpf.jpg](http://i46.tinypic.com/2je2xpf.jpg)

Se nos abrirá entonces el asistente de wxWidgets, en el que habrá que elegir la versión de wxWidgets que vamos a usar (hay que tener cuidado con la compatibilidad entre las diversas librerías). Nosotros usamos la 2.8.x, que es la que tenemos instalada:

![http://i46.tinypic.com/66yz3b.jpg](http://i46.tinypic.com/66yz3b.jpg)

Hay que elegir el GUI que vamos a usar, usaremos wxFormBuilder:

![http://i47.tinypic.com/2u94enq.jpg](http://i47.tinypic.com/2u94enq.jpg)

Finalmente, tras poner nombre y ruta del proyecto, compilador que se usará y autor, etc., hay que dar la ruta donde está instalada wxWidgets. En principio, aunque sale una variable de sistema, mejor dar la ruta absoluta porque creo que con la variable no funciona:

![http://i46.tinypic.com/n730k.jpg](http://i46.tinypic.com/n730k.jpg)

El asistente crea un proyecto en el que introduce varios archivos:

  * `GUIFrame.cpp (.h)`: aquí se definen las clases de las ventanas que hayamos creado. Este archivo se regenera cada vez que hagamos una modificación en cualquier ventana vía FormBuilder, por lo que todo código que agreguemos desaparecerá si se hace una modificación posterior. Es mejor, por tanto, no escribir en este archivo.

  * `NombreProyectoApp.cpp (.h)`: Aquí se define una clase que equivale al método main(), pues este está implementado internamente. Se encarga de llamar a la ventana principal de la aplicación, y de terminar la aplicación cuando se cierre la ventana.

  * `NombreProyectoMain.cpp (.h)`: Aquí se definen las clases derivadas de las definidas en GUIFrame, y se implementan los eventos.

![http://i50.tinypic.com/slqud0.jpg](http://i50.tinypic.com/slqud0.jpg)

## Diseñando una ventana ##

Para el diseño de las ventanas/diálogos, wxFormBuilder incorpora el concepto de sizers.

Los sizers son contenedores, invisibles en tiempo de ejecución, cuya misión es asegurar que la distribución de controles, las fuentes etc, es decir, la apariencia de la ventana permanece proporcional sea cual sea el equipo o el sistema operativo en el que se ejecute.

Estos contenedores se introducen de forma jerárquica, de manera que hay siempre un sizer principal o padre, al que se le añaden tantos sizers hijos como se quiera (imagino que habrá un límite), que a su vez contienen otros sizers, distribuyendo todos ellos en función de la distribución final de controles deseada.

Cada sizer tiende a ocupar todo el espacio proporcionado por su padre. Así, el sizer inicial ocupa todo el frame en el que está:

![http://i50.tinypic.com/24fwmk7.png](http://i50.tinypic.com/24fwmk7.png)

Según vamos añadiendo sizers, estos se reparten el espacio de su sizer padre, aunque variando la propiedad Proportion pueden distribuirse asimétricamente:

![http://i47.tinypic.com/14c9ye0.png](http://i47.tinypic.com/14c9ye0.png)

Se añaden controles y se centran vertical u horizontalmente según el sizer se haya definido vertical u horizontal, se pueden expandir a lo ancho, a lo alto o de ambas formas, con las herramientas de la barra:

![http://i48.tinypic.com/ok0co2.png](http://i48.tinypic.com/ok0co2.png)


![http://i47.tinypic.com/33yo13t.png](http://i47.tinypic.com/33yo13t.png)

En fin, es una cuestión de pelearse con la jerarquía de sizers y sus propiedades hasta dar con el diseño que buscamos.