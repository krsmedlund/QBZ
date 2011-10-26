#include "Network/network.h"

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



Network::Network() : hasFinal(false) {
    std::cout << "new network" <<std::endl;
    finalOut = 0;
}

void Network::registerNode(NetworkNode* node, const std::string & name)
{
    components[name] = node;
    std::string type(node->getType());

    if (type == "RenderTarget")
        renderTargets.push_back(std::make_pair(name, node));
    else if (type == "FinalOut") {
        std::cout << "Added final out!" << std::endl;
        this->finalOut = node;
        this->hasFinal = true;
    }
}

void Network::connectPorts(const std::string & outport, const std::string & inport)
{
    OutPort* out = 0;
    InPort* in = 0;

    if (outPorts.count(outport) > 0) out = outPorts[outport];
    else {
        std::cout << "Cant find out port " << outport << std::endl;
        network::printPorts();
        return;
    }

    if (inPorts.count(inport) > 0) in = inPorts[inport];
    else {
        std::cout << "Cant find in port " << inport << std::endl;
        network::printPorts();
        return;
    }
    this->connectPorts(out, in);
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
    network::printPorts();
    if (!inPorts.count(port->portIdentifier)) {
        inPorts[port->portIdentifier] =  port;
    }
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

const std::vector<std::string> & network::getPortsForNode(const std::string & nodeName)
{
}

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

const std::vector< std::pair<std::string, network::NetworkNode*> >& network::getRenderTargetListHandle()
{
    return gNetwork->renderTargets;
}

NetworkNode* network::getFinalOut()
{
    if (gNetwork->hasFinal == true && gNetwork->finalOut != NULL)
        return gNetwork->finalOut;
    else return NULL;
}

