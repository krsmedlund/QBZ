#ifndef QBZ_CLAM_H

#include <CLAM/Network.hxx>
#include <CLAM/PANetworkPlayer.hxx>
#include <CLAM/XMLStorage.hxx>

namespace qbz {
    class ClamController {
    public:
        ClamController(const char* networkname);
    private:
        CLAM::Network network;
    };
};

#endif