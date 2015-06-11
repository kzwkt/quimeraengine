# Serialización con Boost #

## Descripción ##

Boost es un conjunto de bibliotecas de software libre y revisión por pares preparadas para extender las capacidades del lenguaje de programación C++. Su licencia, de tipo BSD, permite que sea utilizada en cualquier tipo de proyectos, ya sean comerciales o no.
_Extraído de: [Wikipedia](http://es.wikipedia.org/wiki/Bibliotecas_Boost)_

La librería que nos interesa se llama **Serialization**, y aparece bajo el namespace **boost::serialization**. Dentro de la carpeta de los fuentes de Boost, las cabeceras se encuentran en la carpeta **boost/serialization**. También se utilizan clases que simbolizan archivos, bajo el **namespace boost::archive** y en el directorio **boost/archive**.
El autor es Robert Ramey y la versión usada en ésta prueba de concepto es la 1.44.

## Características ##
  * Permite serializar grafos.
  * Requiere RTTI.
  * Ofrece serialización a archivos binarios, XML y texto plano.
  * Ofrece serialización automática de estructuras de la STL.
  * Ofrece versionado.
  * Ofrece 2 metodologías para serializar, una intrusiva y otra no-intrusiva.
  * Serialización profunda.

## Instalación ##

Las librerías de Boost actualmente son, en su mayoría, archivos de cabecera que no necesitan ser compilados, al estilo de la STL. Sin embargo, la parte de **Serialization**, junto a otros, sí que tienen que ser compilados a parte. Para ello:
  1. Abre la consola de VS2010.
  1. Navega hasta la carpeta donde se tenga la librería de Boost.
  1. Escribir: _bootstrap_ . Esto prepara los archivos de configuración.
  1. Escribir: _.\bjam_ . Realiza la compilación de todas las librerías que lo necesitan.
  1. Se habrán generado una serie de archivos .lib en la carpeta **stage/lib**, dentro del directorio de Boost.
  1. En la configuración del linker para nuestro proyecto de VS2010, incluimos tal carpeta y el archivo **libboost\_serialization-vc100-mt-gd.lib**.

## Versionado ##

Cuando definimos un proceso de serialización y generamos archivos en base a éste, tenemos que asegurarnos de que tales archivos sigan siendo compatibles con la aplicación a pesar de que el proceso cambie. Por ejemplo, si la clase que serializábamos ahora contiene un atributo más, y queremos cargar un archivo que habíamos generado cuando la clase aún no contenía tal atributo, tenemos que distinguir de alguna manera la versión del archivo, para evitar, en este caso, que el deserializador busque en el archivo un atributo que, cuando entonces, no existía.
En el método **serialize** recibimos siempre un número de versión, obtenido del archivo. Para especificar cuál es la versión de nuestro proceso, utilizamos en el ámbito global la macro **BOOST\_CLASS\_VERSION(class, version)**, donde el primer parámetro es el nombre de la clase y el segundo su versión actual.

## Metodología intrusiva VS no-intrusiva ##

Existen dos maneras de implementar nuestra serialización, una calificada como "intrusiva", que requiere que modifiquemos la clase para añadir un método de plantilla de nombre fijo "serialize", que acepta un objeto archivo y el número de versión; y otra no-intrusiva, que consiste en declarar una función de plantilla global que acepta un archivo, una instancia de nuestra clase y el número de versión.
Cuando se usa la forma intrusiva, hay que añadir normalmente a la clase **boost::serialization::access** como amiga, ya que es ésta la que llama al método serialize de nuestras clases internamente.

```
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class gps_position
{
    public:
    int degrees;
    int minutes;
    float seconds;
    gps_position(){};
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}
};

namespace boost {
    namespace serialization {

        template<class Archive>
        void serialize(Archive & ar, gps_position & g, const unsigned int version)
        {
            ar & g.degrees;
            ar & g.minutes;
            ar & g.seconds;
        }

    } // namespace serialization
} // namespace boost
```

## Pares nombre-valor en la serialización a XML ##

Para de/serializar de/hacia un archivo XML, es necesario realizar una correspondencia atributo de clase <`==`> elemento de XML. Los elementos de XML están representados por pares nombre-valor, donde se pretende que el nombre sea el del atributo de la clase, y el valor su contenido en forma de cadena de caracteres. Por éste motivo, cuando se usen los tipos de archivo xml\_oarchive y xml\_iarchive, hay que envolver los atributos en la macro **BOOST\_SERIALIZATION\_NVP( atributo )** en la llamada a los operadores << y >>.
Cuando tratamos con herencia, serializaremos la clase base como si fuera un atributo más, pero usando la macro **BOOST\_SERIALIZATION\_BASE\_OBJECT\_NVP( `NombreDeClaseBase` )**.
No se debe llamar al método serialize de la clase base.
No se pueden serializar arrays alojados en el heap (no se conoce su tamaño y tampoco son reconocidos por el sistema de Boost).

## Codificación para serialización en texto (secuencial y XML) ##

Preferentemente, se usará la codificación UTF-8.

  * All text archives (i.e. text`_`?archive) will produce text output in the current stream locale. Generally this will produce no changes in string data.
  * To produce binary output with Microsoft compilers, the stream will have to be opened with mode ios::binary. Failure to do so will result in 0x0d characters (carriage-return) characters being removed from the input stream if they are followed by a 0x0a character (line-feed). This could corrupt the input and make the file unreadable. On UNIX systems the ios::binary is not required and is ignored if used.
  * character XML archives (i.e. xml\_oarchive) will produce XML output with characters encoded according to the current stream locale.
  * wide character XML archives (i.e. xml\_woarchive) will produce files encoded in UTF-8.

This character encoding is implemented by changing the locale of the i/o stream used by an archive when the archive is constructed, the stream local is changed back to its original value. This action can be overridden by specifying boost::archive::no\_codecvt when the archive is opened. In this case, the stream locale will not be changed by the serialization library.

Note that the code conversion included for wide character text and XML archives could alter std::string data stored in archives. Suppose a normal (multi-byte) character string is written to a wide character stream. Our system uses the current locale to translate it to a wide character string before writing it out. Upon reading, it is translated back to a (multi-byte)string. If the locale on the platform that reads the archive is different than the locale on the platform that wrote the stream, the actual string data may be altered by the serialization process. To avoid this, either avoid usage of locale dependent multi-byte strings or be sure that the locale is set correctly before reading the archive.

To produce wide character text output (i.e. 16 bit characters on Win32 systems), do the following.

  * Open a wide character stream.
  * Alter the stream locale to use boost::archive::codecvt\_null<OStream::char\_type>
  * Create the archive with the flag no\_codecvt.

Naturally, the input process has to be symmetrical.

_Extraído de: [Documentación de Boost](http://www.boost.org/doc/libs/1_44_0/libs/serialization/doc/implementation.html#charencoding)_

## Código fuente de la prueba de concepto ##

_`https://quimeraengine.googlecode.com/svn/team/poc/Task 7 - Serialization/BoostSerialization`_

## Páginas web de interés ##
  * [Descarga de Boost](http://sourceforge.net/projects/boost/files/boost/1.44.0/)

  * [Serialization](http://www.boost.org/doc/libs/1_44_0/libs/serialization/doc/index.html)

  * [Boost](http://www.boost.org/)

  * [Guía práctica en Codeproject](http://www.codeproject.com/Articles/225988/A-practical-guide-to-Cplusplus-serialization)