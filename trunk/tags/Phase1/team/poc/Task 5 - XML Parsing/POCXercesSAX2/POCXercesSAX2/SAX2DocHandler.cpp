


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include "SAX2Print.hpp"

// ---------------------------------------------------------------------------
//  SAX2DocHandler: Constructor y Destructor
// ---------------------------------------------------------------------------
SAX2DocHandler::SAX2DocHandler( const   char* const encodingName
                                    , const bool expandNamespaces) 
{
	TagName = "";
}

SAX2DocHandler::~SAX2DocHandler()
{

}


// ---------------------------------------------------------------------------
//  SAX2DocHandler: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void SAX2DocHandler::error(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nError at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void SAX2DocHandler::fatalError(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nFatal Error at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void SAX2DocHandler::warning(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nWarning at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

// ---------------------------------------------------------------------------
//  SAX2DocHandler: Overrides of the SAX DTDHandler interface
// ---------------------------------------------------------------------------
void SAX2DocHandler::unparsedEntityDecl(const    XMLCh* const /* name */
                                          , const   XMLCh* const /* publicId */
                                          , const   XMLCh* const /* systemId */
                                          , const   XMLCh* const /* notationName */)
{
    // Not used at this time
}


void SAX2DocHandler::notationDecl(const  XMLCh* const /* name */
                                    , const XMLCh* const /* publicId */
                                    , const XMLCh* const /* systemId */)
{
    // Not used at this time
}


// ---------------------------------------------------------------------------
//  SAX2DocHandler: Overrides of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------

// Esta función es llamada cuando se encuentra un bloque de texto entre tags
void SAX2DocHandler::characters(const     XMLCh* const    chars
                                  , const   XMLSize_t    length)
{
	/*const char *michars;
	XMLSize_t milength;

	michars = XMLString::transcode(chars);
	milength = length;*/
    
}

// Se llama cuando se encuentra el final del documento
void SAX2DocHandler::endDocument()
{
}

// Se llama cuando se encuentra el final de un elemento
void SAX2DocHandler::endElement(const XMLCh* const uri,
								 const XMLCh* const localname,
								 const XMLCh* const qname)
{
}

// Ni idea, supongo que se llama cuando encuentra espacios ignorables
void SAX2DocHandler::ignorableWhitespace( const   XMLCh* const chars
                                            ,const  XMLSize_t length)
{
}

// Ni idea
void SAX2DocHandler::processingInstruction(const  XMLCh* const target
                                            , const XMLCh* const data)
{
}

// Se llama cuando comienza el documento
void SAX2DocHandler::startDocument()
{
}

// Se llama cuando encuentra un elemento
void SAX2DocHandler::startElement(const   XMLCh* const    uri,
									const   XMLCh* const    localname,
									const   XMLCh* const    qname,
                                    const   Attributes&		attributes)
{
	XMLSize_t length;

	// Guardamos el tagName que estamos parseando
	TagName.assign(XMLString::transcode(qname));
	
	// Guardamos el numero de atributos
	length = attributes.getLength();
		
	// Limpiamos los vectores por si tienen datos del nodo anterior
	Qname.clear();
	Type.clear();
	Value.clear();

	// Cargamos los vectores con los valores de los atributos
	for (XMLSize_t index = 0; index < length; index++)
	{
		Qname.push_back(XMLString::transcode(attributes.getQName(index)));
		Type.push_back(XMLString::transcode(attributes.getType(index)));
		Value.push_back(XMLString::transcode(attributes.getValue(index)));
	}
}

std::string SAX2DocHandler::getTagName()
{
	return TagName;
}

std::vector<std::string> SAX2DocHandler::getAttrName()
{
	return Qname;
}

std::vector<std::string> SAX2DocHandler::getAttrType()
{
	return Type;
}

std::vector<std::string> SAX2DocHandler::getAttrValue()
{
	return Value;
}

