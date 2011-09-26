#pragma once
#include "qbz.h"
#include "composer.h"

class OFWidget 
    : public QGLWidget
#ifdef QBZ_OPENFRAMEWORKS
    , public ofAppBaseWindow
#endif
{
    Q_OBJECT
    
public:
	OFWidget (QWidget* parent=0);
    OFWidget (const QGLFormat & fmt, bool is_embedded=false, QWidget* parent=0, QGLWidget* share_with=0);
	
    /* QT compability */
    QSize minimumSizeHint () const;
	QSize sizeHint () const;

    void hideCursor();
    void showCursor();
    bool event(QEvent*);

	qbz::Composer* scene;
	
    protected:
	void initializeGL ();
	void paintGL ();
	void resizeGL (int width, int height);
	void mousePressEvent (QMouseEvent* event);
	void mouseReleaseEvent (QMouseEvent* event);
	void mouseMoveEvent (QMouseEvent* event);
	void keyPressEvent (QKeyEvent* event);
	void keyReleaseEvent (QKeyEvent* event);

private:
	int width, height;
	QTimer *timer;
	int timerInterval;
	bool is_embedded;

};





