#include "qbz_network.h"

using namespace qbz;
using namespace qbz::network;

// Static hack to register class with the factory before main() is called
// Macros are defined in registry.h
NETWORK_REGISTER(NetworkNode);
NetworkNode::NetworkNode(const std::string & nodeName)
{
}

NetworkNode::NetworkNode()
{
}

NetworkNode::~NetworkNode()
{
}



Network::Network() {
    std::cout << "new network" <<std::endl;
}

void Network::registerNode(NetworkNode* node, const std::string & name)
{
    this->components[name] = node;
}

void Network::connectPorts(const std::string & outport, const std::string & inport)
{
    OutPort* out = 0;
    InPort* in = 0;

    if (outPorts.count(outport) > 0) out = outPorts[outport];
    if (inPorts.count(inport) > 0) in = inPorts[inport];

    if (!in || !out) {
        std::cout << "cant find port."<< std::endl;
        network::printPorts();
    } else {
        this->connectPorts(out, in);
    }
}

void Network::connectPorts(OutPort* outport, InPort* inport)
{
    inport->connectedTo = outport;
}

void Network::disconnectPorts(const std::string & outport, const std::string & inport)
{
    InPort* ip = inPorts[inport];
    OutPort* op = outPorts[outport];
}

OutPort * Network::registerOutPort(const std::string & nodeName, const std::string & portName, void * valuePtr, unsigned int channels)
{
    OutPort * port = new OutPort(nodeName, portName, valuePtr, channels);
    outPorts.insert(std::make_pair(port->portIdentifier, port));
    return port;
}

InPort * Network::registerInPort(const std::string & nodeName, const std::string & portName, unsigned int channelCount, bool isList)
{
    InPort * port = new InPort(nodeName, portName, channelCount, isList);
    inPorts.insert(std::make_pair(port->portIdentifier, port));
    //std::cout << "Registered port '" << port->portIdentifier << "'" << std::endl;
    return port;
}


void Network::setPortValue(const std::string & portIdentifier, float value)
{
    if (inPorts.count( portIdentifier ) > 0) {
        inPorts[ portIdentifier ]->setValue(value);
    } else {
        std::cout << "Can't find port '" << portIdentifier << "'" << std::endl;
        std::map<std::string, InPort*>::iterator it;

        if (inPorts.begin() == inPorts.end()) {
            std::cout << "No ports registered in "<< &inPorts << std::endl;
        }
        else for (it=inPorts.begin(); it != inPorts.end(); ++it) {
            std::cout << "Port: " << it->first << " registered in "<< &inPorts << std::endl;
        }
    }
}


extern Network* gNetwork;

void network::setPortValue(const std::string & portIdentifier, float value)
{
    gNetwork->setPortValue(portIdentifier, value);
}

void network::registerNode(NetworkNode* node, const std::string & name)
{
    gNetwork->registerNode(node, name);
}

OutPort* network::registerOutPort(const std::string & nodeName, const std::string & portName, void * valuePtr, unsigned int channels)
{
    return gNetwork->registerOutPort(nodeName, portName, valuePtr, channels);
}

InPort* network::registerInPort(const std::string & nodeName, const std::string & portName, unsigned int channelCount, bool isList)
{
    return gNetwork->registerInPort(nodeName, portName, channelCount, isList);
}

void network::connectPorts(const std::string & outport, const std::string & inport)
{
    gNetwork->connectPorts(outport, inport);
}

void network::connectPorts(OutPort* outport, InPort* inport)
{
    gNetwork->connectPorts(outport, inport);
}

void network::printPorts()
{
    std::map<std::string, InPort*>::iterator it;
    for (it=gNetwork->inPorts.begin(); it != gNetwork->inPorts.end(); ++it) {
        std::cout << "InPort : '" << it->first << "'" << std::endl;
    }

    std::map<std::string, OutPort*>::iterator oit;
    for (oit=gNetwork->outPorts.begin(); oit != gNetwork->outPorts.end(); ++oit) {
        std::cout << "OutPort [" << oit->second->data.at(0) << "] '" << oit->first << "'" << std::endl;
    }
}


void network::printConnectedPorts()
{
    std::map<std::string, InPort*>::iterator it;
    for (it=gNetwork->inPorts.begin(); it != gNetwork->inPorts.end(); ++it) {
        std::cout << "InPort : '" << it->first << "'" << std::endl;
    }

    std::map<std::string, OutPort*>::iterator oit;
    for (oit=gNetwork->outPorts.begin(); oit != gNetwork->outPorts.end(); ++oit) {
        std::cout << "OutPort [" << oit->second->data.at(0) << "] '" << oit->first << "'" << std::endl;
    }
}
