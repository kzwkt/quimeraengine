# TinyXML #

## Descripción ##

TinyXML es un pequeño parser XML fácilmente integrable en otros programas.

TinyXML parsea un documento XML y contruye un árbol DOM que puede ser recorrido, modificado y guardado en disco u otro stream de salida. Se puede también construir un árbol con objetos C++ o desde un string y escribirlo a disco como documento XML.

TinyXML está diseñado para ser rápido y fácil de aprender. Tiene dos archivos ".h" y cuatro archivos ".cpp". No depende de excepciones ni de RTTI, y puede ser compilado con soporte STL o sin él. Soporta completamente UTF-8. En principio, los proyectos que vienen con la distribución están preparados para generar una librería estática.

Está desarrollado bajo licencia Zlib, que permite su uso en código open source y comercial.

No soporta DTD ni XSL.

Hay dos proyectos relacionados con TinyXML:

  * [TinyXPath](http://tinyxpath.sourceforge.net): es un pequeño parser xPath
  * [TinyXML++](http://code.google.com/p/ticpp/): una nueva interfaz de TinyXML más puramente c++, con templates, excepciones y mejor control de errores.

## Utilización ##

Vamos a trabajar sobre este xml:
```
<?xml version="1.0" standalone="no" ?>
<!-- Our to do list data -->
<ToDo>
    <!-- Do I need a secure PDA? -->
    <Item priority="1" distance="close">Go to the
        <bold>Toy store!</bold>
    </Item>
    <Item priority="2" distance="none">Do bills</Item>
    <Item priority="2" distance="far &amp; back">Look for Evil Dinosaurs!</Item>
</ToDo>
```


En principio se debe incluir al menos un include:

```
#include "tinyxml.h"
```

Para parsear un documento, simplemente declarar la variable y parsear:

```
TiXmlDocument doc( "demotest.xml" );
bool loadOkay = doc.LoadFile();
```

Para recorrerlo, como siempre, iterando y navegando por childs, attributes, etc.
A los hijos de un nodo dado se puede acceder por nombre:

```
TiXmlNode* node = 0;

// Get the "ToDo" element.
// It is a child of the document, and can be selected by name.
node = doc.FirstChild( "ToDo" );
assert( node );
```

Se puede modificar el DOM. Por ejemplo, para modificar un atributo:
```
TiXmlElement* todoElement = 0;
TiXmlElement* itemElement = 0;

todoElement = node->ToElement();
assert( todoElement  );

// Going to the toy store is now our second priority...
// So set the "priority" attribute of the first item in the list.
node = todoElement->FirstChildElement();	// This skips the "PDA" comment.
assert( node );
itemElement = node->ToElement();
assert( itemElement  );
itemElement->SetAttribute( "priority", 2 );

// Change the distance to "doing bills" from
// "none" to "here". It's the next sibling element.
itemElement = itemElement->NextSiblingElement();
assert( itemElement );
itemElement->SetAttribute( "distance", "here" );
```

Eliminamos un nodo:

```
// Remove the "Look for Evil Dinosaurs!" item.
// It is 1 more sibling away. We ask the parent to remove
// a particular child.
itemElement = itemElement->NextSiblingElement();
todoElement->RemoveChild( itemElement );
```

Añadimos un subárbol a un nodo:
```
// Add some meetings.
TiXmlElement item( "Item" );
item.SetAttribute( "priority", "1" );
item.SetAttribute( "distance", "far" );

TiXmlText text( "Talk to:" );

TiXmlElement meeting1( "Meeting" );
meeting1.SetAttribute( "where", "School" );

TiXmlElement meeting2( "Meeting" );
meeting2.SetAttribute( "where", "Lunch" );

TiXmlElement attendee1( "Attendee" );
attendee1.SetAttribute( "name", "Marple" );
attendee1.SetAttribute( "position", "teacher" );

TiXmlElement attendee2( "Attendee" );
attendee2.SetAttribute( "name", "Voel" );
attendee2.SetAttribute( "position", "counselor" );

// Assemble the nodes we've created:
meeting1.InsertEndChild( attendee1 );
meeting1.InsertEndChild( attendee2 );
item.InsertEndChild( text );
item.InsertEndChild( meeting1 );
item.InsertEndChild( meeting2 );

// And add the node to the existing list after the first child.
node = todoElement->FirstChild( "Item" );
assert( node );
itemElement = node->ToElement();
assert( itemElement );
todoElement->InsertAfterChild( itemElement, item );
```

Guardamos los cambios (se puede "guardar como" pasando un nombre como parámetro):
```
doc.savefile();
```

Este sería el nuevo xml:
```
<?xml version="1.0" standalone="no" ?>
<!-- Our to do list data -->
<ToDo>
    <!-- Do I need a secure PDA? -->
    <Item priority="2" distance="close">Go to the
        <bold>Toy store!</bold>
    </Item>
    <Item priority="1" distance="far">Talk to:
        <Meeting where="School">
            <Attendee name="Marple" position="teacher" />
            <Attendee name="Voel" position="counselor" />
        </Meeting>
        <Meeting where="Lunch" />
    </Item>
    <Item priority="2" distance="here">Do bills</Item>
</ToDo>
```