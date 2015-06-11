# Herramientas imprescindibles #

Para colaborar en este proyecto son necesarias, como mínimo, las siguientes herramientas:

## Code::Blocks 10.05 y Visual Studio 2010 Express ##

El IDE elegido para el desarrollo ha sido Code::Blocks 10.05. En un principio utilizamos Visual Studio 2010 Express por la cantidad de usuarios acostumbrados a los IDEs de Microsoft y por su usabilidad. Más tarde nos dimos cuenta de que su compilador no es para nada respetuoso con los estándares de C++, violando normas e incluyendo extensiones arbitrariamente, lo cual ocasiona problemas de portabilidad e incluso del propio desarrollo. Finalmente optamos por Code::Blocks (la última versión disponible era la 10.05) como principal entorno de desarrollo, pues también dispone de una amplia comunidad de usuarios y ofrece la misma cantidad de facilidades que VS (ambos tienen sus ventajas y desventajas). Como compilador utilizamos GCC (MinGW bajo Windows), que además de respetar el estándar, nos asegura la portabilidad entre Windows y Linux sin necesidad de realizar grandes esfuerzos. No obstante, seguimos manteniendo la solución de VS dado que, al final, la mejor decisión es usar cada herramienta para lo que mejor sirva, combinando ambos por una mayor productividad. Es de sobra conocida la calidad del depurador de Microsoft sobre cualquier otro y da algunas pequeñas facilidades adicionales a la hora de codificar unit tests.


## Tortoise SVN 1.7.1 ##

Nuestro sistema de versiones es Subversion y, dado que el S.O. para el que desarrollaremos al principio será Windows 7, es necesario utilizar la herramienta gratuita Tortiose, en su versión 1.7.1. Según se actualice el servidor, se notificará al equipo que se ponga al día. Para Linux está disponible un clon de Tortoise llamado Rabbit CVS, aunque no se realizarán subidas desde tal sistema por razones de compatibilidad, al no estar del todo maduro.