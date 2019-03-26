#include "FBOWrapper.h"
#include "../../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string FBOWrapper::msCLASS_NAME = "FBOWrapper";

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

	void FBOWrapper::attachTexture(TextureWrapper& texture, const EnumBindType& bindType, const EnumAttachmentType& attachmentType)
	{
		texture.generateGLTexture();
		glFramebufferTexture2D(attachmentType, attachmentType, GL_TEXTURE_2D, texture.getID(), 0/*Mipmap level but for now we don't need or support fbo mipmapping*/);
	}

	void FBOWrapper::attachRBO(const RBOWrapper& rboWrapper, const EnumAttachmentType& attachmentType)
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, rboWrapper.getID());

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Framebuffer not complete!");
		}
	}

	void FBOWrapper::createID()
	{
		glGenFramebuffers(1, &mID);
	}
}