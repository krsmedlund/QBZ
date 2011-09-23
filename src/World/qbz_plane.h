#ifndef _QBZ_PLANE_H
#define _QBZ_PLANE_H

#include "qbz.h"
#include "qbz_model.h"

namespace qbz {
	
	class Plane : public Model {

	public:
		Plane(int res);
		
	private:
		vertex* vertices;
		GLushort* indices;
		int x_res, y_res, quad_count, e_buffer_size, v_buffer_size;		
	};
	
};

#endif
