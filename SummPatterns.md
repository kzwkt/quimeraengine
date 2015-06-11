# Convención de Patrones #



## Enumeradores ##
Versión normal
```
// Archivo .h
enum EQEnumeration
{
     Value1,
     Value2,
     Value3
};
```

```
Objeto->SetPropertyThatNeedsEnumAsParameter( Value1);
EQEnumeration myEnum = Value2;
Objeto->SetPropertyThatNeedsEnumAsParameter( myEnum );
```

Versión modificada
```
// Archivo .h
#include <string>
#include <vector>
#include <map>

const int FORCE_DWORD = 0xFFFFFFFF;

class EQEnumeration
{
public:
    enum EnumType
    {
        Value1,
        Value2,
        Value3,
        NotEnumValue = FORCE_DWORD // Fuerza al compilador a tratar el enum como un DWORD (32 bits en Windows-32 y 64 bits en Windows-64).
    };

    EQEnumeration(const int &nValue);
    EQEnumeration& operator=(const int &nValue);
    operator int() const;
    EQEnumeration& operator=(const std::string &strValue);
    bool operator==(const std::string &strValue);
    operator const std::string() const;

private:
    static std::pair<std::string, EQEnumeration::EnumType> s_arValueName[];
    static std::map<std::string, EQEnumeration::EnumType> s_mapValueName;
   
    EQEnumeration::EnumType _value;
};
```

```
// Archivo .cpp
std::pair<std::string, EQEnumeration::EnumType> EQEnumeration::s_arValueName[] =
{
    std::pair<std::string, EQEnumeration::EnumType>("Value1", EQEnumeration::Value1),
    std::pair<std::string, EQEnumeration::EnumType>("Value2", EQEnumeration::Value2),
    std::pair<std::string, EQEnumeration::EnumType>("Value3", EQEnumeration::Value3)
};

std::map<std::string, EQEnumeration::EnumType> EQEnumeration::s_mapValueName (
    EQEnumeration::s_arValueName,
    &EQEnumeration::s_arValueName[0] + sizeof(EQEnumeration::s_arValueName) / sizeof(EQEnumeration::s_arValueName[0])  // puntero al último elemento del array (usando aritmética de punteros)
);

EQEnumeration::EQEnumeration(const int &nValue)
{
    _value = static_cast<EQEnumeration::EnumType>(nValue);
}

EQEnumeration& EQEnumeration::operator=(const int &nValue)
{
    return ( _value = static_cast<EQEnumeration::EnumType>(nValue) );
}

EQEnumeration::operator int() const
{
    return static_cast<int>(_value);
}

EQEnumeration& EQEnumeration::operator=(const std::string &strValue)
{
    return (_value = EQEnumeration::s_mapValueName[strValue]);
}

bool EQEnumeration::operator==(const std::string &strValue)
{
    return (_value == EQEnumeration::s_mapValueName[strValue]);
}

EQEnumeration::operator const std::string() const
{
    // Busca un valor (y no una clave) en el mapa que coincida con el almacenado, y devuelve su clave asociada
    // Ojo, se puede hacer éste tipo de búsqueda porque sabemos que los valores van a ser únicos
    std::map<std::string, EQEnumeration::EnumType>::iterator iValueName = EQEnumeration::s_mapValueName.begin();
    std::map<std::string, EQEnumeration::EnumType>::const_iterator iValueNameEnd = EQEnumeration::s_mapValueName.end();

    while(iValueName != iValueNameEnd && iValueName->second != _value)
        ++iValueName;
   
    if(iValueName != iValueNameEnd)
        return iValueName->first;
    else
        throw QElementNotFoundException();
}
```

```
Objeto->SetPropertyThatNeedsEnumAsParameter( EQEnumeration::Value1);
EQEnumeration myEnum = EQEnumeration::Value2;
Objeto->SetPropertyThatNeedsEnumAsParameter( myEnum );
```

## Interfaces ##
```
class IQInterface
{
protected:                                          // Ocultamos lo siguiente

    IQInterface(){};                                // Constructor por defecto: Cuerpo vacío

    virtual ~IQInterface(){};                       // Destructor: Virtual, con cuerpo vacío

private:

    IQInterface(const IQInterface& );               // Constructor de copia: Sin cuerpo

    IQInterface& operator=(const IQInterface& );    // Operador de copia/asignación: Sin cuerpo

public:                                             // Sólo métodos públicos, propios de la interfaz concreta

    virtual void IQMethod1()=0;                     // Virtual puro, requiere implementación

    // Sin atributos
   
};
```

```
class QImplementation : public IQInterface  // Herencia pública
{
protected:                  // Accesibilidad opcional

    QImplementation();      // Declaración del constructor por defecto, opcional (cuerpo en el .cpp)

    ~QImplementation();     // Declaración del destructor obligatoria al ser virtual (cuerpo en el .cpp)

    // Operador de copia/asignación y constructor de copia no se declaran

public:
   
    void IQMethod1();       // Implementación obligatoria de métodos públicos de la interfaz (cuerpo en el .cpp)

protected:

    // Métodos y Atributos de la implementación

};
```