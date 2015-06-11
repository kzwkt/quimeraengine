# Compilación de las librerías de Boost #

Lo que sigue es una escueta guía, paso a paso, de cómo compilar las librerías de Boost en distintos sistemas operativos.

## Común ##

  * Descargar la última versión del paquete comprimido desde la [página oficial de Boost](http://sourceforge.net/projects/boost/files/boost/).

## Windows ##

  * Descomprimir, abrir y ejecutar el archivo bootstrap.bat. Se debe crear el ejecutable **bjam.exe**, en pocos segundos, en el mismo directorio.
  * Mediante la consola del sistema, ejecutar **bjam.exe** especificando los parámetros deseados, por ejemplo: `bjam toolset=msvc variant=debug link=static threading=multi runtime-link=shared`.
  * Las librerías estarán disponibles en la carpeta **stage**.

## Linux (Ubuntu 10) ##

  * Descomprimir, abrir y ejecutar el script bootstrap.sh (comando "sh bootstrap.sh"). Se debe crear el ejecutable **bjam**, en pocos segundos, en el mismo directorio.
  * Mediante la consola del sistema, ejecutar **bjam** especificando los parámetros deseados, por ejemplo: `bjam toolset=gcc variant=debug link=static threading=multi runtime-link=shared`.
  * Las librerías estarán disponibles en la carpeta **stage**.
  * Nota: Es posible que se produzca un error nada más empezar la compilación, cuyo mensaje se parece a `"rule UPDATE_NOW ( targets * : log ? : ignore-minus-n ? )"`. Si esto ocurre, hay que ir al directorio tools/build/v2/build/ y abrir el fichero **configure.jam**. En la **línea 145**, hay que borrar ": ignore-minus-q". Intentar de nuevo.