#ifndef _QBZ_LIGHTDOT_H
#define _QBZ_LIGHTDOT_H

#include "qbz_model.h"

namespace qbz {
	
	class LightDot : public Model {

	public:
		LightDot(float scale=1.0, glm::vec3 color=glm::vec3(1.0, 1.0, 1.0));

	private:
		vertex vertices[1024];
		GLushort indices[1024];
		GLint buffer_size;
	};
	
};

#endif
