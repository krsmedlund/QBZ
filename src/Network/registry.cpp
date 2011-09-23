#include "registry.h"
#include "qbz_network.h"

using namespace qbz;
using namespace qbz::network;


/**
class NodeCollection
**/

NodeCollection::NodeCollection() : head(NULL), nextId(1)
{
}

NodeCollection::~NodeCollection()
{
    while (head) {
        ObjectNode *tmp(head);
        head = head->next;
        delete tmp;
    }
}

void NodeCollection::printNodes()
{
    ObjectNode* tmp(head);
    while (tmp) {
        ::std::cout << tmp->obj->getType();
        tmp = tmp->next;
    }
}

int NodeCollection::add(NetworkNode* obj)
{
    ObjectNode* tmp(new ObjectNode);
    if (tmp) {
        tmp->next = head;
        tmp->id = nextId++;
        tmp->obj = obj;
        head = tmp;
        return tmp->id;
    }
    return 0;
}

NetworkNode* NodeCollection::find(int id)
{
    ObjectNode* tmp(head);
    while (tmp) {
        if (tmp->id == id)
            return tmp->obj;
        tmp = tmp->next;
    }
    return NULL;
}

int NodeCollection::find(NetworkNode *obj)
{
    ObjectNode* tmp(head);
    while (tmp) {
        if (tmp->obj == obj)
            return tmp->id;
        tmp = tmp->next;
    }
    return 0;
}



/**
class Factory
**/

Factory *Factory::instance = 0;

Factory::Factory() : creatorList(0), nodes(new NodeCollection)
{
}

Factory::~Factory()
{
    while (creatorList) {
        CreatorEntry *tmp(creatorList);
        creatorList = creatorList->next;
        delete tmp;
    }
    if (nodes)
        delete nodes;
}

std::vector<std::string>* Factory::getNodeList()
{
    Factory *f(open());
    CreatorEntry *tmp(f->creatorList);
    std::vector<std::string> * nodeList = new std::vector<std::string>;

    while (tmp) {
        nodeList->push_back(tmp->name);
        tmp = tmp->next;
    }
    return nodeList;
}

Factory* Factory::open()
{
    if (!instance) instance = new Factory;
    return instance;
}

int Factory::registerCreateFunction(const std::string & nodeName, NetworkNode* (*createFunction)(const std::string&) )
{
    Factory *f(open());
    CreatorEntry *tmp(new CreatorEntry);
    if (tmp) {
        tmp->next = f->creatorList;
        tmp->name = nodeName;
        tmp->createFunction = createFunction;
        f->creatorList = tmp;
    }
}

NetworkNode* Factory::createNode(const std::string & className, const std::string & nodeName)
{
    Factory *f(open());
    CreatorEntry *tmp(f->creatorList);
    while (tmp) {
        if (0 == tmp->name.compare(className))
            return tmp->createFunction(nodeName);
        tmp = tmp->next;
    }
    return 0;
}
