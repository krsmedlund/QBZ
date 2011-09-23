#ifndef _QBZ_GLWIDGET_H
#define _QBZ_GLWIDGET_H

#include "qbz.h"
#include "qbz_baseapp.h"

namespace qbz {
class GLWidget : public QGLWidget {
    
	Q_OBJECT
    
	public:
	GLWidget(qbz::BaseApp*, QWidget* parent = 0);
	GLWidget(qbz::BaseApp*, int width, int height, QWidget* parent=0);
		QSize minimumSizeHint() const;
		QSize sizeHint() const;
	
	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);
	
		void draw() { qDebug() << "GLWidget::draw() : Implement me!\n"; }
		void setup() { qDebug() << "GLWidget::setup() : Implement me!\n"; }
		void update() { qDebug() << "GLWidget::update() : Implement me!\n"; }
	
		qbz::BaseApp* app;
		
		QTimer animationTimer;
	
		int width, height;
		
	protected slots:
		void animate();

}; 
};


#endif

