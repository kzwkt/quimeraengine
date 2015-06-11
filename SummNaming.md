# Convención de Nombres #

  * **Archivos de cabecera y de implementación**: `NombreClase.h` / `NombreClase.cpp`.
  * **Definiciones #ifndef ... #define ... [código] ... #endif**: `__NOMBRECLASE__`.
  * **Inclusiones STL**: `<string>`.
  * **Namespaces**: (`PascalCase`, Equipo::Proyecto::Dominio) `KinesisTeam::QuimeraEngine::Core`.
  * **Clases, Clases anidadas**: (`PascalCase`, Prefijo Q) `QSceneElement`.
  * **Interfaces**: (`PascalCase`, Prefijo IQ) `IQSceneObject`.
  * **Variables**:
    * **Prefijos generales**:
      * **int** (Prefijo n): `int nNumero`.
      * **unsigned int** (Prefijo u): `unsigned int uNumero`.
      * **iterator** (Prefijo i): `iterator iVueltas` (salvo i, j, k, etc.).
      * **float** (Prefijo f): `float fNumero`.
      * **DWORD** (Prefijo dw): `DWORD dwPalabra`.
      * **WORD** (Prefijo w): `WORD wPalabra`.
      * **Cadenas** (Prefijo sz): `Char* szCadena`.
      * **Puntero** (Prefijo p): `int *pNumero`.
      * **string** (Prefijo str): `std::string strCadena`.
      * **bool** (Prefijo b): `bool bEsCierto`.
      * **array y std::vector** (Prefijo ar): `float arNuemro[8]` (no resto estructuras)
    * **no-miembro, locales y no-estáticas** (`CamelCase`, Prefijo general) : `int nNumero`
    * **no-miembro, locales y estáticas** (`static_` + Prefijo general): `static_nNumero`.
    * **miembro no-estáticas** (`_` + Prefijo general): `_nNumero`.
    * **miembro estáticas** (`s_` + Prefijo general): `s_nNumero`.
  * **Constantes** (Sin prefijo, mayusculas, palabras separadas): GRAPHIC\_DEVICE\_FLAG.
  * **Métodos y propiedades, de instancia o estáticos** (`PascalCase`): `GetMethod()`.
  * **Typedef:**
    * **A nivel de librería**: Mismas normas que siga el original.
    * **Ámbito concreto** (Prefijo TQ): `typedef std::vector<int>::iterator TQVectorIterator`.
  * **Enumerados**
    * **Nombre** (`PascalCase`, singular, Prefijo EQ): `enum EQObjectType`.
    * **Valores** (`PascalCase`, Sin Prefijo): `enum EQObjectType { Camera = 0, Mesh = 1 }`.