# PugiXML #

## Descripción ##
Página oficial: [pugixml](http://code.google.com/p/pugixml/)

Pugixml es una pequeña librería escrita en C++ para el proceso de documentos XML.

Implementa:

  * Interface DOM con posibilidad de modificación del árbol.
  * Parser sin validación extremadamente rápido.
  * XPath 1.0.
  * Soporte completo Unicode.

Es una librería muy portable y fácil de integrar. Se distribuye bajo licencia MIT, que permite su uso libremente tanto en aplicaciones open-source como propietarias.

La versión actual es la 0.9.

## Utilización ##
Para utilizarla, lo único que hay que hacer es agregar los siguientes archivos a nuestro proyecto (van incluidos en la prueba de concepto):

```
    pugixml.cpp
    pugixml.hpp
    pugiconfig.hpp
```

Luego solo hay que declarar una variable que contenga el documento parseado y en su caso el primer nodo (root):

```
pugi::xml_document doc;

// Se carga el documento
pugi::xml_parse_result result = doc.load_file("players.xml");

// Se comprueba que el documento se ha parseado bien
std::cout << "Load result: " << result.description() << std::endl;

// Se asigna a una variable el primer nodo del documento
pugi::xml_node players = doc.first_child();
```

Se puede recorrer el documento iterativamente (programáticamente) o hacer búsqueda mediante condiciones. Para esto último, es necesario definir una función bool que devuelva true cuando se cumpla la condición:

```
// Esta es la función que hace de predicado. Debe ser una funcion bool
// que compare la propiedad buscada (nombre, atributo, valor, etc) con un
// valor dado que es el buscado. La función debe llevar como parámetro
// un xml_node. No he probado si se pueden poner más parámetros para hacer
// predicados genéricos

bool buscanombre(pugi::xml_node node)
{
    return (!strcmp(node.name(), "PlayerList"));
}
```

A esta función se la llama desde nuestro código de la siguiente manera:

```
// La función find_node hace una búsqueda recursiva sobre el SUBárbol que define el nodo al que se aplica. 
//Es decir, se debe aplicar a un nodo que sea padre en algún grado del nodo buscado.

std::cout << "Encontrado: " << players.find_node(buscanombre).name() << std::endl;
```

## Prueba de Concepto ##
> [POCpugiXML](http://code.google.com/p/quimeraengine/source/browse/#svn/team/poc/Task%205%20-%20XML%20Parsing/POCpugiXML)