#include "RBOWrapper.h"

namespace andrick
{
	RBOWrapper::RBOWrapper()
	{
		createID();
	}

	RBOWrapper::~RBOWrapper()
	{

	}

	void RBOWrapper::bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, mID);
	}
	
	void RBOWrapper::unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void RBOWrapper::setStorage(const glm::vec2& size, EnumRBOStorageType storageType)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, DEPTH32_STENCIL8, static_cast<GLint>(size.x), static_cast<GLint>(size.y));
	}

	void RBOWrapper::createID()
	{
		glad_glGenRenderbuffers(1, &mID);
	}
}