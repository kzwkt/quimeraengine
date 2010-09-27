
// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include "SAX2Print.hpp"
#include <xercesc/util/OutOfMemoryException.hpp>
#include "SAX2FilterHandlers.hpp"

// ---------------------------------------------------------------------------
//  Local data
//
//  encodingName
//      The encoding we are to output in. If not set on the command line,
//      then it is defaulted to LATIN1.
//
//  xmlFile
//      The path to the file to parser. Set via command line.
//
//  valScheme
//      Indicates what validation scheme to use. It defaults to 'auto', but
//      can be set via the -v= command.
//
//	expandNamespaces
//		Indicates if the output should expand the namespaces Alias with
//		their URI's, defaults to false, can be set via the command line -e
// ---------------------------------------------------------------------------
static const char*              encodingName    = "LATIN1";
static SAX2XMLReader::ValSchemes valScheme      = SAX2XMLReader::Val_Auto;
static bool					    expandNamespaces= false ;
// Para que use el schema han de estar a true estas 2 variables:
static bool                     doNamespaces    = true;
static bool                     doSchema        = true;
//
static bool                     schemaFullChecking = false;
static bool                     namespacePrefixes = false;
static bool                     sortAttributes  = false;

// Variables para inicializar y configurar el parser
SAX2XMLReader* parser = NULL;
SAX2XMLReader* reader = NULL;
SAX2XMLReader* filter = NULL;


void imprimeNodo (SAX2DocHandler *handler)
{

	// Imprime los nodos y sus atributos si los hay
	// Si no se pasa handler como puntero da un error de acceso a la clase DefaultHandler

	XERCES_STD_QUALIFIER cout << "Atributos del Nodo " << handler->getTagName().c_str() << ":" << XERCES_STD_QUALIFIER endl;
				
	std::vector<std::string> name = handler->getAttrName();
	std::vector<std::string> type = handler->getAttrType();
	std::vector<std::string> value = handler->getAttrValue();
	for (std::size_t index=0; index<name.size(); index++)
	{
		XERCES_STD_QUALIFIER cout	<< "Nombre: '" << name.at(index).c_str()
									<< "' - Tipo: '" << type.at(index).c_str()
									<< "' - Valor: '" << value.at(index).c_str() << "'"
									<< XERCES_STD_QUALIFIER endl;
	}
}

void configuraParser()
{

	// Originalmente, esto estaba puesto para seleccionar un tipo de parser
	// según si se elegía imprimir los nodos en orden alfabético o no
	// lo conservo por que sirva de referencia pero no se usa

	reader = XMLReaderFactory::createXMLReader();

	if(sortAttributes)
    {
        filter=new SAX2SortAttributesFilter(reader);
        parser=filter;
    }
    else
        parser=reader;

    // Configuraciones varias
    if (valScheme == SAX2XMLReader::Val_Auto)
    {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(XMLUni::fgXercesDynamic, true);
    }

    if (valScheme == SAX2XMLReader::Val_Never)
    {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, false);
    }

    if (valScheme == SAX2XMLReader::Val_Always)
    {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(XMLUni::fgXercesDynamic, false);
    }

    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, doNamespaces);
    parser->setFeature(XMLUni::fgXercesSchema, doSchema);
    parser->setFeature(XMLUni::fgXercesHandleMultipleImports, true);
    parser->setFeature(XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, namespacePrefixes);
}

// ---------------------------------------------------------------------------
//  Program entry point
// ---------------------------------------------------------------------------
int main(void)
{
    // Inicializa la librería
    try
    {
         XMLPlatformUtils::Initialize();
    }

    catch (const XMLException& toCatch)
    {
         XERCES_STD_QUALIFIER cerr << "Error during initialization! :\n"
              << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
         return 1;
    }

    
    // Crea el parser y lo configura	
	configuraParser();

    int errorCount = 0;
    int errorCode = 0;
    try
    {

		// Decidimos el archivo que parseará y el nodo que buscamos

		// Se añade linea para parsear un archivo invalido respecto al XSD. 
		// Se ha eliminado un atributo etiquetado como required
		
		//XMLCh *xmlFile= XMLString::transcode("attrib_invalid.xml");
		XMLCh *xmlFile= XMLString::transcode("attrib.xml");
		
		std::string MiNodo = "ThemeInfo";

		// Instanciamos nuestra clase manejadora
        SAX2DocHandler handler(encodingName, expandNamespaces);

		// Esta variable es necesaria para el parseo discontinuo que hacemos
		// No se hace nada con ella, solo pasarla en parseFirst y parseNext
		XMLPScanToken token;
		
		// Asignamos el manejador al parser
        parser->setContentHandler(&handler);
        parser->setErrorHandler(&handler);

		// Esto es para parsear todo el documento del tirón, no como lo hago ahora que es nodo a nodo
		// Lo dejo comentado como referencia
        // parser->parse(xmlFile); 

		// Parseo la primera línea
		parser->parseFirst(xmlFile, token);

		// Si no es el nodo buscado, sigo parseando las siguientes líneas hasta que lo encuentro
		// o se acaba el documento(parser->parseNext devolvería False
		if (strcmp(handler.getTagName().c_str(), MiNodo.c_str()))
			while(strcmp(handler.getTagName().c_str(), MiNodo.c_str()) && parser->parseNext(token));
		
		// si ha habido errores de parseo, esto los devuelve
		errorCount = parser->getErrorCount();
		
		// Si no ha habido errores, haríamos lo que quisieramos con los datos del nodo
		// En este caso sacarlos por pantalla.
		// Vuelvo a repetir que si no se pasa como handler como puntero, da un error de acceso
		// a la clase DefaultHandler
		if (!errorCount)
			imprimeNodo(&handler);

		// Escojo otro nodo
		MiNodo = "Slider";
		// Sigo parseando hasta que lo encuentre o se acabe el documento
		while(strcmp(handler.getTagName().c_str(), MiNodo.c_str()) && parser->parseNext(token));

		errorCount = parser->getErrorCount();
		
		if (!errorCount)
			imprimeNodo(&handler);

    }
    catch (const OutOfMemoryException&)
    {
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        errorCode = 5;
    }
	
    catch (const XMLException& toCatch)
    {
        XERCES_STD_QUALIFIER cerr << "\nAn error occurred\n  Error: "
             << StrX(toCatch.getMessage())
             << "\n" << XERCES_STD_QUALIFIER endl;
        errorCode = 4;
    }

    if(errorCode) {
        XMLPlatformUtils::Terminate();
        return errorCode;
    }

    // Nos cargamos el parser, siempre antes de terminar la librería
    delete reader;
    if(filter)
        delete filter;

    // Nos cargamos la librería
    XMLPlatformUtils::Terminate();

	getchar();

    if (errorCount > 0)
        return 4;
    else
        return 0;
}
