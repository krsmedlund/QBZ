#include "qbz.h"
#ifndef _QBZ_CAMERA_H
#define _QBZ_CAMERA_H

#include <glm/gtx/quaternion.hpp>
//#include <glm/gtx/inverse_transpose.hpp>


namespace qbz {
    
    class Camera {
    public:
        Camera( const glm::vec3 &pos, const glm::vec3 &look_at );
        void rotate( float yaw, float pitch );
        void move( float value );
        const glm::vec3& position() const;
        const glm::vec3& lookAt() const;
        void setPosition( const glm::vec3 &pos );
        void setLookAt( const glm::vec3 &look_at );
        void getViewMatrix();

        glm::mat4 glViewMatrix;
        glm::mat4 glProjectionMatrix;
        glm::mat4 rotationMatrixInverse;
        glm::mat4 translationMatrixInverse;
        glm::mat4 rotationMatrix;
        
        glm::vec3 _position;
        glm::vec3 _lookAt;
        glm::vec3 _direction;
        glm::vec3 _up;
        
        static Camera* getGlobalCamera();
    };
    
    /*
class Camera {
public:
    
	Camera();
	Camera(float x, float y, float z);
    Camera(glm::vec3 eye);
    
    void rotate(float angle, float x, float y, float z);
    
	void moveTo(float x, float y, float z);
	void moveTo(glm::vec3 pos);
	
    void move(float x, float y, float z);
    void move(glm::vec3 offset);
    
    void lookAt(float x, float y, float z);
	void look(float x, float y, float z);

    void getViewMatrix();

	glm::mat4 identity;
	glm::mat4 glViewMatrix;
	glm::mat4 glProjectionMatrix;
    glm::mat4 rotationMatrixInverse;
    glm::mat4 translationMatrixInverse;

    glm::mat4 rotationMatrix;
    glm::mat4 transformMatrix;
    
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;
};
  */  
};

#endif
