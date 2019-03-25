#include "VAOWrapper.h"
#include "../vbo/VBOWrapper.h"

namespace andrick
{
	VAOWrapper::VAOWrapper() :
		GLObjectWrapper()
	{
		createID();
	}

	VAOWrapper::~VAOWrapper()
	{
		glDeleteVertexArrays(1, &mID);
	}

	void VAOWrapper::bind()
	{
		glBindVertexArray(mID);
	}

	void VAOWrapper::unbind()
	{
		glBindVertexArray(0);
	}

	void VAOWrapper::bindVBOToVAO(GLuint bufferIndex, VBOWrapper* vbo)
	{
		vbo->bind();
		glVertexAttribPointer(bufferIndex, vbo->mElementsPerVertex, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vbo->mElementsPerVertex, (GLvoid*)0);
		glEnableVertexAttribArray(bufferIndex);
		vbo->unbind();
	}

	void VAOWrapper::createID()
	{
		glGenVertexArrays(1, &mID);
	}
}