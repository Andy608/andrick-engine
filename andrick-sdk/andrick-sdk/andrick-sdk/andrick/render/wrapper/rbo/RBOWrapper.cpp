#include "RBOWrapper.h"

namespace andrick
{
	RBOWrapper::RBOWrapper()
	{
		createID();
	}

	RBOWrapper::~RBOWrapper()
	{
		glDeleteBuffers(1, &mID);
	}

	void RBOWrapper::bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, mID);
	}
	
	void RBOWrapper::unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void RBOWrapper::setStorage(const glm::ivec2& size, const EnumInternalFormatType& storageType)
	{
		bind();
		glRenderbufferStorage(GL_RENDERBUFFER, storageType, size.x, size.y);
		unbind();
	}

	void RBOWrapper::createID()
	{
		glGenRenderbuffers(1, &mID);
	}
}