#ifndef FINALOUT_H
#define FINALOUT_H

#include "Network/network.h"

namespace qbz {
namespace render {

class FinalOut : public network::NetworkNode
{
    NETWORK_NODE(FinalOut);

public:
    FinalOut(const std::string & resourceName);
    ~FinalOut();
    void Do();
private:
    std::string resource;
};

}
}

#endif // FINALOUT_H
