# Eternity Official Guide 4.0 #
(Extract)

## Getting started ##

This chapter explains how to install Eternity framework and use it inside your own application.

### Introduction ###

Eternity is a little framework that is comp atible with Standard C++ and is tested to run on several platforms with different IDE (like Microsoft Visual Studio 6 and .NET, KDevelop, Anjuta, C++ Builder, gcc and others).
The instructions in this chapter explain how to use Eternity, beginning with the installation of library and finishing with the distribution of your own application.

### Installation ###

From the web site of Eternity (http://www.winghands.it) is possible to download the framework in various formats:

  * ZIP download: all of Eternity as a single compressed archive file, the .zip format is widely supported on Windows systems;
  * TAR.GZ download: all of Eternity as a single compressed archive file , the .tar.gz format is widely supported on Unix systems;

Decompress Eternity library in any position on your hard disk: at the end of the work what you have is a simply directory named eternity that holds subdirectories. In the rest of this chapter we’ll call INSTALLDIR the main directory (e.g. c:\eternity or /usr/lib/eternity).

Now could be useful to add INSTALLDIR/include (e.g. c:\eternity\include or /usr/lib/eternity/include ) to the PATH environment variable or to the include path of your IDE.
That’s all for installation: there is nothing else to configure or to compile.

### Directories contents ###

The directories installed in INSTALLDIR are the follow ones:
  * src : where the source file are stored;
  * include: the folder to add to your include path
  * examples: where you could found several examples
  * doc : where this manual lies together with the reference handbook

The main directory contains change logs files and license document.

### Configure your project ###

You could enable the use of Eternity in your application following the three steps below (remember to add an include path pointing do INSTALLDIR/include like explain in the previous chapter):

**Step Description**


  1. add the following line to every compile unit in witch you want to use Eternity:
> `#include "eternity/eternity.hpp"`

> 2 add to your project the file with path:

> `INSTALLDIR/src/eternity.cpp`

> make sure this file is compiled by your environment

> 3 remember to enable the RTTI on your compiler

### Dynamic creation ###

Create an object with dynamic creation means instance it in the heap, like the operator new does, but specifying its class only at run-time, for example using a string variable.
Before use dynamic creation you need register the class in the eternity engine using the Factory<> object like in the follow example:

```
//register the class MyObject
factory<MyObject> AFactory;

//instance an empty pointer
MyObject *myObject = NULL;

//dynamic create an object from class MyObject
//and store it in myObject pointer
string className = “MyObject”
create(className, & myObject);
```

In short dynamic creation is like the new operator but you could pass a string to it.
Remember that the factory object used for the registration (in the example AFactory) need to be instanced for all the time that you need dynamic creation although it is not necessary that it could be visible (in the scope) of code that invoke Create() method.
When you have finished dynamic create a class let you feel free to delete the factory object or let it goes out of scope (and so deleted from the stack by compiler).

### Enable your class to binary persistence ###

To make your class ready to be managed by Eternity binary persistence system you have to add a single method and one include.

Step Description

  1. add the following line at the begin of your class definition (if you do not have already added it like show first step of previous paragraph).

> `#include "eternity/eternity.hpp"`

> 2 add a single method to your class:

> `void serialize( bin_archive &stream) ;`

please note that this method does not need to be virtual like in other persistence framework.

> 3 implement the method at step 2 specifying which fields to serialize like in the follow example:

```
void AClass::serialize( bin_archive &stream)
{
    if (stream.is_loading())
    {
        stream >> m_nField1;
        stream >> m_fField2;
        stream >> m_nField3;
    }
    else
    {
        stream << m_nField1;
        stream << m_fField2;
        stream << m_nField3;
    }
}
```

(you could find the complete source code in the directory INSTALLDIR/examples)

The implementation is quite simple, you have only to passing the field you want to serialize to the stream object using the insertion operator (<<) when you are storing and the extraction operator (>>) when you are reading information from a precedent stored archive.

Remember to store and retrieve field in the same order.

### Exceptions handling ###

Eternity system throws exceptions when something goes wrong so is a good practice to enclose the segment of your code that use eternity inside a try catch block, like in the follow example.

```
try
{
    // your code that use eternity
    file_archive fa;
    fa.open("Derived.bin", archive::store);
    myObject.serialize(fa);
    fa.close();
}
catch (eternity::exception e)
{
    cout << "Exception catched: " << e.what() << endl;
}
```

### Storing (and reloading) objects ###

To store an object enable to eternity persistence system (like show in previous paragraph) you could write 4 lines of codes like the follow ones:

```
// instance the persistence archive
file_archive fa;

//open it for storing in a file named Derived.bin
fa.open("Derived.bin", archive::store);

//serialize object
myObject.serialize(fa);

//close archive
fa.close();

The code to reload an object is quite similar.
// instance the persistence archive
file_archive fa;

//open it for loading from a file named Derived.bin
fa.open("Derived.bin", archive::load);

//deserialize object
myObject.serialize(fa);

//close archive
fa.close();
```

There is only one thing to remember: if your class is a pointer to object or if your class contains pointers to other object you need first of all register them to dynamic creation engine of eternity like show in a previous paragraph.

### Enable your class to xml persistence ###

To make your class ready to be managed by Eternity xml persistence system you have to add a single method and one include.

**Step Description**

  1. add the following line at the begin of your class definition (if you do not have already added it like show first step of previous paragraph).

> `#include "eternity/eternity.hpp"`

> 2 add a single method to your class:

> `void xml_serialize( xml_archive &xml)`

> please note that this method does not need to be virtual like in other persistence framework.

> 3 implement the method at step 2 specifying which fields to serialize like in the follow example:

```
void AClass::xml_serialize( xml_archive &xml)
{
    if (xml.is_loading())
    {
        xml.read("Field1", m_nField1 ,0);
        xml.read("Field2", m_fField2, 0);
        xml.read("Field3", m_nField3 ,0);
    }
    else
    {
        xml.write("Field1", m_nField1);
        xml.write("Field3", m_nField3);
        xml.write("Field2", m_fField2);
    }
}
```

(you could find the complete source code in the directory INSTALLDIR/examples)

The implementation specify with fields to store (or load) and what name write for them in the XML archive (the third parameter of xRead is the position from with to read if, for examples, there are more than one with the name request).

Please note that with XML persistence it is not necessary to reload fields in the same order you have stored them because the XML file is not a sequence stream.

### Storing (and reloading) objects with XML ###

To store an object enable to eternity persistence system (like show in previous paragraph) you could write 4 lines of codes like the follow ones:

```
// instance the persistence archive
xml_archive xml;

//open it for storing in a file named Derived.bin
xml.open("Derived.xml", archive::store);

//serialize object
myObject.xml_serialize(xml);

//close archive
xml.close();
```

The code to reload an object is quite similar.

```
// instance the persistence archive
xml_archive xml;

//open it for loading from a file named Derived.bin
fa.open("Derived.xml", archive::load);

//deserialize object
myObject.xml_serialize(xml);

//close archive
xml.close();
```

Please note that the syntax is quite similar to code for binary serialization, the only differences are the archive class to use and the name of persistence method: xml\_serialize() instead of serialize().

Again there is only one thing to remember: if your class is a pointer to object, or if your class contains pointers to other object you need first of all register them to dynamic creation engine of eternity like show in a previous paragraph.

### XML archive example ###

To have an idea of the way eternity stored C++ classes using xml files you could take a look at the follow diagram:

We focus only on template class `TClass<int>` and suppose the xml\_serialize() method look like that:

```
template <class T>
void TClass<T>::xml_serialize( xml_archive &xml)
{
    if (xml.is_loading())
    {
        xml.read("m_TMember", m_TMember,0);
        xml.xRead("m_sText", m_sText ,0);
        xml.get_object("m_pDerived", &m_pDerived[0], 0);
        xml.get_object("m_pDerived", &m_pDerived[1], 1);
        xml.get_stack_object("Derived", m_Derived, 0 );
    }
    else
    {
        xml.write("m_TMember", m_TMember);
        xml.write("m_sText",m_sText);
        xml.put_object("m_pDerived", m_pDerived[0]);
        xml.put_object("m_pDerived", m_pDerived[1]);
        xml.put_stack_object("Derived", m_Derived);
    }
}
```

Note the method use to store and retrieve respectively primitive type (m\_TMember), stack allocated object (m\_Derived) and heap allocated object (m\_pDerived).

The xml archive in storing and object from class `TClass<int>` is quite similar to this one:
```
<?xml version="1.0"?>
<!-- eternity persistence framework -->
<!-- author Nicola Santi - www.winghands.it -->
<Archive version="4.0" sub="1">
    <m_TMember>2000</m_TMember>
    <m_sText>Happy Millenium</m_sText>
    <m_pDerived class="class Derived">
        <m_nABaseMember>2000</m_nABaseMember>
        <m_fABaseMember>1.1</m_fABaseMember>
        <m_nBBaseMember>1</m_nBBaseMember>
    </m_pDerived>
    <m_pDerived position="0" />
    <Derived>
        <m_nABaseMember>2003</m_nABaseMember>
        <m_fABaseMember>3.1</m_fABaseMember>
        <m_nBBaseMember>3</m_nBBaseMember>
    </Derived>
</Archive>
```

Please note that only the first m\_pDerived was store completely: the second one that is a pointer to the same object is managed via eternity double pointer engine, storing only the position in retrieved object array.

Note also those stack allocated objects are correctly indented.

### Redistribution of your application ###

Eternity not use dynamic linked library or any other file at run time so you do not have to redistribute nothing else that your application and the library you need before using Eternity.