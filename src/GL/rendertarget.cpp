#include "rendertarget.h"
#include "qbz_renderprogram.h"

using namespace std;
using namespace qbz;
using namespace qbz::render;


//NETWORK_REGISTER(RenderTarget);

const std::string& RenderTarget::getType()
{
    return "RenderTarget";
}

static qbz::network::NetworkNode* RenderTargetFactoryCreator(const std::string & nodeName)
{
    return new RenderTarget(nodeName);
}

static int foo = qbz::network::Factory::registerCreateFunction("RenderTarget", RenderTargetFactoryCreator);


RenderTarget::RenderTarget(const std::string & nodeName)
{
    network::registerNode(this, nodeName);
    inPorts["RenderProgram"] = network::registerInPort(nodeName, "RenderProgram", 1, true);
    MTR = false;
}

void RenderTarget::Setup(NetworkNodeConfig & cfg)
{
    int renderFormat = RenderColor | RenderPosition | RenderNormal;
    int w = 1280;
    int h = 720;

    glGenFramebuffers(1, &fbo0);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo0);

    if (renderFormat & RenderColor) {
        glGenTextures(1, &colorTexture0);
        glBindTexture(GL_TEXTURE_2D, colorTexture0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture0, 0);
        outPortColorTexture0 = network::registerOutPort("RenderTarget", "ColorTexture", &colorTexture0);
    }

    if (renderFormat & RenderPosition) {
        glGenTextures(1, &positionTexture);
        glBindTexture(GL_TEXTURE_2D, positionTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, w, h, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, positionTexture, 0);
        outPortPositionTexture = network::registerOutPort("RenderTarget", "PositionTexture", &positionTexture);
        MTR = true;
    }

    if (renderFormat & RenderNormal) {
        glGenTextures(1, &normalTexture);
        glBindTexture(GL_TEXTURE_2D, normalTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, w, h, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, normalTexture, 0);
        outPortNormalTexture = network::registerOutPort("RenderTarget", "NormalTexture", &normalTexture);
        MTR = true;
    }

    GLenum FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT && FBOstatus != GL_FRAMEBUFFER_COMPLETE) {
        cout << "glCheckFramebufferStatus returned " << FBOstatus << endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
    glDeleteTextures(1, &colorTexture0);
    glDeleteTextures(1, &colorTexture1);
    glDeleteTextures(1, &colorTexture2);
    glDeleteTextures(1, &colorTexture3);
    glDeleteTextures(1, &normalTexture);
    glDeleteTextures(1, &positionTexture);
    glDeleteTextures(1, &depthTexture);
    glDeleteFramebuffers(1, &fbo0);
    glDeleteFramebuffers(1, &fbo1);
}

void RenderTarget::Do()
{
    // set up FBO for drawing
    if (MTR) {
        GLenum bufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        glBindFramebuffer(GL_FRAMEBUFFER, fbo0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glDrawBuffers(3, bufs);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    RenderProgram* rp = reinterpret_cast<RenderProgram*>(inPortRenderProgram->getValuePtr());
    rp->Do();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
