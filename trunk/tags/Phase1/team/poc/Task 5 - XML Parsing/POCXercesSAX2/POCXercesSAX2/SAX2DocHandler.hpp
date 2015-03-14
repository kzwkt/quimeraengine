#include	<vector>
#include    <xercesc/sax2/DefaultHandler.hpp>

XERCES_CPP_NAMESPACE_USE

class SAX2DocHandler : public DefaultHandler
{
public:
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    SAX2DocHandler
    (
        const   char* const                 encodingName
        , const bool						expandNamespaces
    );
    ~SAX2DocHandler();
	
    // -----------------------------------------------------------------------
    //  Implementations of the SAX DocumentHandler interface
    // -----------------------------------------------------------------------
    void endDocument();

    void endElement( const XMLCh* const uri,
					 const XMLCh* const localname,
					 const XMLCh* const qname);

    void characters(const XMLCh* const chars, const XMLSize_t length);

    void ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const XMLSize_t       length
    );

    void processingInstruction
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    );

    void startDocument();

    void startElement(	const   XMLCh* const    uri,
						const   XMLCh* const    localname,
						const   XMLCh* const    qname,
					    const   Attributes&		attributes);

	std::string getTagName();
	std::vector<std::string> getAttrName();
	std::vector<std::string> getAttrType();
	std::vector<std::string> getAttrValue();
	

    // -----------------------------------------------------------------------
    //  Implementations of the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& exc);
    void error(const SAXParseException& exc);
    void fatalError(const SAXParseException& exc);

	
    // -----------------------------------------------------------------------
    //  Implementation of the SAX DTDHandler interface
    // -----------------------------------------------------------------------
    void notationDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
    );

    void unparsedEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
        , const XMLCh* const    notationName
    );

private :
    // Variable para saber que nodo está parseando
	std::string TagName;

	// Estructura para guardar la lista de atributos
	std::vector<std::string> Qname;
	std::vector<std::string> Value;
	std::vector<std::string> Type;
};
