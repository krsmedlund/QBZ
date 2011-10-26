#include "System/mainwindow.h"
#include <QDeclarativeView>

using namespace std;
using namespace qbz;
using namespace qbz::network;


MainWindow::MainWindow() : QWidget(0)
{  	
    QUiLoader loader;
    QFile file("ui/mainwindow.ui");

    file.open(QFile::ReadOnly);
    QWidget *formWidget = loader.load(&file, this);
    file.close();

    QMetaObject::connectSlotsByName(this);
    formWidget->show();

    this->output_textedit = qFindChild<QTextEdit*>(this, "ui_output");
    this->gl_widget_space = qFindChild<QVBoxLayout*>(this, "glEmbedHook");

    //RenderWidget * renderWidget = new RenderWidget();
    //renderWidget->show();
    //renderWidget->startRenderThread();

    QDeclarativeView *view = qFindChild<QDeclarativeView*>(this, "qmlEmbedHook");

    QStringList qs;
    vector<string>* nodeList = Factory::getNodeList();
    vector<string>::iterator it;
    for (it=nodeList->begin(); it != nodeList->end(); ++it) {
        qs.append(it->c_str());
    }
    view->rootContext()->setContextProperty("NodeListData", QVariant::fromValue(qs));
    view->rootContext()->setContextProperty("mainWindow", this);

    view->setSource(QUrl::fromLocalFile("qmlsrc/Main.qml"));
    view->show();

    //QDeclarativeItem *item = view->rootObject()->findChild<QDeclarativeItem*>("testRenderer");
    //if (item) item->setProperty("name", "Hi from C++");
}

MainWindow::~MainWindow()
{

}


void MainWindow::startGLWidget(int w, int h)
{
    if (!output_textedit) {
        qDebug() << "cant find the ui_output widget\n";
    } else {
        output("Testing output", "info");
    }

    QGLFormat fmt;
    fmt.setDepth(true);
    //fmt.setDepthBufferSize(32);
    fmt.setVersion(3, 3);
    fmt.setProfile(QGLFormat::CoreProfile);
    QGLFormat::setDefaultFormat(fmt);

    ofApp = new OFWidget(fmt);
    ofApp->resize(w,h);

    QRect screenres = QApplication::desktop()->screenGeometry(0);
    if (screenres.x() > 0) {
            ofApp->show();
            ofApp->setGeometry(screenres);
    } else {
            ofApp->show();
    }

    //ofApp_embedded = new OFWidget(s, 640, 480, true, this, ofApp);
    //ofApp_embedded->resize(640, 480);
    //this->gl_widget_space->addWidget(ofApp_embedded);
    //ofApp_embedded->show();
}

void MainWindow::setPortValue(const QString & inPortName, float value)
{
    string n(inPortName.toStdString());
    network::setPortValue(inPortName.toStdString(), value);
}

QString MainWindow::getNodeCfg(const QString & name)
{
    return QString("asdasd");
}

#include "System/library.h"

QString MainWindow::getResourceList(const QString & nodeName)
{
    // get type
    Library& l = Library::open();
    ResourceType type;
    QStringList list;

    if (nodeName == "RenderProgram") type = QBZ_RESOURCE_RENDERPROGRAM;
    else if (nodeName == "ModelFile") type = QBZ_RESOURCE_MODELFILE;
    else if (nodeName == "Texture") type = QBZ_RESOURCE_TEXTURE;
    else {
        std::cout << "no such type loaded in Library: " << nodeName.toStdString() << std::endl;
        return QString("");
    }

    std::vector<std::string> a(l.getResourceListByType(type));
    std::vector<std::string>::iterator i;
    for(i=a.begin(); i!=a.end(); ++i)
        list.append(i->c_str());
    return list.join(":");
}


QString MainWindow::bindComponents(const QString & type, const QString & fromPort, const QString & toPort)
{
    QString in, out;
    if (fromPort.startsWith("OUT")) {
        QStringList portParts = fromPort.split(".");
        portParts.removeFirst();
        out = portParts.join(".");
    } else out = fromPort;

    if (toPort.startsWith("IN")) {
        QStringList portParts(toPort.split("."));
        portParts.removeFirst();
        in = portParts.join(".");
    } else in = toPort;

    qDebug() << "(s): Binding " << out << " to " << in << " of type " << type;
    network::connectPorts(out.toStdString(), in.toStdString());
    return QString("boob");
}


QString MainWindow::addComponent(const QString & type, const QString & identifier)
{
    qDebug() << "type " << type << " :: identifier " << identifier;
    std::string nodeName(type.toStdString());
    std::string resourceName(identifier.toStdString());
    network::registerNode(
                Factory::createNode(nodeName, resourceName),
                resourceName
                );
    return QString("foo");
}

void MainWindow::fromQML(const QString & id, const QString &message)
{
    qDebug() << id << message;
}

void MainWindow::output(QString text, QString function)
{
	QString timestamped = "["+ function +"]: " + text;
	this->output_textedit->append(timestamped);
}
