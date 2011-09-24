#include "qbz.h"
#ifndef _QBZ_CAMERA_H
#define _QBZ_CAMERA_H

#include <glm/gtx/quaternion.hpp>
//#include <glm/gtx/inverse_transpose.hpp>


namespace qbz
{
    
    class Camera
    {
    public:
        Camera(const glm::vec3 & pos, const glm::vec3 & lookAt);

        void rotate(float yaw, float pitch);
        void move(float value);

        void setPosition(const glm::vec3 &pos);
        const glm::vec3& position() const;

        void setLookAt(const glm::vec3 &lookAt);
        const glm::vec3& lookAt() const;

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

}

#endif
