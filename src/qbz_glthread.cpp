#include "qbz_glthread.h"
#include "qbz_renderwidget.h"
#include "qbz_composer.h"


GLThread::GLThread (RenderWidget * glWidget)
    : QThread(0),
      glw(glWidget)
    {
    srand(QTime::currentTime().msec());

    qDebug() << "starting renderthread";

    this->composer = new qbz::Composer();
    this->composer->setup();
    resize = render = false;
}

void GLThread::stop()
{
    render = false;
}

void GLThread::resizeViewport(const QSize & size)
{
    width = size.width();
    height = size.height();
    resize = true;
}


void GLThread::run()
{
    while (render)
    {
        if (resize) {
            glViewport(0, 0, width, height);
            resize = false;
        }
        this->composer->update();
        this->composer->draw();

        glw->swapBuffers();
        msleep(40);
    }
}
