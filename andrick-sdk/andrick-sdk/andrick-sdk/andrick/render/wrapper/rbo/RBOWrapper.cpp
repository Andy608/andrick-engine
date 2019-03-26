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

	void RBOWrapper::setStorage(const glm::ivec2& size, const EnumInternalFormatType& storageType)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, storageType, size.x, size.y);
	}

	void RBOWrapper::createID()
	{
		glad_glGenRenderbuffers(1, &mID);
	}
}