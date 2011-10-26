#include "finalout.h"
#include "GL/renderprogram.h"

using namespace qbz;
using namespace qbz::render;

// network registry
const std::string & FinalOut::getType() { return "FinalOut"; }
static qbz::network::NetworkNode* FinalOutFactoryCreator(const std::string & nodeName) { return new FinalOut(nodeName); }
static int foo = qbz::network::Factory::registerCreateFunction("FinalOut", FinalOutFactoryCreator);


FinalOut::FinalOut(const std::string & resourceName)
{
    inPorts["RenderProgram"] = network::registerInPort("FinalOut", "RenderProgram", 1, false);
}

FinalOut::~FinalOut()
{
}

void FinalOut::Do()
{
    glClearColor(0.4, 0.9, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);
    glDisable(GL_BLEND);

    // draw all renderprograms that are attached to the port.
    if (inPorts["RenderProgram"]->connectedTo != 0) {
        qbz::RenderProgram* rp = reinterpret_cast<qbz::RenderProgram*>(inPorts["RenderProgram"]->getValuePtr());
        rp->Do();
    }
}
