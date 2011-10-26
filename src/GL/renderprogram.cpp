#include "System/library.h"

#include "GL/renderprogram.h"
#include "GL/mesh.h"

#include "World/camera.h"
#include "World/model.h"

using namespace qbz;

const std::string& RenderProgram::getType()
{
    return "RenderProgram";
}

static qbz::network::NetworkNode* RenderProgramFactoryCreator(const std::string & nodeName)
{
    return new RenderProgram(nodeName);
}

static int foo = qbz::network::Factory::registerCreateFunction("RenderProgram", RenderProgramFactoryCreator);

RenderProgram::RenderProgram(const std::string & name, bool is_pp)
{
    std::string _uniform_names[] = { 
        "textures[0]",
        "textures[1]",
        "textures[2]",
        "textures[3]",
        "currentTime",
        "cameraPosition",
        "lightPos",
        "lightColor",
        "lightRadius",
        "shininess",
        "channel", 
        "p_matrix",
        "m_matrix",
        "v_matrix",
        "RotationMatrixInverse",
        "TransformMatrixInverse",
        "shadowTextureMatrix"
    };
    
    std::string _attribute_names[] = { 
        "position",
        "texcoord",
        "normal",
        "color",
        "tangent",
        "bitangent"
    };
    
    this->is_postprocessor = is_pp;
    this->program = Library::open().getShader(name);
    this->program_id = this->program->programId();

    
    for (int i=0; i < sizeof(_attribute_names) / sizeof(_attribute_names[0]); ++i) {        
        this->locations[_attribute_names[i]] = this->program->attributeLocation(_attribute_names[i].c_str());
        this->settings[_attribute_names[i]] = !(this->locations[_attribute_names[i]] == -1);
    }

    for (int i=0; i < sizeof(_uniform_names) / sizeof(_uniform_names[0]); ++i) {        
        this->locations[_uniform_names[i]] = this->program->uniformLocation(_uniform_names[i].c_str());
        this->settings[_uniform_names[i]] = !(this->locations[_uniform_names[i]] == -1);
    }

    inPorts["ModelData"] = network::registerInPort(name, "ModelData", 1, true);
    outPorts["RenderProgram"] = network::registerOutPort(name, "RenderProgram", this);
}


void RenderProgram::Do()
{
    if (inPorts["ModelData"]->connectedTo != 0) {
        qbz::Model* m = reinterpret_cast<qbz::Model*>(inPorts["ModelData"]->getValuePtr());
        drawObject(m);
    }
}

