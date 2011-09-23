#include "qbz_glwidget.h"

using namespace qbz;

QTime* global_time;

void GLWidget::animate() {
	this->update();
    this->updateGL();
}

GLWidget::GLWidget(qbz::BaseApp* app, QWidget* parent) : QGLWidget(parent) {
	this->resize(QSize(width, height));
}

GLWidget::GLWidget(qbz::BaseApp* app, int w, int h, QWidget* parent) : QGLWidget(parent) {
    this->width = w;
    this->height = h;

	this->resize(QSize(width, height));

    global_time = new QTime;
    global_time->start();

}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    if (this->width > 0) {
        return QSize(this->width, this->height);
    }
    return QSize(800, 600);
}

void GLWidget::initializeGL() {
    this->makeCurrent();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	this->setup();
}

void GLWidget::resizeGL(int width, int height) {
    this->makeCurrent();
	glViewport(0, 0, (GLint)width, (GLint)height);
}

void GLWidget::paintGL () {
    this->makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
