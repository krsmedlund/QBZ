#ifndef QBZ_COMPOSER_H
#define QBZ_COMPOSER_H

#include "qbz.h"
#include "Network/qbz_network.h"


namespace qbz{
    
    class FBO;
    class ProjectionArea;
    class Camera;
    class Animator;
    class World;
};

namespace qbz {
    
    class Composer : public qbz::network::NetworkNode {
    public:

        std::string addComponent(ResourceType type, const std::string & identifier);

        void setup();
        void update();
        void draw();
        void draw_embedded();
	
        void keyReleased(int key);
        void mousePressed(int x, int y, int button);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void keyPressed(int key);
        void mouseReleased(int x, int y, int button);
        void midiChanged(int channel, int value);   

        void onConnectedPort() {
            qDebug() << " Connected port! ";
        }

        void Do() {}

    };
};

#endif
