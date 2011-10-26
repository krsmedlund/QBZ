#ifndef QBZ_MAINWINDOW_H
#define QBZ_MAINWINDOW_H

#include "qbz.h"
#include "System/ofwidget.h"

namespace qbz {
    class Composer;
};


class MainWindow : public QWidget
{
    Q_OBJECT
	
public:
    MainWindow();
    MainWindow(QWidget *parent);
    ~MainWindow();

    void startGLWidget(int w, int h);
    void output(QString str, QString function);

    OFWidget* ofApp;
    OFWidget* ofApp_embedded;

private:
    QVBoxLayout* gl_widget_space;
    QTextEdit* output_textedit;
    qbz::Composer* scene;

protected slots:
    QString getResourceList(const QString & nodeName);
    void fromQML(const QString & id, const QString & message);
    QString getNodeCfg(const QString & name);
    QString addComponent(const QString & type, const QString & identifier);
    QString bindComponents(const QString & type, const QString & id1, const QString & id2);
    void setPortValue(const QString & inPortName, float value=1.0f);
	
};

#endif // MAINWINDOW_H
