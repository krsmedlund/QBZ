#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "qbz.h"
#include "Network/qbz_network.h"
#include "Network/registry.h"

namespace qbz
{

namespace render
{
    typedef enum {
        RenderColor     = 0x01,
        RenderPosition  = 0x02,
        RenderNormal    = 0x04,
        RenderDepth     = 0x08,
        RenderColor1    = 0x16,
        RenderColor2    = 0x32,
        RenderColor3    = 0x64
    } RenderTargetFormat;

    struct NetworkNodeConfig
    {
    };

    class RenderTarget : public network::NetworkNode
    {
        NETWORK_NODE(RenderTarget);

    public:
        RenderTarget(const std::string & nodeName);
        ~RenderTarget();

        NetworkNodeConfig & getConfig();
        void Setup(NetworkNodeConfig & cfg);

        void Do();

        void onConnectedPort() {}
        void onDisconnectedPort() {}

        std::map<std::string, std::string> configVariables;
        std::map<std::string, std::string>& getVariablesAndTypes() {
            return configVariables;
        }

        bool isInUse() { return inUse; }
        bool isMTR() { return MTR; }

        bool hasColor0() { return colorTexture0 != 0; }
        bool hasColor1() { return colorTexture1 != 0; }
        bool hasColor2() { return colorTexture2 != 0; }
        bool hasColor3() { return colorTexture3 != 0; }

        bool hasDepth() { return depthTexture != 0; }
        bool hasNormals() { return normalTexture != 0; }
        bool hasPositions() { return positionTexture != 0; }

        GLuint  colorTexture0,
                colorTexture1,
                colorTexture2,
                colorTexture3,
                depthTexture,
                positionTexture,
                normalTexture;

        qbz::network::InPort *inPortRenderProgram;
        qbz::network::OutPort *outPortColorTexture0,
                              *outPortNormalTexture,
                              *outPortPositionTexture;

    private:
        bool MTR, inUse;
        RenderTargetFormat format;
        GLuint fbo0, fbo1;

    };

    RenderTarget* getRenderTarget(render::RenderTargetFormat);
}
}
#endif // RENDERTARGET_H
