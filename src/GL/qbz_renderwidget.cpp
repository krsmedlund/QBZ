#include "qbz_renderwidget.h"
#include "qbz_glthread.h"

RenderWidget::RenderWidget (QWidget * parent)
    : QGLWidget(parent),
      glThread(this)

{
    setAutoBufferSwap(false);
    resize(QSize(1280, 720));
    context = QGLContext::currentContext();
}

void RenderWidget::startRenderThread()
{
    glThread.start();
}

void RenderWidget::stopRenderThread()
{
    glThread.stop();
    glThread.wait();
}

void RenderWidget::resizeEvent(QResizeEvent * event)
{
    glThread.resizeViewport(event->size());
}

void RenderWidget::paintEvent(QPaintEvent *)
{
}

void RenderWidget::closeEvent(QCloseEvent *evt)
{
    stopRenderThread();
    QGLWidget::closeEvent(evt);
}
