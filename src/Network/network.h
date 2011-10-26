#ifndef QBZ_NETWORK_H
#define QBZ_NETWORK_H

#include "qbz.h"
#include "registry.h"

#include <sstream>

namespace qbz {
namespace network {

    enum PortDataType {
        FLOAT       = 0x01,
        TEXTURE     = 0x02,
        MODEL       = 0x03
    };

    class Port
    {
    public:
        std::string portIdentifier;
        std::vector<std::string> portElements;

        int id;

        Port(const std::string & componentName, const std::string & portName)
        {
            portIdentifier = componentName + "." + portName;
            portElements.push_back(componentName);
            portElements.push_back(portName);
        }

        Port(const std::string & name)
            : portIdentifier(name)
        {
            std::stringstream ss(name);
            std::string item;
            while(std::getline(ss, item, '.')) {
                portElements.push_back(item);
            }
        }
    };

    /* a published variable */

    class OutPort : public Port
    {
    public:
        OutPort(const std::string & nName, const std::string & pName, void * valuePtr, unsigned int channelCount=1) : Port(nName, pName)
        {
            data.resize(channelCount);
            if (valuePtr) {
                for (unsigned int i=0; i<channelCount; ++i) {
                    data.at(i) = &(valuePtr[i]);
                }
            }
        }

        void bind(void* valuePtr, unsigned int channel=0)
        {
            if (channel < data.size())
                data.at(channel) = valuePtr;
        }

        ~OutPort() {
        }

        void * getValuePtr(unsigned int channel=0)
        {
            if (channel < data.size())
                return data.at(channel);
        }

        std::vector<void*> data;
    };


    class InPort : public Port
    {
    public:
        bool list;
        unsigned int channels;
        OutPort* connectedTo;
        std::vector<void*> defaultData;
        std::vector<void*>* data;

        InPort(const std::string & cName, const std::string & pName, unsigned int channelCount=1, bool isList=false)
            : Port(cName, pName), list(isList), channels(channelCount)
        {
            data = &defaultData;
            connectedTo = 0;
        }

        ~InPort() {}

        void setDefaultValues(void * valuePtr, unsigned int count)
        {
            for (int i=0; i<count; ++i)
                defaultData.push_back(&(valuePtr[i]));
        }

        void setDefaultValue(void * valuePtr, unsigned int channel=0)
        {
            if (channel < defaultData.size())
                defaultData.at(channel) = valuePtr;
            else defaultData.push_back(valuePtr);
        }

        void * getValuePtr(unsigned int channel=0)
        {
            if (!connectedTo)
                return (void*)0;

            if (channel < connectedTo->data.size())
                return connectedTo->data.at(channel);

            else std::cout << "wrong channel" << std::endl;
            return 0;
        }

        void setValue(float val, unsigned int channel=0)
        {
            if (channel < data->size())
                *((float*)data->at(channel)) = val;
        }
    };

    class NetworkNode
    {

    public:
        std::map<std::string, std::string> metaData;
        std::map<std::string, InPort*> inPorts;
        std::map<std::string, OutPort*> outPorts;

        virtual const std::string & getType();
        NetworkNode(const std::string & nodeName);
        NetworkNode();
        ~NetworkNode();
        void Do() {}
        void onConnectedPort() {}
    };

    struct NetworkNodeConfig {
        std::map<std::string, std::string> configVariables;
    };


    class Network
    {
    public:
        static Network* open()
        {
            static Network instance;
            return &instance;
        }

        void setPortValue(const std::string & portIdentifier, float value);
        void registerNode(NetworkNode* node, const std::string & name);

        void connectPorts(const std::string & outport, const std::string & inport);
        void connectPorts(OutPort* outport, InPort* inport);

        void disconnectPorts(const std::string & outort, const std::string & inport);

        OutPort* registerOutPort(const std::string & nodeName, const std::string & portName, void * valuePtr=0, unsigned int channels=1);
        InPort* registerInPort(const std::string & nodeName, const std::string & portName, unsigned int channelCount=1, bool isList=false);

        // these are the ones we run, they will call all other components, we need to keep this list in order we want to render.
        std::vector< std::pair<std::string, NetworkNode*> > renderTargets;
        std::map<std::string, NetworkNode*> components;
        std::map<std::string, InPort*> inPorts;
        std::map<std::string, OutPort*> outPorts;
        qbz::network::NetworkNode* finalOut;

        bool hasFinal;

    private:
        Network();
    };

    OutPort* registerOutPort(const std::string & nodeName, const std::string & portName, void * valuePtr=0, unsigned int channels=1);
    InPort* registerInPort(const std::string & nodeName, const std::string & portName, unsigned int channelCount=1, bool isList=false);
    void registerNode(NetworkNode* node, const std::string & name);

    const std::vector< std::pair<std::string, network::NetworkNode*> >& getRenderTargetListHandle();
    qbz::network::NetworkNode* getFinalOut();

    void connectPorts(const std::string & outport, const std::string & inport);
    void connectPorts(OutPort* outport, InPort* inport);

    void setPortValue(const std::string & portIdentifier, float value);
    void printPorts();
    void printConnectedPorts();
}
}

#endif // QBZ_NETWORK_H
