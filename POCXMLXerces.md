# Xerces-c Library #


## Descripción ##
[Página oficial](http://xerces.apache.org/xerces-c/)

Xerces-C++ es un parser XML con validación, escrito en un subconjunto portable de C++, que facilita que tus aplicaciones tengan la capacidad de leer y escribir datos XML. La (shared) biblioteca proporcionada puede analizar, generar, manipular y validar documentos XML usando las APIS DOM, SAX y SAX2. Se puede encontrar una introducción a la programación con Xerces-C++ en la [Guía de programación](http://xerces.apache.org/xerces-c/program-3.html).

## Estándares ##
Xerces-C++ es fiel a las recomendaciones de XML 1.0 y muchos estándares asociados:
  * XML 1.0 (Third Edition), W3C Recommendation
  * XML 1.1 (First Edition), W3C Recommendation (Note: section 2.13 Normalization Checking has not been implemented)
  * DOM Level 1 Specification, W3C Recommendation of October 1, 1998
  * DOM Level 2 Core Specification, W3C Recommendation of November 13, 2000
  * DOM Level 2 Traversal and Range Specification, W3C Recommendation of November 13, 2000
  * SAX 1.0 and SAX 2.0
  * Namespaces in XML, W3C Recommendation of January 14, 1999
  * Namespaces in XML 1.1, W3C Recommendation
  * XML Schema Part 1: Structure, W3C Recommendation 2 May 2001
  * XML Schema Part 2: Datatypes, W3C Recommendation 2 May 2001
  * DOM Level 3.0 Core Specification, W3C Recommendation 7 April 2004
  * DOM Level 3.0 Load and Save Specification, W3C Recommendation 7 April 2004 (See DOM Level 3 Support for detail)
  * XML Inclusions (XInclude) 1.0 (Second Edition), W3C Recommendation 15 November 2006

El parser proporciona un alto rendimiento, modularidad y escalabilidad. Con el parser, se proporcionan también el código fuente, ejemplos y documentación de la API. Por razones de portabilidad, se ha tenido cuidado de hacer un uso mínimo de templates y de IFDEFs#.

## Licencia ##
Se proporcionan distibuciones tanto de codigo fuente como precompiladas, para la mayoría de plataformas, y todas bajo licencia Apache Software License, Version 2.0.

## Instalación ##
  1. Descargar el código fuente desde http://xerces.apache.org/xerces-c/download.cgi
  1. Abrir la solución para VS2010 que hay en la carpeta \projects\Win32\VC10.
  1. La configuración por defecto es /MT, con optimización de tamaño.
  1. Compilar el único proyecto de librería: XercesLib.
  1. Si se compiló en forma de librería estática, cuando se añada al proyecto cliente hay que especificar la macro siguiente en el preprocesador: XERCES\_STATIC\_LIBRARY.

## Inicialización ##
En su página viene un ejemplo de inicialización y terminación, que deben ser hechas siempre antes y después de utilizar la librería. Se pueden hacer inicializaciones y terminaciones anidadas, cuidando que cada inicialización lleve su terminación asociada:

```
#include <xercesc/util/PlatformUtils.hpp>
// Other include files, declarations, and non-Xerces-C++ initializations.

using namespace xercesc;

int main(int argc, char`*` argv[])
{
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    // Do your failure processing here
    return 1;
  }

  // Do your actual work with Xerces-C++ here.

  XMLPlatformUtils::Terminate();

  // Other terminations and cleanup.
  return 0;
}
```


Desgraciadamente, no vienen más ejemplos en su página, parece que vienen incluidos en las distribuciones.

## Pruebas de Concepto ##
  * [POC Xerces DOM](http://code.google.com/p/quimeraengine/source/browse/#svn/team/poc/Task%205%20-%20XML%20Parsing/PruebaXercesDOM)

  * [POC Xerces SAX2](http://code.google.com/p/quimeraengine/source/browse/#svn/team/poc/Task%205%20-%20XML%20Parsing/POCXercesSAX2)