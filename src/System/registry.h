#ifndef REGISTRY_H
#define REGISTRY_H

#include "qbz.h"
#include "qbz_network.h"
#include <string>

#define NETWORK_NODE(_type) \
    public: \
        virtual const std::string& getType()

#define NETWORK_REGISTER(_type) \
    const std::string & _type::getType() { return # _type; } \
    NODE_REGISTER(_type)

#define NODE_REGISTER(_type) \
    static NetworkNode* _type ## FactoryCreator(const std::string & nodeName) { return new _type(nodeName); }; \
    static int _type ## CreatorAutoRegHook = qbz::network::Factory::registerCreateFunction(#_type, _type ## FactoryCreator)


namespace qbz {
namespace network {

class NetworkNode;

class NodeCollection
{
public:
    NodeCollection();
    virtual ~NodeCollection();
    int add(NetworkNode* obj);
    NetworkNode* find(int id);
    int find(NetworkNode* obj);
    void printNodes();

protected:
    struct ObjectNode {
        ObjectNode *next;
        int id;
        NetworkNode *obj;
    };
    ObjectNode* head;
    int nextId;
};


class Factory
{
public:
    Factory();
    virtual ~Factory();

    static int registerCreateFunction(const std::string & nodeName, NetworkNode* (*createFunction)(const std::string&));
    static NetworkNode* createNode(const std::string & className, const std::string & nodeName);
    static Factory* open();
    static std::vector<std::string>* getNodeList();

protected:
    struct CreatorEntry
    {
        CreatorEntry* next;
        std::string name;
        NetworkNode* (*createFunction)(const std::string&);
    };

    CreatorEntry* creatorList;
    NodeCollection* nodes;
    static Factory* instance;
};

}
}
#endif // REGISTRY_H
