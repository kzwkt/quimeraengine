// BoostSerializationXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Stl includes used in the sample
#include <string>
#include <vector>
#include <map>
#include <fstream>

// Boost required includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>

// Additional Boost include, only to illustrate its usage
#include <boost/foreach.hpp>

using namespace boost::archive;

// Predeclarations
class LeafObject;
// This typedef is required to use a std::map iterator in Boost foreach macro
typedef std::pair<std::string, LeafObject*> TLeafPair; 

// RootObjectBase class, to test the serialization accross inheritance
class RootObjectBase
{
    // friend declaration needed if serialize method is no visible
    friend class boost::serialization::access;

public:

    int _nBaseClassValue;

    // A way to make template method "serialize" virtual
    // There is a loss of type abstraction, but it is worth
    virtual void SerializeImplementation(xml_oarchive & ar)
    {
        RootObjectBase* pThis = this;
        ar << BOOST_SERIALIZATION_NVP(pThis);
    }

    virtual void DeserializeImplementation(xml_iarchive & ar)
    {
        RootObjectBase* pThis = this;
        ar >> BOOST_SERIALIZATION_NVP(pThis);
    }

protected:
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(_nBaseClassValue);// Works fine.
    }
};

// RootObject class, to demonstrate how to do serialization across a tree or wrapper
class RootObject : public RootObjectBase
{
    // friend declaration needed if serialize method is no visible
    friend class boost::serialization::access;

public:

    int _nBasicAttribute;
    float _fAttributePrecission;
    std::map<std::string, LeafObject*> _stlMap;
    char* _arInHeap;

    // A way to make template method "serialize" virtual
    // There is a loss of type abstraction, but it is worth
    virtual void SerializeImplementation(xml_oarchive & ar)
    {
        RootObject* pThis = this;
        ar << BOOST_SERIALIZATION_NVP(pThis);
    }

    virtual void DeserializeImplementation(xml_iarchive & ar)
    {
        RootObject* pThis = this;
        ar >> BOOST_SERIALIZATION_NVP(pThis);
    }

protected:

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // BOOST_SERIALIZATION_BASE_OBJECT_NVP is used to create a key-value pair to 
        // serialize base class attributes
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(RootObjectBase); // Use this, dont call base class' serialize method directly

        // BOOST_SERIALIZATION_NVP is a macro used to create a key-value pair, taking
        // the attribute name as xml tag name, and its value as inner content
        ar & BOOST_SERIALIZATION_NVP(_nBasicAttribute);      // Works fine.
        ar & BOOST_SERIALIZATION_NVP(_fAttributePrecission); // Doesn't seem to be very accurate.
        ar & BOOST_SERIALIZATION_NVP(_stlMap);               // Works fine. Needs <boost/serialization/map.hpp> to be included.
        //ar & BOOST_SERIALIZATION_NVP(_arInHeap);           // Basic types pointers serialization is not allowed.
    }
};

// Leafbject class, to demonstrate how to do serialization across a tree or wrapper
class LeafObject
{
    // friend declaration needed if serialize method is no visible
    friend class boost::serialization::access;

public:

    std::string _strStlString;
    std::vector<std::string> _stlVector;
    char _arLetters[10];
    RootObject* _pCircularReference;

    // A way to make template method "serialize" virtual
    // There is a loss of type abstraction, but it is worth
    virtual void SerializeImplementation(xml_oarchive & ar)
    {
        LeafObject* pThis = this;
        ar << BOOST_SERIALIZATION_NVP(pThis);
    }

    virtual void DeserializeImplementation(xml_iarchive & ar)
    {
        LeafObject* pThis = this;
        ar >> BOOST_SERIALIZATION_NVP(pThis);
    }

protected:

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(_strStlString);         // Works fine.
        ar & BOOST_SERIALIZATION_NVP(_stlVector);            // Works fine. Needs <boost/serialization/vector.hpp> to be included.
        ar & BOOST_SERIALIZATION_NVP(_arLetters);            // Works fine. Needs <boost/serialization/array.hpp> to be included.
        ar & BOOST_SERIALIZATION_NVP(_pCircularReference);   // Works fine. There is not circular serialization, it seems to follow an internal register of what woas previously serialized.
    }
};

// Predeclarations
void TreeBuilder(RootObject* root1, RootObject* root2);
void TreeDestroyer(RootObject* pRoot);

