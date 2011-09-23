#ifndef QBZ_RENDERWIDGET_H
#define QBZ_RENDERWIDGET_H

#include <QGLWidget>
#include <QGLContext>>

#include "qbz_glthread.h"
#include "qbz.h"

class RenderWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit RenderWidget(QWidget *parent);
    void startRenderThread();
    void stopRenderThread();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

    GLThread glThread;
    const QGLContext * context;
};

#endif
