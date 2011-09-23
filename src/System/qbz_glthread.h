#ifndef QBZ_GLTHREAD_H
#define QBZ_GLTHREAD_H

#include <QThread>
#include <QSize>

namespace qbz {
    class Composer;
};

class RenderWidget;


class GLThread : public QThread
{
    Q_OBJECT

public:
    GLThread(RenderWidget *);

    void run();
    void stop();
    void resizeViewport(const QSize & size);

private:
    int width;
    int height;

    qbz::Composer * composer;
    RenderWidget * glw;
    bool render, resize;
};


#endif
