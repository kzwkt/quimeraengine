// [TERMS&CONDITIONS]

#ifndef __TATXMLREADER__
#define __TATXMLREADER__

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>
#include <list>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Extracts data from an well-formed XML string.
/// </summary>
template<class TString>
class TATXmlReader
{
    // TYPEDEFS
    // ---------------
public:

    typedef boost::property_tree::ptree TXmlTree;
    typedef std::pair<TString, TXmlTree> TXmlElement;


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Obtains an tree of nodes that hold information of every XML element in the string.
    /// </summary>
    /// <param name="inputStream">The string that contains XML data.</param>
    /// <param name="xmlTree">The extracted tree that encapsulates the XML data.</param>
    void ParseXml(std::istream &inputStream, TXmlTree &xmlTree) const
    {
        boost::property_tree::read_xml(inputStream, xmlTree);
    }

    /// <summary>
    /// Obtains the value of a desired attribute of an XML node.
    /// </summary>
    /// <param name="xmlTree">The XML node (or sub-tree).</param>
    /// <param name="strAttributeName">The name of the attribute whose value has to be retrieved.</param>
    /// <returns>
    /// The value of the attribute.
    /// </returns>
    template<typename T>
    T GetAttribute(TXmlTree &xmlTree, const TString &strAttributeName) const
    {
        return xmlTree.get<T>(TString("<xmlattr>.") + strAttributeName);
    }

    /// <summary>
    /// Obtains the content of an XML node.
    /// </summary>
    /// <param name="xmlTree">The XML node (or sub-tree).</param>
    /// <returns>
    /// The content of the node.
    /// </returns>
    template<typename T>
    T GetContent(TXmlTree &xmlTree) const
    {
        return xmlTree.get_value<T>();
    }

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATXMLREADER__
