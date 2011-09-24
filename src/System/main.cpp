#include <openGL.h>
#include <glext.h>

#include "System/mainwindow.h"
#include "qbz_composer.h"
#include "Network/qbz_network.h"

MainWindow* mainwindow;
qbz::network::Network* gNetwork;

float maxTonalData;
float tonalData[12];

int main (int argc, char **argv)
{
    qbz::network::Network network = qbz::network::Network::open();
    gNetwork = &network;
    QApplication app(argc, argv);

    mainwindow = new MainWindow();
    mainwindow->startGLWidget(QBZ_X_RES, QBZ_Y_RES);

    return app.exec();
}
