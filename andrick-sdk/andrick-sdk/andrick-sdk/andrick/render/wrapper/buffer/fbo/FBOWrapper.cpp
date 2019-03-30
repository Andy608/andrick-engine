#include "FBOWrapper.h"
#include "../../../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string FBOWrapper::msCLASS_NAME = "FBOWrapper";

	FBOWrapper::FBOWrapper() :
		mCurrentBindType(EnumBindType::FRAMEBUFFER)
	{
		createID();
	}

	void FBOWrapper::cleanup()
	{
		glDeleteBuffers(1, &mID);
	}

	void FBOWrapper::bind()
	{
		bind(EnumBindType::FRAMEBUFFER);
	}

	void FBOWrapper::bind(EnumBindType bindType)
	{
		mCurrentBindType = bindType;
		glBindFramebuffer(bindType, mID);
	}

	void FBOWrapper::unbind()
	{
		glBindFramebuffer(mCurrentBindType, 0);
	}

	void FBOWrapper::attachTexture(TextureWrapper& texture, 
		const EnumBindType& bindType, 
		const EnumAttachmentType& attachmentType,
		const EnumTextureType& textureType)
	{
		mAttachedTextures.push_back(BoundTextureData(&texture, bindType, attachmentType, textureType));
		texture.generateGLTexture();
		glFramebufferTexture2D(bindType, attachmentType, textureType, texture.getID(), 0/*Mipmap level but for now we don't need or support fbo mipmapping*/);
	}

	void FBOWrapper::attachRBO(RBOWrapper& rboWrapper, const EnumAttachmentType& attachmentType)
	{
		mAttachedRBOs.push_back(BoundRBOData(&rboWrapper, attachmentType));
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, rboWrapper.getID());

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Framebuffer not complete!");
		}
	}

	void FBOWrapper::resizeBuffers(const GLint& width, const GLint& height)
	{
		bind();

		BoundTextureData texData;
		auto texIter = mAttachedTextures.begin();
		for (; texIter != mAttachedTextures.end(); ++texIter)
		{
			texData = *texIter;
			texData.texture->resizeBuffer(width, height);
			texData.texture->generateGLTexture();
			glFramebufferTexture2D(texData.bindType, texData.attachmentType, texData.textureType, texData.texture->getID(), 0/*Mipmap level but for now we don't need or support fbo mipmapping*/);
		}

		BoundRBOData rboData;
		auto rboIter = mAttachedRBOs.begin();
		for (; rboIter != mAttachedRBOs.end(); ++rboIter)
		{
			rboData = *rboIter;
			rboData.rbo->resizeBuffer(width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, rboData.attachmentType, GL_RENDERBUFFER, rboData.rbo->getID());

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Framebuffer not complete!");
			}
		}

		unbind();
	}

	void FBOWrapper::renderFBOToFBO(const FBOWrapper* readFBO, const FBOWrapper* writeFBO,
		const glm::ivec2& readSize, const glm::ivec2& writeSize,
		const GLuint& readStartX, const GLuint& readStartY,
		const GLuint& writeStartX, const GLuint& writeStartY)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, readFBO->getID());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, writeFBO->getID());
		glBlitFramebuffer(0, 0, readSize.x, readSize.y, 0, 0, writeSize.x, writeSize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void FBOWrapper::createID()
	{
		glGenFramebuffers(1, &mID);
	}
}