int _tmain(int argc, _TCHAR* argv[])
{
    // Roots
    RootObjectBase* root1 = new RootObject();
    RootObjectBase* root2 = new RootObject();

    // Builds both trees
    TreeBuilder(dynamic_cast<RootObject*>(root1), dynamic_cast<RootObject*>(root2));

    // Writes the binary file
    std::ofstream output1("BoostSerializationXMLResult1.xml");
    std::ofstream output2("BoostSerializationXMLResult2.xml");

    xml_oarchive archiveOUT1(output1);
    root1->SerializeImplementation(archiveOUT1);

    xml_oarchive archiveOUT2(output2);
    root2->SerializeImplementation(archiveOUT2);

    // The file stream must be closed in order to physically write the file
    output1.close();
    output2.close();

    TreeDestroyer(dynamic_cast<RootObject*>(root1));
    TreeDestroyer(dynamic_cast<RootObject*>(root2));
    
    // Reads the binary file
    root1 = new RootObject();
    root2 = new RootObject();

    std::ifstream input1("BoostSerializationXMLResult1.xml");
    xml_iarchive archiveIN1(input1);
    root1->DeserializeImplementation(archiveIN1);
    dynamic_cast<RootObject*>(root1)->_arInHeap = 0; // Not serialized

    std::ifstream input2("BoostSerializationXMLResult2.xml");
    xml_iarchive archiveIN2(input2);
    root2->DeserializeImplementation(archiveIN2);
    dynamic_cast<RootObject*>(root2)->_arInHeap = 0; // Not serialized

    TreeDestroyer(dynamic_cast<RootObject*>(root1));
    TreeDestroyer(dynamic_cast<RootObject*>(root2));

	return 0;
}

void TreeBuilder(RootObject* root1, RootObject* root2)
{
    // Leafs 1
    LeafObject* leaf1a = new LeafObject();
    LeafObject* leaf1b = new LeafObject();

    // Leafs 2
    LeafObject* leaf2a = new LeafObject();
    LeafObject* leaf2b = new LeafObject();

    // Root 1 building
    root1->_fAttributePrecission = 10000000.0f;
    root1->_nBasicAttribute = 0;

    std::pair<std::string, LeafObject*> pair1("Key1", leaf1a);
    root1->_stlMap.insert(pair1);
    pair1.first = "Key2";
    pair1.second = leaf1b;
    root1->_stlMap.insert(pair1);
    root1->_arInHeap = new char[2];
    root1->_arInHeap[0] = 'A';
    root1->_arInHeap[1] = 'B';
    root1->_nBaseClassValue = 16;

    // Root 2 building
    root2->_fAttributePrecission = 0.00000001f;
    root2->_nBasicAttribute = -5000;

    std::pair<std::string, LeafObject*> pair2("Key1", leaf2a);
    root2->_stlMap.insert(pair2);
    pair2.first = "Key2";
    pair2.second = leaf2b;
    root2->_stlMap.insert(pair2);
    root2->_arInHeap = new char[2];
    root2->_arInHeap[0] = 'Y';
    root2->_arInHeap[1] = 'Z';
    root2->_nBaseClassValue = 32;

    // Leafs 1 building
    leaf1a->_pCircularReference = root1;
    leaf1b->_pCircularReference = root1;

    leaf1a->_stlVector.push_back(std::string("1"));
    leaf1a->_stlVector.push_back(std::string("2"));
    leaf1b->_stlVector.push_back(std::string("3"));
    leaf1b->_stlVector.push_back(std::string("4"));

    leaf1a->_strStlString = "<\\invalid_symbols?\"'>";
    leaf1b->_strStlString = ".ñ_______               ";

    char* aux = new char[2];
    for(int i = 0; i < 10; ++i)
    {
        _itoa(i, aux, 10);
        leaf1a->_arLetters[i] = *aux;
    }

    // leaf1b not filled

    // Leafs 2 building
    leaf2a->_pCircularReference = root2;
    leaf2b->_pCircularReference = 0;

    leaf2a->_stlVector.push_back(std::string("1"));
    leaf2a->_stlVector.push_back(std::string("2"));
    leaf2b->_stlVector.push_back(std::string("3"));
    leaf2b->_stlVector.push_back(std::string("4"));

    leaf2a->_strStlString = "<\\invalid_symbols?\"'///*****FASDDF\n\td>";
    leaf2b->_strStlString = ".ñ_______               .";

    aux = new char[1];;
    for(int i = 0; i < 10; ++i)
    {
        _itoa(i, aux, 10);
        leaf2a->_arLetters[i] = *aux;
    }

    // leaf2b not filled
}

void TreeDestroyer(RootObject* pRoot)
{
    // Boost foreach macro, only to illustrate its usage
    BOOST_FOREACH(TLeafPair it, pRoot->_stlMap)
    {
        delete it.second;
    }

    delete[] pRoot->_arInHeap;
    delete pRoot;
}