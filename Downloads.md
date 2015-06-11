# Descargas: Dependencias #

Aquí se encuentran todos aquellos recursos utilizados por la librería y que resultan imprescindibles para desarrollar.

## Librerías de Boost ##

Librerías estáticas precompiladas de la versión 1.46.1 de Boost. En los paquetes sólo se encuentran aquellas utilizadas por Quimera Engine.

**Includes (cualquier S.O. y cualquier compilador)**
  * [Código fuente no compilado](http://quimeraengine.googlecode.com/files/Boost1_46_1Include.zip)

![http://quimeraengine.googlecode.com/svn/wiki/images/WindowsLogo.png](http://quimeraengine.googlecode.com/svn/wiki/images/WindowsLogo.png)**Windows 32-bits**
  * [Versión Debug + Enlazado de runtime dinámico + Librería estática (Visual Studio Express 2010)](http://quimeraengine.googlecode.com/files/Boost1_46_1DebugWin32Sharedrt.zip)
  * [Versión Release + Enlazado de runtime dinámico + Librería estática (Visual Studio Express 2010)](http://quimeraengine.googlecode.com/files/Boost1_46_1ReleaseWin32Sharedrt.zip)
  * [Versión Debug + Enlazado de runtime dinámico + Librería estática (MinGW)](http://quimeraengine.googlecode.com/files/Boost1_46_1DebugWin32Sharedrt_GCC.zip)
  * [Versión Release + Enlazado de runtime dinámico + Librería estática (MinGW)](http://quimeraengine.googlecode.com/files/Boost1_46_1ReleaseWin32Sharedrt_GCC.zip)

![http://quimeraengine.googlecode.com/svn/wiki/images/LinuxLogo.png](http://quimeraengine.googlecode.com/svn/wiki/images/LinuxLogo.png)**Linux 32-bits**
  * [Versión Debug + Enlazado de runtime dinámico + Librería estática (GCC)](http://quimeraengine.googlecode.com/files/Boost1_46_1DebugLinux32Sharedrt.zip)
  * [Versión Release + Enlazado de runtime dinámico + Librería estática (GCC)](http://quimeraengine.googlecode.com/files/Boost1_46_1ReleaseLinux32Sharedrt.zip)

![http://quimeraengine.googlecode.com/svn/wiki/images/MacLogo.png](http://quimeraengine.googlecode.com/svn/wiki/images/MacLogo.png)**Mac 32-bits**
  * Quimera Engine no es portable para Macintosh todavía.

Para **compilar Boost por cuenta propia**, quizás te sirva [esta guía](CompBoost.md).



# Descargas: Herramientas #

Conjunto de herramientas creadas / modificadas / recopiladas por el equipo de desarrollo para facilitar el trabajo.

## Plug-in `DoxyBlocks` modificado ##

Se trata de un Plug-in para Code::Blocks ya existente, utilizado para automatizar la escritura de documentación de código, que ha sido modificado por el equipo para que pueda insertar el formato de documentación XML (típico de .NET) utilizado en la librería (y que es aceptado por Doxygen).

  * [Versión para Code::Blocks 10.05 (Windows 32-bits)](http://quimeraengine.googlecode.com/files/DoxyBlocks1005PlugInTunedWin32.zip)
  * [Versión para Code::Blocks 10.05 (Linux 32-bits) PRÓXIMAMENTE](http://quimeraengine.googlecode.com/files/DoxyBlocks1005PlugInTunedLinux32.zip)

Para instalar el plug-in basta con seguir estos pasos:
  1. Abrir el IDE Code::Blocks.
  1. En el menú superior, abrir la opción _Plugins_ y elegir _Manage plugins..._.
  1. Pulsar en el botón _Install new_ y seleccionar el archivo con extensión _.cbplugin_ descargado.