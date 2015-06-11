# Convenciones para Unit Tests #

## Nombre de los test case ##

Cada test case debe tener un nombre único dentro del test suite y, preferentemente, deberá aparecer en el mismo orden que aparecen los métodos en la clase bajo pruebas (por facilitar las búsquedas visuales). A continuación se describen las normas a seguir para formar tales nombres:

**General**

Todos los nombres de test case utilizarán la forma `PascalCase` y se dividirán en 3 partes separadas por guiones bajos: 1º, el nombre del método de clase o la función que va a ser probada; 2º, una frase que explique cuándo el test dará positivo, o sea, cuando no fallará; y 3º, el sufijo "Test". Por ejemplo:

_`Intersection_IntersectionIsFoundWhenPlanesCoincide_Test`_


Las funciones incluídas como friend dentro de la clase, serán también testeadas en la misma test suite y tendrán el pregijo Friend-. Ejemplo:

_`FriendIntersection_IntersectionIsFoundWhenPlanesCoincide_Test`_

Adicionalmente, por comodidad, podrá usarse el adjetivo "Common" para describir un objeto utilizado en el test cuyo valor sea arbitrario, que represente a la gran mayoría de los valores que podrá adoptar el objeto y que, por tanto, no coincida con un valor límite o destacado (como pueda ser el cero, la identidad, el valor máximo o mínimo, etc.). Por ejemplo, si en el siguiente test se usara el valor 35º como parámetro del método bajo pruebas, podría usarse el siguiente nombre:

_`ConvertDegreesToRadians_CorrectValueIsObtainedWhenCommonAngleIsProvided_Test`_

**Sobrecargas**

Cuando existan varias sobrecargas para un método, la forma de diferenciarlos en la test suite será añadiendo un número al final del nombre del método, empezando por el nº 1. Por ejemplo, teniendo 2 sobrecargas:

_`Intersection1_IntersectionIsFoundWhenPlanesCoincide_Test`_
_`Intersection1_IntersectionIsNotFoundWhenPlanesAreParallelAndNotCoincident_Test`_
_`Intersection2_IntersectionIsFoundWhenPlanesCoincide_Test`_
_`Intersection2_IntersectionIsNotFoundWhenPlanesAreParallelAndNotCoincident_Test`_

**Operadores**

Los operadores serán nombrados usando la palabra "Operator", seguida de una de las sigueintes palabras:
  * `Addition` (A+B)
  * `Subtraction` (A-B)
  * `Multiplication` (A`*`B)
  * `Division` (A/B)
  * `UnaryMinus` (-A)
  * `UnaryPlus` (+A)
  * `Assignation` (A=B)
  * `Equality` (A==B)
  * `Inequality` (A!=B)
  * `GreaterThan` (A>B)
  * `LowerThan` (A<B)
  * `GreaterThanOrEquals` (A>=B)
  * `LowerThanOrEquals` (A<=B)
  * `ShiftLeft` (A<<B)
  * `ShiftRight` (A>>B)
  * `Parenthesis` (A())
  * `Array` (A[.md](.md))
  * `LogOR` (A||B)
  * `LogAND` (A&&B)
  * `LogNOT` (!A)
  * `BitOR` (A|B)
  * `BitAND` (A&B)
  * `BitNOT` (~A)
  * `CastTo``<Type>` (Type())
  * `AdditionAssignation` (A+=B)
  * [...]

Por ejemplo:

_`OperatorMultiplication_ProductIsNotConmutative_Test`_


## Nombre de objetos involucrados ##

**Objetos constantes**

Un objeto constante puede ser tanto una constante en sí, como una variable que no cambiará durante la ejecución del test. Estos objetos deben seguir la nomenclatura de las constantes.

**Objeto bajo pruebas**

Aquella variable que es instancia de la clase bajo pruebas y que ejecutará las acciones que corresponden al test case concreto, deberá ser nombrada de forma parecida a la clase y llevará el sufijo -UT (under test). Por ejemplo:

_triangleUT_

Dado que en muchas ocasiones es difícil identificar al objeto de pruebas, esta norma es opcional.

## Organización interna ##

Cada test case deberá estar mínimamente organizado, al menos, en las 4 fases siguientes (cuando proceda):

**Preparación**

En esta sección de código se crearán todos los objetos necesarios para la realización de la prueba (valores de entrada, valores esperados de salida, etc.). Algo importante a tener en cuenta es que todas las clases que intervienen en el test (excluyendo a la propia clase bajo pruebas y sus ancestros) deben ser "importadas" en esta sección, es decir, debe usarse una sentencia **using** por cada tipo. Por tanto, este tipo de importaciones no aparecerán al principio del fichero, aunque las clases se usen también en otros tests.

**Ejecución**

Es el trozo de código donde la ejecución de aquello que se quiere probar tiene lugar (la ejecución de un método de la instancia de la clase bajo pruebas, por ejemplo).

**Verificación**

Es la parte en que se realizan todas las comprobaciones para conocer si el test ha pasado o ha fallado, es decir, si se cumplen o no las condiciones esperadas en base a las acciones ejecutadas.

_Nota:_ Cuando se usen funciones de comprobación donde se comprueba que un par de valores son iguales o no, el parámetro izquierdo debe ser el resultado a comprobar, y el parámetro derecho el valor de referencia (normalmente constante).

**Limpieza**

Si la preparación de la prueba requirió la reserva de recursos o la realización de cambios en sistemas externos, este es el lugar donde liberarlo y restaurarlo todo.

## Artefactos especiales ##

A menudo algunos test case de mayor complejidad hacen necesaria la creación de artefactos ad-hoc, como los siguientes:

**Mocks**

Los mocks serán nombrados como cualquier clase, añadiendo el sufijo -Mock. Deben estar definidos en ficheros independientes siguiendo las normas de una clase normal.

**Derivaciones para pruebas de caja blanca**

A veces es necesario crear una clase derivada de la que está siendo probada para poder acceder a sus métodos protegidos, ya sea para falsearlos o para probarlos directamente. Las clases creadas para tal efecto deben estar en ficheros independientes y seguir las normas de nomenclatura de cualquier clase, añadiendo el sufijo -`WhiteBox` (cuando se pretendan testear métodos no públicos) o -Mocked, si se pretende trucar el comportamiento interno.

## Documentación ##

La documentación de los test case consiste en un bloque _summary_ que explica brevemente en qué consiste la prueba. No es deseable dedicar demasiado tiempo a la documentación de tests dado que estos pueden cambiar con relativa frecuencia y pueden aparecer más inconsistencias cuanto más texto haya que revisar. Internamente, el test puede estar escrito siguiendo un estilo "self-explained", de manera que no sean necesarios comentarios ya que, generalmente, un unit test debería ser corto y sencillo. En casos complejos (habría que estudiar si se debería partir en varios) sí será obligatorio describir el proceso de la prueba.