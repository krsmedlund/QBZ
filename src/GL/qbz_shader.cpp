#include "GL/qbz_shader.h"
#include "System/mainwindow.h"

using namespace qbz;

static 	ShaderStore* shader_store_instance;

ShaderStore* ShaderStore::open() {
	if (!shader_store_instance) {
		shader_store_instance = new qbz::ShaderStore();
	}
	return shader_store_instance;
}


QGLShaderProgram* ShaderStore::get_or_load_shader(QString name) {
	
	if (this->shaders.contains(name)) {
		QString output = "Found shader " + name;
        qDebug() << "ShaderStore::get_or_load_shader" << output;
		return this->shaders[name];
	}
	
    const QGLContext* context = QGLContext::currentContext();

    QString vert_file = "data/";
	vert_file += name;
	vert_file.append(".vert");
	
	QString frag_file = "data/";
	frag_file += name;
	frag_file.append(".frag");
	
    QGLShaderProgram* program = new QGLShaderProgram(context);
	
	if (!program->addShaderFromSourceFile(QGLShader::Vertex, vert_file)) {
        qDebug() << "Error from vertex compile: " << program->log();
    } else if (!program->addShaderFromSourceFile(QGLShader::Fragment, frag_file)) {
        qDebug() << "Error from fragment compile: " << program->log();
	}else if (!program->link()) {
        qDebug() << "Error from linking: " << program->log();
	} else  {
		this->shaders[name] = program;
	}
	return program;
}
