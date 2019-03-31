#include "RBOWrapper.h"

namespace andrick
{
	RBOWrapper::RBOWrapper() :
		mSampleSize(GLObjectWrapper::msDEFAULT_SAMPLE_SIZE)
	{
		createID();
	}

	void RBOWrapper::cleanup()
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
		setStorage(size.x, size.y, storageType);
	}

	void RBOWrapper::setStorage(const GLint& width, const GLint& height, const EnumInternalFormatType& storageType)
	{
		bind();
		mInternalFormatType = storageType;
		glRenderbufferStorage(GL_RENDERBUFFER, storageType, width, height);
		unbind();
	}
	
	void RBOWrapper::setStorageMultisample(const glm::ivec2& size,
		const EnumInternalFormatType& storageType, const GLuint& samples)
	{
		setStorageMultisample(size.x, size.y, storageType, samples);
	}

	void RBOWrapper::setStorageMultisample(const GLint& width, const GLint& height,
		const EnumInternalFormatType& storageType, const GLuint& samples)
	{
		mSampleSize = samples;

		bind();
		mInternalFormatType = storageType;
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, mSampleSize, storageType, width, height);
		unbind();
	}

	void RBOWrapper::resizeBuffer(const GLint& width, const GLint& height, const EnumTextureType& textureType)
	{
		if (textureType == EnumTextureType::TEXTURE_2D_MULTISAMPLE)
		{
			setStorageMultisample(width, height, mInternalFormatType, mSampleSize);
		}
		else
		{
			setStorage(width, height, mInternalFormatType);
		}
	}

	void RBOWrapper::createID()
	{
		glGenRenderbuffers(1, &mID);
	}
}