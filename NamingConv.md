# Convención de Nombres #

**Archivos de cabecera y de implementación:** Se llaman igual que la clase o interfaz que esté declarada en su interior. Las extensiones de archivo serán .h para los de cabecera y .cpp para los de implementación.

Ejemplo: `NombreClase`.h / `NombreClase`.cpp.

**Definiciones para evitar inclusiones múltiples (#ifndef ... #define ... [código] #endif):** Se compondrá de 2 guiones bajos al principio, el nombre de la clase o interfaz que se declare en el archivo, en mayúsculas, y por último otros 2 guiones bajos.

Ejemplo: `__`NOMBRECLASE`__`.

**Las inclusiones de librerías de la STL:** Siempre van entre ángulos.

Ejemplo: `<`string`>`.

**Namespaces:** Se usará `PascalCase`. Se dividirá en: Nombre del equipo, Nombre del proyecto, Nombre del Dominio.

Ejemplo: `KinesisTeam`::`QuimeraEngine`::Core.

**Clases:** Se usará `PascalCase`, poniendo como prefijo una Q, de Quimera, mayúscula.

Ejemplo: QSceneElement.

**Interfaces:** Igual que las clases, pero anteponiendo, además, una I mayúscula.

Ejemplo: IQSceneObject.

**Clases anidadas:** Igual que las clases normales.

Ejemplo: QTreeNode.

**Variables no-miembro, locales y no-estáticas:** Se usará camelCase. Los siguientes prefijos serán obligatorios para cada tipo:

  * n --> int con signo.
  * u --> int sin signo.
  * i --> iterador, salvo enteros nombrados como i, j, k, etc.
  * f --> float.
  * dw --> DWORD.
  * w --> WORD
  * sz --> Char`*`.
  * p --> punteros en general.
  * str --> std::string.
  * b --> bool.
  * ar --> arrays y std::vector, no para el resto de estructuras.
  * v --> vectores (álgebra).
  * q --> cuaterniones (álgebra).

Pueden añadirse otros prefijos opcionalmente, siempre que no induzcan a confusión.

Ejemplo: int nNumero; float `arFloats[8]`;.

**Variables miembro no-estáticas:** Igual que las no-miembro locales pero anteponiendo una "m" y un guión bajo delante.

Ejemplo: `m_`nCount.

**Constantes:** Sin prefijos, todo en mayúscula y separando palabras con guiones bajos (podrán tener prefijos sólo en aquellos casos donde la legibilidad se vea muy afectada). Se excluyen de esta norma los parámetros función de tipo constante, que seguirán la convención de las variables locales. El nombre de las constantes locales no puede empezar por "Q" ni por "QE", prefijos que quedan reservados constantes globales o de configuración.

Ejemplo: GRAPHIC\_DEVICE\_FLAG.

**Variables no-miembro locales estáticas:** Igual que cualquier variable local pero anteponiendo el prefijo static_._

Ejemplo: static\_nCount.

**Variables miembro estáticas:** Igual que las variables miembro pero anteponeindo además una s.

Ejemplo: sm\_pMember.

**Métodos y propiedades, de instancia o estáticos:** Usarán `PascalCase`, sin ningún tipo de prefijo o postfijo. Nunca podrán terminar en un número.

Ejemplo: `GetMethod`().

**Typedef:** Si es a nivel de librería, entonces se nombra siguiendo las reglas del original. Si su ámbito se reduce a un sitio concreto, se usa como prefijo TQ.

Ejemplo: typedef std::vector`<`int`>`::iterator TQVectorIterator.

**Enumerados:** El nombre del enumerado se escribirá con `PascalCase`, en singular, precedido por EQ. Los nombres de los valores no tendrán prefijo, y usarán `PascalCase`.

Ejemplo: enum EQObjectType { Camera = 0, Mesh = 1 }.

**General:** Nombres descriptivos, aunque sean algo largos. En casos obvios, acortarlos lo máximo posible.

Ejemplo: strNewConventionName.


Esta lista está sujeta a cambios derivados de propuestas del equipo, bien justificadas, y así como de improbables efectos negativos en la legibilidad y productividad. Está basada en parte en la experiencia personal y en parte en estándares de facto.