#include "qbz_camera.h"

using namespace qbz;

qbz::Camera* _global_camera = NULL;

qbz::Camera* Camera::getGlobalCamera() {
    if (_global_camera == NULL) {
        _global_camera = new qbz::Camera( glm::vec3(0.0f, 1.5f, 0.0f), glm::vec3(0.0f, 0.0f, -2.0f) );
    }
    return _global_camera;
}


Camera::Camera(const glm::vec3 &pos, const glm::vec3 &look_at) {
    this->_position = glm::vec3(pos.x, pos.y, pos.z);
    this->_lookAt = glm::vec3(look_at.x, look_at.y, look_at.z);
    this->_direction = this->_lookAt - this->_position;
    this->glProjectionMatrix = glm::perspective(60.0f, 1280.0f / 720.0f, 1.0f, 1000.0f);
    this->glViewMatrix = glm::mat4(1.0);
    this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->getViewMatrix();
}


void Camera::rotate( float yaw, float pitch ) {
    glm::gtc::quaternion::quat q_rotate;
    q_rotate = glm::gtc::quaternion::rotate( q_rotate, yaw, glm::vec3( 0, 1, 0 ) );
    q_rotate = glm::gtc::quaternion::rotate( q_rotate, -pitch, glm::vec3( 1, 0, 0 ) );
    _direction = q_rotate * _direction;
    _lookAt = _position + _direction;
}

void Camera::move( float value ) {
    glm::vec3 norm = glm::normalize( _direction );
    norm *= value;
    _position += norm;
    _lookAt += norm;
}

const glm::vec3& Camera::position() const {
    return glm::normalize(_lookAt - _position);
    return _position;
}

const glm::vec3& Camera::lookAt() const {
    return _lookAt;
}

void Camera::setPosition( const glm::vec3 &pos ) {
    _position = pos;
    _direction = _lookAt - _position;
}

void Camera::setLookAt( const glm::vec3 &look_at ) {
    _lookAt = look_at;
    _direction = _lookAt - _position;
}

void Camera::getViewMatrix() {    
    glm::vec3 f(glm::normalize(_lookAt - _position)), 
                s(glm::normalize(glm::cross(f, glm::normalize(_up)))),          
                u(glm::normalize(glm::cross(s, f)));
    
    glm::mat4 m( s[0],  s[1],  s[2], 0,             
                u[0],  u[1],  u[2], 0,            
                -f[0], -f[1], -f[2], 0,                
                0,     0,     0, 1);
    this->glViewMatrix = glm::translate(glm::inverse(m), -_position);    
}


