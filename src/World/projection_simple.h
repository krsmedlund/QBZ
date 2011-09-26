#ifndef _QBZ_PROJECTION_SIMPLE_H
#define _QBZ_PROJECTION_SIMPLE_H

#include "World/model.h"

namespace qbz {
	
	class Projection_Simple : public Model {

	public:
		Projection_Simple(bool flip=false, float scale=1.0);

	private:
		vertex vertices[4];
		GLushort indices[4];
		GLint BL, BR, TR, TL, buffer_size;
	};
	
};

#endif
