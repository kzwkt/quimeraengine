//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

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
