#include "qbz_ofwidget.h"




int mouseButton;

#ifndef QBZ_OPENFRAMEWORKS
int	windowMode;
bool	bNewScreenMode;
float	timeNow, timeThen, fps;
 int	nFramesForFPS;
 int	nFrameCount;
 int	buttonInUse;
 bool	bEnableSetupScreen;
 bool	bFrameRateSet;
 int 	millisForFrame;
 int 	prevMillis;
 int 	diffMillis;
 float 	frameRate;
 double	lastFrameTime;
 int	requestedWidth;
 int	requestedHeight;
 int 	nonFullScreenX;
 int 	nonFullScreenY;
 int	windowW;
 int	windowH;
 int	mouseX, mouseY;
 int      nFramesSinceWindowResized;
#else
extern int	windowMode;
extern bool	bNewScreenMode;
extern float	timeNow, timeThen, fps;
extern int	nFramesForFPS;
extern int	nFrameCount;
extern int	buttonInUse;
extern bool	bEnableSetupScreen;
extern bool	bFrameRateSet;
extern int 	millisForFrame;
extern int 	prevMillis;
extern int 	diffMillis;
extern float 	frameRate;
extern double	lastFrameTime;
extern int	requestedWidth;
extern int	requestedHeight;
extern int 	nonFullScreenX;
extern int 	nonFullScreenY;
extern int	windowW;
extern int	windowH;
extern int	mouseX, mouseY;
extern int      nFramesSinceWindowResized;
#endif

QTime* global_time;


#include "qbz_midithread.h"

OFWidget::OFWidget(const QGLFormat & fmt, bool is_embedded, QWidget* parent, QGLWidget* share_with)
            : QGLWidget(fmt, parent, share_with)
{

    this->scene = new qbz::Composer();
    this->width = width;
    this->height = height;
    this->resize(sizeHint());
    this->scene = scene;
	this->is_embedded = is_embedded;

    if (!is_embedded) {
        MidiThread* midiThread = new MidiThread(this);
        midiThread->start();
        midiThread->setPriority(QThread::LowestPriority);
        global_time = new QTime;
        global_time->start();
        this->setFocusPolicy(Qt::StrongFocus);
    }
}

QSize OFWidget::minimumSizeHint () const {
    return QSize(this->width, this->height);
}

QSize OFWidget::sizeHint () const {
    return QSize(this->width, this->height);
}

void OFWidget::initializeGL ()
{
    this->makeCurrent();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glReadBuffer(GL_BACK);
    //glDrawBuffer(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(TRUE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glDisable(GL_STENCIL_TEST);
    glStencilMask(0xFFFFFFFF);
    glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    //glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    glClearDepth(1.0);
    glClearStencil(0);

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DITHER);

    if (!is_embedded) {
		this->scene->setup();
		this->scene->update();
	}
	
	this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    
    if (is_embedded) {
        timer->start(20);
    } else {
        timer->start(100);
    }


    QGLFormat appFmt = this->format();
    int num, depth;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &num);
    glGetIntegerv(GL_DEPTH_BITS, &depth);

    qDebug() << "Available openGL settings: " << appFmt.openGLVersionFlags();
    qDebug() << "Depth buffer " << QString(appFmt.depth() ? "yes" : "no") << " GL_DEPTH_BITS: " << depth;
    qDebug() << "Using GL version GL_VERSION: " << glGetString(GL_VERSION);
    std::cout << "Max texture units GL_MAX_TEXTURE_IMAGE_UNITS_ARB: " << num << std::endl;
}

void OFWidget::resizeGL (int width, int height) {
    height = height?height:1;
    this->height = height;
    this->width = width;
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void OFWidget::paintGL ()
{
    this->makeCurrent();
    if (!is_embedded)
    this->scene->update();
    this->is_embedded ? this->scene->draw_embedded() : this->scene->draw();

}

bool OFWidget::event(QEvent* event) 
{
    if (this->is_embedded)
        return QGLWidget::event(event);
    
    if (event->type() == MidiEvent::MidiType) {
        MidiEvent *me = static_cast<MidiEvent *>(event);
        this->scene->midiChanged(me->channel, me->value);
    }
    return QGLWidget::event(event);
}

void OFWidget::mouseMoveEvent(QMouseEvent* event) {
    mouseX = event->x();
    mouseY = this->height-event->y();
    if (mouseButton != -1) {
		this->scene->mousePressed(mouseX,mouseY,mouseButton);
		this->scene->mouseDragged(event->x(),this->height - event->y(),mouseButton);
		this->scene->mouseMoved(event->x(),this->height - event->y());
    } else {
		this->scene->mouseMoved(event->x(),this->height - event->y());
    }
}
void OFWidget::mousePressEvent (QMouseEvent* event) {
    mouseX = event->x();
    mouseY = this->height-event->y();
    mouseButton = event->button();
    this->scene->mousePressed(mouseX,mouseY,event->button());
}
void OFWidget::mouseReleaseEvent (QMouseEvent* event) {
    mouseX = event->x();
    mouseY = this->height-event->y();
    this->scene->mouseReleased(event->x(),this->height-event->y(),event->button());
    mouseButton = -1;
}
void OFWidget::keyPressEvent(QKeyEvent *e) {
	switch (e->key()) {
	case Qt::Key_Escape:
        close();
	default:
	    this->scene->keyPressed((int)e->text().toAscii()[0]);
    }
}
void OFWidget::keyReleaseEvent (QKeyEvent* event) {	
    this->scene->keyReleased((int)event->text().toAscii()[0]);
}
