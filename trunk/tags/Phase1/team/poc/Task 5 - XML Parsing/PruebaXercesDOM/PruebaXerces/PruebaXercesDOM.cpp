// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMLSParser.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>

// Para escribir el XML
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include "PruebaXercesDOM.h"

#include <string.h>
#include <stdlib.h>

#if defined(XERCES_NEW_IOSTREAMS)
#include <fstream>
#else
#include <fstream.h>
#endif



void escribirXML(DOMDocument *doc, char *path)
{
   // Return the first registered implementation that has the desired features.
   // In this case, we are after a DOM implementation that has the LS feature... or Load/Save.
    DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(L"LS");

    // Create a DOMLSSerializer which is used to serialize a DOM tree into an XML document.
    DOMLSSerializer *serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();

    // Make the output more human readable by inserting line feeds.
    if (serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
        serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

    // The end-of-line sequence of characters to be used in the XML being written out.
    serializer->setNewLine(XMLString::transcode("\r\n"));
	
    // Convert the path into Xerces compatible XMLCh*.
    XMLCh *tempFilePath = XMLString::transcode(path);

    // Specify the target for the XML output.
    XMLFormatTarget *formatTarget = new LocalFileFormatTarget(tempFilePath);

    // Create a new empty output destination object.
    DOMLSOutput *output = ((DOMImplementationLS*)implementation)->createLSOutput();

    // Set the stream to our target.
    output->setByteStream(formatTarget);

    // Write the serialized output to the destination.
    serializer->write(doc, output);

    // Cleanup.
    serializer->release();
    XMLString::release(&tempFilePath);
    delete formatTarget;
    output->release();
}

int main (void)
{
   // Variable que indica cuándo validar. Valores:
   // AbstractDOMParser::Val_Never; (0)
   // AbstractDOMParser::Val_Always; (1)
   // AbstractDOMParser::Val_Auto; (2)
   AbstractDOMParser::ValSchemes valScheme = AbstractDOMParser::Val_Always;
   // Variable que indica si sacar por pantalla los nodos o no
   bool printOutEncounteredEles = true;
   // Control de errores
   bool errorOccurred = false;
   // Nombre del documento
   const char*                xmlFile = 0;

   // Se inicializa xerces. Se puede inicializar a un lenguaje (en_US, es_ES, ...), en cuyo caso sería:
   //XMLPlatformUtils::Initialize("es_ES");
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

   // Instantiate the DOM parser. El parser es LS: Load and save
    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);
    DOMLSParser       *parser = ((DOMImplementationLS*)impl)->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

	// Se establecen opciones de configuración
    DOMConfiguration  *config = parser->getDomConfig();

   // Si se quiere que procese namespaces
    config->setParameter(XMLUni::fgDOMNamespaces, true);
   // Si se quiere que procese schema
    config->setParameter(XMLUni::fgXercesSchema, true);
   // ?
    config->setParameter(XMLUni::fgXercesHandleMultipleImports, true);
   // full schema constraint checking ?
    config->setParameter(XMLUni::fgXercesSchemaFullChecking, false);

   // Dejo las 3 opciones de validación, aunque lo he definido como Val_Auto
    if (valScheme == AbstractDOMParser::Val_Auto)
      config->setParameter(XMLUni::fgDOMValidateIfSchema, true);
    else if (valScheme == AbstractDOMParser::Val_Never)
      config->setParameter(XMLUni::fgDOMValidate, false);
    else if (valScheme == AbstractDOMParser::Val_Always)
        config->setParameter(XMLUni::fgDOMValidate, true);

   // enable datatype normalization - default is off
    config->setParameter(XMLUni::fgDOMDatatypeNormalization, true);

   // Crea el error handler para manejar los errores de parseo
    DOMCountErrorHandler errorHandler;
    config->setParameter(XMLUni::fgDOMErrorHandler, &errorHandler);

    // Cambiar entre estas 2 lineas para ver un archivo que falle a la validación.
	// Tiene únicamente un nombre de tag cambiado que no aparece en el Schema
	//xmlFile = "arena_invalid.xml";
    xmlFile = "arena.xml";
   
    //reset error count first
    errorHandler.resetErrors();

    XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument *doc = 0;

    try
    {
		// Parsea el documento. Nota: para rutas absolutas, creo que hay que usar file://
        doc = parser->parseURI(xmlFile);
    }

    catch (const XMLException& toCatch)
    {
        XERCES_STD_QUALIFIER cerr << "\nError during parsing: '" << xmlFile << "'\n"
             << "Exception message is:  \n"
             << StrX(toCatch.getMessage()) << "\n" << XERCES_STD_QUALIFIER endl;
        errorOccurred = true;

    }
    catch (const DOMException& toCatch)
    {
        const unsigned int maxChars = 2047;
        XMLCh errText[maxChars + 1];

        XERCES_STD_QUALIFIER cerr << "\nDOM Error during parsing: '" << xmlFile << "'\n"
             << "DOMException code is:  " << toCatch.code << XERCES_STD_QUALIFIER endl;

        if (DOMImplementation::loadDOMExceptionMsg(toCatch.code, errText, maxChars))
             XERCES_STD_QUALIFIER cerr << "Message is: " << StrX(errText) << XERCES_STD_QUALIFIER endl;

        errorOccurred = true;
    }
    catch (...)
    {
        XERCES_STD_QUALIFIER cerr << "\nUnexpected exception during parsing: '" << xmlFile << "'\n";
        errorOccurred = true;
    }

    
    if (errorHandler.getSawErrors())
    {
        XERCES_STD_QUALIFIER cout << "\nErrors occurred, no output available\n" << XERCES_STD_QUALIFIER endl;
        errorOccurred = true;
    }
    else
    {
        unsigned int elementCount = 0;
		DOMNode *nodo;
		DOMNodeList *lista;
		XMLCh *tagname;

		// Cojo el primer nodo (_root)
		nodo = (DOMNode *)doc->getDocumentElement();
		char *name = XMLString::transcode(nodo->getNodeName());
		XERCES_STD_QUALIFIER cout <<"ROOT: "<< name << XERCES_STD_QUALIFIER endl;

		// Busco nodos por tag name
		// Hay que usar transcode porque todas estas funciones usan y devuelven XMLCh*
		tagname = XMLString::transcode("Team");
		
		// Me devuelve una lista de nodos que cumplen
		lista = doc->getElementsByTagName(tagname);

		//Añadiendo nodos (Añadimos un nuevo equipo con su ID y su nombre)
		DOMNode *ultimo = lista->item(0);
		DOMNode *nuevo = (DOMNode *)doc->createElement(XMLString::transcode("Team"));
		DOMNode *nuevohijo1 = (DOMNode *)doc->createElement(XMLString::transcode("TeamID"));
		DOMNode *nuevohijo2 = (DOMNode *)doc->createElement(XMLString::transcode("TeamName"));

		// Añado los valores en esos tags
		nuevohijo1->setTextContent(XMLString::transcode("988592"));
		nuevohijo2->setTextContent(XMLString::transcode("Fernanduco4"));

		// Se los añado como hijos, en orden, al nuevo nodo.
		nuevo->appendChild(nuevohijo1);
		nuevo->appendChild(nuevohijo2);

		// Añado el nuevo nodo como hijo
		ultimo->getParentNode()->appendChild(nuevo);

		// Los recorro. La lista es "live" y se autoactualiza
		for (XMLSize_t i=0; i<lista->getLength(); i++)
		{
			if (lista->item(i)->hasChildNodes()) 
			{
				DOMNodeList *hijos = lista->item(i)->getChildNodes();
				for (XMLSize_t j=0; j<hijos->getLength(); j++)
				{
					// Cuidadin, parece que según con que edites el xml o lo que sea hay retornos 
					// de carro que se convierten en nodos vacíos al parsearlos ¿¿¿??? Es la impresión que da
					// Efectivamente, he leido que tanto los espacios como los retornos de carro son nodes, 
					// hay que hacer siempre la comprobación de tipo de nodo
					if (hijos->item(j)->getNodeType() == DOMNode::ELEMENT_NODE)
					{
						char *value = XMLString::transcode(hijos->item(j)->getTextContent());
						char *name = XMLString::transcode(hijos->item(j)->getNodeName());
						XERCES_STD_QUALIFIER cout << name << ": "<< value << XERCES_STD_QUALIFIER endl;
						
					}
				}
				
			}
		}

		escribirXML(doc, "arena2.xml");

		/*
        if (doc) {
            elementCount = countChildElements((DOMNode*)doc->getDocumentElement(), printOutEncounteredEles);
            // test getElementsByTagName and getLength
            XMLCh xa[] = {chAsterisk, chNull};
            if (elementCount != doc->getElementsByTagName(xa)->getLength()) {
                XERCES_STD_QUALIFIER cout << "\nErrors occurred, element count is wrong\n" << XERCES_STD_QUALIFIER endl;
                errorOccurred = true;
            }
        }*/

        // Print out the stats that we collected and time taken.
		XERCES_STD_QUALIFIER cout << XERCES_STD_QUALIFIER endl;
        XERCES_STD_QUALIFIER cout << "Pulsa una tecla para continuar" << XERCES_STD_QUALIFIER endl;
    }
   
    //  Delete the parser itself.  Must be done prior to calling Terminate, below.
    parser->release();

    // And call the termination method
    XMLPlatformUtils::Terminate();

   getchar();
   
   if (errorOccurred)
        return 4;
    else
        return 0;
}

DOMCountErrorHandler::DOMCountErrorHandler() :

    fSawErrors(false)
{
}

DOMCountErrorHandler::~DOMCountErrorHandler()
{
}


// ---------------------------------------------------------------------------
//  DOMCountHandlers: Overrides of the DOM ErrorHandler interface
// ---------------------------------------------------------------------------
bool DOMCountErrorHandler::handleError(const DOMError& domError)
{
    fSawErrors = true;
    if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
        XERCES_STD_QUALIFIER cerr << "\nWarning at file ";
    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
        XERCES_STD_QUALIFIER cerr << "\nError at file ";
    else
        XERCES_STD_QUALIFIER cerr << "\nFatal Error at file ";

    XERCES_STD_QUALIFIER cerr << StrX(domError.getLocation()->getURI())
         << ", line " << domError.getLocation()->getLineNumber()
         << ", char " << domError.getLocation()->getColumnNumber()
         << "\n  Message: " << StrX(domError.getMessage()) << XERCES_STD_QUALIFIER endl;

    return true;
}

void DOMCountErrorHandler::resetErrors()
{
    fSawErrors = false;
}