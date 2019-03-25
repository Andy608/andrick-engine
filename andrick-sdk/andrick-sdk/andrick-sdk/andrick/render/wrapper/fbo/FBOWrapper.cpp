#include "FBOWrapper.h"

namespace andrick
{
	FBOWrapper::FBOWrapper()
	{
		createID();
	}

	FBOWrapper::~FBOWrapper()
	{
		glDeleteBuffers(1, &mID);
	}

	void FBOWrapper::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mID);
	}

	void FBOWrapper::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FBOWrapper::attachRBO()
	{
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, );
	}

	void FBOWrapper::createID()
	{
		glGenFramebuffers(1, &mID);
	}
}