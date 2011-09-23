#ifndef _QBZ_SHADER_H
#define _QBZ_SHADER_H

#define MAX_SHADER_DATA 4

#include "qbz.h"

namespace qbz {
    
    /* forward declares */
    
    class Model;
    class Camera;
    class Mesh;
    class Light;
    
    
    /* helper class */

	class ShaderStore {
	public:
		static ShaderStore* open();		
		QHash<QString, QGLShaderProgram*> shaders;
		QGLShaderProgram* get_or_load_shader(QString name);
	};
};

#endif
