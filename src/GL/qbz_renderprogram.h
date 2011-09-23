#ifndef _QBZ_RENDERPROGRAM_H
#define _QBZ_RENDERPROGRAM_H

#define MAX_SHADER_DATA 4

#include "qbz.h"
#include "qbz_network.h"


namespace qbz {

    namespace render { class RenderTarget; }
    
    class Model;
    class Camera;
    class Mesh;
    class ShaderStore;
    

    class RenderProgram : public network::NetworkNode
    {
	
    public:
        RenderProgram(QString name, bool is_pp=false);

        void Do();
        void drawObject(Model* model, Camera* cam=NULL);
        void set_uniforms();
        void set_attributes();
        void set_variables();
        void begin();
        void end();

        std::map<std::string, GLboolean> settings;
        std::map<std::string, GLint> locations;
        
        std::map<std::string, glm::mat4> _varMat4;
        std::map<std::string, glm::vec4> _varVec4;
        std::map<std::string, glm::vec3> _varVec3;
        std::map<std::string, glm::vec2> _varVec2;
        std::map<std::string, GLfloat> _varFloat;
        std::map<std::string, GLchar> _varChar;
        std::map<std::string, GLint> _varInt;
        
        void setRenderVariable(const std::string &name, GLfloat var) { _varFloat[name] = var; }
        void setRenderVariable(const std::string &name, GLchar var) { _varChar[name] = var; }
        void setRenderVariable(const std::string &name, GLint var) { _varInt[name] = var; }
        void setRenderVariable(const std::string &name, const glm::vec2 & var) { _varVec2[name] = var; }
        void setRenderVariable(const std::string &name, const glm::vec3 & var) { _varVec3[name] = var; }
        void setRenderVariable(const std::string &name, const glm::vec4 & var) { _varVec4[name] = var; }
        void setRenderVariable(const std::string &name, const glm::mat4 & var) { _varMat4[name] = var; }

        network::InPort *inPortModelData;
        network::OutPort *outPortRenderProgram;
        
        QGLShaderProgram* program;
        GLuint program_id;

        glm::vec3 lightColor;
        glm::vec3 lightPos;
        
        GLboolean is_postprocessor;

        glm::mat4 glViewMatrix;
        glm::mat4 glProjectionMatrix;
        glm::mat4 glModelViewMatrix;

	};
};

#endif
