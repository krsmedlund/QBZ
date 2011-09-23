#ifndef _QBZ_H
#define _QBZ_H

#define QBZ_X_RES 1280
#define QBZ_Y_RES 720

#define QBZ_NATIVE
//#define	QBZ_OPENFRAMEWORKS
#define QBZ_ASSIMP

/* stdlib */
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <map>

/* GL */
//#include <opengl.h>

/* qt */
#include <QApplication>
#include <QMetaType>
#include <QKeyEvent>
#include <QWidget>
#include <QTimer>
#include <QThread>

#include <QGLWidget>
#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLFramebufferObject>
#include <QGLFramebufferObjectFormat>
#include <QGLPixelbuffer>

#include <QMatrix4x4>

#include <QtGui>
#include <QSlider>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTreeView>

#include <QtUiTools/QtUiTools>
#include <QtDeclarative>
#include <QDeclarativeView>


/* libraries */
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifdef QBZ_ASSIMP
    #include <assimp.hpp>
    #include <aiScene.h>
    #include <aiPostProcess.h>
#endif

namespace qbz { 

    enum ResourceType
    {
            QBZ_RESOURCE_TEXTURE,
            QBZ_RESOURCE_RENDERPROGRAM,
            QBZ_RESOURCE_POSTPROCESSOR,
    };

    struct vertex
	{
		struct world_position {
			GLfloat x, y, z;
		} position;
		
		struct texture_coordinate {
			GLfloat x, y, z;
		} texcoord;
		
		struct vertex_normal {
			GLfloat x,y,z;
		} normal;

        struct vertex_tangent {
			GLfloat x,y,z;
		} tangent;

        struct vertex_bitangent {
			GLfloat x,y,z;
		} bitangent;
        
		struct vertex_color {
			GLfloat r,g,b;
		} color;
        
        struct vertex_specular {
            GLfloat r,g,b,a;
        } specular;
        
        float shinyness;
    };
};

#endif
