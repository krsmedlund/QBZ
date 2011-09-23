#include "qbz_plane.h"
#include "qbz_world.h"
#include "cookies.h"

qbz::Model* model;
qbz::Camera* cam;
qbz::vertex* vertices;
qbz::Plane* plane;
GLushort* indices;

qbz::World* world;

qbz::Shader* model_renderer;
//qbz::Shader* wireframe_renderer;

extern QTime* global_time;

GLuint scene_list = 0;
const struct aiScene* scene = NULL;
struct aiVector3D scene_min, scene_max, scene_center;
static float angle = 0.f;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

float x_rot, y_rot, z_rot; 


void print_vertex(qbz::vertex v) {
	std::cout << "position {" << v.position.x << ", " << v.position.y << ", " << v.position.z << "}\n";
    //std::cout << "texcoord {" << v.texcoord.x << ", " << v.texcoord.y << "}\n";
    //std::cout << "normal {" << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << "}\n";
    //std::cout << "tangent {" << v.tangent.x << ", " << v.tangent.y << ", " << v.tangent.z << "}\n";

};

Cookies::Cookies(qbz::Animator* animator) {
    this->animator = animator;
}

#include <qbz_tgatexture.h>

void Cookies::setup() {
    
    model = world->newObject(MESH_FROM_FILE, "../../../data/untitled.obj");

	qbz::TGATexture* texture_loader = new qbz::TGATexture();
    
    model->set_texture0(texture_loader->make_texture("../../../data/diamond_pattern_brick_wall.jpg"));
    model->set_texture1(texture_loader->make_texture("../../../data/diamond_pattern_brick_wall_NRM.png"));
    model->set_texture2(texture_loader->make_texture("../../../data/diamond_pattern_brick_wall_SPEC.png"));
    model->set_texture3(texture_loader->make_texture("../../../data/envmap.png"));
    model->translate(-0.0f, -0.0f, -1.0f);
    
    plane = new qbz::Plane(10);
    plane->set_shader("model");
    plane->set_camera(cam);
    plane->set_texture0(texture_loader->make_texture("../../../data/lizard.jpg"));
    plane->set_texture1(texture_loader->make_texture("../../../data/lizard_NRM.png"));
    plane->set_texture2(texture_loader->make_texture("../../../data/lizard_SPEC.png"));
    plane->set_texture3(texture_loader->make_texture("../../../data/envmap.png"));
    plane->scale(20.0f, 20.0f, 1.0f);
    
    world->addObject(plane);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Cookies::update() {
	//model->rotate(2.5f, 1.5f, 1.0f, 2.0f);
}

void Cookies::draw_shadow() {
    model->draw();
}

void Cookies::draw() {
    //plane->draw();
    //model->draw();
    
    world->drawObjects();
}

void Cookies::mouseMoved( int x, int y ){}

int t_x = 0; 
int t_y = 0;

void Cookies::mouseDragged( int x, int y, int button ) {
    if (button == 2) {
        if (t_x == 0 && t_y == 0) {
            t_x = x;
            t_y = y;
        } else  {
            std::cout << "camera dragged, x-delta: "<< x - t_x <<endl;    
            std::cout << "camera dragged, y-delta: "<< y - t_y <<endl;
            cam->move((float)(x - t_x)/20.0f, (float)(y - t_y)/20.0f, sin((float)(y - t_y)/20.0f));
            t_x = x;
            t_y = y;
        }
    } else if (button == 4) {
        if (t_x == 0 && t_y == 0) {
            t_x = x;
            t_y = y;
        } else  {
            std::cout << "camera rotated, x-delta: "<< x - t_x <<endl;    
            std::cout << "camera rotated, y-delta: "<< y - t_y <<endl;    
            cam->look(-(float)(x - t_x)/20.0f, (float)(y - t_y)/20.0f, 0.0f);
            t_x = x;
            t_y = y;
        }
    } else if (button == 1) {
        if (t_x == 0 && t_y == 0) {
            t_x = x;
            t_y = y;
        } else  {
            std::cout << "camera rotated, x-delta: "<< x - t_x <<endl;    
            std::cout << "camera rotated, y-delta: "<< y - t_y <<endl;
            cam->move(-(float)(x - t_x)/20.0f, (float)(y - t_y)/20.0f, 0.0f);
            cam->look(-(float)(x - t_x)/20.0f, (float)(y - t_y)/20.0f, 0.0f);
            t_x = x;
            t_y = y;
        }
    }

}

void Cookies::mousePressed( int x, int y, int button ) {
	switch (button) {
		case 8:
			cam->move(0.0f, 0.0f, -1.0f);
            cam->look(0.0f, 0.0f, -1.0f);
			break;
		case 16:
			cam->move(0.0f, 0.0f, 1.0f);
            cam->look(0.0f, 0.0f, 1.0f);
			break;
	}
	std::cout << "mouse button " << button << " pressed\n";
}

void Cookies::mouseReleased(int x, int y, int button ) {
    t_x = t_y = 0;
}