void RenderProgram::drawObject(Model* model, Camera* cam)
{
    
    glm::mat4 glNormalMatrix;

    if (cam == NULL)
        cam = Camera::getGlobalCamera();

    this->glModelViewMatrix = cam->glViewMatrix * model->model_matrix;

    if (this->settings["shadowTextureMatrix"])
    {
        glm::mat4 shadowMatrix(1.0);
        //shadowMatrix = glm::translate(shadowMatrix, glm::vec3(0.0f, 23.5f, 0.0f));
        shadowMatrix = glm::translate(shadowMatrix, glm::vec3(0.5f));
        shadowMatrix = glm::scale(shadowMatrix, glm::vec3(0.5f));

        //glm::mat4 bias(
        //    0.5, 0.0, 0.0, 0.0,
        //    0.0, 0.5, 0.0, 0.0,
        //    0.0, 0.0, 0.5, 0.0,
        //    0.5, 0.5, 0.5, 1.0);

        shadowMatrix *= glProjectionMatrix;
        shadowMatrix *= glViewMatrix * model->model_matrix;
        shadowMatrix *= glm::inverse(this->glModelViewMatrix);
        glUniformMatrix4fv(this->locations["shadowTextureMatrix"], 1, GL_FALSE, glm::value_ptr(shadowMatrix));
    }

    cam->getViewMatrix();
    this->glProjectionMatrix = cam->glProjectionMatrix;
    this->glViewMatrix = cam->glViewMatrix;

    model->rotationMatrixInverse = glm::inverse(model->rotate_matrix);
    model->model_matrix = model->translate_matrix * model->rotate_matrix * model->scale_matrix;
    Mesh* mesh = & (model->mesh);

    this->begin();

    if (this->settings["p_matrix"])                 glUniformMatrix4fv(this->locations["p_matrix"], 1, GL_FALSE, glm::value_ptr(this->glProjectionMatrix));
    if (this->settings["v_matrix"])                 glUniformMatrix4fv(this->locations["v_matrix"], 1, GL_FALSE, glm::value_ptr(this->glViewMatrix));
    if (this->settings["m_matrix"])                 glUniformMatrix4fv(this->locations["m_matrix"], 1, GL_FALSE, glm::value_ptr(model->model_matrix));
    if (this->settings["rotationMatrixInverse"])    glUniformMatrix4fv(this->locations["rotationMatrixInverse"], 1, GL_FALSE, glm::value_ptr(model->rotationMatrixInverse));
    if (this->settings["cameraPosition"])           glUniform3fv(this->locations["cameraPosition"], 1, glm::value_ptr(cam->position()));
    if (this->settings["currentTime"])              this->program->setUniformValue(this->locations["currentTime"], (float)QTime::currentTime().msec());
    if (this->settings["lightPos"])                 glUniform3fv(this->locations["lightPos"], 1, glm::value_ptr( _varVec3["lightPos"] ));
    if (this->settings["lightColor"])               glUniform3fv(this->locations["lightColor"], 1, glm::value_ptr( _varVec3["lightColor"] ));
    if (this->settings["lightRadius"])              this->program->setUniformValue(this->locations["lightRadius"], _varFloat["lightRadius"] );
    if (this->settings["shininess"])                this->program->setUniformValue(this->locations["shininess"], _varFloat["shininess"] );
    
    //if (this->settings["channel"]) this->program->setUniformValue(this->locations["channel"], *(this->channel));

    if (this->settings["textures[0]"]) {
        glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, model->material.texture[0]);
		this->program->setUniformValue(this->locations["textures[0]"], 0);
	}    
    if (this->settings["textures[1]"]) {
        glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, model->material.texture[1]);
		this->program->setUniformValue(this->locations["textures[1]"], 1);
	}
    if (this->settings["textures[2]"]) {
        glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, model->material.texture[2]);
        this->program->setUniformValue(this->locations["textures[2]"], 2);
	}
    if (this->settings["textures[3]"]) {
		glActiveTexture(GL_TEXTURE3_ARB);
                glBindTexture(GL_TEXTURE_2D, model->material.texture[3]);
        this->program->setUniformValue(this->locations["textures[3]"], 3);
	}

	mesh->bind();
	
	if (this->settings["position"]) {
		glVertexAttribPointer(
                  this->locations["position"],
                  3,
                  GL_FLOAT,
                  GL_FALSE,
                  sizeof(struct vertex),
                  (void*)offsetof(struct vertex, position)
                  );
		glEnableVertexAttribArray(this->locations["position"]);
	}
	
	if (this->settings["texcoord"]) {
		glVertexAttribPointer(
                  this->locations["texcoord"],
                  3,
                  GL_FLOAT,
                  GL_FALSE,
                  sizeof(struct vertex),
                  (void*)offsetof(struct vertex, texcoord)
                  );
		glEnableVertexAttribArray(this->locations["texcoord"]);
	}
	
	if (this->settings["normal"]) {
		glVertexAttribPointer(
                  this->locations["normal"],
                  3,
                  GL_FLOAT,
                  GL_FALSE,
                  sizeof(struct vertex),
                  (void*)offsetof(struct vertex, normal)
                  );
        glEnableVertexAttribArray(this->locations["normal"]);
	}	

	if (this->settings["tangent"]) {
		glVertexAttribPointer(
                  this->locations["tangent"],
                  3,
                  GL_FLOAT,
                  GL_FALSE,
                  sizeof(struct vertex),
                  (void*)offsetof(struct vertex, tangent)
                  );
        glEnableVertexAttribArray(this->locations["tangent"]);
	}	
	if (this->settings["bitangent"]) {
		glVertexAttribPointer(
                  this->locations["bitangent"],
                  3,
                  GL_FLOAT,
                  GL_FALSE,
                  sizeof(struct vertex),
                  (void*)offsetof(struct vertex, bitangent)
                  );
        glEnableVertexAttribArray(this->locations["bitangent"]);
	}	

	if (this->settings["color"]) {
		glVertexAttribPointer(
                 this->locations["color"],
                  3,
                  GL_FLOAT,
                  GL_FALSE,
                  sizeof(struct vertex),
                  (void*)offsetof(struct vertex, color)
                  );
		glEnableVertexAttribArray(this->locations["color"]);
	}
    
	/* execute shaders */
	
    glDrawElements(mesh->primitive_type,
				   mesh->element_buffer_data_length/2,
				   GL_UNSIGNED_SHORT,
				   (void*)0
				   );
	
	/* clean up */
	
	if (this->settings["position"]) glDisableVertexAttribArray(this->locations["position"]);
	if (this->settings["texcoord"]) glDisableVertexAttribArray(this->locations["texcoord"]);
	if (this->settings["normal"]) glDisableVertexAttribArray(this->locations["normal"]);
	if (this->settings["color"]) glDisableVertexAttribArray(this->locations["color"]);
	if (this->settings["tangent"]) glDisableVertexAttribArray(this->locations["tangent"]);
	if (this->settings["bitangent"]) glDisableVertexAttribArray(this->locations["bitangent"]);
	
	mesh->release();
    glBindTexture(GL_TEXTURE_2D, 0);

    this->end();
}

void RenderProgram::begin() {
	this->program->bind();
}

void RenderProgram::end() {
	this->program->release();
}
